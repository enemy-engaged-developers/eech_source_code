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

const division_data
	division_database[NUM_ENTITY_SUB_TYPE_DIVISIONS] =
	{
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_DIVISION_AIRBORNE_HELICOPTER_DIVISION
		//
		////////////////////////////////////////
		{
			"%s Airborne Division",
			NUM_ENTITY_SUB_TYPE_DIVISIONS,								// default_group_division
			0,																		// maximum_groups_per_division
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_DIVISION_AIRBORNE_FIXED_WING_DIVISION
		//
		////////////////////////////////////////
		{
			"%s Airborne Division",
			NUM_ENTITY_SUB_TYPE_DIVISIONS,								// default_group_division
			0,																		// maximum_groups_per_division
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_DIVISION_AIRBORNE_TRANSPORT_DIVISION
		//
		////////////////////////////////////////
		{
			"%s Airborne Division",
			NUM_ENTITY_SUB_TYPE_DIVISIONS,								// default_group_division
			0,																		// maximum_groups_per_division
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_DIVISION_ARMOURED_DIVISION
		//
		////////////////////////////////////////
		{
			"%s Armoured Division",
			NUM_ENTITY_SUB_TYPE_DIVISIONS,								// default_group_division
			0,																		// maximum_groups_per_division
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_DIVISION_CARRIER_DIVISION
		//
		////////////////////////////////////////
		{
			"%s Naval Division",
			NUM_ENTITY_SUB_TYPE_DIVISIONS,								// default_group_division
			0,																		// maximum_groups_per_division
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_DIVISION_INFANTRY_DIVISION
		//
		////////////////////////////////////////
		{
			"%s Infantry Division",
			NUM_ENTITY_SUB_TYPE_DIVISIONS,								// default_group_division
			0,																		// maximum_groups_per_division
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_DIVISION_HC_ATTACK_COMPANY
		//
		////////////////////////////////////////
		{
			"%s Aviation Group",
			ENTITY_SUB_TYPE_DIVISION_AIRBORNE_HELICOPTER_DIVISION,	// default_group_division
			0,																			// maximum_groups_per_division
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_DIVISION_HC_TRANSPORT_COMPANY
		//
		////////////////////////////////////////
		{
			"%s Transport Group",
			ENTITY_SUB_TYPE_DIVISION_AIRBORNE_TRANSPORT_DIVISION,		// default_group_division
			0,																			// maximum_groups_per_division
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_DIVISION_FW_ATTACK_COMPANY
		//
		////////////////////////////////////////
		{
			"%s Attack Squadron",
			ENTITY_SUB_TYPE_DIVISION_AIRBORNE_FIXED_WING_DIVISION,	// default_group_division
			0,																			// maximum_groups_per_division
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_DIVISION_FW_FIGHTER_COMPANY
		//
		////////////////////////////////////////
		{
			"%s Fighter Squadron",
			ENTITY_SUB_TYPE_DIVISION_AIRBORNE_FIXED_WING_DIVISION,	// default_group_division
			0,																			// maximum_groups_per_division
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_DIVISION_FW_TRANSPORT_COMPANY
		//
		////////////////////////////////////////
		{
			"%s Transport Squadron",
			ENTITY_SUB_TYPE_DIVISION_AIRBORNE_TRANSPORT_DIVISION,		// default_group_division
			0,																			// maximum_groups_per_division
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_DIVISION_ADA_COMPANY
		//
		////////////////////////////////////////
		{
			"%s SAM Brigade ADA",
			ENTITY_SUB_TYPE_DIVISION_ARMOURED_DIVISION,				// default_group_division
			0,																		// maximum_groups_per_division
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_DIVISION_ARMOURED_COMPANY
		//
		////////////////////////////////////////
		{
			"%s Armoured Brigade",
			ENTITY_SUB_TYPE_DIVISION_ARMOURED_DIVISION,				// default_group_division
			4,																		// maximum_groups_per_division
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_DIVISION_ARTILLERY_COMPANY
		//
		////////////////////////////////////////
		{
			"%s Artillery Brigade",
			ENTITY_SUB_TYPE_DIVISION_ARMOURED_DIVISION,				// default_group_division
			2,																		// maximum_groups_per_division
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_DIVISION_CARRIER_COMPANY
		//
		////////////////////////////////////////
		{
			"%s Carrier Task Force",
			ENTITY_SUB_TYPE_DIVISION_CARRIER_DIVISION,				// default_group_division
			0,																		// maximum_groups_per_division
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_DIVISION_INFANTRY_COMPANY
		//
		////////////////////////////////////////
		{
			"%s Infantry Brigade",
			ENTITY_SUB_TYPE_DIVISION_INFANTRY_DIVISION,				// default_group_division
			0,																		// maximum_groups_per_division
		},
		////////////////////////////////////////
		//
		// ENTITY_SUB_TYPE_DIVISION_SPECIAL_FORCES_COMPANY
		//
		////////////////////////////////////////
		{
			"%s Special Forces Brigade",
			ENTITY_SUB_TYPE_DIVISION_INFANTRY_DIVISION,				// default_group_division
			0,																		// maximum_groups_per_division
		},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
