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
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static weapon_explosion_criteria
	ball_explosion_criteria_table,
	high_explosive_explosion_criteria_table,
	smoke_grenade_explosion_criteria_table,
	ground_collision_criteria_table,
	water_collision_criteria_table,
	object_collision_criteria_table;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void initialise_ball_explosion_criteria_table ();
static void initialise_high_explosive_explosion_criteria_table ();
static void initialise_smoke_grenade_explosion_criteria_table ();
static void initialise_ground_collision_criteria_table ();
static void initialise_water_collision_criteria_table ();
static void initialise_object_collision_criteria_table ();
static void add_explosion_criteria (int index, int min_damage, int max_damage, meta_explosion_types type, weapon_explosion_criteria *table);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_weapon_explosion_criteria_tables ()
{
	initialise_ball_explosion_criteria_table ();
	initialise_high_explosive_explosion_criteria_table ();
	initialise_smoke_grenade_explosion_criteria_table ();

	initialise_ground_collision_criteria_table ();
	initialise_water_collision_criteria_table ();
	initialise_object_collision_criteria_table ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_ball_explosion_criteria_table ()
{
	weapon_explosion_criteria
		*table;

	table = &ball_explosion_criteria_table;

	table->kill_code_criteria_count = 1;

	table->min_damage = (int *) malloc (sizeof (int) * table->kill_code_criteria_count);
	table->max_damage = (int *) malloc (sizeof (int) * table->kill_code_criteria_count);
	table->type = (meta_explosion_types *) malloc (sizeof (meta_explosion_types) * table->kill_code_criteria_count);

	add_explosion_criteria (0, 0, INT_MAX, META_EXPLOSION_TYPE_NONE, table);

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_high_explosive_explosion_criteria_table ()
{
	weapon_explosion_criteria
		*table;

	table = &high_explosive_explosion_criteria_table;

	table->kill_code_criteria_count = 5;

	table->min_damage = (int *) malloc (sizeof (int) * table->kill_code_criteria_count);
	table->max_damage = (int *) malloc (sizeof (int) * table->kill_code_criteria_count);
	table->type = (meta_explosion_types *) malloc (sizeof (meta_explosion_types) * table->kill_code_criteria_count);

	add_explosion_criteria (0, 0, 49, XSMALL_HE_META_EXPLOSION, table);
	add_explosion_criteria (1, 50, 249, SMALL_HE_META_EXPLOSION, table);
	add_explosion_criteria (2, 249, 999, MEDIUM_HE_META_EXPLOSION, table);
	add_explosion_criteria (3, 1000, 1999, LARGE_HE_META_EXPLOSION, table);
	add_explosion_criteria (4, 2000, INT_MAX, XLARGE_HE_META_EXPLOSION, table);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_smoke_grenade_explosion_criteria_table ()
{
	weapon_explosion_criteria
		*table;


	table = &smoke_grenade_explosion_criteria_table;

	table->kill_code_criteria_count = 1;

	table->min_damage = (int *) malloc (sizeof (int) * table->kill_code_criteria_count);
	table->max_damage = (int *) malloc (sizeof (int) * table->kill_code_criteria_count);
	table->type = (meta_explosion_types *) malloc (sizeof (meta_explosion_types) * table->kill_code_criteria_count);

	add_explosion_criteria (0, 0, INT_MAX, PURPLE_FLARE_META_EXPLOSION, table);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_ground_collision_criteria_table ()
{
	weapon_explosion_criteria
		*table;

	table = &ground_collision_criteria_table;

	table->kill_code_criteria_count = 5;

	table->min_damage = (int *) malloc (sizeof (int) * table->kill_code_criteria_count);
	table->max_damage = (int *) malloc (sizeof (int) * table->kill_code_criteria_count);
	table->type = (meta_explosion_types *) malloc (sizeof (meta_explosion_types) * table->kill_code_criteria_count);

	add_explosion_criteria (0, 0, 49, XSMALL_GROUND_META_EXPLOSION, table);
	add_explosion_criteria (1, 50, 249, SMALL_GROUND_META_EXPLOSION, table);
	add_explosion_criteria (2, 250, 999, MEDIUM_GROUND_META_EXPLOSION, table);
	add_explosion_criteria (3, 1000, 1999, LARGE_GROUND_META_EXPLOSION, table);
	add_explosion_criteria (4, 2000, INT_MAX, XLARGE_GROUND_META_EXPLOSION, table);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_water_collision_criteria_table ()
{
	weapon_explosion_criteria
		*table;

	table = &water_collision_criteria_table;

	table->kill_code_criteria_count = 2;

	table->min_damage = (int *) malloc (sizeof (int) * table->kill_code_criteria_count);
	table->max_damage = (int *) malloc (sizeof (int) * table->kill_code_criteria_count);
	table->type = (meta_explosion_types *) malloc (sizeof (meta_explosion_types) * table->kill_code_criteria_count);

	add_explosion_criteria (0, 0, 249, SMALL_WATER_META_EXPLOSION, table);
	add_explosion_criteria (1, 250, INT_MAX, MEDIUM_WATER_META_EXPLOSION, table);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_object_collision_criteria_table ()
{
	weapon_explosion_criteria
		*table;

	table = &object_collision_criteria_table;

	table->kill_code_criteria_count = 3;

	table->min_damage = (int *) malloc (sizeof (int) * table->kill_code_criteria_count);
	table->max_damage = (int *) malloc (sizeof (int) * table->kill_code_criteria_count);
	table->type = (meta_explosion_types *) malloc (sizeof (meta_explosion_types) * table->kill_code_criteria_count);

	add_explosion_criteria (0, 0, 49, SMALL_OBJECT_META_EXPLOSION, table);
	add_explosion_criteria (1, 50, 999, MEDIUM_OBJECT_META_EXPLOSION, table);
	add_explosion_criteria (2, 1000, INT_MAX, LARGE_OBJECT_META_EXPLOSION, table);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_weapon_explosion_criteria_tables ()
{
	weapon_explosion_criteria
		*table;

	table = &ball_explosion_criteria_table;
	free (table->max_damage);
	free (table->min_damage);
	free (table->type);

	table = &high_explosive_explosion_criteria_table;
	free (table->max_damage);
	free (table->min_damage);
	free (table->type);

	table = &smoke_grenade_explosion_criteria_table;
	free (table->max_damage);
	free (table->min_damage);
	free (table->type);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void add_explosion_criteria (int index, int min_damage, int max_damage, meta_explosion_types type, weapon_explosion_criteria *table)
{
	ASSERT (index >= 0);
	ASSERT (index < table->kill_code_criteria_count); 

	table->min_damage[index] = min_damage;
	table->max_damage[index] = max_damage;
	table->type[index] = type;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

meta_explosion_types get_suitable_weapon_explosion_type( entity *en, weapon_kill_codes kill_code )
{
	int
		loop,
		damage_capability;

	weapon_warhead_types
		warhead_type;

	weapon_explosion_criteria
		*criteria_table;
	
	entity_sub_types
			weapon_type = get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE);

	switch (weapon_database[weapon_type].warhead_type)
	{
		case WEAPON_WARHEAD_TYPE_CONVENTIONAL_MUNITIONS:
			warhead_type = weapon_database[weapon_type + 1].warhead_type;
			damage_capability = weapon_database[weapon_type + 1].damage_capability * weapon_database[weapon_type + 1].burst_duration / 3;
			break;
		default:
			warhead_type = weapon_database[weapon_type].warhead_type;
			damage_capability = weapon_database[weapon_type].damage_capability;
	}

	if (!kill_code) // weapon explosion
		switch (warhead_type)
		{
			case WEAPON_WARHEAD_TYPE_NONE:
			{
				return META_EXPLOSION_TYPE_NONE;
			}
			case WEAPON_WARHEAD_TYPE_SOLID_SHOT:
			case WEAPON_WARHEAD_TYPE_CONVENTIONAL_MUNITIONS:
			case WEAPON_WARHEAD_TYPE_ILLUMINATION_FLARE:
			{
				criteria_table = &ball_explosion_criteria_table;

				break;
			}
			case WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE_DUAL_PURPOSE:
			case WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE_ANTI_TANK:
			case WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE:
			case WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE_ANTI_AIRCRAFT:
			{
				criteria_table = &high_explosive_explosion_criteria_table;

				break;
			}
			case WEAPON_WARHEAD_TYPE_SMOKE_GRENADE:
			{
				criteria_table = &smoke_grenade_explosion_criteria_table;

				break;
			}
			default:
			{
				debug_fatal ("XP_WPN : Invalid warhead type %d", warhead_type);

				return META_EXPLOSION_TYPE_NONE;
			}
		}
	else // weapon collision
		switch (kill_code)
		{
			case WEAPON_KILL_CODE_HIT_WATER:
			{
				criteria_table = &water_collision_criteria_table;

				break;
			}
			case WEAPON_KILL_CODE_HIT_LAND:
			{
				criteria_table = &ground_collision_criteria_table;

				break;
			}
			case WEAPON_KILL_CODE_HIT_TARGET:
			{
				criteria_table = &object_collision_criteria_table;

				break;
			}
		}


	// search through the table, checking all other criteria

	for (loop = 0; loop < criteria_table->kill_code_criteria_count; loop ++)
		if ( criteria_table->min_damage[loop] <= damage_capability && criteria_table->max_damage[loop] >= damage_capability )
			return criteria_table->type[loop];


	return META_EXPLOSION_TYPE_NONE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
