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

#define AIRCRAFT_DAMAGE_TIMER_MAX_VALUE	10.0

static float
	aircraft_damage_timer = 0.0;

static int
	send_damage_update_flag = FALSE;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MORTAL_DAMAGE_LEVEL 25
#define CRITICAL_DAMAGE_LEVEL 15

aircraft_damage_types aircraft_critically_damaged (entity *en)
{

	aircraft
		*raw;

	int
		percent_damaged;

	raw = get_local_entity_data (en);

	percent_damaged = (100 * raw->damage_level) / aircraft_database[raw->mob.sub_type].initial_damage_level;

	if (percent_damaged < CRITICAL_DAMAGE_LEVEL)
	{
		return AIRCRAFT_DAMAGE_CRITICAL;
	}
	else if (percent_damaged < MORTAL_DAMAGE_LEVEL)
	{
		return AIRCRAFT_DAMAGE_MORTAL;
	}
	else
	{
		return AIRCRAFT_DAMAGE_NONE;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void assess_aircraft_damage_level (entity *en, int old_damage_level, int new_damage_level)
{

	switch (get_local_entity_type (en))
	{
		case ENTITY_TYPE_FIXED_WING:
		{
			assess_fixed_wing_damage_level (en, old_damage_level, new_damage_level);

			break;
		}
		case ENTITY_TYPE_HELICOPTER:
		{
			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int
	num_ac_hit_aggressor_wingman_comments [NUM_ENTITY_SIDES] = {0, 1, 1},
	last_ac_hit_aggressor_wingman_comment [NUM_ENTITY_SIDES] = {0, 0, 0};

static speech_instance_type
	aircraft_hit_aggressor_wingman_comments [] =
	{
		{ SPEECH_WINGMAN_TARGET_HIT,					SPEECH_ARRAY_WINGMAN_MESSAGES, 100,	SPEECH_INTRODUCTION_SOMETIMES },
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int
	num_ac_hit_aggressor_cpg_comments [NUM_ENTITY_SIDES] = {0, 1, 1},
	last_ac_hit_aggressor_cpg_comment [NUM_ENTITY_SIDES] = {0, 0, 0};

static speech_instance_type
	aircraft_hit_aggressor_cpg_comments [] =
	{
		{ SPEECH_CPG_TARGET_HIT,								SPEECH_ARRAY_CPG_MESSAGES, 100,	SPEECH_INTRODUCTION_NEVER },
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int
	num_ac_hit_victim_wingman_comments [NUM_ENTITY_SIDES] = {0, 1, 1},
	last_ac_hit_victim_wingman_comment [NUM_ENTITY_SIDES] = {0, 0, 0};

static speech_instance_type
	aircraft_hit_victim_wingman_comments [] =
	{
		{ SPEECH_WINGMAN_TAKING_HITS,					SPEECH_ARRAY_WINGMAN_MESSAGES,	100,	SPEECH_INTRODUCTION_ALWAYS },
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void play_aircraft_shot_at_speech (entity *victim, entity *aggressor)
{
	entity_sides
		victim_side,
		aggressor_side;

	int
		val,
		array_type,
		speech_index,
		*last_index;

	ASSERT (victim);

	ASSERT (aggressor);

	victim_side = get_local_entity_int_value (victim, INT_TYPE_SIDE);

	aggressor_side = get_local_entity_int_value (aggressor, INT_TYPE_SIDE);

	last_index = NULL;

	if (aggressor_side == victim_side)
	{
		//
		// FRIENDLY FIRE
		//

		////////////////////////////////////
		//
		// victims speech
		//
		////////////////////////////////////
		
		////////////////////////////////////
		//
		// Aggressors speech
		//
		////////////////////////////////////

		if (get_local_entity_int_value (aggressor, INT_TYPE_PLAYER) != ENTITY_PLAYER_AI)
		{
			if (aggressor != victim)
			{
				// PLAY_SPEECH (CPG)
				//
				// (Hold your fire, we're hitting friendlies) | (Cease fire, we're hitting our own guys)
	
				if (rand16 () & 1)
				{
					speech_index = SPEECH_CPG_FRIENDLY_FIRE1;
				}
				else
				{
					speech_index = SPEECH_CPG_FRIENDLY_FIRE2;
				}
	
				play_client_server_cpg_message
				(
					aggressor,
					1.0,
					3.0,
					SPEECH_CATEGORY_ATTACKING_TARGETS,
					8.0,
					speech_index
				);
			}
		}
	}
	else
	{
		if (aircraft_critically_damaged (victim))
		{
			////////////////////////////////////
			//
			// victims speech
			//
			////////////////////////////////////
		
			if (get_local_entity_int_value (victim, INT_TYPE_PLAYER) != ENTITY_PLAYER_AI)
			{
				// PLAY_SPEECH (CPG)
				//
				// (Where did that come from) | (We're french fries) | etc
			}
			else
			{
				// PLAY_SPEECH (WINGMAN)
				//
				//	[This is..]
				// [callsign + number]
				// (Mayday, Mayday, we are going down) | (I've been hit, I'm going down, repeat going down) 

				speech_index = SPEECH_WINGMAN_GOING_DOWN;

				play_client_server_wingman_message
				(
					victim,
					0.5,
					4.0,
					SPEECH_CATEGORY_UNDER_ATTACK, 10.0,
					SPEECH_INTRODUCTION_ALWAYS,
					SPEECH_ARRAY_WINGMAN_MESSAGES, speech_index
				);
			}

			////////////////////////////////////
			//
			// Aggressors speech
			//
			////////////////////////////////////

			play_aircraft_destroyed_speech (victim, aggressor);
		}
		else
		{
			////////////////////////////////////
			//
			// victims speech
			//
			////////////////////////////////////

			if (get_local_entity_int_value (victim, INT_TYPE_PLAYER) != ENTITY_PLAYER_AI)
			{
			}
			else
			{
				// PLAY_SPEECH (WINGMAN)
				//
				//	[This is..]
				// [callsign + number]
				// (We're taking hits) | (Things are heating up out here) | (It's too dangerous up here etc..)

				val = get_speech_random_value
						(
							aircraft_hit_victim_wingman_comments,
							num_ac_hit_victim_wingman_comments [victim_side],
							last_ac_hit_victim_wingman_comment [victim_side]
						);

				array_type = aircraft_hit_victim_wingman_comments [val].array_type;
				speech_index = aircraft_hit_victim_wingman_comments [val].speech_index;

				play_client_server_wingman_message
				(
					victim,
					0.8,
					8.0,
					SPEECH_CATEGORY_UNDER_ATTACK, 16.0,
					aircraft_hit_victim_wingman_comments [val].introduction,
					array_type, speech_index
				);
			}

			////////////////////////////////////
			//
			// Aggressors speech
			//
			////////////////////////////////////

			if (get_local_entity_int_value (aggressor, INT_TYPE_IDENTIFY_AIRCRAFT))
			{
				if (get_local_entity_int_value (aggressor, INT_TYPE_PLAYER) != ENTITY_PLAYER_AI)
				{
					// PLAY_SPEECH (CPG)
					//
					// (Target Hit) | (Turkey shoot) | (Fish in a barrel) | (They can run, etc)

					val = get_speech_random_value
							(
								aircraft_hit_aggressor_cpg_comments,
								num_ac_hit_aggressor_cpg_comments [aggressor_side],
								last_ac_hit_aggressor_cpg_comment [aggressor_side]
							);
	
					array_type = aircraft_hit_aggressor_cpg_comments [val].array_type;
					speech_index = aircraft_hit_aggressor_cpg_comments [val].speech_index;
	
					play_client_server_cpg_message
					(
						aggressor,
						0.6,
						5.0,
						SPEECH_CATEGORY_ATTACKING_TARGETS, 15.0,
						speech_index
					);
				}
				else
				{
					// PLAY_SPEECH (WINGMAN)
					//
					//	[This is..]
					// [callsign + number]
					// (Target Hit) | (Turkey shoot) | (Fish in a barrel) | (They can run, etc)

					val = get_speech_random_value
							(
								aircraft_hit_aggressor_wingman_comments,
								num_ac_hit_aggressor_wingman_comments [aggressor_side],
								last_ac_hit_aggressor_wingman_comment [aggressor_side]
							);

					array_type = aircraft_hit_aggressor_wingman_comments [val].array_type;
					speech_index = aircraft_hit_aggressor_wingman_comments [val].speech_index;

					play_client_server_wingman_message
					(
						aggressor,
						0.6,
						5.0,
						SPEECH_CATEGORY_ATTACKING_TARGETS, 16.0,
						aircraft_hit_aggressor_wingman_comments [val].introduction,
						array_type, speech_index
					);
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int
	num_ac_destroyed_cpg_comments [NUM_ENTITY_SIDES] = {0, 4, 4},
	last_ac_destroyed_cpg_comment [NUM_ENTITY_SIDES] = {0, 0, 0};

static speech_instance_type
	aircraft_destroyed_cpg_comments [] =
	{
		{ SPEECH_CPG_TARGET_DESTROYED,						SPEECH_ARRAY_CPG_MESSAGES,			100, 	SPEECH_INTRODUCTION_SOMETIMES },
		{ SPEECH_CPG_TARGET_IS_DOWN,							SPEECH_ARRAY_CPG_MESSAGES,			100, 	SPEECH_INTRODUCTION_SOMETIMES },
		{ SPEECH_CPG_KILL_CONFIRMED,							SPEECH_ARRAY_CPG_MESSAGES,			100, 	SPEECH_INTRODUCTION_SOMETIMES },
		{ SPEECH_CPG_GOOD_KILL,									SPEECH_ARRAY_CPG_MESSAGES,			100, 	SPEECH_INTRODUCTION_SOMETIMES },
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void play_aircraft_destroyed_speech (entity *victim, entity *aggressor)
{
	entity_sides
		victim_side,
		aggressor_side;

	int
		val,
		array_type,
		speech_index;

	ASSERT (victim);

	ASSERT (aggressor);

	victim_side = get_local_entity_int_value (victim, INT_TYPE_SIDE);

	aggressor_side = get_local_entity_int_value (aggressor, INT_TYPE_SIDE);

	if (aggressor_side == victim_side)
	{
		//
		// FRIENDLY FIRE
		//

		if (get_local_entity_int_value (aggressor, INT_TYPE_PLAYER) != ENTITY_PLAYER_AI)
		{
			if (aggressor != victim)
			{
				// PLAY_SPEECH (CPG)
				//
				// (Hold your fire, we're hitting friendlies) | (Cease fire, we're hitting our own guys)
	
				if (rand16 () & 1)
				{
					speech_index = SPEECH_CPG_FRIENDLY_FIRE1;
				}
				else
				{
					speech_index = SPEECH_CPG_FRIENDLY_FIRE2;
				}
	
				play_client_server_cpg_message
				(
					aggressor,
					1.0,
					3.0,
					SPEECH_CATEGORY_ATTACKING_TARGETS,
					8.0,
					speech_index
				);
			}
		}
	}
	else
	{
		if (get_local_entity_int_value (aggressor, INT_TYPE_IDENTIFY_AIRCRAFT))
		{
			if (get_local_entity_int_value (aggressor, INT_TYPE_PLAYER) != ENTITY_PLAYER_AI)
			{
				// PLAY_SPEECH (CPG)
				//
				// (Target down) | (Enemy aircraft shot down) | etc
	
				val = get_speech_random_value
						(
							aircraft_destroyed_cpg_comments,
							num_ac_destroyed_cpg_comments [aggressor_side],
							last_ac_destroyed_cpg_comment [aggressor_side]
						);

				array_type = aircraft_destroyed_cpg_comments [val].array_type;
				speech_index = aircraft_destroyed_cpg_comments [val].speech_index;

				play_client_server_cpg_message
				(
					aggressor,
					0.6,
					5.0,
					SPEECH_CATEGORY_DESTROYED_TARGETS, 8.0,
					speech_index
				);
			}
			else
			{
				// PLAY_SPEECH (WINGMAN)
				//
	
				play_client_server_wingman_message
				(
					aggressor,
					0.6,
					5.0,
					SPEECH_CATEGORY_DESTROYED_TARGETS, 8.0,
					SPEECH_INTRODUCTION_SOMETIMES,
					SPEECH_ARRAY_WINGMAN_MESSAGES, SPEECH_WINGMAN_TARGET_DESTROYED
				);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void play_aircraft_targeted_speech (entity *victim, entity *aggressor)
{
	entity_sides
		victim_side,
		aggressor_side;

	ASSERT (victim);

	ASSERT (aggressor);

	victim_side = get_local_entity_int_value (victim, INT_TYPE_SIDE);

	aggressor_side = get_local_entity_int_value (aggressor, INT_TYPE_SIDE);

	if (victim_side == aggressor_side)
	{
		//
		// TARGETTING OWN SIDE
		//
	}
	else
	{
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void play_aircraft_flown_into_new_sector_speech (entity *en, entity *old_sector, entity *new_sector)
{
	entity_sides
		side;

	ASSERT (en);

	side = get_local_entity_int_value (en, INT_TYPE_SIDE);

	if (side == get_local_entity_int_value (new_sector, INT_TYPE_SECTOR_SIDE))
	{
		//
		// flown into friendly sector
		//
	}
	else
	{
		//
		// flown into enemy sector
		//
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_aircraft_damage_timers (void)
{

	if (send_damage_update_flag)
	{
		send_damage_update_flag = FALSE;
	}

	aircraft_damage_timer -= get_delta_time ();

	if (aircraft_damage_timer < 0.0)
	{
		aircraft_damage_timer = AIRCRAFT_DAMAGE_TIMER_MAX_VALUE;

		send_damage_update_flag = TRUE;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_aircraft_send_damage_update_flag (void)
{
	return send_damage_update_flag;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


