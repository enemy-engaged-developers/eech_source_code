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

#include "ai/highlevl/highlevl.h"
#include "ai/faction/popread.h"
#include "ai/taskgen/assign.h"
#include "ai/taskgen/taskgen.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE 							0

#define KEYSITE_FARP_RADIUS 					6
//VJ#
#define KEYSITE_LANDING_SITE_TOLERANCE 	0.05 //0.01 // ONE CENTIMETRE

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *get_closest_keysite (entity_sub_types type, entity_sides side, vec3d *pos, float min_range, float *actual_range, int outside_of_range, entity *exclude_keysite)
{

	float
		best_range,
		range;

	vec3d
		*keysite_pos;

	entity
		*force,
		*closest_keysite = NULL,
		*current_keysite;

	ASSERT(min_range > 0.0 || outside_of_range);
	
	best_range = FLT_MAX;

	force = get_local_force_entity (side);

	current_keysite = get_local_entity_first_child (force, LIST_TYPE_KEYSITE_FORCE);

	while (current_keysite)
	{

		if (current_keysite != exclude_keysite)
		{

			if ((get_local_entity_int_value (current_keysite, INT_TYPE_ENTITY_SUB_TYPE) == type) || (type == NUM_ENTITY_SUB_TYPE_KEYSITES))
			{
	
				if (get_local_entity_int_value (current_keysite, INT_TYPE_IN_USE))
				{
		
					keysite_pos = get_local_entity_vec3d_ptr (current_keysite, VEC3D_TYPE_POSITION);
		
					range = get_approx_2d_range (keysite_pos, pos);
		
					if (range <= min_range)
					{
		
						#if LANDING_DEBUG >= 2
		
						debug_log ("AI_MISC: EARLY OUT: found key site %d (type %d) range %f", current_keysite, type, range);
		
						#endif
	
						if (actual_range)
						{
		
							*actual_range = range;
						}
		
						return current_keysite;
					}
		
					if (range < best_range && outside_of_range)
					{
		
						best_range = range;
		
						closest_keysite = current_keysite;
		
						#if LANDING_DEBUG
		
						debug_log ("AI_MISC: found key site %d (type %d) range %f", current_keysite, type, range);
		
						#endif
					}
				}
			}
		}

		current_keysite = get_local_entity_child_succ (current_keysite, LIST_TYPE_KEYSITE_FORCE);
	} 

	if ( closest_keysite )
	{

		keysite_pos = get_local_entity_vec3d_ptr (closest_keysite, VEC3D_TYPE_POSITION);

		best_range = get_2d_range (keysite_pos, pos);
	}

	if (actual_range)
	{

		*actual_range = best_range;
	}

	return closest_keysite;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vec3d *get_keysite_supply_position (entity *keysite)
{

	return get_local_entity_vec3d_ptr (keysite, VEC3D_TYPE_POSITION);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_keysite_troop_pickup_position (entity *keysite, vec3d *pos)
{

	get_local_entity_vec3d (keysite, VEC3D_TYPE_POSITION, pos);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_keysite_troop_dropoff_position (entity *keysite, vec3d *pos, float *heading)
{

	vec3d
		keysite_pos;

	get_local_entity_vec3d (keysite, VEC3D_TYPE_POSITION, pos);

	if (get_object_3d_troop_landing_position_and_heading (get_local_entity_int_value (keysite, INT_TYPE_OBJECT_INDEX), &keysite_pos, heading))
	{

		pos->x += keysite_pos.x;
		pos->y += keysite_pos.y;
		pos->z += keysite_pos.z;
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_keysite_troop_in_building_position (entity *keysite, vec3d *pos)
{

	get_local_entity_vec3d (keysite, VEC3D_TYPE_POSITION, pos);

	pos->x += 100.0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_keysite_troop_outside_building_position (entity *keysite, vec3d *pos, int count)
{

	get_local_entity_vec3d (keysite, VEC3D_TYPE_POSITION, pos);

	pos->x += (count * 50.0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_keysite_takenoff_position (entity *keysite, vec3d *pos, entity_sub_types landing_type)
{

	entity
		*landing_en,
		*wp;

	landing_en = get_local_entity_landing_entity (keysite, landing_type);

	wp = get_local_landing_entity_route (landing_en, ENTITY_SUB_TYPE_TASK_TAKEOFF);

	while (wp)
	{

		if (get_local_entity_int_value (wp, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_WAYPOINT_TAKEN_OFF)
		{

			break;
		}

		wp = get_local_entity_child_succ (wp, LIST_TYPE_WAYPOINT);
	}

	if (wp)
	{

		get_local_entity_vec3d (wp, VEC3D_TYPE_POSITION, pos);

		return TRUE;
	}

	get_local_entity_vec3d (keysite, VEC3D_TYPE_POSITION, pos);

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_keysite_start_landing_position (entity *keysite, vec3d *pos, entity_sub_types landing_type)
{

	entity
		*landing_en,
		*wp;

	landing_en = get_local_entity_landing_entity (keysite, landing_type);

	wp = get_local_landing_entity_route (landing_en, ENTITY_SUB_TYPE_TASK_LANDING);

	get_local_entity_vec3d (wp, VEC3D_TYPE_POSITION, pos);

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_keysite_landing_sites_available (entity *en, int landing_type)
{
	entity
		*landing;
		
	landing = get_local_entity_first_child (en, LIST_TYPE_LANDING_SITE);
		
	while (landing)
	{
		if (get_local_entity_int_value (landing, INT_TYPE_ENTITY_SUB_TYPE) == landing_type)
		{
			return get_local_entity_int_value (landing, INT_TYPE_FREE_LANDING_SITES) - get_local_entity_int_value (landing, INT_TYPE_RESERVED_LANDING_SITES);
		}

		landing = get_local_entity_child_succ (landing, LIST_TYPE_LANDING_SITE);
	}

	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_keysite_cargo (entity *en, float cargo_level, entity_sub_types sub_type, float cargo_size)
{

	float
		temp_cargo_level;

	entity
		*force,
		*cargo,
		*destroy_cargo;

	struct OBJECT_3D_BOUNDS
		*bounding_box;

	vec3d
		position;

	keysite
		*raw;

	//
	// Get cargo position
	//

	if (get_game_status () == GAME_STATUS_INITIALISING)
	{

		return;
	}

	raw = (keysite *) get_local_entity_data (en);

	if ((!raw->alive) || (!raw->in_use))
	{

		return;
	}

	memcpy (&position, get_keysite_supply_position (en), sizeof (vec3d));

	bounding_box = get_object_3d_bounding_box (OBJECT_3D_SINGLE_CRATE);

	//
	// work out start position
	//

	position.y -= bounding_box->ymin;

	position.z += sub_type * ((bounding_box->zmax - bounding_box->zmin) + 1);

	//
	// check for existing cargo
	//

	temp_cargo_level = cargo_level;

	cargo = raw->cargo_root.first_child;

	while (cargo)
	{

		if (get_local_entity_int_value (cargo, INT_TYPE_ENTITY_SUB_TYPE) == sub_type)
		{

			temp_cargo_level -= cargo_size;

			if (temp_cargo_level < 0.0)
			{

				//
				// destroy surplus cargo
				//

				destroy_cargo = cargo;

				cargo = get_local_entity_child_succ (cargo, LIST_TYPE_CARGO);

				destroy_client_server_entity_family (destroy_cargo);

				#if DEBUG_MODULE || DEBUG_SUPPLY

				debug_log ("KEYSITE: SUPPLY_INFO: destroying cargo %s at keysite %s (%d)",
							entity_sub_type_cargo_names [sub_type],
							get_local_entity_string (en, STRING_TYPE_KEYSITE_NAME),
							get_local_entity_index (en));

				#endif

				continue;
			}

			position.x += (bounding_box->xmax - bounding_box->xmin) + 1.0;
		}

		cargo = get_local_entity_child_succ (cargo, LIST_TYPE_CARGO);
	}

	//
	// Create new cargo as required
	//

	if (temp_cargo_level > cargo_size)
	{

		while (temp_cargo_level > cargo_size)
		{
	
			#if DEBUG_MODULE || DEBUG_SUPPLY

			debug_log ("KEYSITE: SUPPLY_INFO: creating cargo %s for keysite %s (%d)",
							entity_sub_type_cargo_names [sub_type],
							get_local_entity_string (en, STRING_TYPE_KEYSITE_NAME),
							get_local_entity_index (en));

			#endif
		
			create_client_server_entity
			(
				ENTITY_TYPE_CARGO,
				ENTITY_INDEX_DONT_CARE,
				ENTITY_ATTR_PARENT (LIST_TYPE_CARGO, en),
				ENTITY_ATTR_INT_VALUE (INT_TYPE_SIDE, get_local_entity_int_value (en, INT_TYPE_SIDE)),
				ENTITY_ATTR_INT_VALUE (INT_TYPE_ENTITY_SUB_TYPE, sub_type),
				ENTITY_ATTR_VEC3D (VEC3D_TYPE_POSITION, position.x, position.y, position.z),
				ENTITY_ATTR_END
			);
	
			position.x += (bounding_box->xmax - bounding_box->xmin) + 1.0;
	
			temp_cargo_level -= cargo_size;
		}
	}
	else if (cargo_level <= KEYSITE_SUPPLY_REQUEST_THRESHOLD)
	{
		//
		// low on cargo supplies so request some more
		//

		switch (sub_type)
		{
			case ENTITY_SUB_TYPE_CARGO_AMMO:
			{	
				if (keysite_database [raw->sub_type].default_supply_usage.ammo_supply_level < 0.0)
				{
					force = get_local_force_entity ((entity_sides) raw->side);
			
					notify_local_entity (ENTITY_MESSAGE_FORCE_LOW_ON_SUPPLIES, force, en, sub_type);
				}

				break;
			}
			case ENTITY_SUB_TYPE_CARGO_FUEL:
			{	
				if (keysite_database [raw->sub_type].default_supply_usage.fuel_supply_level < 0.0)
				{
					force = get_local_force_entity ((entity_sides) raw->side);
			
					notify_local_entity (ENTITY_MESSAGE_FORCE_LOW_ON_SUPPLIES, force, en, sub_type);
				}

				break;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_keysite_farp_enable (entity *force)
{
	vec3d
		*keysite_pos;

	entity_sides
		force_side;

	entity
		*sector,
		*keysite;

	if (get_comms_model () != COMMS_MODEL_SERVER)
	{
		return;
	}

	if (!force)
	{
		return;
	}

	keysite = get_local_entity_first_child (force, LIST_TYPE_KEYSITE_FORCE);

	force_side = (entity_sides) get_local_entity_int_value (force, INT_TYPE_SIDE);

	while (keysite)
	{
		if (get_local_entity_int_value (keysite, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_KEYSITE_FARP)
		{
			keysite_pos = get_local_entity_vec3d_ptr (keysite, VEC3D_TYPE_POSITION);

			sector = get_local_sector_entity (keysite_pos);
		
			if (get_local_entity_int_value (sector, INT_TYPE_SIDE) == force_side)
			{
				set_local_entity_int_value (keysite, INT_TYPE_SIDE, force_side);

				if (!get_local_entity_int_value (keysite, INT_TYPE_IN_USE))
				{
					set_local_entity_int_value (keysite, INT_TYPE_IN_USE, TRUE);

					update_imap_sector_side (keysite, TRUE);

					update_imap_importance_level (keysite, TRUE);

					update_keysite_distance_to_friendly_base (keysite, force_side);
				}

				set_local_entity_int_value (keysite, INT_TYPE_KEYSITE_USABLE_STATE, KEYSITE_STATE_USABLE);

				#if DEBUG_MODULE
	
				debug_log ("KEYSITE: building FARP side %s, at %d, %d", entity_side_names [force_side], loop_x, loop_z);

				#endif
			}
		}

		keysite = get_local_entity_child_succ (keysite, LIST_TYPE_KEYSITE_FORCE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *get_fixed_structure_keysite_entity (entity *structure)
{
	entity
		*group,
		*keysite;

	ASSERT (structure);

	group = get_local_entity_parent (structure, LIST_TYPE_MEMBER);

	if (!group)
	{
		return NULL;
	}

	if (get_local_entity_type (group) == ENTITY_TYPE_REGEN)
	{
		//
		// Parent is a REGEN
		//
		
		keysite = get_local_entity_parent (group, LIST_TYPE_REGEN);
	}
	else
	{
		//
		// Parent is a normal GROUP
		//
		
		keysite = get_local_entity_parent (group, LIST_TYPE_BUILDING_GROUP);
	}

	if (get_local_entity_type (keysite) == ENTITY_TYPE_KEYSITE)
	{
		return keysite;
	}

	return NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_local_keysite_member_count (entity *keysite)
{

	entity
		*group,
		*member;

	int
		count;

	count = 0;

	group = get_local_entity_first_child (keysite, LIST_TYPE_KEYSITE_GROUP);

	while (group)
	{
		member = get_local_entity_first_child (group, LIST_TYPE_MEMBER);

		while (member)
		{
			count ++;

			member = get_local_entity_child_succ (member, LIST_TYPE_MEMBER);
		}

		group = get_local_entity_child_succ (group, LIST_TYPE_KEYSITE_GROUP);
	}

	return count;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int add_local_entity_importance_to_keysite (entity *en, entity *keysite_en)
{
	float
		value;

	keysite
		*raw;

	ASSERT (en);

	ASSERT (keysite_en);

	if (get_local_entity_int_value (en, INT_TYPE_ALIVE))
	{
		if (get_local_entity_int_value (en, INT_TYPE_IDENTIFY_FIXED))
		{
			value = get_local_entity_float_value (en, FLOAT_TYPE_FIXED_OBJECT_IMPORTANCE);
	
			if (value > 0.0)
			{
				raw = (keysite *) get_local_entity_data (keysite_en);
		
				raw->keysite_strength += value;
		
				raw->keysite_maximum_strength += value;
		
				#if DEBUG_MODULE

				debug_log ("KEYSITE: %s added %s, new strength (%.2f / %.2f)", raw->keysite_name, get_local_entity_string (en, STRING_TYPE_LONG_DISPLAY_NAME), raw->keysite_strength, raw->keysite_maximum_strength);

				#endif

				return TRUE;
			}
		}
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int restore_local_entity_importance_to_keysite (entity *en, entity *keysite_en)
{
	float
		value;

	keysite
		*raw;

	ASSERT (en);

	ASSERT (keysite_en);

	if (get_local_entity_int_value (en, INT_TYPE_ALIVE))
	{
		if (get_local_entity_int_value (en, INT_TYPE_IDENTIFY_FIXED))
		{
			value = get_local_entity_float_value (en, FLOAT_TYPE_FIXED_OBJECT_IMPORTANCE);
	
			if (value > 0.0)
			{
				raw = (keysite *) get_local_entity_data (keysite_en);
		
				raw->keysite_strength += value;
		
				#if DEBUG_MODULE

				debug_log ("KEYSITE: %s restored %s, new strength (%.2f / %.2f)", raw->keysite_name, get_local_entity_string (en, STRING_TYPE_LONG_DISPLAY_NAME), raw->keysite_strength, raw->keysite_maximum_strength);

				#endif

				return TRUE;
			}
		}
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void subtract_local_entity_importance_from_keysite (entity *en)
{
	entity
		*task,
		*next,
		*keysite_en;

	keysite
		*raw;

	int
		object_index;

	float
		value;

	ASSERT (en);

	keysite_en = get_fixed_structure_keysite_entity (en);

	if (!keysite_en)
	{
		return;
	}

	ASSERT (get_local_entity_type (keysite_en) == ENTITY_TYPE_KEYSITE);

	if (get_local_entity_int_value (en, INT_TYPE_ALIVE))
	{
		if (get_local_entity_int_value (en, INT_TYPE_IDENTIFY_FIXED))
		{
			value = get_local_entity_float_value (en, FLOAT_TYPE_FIXED_OBJECT_IMPORTANCE);
	
			if (value > 0.0)
			{
				raw = (keysite *) get_local_entity_data (keysite_en);
	
				raw->keysite_strength -= value;

				// only remove strength (and not the maximum)

				if (get_game_status () == GAME_STATUS_INITIALISED)
				{
					object_index = get_local_entity_int_value (en, INT_TYPE_OBJECT_3D_SHAPE);

					ai_log ("(KEYSITE) %s removed %s, new strength (%.2f / %.2f)", raw->keysite_name, object_3d_enumeration_names [object_index], raw->keysite_strength, raw->keysite_maximum_strength);
	
					if (get_comms_model () == COMMS_MODEL_SERVER)
					{
						//
						// If the keysite is the objective of a task - check that task for completeness
						//
	
						task = get_local_entity_first_child (keysite_en, LIST_TYPE_TASK_DEPENDENT);
		
						while (task)
						{
							next = get_local_entity_child_succ (task, LIST_TYPE_TASK_DEPENDENT);

							if (get_local_entity_type (task) == ENTITY_TYPE_TASK)
							{		
								if (!get_local_entity_int_value (task, INT_TYPE_TASK_COMPLETED))
								{
									if (assess_task_completeness (task, TASK_TERMINATED_IN_PROGRESS) == TASK_COMPLETED_SUCCESS)
									{
										notify_local_entity (ENTITY_MESSAGE_TASK_COMPLETED, task, keysite_en, TASK_TERMINATED_OBJECTIVE_MESSAGE);
									}
								}
							}

							task = next;
						}
	
						if (get_local_entity_float_value (keysite_en, FLOAT_TYPE_EFFICIENCY) <= keysite_database [raw->sub_type].minimum_efficiency)
						{
							//
							// Keysite is below minimum strength :-
							//
	
							ai_log ("(KEYSITE) SIDE %s : %s BELOW MINIMUN EFFICIENCY", entity_side_short_names [get_local_entity_int_value (keysite_en, INT_TYPE_SIDE)], get_local_entity_string (keysite_en, STRING_TYPE_KEYSITE_NAME));
	
							if (!keysite_database [raw->sub_type].repairable)
							{
								kill_client_server_entity (keysite_en);

								return;
							}

							if (get_local_entity_int_value (keysite_en, INT_TYPE_KEYSITE_USABLE_STATE) != KEYSITE_STATE_UNUSABLE)
							{
								set_client_server_entity_int_value (keysite_en, INT_TYPE_KEYSITE_USABLE_STATE, KEYSITE_STATE_UNUSABLE);
							}
						}
						else
						{
							//
							// Terminate repairing
							//

							if (raw->keysite_usable_state == KEYSITE_STATE_REPAIRING)
							{
								set_client_server_entity_int_value (keysite_en, INT_TYPE_KEYSITE_USABLE_STATE, KEYSITE_STATE_USABLE);
							}
						}
					}
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_keysite_structure_under_attack (entity *structure, entity *aggressor)
{
	entity
		*force,
		*keysite;

	entity_sides
		side;

	ASSERT (structure);

	ASSERT (aggressor);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	if (!get_local_entity_int_value (aggressor, INT_TYPE_ALIVE))
	{
		return;
	}

	keysite = get_fixed_structure_keysite_entity (structure);

	if (!keysite)
	{
		return;
	}

	side = (entity_sides) get_local_entity_int_value (keysite, INT_TYPE_SIDE);
	
	if (get_local_entity_int_value (aggressor, INT_TYPE_SIDE) == side)
	{
		if (get_local_entity_int_value (aggressor, INT_TYPE_PLAYER) == ENTITY_PLAYER_AI)
		{
			//
			// Ignore AI Friendly Fire (usually accidental)
			//

			return;
		}
		else
		{
			//
			// For the player, we could possibly allow a number of FF incidents before things start firing back
			//
			
			return;
		}
	}

	if (get_local_entity_float_value (keysite, FLOAT_TYPE_ASSIST_TIMER) == 0.0)
	{
		set_local_entity_float_value (keysite, FLOAT_TYPE_ASSIST_TIMER, DEFAULT_KEYSITE_ASSISTANCE_REQUEST_TIMER);

		if (get_local_entity_int_value (aggressor, INT_TYPE_IDENTIFY_AIRCRAFT))
		{
			if (!entity_is_object_of_task (keysite, ENTITY_SUB_TYPE_TASK_COMBAT_AIR_PATROL, side))
			{
				//
				// Create CAP task
				//
	
				create_cap_task (side, keysite, aggressor, TRUE, 10.0, 15.0 * ONE_MINUTE, keysite, keysite);
	
				//
				// force assign
				//
				
				assign_keysite_tasks (keysite, task_database [ENTITY_SUB_TYPE_TASK_COMBAT_AIR_PATROL].task_category);
			}
		}
		else
		{
			//
			// Create Scout task ?
			//
		}
	
		//
		// Request assistance from airborne aircraft 
		//

		force = get_local_entity_parent (keysite, LIST_TYPE_KEYSITE_FORCE);
	
		notify_local_entity (ENTITY_MESSAGE_REQUEST_ASSISTANCE, force, keysite, aggressor);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void destroy_keysite (entity *en, entity_sides side)
{
	entity
		*task,
		*group,
		*member,
		*landing,
		*next,
		*next_group;

	vec3d
		*pos;

	ASSERT (en);

	ASSERT (get_local_entity_type (en) == ENTITY_TYPE_KEYSITE);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

	//
	// Destroy cargo
	//

	destroy_client_server_entity_children (en, LIST_TYPE_CARGO);

	if (command_line_capture_aircraft)
	{
		//
		// "Capture" all aircraft landed at the keysite
		//
	
		group = get_local_entity_first_child (en, LIST_TYPE_KEYSITE_GROUP);
	
		while (group)
		{
			next_group = get_local_entity_child_succ (group, LIST_TYPE_KEYSITE_GROUP);
	
			if (get_local_entity_int_value (group, INT_TYPE_AIRCRAFT_GROUP))
			{
				if (get_local_entity_int_value (group, INT_TYPE_SIDE) == side)
				{
					if (!get_local_group_primary_task (group))
					{
						//
						// check primary task so we don't destroy aircraft taxiing at another keysite before doing a task which will bring them to the captured keysite
						// also has the side effect of allowing any aircraft at the captured keysite to continue taking off.
						//
						
						member = get_local_entity_first_child (group, LIST_TYPE_MEMBER);
				
						while (member)
						{
							next = get_local_entity_child_succ (member, LIST_TYPE_MEMBER);
				
							if (!get_local_entity_int_value (member, INT_TYPE_AIRBORNE_AIRCRAFT))
							{
								kill_client_server_entity (member);
							}
				
							member = next;
						}
					}
				}
			}
			
			group = next_group;
		}
	
		//
		// Redirect incoming aircraft to new keysite
		//
	
		group = get_local_entity_first_child (en, LIST_TYPE_KEYSITE_GROUP);
	
		while (group)
		{
			next_group = get_local_entity_child_succ (group, LIST_TYPE_KEYSITE_GROUP);
	
			if (get_local_entity_int_value (group, INT_TYPE_AIRCRAFT_GROUP))
			{
				if (get_local_entity_int_value (group, INT_TYPE_SIDE) == side)
				{
					if (get_local_group_primary_task (group))
					{
						//
						// group is doing primary task - will sort itself out when it reaches land waypoint 
						//
					}
					else
					{
						//
						// group must be landing - create and assign emergency transfer task
						//
		
						//
						// but first, sort out landing locks
						//
						
						member = get_local_entity_first_child (group, LIST_TYPE_MEMBER);
				
						while (member)
						{
							task = get_local_entity_current_task (member);
		
							if (task)
							{
								switch (get_local_entity_int_value (task, INT_TYPE_ENTITY_SUB_TYPE))
								{
									case ENTITY_SUB_TYPE_TASK_LANDING:
									{
										//
										// Landing task needs to free landing SITE and landing ROUTE
										//
										
										landing = get_local_group_member_landing_entity_from_task (member);
								
										notify_local_entity (ENTITY_MESSAGE_UNLOCK_LANDING_ROUTE, landing, member);
		
										notify_local_entity (ENTITY_MESSAGE_UNLOCK_LANDING_SITE, landing, member);
		
										break;
									}
									case ENTITY_SUB_TYPE_TASK_LANDING_HOLDING:
									{
										//
										// Landing-Holding task needs to free landing SITE only
										//
										
										landing = get_local_group_member_landing_entity_from_task (member);
								
										notify_local_entity (ENTITY_MESSAGE_UNLOCK_LANDING_SITE, landing, member);
		
										break;
									}
								}
							}
		
							member = get_local_entity_child_succ (member, LIST_TYPE_MEMBER);
						}
		
						create_group_emergency_transfer_task (group);
					}
				}
			}
			else
			{
				//
				// Kill all other groups linked to keysite (e.g. people, or recently regen-ed tanks etc.)
				//
	
				group_kill_all_members (group);
			}
			
			group = next_group;
		}
	}
	else
	{
		//
		// Destroy all aircraft landed at the keysite
		//
	
		group = get_local_entity_first_child (en, LIST_TYPE_KEYSITE_GROUP);
	
		while (group)
		{
			next_group = get_local_entity_child_succ (group, LIST_TYPE_KEYSITE_GROUP);
	
			if (get_local_entity_int_value (group, INT_TYPE_AIRCRAFT_GROUP))
			{
				if (!get_local_group_primary_task (group))
				{
					//
					// check primary task so we don't destroy aircraft taxiing at another keysite before doing a task which will bring them to the captured keysite
					// also has the side effect of allowing any aircraft at the captured keysite to continue taking off.
					//
					
					member = get_local_entity_first_child (group, LIST_TYPE_MEMBER);
			
					while (member)
					{
						next = get_local_entity_child_succ (member, LIST_TYPE_MEMBER);
			
						if (!get_local_entity_int_value (member, INT_TYPE_AIRBORNE_AIRCRAFT))
						{
							kill_client_server_entity (member);
						}
			
						member = next;
					}
				}
			}
			
			group = next_group;
		}
	
		//
		// Redirect incoming aircraft to new keysite
		//
	
		group = get_local_entity_first_child (en, LIST_TYPE_KEYSITE_GROUP);
	
		while (group)
		{
			next_group = get_local_entity_child_succ (group, LIST_TYPE_KEYSITE_GROUP);
	
			if (get_local_entity_int_value (group, INT_TYPE_AIRCRAFT_GROUP))
			{
				if (get_local_group_primary_task (group))
				{
					//
					// group is doing primary task - will sort itself out when it reaches land waypoint 
					//
				}
				else
				{
					//
					// group must be landing - create and assign emergency transfer task
					//
	
					//
					// but first, sort out landing locks
					//
					
					member = get_local_entity_first_child (group, LIST_TYPE_MEMBER);
			
					while (member)
					{
						task = get_local_entity_current_task (member);
	
						if (task)
						{
							switch (get_local_entity_int_value (task, INT_TYPE_ENTITY_SUB_TYPE))
							{
								case ENTITY_SUB_TYPE_TASK_LANDING:
								{
									//
									// Landing task needs to free landing SITE and landing ROUTE
									//
									
									landing = get_local_group_member_landing_entity_from_task (member);
							
									notify_local_entity (ENTITY_MESSAGE_UNLOCK_LANDING_ROUTE, landing, member);
	
									notify_local_entity (ENTITY_MESSAGE_UNLOCK_LANDING_SITE, landing, member);
	
									break;
								}
								case ENTITY_SUB_TYPE_TASK_LANDING_HOLDING:
								{
									//
									// Landing-Holding task needs to free landing SITE only
									//
									
									landing = get_local_group_member_landing_entity_from_task (member);
							
									notify_local_entity (ENTITY_MESSAGE_UNLOCK_LANDING_SITE, landing, member);
	
									break;
								}
							}
						}
	
						member = get_local_entity_child_succ (member, LIST_TYPE_MEMBER);
					}
	
					create_group_emergency_transfer_task (group);
				}
			}
			else
			{
				//
				// Kill all other groups linked to keysite (e.g. people, or recently regen-ed tanks etc.)
				//
	
				group_kill_all_members (group);
			}
			
			group = next_group;
		}
	}

	//
	// Terminate unassigned tasks
	//

	task = get_local_entity_first_child (en, LIST_TYPE_UNASSIGNED_TASK);

	while (task)
	{
		next = get_local_entity_child_succ (task, LIST_TYPE_UNASSIGNED_TASK);

		notify_local_entity (ENTITY_MESSAGE_TASK_TERMINATED, task, NULL, TASK_TERMINATED_ABORTED);

		task = next;
	}

	//
	// Terminate (complete) all tasks against the keysite
	//

	task = get_local_entity_first_child (en, LIST_TYPE_TASK_DEPENDENT);

	while (task)
	{
		next = get_local_entity_child_succ (task, LIST_TYPE_TASK_DEPENDENT);

		if (get_local_entity_type (task) == ENTITY_TYPE_TASK)
		{
			notify_local_entity (ENTITY_MESSAGE_TASK_COMPLETED, task, NULL, TASK_INCOMPLETE);
		}

		task = next;
	}

	//
	// Reduce size of regen queue dependent on keysite type
	//

	switch (get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE))
	{
		case ENTITY_SUB_TYPE_KEYSITE_AIRBASE:
		{
			increment_regen_queue_size (side, ENTITY_TYPE_HELICOPTER, -6);

			increment_regen_queue_size (side, ENTITY_TYPE_FIXED_WING, -4);

			break;
		}
		case ENTITY_SUB_TYPE_KEYSITE_FARP:
		{
			increment_regen_queue_size (side, ENTITY_TYPE_HELICOPTER, -2);

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void capture_keysite (entity *en, entity_sides new_side)
{
	keysite
		*raw;

	entity
		*force;

	entity_sides
		side;

	entity_sub_types
		keysite_type;

	vec3d
		*pos;

	int
		loop;

	ASSERT (en);

	ASSERT (get_local_entity_type (en) == ENTITY_TYPE_KEYSITE);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	raw = (keysite *) get_local_entity_data (en);

	side = (entity_sides) raw->side;

	ASSERT (side != new_side);

	pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

	ai_log ("(KEYSITE) %s CAPTURED BY %s", get_local_entity_string (en, STRING_TYPE_KEYSITE_NAME), entity_side_short_names [new_side]);
	debug_colour_log (DEBUG_COLOUR_DARK_GREEN, "KEYSITE: %s CAPTURED BY %s", get_local_entity_string (en, STRING_TYPE_KEYSITE_NAME), entity_side_short_names [new_side]);

	//
	// update imaps (old side)
	//

	update_imap_sector_side (en, FALSE);

	transmit_entity_comms_message (ENTITY_COMMS_UPDATE_SECTOR_SIDE, en, FALSE);

	update_imap_importance_level (en, FALSE);

	//
	// switch sides
	//

	set_client_server_entity_int_value (en, INT_TYPE_SIDE, new_side);

	set_client_server_entity_parent (en, LIST_TYPE_KEYSITE_FORCE, get_local_force_entity (new_side));

	// must be done after removed from force
	update_imap_distance_to_friendly_base (side);

	//
	// update imaps (new side)
	//

	update_imap_sector_side (en, TRUE);

	transmit_entity_comms_message (ENTITY_COMMS_UPDATE_SECTOR_SIDE, en, TRUE);

	update_imap_importance_level (en, TRUE);

	update_keysite_distance_to_friendly_base (en, new_side);

	{
		entity
			*group,
			*current_group,
			*member;

		group = get_local_entity_first_child (en, LIST_TYPE_KEYSITE_GROUP);
	
		while (group)
		{
			current_group = group;
			
			group = get_local_entity_child_succ (group, LIST_TYPE_KEYSITE_GROUP);

			if (get_local_entity_int_value (current_group, INT_TYPE_AIRCRAFT_GROUP))
			{
				if (command_line_capture_aircraft && get_local_entity_int_value (current_group, INT_TYPE_GROUP_MODE) == GROUP_MODE_IDLE)
				{
					debug_colour_log (DEBUG_COLOUR_SANDY_BROWN, "KEYSITE: trying to change side of landed aircrafts at keysite %s", get_local_entity_string (en, STRING_TYPE_KEYSITE_NAME));

					member = get_local_entity_first_child (current_group, LIST_TYPE_MEMBER);

					while (member)
					{
						set_client_server_entity_int_value (member, INT_TYPE_SIDE, new_side);

						member = get_local_entity_child_succ (member, LIST_TYPE_MEMBER);
					}

					free_group_callsign (current_group);

					set_client_server_entity_int_value (current_group, INT_TYPE_SIDE, new_side);

					set_client_server_entity_int_value (current_group, INT_TYPE_GROUP_CALLSIGN, assign_group_callsign (current_group));
				}
			}
			else
			{
				if (get_local_entity_int_value (current_group, INT_TYPE_GROUP_LIST_TYPE) == LIST_TYPE_KEYSITE_GROUP)
				{
					debug_colour_log (DEBUG_COLOUR_SANDY_BROWN, "KEYSITE: trying to unlink ground units from keysite %s", get_local_entity_string (en, STRING_TYPE_KEYSITE_NAME));

					force = get_local_force_entity (side);

					ASSERT (force);

					delete_local_entity_from_parents_child_list (current_group, LIST_TYPE_KEYSITE_GROUP);

					set_local_entity_int_value (current_group, INT_TYPE_GROUP_LIST_TYPE, LIST_TYPE_INDEPENDENT_GROUP);

					set_local_entity_parent (current_group, LIST_TYPE_INDEPENDENT_GROUP, force);
				}
				else
				{
					debug_colour_log (DEBUG_COLOUR_RED, "KEYSITE: independed ground units linked with keysite %s", get_local_entity_string (en, STRING_TYPE_KEYSITE_NAME));
				}
			}
		}
	}

	//
	// Kill aircraft landed at keysite + sort out landing locks + unassigned tasks + ground vehicles etc........
	//

	destroy_keysite (en, side);

	//
	// Change side of all buildings connected to the keysite
	//

	change_local_keysite_building_sides (en, new_side);

	transmit_entity_comms_message (ENTITY_COMMS_CAPTURE_KEYSITE, en, new_side);

	//
	// Notify force to check campaign criteria
	//

	force = get_local_entity_first_child (get_session_entity (), LIST_TYPE_FORCE);

	while (force)
	{
		notify_local_entity (ENTITY_MESSAGE_CHECK_CAMPAIGN_OBJECTIVES, force, en);

		force = get_local_entity_child_succ (force, LIST_TYPE_FORCE);
	}

	//
	// Send text message
	//

	send_text_message (en, NULL, MESSAGE_TEXT_SYSTEM_KEYSITE_CAPTURED, NULL);

	//
	// Repair some structures
	//

	for (loop = 0; loop < 5; loop ++)
	{
		if (!repair_client_server_entity_keysite (en))
		{
			break;
		}
	}

	//
	// Set state to repairing (unless full strength)
	//

	if (raw->keysite_strength == raw->keysite_maximum_strength)
	{
		set_client_server_entity_int_value (en, INT_TYPE_KEYSITE_USABLE_STATE, KEYSITE_STATE_USABLE);
	}
	else
	{
		set_client_server_entity_int_value (en, INT_TYPE_KEYSITE_USABLE_STATE, KEYSITE_STATE_REPAIRING);
	}

	//
	// Increase size of regen queue dependent on keysite type
	//

	keysite_type = get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE);

	switch (keysite_type)
	{
		case ENTITY_SUB_TYPE_KEYSITE_AIRBASE:
		{
			increment_regen_queue_size (new_side, ENTITY_TYPE_HELICOPTER, 6);

			add_default_entity_to_regen_queue (new_side, ENTITY_SUB_TYPE_GROUP_ATTACK_HELICOPTER);
			add_default_entity_to_regen_queue (new_side, ENTITY_SUB_TYPE_GROUP_ATTACK_HELICOPTER);

			add_default_entity_to_regen_queue (new_side, ENTITY_SUB_TYPE_GROUP_RECON_ATTACK_HELICOPTER);
			add_default_entity_to_regen_queue (new_side, ENTITY_SUB_TYPE_GROUP_RECON_ATTACK_HELICOPTER);

			add_default_entity_to_regen_queue (new_side, ENTITY_SUB_TYPE_GROUP_ASSAULT_HELICOPTER);
			add_default_entity_to_regen_queue (new_side, ENTITY_SUB_TYPE_GROUP_ASSAULT_HELICOPTER);

			increment_regen_queue_size (new_side, ENTITY_TYPE_FIXED_WING, 4);

			add_default_entity_to_regen_queue (new_side, ENTITY_SUB_TYPE_GROUP_CLOSE_AIR_SUPPORT_AIRCRAFT);
			add_default_entity_to_regen_queue (new_side, ENTITY_SUB_TYPE_GROUP_CLOSE_AIR_SUPPORT_AIRCRAFT);

			add_default_entity_to_regen_queue (new_side, ENTITY_SUB_TYPE_GROUP_MULTI_ROLE_FIGHTER);
			add_default_entity_to_regen_queue (new_side, ENTITY_SUB_TYPE_GROUP_MULTI_ROLE_FIGHTER);

			break;
		}
		case ENTITY_SUB_TYPE_KEYSITE_FARP:
		{
			increment_regen_queue_size (new_side, ENTITY_TYPE_HELICOPTER, 2);

			add_default_entity_to_regen_queue (new_side, ENTITY_SUB_TYPE_GROUP_RECON_ATTACK_HELICOPTER);
			add_default_entity_to_regen_queue (new_side, ENTITY_SUB_TYPE_GROUP_RECON_ATTACK_HELICOPTER);

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void change_local_keysite_building_sides (entity *en, entity_sides new_side)
{
	entity
		*group,
		*member;

	ASSERT (en);

	//
	// Normal Buildings
	//
	
	group = get_local_entity_first_child (en, LIST_TYPE_BUILDING_GROUP);

	while (group)
	{
		set_local_entity_int_value (group, INT_TYPE_SIDE, new_side);

		member = get_local_entity_first_child (group, LIST_TYPE_MEMBER);

		while (member)
		{
			set_local_entity_int_value (member, INT_TYPE_SIDE, new_side);
			
			member = get_local_entity_child_succ (member, LIST_TYPE_MEMBER);
		}

		group = get_local_entity_child_succ (group, LIST_TYPE_BUILDING_GROUP);
	}

	//
	// Regen Buildings
	//
	
	group = get_local_entity_first_child (en, LIST_TYPE_REGEN);

	while (group)
	{
		set_local_entity_int_value (group, INT_TYPE_SIDE, new_side);

		member = get_local_entity_first_child (group, LIST_TYPE_MEMBER);

		while (member)
		{
			set_local_entity_int_value (member, INT_TYPE_SIDE, new_side);
			
			member = get_local_entity_child_succ (member, LIST_TYPE_MEMBER);
		}

		group = get_local_entity_child_succ (group, LIST_TYPE_REGEN);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int repair_client_server_entity_keysite (entity *en)
{
	keysite
		*raw;

	entity
		*group,
		*building,
		*regen;

	float
		importance;

	ASSERT (en);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	raw = (keysite *) get_local_entity_data (en);
	
	//
	// Find next structure to repair
	//

	group = get_local_entity_first_child (en, LIST_TYPE_BUILDING_GROUP);

	while (group)
	{
		building = get_local_entity_first_child (group, LIST_TYPE_MEMBER);

		while (building)
		{
			if (!get_local_entity_int_value (building, INT_TYPE_ALIVE))
			{
				//
				// Repair building
				//
				
				restore_local_fixed_entity (building);

				transmit_entity_comms_message (ENTITY_COMMS_RESTORE_FIXED_ENTITY, building);

				//
				// Set timer
				//

				importance = get_local_entity_float_value (building, FLOAT_TYPE_FIXED_OBJECT_IMPORTANCE);

				raw->repair_timer = (10.0 * ONE_MINUTE);

				ai_log ("(KEYSITE) REPAIRED %s at keysite %s (importance %f) (strength %f / %f)",
								object_3d_enumeration_names [get_local_entity_int_value (building, INT_TYPE_OBJECT_3D_SHAPE)],
								get_local_entity_string (en, STRING_TYPE_KEYSITE_NAME),
								importance,
								raw->keysite_strength, raw->keysite_maximum_strength);

				return TRUE;
			}

			building = get_local_entity_child_succ (building, LIST_TYPE_MEMBER);
		}

		group = get_local_entity_child_succ (group, LIST_TYPE_BUILDING_GROUP);
	}

	//
	// No normal structures found - check regen
	//

	regen = get_local_entity_first_child (en, LIST_TYPE_REGEN);

	while (regen)
	{
		building = get_local_entity_first_child (regen, LIST_TYPE_MEMBER);

		while (building)
		{
			if (!get_local_entity_int_value (building, INT_TYPE_ALIVE))
			{
				//
				// Repair building
				//
				
				restore_local_fixed_entity (building);

				transmit_entity_comms_message (ENTITY_COMMS_RESTORE_FIXED_ENTITY, building);

				//
				// Set timer
				//

				importance = get_local_entity_float_value (building, FLOAT_TYPE_FIXED_OBJECT_IMPORTANCE);

				raw->repair_timer = (20.0 * ONE_MINUTE);

				ai_log ("(KEYSITE) REPAIRED %s (REGEN) at keysite %s (importance %f) (strength %f / %f)",
								object_3d_enumeration_names [get_local_entity_int_value (building, INT_TYPE_OBJECT_3D_SHAPE)],
								get_local_entity_string (en, STRING_TYPE_KEYSITE_NAME),
								importance,
								raw->keysite_strength, raw->keysite_maximum_strength);

				return TRUE;
			}

			building = get_local_entity_child_succ (building, LIST_TYPE_MEMBER);
		}

		regen = get_local_entity_child_succ (regen, LIST_TYPE_REGEN);
	}

	//
	// All buildings repaired - set state back to usable
	//

	ai_log ("(KEYSITE) %s FULLY REPAIRED (strength %f / %f)",
				get_local_entity_string (en, STRING_TYPE_KEYSITE_NAME),
				raw->keysite_strength, raw->keysite_maximum_strength);

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_keysite_suitable_for_player (entity *keysite, entity *pilot)
{
	entity
		*group,
		*member;

	ASSERT (keysite);

	group = get_local_entity_first_child (keysite, LIST_TYPE_KEYSITE_GROUP);

	while (group)
	{
		member = get_local_entity_first_child (group, LIST_TYPE_MEMBER);

		while (member)
		{
			if (get_local_entity_suitable_for_player (member, pilot))
			{
				return TRUE;
			}

			member = get_local_entity_child_succ (member, LIST_TYPE_MEMBER);
		}

		group = get_local_entity_child_succ (group, LIST_TYPE_KEYSITE_GROUP);
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void dump_keysite_info (void)
{

	int
		count;

	float
		hours,
		minutes,
		seconds;

	entity
		*ks,
//		*mb,
		*ts,
		*force;

	session
		*raw;

	FILE
		*file_ptr;

	char
		buffer [32];

	count = 0;

	sprintf (buffer, "ks%d.txt", count);

	while (file_exist (buffer))
	{

		count ++;

		sprintf (buffer, "ks%d.txt", count);
	}

	file_ptr = fopen (buffer, "w");

	if (!file_ptr)
	{

		return;
	}

	force = get_local_entity_first_child (get_session_entity (), LIST_TYPE_FORCE);

	raw = (session *) get_local_entity_data (get_session_entity ());

	get_digital_clock_values (raw->elapsed_time, &hours, &minutes, &seconds);

	fprintf (file_ptr, "SESSION: %02f:%02f:%02f\n", hours, minutes, seconds);

	while (force)
	{

		fprintf (file_ptr, "---------------------------------------------------------------------------------------------------------------------------\n");
		fprintf (file_ptr, "FORCE %s\n", entity_side_names [get_local_entity_int_value (force, INT_TYPE_SIDE)]);

		ks = get_local_entity_first_child (force, LIST_TYPE_KEYSITE_FORCE);

		while (ks)
		{

			if ((!get_local_entity_int_value (ks, INT_TYPE_IN_USE)) || (!get_local_entity_int_value (ks, INT_TYPE_ALIVE)))
			{

				ks = get_local_entity_child_succ (ks, LIST_TYPE_KEYSITE_FORCE);

				continue;
			}

			fprintf (file_ptr, "    --------------------------------------------------------------------------------------\n");

			fprintf (file_ptr, "    Keysite %s %s (%d). In use %d, Alive %d\n",
						get_local_entity_string (ks, STRING_TYPE_FULL_NAME),
						get_local_entity_string (ks, STRING_TYPE_KEYSITE_NAME),
						get_local_entity_index (ks),
						get_local_entity_int_value (ks, INT_TYPE_IN_USE),
						get_local_entity_int_value (ks, INT_TYPE_ALIVE));

			fprintf (file_ptr, "        efficiency %02f, ammo %02f, fuel %02f\n",
						get_local_entity_float_value (ks, FLOAT_TYPE_EFFICIENCY),
						get_local_entity_float_value (ks, FLOAT_TYPE_AMMO_SUPPLY_LEVEL),
						get_local_entity_float_value (ks, FLOAT_TYPE_FUEL_SUPPLY_LEVEL));

			//
			// Members
			//
/*
			fprintf (file_ptr, "        ----------------------------------------------------\n");

			fprintf (file_ptr, "        Members %d\n",
						get_local_entity_list_size (ks, LIST_TYPE_KEYSITE_MEMBER));

			mb = get_local_entity_first_child (ks, LIST_TYPE_KEYSITE_MEMBER);

			while (mb)
			{

				fprintf (file_ptr, "            %s (%d) %s\n",
							get_local_entity_string (mb, STRING_TYPE_FULL_NAME),
							get_local_entity_index (mb),
							operational_state_names [get_local_entity_int_value (mb, INT_TYPE_OPERATIONAL_STATE)]);
	
				mb = get_local_entity_child_succ (mb, LIST_TYPE_KEYSITE_MEMBER);
			}
*/
			//
			// Tasks
			//

			fprintf (file_ptr, "        ----------------------------------------------------\n");

			fprintf (file_ptr, "        Tasks %d\n",
						get_local_entity_list_size (ks, LIST_TYPE_UNASSIGNED_TASK));

			ts = get_local_entity_first_child (ks, LIST_TYPE_UNASSIGNED_TASK);

			while (ts)
			{

				fprintf (file_ptr, "            %s (%d)\n",
							get_local_entity_string (ts, STRING_TYPE_FULL_NAME),
							get_local_entity_index (ts));
	
				ts = get_local_entity_child_succ (ts, LIST_TYPE_UNASSIGNED_TASK);
			}

			ks = get_local_entity_child_succ (ks, LIST_TYPE_KEYSITE_FORCE);
		}

		force = get_local_entity_child_succ (force, LIST_TYPE_FORCE);
	}

	fclose (file_ptr);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void validate_keysite_landing_site_heights (entity *keysite)
{

	entity
		*landing,
		*task,
		*waypoint;

	vec3d
		*keysite_position,
		*waypoint_position;

	float
		terrain_elevation,
		delta_height;

	ASSERT (get_local_entity_type (keysite) == ENTITY_TYPE_KEYSITE);

	keysite_position = get_local_entity_vec3d_ptr (keysite, VEC3D_TYPE_POSITION);

	landing = get_local_entity_first_child (keysite, LIST_TYPE_LANDING_SITE);

	while (landing)
	{

		task = get_local_landing_entity_task (landing, ENTITY_SUB_TYPE_TASK_LANDING);

		ASSERT (task);
	
  		waypoint = get_local_entity_first_child (task, LIST_TYPE_WAYPOINT);

		while (waypoint)
		{

			if (get_local_entity_int_value (waypoint, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_WAYPOINT_LANDED)
			{

				waypoint_position = get_local_entity_vec3d_ptr (waypoint, VEC3D_TYPE_POSITION);

				ASSERT(point_inside_map_area(waypoint_position));
	
				terrain_elevation = get_3d_terrain_elevation (waypoint_position->x, waypoint_position->z);

				delta_height = waypoint_position->y - terrain_elevation;

				if (fabs (delta_height) > KEYSITE_LANDING_SITE_TOLERANCE)
				{

					debug_log ("KEYSITE: WARNING: keysite %s (%d) landing site %s %d waypoint %d outside of height tolerance (delta %f, waypoint- y = %f, terrain elevation %f)",
									get_local_entity_string (keysite, STRING_TYPE_KEYSITE_NAME), get_local_entity_index (keysite),
									get_local_entity_string (landing, STRING_TYPE_FULL_NAME), get_local_entity_index (landing),
									get_local_entity_index (waypoint),
									delta_height, waypoint_position->y, terrain_elevation);

					break;
				}
			}

			waypoint = get_local_entity_child_succ (waypoint, LIST_TYPE_WAYPOINT);
		}

		landing = get_local_entity_child_succ (landing, LIST_TYPE_LANDING_SITE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void play_keysite_under_attack_speech (entity *en, entity *aggressor)
{
	vec3d
		*pos;

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION); 

	ASSERT (pos);

	get_speech_sector_coordinates (pos);

	play_client_server_speech
	(
		get_session_entity (),
		en,
		(entity_sides) get_local_entity_int_value (en, INT_TYPE_SIDE),
		ENTITY_SUB_TYPE_EFFECT_SOUND_RADIO_MESSAGE,
		SOUND_LOCALITY_RADIO,
		0.0,
		1.0,
		20.0,
		SPEECH_ORIGINATOR_FORWARD_AIR_CONTROLLER,
		SPEECH_CATEGORY_UNDER_ATTACK,
		45.0,
		SPEECH_ARRAY_FAC_MESSAGES, SPEECH_FAC_INTRODUCTION,
		SPEECH_ARRAY_FAC_MESSAGES, SPEECH_FAC_BASE_UNDER_ATTACK,
		SPEECH_ARRAY_NUMBERS, speech_sector_coordinates [0],
		SPEECH_ARRAY_NUMBERS, speech_sector_coordinates [1],
		SPEECH_ARRAY_NUMBERS, speech_sector_coordinates [2],
		SPEECH_ARRAY_NUMBERS, speech_sector_coordinates [3],
		SPEECH_ARRAY_NUMBERS, speech_sector_coordinates [4],
		SPEECH_ARRAY_NUMBERS, speech_sector_coordinates [5],
		-1
	);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_keysite_entity_mfd_display_name (entity *en, char *s)
{
	entity_sub_types
		sub_type;

	ASSERT (s);

	ASSERT (en);

	sub_type = get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE);

	if (keysite_database [sub_type].unique_name)
	{
		sprintf (s, "%s", get_local_entity_string (en, STRING_TYPE_KEYSITE_NAME));
	}
	else
	{
		sprintf (s, "%s %d", keysite_database [sub_type].short_name, get_local_entity_int_value (en, INT_TYPE_KEYSITE_ID)); 
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
