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
		// ENTITY_SUB_TYPE_AIRCRAFT_A10A_THUNDERBOLT
		//
		////////////////////////////////////////////////////////////////////////////////

		#define LHS_HARDPOINT1	  			(0)
		#define RHS_HARDPOINT1 	  			(1)
		#define LHS_HARDPOINT2_1  			(2)
		#define RHS_HARDPOINT2_1  			(3)
		#define LHS_HARDPOINT2_2  			(4)
		#define RHS_HARDPOINT2_2  			(5)
		#define LHS_HARDPOINT2_3  			(6)
		#define RHS_HARDPOINT2_3  			(7)
		#define LHS_HARDPOINT3	  			(8)
		#define RHS_HARDPOINT3 	  			(9)
		#define LHS_HARDPOINT4	  			(10)
		#define RHS_HARDPOINT4 	  			(11)
		#define CANNON   			  			(12)
		#define CHAFF_DISPENSER				(13)
		#define FLARE_DISPENSER				(13)

		#define CANNON_BARREL				(0)
		#define SIDEWINDER_PYLON			(0)
		#define LAU69A_ROCKET_POD			(0)
		#define CHAFF_VECTOR	  				(0)
		#define FLARE_VECTOR	  				(0)

		#define NUM_CANNON_ROUNDS			(1174)
		#define NUM_LAU69A_ROCKETS 		(19)
		#define NUM_SIDEWINDER_MISSILES	(2)
		#define NUM_CHAFFS					(30)
		#define NUM_FLARES	  	  			(30)

		////////////////////////////////////////
		//
		// WEAPON_CONFIG_TYPE_A10A_THUNDERBOLT_1
		//
		////////////////////////////////////////
		{
			// WEAPON PACKAGE 1
			{
				ENTITY_SUB_TYPE_WEAPON_CHAFF,								// sub_type
				NUM_CHAFFS,	 	  												// number
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
				knots_to_metres_per_second (10000.0),		  			// rotate_inhibit_velocity
				0,		 															// heading_share_mask
				0,		 			 								  				// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 2
			{
				ENTITY_SUB_TYPE_WEAPON_FLARE,								// sub_type
				NUM_FLARES,	 													// number
				FLARE_DISPENSER,												// heading_depth
				FLARE_VECTOR,			  										// pitch_depth
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
				knots_to_metres_per_second (10000.0),		  			// rotate_inhibit_velocity
				0,		 															// heading_share_mask
				0,		 			 								  				// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 3
			{
				ENTITY_SUB_TYPE_WEAPON_GAU8A_30MM_ROUND,				// sub_type
				NUM_CANNON_ROUNDS,	 										// number
				CANNON,	  														// heading_depth
				CANNON_BARREL,			  	 									// pitch_depth
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
				knots_to_metres_per_second (10000.0),		  			// rotate_inhibit_velocity
				0,		 															// heading_share_mask
				0,		 			 								  				// pitch_share_mask
				MUZZLE_FLASH_MEDIUM_CALIBRE_STRAIGHT,					// muzzle_flash_type
			},
			// WEAPON PACKAGE 4
			{
				ENTITY_SUB_TYPE_WEAPON_LAU69A,	  						// sub_type
				NUM_LAU69A_ROCKETS,	 										// number
				LHS_HARDPOINT1,												// heading_depth
				LAU69A_ROCKET_POD,		  	 								// pitch_depth
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
				knots_to_metres_per_second (10000.0),		  			// rotate_inhibit_velocity
				0,		 															// heading_share_mask
				0,		 			 								  				// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 5
			{
				ENTITY_SUB_TYPE_WEAPON_LAU69A,	  						// sub_type
				NUM_LAU69A_ROCKETS,	 										// number
				RHS_HARDPOINT1,												// heading_depth
				LAU69A_ROCKET_POD,		  	 								// pitch_depth
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
				knots_to_metres_per_second (10000.0),		  			// rotate_inhibit_velocity
				0,		 															// heading_share_mask
				0,		 			 								  				// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 6
			{
				ENTITY_SUB_TYPE_WEAPON_LAU69A,	  						// sub_type
				NUM_LAU69A_ROCKETS,	 										// number
				LHS_HARDPOINT2_1,												// heading_depth
				LAU69A_ROCKET_POD,		  	 								// pitch_depth
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
				knots_to_metres_per_second (10000.0),		  			// rotate_inhibit_velocity
				0,		 															// heading_share_mask
				0,		 			 								  				// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 7
			{
				ENTITY_SUB_TYPE_WEAPON_LAU69A,	  						// sub_type
				NUM_LAU69A_ROCKETS,	 										// number
				RHS_HARDPOINT2_1,												// heading_depth
				LAU69A_ROCKET_POD,		  	 								// pitch_depth
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
				knots_to_metres_per_second (10000.0),		  			// rotate_inhibit_velocity
				0,		 															// heading_share_mask
				0,		 			 								  				// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 8
			{
				ENTITY_SUB_TYPE_WEAPON_LAU69A,	  						// sub_type
				NUM_LAU69A_ROCKETS,	 										// number
				LHS_HARDPOINT2_2,												// heading_depth
				LAU69A_ROCKET_POD,		  	 								// pitch_depth
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
				knots_to_metres_per_second (10000.0),		  			// rotate_inhibit_velocity
				0,		 															// heading_share_mask
				0,		 			 								  				// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 9
			{
				ENTITY_SUB_TYPE_WEAPON_LAU69A,	  						// sub_type
				NUM_LAU69A_ROCKETS,	 										// number
				RHS_HARDPOINT2_2,												// heading_depth
				LAU69A_ROCKET_POD,		  	 								// pitch_depth
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
				knots_to_metres_per_second (10000.0),		  			// rotate_inhibit_velocity
				0,		 															// heading_share_mask
				0,		 			 								  				// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 10
			{
				ENTITY_SUB_TYPE_WEAPON_LAU69A,	  						// sub_type
				NUM_LAU69A_ROCKETS,	 										// number
				LHS_HARDPOINT2_3,												// heading_depth
				LAU69A_ROCKET_POD,		  	 								// pitch_depth
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
				knots_to_metres_per_second (10000.0),		  			// rotate_inhibit_velocity
				0,		 															// heading_share_mask
				0,		 			 								  				// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 11
			{
				ENTITY_SUB_TYPE_WEAPON_LAU69A,	  						// sub_type
				NUM_LAU69A_ROCKETS,	 										// number
				RHS_HARDPOINT2_3,												// heading_depth
				LAU69A_ROCKET_POD,		  	 								// pitch_depth
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
				knots_to_metres_per_second (10000.0),		  			// rotate_inhibit_velocity
				0,		 															// heading_share_mask
				0,		 			 								  				// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 12
			{
				ENTITY_SUB_TYPE_WEAPON_LAU69A,	  						// sub_type
				NUM_LAU69A_ROCKETS,	 										// number
				LHS_HARDPOINT3,												// heading_depth
				LAU69A_ROCKET_POD,		  	 								// pitch_depth
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
				knots_to_metres_per_second (10000.0),		  			// rotate_inhibit_velocity
				0,		 															// heading_share_mask
				0,		 			 								  				// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 13
			{
				ENTITY_SUB_TYPE_WEAPON_LAU69A,	  						// sub_type
				NUM_LAU69A_ROCKETS,	 										// number
				RHS_HARDPOINT3,												// heading_depth
				LAU69A_ROCKET_POD,		  	 								// pitch_depth
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
				knots_to_metres_per_second (10000.0),		  			// rotate_inhibit_velocity
				0,		 															// heading_share_mask
				0,		 			 								  				// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 14
			{
				ENTITY_SUB_TYPE_WEAPON_AIM9M_SIDEWINDER,	  			// sub_type
				NUM_SIDEWINDER_MISSILES,	 								// number
				LHS_HARDPOINT4,												// heading_depth
				SIDEWINDER_PYLON,	  			  	 							// pitch_depth
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
				knots_to_metres_per_second (10000.0),		  			// rotate_inhibit_velocity
				0,		 															// heading_share_mask
				0,		 			 								  				// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
			// WEAPON PACKAGE 15
			{
				ENTITY_SUB_TYPE_WEAPON_AIM9M_SIDEWINDER,	  			// sub_type
				NUM_SIDEWINDER_MISSILES,	 								// number
				RHS_HARDPOINT4,												// heading_depth
				SIDEWINDER_PYLON,				  	 							// pitch_depth
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
				knots_to_metres_per_second (10000.0),		  			// rotate_inhibit_velocity
				0,		 															// heading_share_mask
				0,		 			 								  				// pitch_share_mask
				MUZZLE_FLASH_INVALID,										// muzzle_flash_type
			},
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
		#undef LHS_HARDPOINT2_1
		#undef RHS_HARDPOINT2_1
		#undef LHS_HARDPOINT2_2
		#undef RHS_HARDPOINT2_2
		#undef LHS_HARDPOINT2_3
		#undef RHS_HARDPOINT2_3
		#undef LHS_HARDPOINT3
		#undef RHS_HARDPOINT3
		#undef LHS_HARDPOINT4
		#undef RHS_HARDPOINT4
		#undef CANNON
		#undef CHAFF_DISPENSER
		#undef FLARE_DISPENSER

		#undef CANNON_BARREL
		#undef SIDEWINDER_PYLON
		#undef LAU69A_ROCKET_POD
		#undef CHAFF_VECTOR
		#undef FLARE_VECTOR

		#undef NUM_CANNON_ROUNDS
		#undef NUM_LAU69A_ROCKETS
		#undef NUM_SIDEWINDER_MISSILES
		#undef NUM_CHAFFS
		#undef NUM_FLARES
