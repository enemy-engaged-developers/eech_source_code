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

void play_entity_weapon_selected_speech (entity *en, entity_sub_types weapon_type)
{
	int
		speech_index;

	entity_sides
		side;

	//
	// only play speech for players
	//

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	speech_index = weapon_database [weapon_type].weapon_selected_cpg_speech;

	if (speech_index != -1)
	{
		if (get_local_entity_int_value (en, INT_TYPE_PLAYER) != ENTITY_PLAYER_AI)
		{
			side = (entity_sides) get_local_entity_int_value (en, INT_TYPE_SIDE);

			remove_speech_category_from_buffers (side, SPEECH_ORIGINATOR_CO_PILOT, SPEECH_CATEGORY_WEAPONS_SYSTEMS);

			play_client_server_speech
			(
				en,
				en,
				side,
				ENTITY_SUB_TYPE_EFFECT_SOUND_CPG_MESSAGE,
				SOUND_LOCALITY_RADIO,
				0.4f,		// delay
				0.2f,		// priority
				1.5,		// expire time
				SPEECH_ORIGINATOR_CO_PILOT,
				SPEECH_CATEGORY_WEAPONS_SYSTEMS,
				-1.0,		// category silence timer
				SPEECH_ARRAY_CPG_MESSAGES, speech_index,
				-1
			);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void play_entity_weapon_launched_speech (entity *en, entity_sub_types weapon_type)
{
	int
		speech_index;

	//
	// only play speech for players
	//

	speech_index = weapon_database [weapon_type].weapon_launched_cpg_speech;

	if (speech_index != -1)
	{
		if (get_local_entity_int_value (en, INT_TYPE_PLAYER) != ENTITY_PLAYER_AI)
		{
			play_client_server_cpg_message
			(
				en,
				0.8f,
				2.0,
				SPEECH_CATEGORY_FIRING,
				8.0,
				speech_index
			);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void play_entity_weapon_low_speech (entity *en, entity_sub_types weapon_type)
{
	int
		speech_index;

	//
	// only play speech for players
	//

	speech_index = weapon_database [weapon_type].weapon_low_cpg_speech;

	if (speech_index != -1)
	{
		if (get_local_entity_int_value (en, INT_TYPE_PLAYER) != ENTITY_PLAYER_AI)
		{
			if (!get_local_entity_int_value (get_session_entity (), INT_TYPE_INFINITE_WEAPONS))
			{
				play_client_server_cpg_message
				(
					en,
					1.0,
					5.0,
					SPEECH_CATEGORY_AMMO_LOW,
					-1.0,
					speech_index
				);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void play_entity_weapon_out_speech (entity *en, entity_sub_types weapon_type)
{
	int
		speech_index;

	//
	// only play speech for players
	//

	speech_index = weapon_database [weapon_type].weapon_out_cpg_speech;

	if (speech_index != -1)
	{
		if (get_local_entity_int_value (en, INT_TYPE_PLAYER) != ENTITY_PLAYER_AI)
		{
			play_client_server_cpg_message
			(
				en,
				1.0,
				5.0,
				SPEECH_CATEGORY_AMMO_LOW,
				-1.0,
				speech_index
			);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

