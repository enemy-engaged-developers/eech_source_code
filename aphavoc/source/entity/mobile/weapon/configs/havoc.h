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
		// ENTITY_SUB_TYPE_AIRCRAFT_MI28N_HAVOC_B
		//
		////////////////////////////////////////////////////////////////////////////////

		#define LHS_HARDPOINT1							(HAVOC_LHS_INNER_PYLON)
		#define RHS_HARDPOINT1 							(HAVOC_RHS_INNER_PYLON)
		#define LHS_HARDPOINT2							(HAVOC_LHS_OUTER_PYLON)
		#define RHS_HARDPOINT2							(HAVOC_RHS_OUTER_PYLON)
		#define CANNON_TURRET							(HAVOC_CANNON_TURRET)
		#define CHAFF_DISPENSER							(HAVOC_CHAFF_DISPENSER)
		#define FLARE_DISPENSER							(HAVOC_FLARE_DISPENSER)

		#define CANNON_BARREL							(0)
		#define ATAKA_RACK								(0)
		#define IGLA_PYLON								(1)
		#define B8_POD		  								(2)
		#define B13_POD		  							(3)
		#define CANNON_POD		  						(4)
		#define CHAFF_VECTOR								(0)
		#define FLARE_VECTOR								(0)

		#define NUM_HE_CANNON_ROUNDS					(130)
		#define NUM_AP_CANNON_ROUNDS					(130)
		#define NUM_ATAKA_MISSILES						(8)
		#define NUM_IGLA_MISSILES						(4)
		#define NUM_S8_ROCKETS							(20)
		#define NUM_S13_ROCKETS							(5)
		#define NUM_CANNON_POD_ROUNDS					(250)
		#define NUM_CHAFFS								(30)
		#define NUM_FLARES								(30)

		#define CANNON_TURRET_HEADING_RATE			(rad (90.0))
		#define CANNON_TURRET_MIN_HEADING_LIMIT	(rad (-110.0))
		#define CANNON_TURRET_MAX_HEADING_LIMIT	(rad (110.0))
		#define CANNON_BARREL_PITCH_RATE				(rad (90.0))
		#define CANNON_BARREL_MIN_PITCH_LIMIT		(rad (-40.0))
		#define CANNON_BARREL_MAX_PITCH_LIMIT		(rad (13.0))

		////////////////////////////////////////
		//
		// WEAPON_CONFIG_TYPE_MI28N_HAVOC_B_1
		//
		////////////////////////////////////////
		{
			// WEAPON PACKAGE 1
			{
				ENTITY_SUB_TYPE_WEAPON_CHAFF,								// sub_type
				NUM_CHAFFS,														// number
				CHAFF_DISPENSER,												// heading_depth
				CHAFF_VECTOR,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 2
			{
				ENTITY_SUB_TYPE_WEAPON_FLARE,								// sub_type
				NUM_FLARES,														// number
				FLARE_DISPENSER,												// heading_depth
				FLARE_VECTOR,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 3
			{
				ENTITY_SUB_TYPE_WEAPON_2A42_30MM_HE_ROUND,			// sub_type
				NUM_HE_CANNON_ROUNDS,										// number
				CANNON_TURRET,													// heading_depth
				CANNON_BARREL,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				CANNON_TURRET_HEADING_RATE,								// heading_rate
				CANNON_TURRET_MIN_HEADING_LIMIT,							// min_heading_limit
				CANNON_TURRET_MAX_HEADING_LIMIT,							// max_heading_limit
				CANNON_BARREL_PITCH_RATE,									// pitch_rate
				CANNON_BARREL_MIN_PITCH_LIMIT,							// min_pitch_limit
				CANNON_BARREL_MAX_PITCH_LIMIT,							// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE3 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE4,
				SHARE_WEAPON_PACKAGE3 +										// pitch_share_mask
				SHARE_WEAPON_PACKAGE4,
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 4
			{
				ENTITY_SUB_TYPE_WEAPON_2A42_30MM_AP_ROUND,			// sub_type
				NUM_AP_CANNON_ROUNDS,										// number
				CANNON_TURRET,													// heading_depth
				CANNON_BARREL,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				CANNON_TURRET_HEADING_RATE,								// heading_rate
				CANNON_TURRET_MIN_HEADING_LIMIT,							// min_heading_limit
				CANNON_TURRET_MAX_HEADING_LIMIT,							// max_heading_limit
				CANNON_BARREL_PITCH_RATE,									// pitch_rate
				CANNON_BARREL_MIN_PITCH_LIMIT,							// min_pitch_limit
				CANNON_BARREL_MAX_PITCH_LIMIT,							// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE3 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE4,
				SHARE_WEAPON_PACKAGE3 +										// pitch_share_mask
				SHARE_WEAPON_PACKAGE4,
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 5
			{ENTITY_SUB_TYPE_WEAPON_NO_WEAPON},
			// WEAPON PACKAGE 6
			{ENTITY_SUB_TYPE_WEAPON_NO_WEAPON},
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
		////////////////////////////////////////
		//
		// WEAPON_CONFIG_TYPE_MI28N_HAVOC_B_2
		//
		////////////////////////////////////////
		{
			// WEAPON PACKAGE 1
			{
				ENTITY_SUB_TYPE_WEAPON_CHAFF,								// sub_type
				NUM_CHAFFS,														// number
				CHAFF_DISPENSER,												// heading_depth
				CHAFF_VECTOR,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 2
			{
				ENTITY_SUB_TYPE_WEAPON_FLARE,								// sub_type
				NUM_FLARES,														// number
				FLARE_DISPENSER,												// heading_depth
				FLARE_VECTOR,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 3
			{
				ENTITY_SUB_TYPE_WEAPON_2A42_30MM_HE_ROUND,			// sub_type
				NUM_HE_CANNON_ROUNDS,										// number
				CANNON_TURRET,													// heading_depth
				CANNON_BARREL,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				CANNON_TURRET_HEADING_RATE,								// heading_rate
				CANNON_TURRET_MIN_HEADING_LIMIT,							// min_heading_limit
				CANNON_TURRET_MAX_HEADING_LIMIT,							// max_heading_limit
				CANNON_BARREL_PITCH_RATE,									// pitch_rate
				CANNON_BARREL_MIN_PITCH_LIMIT,							// min_pitch_limit
				CANNON_BARREL_MAX_PITCH_LIMIT,							// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE3 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE4,
				SHARE_WEAPON_PACKAGE3 +										// pitch_share_mask
				SHARE_WEAPON_PACKAGE4,
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 4
			{
				ENTITY_SUB_TYPE_WEAPON_2A42_30MM_AP_ROUND,			// sub_type
				NUM_AP_CANNON_ROUNDS,										// number
				CANNON_TURRET,													// heading_depth
				CANNON_BARREL,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				CANNON_TURRET_HEADING_RATE,								// heading_rate
				CANNON_TURRET_MIN_HEADING_LIMIT,							// min_heading_limit
				CANNON_TURRET_MAX_HEADING_LIMIT,							// max_heading_limit
				CANNON_BARREL_PITCH_RATE,									// pitch_rate
				CANNON_BARREL_MIN_PITCH_LIMIT,							// min_pitch_limit
				CANNON_BARREL_MAX_PITCH_LIMIT,							// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE3 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE4,
				SHARE_WEAPON_PACKAGE3 +										// pitch_share_mask
				SHARE_WEAPON_PACKAGE4,
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 5
			{
				ENTITY_SUB_TYPE_WEAPON_IGLA_V,							// sub_type
				NUM_IGLA_MISSILES,											// number
				LHS_HARDPOINT1,												// heading_depth
				IGLA_PYLON,														// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 6
			{
				ENTITY_SUB_TYPE_WEAPON_IGLA_V,							// sub_type
				NUM_IGLA_MISSILES,											// number
				RHS_HARDPOINT1,												// heading_depth
				IGLA_PYLON,														// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
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
		////////////////////////////////////////
		//
		// WEAPON_CONFIG_TYPE_MI28N_HAVOC_B_3
		//
		////////////////////////////////////////
		{
			// WEAPON PACKAGE 1
			{
				ENTITY_SUB_TYPE_WEAPON_CHAFF,								// sub_type
				NUM_CHAFFS,														// number
				CHAFF_DISPENSER,												// heading_depth
				CHAFF_VECTOR,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 2
			{
				ENTITY_SUB_TYPE_WEAPON_FLARE,								// sub_type
				NUM_FLARES,														// number
				FLARE_DISPENSER,												// heading_depth
				FLARE_VECTOR,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 3
			{
				ENTITY_SUB_TYPE_WEAPON_2A42_30MM_HE_ROUND,			// sub_type
				NUM_HE_CANNON_ROUNDS,										// number
				CANNON_TURRET,													// heading_depth
				CANNON_BARREL,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				CANNON_TURRET_HEADING_RATE,								// heading_rate
				CANNON_TURRET_MIN_HEADING_LIMIT,							// min_heading_limit
				CANNON_TURRET_MAX_HEADING_LIMIT,							// max_heading_limit
				CANNON_BARREL_PITCH_RATE,									// pitch_rate
				CANNON_BARREL_MIN_PITCH_LIMIT,							// min_pitch_limit
				CANNON_BARREL_MAX_PITCH_LIMIT,							// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE3 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE4,
				SHARE_WEAPON_PACKAGE3 +										// pitch_share_mask
				SHARE_WEAPON_PACKAGE4,
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 4
			{
				ENTITY_SUB_TYPE_WEAPON_2A42_30MM_AP_ROUND,			// sub_type
				NUM_AP_CANNON_ROUNDS,										// number
				CANNON_TURRET,													// heading_depth
				CANNON_BARREL,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				CANNON_TURRET_HEADING_RATE,								// heading_rate
				CANNON_TURRET_MIN_HEADING_LIMIT,							// min_heading_limit
				CANNON_TURRET_MAX_HEADING_LIMIT,							// max_heading_limit
				CANNON_BARREL_PITCH_RATE,									// pitch_rate
				CANNON_BARREL_MIN_PITCH_LIMIT,							// min_pitch_limit
				CANNON_BARREL_MAX_PITCH_LIMIT,							// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE3 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE4,
				SHARE_WEAPON_PACKAGE3 +										// pitch_share_mask
				SHARE_WEAPON_PACKAGE4,
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 5
			{
				ENTITY_SUB_TYPE_WEAPON_S8,									// sub_type
				NUM_S8_ROCKETS,												// number
				LHS_HARDPOINT1,												// heading_depth
				B8_POD,															// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				2,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 6
			{
				ENTITY_SUB_TYPE_WEAPON_S8,									// sub_type
				NUM_S8_ROCKETS,												// number
				RHS_HARDPOINT1,												// heading_depth
				B8_POD,															// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				2,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
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
		////////////////////////////////////////
		//
		// WEAPON_CONFIG_TYPE_MI28N_HAVOC_B_4
		//
		////////////////////////////////////////
		{
			// WEAPON PACKAGE 1
			{
				ENTITY_SUB_TYPE_WEAPON_CHAFF,								// sub_type
				NUM_CHAFFS,														// number
				CHAFF_DISPENSER,												// heading_depth
				CHAFF_VECTOR,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 2
			{
				ENTITY_SUB_TYPE_WEAPON_FLARE,								// sub_type
				NUM_FLARES,														// number
				FLARE_DISPENSER,												// heading_depth
				FLARE_VECTOR,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 3
			{
				ENTITY_SUB_TYPE_WEAPON_2A42_30MM_HE_ROUND,			// sub_type
				NUM_HE_CANNON_ROUNDS,										// number
				CANNON_TURRET,													// heading_depth
				CANNON_BARREL,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				CANNON_TURRET_HEADING_RATE,								// heading_rate
				CANNON_TURRET_MIN_HEADING_LIMIT,							// min_heading_limit
				CANNON_TURRET_MAX_HEADING_LIMIT,							// max_heading_limit
				CANNON_BARREL_PITCH_RATE,									// pitch_rate
				CANNON_BARREL_MIN_PITCH_LIMIT,							// min_pitch_limit
				CANNON_BARREL_MAX_PITCH_LIMIT,							// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE3 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE4,
				SHARE_WEAPON_PACKAGE3 +										// pitch_share_mask
				SHARE_WEAPON_PACKAGE4,
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 4
			{
				ENTITY_SUB_TYPE_WEAPON_2A42_30MM_AP_ROUND,			// sub_type
				NUM_AP_CANNON_ROUNDS,										// number
				CANNON_TURRET,													// heading_depth
				CANNON_BARREL,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				CANNON_TURRET_HEADING_RATE,								// heading_rate
				CANNON_TURRET_MIN_HEADING_LIMIT,							// min_heading_limit
				CANNON_TURRET_MAX_HEADING_LIMIT,							// max_heading_limit
				CANNON_BARREL_PITCH_RATE,									// pitch_rate
				CANNON_BARREL_MIN_PITCH_LIMIT,							// min_pitch_limit
				CANNON_BARREL_MAX_PITCH_LIMIT,							// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE3 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE4,
				SHARE_WEAPON_PACKAGE3 +										// pitch_share_mask
				SHARE_WEAPON_PACKAGE4,
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 5
			{
				ENTITY_SUB_TYPE_WEAPON_S13,								// sub_type
				NUM_S13_ROCKETS,												// number
				LHS_HARDPOINT1,												// heading_depth
				B13_POD,															// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				2,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 6
			{
				ENTITY_SUB_TYPE_WEAPON_S13,								// sub_type
				NUM_S13_ROCKETS,												// number
				RHS_HARDPOINT1,												// heading_depth
				B13_POD,															// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				2,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
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
		////////////////////////////////////////
		//
		// WEAPON_CONFIG_TYPE_MI28N_HAVOC_B_5
		//
		////////////////////////////////////////
		{
			// WEAPON PACKAGE 1
			{
				ENTITY_SUB_TYPE_WEAPON_CHAFF,								// sub_type
				NUM_CHAFFS,														// number
				CHAFF_DISPENSER,												// heading_depth
				CHAFF_VECTOR,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 2
			{
				ENTITY_SUB_TYPE_WEAPON_FLARE,								// sub_type
				NUM_FLARES,														// number
				FLARE_DISPENSER,												// heading_depth
				FLARE_VECTOR,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 3
			{
				ENTITY_SUB_TYPE_WEAPON_2A42_30MM_HE_ROUND,			// sub_type
				NUM_HE_CANNON_ROUNDS,										// number
				CANNON_TURRET,													// heading_depth
				CANNON_BARREL,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				CANNON_TURRET_HEADING_RATE,								// heading_rate
				CANNON_TURRET_MIN_HEADING_LIMIT,							// min_heading_limit
				CANNON_TURRET_MAX_HEADING_LIMIT,							// max_heading_limit
				CANNON_BARREL_PITCH_RATE,									// pitch_rate
				CANNON_BARREL_MIN_PITCH_LIMIT,							// min_pitch_limit
				CANNON_BARREL_MAX_PITCH_LIMIT,							// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE3 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE4,
				SHARE_WEAPON_PACKAGE3 +										// pitch_share_mask
				SHARE_WEAPON_PACKAGE4,
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 4
			{
				ENTITY_SUB_TYPE_WEAPON_2A42_30MM_AP_ROUND,			// sub_type
				NUM_AP_CANNON_ROUNDS,										// number
				CANNON_TURRET,													// heading_depth
				CANNON_BARREL,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				CANNON_TURRET_HEADING_RATE,								// heading_rate
				CANNON_TURRET_MIN_HEADING_LIMIT,							// min_heading_limit
				CANNON_TURRET_MAX_HEADING_LIMIT,							// max_heading_limit
				CANNON_BARREL_PITCH_RATE,									// pitch_rate
				CANNON_BARREL_MIN_PITCH_LIMIT,							// min_pitch_limit
				CANNON_BARREL_MAX_PITCH_LIMIT,							// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE3 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE4,
				SHARE_WEAPON_PACKAGE3 +										// pitch_share_mask
				SHARE_WEAPON_PACKAGE4,
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 5
			{
				ENTITY_SUB_TYPE_WEAPON_GSH23L_23MM_ROUND,				// sub_type
				NUM_CANNON_POD_ROUNDS,										// number
				LHS_HARDPOINT1,												// heading_depth
				CANNON_POD,														// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				2,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 6
			{
				ENTITY_SUB_TYPE_WEAPON_GSH23L_23MM_ROUND,				// sub_type
				NUM_CANNON_POD_ROUNDS,										// number
				RHS_HARDPOINT1,												// heading_depth
				CANNON_POD,														// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				2,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
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
		////////////////////////////////////////
		//
		// WEAPON_CONFIG_TYPE_MI28N_HAVOC_B_6
		//
		////////////////////////////////////////
		{
			// WEAPON PACKAGE 1
			{
				ENTITY_SUB_TYPE_WEAPON_CHAFF,								// sub_type
				NUM_CHAFFS,														// number
				CHAFF_DISPENSER,												// heading_depth
				CHAFF_VECTOR,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 2
			{
				ENTITY_SUB_TYPE_WEAPON_FLARE,								// sub_type
				NUM_FLARES,														// number
				FLARE_DISPENSER,												// heading_depth
				FLARE_VECTOR,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 3
			{
				ENTITY_SUB_TYPE_WEAPON_2A42_30MM_HE_ROUND,			// sub_type
				NUM_HE_CANNON_ROUNDS,										// number
				CANNON_TURRET,													// heading_depth
				CANNON_BARREL,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				CANNON_TURRET_HEADING_RATE,								// heading_rate
				CANNON_TURRET_MIN_HEADING_LIMIT,							// min_heading_limit
				CANNON_TURRET_MAX_HEADING_LIMIT,							// max_heading_limit
				CANNON_BARREL_PITCH_RATE,									// pitch_rate
				CANNON_BARREL_MIN_PITCH_LIMIT,							// min_pitch_limit
				CANNON_BARREL_MAX_PITCH_LIMIT,							// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE3 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE4,
				SHARE_WEAPON_PACKAGE3 +										// pitch_share_mask
				SHARE_WEAPON_PACKAGE4,
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 4
			{
				ENTITY_SUB_TYPE_WEAPON_2A42_30MM_AP_ROUND,			// sub_type
				NUM_AP_CANNON_ROUNDS,										// number
				CANNON_TURRET,													// heading_depth
				CANNON_BARREL,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				CANNON_TURRET_HEADING_RATE,								// heading_rate
				CANNON_TURRET_MIN_HEADING_LIMIT,							// min_heading_limit
				CANNON_TURRET_MAX_HEADING_LIMIT,							// max_heading_limit
				CANNON_BARREL_PITCH_RATE,									// pitch_rate
				CANNON_BARREL_MIN_PITCH_LIMIT,							// min_pitch_limit
				CANNON_BARREL_MAX_PITCH_LIMIT,							// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE3 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE4,
				SHARE_WEAPON_PACKAGE3 +										// pitch_share_mask
				SHARE_WEAPON_PACKAGE4,
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 5
			{
				ENTITY_SUB_TYPE_WEAPON_ATAKA,								// sub_type
				NUM_ATAKA_MISSILES,											// number
				LHS_HARDPOINT2,												// heading_depth
				ATAKA_RACK,														// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 6
			{
				ENTITY_SUB_TYPE_WEAPON_ATAKA,								// sub_type
				NUM_ATAKA_MISSILES,											// number
				RHS_HARDPOINT2,												// heading_depth
				ATAKA_RACK,														// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
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
		////////////////////////////////////////
		//
		// WEAPON_CONFIG_TYPE_MI28N_HAVOC_B_7
		//
		////////////////////////////////////////
		{
			// WEAPON PACKAGE 1
			{
				ENTITY_SUB_TYPE_WEAPON_CHAFF,								// sub_type
				NUM_CHAFFS,														// number
				CHAFF_DISPENSER,												// heading_depth
				CHAFF_VECTOR,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 2
			{
				ENTITY_SUB_TYPE_WEAPON_FLARE,								// sub_type
				NUM_FLARES,														// number
				FLARE_DISPENSER,												// heading_depth
				FLARE_VECTOR,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 3
			{
				ENTITY_SUB_TYPE_WEAPON_2A42_30MM_HE_ROUND,			// sub_type
				NUM_HE_CANNON_ROUNDS,										// number
				CANNON_TURRET,													// heading_depth
				CANNON_BARREL,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				CANNON_TURRET_HEADING_RATE,								// heading_rate
				CANNON_TURRET_MIN_HEADING_LIMIT,							// min_heading_limit
				CANNON_TURRET_MAX_HEADING_LIMIT,							// max_heading_limit
				CANNON_BARREL_PITCH_RATE,									// pitch_rate
				CANNON_BARREL_MIN_PITCH_LIMIT,							// min_pitch_limit
				CANNON_BARREL_MAX_PITCH_LIMIT,							// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE3 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE4,
				SHARE_WEAPON_PACKAGE3 +										// pitch_share_mask
				SHARE_WEAPON_PACKAGE4,
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 4
			{
				ENTITY_SUB_TYPE_WEAPON_2A42_30MM_AP_ROUND,			// sub_type
				NUM_AP_CANNON_ROUNDS,										// number
				CANNON_TURRET,													// heading_depth
				CANNON_BARREL,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				CANNON_TURRET_HEADING_RATE,								// heading_rate
				CANNON_TURRET_MIN_HEADING_LIMIT,							// min_heading_limit
				CANNON_TURRET_MAX_HEADING_LIMIT,							// max_heading_limit
				CANNON_BARREL_PITCH_RATE,									// pitch_rate
				CANNON_BARREL_MIN_PITCH_LIMIT,							// min_pitch_limit
				CANNON_BARREL_MAX_PITCH_LIMIT,							// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE3 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE4,
				SHARE_WEAPON_PACKAGE3 +										// pitch_share_mask
				SHARE_WEAPON_PACKAGE4,
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 5
			{
				ENTITY_SUB_TYPE_WEAPON_IGLA_V,							// sub_type
				NUM_IGLA_MISSILES,											// number
				LHS_HARDPOINT1,												// heading_depth
				IGLA_PYLON,														// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 6
			{
				ENTITY_SUB_TYPE_WEAPON_IGLA_V,							// sub_type
				NUM_IGLA_MISSILES,											// number
				RHS_HARDPOINT1,												// heading_depth
				IGLA_PYLON,														// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 7
			{
				ENTITY_SUB_TYPE_WEAPON_ATAKA,								// sub_type
				NUM_ATAKA_MISSILES,											// number
				LHS_HARDPOINT2,												// heading_depth
				ATAKA_RACK,														// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 8
			{
				ENTITY_SUB_TYPE_WEAPON_ATAKA,								// sub_type
				NUM_ATAKA_MISSILES,											// number
				RHS_HARDPOINT2,												// heading_depth
				ATAKA_RACK,														// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
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
		////////////////////////////////////////
		//
		// WEAPON_CONFIG_TYPE_MI28N_HAVOC_B_8
		//
		////////////////////////////////////////
		{
			// WEAPON PACKAGE 1
			{
				ENTITY_SUB_TYPE_WEAPON_CHAFF,								// sub_type
				NUM_CHAFFS,														// number
				CHAFF_DISPENSER,												// heading_depth
				CHAFF_VECTOR,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 2
			{
				ENTITY_SUB_TYPE_WEAPON_FLARE,								// sub_type
				NUM_FLARES,														// number
				FLARE_DISPENSER,												// heading_depth
				FLARE_VECTOR,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 3
			{
				ENTITY_SUB_TYPE_WEAPON_2A42_30MM_HE_ROUND,			// sub_type
				NUM_HE_CANNON_ROUNDS,										// number
				CANNON_TURRET,													// heading_depth
				CANNON_BARREL,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				CANNON_TURRET_HEADING_RATE,								// heading_rate
				CANNON_TURRET_MIN_HEADING_LIMIT,							// min_heading_limit
				CANNON_TURRET_MAX_HEADING_LIMIT,							// max_heading_limit
				CANNON_BARREL_PITCH_RATE,									// pitch_rate
				CANNON_BARREL_MIN_PITCH_LIMIT,							// min_pitch_limit
				CANNON_BARREL_MAX_PITCH_LIMIT,							// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE3 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE4,
				SHARE_WEAPON_PACKAGE3 +										// pitch_share_mask
				SHARE_WEAPON_PACKAGE4,
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 4
			{
				ENTITY_SUB_TYPE_WEAPON_2A42_30MM_AP_ROUND,			// sub_type
				NUM_AP_CANNON_ROUNDS,										// number
				CANNON_TURRET,													// heading_depth
				CANNON_BARREL,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				CANNON_TURRET_HEADING_RATE,								// heading_rate
				CANNON_TURRET_MIN_HEADING_LIMIT,							// min_heading_limit
				CANNON_TURRET_MAX_HEADING_LIMIT,							// max_heading_limit
				CANNON_BARREL_PITCH_RATE,									// pitch_rate
				CANNON_BARREL_MIN_PITCH_LIMIT,							// min_pitch_limit
				CANNON_BARREL_MAX_PITCH_LIMIT,							// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE3 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE4,
				SHARE_WEAPON_PACKAGE3 +										// pitch_share_mask
				SHARE_WEAPON_PACKAGE4,
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 5
			{
				ENTITY_SUB_TYPE_WEAPON_S8,									// sub_type
				NUM_S8_ROCKETS,												// number
				LHS_HARDPOINT1,												// heading_depth
				B8_POD,															// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				8,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 6
			{
				ENTITY_SUB_TYPE_WEAPON_S8,									// sub_type
				NUM_S8_ROCKETS,												// number
				RHS_HARDPOINT1,												// heading_depth
				B8_POD,															// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				8,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 7
			{
				ENTITY_SUB_TYPE_WEAPON_ATAKA,								// sub_type
				NUM_ATAKA_MISSILES,											// number
				LHS_HARDPOINT2,												// heading_depth
				ATAKA_RACK,														// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 8
			{
				ENTITY_SUB_TYPE_WEAPON_ATAKA,								// sub_type
				NUM_ATAKA_MISSILES,											// number
				RHS_HARDPOINT2,												// heading_depth
				ATAKA_RACK,														// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
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
		////////////////////////////////////////
		//
		// WEAPON_CONFIG_TYPE_MI28N_HAVOC_B_9
		//
		////////////////////////////////////////
		{
			// WEAPON PACKAGE 1
			{
				ENTITY_SUB_TYPE_WEAPON_CHAFF,								// sub_type
				NUM_CHAFFS,														// number
				CHAFF_DISPENSER,												// heading_depth
				CHAFF_VECTOR,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 2
			{
				ENTITY_SUB_TYPE_WEAPON_FLARE,								// sub_type
				NUM_FLARES,														// number
				FLARE_DISPENSER,												// heading_depth
				FLARE_VECTOR,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 3
			{
				ENTITY_SUB_TYPE_WEAPON_2A42_30MM_HE_ROUND,			// sub_type
				NUM_HE_CANNON_ROUNDS,										// number
				CANNON_TURRET,													// heading_depth
				CANNON_BARREL,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				CANNON_TURRET_HEADING_RATE,								// heading_rate
				CANNON_TURRET_MIN_HEADING_LIMIT,							// min_heading_limit
				CANNON_TURRET_MAX_HEADING_LIMIT,							// max_heading_limit
				CANNON_BARREL_PITCH_RATE,									// pitch_rate
				CANNON_BARREL_MIN_PITCH_LIMIT,							// min_pitch_limit
				CANNON_BARREL_MAX_PITCH_LIMIT,							// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE3 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE4,
				SHARE_WEAPON_PACKAGE3 +										// pitch_share_mask
				SHARE_WEAPON_PACKAGE4,
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 4
			{
				ENTITY_SUB_TYPE_WEAPON_2A42_30MM_AP_ROUND,			// sub_type
				NUM_AP_CANNON_ROUNDS,										// number
				CANNON_TURRET,													// heading_depth
				CANNON_BARREL,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				CANNON_TURRET_HEADING_RATE,								// heading_rate
				CANNON_TURRET_MIN_HEADING_LIMIT,							// min_heading_limit
				CANNON_TURRET_MAX_HEADING_LIMIT,							// max_heading_limit
				CANNON_BARREL_PITCH_RATE,									// pitch_rate
				CANNON_BARREL_MIN_PITCH_LIMIT,							// min_pitch_limit
				CANNON_BARREL_MAX_PITCH_LIMIT,							// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE3 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE4,
				SHARE_WEAPON_PACKAGE3 +										// pitch_share_mask
				SHARE_WEAPON_PACKAGE4,
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 5
			{
				ENTITY_SUB_TYPE_WEAPON_S13,								// sub_type
				NUM_S13_ROCKETS,												// number
				LHS_HARDPOINT1,												// heading_depth
				B13_POD,															// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				2,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 6
			{
				ENTITY_SUB_TYPE_WEAPON_S13,								// sub_type
				NUM_S13_ROCKETS,												// number
				RHS_HARDPOINT1,												// heading_depth
				B13_POD,															// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				2,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 7
			{
				ENTITY_SUB_TYPE_WEAPON_ATAKA,								// sub_type
				NUM_ATAKA_MISSILES,											// number
				LHS_HARDPOINT2,												// heading_depth
				ATAKA_RACK,														// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 8
			{
				ENTITY_SUB_TYPE_WEAPON_ATAKA,								// sub_type
				NUM_ATAKA_MISSILES,											// number
				RHS_HARDPOINT2,												// heading_depth
				ATAKA_RACK,														// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
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
		////////////////////////////////////////
		//
		// WEAPON_CONFIG_TYPE_MI28N_HAVOC_B_10
		//
		////////////////////////////////////////
		{
			// WEAPON PACKAGE 1
			{
				ENTITY_SUB_TYPE_WEAPON_CHAFF,								// sub_type
				NUM_CHAFFS,														// number
				CHAFF_DISPENSER,												// heading_depth
				CHAFF_VECTOR,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 2
			{
				ENTITY_SUB_TYPE_WEAPON_FLARE,								// sub_type
				NUM_FLARES,														// number
				FLARE_DISPENSER,												// heading_depth
				FLARE_VECTOR,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 3
			{
				ENTITY_SUB_TYPE_WEAPON_2A42_30MM_HE_ROUND,			// sub_type
				NUM_HE_CANNON_ROUNDS,										// number
				CANNON_TURRET,													// heading_depth
				CANNON_BARREL,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				CANNON_TURRET_HEADING_RATE,								// heading_rate
				CANNON_TURRET_MIN_HEADING_LIMIT,							// min_heading_limit
				CANNON_TURRET_MAX_HEADING_LIMIT,							// max_heading_limit
				CANNON_BARREL_PITCH_RATE,									// pitch_rate
				CANNON_BARREL_MIN_PITCH_LIMIT,							// min_pitch_limit
				CANNON_BARREL_MAX_PITCH_LIMIT,							// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE3 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE4,
				SHARE_WEAPON_PACKAGE3 +										// pitch_share_mask
				SHARE_WEAPON_PACKAGE4,
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 4
			{
				ENTITY_SUB_TYPE_WEAPON_2A42_30MM_AP_ROUND,			// sub_type
				NUM_AP_CANNON_ROUNDS,										// number
				CANNON_TURRET,													// heading_depth
				CANNON_BARREL,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				CANNON_TURRET_HEADING_RATE,								// heading_rate
				CANNON_TURRET_MIN_HEADING_LIMIT,							// min_heading_limit
				CANNON_TURRET_MAX_HEADING_LIMIT,							// max_heading_limit
				CANNON_BARREL_PITCH_RATE,									// pitch_rate
				CANNON_BARREL_MIN_PITCH_LIMIT,							// min_pitch_limit
				CANNON_BARREL_MAX_PITCH_LIMIT,							// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE3 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE4,
				SHARE_WEAPON_PACKAGE3 +										// pitch_share_mask
				SHARE_WEAPON_PACKAGE4,
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 5
			{
				ENTITY_SUB_TYPE_WEAPON_GSH23L_23MM_ROUND,				// sub_type
				NUM_CANNON_POD_ROUNDS,										// number
				LHS_HARDPOINT1,												// heading_depth
				CANNON_POD,														// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				2,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 6
			{
				ENTITY_SUB_TYPE_WEAPON_GSH23L_23MM_ROUND,				// sub_type
				NUM_CANNON_POD_ROUNDS,										// number
				RHS_HARDPOINT1,												// heading_depth
				CANNON_POD,														// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				2,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 7
			{
				ENTITY_SUB_TYPE_WEAPON_ATAKA,								// sub_type
				NUM_ATAKA_MISSILES,											// number
				LHS_HARDPOINT2,												// heading_depth
				ATAKA_RACK,														// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 8
			{
				ENTITY_SUB_TYPE_WEAPON_ATAKA,								// sub_type
				NUM_ATAKA_MISSILES,											// number
				RHS_HARDPOINT2,												// heading_depth
				ATAKA_RACK,														// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
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
		////////////////////////////////////////
		//
		// WEAPON_CONFIG_TYPE_MI28N_HAVOC_B_11
		//
		////////////////////////////////////////
		{
			// WEAPON PACKAGE 1
			{
				ENTITY_SUB_TYPE_WEAPON_CHAFF,								// sub_type
				NUM_CHAFFS,														// number
				CHAFF_DISPENSER,												// heading_depth
				CHAFF_VECTOR,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 2
			{
				ENTITY_SUB_TYPE_WEAPON_FLARE,								// sub_type
				NUM_FLARES,														// number
				FLARE_DISPENSER,												// heading_depth
				FLARE_VECTOR,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 3
			{
				ENTITY_SUB_TYPE_WEAPON_2A42_30MM_HE_ROUND,			// sub_type
				NUM_HE_CANNON_ROUNDS,										// number
				CANNON_TURRET,													// heading_depth
				CANNON_BARREL,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				CANNON_TURRET_HEADING_RATE,								// heading_rate
				CANNON_TURRET_MIN_HEADING_LIMIT,							// min_heading_limit
				CANNON_TURRET_MAX_HEADING_LIMIT,							// max_heading_limit
				CANNON_BARREL_PITCH_RATE,									// pitch_rate
				CANNON_BARREL_MIN_PITCH_LIMIT,							// min_pitch_limit
				CANNON_BARREL_MAX_PITCH_LIMIT,							// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE3 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE4,
				SHARE_WEAPON_PACKAGE3 +										// pitch_share_mask
				SHARE_WEAPON_PACKAGE4,
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 4
			{
				ENTITY_SUB_TYPE_WEAPON_2A42_30MM_AP_ROUND,			// sub_type
				NUM_AP_CANNON_ROUNDS,										// number
				CANNON_TURRET,													// heading_depth
				CANNON_BARREL,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				CANNON_TURRET_HEADING_RATE,								// heading_rate
				CANNON_TURRET_MIN_HEADING_LIMIT,							// min_heading_limit
				CANNON_TURRET_MAX_HEADING_LIMIT,							// max_heading_limit
				CANNON_BARREL_PITCH_RATE,									// pitch_rate
				CANNON_BARREL_MIN_PITCH_LIMIT,							// min_pitch_limit
				CANNON_BARREL_MAX_PITCH_LIMIT,							// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE3 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE4,
				SHARE_WEAPON_PACKAGE3 +										// pitch_share_mask
				SHARE_WEAPON_PACKAGE4,
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 5
			{
				ENTITY_SUB_TYPE_WEAPON_IGLA_V,							// sub_type
				NUM_IGLA_MISSILES,											// number
				LHS_HARDPOINT2,												// heading_depth
				IGLA_PYLON,														// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 6
			{
				ENTITY_SUB_TYPE_WEAPON_IGLA_V,							// sub_type
				NUM_IGLA_MISSILES,											// number
				RHS_HARDPOINT2,												// heading_depth
				IGLA_PYLON,														// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
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
		////////////////////////////////////////
		//
		// WEAPON_CONFIG_TYPE_MI28N_HAVOC_B_12
		//
		////////////////////////////////////////
		{
			// WEAPON PACKAGE 1
			{
				ENTITY_SUB_TYPE_WEAPON_CHAFF,								// sub_type
				NUM_CHAFFS,														// number
				CHAFF_DISPENSER,												// heading_depth
				CHAFF_VECTOR,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 2
			{
				ENTITY_SUB_TYPE_WEAPON_FLARE,								// sub_type
				NUM_FLARES,														// number
				FLARE_DISPENSER,												// heading_depth
				FLARE_VECTOR,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 3
			{
				ENTITY_SUB_TYPE_WEAPON_2A42_30MM_HE_ROUND,			// sub_type
				NUM_HE_CANNON_ROUNDS,										// number
				CANNON_TURRET,													// heading_depth
				CANNON_BARREL,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				CANNON_TURRET_HEADING_RATE,								// heading_rate
				CANNON_TURRET_MIN_HEADING_LIMIT,							// min_heading_limit
				CANNON_TURRET_MAX_HEADING_LIMIT,							// max_heading_limit
				CANNON_BARREL_PITCH_RATE,									// pitch_rate
				CANNON_BARREL_MIN_PITCH_LIMIT,							// min_pitch_limit
				CANNON_BARREL_MAX_PITCH_LIMIT,							// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE3 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE4,
				SHARE_WEAPON_PACKAGE3 +										// pitch_share_mask
				SHARE_WEAPON_PACKAGE4,
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 4
			{
				ENTITY_SUB_TYPE_WEAPON_2A42_30MM_AP_ROUND,			// sub_type
				NUM_AP_CANNON_ROUNDS,										// number
				CANNON_TURRET,													// heading_depth
				CANNON_BARREL,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				CANNON_TURRET_HEADING_RATE,								// heading_rate
				CANNON_TURRET_MIN_HEADING_LIMIT,							// min_heading_limit
				CANNON_TURRET_MAX_HEADING_LIMIT,							// max_heading_limit
				CANNON_BARREL_PITCH_RATE,									// pitch_rate
				CANNON_BARREL_MIN_PITCH_LIMIT,							// min_pitch_limit
				CANNON_BARREL_MAX_PITCH_LIMIT,							// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE3 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE4,
				SHARE_WEAPON_PACKAGE3 +										// pitch_share_mask
				SHARE_WEAPON_PACKAGE4,
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 5
			{
				ENTITY_SUB_TYPE_WEAPON_IGLA_V,							// sub_type
				NUM_IGLA_MISSILES,											// number
				LHS_HARDPOINT1,												// heading_depth
				IGLA_PYLON,														// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 6
			{
				ENTITY_SUB_TYPE_WEAPON_IGLA_V,							// sub_type
				NUM_IGLA_MISSILES,											// number
				RHS_HARDPOINT1,												// heading_depth
				IGLA_PYLON,														// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 7
			{
				ENTITY_SUB_TYPE_WEAPON_IGLA_V,							// sub_type
				NUM_IGLA_MISSILES,											// number
				LHS_HARDPOINT2,												// heading_depth
				IGLA_PYLON,														// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 8
			{
				ENTITY_SUB_TYPE_WEAPON_IGLA_V,							// sub_type
				NUM_IGLA_MISSILES,											// number
				RHS_HARDPOINT2,												// heading_depth
				IGLA_PYLON,														// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
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
		////////////////////////////////////////
		//
		// WEAPON_CONFIG_TYPE_MI28N_HAVOC_B_13
		//
		////////////////////////////////////////
		{
			// WEAPON PACKAGE 1
			{
				ENTITY_SUB_TYPE_WEAPON_CHAFF,								// sub_type
				NUM_CHAFFS,														// number
				CHAFF_DISPENSER,												// heading_depth
				CHAFF_VECTOR,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 2
			{
				ENTITY_SUB_TYPE_WEAPON_FLARE,								// sub_type
				NUM_FLARES,														// number
				FLARE_DISPENSER,												// heading_depth
				FLARE_VECTOR,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 3
			{
				ENTITY_SUB_TYPE_WEAPON_2A42_30MM_HE_ROUND,			// sub_type
				NUM_HE_CANNON_ROUNDS,										// number
				CANNON_TURRET,													// heading_depth
				CANNON_BARREL,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				CANNON_TURRET_HEADING_RATE,								// heading_rate
				CANNON_TURRET_MIN_HEADING_LIMIT,							// min_heading_limit
				CANNON_TURRET_MAX_HEADING_LIMIT,							// max_heading_limit
				CANNON_BARREL_PITCH_RATE,									// pitch_rate
				CANNON_BARREL_MIN_PITCH_LIMIT,							// min_pitch_limit
				CANNON_BARREL_MAX_PITCH_LIMIT,							// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE3 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE4,
				SHARE_WEAPON_PACKAGE3 +										// pitch_share_mask
				SHARE_WEAPON_PACKAGE4,
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 4
			{
				ENTITY_SUB_TYPE_WEAPON_2A42_30MM_AP_ROUND,			// sub_type
				NUM_AP_CANNON_ROUNDS,										// number
				CANNON_TURRET,													// heading_depth
				CANNON_BARREL,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				CANNON_TURRET_HEADING_RATE,								// heading_rate
				CANNON_TURRET_MIN_HEADING_LIMIT,							// min_heading_limit
				CANNON_TURRET_MAX_HEADING_LIMIT,							// max_heading_limit
				CANNON_BARREL_PITCH_RATE,									// pitch_rate
				CANNON_BARREL_MIN_PITCH_LIMIT,							// min_pitch_limit
				CANNON_BARREL_MAX_PITCH_LIMIT,							// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE3 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE4,
				SHARE_WEAPON_PACKAGE3 +										// pitch_share_mask
				SHARE_WEAPON_PACKAGE4,
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 5
			{
				ENTITY_SUB_TYPE_WEAPON_S8,									// sub_type
				NUM_S8_ROCKETS,												// number
				LHS_HARDPOINT1,												// heading_depth
				B8_POD,															// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				2,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 6
			{
				ENTITY_SUB_TYPE_WEAPON_S8,									// sub_type
				NUM_S8_ROCKETS,												// number
				RHS_HARDPOINT1,												// heading_depth
				B8_POD,															// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				2,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 7
			{
				ENTITY_SUB_TYPE_WEAPON_IGLA_V,							// sub_type
				NUM_IGLA_MISSILES,											// number
				LHS_HARDPOINT2,												// heading_depth
				IGLA_PYLON,														// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 8
			{
				ENTITY_SUB_TYPE_WEAPON_IGLA_V,							// sub_type
				NUM_IGLA_MISSILES,											// number
				RHS_HARDPOINT2,												// heading_depth
				IGLA_PYLON,														// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
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
		////////////////////////////////////////
		//
		// WEAPON_CONFIG_TYPE_MI28N_HAVOC_B_14
		//
		////////////////////////////////////////
		{
			// WEAPON PACKAGE 1
			{
				ENTITY_SUB_TYPE_WEAPON_CHAFF,								// sub_type
				NUM_CHAFFS,														// number
				CHAFF_DISPENSER,												// heading_depth
				CHAFF_VECTOR,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 2
			{
				ENTITY_SUB_TYPE_WEAPON_FLARE,								// sub_type
				NUM_FLARES,														// number
				FLARE_DISPENSER,												// heading_depth
				FLARE_VECTOR,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 3
			{
				ENTITY_SUB_TYPE_WEAPON_2A42_30MM_HE_ROUND,			// sub_type
				NUM_HE_CANNON_ROUNDS,										// number
				CANNON_TURRET,													// heading_depth
				CANNON_BARREL,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				CANNON_TURRET_HEADING_RATE,								// heading_rate
				CANNON_TURRET_MIN_HEADING_LIMIT,							// min_heading_limit
				CANNON_TURRET_MAX_HEADING_LIMIT,							// max_heading_limit
				CANNON_BARREL_PITCH_RATE,									// pitch_rate
				CANNON_BARREL_MIN_PITCH_LIMIT,							// min_pitch_limit
				CANNON_BARREL_MAX_PITCH_LIMIT,							// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE3 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE4,
				SHARE_WEAPON_PACKAGE3 +										// pitch_share_mask
				SHARE_WEAPON_PACKAGE4,
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 4
			{
				ENTITY_SUB_TYPE_WEAPON_2A42_30MM_AP_ROUND,			// sub_type
				NUM_AP_CANNON_ROUNDS,										// number
				CANNON_TURRET,													// heading_depth
				CANNON_BARREL,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				CANNON_TURRET_HEADING_RATE,								// heading_rate
				CANNON_TURRET_MIN_HEADING_LIMIT,							// min_heading_limit
				CANNON_TURRET_MAX_HEADING_LIMIT,							// max_heading_limit
				CANNON_BARREL_PITCH_RATE,									// pitch_rate
				CANNON_BARREL_MIN_PITCH_LIMIT,							// min_pitch_limit
				CANNON_BARREL_MAX_PITCH_LIMIT,							// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE3 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE4,
				SHARE_WEAPON_PACKAGE3 +										// pitch_share_mask
				SHARE_WEAPON_PACKAGE4,
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 5
			{
				ENTITY_SUB_TYPE_WEAPON_S13,								// sub_type
				NUM_S13_ROCKETS,												// number
				LHS_HARDPOINT1,												// heading_depth
				B13_POD,															// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				2,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 6
			{
				ENTITY_SUB_TYPE_WEAPON_S13,								// sub_type
				NUM_S13_ROCKETS,												// number
				RHS_HARDPOINT1,												// heading_depth
				B13_POD,															// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				2,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 7
			{
				ENTITY_SUB_TYPE_WEAPON_IGLA_V,							// sub_type
				NUM_IGLA_MISSILES,											// number
				LHS_HARDPOINT2,												// heading_depth
				IGLA_PYLON,														// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 8
			{
				ENTITY_SUB_TYPE_WEAPON_IGLA_V,							// sub_type
				NUM_IGLA_MISSILES,											// number
				RHS_HARDPOINT2,												// heading_depth
				IGLA_PYLON,														// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
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
		////////////////////////////////////////
		//
		// WEAPON_CONFIG_TYPE_MI28N_HAVOC_B_15
		//
		////////////////////////////////////////
		{
			// WEAPON PACKAGE 1
			{
				ENTITY_SUB_TYPE_WEAPON_CHAFF,								// sub_type
				NUM_CHAFFS,														// number
				CHAFF_DISPENSER,												// heading_depth
				CHAFF_VECTOR,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 2
			{
				ENTITY_SUB_TYPE_WEAPON_FLARE,								// sub_type
				NUM_FLARES,														// number
				FLARE_DISPENSER,												// heading_depth
				FLARE_VECTOR,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 3
			{
				ENTITY_SUB_TYPE_WEAPON_2A42_30MM_HE_ROUND,			// sub_type
				NUM_HE_CANNON_ROUNDS,										// number
				CANNON_TURRET,													// heading_depth
				CANNON_BARREL,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				CANNON_TURRET_HEADING_RATE,								// heading_rate
				CANNON_TURRET_MIN_HEADING_LIMIT,							// min_heading_limit
				CANNON_TURRET_MAX_HEADING_LIMIT,							// max_heading_limit
				CANNON_BARREL_PITCH_RATE,									// pitch_rate
				CANNON_BARREL_MIN_PITCH_LIMIT,							// min_pitch_limit
				CANNON_BARREL_MAX_PITCH_LIMIT,							// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE3 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE4,
				SHARE_WEAPON_PACKAGE3 +										// pitch_share_mask
				SHARE_WEAPON_PACKAGE4,
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 4
			{
				ENTITY_SUB_TYPE_WEAPON_2A42_30MM_AP_ROUND,			// sub_type
				NUM_AP_CANNON_ROUNDS,										// number
				CANNON_TURRET,													// heading_depth
				CANNON_BARREL,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				CANNON_TURRET_HEADING_RATE,								// heading_rate
				CANNON_TURRET_MIN_HEADING_LIMIT,							// min_heading_limit
				CANNON_TURRET_MAX_HEADING_LIMIT,							// max_heading_limit
				CANNON_BARREL_PITCH_RATE,									// pitch_rate
				CANNON_BARREL_MIN_PITCH_LIMIT,							// min_pitch_limit
				CANNON_BARREL_MAX_PITCH_LIMIT,							// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE3 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE4,
				SHARE_WEAPON_PACKAGE3 +										// pitch_share_mask
				SHARE_WEAPON_PACKAGE4,
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 5
			{
				ENTITY_SUB_TYPE_WEAPON_GSH23L_23MM_ROUND,				// sub_type
				NUM_CANNON_POD_ROUNDS,										// number
				LHS_HARDPOINT1,												// heading_depth
				CANNON_POD,														// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				2,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 6
			{
				ENTITY_SUB_TYPE_WEAPON_GSH23L_23MM_ROUND,				// sub_type
				NUM_CANNON_POD_ROUNDS,										// number
				RHS_HARDPOINT1,												// heading_depth
				CANNON_POD,														// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				2,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 7
			{
				ENTITY_SUB_TYPE_WEAPON_IGLA_V,							// sub_type
				NUM_IGLA_MISSILES,											// number
				LHS_HARDPOINT2,												// heading_depth
				IGLA_PYLON,														// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 8
			{
				ENTITY_SUB_TYPE_WEAPON_IGLA_V,							// sub_type
				NUM_IGLA_MISSILES,											// number
				RHS_HARDPOINT2,												// heading_depth
				IGLA_PYLON,														// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
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
		////////////////////////////////////////
		//
		// WEAPON_CONFIG_TYPE_MI28N_HAVOC_B_16
		//
		////////////////////////////////////////
		{
			// WEAPON PACKAGE 1
			{
				ENTITY_SUB_TYPE_WEAPON_CHAFF,								// sub_type
				NUM_CHAFFS,														// number
				CHAFF_DISPENSER,												// heading_depth
				CHAFF_VECTOR,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 2
			{
				ENTITY_SUB_TYPE_WEAPON_FLARE,								// sub_type
				NUM_FLARES,														// number
				FLARE_DISPENSER,												// heading_depth
				FLARE_VECTOR,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 3
			{
				ENTITY_SUB_TYPE_WEAPON_2A42_30MM_HE_ROUND,			// sub_type
				NUM_HE_CANNON_ROUNDS,										// number
				CANNON_TURRET,													// heading_depth
				CANNON_BARREL,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				CANNON_TURRET_HEADING_RATE,								// heading_rate
				CANNON_TURRET_MIN_HEADING_LIMIT,							// min_heading_limit
				CANNON_TURRET_MAX_HEADING_LIMIT,							// max_heading_limit
				CANNON_BARREL_PITCH_RATE,									// pitch_rate
				CANNON_BARREL_MIN_PITCH_LIMIT,							// min_pitch_limit
				CANNON_BARREL_MAX_PITCH_LIMIT,							// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE3 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE4,
				SHARE_WEAPON_PACKAGE3 +										// pitch_share_mask
				SHARE_WEAPON_PACKAGE4,
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 4
			{
				ENTITY_SUB_TYPE_WEAPON_2A42_30MM_AP_ROUND,			// sub_type
				NUM_AP_CANNON_ROUNDS,										// number
				CANNON_TURRET,													// heading_depth
				CANNON_BARREL,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				CANNON_TURRET_HEADING_RATE,								// heading_rate
				CANNON_TURRET_MIN_HEADING_LIMIT,							// min_heading_limit
				CANNON_TURRET_MAX_HEADING_LIMIT,							// max_heading_limit
				CANNON_BARREL_PITCH_RATE,									// pitch_rate
				CANNON_BARREL_MIN_PITCH_LIMIT,							// min_pitch_limit
				CANNON_BARREL_MAX_PITCH_LIMIT,							// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE3 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE4,
				SHARE_WEAPON_PACKAGE3 +										// pitch_share_mask
				SHARE_WEAPON_PACKAGE4,
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 5
			{
				ENTITY_SUB_TYPE_WEAPON_S8,									// sub_type
				NUM_S8_ROCKETS,												// number
				LHS_HARDPOINT2,												// heading_depth
				B8_POD,															// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				2,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 6
			{
				ENTITY_SUB_TYPE_WEAPON_S8,									// sub_type
				NUM_S8_ROCKETS,												// number
				RHS_HARDPOINT2,												// heading_depth
				B8_POD,															// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				2,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
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
		////////////////////////////////////////
		//
		// WEAPON_CONFIG_TYPE_MI28N_HAVOC_B_17
		//
		////////////////////////////////////////
		{
			// WEAPON PACKAGE 1
			{
				ENTITY_SUB_TYPE_WEAPON_CHAFF,								// sub_type
				NUM_CHAFFS,														// number
				CHAFF_DISPENSER,												// heading_depth
				CHAFF_VECTOR,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 2
			{
				ENTITY_SUB_TYPE_WEAPON_FLARE,								// sub_type
				NUM_FLARES,														// number
				FLARE_DISPENSER,												// heading_depth
				FLARE_VECTOR,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 3
			{
				ENTITY_SUB_TYPE_WEAPON_2A42_30MM_HE_ROUND,			// sub_type
				NUM_HE_CANNON_ROUNDS,										// number
				CANNON_TURRET,													// heading_depth
				CANNON_BARREL,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				CANNON_TURRET_HEADING_RATE,								// heading_rate
				CANNON_TURRET_MIN_HEADING_LIMIT,							// min_heading_limit
				CANNON_TURRET_MAX_HEADING_LIMIT,							// max_heading_limit
				CANNON_BARREL_PITCH_RATE,									// pitch_rate
				CANNON_BARREL_MIN_PITCH_LIMIT,							// min_pitch_limit
				CANNON_BARREL_MAX_PITCH_LIMIT,							// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE3 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE4,
				SHARE_WEAPON_PACKAGE3 +										// pitch_share_mask
				SHARE_WEAPON_PACKAGE4,
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 4
			{
				ENTITY_SUB_TYPE_WEAPON_2A42_30MM_AP_ROUND,			// sub_type
				NUM_AP_CANNON_ROUNDS,										// number
				CANNON_TURRET,													// heading_depth
				CANNON_BARREL,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				CANNON_TURRET_HEADING_RATE,								// heading_rate
				CANNON_TURRET_MIN_HEADING_LIMIT,							// min_heading_limit
				CANNON_TURRET_MAX_HEADING_LIMIT,							// max_heading_limit
				CANNON_BARREL_PITCH_RATE,									// pitch_rate
				CANNON_BARREL_MIN_PITCH_LIMIT,							// min_pitch_limit
				CANNON_BARREL_MAX_PITCH_LIMIT,							// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE3 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE4,
				SHARE_WEAPON_PACKAGE3 +										// pitch_share_mask
				SHARE_WEAPON_PACKAGE4,
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 5
			{
				ENTITY_SUB_TYPE_WEAPON_IGLA_V,							// sub_type
				NUM_IGLA_MISSILES,											// number
				LHS_HARDPOINT1,												// heading_depth
				IGLA_PYLON,														// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 6
			{
				ENTITY_SUB_TYPE_WEAPON_IGLA_V,							// sub_type
				NUM_IGLA_MISSILES,											// number
				RHS_HARDPOINT1,												// heading_depth
				IGLA_PYLON,														// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 7
			{
				ENTITY_SUB_TYPE_WEAPON_S8,									// sub_type
				NUM_S8_ROCKETS,												// number
				LHS_HARDPOINT2,												// heading_depth
				B8_POD,															// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				2,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 8
			{
				ENTITY_SUB_TYPE_WEAPON_S8,									// sub_type
				NUM_S8_ROCKETS,												// number
				RHS_HARDPOINT2,												// heading_depth
				B8_POD,															// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				2,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
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
		////////////////////////////////////////
		//
		// WEAPON_CONFIG_TYPE_MI28N_HAVOC_B_18
		//
		////////////////////////////////////////
		{
			// WEAPON PACKAGE 1
			{
				ENTITY_SUB_TYPE_WEAPON_CHAFF,								// sub_type
				NUM_CHAFFS,														// number
				CHAFF_DISPENSER,												// heading_depth
				CHAFF_VECTOR,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 2
			{
				ENTITY_SUB_TYPE_WEAPON_FLARE,								// sub_type
				NUM_FLARES,														// number
				FLARE_DISPENSER,												// heading_depth
				FLARE_VECTOR,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 3
			{
				ENTITY_SUB_TYPE_WEAPON_2A42_30MM_HE_ROUND,			// sub_type
				NUM_HE_CANNON_ROUNDS,										// number
				CANNON_TURRET,													// heading_depth
				CANNON_BARREL,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				CANNON_TURRET_HEADING_RATE,								// heading_rate
				CANNON_TURRET_MIN_HEADING_LIMIT,							// min_heading_limit
				CANNON_TURRET_MAX_HEADING_LIMIT,							// max_heading_limit
				CANNON_BARREL_PITCH_RATE,									// pitch_rate
				CANNON_BARREL_MIN_PITCH_LIMIT,							// min_pitch_limit
				CANNON_BARREL_MAX_PITCH_LIMIT,							// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE3 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE4,
				SHARE_WEAPON_PACKAGE3 +										// pitch_share_mask
				SHARE_WEAPON_PACKAGE4,
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 4
			{
				ENTITY_SUB_TYPE_WEAPON_2A42_30MM_AP_ROUND,			// sub_type
				NUM_AP_CANNON_ROUNDS,										// number
				CANNON_TURRET,													// heading_depth
				CANNON_BARREL,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				CANNON_TURRET_HEADING_RATE,								// heading_rate
				CANNON_TURRET_MIN_HEADING_LIMIT,							// min_heading_limit
				CANNON_TURRET_MAX_HEADING_LIMIT,							// max_heading_limit
				CANNON_BARREL_PITCH_RATE,									// pitch_rate
				CANNON_BARREL_MIN_PITCH_LIMIT,							// min_pitch_limit
				CANNON_BARREL_MAX_PITCH_LIMIT,							// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE3 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE4,
				SHARE_WEAPON_PACKAGE3 +										// pitch_share_mask
				SHARE_WEAPON_PACKAGE4,
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 5
			{
				ENTITY_SUB_TYPE_WEAPON_S8,									// sub_type
				NUM_S8_ROCKETS,												// number
				LHS_HARDPOINT1,												// heading_depth
				B8_POD,															// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				2,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 6
			{
				ENTITY_SUB_TYPE_WEAPON_S8,									// sub_type
				NUM_S8_ROCKETS,												// number
				RHS_HARDPOINT1,												// heading_depth
				B8_POD,															// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				2,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 7
			{
				ENTITY_SUB_TYPE_WEAPON_S8,									// sub_type
				NUM_S8_ROCKETS,												// number
				LHS_HARDPOINT2,												// heading_depth
				B8_POD,															// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				2,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 8
			{
				ENTITY_SUB_TYPE_WEAPON_S8,									// sub_type
				NUM_S8_ROCKETS,												// number
				RHS_HARDPOINT2,												// heading_depth
				B8_POD,															// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				2,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
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
		////////////////////////////////////////
		//
		// WEAPON_CONFIG_TYPE_MI28N_HAVOC_B_19
		//
		////////////////////////////////////////
		{
			// WEAPON PACKAGE 1
			{
				ENTITY_SUB_TYPE_WEAPON_CHAFF,								// sub_type
				NUM_CHAFFS,														// number
				CHAFF_DISPENSER,												// heading_depth
				CHAFF_VECTOR,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 2
			{
				ENTITY_SUB_TYPE_WEAPON_FLARE,								// sub_type
				NUM_FLARES,														// number
				FLARE_DISPENSER,												// heading_depth
				FLARE_VECTOR,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 3
			{
				ENTITY_SUB_TYPE_WEAPON_2A42_30MM_HE_ROUND,			// sub_type
				NUM_HE_CANNON_ROUNDS,										// number
				CANNON_TURRET,													// heading_depth
				CANNON_BARREL,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				CANNON_TURRET_HEADING_RATE,								// heading_rate
				CANNON_TURRET_MIN_HEADING_LIMIT,							// min_heading_limit
				CANNON_TURRET_MAX_HEADING_LIMIT,							// max_heading_limit
				CANNON_BARREL_PITCH_RATE,									// pitch_rate
				CANNON_BARREL_MIN_PITCH_LIMIT,							// min_pitch_limit
				CANNON_BARREL_MAX_PITCH_LIMIT,							// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE3 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE4,
				SHARE_WEAPON_PACKAGE3 +										// pitch_share_mask
				SHARE_WEAPON_PACKAGE4,
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 4
			{
				ENTITY_SUB_TYPE_WEAPON_2A42_30MM_AP_ROUND,			// sub_type
				NUM_AP_CANNON_ROUNDS,										// number
				CANNON_TURRET,													// heading_depth
				CANNON_BARREL,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				CANNON_TURRET_HEADING_RATE,								// heading_rate
				CANNON_TURRET_MIN_HEADING_LIMIT,							// min_heading_limit
				CANNON_TURRET_MAX_HEADING_LIMIT,							// max_heading_limit
				CANNON_BARREL_PITCH_RATE,									// pitch_rate
				CANNON_BARREL_MIN_PITCH_LIMIT,							// min_pitch_limit
				CANNON_BARREL_MAX_PITCH_LIMIT,							// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE3 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE4,
				SHARE_WEAPON_PACKAGE3 +										// pitch_share_mask
				SHARE_WEAPON_PACKAGE4,
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 5
			{
				ENTITY_SUB_TYPE_WEAPON_S13,								// sub_type
				NUM_S13_ROCKETS,												// number
				LHS_HARDPOINT1,												// heading_depth
				B13_POD,															// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				2,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 6
			{
				ENTITY_SUB_TYPE_WEAPON_S13,								// sub_type
				NUM_S13_ROCKETS,												// number
				RHS_HARDPOINT1,												// heading_depth
				B13_POD,															// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				2,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 7
			{
				ENTITY_SUB_TYPE_WEAPON_S8,									// sub_type
				NUM_S8_ROCKETS,												// number
				LHS_HARDPOINT2,												// heading_depth
				B8_POD,															// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				2,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 8
			{
				ENTITY_SUB_TYPE_WEAPON_S8,									// sub_type
				NUM_S8_ROCKETS,												// number
				RHS_HARDPOINT2,												// heading_depth
				B8_POD,															// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				2,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
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
		////////////////////////////////////////
		//
		// WEAPON_CONFIG_TYPE_MI28N_HAVOC_B_20
		//
		////////////////////////////////////////
		{
			// WEAPON PACKAGE 1
			{
				ENTITY_SUB_TYPE_WEAPON_CHAFF,								// sub_type
				NUM_CHAFFS,														// number
				CHAFF_DISPENSER,												// heading_depth
				CHAFF_VECTOR,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 2
			{
				ENTITY_SUB_TYPE_WEAPON_FLARE,								// sub_type
				NUM_FLARES,														// number
				FLARE_DISPENSER,												// heading_depth
				FLARE_VECTOR,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 3
			{
				ENTITY_SUB_TYPE_WEAPON_2A42_30MM_HE_ROUND,			// sub_type
				NUM_HE_CANNON_ROUNDS,										// number
				CANNON_TURRET,													// heading_depth
				CANNON_BARREL,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				CANNON_TURRET_HEADING_RATE,								// heading_rate
				CANNON_TURRET_MIN_HEADING_LIMIT,							// min_heading_limit
				CANNON_TURRET_MAX_HEADING_LIMIT,							// max_heading_limit
				CANNON_BARREL_PITCH_RATE,									// pitch_rate
				CANNON_BARREL_MIN_PITCH_LIMIT,							// min_pitch_limit
				CANNON_BARREL_MAX_PITCH_LIMIT,							// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE3 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE4,
				SHARE_WEAPON_PACKAGE3 +										// pitch_share_mask
				SHARE_WEAPON_PACKAGE4,
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 4
			{
				ENTITY_SUB_TYPE_WEAPON_2A42_30MM_AP_ROUND,			// sub_type
				NUM_AP_CANNON_ROUNDS,										// number
				CANNON_TURRET,													// heading_depth
				CANNON_BARREL,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				CANNON_TURRET_HEADING_RATE,								// heading_rate
				CANNON_TURRET_MIN_HEADING_LIMIT,							// min_heading_limit
				CANNON_TURRET_MAX_HEADING_LIMIT,							// max_heading_limit
				CANNON_BARREL_PITCH_RATE,									// pitch_rate
				CANNON_BARREL_MIN_PITCH_LIMIT,							// min_pitch_limit
				CANNON_BARREL_MAX_PITCH_LIMIT,							// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE3 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE4,
				SHARE_WEAPON_PACKAGE3 +										// pitch_share_mask
				SHARE_WEAPON_PACKAGE4,
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 5
			{
				ENTITY_SUB_TYPE_WEAPON_GSH23L_23MM_ROUND,				// sub_type
				NUM_CANNON_POD_ROUNDS,										// number
				LHS_HARDPOINT1,												// heading_depth
				CANNON_POD,														// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				2,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 6
			{
				ENTITY_SUB_TYPE_WEAPON_GSH23L_23MM_ROUND,				// sub_type
				NUM_CANNON_POD_ROUNDS,										// number
				RHS_HARDPOINT1,												// heading_depth
				CANNON_POD,														// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				2,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 7
			{
				ENTITY_SUB_TYPE_WEAPON_S8,									// sub_type
				NUM_S8_ROCKETS,												// number
				LHS_HARDPOINT2,												// heading_depth
				B8_POD,															// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				2,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 8
			{
				ENTITY_SUB_TYPE_WEAPON_S8,									// sub_type
				NUM_S8_ROCKETS,												// number
				RHS_HARDPOINT2,												// heading_depth
				B8_POD,															// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				2,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
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
		////////////////////////////////////////
		//
		// WEAPON_CONFIG_TYPE_MI28N_HAVOC_B_21
		//
		////////////////////////////////////////
		{
			// WEAPON PACKAGE 1
			{
				ENTITY_SUB_TYPE_WEAPON_CHAFF,								// sub_type
				NUM_CHAFFS,														// number
				CHAFF_DISPENSER,												// heading_depth
				CHAFF_VECTOR,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 2
			{
				ENTITY_SUB_TYPE_WEAPON_FLARE,								// sub_type
				NUM_FLARES,														// number
				FLARE_DISPENSER,												// heading_depth
				FLARE_VECTOR,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 3
			{
				ENTITY_SUB_TYPE_WEAPON_2A42_30MM_HE_ROUND,			// sub_type
				NUM_HE_CANNON_ROUNDS,										// number
				CANNON_TURRET,													// heading_depth
				CANNON_BARREL,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				CANNON_TURRET_HEADING_RATE,								// heading_rate
				CANNON_TURRET_MIN_HEADING_LIMIT,							// min_heading_limit
				CANNON_TURRET_MAX_HEADING_LIMIT,							// max_heading_limit
				CANNON_BARREL_PITCH_RATE,									// pitch_rate
				CANNON_BARREL_MIN_PITCH_LIMIT,							// min_pitch_limit
				CANNON_BARREL_MAX_PITCH_LIMIT,							// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE3 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE4,
				SHARE_WEAPON_PACKAGE3 +										// pitch_share_mask
				SHARE_WEAPON_PACKAGE4,
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 4
			{
				ENTITY_SUB_TYPE_WEAPON_2A42_30MM_AP_ROUND,			// sub_type
				NUM_AP_CANNON_ROUNDS,										// number
				CANNON_TURRET,													// heading_depth
				CANNON_BARREL,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				CANNON_TURRET_HEADING_RATE,								// heading_rate
				CANNON_TURRET_MIN_HEADING_LIMIT,							// min_heading_limit
				CANNON_TURRET_MAX_HEADING_LIMIT,							// max_heading_limit
				CANNON_BARREL_PITCH_RATE,									// pitch_rate
				CANNON_BARREL_MIN_PITCH_LIMIT,							// min_pitch_limit
				CANNON_BARREL_MAX_PITCH_LIMIT,							// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE3 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE4,
				SHARE_WEAPON_PACKAGE3 +										// pitch_share_mask
				SHARE_WEAPON_PACKAGE4,
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 5
			{
				ENTITY_SUB_TYPE_WEAPON_S13,								// sub_type
				NUM_S13_ROCKETS,												// number
				LHS_HARDPOINT2,												// heading_depth
				B13_POD,															// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				2,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 6
			{
				ENTITY_SUB_TYPE_WEAPON_S13,								// sub_type
				NUM_S13_ROCKETS,												// number
				RHS_HARDPOINT2,												// heading_depth
				B13_POD,															// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				2,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
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
		////////////////////////////////////////
		//
		// WEAPON_CONFIG_TYPE_MI28N_HAVOC_B_22
		//
		////////////////////////////////////////
		{
			// WEAPON PACKAGE 1
			{
				ENTITY_SUB_TYPE_WEAPON_CHAFF,								// sub_type
				NUM_CHAFFS,														// number
				CHAFF_DISPENSER,												// heading_depth
				CHAFF_VECTOR,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 2
			{
				ENTITY_SUB_TYPE_WEAPON_FLARE,								// sub_type
				NUM_FLARES,														// number
				FLARE_DISPENSER,												// heading_depth
				FLARE_VECTOR,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 3
			{
				ENTITY_SUB_TYPE_WEAPON_2A42_30MM_HE_ROUND,			// sub_type
				NUM_HE_CANNON_ROUNDS,										// number
				CANNON_TURRET,													// heading_depth
				CANNON_BARREL,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				CANNON_TURRET_HEADING_RATE,								// heading_rate
				CANNON_TURRET_MIN_HEADING_LIMIT,							// min_heading_limit
				CANNON_TURRET_MAX_HEADING_LIMIT,							// max_heading_limit
				CANNON_BARREL_PITCH_RATE,									// pitch_rate
				CANNON_BARREL_MIN_PITCH_LIMIT,							// min_pitch_limit
				CANNON_BARREL_MAX_PITCH_LIMIT,							// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE3 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE4,
				SHARE_WEAPON_PACKAGE3 +										// pitch_share_mask
				SHARE_WEAPON_PACKAGE4,
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 4
			{
				ENTITY_SUB_TYPE_WEAPON_2A42_30MM_AP_ROUND,			// sub_type
				NUM_AP_CANNON_ROUNDS,										// number
				CANNON_TURRET,													// heading_depth
				CANNON_BARREL,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				CANNON_TURRET_HEADING_RATE,								// heading_rate
				CANNON_TURRET_MIN_HEADING_LIMIT,							// min_heading_limit
				CANNON_TURRET_MAX_HEADING_LIMIT,							// max_heading_limit
				CANNON_BARREL_PITCH_RATE,									// pitch_rate
				CANNON_BARREL_MIN_PITCH_LIMIT,							// min_pitch_limit
				CANNON_BARREL_MAX_PITCH_LIMIT,							// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE3 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE4,
				SHARE_WEAPON_PACKAGE3 +										// pitch_share_mask
				SHARE_WEAPON_PACKAGE4,
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 5
			{
				ENTITY_SUB_TYPE_WEAPON_IGLA_V,							// sub_type
				NUM_IGLA_MISSILES,											// number
				LHS_HARDPOINT1,												// heading_depth
				IGLA_PYLON,														// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 6
			{
				ENTITY_SUB_TYPE_WEAPON_IGLA_V,							// sub_type
				NUM_IGLA_MISSILES,											// number
				RHS_HARDPOINT1,												// heading_depth
				IGLA_PYLON,														// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 7
			{
				ENTITY_SUB_TYPE_WEAPON_S13,								// sub_type
				NUM_S13_ROCKETS,												// number
				LHS_HARDPOINT2,												// heading_depth
				B13_POD,															// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				2,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 8
			{
				ENTITY_SUB_TYPE_WEAPON_S13,								// sub_type
				NUM_S13_ROCKETS,												// number
				RHS_HARDPOINT2,												// heading_depth
				B13_POD,															// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				2,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
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
		////////////////////////////////////////
		//
		// WEAPON_CONFIG_TYPE_MI28N_HAVOC_B_23
		//
		////////////////////////////////////////
		{
			// WEAPON PACKAGE 1
			{
				ENTITY_SUB_TYPE_WEAPON_CHAFF,								// sub_type
				NUM_CHAFFS,														// number
				CHAFF_DISPENSER,												// heading_depth
				CHAFF_VECTOR,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 2
			{
				ENTITY_SUB_TYPE_WEAPON_FLARE,								// sub_type
				NUM_FLARES,														// number
				FLARE_DISPENSER,												// heading_depth
				FLARE_VECTOR,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 3
			{
				ENTITY_SUB_TYPE_WEAPON_2A42_30MM_HE_ROUND,			// sub_type
				NUM_HE_CANNON_ROUNDS,										// number
				CANNON_TURRET,													// heading_depth
				CANNON_BARREL,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				CANNON_TURRET_HEADING_RATE,								// heading_rate
				CANNON_TURRET_MIN_HEADING_LIMIT,							// min_heading_limit
				CANNON_TURRET_MAX_HEADING_LIMIT,							// max_heading_limit
				CANNON_BARREL_PITCH_RATE,									// pitch_rate
				CANNON_BARREL_MIN_PITCH_LIMIT,							// min_pitch_limit
				CANNON_BARREL_MAX_PITCH_LIMIT,							// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE3 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE4,
				SHARE_WEAPON_PACKAGE3 +										// pitch_share_mask
				SHARE_WEAPON_PACKAGE4,
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 4
			{
				ENTITY_SUB_TYPE_WEAPON_2A42_30MM_AP_ROUND,			// sub_type
				NUM_AP_CANNON_ROUNDS,										// number
				CANNON_TURRET,													// heading_depth
				CANNON_BARREL,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				CANNON_TURRET_HEADING_RATE,								// heading_rate
				CANNON_TURRET_MIN_HEADING_LIMIT,							// min_heading_limit
				CANNON_TURRET_MAX_HEADING_LIMIT,							// max_heading_limit
				CANNON_BARREL_PITCH_RATE,									// pitch_rate
				CANNON_BARREL_MIN_PITCH_LIMIT,							// min_pitch_limit
				CANNON_BARREL_MAX_PITCH_LIMIT,							// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE3 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE4,
				SHARE_WEAPON_PACKAGE3 +										// pitch_share_mask
				SHARE_WEAPON_PACKAGE4,
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 5
			{
				ENTITY_SUB_TYPE_WEAPON_S8,									// sub_type
				NUM_S8_ROCKETS,												// number
				LHS_HARDPOINT1,												// heading_depth
				B8_POD,															// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				2,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 6
			{
				ENTITY_SUB_TYPE_WEAPON_S8,									// sub_type
				NUM_S8_ROCKETS,												// number
				RHS_HARDPOINT1,												// heading_depth
				B8_POD,															// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				2,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 7
			{
				ENTITY_SUB_TYPE_WEAPON_S13,								// sub_type
				NUM_S13_ROCKETS,												// number
				LHS_HARDPOINT2,												// heading_depth
				B13_POD,															// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				2,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 8
			{
				ENTITY_SUB_TYPE_WEAPON_S13,								// sub_type
				NUM_S13_ROCKETS,												// number
				RHS_HARDPOINT2,												// heading_depth
				B13_POD,															// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				2,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
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
		////////////////////////////////////////
		//
		// WEAPON_CONFIG_TYPE_MI28N_HAVOC_B_24
		//
		////////////////////////////////////////
		{
			// WEAPON PACKAGE 1
			{
				ENTITY_SUB_TYPE_WEAPON_CHAFF,								// sub_type
				NUM_CHAFFS,														// number
				CHAFF_DISPENSER,												// heading_depth
				CHAFF_VECTOR,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 2
			{
				ENTITY_SUB_TYPE_WEAPON_FLARE,								// sub_type
				NUM_FLARES,														// number
				FLARE_DISPENSER,												// heading_depth
				FLARE_VECTOR,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 3
			{
				ENTITY_SUB_TYPE_WEAPON_2A42_30MM_HE_ROUND,			// sub_type
				NUM_HE_CANNON_ROUNDS,										// number
				CANNON_TURRET,													// heading_depth
				CANNON_BARREL,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				CANNON_TURRET_HEADING_RATE,								// heading_rate
				CANNON_TURRET_MIN_HEADING_LIMIT,							// min_heading_limit
				CANNON_TURRET_MAX_HEADING_LIMIT,							// max_heading_limit
				CANNON_BARREL_PITCH_RATE,									// pitch_rate
				CANNON_BARREL_MIN_PITCH_LIMIT,							// min_pitch_limit
				CANNON_BARREL_MAX_PITCH_LIMIT,							// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE3 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE4,
				SHARE_WEAPON_PACKAGE3 +										// pitch_share_mask
				SHARE_WEAPON_PACKAGE4,
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 4
			{
				ENTITY_SUB_TYPE_WEAPON_2A42_30MM_AP_ROUND,			// sub_type
				NUM_AP_CANNON_ROUNDS,										// number
				CANNON_TURRET,													// heading_depth
				CANNON_BARREL,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				CANNON_TURRET_HEADING_RATE,								// heading_rate
				CANNON_TURRET_MIN_HEADING_LIMIT,							// min_heading_limit
				CANNON_TURRET_MAX_HEADING_LIMIT,							// max_heading_limit
				CANNON_BARREL_PITCH_RATE,									// pitch_rate
				CANNON_BARREL_MIN_PITCH_LIMIT,							// min_pitch_limit
				CANNON_BARREL_MAX_PITCH_LIMIT,							// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE3 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE4,
				SHARE_WEAPON_PACKAGE3 +										// pitch_share_mask
				SHARE_WEAPON_PACKAGE4,
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 5
			{
				ENTITY_SUB_TYPE_WEAPON_S13,								// sub_type
				NUM_S13_ROCKETS,												// number
				LHS_HARDPOINT1,												// heading_depth
				B13_POD,															// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				2,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 6
			{
				ENTITY_SUB_TYPE_WEAPON_S13,								// sub_type
				NUM_S13_ROCKETS,												// number
				RHS_HARDPOINT1,												// heading_depth
				B13_POD,															// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				2,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 7
			{
				ENTITY_SUB_TYPE_WEAPON_S13,								// sub_type
				NUM_S13_ROCKETS,												// number
				LHS_HARDPOINT2,												// heading_depth
				B13_POD,															// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				2,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 8
			{
				ENTITY_SUB_TYPE_WEAPON_S13,								// sub_type
				NUM_S13_ROCKETS,												// number
				RHS_HARDPOINT2,												// heading_depth
				B13_POD,															// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				2,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
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
		////////////////////////////////////////
		//
		// WEAPON_CONFIG_TYPE_MI28N_HAVOC_B_25
		//
		////////////////////////////////////////
		{
			// WEAPON PACKAGE 1
			{
				ENTITY_SUB_TYPE_WEAPON_CHAFF,								// sub_type
				NUM_CHAFFS,														// number
				CHAFF_DISPENSER,												// heading_depth
				CHAFF_VECTOR,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 2
			{
				ENTITY_SUB_TYPE_WEAPON_FLARE,								// sub_type
				NUM_FLARES,														// number
				FLARE_DISPENSER,												// heading_depth
				FLARE_VECTOR,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 3
			{
				ENTITY_SUB_TYPE_WEAPON_2A42_30MM_HE_ROUND,			// sub_type
				NUM_HE_CANNON_ROUNDS,										// number
				CANNON_TURRET,													// heading_depth
				CANNON_BARREL,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				CANNON_TURRET_HEADING_RATE,								// heading_rate
				CANNON_TURRET_MIN_HEADING_LIMIT,							// min_heading_limit
				CANNON_TURRET_MAX_HEADING_LIMIT,							// max_heading_limit
				CANNON_BARREL_PITCH_RATE,									// pitch_rate
				CANNON_BARREL_MIN_PITCH_LIMIT,							// min_pitch_limit
				CANNON_BARREL_MAX_PITCH_LIMIT,							// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE3 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE4,
				SHARE_WEAPON_PACKAGE3 +										// pitch_share_mask
				SHARE_WEAPON_PACKAGE4,
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 4
			{
				ENTITY_SUB_TYPE_WEAPON_2A42_30MM_AP_ROUND,			// sub_type
				NUM_AP_CANNON_ROUNDS,										// number
				CANNON_TURRET,													// heading_depth
				CANNON_BARREL,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				CANNON_TURRET_HEADING_RATE,								// heading_rate
				CANNON_TURRET_MIN_HEADING_LIMIT,							// min_heading_limit
				CANNON_TURRET_MAX_HEADING_LIMIT,							// max_heading_limit
				CANNON_BARREL_PITCH_RATE,									// pitch_rate
				CANNON_BARREL_MIN_PITCH_LIMIT,							// min_pitch_limit
				CANNON_BARREL_MAX_PITCH_LIMIT,							// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE3 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE4,
				SHARE_WEAPON_PACKAGE3 +										// pitch_share_mask
				SHARE_WEAPON_PACKAGE4,
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 5
			{
				ENTITY_SUB_TYPE_WEAPON_GSH23L_23MM_ROUND,				// sub_type
				NUM_CANNON_POD_ROUNDS,										// number
				LHS_HARDPOINT1,												// heading_depth
				CANNON_POD,														// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				2,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 6
			{
				ENTITY_SUB_TYPE_WEAPON_GSH23L_23MM_ROUND,				// sub_type
				NUM_CANNON_POD_ROUNDS,										// number
				RHS_HARDPOINT1,												// heading_depth
				CANNON_POD,														// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				2,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 7
			{
				ENTITY_SUB_TYPE_WEAPON_S13,								// sub_type
				NUM_S13_ROCKETS,												// number
				LHS_HARDPOINT2,												// heading_depth
				B13_POD,															// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				2,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 8
			{
				ENTITY_SUB_TYPE_WEAPON_S13,								// sub_type
				NUM_S13_ROCKETS,												// number
				RHS_HARDPOINT2,												// heading_depth
				B13_POD,															// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				2,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
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
		////////////////////////////////////////
		//
		// WEAPON_CONFIG_TYPE_MI28N_HAVOC_B_26
		//
		////////////////////////////////////////
		{
			// WEAPON PACKAGE 1
			{
				ENTITY_SUB_TYPE_WEAPON_CHAFF,								// sub_type
				NUM_CHAFFS,														// number
				CHAFF_DISPENSER,												// heading_depth
				CHAFF_VECTOR,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 2
			{
				ENTITY_SUB_TYPE_WEAPON_FLARE,								// sub_type
				NUM_FLARES,														// number
				FLARE_DISPENSER,												// heading_depth
				FLARE_VECTOR,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 3
			{
				ENTITY_SUB_TYPE_WEAPON_2A42_30MM_HE_ROUND,			// sub_type
				NUM_HE_CANNON_ROUNDS,										// number
				CANNON_TURRET,													// heading_depth
				CANNON_BARREL,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				CANNON_TURRET_HEADING_RATE,								// heading_rate
				CANNON_TURRET_MIN_HEADING_LIMIT,							// min_heading_limit
				CANNON_TURRET_MAX_HEADING_LIMIT,							// max_heading_limit
				CANNON_BARREL_PITCH_RATE,									// pitch_rate
				CANNON_BARREL_MIN_PITCH_LIMIT,							// min_pitch_limit
				CANNON_BARREL_MAX_PITCH_LIMIT,							// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE3 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE4,
				SHARE_WEAPON_PACKAGE3 +										// pitch_share_mask
				SHARE_WEAPON_PACKAGE4,
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 4
			{
				ENTITY_SUB_TYPE_WEAPON_2A42_30MM_AP_ROUND,			// sub_type
				NUM_AP_CANNON_ROUNDS,										// number
				CANNON_TURRET,													// heading_depth
				CANNON_BARREL,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				CANNON_TURRET_HEADING_RATE,								// heading_rate
				CANNON_TURRET_MIN_HEADING_LIMIT,							// min_heading_limit
				CANNON_TURRET_MAX_HEADING_LIMIT,							// max_heading_limit
				CANNON_BARREL_PITCH_RATE,									// pitch_rate
				CANNON_BARREL_MIN_PITCH_LIMIT,							// min_pitch_limit
				CANNON_BARREL_MAX_PITCH_LIMIT,							// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE3 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE4,
				SHARE_WEAPON_PACKAGE3 +										// pitch_share_mask
				SHARE_WEAPON_PACKAGE4,
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 5
			{
				ENTITY_SUB_TYPE_WEAPON_GSH23L_23MM_ROUND,				// sub_type
				NUM_CANNON_POD_ROUNDS,										// number
				LHS_HARDPOINT2,												// heading_depth
				CANNON_POD,														// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				2,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 6
			{
				ENTITY_SUB_TYPE_WEAPON_GSH23L_23MM_ROUND,				// sub_type
				NUM_CANNON_POD_ROUNDS,										// number
				RHS_HARDPOINT2,												// heading_depth
				CANNON_POD,														// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				2,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
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
		////////////////////////////////////////
		//
		// WEAPON_CONFIG_TYPE_MI28N_HAVOC_B_27
		//
		////////////////////////////////////////
		{
			// WEAPON PACKAGE 1
			{
				ENTITY_SUB_TYPE_WEAPON_CHAFF,								// sub_type
				NUM_CHAFFS,														// number
				CHAFF_DISPENSER,												// heading_depth
				CHAFF_VECTOR,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 2
			{
				ENTITY_SUB_TYPE_WEAPON_FLARE,								// sub_type
				NUM_FLARES,														// number
				FLARE_DISPENSER,												// heading_depth
				FLARE_VECTOR,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 3
			{
				ENTITY_SUB_TYPE_WEAPON_2A42_30MM_HE_ROUND,			// sub_type
				NUM_HE_CANNON_ROUNDS,										// number
				CANNON_TURRET,													// heading_depth
				CANNON_BARREL,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				CANNON_TURRET_HEADING_RATE,								// heading_rate
				CANNON_TURRET_MIN_HEADING_LIMIT,							// min_heading_limit
				CANNON_TURRET_MAX_HEADING_LIMIT,							// max_heading_limit
				CANNON_BARREL_PITCH_RATE,									// pitch_rate
				CANNON_BARREL_MIN_PITCH_LIMIT,							// min_pitch_limit
				CANNON_BARREL_MAX_PITCH_LIMIT,							// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE3 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE4,
				SHARE_WEAPON_PACKAGE3 +										// pitch_share_mask
				SHARE_WEAPON_PACKAGE4,
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 4
			{
				ENTITY_SUB_TYPE_WEAPON_2A42_30MM_AP_ROUND,			// sub_type
				NUM_AP_CANNON_ROUNDS,										// number
				CANNON_TURRET,													// heading_depth
				CANNON_BARREL,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				CANNON_TURRET_HEADING_RATE,								// heading_rate
				CANNON_TURRET_MIN_HEADING_LIMIT,							// min_heading_limit
				CANNON_TURRET_MAX_HEADING_LIMIT,							// max_heading_limit
				CANNON_BARREL_PITCH_RATE,									// pitch_rate
				CANNON_BARREL_MIN_PITCH_LIMIT,							// min_pitch_limit
				CANNON_BARREL_MAX_PITCH_LIMIT,							// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE3 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE4,
				SHARE_WEAPON_PACKAGE3 +										// pitch_share_mask
				SHARE_WEAPON_PACKAGE4,
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 5
			{
				ENTITY_SUB_TYPE_WEAPON_IGLA_V,							// sub_type
				NUM_IGLA_MISSILES,											// number
				LHS_HARDPOINT1,												// heading_depth
				IGLA_PYLON,														// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 6
			{
				ENTITY_SUB_TYPE_WEAPON_IGLA_V,							// sub_type
				NUM_IGLA_MISSILES,											// number
				RHS_HARDPOINT1,												// heading_depth
				IGLA_PYLON,														// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 7
			{
				ENTITY_SUB_TYPE_WEAPON_GSH23L_23MM_ROUND,				// sub_type
				NUM_CANNON_POD_ROUNDS,										// number
				LHS_HARDPOINT2,												// heading_depth
				CANNON_POD,														// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				2,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 8
			{
				ENTITY_SUB_TYPE_WEAPON_GSH23L_23MM_ROUND,				// sub_type
				NUM_CANNON_POD_ROUNDS,										// number
				RHS_HARDPOINT2,												// heading_depth
				CANNON_POD,														// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				2,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
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
		////////////////////////////////////////
		//
		// WEAPON_CONFIG_TYPE_MI28N_HAVOC_B_28
		//
		////////////////////////////////////////
		{
			// WEAPON PACKAGE 1
			{
				ENTITY_SUB_TYPE_WEAPON_CHAFF,								// sub_type
				NUM_CHAFFS,														// number
				CHAFF_DISPENSER,												// heading_depth
				CHAFF_VECTOR,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 2
			{
				ENTITY_SUB_TYPE_WEAPON_FLARE,								// sub_type
				NUM_FLARES,														// number
				FLARE_DISPENSER,												// heading_depth
				FLARE_VECTOR,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 3
			{
				ENTITY_SUB_TYPE_WEAPON_2A42_30MM_HE_ROUND,			// sub_type
				NUM_HE_CANNON_ROUNDS,										// number
				CANNON_TURRET,													// heading_depth
				CANNON_BARREL,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				CANNON_TURRET_HEADING_RATE,								// heading_rate
				CANNON_TURRET_MIN_HEADING_LIMIT,							// min_heading_limit
				CANNON_TURRET_MAX_HEADING_LIMIT,							// max_heading_limit
				CANNON_BARREL_PITCH_RATE,									// pitch_rate
				CANNON_BARREL_MIN_PITCH_LIMIT,							// min_pitch_limit
				CANNON_BARREL_MAX_PITCH_LIMIT,							// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE3 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE4,
				SHARE_WEAPON_PACKAGE3 +										// pitch_share_mask
				SHARE_WEAPON_PACKAGE4,
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 4
			{
				ENTITY_SUB_TYPE_WEAPON_2A42_30MM_AP_ROUND,			// sub_type
				NUM_AP_CANNON_ROUNDS,										// number
				CANNON_TURRET,													// heading_depth
				CANNON_BARREL,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				CANNON_TURRET_HEADING_RATE,								// heading_rate
				CANNON_TURRET_MIN_HEADING_LIMIT,							// min_heading_limit
				CANNON_TURRET_MAX_HEADING_LIMIT,							// max_heading_limit
				CANNON_BARREL_PITCH_RATE,									// pitch_rate
				CANNON_BARREL_MIN_PITCH_LIMIT,							// min_pitch_limit
				CANNON_BARREL_MAX_PITCH_LIMIT,							// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE3 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE4,
				SHARE_WEAPON_PACKAGE3 +										// pitch_share_mask
				SHARE_WEAPON_PACKAGE4,
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 5
			{
				ENTITY_SUB_TYPE_WEAPON_S8,									// sub_type
				NUM_S8_ROCKETS,												// number
				LHS_HARDPOINT1,												// heading_depth
				B8_POD,															// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				2,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 6
			{
				ENTITY_SUB_TYPE_WEAPON_S8,									// sub_type
				NUM_S8_ROCKETS,												// number
				RHS_HARDPOINT1,												// heading_depth
				B8_POD,															// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				2,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 7
			{
				ENTITY_SUB_TYPE_WEAPON_GSH23L_23MM_ROUND,				// sub_type
				NUM_CANNON_POD_ROUNDS,										// number
				LHS_HARDPOINT2,												// heading_depth
				CANNON_POD,														// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				2,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 8
			{
				ENTITY_SUB_TYPE_WEAPON_GSH23L_23MM_ROUND,				// sub_type
				NUM_CANNON_POD_ROUNDS,										// number
				RHS_HARDPOINT2,												// heading_depth
				CANNON_POD,														// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				2,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
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
		////////////////////////////////////////
		//
		// WEAPON_CONFIG_TYPE_MI28N_HAVOC_B_29
		//
		////////////////////////////////////////
		{
			// WEAPON PACKAGE 1
			{
				ENTITY_SUB_TYPE_WEAPON_CHAFF,								// sub_type
				NUM_CHAFFS,														// number
				CHAFF_DISPENSER,												// heading_depth
				CHAFF_VECTOR,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 2
			{
				ENTITY_SUB_TYPE_WEAPON_FLARE,								// sub_type
				NUM_FLARES,														// number
				FLARE_DISPENSER,												// heading_depth
				FLARE_VECTOR,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 3
			{
				ENTITY_SUB_TYPE_WEAPON_2A42_30MM_HE_ROUND,			// sub_type
				NUM_HE_CANNON_ROUNDS,										// number
				CANNON_TURRET,													// heading_depth
				CANNON_BARREL,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				CANNON_TURRET_HEADING_RATE,								// heading_rate
				CANNON_TURRET_MIN_HEADING_LIMIT,							// min_heading_limit
				CANNON_TURRET_MAX_HEADING_LIMIT,							// max_heading_limit
				CANNON_BARREL_PITCH_RATE,									// pitch_rate
				CANNON_BARREL_MIN_PITCH_LIMIT,							// min_pitch_limit
				CANNON_BARREL_MAX_PITCH_LIMIT,							// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE3 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE4,
				SHARE_WEAPON_PACKAGE3 +										// pitch_share_mask
				SHARE_WEAPON_PACKAGE4,
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 4
			{
				ENTITY_SUB_TYPE_WEAPON_2A42_30MM_AP_ROUND,			// sub_type
				NUM_AP_CANNON_ROUNDS,										// number
				CANNON_TURRET,													// heading_depth
				CANNON_BARREL,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				CANNON_TURRET_HEADING_RATE,								// heading_rate
				CANNON_TURRET_MIN_HEADING_LIMIT,							// min_heading_limit
				CANNON_TURRET_MAX_HEADING_LIMIT,							// max_heading_limit
				CANNON_BARREL_PITCH_RATE,									// pitch_rate
				CANNON_BARREL_MIN_PITCH_LIMIT,							// min_pitch_limit
				CANNON_BARREL_MAX_PITCH_LIMIT,							// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE3 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE4,
				SHARE_WEAPON_PACKAGE3 +										// pitch_share_mask
				SHARE_WEAPON_PACKAGE4,
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 5
			{
				ENTITY_SUB_TYPE_WEAPON_S13,								// sub_type
				NUM_S13_ROCKETS,												// number
				LHS_HARDPOINT1,												// heading_depth
				B13_POD,															// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				2,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 6
			{
				ENTITY_SUB_TYPE_WEAPON_S13,								// sub_type
				NUM_S13_ROCKETS,												// number
				RHS_HARDPOINT1,												// heading_depth
				B13_POD,															// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				2,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 7
			{
				ENTITY_SUB_TYPE_WEAPON_GSH23L_23MM_ROUND,				// sub_type
				NUM_CANNON_POD_ROUNDS,										// number
				LHS_HARDPOINT2,												// heading_depth
				CANNON_POD,														// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				2,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 8
			{
				ENTITY_SUB_TYPE_WEAPON_GSH23L_23MM_ROUND,				// sub_type
				NUM_CANNON_POD_ROUNDS,										// number
				RHS_HARDPOINT2,												// heading_depth
				CANNON_POD,														// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				2,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
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
		////////////////////////////////////////
		//
		// WEAPON_CONFIG_TYPE_MI28N_HAVOC_B_30
		//
		////////////////////////////////////////
		{
			// WEAPON PACKAGE 1
			{
				ENTITY_SUB_TYPE_WEAPON_CHAFF,								// sub_type
				NUM_CHAFFS,														// number
				CHAFF_DISPENSER,												// heading_depth
				CHAFF_VECTOR,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 2
			{
				ENTITY_SUB_TYPE_WEAPON_FLARE,								// sub_type
				NUM_FLARES,														// number
				FLARE_DISPENSER,												// heading_depth
				FLARE_VECTOR,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				1,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 3
			{
				ENTITY_SUB_TYPE_WEAPON_2A42_30MM_HE_ROUND,			// sub_type
				NUM_HE_CANNON_ROUNDS,										// number
				CANNON_TURRET,													// heading_depth
				CANNON_BARREL,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				CANNON_TURRET_HEADING_RATE,								// heading_rate
				CANNON_TURRET_MIN_HEADING_LIMIT,							// min_heading_limit
				CANNON_TURRET_MAX_HEADING_LIMIT,							// max_heading_limit
				CANNON_BARREL_PITCH_RATE,									// pitch_rate
				CANNON_BARREL_MIN_PITCH_LIMIT,							// min_pitch_limit
				CANNON_BARREL_MAX_PITCH_LIMIT,							// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE3 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE4,
				SHARE_WEAPON_PACKAGE3 +										// pitch_share_mask
				SHARE_WEAPON_PACKAGE4,
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 4
			{
				ENTITY_SUB_TYPE_WEAPON_2A42_30MM_AP_ROUND,			// sub_type
				NUM_AP_CANNON_ROUNDS,										// number
				CANNON_TURRET,													// heading_depth
				CANNON_BARREL,													// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				TRUE,																// rotate
				1,																	// salvo_size
				CANNON_TURRET_HEADING_RATE,								// heading_rate
				CANNON_TURRET_MIN_HEADING_LIMIT,							// min_heading_limit
				CANNON_TURRET_MAX_HEADING_LIMIT,							// max_heading_limit
				CANNON_BARREL_PITCH_RATE,									// pitch_rate
				CANNON_BARREL_MIN_PITCH_LIMIT,							// min_pitch_limit
				CANNON_BARREL_MAX_PITCH_LIMIT,							// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				SHARE_WEAPON_PACKAGE3 +										// heading_share_mask
				SHARE_WEAPON_PACKAGE4,
				SHARE_WEAPON_PACKAGE3 +										// pitch_share_mask
				SHARE_WEAPON_PACKAGE4,
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 5
			{
				ENTITY_SUB_TYPE_WEAPON_GSH23L_23MM_ROUND,				// sub_type
				NUM_CANNON_POD_ROUNDS,										// number
				LHS_HARDPOINT1,												// heading_depth
				CANNON_POD,														// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				2,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 6
			{
				ENTITY_SUB_TYPE_WEAPON_GSH23L_23MM_ROUND,				// sub_type
				NUM_CANNON_POD_ROUNDS,										// number
				RHS_HARDPOINT1,												// heading_depth
				CANNON_POD,														// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				2,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 7
			{
				ENTITY_SUB_TYPE_WEAPON_GSH23L_23MM_ROUND,				// sub_type
				NUM_CANNON_POD_ROUNDS,										// number
				LHS_HARDPOINT2,												// heading_depth
				CANNON_POD,														// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				2,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 8
			{
				ENTITY_SUB_TYPE_WEAPON_GSH23L_23MM_ROUND,				// sub_type
				NUM_CANNON_POD_ROUNDS,										// number
				RHS_HARDPOINT2,												// heading_depth
				CANNON_POD,														// pitch_depth
				0,																	// muzzle_depth
				FALSE,															// make_weapon_system_ready
				FALSE,															// rotate
				2,																	// salvo_size
				rad (0.0),														// heading_rate
				rad (0.0),														// min_heading_limit
				rad (0.0),														// max_heading_limit
				rad (0.0),														// pitch_rate
				rad (0.0),														// min_pitch_limit
				rad (0.0),														// max_pitch_limit
				rad (0.0),														// muzzle_rotate_rate
				knots_to_metres_per_second (10000.0),					// rotate_inhibit_velocity
				0,																	// heading_share_mask
				0,																	// pitch_share_mask
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
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

		#undef LHS_HARDPOINT1
		#undef RHS_HARDPOINT1
		#undef LHS_HARDPOINT2
		#undef RHS_HARDPOINT2
		#undef CANNON_TURRET
		#undef CHAFF_DISPENSER
		#undef FLARE_DISPENSER

		#undef CANNON_BARREL
		#undef ATAKA_RACK
		#undef IGLA_PYLON
		#undef B8_POD
		#undef B13_POD
		#undef CANNON_POD
		#undef CHAFF_VECTOR
		#undef FLARE_VECTOR

		#undef NUM_HE_CANNON_ROUNDS
		#undef NUM_AP_CANNON_ROUNDS
		#undef NUM_ATAKA_MISSILES
		#undef NUM_IGLA_MISSILES
		#undef NUM_S8_ROCKETS
		#undef NUM_S13_ROCKETS
		#undef NUM_CANNON_POD_ROUNDS
		#undef NUM_CHAFFS
		#undef NUM_FLARES

		#undef CANNON_TURRET_HEADING_RATE
		#undef CANNON_TURRET_MIN_HEADING_LIMIT
		#undef CANNON_TURRET_MAX_HEADING_LIMIT
		#undef CANNON_BARREL_PITCH_RATE
		#undef CANNON_BARREL_MIN_PITCH_LIMIT
		#undef CANNON_BARREL_MAX_PITCH_LIMIT
