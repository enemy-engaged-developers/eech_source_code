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

static int response_to_collision (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{

	entity
		*force,
		*enemy_force,
		*aggressor;

	int
		damage_caused,
		old_damage_state,
		total_damage_level;

	float
		damage_modifier;

	#if DEBUG_MODULE

	debug_log_entity_message (message, receiver, sender, pargs);

	#endif

	damage_modifier = va_arg (pargs, double);

	old_damage_state = vehicle_critically_damaged(receiver);
			
	damage_caused = damage_client_server_entity (receiver, sender, damage_modifier);

	total_damage_level = get_local_entity_int_value (receiver, INT_TYPE_DAMAGE_LEVEL);

	if (sender)
	{
		if (get_local_entity_type (sender) == ENTITY_TYPE_WEAPON)
		{
			aggressor = get_local_entity_parent (sender, LIST_TYPE_LAUNCHED_WEAPON);

			//
			// a direct hit from a H.E. weapon causes smoke from impact point
			//

			if ((damage_modifier == 1.0) && (damage_caused > 100))
			{
				int
					random_seed;

				weapon_warhead_types
					warhead_type;

				random_seed = get_client_server_entity_random_number_seed (sender);

				if (frand1x (&random_seed) > 0.8)
				{
	
					warhead_type = (weapon_warhead_types) get_local_entity_int_value (sender, INT_TYPE_WEAPON_WARHEAD_TYPE);
	
					if ((warhead_type >= WEAPON_WARHEAD_TYPE_HIGH_EXPLOSIVE_ANTI_TANK) &&
							(warhead_type <= WEAPON_WARHEAD_TYPE_CONVENTIONAL_MUNITIONS))
					{
						vec3d
							rel_pos,
							rel_vec,
							*en_pos,
							*weapon_pos;
	
						matrix3x3
							m,
							inv;
	
						en_pos = get_local_entity_vec3d_ptr (receiver, VEC3D_TYPE_POSITION);
						weapon_pos = get_local_entity_vec3d_ptr (sender, VEC3D_TYPE_POSITION);

						rel_vec.x = weapon_pos->x - en_pos->x;
						rel_vec.y = weapon_pos->y - en_pos->y;
						rel_vec.z = weapon_pos->z - en_pos->z;
	
						get_local_entity_attitude_matrix (receiver, m);

						get_inverse_matrix (inv, m);

						multiply_matrix3x3_vec3d (&rel_pos, inv, &rel_vec);

						create_client_server_meta_smoke_list_specified_offset (META_SMOKE_LIST_TYPE_FIRE_SHORT_DURATION, receiver, &rel_pos);
					}
				}
			}
		}
		else
		{
			aggressor = sender;
		}
	}
	else
	{
		aggressor = NULL;
	}

	force = get_local_force_entity ((entity_sides) get_local_entity_int_value (receiver, INT_TYPE_SIDE));

	enemy_force = get_local_force_entity (get_enemy_side (get_local_entity_int_value (receiver, INT_TYPE_SIDE)));

	//
	// assess damage
	//

	if (old_damage_state < vehicle_critically_damaged(receiver)) // vehicle critically damaged
		credit_client_server_mobile_kill (receiver, aggressor);
	
	if (total_damage_level <= 0)
	{
		if (aggressor)
		{
			play_vehicle_destroyed_speech (receiver, aggressor);

//			credit_client_server_mobile_kill (receiver, aggressor);
		}

		notify_local_entity (ENTITY_MESSAGE_FORCE_DESTROYED, force, receiver, aggressor);

		notify_local_entity (ENTITY_MESSAGE_FORCE_DESTROYED, enemy_force, receiver, aggressor);

		kill_client_server_entity (receiver);
	}
	else
	{

		/////////////////////////////////////////////////////////////////
		//
		// SPECIAL_EFFECT_HOOK FOR GETTING_SHOT
		//
		/////////////////////////////////////////////////////////////////

		if (aggressor)
		{
			play_vehicle_shot_at_speech (receiver, aggressor);
		}

		/////////////////////////////////////////////////////////////////
		//
		//
		/////////////////////////////////////////////////////////////////

		//notify hit. ?
	}

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int response_to_articulate_loading_doors (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	object_3d_instance
		*inst3d;

	sound_sample_indices
		sound_sample_index;

	#if DEBUG_MODULE

	debug_log_entity_message (message, receiver, sender, pargs);

	#endif

	inst3d = (object_3d_instance *) get_local_entity_ptr_value (receiver, PTR_TYPE_INSTANCE_3D_OBJECT);

	if (inst3d)
	{
		if (object_contains_sub_object_type (inst3d, OBJECT_3D_SUB_OBJECT_LOADING_DOOR, 0, NULL))
		{
			sound_sample_index = SOUND_SAMPLE_INDEX_SHIP_DOORS;

			create_client_server_sound_effect_entity
			(
				receiver,
				ENTITY_SIDE_NEUTRAL,
				ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,
				SOUND_CHANNEL_SOUND_EFFECT,
				SOUND_LOCALITY_ALL,
				NULL,												// position
				1.0,												// amplification
				1.0,												// Werewolf pitch
				TRUE,												// valid sound effect
				FALSE,											// looping
				1,													// sample count
				&sound_sample_index							// sample index list
			);
		}
	}

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if DEBUG_MODULE

static int response_to_link_child (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	debug_log_entity_message (message, receiver, sender, pargs);

	return (TRUE);
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if DEBUG_MODULE

static int response_to_unlink_child (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	debug_log_entity_message (message, receiver, sender, pargs);

	return (TRUE);
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if DEBUG_MODULE

// WARNING: THIS IS OVERLOADED AT VEHICLE LEVEL //

static int response_to_link_parent (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	debug_log_entity_message (message, receiver, sender, pargs);

	return (TRUE);
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if DEBUG_MODULE

// WARNING: THIS IS OVERLOADED AT VEHICLE LEVEL //

static int response_to_unlink_parent (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	debug_log_entity_message (message, receiver, sender, pargs);

	return (TRUE);
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_ship_vehicle_message_responses (void)
{
	overload_vehicle_message_responses (ENTITY_TYPE_SHIP_VEHICLE);

	message_responses[ENTITY_TYPE_SHIP_VEHICLE][ENTITY_MESSAGE_COLLISION] 						= response_to_collision;

	message_responses[ENTITY_TYPE_SHIP_VEHICLE][ENTITY_MESSAGE_ARTICULATE_LOADING_DOORS] 	= response_to_articulate_loading_doors;

	#if DEBUG_MODULE

	message_responses[ENTITY_TYPE_SHIP_VEHICLE][ENTITY_MESSAGE_LINK_CHILD]		= response_to_link_child;

	message_responses[ENTITY_TYPE_SHIP_VEHICLE][ENTITY_MESSAGE_UNLINK_CHILD]	= response_to_unlink_child;

	message_responses[ENTITY_TYPE_SHIP_VEHICLE][ENTITY_MESSAGE_LINK_PARENT]		= response_to_link_parent;

	message_responses[ENTITY_TYPE_SHIP_VEHICLE][ENTITY_MESSAGE_UNLINK_PARENT]	= response_to_unlink_parent;

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
