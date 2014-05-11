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



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "project.h"

#include "taskgen.h"

#include "../ai_misc/ai_route.h"
#include "../faction/popread.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// 2 levels of debug
//

#define DEBUG_MODULE 0

//
// set TASK_SAFE_LIMIT TO 0 TO DISABLE.
//

#define TASK_SAFE_LIMIT 					0

#define MAX_TROOP_ROUTE_COUNT 			16

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vec3d
   terminator_point = {-1.0, -1.0, -1.0};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int add_task_to_history (entity *new_task, entity *old_task);

float get_estimated_task_duration (entity *task);

static int get_task_start_keysite (entity_sub_types sub_type, entity_sides side, vec3d *start_pos, entity **start_keysite);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *create_task
			(
				entity_sub_types sub_type,
				entity_sides side,
				movement_types movement_type,
				entity *start_keysite,
				entity *end_keysite,
				entity *originator,
				int critical_task,
				float expire_timer,
				float stop_timer,
				entity *task_objective,
				float task_priority,
				...
			)
{

	int
		id,
		id_max,
		air_threats,
		enemy_sectors,
		route_length = 0;

	vec3d
		*position,
		*route_nodes,
		route_node_list [MAX_ROUTE_NODES];

	force
		*force_raw;

	sector
		*sec_raw;

	entity
		*sec,
		*force_en,
		*new_task,
		*dependent,
		**route_dependents,
		*route_dependent_list [MAX_ROUTE_NODES];

	entity_sub_types
		waypoint_type,
		formation_type,
		*route_waypoint_types,
		*route_formation_types,
		route_waypoint_type_list [MAX_ROUTE_NODES],
		route_formation_type_list [MAX_ROUTE_NODES];

	va_list
		pargs;

	int
		create_stack_attributes;

	debug_assert (get_comms_model () == COMMS_MODEL_SERVER);

	if (!validate_task_generation (side, sub_type))
	{
		debug_log ("TASKGEN: Can't create task %s", task_database [sub_type].full_name);

		return NULL;
	}

   #if DEBUG_MODULE >= 2

	if (sub_type == ENTITY_SUB_TYPE_TASK_ENGAGE)
	{

		if (task_objective)
		{

			debug_log ("TASK GENERATION: create task type %s, movement_type %s, objective %s", entity_sub_type_task_names [sub_type], movement_names [movement_type], entity_type_names [task_objective->type]);
		}
		else
		{

			debug_log ("TASK GENERATION: create task type %s, movement_type %s, objective NULL", entity_sub_type_task_names [sub_type], movement_names [movement_type]);
		}
	}

   #endif

	//////////////////////////////////////////////////////////////////
	//
	// Update counter
	//
	//////////////////////////////////////////////////////////////////

	force_en = get_local_force_entity (side);

	force_raw = (force *) get_local_entity_data (force_en);

	force_raw->task_generation [sub_type].created ++;

	//////////////////////////////////////////////////////////////////
	//
	// Read positions off stack
	//
	//////////////////////////////////////////////////////////////////

	va_start (pargs, task_priority);

	do
	{

		position = va_arg (pargs, vec3d *);

		dependent = va_arg (pargs, entity *);

		waypoint_type = va_arg (pargs, entity_sub_types);

		formation_type = va_arg (pargs, entity_sub_types);

		if (!position)
		{
			//
			// added so that cap tasks do not require all 4 waypoints to be valid
			//

			continue;
		}

		route_node_list [route_length].x = ceil (position->x);
		route_node_list [route_length].y = ceil (position->y);
		route_node_list [route_length].z = ceil (position->z);

		route_dependent_list [route_length] = dependent;

		route_waypoint_type_list [route_length] = waypoint_type;

		route_formation_type_list [route_length] = formation_type;

		#if DEBUG_MODULE >= 2

		if (dependent)
		{

			debug_log ("	pos %d = %f, %f, %f, dep %s", route_length + 1, position->x, position->y, position->z, entity_type_names [dependent->type]);
		}
		else
		{

			debug_log ("	pos %d = %f, %f, %f", route_length + 1, position->x, position->y, position->z);
		}

		#endif

		route_length ++;

		ASSERT (route_length < MAX_ROUTE_NODES);
	}
	//
	// Need to sort out position==NULL condition
	//
	while ((!position) || (!((position->x == terminator_point.x) && (position->y == terminator_point.y) && (position->z == terminator_point.z))));

	va_end (pargs);

	//////////////////////////////////////////////////////////////////
	//
	// Allocate route data
	//
	//////////////////////////////////////////////////////////////////

	route_nodes = (vec3d *) malloc_heap_mem (sizeof (vec3d) * route_length);
	memcpy (route_nodes, route_node_list, sizeof (vec3d) * route_length);

	route_dependents = (entity **) malloc_heap_mem (sizeof (entity *) * route_length);
	memcpy (route_dependents, route_dependent_list, sizeof (entity *) * route_length);

	route_waypoint_types = (entity_sub_types *) malloc_heap_mem (sizeof (entity_sub_types) * route_length);
	memcpy (route_waypoint_types, route_waypoint_type_list, sizeof (entity_sub_types) * route_length);

	route_formation_types = (entity_sub_types *) malloc_heap_mem (sizeof (entity_sub_types) * route_length);
	memcpy (route_formation_types, route_formation_type_list, sizeof (entity_sub_types) * route_length);

	// decreased by 1 so as not to include the terminator.

	route_length --;

	//////////////////////////////////////////////////////////////////
	//
	// determine task id number
	//
	//////////////////////////////////////////////////////////////////

	id = force_raw->task_generation [sub_type].created;

	id_max = (1 << NUM_TASK_ID_BITS) - 1;

	while (id > id_max)
	{
		id -= id_max;
	}

	//////////////////////////////////////////////////////////////////
	//
	// Create task
	//
	//////////////////////////////////////////////////////////////////

	create_stack_attributes = force_local_entity_create_stack_attributes;

	if (get_comms_data_flow () == COMMS_DATA_FLOW_RX)
	{
		set_force_local_entity_create_stack_attributes (TRUE);
	}

	new_task = create_client_server_entity
	(
		ENTITY_TYPE_TASK,
		ENTITY_INDEX_DONT_CARE,
		ENTITY_ATTR_PARENT (LIST_TYPE_TASK_DEPENDENT, task_objective),
		ENTITY_ATTR_INT_VALUE (INT_TYPE_ENTITY_SUB_TYPE, sub_type),
		ENTITY_ATTR_INT_VALUE (INT_TYPE_TASK_ID, id),
		ENTITY_ATTR_FLOAT_VALUE (FLOAT_TYPE_EXPIRE_TIMER, expire_timer),
		ENTITY_ATTR_FLOAT_VALUE (FLOAT_TYPE_TASK_PRIORITY, task_priority),
		ENTITY_ATTR_INT_VALUE (INT_TYPE_CRITICAL_TASK, critical_task),
		ENTITY_ATTR_INT_VALUE (INT_TYPE_MOVEMENT_TYPE, movement_type),
		ENTITY_ATTR_INT_VALUE (INT_TYPE_ROUTE_LENGTH, route_length),
		ENTITY_ATTR_INT_VALUE (INT_TYPE_SIDE, side),
		ENTITY_ATTR_END
	);

	ASSERT (new_task);

	set_force_local_entity_create_stack_attributes (create_stack_attributes);

	//////////////////////////////////////////////////////////////////
	//
	// Set stop time (if needed)
	//
	//////////////////////////////////////////////////////////////////

	if (stop_timer > 0.0)
	{
		set_client_server_entity_float_value (new_task, FLOAT_TYPE_STOP_TIMER, stop_timer);
	}

	//////////////////////////////////////////////////////////////////
	//
	// set local pointers (and comms message)
	//
	//////////////////////////////////////////////////////////////////

	set_local_entity_ptr_value (new_task, PTR_TYPE_ROUTE_DEPENDENTS, route_dependents);
	set_local_entity_ptr_value (new_task, PTR_TYPE_ROUTE_NODE, route_nodes);
	set_local_entity_ptr_value (new_task, PTR_TYPE_ROUTE_WAYPOINT_TYPES, route_waypoint_types);
	set_local_entity_ptr_value (new_task, PTR_TYPE_ROUTE_FORMATION_TYPES, route_formation_types);
	set_local_entity_ptr_value (new_task, PTR_TYPE_RETURN_KEYSITE, end_keysite);

	transmit_entity_comms_message (ENTITY_COMMS_SET_TASK_POINTERS, new_task);

	//////////////////////////////////////////////////////////////////
	//
	// Attach task to keysite (only if primary task)
	//
	//////////////////////////////////////////////////////////////////

	if (task_database [sub_type].primary_task)
	{
		ASSERT (start_keysite);
		
		set_client_server_entity_parent (new_task, LIST_TYPE_UNASSIGNED_TASK, start_keysite);
	}

	set_local_entity_int_value (new_task, INT_TYPE_TASK_DIFFICULTY, assess_task_difficulty (new_task, &air_threats, &enemy_sectors));

	//////////////////////////////////////////////////////////////////
	//
	// notify enemy force
	//
	//////////////////////////////////////////////////////////////////

	if (task_objective)
	{

		if (get_local_entity_int_value (task_objective, INT_TYPE_SIDE) != side)
		{

			entity
				*enemy_force;

			enemy_force = (entity*) get_local_force_entity ((entity_sides) get_local_entity_int_value (task_objective, INT_TYPE_SIDE));

			if (enemy_force)
			{

				notify_local_entity (ENTITY_MESSAGE_TASK_CREATED, enemy_force, new_task, task_objective);
			}
		}
	}
	
	//////////////////////////////////////////////////////////////////
	//
	// add task to sector task list
	//
	//////////////////////////////////////////////////////////////////

	position = NULL;

	if (task_objective)
	{
		position = get_local_entity_vec3d_ptr (task_objective, VEC3D_TYPE_POSITION);
	}

	if (!position)
	{
		position = &route_nodes [route_length - 1];
	}

	ASSERT (position);

	sec = get_local_sector_entity (position);

	ASSERT (sec);

	sec_raw = (sector *) get_local_entity_data (sec);

	insert_local_entity_into_parents_child_list (new_task, LIST_TYPE_SECTOR_TASK, sec, NULL);

   return new_task;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *create_anti_ship_strike_task (entity_sides side, entity *target, entity *originator, int critical, float priority, entity *start_keysite, entity *end_keysite)
{
	float
		expire_time;

	entity
		*new_task;

	vec3d
		*pos;

	entity
		*start_ks,
		*end_ks;

	new_task = NULL;

	debug_assert (get_comms_model () == COMMS_MODEL_SERVER);

	pos = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

	start_ks = start_keysite;
	end_ks = end_keysite;

	if (!get_task_start_keysite (ENTITY_SUB_TYPE_TASK_ANTI_SHIP_STRIKE, side, pos, &start_ks))
	{

		return NULL;
	}

	//
	// Create strike task
	//

	#if DEBUG_MODULE >= 2

	debug_log ("TASKGEN: creating side %d anti-ship strike task to keysite %s ", side, get_local_entity_string (target, STRING_TYPE_KEYSITE_NAME));

	#endif

	expire_time = 30 * ONE_MINUTE;

	new_task = create_task (ENTITY_SUB_TYPE_TASK_ANTI_SHIP_STRIKE,
									side,
									MOVEMENT_TYPE_AIR,
									start_ks,
									end_ks,
									originator,
									critical,
									expire_time,
									0.0,
									target,
									priority,
									pos, NULL, ENTITY_SUB_TYPE_WAYPOINT_ATTACK, FORMATION_ROW_LEFT,
									&terminator_point, NULL, NUM_ENTITY_SUB_TYPE_WAYPOINTS, FORMATION_NONE);

	if (new_task)
	{
		float
			efficiency;
			
		efficiency = get_local_entity_float_value (target, FLOAT_TYPE_EFFICIENCY);

		ASSERT (efficiency > 0.0);

		set_local_entity_float_value (new_task, FLOAT_TYPE_TASK_USER_DATA, efficiency);
	}

	return new_task;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *create_bai_task (entity_sides side, entity *target_group, entity *originator, int critical, float priority, entity *start_keysite, entity *end_keysite)
{
	vec3d
		*start_pos;

	float
		expire_time;

	entity
		*new_task;

	entity
		*start_ks,
		*end_ks;

	new_task = NULL;

	debug_assert (get_comms_model () == COMMS_MODEL_SERVER);

	ASSERT (target_group);

	//
	// Create BAI task
	//

	#if DEBUG_MODULE >= 2

	debug_log ("TASKGEN: creating side %d BAI task to %s (%d)", side, get_local_entity_string (target_group, STRING_TYPE_FULL_NAME), get_local_entity_index (target_group));

	#endif

	start_pos = get_local_entity_vec3d_ptr (target_group, VEC3D_TYPE_POSITION);

	start_ks = start_keysite;
	end_ks = end_keysite;

	if (!get_task_start_keysite (ENTITY_SUB_TYPE_TASK_BAI, side, start_pos, &start_ks))
	{

		return NULL;
	}

	expire_time = 20 * ONE_MINUTE;

	new_task = create_task (ENTITY_SUB_TYPE_TASK_BAI,
									side,
									MOVEMENT_TYPE_AIR,
									start_ks,
									end_ks,
									originator,
									critical,
									expire_time,
									0.0,
									target_group,
									priority,
									start_pos, NULL, ENTITY_SUB_TYPE_WAYPOINT_ATTACK, FORMATION_ROW_LEFT,
									&terminator_point, NULL, NUM_ENTITY_SUB_TYPE_WAYPOINTS, FORMATION_NONE);

	if (new_task)
	{
		float
			count;

		//
		// store current group member count
		//

		ASSERT (get_local_entity_type (target_group) == ENTITY_TYPE_GROUP);

		count = get_local_entity_int_value (target_group, INT_TYPE_MEMBER_COUNT);

		ASSERT (count > 0);

		set_local_entity_float_value (new_task, FLOAT_TYPE_TASK_USER_DATA, count);
	}

	return new_task;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *create_barcap_task (entity_sides side, entity *this_keysite, entity *originator, int critical, vec3d *centre_position, float priority, float duration, entity *start_keysite, entity *end_keysite)
{

	vec3d
		cap_position_list [4];

	float
		cap_distance,
		offset_angle,
		sin_angle,
		cos_angle,
		expire_time;

	entity
		*new_task;

	keysite
		*keysite_raw;

	entity
		*start_ks,
		*end_ks;

	new_task = NULL;

	debug_assert (get_comms_model () == COMMS_MODEL_SERVER);

	keysite_raw = (keysite *) get_local_entity_data (this_keysite);

	ASSERT (duration > 0.0);

	ASSERT (centre_position);

	//
	// find 4 air nodes around the stated position
	//

	cap_distance = (8 * KILOMETRE);

	offset_angle = sfrand1 () * PI;
	
	sin_angle = sin (offset_angle);
	cos_angle = cos (offset_angle);
	
	cap_position_list [0] = *centre_position;
	cap_position_list [1] = *centre_position;
	cap_position_list [2] = *centre_position;
	cap_position_list [3] = *centre_position;

	cap_position_list [0].x += (sin_angle * cap_distance);
	cap_position_list [0].y += 0.0;
	cap_position_list [0].z += (cos_angle * cap_distance);

	cap_position_list [1].x += (cos_angle * cap_distance);
	cap_position_list [1].y += 0.0;
	cap_position_list [1].z -= (sin_angle * cap_distance);

	cap_position_list [2].x -= (sin_angle * cap_distance);
	cap_position_list [2].y += 0.0;
	cap_position_list [2].z -= (cos_angle * cap_distance);

	cap_position_list [3].x -= (cos_angle * cap_distance);
	cap_position_list [3].y += 0.0;
	cap_position_list [3].z += (sin_angle * cap_distance);

	#if DEBUG_MODULE
	
	debug_log ("TASKGEN: cap pos %f, %f, %f", cap_position_list [0].x, cap_position_list [0].y, cap_position_list [0].z);
	debug_log ("TASKGEN: cap pos %f, %f, %f", cap_position_list [1].x, cap_position_list [1].y, cap_position_list [1].z);
	debug_log ("TASKGEN: cap pos %f, %f, %f", cap_position_list [2].x, cap_position_list [2].y, cap_position_list [2].z);
	debug_log ("TASKGEN: cap pos %f, %f, %f", cap_position_list [3].x, cap_position_list [3].y, cap_position_list [3].z);

	#endif

	//
	// create task
	//

	start_ks = start_keysite;
	end_ks = end_keysite;

	if (!get_task_start_keysite (ENTITY_SUB_TYPE_TASK_COMBAT_AIR_PATROL, side, &keysite_raw->position, &start_ks))
	{

		return NULL;
	}

	expire_time = 10 * ONE_MINUTE;

	new_task = create_task (ENTITY_SUB_TYPE_TASK_COMBAT_AIR_PATROL,
									side,
									MOVEMENT_TYPE_AIR,
									start_ks,
									end_ks,
									NULL,
									critical,
									expire_time,
									duration,
									this_keysite,
									priority,
									&cap_position_list [0], NULL, ENTITY_SUB_TYPE_WAYPOINT_CAP_START, FORMATION_ROW_LEFT,
									&cap_position_list [1], NULL, ENTITY_SUB_TYPE_WAYPOINT_NAVIGATION, FORMATION_ROW_LEFT,
									&cap_position_list [2], NULL, ENTITY_SUB_TYPE_WAYPOINT_NAVIGATION, FORMATION_ROW_LEFT,
									&cap_position_list [3], NULL, ENTITY_SUB_TYPE_WAYPOINT_CAP_LOOP, FORMATION_ROW_LEFT,
									&terminator_point, NULL, NUM_ENTITY_SUB_TYPE_WAYPOINTS, FORMATION_NONE);

	return new_task;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *create_bda_task (entity_sides side, entity *objective, entity *originator, int critical, float priority, entity *start_keysite, entity *end_keysite)
{

	float
		expire_time;

	entity
		*new_task;

	vec3d
		*pos;

	entity
		*start_ks,
		*end_ks;

	new_task = NULL;

	debug_assert (get_comms_model () == COMMS_MODEL_SERVER);

	#if DEBUG_MODULE >= 2

	debug_log ("TASKGEN: creating side %d BDA task to %s (%d)", side, get_local_entity_string (objective, STRING_TYPE_FULL_NAME), get_local_entity_index (objective));

	#endif

	ASSERT (objective);

	pos = get_local_entity_vec3d_ptr (objective, VEC3D_TYPE_POSITION);

	ASSERT (pos);

	start_ks = start_keysite;
	end_ks = end_keysite;

	if (!get_task_start_keysite (ENTITY_SUB_TYPE_TASK_BDA, side, pos, &start_ks))
	{

		return NULL;
	}

	//
	// Create BDA task
	//

	expire_time = 30 * ONE_MINUTE;

	new_task = create_task (ENTITY_SUB_TYPE_TASK_BDA,
									side,
									MOVEMENT_TYPE_AIR,
									start_ks,
									end_ks,
									originator,
									critical,
									expire_time,
									0.0,
									objective,
									priority,
									pos, NULL, ENTITY_SUB_TYPE_WAYPOINT_RECON, FORMATION_ROW_LEFT,
									&terminator_point, NULL, NUM_ENTITY_SUB_TYPE_WAYPOINTS, FORMATION_NONE);

	return new_task;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *create_cap_task (entity_sides side, entity *this_keysite, entity *originator, int critical, float priority, float duration, entity *start_keysite, entity *end_keysite)
{

	vec3d
		cap_position_list [4];

	float
		cap_distance,
		offset_angle,
		sin_angle,
		cos_angle,
		expire_time;

	entity
		*new_task;

	keysite
		*keysite_raw;

	entity
		*start_ks,
		*end_ks;

	new_task = NULL;

	debug_assert (get_comms_model () == COMMS_MODEL_SERVER);

	keysite_raw = (keysite *) get_local_entity_data (this_keysite);

	ASSERT (duration > 0.0);

	//
	// find 4 air nodes around the keysite
	//

	cap_distance = (8 * KILOMETRE);

	offset_angle = sfrand1 () * PI;

	sin_angle = sin (offset_angle);
	cos_angle = cos (offset_angle);
	
	cap_position_list [0] = keysite_raw->position;
	cap_position_list [1] = keysite_raw->position;
	cap_position_list [2] = keysite_raw->position;
	cap_position_list [3] = keysite_raw->position;

	cap_position_list [0].x += (sin_angle * cap_distance);
	cap_position_list [0].y += 0.0;
	cap_position_list [0].z += (cos_angle * cap_distance);

	bound_position_to_adjusted_map_area (&cap_position_list [0]);

	cap_position_list [1].x += (cos_angle * cap_distance);
	cap_position_list [1].y += 0.0;
	cap_position_list [1].z -= (sin_angle * cap_distance);

	bound_position_to_adjusted_map_area (&cap_position_list [1]);

	cap_position_list [2].x -= (sin_angle * cap_distance);
	cap_position_list [2].y += 0.0;
	cap_position_list [2].z -= (cos_angle * cap_distance);

	bound_position_to_adjusted_map_area (&cap_position_list [2]);

	cap_position_list [3].x -= (cos_angle * cap_distance);
	cap_position_list [3].y += 0.0;
	cap_position_list [3].z += (sin_angle * cap_distance);

	bound_position_to_adjusted_map_area (&cap_position_list [3]);

	#if DEBUG_MODULE
	
	debug_log ("TASKGEN: cap pos %f, %f, %f", cap_position_list [0].x, cap_position_list [0].y, cap_position_list [0].z);
	debug_log ("TASKGEN: cap pos %f, %f, %f", cap_position_list [1].x, cap_position_list [1].y, cap_position_list [1].z);
	debug_log ("TASKGEN: cap pos %f, %f, %f", cap_position_list [2].x, cap_position_list [2].y, cap_position_list [2].z);
	debug_log ("TASKGEN: cap pos %f, %f, %f", cap_position_list [3].x, cap_position_list [3].y, cap_position_list [3].z);

	#endif

	//
	// create task
	//

	start_ks = start_keysite;
	end_ks = end_keysite;

	if (!get_task_start_keysite (ENTITY_SUB_TYPE_TASK_COMBAT_AIR_PATROL, side, &keysite_raw->position, &start_ks))
	{

		return NULL;
	}

	expire_time = 10 * ONE_MINUTE;

	new_task = create_task (ENTITY_SUB_TYPE_TASK_COMBAT_AIR_PATROL,
									side,
									MOVEMENT_TYPE_AIR,
									start_ks,
									end_ks,
									NULL,
									critical,
									expire_time,
									duration,
									this_keysite,
									priority,
									&cap_position_list [0], NULL, ENTITY_SUB_TYPE_WAYPOINT_CAP_START, FORMATION_ROW_LEFT,
									&cap_position_list [1], NULL, ENTITY_SUB_TYPE_WAYPOINT_NAVIGATION, FORMATION_ROW_LEFT,
									&cap_position_list [2], NULL, ENTITY_SUB_TYPE_WAYPOINT_NAVIGATION, FORMATION_ROW_LEFT,
									&cap_position_list [3], NULL, ENTITY_SUB_TYPE_WAYPOINT_CAP_LOOP, FORMATION_ROW_LEFT,
									&terminator_point, NULL, NUM_ENTITY_SUB_TYPE_WAYPOINTS, FORMATION_NONE);

	return new_task;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *create_close_air_support_task (entity_sides side, entity *target_group, entity *originator, int critical, float priority, entity *start_keysite, entity *end_keysite)
{
	vec3d
		*start_pos;

	float
		expire_time;

	entity
		*new_task;

	entity
		*start_ks,
		*end_ks;

	new_task = NULL;

	debug_assert (get_comms_model () == COMMS_MODEL_SERVER);

	ASSERT (target_group);

	//
	// Create C.A.S. task
	//

	#if DEBUG_MODULE >= 2

	debug_log ("TASKGEN: creating side %d Close Air Support task to %s (%d)", side, get_local_entity_string (target_group, STRING_TYPE_FULL_NAME), get_local_entity_index (target_group));

	#endif

	start_pos = get_local_entity_vec3d_ptr (target_group, VEC3D_TYPE_POSITION);

	start_ks = start_keysite;
	end_ks = end_keysite;

	if (!get_task_start_keysite (ENTITY_SUB_TYPE_TASK_CLOSE_AIR_SUPPORT, side, start_pos, &start_ks))
	{

		return NULL;
	}

	expire_time = 20 * ONE_MINUTE;

	new_task = create_task (ENTITY_SUB_TYPE_TASK_CLOSE_AIR_SUPPORT,
									side,
									MOVEMENT_TYPE_AIR,
									start_ks,
									end_ks,
									originator,
									critical,
									expire_time,
									0.0,
									target_group,
									priority,
									start_pos, NULL, ENTITY_SUB_TYPE_WAYPOINT_ATTACK, FORMATION_ROW_LEFT,
									&terminator_point, NULL, NUM_ENTITY_SUB_TYPE_WAYPOINTS, FORMATION_NONE);

	if (new_task)
	{
		float
			count;

		//
		// store current group member count
		//

		ASSERT (get_local_entity_type (target_group) == ENTITY_TYPE_GROUP);

		count = get_local_entity_int_value (target_group, INT_TYPE_MEMBER_COUNT);

		ASSERT (count > 0);

		set_local_entity_float_value (new_task, FLOAT_TYPE_TASK_USER_DATA, count);
	}

	return new_task;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *create_coastal_patrol_task (entity_sides side, vec3d *source_position, vec3d *destination_position, float priority, entity *start_keysite, entity *end_keysite)
{

	entity
		*new_task;

	entity
		*start_ks,
		*end_ks;

	float
		expire_time;

	start_ks = start_keysite;
	end_ks = end_keysite;

	if (!get_task_start_keysite (ENTITY_SUB_TYPE_TASK_COASTAL_PATROL, side, source_position, &start_ks))
	{

		return NULL;
	}

	expire_time = 30.0 * ONE_MINUTE;

	new_task = create_task (ENTITY_SUB_TYPE_TASK_COASTAL_PATROL,
									side,
									MOVEMENT_TYPE_SEA,
									start_ks,
									end_ks,
									NULL,
									TRUE,
									expire_time,
									0.0,
									NULL,
									priority,
									source_position, NULL, ENTITY_SUB_TYPE_WAYPOINT_NAVIGATION, FORMATION_ROW_LEFT,
									destination_position, NULL, ENTITY_SUB_TYPE_WAYPOINT_END, FORMATION_ROW_LEFT,
									&terminator_point, NULL, NUM_ENTITY_SUB_TYPE_WAYPOINTS, FORMATION_NONE);

	return new_task;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *create_escort_task (entity *group, int critical, float priority, entity *start_keysite, entity *end_keysite)
{

	float
		expire_time;

	vec3d
		*start;

	entity
		*new_task;

	entity
		*start_ks,
		*end_ks;

	entity_sides
		side;

	ASSERT (group);

	ASSERT (get_local_entity_type (group) == ENTITY_TYPE_GROUP);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	new_task = NULL;

	expire_time = 15 * ONE_MINUTE;

	start = get_local_entity_vec3d_ptr (group, VEC3D_TYPE_POSITION);

	side = (entity_sides) get_local_entity_int_value (group, INT_TYPE_SIDE);

	start_ks = start_keysite;
	end_ks = end_keysite;

	if (!get_task_start_keysite (ENTITY_SUB_TYPE_TASK_ESCORT, side, start, &start_ks))
	{

		return NULL;
	}

	//
	// REACTIONARY TASK CREATION
	//

	new_task = create_task (ENTITY_SUB_TYPE_TASK_ESCORT,
									side,
									MOVEMENT_TYPE_AIR,
									start_ks,
									end_ks,
									group,
									critical,
									expire_time,
									0.0,
									group,
									priority,
									start, group, ENTITY_SUB_TYPE_WAYPOINT_ESCORT, FORMATION_ROW_LEFT,
									&terminator_point, NULL, NUM_ENTITY_SUB_TYPE_WAYPOINTS, FORMATION_NONE);

	if (new_task)
	{
		float
			count;

		//
		// store current group member count
		//

		ASSERT (get_local_entity_type (group) == ENTITY_TYPE_GROUP);

		count = get_local_entity_int_value (group, INT_TYPE_MEMBER_COUNT);

		ASSERT (count > 0);

		set_local_entity_float_value (new_task, FLOAT_TYPE_TASK_USER_DATA, count);
	}

//	#if DEBUG_MODULE

	debug_log ("TASKGEN: Created Escort Task (%d) for %s (%d)",
						get_local_entity_safe_index (new_task),
						get_local_entity_string (group, STRING_TYPE_FULL_NAME),
						get_local_entity_index (group));

//	#endif

	return new_task;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *create_ground_force_task (entity_sub_types type, entity *group, int from_node, int to_node, float priority, entity *start_keysite, entity *end_keysite)
{

	float
		expire_time;

	formation_types
		original_formation;

	entity
		*new_task,
		*member;

	vec3d
		*start,
		*stop;

	entity
		*start_ks,
		*end_ks;

	entity_sides
		side;

	new_task = NULL;

	side = (entity_sides) get_local_entity_int_value (group, INT_TYPE_SIDE);

	start = &road_node_positions [from_node];
	stop = &road_node_positions [to_node];

	start_ks = start_keysite;
	end_ks = end_keysite;

	if (!get_task_start_keysite (type, side, start, &start_ks))
	{

		return NULL;
	}

	expire_time = 12 * ONE_HOUR;

	member = get_local_entity_first_child (group, LIST_TYPE_MEMBER);

	original_formation = (formation_types) get_local_entity_int_value (group, INT_TYPE_GROUP_FORMATION);

	ASSERT (original_formation <= get_formation_database_count ());

	//
	// Reset members formation positions so they close-up the convoy if one of them is destroyed.
	//

	//set_local_group_member_formation_positions (group);

	// NB. check task frequency ?

	new_task = create_task (type,
									side,
									MOVEMENT_TYPE_GROUND,
									start_ks,
									end_ks,
									NULL,
									TRUE,
									expire_time,
									0.0,
									NULL,
									priority,
									start, NULL, ENTITY_SUB_TYPE_WAYPOINT_CONVOY, original_formation,
									start, NULL, ENTITY_SUB_TYPE_WAYPOINT_SUB_ROUTE_NAVIGATION, FORMATION_1,
									stop, NULL, ENTITY_SUB_TYPE_WAYPOINT_REVERSE_CONVOY, FORMATION_1,
									stop, NULL, ENTITY_SUB_TYPE_WAYPOINT_DEFEND, original_formation,
									&terminator_point, NULL, NUM_ENTITY_SUB_TYPE_WAYPOINTS, FORMATION_NONE);

	return new_task;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *create_ground_strike_task (entity_sides side, entity *target, entity *originator, int critical, float priority, entity *start_keysite, entity *end_keysite)
{

	float
		expire_time;

	entity
		*new_task;

	vec3d
		*pos;

	entity
		*start_ks,
		*end_ks;

	new_task = NULL;

	debug_assert (get_comms_model () == COMMS_MODEL_SERVER);

	pos = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

	start_ks = start_keysite;
	end_ks = end_keysite;

	if (!get_task_start_keysite (ENTITY_SUB_TYPE_TASK_GROUND_STRIKE, side, pos, &start_ks))
	{

		return NULL;
	}

	//
	// Create strike task
	//

	#if DEBUG_MODULE >= 2

	debug_log ("TASKGEN: creating side %d ground strike task to keysite %s ", side, get_local_entity_string (target, STRING_TYPE_KEYSITE_NAME));

	#endif

	expire_time = 40 * ONE_MINUTE;

	new_task = create_task (ENTITY_SUB_TYPE_TASK_GROUND_STRIKE,
									side,
									MOVEMENT_TYPE_AIR,
									start_ks,
									end_ks,
									originator,
									critical,
									expire_time,
									0.0,
									target,
									priority,
									pos, NULL, ENTITY_SUB_TYPE_WAYPOINT_ATTACK, FORMATION_ROW_LEFT,
									&terminator_point, NULL, NUM_ENTITY_SUB_TYPE_WAYPOINTS, FORMATION_NONE);

	if (new_task)
	{
		float
			efficiency;
			
		efficiency = get_local_entity_float_value (target, FLOAT_TYPE_EFFICIENCY);

		ASSERT (efficiency > 0.0);

		set_local_entity_float_value (new_task, FLOAT_TYPE_TASK_USER_DATA, efficiency);
	}

	return new_task;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *create_oca_strike_task (entity_sides side, entity *target, entity *originator, int critical, float priority, entity *start_keysite, entity *end_keysite)
{

	float
		expire_time;

	entity
		*new_task;

	vec3d
		*pos;

	entity
		*start_ks,
		*end_ks;

	new_task = NULL;

	debug_assert (get_comms_model () == COMMS_MODEL_SERVER);

	pos = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

	start_ks = start_keysite;
	end_ks = end_keysite;

	if (!get_task_start_keysite (ENTITY_SUB_TYPE_TASK_OCA_STRIKE, side, pos, &start_ks))
	{

		return NULL;
	}

	//
	// Create strike task
	//

	#if DEBUG_MODULE >= 2

	debug_log ("TASKGEN: creating side %d oca strike task to keysite %s ", side, get_local_entity_string (target, STRING_TYPE_KEYSITE_NAME));

	#endif

	expire_time = 30 * ONE_MINUTE;

	new_task = create_task (ENTITY_SUB_TYPE_TASK_OCA_STRIKE,
									side,
									MOVEMENT_TYPE_AIR,
									start_ks,
									end_ks,
									originator,
									critical,
									expire_time,
									0.0,
									target,
									priority,
									pos, NULL, ENTITY_SUB_TYPE_WAYPOINT_ATTACK, FORMATION_ROW_LEFT,
									&terminator_point, NULL, NUM_ENTITY_SUB_TYPE_WAYPOINTS, FORMATION_NONE);

	return new_task;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *create_oca_sweep_task (entity_sides side, entity *target, entity *originator, int critical, float priority, entity *start_keysite, entity *end_keysite)
{

	float
		expire_time;

	entity
		*new_task;

	vec3d
		*pos;

	entity
		*start_ks,
		*end_ks;

	new_task = NULL;

	debug_assert (get_comms_model () == COMMS_MODEL_SERVER);

	pos = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

	start_ks = start_keysite;
	end_ks = end_keysite;

	if (!get_task_start_keysite (ENTITY_SUB_TYPE_TASK_OCA_SWEEP, side, pos, &start_ks))
	{

		return NULL;
	}

	//
	// Create sweep task
	//

	#if DEBUG_MODULE >= 2

	debug_log ("TASKGEN: creating side %d oca sweep task to keysite %s ", side, get_local_entity_string (target, STRING_TYPE_KEYSITE_NAME));

	#endif

	expire_time = 30 * ONE_MINUTE;

	new_task = create_task (ENTITY_SUB_TYPE_TASK_OCA_SWEEP,
									side,
									MOVEMENT_TYPE_AIR,
									start_ks,
									end_ks,
									originator,
									critical,
									expire_time,
									0.0,
									target,
									priority,
									pos, NULL, ENTITY_SUB_TYPE_WAYPOINT_ATTACK, FORMATION_ROW_LEFT,
									&terminator_point, NULL, NUM_ENTITY_SUB_TYPE_WAYPOINTS, FORMATION_NONE);

	return new_task;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *create_recon_task (entity_sides side, entity *objective, entity *originator, int critical, float priority, entity *start_keysite, entity *end_keysite)
{

	float
		expire_time;

	entity
		*start_ks,
		*end_ks,
		*new_task;

	vec3d
		*pos;

	ASSERT (objective);

	pos = get_local_entity_vec3d_ptr (objective, VEC3D_TYPE_POSITION);

	start_ks = start_keysite;
	end_ks = end_keysite;

	if (!get_task_start_keysite (ENTITY_SUB_TYPE_TASK_RECON, side, pos, &start_ks))
	{

		return NULL;
	}

	new_task = NULL;

	debug_assert (get_comms_model () == COMMS_MODEL_SERVER);

	#if DEBUG_MODULE >= 2

	debug_log ("TASKGEN: creating side %d recon task to %s (%d)", side, get_local_entity_string (objective, STRING_TYPE_FULL_NAME), get_local_entity_index (objective));

	#endif

	ASSERT (pos);

	//
	// Create recon task
	//

	expire_time = 10 * ONE_MINUTE;

	new_task = create_task (ENTITY_SUB_TYPE_TASK_RECON,
									side,
									MOVEMENT_TYPE_AIR,
									start_ks,
									end_ks,
									originator,
									critical,
									expire_time,
									0.0,
									objective,
									priority,
									pos, NULL, ENTITY_SUB_TYPE_WAYPOINT_RECON, FORMATION_ROW_LEFT,
									&terminator_point, NULL, NUM_ENTITY_SUB_TYPE_WAYPOINTS, FORMATION_NONE);

	return new_task;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *create_repair_task (entity_sides side, vec3d *pos, entity *objective, float priority, entity *start_keysite, entity *end_keysite)
{

	entity
		*new_task;

	float
		expire_time;

	entity
		*start_ks,
		*end_ks;

	start_ks = start_keysite;
	end_ks = end_keysite;

	if (!get_task_start_keysite (ENTITY_SUB_TYPE_TASK_REPAIR, side, pos, &start_ks))
	{

		return NULL;
	}

	ASSERT (pos);

	expire_time = 30.0 * ONE_MINUTE;

	new_task = create_task (ENTITY_SUB_TYPE_TASK_REPAIR,
									side,
									MOVEMENT_TYPE_AIR,
									start_ks,
									end_ks,
									objective,
									TRUE,
									expire_time,
									0.0,
									objective,
									priority,
									pos, NULL, ENTITY_SUB_TYPE_WAYPOINT_NAVIGATION, FORMATION_ROW_LEFT,
									pos, NULL, ENTITY_SUB_TYPE_WAYPOINT_REPAIR, FORMATION_ROW_LEFT,
									&terminator_point, NULL, NUM_ENTITY_SUB_TYPE_WAYPOINTS, FORMATION_NONE);

	return new_task;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *create_sead_task (entity_sides side, entity *target, entity *originator, int critical, float priority, entity *start_keysite, entity *end_keysite)
{

	vec3d
		*start_pos;

	float
		expire_time;

	entity
		*new_task;

	entity
		*start_ks,
		*end_ks;

	new_task = NULL;

	ASSERT (target);

	debug_assert (get_comms_model () == COMMS_MODEL_SERVER);

	start_pos = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

	start_ks = start_keysite;
	end_ks = end_keysite;

	if (!get_task_start_keysite (ENTITY_SUB_TYPE_TASK_SEAD, side, start_pos, &start_ks))
	{

		return NULL;
	}

	//
	// Create SEAD task
	//

	#if DEBUG_MODULE >= 2

	debug_log ("TASKGEN: creating side %d SEAD task", side);

	#endif

	expire_time = 30 * ONE_MINUTE;

	new_task = create_task (ENTITY_SUB_TYPE_TASK_SEAD,
									side,
									MOVEMENT_TYPE_AIR,
									start_ks,
									end_ks,
									originator,
									critical,
									expire_time,
									0.0,
									target,
									priority,
									start_pos, NULL, ENTITY_SUB_TYPE_WAYPOINT_ATTACK, FORMATION_ROW_LEFT,
									&terminator_point, NULL, NUM_ENTITY_SUB_TYPE_WAYPOINTS, FORMATION_NONE);

	if (new_task)
	{
		float
			count;

		//
		// store current group member count
		//

		ASSERT (get_local_entity_type (target) == ENTITY_TYPE_GROUP);

		count = get_local_entity_int_value (target, INT_TYPE_MEMBER_COUNT);

		ASSERT (count > 0);

		set_local_entity_float_value (new_task, FLOAT_TYPE_TASK_USER_DATA, count);
	}

	return new_task;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *create_supply_task (entity *requester, entity *supplier, entity *cargo, movement_types movement_type, float priority, entity *start_keysite, entity *end_keysite)
{

	float
		expire_time;

	vec3d
		finish,
		prepare,
		direction,
		*start,
		*stop;

	entity_sides
		side;

	entity
		*new_task,
		*start_ks,
		*end_ks;

	new_task = NULL;

	stop = get_keysite_supply_position (requester);

	start = get_local_entity_vec3d_ptr (cargo, VEC3D_TYPE_POSITION);

	side = (entity_sides) get_local_entity_int_value (requester, INT_TYPE_SIDE);

	start_ks = start_keysite;
	end_ks = end_keysite;

	if (!get_task_start_keysite (ENTITY_SUB_TYPE_TASK_SUPPLY, side, start, &start_ks))
	{

		return NULL;
	}

	direction.x = stop->x - start->x;
	direction.y = stop->y - start->y;
	direction.z = stop->z - start->z;

	normalise_any_3d_vector (&direction);

	prepare.x = stop->x - (direction.x * 4.0 * KILOMETRE);
	prepare.z = stop->z - (direction.z * 4.0 * KILOMETRE);
	bound_position_to_adjusted_map_area (&prepare);

	finish.x = stop->x + (direction.x * 2.0 * KILOMETRE);
	finish.z = stop->z + (direction.z * 2.0 * KILOMETRE);
	bound_position_to_adjusted_map_area (&finish);

	expire_time = 20 * ONE_MINUTE;

	new_task = create_task (ENTITY_SUB_TYPE_TASK_SUPPLY,
											side,
											movement_type,
											start_ks,
											end_ks,
											NULL,
											TRUE,
											expire_time,
											0.0,
											requester,
											priority,
											start, supplier, ENTITY_SUB_TYPE_WAYPOINT_PICK_UP, FORMATION_ROW_LEFT,
											&prepare, NULL, ENTITY_SUB_TYPE_WAYPOINT_PREPARE_FOR_DROP_OFF, FORMATION_ROW_LEFT,
											stop, requester, ENTITY_SUB_TYPE_WAYPOINT_DROP_OFF, FORMATION_ROW_LEFT,
											&finish, NULL, ENTITY_SUB_TYPE_WAYPOINT_FINISH_DROP_OFF, FORMATION_ROW_LEFT,
											&terminator_point, NULL, NUM_ENTITY_SUB_TYPE_WAYPOINTS, FORMATION_NONE);

	set_local_entity_float_value (new_task, FLOAT_TYPE_TASK_USER_DATA, get_local_entity_int_value (cargo, INT_TYPE_ENTITY_SUB_TYPE));

	#if DEBUG_MODULE || DEBUG_SUPPLY

	debug_log ("TASKGEN: SUPPLY_INFO: create SUPPLY, movement_type %s from %s to %s",
					movement_names [movement_type],
					get_local_entity_string (supplier, STRING_TYPE_KEYSITE_NAME),
					get_local_entity_string (requester, STRING_TYPE_FULL_NAME));

	#endif

	return new_task;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *create_transfer_task (entity_sides side, entity_sub_types task_type, float priority, entity *start_keysite, entity *end_keysite)
{
	float
		expire_time;

	entity
		*new_task;

	entity
		//*landing_en,
		*start_ks,
		*end_ks;

	vec3d
		*keysite_position;

	new_task = NULL;

	debug_assert (get_comms_model () == COMMS_MODEL_SERVER);

	ASSERT (end_keysite);

	start_ks = start_keysite;
	end_ks = end_keysite;

	keysite_position = get_local_entity_vec3d_ptr (end_keysite, VEC3D_TYPE_POSITION);

	if (!get_task_start_keysite (task_type, side, keysite_position, &start_ks))
	{

		return NULL;
	}

	//
	// create task
	//

	#if DEBUG_MODULE >= 2

	debug_log ("TASKGEN: creating side %d Transfer task to keysite %s", side, get_local_entity_string (end_keysite, STRING_TYPE_KEYSITE_NAME));

	#endif

	expire_time = 10 * ONE_MINUTE;

	new_task = create_task (task_type,
									side,
									MOVEMENT_TYPE_AIR,
									start_ks,
									end_ks,
									NULL,
									TRUE,
									expire_time,
									0.0,
									end_ks,
									priority,
									keysite_position, end_ks, ENTITY_SUB_TYPE_WAYPOINT_NAVIGATION, FORMATION_ROW_LEFT,
									&terminator_point, NULL, NUM_ENTITY_SUB_TYPE_WAYPOINTS, FORMATION_NONE);

	return new_task;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *create_troop_insertion_task (entity_sides side, entity *destination_keysite, entity *originator, int critical, float priority, entity *start_keysite, entity *end_keysite)
{

	vec3d
		destination_position,
		destination_position_in_air;

	float
		heading,
		expire_time;

	entity
		*new_task;

	entity
		*start_ks,
		*end_ks;

	new_task = NULL;

	debug_assert (get_comms_model () == COMMS_MODEL_SERVER);

	start_ks = start_keysite;
	end_ks = end_keysite;

	get_keysite_troop_dropoff_position (destination_keysite, &destination_position, &heading);

	bound_position_to_adjusted_map_area (&destination_position);

	if (!get_task_start_keysite (ENTITY_SUB_TYPE_TASK_TROOP_INSERTION, side, &destination_position, &start_ks))
	{

		return NULL;
	}

	destination_position_in_air = destination_position;
	destination_position_in_air.x += 1.0;
	destination_position_in_air.y += 50.0;

	bound_position_to_adjusted_map_area (&destination_position_in_air);

	//
	// Create troop insertion task
	//

	#if DEBUG_MODULE >= 2

	debug_log ("TASKGEN: creating side %d troop insertion task to keysite %s %f, %f, %f", side, get_local_entity_string (destination_keysite, STRING_TYPE_KEYSITE_NAME),
					destination_position.x, destination_position.y, destination_position.z);

	#endif

	expire_time = 45 * ONE_MINUTE;

	new_task = create_task (ENTITY_SUB_TYPE_TASK_TROOP_INSERTION,
									side,
									MOVEMENT_TYPE_AIR,
									start_ks,
									end_ks,
									originator,
									critical,
									expire_time,
									0.0,
									destination_keysite,
									priority,
									&destination_position_in_air, destination_keysite, ENTITY_SUB_TYPE_WAYPOINT_NAVIGATION, FORMATION_ROW_LEFT,
									&destination_position, destination_keysite, ENTITY_SUB_TYPE_WAYPOINT_TROOP_INSERT, FORMATION_ROW_LEFT,
									&destination_position, NULL, ENTITY_SUB_TYPE_WAYPOINT_WAIT, FORMATION_ROW_LEFT,
									&destination_position_in_air, destination_keysite, ENTITY_SUB_TYPE_WAYPOINT_NAVIGATION, FORMATION_ROW_LEFT,
									&terminator_point, NULL, NUM_ENTITY_SUB_TYPE_WAYPOINTS, FORMATION_NONE);

	return new_task;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// Troop landing routes can be any length up to 16 points... the task generator deals with routes via the variable parameter list....
// only way to do it  - Guess I won't be going to heaven :(
//

//entity *create_troop_movement_capture_task (entity_sides side, vec3d *start_pos, entity *insert_task, entity *keysite, entity *helicopter)
//{
//
//	int
//		helicopter_count,
//		keysite_count,
//		loop,
//		count;
//
//	entity_sub_types
//		new_route_wp_type [MAX_TROOP_ROUTE_COUNT];
//
//	vec3d
//		*keysite_pos,
//		*helicopter_pos,
//		new_route [MAX_TROOP_ROUTE_COUNT],
//		*helicopter_route,
//		*keysite_route;
//
//	entity
//		*new_task;
//
//	// troops out of helicopter
//
//	helicopter_count = get_object_3d_troop_takeoff_route (get_local_entity_int_value (helicopter, INT_TYPE_OBJECT_3D_SHAPE), &helicopter_route);
//
//	if (helicopter_count)
//	{
//
//		helicopter_pos = get_local_entity_vec3d_ptr (helicopter, VEC3D_TYPE_POSITION);
//
//		// copy route across and assign positions in world coords and waypoint types
//		for (loop = 0; loop < helicopter_count; loop ++)
//		{
//	
//			//new_route [loop].x = helicopter_pos->x + helicopter_route [loop].x;
//			//new_route [loop].y = helicopter_pos->y + helicopter_route [loop].y;
//			//new_route [loop].z = helicopter_pos->z + helicopter_route [loop].z;
//			new_route [loop].x = helicopter_pos->x + (helicopter_route [(helicopter_count - 1) - loop].x * 2);
//			new_route [loop].y = helicopter_pos->y + (helicopter_route [(helicopter_count - 1) - loop].y * 1);
//			new_route [loop].z = helicopter_pos->z + (helicopter_route [(helicopter_count - 1) - loop].z * 2);
//	
//			new_route_wp_type [loop] = ENTITY_SUB_TYPE_WAYPOINT_NAVIGATION;
//		}
//	}
//
//	// troops from helicopter -> keysite
//
//	keysite_pos = get_local_entity_vec3d_ptr (keysite, VEC3D_TYPE_POSITION);
//
//	keysite_count = get_object_3d_troop_landing_route (get_local_entity_int_value (keysite, INT_TYPE_OBJECT_INDEX), &keysite_route);
//
//	if ((keysite_count) && (keysite_count < MAX_TROOP_ROUTE_COUNT))
//	{
//
//		for (loop = 0; loop < keysite_count; loop ++)
//		{
//	
//			new_route [helicopter_count + loop].x = keysite_pos->x + keysite_route [loop].x;
//			new_route [helicopter_count + loop].y = keysite_pos->y + keysite_route [loop].y;
//			new_route [helicopter_count + loop].z = keysite_pos->z + keysite_route [loop].z;
//	
//			new_route_wp_type [helicopter_count + loop] = ENTITY_SUB_TYPE_WAYPOINT_NAVIGATION;
//		}
//	}
//	else
//	{
//
//		keysite_count = 0;
//	
//		new_route [keysite_count + helicopter_count].x = keysite_pos->x;
//		new_route [keysite_count + helicopter_count].y = keysite_pos->y;
//		new_route [keysite_count + helicopter_count].z = keysite_pos->z;
//	
//		new_route_wp_type [keysite_count + helicopter_count] = ENTITY_SUB_TYPE_WAYPOINT_NAVIGATION;
//
//		keysite_count ++;
//	
//		new_route [keysite_count + helicopter_count].x = keysite_pos->x + 10.0;
//		new_route [keysite_count + helicopter_count].y = keysite_pos->y;
//		new_route [keysite_count + helicopter_count].z = keysite_pos->z;
//	
//		new_route_wp_type [keysite_count + helicopter_count] = ENTITY_SUB_TYPE_WAYPOINT_NAVIGATION;
//
//		keysite_count ++;
//	
//		new_route [keysite_count + helicopter_count].x = keysite_pos->x + 10.0;
//		new_route [keysite_count + helicopter_count].y = keysite_pos->y;
//		new_route [keysite_count + helicopter_count].z = keysite_pos->z + 10.0;
//	
//		new_route_wp_type [keysite_count + helicopter_count] = ENTITY_SUB_TYPE_WAYPOINT_NAVIGATION;
//
//		keysite_count ++;
//	}
//
//	count = helicopter_count + keysite_count;
//
//	ASSERT ((count > 0) && (count < MAX_TROOP_ROUTE_COUNT));
//
//	new_route_wp_type [helicopter_count - 1] = ENTITY_SUB_TYPE_WAYPOINT_TROOP_PUTDOWN_POINT;
//	new_route_wp_type [count - 1] = ENTITY_SUB_TYPE_WAYPOINT_TROOP_CAPTURE;
//
//	new_route [count] = terminator_point;
//
//	new_task = create_task (ENTITY_SUB_TYPE_TASK_TROOP_MOVEMENT_INSERT_CAPTURE,
//										side,
//										MOVEMENT_TYPE_GROUND,
//										keysite,
//										NULL,
//										insert_task,
//										TRUE,
//										0.0,
//										0.0,
//										insert_task,
//										task_database [ENTITY_SUB_TYPE_TASK_TROOP_MOVEMENT_INSERT_CAPTURE].task_priority,
//										&new_route [0], NULL, new_route_wp_type [0], FORMATION_1,
//										&new_route [1], NULL, new_route_wp_type [1], FORMATION_INFANTRY_COLUMN,
//										&new_route [2], NULL, new_route_wp_type [2], FORMATION_INFANTRY_COLUMN,
//										&new_route [3], NULL, new_route_wp_type [3], FORMATION_INFANTRY_COLUMN,
//										&new_route [4], NULL, new_route_wp_type [4], FORMATION_INFANTRY_COLUMN,
//										&new_route [5], NULL, new_route_wp_type [5], FORMATION_INFANTRY_COLUMN,
//										&new_route [6], NULL, new_route_wp_type [6], FORMATION_INFANTRY_COLUMN,
//										&new_route [7], NULL, new_route_wp_type [7], FORMATION_INFANTRY_COLUMN,
//										&new_route [8], NULL, new_route_wp_type [8], FORMATION_INFANTRY_COLUMN,
//										&new_route [9], NULL, new_route_wp_type [9], FORMATION_INFANTRY_COLUMN,
//										&new_route [10], NULL, new_route_wp_type [10], FORMATION_INFANTRY_COLUMN,
//										&new_route [11], NULL, new_route_wp_type [11], FORMATION_INFANTRY_COLUMN,
//										&new_route [12], NULL, new_route_wp_type [12], FORMATION_INFANTRY_COLUMN,
//										&new_route [13], NULL, new_route_wp_type [13], FORMATION_INFANTRY_COLUMN,
//										&new_route [14], NULL, new_route_wp_type [14], FORMATION_INFANTRY_COLUMN,
//										&new_route [15], NULL, new_route_wp_type [15], FORMATION_INFANTRY_COLUMN,
//										&terminator_point, NULL, NUM_ENTITY_SUB_TYPE_WAYPOINTS, FORMATION_NONE);
//
//	return new_task;
//}

// I think it will be better to make random movement - FARPs has too small routes, so capture happens right after troops insertion. 
// Troops moving around several minutes, there is will be a chance that they will be killed. Only after that capture calculation will be made.
// Looks like we all will burn in hell. Sincerely, thealx.

entity *create_troop_movement_capture_task (entity_sides side, vec3d *start_pos, entity *insert_task, entity *keysite, entity *helicopter)
{

	int
		loop,
		count;

	entity_sub_types
		new_route_wp_type [MAX_TROOP_ROUTE_COUNT];

	vec3d
		*helicopter_pos,
		new_route [MAX_TROOP_ROUTE_COUNT],
		*helicopter_route;

	float heading_offset = 0;
	
	matrix3x3
		helicopter_att;
	
	entity
		*new_task;

	// troops out of helicopter

	count = get_object_3d_troop_takeoff_route (get_local_entity_int_value (helicopter, INT_TYPE_OBJECT_3D_SHAPE), &helicopter_route) - 1;

	switch (get_local_entity_int_value (helicopter, INT_TYPE_ENTITY_SUB_TYPE))
	{
		case ENTITY_SUB_TYPE_AIRCRAFT_KA29_HELIX_B:
		case ENTITY_SUB_TYPE_AIRCRAFT_MI17_HIP:
		{
			heading_offset = rad(-55);
			break;
		}
		case ENTITY_SUB_TYPE_AIRCRAFT_CH46E_SEA_KNIGHT:
		case ENTITY_SUB_TYPE_AIRCRAFT_CH3_JOLLY_GREEN_GIANT:
		case ENTITY_SUB_TYPE_AIRCRAFT_CH47D_CHINOOK:
		case ENTITY_SUB_TYPE_AIRCRAFT_MI6_HOOK:
		case ENTITY_SUB_TYPE_AIRCRAFT_MV22_OSPREY:
		case ENTITY_SUB_TYPE_AIRCRAFT_CH53E_SUPER_STALLION:
		{
			heading_offset = rad(-75);
			break;
		}
	}

	helicopter_pos = get_local_entity_vec3d_ptr (helicopter, VEC3D_TYPE_POSITION);
	get_local_entity_attitude_matrix(helicopter, helicopter_att);
	get_3d_transformation_heading_matrix(helicopter_att, wrap_angle(get_heading_from_attitude_matrix(helicopter_att) + heading_offset));
	
	if (count > 0)
	{
		// copy route across and assign positions in world coords and waypoint types
		for (loop = 0; loop <= count; loop ++)
		{
			helicopter_route [count - loop].x *= 1.5;
			helicopter_route [count - loop].z *= 1.5;
			multiply_matrix3x3_vec3d(&helicopter_route [count - loop], helicopter_att, &helicopter_route [count - loop]);			
			new_route [loop].x = helicopter_pos->x + helicopter_route [count - loop].x;
			new_route [loop].z = helicopter_pos->z + helicopter_route [count - loop].z;

			ASSERT(point_inside_map_area(&new_route [loop]));
	
			new_route [loop].y = get_3d_terrain_elevation(new_route [loop].x, new_route [loop].z);
			new_route_wp_type [loop] = ENTITY_SUB_TYPE_WAYPOINT_NAVIGATION;
		}
	}
	else
	{
		debug_fatal("Can't find proper troops take off route for aircraft %i", get_local_entity_int_value (helicopter, INT_TYPE_ENTITY_SUB_TYPE));
	}

	// troops from helicopter -> keysite
	
	for (; loop < MAX_TROOP_ROUTE_COUNT; loop ++)
	{
		new_route [loop].x = new_route [loop - 1].x + 50 * sfrand1();
		new_route [loop].z = new_route [loop - 1].z + 50 * sfrand1();

		ASSERT(point_inside_map_area(&new_route [loop]));
	
		new_route [loop].y = get_3d_terrain_elevation(new_route [loop].x, new_route [loop].z);

		new_route_wp_type [loop] = ENTITY_SUB_TYPE_WAYPOINT_NAVIGATION;
	}

	ASSERT (loop - 1 < MAX_TROOP_ROUTE_COUNT);

	new_route_wp_type [count] = ENTITY_SUB_TYPE_WAYPOINT_TROOP_PUTDOWN_POINT;
	new_route_wp_type [loop - 1] = ENTITY_SUB_TYPE_WAYPOINT_TROOP_CAPTURE;

	new_task = create_task (ENTITY_SUB_TYPE_TASK_TROOP_MOVEMENT_INSERT_CAPTURE,
										side,
										MOVEMENT_TYPE_GROUND,
										keysite,
										NULL,
										insert_task,
										TRUE,
										0.0,
										0.0,
										insert_task,
										task_database [ENTITY_SUB_TYPE_TASK_TROOP_MOVEMENT_INSERT_CAPTURE].task_priority,
										&new_route [0], NULL, new_route_wp_type [0], FORMATION_INFANTRY_COLUMN,
										&new_route [1], NULL, new_route_wp_type [1], FORMATION_INFANTRY_COLUMN,
										&new_route [2], NULL, new_route_wp_type [2], FORMATION_INFANTRY_COLUMN,
										&new_route [3], NULL, new_route_wp_type [3], FORMATION_INFANTRY_COLUMN,
										&new_route [4], NULL, new_route_wp_type [4], FORMATION_INFANTRY_COLUMN,
										&new_route [5], NULL, new_route_wp_type [5], FORMATION_INFANTRY_COLUMN,
										&new_route [6], NULL, new_route_wp_type [6], FORMATION_INFANTRY_COLUMN,
										&new_route [7], NULL, new_route_wp_type [7], FORMATION_INFANTRY_COLUMN,
										&new_route [8], NULL, new_route_wp_type [8], FORMATION_INFANTRY_COLUMN,
										&new_route [9], NULL, new_route_wp_type [9], FORMATION_INFANTRY_COLUMN,
										&new_route [10], NULL, new_route_wp_type [10], FORMATION_INFANTRY_COLUMN,
										&new_route [11], NULL, new_route_wp_type [11], FORMATION_INFANTRY_COLUMN,
										&new_route [12], NULL, new_route_wp_type [12], FORMATION_INFANTRY_COLUMN,
										&new_route [13], NULL, new_route_wp_type [13], FORMATION_INFANTRY_COLUMN,
										&new_route [14], NULL, new_route_wp_type [14], FORMATION_INFANTRY_COLUMN,
										&new_route [15], NULL, new_route_wp_type [15], FORMATION_INFANTRY_COLUMN,
										&terminator_point, NULL, NUM_ENTITY_SUB_TYPE_WAYPOINTS, FORMATION_NONE);

	return new_task;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *create_troop_movement_defend_task (entity_sides side, vec3d *start_pos, vec3d *mid_pos, vec3d *end_pos, entity *insert_task, entity *keysite)
{

	vec3d
		mid2_pos;

	entity
		*new_task;

	mid2_pos = *mid_pos;
	mid2_pos.x += 0.1;

	new_task = create_task (ENTITY_SUB_TYPE_TASK_TROOP_MOVEMENT_INSERT_DEFEND,
										side,
										MOVEMENT_TYPE_GROUND,
										keysite,
										NULL,
										insert_task,
										TRUE,
										0.0,
										0.0,
										insert_task,
										task_database [ENTITY_SUB_TYPE_TASK_TROOP_MOVEMENT_INSERT_DEFEND].task_priority,
										start_pos, NULL, ENTITY_SUB_TYPE_WAYPOINT_NAVIGATION, FORMATION_1,
										&mid2_pos, NULL, ENTITY_SUB_TYPE_WAYPOINT_TROOP_PUTDOWN_POINT, FORMATION_1,
										mid_pos, NULL, ENTITY_SUB_TYPE_WAYPOINT_NAVIGATION, FORMATION_INFANTRY_COLUMN,
										end_pos, NULL, ENTITY_SUB_TYPE_WAYPOINT_TROOP_DEFEND, FORMATION_INFANTRY_COLUMN,
										&terminator_point, NULL, NUM_ENTITY_SUB_TYPE_WAYPOINTS, FORMATION_NONE);

	return new_task;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *create_troop_movement_patrol_task (entity_sides side, entity *keysite)
{

	vec3d
		pos;

	entity
		*new_task;

	get_keysite_takenoff_position (keysite, &pos, ENTITY_SUB_TYPE_LANDING_PEOPLE);

	new_task = create_task (ENTITY_SUB_TYPE_TASK_TROOP_MOVEMENT_PATROL,
										side,
										MOVEMENT_TYPE_GROUND,
										keysite,
										keysite,
										NULL,
										TRUE,
										0.0,
										0.0,
										keysite,
										task_database [ENTITY_SUB_TYPE_TASK_TROOP_MOVEMENT_PATROL].task_priority,
										&pos, keysite, ENTITY_SUB_TYPE_WAYPOINT_LAND, FORMATION_1,
										&terminator_point, NULL, NUM_ENTITY_SUB_TYPE_WAYPOINTS, FORMATION_NONE);

	return new_task;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *create_user_task (entity *en, entity_sub_types task_type, vec3d *start_pos, entity *start_keysite, entity *end_keysite)
{

	entity
		*group,
		*keysite,
		*new_task;

	float
		expire_time;

	entity_sub_types
		stop_waypoint_type;

	vec3d
		direction,
		stop;

	entity
		*start_ks,
		*end_ks;

	entity_sides
		side;

	side = (entity_sides) get_local_entity_int_value (en, INT_TYPE_SIDE);

	start_ks = start_keysite;
	end_ks = end_keysite;

	if (!get_task_start_keysite (task_type, side, start_pos, &start_ks))
	{

		return NULL;
	}

	switch (task_type)
	{

		case ENTITY_SUB_TYPE_TASK_RECON:
		{

			stop_waypoint_type = ENTITY_SUB_TYPE_WAYPOINT_RECON;

			break;
		}
		case ENTITY_SUB_TYPE_TASK_GROUND_STRIKE:
		{

			stop_waypoint_type = ENTITY_SUB_TYPE_WAYPOINT_ATTACK;

			break;
		}
		case ENTITY_SUB_TYPE_TASK_CLOSE_AIR_SUPPORT:
		{

			stop_waypoint_type = ENTITY_SUB_TYPE_WAYPOINT_ATTACK;

			break;
		}
		case ENTITY_SUB_TYPE_TASK_SEAD:
		{

			stop_waypoint_type = ENTITY_SUB_TYPE_WAYPOINT_ATTACK;

			break;
		}
		case ENTITY_SUB_TYPE_TASK_TRANSFER_HELICOPTER:
		{

			stop_waypoint_type = ENTITY_SUB_TYPE_WAYPOINT_END;

			break;
		}
		case ENTITY_SUB_TYPE_TASK_COMBAT_AIR_PATROL:
		{

			//new_task = create_cap_task (get_local_entity_int_value (en, INT_TYPE_SIDE), get_base_current_keysite (), NULL);

			return NULL;
		}
		default:
		{

			stop_waypoint_type = ENTITY_SUB_TYPE_WAYPOINT_END;

			break;
		}
	}

	if (get_game_type () == GAME_TYPE_FREE_FLIGHT)
	{

		stop_waypoint_type = ENTITY_SUB_TYPE_WAYPOINT_IMPOSSIBLE;
	}

	expire_time = 3 * ONE_MINUTE;

	// move stop position towards the centre of the map

	direction.x = MID_MAP_X - start_pos->x;
	direction.z = MID_MAP_Z - start_pos->z;

	direction.x /= fabs (direction.x);
	direction.z /= fabs (direction.z);

	stop = *start_pos;

	stop.x += direction.x * 10 * KILOMETRE;
	stop.z += direction.z * 10 * KILOMETRE;

	group = get_local_entity_parent (en, LIST_TYPE_MEMBER);

	ASSERT (group);

	keysite = get_local_entity_parent (group, LIST_TYPE_KEYSITE_GROUP);

	new_task = create_task (task_type,
									side,
									MOVEMENT_TYPE_AIR,
									start_ks,
									end_ks,
									NULL,
									FALSE,
									expire_time,
									0.0,
									NULL,
									1.0,
									&stop, NULL, stop_waypoint_type, FORMATION_ROW_LEFT,
									&terminator_point, NULL, NUM_ENTITY_SUB_TYPE_WAYPOINTS, FORMATION_NONE);

	return new_task;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Debug task generation functions
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Task service functions
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int validate_task_generation (entity_sides side, entity_sub_types sub_type)
{
	return TRUE;

	#if 0

	entity
		*this_force;

	force
		*raw;

	#if TASK_SAFE_LIMIT
	{

		int
			task_count;

		entity
			*task;

		task_count = 0;

		task = get_local_entity_first_child (get_session_entity (), task_database [sub_type].list_type);

		while (task)
		{

			task_count ++;

			task = task->task_data->task_link.child_succ;
		}

		if (task_count > TASK_SAFE_LIMIT)
		{

			debug_log ("TASKGEN: WARNING ! CURRENTLY %d %s TASKS ALIVE", task_count, entity_sub_type_task_names [sub_type]);

			return FALSE;
		}
	}
	#endif

	this_force = get_local_force_entity (side);

	if (this_force)
	{

		raw = get_local_entity_data (this_force);

		if (raw->task_generation [sub_type].valid)
		{

			return TRUE;
		}
	}

	return FALSE;

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_estimated_task_duration (entity *task_en)
{

	entity
		*wp;

	vec3d
		*wp_pos2,
		*wp_pos1;

	float
		time,
		range;

	task
		*task_raw;

	range = 0;

	task_raw = (task *) get_local_entity_data (task_en);

	wp = task_raw->waypoint_root.first_child;

	if (wp)
	{

		wp_pos1 = get_local_entity_vec3d_ptr (wp, VEC3D_TYPE_POSITION);

		wp = get_local_entity_child_succ (wp, LIST_TYPE_WAYPOINT);

		while (wp)
		{

			wp_pos2 = get_local_entity_vec3d_ptr (wp, VEC3D_TYPE_POSITION);

			range += get_approx_2d_range (wp_pos1, wp_pos2);

			wp_pos1 = wp_pos2;

			wp = get_local_entity_child_succ (wp, LIST_TYPE_WAYPOINT);
		}
	}
	else
	{
/*
		int
			loop,
			length;

		vec3d
			*nodes,
			*route,
			*keysite_pos,
			temp_nodes [50];

		//
		// Create vec3d route for task. Not assigned yet as user is only looking !
		//

		nodes = get_local_entity_vec3d_ptr (task_en, VEC3D_TYPE_START_POSITION);

		length = get_local_entity_int_value (task_en, INT_TYPE_ROUTE_LENGTH);

		if (!get_base_current_keysite ())
		{

			return 0.0;
		}

		keysite_pos = get_local_entity_vec3d_ptr (get_base_current_keysite (), VEC3D_TYPE_POSITION);
		temp_nodes [0] = *keysite_pos;

		memcpy (&temp_nodes [1], nodes, sizeof (vec3d) * length);

		temp_nodes [length + 1].x = -1.0;
		temp_nodes [length + 1].y = -1.0;
		temp_nodes [length + 1].z = -1.0;

		build_calculated_air_vec3d_route (temp_nodes, &length, &route, get_global_gunship_side ());

		range = 0.0;

		for (loop = 0; loop < length - 1; loop ++)
		{

			if ( ( route [loop+1].x == -1 ) && ( route [loop+1].z == -1 ) )
			{

				break;
			}

			range += get_approx_2d_range (&route [loop], &route [loop + 1]);
		}
		*/
	}

	time = range / knots_to_metres_per_second (60.0); // average speed

	return time;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void display_task_generation_stats (entity *force_en)
{
	int
		loop;

	force
		*force_raw;

	//suppress_debug_log_timing_info (TRUE);

	force_raw = (force *)get_local_entity_data (force_en);

	debug_log ("======================================================================================");
	debug_log ("TASK GENERATION STATISTICS");
	debug_log ("======================================================================================");

	debug_log (" %s: created	completed failed,	total_created", entity_side_names [force_raw->side]);

	for (loop = 0; loop < NUM_ENTITY_SUB_TYPE_TASKS; loop ++)
	{


		debug_log ("				%d			%d				%d				%d  %s",
						force_raw->task_generation [loop].created,
						force_raw->task_generation [loop].completed,
						force_raw->task_generation [loop].failed,
						force_raw->task_generation [loop].created,
						entity_sub_type_task_names [loop]);
	}

	debug_log ("======================================================================================");

	//suppress_debug_log_timing_info (FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_task_start_keysite (entity_sub_types sub_type, entity_sides side, vec3d *start_pos, entity **start_keysite)
{
	ASSERT (start_keysite);

	if (task_database [sub_type].primary_task)
	{
		if (!(*start_keysite))
		{
			//
			// Keysite not specified - so find best suited
			//
			
			if (task_database [sub_type].landing_types & (1 <<ENTITY_SUB_TYPE_LANDING_GROUND))
			{
				*start_keysite = find_most_suitable_keysite_for_task (sub_type, side, start_pos, FALSE);
			}
			else
			{
				*start_keysite = find_most_suitable_keysite_for_task (sub_type, side, start_pos, TRUE);
			}

			if (!*start_keysite)
			{
				//
				// No suitable keysite found - abort task creation
				//

				return FALSE;
			}
		}
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////







