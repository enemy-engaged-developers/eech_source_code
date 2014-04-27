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
#define AIRCRAFT_MORTAL_DAMAGE_LEVEL 30
#define AIRCRAFT_CRITICAL_DAMAGE_LEVEL 5
#define MAX_META_SMOKE_LIST_ATTACHMENT_POINTS 	2

aircraft_damage_types aircraft_critically_damaged (entity *en)
{

	aircraft
		*raw;

	int
		percent_damaged;

	raw = (aircraft *) get_local_entity_data (en);

	percent_damaged = (100 * raw->damage_level) / aircraft_database[raw->mob.sub_type].initial_damage_level;

	if (percent_damaged < AIRCRAFT_CRITICAL_DAMAGE_LEVEL)
	{
		return AIRCRAFT_DAMAGE_CRITICAL;
	}
	else if (percent_damaged < AIRCRAFT_MORTAL_DAMAGE_LEVEL)
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

static struct ATTACHED_META_SMOKE_LIST_TABLE
{

	meta_smoke_list_types							type;
	object_3d_sub_object_index_numbers			attachment_point[MAX_META_SMOKE_LIST_ATTACHMENT_POINTS];

} attached_meta_smoke_list_table[] =
	{
		////////////////////////////////////////////////
		//
		// LIGHT DAMAGE MOVING
		//
		////////////////////////////////////////////////
		{
			META_SMOKE_LIST_TYPE_AIRCRAFT_LIGHT_DAMAGE_MOVING,
			{
				OBJECT_3D_SUB_OBJECT_DAMAGED_SMOKE,
				-1
			}
		},
		////////////////////////////////////////////////
		//
		// HEAVY DAMAGE MOVING
		//
		////////////////////////////////////////////////
		{
			META_SMOKE_LIST_TYPE_AIRCRAFT_HEAVY_DAMAGE_MOVING,
			{
				OBJECT_3D_SUB_OBJECT_DAMAGED_SMOKE,
				-1
			}
		},
		////////////////////////////////////////////////
		//
		// LIGHT DAMAGE STATIC
		//
		////////////////////////////////////////////////
		{
			META_SMOKE_LIST_TYPE_AIRCRAFT_LIGHT_DAMAGE_STATIC,
			{
				OBJECT_3D_SUB_OBJECT_DAMAGED_SMOKE,
				-1
			}
		},
		////////////////////////////////////////////////
		//
		// HEAVY DAMAGE STATIC
		//
		////////////////////////////////////////////////
		{
			META_SMOKE_LIST_TYPE_AIRCRAFT_HEAVY_DAMAGE_STATIC,
			{
				OBJECT_3D_SUB_OBJECT_DAMAGED_SMOKE,
				-1
			}
		},
		////////////////////////////////////////////////
		//
		// TERMINATOR
		//
		////////////////////////////////////////////////
		{
			(meta_smoke_list_types) -1,
			{
				-1,
				-1
			}
		}
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void attach_aircraft_meta_smoke_lists (entity *en)
{
	int
		item,
		point;

	object_3d_sub_object_index_numbers
		attachment_point;

	meta_smoke_list_types
		type;

	item = 0;

	while (TRUE)
	{
		type = attached_meta_smoke_list_table [item].type;

		if (type == -1)
		{
			break;
		}
		else
		{
			point = 0;

			while (TRUE)
			{
				attachment_point = attached_meta_smoke_list_table [item].attachment_point [point];

				if (attachment_point == -1)
				{
					break;
				}

				if (point >= MAX_META_SMOKE_LIST_ATTACHMENT_POINTS)
				{
					debug_fatal ("AIRCRAFT: Attach meta smoke lists - too many attachment points");
				}

				attach_local_meta_smoke_lists_to_object (en, type, attachment_point, NULL);

				point ++;
			}
		}

		item ++;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void switch_aircraft_damaged_smoke (entity *en)
{
	int
		high_speed;
	aircraft_damage_types
		damage_level;

	high_speed = get_local_entity_float_value (en, FLOAT_TYPE_VELOCITY) >= AIRCRAFT_DAMAGED_SMOKE_SPEED_THRESHOLD;

	damage_level = aircraft_critically_damaged(en);
	
	#if DEBUG_MODULE
		debug_log("AIRCRAFT: switching damaged smoke for %s, damage_level %i, high_speed %i", aircraft_database [get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE)].full_name, damage_level, high_speed);
	#endif
		
	if (get_local_entity_int_value (en, INT_TYPE_OPERATIONAL_STATE) != OPERATIONAL_STATE_DEAD)
	{
		set_infinite_smoke_list_generating_state (en, ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_LIGHT_DAMAGE_MOVING, high_speed && (damage_level == AIRCRAFT_DAMAGE_MORTAL));
		set_infinite_smoke_list_generating_state (en, ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_HEAVY_DAMAGE_MOVING, high_speed && (damage_level == AIRCRAFT_DAMAGE_CRITICAL));
		set_infinite_smoke_list_generating_state (en, ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_LIGHT_DAMAGE_STATIC, !high_speed && (damage_level == AIRCRAFT_DAMAGE_MORTAL));
		set_infinite_smoke_list_generating_state (en, ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_HEAVY_DAMAGE_STATIC, !high_speed && (damage_level == AIRCRAFT_DAMAGE_CRITICAL));
	}
	else
	{
		set_infinite_smoke_list_generating_state (en, ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_LIGHT_DAMAGE_MOVING, FALSE);
		set_infinite_smoke_list_generating_state (en, ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_HEAVY_DAMAGE_MOVING, FALSE);
		set_infinite_smoke_list_generating_state (en, ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_LIGHT_DAMAGE_STATIC, FALSE);
		set_infinite_smoke_list_generating_state (en, ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_HEAVY_DAMAGE_STATIC, FALSE);

		clear_smoke_list_generator_lifetime (en, ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_LIGHT_DAMAGE_MOVING);
		clear_smoke_list_generator_lifetime (en, ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_HEAVY_DAMAGE_MOVING);
		clear_smoke_list_generator_lifetime (en, ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_LIGHT_DAMAGE_STATIC);
		clear_smoke_list_generator_lifetime (en, ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_HEAVY_DAMAGE_STATIC);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void assess_aircraft_damage_level (entity *en, int old_damage_level, int new_damage_level)
{

	float
		initial_damage,
		old_percent_damaged,
		new_percent_damaged;

	if (old_damage_level == new_damage_level)
	{
		return;
	}
	
	initial_damage = (float)(aircraft_database[get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE)].initial_damage_level);
	
	old_percent_damaged = (100.0 * (float)old_damage_level) / initial_damage;
	new_percent_damaged = (100.0 * (float)new_damage_level) / initial_damage;

	#if DEBUG_MODULE
		debug_log("AIRCRAFT: %s old damage %f, new damage %f", aircraft_database [get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE)].full_name, old_percent_damaged, new_percent_damaged);
	#endif
		
	// Eject Pilot(s)

	if (get_local_entity_int_value (en, INT_TYPE_AIRBORNE_AIRCRAFT) && get_local_entity_int_value (en, INT_TYPE_PLAYER) == ENTITY_PLAYER_AI && new_percent_damaged < 0.75 * AIRCRAFT_CRITICAL_DAMAGE_LEVEL && new_damage_level > 10)
		initiate_aircraft_crew_ejection (en);

	// update smoke
	
	if ((new_percent_damaged < AIRCRAFT_CRITICAL_DAMAGE_LEVEL && old_percent_damaged >= AIRCRAFT_CRITICAL_DAMAGE_LEVEL) || 
			(new_percent_damaged < AIRCRAFT_MORTAL_DAMAGE_LEVEL && old_percent_damaged >= AIRCRAFT_MORTAL_DAMAGE_LEVEL)) // damage threshold reached
	{
		switch_aircraft_damaged_smoke(en);
		
		if (get_comms_model() == COMMS_MODEL_SERVER && new_damage_level > 10) // return group home
		{
			entity
				*group,
				*guide,
				*task;
			
			group = get_local_entity_parent (en, LIST_TYPE_MEMBER);

			if (group)
			{
				guide = get_local_group_primary_guide (group);
						
				if (guide)
				{
					task = get_local_entity_parent (guide, LIST_TYPE_GUIDE);

					debug_log("TASK PRIORITY %f", task->task_data->task_priority);
					if (task->task_data->task_priority <= 5.0)
						group_return_to_base (group);
				}
			}
		}
	}
		
	if (new_percent_damaged >= AIRCRAFT_MORTAL_DAMAGE_LEVEL && old_percent_damaged < AIRCRAFT_MORTAL_DAMAGE_LEVEL) // recovery happened
		switch_aircraft_damaged_smoke(en);
		
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

	victim_side = (entity_sides) get_local_entity_int_value (victim, INT_TYPE_SIDE);

	aggressor_side = (entity_sides) get_local_entity_int_value (aggressor, INT_TYPE_SIDE);

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
					(speech_array_types) array_type, speech_index
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
						(speech_array_types) array_type, speech_index
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

	victim_side = (entity_sides) get_local_entity_int_value (victim, INT_TYPE_SIDE);

	aggressor_side = (entity_sides) get_local_entity_int_value (aggressor, INT_TYPE_SIDE);

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

	victim_side = (entity_sides) get_local_entity_int_value (victim, INT_TYPE_SIDE);

	aggressor_side = (entity_sides) get_local_entity_int_value (aggressor, INT_TYPE_SIDE);

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

	side = (entity_sides) get_local_entity_int_value (en, INT_TYPE_SIDE);

	if (side == (entity_sides) get_local_entity_int_value (new_sector, INT_TYPE_SECTOR_SIDE))
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
