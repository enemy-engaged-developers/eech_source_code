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

void reset_entity_weapon_config_animation (entity *en)
{
	weapon_package_status
		*package_status;

	weapon_config_types
		config_type;

	object_3d_instance
		*inst3d;

	object_3d_sub_object_search_data
		search_weapon_system_heading,
		search_weapon_system_pitch,
		search_weapon_system_weapon;

	int
		search_weapon_system_heading_depth,
		search_weapon_system_pitch_depth,
		search_weapon_system_weapon_depth,
		package;

	package_status = get_local_entity_ptr_value (en, PTR_TYPE_WEAPON_PACKAGE_STATUS_ARRAY);

	if (package_status)
	{
		config_type = get_local_entity_int_value (en, INT_TYPE_WEAPON_CONFIG_TYPE);

		ASSERT (weapon_config_type_valid (config_type));

		inst3d = get_local_entity_ptr_value (en, PTR_TYPE_INSTANCE_3D_OBJECT);

		ASSERT (inst3d);

		////////////////////////////////////////
		//
		// disable all weapons
		//
		////////////////////////////////////////

		search_weapon_system_heading_depth = 0;

		while (TRUE)
		{
			search_weapon_system_heading.search_depth = search_weapon_system_heading_depth;
			search_weapon_system_heading.search_object = inst3d;
			search_weapon_system_heading.sub_object_index = OBJECT_3D_SUB_OBJECT_WEAPON_SYSTEM_HEADING;

			if (find_object_3d_sub_object (&search_weapon_system_heading) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
			{
				search_weapon_system_pitch_depth = 0;

				while (TRUE)
				{
					search_weapon_system_pitch.search_depth = search_weapon_system_pitch_depth;
					search_weapon_system_pitch.sub_object_index = OBJECT_3D_SUB_OBJECT_WEAPON_SYSTEM_PITCH;

					if (find_object_3d_sub_object_from_sub_object (&search_weapon_system_heading, &search_weapon_system_pitch) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
					{
						search_weapon_system_pitch.result_sub_object->visible_object = FALSE;

						search_weapon_system_weapon_depth = 0;

						while (TRUE)
						{
							search_weapon_system_weapon.search_depth = search_weapon_system_weapon_depth;
							search_weapon_system_weapon.sub_object_index = OBJECT_3D_SUB_OBJECT_WEAPON_SYSTEM_WEAPON;

							if (find_object_3d_sub_object_from_sub_object (&search_weapon_system_pitch, &search_weapon_system_weapon) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
							{
								search_weapon_system_weapon.result_sub_object->visible_object = FALSE;
							}
							else
							{
								break;
							}

							search_weapon_system_weapon_depth++;
						}
					}
					else
					{
						break;
					}

					search_weapon_system_pitch_depth++;
				}
			}
			else
			{
				break;
			}

			search_weapon_system_heading_depth++;
		}

		////////////////////////////////////////
		//
		// enable weapons
		//
		////////////////////////////////////////

		for (package = 0; package < NUM_WEAPON_PACKAGES; package++)
		{
			if (weapon_config_database[config_type][package].sub_type == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
			{
				break;
			}

			ASSERT (package_status[package].number <= weapon_config_database[config_type][package].number);

			search_weapon_system_heading.search_depth = weapon_config_database[config_type][package].heading_depth;
			search_weapon_system_heading.search_object = inst3d;
			search_weapon_system_heading.sub_object_index = OBJECT_3D_SUB_OBJECT_WEAPON_SYSTEM_HEADING;

			if (find_object_3d_sub_object (&search_weapon_system_heading) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
			{
				if (weapon_config_database[config_type][package].rotate)
				{
					search_weapon_system_heading.result_sub_object->relative_heading = package_status[package].weapon_system_heading;
				}

				search_weapon_system_pitch.search_depth = weapon_config_database[config_type][package].pitch_depth;
				search_weapon_system_pitch.sub_object_index = OBJECT_3D_SUB_OBJECT_WEAPON_SYSTEM_PITCH;

				if (find_object_3d_sub_object_from_sub_object (&search_weapon_system_heading, &search_weapon_system_pitch) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
				{
					if (weapon_config_database[config_type][package].rotate)
					{
						search_weapon_system_pitch.result_sub_object->relative_pitch = -package_status[package].weapon_system_pitch;
					}

					search_weapon_system_pitch.result_sub_object->visible_object = TRUE;

					search_weapon_system_weapon_depth = weapon_config_database[config_type][package].number - package_status[package].number;

					while (TRUE)
					{
						search_weapon_system_weapon.search_depth = search_weapon_system_weapon_depth;
						search_weapon_system_weapon.sub_object_index = OBJECT_3D_SUB_OBJECT_WEAPON_SYSTEM_WEAPON;

						if (find_object_3d_sub_object_from_sub_object (&search_weapon_system_pitch, &search_weapon_system_weapon) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
						{
							search_weapon_system_weapon.result_sub_object->visible_object = TRUE;
						}
						else
						{
							break;
						}

						search_weapon_system_weapon_depth++;
					}
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_weapon_animation (entity *en)
{
	weapon
		*raw;

	ASSERT (en);

	raw = get_local_entity_data (en);

	ASSERT (entity_sub_type_weapon_valid (raw->mob.sub_type));

	switch (raw->mob.sub_type)
	{
		case ENTITY_SUB_TYPE_WEAPON_HOKUM_PILOT:
		case ENTITY_SUB_TYPE_WEAPON_HOKUM_CO_PILOT:
		{
			update_weapon_ejector_seat_animation (raw);

			break;
		}
		case ENTITY_SUB_TYPE_WEAPON_CRATE:
		{
			update_weapon_crate_animation (raw);

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
