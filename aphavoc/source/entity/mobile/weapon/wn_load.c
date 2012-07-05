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

struct WEAPON_LOADING_HARDPOINT_TYPE
{
	int
		valid,
		fixed,
		current_weapon_index,
		number_of_valid_weapon_types;

	int
		sub_object_depth1,
		sub_object_depth2;

	entity_sub_types
		*valid_weapon_types;
};

typedef struct WEAPON_LOADING_HARDPOINT_TYPE weapon_loading_hardpoint_type;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct WEAPON_LOADING_GUNSHIP_TYPE
{
	weapon_loading_hardpoint_type
		hardpoint_list [NUM_WEAPON_LOADING_HARDPOINT_TYPES];
};

typedef struct WEAPON_LOADING_GUNSHIP_TYPE weapon_loading_gunship_type;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static weapon_loading_gunship_type
	weapon_loading_gunship_database [NUM_GUNSHIP_TYPES];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void weapon_loading_reload_all_weapons (entity *en);

static void weapon_loading_set_current_hardpoint_weapon (gunship_types gunship_type, weapon_loading_hardpoint_types hardpoint, entity_sub_types weapon_type);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_weapon_loading_gunship_database (void)
{
	weapon_loading_gunship_type
		*gunship_data;

	weapon_loading_hardpoint_type
		*hardpoint_data;

	int
		loop;

	//////////////////////////
	//
	// APACHE
	//
	//////////////////////////

	gunship_data = &weapon_loading_gunship_database [GUNSHIP_TYPE_APACHE];

	for (loop = 0; loop < NUM_WEAPON_LOADING_HARDPOINT_TYPES; loop ++)
	{
		memset (&(gunship_data->hardpoint_list [loop]), 0, sizeof (weapon_loading_hardpoint_type));
	}

	// GUN 1

	hardpoint_data = &(gunship_data->hardpoint_list [WEAPON_LOADING_HARDPOINT_GUN1]);

	hardpoint_data->valid = TRUE;

	hardpoint_data->fixed = TRUE;

	hardpoint_data->current_weapon_index = 0;

	hardpoint_data->sub_object_depth1 = APACHE_CHAIN_GUN_TURRET;
	hardpoint_data->sub_object_depth2 = -1;

	hardpoint_data->number_of_valid_weapon_types = 1;

	hardpoint_data->valid_weapon_types =(entity_sub_types *) safe_malloc (sizeof (entity_sub_types) * hardpoint_data->number_of_valid_weapon_types);

	hardpoint_data->valid_weapon_types [0] = ENTITY_SUB_TYPE_WEAPON_M230_30MM_ROUND;

	// INNER HARDPOINT

	hardpoint_data = &(gunship_data->hardpoint_list [WEAPON_LOADING_HARDPOINT_INNER]);

	hardpoint_data->valid = TRUE;

	hardpoint_data->fixed = FALSE;

	hardpoint_data->current_weapon_index = 0;

	hardpoint_data->sub_object_depth1 = APACHE_LHS_INNER_PYLON;
	hardpoint_data->sub_object_depth2 = APACHE_RHS_INNER_PYLON;

	hardpoint_data->number_of_valid_weapon_types = 5;

	hardpoint_data->valid_weapon_types =(entity_sub_types *) safe_malloc (sizeof (entity_sub_types) * hardpoint_data->number_of_valid_weapon_types);

	hardpoint_data->valid_weapon_types [0] = ENTITY_SUB_TYPE_WEAPON_AGM114L_LONGBOW_HELLFIRE;
	hardpoint_data->valid_weapon_types [1] = ENTITY_SUB_TYPE_WEAPON_AGM114K_HELLFIRE_II;
	hardpoint_data->valid_weapon_types [2] = ENTITY_SUB_TYPE_WEAPON_HYDRA70_M255;
	hardpoint_data->valid_weapon_types [3] = ENTITY_SUB_TYPE_WEAPON_HYDRA70_M261;
	hardpoint_data->valid_weapon_types [4] = ENTITY_SUB_TYPE_WEAPON_NO_WEAPON;

	// OUTER HARDPOINT

	hardpoint_data = &(gunship_data->hardpoint_list [WEAPON_LOADING_HARDPOINT_OUTER]);

	hardpoint_data->valid = TRUE;

	hardpoint_data->fixed = FALSE;

	hardpoint_data->current_weapon_index = 0;

	hardpoint_data->sub_object_depth1 = APACHE_LHS_OUTER_PYLON;
	hardpoint_data->sub_object_depth2 = APACHE_RHS_OUTER_PYLON;

	hardpoint_data->number_of_valid_weapon_types = 5;

	hardpoint_data->valid_weapon_types =(entity_sub_types *) safe_malloc (sizeof (entity_sub_types) * hardpoint_data->number_of_valid_weapon_types);

	hardpoint_data->valid_weapon_types [0] = ENTITY_SUB_TYPE_WEAPON_AGM114L_LONGBOW_HELLFIRE;
	hardpoint_data->valid_weapon_types [1] = ENTITY_SUB_TYPE_WEAPON_AGM114K_HELLFIRE_II;
	hardpoint_data->valid_weapon_types [2] = ENTITY_SUB_TYPE_WEAPON_HYDRA70_M255;
	hardpoint_data->valid_weapon_types [3] = ENTITY_SUB_TYPE_WEAPON_HYDRA70_M261;
	hardpoint_data->valid_weapon_types [4] = ENTITY_SUB_TYPE_WEAPON_NO_WEAPON;

	// WINGTIP HARDPOINT

	hardpoint_data = &(gunship_data->hardpoint_list [WEAPON_LOADING_HARDPOINT_WINGTIP]);

	hardpoint_data->valid = TRUE;

	hardpoint_data->fixed = FALSE;

	hardpoint_data->current_weapon_index = 0;

	hardpoint_data->sub_object_depth1 = APACHE_LHS_WING_TIP_MOUNT;
	hardpoint_data->sub_object_depth2 = APACHE_RHS_WING_TIP_MOUNT;

	hardpoint_data->number_of_valid_weapon_types = 2;

	hardpoint_data->valid_weapon_types =(entity_sub_types *) safe_malloc (sizeof (entity_sub_types) * hardpoint_data->number_of_valid_weapon_types);

	hardpoint_data->valid_weapon_types [0] = ENTITY_SUB_TYPE_WEAPON_AIM92_STINGER;
	hardpoint_data->valid_weapon_types [1] = ENTITY_SUB_TYPE_WEAPON_NO_WEAPON;

	//////////////////////////
	//
	// HAVOC
	//
	//////////////////////////

	gunship_data = &weapon_loading_gunship_database [GUNSHIP_TYPE_HAVOC];

	for (loop = 0; loop < NUM_WEAPON_LOADING_HARDPOINT_TYPES; loop ++)
	{
		memset (&(gunship_data->hardpoint_list [loop]), 0, sizeof (weapon_loading_hardpoint_type));
	}

	// GUN 1

	hardpoint_data = &(gunship_data->hardpoint_list [WEAPON_LOADING_HARDPOINT_GUN1]);

	hardpoint_data->valid = TRUE;

	hardpoint_data->fixed = TRUE;

	hardpoint_data->current_weapon_index = 0;

	hardpoint_data->sub_object_depth1 = HAVOC_CANNON_TURRET;
	hardpoint_data->sub_object_depth2 = -1;

	hardpoint_data->number_of_valid_weapon_types = 1;

	hardpoint_data->valid_weapon_types =(entity_sub_types *) safe_malloc (sizeof (entity_sub_types) * hardpoint_data->number_of_valid_weapon_types);

	hardpoint_data->valid_weapon_types [0] = ENTITY_SUB_TYPE_WEAPON_2A42_30MM_HE_ROUND;

	// GUN 2

	hardpoint_data = &(gunship_data->hardpoint_list [WEAPON_LOADING_HARDPOINT_GUN2]);

	hardpoint_data->valid = TRUE;

	hardpoint_data->fixed = TRUE;

	hardpoint_data->current_weapon_index = 0;

	hardpoint_data->sub_object_depth1 = HAVOC_CANNON_TURRET;
	hardpoint_data->sub_object_depth2 = -1;

	hardpoint_data->number_of_valid_weapon_types = 1;

	hardpoint_data->valid_weapon_types =(entity_sub_types *) safe_malloc (sizeof (entity_sub_types) * hardpoint_data->number_of_valid_weapon_types);

	hardpoint_data->valid_weapon_types [0] = ENTITY_SUB_TYPE_WEAPON_2A42_30MM_AP_ROUND;

	// INNER HARDPOINT

	hardpoint_data = &(gunship_data->hardpoint_list [WEAPON_LOADING_HARDPOINT_INNER]);

	hardpoint_data->valid = TRUE;

	hardpoint_data->fixed = FALSE;

	hardpoint_data->current_weapon_index = 0;

	hardpoint_data->sub_object_depth1 = HAVOC_LHS_INNER_PYLON;
	hardpoint_data->sub_object_depth2 = HAVOC_RHS_INNER_PYLON;

	hardpoint_data->number_of_valid_weapon_types = 5;

	hardpoint_data->valid_weapon_types =(entity_sub_types *) safe_malloc (sizeof (entity_sub_types) * hardpoint_data->number_of_valid_weapon_types);

	hardpoint_data->valid_weapon_types [0] = ENTITY_SUB_TYPE_WEAPON_IGLA_V;
	hardpoint_data->valid_weapon_types [1] = ENTITY_SUB_TYPE_WEAPON_S8;
	hardpoint_data->valid_weapon_types [2] = ENTITY_SUB_TYPE_WEAPON_S13;
	hardpoint_data->valid_weapon_types [3] = ENTITY_SUB_TYPE_WEAPON_GSH23L_23MM_ROUND;
	hardpoint_data->valid_weapon_types [4] = ENTITY_SUB_TYPE_WEAPON_NO_WEAPON;

	// OUTER HARDPOINT

	hardpoint_data = &(gunship_data->hardpoint_list [WEAPON_LOADING_HARDPOINT_OUTER]);

	hardpoint_data->valid = TRUE;

	hardpoint_data->fixed = FALSE;

	hardpoint_data->current_weapon_index = 0;

	hardpoint_data->sub_object_depth1 = HAVOC_LHS_OUTER_PYLON;
	hardpoint_data->sub_object_depth2 = HAVOC_RHS_OUTER_PYLON;

	hardpoint_data->number_of_valid_weapon_types = 6;

	hardpoint_data->valid_weapon_types =(entity_sub_types *) safe_malloc (sizeof (entity_sub_types) * hardpoint_data->number_of_valid_weapon_types);

	hardpoint_data->valid_weapon_types [0] = ENTITY_SUB_TYPE_WEAPON_ATAKA;
	hardpoint_data->valid_weapon_types [1] = ENTITY_SUB_TYPE_WEAPON_IGLA_V;
	hardpoint_data->valid_weapon_types [2] = ENTITY_SUB_TYPE_WEAPON_S8;
	hardpoint_data->valid_weapon_types [3] = ENTITY_SUB_TYPE_WEAPON_S13;
	hardpoint_data->valid_weapon_types [4] = ENTITY_SUB_TYPE_WEAPON_GSH23L_23MM_ROUND;
	hardpoint_data->valid_weapon_types [5] = ENTITY_SUB_TYPE_WEAPON_NO_WEAPON;

	//////////////////////////
	//
	// COMANCHE
	//
	//////////////////////////

	gunship_data = &weapon_loading_gunship_database [GUNSHIP_TYPE_COMANCHE];

	for (loop = 0; loop < NUM_WEAPON_LOADING_HARDPOINT_TYPES; loop ++)
	{
		memset (&(gunship_data->hardpoint_list [loop]), 0, sizeof (weapon_loading_hardpoint_type));
	}

	// GUN 1

	hardpoint_data = &(gunship_data->hardpoint_list [WEAPON_LOADING_HARDPOINT_GUN1]);

	hardpoint_data->valid = TRUE;

	hardpoint_data->fixed = TRUE;

	hardpoint_data->current_weapon_index = 0;

	hardpoint_data->sub_object_depth1 = COMANCHE_CANNON_TURRET;
	hardpoint_data->sub_object_depth2 = -1;

	hardpoint_data->number_of_valid_weapon_types = 1;

	hardpoint_data->valid_weapon_types =(entity_sub_types *) safe_malloc (sizeof (entity_sub_types) * hardpoint_data->number_of_valid_weapon_types);

	hardpoint_data->valid_weapon_types [0] = ENTITY_SUB_TYPE_WEAPON_M197_20MM_ROUND;

	// INNER HARDPOINT

	hardpoint_data = &(gunship_data->hardpoint_list [WEAPON_LOADING_HARDPOINT_INNER]);

	hardpoint_data->valid = TRUE;

	hardpoint_data->fixed = FALSE;

	hardpoint_data->current_weapon_index = 0;

	hardpoint_data->sub_object_depth1 = COMANCHE_LHS_BAY_DOOR_INNER;
	hardpoint_data->sub_object_depth2 = COMANCHE_RHS_BAY_DOOR_INNER;

	hardpoint_data->number_of_valid_weapon_types = 4;

	hardpoint_data->valid_weapon_types =(entity_sub_types *) safe_malloc (sizeof (entity_sub_types) * hardpoint_data->number_of_valid_weapon_types);

	hardpoint_data->valid_weapon_types [0] = ENTITY_SUB_TYPE_WEAPON_AGM114L_LONGBOW_HELLFIRE;
	hardpoint_data->valid_weapon_types [1] = ENTITY_SUB_TYPE_WEAPON_AGM114K_HELLFIRE_II;
	hardpoint_data->valid_weapon_types [2] = ENTITY_SUB_TYPE_WEAPON_AIM92_STINGER;
	hardpoint_data->valid_weapon_types [3] = ENTITY_SUB_TYPE_WEAPON_NO_WEAPON;

	// MID HARDPOINT

	hardpoint_data = &(gunship_data->hardpoint_list [WEAPON_LOADING_HARDPOINT_MID]);

	hardpoint_data->valid = TRUE;

	hardpoint_data->fixed = FALSE;

	hardpoint_data->current_weapon_index = 0;

	hardpoint_data->sub_object_depth1 = COMANCHE_LHS_BAY_DOOR_MIDDLE;
	hardpoint_data->sub_object_depth2 = COMANCHE_RHS_BAY_DOOR_MIDDLE;

	hardpoint_data->number_of_valid_weapon_types = 4;

	hardpoint_data->valid_weapon_types =(entity_sub_types *) safe_malloc (sizeof (entity_sub_types) * hardpoint_data->number_of_valid_weapon_types);

	hardpoint_data->valid_weapon_types [0] = ENTITY_SUB_TYPE_WEAPON_AGM114L_LONGBOW_HELLFIRE;
	hardpoint_data->valid_weapon_types [1] = ENTITY_SUB_TYPE_WEAPON_AGM114K_HELLFIRE_II;
	hardpoint_data->valid_weapon_types [2] = ENTITY_SUB_TYPE_WEAPON_AIM92_STINGER;
	hardpoint_data->valid_weapon_types [3] = ENTITY_SUB_TYPE_WEAPON_NO_WEAPON;

	// OUTER HARDPOINT

	hardpoint_data = &(gunship_data->hardpoint_list [WEAPON_LOADING_HARDPOINT_OUTER]);

	hardpoint_data->valid = TRUE;

	hardpoint_data->fixed = FALSE;

	hardpoint_data->current_weapon_index = 0;

	hardpoint_data->sub_object_depth1 = COMANCHE_LHS_BAY_DOOR_OUTER;
	hardpoint_data->sub_object_depth2 = COMANCHE_RHS_BAY_DOOR_OUTER;

	hardpoint_data->number_of_valid_weapon_types = 4;

	hardpoint_data->valid_weapon_types =(entity_sub_types *) safe_malloc (sizeof (entity_sub_types) * hardpoint_data->number_of_valid_weapon_types);

	hardpoint_data->valid_weapon_types [0] = ENTITY_SUB_TYPE_WEAPON_AGM114L_LONGBOW_HELLFIRE;
	hardpoint_data->valid_weapon_types [1] = ENTITY_SUB_TYPE_WEAPON_AGM114K_HELLFIRE_II;
	hardpoint_data->valid_weapon_types [2] = ENTITY_SUB_TYPE_WEAPON_AIM92_STINGER;
	hardpoint_data->valid_weapon_types [3] = ENTITY_SUB_TYPE_WEAPON_NO_WEAPON;

	// WINGTIP HARDPOINT

	hardpoint_data = &(gunship_data->hardpoint_list [WEAPON_LOADING_HARDPOINT_WINGTIP]);

	hardpoint_data->valid = TRUE;

	hardpoint_data->fixed = FALSE;

	hardpoint_data->current_weapon_index = 0;

	hardpoint_data->sub_object_depth1 = COMANCHE_LHS_STUB_WING;
	hardpoint_data->sub_object_depth2 = COMANCHE_RHS_STUB_WING;

	hardpoint_data->number_of_valid_weapon_types = 6;

	hardpoint_data->valid_weapon_types =(entity_sub_types *) safe_malloc (sizeof (entity_sub_types) * hardpoint_data->number_of_valid_weapon_types);

	hardpoint_data->valid_weapon_types [0] = ENTITY_SUB_TYPE_WEAPON_AGM114L_LONGBOW_HELLFIRE;
	hardpoint_data->valid_weapon_types [1] = ENTITY_SUB_TYPE_WEAPON_AGM114K_HELLFIRE_II;
	hardpoint_data->valid_weapon_types [2] = ENTITY_SUB_TYPE_WEAPON_HYDRA70_M255;
	hardpoint_data->valid_weapon_types [3] = ENTITY_SUB_TYPE_WEAPON_HYDRA70_M261;
	hardpoint_data->valid_weapon_types [4] = ENTITY_SUB_TYPE_WEAPON_AIM92_STINGER;
	hardpoint_data->valid_weapon_types [5] = ENTITY_SUB_TYPE_WEAPON_NO_WEAPON;

	//////////////////////////
	//
	// HOKUM
	//
	//////////////////////////

	gunship_data = &weapon_loading_gunship_database [GUNSHIP_TYPE_HOKUM];

	for (loop = 0; loop < NUM_WEAPON_LOADING_HARDPOINT_TYPES; loop ++)
	{
		memset (&(gunship_data->hardpoint_list [loop]), 0, sizeof (weapon_loading_hardpoint_type));
	}

	// GUN 1

	hardpoint_data = &(gunship_data->hardpoint_list [WEAPON_LOADING_HARDPOINT_GUN1]);

	hardpoint_data->valid = TRUE;

	hardpoint_data->fixed = TRUE;

	hardpoint_data->current_weapon_index = 0;

	hardpoint_data->sub_object_depth1 = HOKUM_CANNON_TURRET;
	hardpoint_data->sub_object_depth2 = -1;

	hardpoint_data->number_of_valid_weapon_types = 1;

	hardpoint_data->valid_weapon_types =(entity_sub_types *) safe_malloc (sizeof (entity_sub_types) * hardpoint_data->number_of_valid_weapon_types);

	hardpoint_data->valid_weapon_types [0] = ENTITY_SUB_TYPE_WEAPON_2A42_30MM_HE_ROUND;

	// GUN 2

	hardpoint_data = &(gunship_data->hardpoint_list [WEAPON_LOADING_HARDPOINT_GUN2]);

	hardpoint_data->valid = TRUE;

	hardpoint_data->fixed = TRUE;

	hardpoint_data->current_weapon_index = 0;

	hardpoint_data->sub_object_depth1 = HOKUM_CANNON_TURRET;
	hardpoint_data->sub_object_depth2 = -1;

	hardpoint_data->number_of_valid_weapon_types = 1;

	hardpoint_data->valid_weapon_types =(entity_sub_types *) safe_malloc (sizeof (entity_sub_types) * hardpoint_data->number_of_valid_weapon_types);

	hardpoint_data->valid_weapon_types [0] = ENTITY_SUB_TYPE_WEAPON_2A42_30MM_AP_ROUND;

	// INNER HARDPOINT

	hardpoint_data = &(gunship_data->hardpoint_list [WEAPON_LOADING_HARDPOINT_INNER]);

	hardpoint_data->valid = TRUE;

	hardpoint_data->fixed = FALSE;

	hardpoint_data->current_weapon_index = 0;

	hardpoint_data->sub_object_depth1 = HOKUM_LHS_INNER_PYLON;
	hardpoint_data->sub_object_depth2 = HOKUM_RHS_INNER_PYLON;

	hardpoint_data->number_of_valid_weapon_types = 5;

	hardpoint_data->valid_weapon_types =(entity_sub_types *) safe_malloc (sizeof (entity_sub_types) * hardpoint_data->number_of_valid_weapon_types);

	hardpoint_data->valid_weapon_types [0] = ENTITY_SUB_TYPE_WEAPON_IGLA_V;
	hardpoint_data->valid_weapon_types [1] = ENTITY_SUB_TYPE_WEAPON_S8;
	hardpoint_data->valid_weapon_types [2] = ENTITY_SUB_TYPE_WEAPON_S13;
	hardpoint_data->valid_weapon_types [3] = ENTITY_SUB_TYPE_WEAPON_GSH23L_23MM_ROUND;
	hardpoint_data->valid_weapon_types [4] = ENTITY_SUB_TYPE_WEAPON_NO_WEAPON;

	// OUTER HARDPOINT

	hardpoint_data = &(gunship_data->hardpoint_list [WEAPON_LOADING_HARDPOINT_OUTER]);

	hardpoint_data->valid = TRUE;

	hardpoint_data->fixed = FALSE;

	hardpoint_data->current_weapon_index = 0;

	hardpoint_data->sub_object_depth1 = HOKUM_LHS_OUTER_PYLON;
	hardpoint_data->sub_object_depth2 = HOKUM_RHS_OUTER_PYLON;

	hardpoint_data->number_of_valid_weapon_types = 6;

	hardpoint_data->valid_weapon_types =(entity_sub_types *) safe_malloc (sizeof (entity_sub_types) * hardpoint_data->number_of_valid_weapon_types);

	hardpoint_data->valid_weapon_types [0] = ENTITY_SUB_TYPE_WEAPON_VIKHR;
	hardpoint_data->valid_weapon_types [1] = ENTITY_SUB_TYPE_WEAPON_IGLA_V;
	hardpoint_data->valid_weapon_types [2] = ENTITY_SUB_TYPE_WEAPON_S8;
	hardpoint_data->valid_weapon_types [3] = ENTITY_SUB_TYPE_WEAPON_S13;
	hardpoint_data->valid_weapon_types [4] = ENTITY_SUB_TYPE_WEAPON_GSH23L_23MM_ROUND;
	hardpoint_data->valid_weapon_types [5] = ENTITY_SUB_TYPE_WEAPON_NO_WEAPON;

////Moje 030519 Start
	//////////////////////////
	//
	// BLACK-HAWK
	//
	//////////////////////////

	gunship_data = &weapon_loading_gunship_database [GUNSHIP_TYPE_BLACKHAWK];

	for (loop = 0; loop < NUM_WEAPON_LOADING_HARDPOINT_TYPES; loop ++)
	{
		memset (&(gunship_data->hardpoint_list [loop]), 0, sizeof (weapon_loading_hardpoint_type));
	}

	// INNER HARDPOINT

	hardpoint_data = &(gunship_data->hardpoint_list [WEAPON_LOADING_HARDPOINT_INNER]);

	hardpoint_data->valid = TRUE;

	hardpoint_data->fixed = FALSE;

	hardpoint_data->current_weapon_index = 0;

	hardpoint_data->sub_object_depth1 = BLACKHAWK_LHS_INNER_PYLON;
	hardpoint_data->sub_object_depth2 = BLACKHAWK_RHS_INNER_PYLON;

	hardpoint_data->number_of_valid_weapon_types = 3;

	hardpoint_data->valid_weapon_types =(entity_sub_types *) safe_malloc (sizeof (entity_sub_types) * hardpoint_data->number_of_valid_weapon_types);

	hardpoint_data->valid_weapon_types [0] = ENTITY_SUB_TYPE_WEAPON_AGM114K_HELLFIRE_II;
	hardpoint_data->valid_weapon_types [1] = ENTITY_SUB_TYPE_WEAPON_HYDRA70_M261;
	hardpoint_data->valid_weapon_types [2] = ENTITY_SUB_TYPE_WEAPON_NO_WEAPON;

	// OUTER HARDPOINT

	hardpoint_data = &(gunship_data->hardpoint_list [WEAPON_LOADING_HARDPOINT_OUTER]);

	hardpoint_data->valid = TRUE;

	hardpoint_data->fixed = FALSE;

	hardpoint_data->current_weapon_index = 0;

	hardpoint_data->sub_object_depth1 = BLACKHAWK_LHS_OUTER_PYLON;
	hardpoint_data->sub_object_depth2 = BLACKHAWK_RHS_OUTER_PYLON;

	hardpoint_data->number_of_valid_weapon_types = 3;

	hardpoint_data->valid_weapon_types =(entity_sub_types *) safe_malloc (sizeof (entity_sub_types) * hardpoint_data->number_of_valid_weapon_types);

	hardpoint_data->valid_weapon_types [0] = ENTITY_SUB_TYPE_WEAPON_AGM114K_HELLFIRE_II;
	hardpoint_data->valid_weapon_types [1] = ENTITY_SUB_TYPE_WEAPON_HYDRA70_M261;
	hardpoint_data->valid_weapon_types [2] = ENTITY_SUB_TYPE_WEAPON_NO_WEAPON;

////Moje 030519 End
////Moje 030613 start
	//////////////////////////
	//
	// HIND
	//
	//////////////////////////

	gunship_data = &weapon_loading_gunship_database [GUNSHIP_TYPE_HIND];

	for (loop = 0; loop < NUM_WEAPON_LOADING_HARDPOINT_TYPES; loop ++)
	{
		memset (&(gunship_data->hardpoint_list [loop]), 0, sizeof (weapon_loading_hardpoint_type));
	}

	// GUN 1

	hardpoint_data = &(gunship_data->hardpoint_list [WEAPON_LOADING_HARDPOINT_GUN1]);

	hardpoint_data->valid = TRUE;

	hardpoint_data->fixed = TRUE;

	hardpoint_data->current_weapon_index = 0;

	hardpoint_data->sub_object_depth1 = HIND_CANNON_TURRET;
	hardpoint_data->sub_object_depth2 = -1;

	hardpoint_data->number_of_valid_weapon_types = 1;

	hardpoint_data->valid_weapon_types =(entity_sub_types *) safe_malloc (sizeof (entity_sub_types) * hardpoint_data->number_of_valid_weapon_types);

	hardpoint_data->valid_weapon_types [0] = ENTITY_SUB_TYPE_WEAPON_9A642_12P7MM_ROUND;

	// INNER HARDPOINT

	hardpoint_data = &(gunship_data->hardpoint_list [WEAPON_LOADING_HARDPOINT_INNER]);

	hardpoint_data->valid = TRUE;

	hardpoint_data->fixed = FALSE;

	hardpoint_data->current_weapon_index = 0;

	hardpoint_data->sub_object_depth1 = HIND_LHS_INNER_PYLON;
	hardpoint_data->sub_object_depth2 = HIND_RHS_INNER_PYLON;

	hardpoint_data->number_of_valid_weapon_types = 5;

	hardpoint_data->valid_weapon_types =(entity_sub_types *) safe_malloc (sizeof (entity_sub_types) * hardpoint_data->number_of_valid_weapon_types);

	hardpoint_data->valid_weapon_types [0] = ENTITY_SUB_TYPE_WEAPON_S8;
	hardpoint_data->valid_weapon_types [1] = ENTITY_SUB_TYPE_WEAPON_S13;
	hardpoint_data->valid_weapon_types [2] = ENTITY_SUB_TYPE_WEAPON_S5;
	hardpoint_data->valid_weapon_types [3] = ENTITY_SUB_TYPE_WEAPON_GSH23L_23MM_ROUND;
	hardpoint_data->valid_weapon_types [4] = ENTITY_SUB_TYPE_WEAPON_NO_WEAPON;

	// OUTER HARDPOINT

	hardpoint_data = &(gunship_data->hardpoint_list [WEAPON_LOADING_HARDPOINT_OUTER]);

	hardpoint_data->valid = TRUE;

	hardpoint_data->fixed = FALSE;

	hardpoint_data->current_weapon_index = 0;

	hardpoint_data->sub_object_depth1 = HIND_LHS_OUTER_PYLON;
	hardpoint_data->sub_object_depth2 = HIND_RHS_OUTER_PYLON;

	hardpoint_data->number_of_valid_weapon_types = 6;

	hardpoint_data->valid_weapon_types =(entity_sub_types *) safe_malloc (sizeof (entity_sub_types) * hardpoint_data->number_of_valid_weapon_types);

	hardpoint_data->valid_weapon_types [0] = ENTITY_SUB_TYPE_WEAPON_S8;
	hardpoint_data->valid_weapon_types [1] = ENTITY_SUB_TYPE_WEAPON_S13;
	hardpoint_data->valid_weapon_types [2] = ENTITY_SUB_TYPE_WEAPON_S5;
	hardpoint_data->valid_weapon_types [3] = ENTITY_SUB_TYPE_WEAPON_GSH23L_23MM_ROUND;
	hardpoint_data->valid_weapon_types [4] = ENTITY_SUB_TYPE_WEAPON_AT6_SPIRAL;
	hardpoint_data->valid_weapon_types [5] = ENTITY_SUB_TYPE_WEAPON_NO_WEAPON;

	// WINGTIP HARDPOINT

	hardpoint_data = &(gunship_data->hardpoint_list [WEAPON_LOADING_HARDPOINT_WINGTIP]);

	hardpoint_data->valid = TRUE;

	hardpoint_data->fixed = FALSE;

	hardpoint_data->current_weapon_index = 0;

	hardpoint_data->sub_object_depth1 = HIND_LHS_WING_TIP_MOUNT;
	hardpoint_data->sub_object_depth2 = HIND_RHS_WING_TIP_MOUNT;

	hardpoint_data->number_of_valid_weapon_types = 2;

	hardpoint_data->valid_weapon_types =(entity_sub_types *) safe_malloc (sizeof (entity_sub_types) * hardpoint_data->number_of_valid_weapon_types);

	hardpoint_data->valid_weapon_types [0] = ENTITY_SUB_TYPE_WEAPON_AT6_SPIRAL;
	hardpoint_data->valid_weapon_types [1] = ENTITY_SUB_TYPE_WEAPON_NO_WEAPON;

////moje 030613 end

////Moje 030817 start
	//////////////////////////
	//
	// AH64A
	//
	//////////////////////////

	gunship_data = &weapon_loading_gunship_database [GUNSHIP_TYPE_AH64A];

	for (loop = 0; loop < NUM_WEAPON_LOADING_HARDPOINT_TYPES; loop ++)
	{
		memset (&(gunship_data->hardpoint_list [loop]), 0, sizeof (weapon_loading_hardpoint_type));
	}

	// GUN 1

	hardpoint_data = &(gunship_data->hardpoint_list [WEAPON_LOADING_HARDPOINT_GUN1]);

	hardpoint_data->valid = TRUE;

	hardpoint_data->fixed = TRUE;

	hardpoint_data->current_weapon_index = 0;

	hardpoint_data->sub_object_depth1 = AH64A_CHAIN_GUN_TURRET;
	hardpoint_data->sub_object_depth2 = -1;

	hardpoint_data->number_of_valid_weapon_types = 1;

	hardpoint_data->valid_weapon_types =(entity_sub_types *) safe_malloc (sizeof (entity_sub_types) * hardpoint_data->number_of_valid_weapon_types);

	hardpoint_data->valid_weapon_types [0] = ENTITY_SUB_TYPE_WEAPON_M230_30MM_ROUND;

	// INNER HARDPOINT

	hardpoint_data = &(gunship_data->hardpoint_list [WEAPON_LOADING_HARDPOINT_INNER]);

	hardpoint_data->valid = TRUE;

	hardpoint_data->fixed = FALSE;

	hardpoint_data->current_weapon_index = 0;

	hardpoint_data->sub_object_depth1 = AH64A_LHS_INNER_PYLON;
	hardpoint_data->sub_object_depth2 = AH64A_RHS_INNER_PYLON;

	hardpoint_data->number_of_valid_weapon_types = 4;

	hardpoint_data->valid_weapon_types =(entity_sub_types *) safe_malloc (sizeof (entity_sub_types) * hardpoint_data->number_of_valid_weapon_types);

	hardpoint_data->valid_weapon_types [0] = ENTITY_SUB_TYPE_WEAPON_AGM114K_HELLFIRE_II;
	hardpoint_data->valid_weapon_types [1] = ENTITY_SUB_TYPE_WEAPON_HYDRA70_M255;
	hardpoint_data->valid_weapon_types [2] = ENTITY_SUB_TYPE_WEAPON_HYDRA70_M261;
	hardpoint_data->valid_weapon_types [3] = ENTITY_SUB_TYPE_WEAPON_NO_WEAPON;

	// OUTER HARDPOINT

	hardpoint_data = &(gunship_data->hardpoint_list [WEAPON_LOADING_HARDPOINT_OUTER]);

	hardpoint_data->valid = TRUE;

	hardpoint_data->fixed = FALSE;

	hardpoint_data->current_weapon_index = 0;

	hardpoint_data->sub_object_depth1 = AH64A_LHS_OUTER_PYLON;
	hardpoint_data->sub_object_depth2 = AH64A_RHS_OUTER_PYLON;

	hardpoint_data->number_of_valid_weapon_types = 4;

	hardpoint_data->valid_weapon_types =(entity_sub_types *) safe_malloc (sizeof (entity_sub_types) * hardpoint_data->number_of_valid_weapon_types);

	hardpoint_data->valid_weapon_types [0] = ENTITY_SUB_TYPE_WEAPON_AGM114K_HELLFIRE_II;
	hardpoint_data->valid_weapon_types [1] = ENTITY_SUB_TYPE_WEAPON_HYDRA70_M255;
	hardpoint_data->valid_weapon_types [2] = ENTITY_SUB_TYPE_WEAPON_HYDRA70_M261;
	hardpoint_data->valid_weapon_types [3] = ENTITY_SUB_TYPE_WEAPON_NO_WEAPON;

	// WINGTIP HARDPOINT

	hardpoint_data = &(gunship_data->hardpoint_list [WEAPON_LOADING_HARDPOINT_WINGTIP]);

	hardpoint_data->valid = TRUE;

	hardpoint_data->fixed = FALSE;

	hardpoint_data->current_weapon_index = 0;

	hardpoint_data->sub_object_depth1 = AH64A_LHS_WING_TIP_MOUNT;
	hardpoint_data->sub_object_depth2 = AH64A_RHS_WING_TIP_MOUNT;

	hardpoint_data->number_of_valid_weapon_types = 2;

	hardpoint_data->valid_weapon_types =(entity_sub_types *) safe_malloc (sizeof (entity_sub_types) * hardpoint_data->number_of_valid_weapon_types);

	hardpoint_data->valid_weapon_types [0] = ENTITY_SUB_TYPE_WEAPON_AIM92_STINGER;
	hardpoint_data->valid_weapon_types [1] = ENTITY_SUB_TYPE_WEAPON_NO_WEAPON;

	//////////////////////////
	//
	// KA50
	//
	//////////////////////////

	gunship_data = &weapon_loading_gunship_database [GUNSHIP_TYPE_KA50];

	for (loop = 0; loop < NUM_WEAPON_LOADING_HARDPOINT_TYPES; loop ++)
	{
		memset (&(gunship_data->hardpoint_list [loop]), 0, sizeof (weapon_loading_hardpoint_type));
	}

	// GUN 1

	hardpoint_data = &(gunship_data->hardpoint_list [WEAPON_LOADING_HARDPOINT_GUN1]);

	hardpoint_data->valid = TRUE;

	hardpoint_data->fixed = TRUE;

	hardpoint_data->current_weapon_index = 0;

	hardpoint_data->sub_object_depth1 = KA50_CANNON_TURRET;
	hardpoint_data->sub_object_depth2 = -1;

	hardpoint_data->number_of_valid_weapon_types = 1;

	hardpoint_data->valid_weapon_types =(entity_sub_types *) safe_malloc (sizeof (entity_sub_types) * hardpoint_data->number_of_valid_weapon_types);

	hardpoint_data->valid_weapon_types [0] = ENTITY_SUB_TYPE_WEAPON_2A42_30MM_HE_ROUND;

	// GUN 2

	hardpoint_data = &(gunship_data->hardpoint_list [WEAPON_LOADING_HARDPOINT_GUN2]);

	hardpoint_data->valid = TRUE;

	hardpoint_data->fixed = TRUE;

	hardpoint_data->current_weapon_index = 0;

	hardpoint_data->sub_object_depth1 = KA50_CANNON_TURRET;
	hardpoint_data->sub_object_depth2 = -1;

	hardpoint_data->number_of_valid_weapon_types = 1;

	hardpoint_data->valid_weapon_types =(entity_sub_types *) safe_malloc (sizeof (entity_sub_types) * hardpoint_data->number_of_valid_weapon_types);

	hardpoint_data->valid_weapon_types [0] = ENTITY_SUB_TYPE_WEAPON_2A42_30MM_AP_ROUND;

	// INNER HARDPOINT

	hardpoint_data = &(gunship_data->hardpoint_list [WEAPON_LOADING_HARDPOINT_INNER]);

	hardpoint_data->valid = TRUE;

	hardpoint_data->fixed = FALSE;

	hardpoint_data->current_weapon_index = 0;

	hardpoint_data->sub_object_depth1 = KA50_LHS_INNER_PYLON;
	hardpoint_data->sub_object_depth2 = KA50_RHS_INNER_PYLON;

	hardpoint_data->number_of_valid_weapon_types = 5;

	hardpoint_data->valid_weapon_types =(entity_sub_types *) safe_malloc (sizeof (entity_sub_types) * hardpoint_data->number_of_valid_weapon_types);

	hardpoint_data->valid_weapon_types [0] = ENTITY_SUB_TYPE_WEAPON_IGLA_V;
	hardpoint_data->valid_weapon_types [1] = ENTITY_SUB_TYPE_WEAPON_S8;
	hardpoint_data->valid_weapon_types [2] = ENTITY_SUB_TYPE_WEAPON_S13;
	hardpoint_data->valid_weapon_types [3] = ENTITY_SUB_TYPE_WEAPON_GSH23L_23MM_ROUND;
	hardpoint_data->valid_weapon_types [4] = ENTITY_SUB_TYPE_WEAPON_NO_WEAPON;

	// OUTER HARDPOINT

	hardpoint_data = &(gunship_data->hardpoint_list [WEAPON_LOADING_HARDPOINT_OUTER]);

	hardpoint_data->valid = TRUE;

	hardpoint_data->fixed = FALSE;

	hardpoint_data->current_weapon_index = 0;

	hardpoint_data->sub_object_depth1 = KA50_LHS_OUTER_PYLON;
	hardpoint_data->sub_object_depth2 = KA50_RHS_OUTER_PYLON;

	hardpoint_data->number_of_valid_weapon_types = 6;

	hardpoint_data->valid_weapon_types =(entity_sub_types *) safe_malloc (sizeof (entity_sub_types) * hardpoint_data->number_of_valid_weapon_types);

	hardpoint_data->valid_weapon_types [0] = ENTITY_SUB_TYPE_WEAPON_VIKHR;
	hardpoint_data->valid_weapon_types [1] = ENTITY_SUB_TYPE_WEAPON_IGLA_V;
	hardpoint_data->valid_weapon_types [2] = ENTITY_SUB_TYPE_WEAPON_S8;
	hardpoint_data->valid_weapon_types [3] = ENTITY_SUB_TYPE_WEAPON_S13;
	hardpoint_data->valid_weapon_types [4] = ENTITY_SUB_TYPE_WEAPON_GSH23L_23MM_ROUND;
	hardpoint_data->valid_weapon_types [5] = ENTITY_SUB_TYPE_WEAPON_NO_WEAPON;
////Moje 030817 End

	//////////////////////////
	//
	// VIPER
	//
	//////////////////////////

	gunship_data = &weapon_loading_gunship_database [GUNSHIP_TYPE_VIPER];

	for (loop = 0; loop < NUM_WEAPON_LOADING_HARDPOINT_TYPES; loop ++)
	{
		memset (&(gunship_data->hardpoint_list [loop]), 0, sizeof (weapon_loading_hardpoint_type));
	}

	// GUN 1

	hardpoint_data = &(gunship_data->hardpoint_list [WEAPON_LOADING_HARDPOINT_GUN1]);

	hardpoint_data->valid = TRUE;

	hardpoint_data->fixed = TRUE;

	hardpoint_data->current_weapon_index = 0;

	hardpoint_data->sub_object_depth1 = VIPER_CANNON_TURRET;
	hardpoint_data->sub_object_depth2 = -1;

	hardpoint_data->number_of_valid_weapon_types = 1;

	hardpoint_data->valid_weapon_types =(entity_sub_types *) safe_malloc (sizeof (entity_sub_types) * hardpoint_data->number_of_valid_weapon_types);

	hardpoint_data->valid_weapon_types [0] = ENTITY_SUB_TYPE_WEAPON_M197_20MM_ROUND;

	// INNER HARDPOINT

	hardpoint_data = &(gunship_data->hardpoint_list [WEAPON_LOADING_HARDPOINT_INNER]);

	hardpoint_data->valid = TRUE;

	hardpoint_data->fixed = FALSE;

	hardpoint_data->current_weapon_index = 0;

	hardpoint_data->sub_object_depth1 = VIPER_LHS_INNER_PYLON;
	hardpoint_data->sub_object_depth2 = VIPER_RHS_INNER_PYLON;

	hardpoint_data->number_of_valid_weapon_types = 3;

	hardpoint_data->valid_weapon_types =(entity_sub_types *) safe_malloc (sizeof (entity_sub_types) * hardpoint_data->number_of_valid_weapon_types);

	hardpoint_data->valid_weapon_types [0] = ENTITY_SUB_TYPE_WEAPON_AGM114K_HELLFIRE_II;
	hardpoint_data->valid_weapon_types [1] = ENTITY_SUB_TYPE_WEAPON_HYDRA70_M255;
	hardpoint_data->valid_weapon_types [2] = ENTITY_SUB_TYPE_WEAPON_NO_WEAPON;

	// OUTER HARDPOINT

	hardpoint_data = &(gunship_data->hardpoint_list [WEAPON_LOADING_HARDPOINT_OUTER]);

	hardpoint_data->valid = TRUE;

	hardpoint_data->fixed = FALSE;

	hardpoint_data->current_weapon_index = 0;

	hardpoint_data->sub_object_depth1 = VIPER_LHS_OUTER_PYLON;
	hardpoint_data->sub_object_depth2 = VIPER_RHS_OUTER_PYLON;

	hardpoint_data->number_of_valid_weapon_types = 3;

	hardpoint_data->valid_weapon_types =(entity_sub_types *) safe_malloc (sizeof (entity_sub_types) * hardpoint_data->number_of_valid_weapon_types);

	hardpoint_data->valid_weapon_types [0] = ENTITY_SUB_TYPE_WEAPON_AGM114K_HELLFIRE_II;
	hardpoint_data->valid_weapon_types [1] = ENTITY_SUB_TYPE_WEAPON_HYDRA70_M255;
	hardpoint_data->valid_weapon_types [2] = ENTITY_SUB_TYPE_WEAPON_NO_WEAPON;

	// WINGTIP HARDPOINT

	hardpoint_data = &(gunship_data->hardpoint_list [WEAPON_LOADING_HARDPOINT_WINGTIP]);

	hardpoint_data->valid = TRUE;

	hardpoint_data->fixed = FALSE;

	hardpoint_data->current_weapon_index = 0;

	hardpoint_data->sub_object_depth1 = VIPER_LHS_WING_TIP_MOUNT;
	hardpoint_data->sub_object_depth2 = VIPER_RHS_WING_TIP_MOUNT;

	hardpoint_data->number_of_valid_weapon_types = 2;

	hardpoint_data->valid_weapon_types =(entity_sub_types *) safe_malloc (sizeof (entity_sub_types) * hardpoint_data->number_of_valid_weapon_types);

	hardpoint_data->valid_weapon_types [0] = ENTITY_SUB_TYPE_WEAPON_AIM9M_SIDEWINDER;
	hardpoint_data->valid_weapon_types [1] = ENTITY_SUB_TYPE_WEAPON_NO_WEAPON;

	//////////////////////////
	//
	// KIOWA
	//
	//////////////////////////

	gunship_data = &weapon_loading_gunship_database [GUNSHIP_TYPE_KIOWA];

	for (loop = 0; loop < NUM_WEAPON_LOADING_HARDPOINT_TYPES; loop ++)
	{
		memset (&(gunship_data->hardpoint_list [loop]), 0, sizeof (weapon_loading_hardpoint_type));
	}

	// INNER HARDPOINT

	hardpoint_data = &(gunship_data->hardpoint_list [WEAPON_LOADING_HARDPOINT_INNER]);

	hardpoint_data->valid = TRUE;

	hardpoint_data->fixed = FALSE;

	hardpoint_data->current_weapon_index = 0;

	hardpoint_data->sub_object_depth1 = KIOWA_LHS_PYLON;
	hardpoint_data->sub_object_depth2 = -1;

	hardpoint_data->number_of_valid_weapon_types = 5;

	hardpoint_data->valid_weapon_types =(entity_sub_types *) safe_malloc (sizeof (entity_sub_types) * hardpoint_data->number_of_valid_weapon_types);

	hardpoint_data->valid_weapon_types [0] = ENTITY_SUB_TYPE_WEAPON_AGM114K_HELLFIRE_II;
	hardpoint_data->valid_weapon_types [1] = ENTITY_SUB_TYPE_WEAPON_AIM92_STINGER;
	hardpoint_data->valid_weapon_types [2] = ENTITY_SUB_TYPE_WEAPON_HYDRA70_M261;
	hardpoint_data->valid_weapon_types [3] = ENTITY_SUB_TYPE_WEAPON_M2_12P7MM_ROUND;
	hardpoint_data->valid_weapon_types [4] = ENTITY_SUB_TYPE_WEAPON_NO_WEAPON;

	// OUTER HARDPOINT

	hardpoint_data = &(gunship_data->hardpoint_list [WEAPON_LOADING_HARDPOINT_OUTER]);

	hardpoint_data->valid = TRUE;

	hardpoint_data->fixed = FALSE;

	hardpoint_data->current_weapon_index = 0;

	hardpoint_data->sub_object_depth1 = KIOWA_RHS_PYLON;
	hardpoint_data->sub_object_depth2 = -1;

	hardpoint_data->number_of_valid_weapon_types = 4;

	hardpoint_data->valid_weapon_types =(entity_sub_types *) safe_malloc (sizeof (entity_sub_types) * hardpoint_data->number_of_valid_weapon_types);

	hardpoint_data->valid_weapon_types [0] = ENTITY_SUB_TYPE_WEAPON_AGM114K_HELLFIRE_II;
	hardpoint_data->valid_weapon_types [1] = ENTITY_SUB_TYPE_WEAPON_AIM92_STINGER;
	hardpoint_data->valid_weapon_types [2] = ENTITY_SUB_TYPE_WEAPON_HYDRA70_M261;
	hardpoint_data->valid_weapon_types [3] = ENTITY_SUB_TYPE_WEAPON_NO_WEAPON;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_weapon_loading_gunship_database (void)
{
	weapon_loading_gunship_type
		*gunship_data;

	weapon_loading_hardpoint_type
		*hardpoint_data;

	int
		gunship,
		hardpoint;

	for (gunship = 0; gunship < NUM_GUNSHIP_TYPES; gunship ++)
	{
		gunship_data = &weapon_loading_gunship_database [gunship];

		for (hardpoint = 0; hardpoint < NUM_WEAPON_LOADING_HARDPOINT_TYPES; hardpoint ++)
		{
			hardpoint_data = &(gunship_data->hardpoint_list [hardpoint]);

			if (hardpoint_data->valid)
			{
				ASSERT (hardpoint_data->valid_weapon_types);

				safe_free (hardpoint_data->valid_weapon_types);

				hardpoint_data->valid_weapon_types = NULL;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deactivate_weapon_payload_markers (entity *en)
{
	object_3d_instance
		*inst3d;

	ASSERT (en);

	inst3d = (object_3d_instance *) get_local_entity_ptr_value (en, PTR_TYPE_INSTANCE_3D_OBJECT);

	ASSERT (inst3d);

	//
	// hardpoint markers
	//

	set_sub_object_type_visible_status (inst3d, OBJECT_3D_SUB_OBJECT_PAYLOAD_MARKER_1_ON, FALSE);
	set_sub_object_type_visible_status (inst3d, OBJECT_3D_SUB_OBJECT_PAYLOAD_MARKER_2_ON, FALSE);
	set_sub_object_type_visible_status (inst3d, OBJECT_3D_SUB_OBJECT_PAYLOAD_MARKER_3_ON, FALSE);
	set_sub_object_type_visible_status (inst3d, OBJECT_3D_SUB_OBJECT_PAYLOAD_MARKER_4_ON, FALSE);

	set_sub_object_type_visible_status (inst3d, OBJECT_3D_SUB_OBJECT_PAYLOAD_MARKER_1_OFF, FALSE);
	set_sub_object_type_visible_status (inst3d, OBJECT_3D_SUB_OBJECT_PAYLOAD_MARKER_2_OFF, FALSE);
	set_sub_object_type_visible_status (inst3d, OBJECT_3D_SUB_OBJECT_PAYLOAD_MARKER_3_OFF, FALSE);
	set_sub_object_type_visible_status (inst3d, OBJECT_3D_SUB_OBJECT_PAYLOAD_MARKER_4_OFF, FALSE);

	//
	// fuel gauge
	//

	set_sub_object_type_visible_status (inst3d, OBJECT_3D_SUB_OBJECT_FUEL_GAUGE_OUTLINE, FALSE);

	set_sub_object_type_visible_status (inst3d, OBJECT_3D_SUB_OBJECT_FUEL_GAUGE_ON, FALSE);

	//
	// damage gauge
	//

	set_sub_object_type_visible_status (inst3d, OBJECT_3D_SUB_OBJECT_DAMAGE_GAUGE_OUTLINE, FALSE);

	set_sub_object_type_visible_status (inst3d, OBJECT_3D_SUB_OBJECT_DAMAGE_GAUGE_ON, FALSE);

	//
	// lights
	//

	set_sub_object_type_visible_status (inst3d, OBJECT_3D_SUB_OBJECT_PAYLOAD_LIGHTS, FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static weapon_config_types get_weapon_config (gunship_types gunship_type, const entity_sub_types current_weapon[NUM_WEAPON_LOADING_HARDPOINT_TYPES])
{
	const aircraft_data
		*ac_data;

	weapon_config_types
		min_weapon_config_type,
		max_weapon_config_type;

	const weapon_loading_gunship_type
		*wlgt;

	const weapon_loading_hardpoint_type
		*wlht;

	int
		weapon_config_package,
		hardpoint,
		ok;

	entity_sub_types
		hardpoint_weapon;

	ASSERT (gunship_type >= 0 && gunship_type < NUM_GUNSHIP_TYPES);

	ac_data = &aircraft_database[gunship_sub_types[gunship_type]];

	ASSERT (ac_data->gunship_type == gunship_type);

	min_weapon_config_type = ac_data->min_weapon_config_type;
	max_weapon_config_type = ac_data->max_weapon_config_type;

	wlgt = &weapon_loading_gunship_database[gunship_type];

	for (weapon_config_package = min_weapon_config_type; weapon_config_package <= max_weapon_config_type; weapon_config_package++)
	{
		for (hardpoint = 0; hardpoint < NUM_WEAPON_LOADING_HARDPOINT_TYPES; hardpoint++)
		{
			wlht = &wlgt->hardpoint_list[hardpoint];

			if (!wlht->valid || wlht->number_of_valid_weapon_types < 2)
			{
				continue;
			}

			hardpoint_weapon = current_weapon[hardpoint];
			ok = hardpoint_weapon == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON ? check_hardpoint_clean ((weapon_config_types)weapon_config_package, wlht->sub_object_depth1) : check_weapon_on_hardpoint ((weapon_config_types)weapon_config_package, hardpoint_weapon, wlht->sub_object_depth1);

			if (!ok)
			{
				break;
			}
		}

		if (ok)
		{
			return (weapon_config_types)weapon_config_package;
		}
	}

	return WEAPON_CONFIG_TYPE_UNARMED;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void get_weapons_from_weapon_config (gunship_types gunship_type, weapon_config_types weapon_config_type, entity_sub_types current_weapon[NUM_WEAPON_LOADING_HARDPOINT_TYPES] )
{
#ifdef DEBUG

	const aircraft_data
		*ac_data;

	weapon_config_types
		min_weapon_config_type,
		max_weapon_config_type;

#endif

	const weapon_loading_gunship_type
		*wlgt;

	const weapon_loading_hardpoint_type
		*wlht;

	int
		package,
		hardpoint;


#ifdef DEBUG

	ASSERT (gunship_type >= 0 && gunship_type < NUM_GUNSHIP_TYPES);

	ac_data = &aircraft_database[gunship_sub_types[gunship_type]];

	ASSERT (ac_data->gunship_type == gunship_type);

	min_weapon_config_type = ac_data->min_weapon_config_type;
	max_weapon_config_type = ac_data->max_weapon_config_type;

	ASSERT
	(
		(weapon_config_type == WEAPON_CONFIG_TYPE_UNARMED) ||
		(
			(weapon_config_type >= min_weapon_config_type) &&
			(weapon_config_type <= max_weapon_config_type)
		)
	);

#endif

	wlgt = &weapon_loading_gunship_database[gunship_type];

	for (hardpoint = 0; hardpoint < NUM_WEAPON_LOADING_HARDPOINT_TYPES; hardpoint++)
	{
		wlht = &wlgt->hardpoint_list[hardpoint];

		if (!wlht->valid || wlht->number_of_valid_weapon_types < 2)
		{
			continue;
		}

		current_weapon[hardpoint] = ENTITY_SUB_TYPE_WEAPON_NO_WEAPON;
	}

	for (package = 0; package < NUM_WEAPON_PACKAGES; package++)
	{
		if (weapon_config_database[weapon_config_type][package].sub_type == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
		{
			break;
		}

		for (hardpoint = 0; hardpoint < NUM_WEAPON_LOADING_HARDPOINT_TYPES; hardpoint++)
		{
			wlht = &wlgt->hardpoint_list[hardpoint];

			if (!wlht->valid || wlht->number_of_valid_weapon_types < 2)
			{
				continue;
			}

			if (weapon_config_database[weapon_config_type][package].heading_depth == wlht->sub_object_depth1)
			{
				current_weapon[hardpoint] = weapon_config_database[weapon_config_type][package].sub_type;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_hardpoint_weapons (gunship_types gunship_type, const entity_sub_types current_weapon[NUM_WEAPON_LOADING_HARDPOINT_TYPES] )
{
	const weapon_loading_gunship_type
		*wlgt;

	const weapon_loading_hardpoint_type
		*wlht;

	int
		hardpoint;

	ASSERT (gunship_type >= 0 && gunship_type < NUM_GUNSHIP_TYPES);

	wlgt = &weapon_loading_gunship_database[gunship_type];

	for (hardpoint = 0; hardpoint < NUM_WEAPON_LOADING_HARDPOINT_TYPES; hardpoint++)
	{
		wlht = &wlgt->hardpoint_list[hardpoint];

		if (!wlht->valid || wlht->number_of_valid_weapon_types < 2)
		{
			continue;
		}

		weapon_loading_set_current_hardpoint_weapon (gunship_type, (weapon_loading_hardpoint_types)hardpoint, current_weapon[hardpoint]);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void get_current_hardpoint_weapon (gunship_types gunship_type, entity_sub_types current_weapon[NUM_WEAPON_LOADING_HARDPOINT_TYPES] )
{
	const weapon_loading_gunship_type
		*wlgt;

	const weapon_loading_hardpoint_type
		*wlht;

	int
		hardpoint;

	ASSERT (gunship_type >= 0 && gunship_type < NUM_GUNSHIP_TYPES);

	wlgt = &weapon_loading_gunship_database[gunship_type];

	for (hardpoint = 0; hardpoint < NUM_WEAPON_LOADING_HARDPOINT_TYPES; hardpoint++)
	{
		wlht = &wlgt->hardpoint_list[hardpoint];

		if (!wlht->valid || wlht->number_of_valid_weapon_types < 2)
		{
			continue;
		}

		current_weapon[hardpoint] = wlht->valid_weapon_types[wlht->current_weapon_index];
		weapon_loading_set_current_hardpoint_weapon (gunship_type, (weapon_loading_hardpoint_types)hardpoint, current_weapon[hardpoint]);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void weapon_loading_set_current_hardpoint_weapon (gunship_types gunship_type, weapon_loading_hardpoint_types hardpoint, entity_sub_types weapon_type)
{
	weapon_loading_gunship_type
		*gunship_data;

	weapon_loading_hardpoint_type
		*hardpoint_data;

	int
		loop;

	gunship_data = &weapon_loading_gunship_database [gunship_type];

	ASSERT (hardpoint < NUM_WEAPON_LOADING_HARDPOINT_TYPES);

	hardpoint_data = &(gunship_data->hardpoint_list [hardpoint]);

	ASSERT (hardpoint_data->valid);

	for (loop = 0; loop < hardpoint_data->number_of_valid_weapon_types; loop ++)
	{
		if (hardpoint_data->valid_weapon_types [loop] == weapon_type)
		{
			hardpoint_data->current_weapon_index = loop;

			#if DEBUG_MODULE

			debug_log ("WN_LOAD : Hardpoint %d - weapon type ( %s )", hardpoint, entity_sub_type_weapon_names [weapon_type]);

			#endif

			return;
		}
	}

	debug_fatal ("WN_LOAD : Invalid weapon type ( %s ) on hardpoint %d", entity_sub_type_weapon_names [weapon_type], hardpoint);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity_sub_types weapon_loading_get_current_hardpoint_weapon (gunship_types gunship_type, weapon_loading_hardpoint_types hardpoint)
{
	weapon_loading_gunship_type
		*gunship_data;

	weapon_loading_hardpoint_type
		*hardpoint_data;

	gunship_data = &weapon_loading_gunship_database [gunship_type];

	ASSERT (hardpoint < NUM_WEAPON_LOADING_HARDPOINT_TYPES);

	hardpoint_data = &(gunship_data->hardpoint_list [hardpoint]);

	ASSERT (hardpoint_data->valid);

	return (hardpoint_data->valid_weapon_types [hardpoint_data->current_weapon_index]);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void weapon_loading_select_next_weapon (entity *en, weapon_loading_hardpoint_types hardpoint)
{
	weapon_loading_gunship_type
		*gunship_data;

	weapon_loading_hardpoint_type
		*hardpoint_data;

	gunship_types
		gunship_type;

	ASSERT (en);

	gunship_type = (gunship_types) get_local_entity_int_value (en, INT_TYPE_GUNSHIP_TYPE);

	ASSERT (gunship_type < NUM_GUNSHIP_TYPES);

	gunship_data = &weapon_loading_gunship_database [gunship_type];

	hardpoint_data = &(gunship_data->hardpoint_list [hardpoint]);

	ASSERT (hardpoint_data->valid);

	hardpoint_data->current_weapon_index ++;

	if (hardpoint_data->current_weapon_index >= hardpoint_data->number_of_valid_weapon_types)
	{
		hardpoint_data->current_weapon_index = 0;
	}

	if (gunship_type == GUNSHIP_TYPE_HIND && hardpoint == WEAPON_LOADING_HARDPOINT_OUTER)
	{
		weapon_loading_hardpoint_type *compare_hardpoint = &gunship_data->hardpoint_list[WEAPON_LOADING_HARDPOINT_INNER];

		// only allow gun pods on outer pylons if they're also loaded on inner
		if (compare_hardpoint->valid_weapon_types[compare_hardpoint->current_weapon_index] != ENTITY_SUB_TYPE_WEAPON_GSH23L_23MM_ROUND)
			if (hardpoint_data->valid_weapon_types[hardpoint_data->current_weapon_index] == ENTITY_SUB_TYPE_WEAPON_GSH23L_23MM_ROUND)
				hardpoint_data->current_weapon_index++;

		// only allow AT6 on outer pylons if they're also loaded on wingtips
		compare_hardpoint = &gunship_data->hardpoint_list[WEAPON_LOADING_HARDPOINT_WINGTIP];
		if (compare_hardpoint->valid_weapon_types[compare_hardpoint->current_weapon_index] != ENTITY_SUB_TYPE_WEAPON_AT6_SPIRAL)
			if (hardpoint_data->valid_weapon_types[hardpoint_data->current_weapon_index] == ENTITY_SUB_TYPE_WEAPON_AT6_SPIRAL)
				hardpoint_data->current_weapon_index++;
	}

	weapon_loading_reload_all_weapons (en);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int weapon_loading_get_valid_weapon_count (entity *en, weapon_loading_hardpoint_types hardpoint)
{
	weapon_loading_gunship_type
		*gunship_data;

	weapon_loading_hardpoint_type
		*hardpoint_data;

	gunship_types
		gunship_type;

	ASSERT (en);

	gunship_type = (gunship_types) get_local_entity_int_value (en, INT_TYPE_GUNSHIP_TYPE);

	ASSERT (gunship_type < NUM_GUNSHIP_TYPES);

	gunship_data = &weapon_loading_gunship_database [gunship_type];

	hardpoint_data = &(gunship_data->hardpoint_list [hardpoint]);

	ASSERT (hardpoint_data->valid);

	return hardpoint_data->number_of_valid_weapon_types;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void weapon_loading_set_default_air_to_air_config (entity *en)
{
	ASSERT (en);

	set_client_server_entity_int_value (en, INT_TYPE_WEAPON_CONFIG_TYPE, get_local_entity_int_value (en, INT_TYPE_AIR_TO_AIR_WEAPON_CONFIG_TYPE));

	weapon_loading_update_currently_selected_weapons (en);

	if (en == get_gunship_entity ())
	{
		set_flight_dynamics_mass ();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void weapon_loading_set_default_air_to_ground_config (entity *en)
{
	ASSERT (en);

	set_client_server_entity_int_value (en, INT_TYPE_WEAPON_CONFIG_TYPE, get_local_entity_int_value (en, INT_TYPE_AIR_TO_SURFACE_WEAPON_CONFIG_TYPE));

	weapon_loading_update_currently_selected_weapons (en);

	if (en == get_gunship_entity ())
	{
		set_flight_dynamics_mass ();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void weapon_loading_update_currently_selected_weapons (entity *en)
{
	entity_sub_types
		current_weapon [NUM_WEAPON_LOADING_HARDPOINT_TYPES];

	gunship_types
		gunship_type;

	ASSERT (en);

	gunship_type = (gunship_types) get_local_entity_int_value (en, INT_TYPE_GUNSHIP_TYPE);

	get_weapons_from_weapon_config
	(
		gunship_type,
		(weapon_config_types) get_local_entity_int_value (en, INT_TYPE_WEAPON_CONFIG_TYPE),
		current_weapon
	);

	set_hardpoint_weapons 
	(
		gunship_type,
		current_weapon
	);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void weapon_loading_reload_all_weapons (entity *en)
{
	entity_sub_types
		current_weapon [NUM_WEAPON_LOADING_HARDPOINT_TYPES];

	weapon_config_types
		new_config_type;

	gunship_types
		gunship_type;

	ASSERT (en);

	gunship_type = (gunship_types) get_local_entity_int_value (en, INT_TYPE_GUNSHIP_TYPE);

	get_current_hardpoint_weapon
	(
		gunship_type,
		current_weapon
	);

	new_config_type = get_weapon_config
	(
		gunship_type,
		current_weapon
	);

	set_client_server_entity_int_value (en, INT_TYPE_WEAPON_CONFIG_TYPE, new_config_type);

	if (en == get_gunship_entity ())
	{
		set_flight_dynamics_mass ();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_weapon_loading_hardpoint_weapon_count (entity *en, weapon_loading_hardpoint_types hardpoint, entity_sub_types weapon_type)
{
	int
		count,
		number,
		sub_type,
		damaged;

	weapon_loading_gunship_type
		*gunship_data;

	weapon_loading_hardpoint_type
		*hardpoint_data;

	gunship_types
		gunship_type;

	ASSERT (en);

	gunship_type = (gunship_types) get_local_entity_int_value (en, INT_TYPE_GUNSHIP_TYPE);

	ASSERT (gunship_type < NUM_GUNSHIP_TYPES);

	gunship_data = &weapon_loading_gunship_database [gunship_type];

	ASSERT (hardpoint < NUM_WEAPON_LOADING_HARDPOINT_TYPES);

	hardpoint_data = &(gunship_data->hardpoint_list [hardpoint]);

	ASSERT (hardpoint_data->valid);

	count = 0;

	if (hardpoint_data->sub_object_depth1 != -1)
	{
		if (get_local_entity_weapon_hardpoint_info (en, hardpoint_data->sub_object_depth1, weapon_type, &sub_type, &number, &damaged))
		{
			count += number;
		}
	}

	if (hardpoint_data->sub_object_depth2 != -1)
	{
		if (get_local_entity_weapon_hardpoint_info (en, hardpoint_data->sub_object_depth2, weapon_type, &sub_type, &number, &damaged))
		{
			count += number;
		}
	}

	return count;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




