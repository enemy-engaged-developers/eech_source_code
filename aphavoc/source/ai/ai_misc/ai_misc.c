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

#define LANDING_DEBUG 0

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *get_closest_waypoint (entity *task, vec3d *pos, float min_range, float *actual_range)
{

	float
		best_range,
		range;

	vec3d
		*waypoint_pos;

	entity
		*closest_waypoint = NULL,
		*current_waypoint;

	best_range = 99999999;

	current_waypoint = get_local_entity_first_child (task, LIST_TYPE_WAYPOINT);

	while (current_waypoint)
	{

		waypoint_pos = get_local_entity_vec3d_ptr (current_waypoint, VEC3D_TYPE_POSITION);

		range = get_approx_2d_range (waypoint_pos, pos);

		if (actual_range)
		{
	
			*actual_range = range;
		}

		if (range <= min_range)
		{

			#if LANDING_DEBUG >= 2

			debug_log ("AI_MISC: EARLY OUT: found waypoint %d (type %d) range %f", current_waypoint, entity_sub_type_waypoint_names [get_local_entity_int_value (current_waypoint, INT_TYPE_ENTITY_SUB_TYPE)], range);

			#endif

			return current_waypoint;
		}

		if (range < best_range)
		{

			best_range = range;

			closest_waypoint = current_waypoint;

			#if LANDING_DEBUG

			debug_log ("AI_MISC: found waypoint %d (type %d) range %f", current_keysite, entity_sub_type_waypoint_names [get_local_entity_int_value (current_waypoint, INT_TYPE_ENTITY_SUB_TYPE)], range);

			#endif
		}

		current_waypoint = get_local_entity_child_succ (current_waypoint, LIST_TYPE_WAYPOINT);
	} 

	if ( closest_waypoint )
	{

		waypoint_pos = get_local_entity_vec3d_ptr (closest_waypoint, VEC3D_TYPE_POSITION);

		best_range = get_2d_range (waypoint_pos, pos);
	}

	if (actual_range)
	{

		*actual_range = best_range;
	}

	return closest_waypoint;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *get_closest_halfway_waypoint (entity *task, vec3d *pos, float min_range, float *actual_range)
{

	float
		best_range,
		range;

	vec3d
		*waypoint_pos1,
		*waypoint_pos2,
		mid_pos;

	entity
		*closest_waypoint = NULL,
		*waypoint1,
		*waypoint2;

	best_range = 99999999;

	waypoint1 = get_local_entity_first_child (task, LIST_TYPE_WAYPOINT);
	waypoint2 = get_local_entity_child_succ (waypoint1, LIST_TYPE_WAYPOINT);

	while (waypoint2)
	{

		waypoint_pos1 = get_local_entity_vec3d_ptr (waypoint1, VEC3D_TYPE_POSITION);
		waypoint_pos2 = get_local_entity_vec3d_ptr (waypoint2, VEC3D_TYPE_POSITION);

		mid_pos.x = waypoint_pos1->x + ( ( waypoint_pos2->x - waypoint_pos1->x ) / 2 );
		mid_pos.y = waypoint_pos1->y + ( ( waypoint_pos2->y - waypoint_pos1->y ) / 2 );
		mid_pos.z = waypoint_pos1->z + ( ( waypoint_pos2->z - waypoint_pos1->z ) / 2 );

		range = get_approx_2d_range (&mid_pos, pos);

		if (range < best_range)
		{

			best_range = range;
			closest_waypoint = waypoint1;
		}

		waypoint1 = waypoint2;
		waypoint2 = get_local_entity_child_succ (waypoint2, LIST_TYPE_WAYPOINT);
	}

	if ( closest_waypoint )
	{

		waypoint1 = closest_waypoint;
		waypoint2 = get_local_entity_child_succ (waypoint1, LIST_TYPE_WAYPOINT);

		waypoint_pos1 = get_local_entity_vec3d_ptr (waypoint1, VEC3D_TYPE_POSITION);
		waypoint_pos2 = get_local_entity_vec3d_ptr (waypoint2, VEC3D_TYPE_POSITION);

		mid_pos.x = waypoint_pos1->x + ( ( waypoint_pos2->x - waypoint_pos1->x ) / 2 );
		mid_pos.y = waypoint_pos1->y + ( ( waypoint_pos2->y - waypoint_pos1->y ) / 2 );
		mid_pos.z = waypoint_pos1->z + ( ( waypoint_pos2->z - waypoint_pos1->z ) / 2 );

		best_range = get_2d_range (&mid_pos, pos);
	}

	if (actual_range)
	{

		*actual_range = best_range;
	}

	return ( closest_waypoint );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *get_closest_free_landing_site (entity_sub_types sub_type, entity *force, vec3d *pos, float min_range, float *actual_range, int sites_required)
{

	int
		sites_available;

	float
		best_range,
		range;

	vec3d
		*landing_pos;

	entity
		*closest_landing = NULL,
		*current_keysite,
		*current_landing;

	best_range = 99999999;

	current_keysite = get_local_entity_first_child (force, LIST_TYPE_KEYSITE_FORCE);

	while (current_keysite)
	{
		if (get_local_entity_int_value (current_keysite, INT_TYPE_IN_USE))
		{
			if (get_local_entity_int_value (current_keysite, INT_TYPE_KEYSITE_USABLE_STATE) == KEYSITE_STATE_USABLE)
			{
				current_landing = get_local_entity_first_child (current_keysite, LIST_TYPE_LANDING_SITE);
		
				while (current_landing)
				{
		
					if (get_local_entity_int_value (current_landing, INT_TYPE_ENTITY_SUB_TYPE) == sub_type)
					{
		
						sites_available = get_local_entity_int_value (current_landing, INT_TYPE_FREE_LANDING_SITES) - get_local_entity_int_value (current_landing, INT_TYPE_RESERVED_LANDING_SITES);
		
						if (sites_available >= sites_required)
						{
		
							landing_pos = get_local_entity_vec3d_ptr (current_landing, VEC3D_TYPE_POSITION);
		
							range = get_approx_2d_range (landing_pos, pos);
	
							#if DEBUG_MODULE
	
							debug_log ("AI_MISC: assessing keysite %s range %f", get_local_entity_string (current_keysite, STRING_TYPE_KEYSITE_NAME), range);
	
							#endif
		
							if (range <= min_range)
							{
		
								#if LANDING_DEBUG >= 2
		
								debug_log ("AI_MISC: EARLY OUT: found key landing site type %d range %f, total %d, free %d, reserved %d",
									get_local_entity_int_value (current_landing, INT_TYPE_ENTITY_SUB_TYPE),
									range,
									get_local_entity_int_value (current_landing, INT_TYPE_TOTAL_LANDING_SITES),
									get_local_entity_int_value (current_landing, INT_TYPE_FREE_LANDING_SITES),
									get_local_entity_int_value (current_landing, INT_TYPE_RESERVED_LANDING_SITES));
		
								#endif
		
								if (actual_range)
								{
									*actual_range = range;	
								}
	
								return current_landing;
							}
		
							if (range < best_range)
							{
		
								best_range = range;
		
								closest_landing = current_landing;
		
								#if LANDING_DEBUG
		
								debug_log ("AI_MISC: found %s landing site type %d range %f, total %d, free %d, reserved %d",
									get_local_entity_string (current_keysite, STRING_TYPE_KEYSITE_NAME),
									get_local_entity_int_value (current_landing, INT_TYPE_ENTITY_SUB_TYPE),
									range,
									get_local_entity_int_value (current_landing, INT_TYPE_TOTAL_LANDING_SITES),
									get_local_entity_int_value (current_landing, INT_TYPE_FREE_LANDING_SITES),
									get_local_entity_int_value (current_landing, INT_TYPE_RESERVED_LANDING_SITES));
		
								#endif
							}
						}
					}
		
					current_landing = get_local_entity_child_succ (current_landing, LIST_TYPE_LANDING_SITE);
				}
			}
		}
		
		current_keysite = get_local_entity_child_succ (current_keysite, LIST_TYPE_KEYSITE_FORCE);
	}

	if (actual_range)
	{
		*actual_range = best_range;
	}

	//
	// DEBUG
	//

	if (!closest_landing)
	{

		debug_log ("AI_MISC: FAILED GET CLOSEST LANDING_SITE !!!!!!!!!!!!");

		debug_log ("	searching for %d %s landing sites", sites_required, entity_sub_type_landing_names [sub_type]);

		current_keysite = get_local_entity_first_child (force, LIST_TYPE_KEYSITE_FORCE);

		while (current_keysite)
		{

			current_landing = get_local_entity_first_child (current_keysite, LIST_TYPE_LANDING_SITE);

			while (current_landing)
			{

				landing_pos = get_local_entity_vec3d_ptr (current_landing, VEC3D_TYPE_POSITION);

				range = get_approx_2d_range (landing_pos, pos);

				debug_log ("	found %s landing site type %s use %d, range %f, total %d, free %d, reserved %d",
								get_local_entity_string (current_keysite, STRING_TYPE_KEYSITE_NAME),
								entity_sub_type_landing_names [get_local_entity_int_value (current_landing, INT_TYPE_ENTITY_SUB_TYPE)],
								get_local_entity_int_value (current_keysite, INT_TYPE_IN_USE),
								range,
								get_local_entity_int_value (current_landing, INT_TYPE_TOTAL_LANDING_SITES),
								get_local_entity_int_value (current_landing, INT_TYPE_FREE_LANDING_SITES),
								get_local_entity_int_value (current_landing, INT_TYPE_RESERVED_LANDING_SITES));

				current_landing = get_local_entity_child_succ (current_landing, LIST_TYPE_LANDING_SITE);
			}

			current_keysite = get_local_entity_child_succ (current_keysite, LIST_TYPE_KEYSITE_FORCE);
		}
		{
		
			int
				sites_available;
		
			float
				best_range,
				range;
		
			vec3d
				*landing_pos;
		
			entity
				*closest_landing = NULL,
				*current_keysite,
				*current_landing;
		
			best_range = 99999999;
		
			current_keysite = get_local_entity_first_child (force, LIST_TYPE_KEYSITE_FORCE);
		
			while (current_keysite)
			{
				if (get_local_entity_int_value (current_keysite, INT_TYPE_IN_USE))
				{
					if (get_local_entity_int_value (current_keysite, INT_TYPE_KEYSITE_USABLE_STATE) == KEYSITE_STATE_USABLE)
					{
						current_landing = get_local_entity_first_child (current_keysite, LIST_TYPE_LANDING_SITE);
				
						while (current_landing)
						{
				
							if (get_local_entity_int_value (current_landing, INT_TYPE_ENTITY_SUB_TYPE) == sub_type)
							{
				
								sites_available = get_local_entity_int_value (current_landing, INT_TYPE_FREE_LANDING_SITES) - get_local_entity_int_value (current_landing, INT_TYPE_RESERVED_LANDING_SITES);
				
								if (sites_available >= sites_required)
								{
				
									landing_pos = get_local_entity_vec3d_ptr (current_landing, VEC3D_TYPE_POSITION);
				
									range = get_approx_2d_range (landing_pos, pos);
			
									if (range <= min_range)
									{
				
										if (actual_range)
										{
											*actual_range = range;
										}
	
										debug_log ("AI_MISC: found keysite %s", get_local_entity_string (current_keysite, STRING_TYPE_KEYSITE_NAME));
									}
				
									if (range < best_range)
									{
				
										best_range = range;
				
										closest_landing = current_landing;
									}
								}
							}
				
							current_landing = get_local_entity_child_succ (current_landing, LIST_TYPE_LANDING_SITE);
						}
					}
				}
		
				current_keysite = get_local_entity_child_succ (current_keysite, LIST_TYPE_KEYSITE_FORCE);
			}
		
			if (actual_range)
			{
				*actual_range = best_range;
			}

			//debug_log ("AI_MISC: found keysite %s", get_local_entity_string (current_keysite, STRING_TYPE_KEYSITE_NAME));
		}
	}

	//
	// END
	//

	//ASSERT (closest_landing);

	return closest_landing;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_closest_road_node (vec3d *pos, float error)
{

	int
		loop,
		best_node = 0;

	float
		range,
		best_range;

	ASSERT (pos);
		
	ASSERT (road_node_positions);

	best_range = 99999999;

	for (loop = 0; loop < total_number_of_road_nodes; loop ++)
	{

		if (road_nodes [loop].number_of_links > 0)
		{
	
			range = get_approx_2d_range (&road_node_positions [loop], pos);
	
			if (range < best_range)
			{
	
				best_range = range;
	
				best_node = loop;
	
				if (range <= error)
				{
	
					return best_node;
				}
			}
		}
	}

	#if LANDING_DEBUG >= 3

	debug_log ("ROAD ROUTE: closest node to %f, %f is node %d at %f, %f", x, z, best_node, road_node_positions [best_node].x, road_node_positions [best_node].z);

	#endif

	return best_node;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_closest_side_road_node (entity_sides side, vec3d *pos, float error)
{

	int
		loop,
		best_node = 0;

	float
		range,
		best_range;

	ASSERT (pos);
		
	ASSERT (road_node_positions);

	best_range = 99999999;

	for (loop = 0; loop < total_number_of_road_nodes; loop ++)
	{

//		if (road_nodes [loop].side_aware & side)
		{

			if (road_nodes [loop].number_of_links > 0)
			{
		
				range = get_approx_2d_range (&road_node_positions [loop], pos);
		
				if (range < best_range)
				{
		
					best_range = range;
		
					best_node = loop;
		
					if (range <= error)
					{
		
						return best_node;
					}
				}
			}
		}
	}

	#if LANDING_DEBUG >= 3

	debug_log ("ROAD ROUTE: closest node to %f, %f is node %d at %f, %f", x, z, best_node, road_node_positions [best_node].x, road_node_positions [best_node].z);

	#endif

	return best_node;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int validate_landing_route (entity *route_task)
{

	int
		count;

	entity_sub_types
		type;

	entity
		*landing_en,
		*keysite_en,
		*wp;

	formation_types
		route_formation,
		wp_formation;

	landing_en = get_local_entity_parent (route_task, LIST_TYPE_ASSIGNED_TASK);

	keysite_en = get_local_entity_parent (landing_en, LIST_TYPE_LANDING_SITE);

	#if DEBUG_MODULE

	debug_log ("Route Parsing: Keysite %s, landing %s, side %s, route %s",
					get_local_entity_string (keysite_en, STRING_TYPE_KEYSITE_NAME),
					entity_sub_type_landing_names [get_local_entity_int_value (landing_en, INT_TYPE_ENTITY_SUB_TYPE)],
					entity_side_names [get_local_entity_int_value (keysite_en, INT_TYPE_SIDE)],
					entity_sub_type_task_names [get_local_entity_int_value (route_task, INT_TYPE_ENTITY_SUB_TYPE)]);

	#endif

	switch (get_local_entity_int_value (route_task, INT_TYPE_ENTITY_SUB_TYPE))
	{

		case ENTITY_SUB_TYPE_TASK_LANDING:
		{

			switch (get_local_entity_int_value (landing_en, INT_TYPE_ENTITY_SUB_TYPE))
			{

				case ENTITY_SUB_TYPE_LANDING_FIXED_WING:
				{

					//
					// Navigation waypoint
					//
		
					wp = get_local_entity_first_child (route_task, LIST_TYPE_WAYPOINT);

					if (wp)
					{
	
						type = get_local_entity_int_value (wp, INT_TYPE_ENTITY_SUB_TYPE);
	
						count = 0;
			
						while (type != ENTITY_SUB_TYPE_WAYPOINT_LANDED)
						{
			
							if ((type != ENTITY_SUB_TYPE_WAYPOINT_NAVIGATION) &&
								(type != ENTITY_SUB_TYPE_WAYPOINT_TOUCH_DOWN))
							{
			
								debug_fatal ("WARNING. Route parser failed on landing route. Non nav waypoint in route");
							}
	
							if (type == ENTITY_SUB_TYPE_WAYPOINT_TOUCH_DOWN)
							{
	
								count ++;
							}
			
							wp = get_local_entity_child_succ (wp, LIST_TYPE_WAYPOINT);
			
							type = get_local_entity_int_value (wp, INT_TYPE_ENTITY_SUB_TYPE);
						}
	
						if (count != 1)
						{
	
							debug_fatal ("WARNING. Route parser failed on takeoff route. Incorrect number of Touch down waypoints");
						}
	
						//
						// Landed
						//
			
						if (type != ENTITY_SUB_TYPE_WAYPOINT_LANDED)
						{
			
							debug_fatal ("WARNING. Route parser failed on landing route. Landed waypoint not in correct place");
						}
	
						//
						// Extras
						//
			
						if (get_local_entity_child_succ (wp, LIST_TYPE_WAYPOINT))
						{
			
							debug_fatal ("WARNING. Route parser failed on landing route. Waypoint present after Landed waypoint");
						}
					}
					else
					{

						debug_log ("WARNING. Route parser. No Waypoint present in Landing route");
					}

					break;
				}

				case ENTITY_SUB_TYPE_LANDING_HELICOPTER:
				case ENTITY_SUB_TYPE_LANDING_GROUND:
				case ENTITY_SUB_TYPE_LANDING_SEA:
				{

					//
					// Navigations
					//
		
					wp = get_local_entity_first_child (route_task, LIST_TYPE_WAYPOINT);

					if (wp)
					{
			
						while (get_local_entity_child_succ (wp, LIST_TYPE_WAYPOINT))
						{
			
							type = get_local_entity_int_value (wp, INT_TYPE_ENTITY_SUB_TYPE);
			
							if (type != ENTITY_SUB_TYPE_WAYPOINT_NAVIGATION)
							{
			
								debug_fatal ("WARNING. Route parser failed on landing route. Non nav waypoint in route");
							}
			
							wp = get_local_entity_child_succ (wp, LIST_TYPE_WAYPOINT);
						}
	
						//
						// Landed
						//
			
						type = get_local_entity_int_value (wp, INT_TYPE_ENTITY_SUB_TYPE);
			
						if (type != ENTITY_SUB_TYPE_WAYPOINT_LANDED)
						{
			
							debug_fatal ("WARNING. Route parser failed on landing route. Landed waypoint not in correct place");
						}
	
						//
						// Extras
						//
			
						if (get_local_entity_child_succ (wp, LIST_TYPE_WAYPOINT))
						{
			
							debug_fatal ("WARNING. Route parser failed on landing route. Waypoint present after Landed waypoint");
						}
					}
					else
					{

						debug_log ("WARNING. Route parser. No Waypoint present in Landing route");
					}
		
					break;
				}
			}

			break;
		}

		case ENTITY_SUB_TYPE_TASK_TAKEOFF:
		{

			switch (get_local_entity_int_value (landing_en, INT_TYPE_ENTITY_SUB_TYPE))
			{

				case ENTITY_SUB_TYPE_LANDING_FIXED_WING:
				{

					//
					// Navigation waypoints
					//

					count = 0;
		
					wp = get_local_entity_first_child (route_task, LIST_TYPE_WAYPOINT);

					if (wp)
					{
			
						route_formation = get_local_entity_int_value (wp, INT_TYPE_WAYPOINT_FORMATION);
			
						type = get_local_entity_int_value (wp, INT_TYPE_ENTITY_SUB_TYPE);
			
						while (type != ENTITY_SUB_TYPE_WAYPOINT_TAKEN_OFF)
						{
			
							wp_formation = get_local_entity_int_value (wp, INT_TYPE_WAYPOINT_FORMATION);
		/*
							if (route_formation != wp_formation)
							{
			
								debug_fatal ("WARNING. Route parser failed on takeoff formation, route %s, wp %s",
												get_formation_name (route_formation), get_formation_name (wp_formation));
							}
		*/
							if ((type != ENTITY_SUB_TYPE_WAYPOINT_NAVIGATION) &&
								(type != ENTITY_SUB_TYPE_WAYPOINT_LIFT_OFF) &&
								(type != ENTITY_SUB_TYPE_WAYPOINT_START_UP))
							{
			
								debug_fatal ("WARNING. Route parser failed on takeoff route. Non nav / lift off / startup waypoint in route");
							}
	
							if (type == ENTITY_SUB_TYPE_WAYPOINT_LIFT_OFF)
							{
	
								count ++;
							}
			
							wp = get_local_entity_child_succ (wp, LIST_TYPE_WAYPOINT);
			
							type = get_local_entity_int_value (wp, INT_TYPE_ENTITY_SUB_TYPE);
						}
	
						if (count != 1)
						{
	
							debug_fatal ("WARNING. Route parser failed on takeoff route. Incorrect number of Lift off waypoints");
						}
	
						//
						// taken off waypoint
						//
			
						wp_formation = get_local_entity_int_value (wp, INT_TYPE_WAYPOINT_FORMATION);
		/*
						if (route_formation != wp_formation)
						{
			
							debug_fatal ("WARNING. Route parser failed on takeoff formation, route %s, wp %s",
											get_formation_name (route_formation), get_formation_name (wp_formation));
						}
		*/
						if (type != ENTITY_SUB_TYPE_WAYPOINT_TAKEN_OFF)
						{
			
							debug_fatal ("WARNING. Route parser failed on takeoff route. Taken off waypoint not in correct place");
						}
	
						//
						// Extras
						//
			
						if (get_local_entity_child_succ (wp, LIST_TYPE_WAYPOINT))
						{
			
							debug_fatal ("WARNING. Route parser failed on landing route. Waypoint present after Take off waypoint");
						}
					}
					else
					{

						debug_log ("WARNING. Route parser. No Waypoint present in Takeoff route");
					}

					break;
				}

				case ENTITY_SUB_TYPE_LANDING_HELICOPTER:
				case ENTITY_SUB_TYPE_LANDING_GROUND:
				case ENTITY_SUB_TYPE_LANDING_SEA:
				{

					//
					// Navigation waypoints
					//
		
					wp = get_local_entity_first_child (route_task, LIST_TYPE_WAYPOINT);

					if (wp)
					{
			
						route_formation = get_local_entity_int_value (wp, INT_TYPE_WAYPOINT_FORMATION);
			
						while (get_local_entity_child_succ (wp, LIST_TYPE_WAYPOINT))
						{
			
							wp_formation = get_local_entity_int_value (wp, INT_TYPE_WAYPOINT_FORMATION);
		/*
							if (route_formation != wp_formation)
							{
			
								debug_fatal ("WARNING. Route parser failed on takeoff formation, route %s, wp %s",
												get_formation_name (route_formation), get_formation_name (wp_formation));
							}
		*/
							type = get_local_entity_int_value (wp, INT_TYPE_ENTITY_SUB_TYPE);
			
							if (type != ENTITY_SUB_TYPE_WAYPOINT_NAVIGATION)
							{
			
								debug_fatal ("WARNING. Route parser failed on takeoff route. Non nav waypoint in route");
							}
			
							wp = get_local_entity_child_succ (wp, LIST_TYPE_WAYPOINT);
						}
	
						//
						// taken off waypoint
						//
			
						wp_formation = get_local_entity_int_value (wp, INT_TYPE_WAYPOINT_FORMATION);
		/*
						if (route_formation != wp_formation)
						{
			
							debug_fatal ("WARNING. Route parser failed on takeoff formation, route %s, wp %s",
											get_formation_name (route_formation), get_formation_name (wp_formation));
						}
		*/
						type = get_local_entity_int_value (wp, INT_TYPE_ENTITY_SUB_TYPE);
			
						if (type != ENTITY_SUB_TYPE_WAYPOINT_TAKEN_OFF)
						{
			
							debug_fatal ("WARNING. Route parser failed on takeoff route. Taken off waypoint not in correct place");
						}
	
						//
						// Extras
						//
			
						if (get_local_entity_child_succ (wp, LIST_TYPE_WAYPOINT))
						{
			
							debug_fatal ("WARNING. Route parser failed on landing route. Waypoint present after Take off waypoint");
						}
					}
					else
					{

						debug_log ("WARNING. Route parser. No Waypoint present in Takeoff route");
					}

					break;
				}
			}

			break;
		}

		case ENTITY_SUB_TYPE_TASK_LANDING_HOLDING:
		case ENTITY_SUB_TYPE_TASK_TAKEOFF_HOLDING:
		{

			//
			// Navigation waypoint
			//

			wp = get_local_entity_first_child (route_task, LIST_TYPE_WAYPOINT);

			if (wp)
			{
	
				while (get_local_entity_child_succ (wp, LIST_TYPE_WAYPOINT))
				{
	
					type = get_local_entity_int_value (wp, INT_TYPE_ENTITY_SUB_TYPE);
/*
					if (type != ENTITY_SUB_TYPE_WAYPOINT_HOLDING)
					{
	
						debug_fatal ("WARNING. Route parser failed on holding route. Non holding waypoint in route");
					}
				*/
	
					wp = get_local_entity_child_succ (wp, LIST_TYPE_WAYPOINT);
				}
	
				//
				// loop waypoint
				//
	
				type = get_local_entity_int_value (wp, INT_TYPE_ENTITY_SUB_TYPE);
	
				if (type != ENTITY_SUB_TYPE_WAYPOINT_HOLDING_LOOP)
				{
	
					debug_fatal ("WARNING. Route parser failed on holding route. Loop waypoint not in correct place");
				}
	
				//
				// Extras
				//
	
				if (get_local_entity_child_succ (wp, LIST_TYPE_WAYPOINT))
				{
	
					debug_fatal ("WARNING. Route parser failed on landing route. Waypoint present after Loop waypoint");
				}
			}
			else
			{

				debug_log ("WARNING. Route parser. No Waypoint present in Loop route");
			}

			break;
		}
	}

	#if DEBUG_MODULE

	debug_log ("Landing Route Parsing Complete");

	#endif

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *get_closest_mobile_entity (vec3d *pos)
{

	entity
		*closest_en = NULL,
		*en;

	int
		range,
		best_range = INT_MAX;

	vec3d
		pos2,
		test_pos;

	en = get_local_entity_list ();

	while (en)
	{

		if (get_local_entity_int_value (en, INT_TYPE_IDENTIFY_MOBILE))
		{
	
			get_local_entity_vec3d (en, VEC3D_TYPE_POSITION, &pos2);
	
			test_pos.x = pos->x - pos2.x;
	
			test_pos.y = 0.0;
	
			test_pos.z = pos->z - pos2.z;
	
			range = get_3d_vector_magnitude (&test_pos);
	
			if (range < best_range)
			{
	
				best_range = range;
	
				closest_en = en;
	
				if (range < 1.0)
				{
				
					return closest_en;
				}
			}
		}

		en = get_local_entity_succ (en);
	}
	
	return closest_en;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
