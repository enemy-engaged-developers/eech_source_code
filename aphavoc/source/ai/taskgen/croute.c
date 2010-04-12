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



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "project.h"

#include "croute.h"

#include "../ai_misc/ai_misc.h"
#include "../ai_misc/ai_route.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 2 levels of debug

#define DEBUG_MODULE 0

int debug_flag = FALSE;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
	assign_create_waypoint_route;

vec3d
	best_vec3d_route [MAX_ROUTE_LENGTH];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct ROUTE_BIASING_DATABASE_TYPE
{

	float
		elevation_bias,
		range_bias,
		side_bias,
		min_route_range,
		route_deviation_size,
		num_route_samples,
		optimise_tolerance;
};

typedef struct ROUTE_BIASING_DATABASE_TYPE route_biasing_database_type;

route_biasing_database_type
	route_biasing_database [] =
	{
		//MOVEMENT_TYPE_NONE,
		{
			1.0,			// elevation bias
			1.0,			// range bias
			1.0,			// side bias
			5000.0,		// min route range
			3.0,			// route deviation size
			8.0,			// num route samples
			0.94f,			// optimise tolerance
		},
		//MOVEMENT_TYPE_AIR,
		{
			5.0,			// elevation bias
			0.5,			// range bias
			1.0,			// side bias
			5000.0,		// min route range
			3.0,			// route deviation size
			8.0,			// num route samples
			0.94f,			// optimise tolerance
		},
		//MOVEMENT_TYPE_GROUND,
		{
			1.0,			// elevation bias
			1.0,			// range bias
			1.0,			// side bias
			5000.0,		// min route range
			3.0,			// route deviation size
			8.0,			// num route samples
			0.94f,			// optimise tolerance
		},
		//MOVEMENT_TYPE_SEA,
		{
			9999.0,		// elevation bias
			0.1f,			// range bias
			1.0,			// side bias
			5000.0,		// min route range
			2.0,			// route deviation size
			6.0,			// num route samples
			0.94f,			// optimise tolerance
		},
		//MOVEMENT_TYPE_ALL,
		{
			1.0,			// elevation bias
			1.0,			// range bias
			1.0,			// side bias
			5000.0,		// min route range
			3.0,			// route deviation size
			8.0,			// num route samples
			0.94f,			// optimise tolerance
		}
	};

float
	*best_point_terrain_elevations;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

route_node
	*fast_route;

static route_node *create_route (vec3d *start, vec3d *end, entity_sides side, movement_types movement_type);

static void optimise_route (route_node *node, movement_types movement_type);

static int generate_best_mid_point (route_node *start_node, route_node *end_node, entity_sides side, movement_types movement_type);

static int get_best_point (vec3d *start, vec3d *end, vec3d *best_point, entity_sides side, movement_types movement_type);

static void second_past_route (route_node *route, entity_sides side, movement_types movement_type);

