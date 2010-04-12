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
keysite_data
   keysite_database[NUM_ENTITY_SUB_TYPE_KEYSITES] =
   {

      ////////////////////////////////////////
      //
      // ENTITY_SUB_TYPE_KEYSITE_AIRBASE
      //
      ////////////////////////////////////////

      {
         "Airbase",
         "Airbase",

			{													// Supply usage
				0.0,											//    air/ground supply, ignore
				0.0,											//    air/air supply, ignore
				-0.2f, 										// 	ammo
				-0.4f, 										// 	fuel
			},

			1.0,												// importance
			0.3f,												// minimum efficiency
			80.0 * KILOMETRE,								// importance radius
			400.0 * KILOMETRE,							// air coverage radius
			1000.0,											// recon distance
			80.0,												// sector side max value

			MAP_LAYER_CONTROL_KEYSITES,				// map layer type
			MAP_ICON_AIRBASE,								// map icon
			FALSE,											// align with terrain (buildings)
			TRUE,												// unique name
			FALSE,											// hidden by fog
			KEYSITE_AIR_FORCE_CAPACITY_LARGE,		// air force capacity
			TRUE,												// report ammo level
			TRUE,												// report fuel level

			3,													// task assign count
			2,													// task reserve count
			TRUE,												// requires CAP
			FALSE,											// requires BARCAP
			TRUE,												// repairable

			TRUE,												// OCA Target
			TRUE,												// Recon Target
			TRUE,												// Ground Strike Target
			FALSE,											// Ship Strike Target
			TRUE,												// Troop Insertion Target
			TRUE,												// Campaign Objective
      },

      ////////////////////////////////////////
      //
      // ENTITY_SUB_TYPE_KEYSITE_ANCHORAGE
      //
      ////////////////////////////////////////

      {
         "Carrier",
         "Carrier",

			{													// Supply usage
				0.0,											//    air/ground supply, ignore
				0.0,											//    air/air supply, ignore
				0.0, 											// 	ammo
				0.0, 											// 	fuel
			},

			1.0,												// importance
			0.3f,												// minimum efficiency
			60.0 * KILOMETRE,								// importance radius
			100.0 * KILOMETRE,							// air coverage radius
			280.0,											// recon distance
			50.0,												// sector side max value

			MAP_LAYER_CONTROL_SHIPS,					// map layer type
			MAP_ICON_CARRIER,								// map icon
			FALSE,											// align with terrain (buildings)
			TRUE,												// unique name
			TRUE,												// hidden by fog
			KEYSITE_AIR_FORCE_CAPACITY_SMALL,		// air force capacity
			TRUE,												// report ammo level
			TRUE,												// report fuel level

			1,													// task assign count
			1,													// task reserve count
			FALSE,											// requires CAP
			TRUE,												// requires BARCAP
			FALSE,											// repairable

			TRUE,												// OCA Target
			TRUE,												// Recon Target
			FALSE,											// Ground Strike Target
			TRUE,												// Ship Strike Target
			FALSE,											// Troop Insertion Target
			TRUE,												// Campaign Objective
      },

      ////////////////////////////////////////
      //
      // ENTITY_SUB_TYPE_KEYSITE_FACTORY
      //
      ////////////////////////////////////////

      {
         "Factory",
         "Factory",

			{													// Supply usage
				0.0,											//    air/ground supply, ignore
				0.0,											//    air/air supply, ignore
				+1.0,											// 	ammo
				+0.0,											// 	fuel
			},

			0.5,												// importance
			0.3f,												// minimum efficiency
			40.0 * KILOMETRE,								// importance radius
			0.0 * KILOMETRE,								// air coverage radius
			300.0,											// recon distance
			20.0,												// sector side max value

			MAP_LAYER_CONTROL_KEYSITES,				// map layer type
			MAP_ICON_BUILDING,							// map icon
			FALSE,											// align with terrain (buildings)
			FALSE,											// unique name
			FALSE,											// hidden by fog
			KEYSITE_AIR_FORCE_CAPACITY_NONE,			// air force capacity
			TRUE,												// report ammo level
			FALSE,											// report fuel level

			0,													// task assign count
			0,													// task reserve count
			FALSE,											// requires CAP 
			FALSE,											// requires BARCAP
			TRUE,												// repairable

			FALSE,											// OCA Target
			FALSE,											// Recon Target
			TRUE,												// Ground Strike Target
			FALSE,											// Ship Strike Target
			TRUE,												// Troop Insertion Target
			FALSE,											// Campaign Objective
      },

      ////////////////////////////////////////
      //
      // ENTITY_SUB_TYPE_KEYSITE_FARP
      //
      ////////////////////////////////////////

      {
         "FARP",
         "FARP",

			{													// Supply usage
				0.0,											//    air/ground supply, ignore
				0.0,											//    air/air supply, ignore
				-0.05f, 										// 	ammo
				-0.03f, 										// 	fuel
			},

			0.4f,												// importance
			0.3f,												// minimum efficiency
			40.0 * KILOMETRE,								// importance radius
			100.0 * KILOMETRE,							// air coverage radius
			320.0,											// recon distance
			40.0,												// sector side max value

			MAP_LAYER_CONTROL_KEYSITES,				// map layer type
			MAP_ICON_FARP,									// map icon
			TRUE,												// align with terrain (buildings)
			FALSE,											// unique name
			TRUE,												// hidden by fog
			KEYSITE_AIR_FORCE_CAPACITY_SMALL,		// air force capacity
			TRUE,												// report ammo level
			TRUE,												// report fuel level

			1,													// task assign count
			1,													// task reserve count
			TRUE,												// requires CAP 
			FALSE,											// requires BARCAP
			TRUE,												// repairable

			FALSE,											// OCA Target
			TRUE,												// Recon Target
			TRUE,												// Ground Strike Target
			FALSE,											// Ship Strike Target
			TRUE,												// Troop Insertion Target
			FALSE,											// Campaign Objective
      },

      ////////////////////////////////////////
      //
      // ENTITY_SUB_TYPE_KEYSITE_MILITARY_BASE
      //
      ////////////////////////////////////////

      {
         "Military Base",
         "Military Base",

			{													// Supply usage
				0.0,											//    air/ground supply, ignore
				0.0,											//    air/air supply, ignore
				-0.2f,											// 	ammo
				-0.2f,											// 	fuel
			},

			0.8f,												// importance
			0.3f,												// minimum efficiency
			30.0 * KILOMETRE,								// importance radius
			0.0 * KILOMETRE,								// air coverage radius
			450.0,											// recon distance
			30.0,												// sector side max value

			MAP_LAYER_CONTROL_KEYSITES,				// map layer type
			MAP_ICON_BUILDING,							// map icon
			FALSE,											// align with terrain (buildings)
			FALSE,											// unique name
			TRUE,												// hidden by fog
			KEYSITE_AIR_FORCE_CAPACITY_NONE,			// air force capacity
			TRUE,												// report ammo level
			TRUE,												// report fuel level

			0,													// task assign count
			0,													// task reserve count
			FALSE,											// requires CAP 
			FALSE,											// requires BARCAP
			TRUE,												// repairable

			FALSE,											// OCA Target
			TRUE,												// Recon Target
			TRUE,												// Ground Strike Target
			FALSE,											// Ship Strike Target
			TRUE,												// Troop Insertion Target
			TRUE,												// Campaign Objective
      },

      ////////////////////////////////////////
      //
      // ENTITY_SUB_TYPE_KEYSITE_PORT
      //
      ////////////////////////////////////////

      {
         "Port",
         "Port",

			{													// Supply usage
				0.0,											//    air/ground supply, ignore
				0.0,											//    air/air supply, ignore
				+0.2f, 										// 	ammo
				+0.2f, 										// 	fuel
			},

			0.2f,												// importance
			0.3f,												// minimum efficiency
			20.0 * KILOMETRE,								// importance radius
			0.0 * KILOMETRE,								// air coverage radius
			700.0,											// recon distance
			20.0,												// sector side max value

			MAP_LAYER_CONTROL_KEYSITES,				// map layer type
			MAP_ICON_BUILDING,							// map icon
			FALSE,											// align with terrain (buildings)
			FALSE,											// unique name
			FALSE,											// hidden by fog
			KEYSITE_AIR_FORCE_CAPACITY_NONE,			// air force capacity
			TRUE,												// report ammo level
			TRUE,												// report fuel level

			0,													// task assign count
			0,													// task reserve count
			FALSE,											// requires CAP 
			FALSE,											// requires BARCAP
			FALSE,											// repairable

			FALSE,											// OCA Target
			FALSE,											// Recon Target
			TRUE,												// Ground Strike Target
			FALSE,											// Ship Strike Target
			FALSE,											// Troop Insertion Target
			FALSE,											// Campaign Objective
      },

      ////////////////////////////////////////
      //
      // ENTITY_SUB_TYPE_KEYSITE_POWER_STATION
      //
      ////////////////////////////////////////

      {
         "Power Station",
         "Power Station",

			{													// Supply usage
				0.0,											//    air/ground supply, ignore
				0.0,											//    air/air supply, ignore
				0.0, 											// 	ammo
				-0.5, 										// 	fuel
			},

			0.3f,												// importance
			0.3f,												// minimum efficiency
			30.0 * KILOMETRE,								// importance radius
			0.0 * KILOMETRE,								// air coverage radius
			400.0,											// recon distance
			0.0,												// sector side max value

			MAP_LAYER_CONTROL_KEYSITES,				// map layer type
			MAP_ICON_POWER_STATION,						// map icon
			FALSE,											// align with terrain (buildings)
			FALSE,											// unique name
			TRUE,												// hidden by fog
			KEYSITE_AIR_FORCE_CAPACITY_NONE,			// air force capacity
			FALSE,											// report ammo level
			TRUE,												// report fuel level

			0,													// task assign count
			0,													// task reserve count
			FALSE,											// requires CAP
			FALSE,											// requires BARCAP
			FALSE,											// repairable

			FALSE,											// OCA Target
			TRUE,												// Recon Target
			TRUE,												// Ground Strike Target
			FALSE,											// Ship Strike Target
			FALSE,											// Troop Insertion Target
			TRUE,												// Campaign Objective
      },

      ////////////////////////////////////////
      //
      // ENTITY_SUB_TYPE_KEYSITE_OIL_REFINERY
      //
      ////////////////////////////////////////

      {
         "Oil Refinery",
         "Refinery",

			{													// Supply usage
				0.0,											//    air/ground supply, ignore
				0.0,											//    air/air supply, ignore
				0.0, 											// 	ammo
				+1.0, 										// 	fuel
			},

			0.4f,												// importance
			0.3f,												// minimum efficiency
			30.0 * KILOMETRE,								// importance radius
			0.0 * KILOMETRE,								// air coverage radius
			800.0,											// recon distance
			20.0,												// sector side max value

			MAP_LAYER_CONTROL_KEYSITES,				// map layer type
			MAP_ICON_OIL_REFINERY,						// map icon
			FALSE,											// align with terrain (buildings)
			FALSE,											// unique name
			TRUE,												// hidden by fog
			KEYSITE_AIR_FORCE_CAPACITY_NONE,			// air force capacity
			FALSE,											// report ammo level
			TRUE,												// report fuel level

			0,													// task assign count
			0,													// task reserve count
			FALSE,											// requires CAP
			FALSE,											// requires BARCAP
			FALSE,											// repairable

			FALSE,											// OCA Target
			TRUE,												// Recon Target
			TRUE,												// Ground Strike Target
			FALSE,											// Ship Strike Target
			FALSE,											// Troop Insertion Target
			TRUE,												// Campaign Objective
      },

      ////////////////////////////////////////
      //
      // ENTITY_SUB_TYPE_KEYSITE_RADIO_TRANSMITTER
      //
      ////////////////////////////////////////

      {
         "Radio Transmitter",
         "Transmitter",

			{													// Supply usage
				0.0,											//    air/ground supply, ignore
				0.0,											//    air/air supply, ignore
				0.0, 											// 	ammo
				0.0,	 										// 	fuel
			},

			0.5f,												// importance
			0.3f,												// minimum efficiency
			30.0 * KILOMETRE,								// importance radius
			0.0 * KILOMETRE,								// air coverage radius
			250.0,											// recon distance
			30.0,												// sector side max value

			MAP_LAYER_CONTROL_KEYSITES,				// map layer type
			MAP_ICON_RADIO_TRANSMITTER,				// map icon
			FALSE,											// align with terrain (buildings)
			FALSE,											// unique name
			TRUE,												// hidden by fog
			KEYSITE_AIR_FORCE_CAPACITY_NONE,			// air force capacity
			FALSE,											// report ammo level
			FALSE,											// report fuel level

			0,													// task assign count
			0,													// task reserve count
			FALSE,											// requires CAP 
			FALSE,											// requires BARCAP
			FALSE,											// repairable

			FALSE,											// OCA Target
			TRUE,												// Recon Target
			TRUE,												// Ground Strike Target
			FALSE,											// Ship Strike Target
			FALSE,											// Troop Insertion Target
			FALSE,											// Campaign Objective
      },
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
