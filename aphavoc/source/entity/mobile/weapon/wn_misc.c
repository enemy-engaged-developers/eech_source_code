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

float get_local_entity_weapon_load_weight (entity *en)
{
	float
		weapon_load_weight,
		weapon_weight,
		package_weight;

	weapon_package_status
		*package_status;

	weapon_config_types
		config_type;

	int
		package;

	ASSERT (en);

	weapon_load_weight = 0.0;

	package_status = get_local_entity_ptr_value (en, PTR_TYPE_WEAPON_PACKAGE_STATUS_ARRAY);

	if (package_status)
	{
		config_type = get_local_entity_int_value (en, INT_TYPE_WEAPON_CONFIG_TYPE);

		for (package = 0; package < NUM_WEAPON_PACKAGES; package++)
		{
			if (weapon_config_database[config_type][package].sub_type == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
			{
				break;
			}

			weapon_weight = weapon_database[weapon_config_database[config_type][package].sub_type].weight;

			package_weight = weapon_weight * package_status[package].number;

			weapon_load_weight += package_weight;
		}
	}

	return (weapon_load_weight);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_local_entity_weapon_count (entity *en, entity_sub_types weapon_sub_type)
{
	int
		weapon_count,
		package;

	weapon_package_status
		*package_status;

	weapon_config_types
		config_type;

	ASSERT (en);

	ASSERT (entity_sub_type_weapon_valid (weapon_sub_type));

	weapon_count = 0;

	if (weapon_sub_type != ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
	{
		package_status = get_local_entity_ptr_value (en, PTR_TYPE_WEAPON_PACKAGE_STATUS_ARRAY);

		if (package_status)
		{
			config_type = get_local_entity_int_value (en, INT_TYPE_WEAPON_CONFIG_TYPE);

			for (package = 0; package < NUM_WEAPON_PACKAGES; package++)
			{
				if (weapon_config_database[config_type][package].sub_type == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
				{
					break;
				}

				if (weapon_config_database[config_type][package].sub_type == weapon_sub_type)
				{
					if (!package_status[package].damaged)
					{
						weapon_count += package_status[package].number;
					}
				}
			}
		}
	}

	return (weapon_count);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int check_weapon_on_hardpoint (weapon_config_types config_type, entity_sub_types weapon_sub_type, int heading_depth)
{
	int
		package;

	for (package = 0; package < NUM_WEAPON_PACKAGES; package++)
	{
		if (weapon_config_database[config_type][package].sub_type == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
		{
			return (FALSE);
		}

		if (weapon_config_database[config_type][package].sub_type == weapon_sub_type)
		{
			if (weapon_config_database[config_type][package].heading_depth == heading_depth)
			{
				return (TRUE);
			}
		}
	}

	return (FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int check_hardpoint_clean (weapon_config_types config_type, int heading_depth)
{
	int
		package;

	for (package = 0; package < NUM_WEAPON_PACKAGES; package++)
	{
		if (weapon_config_database[config_type][package].sub_type == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
		{
			return (TRUE);
		}

		if (weapon_config_database[config_type][package].heading_depth == heading_depth)
		{
			return (FALSE);
		}
	}

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

weapon_config_types get_apache_weapon_config
(
	entity_sub_types inner_hardpoint_weapon,
	entity_sub_types outer_hardpoint_weapon,
	entity_sub_types wing_tip_weapon
)
{
	weapon_config_types
		config_type;

	int
		ok;

	for (config_type = WEAPON_CONFIG_TYPE_AH64D_APACHE_LONGBOW_1; config_type <= WEAPON_CONFIG_TYPE_AH64D_APACHE_LONGBOW_50; config_type++)
	{
		if (inner_hardpoint_weapon == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
		{
			ok = check_hardpoint_clean (config_type, APACHE_LHS_INNER_PYLON);
		}
		else
		{
			ok = check_weapon_on_hardpoint (config_type, inner_hardpoint_weapon, APACHE_LHS_INNER_PYLON);
		}

		if (ok)
		{
			if (outer_hardpoint_weapon == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
			{
				ok = check_hardpoint_clean (config_type, APACHE_LHS_OUTER_PYLON);
			}
			else
			{
				ok = check_weapon_on_hardpoint (config_type, outer_hardpoint_weapon, APACHE_LHS_OUTER_PYLON);
			}

			if (ok)
			{
				if (wing_tip_weapon == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
				{
					ok = check_hardpoint_clean (config_type, APACHE_LHS_WING_TIP_MOUNT);
				}
				else
				{
					ok = check_weapon_on_hardpoint (config_type, wing_tip_weapon, APACHE_LHS_WING_TIP_MOUNT);
				}

				if (ok)
				{
					return (config_type);
				}
			}
		}
	}

	return (WEAPON_CONFIG_TYPE_UNARMED);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

weapon_config_types get_havoc_weapon_config
(
	entity_sub_types inner_hardpoint_weapon,
	entity_sub_types outer_hardpoint_weapon
)
{
	weapon_config_types
		config_type;

	int
		ok;

	for (config_type = WEAPON_CONFIG_TYPE_MI28N_HAVOC_B_1; config_type <= WEAPON_CONFIG_TYPE_MI28N_HAVOC_B_30; config_type++)
	{
		if (inner_hardpoint_weapon == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
		{
			ok = check_hardpoint_clean (config_type, HAVOC_LHS_INNER_PYLON);
		}
		else
		{
			ok = check_weapon_on_hardpoint (config_type, inner_hardpoint_weapon, HAVOC_LHS_INNER_PYLON);
		}

		if (ok)
		{
			if (outer_hardpoint_weapon == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
			{
				ok = check_hardpoint_clean (config_type, HAVOC_LHS_OUTER_PYLON);
			}
			else
			{
				ok = check_weapon_on_hardpoint (config_type, outer_hardpoint_weapon, HAVOC_LHS_OUTER_PYLON);
			}

			if (ok)
			{
				return (config_type);
			}
		}
	}

	return (WEAPON_CONFIG_TYPE_UNARMED);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

weapon_config_types get_comanche_weapon_config
(
	entity_sub_types stub_wing_weapon,
	entity_sub_types inner_bay_door_weapon,
	entity_sub_types middle_bay_door_weapon,
	entity_sub_types outer_bay_door_weapon
)
{
	weapon_config_types
		config_type;

	int
		ok;

	for (config_type = WEAPON_CONFIG_TYPE_RAH66_COMANCHE_1; config_type <= WEAPON_CONFIG_TYPE_RAH66_COMANCHE_384; config_type++)
	{
		if (stub_wing_weapon == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
		{
			ok = check_hardpoint_clean (config_type, COMANCHE_LHS_STUB_WING);
		}
		else
		{
			ok = check_weapon_on_hardpoint (config_type, stub_wing_weapon, COMANCHE_LHS_STUB_WING);
		}

		if (ok)
		{
			if (inner_bay_door_weapon == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
			{
				ok = check_hardpoint_clean (config_type, COMANCHE_LHS_BAY_DOOR_INNER);
			}
			else
			{
				ok = check_weapon_on_hardpoint (config_type, inner_bay_door_weapon, COMANCHE_LHS_BAY_DOOR_INNER);
			}

			if (ok)
			{
				if (middle_bay_door_weapon == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
				{
					ok = check_hardpoint_clean (config_type, COMANCHE_LHS_BAY_DOOR_MIDDLE);
				}
				else
				{
					ok = check_weapon_on_hardpoint (config_type, middle_bay_door_weapon, COMANCHE_LHS_BAY_DOOR_MIDDLE);
				}

				if (ok)
				{
					if (outer_bay_door_weapon == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
					{
						ok = check_hardpoint_clean (config_type, COMANCHE_LHS_BAY_DOOR_OUTER);
					}
					else
					{
						ok = check_weapon_on_hardpoint (config_type, outer_bay_door_weapon, COMANCHE_LHS_BAY_DOOR_OUTER);
					}

					if (ok)
					{
						return (config_type);
					}
				}
			}
		}
	}

	return (WEAPON_CONFIG_TYPE_UNARMED);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

weapon_config_types get_hokum_weapon_config
(
	entity_sub_types inner_hardpoint_weapon,
	entity_sub_types outer_hardpoint_weapon
)
{
	weapon_config_types
		config_type;

	int
		ok;

	for (config_type = WEAPON_CONFIG_TYPE_KA52_HOKUM_B_1; config_type <= WEAPON_CONFIG_TYPE_KA52_HOKUM_B_30; config_type++)
	{
		if (inner_hardpoint_weapon == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
		{
			ok = check_hardpoint_clean (config_type, HOKUM_LHS_INNER_PYLON);
		}
		else
		{
			ok = check_weapon_on_hardpoint (config_type, inner_hardpoint_weapon, HOKUM_LHS_INNER_PYLON);
		}

		if (ok)
		{
			if (outer_hardpoint_weapon == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
			{
				ok = check_hardpoint_clean (config_type, HOKUM_LHS_OUTER_PYLON);
			}
			else
			{
				ok = check_weapon_on_hardpoint (config_type, outer_hardpoint_weapon, HOKUM_LHS_OUTER_PYLON);
			}

			if (ok)
			{
				return (config_type);
			}
		}
	}

	return (WEAPON_CONFIG_TYPE_UNARMED);
}
////Moje 030525 Start
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

weapon_config_types get_blackhawk_weapon_config
(
	entity_sub_types inner_hardpoint_weapon,
	entity_sub_types outer_hardpoint_weapon
)
{
	weapon_config_types
		config_type;

	int
		ok;

	for (config_type = WEAPON_CONFIG_TYPE_UH60_BLACK_HAWK_1; config_type <= WEAPON_CONFIG_TYPE_UH60_BLACK_HAWK_9; config_type++)
	{
		if (inner_hardpoint_weapon == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
		{
			ok = check_hardpoint_clean (config_type, BLACKHAWK_LHS_INNER_PYLON);
		}
		else
		{
			ok = check_weapon_on_hardpoint (config_type, inner_hardpoint_weapon, BLACKHAWK_LHS_INNER_PYLON);
		}

		if (ok)
		{
			if (outer_hardpoint_weapon == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
			{
				ok = check_hardpoint_clean (config_type, BLACKHAWK_LHS_OUTER_PYLON);
			}
			else
			{
				ok = check_weapon_on_hardpoint (config_type, outer_hardpoint_weapon, BLACKHAWK_LHS_OUTER_PYLON);
			}

			if (ok)
			{
				return (config_type);
			}
		}
	}

	return (WEAPON_CONFIG_TYPE_UNARMED);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////Moje 030525 End
////Moje 030613 start
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

weapon_config_types get_hind_weapon_config
(
	entity_sub_types inner_hardpoint_weapon,
	entity_sub_types outer_hardpoint_weapon,
	entity_sub_types wing_tip_weapon
)
{
	weapon_config_types
		config_type;

	int
		ok;

	for (config_type = WEAPON_CONFIG_TYPE_MI24D_HIND_1; config_type <= WEAPON_CONFIG_TYPE_MI24D_HIND_18; config_type++)
	{
		if (inner_hardpoint_weapon == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
		{
			ok = check_hardpoint_clean (config_type, HIND_LHS_INNER_PYLON);
		}
		else
		{
			ok = check_weapon_on_hardpoint (config_type, inner_hardpoint_weapon, HIND_LHS_INNER_PYLON);
		}

		if (ok)
		{
			if (outer_hardpoint_weapon == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
			{
				ok = check_hardpoint_clean (config_type, HIND_LHS_OUTER_PYLON);
			}
			else
			{
				ok = check_weapon_on_hardpoint (config_type, outer_hardpoint_weapon, HIND_LHS_OUTER_PYLON);
			}

			if (ok)
			{
				if (wing_tip_weapon == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
				{
					ok = check_hardpoint_clean (config_type, HIND_LHS_WING_TIP_MOUNT);
				}
				else
				{
					ok = check_weapon_on_hardpoint (config_type, wing_tip_weapon, HIND_LHS_WING_TIP_MOUNT);
				}

				if (ok)
				{
					return (config_type);
				}
			}
		}
	}

	return (WEAPON_CONFIG_TYPE_UNARMED);
}
////Moje 030613 end

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_apache_weapons_from_weapon_config
(
	weapon_config_types weapon_config_type,
	entity_sub_types *inner_hardpoint_weapon,
	entity_sub_types *outer_hardpoint_weapon,
	entity_sub_types *wing_tip_weapon
)
{
	int
		package;

	ASSERT
	(
		(weapon_config_type == WEAPON_CONFIG_TYPE_UNARMED) ||
		(
			(weapon_config_type >= WEAPON_CONFIG_TYPE_AH64D_APACHE_LONGBOW_1) &&
			(weapon_config_type <= WEAPON_CONFIG_TYPE_AH64D_APACHE_LONGBOW_50)
		)
	);

	ASSERT (inner_hardpoint_weapon);
	ASSERT (outer_hardpoint_weapon);
	ASSERT (wing_tip_weapon);

	*inner_hardpoint_weapon = ENTITY_SUB_TYPE_WEAPON_NO_WEAPON;
	*outer_hardpoint_weapon = ENTITY_SUB_TYPE_WEAPON_NO_WEAPON;
	*wing_tip_weapon = ENTITY_SUB_TYPE_WEAPON_NO_WEAPON;

	for (package = 0; package < NUM_WEAPON_PACKAGES; package++)
	{
		if (weapon_config_database[weapon_config_type][package].sub_type == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
		{
			break;
		}

		if (weapon_config_database[weapon_config_type][package].heading_depth == APACHE_LHS_INNER_PYLON)
		{
			*inner_hardpoint_weapon = weapon_config_database[weapon_config_type][package].sub_type;
		}
		else if (weapon_config_database[weapon_config_type][package].heading_depth == APACHE_LHS_OUTER_PYLON)
		{
			*outer_hardpoint_weapon = weapon_config_database[weapon_config_type][package].sub_type;
		}
		else if (weapon_config_database[weapon_config_type][package].heading_depth == APACHE_LHS_WING_TIP_MOUNT)
		{
			*wing_tip_weapon = weapon_config_database[weapon_config_type][package].sub_type;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_havoc_weapons_from_weapon_config
(
	weapon_config_types weapon_config_type,
	entity_sub_types *inner_hardpoint_weapon,
	entity_sub_types *outer_hardpoint_weapon
)
{
	int
		package;

	ASSERT
	(
		(weapon_config_type == WEAPON_CONFIG_TYPE_UNARMED) ||
		(
			(weapon_config_type >= WEAPON_CONFIG_TYPE_MI28N_HAVOC_B_1) &&
			(weapon_config_type <= WEAPON_CONFIG_TYPE_MI28N_HAVOC_B_30)
		)
	);

	ASSERT (inner_hardpoint_weapon);
	ASSERT (outer_hardpoint_weapon);

	*inner_hardpoint_weapon = ENTITY_SUB_TYPE_WEAPON_NO_WEAPON;
	*outer_hardpoint_weapon = ENTITY_SUB_TYPE_WEAPON_NO_WEAPON;

	for (package = 0; package < NUM_WEAPON_PACKAGES; package++)
	{
		if (weapon_config_database[weapon_config_type][package].sub_type == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
		{
			break;
		}

		if (weapon_config_database[weapon_config_type][package].heading_depth == HAVOC_LHS_INNER_PYLON)
		{
			*inner_hardpoint_weapon = weapon_config_database[weapon_config_type][package].sub_type;
		}
		else if (weapon_config_database[weapon_config_type][package].heading_depth == HAVOC_LHS_OUTER_PYLON)
		{
			*outer_hardpoint_weapon = weapon_config_database[weapon_config_type][package].sub_type;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_comanche_weapons_from_weapon_config
(
	weapon_config_types weapon_config_type,
	entity_sub_types *stub_wing_weapon,
	entity_sub_types *inner_bay_door_weapon,
	entity_sub_types *middle_bay_door_weapon,
	entity_sub_types *outer_bay_door_weapon
)
{
	int
		package;

	ASSERT
	(
		(weapon_config_type == WEAPON_CONFIG_TYPE_UNARMED) ||
		(
			(weapon_config_type >= WEAPON_CONFIG_TYPE_RAH66_COMANCHE_1) &&
			(weapon_config_type <= WEAPON_CONFIG_TYPE_RAH66_COMANCHE_384)
		)
	);

	ASSERT (stub_wing_weapon);
	ASSERT (inner_bay_door_weapon);
	ASSERT (middle_bay_door_weapon);
	ASSERT (outer_bay_door_weapon);

	*stub_wing_weapon = ENTITY_SUB_TYPE_WEAPON_NO_WEAPON;
	*inner_bay_door_weapon = ENTITY_SUB_TYPE_WEAPON_NO_WEAPON;
	*middle_bay_door_weapon = ENTITY_SUB_TYPE_WEAPON_NO_WEAPON;
	*outer_bay_door_weapon = ENTITY_SUB_TYPE_WEAPON_NO_WEAPON;

	for (package = 0; package < NUM_WEAPON_PACKAGES; package++)
	{
		if (weapon_config_database[weapon_config_type][package].sub_type == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
		{
			break;
		}

		if (weapon_config_database[weapon_config_type][package].heading_depth == COMANCHE_LHS_STUB_WING)
		{
			*stub_wing_weapon = weapon_config_database[weapon_config_type][package].sub_type;
		}
		else if (weapon_config_database[weapon_config_type][package].heading_depth == COMANCHE_LHS_BAY_DOOR_INNER)
		{
			*inner_bay_door_weapon = weapon_config_database[weapon_config_type][package].sub_type;
		}
		else if (weapon_config_database[weapon_config_type][package].heading_depth == COMANCHE_LHS_BAY_DOOR_MIDDLE)
		{
			*middle_bay_door_weapon = weapon_config_database[weapon_config_type][package].sub_type;
		}
		else if (weapon_config_database[weapon_config_type][package].heading_depth == COMANCHE_LHS_BAY_DOOR_OUTER)
		{
			*outer_bay_door_weapon = weapon_config_database[weapon_config_type][package].sub_type;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_hokum_weapons_from_weapon_config
(
	weapon_config_types weapon_config_type,
	entity_sub_types *inner_hardpoint_weapon,
	entity_sub_types *outer_hardpoint_weapon
)
{
	int
		package;

	ASSERT
	(
		(weapon_config_type == WEAPON_CONFIG_TYPE_UNARMED) ||
		(
			(weapon_config_type >= WEAPON_CONFIG_TYPE_KA52_HOKUM_B_1) &&
			(weapon_config_type <= WEAPON_CONFIG_TYPE_KA52_HOKUM_B_30)
		)
	);

	ASSERT (inner_hardpoint_weapon);
	ASSERT (outer_hardpoint_weapon);

	*inner_hardpoint_weapon = ENTITY_SUB_TYPE_WEAPON_NO_WEAPON;
	*outer_hardpoint_weapon = ENTITY_SUB_TYPE_WEAPON_NO_WEAPON;

	for (package = 0; package < NUM_WEAPON_PACKAGES; package++)
	{
		if (weapon_config_database[weapon_config_type][package].sub_type == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
		{
			break;
		}

		if (weapon_config_database[weapon_config_type][package].heading_depth == HOKUM_LHS_INNER_PYLON)
		{
			*inner_hardpoint_weapon = weapon_config_database[weapon_config_type][package].sub_type;
		}
		else if (weapon_config_database[weapon_config_type][package].heading_depth == HOKUM_LHS_OUTER_PYLON)
		{
			*outer_hardpoint_weapon = weapon_config_database[weapon_config_type][package].sub_type;
		}
	}
}

////Moje 030525 Start
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_blackhawk_weapons_from_weapon_config
(
	weapon_config_types weapon_config_type,
	entity_sub_types *inner_hardpoint_weapon,
	entity_sub_types *outer_hardpoint_weapon
)
{
	int
		package;

	ASSERT
	(
		(weapon_config_type == WEAPON_CONFIG_TYPE_UNARMED) ||
		(
			(weapon_config_type >= WEAPON_CONFIG_TYPE_UH60_BLACK_HAWK_1) &&
			(weapon_config_type <= WEAPON_CONFIG_TYPE_UH60_BLACK_HAWK_9)
		)
	);

	ASSERT (inner_hardpoint_weapon);
	ASSERT (outer_hardpoint_weapon);

	*inner_hardpoint_weapon = ENTITY_SUB_TYPE_WEAPON_NO_WEAPON;
	*outer_hardpoint_weapon = ENTITY_SUB_TYPE_WEAPON_NO_WEAPON;

	for (package = 0; package < NUM_WEAPON_PACKAGES; package++)
	{
		if (weapon_config_database[weapon_config_type][package].sub_type == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
		{
			break;
		}

		if (weapon_config_database[weapon_config_type][package].heading_depth == BLACKHAWK_LHS_INNER_PYLON)
		{
			*inner_hardpoint_weapon = weapon_config_database[weapon_config_type][package].sub_type;
		}
		else if (weapon_config_database[weapon_config_type][package].heading_depth == BLACKHAWK_LHS_OUTER_PYLON)
		{
			*outer_hardpoint_weapon = weapon_config_database[weapon_config_type][package].sub_type;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////Moje 030525 End
////Moj3 030613 start
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_hind_weapons_from_weapon_config
(
	weapon_config_types weapon_config_type,
	entity_sub_types *inner_hardpoint_weapon,
	entity_sub_types *outer_hardpoint_weapon,
	entity_sub_types *wing_tip_weapon
)
{
	int
		package;

	ASSERT
	(
		(weapon_config_type == WEAPON_CONFIG_TYPE_UNARMED) ||
		(
			(weapon_config_type >= WEAPON_CONFIG_TYPE_MI24D_HIND_1) &&
			(weapon_config_type <= WEAPON_CONFIG_TYPE_MI24D_HIND_18)
		)
	);

	ASSERT (inner_hardpoint_weapon);
	ASSERT (outer_hardpoint_weapon);
	ASSERT (wing_tip_weapon);

	*inner_hardpoint_weapon = ENTITY_SUB_TYPE_WEAPON_NO_WEAPON;
	*outer_hardpoint_weapon = ENTITY_SUB_TYPE_WEAPON_NO_WEAPON;
	*wing_tip_weapon = ENTITY_SUB_TYPE_WEAPON_NO_WEAPON;

	for (package = 0; package < NUM_WEAPON_PACKAGES; package++)
	{
		if (weapon_config_database[weapon_config_type][package].sub_type == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
		{
			break;
		}

		if (weapon_config_database[weapon_config_type][package].heading_depth == HIND_LHS_INNER_PYLON)
		{
			*inner_hardpoint_weapon = weapon_config_database[weapon_config_type][package].sub_type;
		}
		else if (weapon_config_database[weapon_config_type][package].heading_depth == HIND_LHS_OUTER_PYLON)
		{
			*outer_hardpoint_weapon = weapon_config_database[weapon_config_type][package].sub_type;
		}
		else if (weapon_config_database[weapon_config_type][package].heading_depth == HIND_LHS_WING_TIP_MOUNT)
		{
			*wing_tip_weapon = weapon_config_database[weapon_config_type][package].sub_type;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////Moje 030613 end
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_local_entity_weapon_damage (entity *en, int heading_depth, entity_sub_types weapon_sub_type, int damage)
{
	int
		package;

	weapon_package_status
		*package_status;

	weapon_config_types
		config_type;

	ASSERT (en);

	package_status = get_local_entity_ptr_value (en, PTR_TYPE_WEAPON_PACKAGE_STATUS_ARRAY);

	if (package_status)
	{
		config_type = get_local_entity_int_value (en, INT_TYPE_WEAPON_CONFIG_TYPE);

		for (package = 0; package < NUM_WEAPON_PACKAGES; package++)
		{
			if (weapon_config_database[config_type][package].sub_type == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
			{
				break;
			}

			if (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
			{
				if (weapon_config_database[config_type][package].heading_depth == heading_depth)
				{
					package_status[package].damaged = damage;

					break;
				}
			}
			else
			{
				if (weapon_config_database[config_type][package].sub_type == weapon_sub_type)
				{
					if (weapon_config_database[config_type][package].heading_depth == heading_depth)
					{
						package_status[package].damaged = damage;

						break;
					}
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_client_server_entity_weapon_damage (entity *en, int heading_depth, entity_sub_types weapon_sub_type, int damage)
{
	ASSERT (en);

	if (get_comms_model () == COMMS_MODEL_SERVER)
	{
		////////////////////////////////////////
		//
		// SERVER/TX and SERVER/RX
		//
		////////////////////////////////////////

		set_local_entity_weapon_damage (en, heading_depth, weapon_sub_type, damage);

		transmit_entity_comms_message (ENTITY_COMMS_DAMAGE_WEAPON_PACKAGE, en, heading_depth, weapon_sub_type, damage);
	}
	else
	{
		if (get_comms_data_flow () == COMMS_DATA_FLOW_TX)
		{
			////////////////////////////////////////
			//
			// CLIENT/TX
			//
			////////////////////////////////////////

			transmit_entity_comms_message (ENTITY_COMMS_DAMAGE_WEAPON_PACKAGE, en, heading_depth, weapon_sub_type, damage);
		}
		else
		{
			////////////////////////////////////////
			//
			// CLIENT/RX
			//
			////////////////////////////////////////

			set_local_entity_weapon_damage (en, heading_depth, weapon_sub_type, damage);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_local_entity_weapon_hardpoint_info
(
	entity *en,
	int heading_depth,
	entity_sub_types given_weapon_sub_type,
	entity_sub_types *weapon_sub_type,
	int *number,
	int *damaged
)
{
	int
		package,
		result;

	weapon_package_status
		*package_status;

	weapon_config_types
		config_type;

	ASSERT (en);

	ASSERT (weapon_sub_type);

	ASSERT (number);

	ASSERT (damaged);

	*weapon_sub_type = ENTITY_SUB_TYPE_WEAPON_NO_WEAPON;

	*number = 0;

	*damaged = FALSE;

	result = FALSE;

	package_status = get_local_entity_ptr_value (en, PTR_TYPE_WEAPON_PACKAGE_STATUS_ARRAY);

	if (package_status)
	{
		config_type = get_local_entity_int_value (en, INT_TYPE_WEAPON_CONFIG_TYPE);

		for (package = 0; package < NUM_WEAPON_PACKAGES; package++)
		{
			if (weapon_config_database[config_type][package].sub_type == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
			{
				break;
			}

			if (given_weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
			{
				if (weapon_config_database[config_type][package].heading_depth == heading_depth)
				{
					*weapon_sub_type = weapon_config_database[config_type][package].sub_type;

					*number = package_status[package].number;

					*damaged = package_status[package].damaged;

					result = TRUE;

					break;
				}
			}
			else
			{
				if (weapon_config_database[config_type][package].sub_type == given_weapon_sub_type)
				{
					if (weapon_config_database[config_type][package].heading_depth == heading_depth)
					{
						*weapon_sub_type = weapon_config_database[config_type][package].sub_type;

						*number = package_status[package].number;

						*damaged = package_status[package].damaged;

						result = TRUE;

						break;
					}
				}
			}
		}
	}

	return (result);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_comanche_stub_wing_visibility (entity *en)
{
	weapon_package_status
		*package_status;

	weapon_config_types
		config_type;

	object_3d_sub_object_search_data
		search;

	object_3d_instance
		*inst3d;

	int
		depth,
		package,
		stub_wings_required;

	ASSERT (en);

	if (get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE) != ENTITY_SUB_TYPE_AIRCRAFT_RAH66_COMANCHE)
	{
		return;
	}

	//
	// search packages for stub wings (include empty and damaged weapons)
	//

	stub_wings_required = FALSE;

	package_status = get_local_entity_ptr_value (en, PTR_TYPE_WEAPON_PACKAGE_STATUS_ARRAY);

	if (package_status)
	{
		config_type = get_local_entity_int_value (en, INT_TYPE_WEAPON_CONFIG_TYPE);

		ASSERT (weapon_config_type_valid (config_type));

		for (package = 0; package < NUM_WEAPON_PACKAGES; package++)
		{
			if (weapon_config_database[config_type][package].sub_type == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
			{
				break;
			}

			if
			(
				(weapon_config_database[config_type][package].heading_depth == COMANCHE_LHS_STUB_WING) ||
				(weapon_config_database[config_type][package].heading_depth == COMANCHE_RHS_STUB_WING)
			)
			{
				stub_wings_required = TRUE;

				break;
			}
		}
	}

	//
	// set visibility status
	//

	inst3d = get_local_entity_ptr_value (en, PTR_TYPE_INSTANCE_3D_OBJECT);

	ASSERT (inst3d);

	depth = 0;

	while (TRUE)
	{
		search.search_object = inst3d;
		search.search_depth = depth;
		search.sub_object_index = OBJECT_3D_SUB_OBJECT_STUBWINGS;

		if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
		{
			search.result_sub_object->visible_object = stub_wings_required;
		}
		else
		{
			break;
		}

		depth++;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_comanche_stub_wings_attached (entity *en)
{
	weapon_package_status
		*package_status;

	weapon_config_types
		config_type;

	int
		package;

	ASSERT (en);

	if (get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE) != ENTITY_SUB_TYPE_AIRCRAFT_RAH66_COMANCHE)
	{
		return (FALSE);
	}

	//
	// search packages for stub wings (include empty and damaged weapons)
	//

	package_status = get_local_entity_ptr_value (en, PTR_TYPE_WEAPON_PACKAGE_STATUS_ARRAY);

	if (package_status)
	{
		config_type = get_local_entity_int_value (en, INT_TYPE_WEAPON_CONFIG_TYPE);

		ASSERT (weapon_config_type_valid (config_type));

		for (package = 0; package < NUM_WEAPON_PACKAGES; package++)
		{
			if (weapon_config_database[config_type][package].sub_type == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
			{
				break;
			}

			if
			(
				(weapon_config_database[config_type][package].heading_depth == COMANCHE_LHS_STUB_WING) ||
				(weapon_config_database[config_type][package].heading_depth == COMANCHE_RHS_STUB_WING)
			)
			{
				return (TRUE);
			}
		}
	}

	return (FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
