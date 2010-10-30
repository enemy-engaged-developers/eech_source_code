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
//
// Definition of Terms
// ===================
//
//	PRIMARY TASK			-		Main 'Mission' that requires the group to first take-off and then land upon completion,
//										is used to update force stats, and is given a rating upon completion,
//										may request escort, and may result in the group being linked to a new keysite.
//										A group can only have ONE primary task at any one time.
//
//	SOLO TASK				-		Each mobile doing this task will have it's own guide entity, e.g. Landing, Engage etc.
//
// PERSISTENT TASK		-		A Task that is not terminated / destroyed when a mobile completes it, e.g. Landing, Taking-off etc.
//
//	VISIBLE TASK			-		A Task that is shown to the user
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//VJ WUT mod bug, date: 26-mar-03
//remove "const" from definition
task_data
	task_database[NUM_ENTITY_SUB_TYPE_TASKS] =
	{
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_TASK_NOTHING,
		//
		////////////////////////////////////////

		"Nothing",													// Name
		"NOTHING",													// Short Name
		"",															// Key

		TASK_CATEGORY_MISC,										// task category

		0,																// task priority
		0,																// difficulty rating

		TASK_TARGET_CLASS_ALL,									// Task default target class type
		TASK_TARGET_SOURCE_NONE,								// Task default target source type
		TASK_TARGET_TYPE_NONE,									// Task default target type
		TASK_OBJECTIVE_INFO_NONE,								// Task Objective Info Type
		1,																// Minimum Member Count
		TASK_ROE_NONE,												// Rules Of Engagement
		FALSE,														// Engage Enemy
		ESCORT_NEVER,												// Escort Required Threshold
		COLOUR_WHITE,												// 2D waypoint route colour

		TRUE,															// add start waypoint
		FALSE,														// primary task
		FALSE,														// solo task
		FALSE,														// persistent task
		FALSE,														// visible task
		KEYSITE_AIR_FORCE_CAPACITY_NONE,						// keysite air force capacity
		TRUE,															// Assess landing on completion
		TRUE,															// Task route search
		FALSE,														// Perform debrief
		FALSE,														// delay task assignment
		TASK_OBJECTIVE_PREVIEW_NONE,							// task_objective_preview
		FALSE,														// counts_towards_player_log
		FALSE,														// wait_for_end_task
		0,																// player_reserve_factor

		100,															// Task pass percentage partial
		100,															// Task pass percentage success
		0,																// Task Completed Score

		MOVEMENT_TYPE_ALL,										// Movement Type

		// landing types
		0,
		
		// AI Stats
		{
			0,															// Air Attack strength
			0,															// Ground Attack strength
			0,															// Movement Speed
			0,															// Movement Stealth
			0,															// Cargo Space
			0,															// Troop Space
		},

		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_TASK_ADVANCE,
		//
		////////////////////////////////////////

		"Advance",													// Name
		"Advance",													// Short Name
		"ADV",														// Key

		TASK_CATEGORY_SUPPORT,									// task category

		9,																// task priority
		0,																// difficulty rating

		TASK_TARGET_CLASS_ALL,									// Task default target class type
		TASK_TARGET_SOURCE_SCAN_ALL,							// Default Task target source type
		TASK_TARGET_TYPE_MOBILE,								// Task default target type
		TASK_OBJECTIVE_INFO_NONE,								// Task Objective Info Type
		1,																// Minimum Member Count
		TASK_ROE_ALL,												// Rules Of Engagement
		FALSE,														// Engage Enemy
		ESCORT_NEVER,												// Escort Required Threshold
		COLOUR_WHITE,												// 2D waypoint route colour

		TRUE,															// add start waypoint
		TRUE,															// primary task
		FALSE,														// solo task
		FALSE,														// persistent task
		TRUE,															// visible task
		KEYSITE_AIR_FORCE_CAPACITY_NONE,						// keysite air force capacity
		FALSE,														// Assess landing on completion
		FALSE,														// Task route search
		TRUE,															// Perform debrief
		FALSE,														// delay task assignment
		TASK_OBJECTIVE_PREVIEW_NONE,							// task_objective_preview
		FALSE,														// counts_towards_player_log
		FALSE,														// wait_for_end_task
		0,																// player_reserve_factor

		100,															// Task pass percentage partial
		100,															// Task pass percentage success
		0,																// Task Completed Score

		MOVEMENT_TYPE_GROUND,									// Movement Type

		// landing types
		(1 << ENTITY_SUB_TYPE_LANDING_GROUND),
		
		// AI Stats
		{
			0,															// Air Attack strength
			0,															// Ground Attack strength
			0,															// Movement Speed
			0,															// Movement Stealth
			0,															// Cargo Space
			0,															// Troop Space
		},


		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_TASK_ANTI_SHIP_STRIKE,
		//
		////////////////////////////////////////

		"Anti-Ship Strike",										// Name
		"Anti-Ship Strike",										// Short Name
		"NST",														// Key

		TASK_CATEGORY_STRIKE,									// task category

		7,																// task priority
		4,																// difficulty rating

		TASK_TARGET_CLASS_GROUND,								// Task default target class type
		TASK_TARGET_SOURCE_NONE,								// Default Task target source type
		TASK_TARGET_TYPE_SHIP,									// Task default target type
		TASK_OBJECTIVE_INFO_ALWAYS_KNOWN,					// Task Objective Info Type
		2,																// Minimum Member Count
		TASK_ROE_ALL,												// Rules Of Engagement
		TRUE,															// Engage Enemy
		3,																// Escort Required Threshold
		COLOUR_WHITE,												// 2D waypoint route colour

		TRUE,															// add start waypoint
		TRUE,															// primary task
		FALSE,														// solo task
		FALSE,														// persistent task
		TRUE,															// visible task
		KEYSITE_AIR_FORCE_CAPACITY_SMALL,					// keysite air force capacity
		TRUE,															// Assess landing on completion
		TRUE,															// Task route search
		TRUE,															// Perform debrief
		TRUE,															// delay task assignment
		TASK_OBJECTIVE_PREVIEW_STILL,							// task_objective_preview
		TRUE,															// counts_towards_player_log
		TRUE,															// wait_for_end_task
		3,																// player_reserve_factor

		25,															// Task pass percentage partial
		50,															// Task pass percentage success
		750,															// Task Completed Score

		MOVEMENT_TYPE_AIR,										// Movement Type

		// landing types
		(1 << ENTITY_SUB_TYPE_LANDING_FIXED_WING) +
		(1 << ENTITY_SUB_TYPE_LANDING_HELICOPTER),
		
		// AI Stats
		{
			0,															// Air Attack strength
			5,															// Ground Attack strength
			3,															// Movement Speed
			0,															// Movement Stealth
			0,															// Cargo Space
			0,															// Troop Space
		},


		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_TASK_BAI
		//
		////////////////////////////////////////

		"Battlefield Air Interdiction",						// Name
		"BAI",														// Short Name
		"BAI",														// Key

		TASK_CATEGORY_STRIKE,									// task category

		4,																// task priority
		3,																// difficulty rating

		TASK_TARGET_CLASS_GROUND,								// Task default target class type
		TASK_TARGET_SOURCE_NONE,								// Default Task target source type
		TASK_TARGET_TYPE_VEHICLE,								// Task default target type
		TASK_OBJECTIVE_INFO_ALWAYS_KNOWN,					// Task Objective Info Type
		1,																// Minimum Member Count
		TASK_ROE_OBJECTIVE,										// Rules Of Engagement
		TRUE,															// Engage Enemy
		ESCORT_NEVER,												// Escort Required Threshold
		COLOUR_WHITE,												// 2D waypoint route colour

		TRUE,															// add start waypoint
		TRUE,															// primary task
		FALSE,														// solo task
		FALSE,														// persistent task
		TRUE,															// visible task
		KEYSITE_AIR_FORCE_CAPACITY_SMALL,					// keysite air force capacity
		TRUE,															// Assess landing on completion
		TRUE,															// Task route search
		TRUE,															// Perform debrief
		TRUE,															// delay task assignment
		TASK_OBJECTIVE_PREVIEW_STILL,							// task_objective_preview
		TRUE,															// counts_towards_player_log
		TRUE,															// wait_for_end_task
		2,																// player_reserve_factor

		25,															// Task pass percentage partial
		75,															// Task pass percentage success
		1000,															// Task Completed Score

		MOVEMENT_TYPE_AIR,										// Movement Type

		// landing types
		(1 << ENTITY_SUB_TYPE_LANDING_FIXED_WING) +
		(1 << ENTITY_SUB_TYPE_LANDING_HELICOPTER),
		
		// AI Stats
		{
			0,															// Air Attack strength
			6,															// Ground Attack strength
			2,															// Movement Speed
			0,															// Movement Stealth
			0,															// Cargo Space
			0,															// Troop Space
		},


		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_TASK_BARCAP
		//
		////////////////////////////////////////

		"Barrier Combat Air Patrol",							// Name
		"BARCAP",													// Short Name
		"BAR",														// Key

		TASK_CATEGORY_SUPPORT,									// task category

		7,																// task priority
		1,																// difficulty rating

		TASK_TARGET_CLASS_AIR,									// Task default target class type
		TASK_TARGET_SOURCE_SCAN_AIR,							// Default Task target source type
		TASK_TARGET_TYPE_AIRBORNE_AIRCRAFT,					// Task default target type
		TASK_OBJECTIVE_INFO_ALWAYS_KNOWN,					// Task Objective Info Type
		1,																// Minimum Member Count
		TASK_ROE_ALL,												// Rules Of Engagement
		TRUE,															// Engage Enemy
		ESCORT_NEVER,												// Escort Required Threshold
		COLOUR_WHITE,												// 2D waypoint route colour

		TRUE,															// add start waypoint
		TRUE,															// primary task
		FALSE,														// solo task
		FALSE,														// persistent task
		TRUE,															// visible task
		KEYSITE_AIR_FORCE_CAPACITY_SMALL,					// keysite air force capacity
		TRUE,															// Assess landing on completion
		TRUE,															// Task route search
		TRUE,															// Perform debrief
		TRUE,															// delay task assignment
		TASK_OBJECTIVE_PREVIEW_NONE,							// task_objective_preview
		TRUE,															// counts_towards_player_log
		FALSE,														// wait_for_end_task
		0,																// player_reserve_factor

		100,															// Task pass percentage partial
		100,															// Task pass percentage success
		0,																// Task Completed Score

		MOVEMENT_TYPE_AIR,										// Movement Type

		// landing types
		(1 << ENTITY_SUB_TYPE_LANDING_FIXED_WING) +
		(1 << ENTITY_SUB_TYPE_LANDING_HELICOPTER),
		
		// AI Stats
		{
			6,															// Air Attack strength
			0,															// Ground Attack strength
			3,															// Movement Speed
			0,															// Movement Stealth
			0,															// Cargo Space
			0,															// Troop Space
		},


		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_TASK_BDA,
		//
		////////////////////////////////////////

		"Battle Damage Assessment",							// Name
		"BDA",														// Short Name
		"BDA",														// Key

		TASK_CATEGORY_RECON,										// task category

		9,																// task priority
		1,																// difficulty rating

		TASK_TARGET_CLASS_ALL,									// Task default target class type
		TASK_TARGET_SOURCE_NONE,								// Default Task target source type
		TASK_TARGET_TYPE_NONE,									// Task default target type
		TASK_OBJECTIVE_INFO_ALWAYS_KNOWN,					// Task Objective Info Type
		1,																// Minimum Member Count
		TASK_ROE_NONE,												// Rules Of Engagement
		FALSE,														// Engage Enemy
		ESCORT_NEVER,												// Escort Required Threshold
		COLOUR_WHITE,												// 2D waypoint route colour

		TRUE,															// add start waypoint
		TRUE,															// primary task
		FALSE,														// solo task
		FALSE,														// persistent task
		TRUE,															// visible task
		KEYSITE_AIR_FORCE_CAPACITY_SMALL,					// keysite air force capacity
		TRUE,															// Assess landing on completion
		TRUE,															// Task route search
		TRUE,															// Perform debrief
		TRUE,															// delay task assignment
		TASK_OBJECTIVE_PREVIEW_NONE,							// task_objective_preview
		TRUE,															// counts_towards_player_log
		FALSE,														// wait_for_end_task
		3,																// player_reserve_factor

		100,															// Task pass percentage partial
		100,															// Task pass percentage success
		1000,															// Task Completed Score

		MOVEMENT_TYPE_AIR,										// Movement Type

		// landing types
		(1 << ENTITY_SUB_TYPE_LANDING_HELICOPTER),
		
		// AI Stats
		{
			0,															// Air Attack strength
			0,															// Ground Attack strength
			3,															// Movement Speed
			5,															// Movement Stealth
			0,															// Cargo Space
			0,															// Troop Space
		},


		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_TASK_CLOSE_AIR_SUPPORT
		//
		////////////////////////////////////////

		"Close Air Support",										// Name
		"CAS",														// Short Name
		"CAS",														// Key

		TASK_CATEGORY_STRIKE,									// task category

		6,																// task priority
		3,																// difficulty rating

		TASK_TARGET_CLASS_GROUND,								// Task default target class type
		TASK_TARGET_SOURCE_NONE,								// Default Task target source type
		TASK_TARGET_TYPE_VEHICLE,								// Task default target type
		TASK_OBJECTIVE_INFO_ALWAYS_KNOWN,					// Task Objective Info Type
		2,																// Minimum Member Count
		TASK_ROE_OBJECTIVE,										// Rules Of Engagement
		TRUE,															// Engage Enemy
		ESCORT_NEVER,												// Escort Required Threshold
		COLOUR_WHITE,												// 2D waypoint route colour

		TRUE,															// add start waypoint
		TRUE,															// primary task
		FALSE,														// solo task
		FALSE,														// persistent task
		TRUE,															// visible task
		KEYSITE_AIR_FORCE_CAPACITY_SMALL,					// keysite air force capacity
		TRUE,															// Assess landing on completion
		TRUE,															// Task route search
		TRUE,															// Perform debrief
		TRUE,															// delay task assignment
		TASK_OBJECTIVE_PREVIEW_STILL,							// task_objective_preview
		TRUE,															// counts_towards_player_log
		TRUE,															// wait_for_end_task
		2,																// player_reserve_factor

		25,															// Task pass percentage partial
		75,															// Task pass percentage success
		1000,															// Task Completed Score

		MOVEMENT_TYPE_AIR,										// Movement Type

		// landing types
		(1 << ENTITY_SUB_TYPE_LANDING_FIXED_WING) +
		(1 << ENTITY_SUB_TYPE_LANDING_HELICOPTER),
		
		// AI Stats
		{
			0,															// Air Attack strength
			8,															// Ground Attack strength
			2,															// Movement Speed
			0,															// Movement Stealth
			0,															// Cargo Space
			0,															// Troop Space
		},


		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_TASK_COASTAL_PATROL,
		//
		////////////////////////////////////////

		"Coastal Patrol",											// Name
		"Patrol",													// Short Name
		"CPTL",														// Key

		TASK_CATEGORY_SUPPORT,									// task category

		1,																// task priority
		0,																// difficulty rating

		TASK_TARGET_CLASS_ALL,									// Task default target class type
		TASK_TARGET_SOURCE_NONE,								// Default Task target source type
		TASK_TARGET_TYPE_NONE,									// Task default target type
		TASK_OBJECTIVE_INFO_NONE,								// Task Objective Info Type
		1,																// Minimum Member Count
		TASK_ROE_ALL,												// Rules Of Engagement
		FALSE,														// Engage Enemy
		ESCORT_NEVER,												// Escort Required Threshold
		COLOUR_WHITE,												// 2D waypoint route colour

		TRUE,															// add start waypoint
		TRUE,															// primary task
		FALSE,														// solo task
		FALSE,														// persistent task
		TRUE,															// visible task
		KEYSITE_AIR_FORCE_CAPACITY_NONE,						// keysite air force capacity
		TRUE,															// Assess landing on completion
		TRUE,															// Task route search
		TRUE,															// Perform debrief
		TRUE,															// delay task assignment
		TASK_OBJECTIVE_PREVIEW_NONE,							// task_objective_preview
		FALSE,														// counts_towards_player_log
		FALSE,														// wait_for_end_task
		0,																// player_reserve_factor

		100,															// Task pass percentage partial
		100,															// Task pass percentage success
		0,																// Task Completed Score

		MOVEMENT_TYPE_SEA,										// Movement Type

		// landing types
		(1 << ENTITY_SUB_TYPE_LANDING_SEA),
		
		// AI Stats
		{
			0,															// Air Attack strength
			0,															// Ground Attack strength
			0,															// Movement Speed
			0,															// Movement Stealth
			0,															// Cargo Space
			0,															// Troop Space
		},


		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_TASK_COMBAT_AIR_PATROL
		//
		////////////////////////////////////////

		"Combat Air Patrol",										// Name
		"CAP",														// Short Name
		"CAP",														// Key

		TASK_CATEGORY_SUPPORT,									// task category

		5,																// task priority
		1,																// difficulty rating

		TASK_TARGET_CLASS_AIR,									// Task default target class type
		TASK_TARGET_SOURCE_SCAN_AIR,							// Default Task target source type
		TASK_TARGET_TYPE_AIRBORNE_AIRCRAFT,					// Task default target type
		TASK_OBJECTIVE_INFO_ALWAYS_KNOWN,					// Task Objective Info Type
		1,																// Minimum Member Count
		TASK_ROE_ALL,												// Rules Of Engagement
		TRUE,															// Engage Enemy
		ESCORT_NEVER,												// Escort Required Threshold
		COLOUR_WHITE,												// 2D waypoint route colour

		TRUE,															// add start waypoint
		TRUE,															// primary task
		FALSE,														// solo task
		FALSE,														// persistent task
		TRUE,															// visible task
		KEYSITE_AIR_FORCE_CAPACITY_SMALL,					// keysite air force capacity
		TRUE,															// Assess landing on completion
		TRUE,															// Task route search
		TRUE,															// Perform debrief
		TRUE,															// delay task assignment
		TASK_OBJECTIVE_PREVIEW_NONE,							// task_objective_preview
		TRUE,															// counts_towards_player_log
		FALSE,														// wait_for_end_task
		3,																// player_reserve_factor

		100,															// Task pass percentage partial
		100,															// Task pass percentage success
		750,															// Task Completed Score

		MOVEMENT_TYPE_AIR,										// Movement Type

		// landing types
		(1 << ENTITY_SUB_TYPE_LANDING_FIXED_WING) +
		(1 << ENTITY_SUB_TYPE_LANDING_HELICOPTER),
		
		// AI Stats
		{
			6,															// Air Attack strength
			0,															// Ground Attack strength
			0,															// Movement Speed
			0,															// Movement Stealth
			0,															// Cargo Space
			0,															// Troop Space
		},


		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_TASK_ENGAGE,
		//
		////////////////////////////////////////

		"Engage",													// Name
		"Engage",													// Short Name
		"ENG",														// Key

		TASK_CATEGORY_MISC,										// task category

		10,															// task priority
		0,																// difficulty rating

		TASK_TARGET_CLASS_ALL,									// Task default target class type
		TASK_TARGET_SOURCE_TASK_OBJECTIVE,					// Default Task target source type
		TASK_TARGET_TYPE_ANY,									// Task default target type
		TASK_OBJECTIVE_INFO_ALWAYS_KNOWN,					// Task Objective Info Type
		1,																// Minimum Member Count
		TASK_ROE_OBJECTIVE,										// Rules Of Engagement
		TRUE,															// Engage Enemy
		ESCORT_NEVER,												// Escort Required Threshold
		COLOUR_RED,													// 2D waypoint route colour

		FALSE,														// add start waypoint
		FALSE,														// primary task
		TRUE,															// solo task
		FALSE,														// persistent task
		FALSE,														// visible task
		KEYSITE_AIR_FORCE_CAPACITY_NONE,						// keysite air force capacity
		FALSE,														// Assess landing on completion
		FALSE,														// Task route search
		FALSE,														// Perform debrief
		FALSE,														// delay task assignment
		TASK_OBJECTIVE_PREVIEW_NONE,							// task_objective_preview
		FALSE,														// counts_towards_player_log
		FALSE,														// wait_for_end_task
		0,																// player_reserve_factor

		100,															// Task pass percentage partial
		100,															// Task pass percentage success
		0,																// Task Completed Score

		MOVEMENT_TYPE_ALL,										// Movement Type

		// landing types
		(1 << ENTITY_SUB_TYPE_LANDING_FIXED_WING) +
		(1 << ENTITY_SUB_TYPE_LANDING_FIXED_WING_TRANSPORT) +
		(1 << ENTITY_SUB_TYPE_LANDING_HELICOPTER) +
		(1 << ENTITY_SUB_TYPE_LANDING_GROUND) +
		(1 << ENTITY_SUB_TYPE_LANDING_PEOPLE) +
		(1 << ENTITY_SUB_TYPE_LANDING_SEA),
		
		// AI Stats
		{
			0,															// Air Attack strength
			0,															// Ground Attack strength
			0,															// Movement Speed
			0,															// Movement Stealth
			0,															// Cargo Space
			0,															// Troop Space
		},


		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_TASK_ESCORT,
		//
		////////////////////////////////////////

		"Escort",													// Name
		"Escort",													// Short Name
		"ESC",														// Key

		TASK_CATEGORY_SUPPORT,									// task category

		7,																// task priority
		1,																// difficulty rating

		TASK_TARGET_CLASS_ALL,									// Task default target class type
		TASK_TARGET_SOURCE_SCAN_ALL,							// Default Task target source type
		TASK_TARGET_TYPE_MOBILE,								// Task default target type
		TASK_OBJECTIVE_INFO_ALWAYS_KNOWN,					// Task Objective Info Type
		1,																// Minimum Member Count
		TASK_ROE_ALL,												// Rules Of Engagement
		TRUE,															// Engage Enemy
		ESCORT_NEVER,												// Escort Required Threshold
		COLOUR_WHITE,												// 2D waypoint route colour

		TRUE,															// add start waypoint
		TRUE,															// primary task
		FALSE,														// solo task
		FALSE,														// persistent task
		TRUE,															// visible task
		KEYSITE_AIR_FORCE_CAPACITY_SMALL,					// keysite air force capacity
		TRUE,															// Assess landing on completion
		TRUE,															// Task route search
		TRUE,															// Perform debrief
		TRUE,															// delay task assignment
		TASK_OBJECTIVE_PREVIEW_LIVE,							// task_objective_preview
		TRUE,															// counts_towards_player_log
		FALSE,														// wait_for_end_task
		3,																// player_reserve_factor

		25,															// Task pass percentage partial
		100,															// Task pass percentage success
		1000,															// Task Completed Score

		MOVEMENT_TYPE_AIR,										// Movement Type

		// landing types
		(1 << ENTITY_SUB_TYPE_LANDING_FIXED_WING) +
		(1 << ENTITY_SUB_TYPE_LANDING_HELICOPTER),
		
		// AI Stats
		{
			4,															// Air Attack strength
			2,															// Ground Attack strength
			0,															// Movement Speed
			0,															// Movement Stealth
			0,															// Cargo Space
			0,															// Troop Space
		},


		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_TASK_FREE_FLIGHT,
		//
		////////////////////////////////////////

		"Free Flight",												// Name
		"Free Flight",												// Short Name
		"FREE",														// Key

		TASK_CATEGORY_MISC,										// task category

		7,																// task priority
		1,																// difficulty rating

		TASK_TARGET_CLASS_ALL,									// Task default target class type
		TASK_TARGET_SOURCE_NONE,								// Default Task target source type
		TASK_TARGET_TYPE_NONE,									// Task default target type
		TASK_OBJECTIVE_INFO_ALWAYS_KNOWN,					// Task Objective Info Type
		1,																// Minimum Member Count
		TASK_ROE_NONE,												// Rules Of Engagement
		FALSE,														// Engage Enemy
		ESCORT_NEVER,												// Escort Required Threshold
		COLOUR_WHITE,												// 2D waypoint route colour

		TRUE,															// add start waypoint
		TRUE,															// primary task
		FALSE,														// solo task
		FALSE,														// persistent task
		TRUE,															// visible task
		KEYSITE_AIR_FORCE_CAPACITY_SMALL,					// keysite air force capacity
		TRUE,															// Assess landing on completion
		TRUE,															// Task route search
		TRUE,															// Perform debrief
		TRUE,															// delay task assignment
		TASK_OBJECTIVE_PREVIEW_NONE,							// task_objective_preview
		FALSE,														// counts_towards_player_log
		FALSE,														// wait_for_end_task
		0,																// player_reserve_factor

		100,															// Task pass percentage partial
		100,															// Task pass percentage success
		0,																// Task Completed Score

		MOVEMENT_TYPE_AIR,										// Movement Type

		// landing types
		(1 << ENTITY_SUB_TYPE_LANDING_HELICOPTER),
		
		// AI Stats
		{
			0,															// Air Attack strength
			0,															// Ground Attack strength
			0,															// Movement Speed
			0,															// Movement Stealth
			0,															// Cargo Space
			0,															// Troop Space
		},


		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_TASK_GROUND_STRIKE,
		//
		////////////////////////////////////////

		"Ground Strike",											// Name
		"Strike",													// Short Name
		"STK",														// Key

		TASK_CATEGORY_STRIKE,									// task category

		9,																// task priority
		4,																// difficulty rating

		TASK_TARGET_CLASS_GROUND,								// Task default target class type
		TASK_TARGET_SOURCE_NONE,								// Default Task target source type
		TASK_TARGET_TYPE_BUILDING,								// Task default target type
		TASK_OBJECTIVE_INFO_ALWAYS_KNOWN,					// Task Objective Info Type
		2,																// Minimum Member Count
		TASK_ROE_ALL,												// Rules Of Engagement
		TRUE,															// Engage Enemy
		3,																// Escort Required Threshold
		COLOUR_WHITE,												// 2D waypoint route colour

		TRUE,															// add start waypoint
		TRUE,															// primary task
		FALSE,														// solo task
		FALSE,														// persistent task
		TRUE,															// visible task
		KEYSITE_AIR_FORCE_CAPACITY_SMALL,					// keysite air force capacity
		TRUE,															// Assess landing on completion
		TRUE,															// Task route search
		TRUE,															// Perform debrief
		TRUE,															// delay task assignment
		TASK_OBJECTIVE_PREVIEW_STILL,							// task_objective_preview
		TRUE,															// counts_towards_player_log
		TRUE,															// wait_for_end_task
		2,																// player_reserve_factor

		10,															// Task pass percentage partial
		25,															// Task pass percentage success
		1000,															// Task Completed Score

		MOVEMENT_TYPE_AIR,										// Movement Type

		// landing types
		(1 << ENTITY_SUB_TYPE_LANDING_FIXED_WING) +
		(1 << ENTITY_SUB_TYPE_LANDING_HELICOPTER),
		
		// AI Stats
		{
			0,															// Air Attack strength
			8,															// Ground Attack strength
			0,															// Movement Speed
			0,															// Movement Stealth
			0,															// Cargo Space
			0,															// Troop Space
		},


		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_TASK_LANDING,
		//
		////////////////////////////////////////

		"Landing",													// Name
		"Landing",													// Short Name
		"",															// Key

		TASK_CATEGORY_MISC,										// task category

		10,															// task priority
		0,																// difficulty rating

		TASK_TARGET_CLASS_ALL,									// Task default target class type
		TASK_TARGET_SOURCE_NONE,								// Default Task target source type
		TASK_TARGET_TYPE_NONE,									// Task default target type
		TASK_OBJECTIVE_INFO_NONE,								// Task Objective Info Type
		1,																// Minimum Member Count
		TASK_ROE_NONE,												// Rules Of Engagement
		FALSE,														// Engage Enemy
		ESCORT_NEVER,												// Escort Required Threshold
		COLOUR_WHITE,												// 2D waypoint route colour

		TRUE,															// add start waypoint
		FALSE,														// primary task
		TRUE,															// solo task
		TRUE,															// persistent task
		FALSE,														// visible task
		KEYSITE_AIR_FORCE_CAPACITY_NONE,						// keysite air force capacity
		FALSE,														// Assess landing on completion
		FALSE,														// Task route search
		FALSE,														// Perform debrief
		FALSE,														// delay task assignment
		TASK_OBJECTIVE_PREVIEW_NONE,							// task_objective_preview
		FALSE,														// counts_towards_player_log
		FALSE,														// wait_for_end_task
		0,																// player_reserve_factor

		100,															// Task pass percentage partial
		100,															// Task pass percentage success
		0,																// Task Completed Score

		MOVEMENT_TYPE_ALL,										// Movement Type

		// landing types
		(1 << ENTITY_SUB_TYPE_LANDING_FIXED_WING) +
		(1 << ENTITY_SUB_TYPE_LANDING_FIXED_WING_TRANSPORT) +
		(1 << ENTITY_SUB_TYPE_LANDING_HELICOPTER) +
		(1 << ENTITY_SUB_TYPE_LANDING_GROUND) +
		(1 << ENTITY_SUB_TYPE_LANDING_PEOPLE) +
		(1 << ENTITY_SUB_TYPE_LANDING_SEA),
		
		// AI Stats
		{
			0,															// Air Attack strength
			0,															// Ground Attack strength
			0,															// Movement Speed
			0,															// Movement Stealth
			0,															// Cargo Space
			0,															// Troop Space
		},


		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_TASK_LANDING_HOLDING,
		//
		////////////////////////////////////////

		"Landing Holding",										// Name
		"Landing Holding",										// Short Name
		"",															// Key

		TASK_CATEGORY_MISC,										// task category

		10,															// task priority
		0,																// difficulty rating

		TASK_TARGET_CLASS_ALL,									// Task default target class type
		TASK_TARGET_SOURCE_NONE,								// Default Task target source type
		TASK_TARGET_TYPE_NONE,									// Task default target type
		TASK_OBJECTIVE_INFO_NONE,								// Task Objective Info Type
		1,																// Minimum Member Count
		TASK_ROE_NONE,												// Rules Of Engagement
		FALSE,														// Engage Enemy
		ESCORT_NEVER,												// Escort Required Threshold
		COLOUR_WHITE,												// 2D waypoint route colour

		TRUE,															// add start waypoint
		FALSE,														// primary task
		TRUE,															// solo task
		TRUE,															// persistent task
		FALSE,														// visible task
		KEYSITE_AIR_FORCE_CAPACITY_NONE,						// keysite air force capacity
		FALSE,														// Assess landing on completion
		FALSE,														// Task route search
		FALSE,														// Perform debrief
		FALSE,														// delay task assignment
		TASK_OBJECTIVE_PREVIEW_NONE,							// task_objective_preview
		FALSE,														// counts_towards_player_log
		FALSE,														// wait_for_end_task
		0,																// player_reserve_factor

		100,															// Task pass percentage partial
		100,															// Task pass percentage success
		0,																// Task Completed Score

		MOVEMENT_TYPE_ALL,										// Movement Type

		// landing types
		(1 << ENTITY_SUB_TYPE_LANDING_FIXED_WING) +
		(1 << ENTITY_SUB_TYPE_LANDING_FIXED_WING_TRANSPORT) +
		(1 << ENTITY_SUB_TYPE_LANDING_HELICOPTER) +
		(1 << ENTITY_SUB_TYPE_LANDING_GROUND) +
		(1 << ENTITY_SUB_TYPE_LANDING_PEOPLE) +
		(1 << ENTITY_SUB_TYPE_LANDING_SEA),
		
		// AI Stats
		{
			0,															// Air Attack strength
			0,															// Ground Attack strength
			0,															// Movement Speed
			0,															// Movement Stealth
			0,															// Cargo Space
			0,															// Troop Space
		},


		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_TASK_OCA_STRIKE,
		//
		////////////////////////////////////////

		"Offensive Counter Air Strike",						// Name
		"OCA Strike",												// Short Name
		"OCA",														// Key

		TASK_CATEGORY_STRIKE,									// task category

		6,																// task priority
		4,																// difficulty rating

		TASK_TARGET_CLASS_GROUND,								// Task default target class type
		TASK_TARGET_SOURCE_NONE,								// Default Task target source type
		TASK_TARGET_TYPE_GROUNDED_AIRCRAFT,					// Task default target type
		TASK_OBJECTIVE_INFO_ALWAYS_KNOWN,					// Task Objective Info Type
		1,																// Minimum Member Count
		TASK_ROE_ALL,												// Rules Of Engagement
		TRUE,															// Engage Enemy
		ESCORT_NEVER,												// Escort Required Threshold
		COLOUR_WHITE,												// 2D waypoint route colour

		TRUE,															// add start waypoint
		TRUE,															// primary task
		FALSE,														// solo task
		FALSE,														// persistent task
		TRUE,															// visible task
		KEYSITE_AIR_FORCE_CAPACITY_LARGE,					// keysite air force capacity
		TRUE,															// Assess landing on completion
		TRUE,															// Task route search
		TRUE,															// Perform debrief
		TRUE,															// delay task assignment
		TASK_OBJECTIVE_PREVIEW_STILL,							// task_objective_preview
		FALSE,														// counts_towards_player_log
		FALSE,														// wait_for_end_task
		0,																// player_reserve_factor

		10,															// Task pass percentage partial
		33,															// Task pass percentage success
		0,																// Task Completed Score

		MOVEMENT_TYPE_AIR,										// Movement Type

		// landing types
		(1 << ENTITY_SUB_TYPE_LANDING_FIXED_WING),
		
		// AI Stats
		{
			0,															// Air Attack strength
			6,															// Ground Attack strength
			5,															// Movement Speed
			0,															// Movement Stealth
			0,															// Cargo Space
			0,															// Troop Space
		},


		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_TASK_OCA_SWEEP,
		//
		////////////////////////////////////////

		"Offensive Counter Air Sweep",						// Name
		"OCA Sweep",												// Short Name
		"OCA",														// Key

		TASK_CATEGORY_STRIKE,									// task category

		7,																// task priority
		4,																// difficulty rating

		TASK_TARGET_CLASS_AIR,									// Task default target class type
		TASK_TARGET_SOURCE_SCAN_AIR,							// Default Task target source type
		TASK_TARGET_TYPE_AIRBORNE_AIRCRAFT,					// Task default target type
		TASK_OBJECTIVE_INFO_ALWAYS_KNOWN,					// Task Objective Info Type
		1,																// Minimum Member Count
		TASK_ROE_ALL,												// Rules Of Engagement
		TRUE,															// Engage Enemy
		ESCORT_NEVER,												// Escort Required Threshold
		COLOUR_WHITE,												// 2D waypoint route colour

		TRUE,															// add start waypoint
		TRUE,															// primary task
		FALSE,														// solo task
		FALSE,														// persistent task
		TRUE,															// visible task
		KEYSITE_AIR_FORCE_CAPACITY_LARGE,					// keysite air force capacity
		TRUE,															// Assess landing on completion
		TRUE,															// Task route search
		TRUE,															// Perform debrief
		TRUE,															// delay task assignment
		TASK_OBJECTIVE_PREVIEW_STILL,							// task_objective_preview
		FALSE,														// counts_towards_player_log
		FALSE,														// wait_for_end_task
		0,																// player_reserve_factor

		25,															// Task pass percentage partial
		50,															// Task pass percentage success
		0,																// Task Completed Score

		MOVEMENT_TYPE_AIR,										// Movement Type

		// landing types
		(1 << ENTITY_SUB_TYPE_LANDING_FIXED_WING),
		
		// AI Stats
		{
			5,															// Air Attack strength
			0,															// Ground Attack strength
			5,															// Movement Speed
			0,															// Movement Stealth
			0,															// Cargo Space
			0,															// Troop Space
		},


		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_TASK_RECON,
		//
		////////////////////////////////////////

		"Recon",														// Name
		"Recon",														// Short Name
		"REC",														// Key

		TASK_CATEGORY_RECON,										// task category

		7,																// task priority
		1,																// difficulty rating

		TASK_TARGET_CLASS_ALL,									// Task default target class type
		TASK_TARGET_SOURCE_NONE,								// Default Task target source type
		TASK_TARGET_TYPE_NONE,									// Task default target type
		TASK_OBJECTIVE_INFO_FOG_OF_WAR_KNOWN,				// Task Objective Info Type
		1,																// Minimum Member Count
		TASK_ROE_NONE,												// Rules Of Engagement
		FALSE,														// Engage Enemy
		ESCORT_NEVER,												// Escort Required Threshold
		COLOUR_WHITE,												// 2D waypoint route colour

		TRUE,															// add start waypoint
		TRUE,															// primary task
		FALSE,														// solo task
		FALSE,														// persistent task
		TRUE,															// visible task
		KEYSITE_AIR_FORCE_CAPACITY_SMALL,					// keysite air force capacity
		TRUE,															// Assess landing on completion
		TRUE,															// Task route search
		TRUE,															// Perform debrief
		TRUE,															// delay task assignment
		TASK_OBJECTIVE_PREVIEW_NONE,							// task_objective_preview
		TRUE,															// counts_towards_player_log
		FALSE,														// wait_for_end_task
		4,																// player_reserve_factor

		100,															// Task pass percentage partial
		100,															// Task pass percentage success
		1000,															// Task Completed Score

		MOVEMENT_TYPE_AIR,										// Movement Type

		// landing types
		(1 << ENTITY_SUB_TYPE_LANDING_HELICOPTER),
		
		// AI Stats
		{
			0,															// Air Attack strength
			0,															// Ground Attack strength
			3,															// Movement Speed
			5,															// Movement Stealth
			0,															// Cargo Space
			0,															// Troop Space
		},


		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_TASK_REPAIR,
		//
		////////////////////////////////////////

		"Repair",													// Name
		"Repair",													// Short Name
		"REP",														// Key

		TASK_CATEGORY_SUPPORT,									// task category

		5,																// task priority
		0,																// difficulty rating

		TASK_TARGET_CLASS_ALL,									// Task default target class type
		TASK_TARGET_SOURCE_NONE,								// Default Task target source type
		TASK_TARGET_TYPE_NONE,									// Task default target type
		TASK_OBJECTIVE_INFO_ALWAYS_KNOWN,					// Task Objective Info Type
		1,																// Minimum Member Count
		TASK_ROE_NONE,												// Rules Of Engagement
		FALSE,														// Engage Enemy
		5,																// Escort Required Threshold
		COLOUR_WHITE,												// 2D waypoint route colour

		TRUE,															// add start waypoint
		TRUE,															// primary task
		FALSE,														// solo task
		FALSE,														// persistent task
		TRUE,															// visible task
		KEYSITE_AIR_FORCE_CAPACITY_SMALL,					// keysite air force capacity
		TRUE,															// Assess landing on completion
		TRUE,															// Task route search
		TRUE,															// Perform debrief
		TRUE,															// delay task assignment
		TASK_OBJECTIVE_PREVIEW_LIVE,							// task_objective_preview
		FALSE,														// counts_towards_player_log
		FALSE,														// wait_for_end_task
		0,																// player_reserve_factor

		100,															// Task pass percentage partial
		100,															// Task pass percentage success
		0,																// Task Completed Score

		MOVEMENT_TYPE_AIR,										// Movement Type

		// landing types
		(1 << ENTITY_SUB_TYPE_LANDING_HELICOPTER),
		
		// AI Stats
		{
			0,															// Air Attack strength
			0,															// Ground Attack strength
			0,															// Movement Speed
			0,															// Movement Stealth
			6,															// Cargo Space
			0,															// Troop Space
		},


		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_TASK_RETREAT,
		//
		////////////////////////////////////////

		"Retreat",													// Name
		"Retreat",													// Short Name
		"RET",														// Key

		TASK_CATEGORY_SUPPORT,									// task category

		9,																// task priority
		0,																// difficulty rating

		TASK_TARGET_CLASS_ALL,									// Task default target class type
		TASK_TARGET_SOURCE_SCAN_ALL,							// Default Task target source type
		TASK_TARGET_TYPE_MOBILE,								// Task default target type
		TASK_OBJECTIVE_INFO_NONE,								// Task Objective Info Type
		1,																// Minimum Member Count
		TASK_ROE_ALL,												// Rules Of Engagement
		FALSE,														// Engage Enemy
		ESCORT_NEVER,												// Escort Required Threshold
		COLOUR_WHITE,												// 2D waypoint route colour

		TRUE,															// add start waypoint
		TRUE,															// primary task
		FALSE,														// solo task
		FALSE,														// persistent task
		TRUE,															// visible task
		KEYSITE_AIR_FORCE_CAPACITY_NONE,						// keysite air force capacity
		FALSE,														// Assess landing on completion
		FALSE,														// Task route search
		TRUE,															// Perform debrief
		FALSE,														// delay task assignment
		TASK_OBJECTIVE_PREVIEW_NONE,							// task_objective_preview
		FALSE,														// counts_towards_player_log
		FALSE,														// wait_for_end_task
		0,																// player_reserve_factor

		100,															// Task pass percentage partial
		100,															// Task pass percentage success
		0,																// Task Completed Score

		MOVEMENT_TYPE_GROUND,									// Movement Type

		// landing types
		(1 << ENTITY_SUB_TYPE_LANDING_GROUND),

		// AI Stats
		{
			0,															// Air Attack strength
			0,															// Ground Attack strength
			0,															// Movement Speed
			0,															// Movement Stealth
			0,															// Cargo Space
			0,															// Troop Space
		},


		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_TASK_SEAD,
		//
		////////////////////////////////////////

		"Suppression Of Enemy Air Defences",				// Name
		"SEAD",														// Short Name
		"SEAD",														// Key

		TASK_CATEGORY_STRIKE,									// task category

		9,																// task priority
		4,																// difficulty rating

		TASK_TARGET_CLASS_GROUND,								// Task default target class type
		TASK_TARGET_SOURCE_NONE,								// Default target source type
		TASK_TARGET_TYPE_VEHICLE,								// Task default target type
		TASK_OBJECTIVE_INFO_ALWAYS_KNOWN,					// Task Objective Info Type
		2,																// Minimum Member Count
		TASK_ROE_OBJECTIVE,										// Rules Of Engagement
		TRUE,															// Engage Enemy
		5,																// Escort Required Threshold
		COLOUR_WHITE,												// 2D waypoint route colour

		TRUE,															// add start waypoint
		TRUE,															// primary task
		FALSE,														// solo task
		FALSE,														// persistent task
		TRUE,															// visible task
		KEYSITE_AIR_FORCE_CAPACITY_SMALL,					// keysite air force capacity
		TRUE,															// Assess landing on completion
		TRUE,															// Task route search
		TRUE,															// Perform debrief
		TRUE,															// delay task assignment
		TASK_OBJECTIVE_PREVIEW_STILL,							// task_objective_preview
		TRUE,															// counts_towards_player_log
		TRUE,															// wait_for_end_task
		2,																// player_reserve_factor

		10,															// Task pass percentage partial
		100,															// Task pass percentage success
		1000,															// Task Completed Score

		MOVEMENT_TYPE_AIR,										// Movement Type

		// landing types
		(1 << ENTITY_SUB_TYPE_LANDING_FIXED_WING) +
		(1 << ENTITY_SUB_TYPE_LANDING_HELICOPTER),
		
		// AI Stats
		{
			0,															// Air Attack strength
			6,															// Ground Attack strength
			0,															// Movement Speed
			0,															// Movement Stealth
			0,															// Cargo Space
			0,															// Troop Space
		},


		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_TASK_SUPPLY,
		//
		////////////////////////////////////////

		"Supply",													// Name
		"Supply",													// Short Name
		"SUP",														// Key

		TASK_CATEGORY_SUPPORT,									// task category

		4,																// task priority
		0,																// difficulty rating

		TASK_TARGET_CLASS_ALL,									// Task default target class type
		TASK_TARGET_SOURCE_NONE,								// Default Task target source type
		TASK_TARGET_TYPE_NONE,									// Task default target type
		TASK_OBJECTIVE_INFO_ALWAYS_KNOWN,					// Task Objective Info Type
		1,																// Minimum Member Count
		TASK_ROE_NONE,												// Rules Of Engagement
		FALSE,														// Engage Enemy
		6,																// Escort Required Threshold
		COLOUR_WHITE,												// 2D waypoint route colour

		TRUE,															// add start waypoint
		TRUE,															// primary task
		FALSE,														// solo task
		FALSE,														// persistent task
		TRUE,															// visible task
		KEYSITE_AIR_FORCE_CAPACITY_LARGE,					// keysite air force capacity
		TRUE,															// Assess landing on completion
		TRUE,															// Task route search
		TRUE,															// Perform debrief
		FALSE,														// delay task assignment
		TASK_OBJECTIVE_PREVIEW_NONE,							// task_objective_preview
		FALSE,														// counts_towards_player_log
		FALSE,														// wait_for_end_task
		0,																// player_reserve_factor

		100,															// Task pass percentage partial
		100,															// Task pass percentage success
		0,																// Task Completed Score

		MOVEMENT_TYPE_AIR,										// Movement Type

		// landing types
		(1 << ENTITY_SUB_TYPE_LANDING_FIXED_WING_TRANSPORT) +
		(1 << ENTITY_SUB_TYPE_LANDING_HELICOPTER),
		
		// AI Stats
		{
			0,															// Air Attack strength
			0,															// Ground Attack strength
			0,															// Movement Speed
			0,															// Movement Stealth
			5,															// Cargo Space
			0,															// Troop Space
		},


		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_TASK_TAKEOFF,
		//
		////////////////////////////////////////

		"Takeoff",													// Name
		"Takeoff",													// Short Name
		"",															// Key

		TASK_CATEGORY_MISC,										// task category

		10,															// task priority
		0,																// difficulty rating

		TASK_TARGET_CLASS_ALL,									// Task default target class type
		TASK_TARGET_SOURCE_NONE,								// Default Task target source type
		TASK_TARGET_TYPE_NONE,									// Task default target type
		TASK_OBJECTIVE_INFO_NONE,								// Task Objective Info Type
		1,																// Minimum Member Count
		TASK_ROE_NONE,												// Rules Of Engagement
		FALSE,														// Engage Enemy
		ESCORT_NEVER,												// Escort Required Threshold
		COLOUR_WHITE,												// 2D waypoint route colour

		TRUE,															// add start waypoint
		FALSE,														// primary task
		TRUE,															// solo task
		TRUE,															// persistent task
		FALSE,														// visible task
		KEYSITE_AIR_FORCE_CAPACITY_NONE,						// keysite air force capacity
		FALSE,														// Assess landing on completion
		FALSE,														// Task route search
		FALSE,														// Perform debrief
		FALSE,														// delay task assignment
		TASK_OBJECTIVE_PREVIEW_NONE,							// task_objective_preview
		FALSE,														// counts_towards_player_log
		FALSE,														// wait_for_end_task
		0,																// player_reserve_factor

		100,															// Task pass percentage partial
		100,															// Task pass percentage success
		0,																// Task Completed Score

		MOVEMENT_TYPE_ALL,										// Movement Type

		// landing types
		(1 << ENTITY_SUB_TYPE_LANDING_FIXED_WING) +
		(1 << ENTITY_SUB_TYPE_LANDING_FIXED_WING_TRANSPORT) +
		(1 << ENTITY_SUB_TYPE_LANDING_HELICOPTER) +
		(1 << ENTITY_SUB_TYPE_LANDING_GROUND) +
		(1 << ENTITY_SUB_TYPE_LANDING_PEOPLE) +
		(1 << ENTITY_SUB_TYPE_LANDING_SEA),
		
		// AI Stats
		{
			0,															// Air Attack strength
			0,															// Ground Attack strength
			0,															// Movement Speed
			0,															// Movement Stealth
			0,															// Cargo Space
			0,															// Troop Space
		},


		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_TASK_TAKEOFF_HOLDING,
		//
		////////////////////////////////////////

		"Takeoff Holding",										// Name
		"Takeoff Holding",										// Short Name
		"",															// Key

		TASK_CATEGORY_MISC,										// task category

		10,															// task priority
		0,																// difficulty rating

		TASK_TARGET_CLASS_ALL,									// Task default target class type
		TASK_TARGET_SOURCE_NONE,								// Default Task target source type
		TASK_TARGET_TYPE_NONE,									// Task default target type
		TASK_OBJECTIVE_INFO_NONE,								// Task Objective Info Type
		1,																// Minimum Member Count
		TASK_ROE_NONE,												// Rules Of Engagement
		FALSE,														// Engage Enemy
		ESCORT_NEVER,												// Escort Required Threshold
		COLOUR_WHITE,												// 2D waypoint route colour

		TRUE,															// add start waypoint
		FALSE,														// primary task
		TRUE,															// solo task
		TRUE,															// persistent task
		FALSE,														// visible task
		KEYSITE_AIR_FORCE_CAPACITY_NONE,						// keysite air force capacity
		FALSE,														// Assess landing on completion
		FALSE,														// Task route search
		FALSE,														// Perform debrief
		FALSE,														// delay task assignment
		TASK_OBJECTIVE_PREVIEW_NONE,							// task_objective_preview
		FALSE,														// counts_towards_player_log
		FALSE,														// wait_for_end_task
		0,																// player_reserve_factor

		100,															// Task pass percentage partial
		100,															// Task pass percentage success
		0,																// Task Completed Score

		MOVEMENT_TYPE_ALL,										// Movement Type

		// landing types
		(1 << ENTITY_SUB_TYPE_LANDING_FIXED_WING) +
		(1 << ENTITY_SUB_TYPE_LANDING_FIXED_WING_TRANSPORT) +
		(1 << ENTITY_SUB_TYPE_LANDING_HELICOPTER) +
		(1 << ENTITY_SUB_TYPE_LANDING_GROUND) +
		(1 << ENTITY_SUB_TYPE_LANDING_PEOPLE) +
		(1 << ENTITY_SUB_TYPE_LANDING_SEA),
		
		// AI Stats
		{
			0,															// Air Attack strength
			0,															// Ground Attack strength
			0,															// Movement Speed
			0,															// Movement Stealth
			0,															// Cargo Space
			0,															// Troop Space
		},


		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_TRANSFER_FIXED_WING,
		//
		////////////////////////////////////////

		"Transfer",													// Name
		"Transfer",													// Short Name
		"TR",															// Key

		TASK_CATEGORY_SUPPORT,									// task category

		5,																// task priority
		1,																// difficulty rating

		TASK_TARGET_CLASS_ALL,									// Task default target class type
		TASK_TARGET_SOURCE_NONE,								// Default Task target source type
		TASK_TARGET_TYPE_NONE,									// Task default target type
		TASK_OBJECTIVE_INFO_ALWAYS_KNOWN,					// Task Objective Info Type
		1,																// Minimum Member Count
		TASK_ROE_NONE,												// Rules Of Engagement
		FALSE,														// Engage Enemy
		6,																// Escort Required Threshold
		COLOUR_WHITE,												// 2D waypoint route colour

		TRUE,															// add start waypoint
		TRUE,															// primary task
		FALSE,														// solo task
		FALSE,														// persistent task
		FALSE,														// visible task
		KEYSITE_AIR_FORCE_CAPACITY_LARGE,					// keysite air force capacity
		TRUE,															// Assess landing on completion
		TRUE,															// Task route search
		TRUE,															// Perform debrief
		TRUE,															// delay task assignment
		TASK_OBJECTIVE_PREVIEW_NONE,							// task_objective_preview
		FALSE,														// counts_towards_player_log
		FALSE,														// wait_for_end_task
		0,																// player_reserve_factor

		100,															// Task pass percentage partial
		100,															// Task pass percentage success
		0,																// Task Completed Score

		MOVEMENT_TYPE_AIR,										// Movement Type

		// landing types
		(1 << ENTITY_SUB_TYPE_LANDING_FIXED_WING) +
		(1 << ENTITY_SUB_TYPE_LANDING_FIXED_WING_TRANSPORT),
		
		// AI Stats
		{
			0,															// Air Attack strength
			0,															// Ground Attack strength
			0,															// Movement Speed
			0,															// Movement Stealth
			0,															// Cargo Space
			0,															// Troop Space
		},

		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_TRANSFER_HELICOPTER,
		//
		////////////////////////////////////////

		"Transfer",													// Name
		"Transfer",													// Short Name
		"TR",															// Key

		TASK_CATEGORY_SUPPORT,									// task category

		7,																// task priority
		1,																// difficulty rating

		TASK_TARGET_CLASS_ALL,									// Task default target class type
		TASK_TARGET_SOURCE_NONE,								// Default Task target source type
		TASK_TARGET_TYPE_NONE,									// Task default target type
		TASK_OBJECTIVE_INFO_ALWAYS_KNOWN,					// Task Objective Info Type
		1,																// Minimum Member Count
		TASK_ROE_NONE,												// Rules Of Engagement
		FALSE,														// Engage Enemy
		7,																// Escort Required Threshold
		COLOUR_WHITE,												// 2D waypoint route colour

		TRUE,															// add start waypoint
		TRUE,															// primary task
		FALSE,														// solo task
		FALSE,														// persistent task
		TRUE,															// visible task
		KEYSITE_AIR_FORCE_CAPACITY_SMALL,					// keysite air force capacity
		TRUE,															// Assess landing on completion
		TRUE,															// Task route search
		TRUE,															// Perform debrief
		TRUE,															// delay task assignment
		TASK_OBJECTIVE_PREVIEW_NONE,							// task_objective_preview
		FALSE,														// counts_towards_player_log
		FALSE,														// wait_for_end_task
		0,																// player_reserve_factor

		100,															// Task pass percentage partial
		100,															// Task pass percentage success
		500,															// Task Completed Score

		MOVEMENT_TYPE_AIR,										// Movement Type

		// landing types
		(1 << ENTITY_SUB_TYPE_LANDING_HELICOPTER),
		
		// AI Stats
		{
			0,															// Air Attack strength
			0,															// Ground Attack strength
			0,															// Movement Speed
			0,															// Movement Stealth
			0,															// Cargo Space
			0,															// Troop Space
		},

		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_TASK_TROOP_INSERTION,
		//
		////////////////////////////////////////

		"Troop Insertion",										// Name
		"Insertion",												// Short Name
		"TI",															// Key

		TASK_CATEGORY_STRIKE,									// task category

		10,															// task priority
		2,																// difficulty rating

		TASK_TARGET_CLASS_ALL,									// Task default target class type
		TASK_TARGET_SOURCE_NONE,								// Default Task target source type
		TASK_TARGET_TYPE_NONE,									// Task default target type
		TASK_OBJECTIVE_INFO_ALWAYS_KNOWN,					// Task Objective Info Type
		1,																// Minimum Member Count
		TASK_ROE_NONE,												// Rules Of Engagement
		FALSE,														// Engage Enemy
		3,																// Escort Required Threshold
		COLOUR_WHITE,												// 2D waypoint route colour

		TRUE,															// add start waypoint
		TRUE,															// primary task
		FALSE,														// solo task
		FALSE,														// persistent task
		TRUE,															// visible task
		KEYSITE_AIR_FORCE_CAPACITY_SMALL,					// keysite air force capacity
		TRUE,															// Assess landing on completion
		TRUE,															// Task route search
		TRUE,															// Perform debrief
		TRUE,															// delay task assignment
		TASK_OBJECTIVE_PREVIEW_STILL,							// task_objective_preview
		FALSE,														// counts_towards_player_log
		FALSE,														// wait_for_end_task
		0,																// player_reserve_factor

		100,															// Task pass percentage partial
		100,															// Task pass percentage success
		0,																// Task Completed Score

		MOVEMENT_TYPE_AIR,										// Movement Type

		// landing types
		(1 << ENTITY_SUB_TYPE_LANDING_HELICOPTER),
		
		// AI Stats
		{
			0,															// Air Attack strength
			0,															// Ground Attack strength
			0,															// Movement Speed
			0,															// Movement Stealth
			0,															// Cargo Space
			8,															// Troop Space
		},

		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_TASK_TROOP_MOVEMENT_INSERT_CAPTURE,
		//
		////////////////////////////////////////

		"Troop Movement (Insert/capture)",					// Name
		"TROOP MOVEMENT (INS/CAPT)",							// Short Name
		"TM",															// Key

		TASK_CATEGORY_MISC,										// task category

		5,																// task priority
		2,																// difficulty rating

		TASK_TARGET_CLASS_ALL,									// Task default target class type
		TASK_TARGET_SOURCE_NONE,								// Task default target source type
		TASK_TARGET_TYPE_NONE,									// Task default target type
		TASK_OBJECTIVE_INFO_NONE,								// Task Objective Info Type
		1,																// Minimum Member Count
		TASK_ROE_ALL,												// Rules Of Engagement
		TRUE,															// Engage Enemy
		ESCORT_NEVER,												// Escort Required Threshold
		COLOUR_WHITE,												// 2D waypoint route colour

		TRUE,															// add start waypoint
		FALSE,														// primary task
		FALSE,														// solo task
		FALSE,														// persistent task
		FALSE,														// visible task
		KEYSITE_AIR_FORCE_CAPACITY_NONE,						// keysite air force capacity
		FALSE,														// Assess landing on completion
		FALSE,														// Task route search
		TRUE,															// Perform debrief
		TRUE,															// delay task assignment
		TASK_OBJECTIVE_PREVIEW_NONE,							// task_objective_preview
		FALSE,														// counts_towards_player_log
		FALSE,														// wait_for_end_task
		0,																// player_reserve_factor

		100,															// Task pass percentage partial
		100,															// Task pass percentage success
		0,																// Task Completed Score

		MOVEMENT_TYPE_GROUND,									// Movement Type

		// landing types
		(1 << ENTITY_SUB_TYPE_LANDING_PEOPLE),
		
		// AI Stats
		{
			0,															// Air Attack strength
			0,															// Ground Attack strength
			0,															// Movement Speed
			0,															// Movement Stealth
			0,															// Cargo Space
			0,															// Troop Space
		},

		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_TASK_TROOP_MOVEMENT_INSERT_DEFEND,
		//
		////////////////////////////////////////

		"Troop Movement (Insert/Defend)",					// Name
		"TROOP MOVEMENT (Ins/Def)",							// Short Name
		"TM",															// Key

		TASK_CATEGORY_MISC,										// task category

		5,																// task priority
		2,																// difficulty rating

		TASK_TARGET_CLASS_ALL,									// Task default target class type
		TASK_TARGET_SOURCE_NONE,								// Task default target source type
		TASK_TARGET_TYPE_NONE,									// Task default target type
		TASK_OBJECTIVE_INFO_NONE,								// Task Objective Info Type
		1,																// Minimum Member Count
		TASK_ROE_ALL,												// Rules Of Engagement
		TRUE,															// Engage Enemy
		ESCORT_NEVER,												// Escort Required Threshold
		COLOUR_WHITE,												// 2D waypoint route colour

		TRUE,															// add start waypoint
		FALSE,														// primary task
		FALSE,														// solo task
		FALSE,														// persistent task
		FALSE,														// visible task
		KEYSITE_AIR_FORCE_CAPACITY_NONE,						// keysite air force capacity
		FALSE,														// Assess landing on completion
		FALSE,														// Task route search
		TRUE,															// Perform debrief
		TRUE,															// delay task assignment
		TASK_OBJECTIVE_PREVIEW_NONE,							// task_objective_preview
		FALSE,														// counts_towards_player_log
		FALSE,														// wait_for_end_task
		0,																// player_reserve_factor

		100,															// Task pass percentage partial
		100,															// Task pass percentage success
		0,																// Task Completed Score

		MOVEMENT_TYPE_GROUND,									// Movement Type

		// landing types
		(1 << ENTITY_SUB_TYPE_LANDING_PEOPLE),
		
		// AI Stats
		{
			0,															// Air Attack strength
			0,															// Ground Attack strength
			0,															// Movement Speed
			0,															// Movement Stealth
			0,															// Cargo Space
			0,															// Troop Space
		},

		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_TASK_TROOP_MOVEMENT_PATROL,
		//
		////////////////////////////////////////

		"Troop Movement (Patrol)",								// Name
		"TROOP MOVEMENT (Patrol)",								// Short Name
		"TM",															// Key

		TASK_CATEGORY_MISC,										// task category

		5,																// task priority
		2,																// difficulty rating

		TASK_TARGET_CLASS_ALL,									// Task default target class type
		TASK_TARGET_SOURCE_NONE,								// Task default target source type
		TASK_TARGET_TYPE_NONE,									// Task default target type
		TASK_OBJECTIVE_INFO_NONE,								// Task Objective Info Type
		1,																// Minimum Member Count
		TASK_ROE_ALL,												// Rules Of Engagement
		TRUE,															// Engage Enemy
		ESCORT_NEVER,												// Escort Required Threshold
		COLOUR_WHITE,												// 2D waypoint route colour

		FALSE,														// add start waypoint
		TRUE,															// primary task
		FALSE,														// solo task
		FALSE,														// persistent task
		FALSE,														// visible task
		KEYSITE_AIR_FORCE_CAPACITY_NONE,						// keysite air force capacity
		TRUE,															// Assess landing on completion
		FALSE,														// Task route search
		TRUE,															// Perform debrief
		TRUE,															// delay task assignment
		TASK_OBJECTIVE_PREVIEW_NONE,							// task_objective_preview
		FALSE,														// counts_towards_player_log
		FALSE,														// wait_for_end_task
		0,																// player_reserve_factor

		100,															// Task pass percentage partial
		100,															// Task pass percentage success
		0,																// Task Completed Score

		MOVEMENT_TYPE_GROUND,									// Movement Type

		// landing types
		(1 << ENTITY_SUB_TYPE_LANDING_PEOPLE),
		
		// AI Stats
		{
			0,															// Air Attack strength
			0,															// Ground Attack strength
			0,															// Movement Speed
			0,															// Movement Stealth
			0,															// Cargo Space
			0,															// Troop Space
		},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
