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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern int weapon_damage_capability (entity *wpn, entity *target, float damage_modifier, entity_sub_types weapon_type, float velocity);

static float get_player_damage_modifier (entity *en);

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
			case WEAPON_WARHEAD_TYPE_SOLID_SHOT:
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
			case WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE_ANTI_TANK:
			case WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE_DUAL_PURPOSE:
			case WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE:
			case WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE_ANTI_AIRCRAFT:
			case WEAPON_WARHEAD_TYPE_CONVENTIONAL_MUNITIONS:
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

	damage_level = get_local_entity_int_value (en, INT_TYPE_DAMAGE_LEVEL);

	damage_capability = weapon_damage_capability (weapon, en, damage_modifier, get_local_entity_int_value (weapon, INT_TYPE_ENTITY_SUB_TYPE), FALSE);

	ASSERT (get_session_entity ());

	if (damage_capability > 0 && (!command_line_debug_damage_invulnerable || !get_local_entity_int_value (get_session_entity (), INT_TYPE_CHEATS_ENABLED)))
	{
		damage_level -= damage_capability;

		damage_level = max (damage_level, 0);

		set_client_server_entity_int_value (en, INT_TYPE_DAMAGE_LEVEL, damage_level);

		#if DEBUG_MODULE

		debug_log ("DAMAGE: %s hit = %d , new damage level = %d", get_local_entity_string (en, STRING_TYPE_FULL_NAME), damage_capability, damage_level);

		#endif
	}

	return damage_capability;
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

int weapon_damage_capability (entity *wpn, entity *target, float damage_modifier, entity_sub_types weapon_type, float velocity)
{
	int
		result = 0,
		i,
		temp,
		high_explosive = FALSE,
		warhead_type;

	float
		weapon_armor_penetration_capability,
		random_modifier = 1,
		target_armor_thickness,
		armor_modifier,
		damage_capability,
		armor_penetration_capability;
	weapon
		*raw;

	ASSERT (target);

	switch (weapon_database[weapon_type].warhead_type)
	{
		case WEAPON_WARHEAD_TYPE_CONVENTIONAL_MUNITIONS:
			warhead_type = weapon_database[weapon_type + 1].warhead_type;
			damage_capability = weapon_database[weapon_type + 1].damage_capability * weapon_database[weapon_type + 1].burst_duration / 3;
			armor_penetration_capability = weapon_database[weapon_type + 1].armor_penetration_capability;
			break;
		default:
			warhead_type = weapon_database[weapon_type].warhead_type;
			damage_capability = weapon_database[weapon_type].damage_capability;
			armor_penetration_capability = weapon_database[weapon_type].armor_penetration_capability;
	}
	
	if (wpn) // only for real weapon!
	{
		raw = (weapon *) get_local_entity_data (wpn);

		target_armor_thickness = get_local_entity_armour_thickness (target, wpn);
		random_modifier = frand1();

		if (warhead_type >= WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE_ANTI_TANK && 
				warhead_type <= WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE_ANTI_AIRCRAFT)
		{
			velocity = 1;	
			high_explosive = TRUE;
			random_modifier = 0.75 + 2 * random_modifier * random_modifier * random_modifier; // random chance from 75% to 275%, average 100%
		}
		else
		{
			velocity = raw->mob.velocity / weapon_database[weapon_type].cruise_velocity;
			random_modifier = 0.75 + 0.5 * random_modifier; // random chance from 75% to 125%, average 100%
		}

	}
	else
	{
		target_armor_thickness = (float) get_local_entity_int_value (target, INT_TYPE_ARMOR_LEVEL);
		if (warhead_type >= WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE_ANTI_TANK && 
				warhead_type <= WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE_ANTI_AIRCRAFT)
		{
			velocity = 1;	
			high_explosive = TRUE;
		}
	}
	
	weapon_armor_penetration_capability = armor_penetration_capability * random_modifier * velocity;
	
	if (weapon_armor_penetration_capability >= target_armor_thickness && damage_modifier < 0.01) // weapon pierces through the armor
	{
		result = (int) (damage_capability * random_modifier * velocity);

		#if DEBUG_MODULE
			debug_log("DAMAGE: DIRECT HIT - weapon penetration %.1f, target armor %.1f, damage_modifier %.4f, random modifier %.4f, damage %d", 
					weapon_armor_penetration_capability, target_armor_thickness, damage_modifier, random_modifier, result);
		#endif
		
	}
	else if (high_explosive)
	{
		float he_warheads = WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE_ANTI_AIRCRAFT - WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE_ANTI_TANK; // subtract 1
		
		damage_modifier = 1 - pow(damage_modifier, pow((float)(warhead_type - WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE_ANTI_TANK + 1) / he_warheads, 1.5f));
		armor_modifier =  min(1.0f, damage_capability * damage_modifier * random_modifier / pow(target_armor_thickness, 1.5f));
		
		result = (int) (damage_capability * damage_modifier * armor_modifier * random_modifier);

		#if DEBUG_MODULE
			debug_log("DAMAGE: SPLASH DAMAGE - weapon penetration %.1f, target armor %.1f, damage_modifier %.4f, armor modifier %.4f, random modifier %.4f, damage %d", 
					weapon_armor_penetration_capability, target_armor_thickness, damage_modifier, armor_modifier, random_modifier, result);
		#endif

	}
	
	if (get_local_entity_int_value (target, INT_TYPE_PLAYER) != ENTITY_PLAYER_AI)
		result *= get_player_damage_modifier (target);
	
	if (wpn) // damage multiplier for clients
		if (wpn->weapon_data->launched_weapon_link.parent)
			result *= comms_weapon_damage_multiplier_value(wpn->weapon_data->launched_weapon_link.parent, FALSE, weapon_type);

	if (wpn && command_line_debug_show_damage) // draw damage value
	{
		viewpoint
			temp_vp;
		vec3d
			temp_vec;
		int
			digit,
			zero = TRUE,
			p = 1000;
		
		get_local_entity_vec3d (target, VEC3D_TYPE_POSITION, &temp_vp.position);
		get_local_entity_attitude_matrix (wpn, temp_vp.attitude);
		temp_vec.x = 4;
		temp_vec.y = temp_vec.z = 0;
		multiply_matrix3x3_vec3d(&temp_vec, temp_vp.attitude, &temp_vec);
		temp_vp.position.x -= 2 * temp_vec.x;
		temp_vp.position.y -= 2 * temp_vec.y;
		temp_vp.position.z -= 2 * temp_vec.z;

		temp = result;

		for (i = 3; i >= 0; i-- )
		{
			digit = temp / p;
			if (digit)
				zero = FALSE;

			if (!zero)
				create_debug_3d_object (&temp_vp, OBJECT_3D_DIG_0 + digit, 2, 5.0);

			temp %= p;
			p /= 10;
			temp_vp.position.x += temp_vec.x;
			temp_vp.position.y += temp_vec.y;
			temp_vp.position.z += temp_vec.z;
		}
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
				if (objects_3d_scene_database[destroyed_object].succeeded)
				{
					destroyed_object_table [normal_object] = destroyed_object;

					restored_object_table [destroyed_object] = normal_object;

					found_flag = TRUE;
				}
				else
				{
					debug_log("DAMAGE : Failed to load destroyed scene for %s", normal_object_string);
				}

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
		GAME_DIFFICULTY_MEDIUM,		0.75,
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
	return command_line_debug_damage_invulnerable;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int toggle_damage_debug_invulnerable_flag (void)
{
	command_line_debug_damage_invulnerable = !command_line_debug_damage_invulnerable;

	return command_line_debug_damage_invulnerable;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
