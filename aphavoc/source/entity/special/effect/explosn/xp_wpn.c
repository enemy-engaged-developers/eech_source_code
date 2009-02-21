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
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static weapon_explosion_criteria
	ball_explosion_criteria_table,
	high_explosive_explosion_criteria_table,
	armour_piercing_explosion_criteria_table,
	heat_explosion_criteria_table,
	smoke_grenade_explosion_criteria_table;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void initialise_ball_explosion_criteria_table ();

static void initialise_high_explosive_explosion_criteria_table ();

static void initialise_armour_piercing_explosion_criteria_table ();

static void initialise_heat_explosion_criteria_table ();

static void initialise_smoke_grenade_explosion_criteria_table ();

static void add_explosion_criteria (int index, weapon_kill_codes kill_code, int min_damage, int max_damage, meta_explosion_types type, weapon_explosion_criteria *table);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_weapon_explosion_criteria_tables ()
{
	initialise_ball_explosion_criteria_table ();

	initialise_high_explosive_explosion_criteria_table ();

	initialise_armour_piercing_explosion_criteria_table ();

	initialise_heat_explosion_criteria_table ();

	initialise_smoke_grenade_explosion_criteria_table ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_ball_explosion_criteria_table ()
{
	weapon_explosion_criteria
		*table;

	weapon_kill_codes
		kill_code;

	int
		count;

	table = &ball_explosion_criteria_table;

	////////////////////////////////////////

	kill_code =  WEAPON_KILL_CODE_OK;

	table->kill_code_criteria_count [kill_code] = 0;

	table->kill_code_criteria [kill_code] = NULL;

	////////////////////////////////////////

	kill_code = WEAPON_KILL_CODE_EXHAUSTED;

	count = 1;

	table->kill_code_criteria_count [kill_code] = count;

	table->kill_code_criteria [kill_code] = malloc_heap_mem (sizeof (weapon_explosion_kill_code_criteria) * count);

	add_explosion_criteria (0, kill_code, 0, INT_MAX, META_EXPLOSION_TYPE_NONE, table);

	////////////////////////////////////////

	kill_code = WEAPON_KILL_CODE_OUT_OF_BOUNDS;

	count = 1;

	table->kill_code_criteria_count [kill_code] = count;

	table->kill_code_criteria [kill_code] = malloc_heap_mem (sizeof (weapon_explosion_kill_code_criteria) * count);

	add_explosion_criteria (0, kill_code, 0, INT_MAX, META_EXPLOSION_TYPE_NONE, table);

	////////////////////////////////////////

	kill_code = WEAPON_KILL_CODE_HIT_LAND;

	count = 1;

	table->kill_code_criteria_count [kill_code] = count;

	table->kill_code_criteria [kill_code] = malloc_heap_mem (sizeof (weapon_explosion_kill_code_criteria) * count);

	add_explosion_criteria (0, kill_code, 0, INT_MAX, SMALL_EARTH_META_EXPLOSION, table);

	////////////////////////////////////////

	kill_code = WEAPON_KILL_CODE_HIT_WATER;

	count = 1;

	table->kill_code_criteria_count [kill_code] = count;

	table->kill_code_criteria [kill_code] = malloc_heap_mem (sizeof (weapon_explosion_kill_code_criteria) * count);

	add_explosion_criteria (0, kill_code, 0, INT_MAX, SMALL_WATER_META_EXPLOSION, table);

	////////////////////////////////////////

	kill_code = WEAPON_KILL_CODE_HIT_TARGET;

	count = 1;

	table->kill_code_criteria_count [kill_code] = count;

	table->kill_code_criteria [kill_code] = malloc_heap_mem (sizeof (weapon_explosion_kill_code_criteria) * count);

	add_explosion_criteria (0, kill_code, 0, INT_MAX, SMALL_AP_META_EXPLOSION, table);

	////////////////////////////////////////

	kill_code = WEAPON_KILL_CODE_OVERSHOT_TARGET;

	count = 1;

	table->kill_code_criteria_count [kill_code] = count;

	table->kill_code_criteria [kill_code] = malloc_heap_mem (sizeof (weapon_explosion_kill_code_criteria) * count);

	add_explosion_criteria (0, kill_code, 0, INT_MAX, META_EXPLOSION_TYPE_NONE, table);

	////////////////////////////////////////

	kill_code = WEAPON_KILL_CODE_SELF_DESTRUCT;

	count = 1;

	table->kill_code_criteria_count [kill_code] = count;

	table->kill_code_criteria [kill_code] = malloc_heap_mem (sizeof (weapon_explosion_kill_code_criteria) * count);

	add_explosion_criteria (0, kill_code, 0, INT_MAX, META_EXPLOSION_TYPE_NONE, table);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_high_explosive_explosion_criteria_table ()
{
	weapon_explosion_criteria
		*table;

	weapon_kill_codes
		kill_code;

	int
		count;

	table = &high_explosive_explosion_criteria_table;

	////////////////////////////////////////

	kill_code =  WEAPON_KILL_CODE_OK;

	table->kill_code_criteria_count [kill_code] = 0;

	table->kill_code_criteria [kill_code] = NULL;

	////////////////////////////////////////

	kill_code = WEAPON_KILL_CODE_EXHAUSTED;

	count = 1;

	table->kill_code_criteria_count [kill_code] = count;

	table->kill_code_criteria [kill_code] = malloc_heap_mem (sizeof (weapon_explosion_kill_code_criteria) * count);

	add_explosion_criteria (0, kill_code, 0, INT_MAX, META_EXPLOSION_TYPE_NONE, table);

	////////////////////////////////////////

	kill_code = WEAPON_KILL_CODE_OUT_OF_BOUNDS;

	count = 1;

	table->kill_code_criteria_count [kill_code] = count;

	table->kill_code_criteria [kill_code] = malloc_heap_mem (sizeof (weapon_explosion_kill_code_criteria) * count);

	add_explosion_criteria (0, kill_code, 0, INT_MAX, META_EXPLOSION_TYPE_NONE, table);

	////////////////////////////////////////

	kill_code = WEAPON_KILL_CODE_HIT_LAND;

	count = 3;

	table->kill_code_criteria_count [kill_code] = count;

	table->kill_code_criteria [kill_code] = malloc_heap_mem (sizeof (weapon_explosion_kill_code_criteria) * count);

	add_explosion_criteria (0, kill_code, 0, 99, SMALL_HE_META_EXPLOSION, table);
	add_explosion_criteria (1, kill_code, 100, 999, MEDIUM_HE_META_EXPLOSION, table);
	add_explosion_criteria (2, kill_code, 1000, INT_MAX, LARGE_HE_META_EXPLOSION, table);

	////////////////////////////////////////

	kill_code = WEAPON_KILL_CODE_HIT_WATER;

	count = 3;

	table->kill_code_criteria_count [kill_code] = count;

	table->kill_code_criteria [kill_code] = malloc_heap_mem (sizeof (weapon_explosion_kill_code_criteria) * count);

	add_explosion_criteria (0, kill_code, 0, 99, SMALL_WATER_META_EXPLOSION, table);
	add_explosion_criteria (1, kill_code, 100, 999, MEDIUM_WATER_META_EXPLOSION, table);
	add_explosion_criteria (2, kill_code, 1000, INT_MAX, LARGE_WATER_META_EXPLOSION, table);

	////////////////////////////////////////

	kill_code = WEAPON_KILL_CODE_HIT_TARGET;

	count = 3;

	table->kill_code_criteria_count [kill_code] = count;

	table->kill_code_criteria [kill_code] = malloc_heap_mem (sizeof (weapon_explosion_kill_code_criteria) * count);

	add_explosion_criteria (0, kill_code, 0, 99, SMALL_AP_META_EXPLOSION, table);
	add_explosion_criteria (1, kill_code, 100, 999, MEDIUM_HE_META_EXPLOSION, table);
	add_explosion_criteria (2, kill_code, 1000, INT_MAX, LARGE_HE_META_EXPLOSION, table);

	////////////////////////////////////////

	kill_code = WEAPON_KILL_CODE_OVERSHOT_TARGET;

	count = 3;

	table->kill_code_criteria_count [kill_code] = count;

	table->kill_code_criteria [kill_code] = malloc_heap_mem (sizeof (weapon_explosion_kill_code_criteria) * count);

	add_explosion_criteria (0, kill_code, 0, 99, META_EXPLOSION_TYPE_NONE, table);
	add_explosion_criteria (1, kill_code, 100, 999, MEDIUM_HE_META_EXPLOSION, table);
	add_explosion_criteria (2, kill_code, 1000, INT_MAX, LARGE_HE_META_EXPLOSION, table);

	////////////////////////////////////////

	kill_code = WEAPON_KILL_CODE_SELF_DESTRUCT;

	count = 3;

	table->kill_code_criteria_count [kill_code] = count;

	table->kill_code_criteria [kill_code] = malloc_heap_mem (sizeof (weapon_explosion_kill_code_criteria) * count);

	add_explosion_criteria (0, kill_code, 0, 99, META_EXPLOSION_TYPE_NONE, table);
	add_explosion_criteria (1, kill_code, 100, 999, MEDIUM_HE_META_EXPLOSION, table);
	add_explosion_criteria (2, kill_code, 1000, INT_MAX, LARGE_HE_META_EXPLOSION, table);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_armour_piercing_explosion_criteria_table ()
{
	weapon_explosion_criteria
		*table;

	weapon_kill_codes
		kill_code;

	int
		count;

	table = &armour_piercing_explosion_criteria_table;

	////////////////////////////////////////

	kill_code =  WEAPON_KILL_CODE_OK;

	table->kill_code_criteria_count [kill_code] = 0;

	table->kill_code_criteria [kill_code] = NULL;

	////////////////////////////////////////

	kill_code = WEAPON_KILL_CODE_EXHAUSTED;

	count = 1;

	table->kill_code_criteria_count [kill_code] = count;

	table->kill_code_criteria [kill_code] = malloc_heap_mem (sizeof (weapon_explosion_kill_code_criteria) * count);

	add_explosion_criteria (0, kill_code, 0, INT_MAX, META_EXPLOSION_TYPE_NONE, table);

	////////////////////////////////////////

	kill_code = WEAPON_KILL_CODE_OUT_OF_BOUNDS;

	count = 1;

	table->kill_code_criteria_count [kill_code] = count;

	table->kill_code_criteria [kill_code] = malloc_heap_mem (sizeof (weapon_explosion_kill_code_criteria) * count);

	add_explosion_criteria (0, kill_code, 0, INT_MAX, META_EXPLOSION_TYPE_NONE, table);

	////////////////////////////////////////

	kill_code = WEAPON_KILL_CODE_HIT_LAND;

	count = 3;

	table->kill_code_criteria_count [kill_code] = count;

	table->kill_code_criteria [kill_code] = malloc_heap_mem (sizeof (weapon_explosion_kill_code_criteria) * count);

	add_explosion_criteria (0, kill_code, 0, 99, SMALL_EARTH_META_EXPLOSION, table);
	add_explosion_criteria (1, kill_code, 100, 999, MEDIUM_EARTH_META_EXPLOSION, table);
	add_explosion_criteria (2, kill_code, 1000, INT_MAX, LARGE_EARTH_META_EXPLOSION, table);

	////////////////////////////////////////

	kill_code = WEAPON_KILL_CODE_HIT_WATER;

	count = 3;

	table->kill_code_criteria_count [kill_code] = count;

	table->kill_code_criteria [kill_code] = malloc_heap_mem (sizeof (weapon_explosion_kill_code_criteria) * count);

	add_explosion_criteria (0, kill_code, 0, 99, SMALL_WATER_META_EXPLOSION, table);
	add_explosion_criteria (1, kill_code, 100, 999, MEDIUM_WATER_META_EXPLOSION, table);
	add_explosion_criteria (2, kill_code, 1000, INT_MAX, LARGE_WATER_META_EXPLOSION, table);

	////////////////////////////////////////

	kill_code = WEAPON_KILL_CODE_HIT_TARGET;

	count = 3;

	table->kill_code_criteria_count [kill_code] = count;

	table->kill_code_criteria [kill_code] = malloc_heap_mem (sizeof (weapon_explosion_kill_code_criteria) * count);

	add_explosion_criteria (0, kill_code, 0, 99, SMALL_AP_META_EXPLOSION, table);
	add_explosion_criteria (1, kill_code, 100, 999, MEDIUM_AP_META_EXPLOSION, table);
	add_explosion_criteria (2, kill_code, 1000, INT_MAX, LARGE_AP_META_EXPLOSION, table);

	////////////////////////////////////////

	kill_code = WEAPON_KILL_CODE_OVERSHOT_TARGET;

	count = 1;

	table->kill_code_criteria_count [kill_code] = count;

	table->kill_code_criteria [kill_code] = malloc_heap_mem (sizeof (weapon_explosion_kill_code_criteria) * count);

	add_explosion_criteria (0, kill_code, 0, INT_MAX, META_EXPLOSION_TYPE_NONE, table);

	////////////////////////////////////////

	kill_code = WEAPON_KILL_CODE_SELF_DESTRUCT;

	count = 1;

	table->kill_code_criteria_count [kill_code] = count;

	table->kill_code_criteria [kill_code] = malloc_heap_mem (sizeof (weapon_explosion_kill_code_criteria) * count);

	add_explosion_criteria (0, kill_code, 0, INT_MAX, META_EXPLOSION_TYPE_NONE, table);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_heat_explosion_criteria_table ()
{
	weapon_explosion_criteria
		*table;

	weapon_kill_codes
		kill_code;

	int
		count;

	table = &heat_explosion_criteria_table;

	////////////////////////////////////////

	kill_code =  WEAPON_KILL_CODE_OK;

	table->kill_code_criteria_count [kill_code] = 0;

	table->kill_code_criteria [kill_code] = NULL;

	////////////////////////////////////////

	kill_code = WEAPON_KILL_CODE_EXHAUSTED;

	count = 1;

	table->kill_code_criteria_count [kill_code] = count;

	table->kill_code_criteria [kill_code] = malloc_heap_mem (sizeof (weapon_explosion_kill_code_criteria) * count);

	add_explosion_criteria (0, kill_code, 0, INT_MAX, SMALL_HE_META_EXPLOSION, table);

	////////////////////////////////////////

	kill_code = WEAPON_KILL_CODE_OUT_OF_BOUNDS;

	count = 1;

	table->kill_code_criteria_count [kill_code] = count;

	table->kill_code_criteria [kill_code] = malloc_heap_mem (sizeof (weapon_explosion_kill_code_criteria) * count);

	add_explosion_criteria (0, kill_code, 0, INT_MAX, META_EXPLOSION_TYPE_NONE, table);

	////////////////////////////////////////

	kill_code = WEAPON_KILL_CODE_HIT_LAND;

	count = 3;

	table->kill_code_criteria_count [kill_code] = count;

	table->kill_code_criteria [kill_code] = malloc_heap_mem (sizeof (weapon_explosion_kill_code_criteria) * count);

	add_explosion_criteria (0, kill_code, 0, 99, SMALL_HE_META_EXPLOSION, table);
	add_explosion_criteria (1, kill_code, 100, 999, MEDIUM_HE_META_EXPLOSION, table);
	add_explosion_criteria (2, kill_code, 1000, INT_MAX, LARGE_HE_META_EXPLOSION, table);

	////////////////////////////////////////

	kill_code = WEAPON_KILL_CODE_HIT_WATER;

	count = 3;

	table->kill_code_criteria_count [kill_code] = count;

	table->kill_code_criteria [kill_code] = malloc_heap_mem (sizeof (weapon_explosion_kill_code_criteria) * count);

	add_explosion_criteria (0, kill_code, 0, 99, SMALL_WATER_META_EXPLOSION, table);
	add_explosion_criteria (1, kill_code, 100, 999, MEDIUM_WATER_META_EXPLOSION, table);
	add_explosion_criteria (2, kill_code, 1000, INT_MAX, LARGE_WATER_META_EXPLOSION, table);

	////////////////////////////////////////

	kill_code = WEAPON_KILL_CODE_HIT_TARGET;

	count = 3;

	table->kill_code_criteria_count [kill_code] = count;

	table->kill_code_criteria [kill_code] = malloc_heap_mem (sizeof (weapon_explosion_kill_code_criteria) * count);

	add_explosion_criteria (0, kill_code, 0, 99, SMALL_HE_META_EXPLOSION, table);
	add_explosion_criteria (1, kill_code, 100, 999, MEDIUM_HE_META_EXPLOSION, table);
	add_explosion_criteria (2, kill_code, 1000, INT_MAX, LARGE_HE_META_EXPLOSION, table);

	////////////////////////////////////////

	kill_code = WEAPON_KILL_CODE_OVERSHOT_TARGET;

	count = 1;

	table->kill_code_criteria_count [kill_code] = count;

	table->kill_code_criteria [kill_code] = malloc_heap_mem (sizeof (weapon_explosion_kill_code_criteria) * count);

	add_explosion_criteria (0, kill_code, 0, INT_MAX, SMALL_HE_META_EXPLOSION, table);

/*	count = 3;

	table->kill_code_criteria_count [kill_code] = count;

	table->kill_code_criteria [kill_code] = malloc_heap_mem (sizeof (weapon_explosion_kill_code_criteria) * count);

	add_explosion_criteria (0, kill_code, 0, 99, SMALL_HE_META_EXPLOSION, table);
	add_explosion_criteria (1, kill_code, 100, 999, MEDIUM_HE_META_EXPLOSION, table);
	add_explosion_criteria (2, kill_code, 1000, INT_MAX, LARGE_HE_META_EXPLOSION, table); */

	////////////////////////////////////////

	kill_code = WEAPON_KILL_CODE_SELF_DESTRUCT;

	count = 1;

	table->kill_code_criteria_count [kill_code] = count;

	table->kill_code_criteria [kill_code] = malloc_heap_mem (sizeof (weapon_explosion_kill_code_criteria) * count);

	add_explosion_criteria (0, kill_code, 0, INT_MAX, SMALL_HE_META_EXPLOSION, table);

/*
	count = 3;

	table->kill_code_criteria_count [kill_code] = count;

	table->kill_code_criteria [kill_code] = malloc_heap_mem (sizeof (weapon_explosion_kill_code_criteria) * count);

	add_explosion_criteria (0, kill_code, 0, 99, SMALL_HE_META_EXPLOSION, table);
	add_explosion_criteria (1, kill_code, 100, 999, MEDIUM_HE_META_EXPLOSION, table);
	add_explosion_criteria (2, kill_code, 1000, INT_MAX, LARGE_HE_META_EXPLOSION, table);*/
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_smoke_grenade_explosion_criteria_table ()
{
	weapon_explosion_criteria
		*table;

	weapon_kill_codes
		kill_code;

	int
		count;

	table = &smoke_grenade_explosion_criteria_table;

	////////////////////////////////////////

	kill_code =  WEAPON_KILL_CODE_OK;

	table->kill_code_criteria_count [kill_code] = 0;

	table->kill_code_criteria [kill_code] = NULL;

	////////////////////////////////////////

	kill_code = WEAPON_KILL_CODE_EXHAUSTED;

	count = 1;

	table->kill_code_criteria_count [kill_code] = count;

	table->kill_code_criteria [kill_code] = malloc_heap_mem (sizeof (weapon_explosion_kill_code_criteria) * count);

	add_explosion_criteria (0, kill_code, 0, INT_MAX, META_EXPLOSION_TYPE_NONE, table);

	////////////////////////////////////////

	kill_code = WEAPON_KILL_CODE_OUT_OF_BOUNDS;

	count = 1;

	table->kill_code_criteria_count [kill_code] = count;

	table->kill_code_criteria [kill_code] = malloc_heap_mem (sizeof (weapon_explosion_kill_code_criteria) * count);

	add_explosion_criteria (0, kill_code, 0, INT_MAX, META_EXPLOSION_TYPE_NONE, table);

	////////////////////////////////////////

	kill_code = WEAPON_KILL_CODE_HIT_LAND;

	count = 1;

	table->kill_code_criteria_count [kill_code] = count;

	table->kill_code_criteria [kill_code] = malloc_heap_mem (sizeof (weapon_explosion_kill_code_criteria) * count);

	add_explosion_criteria (0, kill_code, 0, INT_MAX, PURPLE_FLARE_META_EXPLOSION, table);

	////////////////////////////////////////

	kill_code = WEAPON_KILL_CODE_HIT_WATER;

	count = 1;

	table->kill_code_criteria_count [kill_code] = count;

	table->kill_code_criteria [kill_code] = malloc_heap_mem (sizeof (weapon_explosion_kill_code_criteria) * count);

	add_explosion_criteria (0, kill_code, 0, INT_MAX, META_EXPLOSION_TYPE_NONE, table);

	////////////////////////////////////////

	kill_code = WEAPON_KILL_CODE_HIT_TARGET;

	table->kill_code_criteria_count [kill_code] = 0;

	table->kill_code_criteria [kill_code] = NULL;

	////////////////////////////////////////

	kill_code = WEAPON_KILL_CODE_OVERSHOT_TARGET;

	table->kill_code_criteria_count [kill_code] = 0;

	table->kill_code_criteria [kill_code] = NULL;

	////////////////////////////////////////

	kill_code = WEAPON_KILL_CODE_SELF_DESTRUCT;

	table->kill_code_criteria_count [kill_code] = 0;

	table->kill_code_criteria [kill_code] = NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_weapon_explosion_criteria_tables ()
{
	weapon_explosion_criteria
		*table;

	weapon_kill_codes
		kill_code;

	///////////////////////////////////////////////////////////////////////

	table = &ball_explosion_criteria_table;

	for (kill_code = 0; kill_code < NUM_WEAPON_KILL_CODES; kill_code ++)
	{
		if (table->kill_code_criteria [kill_code])
		{
			free_mem (table->kill_code_criteria [kill_code]);
		}
	}

	///////////////////////////////////////////////////////////////////////

	table = &high_explosive_explosion_criteria_table;

	for (kill_code = 0; kill_code < NUM_WEAPON_KILL_CODES; kill_code ++)
	{
		if (table->kill_code_criteria [kill_code])
		{
			free_mem (table->kill_code_criteria [kill_code]);
		}
	}

	///////////////////////////////////////////////////////////////////////

	table = &armour_piercing_explosion_criteria_table;

	for (kill_code = 0; kill_code < NUM_WEAPON_KILL_CODES; kill_code ++)
	{
		if (table->kill_code_criteria [kill_code])
		{
			free_mem (table->kill_code_criteria [kill_code]);
		}
	}

	///////////////////////////////////////////////////////////////////////

	table = &heat_explosion_criteria_table;

	for (kill_code = 0; kill_code < NUM_WEAPON_KILL_CODES; kill_code ++)
	{
		if (table->kill_code_criteria [kill_code])
		{
			free_mem (table->kill_code_criteria [kill_code]);
		}
	}

	///////////////////////////////////////////////////////////////////////

	table = &smoke_grenade_explosion_criteria_table;

	for (kill_code = 0; kill_code < NUM_WEAPON_KILL_CODES; kill_code ++)
	{
		if (table->kill_code_criteria [kill_code])
		{
			free_mem (table->kill_code_criteria [kill_code]);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void add_explosion_criteria (int index, weapon_kill_codes kill_code, int min_damage, int max_damage, meta_explosion_types type, weapon_explosion_criteria *table)
{

	ASSERT (index >= 0);

	ASSERT (index < table->kill_code_criteria_count [kill_code]);

	table->kill_code_criteria [kill_code][index].min_damage = min_damage;
	table->kill_code_criteria [kill_code][index].max_damage = max_damage;

	table->kill_code_criteria [kill_code][index].type = type;
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

	warhead_type = get_local_entity_int_value (en, INT_TYPE_WEAPON_WARHEAD_TYPE);

	//
	// get relevant criteria table, based on warhead type
	//

	switch (warhead_type)
	{
		case WEAPON_WARHEAD_TYPE_NONE:
		{
			return META_EXPLOSION_TYPE_NONE;
		}
		case WEAPON_WARHEAD_TYPE_BALL:
		{
			damage_capability = get_local_entity_int_value (en, INT_TYPE_SOFT_DAMAGE_CAPABILITY);

			criteria_table = &ball_explosion_criteria_table;

			break;
		}
		case WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE:
		{
			damage_capability = get_local_entity_int_value (en, INT_TYPE_SOFT_DAMAGE_CAPABILITY);

			criteria_table = &high_explosive_explosion_criteria_table;

			break;
		}
		case WEAPON_WARHEAD_TYPE_ARMOUR_PIERCING:
		{
			damage_capability = get_local_entity_int_value (en, INT_TYPE_HARD_DAMAGE_CAPABILITY);

			criteria_table = &armour_piercing_explosion_criteria_table;

			break;
		}
		case WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE_ANTI_TANK:
		{
			damage_capability = get_local_entity_int_value (en, INT_TYPE_SOFT_DAMAGE_CAPABILITY);

			criteria_table = &heat_explosion_criteria_table;

			break;
		}
		case WEAPON_WARHEAD_TYPE_SMOKE_GRENADE:
		{
			damage_capability = 0;

			criteria_table = &smoke_grenade_explosion_criteria_table;

			break;
		}
		default:
		{
			debug_fatal ("XP_WPN : Invalid warhead type %d", warhead_type);

			return META_EXPLOSION_TYPE_NONE;
		}
	}

	//
	// search through the table, checking all other criteria
	//

	if (criteria_table->kill_code_criteria [kill_code] == NULL)
	{
		debug_fatal ("XP_WPN : No criteria table found for warhead type %d, kill code %d", warhead_type, kill_code);
	}

	for (loop = 0; loop < criteria_table->kill_code_criteria_count [kill_code]; loop ++)
	{
		//
		// check damage capability
		//

		if ( ( criteria_table->kill_code_criteria [kill_code][loop].min_damage <= damage_capability ) &&
				( criteria_table->kill_code_criteria [kill_code][loop].max_damage >= damage_capability ) )
		{

			return criteria_table->kill_code_criteria [kill_code][loop].type;
		}
	}

	return META_EXPLOSION_TYPE_NONE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
