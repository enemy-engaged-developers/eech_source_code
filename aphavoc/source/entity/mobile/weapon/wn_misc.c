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

void get_local_entity_weapon_load(entity* en, weapon_count weapon_load[], unsigned max_num_weapons)
{
	weapon_package_status
		*package_status;

	unsigned next_free = 0;

	ASSERT(en);
	ASSERT(weapon_load);
	ASSERT(max_num_weapons > 0);

	package_status = (weapon_package_status *) get_local_entity_ptr_value(en, PTR_TYPE_WEAPON_PACKAGE_STATUS_ARRAY);

	if (package_status)
	{
		int package;
		weapon_config_types config_type = (weapon_config_types) get_local_entity_int_value (en, INT_TYPE_WEAPON_CONFIG_TYPE);

		for (package = 0; package < NUM_WEAPON_PACKAGES; package++)
		{
			entity_sub_types weapon_type;
			int number;

			if (weapon_config_database[config_type][package].sub_type != ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
			{
				if (!package_status[package].damaged)
				{
					unsigned i;

					weapon_type = weapon_config_database[config_type][package].sub_type;
					number = package_status[package].number;

					for (i=0; i < next_free; i++)
					{
						if (weapon_load[i].weapon_type == weapon_type)
						{
							weapon_load[i].count += number;
							break;
						}
					}

					if (i == next_free && next_free <= max_num_weapons-1 && weapon_type != ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)  // weapon not in array already
					{
						next_free++;
						weapon_load[i].weapon_type = weapon_type;
						weapon_load[i].count = number;
					}
				}
			}
		}
	}

	weapon_load[next_free].weapon_type = ENTITY_SUB_TYPE_WEAPON_NO_WEAPON;
}

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

	package_status = (weapon_package_status *) get_local_entity_ptr_value (en, PTR_TYPE_WEAPON_PACKAGE_STATUS_ARRAY);

	if (package_status)
	{
		config_type = (weapon_config_types) get_local_entity_int_value (en, INT_TYPE_WEAPON_CONFIG_TYPE);

		for (package = 0; package < NUM_WEAPON_PACKAGES; package++)
		{
			if (weapon_config_database[config_type][package].sub_type != ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
			{
				weapon_weight = weapon_database[weapon_config_database[config_type][package].sub_type].start_weight;

				package_weight = weapon_weight * package_status[package].number;

				weapon_load_weight += package_weight;
			}
		}
	}
	
	// cargo weight
	
	{
		entity
			*group,
			*guide,
			*task;

		group = get_local_entity_parent (en, LIST_TYPE_MEMBER);

		if (group->group_data->sub_type == ENTITY_SUB_TYPE_GROUP_HEAVY_LIFT_TRANSPORT_HELICOPTER || group->group_data->sub_type == ENTITY_SUB_TYPE_GROUP_MEDIUM_LIFT_TRANSPORT_HELICOPTER)
		{
			guide = get_local_group_primary_guide (group);

			if (guide)
			{
				task = get_local_entity_parent (guide, LIST_TYPE_GUIDE);

				if (task->task_data->sub_type == ENTITY_SUB_TYPE_TASK_SUPPLY)
				{
					if (group->group_data->sub_type == ENTITY_SUB_TYPE_GROUP_HEAVY_LIFT_TRANSPORT_HELICOPTER)
						weapon_load_weight += 6000;
					else
						weapon_load_weight += 2000;
				}
			}
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
		package_status = (weapon_package_status *) get_local_entity_ptr_value (en, PTR_TYPE_WEAPON_PACKAGE_STATUS_ARRAY);

		if (package_status)
		{
			config_type = (weapon_config_types) get_local_entity_int_value (en, INT_TYPE_WEAPON_CONFIG_TYPE);

			for (package = 0; package < NUM_WEAPON_PACKAGES; package++)
			{
				if (weapon_config_database[config_type][package].sub_type != ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
				{
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
	}

	return (weapon_count);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int check_weapon_on_hardpoint (weapon_config_types config_type, entity_sub_types weapon_sub_type, int heading_depth)
{
	int
		package;

	for (package = 0; package < NUM_WEAPON_PACKAGES; package++)
	{
		if (weapon_config_database[config_type][package].sub_type != ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
		{
			if (weapon_config_database[config_type][package].sub_type == weapon_sub_type)
			{
				if (weapon_config_database[config_type][package].heading_depth == heading_depth)
				{
					return (TRUE);
				}
			}
		}
	}

	return (FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int check_hardpoint_clean (weapon_config_types config_type, int heading_depth)
{
	int
		package;

	for (package = 0; package < NUM_WEAPON_PACKAGES; package++)
		if (weapon_config_database[config_type][package].sub_type != ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
			if (weapon_config_database[config_type][package].heading_depth == heading_depth)
				return (FALSE);

	return (TRUE);
}

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

	package_status = (weapon_package_status *) get_local_entity_ptr_value (en, PTR_TYPE_WEAPON_PACKAGE_STATUS_ARRAY);

	if (package_status)
	{
		config_type = (weapon_config_types) get_local_entity_int_value (en, INT_TYPE_WEAPON_CONFIG_TYPE);

		for (package = 0; package < NUM_WEAPON_PACKAGES; package++)
		{
			if (weapon_config_database[config_type][package].sub_type != ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
			{
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

	package_status = (weapon_package_status *) get_local_entity_ptr_value (en, PTR_TYPE_WEAPON_PACKAGE_STATUS_ARRAY);

	if (package_status)
	{
		config_type = (weapon_config_types) get_local_entity_int_value (en, INT_TYPE_WEAPON_CONFIG_TYPE);

		for (package = 0; package < NUM_WEAPON_PACKAGES; package++)
		{
			if (weapon_config_database[config_type][package].sub_type != ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
			{
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

	object_3d_instance
		*inst3d;

	int
		package,
		stub_wings_required;

	ASSERT (en);

	if (get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE) != ENTITY_SUB_TYPE_AIRCRAFT_RAH66_COMANCHE && get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE) != ENTITY_SUB_TYPE_AIRCRAFT_OH58D_KIOWA_WARRIOR)
	{
		return;
	}

	//
	// search packages for stub wings (include empty and damaged weapons)
	//

	stub_wings_required = FALSE;

	package_status = (weapon_package_status *) get_local_entity_ptr_value (en, PTR_TYPE_WEAPON_PACKAGE_STATUS_ARRAY);

	if (package_status)
	{
		config_type = (weapon_config_types) get_local_entity_int_value (en, INT_TYPE_WEAPON_CONFIG_TYPE);

		ASSERT (weapon_config_type_valid (config_type));

		for (package = 0; package < NUM_WEAPON_PACKAGES; package++)
		{
			if (weapon_config_database[config_type][package].sub_type != ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
			{
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
	}

	//
	// set visibility status
	//

	inst3d = (object_3d_instance *) get_local_entity_ptr_value (en, PTR_TYPE_INSTANCE_3D_OBJECT);

	ASSERT (inst3d);

	set_sub_object_type_visible_status(inst3d, OBJECT_3D_SUB_OBJECT_STUBWINGS, stub_wings_required);
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

	if (get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE) != ENTITY_SUB_TYPE_AIRCRAFT_RAH66_COMANCHE && get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE) != ENTITY_SUB_TYPE_AIRCRAFT_OH58D_KIOWA_WARRIOR)
		return (TRUE);

	//
	// search packages for stub wings (include empty and damaged weapons)
	//

	package_status = (weapon_package_status *) get_local_entity_ptr_value (en, PTR_TYPE_WEAPON_PACKAGE_STATUS_ARRAY);

	if (package_status)
	{
		config_type = (weapon_config_types) get_local_entity_int_value (en, INT_TYPE_WEAPON_CONFIG_TYPE);

		ASSERT (weapon_config_type_valid (config_type));

		for (package = 0; package < NUM_WEAPON_PACKAGES; package++)
		{
			if (weapon_config_database[config_type][package].sub_type != ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
				if
				(
					(weapon_config_database[config_type][package].heading_depth == COMANCHE_LHS_STUB_WING) ||
					(weapon_config_database[config_type][package].heading_depth == COMANCHE_RHS_STUB_WING)
				)
					return (TRUE);
		}
	}

	return (FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
