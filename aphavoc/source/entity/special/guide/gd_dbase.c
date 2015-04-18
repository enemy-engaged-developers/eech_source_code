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

//VJ 040321 GWUT change
//remove "const" from definition
guide_data
   guide_database[NUM_ENTITY_SUB_TYPE_GUIDES] =
	{
      ////////////////////////////////////////
      //
      // ENTITY_SUB_TYPE_GUIDE_NAVIGATION_DIRECT
      //
      ////////////////////////////////////////
      {
			TRUE,															// evade fire
			TRUE,															// follow formation
			GUIDE_POSITION_WAYPOINT,								// position type
			GUIDE_TERRAIN_FOLLOW_CRUISE_ALTITUDE,				// terrain check

			{
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_RADIUS
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_HEADING
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_ALTITUDE
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_TRANSMIT_DATA
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_LAST_TO_REACH
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_WEAPON_VECTOR
			}
      },
      ////////////////////////////////////////
      //
      // ENTITY_SUB_TYPE_GUIDE_NAVIGATION_VIRTUAL
      //
      ////////////////////////////////////////
      {
			TRUE,															// evade fire
			TRUE,															// follow formation
			GUIDE_POSITION_RELATIVE_WORLD_SPACE,				// position type
			GUIDE_TERRAIN_FOLLOW_CRUISE_ALTITUDE,				// terrain check

			{
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_RADIUS
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_HEADING
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_ALTITUDE
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_TRANSMIT_DATA
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_LAST_TO_REACH
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_WEAPON_VECTOR
			}
      },
      ////////////////////////////////////////
      //
      // ENTITY_SUB_TYPE_GUIDE_NAVIGATION_ROUTED
      //
      ////////////////////////////////////////
      {
			FALSE,														// evade fire
			TRUE,															// follow formation
			GUIDE_POSITION_WAYPOINT,								// position type
			GUIDE_TERRAIN_FOLLOW_NONE,								// terrain check

			{
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_RADIUS
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_HEADING
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_ALTITUDE
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_TRANSMIT_DATA
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_LAST_TO_REACH
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_WEAPON_VECTOR
			}
      },
      ////////////////////////////////////////
      //
      // ENTITY_SUB_TYPE_GUIDE_NAVIGATION_ALTITUDE
      //
      ////////////////////////////////////////
      {
			FALSE,														// evade fire
			TRUE,															// follow formation
			GUIDE_POSITION_WAYPOINT,								// position type
			GUIDE_TERRAIN_FOLLOW_NONE,								// terrain check

			{
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_RADIUS
				{ FALSE,		0.0 },							// GUIDE_CRITERIA_HEADING
				{ TRUE,			0.5 },									// GUIDE_CRITERIA_ALTITUDE
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_TRANSMIT_DATA
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_LAST_TO_REACH
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_WEAPON_VECTOR
			}
      },
      ////////////////////////////////////////
      //
      // ENTITY_SUB_TYPE_GUIDE_LANDING_DIRECT
      //
      ////////////////////////////////////////
      {
			FALSE,														// evade fire
			TRUE,															// follow formation
			GUIDE_POSITION_WAYPOINT,								// position type
			GUIDE_TERRAIN_FOLLOW_NONE,								// terrain check

			{
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_RADIUS
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_HEADING
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_ALTITUDE
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_TRANSMIT_DATA
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_LAST_TO_REACH
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_WEAPON_VECTOR
			}
      },
      ////////////////////////////////////////
      //
      // ENTITY_SUB_TYPE_GUIDE_LANDED
      //
      ////////////////////////////////////////
      {
			FALSE,														// evade fire
			TRUE,															// follow formation
			GUIDE_POSITION_WAYPOINT,								// position type
			GUIDE_TERRAIN_FOLLOW_NONE,								// terrain check
//VJ FARP bug, date: 18-mar-03
			{
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_RADIUS
//VJ FARP bug: changed heading from 1 to 30, additional movement seems to stop bunny hopping 
//VJ 03/10/28: FARP bug: changed heading to 360, meaing all directions count 
				{ TRUE,		rad (360.0) },							// GUIDE_CRITERIA_HEADING				
//VJ FARP bug: changed altitude boundary from 0.005 to 0.5 m stops bunny hopping 
				{ TRUE,		0.5 },									// GUIDE_CRITERIA_ALTITUDE
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_TRANSMIT_DATA
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_LAST_TO_REACH
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_WEAPON_VECTOR
			}
//VJ FARP bug, date: 18-mar-03, end
      },
      ////////////////////////////////////////
      //
		//	ENTITY_SUB_TYPE_GUIDE_ATTACK_AA_MOVE_SIX,
      //
      ////////////////////////////////////////
      {
			TRUE,															// evade fire
			FALSE,														// follow formation
			GUIDE_POSITION_ABSOLUTE,								// position type
			GUIDE_TERRAIN_FOLLOW_CRUISE_ALTITUDE,				// terrain check

			{
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_RADIUS
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_HEADING
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_ALTITUDE
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_TRANSMIT_DATA
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_LAST_TO_REACH
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_WEAPON_VECTOR
			}
      },
      ////////////////////////////////////////
      //
		//	ENTITY_SUB_TYPE_GUIDE_ATTACK_AA_MOVE_CIRCLE,
      //
      ////////////////////////////////////////
      {
			TRUE,															// evade fire
			FALSE,														// follow formation
			GUIDE_POSITION_ABSOLUTE,								// position type
			GUIDE_TERRAIN_FOLLOW_CRUISE_ALTITUDE,				// terrain check

			{
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_RADIUS
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_HEADING
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_ALTITUDE
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_TRANSMIT_DATA
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_LAST_TO_REACH
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_WEAPON_VECTOR
			}
      },
      ////////////////////////////////////////
      //
		//	ENTITY_SUB_TYPE_GUIDE_ATTACK_AA_FIRE_INTERCEPT,
      //
      ////////////////////////////////////////
      {
			FALSE,														// evade fire
			FALSE,														// follow formation
			GUIDE_POSITION_RELATIVE_OBJECT_SPACE,				// position type
			GUIDE_TERRAIN_FOLLOW_CRUISE_ALTITUDE,				// terrain check

			{
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_RADIUS
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_HEADING
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_ALTITUDE
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_TRANSMIT_DATA
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_LAST_TO_REACH
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_WEAPON_VECTOR
			}
      },
      ////////////////////////////////////////
      //
		//	ENTITY_SUB_TYPE_GUIDE_ATTACK_AG_APPROACH,
      //
      ////////////////////////////////////////
      {
			TRUE,															// evade fire
			FALSE,														// follow formation
			GUIDE_POSITION_ABSOLUTE,								// position type
			GUIDE_TERRAIN_FOLLOW_ATTACK_ALTITUDE,				// terrain check

			{
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_RADIUS
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_HEADING
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_ALTITUDE
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_TRANSMIT_DATA
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_LAST_TO_REACH
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_WEAPON_VECTOR
			}
      },
      ////////////////////////////////////////
      //
		//	ENTITY_SUB_TYPE_GUIDE_ATTACK_AG_SEEK_COVER,
      //
      ////////////////////////////////////////
      {
			TRUE,															// evade fire
			FALSE,														// follow formation
			GUIDE_POSITION_ABSOLUTE,								// position type
			GUIDE_TERRAIN_FOLLOW_ATTACK_ALTITUDE,				// terrain check

			{
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_RADIUS
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_HEADING
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_ALTITUDE
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_TRANSMIT_DATA
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_LAST_TO_REACH
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_WEAPON_VECTOR
			}
      },
      ////////////////////////////////////////
      //
		//	ENTITY_SUB_TYPE_GUIDE_ATTACK_AG_FLY_TO_COVER,
      //
      ////////////////////////////////////////
      {
			TRUE,															// evade fire
			FALSE,														// follow formation
			GUIDE_POSITION_ABSOLUTE,								// position type
			GUIDE_TERRAIN_FOLLOW_ATTACK_ALTITUDE,				// terrain check

			{
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_RADIUS
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_HEADING
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_ALTITUDE
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_TRANSMIT_DATA
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_LAST_TO_REACH
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_WEAPON_VECTOR
			}
      },
      ////////////////////////////////////////
      //
		//	ENTITY_SUB_TYPE_GUIDE_ATTACK_AG_TAKE_COVER,
      //
      ////////////////////////////////////////
      {
			TRUE,															// evade fire
			FALSE,														// follow formation
			GUIDE_POSITION_ABSOLUTE,								// position type
			GUIDE_TERRAIN_FOLLOW_NONE,								// terrain check

			{
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_RADIUS
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_HEADING
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_ALTITUDE
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_TRANSMIT_DATA
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_LAST_TO_REACH
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_WEAPON_VECTOR
			}
      },
      ////////////////////////////////////////
      //
		//	ENTITY_SUB_TYPE_GUIDE_ATTACK_AG_CLIMB,
      //
      ////////////////////////////////////////
      {
			TRUE,															// evade fire
			FALSE,														// follow formation
			GUIDE_POSITION_ABSOLUTE,								// position type
			GUIDE_TERRAIN_FOLLOW_ATTACK_ALTITUDE,				// terrain check

			{
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_RADIUS
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_HEADING
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_ALTITUDE
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_TRANSMIT_DATA
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_LAST_TO_REACH
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_WEAPON_VECTOR
			}
      },
      ////////////////////////////////////////
      //
		//	ENTITY_SUB_TYPE_GUIDE_ATTACK_AG_DIVE,
      //
      ////////////////////////////////////////
      {
			TRUE,															// evade fire
			FALSE,														// follow formation
			GUIDE_POSITION_ABSOLUTE,								// position type
			GUIDE_TERRAIN_FOLLOW_CRUISE_ALTITUDE,				// terrain check

			{
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_RADIUS
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_HEADING
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_ALTITUDE
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_TRANSMIT_DATA
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_LAST_TO_REACH
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_WEAPON_VECTOR
			}
      },
      ////////////////////////////////////////
      //
		//	ENTITY_SUB_TYPE_GUIDE_ATTACK_AG_FIRE,
      //
      ////////////////////////////////////////
      {
			TRUE,															// evade fire
			FALSE,														// follow formation
			GUIDE_POSITION_ABSOLUTE,								// position type
			GUIDE_TERRAIN_FOLLOW_NONE,								// terrain check

			{
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_RADIUS
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_HEADING
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_ALTITUDE
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_TRANSMIT_DATA
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_LAST_TO_REACH
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_WEAPON_VECTOR
			}
      },
      ////////////////////////////////////////
      //
		//	ENTITY_SUB_TYPE_GUIDE_ATTACK_AG_FIRE_VIRTUAL,
      //
      ////////////////////////////////////////
      {
			TRUE,															// evade fire
			FALSE,														// follow formation
			GUIDE_POSITION_RELATIVE_OBJECT_SPACE,				// position type
			GUIDE_TERRAIN_FOLLOW_NONE,								// terrain check

			{
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_RADIUS
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_HEADING
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_ALTITUDE
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_TRANSMIT_DATA
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_LAST_TO_REACH
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_WEAPON_VECTOR
			}
      },
      ////////////////////////////////////////
      //
		//	ENTITY_SUB_TYPE_GUIDE_ATTACK_AG_DISENGAGE,
      //
      ////////////////////////////////////////
      {
			FALSE,														// evade fire
			FALSE,														// follow formation
			GUIDE_POSITION_ABSOLUTE,								// position type
			GUIDE_TERRAIN_FOLLOW_NONE,								// terrain check

			{
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_RADIUS
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_HEADING
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_ALTITUDE
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_TRANSMIT_DATA
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_LAST_TO_REACH
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_WEAPON_VECTOR
			}
      },
      ////////////////////////////////////////
      //
		//	ENTITY_SUB_TYPE_GUIDE_ATTACK_AG_DISENGAGE_VIRTUAL,
      //
      ////////////////////////////////////////
      {
			FALSE,														// evade fire
			FALSE,														// follow formation
			GUIDE_POSITION_RELATIVE_OBJECT_SPACE,				// position type
			GUIDE_TERRAIN_FOLLOW_NONE,								// terrain check

			{
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_RADIUS
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_HEADING
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_ALTITUDE
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_TRANSMIT_DATA
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_LAST_TO_REACH
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_WEAPON_VECTOR
			}
      },
      ////////////////////////////////////////
      //
		//	ENTITY_SUB_TYPE_GUIDE_ATTACK_AG_EGRESS,
      //
      ////////////////////////////////////////
      {
			TRUE,															// evade fire
			FALSE,														// follow formation
			GUIDE_POSITION_ABSOLUTE,								// position type
			GUIDE_TERRAIN_FOLLOW_ATTACK_ALTITUDE,				// terrain check

			{
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_RADIUS
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_HEADING
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_ALTITUDE
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_TRANSMIT_DATA
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_LAST_TO_REACH
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_WEAPON_VECTOR
			}
      },

      ////////////////////////////////////////
      //
		//	ENTITY_SUB_TYPE_GUIDE_ATTACK_AG_HASTY_FIRE,
      //
      ////////////////////////////////////////
      {
			TRUE,															// evade fire
			FALSE,														// follow formation
			GUIDE_POSITION_ABSOLUTE,								// position type
			GUIDE_TERRAIN_FOLLOW_NONE,								// terrain check

			{
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_RADIUS
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_HEADING
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_ALTITUDE
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_TRANSMIT_DATA
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_LAST_TO_REACH
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_WEAPON_VECTOR
			}
      },

      ////////////////////////////////////////
      //
		//	ENTITY_SUB_TYPE_GUIDE_ATTACK_AG_HASTY_TAKE_COVER,
      //
      ////////////////////////////////////////
      {
			TRUE,															// evade fire
			FALSE,														// follow formation
			GUIDE_POSITION_ABSOLUTE,								// position type
			GUIDE_TERRAIN_FOLLOW_NONE,								// terrain check

			{
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_RADIUS
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_HEADING
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_ALTITUDE
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_TRANSMIT_DATA
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_LAST_TO_REACH
				{ FALSE,		0.0 },									// GUIDE_CRITERIA_WEAPON_VECTOR
			}
      },
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
