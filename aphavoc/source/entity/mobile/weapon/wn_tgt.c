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

entity_sub_types get_best_weapon_for_target (entity *launcher, entity *target, unsigned int criteria)
{
	weapon_package_status
		*package_status;

	weapon_config_types
		config_type;

	int
		package,
		los_to_target,
		suitability[NUM_WEAPON_PACKAGES],
		suitable_weapon_count;

	entity_sub_types
		weapon_type;

	ASSERT (launcher);

	ASSERT (target);

	ASSERT (criteria <= BEST_WEAPON_CRITERIA_ALL);

	//
	// get list of weapons available on the launcher
	//

	package_status = (weapon_package_status *) get_local_entity_ptr_value (launcher, PTR_TYPE_WEAPON_PACKAGE_STATUS_ARRAY);

	if (!package_status)
	{
		return ENTITY_SUB_TYPE_WEAPON_NO_WEAPON;
	}

	config_type = (weapon_config_types) get_local_entity_int_value (launcher, INT_TYPE_WEAPON_CONFIG_TYPE);

	ASSERT (weapon_config_type_valid (config_type));

	suitable_weapon_count = 0;

	#if DEBUG_MODULE

	if (launcher == get_external_view_entity ())
	{
		debug_log ("WN_TGT : Get Suitable Weapon ( Launcher %s , Target %s )", get_local_entity_string (launcher, STRING_TYPE_FULL_NAME), get_local_entity_string (target, STRING_TYPE_FULL_NAME));

		debug_log ("WN_TGT : Available Weapon List :");
	}

	#endif

	for (package = 0; package < NUM_WEAPON_PACKAGES; package++)
	{
		suitability[package] = FALSE;

		weapon_type = weapon_config_database[config_type][package].sub_type;

		//
		// check package is valid
		//

		if (weapon_type != ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
		{
			ASSERT (package_status[package].number <= weapon_config_database[config_type][package].number);

			//
			// check warhead is capable of damage
			//

			if (weapon_is_capable_of_damage (weapon_type))
			{
				//
				// check package is not damaged
				//

				if (!package_status[package].damaged)
				{
					//
					// check package has rounds left
					//

					if (package_status[package].number > 0)
					{
						suitability[package] = TRUE;

						suitable_weapon_count ++;

						#if DEBUG_MODULE

						if (launcher == get_external_view_entity ())
						{
							debug_log ("WN_TGT : (%d) %s :", package, weapon_database[weapon_type].full_name);
						}

						#endif
					}
				}
			}
		}
	}

	if (suitable_weapon_count == 0)
	{
		return ENTITY_SUB_TYPE_WEAPON_NO_WEAPON;
	}

	//
	// filter out unsuitables with respect to weapon class
	//

	{
		int
			weapon_class,
			suitable_weapon_classes;

		#if DEBUG_MODULE

		if (launcher == get_external_view_entity ())
		{
			debug_log ("WN_TGT : Suitable Weapon List After Class Filter:");
		}

		#endif

		if (get_local_entity_int_value (target, INT_TYPE_AIRBORNE_AIRCRAFT))
		{
			//
			// target is an aircraft in the air
			//

			suitable_weapon_classes = WEAPON_CLASS_AIR_TO_AIR + WEAPON_CLASS_SURFACE_TO_AIR;
		}
		else
		{
			//
			// target is an aircraft or a vehicle on the ground
			//

			suitable_weapon_classes = WEAPON_CLASS_AIR_TO_SURFACE + WEAPON_CLASS_SURFACE_TO_SURFACE;
		}

		for (package = 0; package < NUM_WEAPON_PACKAGES; package++)
		{
			if (suitability[package])
			{
				weapon_type = weapon_config_database[config_type][package].sub_type;

				weapon_class = weapon_database[weapon_type].weapon_class;

				//
				// bitwise AND to test weapon class compatibility
				//

				if ((suitable_weapon_classes & weapon_class) == 0)
				{
					suitability[package] = FALSE;

					suitable_weapon_count --;
				}
				else
				{
					if (criteria & BEST_WEAPON_ALTITUDE_CHECK)
					{
						//
						// if target is airborne, and launcher is a vehicle - check launchers floor and ceiling scanning ability
						//

						if ((get_local_entity_int_value (target, INT_TYPE_AIRBORNE_AIRCRAFT)) && (get_local_entity_int_value (launcher, INT_TYPE_IDENTIFY_VEHICLE)))
						{
							float
								target_altitude;

							target_altitude = get_local_entity_float_value (target, FLOAT_TYPE_RADAR_ALTITUDE);

							if ((target_altitude > get_local_entity_float_value (launcher, FLOAT_TYPE_AIR_SCAN_CEILING)) ||
									(target_altitude < get_local_entity_float_value (launcher, FLOAT_TYPE_AIR_SCAN_FLOOR)))
							{
								suitability[package] = FALSE;

								suitable_weapon_count --;
							}
						}
					}
					
				//magitek: revise this!
#if 0  // disable until we have a way of aborting attacking other targets until air defences are out of the way
					// TODO: not do for some criteria?
					if (get_local_entity_int_value(launcher, INT_TYPE_AIRBORNE_AIRCRAFT)
							 && get_local_entity_int_value(target, INT_TYPE_VIEW_CATEGORY) == VIEW_CATEGORY_AIR_DEFENCE_UNITS)
					{
						// don't try to take out anti-aircaft systems with unguided weapons, it's suicide
						if (weapon_database[weapon_type].guidance_type == WEAPON_GUIDANCE_TYPE_NONE)
						{
							suitability[package] = FALSE;
							suitable_weapon_count --;
						}
					}
#endif
				}
				#if DEBUG_MODULE

				if (launcher == get_external_view_entity ())
				{
					if (suitability [package])
					{
						debug_log ("WN_TGT : (%d) %s :", package, weapon_database[weapon_type].full_name);
					}
				}

				#endif
			}
		}
	}

	if (suitable_weapon_count == 0)
	{
		return ENTITY_SUB_TYPE_WEAPON_NO_WEAPON;
	}

	//
	// special case for vehicles - only fire projectiles if no line of sight
	//

	if (criteria & BEST_WEAPON_LOS_CHECK)
	{
		if (get_local_entity_int_value (launcher, INT_TYPE_IDENTIFY_VEHICLE))
		{
			los_to_target = check_entity_line_of_sight (launcher, target, MOBILE_LOS_CHECK_COURSE_TERRAIN);

			set_local_entity_int_value (launcher, INT_TYPE_LOS_TO_TARGET, los_to_target);

			if (!los_to_target)
			{
				#if DEBUG_MODULE

				if (launcher == get_external_view_entity ())
				{
					debug_log ("WN_TGT : Suitable Weapon List After LOS Filter :");
				}

				#endif

				for (package = 0; package < NUM_WEAPON_PACKAGES; package++)
				{
					if (suitability[package])
					{
						weapon_type = weapon_config_database[config_type][package].sub_type;

						if (weapon_database[weapon_type].aiming_type != WEAPON_AIMING_TYPE_CALC_ANGLE_OF_PROJECTION)
						{
							suitability[package] = FALSE;

							suitable_weapon_count --;
						}
						#if DEBUG_MODULE
						else
						{
							if (launcher == get_external_view_entity ())
							{
								debug_log ("WN_TGT : (%d) %s :", package, weapon_database[weapon_type].full_name);
							}
						}
						#endif
					}
				}
			}
		}

		if (suitable_weapon_count == 0)
		{
			return ENTITY_SUB_TYPE_WEAPON_NO_WEAPON;
		}
	}

	//
	// filter out unsuitables with respect to range
	//

	if (criteria & BEST_WEAPON_RANGE_CHECK)
	{
		float
			target_range,
			min_weapon_range,
			max_weapon_range;

		vec3d
			*launcher_pos,
			*target_pos;

		launcher_pos = get_local_entity_vec3d_ptr (launcher, VEC3D_TYPE_POSITION);

		target_pos = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

		target_range = get_approx_3d_range (launcher_pos, target_pos);

		#if DEBUG_MODULE

		if (launcher == get_external_view_entity ())
		{
			debug_log ("WN_TGT : Suitable Weapon List After Range Filter ( Range = %f ) :", target_range);
		}

		#endif

		for (package = 0; package < NUM_WEAPON_PACKAGES; package++)
		{
			if (suitability[package])
			{
				weapon_type = weapon_config_database[config_type][package].sub_type;

				min_weapon_range = weapon_database[weapon_type].min_range;
//				max_weapon_range = weapon_database[weapon_type].max_range;
				max_weapon_range = weapon_database[weapon_type].effective_range;

				if ((target_range < min_weapon_range) || (target_range > max_weapon_range))
				{
					suitability[package] = FALSE;

					suitable_weapon_count --;
				}
				#if DEBUG_MODULE
				else
				{
					if (launcher == get_external_view_entity ())
					{
						debug_log ("WN_TGT : (%d) %s :", package, weapon_database[weapon_type].full_name);
					}
				}
				#endif
			}
		}

		if (suitable_weapon_count == 0)
		{
			return ENTITY_SUB_TYPE_WEAPON_NO_WEAPON;
		}
	}

	//
	// find how much damage each weapon could possibly cause
	//

	{
		int
			target_damage_level,
			damage_capability,
			total_damage_possible;

		target_damage_level = get_local_entity_int_value (target, INT_TYPE_DAMAGE_LEVEL);//magitek, doubled target_health for calculation purposes

		ASSERT (target_damage_level > 0);

		#if DEBUG_MODULE

		if (launcher == get_external_view_entity ())
		{
			debug_log ("WN_TGT : Suitable Weapon List After Damage Filter ( current damage level = %d ) :", target_damage_level);
		}

		#endif

		for (package = 0; package < NUM_WEAPON_PACKAGES; package++)
		{
			if (suitability[package])
			{
				weapon_type = weapon_config_database[config_type][package].sub_type;

				if (weapon_database[weapon_type].rate_of_fire == FIRE_SINGLE_WEAPON)
				{
					damage_capability = weapon_is_suitable_for_damaging_target (weapon_type, target, TRUE);
				}
				else
				{
					switch (get_local_entity_type (launcher))
					{
						case ENTITY_TYPE_FIXED_WING:
						{
							damage_capability = (weapon_is_suitable_for_damaging_target (weapon_type, target, TRUE)
											* weapon_database[weapon_type].rate_of_fire
											* weapon_database[weapon_type].burst_duration);
							break;
						}
						case ENTITY_TYPE_HELICOPTER:
						{
							damage_capability = (weapon_is_suitable_for_damaging_target (weapon_type, target, TRUE)
											* weapon_database[weapon_type].rate_of_fire
											* weapon_database[weapon_type].burst_duration);
							break;
						}
						
						default:
						{
							damage_capability = (weapon_is_suitable_for_damaging_target (weapon_type, target, TRUE)
											* weapon_database[weapon_type].rate_of_fire
											* weapon_database[weapon_type].burst_duration);
							break;
						}
					}
				}

				total_damage_possible = min (damage_capability, target_damage_level);

				suitability[package] = total_damage_possible;

				if (total_damage_possible == 0)
				{
					suitable_weapon_count --;
				}
				#if DEBUG_MODULE
				else
				{
					if (launcher == get_external_view_entity ())
					{
						debug_log ("WN_TGT : (%d) %s - damage %d", package, weapon_database[weapon_type].full_name, total_damage_possible);
					}
				}
				#endif
			}
		}
	}

	if (suitable_weapon_count == 0)
	{
		return ENTITY_SUB_TYPE_WEAPON_NO_WEAPON;
	}

	//
	// guided weapons are generally more suitable...
	//

	for (package = 0; package < NUM_WEAPON_PACKAGES; package++)
	{
		weapon_type = weapon_config_database[config_type][package].sub_type;

		if (weapon_database[weapon_type].guidance_type != WEAPON_GUIDANCE_TYPE_NONE)
		{
			suitability[package] *= 4;
		}
	}

	//
	// Special case :- Aircraft should only use guided missiles against other aircraft
	//

	if (get_local_entity_int_value (launcher, INT_TYPE_IDENTIFY_AIRCRAFT))
	{
		if (get_local_entity_int_value (target, INT_TYPE_AIRBORNE_AIRCRAFT))
		{
			for (package = 0; package < NUM_WEAPON_PACKAGES; package++)
			{
				weapon_type = weapon_config_database[config_type][package].sub_type;

				if (weapon_database[weapon_type].guidance_type == WEAPON_GUIDANCE_TYPE_NONE)
				{
					suitability[package] = 0;
				}
			}
		}
	}

	//
	// find the most suitable weapon
	//

	{
		int
			highest_suitability;

		highest_suitability = 0;

		weapon_type = ENTITY_SUB_TYPE_WEAPON_NO_WEAPON;

		switch (get_local_entity_type (launcher))
		{
			case ENTITY_TYPE_FIXED_WING:
			{
				for (package = NUM_WEAPON_PACKAGES-1; package > 0; package--)
				{
					if (suitability[package] > highest_suitability)
					{
						weapon_type = weapon_config_database[config_type][package].sub_type;

						highest_suitability = suitability[package];
					}
				}
				break;
			}
			
			default:
			{
				for (package = 0; package < NUM_WEAPON_PACKAGES; package++)
				{
					if (suitability[package] > highest_suitability)
					{
						weapon_type = weapon_config_database[config_type][package].sub_type;

						highest_suitability = suitability[package];
					}
				}
				break;
			}
		}

		#if DEBUG_MODULE

		if (launcher == get_external_view_entity ())
		{
			debug_log ("WN_TGT : BEST WEAPON %s - damage %d", weapon_database[weapon_type].full_name, highest_suitability);
		}

		#endif
	}

	return weapon_type;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_local_entity_max_weapon_range (entity *launcher)
{
	weapon_package_status
		*package_status;

	weapon_config_types
		config_type;

	int
		package;

	float
		range,
		max_range;

	entity_sub_types
		weapon_type;

	ASSERT (launcher);

	max_range = 0.0;

	//
	// get list of weapons available on the launcher
	//

	package_status = (weapon_package_status *) get_local_entity_ptr_value (launcher, PTR_TYPE_WEAPON_PACKAGE_STATUS_ARRAY);

	if (!package_status)
	{
		return 0.0;
	}

	config_type = (weapon_config_types) get_local_entity_int_value (launcher, INT_TYPE_WEAPON_CONFIG_TYPE);

	ASSERT (weapon_config_type_valid (config_type));

	for (package = 0; package < NUM_WEAPON_PACKAGES; package++)
	{
		weapon_type = weapon_config_database[config_type][package].sub_type;

		if (weapon_type != ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
		{
			ASSERT (package_status[package].number <= weapon_config_database[config_type][package].number);

			range = weapon_database [weapon_type].max_range;

			if (range > max_range)
			{
				//
				// check warhead is capable of damage
				//

				if (weapon_is_capable_of_damage (weapon_type))
				{
					//
					// check package is not damaged
					//

					if (!package_status[package].damaged)
					{
						//
						// check package has rounds left
						//

						if (package_status[package].number > 0)
						{
							max_range = range;
						}
					}
				}
			}
		}
	}

	return max_range;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_local_group_max_weapon_range (entity *group)
{
	entity
		*en;

	float
		max_range;

	ASSERT (group);

	max_range = 0;

	en = get_local_entity_first_child (group, LIST_TYPE_MEMBER);

	while (en)
	{
		max_range = max (max_range, get_local_entity_max_weapon_range (en));

		en = get_local_entity_child_succ (en, LIST_TYPE_MEMBER);
	}

	return max_range;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
