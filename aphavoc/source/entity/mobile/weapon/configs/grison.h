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



		////////////////////////////////////////////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_VEHICLE_SA19_GRISON
		//
		////////////////////////////////////////////////////////////////////////////////

		#define GUN_TURRET								(0)
		#define GRISON_LAUNCHER_TURRET				(GUN_TURRET)

		#define GUN_BARREL								(0)
		#define GRISON_LAUNCHER_INNER_TUBES			(1)
		#define GRISON_LAUNCHER_OUTER_TUBES			(2)

		#define LHS_UPPER_GUN_MUZZLE					(0)
		#define RHS_UPPER_GUN_MUZZLE					(1)
		#define LHS_LOWER_GUN_MUZZLE					(2)
		#define RHS_LOWER_GUN_MUZZLE					(3)

		#define NUM_GUN_ROUNDS							(1904 / 4)
		#define NUM_GRISON_MISSILES					(8 / 2)

		#define GUN_TURRET_HEADING_RATE				(rad (90.0))
		#define GUN_TURRET_MIN_HEADING_LIMIT		(rad (-180.0))
		#define GUN_TURRET_MAX_HEADING_LIMIT		(rad (180.0))
		#define GUN_BARREL_PITCH_RATE					(rad (45.0))
		#define GUN_BARREL_MIN_PITCH_LIMIT			(rad (0.0))
		#define GUN_BARREL_MAX_PITCH_LIMIT			(rad (60.0))

		#define GRISON_LAUNCHER_HEADING_RATE		(GUN_TURRET_HEADING_RATE)
		#define GRISON_LAUNCHER_MIN_HEADING_LIMIT	(GUN_TURRET_MIN_HEADING_LIMIT)
		#define GRISON_LAUNCHER_MAX_HEADING_LIMIT	(GUN_TURRET_MAX_HEADING_LIMIT)
		#define GRISON_LAUNCHER_PITCH_RATE			(rad (45.0))
		#define GRISON_LAUNCHER_MIN_PITCH_LIMIT	(rad (0.0))
		#define GRISON_LAUNCHER_MAX_PITCH_LIMIT	(rad (60.0))

		////////////////////////////////////////
		//
		// WEAPON_CONFIG_TYPE_SA19_GRISON_1
		//
		////////////////////////////////////////
		{
			// WEAPON PACKAGE 1
			{
				ENTITY_SUB_TYPE_WEAPON_2A38M_30MM_ROUND,				// sub_type
				NUM_GUN_ROUNDS,												// number
				GUN_TURRET,														// heading_depth
				GUN_BARREL,														// pitch_depth
				LHS_UPPER_GUN_MUZZLE,			  							// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				GUN_TURRET_HEADING_RATE,									// heading_rate
				GUN_TURRET_MIN_HEADING_LIMIT,								// min_heading_limit
				GUN_TURRET_MAX_HEADING_LIMIT,								// max_heading_limit
				GUN_BARREL_PITCH_RATE,										// pitch_rate
				GUN_BARREL_MIN_PITCH_LIMIT,								// min_pitch_limit
				GUN_BARREL_MAX_PITCH_LIMIT,								// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE1 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE2 +
				SHARE_WEAPON_PACKAGE3 +
				SHARE_WEAPON_PACKAGE4 +
				SHARE_WEAPON_PACKAGE5 +
				SHARE_WEAPON_PACKAGE6,
				SHARE_WEAPON_PACKAGE1 +										// pitch_share_mask
				SHARE_WEAPON_PACKAGE2 +
				SHARE_WEAPON_PACKAGE3 +
				SHARE_WEAPON_PACKAGE4,
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 2
			{
				ENTITY_SUB_TYPE_WEAPON_2A38M_30MM_ROUND,				// sub_type
				NUM_GUN_ROUNDS,												// number
				GUN_TURRET,														// heading_depth
				GUN_BARREL,														// pitch_depth
				RHS_UPPER_GUN_MUZZLE,			  							// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				GUN_TURRET_HEADING_RATE,									// heading_rate
				GUN_TURRET_MIN_HEADING_LIMIT,								// min_heading_limit
				GUN_TURRET_MAX_HEADING_LIMIT,								// max_heading_limit
				GUN_BARREL_PITCH_RATE,										// pitch_rate
				GUN_BARREL_MIN_PITCH_LIMIT,								// min_pitch_limit
				GUN_BARREL_MAX_PITCH_LIMIT,								// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE1 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE2 +
				SHARE_WEAPON_PACKAGE3 +
				SHARE_WEAPON_PACKAGE4 +
				SHARE_WEAPON_PACKAGE5 +
				SHARE_WEAPON_PACKAGE6,
				SHARE_WEAPON_PACKAGE1 +										// pitch_share_mask
				SHARE_WEAPON_PACKAGE2 +
				SHARE_WEAPON_PACKAGE3 +
				SHARE_WEAPON_PACKAGE4,
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 3
			{
				ENTITY_SUB_TYPE_WEAPON_2A38M_30MM_ROUND,				// sub_type
				NUM_GUN_ROUNDS,												// number
				GUN_TURRET,														// heading_depth
				GUN_BARREL,														// pitch_depth
				LHS_LOWER_GUN_MUZZLE,			  							// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				GUN_TURRET_HEADING_RATE,									// heading_rate
				GUN_TURRET_MIN_HEADING_LIMIT,								// min_heading_limit
				GUN_TURRET_MAX_HEADING_LIMIT,								// max_heading_limit
				GUN_BARREL_PITCH_RATE,										// pitch_rate
				GUN_BARREL_MIN_PITCH_LIMIT,								// min_pitch_limit
				GUN_BARREL_MAX_PITCH_LIMIT,								// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE1 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE2 +
				SHARE_WEAPON_PACKAGE3 +
				SHARE_WEAPON_PACKAGE4 +
				SHARE_WEAPON_PACKAGE5 +
				SHARE_WEAPON_PACKAGE6,
				SHARE_WEAPON_PACKAGE1 +										// pitch_share_mask
				SHARE_WEAPON_PACKAGE2 +
				SHARE_WEAPON_PACKAGE3 +
				SHARE_WEAPON_PACKAGE4,
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 3
			{
				ENTITY_SUB_TYPE_WEAPON_2A38M_30MM_ROUND,				// sub_type
				NUM_GUN_ROUNDS,												// number
				GUN_TURRET,														// heading_depth
				GUN_BARREL,														// pitch_depth
				RHS_LOWER_GUN_MUZZLE,			  							// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				GUN_TURRET_HEADING_RATE,									// heading_rate
				GUN_TURRET_MIN_HEADING_LIMIT,								// min_heading_limit
				GUN_TURRET_MAX_HEADING_LIMIT,								// max_heading_limit
				GUN_BARREL_PITCH_RATE,										// pitch_rate
				GUN_BARREL_MIN_PITCH_LIMIT,								// min_pitch_limit
				GUN_BARREL_MAX_PITCH_LIMIT,								// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE1 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE2 +
				SHARE_WEAPON_PACKAGE3 +
				SHARE_WEAPON_PACKAGE4 +
				SHARE_WEAPON_PACKAGE5 +
				SHARE_WEAPON_PACKAGE6,
				SHARE_WEAPON_PACKAGE1 +										// pitch_share_mask
				SHARE_WEAPON_PACKAGE2 +
				SHARE_WEAPON_PACKAGE3 +
				SHARE_WEAPON_PACKAGE4,
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 5
			{
				ENTITY_SUB_TYPE_WEAPON_SA19_GRISON,						// sub_type
				NUM_GRISON_MISSILES,											// number
				GRISON_LAUNCHER_TURRET,										// heading_depth
				GRISON_LAUNCHER_INNER_TUBES,								// pitch_depth
				0,			  														// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				GRISON_LAUNCHER_HEADING_RATE,								// heading_rate
				GRISON_LAUNCHER_MIN_HEADING_LIMIT,						// min_heading_limit
				GRISON_LAUNCHER_MAX_HEADING_LIMIT,						// max_heading_limit
				GRISON_LAUNCHER_PITCH_RATE,								// pitch_rate
				GRISON_LAUNCHER_MIN_PITCH_LIMIT,							// min_pitch_limit
				GRISON_LAUNCHER_MAX_PITCH_LIMIT,							// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE1 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE2 +
				SHARE_WEAPON_PACKAGE3 +
				SHARE_WEAPON_PACKAGE4 +
				SHARE_WEAPON_PACKAGE5 +
				SHARE_WEAPON_PACKAGE6,
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 6
			{
				ENTITY_SUB_TYPE_WEAPON_SA19_GRISON,						// sub_type
				NUM_GRISON_MISSILES,											// number
				GRISON_LAUNCHER_TURRET,										// heading_depth
				GRISON_LAUNCHER_OUTER_TUBES,								// pitch_depth
				0,			  														// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				GRISON_LAUNCHER_HEADING_RATE,								// heading_rate
				GRISON_LAUNCHER_MIN_HEADING_LIMIT,						// min_heading_limit
				GRISON_LAUNCHER_MAX_HEADING_LIMIT,						// max_heading_limit
				GRISON_LAUNCHER_PITCH_RATE,								// pitch_rate
				GRISON_LAUNCHER_MIN_PITCH_LIMIT,							// min_pitch_limit
				GRISON_LAUNCHER_MAX_PITCH_LIMIT,		 					// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE1 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE2 +
				SHARE_WEAPON_PACKAGE3 +
				SHARE_WEAPON_PACKAGE4 +
				SHARE_WEAPON_PACKAGE5 +
				SHARE_WEAPON_PACKAGE6,
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 7
			{ENTITY_SUB_TYPE_WEAPON_NO_WEAPON},
			// WEAPON PACKAGE 8
			{ENTITY_SUB_TYPE_WEAPON_NO_WEAPON},
			// WEAPON PACKAGE 9
			{ENTITY_SUB_TYPE_WEAPON_NO_WEAPON},
			// WEAPON PACKAGE 10
			{ENTITY_SUB_TYPE_WEAPON_NO_WEAPON},
			// WEAPON PACKAGE 11
			{ENTITY_SUB_TYPE_WEAPON_NO_WEAPON},
			// WEAPON PACKAGE 12
			{ENTITY_SUB_TYPE_WEAPON_NO_WEAPON},
			// WEAPON PACKAGE 13
			{ENTITY_SUB_TYPE_WEAPON_NO_WEAPON},
			// WEAPON PACKAGE 14
			{ENTITY_SUB_TYPE_WEAPON_NO_WEAPON},
			// WEAPON PACKAGE 15
			{ENTITY_SUB_TYPE_WEAPON_NO_WEAPON},
			// WEAPON PACKAGE 16
			{ENTITY_SUB_TYPE_WEAPON_NO_WEAPON},
			// WEAPON PACKAGE 17
			{ENTITY_SUB_TYPE_WEAPON_NO_WEAPON},
			// WEAPON PACKAGE 18
			{ENTITY_SUB_TYPE_WEAPON_NO_WEAPON},
			// WEAPON PACKAGE 19
			{ENTITY_SUB_TYPE_WEAPON_NO_WEAPON},
			// WEAPON PACKAGE 20
			{ENTITY_SUB_TYPE_WEAPON_NO_WEAPON},
			// WEAPON PACKAGE 21
			{ENTITY_SUB_TYPE_WEAPON_NO_WEAPON},
			// WEAPON PACKAGE 22
			{ENTITY_SUB_TYPE_WEAPON_NO_WEAPON},
			// WEAPON PACKAGE 23
			{ENTITY_SUB_TYPE_WEAPON_NO_WEAPON},
			// WEAPON PACKAGE 24
			{ENTITY_SUB_TYPE_WEAPON_NO_WEAPON},
			// WEAPON PACKAGE 25
			{ENTITY_SUB_TYPE_WEAPON_NO_WEAPON},
			// WEAPON PACKAGE 26
			{ENTITY_SUB_TYPE_WEAPON_NO_WEAPON},
			// WEAPON PACKAGE 27
			{ENTITY_SUB_TYPE_WEAPON_NO_WEAPON},
			// WEAPON PACKAGE 28
			{ENTITY_SUB_TYPE_WEAPON_NO_WEAPON},
			// WEAPON PACKAGE 29
			{ENTITY_SUB_TYPE_WEAPON_NO_WEAPON},
			// WEAPON PACKAGE 30
			{ENTITY_SUB_TYPE_WEAPON_NO_WEAPON},
			// WEAPON PACKAGE 31
			{ENTITY_SUB_TYPE_WEAPON_NO_WEAPON},
			// WEAPON PACKAGE 32
			{ENTITY_SUB_TYPE_WEAPON_NO_WEAPON},
		},

		#undef GUN_TURRET
		#undef GRISON_LAUNCHER_TURRET

		#undef GUN_BARREL
		#undef GRISON_LAUNCHER_INNER_TUBES
		#undef GRISON_LAUNCHER_OUTER_TUBES

		#undef LHS_UPPER_GUN_MUZZLE
		#undef RHS_UPPER_GUN_MUZZLE
		#undef LHS_LOWER_GUN_MUZZLE
		#undef RHS_LOWER_GUN_MUZZLE

		#undef NUM_GUN_ROUNDS
		#undef NUM_GRISON_MISSILES

		#undef GUN_TURRET_HEADING_RATE
		#undef GUN_TURRET_MIN_HEADING_LIMIT
		#undef GUN_TURRET_MAX_HEADING_LIMIT
		#undef GUN_BARREL_PITCH_RATE
		#undef GUN_BARREL_MIN_PITCH_LIMIT
		#undef GUN_BARREL_MAX_PITCH_LIMIT

		#undef GRISON_LAUNCHER_HEADING_RATE
		#undef GRISON_LAUNCHER_MIN_HEADING_LIMIT
		#undef GRISON_LAUNCHER_MAX_HEADING_LIMIT
		#undef GRISON_LAUNCHER_PITCH_RATE
		#undef GRISON_LAUNCHER_MIN_PITCH_LIMIT
		#undef GRISON_LAUNCHER_MAX_PITCH_LIMIT
