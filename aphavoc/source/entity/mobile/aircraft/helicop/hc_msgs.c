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

static int response_to_link_child (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	list_types
		list_type;

	list_type = va_arg (pargs, list_types);

	#if DEBUG_MODULE

	debug_log_entity_message (message, receiver, sender, pargs);

	#endif

	switch (list_type)
	{
		////////////////////////////////////////
		case LIST_TYPE_TARGET:
		////////////////////////////////////////
		{
			if (sender)
			{
				if (receiver == get_gunship_entity ())
				{
					if (get_local_entity_int_value (sender, INT_TYPE_THREAT_TYPE) != THREAT_TYPE_INVALID)
					{
						activate_common_threat_warning_system (sender);
					}
				}
			}

			break;
		}
	}

	return (TRUE);
}

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

// WARNING: THIS IS OVERLOADED AT AIRCRAFT LEVEL //

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

// WARNING: THIS IS OVERLOADED AT AIRCRAFT LEVEL //

static int response_to_unlink_parent (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	debug_log_entity_message (message, receiver, sender, pargs);

	return (TRUE);
}

#endif

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
		total_damage_level;

	aircraft_damage_types
		old_damage_state,
		new_damage_state;

	float
		damage_modifier;

	ASSERT (receiver);

	damage_modifier = va_arg (pargs, double);
	
	ASSERT(damage_modifier >= 0 && damage_modifier <= 1.0);

	#if DEBUG_MODULE

	// IMPORTANT: this muct come after we read va_arg, or it will clobber it!
	debug_log_entity_message (message, receiver, sender, pargs);

	#endif

	if (sender)
	{
		if (get_local_entity_type (sender) == ENTITY_TYPE_WEAPON)
		{
			aggressor = get_local_entity_parent (sender, LIST_TYPE_LAUNCHED_WEAPON);
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

	//
	// Fix to stop helicopters from killing themselves through firing missiles into the ground...
	//

	if ((aggressor == receiver) && (get_local_entity_int_value (receiver, INT_TYPE_PLAYER) == ENTITY_PLAYER_AI))
	{
		return TRUE;
	}

	//
	//
	//

	force = get_local_force_entity ((entity_sides) get_local_entity_int_value (receiver, INT_TYPE_SIDE));

	enemy_force = get_local_force_entity (get_enemy_side (get_local_entity_int_value (receiver, INT_TYPE_SIDE)));

	//
	// assess damage
	//

	old_damage_state = aircraft_critically_damaged (receiver);

	damage_caused = damage_client_server_entity (receiver, sender, damage_modifier);

	total_damage_level = get_local_entity_int_value (receiver, INT_TYPE_DAMAGE_LEVEL);

	new_damage_state = aircraft_critically_damaged (receiver);

	if ((old_damage_state != AIRCRAFT_DAMAGE_CRITICAL) && (new_damage_state == AIRCRAFT_DAMAGE_CRITICAL))
	{
		if (aggressor)
		{
			//
			// credit kill
			//
		
			credit_client_server_mobile_kill (receiver, aggressor);
/*	
			//
			// multiplayer pilot kills
			//
	
			if (receiver != aggressor)
			{
				if (
						(get_local_entity_int_value (receiver, INT_TYPE_PLAYER) != ENTITY_PLAYER_AI) &&
						(get_local_entity_int_value (aggressor, INT_TYPE_PLAYER) != ENTITY_PLAYER_AI)
					)
				{
					entity
						*pilot_en;
	
					int
						score;
	
					pilot_en = get_local_entity_first_child (aggressor, LIST_TYPE_AIRCREW);
	
					while (pilot_en)
					{
						score = get_local_entity_int_value (pilot_en, INT_TYPE_KILLS);	
	
						if ((get_global_session_special_gametype() == SPECIAL_GAME_TYPE_COOPERATIVE) &&
								(get_local_entity_int_value (receiver, INT_TYPE_SIDE) == get_local_entity_int_value (aggressor, INT_TYPE_SIDE)))
						{
							score -= 1;
						}
						else
						{
							score += 1;
	
							notify_local_entity (ENTITY_MESSAGE_FORCE_SPECIAL_KILL, enemy_force, receiver, score);
						}
	
						set_client_server_entity_int_value (pilot_en, INT_TYPE_KILLS, score);
	
						pilot_en = get_local_entity_child_succ (pilot_en, LIST_TYPE_AIRCREW);
					}
				}
			}
*/
		}
	}

	/////////////////////////////////////////////////////////////////
	//
	// Assess damage caused
	//
	/////////////////////////////////////////////////////////////////

	if (total_damage_level <= 0)
	{
		ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

		//
		// if the player was shot down, record it in the log
		//

		if (get_local_entity_int_value (receiver, INT_TYPE_PLAYER) == ENTITY_PLAYER_LOCAL)
		{
			// deaths moved to landing assessment - player dies upon hitting the ground with enough force
//			inc_player_log_kills (get_global_gunship_side (), get_current_player_log (), receiver);

			dynamics_kill_model (DYNAMICS_DESTROY_SHOT_DOWN, aggressor);
		}
		else if (get_local_entity_int_value (receiver, INT_TYPE_PLAYER) == ENTITY_PLAYER_REMOTE)
		{
			transmit_entity_comms_message (ENTITY_COMMS_PLAYER_KILL, aggressor, receiver);

			kill_client_server_entity (receiver);
		}
		else
		{

			kill_client_server_entity (receiver);
		}

		notify_local_entity (ENTITY_MESSAGE_FORCE_DESTROYED, force, receiver, aggressor); // should these be before kill ?

		notify_local_entity (ENTITY_MESSAGE_FORCE_DESTROYED, enemy_force, receiver, aggressor);

		//
		// Play appropriate sound effects / speech
		//

		if (aggressor)
		{
			play_aircraft_destroyed_speech (receiver, aggressor);
		}
	}
	else
	{
		if (damage_caused > 0)
		{
			if (get_local_entity_int_value (receiver, INT_TYPE_PLAYER) != ENTITY_PLAYER_AI)
			{
				//
				// Damage users helicopter
				//

				damage_helicopter_via_damage_level (receiver, aggressor);

				//
				// damage avionics
				//

				if (get_local_entity_int_value (receiver, INT_TYPE_PLAYER) != ENTITY_PLAYER_AI)	
				{
					if (damage_caused < 100.0)
					{
						damage_client_server_entity_avionics (receiver, GUNSHIP_DAMAGE_LEVEL_LIGHT);
					}
					else if (damage_caused < 300.0)
					{
						damage_client_server_entity_avionics (receiver, GUNSHIP_DAMAGE_LEVEL_MEDIUM);
					}
					else
					{
						damage_client_server_entity_avionics (receiver, GUNSHIP_DAMAGE_LEVEL_HEAVY);
					}
				}
			}
		}

		/////////////////////////////////////////////////////////////////
		//
		// SPECIAL_EFFECT_HOOK FOR GETTING_SHOT
		//
		/////////////////////////////////////////////////////////////////

		if (aggressor)
		{
			play_aircraft_shot_at_speech (receiver, aggressor);
		}

		/////////////////////////////////////////////////////////////////
		//
		//
		/////////////////////////////////////////////////////////////////

		//notify hit. ?
	}

	//
	// add force to players helicopters
	//

	if (damage_caused > 0.0)
	{
		switch (get_local_entity_int_value (receiver, INT_TYPE_PLAYER))
		{
			case ENTITY_PLAYER_LOCAL:
			{
				add_dynamic_explosion_force (get_local_entity_vec3d_ptr (sender, VEC3D_TYPE_POSITION), (float)damage_caused);
	
				break;
			}
			case ENTITY_PLAYER_REMOTE:
			{
				// send comms message
	
				break;
			}
		}
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
			sound_sample_index = SOUND_SAMPLE_INDEX_HELICOPTER_DOORS;

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

static int response_to_set_entity_position (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{

	vec3d
		*position,
		new_position,
		delta_position,
		*parent_position;

	float
		velocity,
		en_heading,
		heading;

	helicopter
		*raw;

	raw = (helicopter *) get_local_entity_data (receiver);

	position = va_arg (pargs, vec3d *);

	heading = (float) va_arg (pargs, double);

	en_heading = get_local_entity_float_value (receiver, FLOAT_TYPE_HEADING);

	velocity = (float) va_arg (pargs, double);

	parent_position = get_local_entity_vec3d_ptr (sender, VEC3D_TYPE_POSITION);

	delta_position.x = raw->ac.mob.position.x - parent_position->x;
	delta_position.y = raw->ac.mob.position.y - parent_position->y;
	delta_position.z = raw->ac.mob.position.z - parent_position->z;

	new_position.x = position->x + ((cos (heading - en_heading) * delta_position.x) + (sin (heading - en_heading) * delta_position.z));
	new_position.y = position->y + delta_position.y;
	new_position.z = position->z + ((cos (heading - en_heading) * delta_position.z) - (sin (heading - en_heading) * delta_position.x));

	set_local_entity_vec3d (receiver, VEC3D_TYPE_POSITION, &new_position);

	set_local_entity_float_value (receiver, FLOAT_TYPE_HEADING, heading);

	set_local_entity_float_value (receiver, FLOAT_TYPE_VELOCITY, velocity);

	return (TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define HELICOPTER_LAST_TO_REACH_DISTANCE		(750.0 * 750.0)

static int response_to_check_mobile_reached_guide (entity_messages message, entity *receiver, entity *sender, va_list pargs)
{
	float
		range;

	vec3d
		guide_pos;

	entity
		*wp;

	entity_sub_types
		waypoint_type;

	if (receiver == get_external_view_entity ())
	{

		wp = NULL;
	}

	ASSERT (sender);

	ASSERT (get_local_entity_type (sender) == ENTITY_TYPE_GUIDE);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	wp = get_local_entity_parent (sender, LIST_TYPE_CURRENT_WAYPOINT);

	ASSERT (wp);

	//
	// Check if player should skip waypoint
	//

	if (get_local_entity_int_value (receiver, INT_TYPE_PLAYER) != ENTITY_PLAYER_AI)
	{
		waypoint_type = get_local_entity_int_value (wp, INT_TYPE_ENTITY_SUB_TYPE);

		if (waypoint_database [waypoint_type].player_skip_waypoint)
		{
			return TRUE;
		}
	}
	else
	{
	
		//
		// Check if landed
		//
	
		if (get_local_entity_int_value (receiver, INT_TYPE_LANDED))
		{
			return FALSE;
		}
	}
	
	//
	// Don't allow movement before rotors have spun up.
	//

	if ((get_local_entity_float_value (receiver, FLOAT_TYPE_MAIN_ROTOR_SPIN_UP_TIMER) > 0.0) && (get_local_entity_int_value (receiver, INT_TYPE_PLAYER) == ENTITY_PLAYER_AI))
	{
		return FALSE;
	}

	if (get_local_entity_int_value (receiver, INT_TYPE_TASK_LEADER))
	{
		//
		// check range to guide
		//
	
		if (get_guide_criteria_valid (sender, GUIDE_CRITERIA_RADIUS))
		{
			range = get_local_entity_float_value (receiver, FLOAT_TYPE_DISTANCE);
	
			if (range > get_guide_criteria_value (sender, GUIDE_CRITERIA_RADIUS))
			{

				return FALSE;
			}
		}
	
		//
		// check altitude
		//
	
		if (get_guide_criteria_valid (sender, GUIDE_CRITERIA_ALTITUDE))
		{
			if ((get_local_entity_int_value (receiver, INT_TYPE_PLAYER) != ENTITY_PLAYER_AI) &&
				(get_local_entity_int_value (wp, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_WAYPOINT_LANDED) &&
				(!get_local_entity_int_value (receiver, INT_TYPE_AUTO_PILOT)))
			{
				if (get_local_entity_int_value (receiver, INT_TYPE_AIRBORNE_AIRCRAFT))
				{

					// if player, not autopilot, land wp and not airborne

					return FALSE;
				}
			}
			else
			{
	
				get_local_entity_vec3d (sender, VEC3D_TYPE_POSITION, &guide_pos);
					
				range = get_local_entity_float_value (receiver, FLOAT_TYPE_ALTITUDE);
		
				range -= get_local_entity_float_value (receiver, FLOAT_TYPE_CENTRE_OF_GRAVITY_TO_GROUND_DISTANCE);
		
				range -= guide_pos.y;
		
				if (fabs (range) > get_guide_criteria_value (sender, GUIDE_CRITERIA_ALTITUDE))
				{
	
					return FALSE;
				}
			}
		}
	
		//
		// check heading
		//
	
		if (get_local_entity_int_value (receiver, INT_TYPE_PLAYER) == ENTITY_PLAYER_AI)
		{
			if (get_guide_criteria_valid (sender, GUIDE_CRITERIA_HEADING))
			{
				float
					heading,
					delta_heading,
					required_heading;
		
				heading = get_local_entity_float_value (receiver, FLOAT_TYPE_HEADING);
		
				get_guide_required_heading (sender, receiver, &required_heading);
		
				delta_heading = (required_heading - heading);
		
				if (delta_heading < -PI)
				{
					delta_heading += PI2;
				}
				else if (delta_heading > PI)
				{
					delta_heading -= PI2;
				}
		
				if (fabs (delta_heading) > get_guide_criteria_value (sender, GUIDE_CRITERIA_HEADING))
				{
					return FALSE;
				}
			}
		}
		
		//
		// check weapon vector
		//
	
		if (get_local_entity_int_value (receiver, INT_TYPE_PLAYER) == ENTITY_PLAYER_AI)
		{
			if (get_guide_criteria_valid (sender, GUIDE_CRITERIA_WEAPON_VECTOR))
			{
				entity_sub_types
					selected_weapon;
		
				vec3d
					*weapon_vector,
					*weapon_to_target_vector;
		
				float
					launch_angle_error;
					
				selected_weapon = get_local_entity_int_value (receiver, INT_TYPE_SELECTED_WEAPON);
		
				ASSERT (selected_weapon != ENTITY_SUB_TYPE_WEAPON_NO_WEAPON);
		
				if (get_local_entity_int_value (receiver, INT_TYPE_WEAPON_AND_TARGET_VECTORS_VALID))
				{
					weapon_vector = get_local_entity_vec3d_ptr (receiver, VEC3D_TYPE_WEAPON_VECTOR);
			
					ASSERT (weapon_vector);
			
					weapon_to_target_vector = get_local_entity_vec3d_ptr (receiver, VEC3D_TYPE_WEAPON_TO_TARGET_VECTOR);
			
					ASSERT (weapon_to_target_vector);
			
					launch_angle_error = acos (get_3d_unit_vector_dot_product (weapon_vector, weapon_to_target_vector));
		
					if (fabs (launch_angle_error) > weapon_database[selected_weapon].max_launch_angle_error)
					{
						return FALSE;
					}
				}
			}
		}
	}
	else
	{
		entity
			*leader;

		vec3d
			*pos,
			*leader_pos;

		ASSERT (get_guide_criteria_valid (sender, GUIDE_CRITERIA_LAST_TO_REACH));

		//
		// None Task Leader Entities (only for last to reach)
		// Check distance to task leader
		//

		leader = (entity *) get_local_entity_ptr_value (sender, PTR_TYPE_TASK_LEADER);

		ASSERT (leader);

		if (get_local_entity_int_value (leader, INT_TYPE_PLAYER) == ENTITY_PLAYER_AI)
		{
			pos = get_local_entity_vec3d_ptr (receiver, VEC3D_TYPE_POSITION);
			
			leader_pos = get_local_entity_vec3d_ptr (leader, VEC3D_TYPE_POSITION);

			range = get_sqr_2d_range (pos, leader_pos);

			if (range > HELICOPTER_LAST_TO_REACH_DISTANCE)
			{
				return FALSE;
			}
		}
	}
		
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_helicopter_message_responses (void)
{
	overload_aircraft_message_responses (ENTITY_TYPE_HELICOPTER);

	message_responses[ENTITY_TYPE_HELICOPTER][ENTITY_MESSAGE_LINK_CHILD]							= response_to_link_child;

	#if DEBUG_MODULE

	message_responses[ENTITY_TYPE_HELICOPTER][ENTITY_MESSAGE_UNLINK_CHILD]						= response_to_unlink_child;

	message_responses[ENTITY_TYPE_HELICOPTER][ENTITY_MESSAGE_LINK_PARENT]						= response_to_link_parent;

	message_responses[ENTITY_TYPE_HELICOPTER][ENTITY_MESSAGE_UNLINK_PARENT]						= response_to_unlink_parent;

	#endif

	message_responses[ENTITY_TYPE_HELICOPTER][ENTITY_MESSAGE_COLLISION]							= response_to_collision;

	message_responses[ENTITY_TYPE_HELICOPTER][ENTITY_MESSAGE_ARTICULATE_LOADING_DOORS]		= response_to_articulate_loading_doors;

	message_responses[ENTITY_TYPE_HELICOPTER][ENTITY_MESSAGE_SET_ENTITY_POSITION]				= response_to_set_entity_position;

	message_responses[ENTITY_TYPE_HELICOPTER][ENTITY_MESSAGE_CHECK_MOBILE_REACHED_GUIDE]	= response_to_check_mobile_reached_guide;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////






