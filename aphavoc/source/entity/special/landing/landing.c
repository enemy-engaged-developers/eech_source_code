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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE 0

#define DEBUG_LANDING_TYPE (1 << ENTITY_SUB_TYPE_LANDING_FIXED_WING)

#define DEBUG_LANDING_SIDE ((1 << ENTITY_SIDE_RED_FORCE) & (1 << ENTITY_SIDE_BLUE_FORCE))

#define FATAL	1

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *get_local_entity_landing_entity (entity *en, entity_sub_types landing_type)
{

	entity
		*landing_entity;

	ASSERT (get_local_entity_type (en) == ENTITY_TYPE_KEYSITE);

	landing_entity = get_local_entity_first_child (en, LIST_TYPE_LANDING_SITE);

	while (landing_entity)
	{

		if (get_local_entity_int_value (landing_entity, INT_TYPE_ENTITY_SUB_TYPE) == landing_type)
		{

			return landing_entity;
		}

		landing_entity = get_local_entity_child_succ (landing_entity, LIST_TYPE_LANDING_SITE);
	}

	return NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *get_local_landing_entity_route (entity *landing_en, entity_sub_types type)
{

	entity
		*task,
		*wp;

	if (landing_en->type != ENTITY_TYPE_LANDING)
	{

		// not even a landing entity

		return NULL;
	}

	task = get_local_entity_first_child (landing_en, LIST_TYPE_ASSIGNED_TASK);

	//

	while (task)
	{

		if (get_local_entity_int_value (task, INT_TYPE_ENTITY_SUB_TYPE) == type)
		{

			wp = get_local_entity_first_child (task, LIST_TYPE_WAYPOINT);

			return wp;
		}

		task = get_local_entity_child_succ (task, LIST_TYPE_ASSIGNED_TASK);
	}

	return NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *get_local_landing_entity_task (entity *landing_en, entity_sub_types type)
{

	entity
		*task;

	ASSERT (landing_en->type == ENTITY_TYPE_LANDING);

	task = get_local_entity_first_child (landing_en, LIST_TYPE_ASSIGNED_TASK);

	//

	while (task)
	{

		if (get_local_entity_int_value (task, INT_TYPE_ENTITY_SUB_TYPE) == type)
		{

			return task;
		}

		task = get_local_entity_child_succ (task, LIST_TYPE_ASSIGNED_TASK);
	}

	return NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *get_local_group_member_landing_entity_from_keysite (entity *en)
{
	entity
		*group,
		*keysite,
		*landing;

	entity_sub_types
		group_type;

	landing = NULL;

	group = get_local_entity_parent (en, LIST_TYPE_MEMBER);

	if (group)
	{
		keysite = get_local_entity_parent (group, LIST_TYPE_KEYSITE_GROUP);

		if ((keysite) && (get_local_entity_type (keysite) == ENTITY_TYPE_KEYSITE))
		{
			group_type = get_local_entity_int_value (group, INT_TYPE_ENTITY_SUB_TYPE);

			landing = get_local_entity_landing_entity (keysite, group_database [group_type].default_landing_type);
		}
	}

	return landing;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *get_local_group_member_landing_entity_from_task (entity *en)
{
	entity
		*task,
		*guide,
		*landing;

	landing = NULL;

	guide = get_local_entity_parent (en, LIST_TYPE_FOLLOWER);

	if (guide)
	{

		task = get_local_entity_parent (guide, LIST_TYPE_GUIDE);

		if (task)
		{

			landing = get_local_entity_parent (task, LIST_TYPE_ASSIGNED_TASK);
		}
	}

	return landing;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if 0
void set_local_landing_route_clear (entity *task, entity *en)
{

	formation_type
		*formation_data;

	entity
		*wp;

	unsigned int
		formation_position,
		formation_check,
		wp_value;

	ASSERT (en);

	ASSERT (task);

	//
	// Clear landing route for this member
	//

	wp = get_local_entity_first_child (task, LIST_TYPE_WAYPOINT);

	// get members group position, not'ed.

	formation_position = get_local_entity_int_value (en, INT_TYPE_FORMATION_POSITION);
	
	// Clear members flag in waypoint route

	#if DEBUG_MODULE

	debug_log ("LANDING: clearing %s route for %s (%d: index %d) pos %d", get_local_entity_string (task, STRING_TYPE_FULL_NAME), get_local_entity_string (en, STRING_TYPE_FULL_NAME), get_local_entity_index (en), get_local_entity_index (en), formation_position);

	#endif

	while (wp)
	{

		formation_data = get_formation (get_local_entity_int_value (wp, INT_TYPE_WAYPOINT_FORMATION));

		formation_check = formation_position % formation_data->number_in_formation;
	
		formation_check = ~(1 << formation_check);

		// members reached

		wp_value = get_local_entity_int_value (wp, INT_TYPE_MEMBERS_REACHED);

		wp_value &= formation_check;

		set_local_entity_int_value (wp, INT_TYPE_MEMBERS_REACHED, wp_value);

		// members waiting

		wp_value = get_local_entity_int_value (wp, INT_TYPE_MEMBERS_WAITING);

		wp_value &= formation_position;

		set_local_entity_int_value (wp, INT_TYPE_MEMBERS_WAITING, wp_value);

		// members pursuing

		wp_value = get_local_entity_int_value (wp, INT_TYPE_MEMBERS_PURSUING);

		wp_value &= formation_position;

		set_local_entity_int_value (wp, INT_TYPE_MEMBERS_PURSUING, wp_value);

		//
		//
		//
	
		wp = get_local_entity_child_succ (wp, LIST_TYPE_WAYPOINT);
	}
}
#endif
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void validate_landing_entity_routes (entity *en)
{

	entity_sides
		side;

	formation_type
		*formation_data;

	entity
		*ts,
		*ks,
		*gd,
		*gp,
		*mb,
		*wp,
		*task;

	unsigned int
		landed_flags,
		landing_flags,
		takeoff_flags,
		formation_position,
		waypoint_formation,
		landing_holding_flags;

	landing
		*raw;

	raw = get_local_entity_data (en);

	side = get_local_entity_int_value (get_local_entity_parent (en, LIST_TYPE_LANDING_SITE), INT_TYPE_SIDE);

	if (((1 << raw->sub_type) & (DEBUG_LANDING_TYPE)) && (DEBUG_LANDING_SIDE & (1 << side)))
	{
	
		/////////////////////////////////////////////////////////////////
		//
		// Check landing route locks are valid
		//
		/////////////////////////////////////////////////////////////////
	
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//
		// LANDING ROUTE
		//
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
		#if DEBUG_MODULE
	
		debug_log ("LANDING: -------------------- checking routes for %s, (%d) --------------------------", entity_sub_type_landing_names [raw->sub_type], get_local_entity_index (en));
	
		#endif
	
		task = get_local_landing_entity_task (en, ENTITY_SUB_TYPE_TASK_LANDING);
	
		wp = get_local_entity_first_child (task, LIST_TYPE_WAYPOINT);
	
		#if DEBUG_MODULE
	
		debug_log ("LANDING: Landing route lock = %d, landed route lock = %d", raw->landing_lock, raw->landed_lock);
	
		#endif
	
		//
		// count up landing route
		//
	
		// landing
	
		landing_flags = 0;
	
		waypoint_formation = get_local_entity_int_value (wp, INT_TYPE_WAYPOINT_FORMATION);
	
		formation_data = get_formation (waypoint_formation);
	
		while (wp)
		{
	
			gd = get_local_entity_first_child (wp, LIST_TYPE_CURRENT_WAYPOINT);

			while (gd)
			{
	
				if (get_local_entity_type (gd) == ENTITY_TYPE_GUIDE)
				{
			
					mb = get_local_entity_first_child (gd, LIST_TYPE_FOLLOWER);
		
					if (mb)
					{
		
						if (get_local_entity_int_value (mb, INT_TYPE_IDENTIFY_MOBILE))
						{
				
							if ((!get_local_entity_int_value (mb, INT_TYPE_LANDED)) && (get_local_entity_int_value (mb, INT_TYPE_PLAYER) == ENTITY_PLAYER_AI))
							{
					
								//
								// check that landing mb has landing route locked
								//
					
								formation_position = get_local_entity_int_value (mb, INT_TYPE_FORMATION_POSITION);
					
								formation_position %= formation_data->number_in_formation;
					
								#if FATAL
		
								ASSERT (!(landing_flags & (1 << formation_position)));
		
								#endif
					
								landing_flags |= 1 << formation_position;
					
								#if DEBUG_MODULE
				
								#if LANDING_LOCK_USER_ONLY
								if (mb == get_gunship_entity ())
								#endif
								debug_log ("LANDING: member %s (%d) has lock on landing route (formation %s). Position %d, route position %d, state %s",
											entity_type_names [mb->type],
											get_local_entity_index (mb),
											get_formation_name (waypoint_formation),
											get_local_entity_int_value (mb, INT_TYPE_FORMATION_POSITION),
											1 << formation_position,
											operational_state_names [get_local_entity_int_value (mb, INT_TYPE_OPERATIONAL_STATE)]);
				
								#endif
							}
						}
			
						//mb = get_local_entity_child_succ (mb, LIST_TYPE_CURRENT_WAYPOINT);
					}
				}

				gd = get_local_entity_child_succ (gd, LIST_TYPE_CURRENT_WAYPOINT);
			}
	
			wp = get_local_entity_child_succ (wp, LIST_TYPE_WAYPOINT);
		}
	
		#if DEBUG_MODULE
	
		debug_log ("LANDING: members on landing route = %d", landing_flags);
	
		#endif
	
		#if FATAL

		ASSERT (raw->landing_lock == landing_flags);

		#endif
	
		//
		// Landed
		//

		ks = get_local_entity_parent (en, LIST_TYPE_LANDING_SITE);
	
		landed_flags = 0;

		gp = get_local_entity_first_child (ks, LIST_TYPE_KEYSITE_GROUP);

		while (gp)
		{

			if (group_database [get_local_entity_int_value (gp, INT_TYPE_ENTITY_SUB_TYPE)].default_landing_type == get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE))
			{
		
				mb = get_local_entity_first_child (gp, LIST_TYPE_MEMBER);
	
				while (mb)
				{

					gd = get_local_entity_parent (mb, LIST_TYPE_FOLLOWER);

					ts = NULL;

					if (gd)
					{

						ts = get_local_entity_parent (gd, LIST_TYPE_GUIDE);
					}
		
	  				// if no task or task == landing_task the entity has a lock on the landed_lock
					if ((!ts) ||
						(get_local_entity_int_value (ts, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_TASK_LANDING) ||
						(get_local_entity_parent (mb, LIST_TYPE_TAKEOFF_QUEUE)))
					{
			
						//
						// check that landed mb has landed lock
						//
				
						formation_position = get_local_entity_int_value (mb, INT_TYPE_FORMATION_POSITION);
				
						formation_position %= raw->total_landing_sites;
				
						#if FATAL
			
						ASSERT (!(landed_flags & (1 << formation_position)));
			
						#endif
				
						landed_flags |= 1 << formation_position;
				
						#if DEBUG_MODULE
			
						#if LANDING_LOCK_USER_ONLY
						if (mb == get_gunship_entity ())
						#endif
						debug_log ("LANDING: member %s (%d) has lock on landed lock. Position %d, landed position %d", entity_type_names [mb->type], get_local_entity_index (mb), get_local_entity_int_value (mb, INT_TYPE_FORMATION_POSITION), 1 << formation_position);
			
						#endif
					}
	
					mb = get_local_entity_child_succ (mb, LIST_TYPE_MEMBER);
				}
			}
	
			gp = get_local_entity_child_succ (gp, LIST_TYPE_KEYSITE_GROUP);
		}
	
		#if DEBUG_MODULE
	
		debug_log ("LANDING: members on landed lock = %d", landed_flags);
	
		#endif
	
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//
		// LANDING_HOLDING ROUTE
		//
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
		landing_holding_flags = 0;
	
		task = get_local_landing_entity_task (en, ENTITY_SUB_TYPE_TASK_LANDING_HOLDING);
	
		wp = get_local_entity_first_child (task, LIST_TYPE_WAYPOINT);
	
		while (wp)
		{

			gd = get_local_entity_first_child (wp, LIST_TYPE_CURRENT_WAYPOINT);

			while (gd)
			{
	
				if (get_local_entity_type (gd) == ENTITY_TYPE_GUIDE)
				{
			
					mb = get_local_entity_first_child (gd, LIST_TYPE_FOLLOWER);
			
					if (mb)
					{
			
						if (get_local_entity_int_value (mb, INT_TYPE_IDENTIFY_MOBILE))
						{
				
							//
							// check that landing mb has landing route locked
							//
				
							formation_position = get_local_entity_int_value (mb, INT_TYPE_FORMATION_POSITION);
				
							formation_position %= raw->total_landing_sites;
				
							#if FATAL
		
							ASSERT (!(landing_holding_flags & (1 << formation_position)));
		
							ASSERT ((raw->landed_lock & (1 << formation_position)));
		
							#endif
				
							landing_holding_flags |= (1 << formation_position);
				
							#if DEBUG_MODULE
				
							#if LANDING_LOCK_USER_ONLY
							if (mb == get_gunship_entity ())
							#endif
							debug_log ("LANDING: holding member %s (%d) has lock on landing holding route. Position %d, route position %d", entity_type_names [mb->type], get_local_entity_index (mb), get_local_entity_int_value (mb, INT_TYPE_FORMATION_POSITION), 1 << formation_position);
				
							#endif
						}
			
						//mb = get_local_entity_child_succ (mb, LIST_TYPE_CURRENT_WAYPOINT);
					}
				}
	
				gd = get_local_entity_child_succ (gd, LIST_TYPE_CURRENT_WAYPOINT);
			}
	
			wp = get_local_entity_child_succ (wp, LIST_TYPE_WAYPOINT);
		}
	
		#if DEBUG_MODULE
	
		debug_log ("LANDING: members on landing holding route= %d", landing_holding_flags);
	
		#endif
	
		//
		// ASSERT that landing members are the same as the ones that have locked the route
		//
	
		#if FATAL

		ASSERT (raw->landed_lock == (landed_flags | landing_holding_flags));

		#endif
	
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//
		// TAKEOFF ROUTE
		//
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
		task = get_local_landing_entity_task (en, ENTITY_SUB_TYPE_TASK_TAKEOFF);
	
		wp = get_local_entity_first_child (task, LIST_TYPE_WAYPOINT);
	
		takeoff_flags = 0;
	
		#if DEBUG_MODULE
	
		debug_log ("LANDING: takeoff route lock = %d", raw->takeoff_lock);
	
		#endif
	
		while (get_local_entity_child_succ (wp, LIST_TYPE_WAYPOINT))
		{
	
			wp = get_local_entity_child_succ (wp, LIST_TYPE_WAYPOINT);
		}
	
		formation_data = get_formation (get_local_entity_int_value (wp, INT_TYPE_WAYPOINT_FORMATION));
	
		wp = get_local_entity_first_child (task, LIST_TYPE_WAYPOINT);
	
		while (wp)
		{

			gd = get_local_entity_first_child (wp, LIST_TYPE_CURRENT_WAYPOINT);

			while (gd)
			{
		
				if (get_local_entity_type (gd) == ENTITY_TYPE_GUIDE)
				{
			
					mb = get_local_entity_first_child (gd, LIST_TYPE_FOLLOWER);
			
					if (mb)
					{
			
						if (get_local_entity_int_value (mb, INT_TYPE_IDENTIFY_MOBILE))
						{
					
							//
							// check that takingoff mb has takeoff route locked
							//
				
							formation_position = get_local_entity_int_value (mb, INT_TYPE_FORMATION_POSITION);
				
							#if FATAL
		
							ASSERT (!(takeoff_flags & (1 << (formation_position % formation_data->number_in_formation))));
		
							#endif
				
							takeoff_flags |= (1 << (formation_position % formation_data->number_in_formation));
				
							#if DEBUG_MODULE
				
							#if LANDING_LOCK_USER_ONLY
							if (mb == get_gunship_entity ())
							#endif
							debug_log ("LANDING: member %s (%d) has lock on takeoff route. Position %d, route position %d", entity_type_names [mb->type], get_local_entity_index (mb), formation_position, (1 << (formation_position % formation_data->number_in_formation)));
				
							#endif
						}
			
						//mb = get_local_entity_child_succ (mb, LIST_TYPE_CURRENT_WAYPOINT);
					}
				}
		
				gd = get_local_entity_child_succ (gd, LIST_TYPE_CURRENT_WAYPOINT);
			}
	
			wp = get_local_entity_child_succ (wp, LIST_TYPE_WAYPOINT);
		}
	
		//
		// ASSERT that landing members are the same as the ones that have locked the route
		//
	
		#if FATAL

		ASSERT (raw->takeoff_lock == takeoff_flags);

		#endif
	
		wp = get_local_entity_first_child (task, LIST_TYPE_WAYPOINT); // debug just to allow me to get to the line above in the debugger
	
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
		#if DEBUG_MODULE
	
		debug_log ("LANDING: ----------------------------------------------------------------------------");
	
		#endif
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int check_available_landing_route_lock (entity *landing_en)
{

	formation_type
		*formation_data;

	entity
		*wp;

	landing
		*raw;

	unsigned int
		mask,
		new_mask;

	raw = get_local_entity_data (landing_en);

	wp = get_local_landing_entity_route (landing_en, ENTITY_SUB_TYPE_TASK_LANDING);

	formation_data = get_formation (get_local_entity_int_value (wp, INT_TYPE_WAYPOINT_FORMATION));

	mask = pow (2, formation_data->number_in_formation) - 1;

	new_mask = (~raw->landing_lock);// & (~raw->landed_lock);

	return (mask & new_mask);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int check_landing_route_lock_clear (entity *landing_en, entity *en)
{

	formation_type
		*formation_data;

	entity
		*wp;

	landing
		*raw;

	unsigned int
		formation_landing;

	raw = get_local_entity_data (landing_en);

	formation_landing = get_local_entity_int_value (en, INT_TYPE_FORMATION_POSITION);

	wp = get_local_landing_entity_route (landing_en, ENTITY_SUB_TYPE_TASK_LANDING);

	formation_data = get_formation (get_local_entity_int_value (wp, INT_TYPE_WAYPOINT_FORMATION));

	formation_landing %= formation_data->number_in_formation;

	return (!(raw->landing_lock & (1 << formation_landing)));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int check_takeoff_route_lock_clear (entity *landing_en, entity *en)
{

	formation_type
		*formation_data;

	entity
		*wp;

	landing
		*raw;

	unsigned int
		formation_takeoff;

	raw = get_local_entity_data (landing_en);

	formation_takeoff = get_local_entity_int_value (en, INT_TYPE_FORMATION_POSITION);

	wp = get_local_landing_entity_route (landing_en, ENTITY_SUB_TYPE_TASK_TAKEOFF);

	formation_data = get_formation (get_local_entity_int_value (wp, INT_TYPE_WAYPOINT_FORMATION));

	formation_takeoff %= formation_data->number_in_formation;

	return (!(raw->takeoff_lock & (1 << formation_takeoff)));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int check_landing_site_lock_clear (entity *landing_en, entity *en)
{

	landing
		*raw;

	unsigned int
		formation_landing;

	raw = get_local_entity_data (landing_en);

	formation_landing = get_local_entity_int_value (en, INT_TYPE_FORMATION_POSITION);

	return (!(raw->landed_lock & (1 << formation_landing)));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void release_mobile_entity_landing_locks (entity *en)
{
	entity
		*task,
		*group,
		*guide,
		*keysite,
		*landing_en;

	int
		landing_flag;

	#if DEBUG_MODULE

	debug_log ("LANDING: ***** releasing landing locks for entity %s (%d)", get_local_entity_string (en, STRING_TYPE_FULL_NAME), get_local_entity_index (en));

	#endif

	landing_flag = FALSE;

	group = get_local_entity_parent (en, LIST_TYPE_MEMBER);

	ASSERT (group);

	guide = get_local_entity_parent (en, LIST_TYPE_FOLLOWER);

	if (guide)
	{
		task = get_local_entity_parent (guide, LIST_TYPE_GUIDE);

		if (task)
		{
			switch (get_local_entity_int_value (task, INT_TYPE_ENTITY_SUB_TYPE))
			{
				case ENTITY_SUB_TYPE_TASK_LANDING:
				{
					#if DEBUG_MODULE

					debug_log ("LANDING: %s was landing, freeing landed site and landing route", get_local_entity_string (en, STRING_TYPE_FULL_NAME));

					#endif

					landing_en = get_local_entity_parent (task, LIST_TYPE_ASSIGNED_TASK);

					notify_local_entity (ENTITY_MESSAGE_UNLOCK_LANDING_ROUTE, landing_en, en);

					landing_flag = TRUE;

					break;
				}

				case ENTITY_SUB_TYPE_TASK_LANDING_HOLDING:
				{

					#if DEBUG_MODULE

					debug_log ("LANDING: %s was landing holding, freeing landed site", get_local_entity_string (en, STRING_TYPE_FULL_NAME));

					#endif

					landing_flag = TRUE;

					break;
				}

				case ENTITY_SUB_TYPE_TASK_TAKEOFF:
				{
					#if DEBUG_MODULE

					debug_log ("LANDING: %s was taking off, freeing takeoff route", get_local_entity_string (en, STRING_TYPE_FULL_NAME));

					#endif

					landing_en = get_local_entity_parent (task, LIST_TYPE_ASSIGNED_TASK);

					notify_local_entity (ENTITY_MESSAGE_UNLOCK_TAKEOFF_ROUTE, landing_en, en);

					//break;
				}
				default:
				{
			
					keysite = get_local_entity_parent (group, LIST_TYPE_KEYSITE_GROUP);
			
					if ((keysite) && (get_local_entity_type (keysite) == ENTITY_TYPE_KEYSITE))
					{
						landing_en = get_local_entity_landing_entity (keysite, group_database [get_local_entity_int_value (group, INT_TYPE_ENTITY_SUB_TYPE)].default_landing_type);
	
						#if DEBUG_MODULE
	
						debug_log ("LANDING: %s (%d) had a reservation at %d (landing %d), freeing it",
										get_local_entity_string (en, STRING_TYPE_FULL_NAME),
										get_local_entity_index (en),
										get_local_entity_index (keysite),
										get_local_entity_index (landing_en));
	
						#endif
										
						// unreserve landing lock
				
						if (landing_en)
						{
	
							entity
								*primary_task;
	
							primary_task = get_local_group_primary_task (group);
	
							if ((primary_task) && (get_local_entity_int_value (primary_task, INT_TYPE_ASSESS_LANDING)))
							{
	
								notify_local_entity (ENTITY_MESSAGE_UNRESERVE_LANDING_SITE, landing_en, en, 1);
							}
						}
					}
					
					break;
				}
			}
		}
	}

	if ((get_local_entity_int_value (en, INT_TYPE_LANDED)) || (landing_flag))
	{

		keysite = get_local_entity_parent (group, LIST_TYPE_KEYSITE_GROUP);

		ASSERT (keysite);

		if (get_local_entity_type (keysite) != ENTITY_TYPE_KEYSITE)
		{

			ASSERT (get_local_entity_type (en) == ENTITY_TYPE_SHIP_VEHICLE);

			ASSERT (get_local_entity_type (keysite) == ENTITY_TYPE_FORCE);

			#if DEBUG_MODULE

			debug_log ("LANDING: %s. Not unlocking", get_local_entity_string (en, STRING_TYPE_FULL_NAME));

			#endif

			return;
		}

		landing_en = get_local_entity_landing_entity (keysite, group_database [get_local_entity_int_value (group, INT_TYPE_ENTITY_SUB_TYPE)].default_landing_type);

		ASSERT (landing_en);

		#if DEBUG_MODULE

		debug_log ("LANDING: %s was landed, freeing landed site", get_local_entity_string (en, STRING_TYPE_FULL_NAME));

		#endif

		notify_local_entity (ENTITY_MESSAGE_UNLOCK_LANDING_SITE, landing_en, en);
	}
	/*
	else
	{
						
		// unreserve landing lock

		keysite = get_local_entity_parent (group, LIST_TYPE_KEYSITE_GROUP);

		landing_en = get_local_entity_landing_entity (keysite, group_database [get_local_entity_int_value (group, INT_TYPE_ENTITY_SUB_TYPE)].default_landing_type);

		if (landing_en)
		{
			notify_local_entity (ENTITY_MESSAGE_UNRESERVE_LANDING_SITE, landing_en, en, 1);
		}
	}
	*/
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void play_landing_clear_for_takeoff_speech (entity *en)
{
	entity
		*group_en;

	//
	// PLAY_SPEECH (ATC)
	//

	ASSERT (en);

	group_en = get_local_entity_parent (en, LIST_TYPE_MEMBER);

	ASSERT (group_en);
	
	play_client_server_speech
	(
		get_session_entity (),
		en,
		get_local_entity_int_value (en, INT_TYPE_SIDE),
		ENTITY_SUB_TYPE_EFFECT_SOUND_RADIO_MESSAGE,
		SOUND_LOCALITY_RADIO,
		0.0,
		0.5,
		12.0,
		SPEECH_ORIGINATOR_AIR_TRAFFIC_CONTROLLER, 
		SPEECH_CATEGORY_LANDING_TAKING_OFF, 16.0,
		SPEECH_ARRAY_CALLSIGNS, get_local_entity_int_value (group_en, INT_TYPE_GROUP_CALLSIGN),
		SPEECH_ARRAY_NUMBERS, 1,
		SPEECH_ARRAY_NUMBERS, get_local_entity_int_value (en, INT_TYPE_GROUP_MEMBER_ID),
		SPEECH_ARRAY_ATC_MESSAGES, SPEECH_ATC_INTRODUCTION,
		SPEECH_ARRAY_ATC_MESSAGES, SPEECH_ATC_CLEAR_FOR_TAKEOFF1,
		SPEECH_ARRAY_ATC_MESSAGES, SPEECH_ATC_WINDS,
		SPEECH_ARRAY_ATC_MESSAGES, get_speech_atc_wind_speed (en),
		-1
	);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
