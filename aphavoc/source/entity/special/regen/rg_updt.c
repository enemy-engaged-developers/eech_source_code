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

#define HACK_PEOPLE_INTO_REGEN_QUEUE 1

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int get_regen_sub_type (int type);

static void regen_queue_insert (entity_sides side, int regen_type, regen_list_element *insert_me);

static void regen_queue_remove (entity_sides side, int regen_type);

static void regen_queue_use (entity_sides side, int regen_type);

static int set_regen_queue_size (regen_management_element *m1, int size);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if DEBUG_MODULE

static void output_regen_data (int side, int regen_type);

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if DEBUG_MODULE

static int regen_ac_debug[NUM_ENTITY_SUB_TYPE_AIRCRAFT];

static int regen_vh_debug[NUM_ENTITY_SUB_TYPE_VEHICLES];

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
	helicopter_groups_count = 6,
	fixed_wing_groups_count = 4,
	routed_vehicle_groups_count = 7,
	ship_groups_count = 2;

entity_sub_types
	helicopter_groups [] =
	{
		ENTITY_SUB_TYPE_GROUP_RECON_HELICOPTER,
		ENTITY_SUB_TYPE_GROUP_ATTACK_HELICOPTER,
		ENTITY_SUB_TYPE_GROUP_ASSAULT_HELICOPTER,
		ENTITY_SUB_TYPE_GROUP_HEAVY_LIFT_TRANSPORT_HELICOPTER,
		ENTITY_SUB_TYPE_GROUP_MARINE_ASSAULT_HELICOPTER,
		ENTITY_SUB_TYPE_GROUP_MEDIUM_LIFT_TRANSPORT_HELICOPTER
	},

	fixed_wing_groups [] =
	{
		ENTITY_SUB_TYPE_GROUP_CARRIER_BORNE_ATTACK_AIRCRAFT,
		ENTITY_SUB_TYPE_GROUP_CARRIER_BORNE_INTERCEPTOR,
		ENTITY_SUB_TYPE_GROUP_CLOSE_AIR_SUPPORT_AIRCRAFT,
		ENTITY_SUB_TYPE_GROUP_MULTI_ROLE_FIGHTER
	},

	routed_vehicle_groups [] =
	{
		ENTITY_SUB_TYPE_GROUP_PRIMARY_FRONTLINE,
		ENTITY_SUB_TYPE_GROUP_SECONDARY_FRONTLINE,
		ENTITY_SUB_TYPE_GROUP_SELF_PROPELLED_ARTILLERY,
		ENTITY_SUB_TYPE_GROUP_SELF_PROPELLED_MLRS,
	},

	ship_groups [] =
	{
		ENTITY_SUB_TYPE_GROUP_FRIGATE,
		ENTITY_SUB_TYPE_GROUP_LANDING_CRAFT,
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_server (entity *en)
{

	regen
		*raw;

	raw = get_local_entity_data (en);

	if (!raw->alive)
	{
		return;
	}

	raw->sleep -= get_delta_time ();

	if (raw->sleep <= 0.0)
	{
		regen_update (en);

		raw->sleep = regen_frequency [raw->side] * get_regen_frequency_difficulty_modifier ();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_regen_update_functions (void)
{
	fn_update_client_server_entity[ENTITY_TYPE_REGEN][COMMS_MODEL_SERVER]  	= update_server;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *regen_update (entity *en)
{

	regen_management_element
		*m1;

	entity_sub_types
		member_type,
		group_type;

	entity
		*wp,
		*task,
		*group,
		*member,
		*building,
		*force_en,
		*landing,
		*keysite;

	unsigned int
		member_number;

	int
		reserve_count;

	force
		*force_raw;

	regen
		*raw;

	regen_list_element
		*e1;

	raw = get_local_entity_data (en);

	wp = get_local_entity_parent (en, LIST_TYPE_CURRENT_WAYPOINT);

	task = get_local_entity_parent (wp, LIST_TYPE_WAYPOINT);

	landing = get_local_entity_parent (task, LIST_TYPE_UNASSIGNED_TASK);
			
	keysite = get_local_entity_parent (landing, LIST_TYPE_LANDING_SITE);

	force_en = get_local_force_entity (raw->side);

	force_raw = get_local_entity_data (force_en);

	group_type = NUM_ENTITY_SUB_TYPE_GROUPS;

	m1 = &regen_manager [raw->side][raw->sub_type];

	//
	// is there anything in the regen queues?
	//
	
	if (m1->count == 0)
	{
		return NULL;
	}

	//
	// Can regen operate
	//

	building = raw->member_root.first_child;

	if ((!get_local_entity_int_value (building, INT_TYPE_ALIVE)) || (get_local_entity_int_value (keysite, INT_TYPE_KEYSITE_USABLE_STATE) != KEYSITE_STATE_USABLE))
	{
		#if DEBUG_MODULE

		debug_log ("RG_UPDT: keysite %s too damaged to regen", get_local_entity_string (keysite, STRING_TYPE_KEYSITE_NAME));

		#endif

		return NULL;
	}

	e1 = &regen_queue [raw->side][raw->sub_type][m1->front];

	ASSERT (e1->type != -1);
	ASSERT (e1->sub_type != -1);
	ASSERT (e1->group != -1);

	// is there a reserve of this type?
	if ((e1->type == ENTITY_TYPE_FIXED_WING) || (e1->type == ENTITY_TYPE_HELICOPTER))
	{
		reserve_count = force_raw->force_info_reserve_hardware[aircraft_database[e1->sub_type].force_info_catagory];
	}
	else
	{
		reserve_count = force_raw->force_info_reserve_hardware[vehicle_database[e1->sub_type].force_info_catagory];
	}

	if (reserve_count <= 0)
	{
		return NULL;
	}

	#if DEBUG_MODULE

	debug_log ("RG_UPDT: Trying to Regen %s Sub Type %d at %s - reserve count %d",
								get_entity_type_name (e1->type), e1->sub_type,
								get_local_entity_string (keysite, STRING_TYPE_KEYSITE_NAME), reserve_count);

	#endif

	//
	// Don't regen if PLAYER landed there
	//

	group = get_local_entity_first_child (keysite, LIST_TYPE_KEYSITE_GROUP);

	while (group)
	{
		member = get_local_entity_first_child (group, LIST_TYPE_MEMBER);

		while (member)
		{

			if (get_local_entity_int_value (member, INT_TYPE_PLAYER) != ENTITY_PLAYER_AI)
			{

				if (get_local_entity_int_value (member, INT_TYPE_LANDED))
				{
					#if DEBUG_MODULE

					debug_log ("RG_UPDT: PLAYER landed at keysite %s, can't regen", get_local_entity_string (keysite, STRING_TYPE_KEYSITE_NAME));

					#endif

					return NULL;
				}
			}

			member = get_local_entity_child_succ (member, LIST_TYPE_MEMBER);
		}

		group = get_local_entity_child_succ (group, LIST_TYPE_KEYSITE_GROUP);
	}

	group_type = e1->group;
	
	member_type = e1->sub_type;

	////////////////////////////////////////////////////////////////////////////
	// Dont regen people or transport aircraft in apache havoc campaign as airport might not be correct (landing routes etc)
	////////////////////////////////////////////////////////////////////////////
	if (get_local_entity_int_value (get_session_entity (), INT_TYPE_CAMPAIGN_REQUIRES_APACHE_HAVOC))
	{

		switch (get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE))
		{

			case ENTITY_SUB_TYPE_REGEN_PEOPLE:
			{

				#if DEBUG_MODULE

				debug_log ("RG_UPDT: Stopping Regening People - wrong warzone");

				#endif

				return NULL;
			}

			case ENTITY_SUB_TYPE_REGEN_FIXED_WING:
			{

				if (group_database [group_type].default_landing_type == ENTITY_SUB_TYPE_LANDING_FIXED_WING_TRANSPORT)
				{

					#if DEBUG_MODULE

					debug_log ("RG_UPDT: Stopping Regening Transport aircraft - wrong warzone");

					#endif

					return NULL;
				}
			}
		}
	}
	////////////////////////////////////////////////////////////////////////////
	// Dont regen people or transport aircraft in apache havoc campaign as airport might not be correct (landing routes etc)
	////////////////////////////////////////////////////////////////////////////

	if (group_type != NUM_ENTITY_SUB_TYPE_GROUPS)
	{

		int
			route_node;

		entity
			*building,
			*member,
			*guide,
			*group = NULL;

		group = create_landing_faction_members (keysite, member_type, group_type, 1, wp, &raw->position);

		if (group)
		{

			//
			// Assign closest route_node (only needed for routed vehicles)
			//

			if (get_local_entity_int_value (group, INT_TYPE_FRONTLINE))
			{
	
				route_node = get_closest_side_road_node (get_local_entity_int_value (group, INT_TYPE_SIDE), &raw->position, 5 * KILOMETRE);
	
				set_client_server_entity_int_value (group, INT_TYPE_ROUTE_NODE, route_node);
			}

			//
			//
			//
			
			member = get_local_entity_first_child (group, LIST_TYPE_MEMBER);

			//
			// close members doors
			//

			close_client_server_entity_cargo_doors (member);

			close_client_server_entity_loading_doors (member);

			//
			// open building doors
			//

			building = get_local_entity_first_child (en, LIST_TYPE_MEMBER);

			open_client_server_entity_loading_doors (building);

			set_local_entity_float_value (building, FLOAT_TYPE_LOADING_DOOR_TIMER, 30.0);

			//
			// create guide entity for task (TEST)
			//

			// Debug for Transport aircraft.
			// Locate nearest Transport landing wp and insert into it
			if (group_database [group_type].default_landing_type == ENTITY_SUB_TYPE_LANDING_FIXED_WING_TRANSPORT)
			{

				float
					range,
					best_range;

				entity
					*transport_wp,
					*transport_task,
					*transport_landing;

				best_range = 999999999.0;

				transport_landing = get_local_entity_landing_entity (keysite, ENTITY_SUB_TYPE_LANDING_FIXED_WING_TRANSPORT);

				if (transport_landing)
				{
	
					transport_task = get_local_landing_entity_task (transport_landing, ENTITY_SUB_TYPE_TASK_LANDING);

					ASSERT (transport_task);
	
					transport_wp = get_local_entity_first_child (transport_task, LIST_TYPE_WAYPOINT);

					ASSERT (transport_wp);
	
					while (transport_wp)
					{
	
						range = get_sqr_2d_range (get_local_entity_vec3d_ptr (transport_wp, VEC3D_TYPE_POSITION), get_local_entity_vec3d_ptr (building, VEC3D_TYPE_POSITION));
	
						if (range < best_range)
						{
	
							wp = transport_wp;
	
							task = transport_task;
	
							best_range = range;
						}
	
						transport_wp = get_local_entity_child_succ (transport_wp, LIST_TYPE_WAYPOINT);
					}
				}
			}
			// Debug for Transport aircraft.

			member_number = get_local_entity_int_value (member, INT_TYPE_GROUP_MEMBER_NUMBER);

			guide = create_client_server_guide_entity (task, wp, (1 << member_number));

			attach_group_to_guide_entity (group, guide);

			attach_group_member_to_guide_entity (member, guide);

			//#if DEBUG_MODULE
			{

				entity
					*keysite;

				keysite = get_local_entity_parent (landing, LIST_TYPE_LANDING_SITE);

				member = get_local_entity_first_child (group, LIST_TYPE_MEMBER);

				debug_log ("RG_UPDT: %s creating %s (%d) at keysite %s free landing sites %d, reserved %d, lock %d, available lock: %d",
						entity_side_names [get_local_entity_int_value (keysite, INT_TYPE_SIDE)],
						get_local_entity_type_name (member),
						get_local_entity_index (member),
						get_local_entity_string (keysite, STRING_TYPE_KEYSITE_NAME), 
						get_local_entity_int_value (landing, INT_TYPE_FREE_LANDING_SITES),
						get_local_entity_int_value (landing, INT_TYPE_RESERVED_LANDING_SITES),
						get_local_entity_int_value (landing, INT_TYPE_LANDING_LOCK),
						check_available_landing_route_lock (landing)
						);

				if ((e1->type == ENTITY_TYPE_FIXED_WING) || (e1->type == ENTITY_TYPE_HELICOPTER))
				{
					debug_log("%s reserves left: %d",
							force_info_catagory_names[aircraft_database[e1->sub_type].force_info_catagory],
							force_raw->force_info_reserve_hardware[aircraft_database[e1->sub_type].force_info_catagory]
							);
				}
				else
				{
					debug_log("%s reserves left: %d",
							force_info_catagory_names[vehicle_database[e1->sub_type].force_info_catagory],
							force_raw->force_info_reserve_hardware[vehicle_database[e1->sub_type].force_info_catagory]
							);
				}

			}
			//#endif

			#if DEBUG_MODULE
			switch (e1->type)
			{
				case ENTITY_TYPE_FIXED_WING:
				case ENTITY_TYPE_HELICOPTER:
				{
					ASSERT (regen_ac_debug[e1->sub_type] > 0);

					break;
				}
				
				case ENTITY_TYPE_ROUTED_VEHICLE:
				case ENTITY_TYPE_SHIP_VEHICLE:
				case ENTITY_TYPE_PERSON:
				{
					ASSERT (regen_vh_debug[e1->sub_type] > 0);

					break;
				}
				
				default:
				{
					debug_fatal ("RG_UPDT: Unknown entity type for debug");
				}
				
			}
			#endif

			// update markers
			regen_queue_use (raw->side, (raw->sub_type));

			return member;
		}
	}
	else
	{
		#if DEBUG_MODULE >= 2

		debug_log ("RG_UPDT: not creating anything at keysite %s free landing sites %d, reserved %d, lock %d",
						get_local_entity_string (keysite, STRING_TYPE_KEYSITE_NAME), 
						get_local_entity_int_value (landing, INT_TYPE_FREE_LANDING_SITES),
						get_local_entity_int_value (landing, INT_TYPE_RESERVED_LANDING_SITES),
						check_available_landing_route_lock (landing));

		#endif
	}

	return NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_regen_sub_type (int type)
{
	int
		regen_type;

	switch (type)
	{
		case ENTITY_TYPE_FIXED_WING:
		{
			regen_type = ENTITY_SUB_TYPE_REGEN_FIXED_WING;

			break;
		}
		
		case ENTITY_TYPE_HELICOPTER:
		{
			regen_type = ENTITY_SUB_TYPE_REGEN_HELICOPTER;

			break;
		}
		
		case ENTITY_TYPE_ROUTED_VEHICLE:
		{
			regen_type = ENTITY_SUB_TYPE_REGEN_GROUND;

			break;
		}
		
		case ENTITY_TYPE_SHIP_VEHICLE:
		{
			regen_type = ENTITY_SUB_TYPE_REGEN_SEA;

			break;
		}
		
		case ENTITY_TYPE_PERSON:
		{
			regen_type = ENTITY_SUB_TYPE_REGEN_PEOPLE;

			break;
		}
		
		case ENTITY_SUB_TYPE_REGEN_NONE:
		{
			debug_fatal ("RG_UPDT: illegal regen sub type: ENTITY_SUB_TYPE_REGEN_NONE");
		}
		
		default:
		{
			debug_fatal ("RG_UPDT: Unknown entity type");
		}
		
	}

	return regen_type;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void add_entity_to_regen_queue (entity_sides side, entity_types type, entity_sub_types sub_type, entity_sub_types group_type)
{
	regen_list_element
		e1;

	int
		regen_type;
		
	e1.type = type;
	e1.sub_type = sub_type;	
	e1.group = group_type;

	// get index into correct queue

	regen_type = get_regen_sub_type (e1.type);

	
#if DEBUG_MODULE

	switch (e1.type)
	{
		case ENTITY_TYPE_FIXED_WING:
		{
			regen_ac_debug[e1.sub_type] = 1;

			break;
		}
		
		case ENTITY_TYPE_HELICOPTER:
		{
			regen_ac_debug[e1.sub_type] = 1;

			break;
		}
		
		case ENTITY_TYPE_ROUTED_VEHICLE:
		{
			regen_vh_debug[e1.sub_type] = 1;

			break;
		}
		
		case ENTITY_TYPE_SHIP_VEHICLE:
		{
			regen_vh_debug[e1.sub_type] = 1;

			break;
		}
		
		case ENTITY_TYPE_PERSON:
		{
			regen_vh_debug[e1.sub_type] = 1;

			break;
		}
		
		default:
		{
			debug_fatal ("RG_UPDT: Unknown entity type");
		}
	}

#endif

	// insert entity into regen queue
	regen_queue_insert (side, regen_type, &e1);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void add_default_entity_to_regen_queue (entity_sides side, entity_sub_types group_type)
{
	switch (side)
	{
		case ENTITY_SIDE_BLUE_FORCE:
		{
			add_entity_to_regen_queue (side,
												group_database [group_type].default_entity_type,
												group_database [group_type].default_blue_force_sub_type,
												group_type);

			break;
		}
		case ENTITY_SIDE_RED_FORCE:
		{
			add_entity_to_regen_queue (side,
												group_database [group_type].default_entity_type,
												group_database [group_type].default_red_force_sub_type,
												group_type);

			break;
		}
		default:
		{
			debug_fatal ("RG_UPDT: Invalid Side %d For Default Entity Regen", side);

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void regen_queue_insert (entity_sides side, int regen_type, regen_list_element *insert_me)
{
	regen_list_element
		*e1;

	regen_management_element
		*m1;

	int
		rear;

	m1 = &regen_manager [side][regen_type];

	ASSERT ((m1->count >= 0) && (m1->count <= m1->size));

	rear = (m1->front + m1->count) % m1->size;

	e1 = &regen_queue [side][regen_type][rear];

	// copy dead entity details into regen queue
	e1->type = insert_me->type;

	e1->sub_type = insert_me->sub_type;

	e1->group = insert_me->group;

	// update queue markers

	if (m1->count == m1->size)
	{
		m1->front = (m1->front + 1) % m1->size;
	}
	else
	{
		m1->count = min ((m1->count + 1), m1->size);
	}
	
	ASSERT ((m1->count >= 0) && (m1->count <= m1->size));
/*
	#if DEBUG_MODULE
	
	debug_log ("INSERTED: Type:%3d Sub:%3d Group:%3d side:%2d",
									e1->type,
									e1->sub_type,
									e1->group,
									side);

	output_regen_data (side, regen_type);

	#endif
	*/
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void regen_queue_use (entity_sides side, int regen_type)
{
	regen_list_element
		*e1;

	regen_management_element
		*m1;

	m1 = &regen_manager [side][regen_type];

	e1 = &regen_queue [side][regen_type][m1->front];

	ASSERT ((m1->count > 0) && (m1->count <= m1->size));
/*
	#if DEBUG_MODULE
	
		debug_log ("REGENED: Type:%d Subtype:%d Group:%d Side:%d",
									e1->type,
									e1->sub_type,
									e1->group,
									side);
	#endif
*/
	// clear the element in the reqen queue - not really neccesary... but good form

	if (regen_type == ENTITY_SUB_TYPE_REGEN_PEOPLE)
	{

		// don't do if person... we want the regen queue always full

		return;
	}

	e1->type = -1;
	e1->sub_type = -1;
	e1->group = -1;

	// update queue front marker

	m1->front = (m1->front + 1) % m1->size;

	m1->count --;

	#if DEBUG_MODULE
	
	output_regen_data (side, regen_type);

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int set_regen_queue_size (regen_management_element *m1, int size)
{
	int
		new_size;

	// set new queue size

	new_size = max (size, REGEN_QUEUE_MINIMUM_SIZE);

	m1->size = new_size;
	
	return new_size;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_regen_queues (void)
{
	regen_management_element
		*m1;

	int
		i,
		j;
		
	memset (regen_manager, 0, sizeof (regen_management_element) * NUM_ENTITY_SIDES * NUM_ENTITY_SUB_TYPE_REGENS);

	for (i = 0; i < NUM_ENTITY_SIDES; i++)
	{
		for (j = 0; j < NUM_ENTITY_SUB_TYPE_REGENS; j++)
		{
			m1 = &regen_manager [i][j];

			if (m1->size <= 0)
			{
				m1->size = REGEN_QUEUE_DEFAULT_SIZE;
			}

			regen_queue [i][j] = safe_malloc (sizeof (regen_list_element) * m1->size);

			memset (regen_queue [i][j], -1, sizeof (regen_list_element) * m1->size);
		}
	}	

	#if HACK_PEOPLE_INTO_REGEN_QUEUE
	{
		int
			i;
		
		for (i = 0; i < 10; i++)
		{
			add_entity_to_regen_queue
			(
				ENTITY_SIDE_BLUE_FORCE,
				ENTITY_TYPE_PERSON,
				ENTITY_SUB_TYPE_VEHICLE_US_INFANTRY,
				ENTITY_SUB_TYPE_GROUP_INFANTRY_PATROL
			);

			add_entity_to_regen_queue
			(
				ENTITY_SIDE_RED_FORCE,
				ENTITY_TYPE_PERSON,
				ENTITY_SUB_TYPE_VEHICLE_CIS_INFANTRY,
				ENTITY_SUB_TYPE_GROUP_INFANTRY_PATROL
			);
		}		
	}
	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int increment_regen_queue_size (entity_sides side, entity_types type, int shift)
{
	regen_list_element
		*e1,
		*temp;

	regen_management_element
		*m1;

	int
		front,
		count,
		old_size,
		new_size,
		regen_type,
		num_elements;

	regen_type = get_regen_sub_type (type);

	m1 = &regen_manager [side][regen_type];

	e1 = &regen_queue [side][regen_type][m1->front];

	#if DEBUG_MODULE

	debug_log ("Growing Regen Queue %s - Type %s by %d", entity_side_short_names [side], entity_sub_type_regen_names [regen_type], shift);

	debug_log ("OLD LIST:");

	output_regen_data (side, regen_type);
	
	#endif

	// copy old queue

	//temp = safe_malloc (sizeof (regen_list_element) * m1->size);

	//memcpy (temp, regen_queue[side][regen_type], sizeof (regen_list_element) * m1->size);

	// get old queue size

	old_size = m1->size;

	// update queue size

	new_size = m1->size + shift;

	// set new size
	
	new_size = set_regen_queue_size (m1, new_size);

	// free old queue

	//safe_free (regen_queue[side][regen_type]);

	// allocate new queue

	//regen_queue[side][regen_type] = safe_malloc (sizeof (regen_list_element) * m1->size);
	temp = safe_malloc (sizeof (regen_list_element) * m1->size);

	//memset (regen_queue [side][regen_type], -1, sizeof (regen_list_element) * m1->size);
	memset (temp, -1, sizeof (regen_list_element) * m1->size);

	count = 0;
	front = m1->front;

	num_elements = min (m1->count, new_size);

	while (count < num_elements)
	{
		//regen_queue[side][regen_type][count].type = temp [front].type;
		//regen_queue[side][regen_type][count].sub_type = temp [front].sub_type;
		//regen_queue[side][regen_type][count].group = temp [front].group;
		temp [count].type = regen_queue[side][regen_type][front].type;
		temp [count].sub_type = regen_queue[side][regen_type][front].sub_type;
		temp [count].group = regen_queue[side][regen_type][front].group;

		count++;

		front = (front + 1) % old_size;
	}

	m1->count = count;
	m1->front = 0;

	safe_free (regen_queue[side][regen_type]);
	regen_queue[side][regen_type] = temp;

	#if DEBUG_MODULE

	debug_log ("NEW LIST:");

	output_regen_data (side, regen_type);
	
	#endif

	return new_size;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if DEBUG_MODULE

void output_regen_data (int side, int regen_type)
{
	regen_list_element
		*e1;

	regen_management_element
		*m1;

	int
		i;
		
	//debug_log ("Regen Data %s - Type %s", entity_side_short_names [side], entity_sub_type_regen_names [regen_type]);

	m1 = &regen_manager [side][regen_type];

/*
	debug_log ("f:%3d   c:%3d   s:%3d",
									m1->front,
									m1->count,
									m1->size);
*/
	for (i = 0; i < m1->size; i++)
	{
		e1 = &regen_queue [side][regen_type][i];
/*
		debug_log ("type:%d subtype:%d group:%d side:%d count:%d",
									e1->type,
									e1->sub_type,
									e1->group,
									side,
									i);
*/
	}
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


