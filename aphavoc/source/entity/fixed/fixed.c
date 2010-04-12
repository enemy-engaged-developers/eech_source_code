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

static int
	num_building_destroyed_cpg_comments [NUM_ENTITY_SIDES] = {0, 2, 2},
	last_building_destroyed_cpg_comment [NUM_ENTITY_SIDES] = {0, 0, 0};

static speech_instance_type
	building_destroyed_cpg_comments [] =
	{
		{ -1,												(speech_array_types) -1, 										100,	SPEECH_INTRODUCTION_NEVER },
		{ SPEECH_CPG_TARGET_DESTROYED,						SPEECH_ARRAY_CPG_MESSAGES,			25,	SPEECH_INTRODUCTION_SOMETIMES },
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void play_building_destroyed_speech (entity *building, entity *aggressor)
{
	int
		val,
		array_type,
		speech_index;

	entity_sides
		aggressor_side;

	ASSERT (aggressor);

	if (get_local_entity_int_value (aggressor, INT_TYPE_IDENTIFY_AIRCRAFT))
	{
		// PLAY_SPEECH (WINGMAN/CPG)
		//
		// (There goes the neighbourhood) | (meeting adjourned) etc.

		aggressor_side = (entity_sides) get_local_entity_int_value (aggressor, INT_TYPE_SIDE);
		
		val = get_speech_random_value
				(
					building_destroyed_cpg_comments,
					num_building_destroyed_cpg_comments [aggressor_side],
					last_building_destroyed_cpg_comment [aggressor_side]
				);

		array_type = building_destroyed_cpg_comments [val].array_type;
		speech_index = building_destroyed_cpg_comments [val].speech_index;

		if (get_local_entity_int_value (aggressor, INT_TYPE_PLAYER) != ENTITY_PLAYER_AI)
		{
			play_client_server_cpg_message (aggressor, 0.4f, 4.0, SPEECH_CATEGORY_DESTROYED_TARGETS, 18.0, speech_index);
		}
		else
		{
			play_client_server_wingman_message
			(
				aggressor,
				0.4f,
				4.0,
				SPEECH_CATEGORY_DESTROYED_TARGETS, 18.0,
				SPEECH_INTRODUCTION_SOMETIMES,
				SPEECH_ARRAY_WINGMAN_MESSAGES, SPEECH_WINGMAN_TARGET_DESTROYED
			);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void restore_local_fixed_entity (entity *en)
{
	int
		object_index;

	entity
		*keysite;

	ASSERT (en);

	//
	// Set alive flag
	//

	ASSERT (!get_local_entity_int_value (en, INT_TYPE_ALIVE));

	set_local_entity_int_value (en, INT_TYPE_ALIVE, TRUE);

	//
	// 3d shape
	//

	object_index = get_local_entity_int_value (en, INT_TYPE_OBJECT_3D_SHAPE);

	set_local_entity_int_value (en, INT_TYPE_OBJECT_3D_SHAPE, get_3d_object_restored_object_index (object_index));

	//
	// Restore damage level (MUST be done AFTER object 3d shape reset)
	//

	set_local_entity_int_value (en, INT_TYPE_DAMAGE_LEVEL, get_local_entity_int_value (en, INT_TYPE_INITIAL_DAMAGE_LEVEL));

	ASSERT (get_local_entity_int_value (en, INT_TYPE_DAMAGE_LEVEL) > 0);

	//
	// Keysite strength
	//

	keysite = get_fixed_structure_keysite_entity (en);

	ASSERT (keysite);
	
	restore_local_entity_importance_to_keysite (en, keysite);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



