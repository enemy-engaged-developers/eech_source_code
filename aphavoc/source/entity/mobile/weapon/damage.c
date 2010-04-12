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

#include "ai/highlevl/highlevl.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE 				0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static object_3d_index_numbers
	*destroyed_object_table,
	*restored_object_table;

static int
	damage_debug_invulnerable_flag = FALSE;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int weapon_damage_capability (entity_sub_types weapon_type, entity *target, int direct_hit);

static float get_player_damage_modifier (entity *en);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct WARHEAD_DAMAGE_DATA
{
	int
		effective_targets;
};

typedef struct WARHEAD_DAMAGE_DATA warhead_damage_data;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const warhead_damage_data
	warhead_damage_database [NUM_WEAPON_WARHEAD_TYPES] =
	{
		//
		//	WEAPON_WARHEAD_TYPE_NONE
		//
		{
			WARHEAD_EFFECTIVE_NONE
		},

		//
		//	WEAPON_WARHEAD_TYPE_BALL
		//
		{
			WARHEAD_EFFECTIVE_HELICOPTER +
			WARHEAD_EFFECTIVE_FIXED_WING +
			WARHEAD_EFFECTIVE_INFANTRY +
			WARHEAD_EFFECTIVE_LIGHT_VEHICLE +
			WARHEAD_EFFECTIVE_LIGHT_BUILDING
		},

		//
		//	WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE
		//
		{
			WARHEAD_EFFECTIVE_HELICOPTER +
			WARHEAD_EFFECTIVE_FIXED_WING +
			WARHEAD_EFFECTIVE_INFANTRY +
			WARHEAD_EFFECTIVE_LIGHT_VEHICLE +
			WARHEAD_EFFECTIVE_LIGHT_SHIP +
			WARHEAD_EFFECTIVE_WOOD_BRIDGE +
			WARHEAD_EFFECTIVE_STONE_BRIDGE +
			WARHEAD_EFFECTIVE_LIGHT_BUILDING +
			WARHEAD_EFFECTIVE_STONE_BUILDING
		},

		//
		//	WEAPON_WARHEAD_TYPE_ARMOUR_PIERCING
		//
		{
			WARHEAD_EFFECTIVE_HELICOPTER +
			WARHEAD_EFFECTIVE_FIXED_WING +
			WARHEAD_EFFECTIVE_INFANTRY +
//			WARHEAD_EFFECTIVE_LIGHT_VEHICLE +			// To favour H.E. weapons over A.P.
			WARHEAD_EFFECTIVE_ARMOURED_VEHICLE +
			WARHEAD_EFFECTIVE_LIGHT_SHIP +
			WARHEAD_EFFECTIVE_WOOD_BRIDGE +
			WARHEAD_EFFECTIVE_STONE_BRIDGE +
//			WARHEAD_EFFECTIVE_LIGHT_BUILDING +			// To favour H.E. weapons over A.P.
			WARHEAD_EFFECTIVE_STONE_BUILDING
		},

		//
		//	WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE_ANTI_TANK
		//
		{
			WARHEAD_EFFECTIVE_HELICOPTER +
			WARHEAD_EFFECTIVE_FIXED_WING +
			WARHEAD_EFFECTIVE_INFANTRY	 +
			WARHEAD_EFFECTIVE_LIGHT_VEHICLE +
			WARHEAD_EFFECTIVE_ARMOURED_VEHICLE +
			WARHEAD_EFFECTIVE_LIGHT_SHIP +
			WARHEAD_EFFECTIVE_FRIGATE +
			WARHEAD_EFFECTIVE_CARRIER +
			WARHEAD_EFFECTIVE_WOOD_BRIDGE +
			WARHEAD_EFFECTIVE_STONE_BRIDGE +
			WARHEAD_EFFECTIVE_METAL_BRIDGE +
			WARHEAD_EFFECTIVE_LIGHT_BUILDING +
			WARHEAD_EFFECTIVE_STONE_BUILDING +
			WARHEAD_EFFECTIVE_HARDENED_BUILDING
		},

		//
		//	WEAPON_WARHEAD_TYPE_SMOKE_GRENADE
		//
		{
			WARHEAD_EFFECTIVE_NONE
		},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int damage_client_server_entity (entity *en, entity *weapon, float damage_modifier)
{
	int
		damage_capability,
		damage_level;

	weapon_warhead_types
		warhead_type;

	float
		temp_damage,
		armour_thickness;

	ASSERT (en);

	if (!weapon)
	{
		return 0;
	}

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	ASSERT ((damage_modifier >= 0.0) && (damage_modifier <= 1.0));

	warhead_type = (weapon_warhead_types) get_local_entity_int_value (weapon, INT_TYPE_WEAPON_WARHEAD_TYPE);

	ASSERT ((warhead_type >= WEAPON_WARHEAD_TYPE_NONE) && (warhead_type < NUM_WEAPON_WARHEAD_TYPES));

	if (get_local_entity_int_value (en, INT_TYPE_PLAYER) != ENTITY_PLAYER_AI)
	{
		sound_sample_indices
			int_sound,
			ext_sound;

		//
		// damage sound effects
		//

		int_sound = SOUND_SAMPLE_INDEX_NONE;
		ext_sound = SOUND_SAMPLE_INDEX_NONE;

		switch (warhead_type)
		{
			case WEAPON_WARHEAD_TYPE_BALL:
			case WEAPON_WARHEAD_TYPE_ARMOUR_PIERCING:
			{
				if (get_local_entity_index (weapon) & 1)
				{
					int_sound = SOUND_SAMPLE_INDEX_INTERIOR_LIGHT_DAMAGE2;
					ext_sound = SOUND_SAMPLE_INDEX_EXTERIOR_LIGHT_DAMAGE2;
				}
				else
				{
					int_sound = SOUND_SAMPLE_INDEX_INTERIOR_LIGHT_DAMAGE1;
					ext_sound = SOUND_SAMPLE_INDEX_EXTERIOR_LIGHT_DAMAGE1;
				}

				break;
			}
			case WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE:
			case WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE_ANTI_TANK:
			{
				if (get_local_entity_index (weapon) & 1)
				{
					int_sound = SOUND_SAMPLE_INDEX_INTERIOR_HEAVY_DAMAGE2;
					ext_sound = SOUND_SAMPLE_INDEX_EXTERIOR_HEAVY_DAMAGE2;
				}
				else
				{
					int_sound = SOUND_SAMPLE_INDEX_INTERIOR_HEAVY_DAMAGE1;
					ext_sound = SOUND_SAMPLE_INDEX_EXTERIOR_HEAVY_DAMAGE1;
				}

				break;
			}
		}

		if (int_sound != SOUND_SAMPLE_INDEX_NONE)
		{
			create_client_server_sound_effect_entity
			(
				en,
				ENTITY_SIDE_NEUTRAL,
				ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,
				SOUND_CHANNEL_SOUND_EFFECT,
				SOUND_LOCALITY_INTERIOR,
				NULL,												// position
				damage_modifier,								// amplification
				1.0,												// Werewolf pitch
				TRUE,												// valid sound effect
				FALSE,											// looping
				1,													// sample count
				&int_sound										// sample index list
			);
		}

		if (ext_sound != SOUND_SAMPLE_INDEX_NONE)
		{
			create_client_server_sound_effect_entity
			(
				en,
				ENTITY_SIDE_NEUTRAL,
				ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,
				SOUND_CHANNEL_SOUND_EFFECT,
				SOUND_LOCALITY_EXTERIOR,
				NULL,												// position
				damage_modifier,								// amplification
				1.0,												// Werewolf pitch
				TRUE,												// valid sound effect
				FALSE,											// looping
				1,													// sample count
				&ext_sound										// sample index list
			);
		}

		//
		// invulnerability option for players
		//

		if (get_local_entity_int_value (en, INT_TYPE_INVULNERABLE_FROM_WEAPONS))
		{
			return 0;
		}
	}
	else
	{
		//
		// invulnerability option for AI
		//

		if (damage_debug_invulnerable_flag)
		{
			return 0;
		}
	}

	damage_level = get_local_entity_int_value (en, INT_TYPE_DAMAGE_LEVEL);

	damage_capability = weapon_damage_capability (get_local_entity_int_value (weapon, INT_TYPE_ENTITY_SUB_TYPE), en, (damage_modifier == 1.0));

	if (damage_capability > 0)
	{
		//
		// weapon is capable of doing damage
		//

		temp_damage = (float)damage_capability;

		temp_damage *= damage_modifier;

		if (damage_modifier == (float) 1.0)
		{
			//
			// direct hit - compensate for armour thickness
			//

			armour_thickness = get_local_entity_armour_thickness (en, weapon);

			temp_damage -= temp_damage * armour_thickness * 2.0 / 3.0;
		}

		//
		// add +/- 10% random tolerance
		//

		temp_damage += (temp_damage * 0.1 * sfrand1 ());

		// adjust for burst size
		temp_damage *= get_local_entity_int_value(weapon, INT_TYPE_WEAPON_BURST_SIZE);
		
		//
		// subtract from entities damage level
		//

		convert_float_to_int (temp_damage, &damage_capability);

		damage_level -= damage_capability;

		damage_level = max (damage_level, 0);

		set_client_server_entity_int_value (en, INT_TYPE_DAMAGE_LEVEL, damage_level);

		#if DEBUG_MODULE

		debug_log ("DAMAGE: %s hit : new damage = %d", get_local_entity_string (en, STRING_TYPE_FULL_NAME), damage_level);

		#endif
	}

	return damage_capability;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// DEBUG FUNCTION
//

void assess_effectiveness_of_all_weapons_on_entity (entity *en)
{
	const char
		*target_name;
	char
		*filename;

	FILE
		*fp;

	int
		loop,
		count,
		damage_level;

	entity_sub_types
		weapon_type;

	//
	// output :
	// target name,
	// current damage,
	//
	// for each weapon
	//		weapon name,
	//		number of rounds needed to destroy using weapon

	ASSERT (en);

	if (get_local_entity_int_value (en, INT_TYPE_IDENTIFY_AIRCRAFT))
	{
		target_name = entity_sub_type_aircraft_names [get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE)];
	}
	else if (get_local_entity_int_value (en, INT_TYPE_IDENTIFY_VEHICLE))
	{
		target_name = entity_sub_type_vehicle_names [get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE)];
	}
	else
	{
		target_name = entity_type_names [en->type];
	}

	debug_colour_log (DEBUG_COLOUR_RED, "Testing weapon effectiveness on entity : %s", target_name);

	//
	// open file
	//

	filename = (char *) malloc_fast_mem (strlen (target_name) + 6);

	sprintf (filename, "%s.dmg", target_name);

	fp = safe_fopen (filename, "w");

    safe_free (filename);

	//
	// output target name
	//

	count = fprintf (fp, "OBJECT : %s\n", target_name);

	for (loop = 0; loop < count - 1; loop ++)
	{
		fputc ('=', fp);
	}

	fprintf (fp, "\n\n");

	//
	// output current damage levels
	//

	damage_level = get_local_entity_int_value (en, INT_TYPE_DAMAGE_LEVEL);

	fprintf (fp, "Current Damage :- %4d\n\n", damage_level);

	if (damage_level > 0)
	{
		//
		// cycle through each weapon
		//

		for (weapon_type = ENTITY_SUB_TYPE_WEAPON_NO_WEAPON + 1; weapon_type < NUM_ENTITY_SUB_TYPE_WEAPONS; weapon_type ++ )
		{
			int
				weapon_power,
				rounds_needed;

			//
			// output weapon name
			//

			count = fprintf (fp, "%s\n", entity_sub_type_weapon_names [weapon_type]);

			for (loop = 0; loop < count - 1; loop ++)
			{
				fputc ('-', fp);
			}

			weapon_power = weapon_damage_capability (weapon_type, en, TRUE);

			rounds_needed = -1;

			if (weapon_power > 0)
			{
				rounds_needed = damage_level / weapon_power;

				rounds_needed += 1;
			}

			//
			//	output number of rounds needed to destroy / maximum damage possible using weapon
			//

			if (rounds_needed == -1)
			{
				fprintf (fp, "\n    Rounds Needed To Destroy Target : ----\n\n");
			}
			else
			{
				fprintf (fp, "\n    ROUNDS NEEDED TO DESTROY TARGET : %4d.\n\n", rounds_needed);
			}
		}
	}

	fclose (fp);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void display_debug_kill_info (entity *victim, entity *aggressor)
{

	entity
		*victim_task,
		*aggressor_task;

	const char
		*desc1,
		*desc2,
		*victim_desc,
		*aggressor_desc;

	debug_colours
		col;

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	//
	// get task descriptions
	//

	// victim

	victim_task = get_local_entity_primary_task (victim);

	if (victim_task)
	{
		desc1 = get_local_entity_string (victim_task, STRING_TYPE_FULL_NAME);
	}
	else
	{
		desc1 = task_database [ENTITY_SUB_TYPE_TASK_NOTHING].full_name;
	}

	// aggressor

	aggressor_task = get_local_entity_primary_task (aggressor);

	if (aggressor_task)
	{
		desc2 = get_local_entity_string (aggressor_task, STRING_TYPE_FULL_NAME);
	}
	else
	{
		desc2 = task_database [ENTITY_SUB_TYPE_TASK_NOTHING].full_name;
	}

	//
	// get mobile descriptions
	//

	// victim

	victim_desc = get_local_entity_string (victim, STRING_TYPE_FULL_NAME);

	ASSERT (victim_desc);

	// aggressor

	aggressor_desc = get_local_entity_string (aggressor, STRING_TYPE_FULL_NAME);

	ASSERT (aggressor_desc);

	//

	if (get_local_entity_int_value (aggressor, INT_TYPE_SIDE) == ENTITY_SIDE_BLUE_FORCE)
	{
		col = DEBUG_COLOUR_BLUE;
	}
	else
	{
		col = DEBUG_COLOUR_RED;
	}

	debug_colour_log (col, "DAMAGE: %s (%d) doing %s - killed by %s (%d) doing %s",
								victim_desc,
								get_local_entity_index (victim),
								desc1,
								aggressor_desc,
								get_local_entity_index (aggressor),
								desc2);

	ai_log ("(KILL) %s doing %s - killed by %s doing %s", victim_desc, desc1, aggressor_desc, desc2);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int warhead_is_capable_of_damage (weapon_warhead_types type)
{
	ASSERT ((type >= WEAPON_WARHEAD_TYPE_NONE) && (type < NUM_WEAPON_WARHEAD_TYPES));

	return (warhead_damage_database [type].effective_targets);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int weapon_is_capable_of_damage (entity_sub_types weapon_type)
{
	return (warhead_is_capable_of_damage (weapon_database [weapon_type].warhead_type));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int weapon_is_suitable_for_damaging_target (entity_sub_types weapon_type, entity *target, int direct_hit)
{
	weapon_warhead_types
		warhead_type;

	int
		warhead_effective_mask,
		warhead_target_class;

	warhead_type = weapon_database [weapon_type].warhead_type;

	ASSERT ((warhead_type >= WEAPON_WARHEAD_TYPE_NONE) && (warhead_type < NUM_WEAPON_WARHEAD_TYPES));

	ASSERT (target);

	if ((warhead_type == WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE_ANTI_TANK) && (!direct_hit))
	{
		warhead_effective_mask = warhead_damage_database [WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE].effective_targets;
	}
	else
	{
		warhead_effective_mask = warhead_damage_database [warhead_type].effective_targets;
	}

	warhead_target_class = get_local_entity_int_value (target, INT_TYPE_WARHEAD_EFFECTIVE_CLASS);

	if (warhead_effective_mask & warhead_target_class)
	{
		if (warhead_target_class < WARHEAD_EFFECTIVE_HARD_TARGETS)
		{
			return weapon_database [weapon_type].soft_damage_capability;
		}
		else
		{
			return weapon_database [weapon_type].hard_damage_capability;
		}
	}
	else
	{
		return 0;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int weapon_damage_capability (entity_sub_types weapon_type, entity *target, int direct_hit)
{
	int
		result,
		warhead_target_class;

	ASSERT (target);

	result = 0;

	warhead_target_class = get_local_entity_int_value (target, INT_TYPE_WARHEAD_EFFECTIVE_CLASS);

	if (warhead_target_class < WARHEAD_EFFECTIVE_HARD_TARGETS)
	{
		result = weapon_database [weapon_type].soft_damage_capability;
	}
	else
	{
		if ((weapon_database [weapon_type].warhead_type == WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE_ANTI_TANK) && (!direct_hit))
		{
			//
			// reduce effectiveness of HEAT missiles if hit is not direct
			//

			result = (weapon_database [weapon_type].hard_damage_capability >> 3);
		}
		else
		{
			result = weapon_database [weapon_type].hard_damage_capability;
		}
	}

	if (get_local_entity_int_value (target, INT_TYPE_PLAYER) != ENTITY_PLAYER_AI)
	{
		result *= get_player_damage_modifier (target);
	}

	return result;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DESTROYED_OBJECT_KEYWORD "_DESTROYED"

#define DEBUG_NON_ENTRIES	0

void initialise_destroyed_object_database (void)
{
	object_3d_index_numbers
		normal_object,
		destroyed_object;

	const char
		*normal_object_string;
	char
		*destroyed_object_string;

	int
		found_flag,
		keyword_length;

	keyword_length = strlen (DESTROYED_OBJECT_KEYWORD);

	destroyed_object_table = (object_3d_index_numbers *) safe_malloc (sizeof (object_3d_index_numbers) * OBJECT_3D_LAST);

	restored_object_table = (object_3d_index_numbers *) safe_malloc (sizeof (object_3d_index_numbers) * OBJECT_3D_LAST);

	//
	// set defaults
	//

	for (normal_object = 0; normal_object < OBJECT_3D_LAST; normal_object ++)
	{
		destroyed_object_table [normal_object] = normal_object;

		restored_object_table [normal_object] = normal_object;
	}

	//
	// search every 3d object for a destroyed counterpart
	//

	for (normal_object = 0; normal_object < OBJECT_3D_LAST; normal_object ++)
	{
		//
		// construct search string
		//

		normal_object_string = object_3d_information_database [normal_object].name;

		destroyed_object_string = (char *) malloc_fast_mem (strlen (normal_object_string) + keyword_length + 4);

		strcpy (destroyed_object_string, normal_object_string);

		strcat (destroyed_object_string, DESTROYED_OBJECT_KEYWORD);

		//
		// search database for new string
		//

		found_flag = FALSE;

		for (destroyed_object = 0; destroyed_object < OBJECT_3D_LAST; destroyed_object ++)
		{
			if (strcmp (destroyed_object_string, object_3d_information_database [destroyed_object].name) == 0)
			{
				destroyed_object_table [normal_object] = destroyed_object;

				restored_object_table [destroyed_object] = normal_object;

				found_flag = TRUE;

				break;
			}
		}

		#if DEBUG_NON_ENTRIES

		if ((!found_flag) && (!strstr (normal_object_string, DESTROYED_OBJECT_KEYWORD)))
		{
			debug_log ("DAMAGE : No entry found for %s", normal_object_string);
		}

		#endif

		free_mem (destroyed_object_string);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_destroyed_object_database (void)
{
	safe_free (destroyed_object_table);

	safe_free (restored_object_table);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

object_3d_index_numbers get_3d_object_destroyed_object_index (object_3d_index_numbers index)
{
	ASSERT ((index >= 0) && (index < OBJECT_3D_LAST));

	return destroyed_object_table [index];
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

object_3d_index_numbers get_3d_object_restored_object_index (object_3d_index_numbers index)
{
	ASSERT ((index >= 0) && (index < OBJECT_3D_LAST));

	return restored_object_table [index];
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static struct PLAYER_DAMAGE_MODIFIER_TABLE
{
	game_difficulty_settings
		difficulty;

	float
		damage_modifier;

} player_damage_modifier_table [] =
	{
		GAME_DIFFICULTY_EASY,		0.5,
		GAME_DIFFICULTY_MEDIUM,		0.75f,
		GAME_DIFFICULTY_HARD,		1.0,
		(game_difficulty_settings) -1
	};

float get_player_damage_modifier (entity *en)
{
	int
		loop;

	entity
		*pilot_en;

	game_difficulty_settings
		difficulty;

	ASSERT (en);

	pilot_en = get_local_entity_first_child (en, LIST_TYPE_AIRCREW);

	if (pilot_en)
	{
		difficulty = (game_difficulty_settings) get_local_entity_int_value (pilot_en, INT_TYPE_DIFFICULTY_LEVEL);
	
		loop = 0;
	
		while (player_damage_modifier_table [loop].difficulty >= 0)
		{
			if (player_damage_modifier_table [loop].difficulty == difficulty)
			{
				return player_damage_modifier_table [loop].damage_modifier;
			}
	
			loop ++;
		}
	
		debug_fatal ("DAMAGE: No player damage modifier for difficulty level %d", difficulty);
	}
	
	return 1.0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_damage_debug_invulnerable_flag (void)
{
	return damage_debug_invulnerable_flag;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int toggle_damage_debug_invulnerable_flag (void)
{
	damage_debug_invulnerable_flag = !damage_debug_invulnerable_flag;

	return damage_debug_invulnerable_flag;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
