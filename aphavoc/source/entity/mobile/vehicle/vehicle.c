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

static int
	num_vehicle_hit_comments [NUM_ENTITY_SIDES] = {0, 4, 4},
	last_vehicle_hit_comment [NUM_ENTITY_SIDES] = {0, 0, 0};

static speech_instance_type
	vehicle_hit_comments [] =
	{
		{ SPEECH_GC_REQUEST_SUPPORT_AT,		SPEECH_ARRAY_GC_MESSAGES,		100,	SPEECH_INTRODUCTION_ALWAYS },
		{ SPEECH_GC_PINNED_DOWN_AT,			SPEECH_ARRAY_GC_MESSAGES,		100,	SPEECH_INTRODUCTION_ALWAYS },
		{ SPEECH_GC_NEED_AIR_SUPPORT_AT,		SPEECH_ARRAY_GC_MESSAGES,		100,	SPEECH_INTRODUCTION_ALWAYS },
		{ SPEECH_GC_UNDER_HEAVY_FIRE,			SPEECH_ARRAY_GC_MESSAGES,		100,	SPEECH_INTRODUCTION_ALWAYS },
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void play_vehicle_shot_at_speech (entity *victim, entity *aggressor)
{
	entity_sides
		victim_side,
		aggressor_side;

	int
		val,
		speech_index;

	vec3d
		*pos;

	ASSERT (victim);

	ASSERT (aggressor);

	pos = get_local_entity_vec3d_ptr (victim, VEC3D_TYPE_POSITION);

	ASSERT (pos);

	victim_side = (entity_sides) get_local_entity_int_value (victim, INT_TYPE_SIDE);

	aggressor_side = (entity_sides) get_local_entity_int_value (aggressor, INT_TYPE_SIDE);

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
			//
			// PLAY_SPEECH (CPG)
			//

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
				12.0,
				speech_index
			);
		}
	}
	else
	{
		////////////////////////////////////
		//
		// victims speech
		//
		////////////////////////////////////

		val = get_speech_random_value
				(
					vehicle_hit_comments,
					num_vehicle_hit_comments [victim_side],
					last_vehicle_hit_comment [victim_side]
				);

		speech_index = vehicle_hit_comments [val].speech_index;
	
		get_speech_sector_coordinates (pos);

		// PLAY_SPEECH (GC)
		//
		// [GC Introduction],
		// (We are pinned down by enemy fire) | (we are taking heavy fire, requesting ariel assistance)
		// location

		play_client_server_speech
		(
			get_session_entity (),
			victim,
			victim_side,
			ENTITY_SUB_TYPE_EFFECT_SOUND_RADIO_MESSAGE,
			SOUND_LOCALITY_RADIO,
			0.0,
			1.0,
			45.0,
			SPEECH_ORIGINATOR_GROUND_CONTROLLER,
			SPEECH_CATEGORY_UNDER_ATTACK,
			300.0,
			SPEECH_ARRAY_GC_MESSAGES, SPEECH_GC_INTRODUCTION,
			SPEECH_ARRAY_GC_MESSAGES, speech_index,
			SPEECH_ARRAY_NUMBERS, speech_sector_coordinates [0],
			SPEECH_ARRAY_NUMBERS, speech_sector_coordinates [1],
			SPEECH_ARRAY_NUMBERS, speech_sector_coordinates [2],
			SPEECH_ARRAY_NUMBERS, speech_sector_coordinates [3],
			SPEECH_ARRAY_NUMBERS, speech_sector_coordinates [4],
			SPEECH_ARRAY_NUMBERS, speech_sector_coordinates [5],
			-1
		);

		////////////////////////////////////
		//
		// Aggressors speech
		//
		////////////////////////////////////

		if (get_local_entity_int_value (aggressor, INT_TYPE_IDENTIFY_AIRCRAFT))
		{
			if (get_local_entity_int_value (aggressor, INT_TYPE_PLAYER) != ENTITY_PLAYER_AI)
			{
				//
				// PLAY_SPEECH (CPG)
				//

				play_client_server_cpg_message
				(
					aggressor,
					0.4f,
					3.0,
					SPEECH_CATEGORY_ATTACKING_TARGETS,
					12.0,
					SPEECH_CPG_TARGET_HIT
				);
			}
			else
			{
				//
				// PLAY_SPEECH (WINGMAN)
				//

				play_client_server_wingman_message
				(
					aggressor,
					0.4f,
					3.0,
					SPEECH_CATEGORY_ATTACKING_TARGETS, 12.0,
					SPEECH_INTRODUCTION_SOMETIMES,
					SPEECH_ARRAY_WINGMAN_MESSAGES, SPEECH_WINGMAN_TARGET_HIT
				);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int
	num_vh_destroyed_wingman_comments [NUM_ENTITY_SIDES] = {0, 1, 1},
	last_vh_destroyed_wingman_comment [NUM_ENTITY_SIDES] = {0, 0, 0};

static speech_instance_type
	vehicle_destroyed_wingman_comments [] =
	{
		{ SPEECH_WINGMAN_TARGET_DESTROYED,	SPEECH_ARRAY_WINGMAN_MESSAGES,	100, 	SPEECH_INTRODUCTION_SOMETIMES },
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int
	num_vh_destroyed_cpg_comments [NUM_ENTITY_SIDES] = {0, 3, 3},
	last_vh_destroyed_cpg_comment [NUM_ENTITY_SIDES] = {0, 0, 0};

static speech_instance_type
	vehicle_destroyed_cpg_comments [] =
	{
		{ SPEECH_CPG_TARGET_DESTROYED,					SPEECH_ARRAY_CPG_MESSAGES,			100, 	SPEECH_INTRODUCTION_SOMETIMES },
		{ SPEECH_CPG_KILL_CONFIRMED,						SPEECH_ARRAY_CPG_MESSAGES,			100, 	SPEECH_INTRODUCTION_SOMETIMES },
		{ SPEECH_CPG_GOOD_KILL,								SPEECH_ARRAY_CPG_MESSAGES,			100, 	SPEECH_INTRODUCTION_SOMETIMES },
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void play_vehicle_destroyed_speech (entity *victim, entity *aggressor)
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

	if (victim_side == aggressor_side)
	{
		//
		// FRIENDLY FIRE
		//

		if (get_local_entity_int_value (aggressor, INT_TYPE_PLAYER) != ENTITY_PLAYER_AI)
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
	else
	{
		if (get_local_entity_int_value (aggressor, INT_TYPE_IDENTIFY_AIRCRAFT))
		{
			if (get_local_entity_int_value (aggressor, INT_TYPE_PLAYER) != ENTITY_PLAYER_AI)
			{
				// PLAY_SPEECH (CPG)
				//
				// (Target destroyed) | (Enemy armour destroyed) | (Good Kill) | etc

				val = get_speech_random_value
						(
							vehicle_destroyed_cpg_comments,
							num_vh_destroyed_cpg_comments [aggressor_side],
							last_vh_destroyed_cpg_comment [aggressor_side]
						);

				speech_index = vehicle_destroyed_cpg_comments [val].speech_index;
	
				play_client_server_cpg_message
				(
					aggressor,
					0.4f,
					3.0,
					SPEECH_CATEGORY_ATTACKING_TARGETS, 10.0,
					speech_index
				);
			}
			else
			{
				// PLAY_SPEECH (WINGMAN)
				//
				// (Target destroyed) | (Enemy armour destroyed) | (Good Kill) | etc

				val = get_speech_random_value
						(
							vehicle_destroyed_wingman_comments,
							num_vh_destroyed_wingman_comments [aggressor_side],
							last_vh_destroyed_wingman_comment [aggressor_side]
						);

				array_type = vehicle_destroyed_wingman_comments [val].array_type;
				speech_index = vehicle_destroyed_wingman_comments [val].speech_index;
	
				play_client_server_wingman_message
				(
					aggressor,
					0.4f,
					3.0,
					SPEECH_CATEGORY_ATTACKING_TARGETS, 10.0,
					vehicle_destroyed_wingman_comments [val].introduction,
					(speech_array_types) array_type, speech_index
				);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
