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

#define DEBUG_KILL_INFO TRUE

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float mobile_terrain_adjust_waypoint_height (entity *en, vec3d *wp_pos, float min_height)
{

	float
		range,
		terrain_elevation;

	vec3d
		test_point,
		wp_vec,
		vector;

	mobile
		*raw;

	raw = (mobile *) get_local_entity_data (en);

	//
	// find point in front of mobile
	//
	
	test_point.x = raw->position.x + ((raw->velocity * 1.0 + 10.0) * raw->zv.x);
	test_point.z = raw->position.z + ((raw->velocity * 1.0 + 10.0) * raw->zv.z);

	terrain_elevation = get_3d_terrain_fast_elevation (test_point.x, test_point.z);

	//
	// check waypoint SHOULD be adjusted
	//
	
	if (min_height == -1.0)
	{
		return terrain_elevation;
	}

	//
	// get vector to waypoint
	//
	
	wp_vec.x = wp_pos->x - raw->position.x;
	wp_vec.y = 0.0;
	wp_vec.z = wp_pos->z - raw->position.z;

	range = sqrt ((wp_vec.x * wp_vec.x) + (wp_vec.z * wp_vec.z));

//	if (range < (raw->velocity + 10.0))
	if (range <= 1.0)
	{

		wp_pos->y = terrain_elevation + min_height;

		return terrain_elevation;
	}

	//
	// adjust waypoint height
	//

	test_point.y = terrain_elevation + min_height;

	vector.x = test_point.x - raw->position.x;
	vector.y = test_point.y - raw->position.y;
	vector.z = test_point.z - raw->position.z;

	if (normalise_any_3d_vector (&vector) != 0.0)
	{
		float
			d,
			h;

		h = vector.y;

		d = sqrt ((vector.x * vector.x) + (vector.z * vector.z));

		//
		// check condition for too little lateral velocity (caused jets to suspend themselves pointing down into the ground)
		//

		if (d > fabs (h))
		{	

			wp_pos->y = raw->position.y + (range * h / d);
		}
		else
		{

			if (get_local_entity_type (en) == ENTITY_TYPE_HELICOPTER)
			{

				wp_pos->y += (vector.y * range);
			}
			else
			{

				wp_pos->y = terrain_elevation + min_height;
			}
		}
	}

	return terrain_elevation;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_mobile_entity_debug_info (entity *en)
{
	vec3d
		*pos,
		velocity_vector,
		*target_pos,
		line_pos;

	entity
		*guide,
		*target;

	mobile
		*raw;

	ASSERT (en);

	raw = (mobile *) get_local_entity_data (en);
	
	pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

	//
	// draw guide vector
	//

	guide = get_local_entity_parent (en, LIST_TYPE_FOLLOWER);

	if (guide)
	{
		draw_debug_guide_entity (guide);
	}

	//
	// draw xv vector
	//

	line_pos.x = pos->x + (raw->xv.x * 20.0);
	line_pos.y = pos->y + (raw->xv.y * 20.0);
	line_pos.z = pos->z + (raw->xv.z * 20.0);

	create_debug_3d_line (pos, &line_pos, sys_col_yellow, 0.0);

	//
	// draw zv vector
	//

	line_pos.x = pos->x + (raw->zv.x * 20.0);
	line_pos.y = pos->y + (raw->zv.y * 20.0);
	line_pos.z = pos->z + (raw->zv.z * 20.0);

	create_debug_3d_line (pos, &line_pos, sys_col_green, 0.0);

	//
	// draw velocity vector
	//

	velocity_vector.x = pos->x + (raw->motion_vector.x * raw->velocity);
	velocity_vector.y = pos->y + (raw->motion_vector.y * raw->velocity);
	velocity_vector.z = pos->z + (raw->motion_vector.z * raw->velocity);

	create_debug_3d_line (pos, &velocity_vector, sys_col_sky_blue, 0.0);

	//
	// draw target vector
	//

	target = get_local_entity_parent (en, LIST_TYPE_TARGET);

	if (target)
	{
		target_pos = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

		if (target_pos)
		{
			create_debug_3d_line (pos, target_pos, sys_col_dark_red, 0.0);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_mobile_sprite_light_timers (void)
{
	update_fixed_wing_sprite_light_timers ();

	update_helicopter_sprite_light_timers ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int calculate_task_points_for_kill (entity *victim, entity *aggressor)
{
	int
		side,
		points;

	float
		p;

	entity
		*target,
		*group,
		*aggressor_group;

	points = get_local_entity_int_value (victim, INT_TYPE_POINTS_VALUE);

	if (points == 0)
	{
		return 0;
	}

	//
	// No points awarded for same-side kills....
	//

	side = get_local_entity_int_value (aggressor, INT_TYPE_SIDE);

	if (get_local_entity_int_value (victim, INT_TYPE_SIDE) == side)
	{
		return 0;
	}

	aggressor_group = get_local_entity_parent (aggressor, LIST_TYPE_MEMBER);

	//
	// Extra points for helping out allies....
	//

	target = get_local_entity_parent (victim, LIST_TYPE_TARGET);

	if (target)
	{
		p = (float)points;

		if ((get_local_entity_int_value (target, INT_TYPE_IDENTIFY_AIRCRAFT)) ||
				(get_local_entity_int_value (target, INT_TYPE_IDENTIFY_VEHICLE)))
		{
			group = get_local_entity_parent (target, LIST_TYPE_MEMBER);

			if (group)
			{
				if (group == aggressor_group)
				{
					//
					// 10% bonus for threat to your group....
					//
					
					p += (p * 0.10);
				}
				else if (get_local_entity_int_value (group, INT_TYPE_SIDE) == side)
				{
					//
					// 50% bonus for threat to another friendly group....
					//
					
					p += (p * 0.50);
				}
			}
		}

		//
		// Round Up
		//
		
		convert_float_to_int (ceil (p), &points);
	}

	return points;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void credit_client_server_mobile_kill (entity *victim, entity *aggressor)
{
	entity
		*force,
		*task,
		*group;

	int
		side,
		kills,
		points,
		total;

	ASSERT (victim);

	ASSERT (aggressor);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	// Victim should still be "alive" at this point
	ASSERT (get_local_entity_int_value (victim, INT_TYPE_ALIVE));

	//
	// Group kills
	//

	group = get_local_entity_parent (aggressor, LIST_TYPE_MEMBER);

	if (group)
	{
		kills = get_local_entity_int_value (group, INT_TYPE_KILLS);

		kills ++;

		set_client_server_entity_int_value (group, INT_TYPE_KILLS, kills);
	}

	//
	// Task kills
	//

	task = get_local_entity_primary_task (aggressor);

	if (task)
	{
		kills = get_local_entity_int_value (task, INT_TYPE_KILLS);

		kills ++;

		set_client_server_entity_int_value (task, INT_TYPE_KILLS, kills);

		points = calculate_task_points_for_kill (victim, aggressor);

		if (points > 0)
		{
			total = get_local_entity_int_value (task, INT_TYPE_TASK_SCORE);

			total += points;

			set_client_server_entity_int_value (task, INT_TYPE_TASK_SCORE, total);
		}

		add_kill_to_task (task, victim, aggressor);
	
		transmit_entity_comms_message (ENTITY_COMMS_TASK_KILL, task, victim, aggressor);
	}

	//
	// Task losses
	//

	task = get_local_entity_primary_task (victim);

	if (task)
	{
		add_loss_to_task (task, victim, aggressor);
	
		transmit_entity_comms_message (ENTITY_COMMS_TASK_LOSS, task, victim, aggressor);
	}

	//
	// Player kills
	//

	if (get_game_type () != GAME_TYPE_FREE_FLIGHT)
	{
		if (get_local_entity_int_value (aggressor, INT_TYPE_PLAYER) == ENTITY_PLAYER_LOCAL)
		{
			inc_player_log_kills (get_global_gunship_side (), get_current_player_log (), victim);
		}
		else if (get_local_entity_int_value (aggressor, INT_TYPE_PLAYER) == ENTITY_PLAYER_REMOTE)
		{
			transmit_entity_comms_message (ENTITY_COMMS_PLAYER_KILL, aggressor, victim);
		}
	}
	
	//
	// Send Text Message
	//

	send_text_message (aggressor, victim, MESSAGE_TEXT_SYSTEM_ENTITY_KILLED, NULL);

	//
	// Add to force statistics
	//

	side = get_local_entity_int_value (aggressor, INT_TYPE_SIDE);
	
	force = get_local_force_entity ((entity_sides) side);

	add_mobile_to_force_kills_stats (force, victim);

	transmit_entity_comms_message (ENTITY_COMMS_MOBILE_KILL, force, victim);

	#if DEBUG_KILL_INFO

	display_debug_kill_info (victim, aggressor);

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MIN_DEATH_TIMER_RANGE	1000 * 1000
#define MAX_DEATH_TIMER_RANGE	10000 * 10000

#define MIN_DEATH_TIMER_VALUE	5.0 * ONE_MINUTE
#define MAX_DEATH_TIMER_VALUE	3.0 * ONE_HOUR

#define DEATH_TIMER_SPECIAL_GAME_MULTIPLIER	0.1

float calculate_mobile_death_timer_value (entity *en)
{
	vec3d
		*pos,
		*keysite_pos;

	float
		result,
		range,
		closest;

	entity
		*force,
		*keysite;

	//
	// calculate timer based on proximity to nearest keysite
	//

	pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

	closest = FLT_MAX;

	ASSERT (get_session_entity ());

	force = get_local_entity_first_child (get_session_entity (), LIST_TYPE_FORCE);

	while (force)
	{
		keysite = get_local_entity_first_child (force, LIST_TYPE_KEYSITE_FORCE);

		while (keysite)
		{
			keysite_pos = get_local_entity_vec3d_ptr (keysite, VEC3D_TYPE_POSITION);

			range = get_sqr_2d_range (pos, keysite_pos);

			if (range < closest)
			{
				closest = range;
			}

			keysite = get_local_entity_child_succ (keysite, LIST_TYPE_KEYSITE_FORCE);
		}

		force = get_local_entity_child_succ (force, LIST_TYPE_FORCE);
	}

	range = closest;

	if (range <= MIN_DEATH_TIMER_RANGE)
	{
		result = MIN_DEATH_TIMER_VALUE;
	}
	else if (range >= MAX_DEATH_TIMER_RANGE)
	{
		result = MAX_DEATH_TIMER_VALUE;
	}
	else
	{
		float
			temp;

		temp = ((range - MIN_DEATH_TIMER_RANGE) / (MAX_DEATH_TIMER_RANGE / MIN_DEATH_TIMER_RANGE));

		result = MIN_DEATH_TIMER_VALUE + ((MAX_DEATH_TIMER_VALUE - MIN_DEATH_TIMER_VALUE) * temp);
	}

	return result;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int insert_mobile_into_takeoff_route (entity *member, entity *landing_entity)
{
	entity
		*task,
		*guide,
		*group,
		*route_wp;

	unsigned int
		member_number;

	ASSERT (member);

	ASSERT (landing_entity);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	group = get_local_entity_parent (member, LIST_TYPE_MEMBER);

	ASSERT (group);

	task = get_local_landing_entity_task (landing_entity, ENTITY_SUB_TYPE_TASK_TAKEOFF);

	ASSERT (task);

	//
	// Link into new route
	//

	route_wp = get_local_landing_entity_route (landing_entity, ENTITY_SUB_TYPE_TASK_TAKEOFF);

	ASSERT (route_wp);

	member_number = get_local_entity_int_value (member, INT_TYPE_GROUP_MEMBER_NUMBER);

	guide = create_client_server_guide_entity (task, route_wp, (1 << member_number));

	attach_group_to_guide_entity (group, guide);

	attach_group_member_to_guide_entity (member, guide);

	play_landing_clear_for_takeoff_speech (member);

	//
	// Unlock landed site, do after locking takeoff route in case entity can't takeoff.
	//

	notify_local_entity (ENTITY_MESSAGE_UNLOCK_LANDING_SITE, landing_entity, member);

	//
	// set operational state
	//

	switch (get_local_entity_type (member))
	{
		case ENTITY_TYPE_FIXED_WING:
		case ENTITY_TYPE_PERSON:
		{
			set_client_server_entity_int_value (member, INT_TYPE_OPERATIONAL_STATE, OPERATIONAL_STATE_TAXIING);

			break;
		}
		case ENTITY_TYPE_ROUTED_VEHICLE:
		case ENTITY_TYPE_SHIP_VEHICLE:
		{
			set_client_server_entity_int_value (member, INT_TYPE_OPERATIONAL_STATE, OPERATIONAL_STATE_TAKEOFF);

			break;
		}
		case ENTITY_TYPE_HELICOPTER:
		{
			//
			// Operational state remains landed until rotors spun up, and all human players in the group have taken off
			//
			
			set_client_server_entity_int_value (member, INT_TYPE_OPERATIONAL_STATE, OPERATIONAL_STATE_LANDED);

			if (get_local_entity_int_value (member, INT_TYPE_PLAYER) == ENTITY_PLAYER_AI)
			{
				set_client_server_entity_float_value (member, FLOAT_TYPE_MAIN_ROTOR_SPIN_UP_TIMER, MAIN_ROTOR_SPIN_UP_TIMER);
			}

			break;
		}

		default:
		{

			debug_fatal ("MOBILE: can't set operational state for %s (%d)",
							get_local_entity_string (member, STRING_TYPE_FULL_NAME),
							get_local_entity_index (member));

			break;
		}
	}

	//
	// Remove from MOVEMENT_DEPENDENT list (if on mobile_keysite)
	//

	if (get_local_entity_type (member) != ENTITY_TYPE_FIXED_WING)
	{

		delete_local_entity_from_parents_child_list (member, LIST_TYPE_MOVEMENT_DEPENDENT);
	}

	/////////////////////////////////////////////////////////////////
	//
	// SPECIAL_EFFECT_HOOK FOR STARTING TO TAKEOFF
	//
	/////////////////////////////////////////////////////////////////

	close_client_server_entity_loading_doors (member);

	close_client_server_entity_cargo_doors (member);

	/////////////////////////////////////////////////////////////////
	//
	//
	/////////////////////////////////////////////////////////////////

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int mobile_check_all_members_taken_off (entity *en)
{
	entity
		*group,
		*force,
		*member,
		*mb_guide,
		*mb_task,
		*new_guide,
		*task,
		*current_guide,
		*landing_en;

	entity_sides
		side;

	unsigned int
		member_number,
		takeoff_flag;

	//
	// Called when "Taken Off" and "Loop" waypoints are reached
	//
	// Check to see if all other members have taken off - if so insert the whole group onto the primary task
	// Otherwise insert the member onto the holding pattern
	//

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	landing_en = get_local_group_member_landing_entity_from_task (en);

	group = get_local_entity_parent (en, LIST_TYPE_MEMBER);

	takeoff_flag = TRUE;

	member = get_local_entity_first_child (group, LIST_TYPE_MEMBER);

	while (member)
	{
		if (member != en)
		{
			mb_guide = get_local_entity_parent (member, LIST_TYPE_FOLLOWER);
	
			if (mb_guide)
			{
				mb_task = get_local_entity_parent (mb_guide, LIST_TYPE_GUIDE);
	
				if (mb_task)
				{
					switch (get_local_entity_int_value (mb_task, INT_TYPE_ENTITY_SUB_TYPE))
					{
						case ENTITY_SUB_TYPE_TASK_TAKEOFF_HOLDING:
						{
							break;
						}

						default:
						{
							if (get_local_entity_int_value (member, INT_TYPE_PLAYER) == ENTITY_PLAYER_AI)
							{
								takeoff_flag = FALSE;
							}
							else if (get_local_entity_int_value (member, INT_TYPE_OPERATIONAL_STATE) == OPERATIONAL_STATE_LANDED)
							{
								takeoff_flag = FALSE;
							}
			
							break;
						}
					}
				}
			}
		}

		member = get_local_entity_child_succ (member, LIST_TYPE_MEMBER);
	}

	//
	//
	//

	if (takeoff_flag)
	{
		//
		// move all members from takeoff route to group wp route
		//

		//
		// find primary task
		//

		new_guide = get_local_group_primary_guide (group);

		ASSERT (new_guide);

		//
		// Allow group to engage
		//

		#ifdef DEBUG

		if (get_local_entity_int_value (group, INT_TYPE_AIRCRAFT_GROUP))
		{
			ASSERT (get_local_entity_int_value (group, INT_TYPE_ENGAGE_ENEMY) == FALSE);		// should be FALSE at this point
		}

		#endif
		
		set_local_entity_int_value (group, INT_TYPE_ENGAGE_ENEMY, get_local_entity_int_value (group, INT_TYPE_DEFAULT_ENGAGE_ENEMY));

		//
		// Remove independent groups from keysite
		//

		ASSERT (get_local_entity_int_value (group, INT_TYPE_GROUP_LIST_TYPE) == LIST_TYPE_KEYSITE_GROUP);

		if (get_local_entity_int_value (group, INT_TYPE_DEFAULT_GROUP_LIST_TYPE) == LIST_TYPE_INDEPENDENT_GROUP)
		{
			side = (entity_sides) get_local_entity_int_value (group, INT_TYPE_SIDE);

			force = get_local_force_entity (side);

			ASSERT (force);

			set_client_server_entity_int_value (group, INT_TYPE_GROUP_LIST_TYPE, LIST_TYPE_INDEPENDENT_GROUP);

			set_client_server_entity_parent (group, LIST_TYPE_KEYSITE_GROUP, NULL);

			set_client_server_entity_parent (group, LIST_TYPE_INDEPENDENT_GROUP, force);
		}

		member = get_local_entity_first_child (group, LIST_TYPE_MEMBER);

		while (member)
		{
			//
			// remove from takeoff task (assumes mobile is the only guide follower) 
			//

			current_guide = get_local_entity_parent (member, LIST_TYPE_FOLLOWER);

			ASSERT (current_guide);

			if (current_guide == new_guide)
			{
				member = get_local_entity_child_succ (member, LIST_TYPE_MEMBER);
				continue;
			}

			ASSERT (current_guide != new_guide);

			destroy_client_server_entity (current_guide);

			#if DEBUG_MODULE

			debug_log ("MOBILE: moving member %s (%d) onto task waypoint list", get_local_entity_string (member, STRING_TYPE_FULL_NAME), get_local_entity_index (member));

			#endif

			attach_group_member_to_guide_entity (member, new_guide);

			set_client_server_entity_int_value (member, INT_TYPE_OPERATIONAL_STATE, OPERATIONAL_STATE_NAVIGATING);

			/////////////////////////////////////////////////////////////////
			//
			// SPECIAL_EFFECT_HOOK FOR COMPLETED TAKEOFF AND ENTERING NAVIGATING MODE
			//
			/////////////////////////////////////////////////////////////////

			/////////////////////////////////////////////////////////////////
			//
			//
			/////////////////////////////////////////////////////////////////

			member = get_local_entity_child_succ (member, LIST_TYPE_MEMBER);
		}
	}
	else
	{
		//
		// place member into holding route
		//

		#if DEBUG_MODULE

		debug_log ("MOBILE: placing member %s (%d) into holding route", get_local_entity_string (en, STRING_TYPE_FULL_NAME), get_local_entity_index (en));

		#endif

		//
		// remove from takeoff task (assumes mobile is the only guide follower) 
		//

		current_guide = get_local_entity_parent (en, LIST_TYPE_FOLLOWER);

		ASSERT (current_guide);

		destroy_client_server_entity (current_guide);

		//
		// find holding task
		//

		task = get_local_landing_entity_task (landing_en, ENTITY_SUB_TYPE_TASK_TAKEOFF_HOLDING);

		ASSERT (task);

		member_number = get_local_entity_int_value (en, INT_TYPE_GROUP_MEMBER_NUMBER);

		new_guide = create_client_server_guide_entity (task, NULL, (1 << member_number));

		attach_group_to_guide_entity (group, new_guide);

		attach_group_member_to_guide_entity (en, new_guide);
	}

	return takeoff_flag;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void play_mobile_under_attack_speech (entity *en, entity *aggressor)
{
	vec3d
		*pos;

	int
		member_number,
		speech_index;

	entity
		*group;

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	if (get_local_entity_int_value (en, INT_TYPE_IDENTIFY_AIRCRAFT))
	{
		if (get_local_entity_int_value (en, INT_TYPE_PLAYER) == ENTITY_PLAYER_AI)
		{
			pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION); 

			ASSERT (pos);

			get_speech_sector_coordinates (pos);

			if (get_local_entity_int_value (aggressor, INT_TYPE_IDENTIFY_AIRCRAFT))
			{
				speech_index = SPEECH_WINGMAN_UNDER_ATTACK_AIRCRAFT;
			}
			else
			{
				speech_index = SPEECH_WINGMAN_UNDER_ATTACK_ARMOUR;
			}

			group = get_local_entity_parent (en, LIST_TYPE_MEMBER);

			member_number = get_local_entity_int_value (en, INT_TYPE_GROUP_MEMBER_NUMBER);

			play_client_server_speech
			(
				get_session_entity (),
				en,
				(entity_sides) get_local_entity_int_value (en, INT_TYPE_SIDE),
				ENTITY_SUB_TYPE_EFFECT_SOUND_RADIO_MESSAGE,
				SOUND_LOCALITY_RADIO,
				0.0,
				0.7,
				6.0,
				get_wingman_speech_originator (en),
				SPEECH_CATEGORY_UNDER_ATTACK,
				15.0,
				SPEECH_ARRAY_WINGMAN_MESSAGES, SPEECH_WINGMAN_INTRODUCTION,
				SPEECH_ARRAY_CALLSIGNS, get_local_entity_int_value (group, INT_TYPE_GROUP_CALLSIGN),
				SPEECH_ARRAY_NUMBERS, 1,
				SPEECH_ARRAY_NUMBERS, member_number,
				SPEECH_ARRAY_WINGMAN_MESSAGES, speech_index,
				SPEECH_ARRAY_NUMBERS, speech_sector_coordinates [0],
				SPEECH_ARRAY_NUMBERS, speech_sector_coordinates [1],
				SPEECH_ARRAY_NUMBERS, speech_sector_coordinates [2],
				SPEECH_ARRAY_NUMBERS, speech_sector_coordinates [3],
				SPEECH_ARRAY_NUMBERS, speech_sector_coordinates [4],
				SPEECH_ARRAY_NUMBERS, speech_sector_coordinates [5],
				SPEECH_ARRAY_WINGMAN_MESSAGES, SPEECH_WINGMAN_REQUEST_ASSISTANCE,
				-1
			);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