static float get_route_point_rating (float sample_number, vec3d *test_point, entity_sides side, movement_types movement_type);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void parser_task_waypoint_route (entity *group, entity *task);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int create_generic_waypoint_route (entity *group, entity *task_en, entity *return_keysite, vec3d *client_start, vec3d *client_stop, unsigned int *waypoint_indices, int indices_count)
{

	route_node
		*new_node,
		*new_route,
		*specified_route,
		*specified_route_ptr,
		*last_specified_node;

	movement_types
		movement_type;

	entity_types
		task_route_type;

	entity_sub_types
		landing_type;

	vec3d
		stop,
		start,
		*stop_ptr,
		*start_ptr,
		*waypoint_pos,
		*route_points_ptr;

	int
		loop,
		index,
		road_node,
		check_sum,
		node_count,
		route_length,
		generate_route,
		start_point_count,
		create_stack_attributes;
	
	entity_sides
		side;
  	
	float
		mb_vel,
		height,
		flight_time = 0,
		terrain_elevation;

	entity
		*wp,
		*member,
		*last_wp,
		**route_dependents_ptr;

	entity_sub_types
		*route_waypoint_types_ptr;

	formation_types
		*route_formation_types_ptr;

	ASSERT (group);

	ASSERT (task_en);

	#if DEBUG_MODULE
	if (debug_flag)
	{
	
		debug_log ("CROUTE: ===================================================================================");
	
		debug_log ("CROUTE: Creating route for task %s (%d), movement type %s",
						get_local_entity_string (task_en, STRING_TYPE_FULL_NAME),
						get_local_entity_index (task_en),
						movement_names [get_local_entity_int_value (task_en, INT_TYPE_MOVEMENT_TYPE)]);
	
	}
	#endif

	if (get_local_entity_first_child (task_en, LIST_TYPE_WAYPOINT))
	{
	
		#if DEBUG_MODULE
		if (debug_flag)
		{
	
			debug_log ("CROUTE:     Task %s already has waypoint route", get_local_entity_string (task_en, STRING_TYPE_FULL_NAME));
			
			debug_log ("CROUTE: ===================================================================================");
	
		}
		#endif
	
		return TRUE;
	}

	// set stack attirbutes

	create_stack_attributes = force_local_entity_create_stack_attributes;

	if (get_comms_data_flow () == COMMS_DATA_FLOW_RX)
	{

		set_force_local_entity_create_stack_attributes (TRUE);
	}
	
	//////////////////////////////////////////////////////////////////
	//
	// Sort route generation type
	//
	//////////////////////////////////////////////////////////////////

	member = get_local_entity_first_child (group, LIST_TYPE_MEMBER);

	ASSERT (member);

	side = (entity_sides) get_local_entity_int_value (group, INT_TYPE_SECTOR_SIDE);

	mb_vel = get_local_entity_float_value (member, FLOAT_TYPE_CRUISE_VELOCITY);

	height = get_local_entity_float_value (member, FLOAT_TYPE_CRUISE_ALTITUDE);

	movement_type = group_database [get_local_entity_int_value (group, INT_TYPE_ENTITY_SUB_TYPE)].movement_type;
		
	task_route_type = group_database [get_local_entity_int_value (group, INT_TYPE_ENTITY_SUB_TYPE)].default_entity_type;

	landing_type = group_database [get_local_entity_int_value (group, INT_TYPE_ENTITY_SUB_TYPE)].default_landing_type;

	generate_route = task_database [get_local_entity_int_value (task_en, INT_TYPE_ENTITY_SUB_TYPE)].task_route_search;

	start_point_count = task_database [get_local_entity_int_value (task_en, INT_TYPE_ENTITY_SUB_TYPE)].add_start_waypoint;

	//////////////////////////////////////////////////////////////////
	//
	// Generate list of Specified route
	//
	//////////////////////////////////////////////////////////////////

	route_points_ptr = (vec3d*) get_local_entity_ptr_value (task_en, PTR_TYPE_ROUTE_NODE);

	route_dependents_ptr = (entity**) get_local_entity_ptr_value (task_en, PTR_TYPE_ROUTE_DEPENDENTS);

	route_waypoint_types_ptr = (entity_sub_types *) get_local_entity_ptr_value (task_en, PTR_TYPE_ROUTE_WAYPOINT_TYPES);

	route_formation_types_ptr = (formation_types *) get_local_entity_ptr_value (task_en, PTR_TYPE_ROUTE_FORMATION_TYPES);

	route_length = get_local_entity_int_value (task_en, INT_TYPE_ROUTE_LENGTH);

	last_specified_node = NULL;

	for (loop = route_length - 1; loop >= 0; loop --)
	{

		specified_route = (route_node *) malloc_fast_mem (sizeof (route_node));

		// position
		specified_route->position.x = ceil (route_points_ptr [loop].x);
		specified_route->position.y = ceil (route_points_ptr [loop].y);
		specified_route->position.z = ceil (route_points_ptr [loop].z);

		// dependent
		specified_route->dependent = route_dependents_ptr [loop];

		// waypoint_type
		specified_route->type = route_waypoint_types_ptr [loop];

		// formation_type
		specified_route->formation = route_formation_types_ptr [loop];

		specified_route->next = last_specified_node;
		specified_route->prev = NULL;

		if (last_specified_node)
		{

			last_specified_node->prev = specified_route;
		}

		last_specified_node = specified_route;
	}

	#if DEBUG_MODULE
	if (debug_flag)
	{
	
		debug_log ("CROUTE:   Route specified =");
	
		for (loop = 0; loop < route_length; loop ++)
		{
	
			debug_log ("CROUTE:         Wp %d = %s %s %s [%f, %f, %f]",
							loop,
							entity_sub_type_waypoint_names [route_waypoint_types_ptr [loop]],
							formation_names [route_formation_types_ptr [loop]],
							((route_dependents_ptr [loop]) ? get_local_entity_string (route_dependents_ptr [loop], STRING_TYPE_FULL_NAME) : "None"),
							route_points_ptr [loop].x, route_points_ptr [loop].y, route_points_ptr [loop].z);
		}
	
	}
	#endif

	start_ptr = NULL;
	stop_ptr = NULL;

	if (start_point_count > 0)
	{

		//
		// Add start waypoint
		//

		if (get_comms_model () == COMMS_MODEL_SERVER)
		{
	
			get_local_entity_vec3d (member, VEC3D_TYPE_POSITION, &start);
		}
		else
		{

			start = *client_start;
		}

		start.x = ceil (start.x);
		start.y = ceil (start.y);
		start.z = ceil (start.z);

		start_ptr = &start;

		new_node = (route_node *) malloc_fast_mem (sizeof (route_node));

		// position
		new_node->position.x = start.x;
		new_node->position.y = start.y;
		new_node->position.z = start.z;

		// dependent
		new_node->dependent = NULL;

		// waypoint_type
		new_node->type = ENTITY_SUB_TYPE_WAYPOINT_NAVIGATION;

		// formation_type
		new_node->formation = FORMATION_ROW_LEFT;

		new_node->next = specified_route;
		new_node->prev = NULL;

		specified_route->prev = new_node;

		specified_route = new_node;
	
		#if DEBUG_MODULE
		if (debug_flag)
		{
		
			debug_log ("CROUTE:     Adding START waypoint at [%f, %f, %f]", new_node->position.x, new_node->position.y, new_node->position.z);
		}
		#endif

		if (return_keysite)
		{

			if (get_comms_model () == COMMS_MODEL_SERVER)
			{
		
				get_local_entity_vec3d (return_keysite, VEC3D_TYPE_POSITION, &stop);
			}
			else
			{
	
				stop = *client_stop;
			}

			stop.x = ceil (stop.x);
			stop.y = ceil (stop.y);
			stop.z = ceil (stop.z);

			stop_ptr = &stop;
	
  			//
			// add land waypoint
  			//

			new_node = (route_node *) malloc_fast_mem (sizeof (route_node));

			// position
			new_node->position.x = stop.x;
			new_node->position.y = stop.y;
			new_node->position.z = stop.z;

			// dependent
			new_node->dependent = return_keysite;

			// waypoint_type
			new_node->type = ENTITY_SUB_TYPE_WAYPOINT_LAND;

			// formation_type
			new_node->formation = FORMATION_ROW_LEFT;

			last_specified_node = specified_route;

			while (last_specified_node->next)
			{

				last_specified_node = last_specified_node->next;
			}

			new_node->prev = last_specified_node;
			new_node->next = NULL;

			last_specified_node->next = new_node;

			last_specified_node = new_node;
	
			#if DEBUG_MODULE
			if (debug_flag)
			{
		
				debug_log ("CROUTE:     Adding LAND waypoint at [%f, %f, %f] keysite %s (%d)",
								new_node->position.x, new_node->position.y, new_node->position.z,
								get_local_entity_string (return_keysite, STRING_TYPE_FULL_NAME), get_local_entity_index (return_keysite));
		
			}
			#endif
		}
	}

	//////////////////////////////////////////////////////////////////
	//
	// Generate route
	//
	//////////////////////////////////////////////////////////////////

	if (generate_route)
	{

		//
		// build route
		//
	
		if (!generate_biased_vec3d_route (specified_route, &new_route, side, movement_type))
		{
	
			#if DEBUG_MODULE
			if (debug_flag)
			{
		
				debug_log ("CROUTE:     ***** Cannot create route *****");
			
				debug_log ("CROUTE: ===================================================================================");
		
			}
			#endif

			destroy_fast_route (specified_route);
	
			// restore stack attirbutes

			set_force_local_entity_create_stack_attributes (create_stack_attributes);
		
			return FALSE;
		}
	
	}
	else
	{

		new_route = specified_route;
	}
	
	//////////////////////////////////////////////////////////////////
	//
	// Generate checksum
	//
	//////////////////////////////////////////////////////////////////

	check_sum = generate_route_check_sum (new_route);

	if (get_comms_model () == COMMS_MODEL_CLIENT)
	{

		route_node
			*route;

		//ASSERT (check_sum == get_local_entity_int_value (task_en, INT_TYPE_ROUTE_CHECK_SUM));
		if (check_sum != get_local_entity_int_value (task_en, INT_TYPE_ROUTE_CHECK_SUM))
		{

			debug_log ("CROUTE: WARNING: checksums differ... server %d, client %d (task %s, %d)", check_sum, get_local_entity_int_value (task_en, INT_TYPE_ROUTE_CHECK_SUM), get_local_entity_string (task_en, STRING_TYPE_FULL_NAME), get_local_entity_index (task_en));

			route = new_route;

			while (route)
			{
		
				debug_log ("CROUTE:    %s %s [%f, %f, %f]", entity_sub_type_waypoint_names [route->type], formation_names [route->formation], route->position.x, route->position.y, route->position.z);
		
				route = route->next;
			}
		}
	}
	else
	{

		set_client_server_entity_int_value (task_en, INT_TYPE_ROUTE_CHECK_SUM, check_sum);
	}

	//////////////////////////////////////////////////////////////////
	//
	// Create waypoint route
	//
	//////////////////////////////////////////////////////////////////

	node_count = 0;

	last_wp = NULL;

	specified_route_ptr = specified_route;

	while (new_route)
	{

		waypoint_pos = &new_route->position;

		waypoint_pos->x = bound (waypoint_pos->x, 1, MAX_MAP_X - 1);
		waypoint_pos->y = bound (waypoint_pos->y, 1, MAX_MAP_Y - 1);
		waypoint_pos->z = bound (waypoint_pos->z, 1, MAX_MAP_Z - 1);

		#if DEBUG_MODULE
		if (debug_flag)
		{
		
			debug_log ("CROUTE:     (N wp route) placing waypoint (count %d), at [%f, %f, %f]", node_count, waypoint_pos->x, waypoint_pos->y, waypoint_pos->z);
	
		}
		#endif

		terrain_elevation = get_3d_terrain_elevation (waypoint_pos->x, waypoint_pos->z);

		road_node = get_closest_road_node (waypoint_pos, 5.0);

		// flight time between waypoints

		if (last_wp)
		{

			float
				range;

			vec3d
				*last_waypoint_pos;

			last_waypoint_pos = get_local_entity_vec3d_ptr (last_wp, VEC3D_TYPE_POSITION);

			range = get_2d_range (waypoint_pos, last_waypoint_pos);

			flight_time = 999999.0;

			if (get_local_entity_float_value (member, FLOAT_TYPE_CRUISE_VELOCITY) > 0.0)
			{

				flight_time = range / get_local_entity_float_value (member, FLOAT_TYPE_CRUISE_VELOCITY);
			}
		}

		// waypoint index

		if (!waypoint_indices)
		{

			index = ENTITY_INDEX_DONT_CARE;
		}
		else
		{

			index = waypoint_indices [node_count];

			ASSERT (node_count < indices_count);
		}

		wp = create_local_entity
		(
			ENTITY_TYPE_WAYPOINT,
			index,
			ENTITY_ATTR_PARENT (LIST_TYPE_WAYPOINT, task_en),
			ENTITY_ATTR_CHILD_PRED (LIST_TYPE_WAYPOINT, last_wp),
			ENTITY_ATTR_VEC3D (VEC3D_TYPE_POSITION, waypoint_pos->x, waypoint_pos->y, waypoint_pos->z),
			ENTITY_ATTR_INT_VALUE (INT_TYPE_ENTITY_SUB_TYPE, ENTITY_SUB_TYPE_WAYPOINT_NAVIGATION),
			ENTITY_ATTR_INT_VALUE (INT_TYPE_ROUTE_NODE, road_node),
			ENTITY_ATTR_INT_VALUE (INT_TYPE_WAYPOINT_FORMATION, FORMATION_ROW_LEFT),
			ENTITY_ATTR_FLOAT_VALUE (FLOAT_TYPE_ALTITUDE, height),
			ENTITY_ATTR_FLOAT_VALUE (FLOAT_TYPE_FLIGHT_TIME, flight_time),
			ENTITY_ATTR_END
		);

		//
		// Assign specified waypoint stuff
		//

		if ((waypoint_pos->x == specified_route_ptr->position.x) && (waypoint_pos->z == specified_route_ptr->position.z))
		{

			#if DEBUG_MODULE
			if (debug_flag)
			{
	
				debug_log ("CROUTE:    Assigning waypoint %d (%d) to route. Type %s, formation %s, dependent %s",
								node_count,
								get_local_entity_index (wp),
								waypoint_database [specified_route_ptr->type].full_name,
								formation_names [specified_route_ptr->formation],
								(specified_route_ptr->dependent) ? (get_local_entity_string (specified_route_ptr->dependent, STRING_TYPE_FULL_NAME)) : ("None"));
	
			}
			#endif

			set_local_entity_int_value (wp, INT_TYPE_ENTITY_SUB_TYPE, specified_route_ptr->type);

			set_local_entity_int_value (wp, INT_TYPE_WAYPOINT_FORMATION, specified_route_ptr->formation);

			set_local_entity_int_value (wp, INT_TYPE_POSITION_TYPE, get_waypoint_database_position_type_value (specified_route_ptr->type, task_route_type));

			if (specified_route_ptr->dependent)
			{

				insert_local_entity_into_parents_child_list (wp, LIST_TYPE_TASK_DEPENDENT, specified_route_ptr->dependent, NULL);
			}

			specified_route_ptr = specified_route_ptr->next;
		}

		node_count ++;

		last_wp = wp;

		new_route = new_route->next;
	}

	//////////////////////////////////////////////////////////////////
	//
	// Post process route
	//
	//////////////////////////////////////////////////////////////////
	
	parser_task_waypoint_route (group, task_en);

	#if DEBUG_MODULE
	if (debug_flag)
	{

		vec3d
			*pos;

		entity
			*wp;

		debug_log ("CROUTE: -----------------------------------------------------------------------------------");

		debug_log ("CROUTE: Task %s (%d) Final route created = ", get_local_entity_string (task_en, STRING_TYPE_FULL_NAME), get_local_entity_index (task_en));

		wp = get_local_entity_first_child (task_en, LIST_TYPE_WAYPOINT);

		while (wp)
		{

			if (get_local_entity_int_value (wp, INT_TYPE_POSITION_TYPE) == POSITION_TYPE_VIRTUAL)
			{
	
				debug_log ("CROUTE:      waypoint %s (%d) at virtual position, formation %s, dependent on %s",
								entity_sub_type_waypoint_names [get_local_entity_int_value (wp, INT_TYPE_ENTITY_SUB_TYPE)],
								get_local_entity_index (wp),
								formation_names [get_local_entity_int_value (wp, INT_TYPE_WAYPOINT_FORMATION)],
								(get_local_entity_parent (wp, LIST_TYPE_TASK_DEPENDENT)) ? (get_local_entity_string (get_local_entity_parent (wp, LIST_TYPE_TASK_DEPENDENT), STRING_TYPE_FULL_NAME)) : ("None"));
			}
			else
			{
	
				pos = get_local_entity_vec3d_ptr (wp, VEC3D_TYPE_POSITION);
	
				debug_log ("CROUTE:      waypoint %s (%d) at [%f, %f, %f], formation %s, dependent %s",
								entity_sub_type_waypoint_names [get_local_entity_int_value (wp, INT_TYPE_ENTITY_SUB_TYPE)],
								get_local_entity_index (wp),
								pos->x, pos->y, pos->z,
								formation_names [get_local_entity_int_value (wp, INT_TYPE_WAYPOINT_FORMATION)],
								(get_local_entity_parent (wp, LIST_TYPE_TASK_DEPENDENT)) ? (get_local_entity_string (get_local_entity_parent (wp, LIST_TYPE_TASK_DEPENDENT), STRING_TYPE_FULL_NAME)) : ("None"));
			}

			wp = get_local_entity_child_succ (wp, LIST_TYPE_WAYPOINT);
		}

		debug_log ("CROUTE: ===================================================================================");
	}
	#endif

	//////////////////////////////////////////////////////////////////
	//
	// Tidy up
	//
	//////////////////////////////////////////////////////////////////

	// restore stack attirbutes

	set_force_local_entity_create_stack_attributes (create_stack_attributes);

	// free memory

	if (new_route != specified_route)
	{

		destroy_fast_route (specified_route);
	}

	destroy_fast_route (new_route);

	//////////////////////////////////////////////////////////////////
	//
	// Create on Clients
	//
	//////////////////////////////////////////////////////////////////

	if (get_comms_model () == COMMS_MODEL_SERVER)
	{

		transmit_entity_comms_message (ENTITY_COMMS_CREATE_WAYPOINT_ROUTE, task_en, group, return_keysite, start_ptr, stop_ptr, check_sum, node_count);
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void parser_task_waypoint_route (entity *group, entity *task)
{

	float
		range,
		min_range;

	vec3d
		new_pos,
		*next_next_pos,
		*last_pos,
		*this_pos,
		*next_pos;

	entity
		*next_next_wp,
		*last_wp,
		*next_wp,
		*this_wp;

	ASSERT (task->type == ENTITY_TYPE_TASK);

	last_wp = get_local_entity_first_child (task, LIST_TYPE_WAYPOINT);

	if (!last_wp)
	{

		return;
	}

	this_wp = get_local_entity_child_succ (last_wp, LIST_TYPE_WAYPOINT);

	if (!this_wp)
	{

		return;
	}

	next_wp = get_local_entity_child_succ (this_wp, LIST_TYPE_WAYPOINT);

	if (!next_wp)
	{

		return;
	}

	while (next_wp)
	{
	
		this_pos = get_local_entity_vec3d_ptr (this_wp, VEC3D_TYPE_POSITION);

		next_pos = get_local_entity_vec3d_ptr (next_wp, VEC3D_TYPE_POSITION);
	
		//
		// check if this_wp is on top off next_wp
		//


		range = get_approx_3d_range (next_pos, this_pos);

		min_range = get_waypoint_database_minimum_previous_waypoint_distance (get_local_entity_int_value (next_wp, INT_TYPE_ENTITY_SUB_TYPE), group_database [get_local_entity_int_value (group, INT_TYPE_ENTITY_SUB_TYPE)].default_entity_type);

		//if ((memncmp ((unsigned char *) this_pos, (unsigned char *) next_pos, sizeof (vec3d))))
		if (range < min_range)
		{

			last_pos = get_local_entity_vec3d_ptr (last_wp, VEC3D_TYPE_POSITION);

			//
			// move this waypoint if its a navigation one
			//

			if (get_local_entity_int_value (this_wp, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_WAYPOINT_NAVIGATION)
			{

				vec3d
					delta_position;

				delta_position.x = (next_pos->x - last_pos->x) / 2.0;
				delta_position.y = 0.0;
				delta_position.z = (next_pos->z - last_pos->z) / 2.0;
	
				new_pos.x = ceil (last_pos->x + delta_position.x);
				new_pos.y = ceil (this_pos->y + delta_position.y);
				new_pos.z = ceil (last_pos->z + delta_position.z);

				range = get_approx_3d_range (next_pos, &new_pos);

				min_range = get_waypoint_database_minimum_previous_waypoint_distance (get_local_entity_int_value (next_wp, INT_TYPE_ENTITY_SUB_TYPE), group_database [get_local_entity_int_value (group, INT_TYPE_ENTITY_SUB_TYPE)].default_entity_type);

				if (range < min_range)
				{

					normalise_3d_vector (&delta_position);

					//invert_3d_vector (&delta_position);

					delta_position.x *= min_range;
					delta_position.y *= min_range;
					delta_position.z *= min_range;
	
					new_pos.x = ceil (next_pos->x - delta_position.x);
					new_pos.y = ceil (next_pos->y - delta_position.y);
					new_pos.z = ceil (next_pos->z - delta_position.z);

					debug_log ("CROUTE: Limiting waypoint spacing... wp %s [%f, %f, %f] is limited to %f from wp %s [%f, %f, %f], (this -> next)",
									get_local_entity_string (this_wp, STRING_TYPE_FULL_NAME),
									this_pos->x, this_pos->y, this_pos->z,
									min_range,
									get_local_entity_string (next_wp, STRING_TYPE_FULL_NAME),
									next_pos->x, next_pos->y, next_pos->z);
				}
	
				#if DEBUG_MODULE
				if (debug_flag)
				{
	
					debug_log ("CROUTE: PARSING WAYPOINT ROUTE.... spacing this_waypoint");
				}
				#endif
	
				set_local_entity_vec3d (this_wp, VEC3D_TYPE_POSITION, &new_pos);
			}
			else if (get_local_entity_int_value (next_wp, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_WAYPOINT_NAVIGATION)
			{

				next_next_wp = get_local_entity_child_succ (next_wp, LIST_TYPE_WAYPOINT);
	
				next_next_pos = get_local_entity_vec3d_ptr (next_next_wp, VEC3D_TYPE_POSITION);

				if (next_next_wp)
				{

					float
						range,
						min_range;

					vec3d
						delta_position;

					//
					// move the next one towards the next_next
					//

					delta_position.x = (next_next_pos->x - this_pos->x) / 2.0;
					delta_position.y = 0.0;
					delta_position.z = (next_next_pos->z - this_pos->z) / 2.0;
	
					new_pos.x = ceil (this_pos->x + delta_position.x);
					new_pos.y = ceil (next_pos->y + delta_position.y);
					new_pos.z = ceil (this_pos->z + delta_position.z);

					range = get_approx_3d_range (next_next_pos, &new_pos);

					min_range = get_waypoint_database_minimum_previous_waypoint_distance (get_local_entity_int_value (next_next_wp, INT_TYPE_ENTITY_SUB_TYPE), group_database [get_local_entity_int_value (group, INT_TYPE_ENTITY_SUB_TYPE)].default_entity_type);

					if (range < min_range)
					{

						normalise_3d_vector (&delta_position);

						//invert_3d_vector (&delta_position);

						delta_position.x *= min_range;
						delta_position.y *= min_range;
						delta_position.z *= min_range;
	
						new_pos.x = ceil (next_next_pos->x - delta_position.x);
						new_pos.y = ceil (next_next_pos->y - delta_position.y);
						new_pos.z = ceil (next_next_pos->z - delta_position.z);

						debug_log ("CROUTE: Limiting waypoint spacing... wp %s [%f, %f, %f] is limited to %f from wp %s [%f, %f, %f], (next -> next_next)",
									get_local_entity_string (next_wp, STRING_TYPE_FULL_NAME),
									next_pos->x, next_pos->y, next_pos->z,
									min_range,
									get_local_entity_string (next_next_wp, STRING_TYPE_FULL_NAME),
									next_next_pos->x, next_next_pos->y, next_next_pos->z);
					}

					#if DEBUG_MODULE
					if (debug_flag)
					{
			
						debug_log ("CROUTE: PARSING WAYPOINT ROUTE.... spacing next waypoint");
				
					}
					#endif

					bound_position_to_adjusted_map_volume (&new_pos);
		
					set_local_entity_vec3d (next_wp, VEC3D_TYPE_POSITION, &new_pos);
				}
			}
		}

		last_wp = this_wp;

		this_wp = next_wp;

		next_wp = get_local_entity_child_succ (next_wp, LIST_TYPE_WAYPOINT);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned char generate_route_check_sum (route_node *route)
{

	unsigned char
		check_sum;

	check_sum = 0;

	#if DEBUG_MODULE
	if (debug_flag)
	{

		debug_log ("CROUTE: Generating checksum");
	}
	#endif

	// dont checksum start and end points because entities may be in slightly different positions due to pack/unpack

	route = route->next;

	if (route)
	{
	
		while (route->next)
		{
	
			check_sum += (int) route->position.x;
			#if DEBUG_MODULE
			if (debug_flag)
			{
				debug_log ("CROUTE:    after x %f = check_sum = %d", route->position.x, check_sum);
			}
			#endif

			check_sum += (int) route->position.y;
			#if DEBUG_MODULE
			if (debug_flag)
			{
				debug_log ("CROUTE:    after y %f = check_sum = %d", route->position.y, check_sum);
			}
			#endif

			check_sum += (int) route->position.z;
			#if DEBUG_MODULE
			if (debug_flag)
			{
				debug_log ("CROUTE:    after z %f = check_sum = %d", route->position.z, check_sum);
			}
			#endif

			route = route->next;
		}
	}

	#if DEBUG_MODULE
	if (debug_flag)
	{

		debug_log ("CROUTE:    checksum %d", check_sum);
	}
	#endif

	return check_sum;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_route_generator (void)
{

	route_node
		*destroy_node;

	destroy_node = fast_route;

	while (fast_route)
	{

		free_mem (destroy_node);

		fast_route = fast_route->next;
	}

	fast_route = NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int generate_biased_vec3d_route (route_node *points, route_node **route, int side, movement_types movement_type)
{

	int
		node_count;

	route_node
		*route_start,
		*route_end,
		*this_node,
		*next_node;

	route_start = NULL;

	node_count = 0;

	best_point_terrain_elevations = (float *) malloc_fast_mem (sizeof (float) * (route_biasing_database [movement_type].num_route_samples + 1));

	this_node = points;
	next_node = this_node->next;

	while (next_node)
	{

		fast_route = create_route (&this_node->position, &next_node->position, (entity_sides) side, movement_type);

		second_past_route (fast_route, (entity_sides) side, movement_type);
	
		optimise_route (fast_route, movement_type);

		// skip start of route if its not the first iteration
		// this avoids putting 2 waypoints on top of each other...
		// ie. end of one route and start of next
		if (node_count > 0)
		{

			route_node
				*destroy_node;
	
			destroy_node = fast_route;
			fast_route = fast_route->next;
			fast_route->prev = NULL;
			free_mem (destroy_node);

			ASSERT (route_start);

			// link into list

			route_end = route_start;

			while (route_end->next)
			{

				route_end = route_end->next;
			}

			route_end->next = fast_route;

			// set last waypoint type (of sub_route)

			route_end = fast_route;

			while (route_end->next)
			{

				route_end = route_end->next;
			}

			route_end->type = next_node->type;
			route_end->formation = next_node->formation;
		}
		else
		{

			// set 1st waypoint type
			fast_route->type = this_node->type;
			fast_route->formation = this_node->formation;

			route_start = fast_route;

			// set last waypoint type (of this sub_route)
			route_end = route_start;

			while (route_end->next)
			{

				route_end = route_end->next;
			}

			route_end->type = next_node->type;
			route_end->formation = next_node->formation;
		}

		node_count ++;

		this_node = next_node;
		next_node = next_node->next;
	}

	free_mem (best_point_terrain_elevations);

	*route = route_start;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

route_node *create_route (vec3d *start, vec3d *end, entity_sides side, movement_types movement_type)
{

	route_node
		*start_node,
		*end_node;

	start_node = (route_node *) malloc_fast_mem (sizeof (route_node));
	memset (start_node, 0, sizeof (route_node));
	start_node->type = ENTITY_SUB_TYPE_WAYPOINT_NAVIGATION;
	start_node->position.x = ceil (start->x);
	start_node->position.y = ceil (start->y);
	start_node->position.z = ceil (start->z);

	end_node = (route_node *) malloc_fast_mem (sizeof (route_node));
	memset (end_node, 0, sizeof (route_node));
	end_node->type = ENTITY_SUB_TYPE_WAYPOINT_NAVIGATION;
	end_node->position.x = ceil (end->x);
	end_node->position.y = ceil (end->y);
	end_node->position.z = ceil (end->z);

	start_node->next = end_node;
	end_node->prev = start_node;

	generate_best_mid_point (start_node, end_node, side, movement_type);

	return start_node;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int generate_best_mid_point (route_node *start_node, route_node *end_node, entity_sides side, movement_types movement_type)
{

	route_node
		*new_node;

	vec3d
		best_point;

	if (get_best_point (&start_node->position, &end_node->position, &best_point, side, movement_type))
	{

		new_node = (route_node *) malloc_fast_mem (sizeof (route_node));
		memset (new_node, 0, sizeof (route_node));

		new_node->type = ENTITY_SUB_TYPE_WAYPOINT_NAVIGATION;
		new_node->position.x = ceil (best_point.x);
		new_node->position.y = ceil (best_point.y);
		new_node->position.z = ceil (best_point.z);

		new_node->next = end_node;
		new_node->prev = start_node;

		start_node->next = new_node;
		end_node->prev = new_node;

		generate_best_mid_point (start_node, new_node, side, movement_type);

		generate_best_mid_point (new_node, end_node, side, movement_type);

		return TRUE;
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_best_point (vec3d *start, vec3d *end, vec3d *best_point, entity_sides side, movement_types movement_type)
{

	vec3d
		mid_point,
		end_point,
		test_point,
		start_point,
		test_direction,
		route_direction;

	float
		loop,
		range,
		best_loop,
		point_rating,
		best_point_rating,
		test_direction_x_inc,
		test_direction_z_inc;

	// Quantize points

	start_point.x = ceil (start->x);
	start_point.y = ceil (start->y);
	start_point.z = ceil (start->z);

	end_point.x = ceil (end->x);
	end_point.y = ceil (end->y);
	end_point.z = ceil (end->z);

	range = get_sqr_2d_range (&start_point, &end_point);

	if (range > (route_biasing_database [movement_type].min_route_range * route_biasing_database [movement_type].min_route_range))
	{
	
		route_direction.x = end_point.x - start_point.x;
		route_direction.y = 0.0;
		route_direction.z = end_point.z - start_point.z;
	
		test_direction.x = route_direction.z;
		test_direction.y = 0.0;
		test_direction.z = -route_direction.x;

		// test increments
		test_direction_x_inc = test_direction.x / (route_biasing_database [movement_type].num_route_samples * route_biasing_database [movement_type].route_deviation_size);
		test_direction_z_inc = test_direction.z / (route_biasing_database [movement_type].num_route_samples * route_biasing_database [movement_type].route_deviation_size);
	
		// route mid point
		mid_point.x = (start_point.x + (route_direction.x * 0.5));
		mid_point.y = 0.0;
		mid_point.z = (start_point.z + (route_direction.z * 0.5));

		// test point start
		start_point.x = mid_point.x - test_direction_x_inc * (route_biasing_database [movement_type].num_route_samples * 0.5);
		start_point.z = mid_point.z - test_direction_z_inc * (route_biasing_database [movement_type].num_route_samples * 0.5);
	
		start_point.x = bound (start_point.x, MIN_MAP_X, MAX_MAP_X);
		start_point.y = 0.0;
		start_point.z = bound (start_point.z, MIN_MAP_Z, MAX_MAP_Z);
	
		// get terrain elevations across sample area
		{

			int
				loop;

			// test point start
			test_point.x = ceil (start_point.x);
			test_point.z = ceil (start_point.z);
		
			for (loop = 1; loop <= route_biasing_database [movement_type].num_route_samples; loop ++)
			{
	
				best_point_terrain_elevations [loop] = ceil (get_3d_terrain_elevation (test_point.x, test_point.z));
		
				// next test point
				test_point.x += test_direction_x_inc;
				test_point.z += test_direction_z_inc;
		
				test_point.x = bound (ceil (test_point.x), MIN_MAP_X, MAX_MAP_X);
				test_point.z = bound (ceil (test_point.z), MIN_MAP_Z, MAX_MAP_Z);
			}
		}
	
  		// test point start
		test_point.x = ceil (start_point.x);
		test_point.y = 0.0;
		test_point.z = ceil (start_point.z);
	
		// best so far
		best_point_rating = get_route_point_rating (1.0, &test_point, side, movement_type);
		memcpy (best_point, &test_point, sizeof (vec3d));
		best_loop = 0.0;
	
  		// test points along perpendicular line
		for (loop = 1.0; loop < route_biasing_database [movement_type].num_route_samples; loop ++)
		{
	
  			// next test point
			test_point.x += test_direction_x_inc;
			test_point.z += test_direction_z_inc;
	
			test_point.x = bound (ceil (test_point.x), MIN_MAP_X, MAX_MAP_X);
			test_point.z = bound (ceil (test_point.z), MIN_MAP_Z, MAX_MAP_Z);
	
  			// best so far
			point_rating = get_route_point_rating (loop + 1.0, &test_point, side, movement_type);

			#if DEBUG_MODULE
			if (debug_flag)
			{

				debug_log ("GENROUTE: test point %f = %f, %f, %f... rating %f (best point %f)", loop, test_point.x, test_point.y, test_point.z, point_rating, best_point_rating);
			}
			#endif
	
			if (point_rating < best_point_rating)
			{
	
  				best_loop = loop;
				best_point_rating = point_rating;
				memcpy (best_point, &test_point, sizeof (vec3d));
			}
		}

		#if DEBUG_MODULE
		if (debug_flag)
		{
	
			debug_log ("GENROUTE: generating node at [%0.2f, %0.2f, %0.2f] between [%0.2f, %0.2f, %0.2f] and [%0.2f, %0.2f, %0.2f], range %f",
							best_point->x, best_point->y, best_point->z,
							ceil (start->x), ceil (start->y), ceil (start->z),
							ceil (end->x), ceil (end->y), ceil (end->z),
							get_2d_range (start, end));
	
		}
		#endif

		return TRUE;
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void second_past_route (route_node *route, entity_sides side, movement_types movement_type)
{

	vec3d
		best_point;

	route_node
		*prev_node,
		*node,
		*next_node;

	prev_node = route;

	node = prev_node->next;

	next_node = node->next;

	while (next_node)
	{

		get_best_point (&prev_node->position, &next_node->position, &best_point, side, movement_type);

		node->position.x = ceil (best_point.x);
		node->position.y = ceil (best_point.y);
		node->position.z = ceil (best_point.z);

		prev_node = node;

		node = prev_node->next;

		next_node = node->next;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_route_point_rating (float sample_number, vec3d *test_point, entity_sides side, movement_types movement_type)
{

	float
		average_terrain_elevation,
		side_bias,
		elevation,
		range_bias,
		rating;

	entity
		*sector_en;

	entity_sides
		sector_side;

	// minimum height of 1.0m to allow biasing

	average_terrain_elevation = best_point_terrain_elevations [(int) sample_number] +
										best_point_terrain_elevations [(int) (max ((sample_number - 1.0f), 1.0f))] +
										best_point_terrain_elevations [(int) (min ((sample_number + 1.0f), route_biasing_database [movement_type].num_route_samples))];

	average_terrain_elevation /= 3.0;

	average_terrain_elevation = max (average_terrain_elevation, 0.0f);

	elevation = route_biasing_database [movement_type].elevation_bias * average_terrain_elevation;

	range_bias = route_biasing_database [movement_type].range_bias *
						fabs ((2.0 * sample_number) - route_biasing_database [movement_type].num_route_samples) /
						(route_biasing_database [movement_type].num_route_samples * 2.0);

	sector_en = get_local_sector_entity (test_point);

	sector_side = (entity_sides) get_local_entity_int_value (sector_en, INT_TYPE_SECTOR_SIDE);

	side_bias = route_biasing_database [movement_type].side_bias * (sector_side != side);

	rating = elevation +
				(range_bias * max (average_terrain_elevation, 1.0f)) +
				(side_bias * max (average_terrain_elevation, 1.0f));

	#if DEBUG_MODULE
	if (debug_flag)
	{

		debug_log ("ROUTEGEN: point rating %f, elevation %f, range %f, side %f", rating, elevation, range_bias, side_bias);
	}
	#endif

	return rating;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void optimise_route (route_node *node, movement_types movement_type)
{

	route_node
		*prev_node,
		*next_node;

	int
		remove_node;

	float
		angle;

	vec3d
		vec1,
		vec2;

	node = node->next;
	prev_node = node->prev;
	next_node = node->next;

	while (next_node)
	{

		remove_node = FALSE;

		vec1.x = node->position.x - prev_node->position.x;
		vec1.y = 0.0;
		vec1.z = node->position.z - prev_node->position.z;

		if (check_zero_3d_vector (&vec1))
		{

			remove_node = TRUE;
		}
		else
		{
	
			vec2.x = next_node->position.x - node->position.x;
			vec2.y = 0.0;
			vec2.z = next_node->position.z - node->position.z;
	
			if (check_zero_3d_vector (&vec2))
			{
	
				remove_node = TRUE;
			}
			else
			{

				float
					square;

				square = get_inverse_square_root ( vec1.x * vec1.x + vec1.z * vec1.z );
				vec1.x *= square;
				vec1.z *= square;

				square = get_inverse_square_root ( vec2.x * vec2.x + vec2.z * vec2.z );
				vec2.x *= square;
				vec2.z *= square;

//				normalise_any_3d_vector (&vec1);
	
//				normalise_any_3d_vector (&vec2);

				angle = ((vec1.x * vec2.x) + (vec1.z * vec2.z));

				if (fabs (angle) > route_biasing_database [movement_type].optimise_tolerance)
				{

					remove_node = TRUE;
				}
			}
		}

		if (remove_node)
		{

			// delete node

			#if DEBUG_MODULE
			if (debug_flag)
			{
	
				debug_log ("GENROUTE: removing node, within optimise tolerance");
			}
			#endif

			prev_node->next = next_node;

			next_node->prev = prev_node;

			free_mem (node);

			node = next_node;

			next_node = next_node->next;
		}
		else
		{
	
			// advance links (careful cause node could be freed)
	
			prev_node = prev_node->next;
	
			node = prev_node->next;
	
			next_node = node->next;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void destroy_fast_route (route_node *route)
{

	route_node
		*destroy_node;
		
	while (route)
	{

		destroy_node = route;

		route = route->next;

		free_mem (destroy_node);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

route_node *temp_create_generic_waypoint_route (entity *group, entity *task_en, entity *return_keysite, unsigned int *waypoint_indices, int indices_count)
{

	route_node
		*new_node,
		*new_route,
		//*temp_new_route,
		*specified_route,
		//*specified_route_ptr,
		*last_specified_node;

	movement_types
		movement_type;

	entity_sub_types
		landing_type;

	vec3d
		*stop,
		*start,
		//*waypoint_pos,
		*route_points_ptr;

	int
		loop,
		route_length,
		generate_route,
		start_point_count,
		create_stack_attributes;
	
	entity_sides
		side;
  	
	float
		mb_vel,
		height;

	entity
		*landing_entity,
		**route_dependents_ptr;

	entity_sub_types
		*route_waypoint_types_ptr;

	formation_types
		*route_formation_types_ptr;

	ASSERT (task_en);

	#if DEBUG_MODULE
	if (debug_flag)
	{
	
		debug_log ("CROUTE: ===================================================================================");
	
		debug_log ("CROUTE: Creating route for task %s (%d), movement type %s",
						get_local_entity_string (task_en, STRING_TYPE_FULL_NAME),
						get_local_entity_index (task_en),
						movement_names [get_local_entity_int_value (task_en, INT_TYPE_MOVEMENT_TYPE)]);
	
	}
	#endif

	reset_waypoint_tags ();

	if (get_local_entity_first_child (task_en, LIST_TYPE_WAYPOINT))
	{

		#if DEBUG_MODULE
		if (debug_flag)
		{

			debug_log ("CROUTE:     Task %s already has waypoint route", get_local_entity_string (task_en, STRING_TYPE_FULL_NAME));
			
			debug_log ("CROUTE: ===================================================================================");
		}
		#endif

		return NULL;
	}

	// set stack attirbutes

	create_stack_attributes = force_local_entity_create_stack_attributes;

	if (get_comms_data_flow () == COMMS_DATA_FLOW_RX)
	{

		set_force_local_entity_create_stack_attributes (TRUE);
	}
	
	//////////////////////////////////////////////////////////////////
	//
	// Sort route generation type
	//
	//////////////////////////////////////////////////////////////////

	//member = get_local_entity_first_child (group, LIST_TYPE_MEMBER);

	//ASSERT (member);

	side = (entity_sides) get_local_entity_int_value (task_en, INT_TYPE_SIDE);

	//mb_vel = get_local_entity_float_value (member, FLOAT_TYPE_CRUISE_VELOCITY);
	mb_vel = 50.0;

	//height = get_local_entity_float_value (member, FLOAT_TYPE_CRUISE_ALTITUDE);
	height = 50.0;

	//movement_type = group_database [get_local_entity_int_value (group, INT_TYPE_ENTITY_SUB_TYPE)].movement_type;
	movement_type = (movement_types) get_local_entity_int_value (task_en, INT_TYPE_MOVEMENT_TYPE);

	//landing_type = group_database [get_local_entity_int_value (group, INT_TYPE_ENTITY_SUB_TYPE)].default_landing_type;
	landing_type = ENTITY_SUB_TYPE_LANDING_HELICOPTER;

	generate_route = task_database [get_local_entity_int_value (task_en, INT_TYPE_ENTITY_SUB_TYPE)].task_route_search;

	start_point_count = task_database [get_local_entity_int_value (task_en, INT_TYPE_ENTITY_SUB_TYPE)].add_start_waypoint;

	//////////////////////////////////////////////////////////////////
	//
	// Generate list of Specified route
	//
	//////////////////////////////////////////////////////////////////

	route_points_ptr = (vec3d *) get_local_entity_ptr_value (task_en, PTR_TYPE_ROUTE_NODE);

	route_dependents_ptr = (entity **) get_local_entity_ptr_value (task_en, PTR_TYPE_ROUTE_DEPENDENTS);

	route_waypoint_types_ptr = (entity_sub_types *) get_local_entity_ptr_value (task_en, PTR_TYPE_ROUTE_WAYPOINT_TYPES);

	route_formation_types_ptr = (formation_types *) get_local_entity_ptr_value (task_en, PTR_TYPE_ROUTE_FORMATION_TYPES);

	route_length = get_local_entity_int_value (task_en, INT_TYPE_ROUTE_LENGTH);

	last_specified_node = NULL;

	for (loop = route_length - 1; loop >= 0; loop --)
	{

		specified_route = (route_node *) malloc_fast_mem (sizeof (route_node));

		// position
		specified_route->position.x = ceil (route_points_ptr [loop].x);
		specified_route->position.y = ceil (route_points_ptr [loop].y);
		specified_route->position.z = ceil (route_points_ptr [loop].z);

		// dependent
		specified_route->dependent = route_dependents_ptr [loop];

		// waypoint_type
		specified_route->type = route_waypoint_types_ptr [loop];

		// formation_type
		specified_route->formation = route_formation_types_ptr [loop];

		specified_route->next = last_specified_node;
		specified_route->prev = NULL;

		if (last_specified_node)
		{

			last_specified_node->prev = specified_route;
		}

		last_specified_node = specified_route;
	}

	#if DEBUG_MODULE
	if (debug_flag)
	{
	
		debug_log ("CROUTE:   Route specified =");
	
		for (loop = 0; loop < route_length; loop ++)
		{
	
			debug_log ("CROUTE:         Wp %d = %s %s %s [%f, %f, %f]",
							loop,
							entity_sub_type_waypoint_names [route_waypoint_types_ptr [loop]],
							formation_names [route_formation_types_ptr [loop]],
							((route_dependents_ptr [loop]) ? get_local_entity_string (route_dependents_ptr [loop], STRING_TYPE_FULL_NAME) : "None"),
							route_points_ptr [loop].x, route_points_ptr [loop].y, route_points_ptr [loop].z);
		}
	}
	#endif

	if (start_point_count > 0)
	{

		entity
			*start_keysite;

		//
		// Add start waypoint
		//

		start_keysite = get_local_entity_parent (task_en, LIST_TYPE_UNASSIGNED_TASK);
	
		start = get_local_entity_vec3d_ptr (start_keysite, VEC3D_TYPE_POSITION);

		new_node = (route_node *) malloc_fast_mem (sizeof (route_node));

		// position
		new_node->position.x = ceil (start->x);
		new_node->position.y = ceil (start->y);
		new_node->position.z = ceil (start->z);

		// dependent
		new_node->dependent = NULL;

		// waypoint_type
		new_node->type = ENTITY_SUB_TYPE_WAYPOINT_NAVIGATION;

		// formation_type
		new_node->formation = FORMATION_ROW_LEFT;

		new_node->next = specified_route;
		new_node->prev = NULL;

		specified_route->prev = new_node;

		specified_route = new_node;
	
		#if DEBUG_MODULE
		if (debug_flag)
		{
	
			debug_log ("CROUTE:     Adding START waypoint at [%f, %f, %f]", new_node->position.x, new_node->position.y, new_node->position.z);
		}
		#endif

		if (return_keysite)
		{
		
			stop = get_local_entity_vec3d_ptr (return_keysite, VEC3D_TYPE_POSITION);
	
			landing_entity = get_local_entity_landing_entity (return_keysite, landing_type);
	
  			//
			// add land waypoint
  			//

			new_node = (route_node *) malloc_fast_mem (sizeof (route_node));

			// position
			new_node->position.x = ceil (stop->x);
			new_node->position.y = ceil (stop->y);
			new_node->position.z = ceil (stop->z);

			// dependent
			new_node->dependent = return_keysite;

			// waypoint_type
			new_node->type = ENTITY_SUB_TYPE_WAYPOINT_LAND;

			// formation_type
			new_node->formation = FORMATION_ROW_LEFT;

			last_specified_node = specified_route;

			while (last_specified_node->next)
			{

				last_specified_node = last_specified_node->next;
			}

			new_node->prev = last_specified_node;
			new_node->next = NULL;

			last_specified_node->next = new_node;

			last_specified_node = new_node;
	
			#if DEBUG_MODULE
			if (debug_flag)
			{
	
				debug_log ("CROUTE:     Adding LAND waypoint at [%f, %f, %f] keysite %s (%d)",
							new_node->position.x, new_node->position.y, new_node->position.z,
							get_local_entity_string (return_keysite, STRING_TYPE_FULL_NAME), get_local_entity_index (return_keysite));
	
			}
			#endif
		}
	}

	//////////////////////////////////////////////////////////////////
	//
	// Generate route
	//
	//////////////////////////////////////////////////////////////////

	if (generate_route)
	{
	
		//
		// build route
		//
	
		if (!generate_biased_vec3d_route (specified_route, &new_route, side, movement_type))
		{
	
			#if DEBUG_MODULE
			if (debug_flag)
			{
		
				debug_log ("CROUTE:     ***** Cannot create route *****");
			
				debug_log ("CROUTE: ===================================================================================");
		
			}
			#endif

			destroy_fast_route (specified_route);
	
			// restore stack attirbutes

			set_force_local_entity_create_stack_attributes (create_stack_attributes);
		
			return FALSE;
		}
	}
	else
	{

		new_route = specified_route;
	}

	//////////////////////////////////////////////////////////////////
	//
	// Tidy up
	//
	//////////////////////////////////////////////////////////////////

	// free memory

	if (new_route != specified_route)
	{

		destroy_fast_route (specified_route);
	}

	// restore stack attirbutes

	set_force_local_entity_create_stack_attributes (create_stack_attributes);

	return new_route;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
