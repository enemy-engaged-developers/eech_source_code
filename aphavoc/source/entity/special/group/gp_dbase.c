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

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "project.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const group_data
	group_database[NUM_ENTITY_SUB_TYPE_GROUPS] =
	{
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_GROUP_ATTACK_HELICOPTER
		//
		////////////////////////////////////////
		{
			"Attack Helicopters",								  			// full_name
			"Attack",															// group_short_name
			GROUP_CATEGORY_HELICOPTERS,									// group_category
			LIST_TYPE_AIR_REGISTRY,											// registery list
			LIST_TYPE_KEYSITE_GROUP,										// group list
			MOVEMENT_TYPE_AIR,                           			// .movement type
			ENTITY_SUB_TYPE_LANDING_HELICOPTER,							// landing type
			ENTITY_TYPE_HELICOPTER,											// default_entity_type
			ENTITY_SUB_TYPE_AIRCRAFT_AH64D_APACHE_LONGBOW, 			// default_blue_force_sub_type
			ENTITY_SUB_TYPE_AIRCRAFT_MI28N_HAVOC_B,	  				// default_red_force_sub_type
			FORMATION_ECHELON_LEFT,											// default_group_formation
			ENTITY_SUB_TYPE_DIVISION_HC_ATTACK_COMPANY,				// default_group_division
			5,																		// maximum_groups_per_division
			"N/A",																// platoon_name
			PLATOON_SHORT_NAME_CALLSIGN,									// platoon_short_name_type
			MAP_LAYER_CONTROL_AIRCRAFT,									// map layer type
			MAP_ICON_HELICOPTER,												// map icon type
			(60.0 * 1.0),														// rearming time
			GROUP_FRONTLINE_FLAG_NONE,										// frontline_flag (part of)
			FALSE,																// local_only_group
			TRUE,																	// default_engage_enemy
			TRUE,																	// amalgamate
			PLATOON_ID_CALLSIGN,												// platoon_id_type
			4,																		// maximum_member_count
			2, 																	// minimum_idle_count
			RESUPPLY_SOURCE_KEYSITE,										// resupply_source
			{                                               		// ai_stats
				6,                                           		// .air attack strength
				8,                                           		// .ground attack strength
				3,                                           		// .movement speed
				6,                                           		// .movement stealth
				0,																	// .cargo space
				0,																	// .troop space
			}
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_GROUP_MARINE_ATTACK_HELICOPTER
		//
		////////////////////////////////////////
		{
			"Marine Attack Helicopters",									// full_name
			"Marine Attack",													// group_short_name
			GROUP_CATEGORY_HELICOPTERS,									// group_category
			LIST_TYPE_AIR_REGISTRY,											// registery list
			LIST_TYPE_KEYSITE_GROUP,										// group list
			MOVEMENT_TYPE_AIR,                           			// .movement type
			ENTITY_SUB_TYPE_LANDING_HELICOPTER,							// landing type
			ENTITY_TYPE_HELICOPTER,                         		// default_entity_type
			ENTITY_SUB_TYPE_AIRCRAFT_AH1T_SEACOBRA,					// default_blue_force_sub_type
			ENTITY_SUB_TYPE_AIRCRAFT_KA29_HELIX_B,						// default_red_force_sub_type
			FORMATION_ECHELON_LEFT,											// default_group_formation
			ENTITY_SUB_TYPE_DIVISION_HC_ATTACK_COMPANY,				// default_group_division
			5,																		// maximum_groups_per_division
			"N/A",																// platoon_name
			PLATOON_SHORT_NAME_CALLSIGN,									// platoon_short_name_type
			MAP_LAYER_CONTROL_AIRCRAFT,									// map layer type
			MAP_ICON_HELICOPTER,												// map icon type
			(60.0 * 1.0),														// rearming time
			GROUP_FRONTLINE_FLAG_NONE,										// frontline_flag (part of)
			FALSE,																// local_only_group
			TRUE,																	// default_engage_enemy
			TRUE,																	// amalgamate
			PLATOON_ID_CALLSIGN,												// platoon_id_type
			4,																		// maximum_member_count
			0, 																	// minimum_idle_count
			RESUPPLY_SOURCE_KEYSITE,										// resupply_source
			{                                               		// ai_stats
				4,                                           		// .air attack strength
				5,                                           		// .ground attack strength
				3,                                           		// .movement speed
				6,                                           		// .movement stealth
				0,																	// .cargo space
				0,																	// .troop space
			}
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_GROUP_ASSAULT_HELICOPTER
		//
		////////////////////////////////////////
		{
			"Assault Helicopters",											// full_name
			"Assault",															// group_short_name
			GROUP_CATEGORY_HELICOPTERS,									// group_category
			LIST_TYPE_AIR_REGISTRY,											// registery list
			LIST_TYPE_KEYSITE_GROUP,										// group list
			MOVEMENT_TYPE_AIR,                           			// .movement type
			ENTITY_SUB_TYPE_LANDING_HELICOPTER,							// landing type
			ENTITY_TYPE_HELICOPTER,                         		// default_entity_type
			ENTITY_SUB_TYPE_AIRCRAFT_UH60_BLACK_HAWK,       		// default_blue_force_sub_type
			ENTITY_SUB_TYPE_AIRCRAFT_MI24D_HIND,            		// default_red_force_sub_type
			FORMATION_WEDGE,													// default_group_formation
			ENTITY_SUB_TYPE_DIVISION_HC_ATTACK_COMPANY,				// default_group_division
			5,																		// maximum_groups_per_division
			"N/A",																// platoon_name
			PLATOON_SHORT_NAME_CALLSIGN,									// platoon_short_name_type
			MAP_LAYER_CONTROL_AIRCRAFT,									// map layer type
			MAP_ICON_HELICOPTER,												// map icon type
			(60.0 * 1.0),														// rearming time
			GROUP_FRONTLINE_FLAG_NONE,										// frontline_flag (part of)
			FALSE,																// local_only_group
			TRUE,																	// default_engage_enemy
			TRUE,																	// amalgamate
			PLATOON_ID_CALLSIGN,												// platoon_id_type
			4,																		// maximum_member_count
			0, 																	// minimum_idle_count
			RESUPPLY_SOURCE_KEYSITE,										// resupply_source
			{                                               		// ai_stats
				0,                                           		// .air attack strength
				8,                                           		// .ground attack strength
				2,                                           		// .movement speed
				6,                                           		// .movement stealth
				0,																	// .cargo space
				10,																// .troop space
			}
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_GROUP_MARINE_ASSAULT_HELICOPTER
		//
		////////////////////////////////////////
		{
			"Marine Assault Helicopters",									// full_name
			"Marine Assault",													// group_short_name
			GROUP_CATEGORY_HELICOPTERS,									// group_category
			LIST_TYPE_AIR_REGISTRY,											// registery list
			LIST_TYPE_KEYSITE_GROUP,										// group list
			MOVEMENT_TYPE_AIR,                           			// .movement type
			ENTITY_SUB_TYPE_LANDING_HELICOPTER,							// landing type
			ENTITY_TYPE_HELICOPTER,                               // default_entity_type
			ENTITY_SUB_TYPE_AIRCRAFT_CH46E_SEA_KNIGHT,            // default_blue_force_sub_type
			ENTITY_SUB_TYPE_AIRCRAFT_KA29_HELIX_B,                // default_red_force_sub_type
			FORMATION_WEDGE,													// default_group_formation
			ENTITY_SUB_TYPE_DIVISION_HC_ATTACK_COMPANY,				// default_group_division
			5,																		// maximum_groups_per_division
			"N/A",																// platoon_name
			PLATOON_SHORT_NAME_CALLSIGN,									// platoon_short_name_type
			MAP_LAYER_CONTROL_AIRCRAFT,									// map layer type
			MAP_ICON_HELICOPTER,												// map icon type
			(60.0 * 1.0),														// rearming time
			GROUP_FRONTLINE_FLAG_NONE,										// frontline_flag (part of)
			FALSE,																// local_only_group
			TRUE,																	// default_engage_enemy
			TRUE,																	// amalgamate
			PLATOON_ID_CALLSIGN,												// platoon_id_type
			4,																		// maximum_member_count
			0, 																	// minimum_idle_count
			RESUPPLY_SOURCE_KEYSITE,										// resupply_source
			{                                               		// ai_stats
				0,                                           		// .air attack strength
				0,                                           		// .ground attack strength
				2,                                           		// .movement speed
				5,                                           		// .movement stealth
				4,																	// .cargo space
				0,																	// .troop space
			}
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_GROUP_RECON_HELICOPTER
		//
		////////////////////////////////////////
		{
			"Recon Helicopters",												// full_name
			"Recon",																// group_short_name
			GROUP_CATEGORY_HELICOPTERS,									// group_category
			LIST_TYPE_AIR_REGISTRY,											// registery list
			LIST_TYPE_KEYSITE_GROUP,										// group list
			MOVEMENT_TYPE_AIR,                           			// .movement type
			ENTITY_SUB_TYPE_LANDING_HELICOPTER,							// landing type
			ENTITY_TYPE_HELICOPTER,                         		// default_entity_type
			ENTITY_SUB_TYPE_AIRCRAFT_OH58D_KIOWA_WARRIOR,     		// default_blue_force_sub_type
			ENTITY_SUB_TYPE_AIRCRAFT_KA50_HOKUM,   	       		// default_red_force_sub_type
			FORMATION_ECHELON_LEFT,											// default_group_formation
			ENTITY_SUB_TYPE_DIVISION_HC_ATTACK_COMPANY,				// default_group_division
			5,																		// maximum_groups_per_division
			"N/A",																// platoon_name
			PLATOON_SHORT_NAME_CALLSIGN,									// platoon_short_name_type
			MAP_LAYER_CONTROL_AIRCRAFT,									// map layer type
			MAP_ICON_HELICOPTER,												// map icon type
			(60.0 * 1.0),														// rearming time
			GROUP_FRONTLINE_FLAG_NONE,										// frontline_flag (part of)
			FALSE,																// local_only_group
			TRUE,																	// default_engage_enemy
			TRUE,																	// amalgamate
			PLATOON_ID_CALLSIGN,												// platoon_id_type
			4,																		// maximum_member_count
			0, 																	// minimum_idle_count
			RESUPPLY_SOURCE_KEYSITE,										// resupply_source
			{                                               		// ai_stats
				0,                                           		// .air attack strength
				0,                                           		// .ground attack strength
				4,                                           		// .movement speed
				8,                                           		// .movement stealth
				0,																	// .cargo space
				0,																	// .troop space
			}
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_GROUP_RECON_ATTACK_HELICOPTER
		//
		////////////////////////////////////////
		{
			"Recon/Attack Helicopters",									// full_name
			"Recon/Attack",													// group_short_name
			GROUP_CATEGORY_HELICOPTERS,									// group_category
			LIST_TYPE_AIR_REGISTRY,											// registery list
			LIST_TYPE_KEYSITE_GROUP,										// group list
			MOVEMENT_TYPE_AIR,                           			// .movement type
			ENTITY_SUB_TYPE_LANDING_HELICOPTER,							// landing type
			ENTITY_TYPE_HELICOPTER,                         		// default_entity_type
			ENTITY_SUB_TYPE_AIRCRAFT_RAH66_COMANCHE,        		// default_blue_force_sub_type
			ENTITY_SUB_TYPE_AIRCRAFT_KA52_HOKUM_B,          		// default_red_force_sub_type
			FORMATION_ECHELON_LEFT,											// default_group_formation
			ENTITY_SUB_TYPE_DIVISION_HC_ATTACK_COMPANY,				// default_group_division
			5,																		// maximum_groups_per_division
			"N/A",																// platoon_name
			PLATOON_SHORT_NAME_CALLSIGN,									// platoon_short_name_type
			MAP_LAYER_CONTROL_AIRCRAFT,									// map layer type
			MAP_ICON_HELICOPTER,												// map icon type
			(60.0 * 1.0),														// rearming time
			GROUP_FRONTLINE_FLAG_NONE,										// frontline_flag (part of)
			FALSE,																// local_only_group
			TRUE,																	// default_engage_enemy
			TRUE,																	// amalgamate
			PLATOON_ID_CALLSIGN,												// platoon_id_type
			4,																		// maximum_member_count
			3, 																	// minimum_idle_count
			RESUPPLY_SOURCE_KEYSITE,										// resupply_source
			{                                               		// ai_stats
				7,                                           		// .air attack strength
				8,                                           		// .ground attack strength
				4,                                           		// .movement speed
				8,                                           		// .movement stealth
				0,																	// .cargo space
				0,																	// .troop space
			}
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_GROUP_MEDIUM_LIFT_TRANSPORT_HELICOPTER
		//
		////////////////////////////////////////
		{
			"Medium-Lift Transport Helicopters",						// full_name
			"Medium-Lift",														// group_short_name
			GROUP_CATEGORY_HELICOPTERS,									// group_category
			LIST_TYPE_AIR_REGISTRY,											// registery list
			LIST_TYPE_KEYSITE_GROUP,										// group list
			MOVEMENT_TYPE_AIR,                           			// .movement type
			ENTITY_SUB_TYPE_LANDING_HELICOPTER,							// landing type
			ENTITY_TYPE_HELICOPTER,                         		// default_entity_type
			ENTITY_SUB_TYPE_AIRCRAFT_CH3_JOLLY_GREEN_GIANT, 		// default_blue_force_sub_type
			ENTITY_SUB_TYPE_AIRCRAFT_MI17_HIP,              		// default_red_force_sub_type
			FORMATION_WEDGE,													// default_group_formation
			ENTITY_SUB_TYPE_DIVISION_HC_TRANSPORT_COMPANY,			// default_group_division
			5,																		// maximum_groups_per_division
			"N/A",																// platoon_name
			PLATOON_SHORT_NAME_CALLSIGN,									// platoon_short_name_type
			MAP_LAYER_CONTROL_AIRCRAFT,									// map layer type
			MAP_ICON_TRANSPORT_HELICOPTER,								// map icon type
			(60.0 * 1.0),														// rearming time
			GROUP_FRONTLINE_FLAG_NONE,										// frontline_flag (part of)
			FALSE,																// local_only_group
			FALSE,																// default_engage_enemy
			TRUE,																	// amalgamate
			PLATOON_ID_CALLSIGN,												// platoon_id_type
			2,																		// maximum_member_count
			0, 																	// minimum_idle_count
			RESUPPLY_SOURCE_KEYSITE,										// resupply_source
			{                                               		// ai_stats
				0,                                           		// .air attack strength
				0,                                           		// .ground attack strength
				1,                                           		// .movement speed
				4,                                           		// .movement stealth
				8,																	// .cargo space
				0,																	// .troop space
			}
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_GROUP_HEAVY_LIFT_TRANSPORT_HELICOPTER
		//
		////////////////////////////////////////
		{
			"Heavy-Lift Transport Helicopters",							// full_name
			"Heavy-Lift",														// group_short_name
			GROUP_CATEGORY_HELICOPTERS,									// group_category
			LIST_TYPE_AIR_REGISTRY,											// registery list
			LIST_TYPE_KEYSITE_GROUP,										// group list
			MOVEMENT_TYPE_AIR,                           			// .movement type
			ENTITY_SUB_TYPE_LANDING_HELICOPTER,							// landing type
			ENTITY_TYPE_HELICOPTER,                         		// default_entity_type
			ENTITY_SUB_TYPE_AIRCRAFT_CH47D_CHINOOK,         		// default_blue_force_sub_type
			ENTITY_SUB_TYPE_AIRCRAFT_MI6_HOOK,              		// default_red_force_sub_type
			FORMATION_WEDGE,													// default_group_formation
			ENTITY_SUB_TYPE_DIVISION_HC_TRANSPORT_COMPANY,			// default_group_division
			5,																		// maximum_groups_per_division
			"N/A",																// platoon_name
			PLATOON_SHORT_NAME_CALLSIGN,									// platoon_short_name_type
			MAP_LAYER_CONTROL_AIRCRAFT,									// map layer type
			MAP_ICON_TRANSPORT_HELICOPTER,								// map icon type
			(60.0 * 1.0),														// rearming time
			GROUP_FRONTLINE_FLAG_NONE,										// frontline_flag (part of)
			FALSE,																// local_only_group
			FALSE,																// default_engage_enemy
			TRUE,																	// amalgamate
			PLATOON_ID_CALLSIGN,												// platoon_id_type
			2,																		// maximum_member_count
			0, 																	// minimum_idle_count
			RESUPPLY_SOURCE_KEYSITE,										// resupply_source
			{                                               		// ai_stats
				0,                                           		// .air attack strength
				0,                                           		// .ground attack strength
				1,                                           		// .movement speed
				4,                                           		// .movement stealth
				10,																// .cargo space
				0,																	// .troop space
			}
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_GROUP_MULTI_ROLE_FIGHTER
		//
		////////////////////////////////////////
		{
			"Multi-Role Fighters",											// full_name
			"Fighter",															// group_short_name
			GROUP_CATEGORY_AIRCRAFT,										// group_category
			LIST_TYPE_AIR_REGISTRY,											// registery list
			LIST_TYPE_KEYSITE_GROUP,										// group list
			MOVEMENT_TYPE_AIR,                           			// .movement type
			ENTITY_SUB_TYPE_LANDING_FIXED_WING,							// landing type
			ENTITY_TYPE_FIXED_WING,                         		// default_entity_type
			ENTITY_SUB_TYPE_AIRCRAFT_F16_FIGHTING_FALCON,   		// default_blue_force_sub_type
			ENTITY_SUB_TYPE_AIRCRAFT_MIG29_FULCRUM,         		// default_red_force_sub_type
			FORMATION_ROW_LEFT,												// default_group_formation
			ENTITY_SUB_TYPE_DIVISION_FW_FIGHTER_COMPANY,				// default_group_division
			5,																		// maximum_groups_per_division
			"N/A",																// platoon_name
			PLATOON_SHORT_NAME_CALLSIGN,									// platoon_short_name_type
			MAP_LAYER_CONTROL_AIRCRAFT,									// map layer type
			MAP_ICON_JET,														// map icon type
			(60.0 * 1.0),														// rearming time
			GROUP_FRONTLINE_FLAG_NONE,										// frontline_flag (part of)
			FALSE,																// local_only_group
			TRUE,																	// default_engage_enemy
			TRUE,																	// amalgamate
			PLATOON_ID_CALLSIGN,												// platoon_id_type
			4,																		// maximum_member_count
			1, 																	// minimum_idle_count
			RESUPPLY_SOURCE_KEYSITE,										// resupply_source
			{                                               		// ai_stats
				10,                                           		// .air attack strength
				6,                                           		// .ground attack strength
				10,                                           		// .movement speed
				0,                                           		// .movement stealth
				0,																	// .cargo space
				0,																	// .troop space
			}
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_GROUP_CARRIER_BORNE_ATTACK_AIRCRAFT
		//
		////////////////////////////////////////
		{
			"Carrier-Borne Attack Aircraft",								// full_name
			"Navy Attack",														// group_short_name
			GROUP_CATEGORY_AIRCRAFT,										// group_category
			LIST_TYPE_AIR_REGISTRY,											// registery list
			LIST_TYPE_KEYSITE_GROUP,										// group list
			MOVEMENT_TYPE_AIR,                           			// .movement type
			ENTITY_SUB_TYPE_LANDING_FIXED_WING,							// landing type
			ENTITY_TYPE_FIXED_WING,                         		// default_entity_type
			ENTITY_SUB_TYPE_AIRCRAFT_AV8B_HARRIER,          		// default_blue_force_sub_type
			ENTITY_SUB_TYPE_AIRCRAFT_YAK41_FREESTYLE,  	    		// default_red_force_sub_type
			FORMATION_ROW_LEFT,												// default_group_formation
			ENTITY_SUB_TYPE_DIVISION_FW_FIGHTER_COMPANY,				// default_group_division
			5,																		// maximum_groups_per_division
			"N/A",																// platoon_name
			PLATOON_SHORT_NAME_CALLSIGN,									// platoon_short_name_type
			MAP_LAYER_CONTROL_AIRCRAFT,									// map layer type
			MAP_ICON_JET,														// map icon type
			(60.0 * 1.0),														// rearming time
			GROUP_FRONTLINE_FLAG_NONE,										// frontline_flag (part of)
			FALSE,																// local_only_group
			TRUE,																	// default_engage_enemy
			TRUE,																	// amalgamate
			PLATOON_ID_CALLSIGN,												// platoon_id_type
			4,																		// maximum_member_count
			1, 																	// minimum_idle_count
			RESUPPLY_SOURCE_KEYSITE,										// resupply_source
			{                                               		// ai_stats
				5,                                           		// .air attack strength
				8,                                           		// .ground attack strength
				8,                                           		// .movement speed
				0,                                           		// .movement stealth
				0,																	// .cargo space
				0,																	// .troop space
			}
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_GROUP_CARRIER_BORNE_INTERCEPTOR
		//
		////////////////////////////////////////
		{
			"Carrier-Borne Interceptors",									// full_name
			"Navy Fighter",													// group_short_name
			GROUP_CATEGORY_AIRCRAFT,										// group_category
			LIST_TYPE_AIR_REGISTRY,											// registery list
			LIST_TYPE_KEYSITE_GROUP,										// group list
			MOVEMENT_TYPE_AIR,                           			// .movement type
			ENTITY_SUB_TYPE_LANDING_FIXED_WING,							// landing type
			ENTITY_TYPE_FIXED_WING,                         		// default_entity_type
			ENTITY_SUB_TYPE_AIRCRAFT_FA18_HORNET,            		// default_blue_force_sub_type
			ENTITY_SUB_TYPE_AIRCRAFT_SU33_FLANKER,          		// default_red_force_sub_type
			FORMATION_ROW_LEFT,												// default_group_formation
			ENTITY_SUB_TYPE_DIVISION_FW_FIGHTER_COMPANY,				// default_group_division
			5,																		// maximum_groups_per_division
			"N/A",																// platoon_name
			PLATOON_SHORT_NAME_CALLSIGN,									// platoon_short_name_type
			MAP_LAYER_CONTROL_AIRCRAFT,									// map layer type
			MAP_ICON_JET,														// map icon type
			(60.0 * 1.0),														// rearming time
			GROUP_FRONTLINE_FLAG_NONE,										// frontline_flag (part of)
			FALSE,																// local_only_group
			TRUE,																	// default_engage_enemy
			TRUE,																	// amalgamate
			PLATOON_ID_CALLSIGN,												// platoon_id_type
			4,																		// maximum_member_count
			0, 																	// minimum_idle_count
			RESUPPLY_SOURCE_KEYSITE,										// resupply_source
			{                                               		// ai_stats
				10,                                           		// .air attack strength
				2,                                           		// .ground attack strength
				10,                                           		// .movement speed
				0,                                           		// .movement stealth
				0,																	// .cargo space
				0,																	// .troop space
			}
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_GROUP_CLOSE_AIR_SUPPORT_AIRCRAFT
		//
		////////////////////////////////////////
		{
			"Close Air Support Aircraft",									// full_name
			"CAS",																// group_short_name
			GROUP_CATEGORY_AIRCRAFT,										// group_category
			LIST_TYPE_AIR_REGISTRY,											// registery list
			LIST_TYPE_KEYSITE_GROUP,										// group list
			MOVEMENT_TYPE_AIR,                           			// .movement type
			ENTITY_SUB_TYPE_LANDING_FIXED_WING,							// landing type
			ENTITY_TYPE_FIXED_WING,                         		// default_entity_type
			ENTITY_SUB_TYPE_AIRCRAFT_A10A_THUNDERBOLT,      		// default_blue_force_sub_type
			ENTITY_SUB_TYPE_AIRCRAFT_SU25_FROGFOOT,         		// default_red_force_sub_type
			FORMATION_ROW_LEFT,												// default_group_formation
			ENTITY_SUB_TYPE_DIVISION_FW_ATTACK_COMPANY,				// default_group_division
			5,																		// maximum_groups_per_division
			"N/A",																// platoon_name
			PLATOON_SHORT_NAME_CALLSIGN,									// platoon_short_name_type
			MAP_LAYER_CONTROL_AIRCRAFT,									// map layer type
			MAP_ICON_JET,														// map icon type
			(60.0 * 1.0),														// rearming time
			GROUP_FRONTLINE_FLAG_NONE,										// frontline_flag (part of)
			FALSE,																// local_only_group
			TRUE,																	// default_engage_enemy
			TRUE,																	// amalgamate
			PLATOON_ID_CALLSIGN,												// platoon_id_type
			4,																		// maximum_member_count
			1, 																	// minimum_idle_count
			RESUPPLY_SOURCE_KEYSITE,										// resupply_source
			{                                               		// ai_stats
				0,                                           		// .air attack strength
				10,                                           		// .ground attack strength
				8,                                           		// .movement speed
				0,                                           		// .movement stealth
				0,																	// .cargo space
				0,																	// .troop space
			}
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_GROUP_MEDIUM_LIFT_TRANSPORT_AIRCRAFT
		//
		////////////////////////////////////////
		{
			"Medium-Lift Transport Aircraft",							// full_name
			"Medium-Lift",														// group_short_name
			GROUP_CATEGORY_AIRCRAFT,										// group_category
			LIST_TYPE_AIR_REGISTRY,											// registery list
			LIST_TYPE_KEYSITE_GROUP,										// group list
			MOVEMENT_TYPE_AIR,                           			// .movement type
			ENTITY_SUB_TYPE_LANDING_FIXED_WING_TRANSPORT,			// landing type
			ENTITY_TYPE_FIXED_WING,                         		// default_entity_type
			ENTITY_SUB_TYPE_AIRCRAFT_C130J_HERCULES_II,				// default_blue_force_sub_type
			ENTITY_SUB_TYPE_AIRCRAFT_AN12B_CUB,							// default_red_force_sub_type
			FORMATION_WEDGE,													// default_group_formation
			ENTITY_SUB_TYPE_DIVISION_FW_TRANSPORT_COMPANY,			// default_group_division
			5,																		// maximum_groups_per_division
			"N/A",																// platoon_name
			PLATOON_SHORT_NAME_CALLSIGN,									// platoon_short_name_type
			MAP_LAYER_CONTROL_AIRCRAFT,									// map layer type
			MAP_ICON_TRANSPORT_AIRCRAFT,									// map icon type
			(60.0 * 1.0),														// rearming time
			GROUP_FRONTLINE_FLAG_NONE,										// frontline_flag (part of)
			FALSE,																// local_only_group
			FALSE,																// default_engage_enemy
			TRUE,																	// amalgamate
			PLATOON_ID_CALLSIGN,												// platoon_id_type
			2,																		// maximum_member_count
			0, 																	// minimum_idle_count
			RESUPPLY_SOURCE_KEYSITE,										// resupply_source
			{                                               		// ai_stats
				0,                                           		// .air attack strength
				0,                                           		// .ground attack strength
				6,                                           		// .movement speed
				0,                                           		// .movement stealth
				8,																	// .cargo space
				0,																	// .troop space
			}
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_GROUP_HEAVY_LIFT_TRANSPORT_AIRCRAFT
		//
		////////////////////////////////////////
		{
			"Heavy-Lift Transport Aircraft",								// full_name
			"Heavy-Lift",														// group_short_name
			GROUP_CATEGORY_AIRCRAFT,										// group_category
			LIST_TYPE_AIR_REGISTRY,											// registery list
			LIST_TYPE_KEYSITE_GROUP,										// group list
			MOVEMENT_TYPE_AIR,                           			// .movement type
			ENTITY_SUB_TYPE_LANDING_FIXED_WING_TRANSPORT,			// landing type
			ENTITY_TYPE_FIXED_WING,                         		// default_entity_type
			ENTITY_SUB_TYPE_AIRCRAFT_C17_GLOBEMASTER_III,     		// default_blue_force_sub_type
			ENTITY_SUB_TYPE_AIRCRAFT_IL76MD_CANDID_B,         		// default_red_force_sub_type
			FORMATION_WEDGE,													// default_group_formation
			ENTITY_SUB_TYPE_DIVISION_FW_TRANSPORT_COMPANY,			// default_group_division
			5,																		// maximum_groups_per_division
			"N/A",																// platoon_name
			PLATOON_SHORT_NAME_CALLSIGN,									// platoon_short_name_type
			MAP_LAYER_CONTROL_AIRCRAFT,									// map layer type
			MAP_ICON_TRANSPORT_AIRCRAFT,									// map icon type
			(60.0 * 1.0),														// rearming time
			GROUP_FRONTLINE_FLAG_NONE,										// frontline_flag (part of)
			FALSE,																// local_only_group
			FALSE,																// default_engage_enemy
			TRUE,																	// amalgamate
			PLATOON_ID_CALLSIGN,												// platoon_id_type
			2,																		// maximum_member_count
			0, 																	// minimum_idle_count
			RESUPPLY_SOURCE_KEYSITE,										// resupply_source
			{                                               		// ai_stats
				0,                                           		// .air attack strength
				0,                                           		// .ground attack strength
				5,                                           		// .movement speed
				0,                                           		// .movement stealth
				10,																// .cargo space
				0,																	// .troop space
			}
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_GROUP_ANTI_AIRCRAFT
		//
		////////////////////////////////////////
		{
			"Air Defence Artillery",										// full_name
			"SAM/AAA",															// group_short_name
			GROUP_CATEGORY_ARMOUR,											// group_category
			LIST_TYPE_GROUND_REGISTRY,										// registery list
			LIST_TYPE_INDEPENDENT_GROUP,									// group list
			MOVEMENT_TYPE_GROUND,                          			// .movement type
			ENTITY_SUB_TYPE_LANDING_GROUND,								// landing type
			ENTITY_TYPE_ANTI_AIRCRAFT,   	                  		// default_entity_type
			ENTITY_SUB_TYPE_VEHICLE_M48A1_CHAPARRAL,        		// default_blue_force_sub_type
			ENTITY_SUB_TYPE_VEHICLE_SA13_GOPHER,            		// default_red_force_sub_type
			FORMATION_WEDGE,													// default_group_formation
			ENTITY_SUB_TYPE_DIVISION_ADA_COMPANY,						// default_group_division
			10,																	// maximum_groups_per_division
			"%s Battalion",													// platoon_name
			PLATOON_SHORT_NAME_ARMOUR,										// platoon_short_name_type
			MAP_LAYER_CONTROL_SAM_AAA,										// map layer type
			MAP_ICON_AAA,														// map icon type
			(60.0 * 1.0),														// rearming time
			GROUP_FRONTLINE_FLAG_NONE,										// frontline_flag (part of)
			TRUE,																	// local_only_group
			TRUE,																	// default_engage_enemy
			FALSE,																// amalgamate
			PLATOON_ID_NUMBER,												// platoon_id_type
			4,																		// maximum_member_count
			0, 																	// minimum_idle_count
			RESUPPLY_SOURCE_GROUP,											// resupply_source
			{                                               		// ai_stats
				10,                                           		// .air attack strength
				0,                                           		// .ground attack strength
				0,                                           		// .movement speed
				0,                                           		// .movement stealth
				0,																	// .cargo space
				0,																	// .troop space
			}
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_GROUP_PRIMARY_FRONTLINE
		//
		////////////////////////////////////////
		{
			"Frontline",														// full_name
			"Frontline",														// group_short_name
			GROUP_CATEGORY_ARMOUR,											// group_category
			LIST_TYPE_GROUND_REGISTRY,										// registery list
			LIST_TYPE_INDEPENDENT_GROUP,									// group list
			MOVEMENT_TYPE_GROUND,                          			// .movement type
			ENTITY_SUB_TYPE_LANDING_GROUND,								// landing type
			ENTITY_TYPE_ROUTED_VEHICLE,                     		// default_entity_type
			ENTITY_SUB_TYPE_VEHICLE_M1A2_ABRAMS,            		// default_blue_force_sub_type
			ENTITY_SUB_TYPE_VEHICLE_T80U,                   		// default_red_force_sub_type
			FORMATION_80M_ROAD_NODE_16_TANKS,							// default_group_formation
			ENTITY_SUB_TYPE_DIVISION_ARMOURED_COMPANY,				// default_group_division
			3,																		// maximum_groups_per_division
			"%s Battalion",													// platoon_name
			PLATOON_SHORT_NAME_ARMOUR,										// platoon_short_name_type
			MAP_LAYER_CONTROL_ARMOUR,										// map layer type
			MAP_ICON_TANK,														// map icon type
			(60.0 * 1.0),														// rearming time
			GROUP_FRONTLINE_FLAG_PRIMARY,									// frontline_flag (part of)
			FALSE,																// local_only_group
			TRUE,																	// default_engage_enemy
			TRUE,																	// amalgamate
			PLATOON_ID_NUMBER,												// platoon_id_type
			16,																	// maximum_member_count
			0, 																	// minimum_idle_count
			RESUPPLY_SOURCE_GROUP,											// resupply_source
			{                                               		// ai_stats
				6,                                           		// .air attack strength
				10,                                           		// .ground attack strength
				0,                                           		// .movement speed
				0,                                           		// .movement stealth
				0,																	// .cargo space
				0,																	// .troop space
			}
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_GROUP_SECONDARY_FRONTLINE
		//
		////////////////////////////////////////
		{
			"Support",															// full_name
			"Support",															// group_short_name
			GROUP_CATEGORY_ARMOUR,											// group_category
			LIST_TYPE_GROUND_REGISTRY,										// registery list
			LIST_TYPE_INDEPENDENT_GROUP,									// group list
			MOVEMENT_TYPE_GROUND,                          			// .movement type
			ENTITY_SUB_TYPE_LANDING_GROUND,								// landing type
			ENTITY_TYPE_ROUTED_VEHICLE,                     		// default_entity_type
			ENTITY_SUB_TYPE_VEHICLE_M1A2_ABRAMS,            		// default_blue_force_sub_type
			ENTITY_SUB_TYPE_VEHICLE_T80U,                   		// default_red_force_sub_type
			FORMATION_80M_ROAD_NODE_16_TANKS,							// default_group_formation
			ENTITY_SUB_TYPE_DIVISION_ARMOURED_COMPANY,				// default_group_division
			3,																		// maximum_groups_per_division
			"%s Battalion",													// platoon_name
			PLATOON_SHORT_NAME_ARMOUR,										// platoon_short_name_type
			MAP_LAYER_CONTROL_ARMOUR,										// map layer type
			MAP_ICON_APC,														// map icon type
			(60.0 * 1.0),														// rearming time
			GROUP_FRONTLINE_FLAG_SECONDARY,								// frontline_flag (part of)
			FALSE,																// local_only_group
			TRUE,																	// default_engage_enemy
			TRUE,																	// amalgamate
			PLATOON_ID_NUMBER,												// platoon_id_type
			16,																	// maximum_member_count
			0, 																	// minimum_idle_count
			RESUPPLY_SOURCE_GROUP,											// resupply_source
			{                                               		// ai_stats
				5,                                           		// .air attack strength
				7,                                           		// .ground attack strength
				0,                                           		// .movement speed
				0,                                           		// .movement stealth
				0,																	// .cargo space
				0,																	// .troop space
			}
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_GROUP_SELF_PROPELLED_ARTILLERY
		//
		////////////////////////////////////////
		{
			"Artillery",														// full_name
			"Artillery",														// group_short_name
			GROUP_CATEGORY_ARMOUR,											// group_category
			LIST_TYPE_GROUND_REGISTRY,										// registery list
			LIST_TYPE_INDEPENDENT_GROUP,									// group list
			MOVEMENT_TYPE_GROUND,                          			// .movement type
			ENTITY_SUB_TYPE_LANDING_GROUND,								// landing type
			ENTITY_TYPE_ROUTED_VEHICLE,                     		// default_entity_type
			ENTITY_SUB_TYPE_VEHICLE_M109A2,                 		// default_blue_force_sub_type
			ENTITY_SUB_TYPE_VEHICLE_2S19,                   		// default_red_force_sub_type
			FORMATION_80M_ROAD_NODE_16_TANKS,							// default_group_formation
			ENTITY_SUB_TYPE_DIVISION_ARTILLERY_COMPANY,				// default_group_division
			1,																		// maximum_groups_per_division
			"%s Battalion",													// platoon_name
			PLATOON_SHORT_NAME_ARMOUR,										// platoon_short_name_type
			MAP_LAYER_CONTROL_ARMOUR,										// map layer type
			MAP_ICON_ARTILLERY,												// map icon type
			(60.0 * 1.0),														// rearming time
			GROUP_FRONTLINE_FLAG_ARTILLERY,								// frontline_flag (part of)
			FALSE,																// local_only_group
			TRUE,																	// default_engage_enemy
			TRUE,																	// amalgamate
			PLATOON_ID_NUMBER,												// platoon_id_type
			4,																		// maximum_member_count
			0, 																	// minimum_idle_count
			RESUPPLY_SOURCE_GROUP,											// resupply_source
			{                                               		// ai_stats
				0,                                           		// .air attack strength
				10,                                           		// .ground attack strength
				0,                                           		// .movement speed
				0,                                           		// .movement stealth
				0,																	// .cargo space
				0,																	// .troop space
			}
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_GROUP_SELF_PROPELLED_MLRS
		//
		////////////////////////////////////////
		{
			"MLRS",																// full_name
			"MLRS",																// group_short_name
			GROUP_CATEGORY_ARMOUR,											// group_category
			LIST_TYPE_GROUND_REGISTRY,										// registery list
			LIST_TYPE_INDEPENDENT_GROUP,									// group list
			MOVEMENT_TYPE_GROUND,                          			// .movement type
			ENTITY_SUB_TYPE_LANDING_GROUND,								// landing type
			ENTITY_TYPE_ROUTED_VEHICLE,                     		// default_entity_type
			ENTITY_SUB_TYPE_VEHICLE_M270_MLRS,              		// default_blue_force_sub_type
			ENTITY_SUB_TYPE_VEHICLE_BM21_GRAD,							// default_red_force_sub_type
			FORMATION_80M_ROAD_NODE_16_TANKS,							// default_group_formation
			ENTITY_SUB_TYPE_DIVISION_ARTILLERY_COMPANY,				// default_group_division
			1,																		// maximum_groups_per_division
			"%s Battalion",													// platoon_name
			PLATOON_SHORT_NAME_ARMOUR,										// platoon_short_name_type
			MAP_LAYER_CONTROL_ARMOUR,										// map layer type
			MAP_ICON_ARTILLERY,												// map icon type
			(60.0 * 1.0),														// rearming time
			GROUP_FRONTLINE_FLAG_ARTILLERY,								// frontline_flag (part of)
			FALSE,																// local_only_group
			TRUE,																	// default_engage_enemy
			TRUE,																	// amalgamate
			PLATOON_ID_NUMBER,												// platoon_id_type
			4,																		// maximum_member_count
			0, 																	// minimum_idle_count
			RESUPPLY_SOURCE_GROUP,											// resupply_source
			{                                               		// ai_stats
				0,                                           		// .air attack strength
				10,                                           		// .ground attack strength
				0,                                           		// .movement speed
				0,                                           		// .movement stealth
				0,																	// .cargo space
				0,																	// .troop space
			}
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_GROUP_STATIC_INFANTRY
		//
		////////////////////////////////////////
		{
			"Infantry",															// full_name
			"Infantry",															// group_short_name
			NUM_GROUP_CATEGORY_TYPES,										// group_category
			LIST_TYPE_GROUND_REGISTRY,										// registery list
			LIST_TYPE_INDEPENDENT_GROUP,									// group list
			MOVEMENT_TYPE_GROUND,                          			// .movement type
			ENTITY_SUB_TYPE_LANDING_PEOPLE,								// landing type
			ENTITY_TYPE_ANTI_AIRCRAFT,	                     		// default_entity_type ; Static AAA people on buildings...
			ENTITY_SUB_TYPE_VEHICLE_US_INFANTRY_SAM_STANDING,		// default_blue_force_sub_type
			ENTITY_SUB_TYPE_VEHICLE_CIS_INFANTRY_SAM_STANDING, 	// default_red_force_sub_type
			FORMATION_WEDGE,													// default_group_formation
			ENTITY_SUB_TYPE_DIVISION_INFANTRY_COMPANY,				// default_group_division
			8,																		// maximum_groups_per_division
			"%c Company",														// platoon_name
			PLATOON_SHORT_NAME_ARMOUR,										// platoon_short_name_type
			MAP_LAYER_CONTROL_NONE,											// map layer type
			MAP_ICON_NONE,														// map icon type
			(60.0 * 1.0),														// rearming time
			GROUP_FRONTLINE_FLAG_NONE,										// frontline_flag (part of)
			TRUE,																	// local_only_group
			TRUE,																	// default_engage_enemy
			FALSE,																// amalgamate
			PLATOON_ID_LETTER,												// platoon_id_type
			1,																		// maximum_member_count
			0, 																	// minimum_idle_count
			RESUPPLY_SOURCE_NONE,											// resupply_source
			{                                               		// ai_stats
				6,                                           		// .air attack strength
				0,                                           		// .ground attack strength
				0,                                           		// .movement speed
				0,                                           		// .movement stealth
				0,																	// .cargo space
				0,																	// .troop space
			}
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_GROUP_INFANTRY
		//
		////////////////////////////////////////
		{
			"Infantry",															// full_name
			"Infantry",															// group_short_name
			NUM_GROUP_CATEGORY_TYPES,										// group_category
			LIST_TYPE_GROUND_REGISTRY,										// registery list
			LIST_TYPE_INDEPENDENT_GROUP,									// group list
			MOVEMENT_TYPE_GROUND,                          			// .movement type
			ENTITY_SUB_TYPE_LANDING_PEOPLE,								// landing type
			ENTITY_TYPE_PERSON,			                     		// default_entity_type
			ENTITY_SUB_TYPE_VEHICLE_US_INFANTRY,						// default_blue_force_sub_type
			ENTITY_SUB_TYPE_VEHICLE_CIS_INFANTRY, 						// default_red_force_sub_type
			FORMATION_WEDGE,													// default_group_formation
			ENTITY_SUB_TYPE_DIVISION_SPECIAL_FORCES_COMPANY,		// default_group_division
			4,																		// maximum_groups_per_division
			"%c Company",														// platoon_name
			PLATOON_SHORT_NAME_ARMOUR,										// platoon_short_name_type
			MAP_LAYER_CONTROL_NONE,											// map layer type
			MAP_ICON_NONE,														// map icon type
			(60.0 * 1.0),														// rearming time
			GROUP_FRONTLINE_FLAG_NONE,										// frontline_flag (part of)
			FALSE,																// local_only_group
			FALSE,																// default_engage_enemy
			FALSE,																// amalgamate
			PLATOON_ID_LETTER,												// platoon_id_type
			8,																		// maximum_member_count
			0, 																	// minimum_idle_count
			RESUPPLY_SOURCE_NONE,											// resupply_source
			{                                               		// ai_stats
				6,                                           		// .air attack strength
				0,                                           		// .ground attack strength
				0,                                           		// .movement speed
				0,                                           		// .movement stealth
				0,																	// .cargo space
				0,																	// .troop space
			}
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_GROUP_INFANTRY_PATROL
		//
		////////////////////////////////////////
		{
			"Infantry",															// full_name
			"Infantry",															// group_short_name
			NUM_GROUP_CATEGORY_TYPES,										// group_category
			LIST_TYPE_GROUND_REGISTRY,										// registery list
			LIST_TYPE_KEYSITE_GROUP,										// group list
			MOVEMENT_TYPE_GROUND,                          			// .movement type
			ENTITY_SUB_TYPE_LANDING_PEOPLE,								// landing type
			ENTITY_TYPE_PERSON,			                     		// default_entity_type
			ENTITY_SUB_TYPE_VEHICLE_US_INFANTRY,						// default_blue_force_sub_type
			ENTITY_SUB_TYPE_VEHICLE_CIS_INFANTRY, 						// default_red_force_sub_type
			FORMATION_WEDGE,													// default_group_formation
			ENTITY_SUB_TYPE_DIVISION_INFANTRY_COMPANY,				// default_group_division
			1,																		// maximum_groups_per_division
			"%c Company",														// platoon_name
			PLATOON_SHORT_NAME_ARMOUR,										// platoon_short_name_type
			MAP_LAYER_CONTROL_NONE,											// map layer type
			MAP_ICON_NONE,														// map icon type
			(60.0 * 1.0),														// rearming time
			GROUP_FRONTLINE_FLAG_NONE,										// frontline_flag (part of)
			FALSE,																// local_only_group
			FALSE,																// default_engage_enemy
			FALSE,																// amalgamate
			PLATOON_ID_LETTER,												// platoon_id_type
			8,																		// maximum_member_count
			0, 																	// minimum_idle_count
			RESUPPLY_SOURCE_NONE,											// resupply_source
			{                                               		// ai_stats
				6,                                           		// .air attack strength
				0,                                           		// .ground attack strength
				0,                                           		// .movement speed
				0,                                           		// .movement stealth
				0,																	// .cargo space
				0,																	// .troop space
			}
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_GROUP_ASSAULT_SHIP
		//
		////////////////////////////////////////
		{
			"Assault Ships",													// full_name
			"Assault",															// group_short_name
			GROUP_CATEGORY_WARSHIPS,										// group_category
			LIST_TYPE_SEA_REGISTRY,											// registery list
			LIST_TYPE_INDEPENDENT_GROUP,									// group list
			MOVEMENT_TYPE_SEA,                           			// .movement type
			ENTITY_SUB_TYPE_LANDING_SEA,									// landing type
			ENTITY_TYPE_SHIP_VEHICLE,                       		// default_entity_type
			ENTITY_SUB_TYPE_VEHICLE_TARAWA_CLASS,           		// default_blue_force_sub_type
			ENTITY_SUB_TYPE_VEHICLE_KIEV_CLASS,             		// default_red_force_sub_type
			FORMATION_COLUMN,													// default_group_formation
			ENTITY_SUB_TYPE_DIVISION_CARRIER_COMPANY,					// default_group_division
			5,																		// maximum_groups_per_division
			"%s",																	// platoon_name
			PLATOON_SHORT_NAME_KEYSITE,									// platoon_short_name_type
			MAP_LAYER_CONTROL_SHIPS,										// map layer type
			MAP_ICON_CARRIER,													// map icon type
			(60.0 * 1.0),														// rearming time
			GROUP_FRONTLINE_FLAG_NONE,										// frontline_flag (part of)
			FALSE,																// local_only_group
			TRUE,																	// default_engage_enemy
			FALSE,																// amalgamate
			PLATOON_ID_KEYSITE,												// platoon_id_type
			1,																		// maximum_member_count
			0, 																	// minimum_idle_count
			RESUPPLY_SOURCE_KEYSITE,										// resupply_source
			{                                               		// ai_stats
				10,                                           		// .air attack strength
				0,                                           		// .ground attack strength
				0,                                           		// .movement speed
				0,                                           		// .movement stealth
				0,																	// .cargo space
				0,																	// .troop space
			}
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_GROUP_FRIGATE
		//
		////////////////////////////////////////
		{
			"Frigates",															// full_name
			"Frigate",															// group_short_name
			GROUP_CATEGORY_WARSHIPS,										// group_category
			LIST_TYPE_SEA_REGISTRY,											// registery list
			LIST_TYPE_INDEPENDENT_GROUP,									// group list
			MOVEMENT_TYPE_SEA,                           			// .movement type
			ENTITY_SUB_TYPE_LANDING_SEA,									// landing type
			ENTITY_TYPE_SHIP_VEHICLE,                             // default_entity_type
			ENTITY_SUB_TYPE_VEHICLE_OLIVER_HAZARD_PERRY_CLASS,    // default_blue_force_sub_type
			ENTITY_SUB_TYPE_VEHICLE_KRIVAK_II_CLASS,              // default_red_force_sub_type
			FORMATION_COLUMN,													// default_group_formation
			ENTITY_SUB_TYPE_DIVISION_CARRIER_COMPANY,					// default_group_division
			5,																		// maximum_groups_per_division
			"Frigates (%s)",													// platoon_name
			PLATOON_SHORT_NAME_SHIPS,										// platoon_short_name_type
			MAP_LAYER_CONTROL_SHIPS,										// map layer type
			MAP_ICON_SHIP,														// map icon type
			(60.0 * 1.0),														// rearming time
			GROUP_FRONTLINE_FLAG_NONE,										// frontline_flag (part of)
			FALSE,																// local_only_group
			TRUE,																	// default_engage_enemy
			TRUE,																	// amalgamate
			PLATOON_ID_KEYSITE,												// platoon_id_type
			2,																		// maximum_member_count
			0, 																	// minimum_idle_count
			RESUPPLY_SOURCE_KEYSITE,										// resupply_source
			{                                               		// ai_stats
				8,                                           		// .air attack strength
				0,                                           		// .ground attack strength
				0,                                           		// .movement speed
				0,                                           		// .movement stealth
				0,																	// .cargo space
				0,																	// .troop space
			}
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_GROUP_LANDING_CRAFT
		//
		////////////////////////////////////////
		{
			"Landing Craft",													// full_name
			"LCU",																// group_short_name
			GROUP_CATEGORY_WARSHIPS,										// group_category
			LIST_TYPE_SEA_REGISTRY,											// registery list
			LIST_TYPE_INDEPENDENT_GROUP,									// group list
			MOVEMENT_TYPE_SEA,                           			// .movement type
			ENTITY_SUB_TYPE_LANDING_SEA,									// landing type
			ENTITY_TYPE_SHIP_VEHICLE,                             // default_entity_type
			ENTITY_SUB_TYPE_VEHICLE_LCAC,									// default_blue_force_sub_type
			ENTITY_SUB_TYPE_VEHICLE_AIST_CLASS,							// default_red_force_sub_type
			FORMATION_COLUMN,													// default_group_formation
			ENTITY_SUB_TYPE_DIVISION_CARRIER_COMPANY,					// default_group_division
			5,																		// maximum_groups_per_division
			"Landing Craft (%s)",											// platoon_name
			PLATOON_SHORT_NAME_SHIPS,										// platoon_short_name_type
			MAP_LAYER_CONTROL_SHIPS,										// map layer type
			MAP_ICON_SHIP,														// map icon type
			(60.0 * 1.0),														// rearming time
			GROUP_FRONTLINE_FLAG_NONE,										// frontline_flag (part of)
			FALSE,																// local_only_group
			FALSE,																// default_engage_enemy
			TRUE,																	// amalgamate
			PLATOON_ID_KEYSITE,												// platoon_id_type
			4,																		// maximum_member_count
			0, 																	// minimum_idle_count
			RESUPPLY_SOURCE_KEYSITE,										// resupply_source
			{                                               		// ai_stats
				0,                                           		// .air attack strength
				0,                                           		// .ground attack strength
				0,                                           		// .movement speed
				0,                                           		// .movement stealth
				0,																	// .cargo space
				0,																	// .troop space
			}
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_GROUP_BUILDINGS
		//
		////////////////////////////////////////
		{
			"Buildings",														// full_name
			"Buildings",														// group_short_name
			NUM_GROUP_CATEGORY_TYPES,										// group_category
			LIST_TYPE_INVALID,												// registery list
			LIST_TYPE_BUILDING_GROUP,										// group list
			MOVEMENT_TYPE_NONE,                           			// .movement type
			ENTITY_SUB_TYPE_LANDING_GROUND,								// landing type
			ENTITY_TYPE_SITE,													// default_entity_type
			ENTITY_SUB_TYPE_SITE_TARAWA,									// default_blue_force_sub_type
			ENTITY_SUB_TYPE_SITE_TARAWA,									// default_red_force_sub_type
			FORMATION_NONE,													// default_group_formation
			NUM_ENTITY_SUB_TYPE_DIVISIONS,								// default_group_division
			0,																		// maximum_groups_per_division
			"N/A",																// platoon_name
			PLATOON_SHORT_NAME_INVALID,									// platoon_short_name_type
			MAP_LAYER_CONTROL_NONE,											// map layer type
			MAP_ICON_NONE,														// map icon type
			0.0,																	// rearming time
			GROUP_FRONTLINE_FLAG_NONE,										// frontline_flag (part of)
			TRUE,																	// local_only_group
			FALSE,																// default_engage_enemy
			FALSE,																// amalgamate
			PLATOON_ID_NONE,													// platoon_id_type
			0,																		// maximum_member_count
			0, 																	// minimum_idle_count
			RESUPPLY_SOURCE_NONE,											// resupply_source
			{                                               		// ai_stats
				0,                                           		// .air attack strength
				0,                                           		// .ground attack strength
				0,                                           		// .movement speed
				0,                                           		// .movement stealth
				0,																	// .cargo space
				0,																	// .troop space
			}
		},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
