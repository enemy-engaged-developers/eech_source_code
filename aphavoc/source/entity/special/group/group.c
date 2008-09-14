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

#include "ai/taskgen/taskgen.h"
#include "ai/highlevl/highlevl.h"
#include "ai/ai_misc/ai_misc.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

group_callsign_name_type
	group_callsign_names [] =
	{
		{"Angel", 0, 0, 0},
		{"Apollo", 0, 0, 0},
		{"Archer", 0, 0, 0},
		{"Banshee", 0, 0, 0},
		{"Bloodhound", 0, 0, 0},
		{"Bulldog", 0, 0, 0},
		{"Charger", 0, 0, 0},
		{"Cheetah", 0, 0, 0},
		{"Chieftain", 0, 0, 0},
		{"Cobra", 0, 0, 0},
		{"Comet", 0, 0, 0},
		{"Condor", 0, 0, 0},
		{"Cougar", 0, 0, 0},
		{"Cowboy", 0, 0, 0},
		{"Darkhorse", 0, 0, 0},
		{"Demon", 0, 0, 0},
		{"Dodger", 0, 0, 0},
		{"Dragon", 0, 0, 0},
		{"Eagle", 0, 0, 0},
		{"Eight-Ball", 0, 0, 0},
		{"Farsight", 0, 0, 0},
		{"Fireball", 0, 0, 0},
		{"Firebird", 0, 0, 0},
		{"Firefox", 0, 0, 0},
		{"Freelancer", 0, 0, 0},
		{"Gator", 0, 0, 0},
		{"Gauntlet", 0, 0, 0},
		{"Ghostrider", 0, 0, 0},
		{"Gladiator", 0, 0, 0},
		{"Goliath", 0, 0, 0},
		{"Goose", 0, 0, 0},
		{"Hawkeye", 0, 0, 0},
		{"Hellcat", 0, 0, 0},
		{"Hunter", 0, 0, 0},
		{"Jaguar", 0, 0, 0},
		{"Jester", 0, 0, 0},
		{"Jupiter", 0, 0, 0},
		{"Juggernaut", 0, 0, 0},
		{"Kestrel", 0, 0, 0},
		{"Lancer", 0, 0, 0},
		{"Lima", 0, 0, 0},
		{"Maniac", 0, 0, 0},
		{"Mantis", 0, 0, 0},
		{"Mauler", 0, 0, 0},
		{"Mercury", 0, 0, 0},
		{"Merlin", 0, 0, 0},
		{"Milkman", 0, 0, 0},
		{"Mustang", 0, 0, 0},
		{"Nightmare", 0, 0, 0},
		{"Panther", 0, 0, 0},
		{"Patriot", 0, 0, 0},
		{"Phantom", 0, 0, 0},
		{"Phoenix", 0, 0, 0},
		{"Preacher", 0, 0, 0},
		{"Python", 0, 0, 0},
		{"Raptor", 0, 0, 0},
		{"Rattlesnake", 0, 0, 0},
		{"Razorback", 0, 0, 0},
		{"Razorworks", 0, 0, 0},
		{"Reaper", 0, 0, 0},
		{"Renegade", 0, 0, 0},
		{"Sabre", 0, 0, 0},
		{"Savage", 0, 0, 0},
		{"Shadow", 0, 0, 0},
		{"Sheriff", 0, 0, 0},
		{"Shogun", 0, 0, 0},
		{"Snowball", 0, 0, 0},
		{"Spartakus", 0, 0, 0},
		{"Spectrum", 0, 0, 0},
		{"Stalker", 0, 0, 0},
		{"Stingray", 0, 0, 0},
		{"Striker", 0, 0, 0},
		{"Sundown", 0, 0, 0},
		{"Swamp-Fox", 0, 0, 0},
		{"Tempest", 0, 0, 0},
		{"Tiger-Shark", 0, 0, 0},
		{"Touchdown", 0, 0, 0},
		{"Vampire", 0, 0, 0},
		{"Vertigo", 0, 0, 0},
		{"Vigilante", 0, 0, 0},
		{"Viking", 0, 0, 0},
		{"Viper", 0, 0, 0},
		{"Voodoo", 0, 0, 0},
		{"Vulcan", 0, 0, 0},
		{"Vulture", 0, 0, 0},
		{"Warlock", 0, 0, 0},
		{"Warlord", 0, 0, 0},
		{"Warrior", 0, 0, 0},
		{"Wildcat", 0, 0, 0},
		{"Wolfpack", 0, 0, 0},
		{"NUM_GROUP_CALLSIGNS", 0 ,0 ,0},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// counts the total number of members in a group

int get_local_group_member_count (entity *group)
{

	entity
		*member;

	int
		count;

	count = 0;

	member = get_local_entity_first_child (group, LIST_TYPE_MEMBER);

	while (member)
	{

		count ++;

		member = get_local_entity_child_succ (member, LIST_TYPE_MEMBER);
	}

	return count;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_local_group_member_max_formation_position (entity *group)
{

	entity
		*member;

	int
		max_formation_position;

	max_formation_position = 0;

	member = get_local_entity_first_child (group, LIST_TYPE_MEMBER);

	while (member)
	{

		if (max_formation_position < get_local_entity_int_value (member, INT_TYPE_FORMATION_POSITION))
		{

			max_formation_position = get_local_entity_int_value (member, INT_TYPE_FORMATION_POSITION);
		}

		member = get_local_entity_child_succ (member, LIST_TYPE_MEMBER);
	}

	return max_formation_position;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int assess_group_task_locality_factor (entity *group_en, entity *task_en, float *return_distance)
{
	entity
		*keysite,
		*member;

	vec3d
		*pos1,
		*pos2;

	float
		eta,
		distance,
		cruise_speed;

	//
	// locality
	// assess if group could get to end position quick enough, using first members cruise speed.
	//

	if (return_distance)
	{
		*return_distance = 0.0;
	}

	member = get_local_entity_first_child (group_en, LIST_TYPE_MEMBER);

	if (!member)
	{
		return FALSE;
	}

	pos1 = get_local_entity_vec3d_ptr (member, VEC3D_TYPE_POSITION);

	// get task start position, either keysite it is assigned to or the tasks start pos (NB. might actually be its end point)

	keysite = get_local_entity_parent (task_en, LIST_TYPE_UNASSIGNED_TASK);

	if ((keysite) && (get_local_entity_type (keysite) == ENTITY_TYPE_KEYSITE))
	{

		pos2 = get_local_entity_vec3d_ptr (keysite, VEC3D_TYPE_POSITION);
	}
	else
	{

		pos2 = get_local_entity_vec3d_ptr (task_en, VEC3D_TYPE_START_POSITION);
	}

	distance = get_approx_2d_range (pos1, pos2);

	cruise_speed = get_local_entity_float_value (member, FLOAT_TYPE_CRUISE_VELOCITY);

	eta = distance / cruise_speed;

	#if DEBUG_MODULE

	debug_log ("GROUP: en %s (%d) task %s (%d), speed = %f, distance = %f. ETA = %f sec, expire time %f sec",
					get_local_entity_string (member, STRING_TYPE_FULL_NAME),
					get_local_entity_index (member),
					get_local_entity_string (task_en, STRING_TYPE_FULL_NAME),
					get_local_entity_index (task_en),
					cruise_speed,
					distance,
					eta,
					get_local_entity_float_value (task_en, FLOAT_TYPE_EXPIRE_TIMER));

	#endif

	if (eta > get_local_entity_float_value (task_en, FLOAT_TYPE_EXPIRE_TIMER))
	{

		#if DEBUG_MODULE

		debug_log ("GROUP: task %s (%d) group %s (%d), rejected, too far away.",
					get_local_entity_string (task_en, STRING_TYPE_FULL_NAME),
					get_local_entity_index (task_en),
					get_local_entity_string (group_en, STRING_TYPE_FULL_NAME),
					get_local_entity_index (group_en));

		#endif

		return FALSE;
	}

	if (return_distance)
	{
		*return_distance = distance;
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *get_group_at_road_node (int node)
{
	entity
		*force,
		*group;

	force = get_local_entity_first_child (get_session_entity (), LIST_TYPE_FORCE);

	while (force)
	{
		group = get_local_entity_first_child (force, LIST_TYPE_GROUND_REGISTRY);

		while (group)
		{
			if ((get_local_entity_int_value (group, INT_TYPE_ROUTE_NODE) == node) &&
				(get_local_entity_int_value (group, INT_TYPE_ALIVE)))
			{
				#if DEBUG_MODULE

				debug_log ("GP_MSGS: found retreat group %d side %s at node %d", group, entity_side_names [get_local_entity_int_value (group, INT_TYPE_SIDE)], node);

				#endif

				return group;
			}

			group = get_local_entity_child_succ (group, LIST_TYPE_GROUND_REGISTRY);
		}

		force = get_local_entity_child_succ (force, LIST_TYPE_FORCE);
	}

	return NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int amalgamate_groups (entity *receiving_group, entity *donating_group)
{

	entity
		*this_member,
		*member;

	int
		group_type,
		group_kills,
		group_losses,
		donating_group_count,
		receiving_group_count;

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	// check both groups are not doing any tasks

	ASSERT (get_local_entity_int_value (receiving_group, INT_TYPE_GROUP_MODE) == GROUP_MODE_IDLE);

	ASSERT (get_local_entity_int_value (donating_group, INT_TYPE_GROUP_MODE) == GROUP_MODE_IDLE);

	// check group type are the same

	group_type = get_local_entity_int_value (receiving_group, INT_TYPE_ENTITY_SUB_TYPE);

	if (group_type != get_local_entity_int_value (donating_group, INT_TYPE_ENTITY_SUB_TYPE))
	{
		return FALSE;
	}

	ASSERT (group_database [group_type].amalgamate);

	ASSERT (get_local_entity_int_value (donating_group, INT_TYPE_SIDE) == get_local_entity_int_value (receiving_group, INT_TYPE_SIDE));

	donating_group_count = get_local_entity_int_value (donating_group, INT_TYPE_MEMBER_COUNT);

	receiving_group_count = get_local_entity_int_value (receiving_group, INT_TYPE_MEMBER_COUNT);

	if ((donating_group_count + receiving_group_count) <= group_database [group_type].maximum_member_count)
	{

		#ifdef DEBUG

		//#if DEBUG_MODULE

		if ((get_local_entity_parent (donating_group, LIST_TYPE_KEYSITE_GROUP)) && (get_local_entity_parent (receiving_group, LIST_TYPE_KEYSITE_GROUP)))
		{

			ASSERT (get_local_entity_type (get_local_entity_parent (donating_group, LIST_TYPE_KEYSITE_GROUP)) == get_local_entity_type (get_local_entity_parent (receiving_group, LIST_TYPE_KEYSITE_GROUP)));
		}

		debug_log ("GROUP: amalgamating group %s %d (count %d) with group %s %d (count %d)",
							entity_sub_type_group_names [group_type], get_local_entity_index (donating_group), donating_group_count,
							entity_sub_type_group_names [group_type], get_local_entity_index (receiving_group), receiving_group_count);

		member = get_local_entity_first_child (donating_group, LIST_TYPE_MEMBER);

		while (member)
		{

			debug_log ("GROUP:	donating group member %s (%d)", get_local_entity_string (member, STRING_TYPE_FULL_NAME), get_local_entity_index (member));

			ASSERT (get_local_entity_int_value (member, INT_TYPE_OPERATIONAL_STATE) == OPERATIONAL_STATE_LANDED);

			member = get_local_entity_child_succ (member, LIST_TYPE_MEMBER);
		}

		member = get_local_entity_first_child (receiving_group, LIST_TYPE_MEMBER);

		while (member)
		{

			debug_log ("GROUP:	receiving group member %s (%d)", get_local_entity_string (member, STRING_TYPE_FULL_NAME), get_local_entity_index (member));

			ASSERT (get_local_entity_int_value (member, INT_TYPE_OPERATIONAL_STATE) == OPERATIONAL_STATE_LANDED);

			member = get_local_entity_child_succ (member, LIST_TYPE_MEMBER);
		}

		//#endif

		#endif

		member = get_local_entity_first_child (donating_group, LIST_TYPE_MEMBER);

		while (member)
		{

			this_member = member;

			member = get_local_entity_child_succ (member, LIST_TYPE_MEMBER);

			set_client_server_entity_parent (this_member, LIST_TYPE_MEMBER, receiving_group);
		}

		group_kills = get_local_entity_int_value (receiving_group, INT_TYPE_KILLS);
		group_losses = get_local_entity_int_value (receiving_group, INT_TYPE_LOSSES);

		group_kills += get_local_entity_int_value (donating_group, INT_TYPE_KILLS);
		group_losses += get_local_entity_int_value (donating_group, INT_TYPE_LOSSES);

		if (get_local_entity_int_value (receiving_group, INT_TYPE_KILLS) != group_kills)
		{

			set_client_server_entity_int_value (receiving_group, INT_TYPE_KILLS, group_kills);
		}

		if (get_local_entity_int_value (receiving_group, INT_TYPE_LOSSES) != group_losses)
		{

			set_client_server_entity_int_value (receiving_group, INT_TYPE_LOSSES, group_losses);
		}

		//
		// renumber the group members
		//

		set_group_member_numbers (receiving_group);

		//
		// place empty donating group on free list
		//

		ASSERT (get_local_entity_int_value (donating_group, INT_TYPE_MEMBER_COUNT) == 0);

		kill_client_server_group_entity (donating_group);

		#ifdef DEBUG
		{

			vec3d
				*pos1,
				*test_pos;

			float
				amalgamate_max_range = 10 * KILOMETRE;

			member = get_local_entity_first_child (receiving_group, LIST_TYPE_MEMBER);

			ASSERT (member);
	
			pos1 = get_local_entity_vec3d_ptr (member, VEC3D_TYPE_POSITION);
	
			member = get_local_entity_child_succ (member, LIST_TYPE_MEMBER);

			while (member)
			{
	
				test_pos = get_local_entity_vec3d_ptr (member, VEC3D_TYPE_POSITION);

				if (get_2d_range (pos1, test_pos) > amalgamate_max_range)
				{

					debug_log ("GROUP: WARNING: Amalgamated group with members (%s (%d) and %s (%d)) %f apart -------------------------",
									get_local_entity_string (get_local_entity_first_child (receiving_group, LIST_TYPE_MEMBER), STRING_TYPE_FULL_NAME),
									get_local_entity_index (get_local_entity_first_child (receiving_group, LIST_TYPE_MEMBER)),
									get_local_entity_string (member, STRING_TYPE_FULL_NAME),
									get_local_entity_index (member),
									get_2d_range (pos1, test_pos));
				}

				member = get_local_entity_child_succ (member, LIST_TYPE_MEMBER);
			}
	
		}
		#endif

		return TRUE;
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_group_verbose_operational_state (entity *en, int state)
{

	group
		*raw;

	if (get_comms_model () == COMMS_MODEL_CLIENT)
	{

		return;
	}

	raw = get_local_entity_data (en);

	if (raw->verbose_operational_state == state)
	{

		return;
	}

	set_client_server_entity_int_value (en, INT_TYPE_VERBOSE_OPERATIONAL_STATE, state);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_group_suitable_for_player (entity *group, entity *pilot)
{
	entity
		*member;

	ASSERT (group);

	if (!group)
	{
		return FALSE;
	}

	member = get_local_entity_first_child (group, LIST_TYPE_MEMBER);

	while (member)
	{
		if (get_local_entity_suitable_for_player (member, pilot))
		{
			return TRUE;
		}

		member = get_local_entity_child_succ (member, LIST_TYPE_MEMBER);
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void assess_group_supplies (entity *en)
{

	entity
		*keysite,
		*force;

	group
		*raw;

	float
		required,
		level;

	raw = get_local_entity_data (en);

	if (get_local_entity_int_value (en, INT_TYPE_RESUPPLY_SOURCE) == RESUPPLY_SOURCE_GROUP)
	{

		//
		// Check if Group needs to request Supplies via Mission...
		//

		if (raw->supplies.ammo_supply_level < 100.0)
		{

			force = get_local_force_entity (get_local_entity_int_value (en, INT_TYPE_SIDE));

			#if DEBUG_MODULE || DEBUG_SUPPLY

			debug_log ("GROUP: SUPPLY_INFO: ground group %s low on ammo, requesting Supply mission", get_local_entity_string (en, STRING_TYPE_FULL_NAME));

			#endif

			notify_local_entity (ENTITY_MESSAGE_FORCE_LOW_ON_SUPPLIES, force, en, ENTITY_SUB_TYPE_CARGO_AMMO);
		}
		else if (raw->supplies.fuel_supply_level < 100.0)
		{

			force = get_local_force_entity (get_local_entity_int_value (en, INT_TYPE_SIDE));

			#if DEBUG_MODULE || DEBUG_SUPPLY

			debug_log ("GROUP: SUPPLY_INFO: ground group %s low on fuel, requesting Supply mission", get_local_entity_string (en, STRING_TYPE_FULL_NAME));

			#endif

			notify_local_entity (ENTITY_MESSAGE_FORCE_LOW_ON_SUPPLIES, force, en, ENTITY_SUB_TYPE_CARGO_FUEL);
		}
	}
	else if (get_local_entity_int_value (en, INT_TYPE_RESUPPLY_SOURCE) == RESUPPLY_SOURCE_KEYSITE)
	{
		//
		// check all group is landed. If so refuel/rearm group via keysite supplies
		//

		if (get_local_entity_int_value (en, INT_TYPE_GROUP_MODE) == GROUP_MODE_IDLE)
		{

			if (raw->supplies.ammo_supply_level < 100.0)
			{

				//
				// re-arm
				//

				keysite = get_local_entity_parent (en, LIST_TYPE_KEYSITE_GROUP);

				if ((!keysite) || (get_local_entity_type (keysite) != ENTITY_TYPE_KEYSITE))
				{
					keysite = get_closest_keysite (NUM_ENTITY_SUB_TYPE_KEYSITES, raw->side, get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION), 1.0 * KILOMETRE, NULL, NULL);
				}

				ASSERT (keysite);

				level = get_local_entity_float_value (keysite, FLOAT_TYPE_AMMO_SUPPLY_LEVEL);

				required = 100.0 - (raw->supplies.ammo_supply_level * AMMO_USAGE_ACCELERATOR);

				required = bound (required, 0.0, level);

				level -= required;

				set_client_server_entity_float_value (keysite, FLOAT_TYPE_AMMO_SUPPLY_LEVEL, level);

				set_client_server_entity_float_value (en, FLOAT_TYPE_AMMO_SUPPLY_LEVEL, raw->supplies.ammo_supply_level + required);

				#if DEBUG_MODULE || DEBUG_SUPPLY

				debug_log ("GROUP: SUPPLY_INFO: Air group %s members landed, rearming group (now ammo = %f, fuel = %f) from keysite %s (%d) (now ammo = %f, fuel = %f)",
							get_local_entity_string (en, STRING_TYPE_FULL_NAME),
							get_local_entity_float_value (en, FLOAT_TYPE_AMMO_SUPPLY_LEVEL),
							get_local_entity_float_value (en, FLOAT_TYPE_FUEL_SUPPLY_LEVEL),
							get_local_entity_string (keysite, STRING_TYPE_FULL_NAME),
							get_local_entity_index (keysite),
							get_local_entity_float_value (keysite, FLOAT_TYPE_AMMO_SUPPLY_LEVEL),
							get_local_entity_float_value (keysite, FLOAT_TYPE_FUEL_SUPPLY_LEVEL));

				#endif
			}

			if (raw->supplies.fuel_supply_level < 100.0)
			{

				//
				// re-fuel
				//

				keysite = get_local_entity_parent (en, LIST_TYPE_KEYSITE_GROUP);

				if ((!keysite) || (get_local_entity_type (keysite) != ENTITY_TYPE_KEYSITE))
				{
					keysite = get_closest_keysite (NUM_ENTITY_SUB_TYPE_KEYSITES, raw->side, get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION), 1.0 * KILOMETRE, NULL, NULL);
				}

				ASSERT (keysite);

				level = get_local_entity_float_value (keysite, FLOAT_TYPE_FUEL_SUPPLY_LEVEL);

				required = 100.0 - (raw->supplies.fuel_supply_level * FUEL_USAGE_ACCELERATOR);

				required = bound (required, 0.0, level);

				level -= required;

				set_client_server_entity_float_value (keysite, FLOAT_TYPE_FUEL_SUPPLY_LEVEL, level);

				set_client_server_entity_float_value (en, FLOAT_TYPE_FUEL_SUPPLY_LEVEL, raw->supplies.fuel_supply_level + required);

				#if DEBUG_MODULE || DEBUG_SUPPLY

				debug_log ("GROUP: SUPPLY_INFO: Air group %s members landed, refuelling group (now ammo = %f, fuel = %f) from keysite %s (%d) (now ammo = %f, fuel = %f)",
							get_local_entity_string (en, STRING_TYPE_FULL_NAME),
							get_local_entity_float_value (en, FLOAT_TYPE_AMMO_SUPPLY_LEVEL),
							get_local_entity_float_value (en, FLOAT_TYPE_FUEL_SUPPLY_LEVEL),
							get_local_entity_string (keysite, STRING_TYPE_FULL_NAME),
							get_local_entity_index (keysite),
							get_local_entity_float_value (keysite, FLOAT_TYPE_AMMO_SUPPLY_LEVEL),
							get_local_entity_float_value (keysite, FLOAT_TYPE_FUEL_SUPPLY_LEVEL));

				#endif
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_group_member_numbers (entity *en)
{
	int
		number;

	entity
		*member;

	ASSERT (en);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	number = 0;

	member = get_local_entity_first_child (en, LIST_TYPE_MEMBER);

	while (member)
	{
		set_client_server_entity_int_value (member, INT_TYPE_GROUP_MEMBER_NUMBER, number);

		member = get_local_entity_child_succ (member, LIST_TYPE_MEMBER);

		number ++;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_group_formation_positions (entity *en)
{
	entity
		*member;

	ASSERT (en);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	member = get_local_entity_first_child (en, LIST_TYPE_MEMBER);

	while (member)
	{
		set_client_server_entity_int_value (member, INT_TYPE_FORMATION_POSITION, get_local_entity_int_value (member, INT_TYPE_GROUP_MEMBER_NUMBER));

		member = get_local_entity_child_succ (member, LIST_TYPE_MEMBER);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void group_return_to_base (entity *en)
{

	entity
		*wp,
		*guide,
		*last_wp,
		*best_wp,
		*obj_wp,
		*current_wp;

	vec3d
		*pos,
		*wp_pos,
		*last_pos,
		normal;

	float
		d,
		range,
		best_range;

	int
		s,
		sub_type;

	debug_log ("GROUP: sending group %s (%d) home... ", get_local_entity_string (en, STRING_TYPE_FULL_NAME), get_local_entity_index (en));

	//
	// Abort all engage tasks
	//

	terminate_all_engage_tasks (en);

	//
	// Find group position
	//

	pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

	//
	// find objective wp, and last wp position
	//

	obj_wp = NULL;

	guide = get_local_group_primary_guide (en);

	ASSERT (guide);

	current_wp = get_local_entity_parent (guide, LIST_TYPE_CURRENT_WAYPOINT);

	ASSERT (current_wp);

	wp = current_wp;

	while (get_local_entity_child_succ (wp, LIST_TYPE_WAYPOINT))
	{
		wp = get_local_entity_child_succ (wp, LIST_TYPE_WAYPOINT);

		sub_type = get_local_entity_int_value (wp, INT_TYPE_ENTITY_SUB_TYPE);

		if (waypoint_database [sub_type].objective_waypoint)
		{
			obj_wp = wp;
		}
	}

	last_wp = wp;

	last_pos = get_local_entity_vec3d_ptr (last_wp, VEC3D_TYPE_POSITION);

	if (current_wp == last_wp)
	{
		return;
	}

	//
	// Check each waypoint after the objective waypoint (if obj_wp is NULL then the group has already passed the objective wp
	//		or there isn't one)
	//

	if (!obj_wp)
	{
		obj_wp = current_wp;
	}

	//
	// Find vector of group to last wp
	//

	normal.x = last_pos->x - pos->x;
	normal.y = 0.0;
	normal.z = last_pos->z - pos->z;

	if (normalise_any_3d_vector (&normal) == 0.0)
	{
		return;
	}

	//
	// Test sign of last position
	//

	d = ((last_pos->x * normal.x) + (last_pos->z * normal.z)) - ((pos->x * normal.x) + (pos->z * normal.z));

	s = sign (d);

	//
	// find closest waypoint heading back towards the last waypoint
	//

	wp = get_local_entity_child_succ (obj_wp, LIST_TYPE_WAYPOINT);

	ASSERT (wp);

	best_wp = last_wp;

	best_range = FLT_MAX;

	while (wp)
	{
		wp_pos = get_local_entity_vec3d_ptr (wp, VEC3D_TYPE_POSITION);

		d = ((wp_pos->x * normal.x) + (wp_pos->z * normal.z)) - ((pos->x * normal.x) + (pos->z * normal.z));

		if (sign (d) == s)
		{
			range = get_2d_range (wp_pos, pos);

			if (range < best_range)
			{
				best_wp = wp;

				best_range = range;
			}
		}

		wp = get_local_entity_child_succ (wp, LIST_TYPE_WAYPOINT);
	}

	//
	// set guide to best waypoint
	//

	set_guide_new_waypoint (guide, best_wp);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void group_terminate_all_tasks (entity *en)
{
	entity
		*task,
		*guide;

	int
		task_type;

	ASSERT (en);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	terminate_all_engage_tasks (en);

	do
	{
		guide = get_local_entity_first_child (en, LIST_TYPE_GUIDE_STACK);

		if (guide)
		{
			task = get_local_entity_parent (guide, LIST_TYPE_GUIDE);

			ASSERT (task);

			task_type = get_local_entity_int_value (task, INT_TYPE_ENTITY_SUB_TYPE);

			if (task_database [task_type].persistent_task)
			{
				destroy_client_server_entity (guide);
			}
			else
			{
				notify_local_entity (ENTITY_MESSAGE_TASK_TERMINATED, task, NULL, TASK_TERMINATED_ABORTED);
			}
		}
	}
	while (guide);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void group_kill_all_members (entity *en)
{
	entity
		*next,
		*member;

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	member = get_local_entity_first_child (en, LIST_TYPE_MEMBER);

	while (member)
	{
		next = get_local_entity_child_succ (member, LIST_TYPE_MEMBER);

		kill_client_server_entity (member);

		member = next;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void group_destroy_all_members (entity *en)
{
	entity
		*next,
		*member;

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	//
	// DESTROY each member
	//

	member = get_local_entity_first_child (en, LIST_TYPE_MEMBER);

	while (member)
	{
		next = get_local_entity_child_succ (member, LIST_TYPE_MEMBER);

		destroy_client_server_entity (member);

		member = next;
	}

	//
	// Must also KILL the group
	//

	kill_client_server_group_entity (en);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void kill_client_server_group_entity (entity *en)
{
	entity
		*guide,
		*task,
		*next;

	ASSERT (en);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	//
	// abort tasks (NOTE: Notifying each guide could indirectly destroy other guides on the stack)
	//

	do
	{
		guide = get_local_entity_first_child (en, LIST_TYPE_GUIDE_STACK);

		if (guide)
		{
			notify_local_entity (ENTITY_MESSAGE_GROUP_KILLED, guide, en);
		}
	}
	while (guide);

	//
	// notify task dependents
	//

	task = get_local_entity_first_child (en, LIST_TYPE_TASK_DEPENDENT);

	while (task)
	{
		next = get_local_entity_child_succ (task, LIST_TYPE_TASK_DEPENDENT);

		if (task->type == ENTITY_TYPE_TASK)
		{
			notify_local_entity (ENTITY_MESSAGE_TASK_COMPLETED, task, en, TASK_TERMINATED_OBJECTIVE_MESSAGE);
		}

		task = next;
	}

	kill_client_server_entity (en);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int create_group_emergency_transfer_task (entity *en)
{
	entity
		*landing,
		*new_keysite,
		*new_task;

	int
		side,
		landing_type,
		sites_required;

	vec3d
		*pos;

	ASSERT (en);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	side = get_local_entity_int_value (en, INT_TYPE_SIDE);

	pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

	group_terminate_all_tasks (en);

	sites_required = get_local_group_member_count (en);

	landing_type = group_database [get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE)].default_landing_type;

	landing = get_closest_free_landing_site (landing_type, get_local_force_entity (side), pos, 0.0, NULL, sites_required);

	if (landing)
	{
		//
		// Found new keysite
		//

		new_keysite = get_local_entity_parent (landing, LIST_TYPE_LANDING_SITE);

		if (landing_type == ENTITY_SUB_TYPE_LANDING_HELICOPTER)
		{
			new_task = create_transfer_task (side, ENTITY_SUB_TYPE_TASK_TRANSFER_HELICOPTER, 10.0, new_keysite, new_keysite);
		}
		else
		{
			new_task = create_transfer_task (side, ENTITY_SUB_TYPE_TASK_TRANSFER_FIXED_WING, 10.0, new_keysite, new_keysite);
		}

		ASSERT (new_task);

		if (!assign_primary_task_to_group (en, new_task))
		{
			//
			// Failed to assign transfer task
			//

			ai_log ("(TRANSFER) Failed to assign Emergency Transfer to %s", get_local_entity_string (en, STRING_TYPE_FULL_NAME));

			group_kill_all_members (en);

			return FALSE;
		}
		else
		{
			ai_log ("(TRANSFER) Successfully assigned Emergency Transfer to %s", get_local_entity_string (en, STRING_TYPE_FULL_NAME));

			return TRUE;
		}
	}
	else
	{
		//
		// Failed to find alternate keysite
		//

		ai_log ("(TRANSFER) Failed to find Emergency Transfer keysite for %s", get_local_entity_string (en, STRING_TYPE_FULL_NAME));

		group_kill_all_members (en);

		return FALSE;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int check_group_task_type (entity *group, entity_sub_types task_type)
{

	entity
		*guide,
		*task;

	guide = get_local_entity_first_child (group, LIST_TYPE_GUIDE_STACK);

	while (guide)
	{

		task = get_local_entity_parent (guide, LIST_TYPE_GUIDE);

		if (get_local_entity_int_value (task, INT_TYPE_ENTITY_SUB_TYPE) == task_type)
		{

			return TRUE;
		}

		guide = get_local_entity_child_succ (guide, LIST_TYPE_GUIDE_STACK);
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int check_group_task_type_valid_members (entity *group, entity_sub_types task_type)
{
	entity
		*guide,
		*task;

	guide = get_local_entity_first_child (group, LIST_TYPE_GUIDE_STACK);

	while (guide)
	{
		if (get_local_entity_int_value (guide, INT_TYPE_VALID_GUIDE_MEMBERS) != TASK_ASSIGN_NO_MEMBERS)
		{
			task = get_local_entity_parent (guide, LIST_TYPE_GUIDE);

			if (get_local_entity_int_value (task, INT_TYPE_ENTITY_SUB_TYPE) == task_type)
			{
				return TRUE;
			}
		}

		guide = get_local_entity_child_succ (guide, LIST_TYPE_GUIDE_STACK);
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int group_task_specific_retaliation_checks (entity *group, entity *aggressor, int assisted)
{
	entity
		*task,
		*objective;

	task_roe_types
		roe;

	entity_sides
		side;

	vec3d
		*group_pos,
		*objective_pos,
		*aggressor_pos;

	int
		sx,
		sz;

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	ASSERT (group);

	ASSERT (aggressor);

	if (get_local_entity_int_value (group, INT_TYPE_AIRCRAFT_GROUP))
	{
		task = get_local_group_primary_task (group);

		if (!task)
		{
			return FALSE;
		}

		if (get_local_entity_int_value (aggressor, INT_TYPE_PLAYER) != ENTITY_PLAYER_AI)
		{
			return TRUE;
		}

		roe = get_local_entity_int_value (task, INT_TYPE_RULES_OF_ENGAGEMENT);

		switch (roe)
		{
			case TASK_ROE_NONE:
			{
				//
				// FALSE if aggressor is within target area (stop RECON missions from destroying objectives)
				//

				if (get_local_entity_int_value (task, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_TASK_RECON)
				{
					objective = get_local_entity_parent (task, LIST_TYPE_TASK_DEPENDENT);

					if (objective)
					{
						objective_pos = get_local_entity_vec3d_ptr (objective, VEC3D_TYPE_POSITION);
	
						ASSERT (objective_pos);
	
						aggressor_pos = get_local_entity_vec3d_ptr (aggressor, VEC3D_TYPE_POSITION);
	
						ASSERT (aggressor_pos);
	
						if (get_sqr_2d_range (aggressor_pos, objective_pos) < ((2.0 * KILOMETRE) * (2.0 * KILOMETRE)))
						{
							ai_log ("(RETALIATE CHECK) ROE NONE - Failed (Aggressor at target area)");
	
							return FALSE;
						}
					}
				}

				//
				// Retaliate if no-one else coming to assist, AND (mission complete OR aggressor in friendly territory)
				//

				if (!assisted)
				{
					if (get_local_entity_int_value (task, INT_TYPE_TASK_COMPLETED) != TASK_INCOMPLETE)
					{
						ai_log ("(RETALIATE CHECK) ROE NONE - Task Complete");

						return TRUE;
					}

					side = get_local_entity_int_value (group, INT_TYPE_SIDE);

					group_pos = get_local_entity_vec3d_ptr (group, VEC3D_TYPE_POSITION);

					ASSERT (group_pos);

					get_x_sector (sx, group_pos->x);
					get_z_sector (sz, group_pos->z);

					if (get_local_sector_side_ratio (sx, sz, side) > 0.5)
					{
						ai_log ("(RETALIATE CHECK) ROE NONE - Friendly Territory");

						return TRUE;
					}
				}

				ai_log ("(RETALIATE CHECK) ROE NONE - Failed Checks");

				break;
			}
			case TASK_ROE_OBJECTIVE:
			{
				//
				// Retaliate if no-one else coming to assist, OR primary task completed
				//

				if (!assisted)
				{
					ai_log ("(RETALIATE CHECK) ROE OBJECTIVE - No Assistance");

					return TRUE;
				}

				if (get_local_entity_int_value (task, INT_TYPE_TASK_COMPLETED) != TASK_INCOMPLETE)
				{
					ai_log ("(RETALIATE CHECK) ROE OBJECTIVE - Task Complete");

					return TRUE;
				}

				ai_log ("(RETALIATE CHECK) ROE OBJECTIVE - Failed Checks");

				break;
			}
			case TASK_ROE_ALL:
			{
				//
				// Always retaliate
				//

				ai_log ("(RETALIATE CHECK) ROE ALL");

				return TRUE;
			}
		}

		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_group_callsign_database (void)
{

	int
		loop;

	for (loop = 0; loop < NUM_GROUP_CALLSIGNS; loop ++)
	{

		memset (group_callsign_names [loop].side, 0, sizeof (char) * NUM_ENTITY_SIDES);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int assign_group_callsign (entity *en)
{

	int
		start_position,
		side,
		index;

	index = 0;

	if (get_comms_model () != COMMS_MODEL_SERVER)
	{

		return index;
	}

	if (get_local_entity_int_value (en, INT_TYPE_AIRCRAFT_GROUP))
	{

		index = get_local_entity_index (en) % NUM_GROUP_CALLSIGNS;

		start_position = index;

		side = get_local_entity_int_value (en, INT_TYPE_SIDE);

		while (group_callsign_names [index].side [side])
		{

			index = ( index + 1 ) % NUM_GROUP_CALLSIGNS;

			if (index == start_position)
			{

				debug_log ("GROUP: WARNING: reusing group callsign %s for group %s", group_callsign_names [index].callsign, get_local_entity_string (en, STRING_TYPE_FULL_NAME));

				break;
			}
		}

		group_callsign_names [index].side [side] ++;
	}

	return index;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void free_group_callsign (entity *en)
{

	int
		side,
		index;

	if (get_comms_model () != COMMS_MODEL_SERVER)
	{

		return;
	}

	if (get_local_entity_int_value (en, INT_TYPE_AIRCRAFT_GROUP))
	{

		side = get_local_entity_int_value (en, INT_TYPE_SIDE);

		index = get_local_entity_int_value (en, INT_TYPE_GROUP_CALLSIGN);

		ASSERT (group_callsign_names [index].side [side] > 0);

		group_callsign_names [index].side [side] --;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

