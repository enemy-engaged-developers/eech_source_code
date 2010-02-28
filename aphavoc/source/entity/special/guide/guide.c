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
#include "ai/taskgen/taskgen.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void initialise_guide_criteria (entity *en);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char
	*guide_criteria_type_names [NUM_GUIDE_CRITERIA_TYPES] =
	{
		"RADIUS",
		"HEADING",
		"ALTITUDE",
		"TRANSMIT_DATA",
		"LAST_TO_REACH",	
		"WEAPON_VECTOR"
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const int
	guide_position_type_virtual [NUM_GUIDE_POSITION_TYPES] =
	{
		FALSE,					// ABSOLUTE
		FALSE,					// WAYPOINT
		TRUE,						// RELATIVE_WORLD_SPACE
		TRUE,						// RELATIVE_OBJECT_SPACE,
		TRUE,						// RELATIVE_CIRCULAR,
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *create_client_server_guide_entity (entity *task_en, entity *first_waypoint, unsigned int valid_members)
{
	entity
		*en,
		*wp;

	vec3d
		*pos;

	int
		guide_type,
		create_stack_attributes;

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	ASSERT (task_en);

	#ifdef DEBUG
	
	if (valid_members == 0)
	{
		ASSERT (get_local_entity_int_value (task_en, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_TASK_ENGAGE);
	}

	#endif

	if (first_waypoint)
	{
		//
		// first waypoint has been specified - but check it actually belongs to the task...
		//
		
		wp = first_waypoint;

		ASSERT (get_local_entity_parent (wp, LIST_TYPE_WAYPOINT) == task_en);
	}
	else
	{
		//
		// get first waypoint of the task
		//

		wp = get_local_entity_first_child (task_en, LIST_TYPE_WAYPOINT);
	}

	ASSERT (wp);

	//
	// set sub type (must be done before set position)
	//

	guide_type = get_local_entity_int_value (wp, INT_TYPE_WAYPOINT_GUIDE_TYPE);

	//
	// get waypoint position 
	//

	pos = get_local_entity_vec3d_ptr (wp, VEC3D_TYPE_POSITION);

	ASSERT (pos);
	
	//
	// create guide entity
	//

	create_stack_attributes = force_local_entity_create_stack_attributes;

	if (get_comms_data_flow () == COMMS_DATA_FLOW_RX)
	{
		set_force_local_entity_create_stack_attributes (TRUE);
	}

	en = create_client_server_entity
	(
		ENTITY_TYPE_GUIDE,
		ENTITY_INDEX_DONT_CARE,
		ENTITY_ATTR_PARENT (LIST_TYPE_GUIDE, task_en),
		ENTITY_ATTR_PARENT (LIST_TYPE_CURRENT_WAYPOINT, wp),
		ENTITY_ATTR_INT_VALUE (INT_TYPE_ENTITY_SUB_TYPE, guide_type),
		ENTITY_ATTR_INT_VALUE (INT_TYPE_VALID_GUIDE_MEMBERS, valid_members),
		ENTITY_ATTR_VEC3D (VEC3D_TYPE_POSITION, pos->x, pos->y, pos->z),
		ENTITY_ATTR_END
	);

	set_force_local_entity_create_stack_attributes (create_stack_attributes);

	return en;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int validate_local_guide_entity (entity *en)
{
	entity
		*task;

	//
	// guide should always have a task and a group
	//

	task = get_local_entity_parent (en, LIST_TYPE_GUIDE);

	ASSERT (task);

	ASSERT (get_local_entity_parent (en, LIST_TYPE_GUIDE_STACK));

	//
	// Guide cannot be terrain following if waypoint has altitude criteria
	//

	if (get_local_entity_int_value (en, INT_TYPE_TERRAIN_FOLLOW_MODE) != GUIDE_TERRAIN_FOLLOW_NONE)
	{
		ASSERT (!get_guide_criteria_valid (en, GUIDE_CRITERIA_ALTITUDE));
	}

	//
	// Guide shouldn't have both heading AND weapon_vector criteria set
	//

	if (get_guide_criteria_valid (en, GUIDE_CRITERIA_HEADING))
	{
		ASSERT (!get_guide_criteria_valid (en, GUIDE_CRITERIA_WEAPON_VECTOR));
	}

	//
	// Engage tasks with valid members should never be on the stack unless they are being done 
	//

	if (get_local_entity_int_value (task, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_TASK_ENGAGE)
	{
		if (get_local_entity_int_value (en, INT_TYPE_VALID_GUIDE_MEMBERS) != TASK_ASSIGN_NO_MEMBERS)
		{
			ASSERT (get_local_entity_first_child (en, LIST_TYPE_FOLLOWER));
		}
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int check_guide_reached_waypoint (entity *en)
{
	entity
		*leader,
		*member,
		*group;

	int
		member_number,
		valid_members;

	//
	// find task leader
	//

	leader = (entity *) get_local_entity_ptr_value (en, PTR_TYPE_TASK_LEADER);

	if (!leader)
	{
		return FALSE;
	}

	if (get_guide_criteria_valid (en, GUIDE_CRITERIA_LAST_TO_REACH))
	{
		//
		// check all valid members reached
		//

		group = get_local_entity_parent (en, LIST_TYPE_GUIDE_STACK);

		ASSERT (group);

		valid_members = get_local_entity_int_value (en, INT_TYPE_VALID_GUIDE_MEMBERS);

		member = get_local_entity_first_child (group, LIST_TYPE_MEMBER);
		
		while (member)
		{
			member_number = (1 << get_local_entity_int_value (member, INT_TYPE_GROUP_MEMBER_NUMBER));

			if (valid_members & member_number)
			{
				if (!notify_local_entity (ENTITY_MESSAGE_CHECK_MOBILE_REACHED_GUIDE, member, en))
				{
					return FALSE;
				}
			}

			member = get_local_entity_child_succ (member, LIST_TYPE_MEMBER);
		}
	}
	else
	{
		//
		// check task leader reached
		//

		if (!notify_local_entity (ENTITY_MESSAGE_CHECK_MOBILE_REACHED_GUIDE, leader, en))
		{
			return FALSE;
		}
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int check_guide_waypoint_action_reached (entity *en)
{
	float
		range;

	entity
		*wp,
		*leader;

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	//
	// find task leader
	//

	leader = (entity *) get_local_entity_ptr_value (en, PTR_TYPE_TASK_LEADER);

	if (!leader)
	{
		return FALSE;
	}

	//
	// Check if landed
	//

	if (get_local_entity_int_value (leader, INT_TYPE_LANDED))
	{
		return FALSE;
	}

	//
	// check task leader reached action radius
	//

	wp = get_local_entity_parent (en, LIST_TYPE_CURRENT_WAYPOINT);

	ASSERT (wp);

	range = get_local_entity_float_value (leader, FLOAT_TYPE_DISTANCE);
	
	if (range > get_local_entity_waypoint_database_action_radius_value (wp, leader))
	{
		return FALSE;
	}
		
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int set_guide_new_waypoint (entity *en, entity *wp)
{
	entity
		*task,
		*group,
		*leader,
		*member,
		*objective,
		*current_wp;

	vec3d
		new_pos,
		*leader_pos;

	float
		range,
		velocity;

	entity_sub_types
		guide_type,
		group_type,
		waypoint_type;
		
	entity_types
		member_type;

	if (get_comms_model () != COMMS_MODEL_SERVER)
	{
		transmit_entity_comms_message (ENTITY_COMMS_SET_WAYPOINT, en, wp);

		return TRUE;
	}

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	ASSERT (wp);

	current_wp = get_local_entity_parent (en, LIST_TYPE_CURRENT_WAYPOINT);

	ASSERT (current_wp);

	group = get_local_entity_parent (en, LIST_TYPE_GUIDE_STACK);

	ASSERT (group);

	group_type = get_local_entity_int_value (group, INT_TYPE_ENTITY_SUB_TYPE);

	member = get_local_entity_first_child (group, LIST_TYPE_MEMBER);

	ASSERT (member);

	member_type = group_database [group_type].default_entity_type;

	waypoint_type = get_local_entity_int_value (wp, INT_TYPE_ENTITY_SUB_TYPE);

	//
	// set sub type (must be done before set position)
	//

	guide_type = get_local_entity_int_value (wp, INT_TYPE_WAYPOINT_GUIDE_TYPE);

	set_client_server_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE, guide_type);

	//
	// set positions
	//

	if (guide_position_type_virtual [guide_database [guide_type].position_type])
	{
		task = get_local_entity_parent (wp, LIST_TYPE_WAYPOINT);

		ASSERT (task);

		objective = get_local_entity_parent (task, LIST_TYPE_TASK_DEPENDENT);

		ASSERT (objective);

		new_pos.x = 0.0;
		new_pos.y = 0.0;
		new_pos.z = get_waypoint_database_reached_radius_value (waypoint_type, member_type);

		set_client_server_guide_entity_new_position (en, &new_pos, objective);
	}
	else
	{
		get_local_entity_vec3d (wp, VEC3D_TYPE_POSITION, &new_pos);

////Moje 030923 Todd's suggestion to solve the FARP bug Start

////Moje 030924 -didn't help                 new_pos.y = get_3d_terrain_elevation (new_pos.x, new_pos.z);

////Moje 030923 Todd's suggestion to solve the FARP bug End

		set_client_server_guide_entity_new_position (en, &new_pos, NULL);
	}

	//
	// Set distance to task leader
	//

	leader = (entity *) get_local_entity_ptr_value (en, PTR_TYPE_TASK_LEADER);

	if (leader)
	{
		leader_pos = get_local_entity_vec3d_ptr (leader, VEC3D_TYPE_POSITION);

		range = get_2d_range (leader_pos, &new_pos);

		set_local_entity_float_value (leader, FLOAT_TYPE_DISTANCE, range);
	}

	//
	// set velocity
	//

	velocity = get_waypoint_database_velocity_value (waypoint_type, member_type);

	velocity *= get_local_entity_float_value (member, FLOAT_TYPE_CRUISE_VELOCITY);

	set_client_server_entity_float_value (en, FLOAT_TYPE_VELOCITY, velocity);

	//
	// seperate check for waypoint action ?
	//

	set_local_entity_int_value (en, INT_TYPE_CHECK_WAYPOINT_ACTION, get_local_entity_int_value (wp, INT_TYPE_CHECK_WAYPOINT_ACTION));

	//
	// set new waypoint
	//

	set_client_server_entity_parent (en, LIST_TYPE_CURRENT_WAYPOINT, wp);

	//
	// set new guide reached criteria
	//

	initialise_guide_criteria (en);

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int set_guide_next_waypoint (entity *en)
{
	entity
		*current_wp,
		*next_wp;

	current_wp = get_local_entity_parent (en, LIST_TYPE_CURRENT_WAYPOINT);

	ASSERT (current_wp);

	next_wp = get_local_entity_child_succ (current_wp, LIST_TYPE_WAYPOINT);

	if (next_wp)
	{
		set_guide_new_waypoint (en, next_wp);
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int set_guide_prev_waypoint (entity *en)
{
	entity
		*current_wp,
		*prev_wp;

	current_wp = get_local_entity_parent (en, LIST_TYPE_CURRENT_WAYPOINT);

	ASSERT (current_wp);

	prev_wp = get_local_entity_child_pred (current_wp, LIST_TYPE_WAYPOINT);

	if (prev_wp)
	{
		set_guide_new_waypoint (en, prev_wp);
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_local_guide_position (entity *en, vec3d *pos)
{
	guide
		*raw;

	ASSERT (en);

	ASSERT (pos);

	raw = (guide *) get_local_entity_data (en);
	
	switch (raw->guide_position_type)
	{
		case GUIDE_POSITION_ABSOLUTE:
		{
			get_local_entity_vec3d (en, VEC3D_TYPE_POSITION, pos);

			break;
		}

		case GUIDE_POSITION_WAYPOINT:
		{
			entity
				*wp;

			wp = get_local_entity_parent (en, LIST_TYPE_CURRENT_WAYPOINT);

			ASSERT (wp);
			
			get_local_entity_vec3d (wp, VEC3D_TYPE_POSITION, pos);

			break;
		}

		case GUIDE_POSITION_RELATIVE_WORLD_SPACE:
		{
			vec3d
				*rel_pos,
				*target_pos;

			entity
				*target;

			rel_pos = &raw->position;

			target = raw->position_entity;
		
			ASSERT (target);

			target_pos = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

			pos->x = target_pos->x + rel_pos->x;
			pos->y = target_pos->y + rel_pos->y;
			pos->z = target_pos->z + rel_pos->z;

			break;
		}

		case GUIDE_POSITION_RELATIVE_OBJECT_SPACE:
		{
			vec3d
				*rel_pos,
				*target_pos;

			entity
				*target;

			matrix3x3
				m;

			rel_pos = &raw->position;

			target = raw->position_entity;
		
			ASSERT (target);

			target_pos = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

			if (check_zero_3d_vector (rel_pos))
			{
				*pos = *target_pos;
			}
			else
			{	
				get_local_entity_attitude_matrix (target, m);

				pos->x = target_pos->x + ( ( rel_pos->x * m[0][0] ) + ( rel_pos->y * m[1][0] ) + ( rel_pos->z * m[2][0] ) );
				pos->y = target_pos->y + ( ( rel_pos->x * m[0][1] ) + ( rel_pos->y * m[1][1] ) + ( rel_pos->z * m[2][1] ) );
				pos->z = target_pos->z + ( ( rel_pos->x * m[0][2] ) + ( rel_pos->y * m[1][2] ) + ( rel_pos->z * m[2][2] ) );
			}

			break;
		}

		case GUIDE_POSITION_RELATIVE_CIRCULAR:
		{
			vec3d
				*rel_pos,
				*target_pos,
				*aggressor_pos,
				target_vec;

			entity
				*target,
				*aggressor;

			float
				distance;

			rel_pos = &raw->position;

			target = raw->position_entity;
		
			ASSERT (target);

			target_pos = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

			//
			// radius of circle stored in guide position z component
			//

			distance = rel_pos->z;

			if (distance == 0.0)
			{
				*pos = *target_pos;
			}
			else
			{
				aggressor = get_local_entity_first_child (en, LIST_TYPE_FOLLOWER);

				ASSERT (aggressor);

				aggressor_pos = get_local_entity_vec3d_ptr (aggressor, VEC3D_TYPE_POSITION);
				
				target_vec.x = aggressor_pos->x - target_pos->x;
				target_vec.y = 0.0;
				target_vec.z = aggressor_pos->z - target_pos->z;

				if (normalise_any_3d_vector (&target_vec) == 0.0)
				{
					//
					// just in case aggressor is on top of target
					//
					
					get_local_entity_vec3d (aggressor, VEC3D_TYPE_ZV, &target_vec);

					target_vec.y = 0.0;
				
					normalise_3d_vector (&target_vec);
				}

				pos->x = target_pos->x + (target_vec.x * distance);
				pos->y = target_pos->y;
				pos->z = target_pos->z + (target_vec.z * distance);
			}

			break;
		}

		default:
		{
			debug_fatal ("GUIDE: Invalid guide position type (%d)", raw->guide_position_type);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void attach_group_member_to_guide_entity (entity *member, entity *guide)
{
	ASSERT (member);
	ASSERT (guide);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	#ifdef DEBUG
	{
		int
			valid_members,
			member_number;
			
		valid_members = get_local_entity_int_value (guide, INT_TYPE_VALID_GUIDE_MEMBERS);

		member_number = (1 << get_local_entity_int_value (member, INT_TYPE_GROUP_MEMBER_NUMBER));

		ASSERT (valid_members & member_number);
	}
	#endif

	//
	// follower link
	//

	delete_local_entity_from_parents_child_list (member, LIST_TYPE_FOLLOWER);

	insert_local_entity_into_parents_child_list (member, LIST_TYPE_FOLLOWER, guide, NULL);

	transmit_entity_comms_message (ENTITY_COMMS_SWITCH_LIST, member, LIST_TYPE_FOLLOWER, guide, LIST_TYPE_FOLLOWER);

	//
	// set mobile range to maximum (okay, so I've just picked an arbitrary big number coz it may need to be packed up)
	//

	set_local_entity_float_value (member, FLOAT_TYPE_DISTANCE, 32000.0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void attach_group_to_guide_entity (entity *group, entity *guide)
{
	ASSERT (group);
	ASSERT (guide);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	//
	// guide stack
	//

	ASSERT (get_local_entity_parent (guide, LIST_TYPE_GUIDE_STACK) == NULL);

	insert_local_entity_into_parents_child_list (guide, LIST_TYPE_GUIDE_STACK, group, NULL);

	transmit_entity_comms_message (ENTITY_COMMS_SWITCH_LIST, guide, LIST_TYPE_GUIDE_STACK, group, LIST_TYPE_GUIDE_STACK);

	//
	// set-up guide criteria relevant to the group type
	//

	initialise_guide_criteria (guide);

	//
	// Set guide velocity with respect to the group type
	//
	{
		entity
			*wp,
			*member;

		float
			velocity;

		entity_sub_types
			group_type,
			waypoint_type;

		wp = get_local_entity_parent (guide, LIST_TYPE_CURRENT_WAYPOINT);

		ASSERT (wp);

		member = get_local_entity_first_child (group, LIST_TYPE_MEMBER);

		ASSERT (member);
		
		group_type = get_local_entity_int_value (group, INT_TYPE_ENTITY_SUB_TYPE);

		waypoint_type = get_local_entity_int_value (wp, INT_TYPE_ENTITY_SUB_TYPE);

		velocity = get_waypoint_database_velocity_value (waypoint_type, group_database [group_type].default_entity_type);

		velocity *= get_local_entity_float_value (member, FLOAT_TYPE_CRUISE_VELOCITY);

		set_client_server_entity_float_value (guide, FLOAT_TYPE_VELOCITY, velocity);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void delete_group_member_from_guide_entity (entity *member, entity *guide)
{
	unsigned int
		valid_members,
		member_number;
			
	ASSERT (member);
	ASSERT (guide);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	valid_members = get_local_entity_int_value (guide, INT_TYPE_VALID_GUIDE_MEMBERS);

	ASSERT (valid_members != TASK_ASSIGN_ALL_MEMBERS);

	member_number = (1 << get_local_entity_int_value (member, INT_TYPE_GROUP_MEMBER_NUMBER));
	
	ASSERT (valid_members & member_number);

	//
	// adjust guide valid members
	//

	valid_members &= (~member_number);

	//
	// if valid members empty - terminate the task (which will also destroy the guide)
	//

	if (!valid_members)
	{
		entity
			*task;

		task = get_local_entity_parent (guide, LIST_TYPE_GUIDE);

		ASSERT (task);
		
		#if DEBUG_MODULE

		debug_log ("GUIDE: Deleting %s (%d) from guide (%d) valid members zero - task %s (%d)",
							get_local_entity_string (member, STRING_TYPE_FULL_NAME),
							get_local_entity_index (member),
							get_local_entity_index (guide),
							get_local_entity_string (task, STRING_TYPE_FULL_NAME),
							get_local_entity_index (task));

		#endif

		notify_local_entity (ENTITY_MESSAGE_TASK_TERMINATED, task, NULL, TASK_TERMINATED_GROUP_DESTROYED);
	}
	else
	{
		set_client_server_entity_int_value (guide, INT_TYPE_VALID_GUIDE_MEMBERS, valid_members);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void delete_group_member_from_engage_guide (entity *member, entity *guide, int engage_enemy)
{
	entity
		*task,
		*group;

	unsigned int
		valid_members,
		member_number;
			
	ASSERT (member);
	ASSERT (guide);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	valid_members = get_local_entity_int_value (guide, INT_TYPE_VALID_GUIDE_MEMBERS);

	member_number = (1 << get_local_entity_int_value (member, INT_TYPE_GROUP_MEMBER_NUMBER));
	
	ASSERT (valid_members == member_number);

	group = get_local_entity_parent (guide, LIST_TYPE_GUIDE_STACK);

	ASSERT (group);

	task = get_local_entity_parent (guide, LIST_TYPE_GUIDE);

	ASSERT (task);

	ASSERT (get_local_entity_int_value (task, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_TASK_ENGAGE);
		
	destroy_client_server_entity (guide);

	reassign_group_members_to_valid_tasks (group, task, valid_members, engage_enemy);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_client_server_guide_entity_new_position (entity *en, vec3d *position, entity *position_entity)
{
	entity_sub_types
		sub_type;

	guide_position_types
		position_type;

	ASSERT (en);

	ASSERT (position);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	sub_type = get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE);
			
	//
	// set new position type
	//
	
	position_type = (guide_position_types) guide_database [sub_type].position_type;

	set_client_server_entity_int_value (en, INT_TYPE_GUIDE_POSITION_TYPE, position_type);

	//
	// set new position
	//
		
	if (guide_position_type_virtual [position_type])
	{
		//
		// Virtual Position
		//
		
		ASSERT (position_entity);

		set_client_server_entity_vec3d (en, VEC3D_TYPE_RELATIVE_POSITION, position);

		set_local_entity_ptr_value (en, PTR_TYPE_POSITION_ENTITY, position_entity);

		transmit_entity_comms_message (ENTITY_COMMS_SET_GUIDE_POSITION_ENTITY, en, position_entity);
	}
	else
	{
		//
		// Absolute Position
		//
		
		ASSERT (!position_entity);

		set_client_server_entity_vec3d (en, VEC3D_TYPE_POSITION, position);

		set_local_entity_ptr_value (en, PTR_TYPE_POSITION_ENTITY, NULL);

		transmit_entity_comms_message (ENTITY_COMMS_SET_GUIDE_POSITION_ENTITY, en, NULL);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *get_local_group_primary_guide (entity *en)
{
	entity
		*guide,
		*task,
		*primary_guide;

	entity_sub_types
		sub_type;

	int
		count;

	ASSERT (en);

	count = 0;

	primary_guide = NULL;

	guide = get_local_entity_first_child (en, LIST_TYPE_GUIDE_STACK);

	while (guide)
	{
		task = get_local_entity_parent (guide, LIST_TYPE_GUIDE);

		sub_type = get_local_entity_int_value (task, INT_TYPE_ENTITY_SUB_TYPE);

		if (task_database [sub_type].primary_task)
		{
			count ++;

			primary_guide = guide;

			//
			// could break out / return here, but keep going to check that there is only one primary task
			//								
		}

		guide = get_local_entity_child_succ (guide, LIST_TYPE_GUIDE_STACK);
	}

	ASSERT (count <= 1);

	return primary_guide;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *get_local_entity_primary_guide (entity *en)
{
	entity
		*group;

	ASSERT (en);

	group = get_local_entity_parent (en, LIST_TYPE_MEMBER);

	if (group)
	{
		return get_local_group_primary_guide (group);
	}
	else
	{
		return NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_local_guide_entity_pointers (entity *en, entity **aggressor, entity **waypoint, entity **task, entity **objective)
{
	entity
		*agg,
		*wp,
		*ts,
		*obj;

	ASSERT (en);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	agg = (entity *) get_local_entity_ptr_value (en, PTR_TYPE_TASK_LEADER);

	ASSERT (agg);

	wp = get_local_entity_parent (en, LIST_TYPE_CURRENT_WAYPOINT);

	ASSERT (wp);

	ts = get_local_entity_parent (en, LIST_TYPE_GUIDE);

	ASSERT (ts);

	obj = get_local_entity_parent (ts, LIST_TYPE_TASK_DEPENDENT);

	if (aggressor) *aggressor = agg;

	if (waypoint) *waypoint = wp;

	if (task) *task = ts;

	if (objective) *objective = obj;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_guide_required_heading (entity *en, entity *mobile, float *heading)
{
	ASSERT (en);

	ASSERT (mobile);

	ASSERT (heading);

	if (get_guide_criteria_valid (en, GUIDE_CRITERIA_HEADING))
	{
		entity
			*current_waypoint,
			*task,
			*target;

		current_waypoint = get_local_entity_parent (en, LIST_TYPE_CURRENT_WAYPOINT);
	
		ASSERT (current_waypoint);
	
		if (get_local_entity_int_value (current_waypoint, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_WAYPOINT_TARGET)
		{
			//
			// Target WP points towards target
			//
		
			vec3d
				*current_pos,
				*target_pos,
				target_vec;
	
			task = get_local_entity_parent (en, LIST_TYPE_GUIDE);
	
			ASSERT (task);
	
			target = get_local_entity_parent (task, LIST_TYPE_TASK_DEPENDENT);
	
			ASSERT (target);
	
			current_pos = get_local_entity_vec3d_ptr (mobile, VEC3D_TYPE_POSITION);
			
			target_pos = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

			if ((target_pos) && (current_pos))
			{
				//
				// SHOULD always be TRUE, but crash logs appear to show that this is not the case...
				//
				
				target_vec.x = target_pos->x - current_pos->x;
				target_vec.y = target_pos->y - current_pos->y;
				target_vec.z = target_pos->z - current_pos->z;
	
				*heading = (atan2 (target_vec.x, target_vec.z));
			}
			else
			{
				//
				// ... so use default heading specified in waypoint
				//
				
				*heading = get_local_entity_float_value (current_waypoint, FLOAT_TYPE_HEADING);
			}
			
			return TRUE;
		}
		else
		{
			//
			// Use heading value specified in waypoint
			//
						
			*heading = get_local_entity_float_value (current_waypoint, FLOAT_TYPE_HEADING);
	
			return TRUE;
		}
	}

	if (get_guide_criteria_valid (en, GUIDE_CRITERIA_WEAPON_VECTOR))
	{
		//
		// assume weapon is forward facing (for now)
		//

		entity_sub_types
			selected_weapon;

		vec3d
			weapon_vector,
			weapon_to_target_vector,
			perpendicular;

		float
			launch_angle_error;
			
		selected_weapon = get_local_entity_int_value (mobile, INT_TYPE_SELECTED_WEAPON);

		ASSERT (selected_weapon != ENTITY_SUB_TYPE_WEAPON_NO_WEAPON);

		if (get_local_entity_int_value (mobile, INT_TYPE_WEAPON_AND_TARGET_VECTORS_VALID))
		{
			//
			// get the heading difference between the weapon and the target
			//
	
			get_local_entity_vec3d (mobile, VEC3D_TYPE_WEAPON_VECTOR, &weapon_vector);
	
			weapon_vector.y = 0.0;
	
			get_local_entity_vec3d (mobile, VEC3D_TYPE_WEAPON_TO_TARGET_VECTOR, &weapon_to_target_vector);
	
			weapon_to_target_vector.y = 0.0;
	
			launch_angle_error = fabs (acos (get_3d_vector_dot_product (&weapon_vector, &weapon_to_target_vector)));
	
			//
			// find the sign of the angle by dot product with the perpendicular
			//
	
			perpendicular.x = weapon_vector.z;
			perpendicular.y = 0.0;
			perpendicular.z = -weapon_vector.x;
	
			if (get_3d_vector_dot_product (&perpendicular, &weapon_to_target_vector) < 0.0)
			{
				launch_angle_error = -launch_angle_error;
			}
	
//			debug_filtered_log ("GUIDE: Delta Heading = %f", deg (launch_angle_error));
	
			*heading = (get_local_entity_float_value (mobile, FLOAT_TYPE_HEADING) + launch_angle_error);
	
			return TRUE;
		}
		else
		{
			debug_log ("GUIDE: W/T vector invalid for %s (%d)", get_local_entity_string (mobile, STRING_TYPE_FULL_NAME), get_local_entity_index (mobile));
		}
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_guide_required_pitch (entity *en, entity *mobile, float *pitch)
{
	ASSERT (en);

	ASSERT (mobile);

	ASSERT (pitch);

	if (get_guide_criteria_valid (en, GUIDE_CRITERIA_WEAPON_VECTOR))
	{
		//
		// assume weapon is forward facing (for now)
		//

		entity_sub_types
			selected_weapon;

		vec3d
			*weapon_vector,
			*weapon_to_target_vector;

		float
			angle1,
			angle2,
			launch_angle_error;
			
		selected_weapon = get_local_entity_int_value (mobile, INT_TYPE_SELECTED_WEAPON);

		ASSERT (selected_weapon != ENTITY_SUB_TYPE_WEAPON_NO_WEAPON);

		if (get_local_entity_int_value (mobile, INT_TYPE_WEAPON_AND_TARGET_VECTORS_VALID))
		{
			//
			// get the pitch difference between the weapon and the target
			//
	
			weapon_vector = get_local_entity_vec3d_ptr (mobile, VEC3D_TYPE_WEAPON_VECTOR);
	
			weapon_to_target_vector = get_local_entity_vec3d_ptr (mobile, VEC3D_TYPE_WEAPON_TO_TARGET_VECTOR);
	
			angle1 = asin (weapon_vector->y);
	
			angle2 = asin (weapon_to_target_vector->y);
	
			launch_angle_error = angle2 - angle1; 
	
//			debug_filtered_log ("GUIDE: Delta Pitch = %f", deg (launch_angle_error));
	
			*pitch = (get_local_entity_float_value (mobile, FLOAT_TYPE_PITCH) + launch_angle_error);
	
			return TRUE;
		}
		else
		{
			debug_log ("GUIDE: W/T vector invalid for %s (%d)", get_local_entity_string (mobile, STRING_TYPE_FULL_NAME), get_local_entity_index (mobile));
		}
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_guide_criteria_valid (entity *en, guide_criteria_types type)
{
	guide
		*raw;

	ASSERT (en);

	ASSERT (type < NUM_GUIDE_CRITERIA_TYPES);

	raw = (guide *) get_local_entity_data (en);

	return raw->criteria [type].valid;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_guide_criteria_value (entity *en, guide_criteria_types type)
{
	guide
		*raw;

	ASSERT (en);

	ASSERT (type < NUM_GUIDE_CRITERIA_TYPES);

	raw = (guide *) get_local_entity_data (en);

	return raw->criteria [type].value;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_client_server_guide_criteria_valid (entity *en, guide_criteria_types type, int valid, float value)
{
	guide
		*raw;

	ASSERT (en);

	ASSERT (type < NUM_GUIDE_CRITERIA_TYPES);

	raw = (guide *) get_local_entity_data (en);

	if ((raw->criteria [type].valid != valid) || (raw->criteria [type].value != value))
	{
		set_local_guide_criteria_valid (en, type, valid, value);

		//
		// transmit comms message
		//

		transmit_entity_comms_message (ENTITY_COMMS_SET_GUIDE_CRITERIA, en, type, valid, value);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_local_guide_criteria_valid (entity *en, guide_criteria_types type, int valid, float value)
{
	guide
		*raw;

	ASSERT (en);

	ASSERT (type < NUM_GUIDE_CRITERIA_TYPES);

	raw = (guide *) get_local_entity_data (en);

	raw->criteria [type].valid = valid;
	raw->criteria [type].value = value;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_guide_criteria (entity *en)
{
	entity
		*current_wp,
		*group;

	entity_sub_types
		waypoint_type,
		group_type,
		guide_type;

	entity_types
		mobile_type;

	int
		loop_;

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	guide_type = get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE);

	//
	// get current waypoint
	//

	current_wp = get_local_entity_parent (en, LIST_TYPE_CURRENT_WAYPOINT);

	ASSERT (current_wp);

	waypoint_type = get_local_entity_int_value (current_wp, INT_TYPE_ENTITY_SUB_TYPE);

	//
	// get follower type
	//

	group = get_local_entity_parent (en, LIST_TYPE_GUIDE_STACK);

	ASSERT (group);

	group_type = get_local_entity_int_value (group, INT_TYPE_ENTITY_SUB_TYPE);

	mobile_type = group_database [group_type].default_entity_type;

	//
	// get values from GUIDE DATABASE
	//

	for (loop_ = 0; loop_ < NUM_GUIDE_CRITERIA_TYPES; loop_++)
	{
		guide_criteria_types
			loop;

		loop = (guide_criteria_types) loop_;

		if (guide_database [guide_type].criteria [loop].valid)
		{
			set_client_server_guide_criteria_valid (en, loop, TRUE, guide_database [guide_type].criteria [loop].value);
		}
		else
		{
			if (get_guide_criteria_valid (en, loop))
			{
				set_client_server_guide_criteria_valid (en, loop, FALSE, 0.0);
			}
		}
	}
	 
	//
	// get values from WAYPOINT DATABASE
	//

	set_client_server_guide_criteria_valid (en, GUIDE_CRITERIA_RADIUS, TRUE, get_waypoint_database_reached_radius_value (waypoint_type, mobile_type));

	set_client_server_guide_criteria_valid (en, GUIDE_CRITERIA_TRANSMIT_DATA, get_waypoint_database_transmit_recon_flag (waypoint_type, mobile_type), 0.0);

	set_client_server_guide_criteria_valid (en, GUIDE_CRITERIA_LAST_TO_REACH, get_waypoint_database_last_to_reach_flag (waypoint_type, mobile_type), 0.0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




