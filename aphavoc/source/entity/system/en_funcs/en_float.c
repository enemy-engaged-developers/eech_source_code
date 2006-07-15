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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE				0

#define DEBUG_MODULE_PACK_ONE	0

#define DEBUG_MODULE_PACK_ALL	(PACK_ENTIRE_SESSION || 0)

#define DEBUG_PACK_OVERFLOW TRUE

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define ILLEGAL	(FALSE)												// use for values which cannot be fast tracked

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float_type_data
	float_type_database[NUM_FLOAT_TYPES] =
	{
		{
			"FLOAT_TYPE_AFTERBURNER_STATE",	           			// name
			FLOAT_PACK_TYPE_UNPACKED,	                 			// pack_type
			0,																	// num_pack_bits (including sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_AIRBRAKE_STATE",		           			// name
			FLOAT_PACK_TYPE_UNSIGNED_VALUE,     	    			// pack_type
			2,																	// pack_num_whole_bits (excluding sign bit)
			6,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_AIR_RADAR_CONTACT_TIMEOUT",				// name
			FLOAT_PACK_TYPE_UNPACKED,									// pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_AIR_SCAN_CEILING",	 						// name
			FLOAT_PACK_TYPE_UNPACKED,									// pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_AIR_SCAN_FLOOR",	 							// name
			FLOAT_PACK_TYPE_UNPACKED,									// pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_AIR_SCAN_RANGE",		 						// name
			FLOAT_PACK_TYPE_UNPACKED,									// pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_ALTITUDE",										// name
			FLOAT_PACK_TYPE_SIGNED_VALUE,								// pack_type
			14,																// pack_num_whole_bits (excluding sign bit)
			6,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_AMMO_ECONOMY",		 							// name
			FLOAT_PACK_TYPE_UNPACKED,                          // pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_AMMO_SUPPLY_LEVEL", 							// name
			FLOAT_PACK_TYPE_UNPACKED,                          // pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_AMPLIFICATION", 								// name
			FLOAT_PACK_TYPE_UNSIGNED_VALUE,                    // pack_type
			1,																	// pack_num_whole_bits (excluding sign bit)
			4,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_SOUNDPITCH", 								// name
			FLOAT_PACK_TYPE_UNSIGNED_VALUE,                    // pack_type
			3,																	// pack_num_whole_bits (excluding sign bit)
			4,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_ANIMATION_FREQUENCY", 						// name
			FLOAT_PACK_TYPE_UNSIGNED_VALUE,		  					// pack_type
			4,																	// pack_num_whole_bits (excluding sign bit)
			4,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_ASSIGN_TIMER",		  	         			// name
			FLOAT_PACK_TYPE_UNSIGNED_VALUE,     	    			// pack_type
			12,																// pack_num_whole_bits (excluding sign bit)
			4,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_ASSIST_TIMER",		  	         			// name
			FLOAT_PACK_TYPE_UNSIGNED_VALUE,     	    			// pack_type
			8,																	// pack_num_whole_bits (excluding sign bit)
			4,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_ATTACK_ALTITUDE",								// name
			FLOAT_PACK_TYPE_UNPACKED,                          // pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_AVOIDANCE_RADIUS",	 						// name
			FLOAT_PACK_TYPE_UNPACKED,                          // pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_AXLE_LENGTH",			 						// name
			FLOAT_PACK_TYPE_UNPACKED,                          // pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_CARGO_DOOR_STATE",							// name
			FLOAT_PACK_TYPE_UNSIGNED_VALUE,							// pack_type
			2,																	// pack_num_whole_bits (excluding sign bit)
			6,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_CENTRE_OF_GRAVITY_TO_GROUND_DISTANCE",	// name
			FLOAT_PACK_TYPE_UNPACKED,                          // pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_CHASE_VIEW_MAX_DISTANCE",              // name
			FLOAT_PACK_TYPE_UNPACKED,                          // pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_CHASE_VIEW_MAX_DISTANCE_TEST",         // name
			FLOAT_PACK_TYPE_UNPACKED,                          // pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_CHASE_VIEW_MIN_DISTANCE",              // name
			FLOAT_PACK_TYPE_UNPACKED,                          // pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_CHASE_VIEW_MIN_DISTANCE_TEST",         // name
			FLOAT_PACK_TYPE_UNPACKED,                          // pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_CRATER_LIFETIME",								// name
			FLOAT_PACK_TYPE_UNSIGNED_VALUE,		 					// pack_type
			10,																// pack_num_whole_bits (excluding sign bit)
			6,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_CRUISE_ALTITUDE",								// name
			FLOAT_PACK_TYPE_UNPACKED,                          // pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_CRUISE_VELOCITY",								// name
			FLOAT_PACK_TYPE_UNPACKED,                          // pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_CURRENT_MESSAGE_TIMER",						// name
			FLOAT_PACK_TYPE_UNSIGNED_VALUE,                    // pack_type
			4,																	// pack_num_whole_bits (excluding sign bit)
			4,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_DEATH_TIMER",									// name
			FLOAT_PACK_TYPE_UNSIGNED_VALUE,							// pack_type
			16,																// pack_num_whole_bits (excluding sign bit)
			4,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_DECOY_RELEASE_TIMER",	 					// name
			FLOAT_PACK_TYPE_UNSIGNED_VALUE,							// pack_type
			4,																	// pack_num_whole_bits (excluding sign bit)
			4,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_DECOY_TIMER",									// name
			FLOAT_PACK_TYPE_UNSIGNED_VALUE,							// pack_type
			4,																	// pack_num_whole_bits (excluding sign bit)
			4,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_DESIRED_VELOCITY",                     // name
			FLOAT_PACK_TYPE_SIGNED_VALUE,		 						// pack_type
			7,																	// pack_num_whole_bits (excluding sign bit)
			6,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_DISTANCE",										// name
			FLOAT_PACK_TYPE_UNSIGNED_VALUE,							// pack_type
			20,																// pack_num_whole_bits (excluding sign bit)
			4,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_EFFECT_LIFETIME",                      // name
			FLOAT_PACK_TYPE_SIGNED_VALUE,	  							// pack_type
			7,																	// pack_num_whole_bits (excluding sign bit)
			4,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_EFFICIENCY",									// name
			FLOAT_PACK_TYPE_UNPACKED,	 								// pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_ELAPSED_MISSION_TIME",						// name
			FLOAT_PACK_TYPE_UNPACKED,	 								// pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_ELAPSED_TIME",									// name
			FLOAT_PACK_TYPE_UNPACKED,	 								// pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_END_SCALE",										// name
			FLOAT_PACK_TYPE_UNSIGNED_VALUE,							// pack_type
			8,																	// pack_num_whole_bits (excluding sign bit)
			4,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_EXPIRE_TIMER",		                     // name
			FLOAT_PACK_TYPE_UNPACKED,                          // pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_EXPLOSION_STATE",                      // name
			FLOAT_PACK_TYPE_SIGNED_VALUE,	  							// pack_type
			2,																	// pack_num_whole_bits (excluding sign bit)
			6,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_FIXED_OBJECT_IMPORTANCE",	            // name
			FLOAT_PACK_TYPE_UNPACKED,                          // pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_FIXED_STRUCTURE_HEIGHT",	            // name
			FLOAT_PACK_TYPE_UNPACKED,                          // pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_FLAP_STATE",		   	        			// name
			FLOAT_PACK_TYPE_UNSIGNED_VALUE,     	    			// pack_type
			2,																	// pack_num_whole_bits (excluding sign bit)
			6,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_FLIGHT_TIME",		   	        			// name
			FLOAT_PACK_TYPE_UNPACKED,			     	    			// pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_FOG_OF_WAR",					            // name
			FLOAT_PACK_TYPE_UNSIGNED_VALUE,                    // pack_type
			15,																// pack_num_whole_bits (excluding sign bit)
			1,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_FOG_OF_WAR_MAXIMUM_VALUE",		         // name
			FLOAT_PACK_TYPE_UNSIGNED_VALUE,                    // pack_type
			15,																// pack_num_whole_bits (excluding sign bit)
			1,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_FREQUENCY",                            // name
			FLOAT_PACK_TYPE_UNSIGNED_VALUE,							// pack_type
			8,																	// pack_num_whole_bits (excluding sign bit)
			8,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_FUEL_DEFAULT_WEIGHT", 		            // name
			FLOAT_PACK_TYPE_UNPACKED,                          // pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_FUEL_ECONOMY", 		                   // name
			FLOAT_PACK_TYPE_UNPACKED,                          // pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_FUEL_SUPPLY_LEVEL",                    // name
			FLOAT_PACK_TYPE_UNPACKED,                          // pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_FUSELAGE_ANGLE",                       // name
			FLOAT_PACK_TYPE_UNPACKED,                          // pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_GENERATOR_LIFETIME",							// name
			FLOAT_PACK_TYPE_SIGNED_VALUE,								// pack_type
			16,																	// pack_num_whole_bits (excluding sign bit)
			4,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_GUIDE_CRITERIA_VALUE",						// name
			FLOAT_PACK_TYPE_SIGNED_VALUE,								// pack_type
			16,																// pack_num_whole_bits (excluding sign bit)
			6,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_HEADING",                              // name
			FLOAT_PACK_TYPE_SIGNED_ANGLE,								// pack_type
			3,																	// pack_num_whole_bits (excluding sign bit)
			8,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_HIGH_VELOCITY",								// name
			FLOAT_PACK_TYPE_SIGNED_VALUE,								// pack_type
			10,																	// pack_num_whole_bits (excluding sign bit)
			6,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_INITIAL_SPEED",								// name
			FLOAT_PACK_TYPE_SIGNED_VALUE,								// pack_type
			7,																	// pack_num_whole_bits (excluding sign bit)
			6,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_INVULNERABLE_TIMER",							// name
			FLOAT_PACK_TYPE_UNPACKED,									// pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_KEYSITE_IMPORTANCE",                   // name
			FLOAT_PACK_TYPE_UNPACKED,                          // pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_KEYSITE_MAXIMUM_STRENGTH",  	         // name
			FLOAT_PACK_TYPE_UNPACKED,                          // pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_KEYSITE_STRENGTH",  		               // name
			FLOAT_PACK_TYPE_UNPACKED,                          // pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_LAND_URGENCY",                         // name
			FLOAT_PACK_TYPE_UNPACKED,                          // pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_LIFETIME",										// name
			FLOAT_PACK_TYPE_UNPACKED,									// pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_LIGHTNING_TIMER",								// name
			FLOAT_PACK_TYPE_UNSIGNED_VALUE,							// pack_type
			8,																	// pack_num_whole_bits (excluding sign bit)
			2,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_LOADING_DOOR_STATE",							// name
			FLOAT_PACK_TYPE_UNSIGNED_VALUE,							// pack_type
			2,																	// pack_num_whole_bits (excluding sign bit)
			6,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_LOADING_DOOR_TIMER",							// name
			FLOAT_PACK_TYPE_UNSIGNED_VALUE,							// pack_type
			5,																	// pack_num_whole_bits (excluding sign bit)
			6,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_LOW_VELOCITY",									// name
			FLOAT_PACK_TYPE_SIGNED_VALUE,								// pack_type
			7,																	// pack_num_whole_bits (excluding sign bit)
			6,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_MAIN_ROTOR_BLADE_CONING_ANGLE",        // name
			FLOAT_PACK_TYPE_UNPACKED,                          // pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_MAIN_ROTOR_DIRECTION",						// name
			FLOAT_PACK_TYPE_UNPACKED,                          // pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_MAIN_ROTOR_BLADE_DROOP_ANGLE",         // name
			FLOAT_PACK_TYPE_UNPACKED,                          // pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_MAIN_ROTOR_PITCH",                     // name
			FLOAT_PACK_TYPE_UNPACKED,                          // pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		// Xhit: added "FLOAT_TYPE_MAIN_ROTOR_RADIUS" for downwash effect (030328)
		{
			"FLOAT_TYPE_MAIN_ROTOR_RADIUS",                    // name
			FLOAT_PACK_TYPE_UNPACKED,                          // pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_MAIN_ROTOR_ROLL",                      // name
			FLOAT_PACK_TYPE_UNPACKED,                          // pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_MAIN_ROTOR_RPM",                       // name
			FLOAT_PACK_TYPE_UNSIGNED_VALUE,		  					// pack_type
			4,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_MAIN_ROTOR_SHAFT_ANGLE",               // name
			FLOAT_PACK_TYPE_UNPACKED,                          // pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_MAIN_ROTOR_SPIN_UP_TIMER",             // name
			FLOAT_PACK_TYPE_UNSIGNED_VALUE,		  					// pack_type
			6,																	// pack_num_whole_bits (excluding sign bit)
			6,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_MAX_3D_OBJECT_VISUAL_RANGE",				// name
			FLOAT_PACK_TYPE_UNPACKED,									// pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_MAX_ACCELERATION",                     // name
			FLOAT_PACK_TYPE_UNPACKED,                          // pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_MAX_TURN_RATE",								// name
			FLOAT_PACK_TYPE_UNPACKED,									// pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_MAX_ROLL",										// name
			FLOAT_PACK_TYPE_UNPACKED,									// pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_MAX_VERTICAL_TURN_ALLOWANCE",				// name
			FLOAT_PACK_TYPE_UNPACKED,									// pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_MEDIUM_VELOCITY",								// name
			FLOAT_PACK_TYPE_SIGNED_VALUE,	  							// pack_type
			8,																	// pack_num_whole_bits (excluding sign bit)
			6,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_MINIMUM_EFFICIENCY",							// name
			FLOAT_PACK_TYPE_UNSIGNED_VALUE,	 						// pack_type
			1,																	// pack_num_whole_bits (excluding sign bit)
			7,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		// Xhit: added "FLOAT_TYPE_NUMBER_OF_MAIN_ROTORS" for downwash effect (030328)
		{
			"FLOAT_TYPE_NUMBER_OF_MAIN_ROTORS",                    // name
			FLOAT_PACK_TYPE_UNPACKED,                          // pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_PERSON_ANIMATION_STATE",               // name
			FLOAT_PACK_TYPE_UNSIGNED_VALUE,	 						// pack_type
			4,																	// pack_num_whole_bits (excluding sign bit)
			8,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_PITCH",                                // name
			FLOAT_PACK_TYPE_SIGNED_ANGLE,	 							// pack_type
			3,																	// pack_num_whole_bits (excluding sign bit)
			8,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
// Jabberwock 050310 MP Cannon bug
		{
			"FLOAT_TYPE_PLAYER_WEAPON_HEADING",                                // name
			FLOAT_PACK_TYPE_SIGNED_ANGLE,	 							// pack_type
			3,																	// pack_num_whole_bits (excluding sign bit)
			8,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_PLAYER_WEAPON_PITCH",                                // name
			FLOAT_PACK_TYPE_SIGNED_ANGLE,	 							// pack_type
			3,																	// pack_num_whole_bits (excluding sign bit)
			8,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
// Jabberwock 050310 ends
		{
			"FLOAT_TYPE_POPULATION_X_MIN",                     // name
			FLOAT_PACK_TYPE_UNPACKED,		 							// pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_POPULATION_X_MAX",                     // name
			FLOAT_PACK_TYPE_UNPACKED,		 							// pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_POPULATION_Z_MIN",                     // name
			FLOAT_PACK_TYPE_UNPACKED,		 							// pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_POPULATION_Z_MAX",                     // name
			FLOAT_PACK_TYPE_UNPACKED,		 							// pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_POTENTIAL_AIR_THREAT",						// name
			FLOAT_PACK_TYPE_UNPACKED,                          // pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_POTENTIAL_AIR_TO_AIR_THREAT",				// name
			FLOAT_PACK_TYPE_UNPACKED,                          // pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_POTENTIAL_AIR_TO_SURFACE_THREAT",		// name
			FLOAT_PACK_TYPE_UNPACKED,									// pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_POTENTIAL_SURFACE_THREAT",					// name
			FLOAT_PACK_TYPE_UNPACKED,									// pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_POTENTIAL_SURFACE_TO_AIR_THREAT",		// name
			FLOAT_PACK_TYPE_UNPACKED,									// pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_POTENTIAL_SURFACE_TO_SURFACE_THREAT",	// name
			FLOAT_PACK_TYPE_UNPACKED,                          // pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_POWER_OUTPUT",                         // name
			FLOAT_PACK_TYPE_UNPACKED,                          // pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_PROPELLOR_DIRECTION",						// name
			FLOAT_PACK_TYPE_UNPACKED,                          // pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_PROPELLOR_RPM",                        // name
			FLOAT_PACK_TYPE_UNPACKED,                          // pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_PROTOTYPE_1",									// name
			FLOAT_PACK_TYPE_UNPACKED,                          // pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_PROTOTYPE_2",									// name
			FLOAT_PACK_TYPE_UNPACKED,                          // pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_PROTOTYPE_3",									// name
			FLOAT_PACK_TYPE_UNPACKED,                          // pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_PROTOTYPE_4",									// name
			FLOAT_PACK_TYPE_UNPACKED,                          // pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_RADAR_ALTITUDE",								// name
			FLOAT_PACK_TYPE_UNPACKED,                          // pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_RADAR_ROTATION_STATE",						// name
			FLOAT_PACK_TYPE_UNPACKED,                          // pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_RADAR_STEALTH_FACTOR",						// name
			FLOAT_PACK_TYPE_UNPACKED,			  						// pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_RANGE",                                // name
			FLOAT_PACK_TYPE_UNPACKED,                          // pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_RATING",                               // name
			FLOAT_PACK_TYPE_UNSIGNED_VALUE,                    // pack_type
			1,																	// pack_num_whole_bits (excluding sign bit)
			7,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_REARMING_TIME",  			               // name
			FLOAT_PACK_TYPE_UNPACKED,                          // pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_RECON_DISTANCE",   		               // name
			FLOAT_PACK_TYPE_UNPACKED,                          // pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_RECON_RADIUS",   			               // name
			FLOAT_PACK_TYPE_UNPACKED,                          // pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_REPAIR_TIMER",   			               // name
			FLOAT_PACK_TYPE_SIGNED_VALUE,                      // pack_type
			10,																// pack_num_whole_bits (excluding sign bit)
			4,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_ROLL",                                 // name
			FLOAT_PACK_TYPE_SIGNED_ANGLE,								// pack_type
			3,																	// pack_num_whole_bits (excluding sign bit)
			8,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_RUDDER_STATE",			           			// name
			FLOAT_PACK_TYPE_UNSIGNED_VALUE,     	    			// pack_type
			2,																	// pack_num_whole_bits (excluding sign bit)
			6,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_SCALE",											// name
			FLOAT_PACK_TYPE_UNSIGNED_VALUE,							// pack_type
			8,																	// pack_num_whole_bits (excluding sign bit)
			4,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_SECTOR_SIDE_MAX_VALUE",						// name
			FLOAT_PACK_TYPE_UNPACKED,									// pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_SLEEP",                                // name
			FLOAT_PACK_TYPE_UNPACKED,                          // pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_SMOKE_LIFETIME",								// name
			FLOAT_PACK_TYPE_SIGNED_VALUE,								// pack_type
			16,																	// pack_num_whole_bits (excluding sign bit)
			4,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_SMOKE_SLEEP",									// name
			FLOAT_PACK_TYPE_UNSIGNED_VALUE,							// pack_type
			8,																	// pack_num_whole_bits (excluding sign bit)
			8,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_SPEECH_CATEGORY_SILENCE_TIMER",			// name
			FLOAT_PACK_TYPE_UNSIGNED_VALUE,							// pack_type
			7,																	// pack_num_whole_bits (excluding sign bit)
			2,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_SPEECH_EXPIRE_TIME",							// name
			FLOAT_PACK_TYPE_UNSIGNED_VALUE,							// pack_type
			10,																// pack_num_whole_bits (excluding sign bit)
			4,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_SPEECH_PRIORITY",								// name
			FLOAT_PACK_TYPE_UNSIGNED_VALUE,		 					// pack_type
			1,																	// pack_num_whole_bits (excluding sign bit)
			7,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_SPRITE_LIFETIME",								// name
			FLOAT_PACK_TYPE_SIGNED_VALUE,		  						// pack_type
			7,																	// pack_num_whole_bits (excluding sign bit)
			4,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_START_SCALE",									// name
			FLOAT_PACK_TYPE_UNSIGNED_VALUE,							// pack_type
			8,																	// pack_num_whole_bits (excluding sign bit)
			4,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_START_TIME",		                     // name
			FLOAT_PACK_TYPE_UNPACKED,                          // pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_STOP_TIMER",		                     // name
			FLOAT_PACK_TYPE_UNPACKED,                          // pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_SURFACE_SCAN_RANGE",							// name
			FLOAT_PACK_TYPE_UNPACKED,                          // pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_TAIL_ROTOR_DIRECTION",                 // name
			FLOAT_PACK_TYPE_UNPACKED,                          // pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_TAIL_ROTOR_RPM",								// name
			FLOAT_PACK_TYPE_UNPACKED,									// pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_TALLEST_STRUCTURE_HEIGHT",	 				// name
			FLOAT_PACK_TYPE_UNPACKED,                          // pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_TARGET_FIRE_TIMER",							// name
			FLOAT_PACK_TYPE_UNPACKED,									// pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_TARGET_PRIORITY_AIR_ATTACK",				// name
			FLOAT_PACK_TYPE_UNPACKED,									// pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_TARGET_PRIORITY_GROUND_ATTACK",			// name
			FLOAT_PACK_TYPE_UNPACKED,									// pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_TARGET_SCAN_DELAY",							// name
			FLOAT_PACK_TYPE_UNPACKED,									// pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_TARGET_SCAN_TIMER",							// name
			FLOAT_PACK_TYPE_UNPACKED,									// pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_TASK_COST",                            // name
			FLOAT_PACK_TYPE_UNPACKED,                          // pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_TASK_DEFAULT_PRIORITY",                // name
			FLOAT_PACK_TYPE_UNPACKED,                          // pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_TASK_PRIORITY",                        // name
			FLOAT_PACK_TYPE_SIGNED_VALUE,                      // pack_type
			4,																	// pack_num_whole_bits (excluding sign bit)
			4,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_TASK_SUCCESS_RATE",                    // name
			FLOAT_PACK_TYPE_UNSIGNED_VALUE,                    // pack_type
			1,																	// pack_num_whole_bits (excluding sign bit)
			7,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_TASK_USER_DATA",                       // name
			FLOAT_PACK_TYPE_UNPACKED,                          // pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_TERRAIN_ELEVATION",                    // name
			FLOAT_PACK_TYPE_UNPACKED,                          // pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_TIME_OF_DAY",									// name
			FLOAT_PACK_TYPE_UNSIGNED_VALUE,							// pack_type
			17,																// pack_num_whole_bits (excluding sign bit)
			4,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_TIME_OF_DAY_ACCELERATION",             // name
			FLOAT_PACK_TYPE_UNPACKED,                          // pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_UNDERCARRIAGE_STATE",           			// name
			FLOAT_PACK_TYPE_UNSIGNED_VALUE,     	    			// pack_type
			2,																	// pack_num_whole_bits (excluding sign bit)
			6,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_URGENCY",				           			// name
			FLOAT_PACK_TYPE_UNPACKED,                   			// pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_VALID_EFFECT_LIFETIME",         			// name
			FLOAT_PACK_TYPE_UNSIGNED_VALUE,     	    			// pack_type
			2,																	// pack_num_whole_bits (excluding sign bit)
			6,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_VELOCITY",                             // name
			FLOAT_PACK_TYPE_UNPACKED,                          // pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_VERY_HIGH_VELOCITY",							// name
			FLOAT_PACK_TYPE_SIGNED_VALUE,								// pack_type
			11,																// pack_num_whole_bits (excluding sign bit)
			6,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_VIEW_INTEREST_LEVEL",						// name
			FLOAT_PACK_TYPE_UNPACKED,									// pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_WEAPON_BURST_TIMER",							// name
			FLOAT_PACK_TYPE_UNPACKED,									// pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_WEAPON_LIFETIME",								// name
			FLOAT_PACK_TYPE_SIGNED_VALUE,								// pack_type
			9,																	// pack_num_whole_bits (excluding sign bit)
			4,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_WEAPON_SYSTEM_HEADING",						// name
			FLOAT_PACK_TYPE_SIGNED_ANGLE,								// pack_type
			3,																	// pack_num_whole_bits (excluding sign bit)
			8,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_WEAPON_SYSTEM_PITCH",						// name
			FLOAT_PACK_TYPE_SIGNED_ANGLE,								// pack_type
			3,																	// pack_num_whole_bits (excluding sign bit)
			8,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_WEAPON_SYSTEM_READY_STATE",				// name
			FLOAT_PACK_TYPE_UNSIGNED_VALUE,		  					// pack_type
			2,																	// pack_num_whole_bits (excluding sign bit)
			6,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_WEATHER_MODE_TRANSITIONAL_PERIOD",     // name
			FLOAT_PACK_TYPE_UNPACKED,                          // pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_WEATHER_MODE_TRANSITIONAL_STATUS",     // name
			FLOAT_PACK_TYPE_UNPACKED,                          // pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_WEATHER_RADIUS", 							   // name
			FLOAT_PACK_TYPE_UNSIGNED_VALUE,                    // pack_type
			20,																// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_WEIGHT",											// name
			FLOAT_PACK_TYPE_UNPACKED,                          // pack_type
			0,																	// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_WIDTH_ADJUSTMENT",							// name
			FLOAT_PACK_TYPE_UNSIGNED_VALUE,							// pack_type
			8,																	// pack_num_whole_bits (excluding sign bit)
			4,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_WIND_EFFECT_RADIUS", 					   // name
			FLOAT_PACK_TYPE_UNSIGNED_VALUE,                    // pack_type
			20,																// pack_num_whole_bits (excluding sign bit)
			0,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_WIND_GUSTING_VALUE", 					   // name
			FLOAT_PACK_TYPE_UNSIGNED_VALUE,                    // pack_type
			1,																	// pack_num_whole_bits (excluding sign bit)
			7,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_WIND_MAXIMUM_SPEED", 					   // name
			FLOAT_PACK_TYPE_UNSIGNED_VALUE,                    // pack_type
			6,																	// pack_num_whole_bits (excluding sign bit)
			4,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_WIND_MINIMUM_SPEED", 					   // name
			FLOAT_PACK_TYPE_UNSIGNED_VALUE,                    // pack_type
			6,																	// pack_num_whole_bits (excluding sign bit)
			4,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_MINIMUM_SOUND_RANGE",							// name
			FLOAT_PACK_TYPE_UNSIGNED_VALUE,							// pack_type
			8,																	// pack_num_whole_bits (excluding sign bit)
			4,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_REFERENCE_SOUND_RANGE",							// name
			FLOAT_PACK_TYPE_UNSIGNED_VALUE,							// pack_type
			8,																	// pack_num_whole_bits (excluding sign bit)
			4,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
		{
			"FLOAT_TYPE_MAXIMUM_SOUND_RANGE",							// name
			FLOAT_PACK_TYPE_UNSIGNED_VALUE,							// pack_type
			8,																	// pack_num_whole_bits (excluding sign bit)
			4,																	// pack_num_fractional_bits
			(DEBUG_MODULE_PACK_ALL || 0),								// debug_pack
			FALSE,															// fast_track
		},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char
	*overload_invalid_float_type_message = "Overloaded entity function invoked with invalid float type",
	*debug_fatal_invalid_float_type_message = "Invalid float type (entity type = %s, index = %d, float type = %s, file = %s, line = %d)";

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void (*fn_set_local_entity_raw_float_value[NUM_ENTITY_TYPES][NUM_FLOAT_TYPES]) (entity *en, float_types type, float value);

void (*fn_set_local_entity_float_value[NUM_ENTITY_TYPES][NUM_FLOAT_TYPES]) (entity *en, float_types type, float value);

void (*fn_set_client_server_entity_float_value[NUM_ENTITY_TYPES][NUM_FLOAT_TYPES][NUM_COMMS_MODEL_TYPES]) (entity *en, float_types type, float value);

float (*fn_get_local_entity_float_value[NUM_ENTITY_TYPES][NUM_FLOAT_TYPES]) (entity *en, float_types type);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void default_set_entity_float_value (entity *en, float_types type, float value)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static float default_get_entity_float_value (entity *en, float_types type)
{
	float
		value;

	switch (type)
	{
		////////////////////////////////////////
		case FLOAT_TYPE_AIR_RADAR_CONTACT_TIMEOUT:
		////////////////////////////////////////
		{
			value = AIR_RADAR_CONTACT_TIMEOUT_INVALID;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_MAX_3D_OBJECT_VISUAL_RANGE:
		////////////////////////////////////////
		{
			value = NOMINAL_3D_OBJECT_VISUAL_RANGE;

			break;
		}
		////////////////////////////////////////
		case FLOAT_TYPE_RADAR_STEALTH_FACTOR:
		////////////////////////////////////////
		{
			value = NO_RADAR_STEALTH_FACTOR;

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			value = 0.0;

			break;
		}
	}

	return (value);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_entity_float_value_default_functions (void)
{
	int
		i,
		j;

	for (i = 0; i < NUM_ENTITY_TYPES; i++)
	{
		for (j = 0; j < NUM_FLOAT_TYPES; j++)
		{
			fn_set_local_entity_raw_float_value[i][j]									= default_set_entity_float_value;

			fn_set_local_entity_float_value[i][j]										= default_set_entity_float_value;

			fn_set_client_server_entity_float_value[i][j][COMMS_MODEL_SERVER]	= default_set_entity_float_value;

			fn_set_client_server_entity_float_value[i][j][COMMS_MODEL_CLIENT]	= default_set_entity_float_value;

			fn_get_local_entity_float_value[i][j]										= default_get_entity_float_value;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void pack_float_value (entity *en, float_types type, float value)
{
	ASSERT ((type >= 0) && (type < NUM_FLOAT_TYPES));

	switch (float_type_database[type].pack_type)
	{
		////////////////////////////////////////
		case FLOAT_PACK_TYPE_UNPACKED:
		////////////////////////////////////////
		{
			pack_unsigned_data (*(int *)&value, 32);

			#if (DEBUG_MODULE_PACK_ONE || DEBUG_MODULE_PACK_ALL)

			if (float_type_database[type].debug_pack)
			{
				debug_log_entity_args (ENTITY_DEBUG_PACK, ENTITY_DEBUG_FLOAT_VALUE, en, type, value);
			}

			#endif

			break;
		}
		////////////////////////////////////////
		case FLOAT_PACK_TYPE_SIGNED_ANGLE:
		////////////////////////////////////////
		{
			int
				i,
				width;

			ASSERT (float_type_database[type].pack_num_whole_bits == 3);

			ASSERT
			(
				(float_type_database[type].pack_num_fractional_bits >= 0) &&
				(float_type_database[type].pack_num_fractional_bits <= MAX_FRACTIONAL_BITS)
			);

			switch (float_type_database[type].pack_num_fractional_bits)
			{
				case 0: pack_float_0_fractional_bits (fmod (value, PI2), &i); break;
				case 1: pack_float_1_fractional_bits (fmod (value, PI2), &i); break;
				case 2: pack_float_2_fractional_bits (fmod (value, PI2), &i); break;
				case 3: pack_float_3_fractional_bits (fmod (value, PI2), &i); break;
				case 4: pack_float_4_fractional_bits (fmod (value, PI2), &i); break;
				case 5: pack_float_5_fractional_bits (fmod (value, PI2), &i); break;
				case 6: pack_float_6_fractional_bits (fmod (value, PI2), &i); break;
				case 7: pack_float_7_fractional_bits (fmod (value, PI2), &i); break;
				case 8: pack_float_8_fractional_bits (fmod (value, PI2), &i); break;
				case 9: pack_float_9_fractional_bits (fmod (value, PI2), &i); break;
				case 10: pack_float_10_fractional_bits (fmod (value, PI2), &i); break;
				case 11: pack_float_11_fractional_bits (fmod (value, PI2), &i); break;
			}

			width = 1 + float_type_database[type].pack_num_whole_bits + float_type_database[type].pack_num_fractional_bits;

			#ifdef DEBUG_PACK_OVERFLOW
			{
				int max_val = (1 << (width - 1)) - 1;
				int min_val = -max_val - 1;

				if (width < 32 && (i > max_val || i < min_val))
				{
					#ifdef DEBUG_PACK_OVERFLOW
						debug_log_pack_overflow("signed angle", get_float_type_name(type), width, i, value);
					#endif
					
					if (i > 0)
						i = max_val;
					else
						i = min_val;
					
					ASSERT(!"Overflow when packing signed float type!");
				}
			}
			#endif

			pack_signed_data (i, width);

			#if (DEBUG_MODULE_PACK_ONE || DEBUG_MODULE_PACK_ALL)

			if (float_type_database[type].debug_pack)
			{
				float
					value;

				//
				// packed debug message to match unpacked debug message
				//

				switch (float_type_database[type].pack_num_fractional_bits)
				{
					case 0: value = unpack_float_0_fractional_bits (i); break;
					case 1: value = unpack_float_1_fractional_bits (i); break;
					case 2: value = unpack_float_2_fractional_bits (i); break;
					case 3: value = unpack_float_3_fractional_bits (i); break;
					case 4: value = unpack_float_4_fractional_bits (i); break;
					case 5: value = unpack_float_5_fractional_bits (i); break;
					case 6: value = unpack_float_6_fractional_bits (i); break;
					case 7: value = unpack_float_7_fractional_bits (i); break;
					case 8: value = unpack_float_8_fractional_bits (i); break;
					case 9: value = unpack_float_9_fractional_bits (i); break;
					case 10: value = unpack_float_10_fractional_bits (i); break;
					case 11: value = unpack_float_11_fractional_bits (i); break;
				}

				debug_log_entity_args (ENTITY_DEBUG_PACK, ENTITY_DEBUG_FLOAT_VALUE, en, type, value);
			}

			#endif

			break;
		}
		////////////////////////////////////////
		case FLOAT_PACK_TYPE_UNSIGNED_ANGLE:
		////////////////////////////////////////
		{
			int
				i,
				width;

			ASSERT (value >= 0.0);

			ASSERT (float_type_database[type].pack_num_whole_bits == 3);

			ASSERT
			(
				(float_type_database[type].pack_num_fractional_bits >= 0) &&
				(float_type_database[type].pack_num_fractional_bits <= MAX_FRACTIONAL_BITS)
			);

			switch (float_type_database[type].pack_num_fractional_bits)
			{
				case 0: pack_float_0_fractional_bits (fmod (value, PI2), &i); break;
				case 1: pack_float_1_fractional_bits (fmod (value, PI2), &i); break;
				case 2: pack_float_2_fractional_bits (fmod (value, PI2), &i); break;
				case 3: pack_float_3_fractional_bits (fmod (value, PI2), &i); break;
				case 4: pack_float_4_fractional_bits (fmod (value, PI2), &i); break;
				case 5: pack_float_5_fractional_bits (fmod (value, PI2), &i); break;
				case 6: pack_float_6_fractional_bits (fmod (value, PI2), &i); break;
				case 7: pack_float_7_fractional_bits (fmod (value, PI2), &i); break;
				case 8: pack_float_8_fractional_bits (fmod (value, PI2), &i); break;
				case 9: pack_float_9_fractional_bits (fmod (value, PI2), &i); break;
				case 10: pack_float_10_fractional_bits (fmod (value, PI2), &i); break;
				case 11: pack_float_11_fractional_bits (fmod (value, PI2), &i); break;
			}

			width = float_type_database[type].pack_num_whole_bits + float_type_database[type].pack_num_fractional_bits;

			#ifdef DEBUG_PACK_OVERFLOW
			{
				int max_val = (1 << (width)) - 1;
				int min_val = 0;

				if (width < 32 && (i > max_val || i < min_val))
				{
					#ifdef DEBUG_PACK_OVERFLOW
						debug_log_pack_overflow("unsigned float angle", get_float_type_name(type), width, i, value);
					#endif
					
					if (i > 0)
						i = max_val;
					else
						i = min_val;
					
					ASSERT(!"Overflow when packing unsigned float type!");
				}
			}
			#endif
			ASSERT(!(i >> width));

			pack_unsigned_data (i, width);

			#if (DEBUG_MODULE_PACK_ONE || DEBUG_MODULE_PACK_ALL)

			if (float_type_database[type].debug_pack)
			{
				float
					value;

				//
				// packed debug message to match unpacked debug message
				//

				switch (float_type_database[type].pack_num_fractional_bits)
				{
					case 0: value = unpack_float_0_fractional_bits (i); break;
					case 1: value = unpack_float_1_fractional_bits (i); break;
					case 2: value = unpack_float_2_fractional_bits (i); break;
					case 3: value = unpack_float_3_fractional_bits (i); break;
					case 4: value = unpack_float_4_fractional_bits (i); break;
					case 5: value = unpack_float_5_fractional_bits (i); break;
					case 6: value = unpack_float_6_fractional_bits (i); break;
					case 7: value = unpack_float_7_fractional_bits (i); break;
					case 8: value = unpack_float_8_fractional_bits (i); break;
					case 9: value = unpack_float_9_fractional_bits (i); break;
					case 10: value = unpack_float_10_fractional_bits (i); break;
					case 11: value = unpack_float_11_fractional_bits (i); break;
				}

				debug_log_entity_args (ENTITY_DEBUG_PACK, ENTITY_DEBUG_FLOAT_VALUE, en, type, value);
			}

			#endif

			break;
		}
		////////////////////////////////////////
		case FLOAT_PACK_TYPE_SIGNED_VALUE:
		////////////////////////////////////////
		{
			int
				i,
				width;

			ASSERT
			(
				(float_type_database[type].pack_num_fractional_bits >= 0) &&
				(float_type_database[type].pack_num_fractional_bits <= MAX_FRACTIONAL_BITS)
			);

			switch (float_type_database[type].pack_num_fractional_bits)
			{
				case 0: pack_float_0_fractional_bits (value, &i); break;
				case 1: pack_float_1_fractional_bits (value, &i); break;
				case 2: pack_float_2_fractional_bits (value, &i); break;
				case 3: pack_float_3_fractional_bits (value, &i); break;
				case 4: pack_float_4_fractional_bits (value, &i); break;
				case 5: pack_float_5_fractional_bits (value, &i); break;
				case 6: pack_float_6_fractional_bits (value, &i); break;
				case 7: pack_float_7_fractional_bits (value, &i); break;
				case 8: pack_float_8_fractional_bits (value, &i); break;
				case 9: pack_float_9_fractional_bits (value, &i); break;
				case 10: pack_float_10_fractional_bits (value, &i); break;
				case 11: pack_float_11_fractional_bits (value, &i); break;
			}

			width = 1 + float_type_database[type].pack_num_whole_bits + float_type_database[type].pack_num_fractional_bits;

			#ifdef DEBUG_PACK_OVERFLOW
			{
				int max_val = (1 << (width - 1)) - 1;
				int min_val = -max_val - 1;

				if (width < 32 && (i > max_val || i < min_val))
				{
					#ifdef DEBUG_PACK_OVERFLOW
						debug_log_pack_overflow("signed float value", get_float_type_name(type), width, i, value);
					#endif
					
					if (i > 0)
						i = max_val;
					else
						i = min_val;
					
					ASSERT(!"Overflow when packing signed float type!");
				}
			}
			#endif
			
			pack_signed_data (i, width);

			#if (DEBUG_MODULE_PACK_ONE || DEBUG_MODULE_PACK_ALL)

			if (float_type_database[type].debug_pack)
			{
				float
					value;

				//
				// packed debug message to match unpacked debug message
				//

				switch (float_type_database[type].pack_num_fractional_bits)
				{
					case 0: value = unpack_float_0_fractional_bits (i); break;
					case 1: value = unpack_float_1_fractional_bits (i); break;
					case 2: value = unpack_float_2_fractional_bits (i); break;
					case 3: value = unpack_float_3_fractional_bits (i); break;
					case 4: value = unpack_float_4_fractional_bits (i); break;
					case 5: value = unpack_float_5_fractional_bits (i); break;
					case 6: value = unpack_float_6_fractional_bits (i); break;
					case 7: value = unpack_float_7_fractional_bits (i); break;
					case 8: value = unpack_float_8_fractional_bits (i); break;
					case 9: value = unpack_float_9_fractional_bits (i); break;
					case 10: value = unpack_float_10_fractional_bits (i); break;
					case 11: value = unpack_float_11_fractional_bits (i); break;
				}

				debug_log_entity_args (ENTITY_DEBUG_PACK, ENTITY_DEBUG_FLOAT_VALUE, en, type, value);
			}

			#endif

			break;
		}
		////////////////////////////////////////
		case FLOAT_PACK_TYPE_UNSIGNED_VALUE:
		////////////////////////////////////////
		{
			int
				i,
				width;

			ASSERT (value >= 0.0);

			ASSERT
			(
				(float_type_database[type].pack_num_fractional_bits >= 0) &&
				(float_type_database[type].pack_num_fractional_bits <= MAX_FRACTIONAL_BITS)
			);

			switch (float_type_database[type].pack_num_fractional_bits)
			{
				case 0: pack_float_0_fractional_bits (value, &i); break;
				case 1: pack_float_1_fractional_bits (value, &i); break;
				case 2: pack_float_2_fractional_bits (value, &i); break;
				case 3: pack_float_3_fractional_bits (value, &i); break;
				case 4: pack_float_4_fractional_bits (value, &i); break;
				case 5: pack_float_5_fractional_bits (value, &i); break;
				case 6: pack_float_6_fractional_bits (value, &i); break;
				case 7: pack_float_7_fractional_bits (value, &i); break;
				case 8: pack_float_8_fractional_bits (value, &i); break;
				case 9: pack_float_9_fractional_bits (value, &i); break;
				case 10: pack_float_10_fractional_bits (value, &i); break;
				case 11: pack_float_11_fractional_bits (value, &i); break;
			}

			width = float_type_database[type].pack_num_whole_bits + float_type_database[type].pack_num_fractional_bits;

			#ifdef DEBUG_PACK_OVERFLOW
			{
				int max_val = (1 << (width)) - 1;
				int min_val = 0;

				if (width < 32 && (i > max_val || i < min_val))
				{
					#ifdef DEBUG_PACK_OVERFLOW
						debug_log_pack_overflow("unsigned float value", get_float_type_name(type), width, i, value);
					#endif
					
					if (i > 0)
						i = max_val;
					else
						i = min_val;
					
					ASSERT(!"Overflow when packing unsigned float type!");
				}
			}
			#endif
			ASSERT(!(i >> width));

			pack_unsigned_data (i, width);

			#if (DEBUG_MODULEPACK_ONE || DEBUG_MODULE_PACK_ALL)

			if (float_type_database[type].debug_pack)
			{
				float
					value;

				//
				// packed debug message to match unpacked debug message
				//

				switch (float_type_database[type].pack_num_fractional_bits)
				{
					case 0: value = unpack_float_0_fractional_bits (i); break;
					case 1: value = unpack_float_1_fractional_bits (i); break;
					case 2: value = unpack_float_2_fractional_bits (i); break;
					case 3: value = unpack_float_3_fractional_bits (i); break;
					case 4: value = unpack_float_4_fractional_bits (i); break;
					case 5: value = unpack_float_5_fractional_bits (i); break;
					case 6: value = unpack_float_6_fractional_bits (i); break;
					case 7: value = unpack_float_7_fractional_bits (i); break;
					case 8: value = unpack_float_8_fractional_bits (i); break;
					case 9: value = unpack_float_9_fractional_bits (i); break;
					case 10: value = unpack_float_10_fractional_bits (i); break;
					case 11: value = unpack_float_11_fractional_bits (i); break;
				}

				debug_log_entity_args (ENTITY_DEBUG_PACK, ENTITY_DEBUG_FLOAT_VALUE, en, type, value);
			}

			#endif

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			debug_fatal ("Invalid float pack type = %d", float_type_database[type].pack_type);

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float unpack_float_value (entity *en, float_types type)
{
	float
		value;

	ASSERT ((type >= 0) && (type < NUM_FLOAT_TYPES));

	switch (float_type_database[type].pack_type)
	{
		////////////////////////////////////////
		case FLOAT_PACK_TYPE_UNPACKED:
		////////////////////////////////////////
		{
			int
				i;

			i = unpack_unsigned_data (32);

			value = *(float *)&i;

			break;
		}
		////////////////////////////////////////
		case FLOAT_PACK_TYPE_SIGNED_ANGLE:
		////////////////////////////////////////
		{
			int
				i,
				width;

			ASSERT (float_type_database[type].pack_num_whole_bits == 3);

			ASSERT
			(
				(float_type_database[type].pack_num_fractional_bits >= 0) &&
				(float_type_database[type].pack_num_fractional_bits <= MAX_FRACTIONAL_BITS)
			);

			width = float_type_database[type].pack_num_whole_bits + float_type_database[type].pack_num_fractional_bits;

			i = unpack_signed_data (width + 1);

			switch (float_type_database[type].pack_num_fractional_bits)
			{
				case 0: value = unpack_float_0_fractional_bits (i); break;
				case 1: value = unpack_float_1_fractional_bits (i); break;
				case 2: value = unpack_float_2_fractional_bits (i); break;
				case 3: value = unpack_float_3_fractional_bits (i); break;
				case 4: value = unpack_float_4_fractional_bits (i); break;
				case 5: value = unpack_float_5_fractional_bits (i); break;
				case 6: value = unpack_float_6_fractional_bits (i); break;
				case 7: value = unpack_float_7_fractional_bits (i); break;
				case 8: value = unpack_float_8_fractional_bits (i); break;
				case 9: value = unpack_float_9_fractional_bits (i); break;
				case 10: value = unpack_float_10_fractional_bits (i); break;
				case 11: value = unpack_float_11_fractional_bits (i); break;
			}

			break;
		}
		////////////////////////////////////////
		case FLOAT_PACK_TYPE_UNSIGNED_ANGLE:
		////////////////////////////////////////
		{
			int
				i,
				width;

			ASSERT (float_type_database[type].pack_num_whole_bits == 3);

			ASSERT
			(
				(float_type_database[type].pack_num_fractional_bits >= 0) &&
				(float_type_database[type].pack_num_fractional_bits <= MAX_FRACTIONAL_BITS)
			);

			width = float_type_database[type].pack_num_whole_bits + float_type_database[type].pack_num_fractional_bits;

			i = unpack_unsigned_data (width);

			switch (float_type_database[type].pack_num_fractional_bits)
			{
				case 0: value = unpack_float_0_fractional_bits (i); break;
				case 1: value = unpack_float_1_fractional_bits (i); break;
				case 2: value = unpack_float_2_fractional_bits (i); break;
				case 3: value = unpack_float_3_fractional_bits (i); break;
				case 4: value = unpack_float_4_fractional_bits (i); break;
				case 5: value = unpack_float_5_fractional_bits (i); break;
				case 6: value = unpack_float_6_fractional_bits (i); break;
				case 7: value = unpack_float_7_fractional_bits (i); break;
				case 8: value = unpack_float_8_fractional_bits (i); break;
				case 9: value = unpack_float_9_fractional_bits (i); break;
				case 10: value = unpack_float_10_fractional_bits (i); break;
				case 11: value = unpack_float_11_fractional_bits (i); break;
			}

			break;
		}
		////////////////////////////////////////
		case FLOAT_PACK_TYPE_SIGNED_VALUE:
		////////////////////////////////////////
		{
			int
				i,
				width;

			ASSERT
			(
				(float_type_database[type].pack_num_fractional_bits >= 0) &&
				(float_type_database[type].pack_num_fractional_bits <= MAX_FRACTIONAL_BITS)
			);

			width = float_type_database[type].pack_num_whole_bits + float_type_database[type].pack_num_fractional_bits;

			i = unpack_signed_data (width + 1);

			switch (float_type_database[type].pack_num_fractional_bits)
			{
				case 0: value = unpack_float_0_fractional_bits (i); break;
				case 1: value = unpack_float_1_fractional_bits (i); break;
				case 2: value = unpack_float_2_fractional_bits (i); break;
				case 3: value = unpack_float_3_fractional_bits (i); break;
				case 4: value = unpack_float_4_fractional_bits (i); break;
				case 5: value = unpack_float_5_fractional_bits (i); break;
				case 6: value = unpack_float_6_fractional_bits (i); break;
				case 7: value = unpack_float_7_fractional_bits (i); break;
				case 8: value = unpack_float_8_fractional_bits (i); break;
				case 9: value = unpack_float_9_fractional_bits (i); break;
				case 10: value = unpack_float_10_fractional_bits (i); break;
				case 11: value = unpack_float_11_fractional_bits (i); break;
			}

			break;
		}
		////////////////////////////////////////
		case FLOAT_PACK_TYPE_UNSIGNED_VALUE:
		////////////////////////////////////////
		{
			int
				i,
				width;

			ASSERT
			(
				(float_type_database[type].pack_num_fractional_bits >= 0) &&
				(float_type_database[type].pack_num_fractional_bits <= MAX_FRACTIONAL_BITS)
			);

			width = float_type_database[type].pack_num_whole_bits + float_type_database[type].pack_num_fractional_bits;

			i = unpack_unsigned_data (width);

			switch (float_type_database[type].pack_num_fractional_bits)
			{
				case 0: value = unpack_float_0_fractional_bits (i); break;
				case 1: value = unpack_float_1_fractional_bits (i); break;
				case 2: value = unpack_float_2_fractional_bits (i); break;
				case 3: value = unpack_float_3_fractional_bits (i); break;
				case 4: value = unpack_float_4_fractional_bits (i); break;
				case 5: value = unpack_float_5_fractional_bits (i); break;
				case 6: value = unpack_float_6_fractional_bits (i); break;
				case 7: value = unpack_float_7_fractional_bits (i); break;
				case 8: value = unpack_float_8_fractional_bits (i); break;
				case 9: value = unpack_float_9_fractional_bits (i); break;
				case 10: value = unpack_float_10_fractional_bits (i); break;
				case 11: value = unpack_float_11_fractional_bits (i); break;
			}

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			debug_fatal ("Invalid float pack type = %d", float_type_database[type].pack_type);

			break;
		}
	}

	#if (DEBUG_MODULE_PACK_ONE || DEBUG_MODULE_PACK_ALL)

	if (float_type_database[type].debug_pack)
	{
		debug_log_entity_args (ENTITY_DEBUG_UNPACK, ENTITY_DEBUG_FLOAT_VALUE, en, type, value);
	}

	#endif

	return (value);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void pack_float_type (float_types type)
{
	ASSERT ((type >= 0) && (type < NUM_FLOAT_TYPES));

	#if (DEBUG_MODULE_PACK_ONE || DEBUG_MODULE_PACK_ALL)

	if (float_type_database[type].debug_pack)
	{
		debug_log_entity_args (ENTITY_DEBUG_PACK, ENTITY_DEBUG_FLOAT_TYPE, NULL, type);
	}

	#endif

	ASSERT(!(type >> NUM_FLOAT_TYPE_PACK_BITS));

	pack_unsigned_data (type, NUM_FLOAT_TYPE_PACK_BITS);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float_types unpack_float_type (void)
{
	float_types
		type;

	type = unpack_unsigned_data (NUM_FLOAT_TYPE_PACK_BITS);

	ASSERT ((type >= 0) && (type < NUM_FLOAT_TYPES));

	#if (DEBUG_MODULE_PACK_ONE || DEBUG_MODULE_PACK_ALL)

	if (float_type_database[type].debug_pack)
	{
		debug_log_entity_args (ENTITY_DEBUG_UNPACK, ENTITY_DEBUG_FLOAT_TYPE, NULL, type);
	}

	#endif

	return (type);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
