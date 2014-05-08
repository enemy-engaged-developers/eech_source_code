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
		suitable_weapon_count,
		debug_flag = 0,
		damage_by_type[NUM_ENTITY_SUB_TYPE_WEAPONS];

	entity_sub_types
		weapon_type;

	vec3d
		*launcher_pos,
		*target_pos;
	float
		target_range;

	ASSERT (launcher);

	ASSERT (target);

	ASSERT (criteria <= BEST_WEAPON_CRITERIA_ALL);

#if DEBUG_MODULE

	if (launcher == get_external_view_entity ())
		debug_flag = DEBUG_MODULE;
	if (get_gunship_entity())
		if (launcher == (get_local_entity_parent (get_gunship_entity(), LIST_TYPE_TARGET)))
			debug_flag = DEBUG_MODULE;

#endif

	// get list of weapons available on the launcher

	package_status = (weapon_package_status *) get_local_entity_ptr_value (launcher, PTR_TYPE_WEAPON_PACKAGE_STATUS_ARRAY);

	if (!package_status)
		return ENTITY_SUB_TYPE_WEAPON_NO_WEAPON;

	config_type = (weapon_config_types) get_local_entity_int_value (launcher, INT_TYPE_WEAPON_CONFIG_TYPE);

	ASSERT (weapon_config_type_valid (config_type));

	for (package = 1; package < NUM_ENTITY_SUB_TYPE_WEAPONS; package++)
		damage_by_type[package] = 0;
	
	suitable_weapon_count = 0;

	if (get_local_entity_type (launcher) == ENTITY_TYPE_SHIP_VEHICLE) // disable out of angle weapons
		suppress_ineffective_ship_weapons (launcher, target);

	launcher_pos = get_local_entity_vec3d_ptr (launcher, VEC3D_TYPE_POSITION);
	target_pos = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);
	target_range = get_3d_range (launcher_pos, target_pos);

	if (debug_flag)
	{
		debug_log ("WN_TGT : Get Suitable Weapon ( Launcher %s , Target %s )", get_local_entity_string (launcher, STRING_TYPE_FULL_NAME), get_local_entity_string (target, STRING_TYPE_FULL_NAME));

		debug_log ("WN_TGT : Available Weapon List :");
	}

	for (package = 0; package < NUM_WEAPON_PACKAGES; package++)
	{
		suitability[package] = FALSE;

		weapon_type = weapon_config_database[config_type][package].sub_type;

		// check package is valid

		if (weapon_type != ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
		{
			ASSERT (package_status[package].number <= weapon_config_database[config_type][package].number);

			// check warhead is capable of damage

			if (!weapon_database[weapon_type].rate_of_fire ?
				(weapon_damage_capability (NULL, target, 0.0, weapon_type, 0.75) * weapon_config_database[config_type][package].salvo_size) :
				(weapon_damage_capability (NULL, target, 0.0, weapon_type, 0.75)
										* weapon_database[weapon_type].rate_of_fire
										* weapon_database[weapon_type].burst_duration / 60))
			{
				// check package is not damaged

				if (!package_status[package].damaged)
				{
					// check package has rounds left

					if (package_status[package].number > 0)
					{
						suitability[package] = TRUE;

						suitable_weapon_count ++;
					}
				}
			}

			if (debug_flag)
			{
				debug_log ("WN_TGT : (%d) %s : damaged %i, ammo left %i, capable of damage %i", package, weapon_database[weapon_type].full_name, package_status[package].damaged, package_status[package].number, suitability[package]);
			}
		}
	}

	if (suitable_weapon_count == 0)
	{
		return ENTITY_SUB_TYPE_WEAPON_NO_WEAPON;
	}

	// filter out unsuitables with respect to weapon class

	{
		int
			weapon_class,
			suitable_weapon_classes;

		if (debug_flag)
		{
			debug_log ("WN_TGT : Class Filter:");
		}

		for (package = 0; package < NUM_WEAPON_PACKAGES; package++)
		{
			weapon_type = weapon_config_database[config_type][package].sub_type;
			
			if (get_local_entity_int_value (target, INT_TYPE_AIRBORNE_AIRCRAFT) && get_local_entity_type (target) == ENTITY_TYPE_FIXED_WING)
			{
				// fixed wing

				suitable_weapon_classes = !(weapon_database[weapon_type].guidance_type && WEAPON_CLASS_AIR_TO_SURFACE) * WEAPON_CLASS_AIR_TO_AIR + WEAPON_CLASS_SURFACE_TO_AIR; // do not use shturm, vikhr etc. against jets!
			}
			else if (get_local_entity_int_value (target, INT_TYPE_AIRBORNE_AIRCRAFT))
			{
				// heli, missile

				suitable_weapon_classes = WEAPON_CLASS_AIR_TO_AIR + WEAPON_CLASS_SURFACE_TO_AIR + WEAPON_CLASS_SURFACE_TO_SURFACE * (target_range < 200 && !weapon_database[weapon_type].guidance_type && weapon_database[weapon_type].aiming_type != WEAPON_AIMING_TYPE_CALC_ANGLE_OF_PROJECTION); // small exception for close slow targets
			}
			else
			{
				// target is an aircraft or a vehicle on the ground

				suitable_weapon_classes = WEAPON_CLASS_AIR_TO_SURFACE + WEAPON_CLASS_SURFACE_TO_SURFACE;
			}

			if (suitability[package])
			{
				weapon_class = weapon_database[weapon_type].weapon_class;

				// bitwise AND to test weapon class compatibility

				if ((suitable_weapon_classes & weapon_class) == 0)
				{
					suitability[package] = FALSE;

					suitable_weapon_count --;
				}

				if (criteria & BEST_WEAPON_ALTITUDE_CHECK && get_local_entity_int_value (launcher, INT_TYPE_AIRBORNE_AIRCRAFT))
				{
					// if target is airborne, and launcher is a vehicle - check launchers floor and ceiling scanning ability

					if ((get_local_entity_int_value (target, INT_TYPE_AIRBORNE_AIRCRAFT)) && (get_local_entity_int_value (launcher, INT_TYPE_IDENTIFY_VEHICLE)) &&
							(weapon_database [weapon_type].guidance_type == WEAPON_GUIDANCE_TYPE_SEMI_ACTIVE_RADAR || weapon_database [weapon_type].guidance_type == WEAPON_GUIDANCE_TYPE_ACTIVE_RADAR))
					{
						float
							target_altitude;

						target_altitude = get_local_entity_float_value (target, FLOAT_TYPE_RADAR_ALTITUDE);

						if ((target_altitude > get_local_entity_float_value (launcher, FLOAT_TYPE_AIR_SCAN_CEILING)) ||
								(target_altitude < get_local_entity_float_value (launcher, FLOAT_TYPE_AIR_SCAN_FLOOR)))
						{
							if(suitability[package])
							{
								suitability[package] = FALSE;

								suitable_weapon_count --;
							}
						}
					}
				}

				if (debug_flag && !suitability[package])
				{
					debug_log ("WN_TGT : (%d) %s : EXCLUDED", package, weapon_database[weapon_type].full_name);
				}
			}
		}
	}

	if (suitable_weapon_count == 0)
	{
		return ENTITY_SUB_TYPE_WEAPON_NO_WEAPON;
	}

	// special case for vehicles - only fire projectiles if no line of sight

	if (criteria & BEST_WEAPON_LOS_CHECK)
	{
		if (get_local_entity_int_value (launcher, INT_TYPE_IDENTIFY_VEHICLE))
		{
			los_to_target = check_entity_line_of_sight (launcher, target, MOBILE_LOS_CHECK_COURSE_TERRAIN);

			set_local_entity_int_value (launcher, INT_TYPE_LOS_TO_TARGET, los_to_target);

			if (!los_to_target)
			{
				if (debug_flag)
				{
					debug_log ("WN_TGT : LOS Filter :");
				}

				for (package = 0; package < NUM_WEAPON_PACKAGES; package++)
				{
					if (suitability[package])
					{
						weapon_type = weapon_config_database[config_type][package].sub_type;

						if (weapon_database[weapon_type].aiming_type != WEAPON_AIMING_TYPE_CALC_ANGLE_OF_PROJECTION || target_range < 8000 )
						{
							suitability[package] = FALSE;

							suitable_weapon_count --;
							
							if (debug_flag)
							{
								debug_log ("WN_TGT : (%d) %s : EXCLUDED", package, weapon_database[weapon_type].full_name);
							}
						}
					}
				}
			}
		}

		if (suitable_weapon_count == 0)
		{
			return ENTITY_SUB_TYPE_WEAPON_NO_WEAPON;
		}
	}

	// filter out unsuitables with respect to range

	if (criteria & BEST_WEAPON_RANGE_CHECK)
	{
		float
			min_weapon_range,
			max_weapon_range;

		if (debug_flag)
		{
			debug_log ("WN_TGT : Range Filter ( Range = %f ) :", target_range);
		}

		for (package = 0; package < NUM_WEAPON_PACKAGES; package++)
		{
			if (suitability[package])
			{
				weapon_type = weapon_config_database[config_type][package].sub_type;

				min_weapon_range = weapon_database[weapon_type].min_range;
				max_weapon_range = weapon_database[weapon_type].effective_range;
				
				switch(get_local_entity_int_value(target, INT_TYPE_VIEW_CATEGORY))
				{
					case VIEW_CATEGORY_COMBAT_HELICOPTERS:
					{
						if (weapon_database[weapon_type].guidance_type)
							max_weapon_range = max(weapon_database[weapon_type].effective_range, 0.9 * weapon_database[weapon_type].max_range);
						break;
					}
					case VIEW_CATEGORY_WARSHIPS:
					case VIEW_CATEGORY_AIR_DEFENCE_UNITS:
					{
						max_weapon_range = max(weapon_database[weapon_type].effective_range, 0.9 * weapon_database[weapon_type].max_range);
						break;
					}
				}
				
				if (!weapon_database[weapon_type].guidance_type && (get_local_entity_type (target) == ENTITY_TYPE_WEAPON || get_local_entity_int_value (target, INT_TYPE_AIRBORNE_AIRCRAFT)))
					max_weapon_range = weapon_database[weapon_type].max_range;

				if ((target_range < min_weapon_range) || (target_range > max_weapon_range))
				{
					suitability[package] = FALSE;

					suitable_weapon_count --;

					if (debug_flag)
					{
						debug_log ("WN_TGT : (%d) %s : EXCLUDED (min_range %.1f, max_range %.1f", package, weapon_database[weapon_type].full_name, min_weapon_range, max_weapon_range);
					}
				}
			}
		}

		if (suitable_weapon_count == 0)
		{
			return ENTITY_SUB_TYPE_WEAPON_NO_WEAPON;
		}
	}

	// find how much damage each weapon could possibly cause

	if (get_local_entity_type (target) != ENTITY_TYPE_WEAPON)
	{
		int
			target_damage_level,
			damage_capability,
			total_damage_possible;

		target_damage_level = 2 * get_local_entity_int_value (target, INT_TYPE_DAMAGE_LEVEL);
		
		ASSERT (target_damage_level > 0);

		if (target_damage_level <= 0) // something wrong, abort
			return ENTITY_SUB_TYPE_WEAPON_NO_WEAPON;

		if (debug_flag)
		{
			debug_log ("WN_TGT : Damage Filter ( target damage level = %d ) :", target_damage_level / 2);
		}

		for (package = 0; package < NUM_WEAPON_PACKAGES; package++)
		{
			float damage_multiplier = 1;
			
			if (suitability[package])
			{
				weapon_type = weapon_config_database[config_type][package].sub_type;

				if (weapon_database[weapon_type].rate_of_fire == FIRE_SINGLE_WEAPON)
				{
					damage_capability = weapon_damage_capability (NULL, target, 0.0, weapon_type, 0.75) * weapon_config_database[config_type][package].salvo_size;
				}
				else
				{
					damage_capability = weapon_damage_capability (NULL, target, 0.0, weapon_type, 0.75)
									* weapon_database[weapon_type].rate_of_fire
									* weapon_database[weapon_type].burst_duration / 60;
				}

				if (weapon_database[weapon_type].guidance_type != WEAPON_GUIDANCE_TYPE_NONE) //	 guided weapons are generally more suitable for air target except close range
				{
					damage_multiplier = target_range / 1000 + 1;

					if (get_local_entity_int_value (target, INT_TYPE_AIRBORNE_AIRCRAFT) && !(weapon_database[weapon_type].weapon_class & WEAPON_CLASS_AIR_TO_SURFACE))
						damage_multiplier *= 2;

					total_damage_possible = damage_multiplier * min (damage_capability, target_damage_level);
				}
				else
				{
					if (weapon_database[weapon_type].circular_error_probable) // chance to get 50% hits in 1m radius circle from this distance, small advantage for unguided rockets
						damage_multiplier = min (1, weapon_config_database[config_type][package].salvo_size / (weapon_database[weapon_type].circular_error_probable * target_range));

					total_damage_possible = min (damage_multiplier * damage_capability, target_damage_level);
				}

				if (weapon_database[weapon_type].rate_of_fire != FIRE_SINGLE_WEAPON)
					damage_by_type[weapon_type] = min(damage_by_type[weapon_type] + total_damage_possible, target_damage_level); // summ all avialable weapons
				else
					damage_by_type[weapon_type] = max(damage_by_type[weapon_type], total_damage_possible);

				if (total_damage_possible == 0)
				{
					suitable_weapon_count --;
					
					if (debug_flag)
					{
						debug_log ("WN_TGT : (%d) %s EXCLUDED (damage %d, damage multiplier %.2f)", package, weapon_database[weapon_type].full_name, total_damage_possible, damage_multiplier);
					}
				}
				else if (debug_flag)
				{
					debug_log ("WN_TGT : (%d) %s (damage %d, damage multiplier %.2f)", package, weapon_database[weapon_type].full_name, total_damage_possible, damage_multiplier);
				}
			}
		}
	}
	else // ANTI MISSILE WEAPON SYSTEMS
	{
		int
			damage_capability,
			total_damage_possible;

		for (package = 0; package < NUM_WEAPON_PACKAGES; package++)
		{
			float damage_multiplier = 1;
			
			if (suitability[package])
			{
				weapon_type = weapon_config_database[config_type][package].sub_type;

				if (weapon_database[weapon_type].warhead_type == WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE_ANTI_AIRCRAFT)
				{
					if (weapon_database[weapon_type].rate_of_fire == FIRE_SINGLE_WEAPON)
					{
						damage_capability = weapon_damage_capability (NULL, target, 0.0, weapon_type, 0.75) * weapon_config_database[config_type][package].salvo_size;
					}
					else
					{
						damage_capability = weapon_damage_capability (NULL, target, 0.0, weapon_type, 0.75)
										* weapon_database[weapon_type].rate_of_fire
										* weapon_database[weapon_type].burst_duration / 60;
					}

					if (weapon_database[weapon_type].guidance_type != WEAPON_GUIDANCE_TYPE_NONE) //	 guided weapons are generally more suitable for air target except close range
					{
						damage_multiplier = target_range / 1000 + 1;

						total_damage_possible = damage_multiplier * damage_capability;
					}
					else
					{
						if (weapon_database[weapon_type].circular_error_probable) // chance to get 50% hits in 1m radius circle from this distance, small advantage for unguided rockets
							damage_multiplier = min (1, weapon_config_database[config_type][package].salvo_size / (weapon_database[weapon_type].circular_error_probable * target_range));

						total_damage_possible = damage_multiplier * damage_capability;
					}

					if (weapon_database[weapon_type].rate_of_fire != FIRE_SINGLE_WEAPON)
						damage_by_type[weapon_type] = damage_by_type[weapon_type] + total_damage_possible; // summ all avialable weapons
					else
						damage_by_type[weapon_type] = max(damage_by_type[weapon_type], total_damage_possible);

					if (total_damage_possible == 0)
					{
						suitable_weapon_count --;

						if (debug_flag)
						{
							debug_log ("WN_TGT : (%d) %s EXCLUDED (damage %d, damage multiplier %.2f)", package, weapon_database[weapon_type].full_name, total_damage_possible, damage_multiplier);
						}
					}
					else if (debug_flag)
					{
						debug_log ("WN_TGT : (%d) %s (damage %d, damage multiplier %.2f)", package, weapon_database[weapon_type].full_name, total_damage_possible, damage_multiplier);
					}
				}
				else
				{
					suitable_weapon_count --;
					if (debug_flag)
					{
						debug_log ("WN_TGT : (%d) %s EXCLUDED (damage %d, damage multiplier %.2f)", package, weapon_database[weapon_type].full_name, total_damage_possible, damage_multiplier);
					}
				}
			}
		}
	}

	if (suitable_weapon_count == 0)
	{
		return ENTITY_SUB_TYPE_WEAPON_NO_WEAPON;
	}

	// find the most suitable weapon

	{
		int
			highest_suitability = 0;

		weapon_type = ENTITY_SUB_TYPE_WEAPON_NO_WEAPON;

		for (package = 1; package < NUM_ENTITY_SUB_TYPE_WEAPONS; package++)
		{
			if (damage_by_type[package] > highest_suitability)
			{
				weapon_type = package;
				highest_suitability = damage_by_type[package];
			}
		}

		if (debug_flag)
		{
			debug_log ("WN_TGT : PRIMARY WEAPON %s - damage %d", weapon_database[weapon_type].full_name, highest_suitability);
		}
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

				if (weapon_type >= WEAPON_WARHEAD_TYPE_SOLID_SHOT)
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
