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



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "project.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE   0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void create_reaction_to_recon_task_completed (entity *task);

static void create_reaction_to_strike_task_completed (entity *task);

static void create_reaction_to_offensive_keysite_task_assigned (entity *task);


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_task_assigned_reactionary_tasks (entity *task)
{
	entity_sub_types
		task_type;

	entity_sides
		task_side;

	ASSERT (task);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	task_side = get_local_entity_int_value (task, INT_TYPE_SIDE);

	task_type = get_local_entity_int_value (task, INT_TYPE_ENTITY_SUB_TYPE);

	switch (task_type)
	{
		//
		// Tasks aimed at enemy keysites create CAP as reaction
		//
		
		case ENTITY_SUB_TYPE_TASK_GROUND_STRIKE:
		case ENTITY_SUB_TYPE_TASK_OCA_STRIKE:
		case ENTITY_SUB_TYPE_TASK_OCA_SWEEP:
		case ENTITY_SUB_TYPE_TASK_RECON:
		{
			create_reaction_to_offensive_keysite_task_assigned (task);

			break;
		}

		case ENTITY_SUB_TYPE_TASK_BAI:
		case ENTITY_SUB_TYPE_TASK_BDA:
		case ENTITY_SUB_TYPE_TASK_CLOSE_AIR_SUPPORT:
		case ENTITY_SUB_TYPE_TASK_COASTAL_PATROL:
		case ENTITY_SUB_TYPE_TASK_COMBAT_AIR_PATROL:
		case ENTITY_SUB_TYPE_TASK_ESCORT:
		case ENTITY_SUB_TYPE_TASK_REPAIR:
		case ENTITY_SUB_TYPE_TASK_SEAD:
		case ENTITY_SUB_TYPE_TASK_SUPPLY:
		case ENTITY_SUB_TYPE_TASK_TRANSFER_FIXED_WING:
		case ENTITY_SUB_TYPE_TASK_TRANSFER_HELICOPTER:
		case ENTITY_SUB_TYPE_TASK_TROOP_INSERTION:
		default:
		{
			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_task_completed_reactionary_tasks (entity *task)
{
	entity_sub_types
		task_type;

	entity_sides
		task_side;

	ASSERT (task);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	task_side = get_local_entity_int_value (task, INT_TYPE_SIDE);

	task_type = get_local_entity_int_value (task, INT_TYPE_ENTITY_SUB_TYPE);

	switch (task_type)
	{
		case ENTITY_SUB_TYPE_TASK_RECON:
		case ENTITY_SUB_TYPE_TASK_BDA:
		{
			//
			// Recon tasks aimed at enemy installations create offensive missions when completed
			//
		
			create_reaction_to_recon_task_completed (task);

			break;
		}

		case ENTITY_SUB_TYPE_TASK_GROUND_STRIKE:
		case ENTITY_SUB_TYPE_TASK_OCA_STRIKE:
		{
			//
			// Strike missions create BDA tasks when completed
			//

			create_reaction_to_strike_task_completed (task);

			break;
		}

		case ENTITY_SUB_TYPE_TASK_OCA_SWEEP:
		case ENTITY_SUB_TYPE_TASK_BAI:
		case ENTITY_SUB_TYPE_TASK_CLOSE_AIR_SUPPORT:
		case ENTITY_SUB_TYPE_TASK_COASTAL_PATROL:
		case ENTITY_SUB_TYPE_TASK_COMBAT_AIR_PATROL:
		case ENTITY_SUB_TYPE_TASK_ESCORT:
		case ENTITY_SUB_TYPE_TASK_REPAIR:
		case ENTITY_SUB_TYPE_TASK_SEAD:
		case ENTITY_SUB_TYPE_TASK_SUPPLY:
		case ENTITY_SUB_TYPE_TASK_TRANSFER_FIXED_WING:
		case ENTITY_SUB_TYPE_TASK_TRANSFER_HELICOPTER:
		case ENTITY_SUB_TYPE_TASK_TROOP_INSERTION:
		default:
		{
			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_reaction_to_offensive_keysite_task_assigned (entity *task)
{
	entity
		*new_task,
		*objective;
	
	entity_sub_types
		objective_type;

	entity_sides
		objective_side;

	objective = get_local_entity_parent (task, LIST_TYPE_TASK_DEPENDENT);

	ASSERT (objective);

	if (get_local_entity_type (objective) == ENTITY_TYPE_KEYSITE)
	{
		ai_log ("===========================================");
		ai_log ("REACTION TO OFFENSIVE KEYSITE TASK ASSIGNED");
		ai_log ("-------------------------------------------");

		objective_side = get_local_entity_int_value (objective, INT_TYPE_SIDE);

		objective_type = get_local_entity_int_value (objective, INT_TYPE_ENTITY_SUB_TYPE);

		if (keysite_database [objective_type].requires_cap)
		{
			if (!entity_is_object_of_task (objective, ENTITY_SUB_TYPE_TASK_COMBAT_AIR_PATROL, objective_side))
			{
				new_task = create_cap_task (objective_side, objective, task, TRUE, task_database [ENTITY_SUB_TYPE_TASK_COMBAT_AIR_PATROL].task_priority, 30.0 * ONE_MINUTE, NULL, NULL);

				ai_log ("(TASK) Side %s : Created CAP (%d) at %s in reaction to %s",
							entity_side_short_names [objective_side],
							get_local_entity_safe_index (new_task),
							get_local_entity_string (objective, STRING_TYPE_KEYSITE_NAME),
							get_local_entity_string (task, STRING_TYPE_FULL_NAME));
			}
		}

		if (keysite_database [objective_type].requires_barcap)
		{
			if (!entity_is_object_of_task (objective, ENTITY_SUB_TYPE_TASK_BARCAP, objective_side))
			{
				entity
					*group,
					*guide;

				vec3d
					position,
					direction,
					*objective_pos,
					*group_pos;

				float
					distance;

				guide = get_local_entity_first_child (task, LIST_TYPE_GUIDE);

				ASSERT (guide);

				group = get_local_entity_parent (guide, LIST_TYPE_GUIDE_STACK);

				ASSERT (group);

				group_pos = get_local_entity_vec3d_ptr (group, VEC3D_TYPE_POSITION);

				objective_pos = get_local_entity_vec3d_ptr (objective, VEC3D_TYPE_POSITION);

				direction.x = group_pos->x - objective_pos->x;
				direction.y = 0.0;
				direction.z = group_pos->z - objective_pos->z;

				normalise_any_3d_vector (&direction);

				distance = 6.0 * KILOMETRE;

				position.x = objective_pos->x + (direction.x * distance);
				position.y = objective_pos->y;
				position.z = objective_pos->z + (direction.z * distance);

				new_task = create_barcap_task (objective_side, objective, task, TRUE, &position, task_database [ENTITY_SUB_TYPE_TASK_BARCAP].task_priority, 30.0 * ONE_MINUTE, NULL, NULL);
					
				ai_log ("(TASK) Side %s : Created BARCAP (%d) at %s in reaction to %s",
							entity_side_short_names [objective_side],
							get_local_entity_safe_index (new_task),
							get_local_entity_string (objective, STRING_TYPE_KEYSITE_NAME),
							get_local_entity_string (task, STRING_TYPE_FULL_NAME));
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_reaction_to_recon_task_completed (entity *task)
{
	entity
		*force,
		*new_task,
		*objective;

	entity_sides
		task_side;

	int
		sub_type;

	float
		priority;

	unsigned char
		s [256];

	ASSERT (task);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	task_side = get_local_entity_int_value (task, INT_TYPE_SIDE);

	force = get_local_force_entity (task_side);

	ASSERT (force);

	objective = get_local_entity_parent (task, LIST_TYPE_TASK_DEPENDENT);

	ASSERT (objective);

	sub_type = get_local_entity_int_value (objective, INT_TYPE_ENTITY_SUB_TYPE);

	//
	// Quick check that objective is enemy
	//
	
	if (get_local_entity_int_value (objective, INT_TYPE_SIDE) == task_side)
	{
		return;
	}

	if (get_local_entity_int_value (task, INT_TYPE_TASK_COMPLETED) != TASK_COMPLETED_SUCCESS)
	{
		return;
	}

	ai_log ("================================");
	ai_log ("REACTION TO RECON TASK COMPLETED");
	ai_log ("--------------------------------");

	priority = get_local_entity_float_value (task, FLOAT_TYPE_TASK_PRIORITY);

	//
	// Check objective type :- keysites create strikes, air defence groups create SEAD etc.
	//

	switch (get_local_entity_type (objective))
	{
		case ENTITY_TYPE_KEYSITE:
		{
			float
				efficiency;

			efficiency = get_local_entity_float_value (objective, FLOAT_TYPE_EFFICIENCY);

			//
			// Check surrounding air defences - if greater than threshold abort strike and create S.E.A.D.
			//

			if (create_sead_tasks_around_keysite (task, objective, task_side) > 1)
			{
				break;
			}

			if (get_local_entity_int_value (objective, INT_TYPE_ALIVE))
			{
				sprintf (s, "%s %s %s %s %s",
										get_local_entity_string (task, STRING_TYPE_SHORT_DISPLAY_NAME),
										get_trans ("revealed enemy"),
										get_local_entity_string (objective, STRING_TYPE_FULL_NAME),
										get_trans ("is currently"),
										keysite_usable_state_names [get_local_entity_int_value (objective, INT_TYPE_KEYSITE_USABLE_STATE)]);

				send_text_message (objective, force, MESSAGE_TEXT_SYSTEM_RECON_DATA, s);

				if (keysite_database [sub_type].troop_insertion_target)
				{
					//
					// check keysite efficiency - if less than threshold level then create T.I.
					//
	
					if (efficiency < keysite_database [sub_type].minimum_efficiency)
					{
						if (!entity_is_object_of_task (objective, ENTITY_SUB_TYPE_TASK_TROOP_INSERTION, task_side))
						{
							new_task = create_troop_insertion_task (task_side, objective, task, TRUE, task_database [ENTITY_SUB_TYPE_TASK_TROOP_INSERTION].task_priority, NULL, NULL);
	
							ai_log ("(TASK) Side %s : Created TROOP INSERTION (%d) at %s (eff. %.3f) in reaction to %s",
										entity_side_short_names [task_side],
										get_local_entity_safe_index (new_task),
										get_local_entity_string (objective, STRING_TYPE_KEYSITE_NAME),
										efficiency,
										get_local_entity_string (task, STRING_TYPE_FULL_NAME));
						}
					}
				}
	
				if (keysite_database [sub_type].oca_target)
				{
					if (!entity_is_object_of_task (objective, ENTITY_SUB_TYPE_TASK_OCA_STRIKE, task_side))
					{
						new_task = create_oca_strike_task (task_side, objective, task, TRUE, task_database [ENTITY_SUB_TYPE_TASK_OCA_STRIKE].task_priority, NULL, NULL);

						ai_log ("(TASK) Side %s : Created OCA STRIKE (%d) at %s (eff. %.3f) in reaction to %s",
										entity_side_short_names [task_side],
										get_local_entity_safe_index (new_task),
										get_local_entity_string (objective, STRING_TYPE_KEYSITE_NAME),
										efficiency,
										get_local_entity_string (task, STRING_TYPE_FULL_NAME));
					}
					
					if (!entity_is_object_of_task (objective, ENTITY_SUB_TYPE_TASK_OCA_SWEEP, task_side))
					{
						new_task = create_oca_sweep_task (task_side, objective, task, TRUE, task_database [ENTITY_SUB_TYPE_TASK_OCA_SWEEP].task_priority, NULL, NULL);
		
						ai_log ("(TASK) Side %s : Created OCA SWEEP (%d) at %s (eff. %.3f) in reaction to %s",
											entity_side_short_names [task_side],
											get_local_entity_safe_index (new_task),
											get_local_entity_string (objective, STRING_TYPE_KEYSITE_NAME),
											efficiency,
											get_local_entity_string (task, STRING_TYPE_FULL_NAME));
					}
				}
	
				if (keysite_database [sub_type].ground_strike_target)
				{
					if (efficiency >= keysite_database [sub_type].minimum_efficiency)
					{
						new_task = create_ground_strike_task (task_side, objective, task, TRUE, task_database [ENTITY_SUB_TYPE_TASK_GROUND_STRIKE].task_priority, NULL, NULL);
	
						ai_log ("(TASK) Side %s : Created STRIKE (%d) at %s (eff. %.3f) in reaction to %s",
										entity_side_short_names [task_side],
										get_local_entity_safe_index (new_task),
										get_local_entity_string (objective, STRING_TYPE_KEYSITE_NAME),
										efficiency,
										get_local_entity_string (task, STRING_TYPE_FULL_NAME));
					}
				}
	
				if (keysite_database [sub_type].ship_strike_target)
				{
					new_task = create_anti_ship_strike_task (task_side, objective, task, TRUE, task_database [ENTITY_SUB_TYPE_TASK_ANTI_SHIP_STRIKE].task_priority, NULL, NULL);
	
					ai_log ("(TASK) Side %s : Created ANTI-SHIP STRIKE (%d) at %s (eff. %.3f) in reaction to %s",
										entity_side_short_names [task_side],
										get_local_entity_safe_index (new_task),
										get_local_entity_string (objective, STRING_TYPE_KEYSITE_NAME),
										efficiency,
										get_local_entity_string (task, STRING_TYPE_FULL_NAME));
				}
			}
			else
			{
				sprintf (s, "%s %s %s",
										get_local_entity_string (task, STRING_TYPE_FULL_NAME),
										get_trans ("revealed"),
										get_local_entity_string (objective, STRING_TYPE_FULL_NAME),
										get_trans ("has been destroyed"));

				send_text_message (objective, force, MESSAGE_TEXT_SYSTEM_RECON_DATA, s);
			}

			break;
		}

		case ENTITY_TYPE_GROUP:
		{
			if (sub_type == ENTITY_SUB_TYPE_GROUP_ANTI_AIRCRAFT)
			{
				//
				// CREATE SEAD
				//
				
				int
					member_count;

				member_count = get_local_entity_int_value (objective, INT_TYPE_MEMBER_COUNT);

				if (member_count > 0)
				{
					if (!entity_is_object_of_task (objective, ENTITY_SUB_TYPE_TASK_SEAD, task_side))
					{
						new_task = create_sead_task (task_side, objective, task, TRUE, task_database [ENTITY_SUB_TYPE_TASK_SEAD].task_priority, NULL, NULL);
	
						ai_log ("(TASK) Side %s : Created SEAD (%d) to %s in reaction to %s",
										entity_side_short_names [task_side],
										get_local_entity_safe_index (new_task),
										get_local_entity_string (objective, STRING_TYPE_FULL_NAME),
										get_local_entity_string (task, STRING_TYPE_FULL_NAME));
					}	
	
					if (member_count == 1)
					{
						sprintf (s, "%s %s 1 %s",
											get_local_entity_string (task, STRING_TYPE_FULL_NAME),
											get_trans ("revealed"),
											get_trans ("enemy A-A installation"));
					}
					else
					{
						sprintf (s, "%s %s %d %s",
											get_local_entity_string (task, STRING_TYPE_FULL_NAME),
											get_trans ("revealed"),
											get_local_entity_int_value (objective, INT_TYPE_MEMBER_COUNT),
											get_trans ("enemy A-A installations"));
					}
						
					send_text_message (objective, force, MESSAGE_TEXT_SYSTEM_RECON_DATA, s);
				}
			}
			else if (group_database [sub_type].frontline_flag)
			{
				//
				// CREATE BAI
				//
				
				int
					member_count;

				member_count = get_local_entity_int_value (objective, INT_TYPE_MEMBER_COUNT);

				if (member_count > 0)
				{
					if (!entity_is_object_of_task (objective, ENTITY_SUB_TYPE_TASK_BAI, task_side))
					{
						new_task = create_bai_task (task_side, objective, task, TRUE, task_database [ENTITY_SUB_TYPE_TASK_BAI].task_priority, NULL, NULL);
	
						ai_log ("(TASK) Side %s : Created BAI (%d) to %s in reaction to %s",
										entity_side_short_names [task_side],
										get_local_entity_safe_index (new_task),
										get_local_entity_string (objective, STRING_TYPE_FULL_NAME),
										get_local_entity_string (task, STRING_TYPE_FULL_NAME));
					}	
	
					sprintf (s, "%s %s",
											get_local_entity_string (task, STRING_TYPE_FULL_NAME),
											get_trans ("revealed enemy armoured battalion"));
						
					send_text_message (objective, force, MESSAGE_TEXT_SYSTEM_RECON_DATA, s);
				}
			}

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_reaction_to_strike_task_completed (entity *task)
{
	entity
		*new_task,
		*objective;

	entity_sides
		task_side;

	int
		sub_type;

	float
		priority,
		efficiency;

	ASSERT (task);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	if ((get_local_entity_int_value (task, INT_TYPE_TASK_COMPLETED) != TASK_COMPLETED_SUCCESS) &&
			(get_local_entity_int_value (task, INT_TYPE_TASK_COMPLETED) != TASK_COMPLETED_PARTIAL))
	{
		return;
	}

	ai_log ("================================");
	ai_log ("REACTION TO STRIKE TASK COMPLETED");
	ai_log ("--------------------------------");

	task_side = get_local_entity_int_value (task, INT_TYPE_SIDE);

	objective = get_local_entity_parent (task, LIST_TYPE_TASK_DEPENDENT);

	ASSERT (objective);

	sub_type = get_local_entity_int_value (objective, INT_TYPE_ENTITY_SUB_TYPE);

	priority = get_local_entity_float_value (task, FLOAT_TYPE_TASK_PRIORITY);

	switch (get_local_entity_type (objective))
	{
		case ENTITY_TYPE_KEYSITE:
		{
			//
			// Upon completion of ground strike - create another ground strike, or BDA if below min efficiency
			//
			
			efficiency = get_local_entity_float_value (objective, FLOAT_TYPE_EFFICIENCY);

			if (keysite_database [sub_type].ground_strike_target)
			{
				if (efficiency >= keysite_database [sub_type].minimum_efficiency)
				{
					new_task = create_ground_strike_task (task_side, objective, task, TRUE, task_database [ENTITY_SUB_TYPE_TASK_GROUND_STRIKE].task_priority, NULL, NULL);
	
					ai_log ("(TASK) Side %s : Created STRIKE (%d) at %s (eff. %.3f) in reaction to %s",
										entity_side_short_names [task_side],
										get_local_entity_safe_index (new_task),
										get_local_entity_string (objective, STRING_TYPE_KEYSITE_NAME),
										efficiency,
										get_local_entity_string (task, STRING_TYPE_FULL_NAME));

					return;
				}
			}
	
			if (keysite_database [sub_type].recon_target)
			{
				if (
						(!entity_is_object_of_task (objective, ENTITY_SUB_TYPE_TASK_RECON, task_side)) &&
						(!entity_is_object_of_task (objective, ENTITY_SUB_TYPE_TASK_BDA, task_side))
					)
				{
					new_task = create_bda_task (task_side, objective, task, TRUE, task_database [ENTITY_SUB_TYPE_TASK_BDA].task_priority, NULL, NULL);

					ai_log ("(TASK) Side %s : Created BDA (%d) at %s (eff. %.3f) in reaction to %s",
									entity_side_short_names [task_side],
									get_local_entity_safe_index (new_task),
									get_local_entity_string (objective, STRING_TYPE_KEYSITE_NAME),
									get_local_entity_float_value (objective, FLOAT_TYPE_EFFICIENCY),
									get_local_entity_string (task, STRING_TYPE_FULL_NAME));
				}
			}

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_reaction_to_artillery_fire (entity *group, entity *target)
{
	entity
		*sector,
		*new_task;

	entity_sides
		side,
		enemy_side;

	int
		x,
		z;

	float
		rating,
		max_rating,
		priority,
		air_defence_rating,
		surface_defence_rating,
		base_distance_rating;

	vec3d
		*pos;

	//
	// Create Recon/BAI Task in response to artillery fire
	//

	ASSERT (group);

	ASSERT (target);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

	side = get_local_entity_int_value (target, INT_TYPE_SIDE);

	if ((entity_is_object_of_task (group, ENTITY_SUB_TYPE_TASK_BAI, side)) ||
			(entity_is_object_of_task (group, ENTITY_SUB_TYPE_TASK_RECON, side)))
	{
		return;
	}
	
	enemy_side = get_local_entity_int_value (group, INT_TYPE_SIDE);

	pos = get_local_entity_vec3d_ptr (group, VEC3D_TYPE_POSITION);

	sector = get_local_sector_entity (pos);

	ASSERT (sector);

	x = get_local_entity_int_value (sector, INT_TYPE_X_SECTOR);
	z = get_local_entity_int_value (sector, INT_TYPE_Z_SECTOR);

	//
	// Calculate sector rating
	//
	
	air_defence_rating = get_imap_value (IMAP_AIR_DEFENCE, side, x, z);
	
	surface_defence_rating = get_imap_value (IMAP_SURFACE_DEFENCE, side, x, z);
	
	base_distance_rating = get_imap_value (IMAP_BASE_DISTANCE, side, x, z);
	
	rating = 0.0;
		
	// low enemy S-A threat 
	rating += (1.0 - air_defence_rating);
	
	// high enemy S-S threat
	rating += (surface_defence_rating);
	
	// close to enemy base
	rating += 2.0 * (base_distance_rating);
	
	max_rating = 4.0;
		
	if (get_sector_fog_of_war_value (sector, side) > (0.5 * get_local_entity_float_value (get_session_entity (), FLOAT_TYPE_FOG_OF_WAR_MAXIMUM_VALUE)))
	{
		//
		// Create BAI
		//
								
		priority = (rating / max_rating) * task_database [ENTITY_SUB_TYPE_TASK_BAI].task_priority;
		
		new_task = create_bai_task (side, group, NULL, FALSE, priority, NULL, NULL);
	
		ai_log ("(TASK) Side %s : Created BAI (%d) to sector (%d, %d) in reaction to Artillery Fire",
					entity_side_short_names [side],
					get_local_entity_safe_index (new_task),
					x, z);
	}
	else
	{
		//
		// Create RECON
		//
								
		priority = (rating / max_rating) * task_database [ENTITY_SUB_TYPE_TASK_BAI].task_priority;
		
		new_task = create_recon_task (side, group, NULL, TRUE, priority, NULL, NULL);
	
		ai_log ("(TASK) Side %s : Created RECON (%d) to sector (%d, %d) in reaction to Artillery Fire",
					entity_side_short_names [side],
					get_local_entity_safe_index (new_task),
					x, z);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Jabberwock 031007 - Campaign Commander functions

void create_reaction_to_map_click (entity *objective)
{
	entity
		*force,
		*new_task;

	entity_sides
		task_side;

	int
		sub_type;

	float
		efficiency;

	task_side = get_local_entity_int_value (get_pilot_entity (), INT_TYPE_SIDE);

	force = get_local_force_entity (task_side);

	ASSERT (force);

	sub_type = get_local_entity_int_value (objective, INT_TYPE_ENTITY_SUB_TYPE);

	switch (get_local_entity_type (objective))
	{
		case ENTITY_TYPE_KEYSITE:
		{
			efficiency = get_local_entity_float_value (objective, FLOAT_TYPE_EFFICIENCY);

			if (get_local_entity_int_value (objective, INT_TYPE_ALIVE))
			{

				if (keysite_database [sub_type].troop_insertion_target)
				{
					//
					// check keysite efficiency - if less than threshold level then create T.I.
					//
	
					if (efficiency < keysite_database [sub_type].minimum_efficiency)
					{
						if (!entity_is_object_of_task (objective, ENTITY_SUB_TYPE_TASK_TROOP_INSERTION, task_side))
						{
							new_task = create_troop_insertion_task (task_side, objective, NULL, TRUE, task_database [ENTITY_SUB_TYPE_TASK_TROOP_INSERTION].task_priority, NULL, NULL);
	
						}
					}
				}
	
				if (keysite_database [sub_type].ground_strike_target)
				{
					if (efficiency >= keysite_database [sub_type].minimum_efficiency)
					{
						if (!entity_is_object_of_task (objective, ENTITY_SUB_TYPE_TASK_GROUND_STRIKE, task_side))
						{
							new_task = create_ground_strike_task (task_side, objective, NULL, TRUE, task_database [ENTITY_SUB_TYPE_TASK_GROUND_STRIKE].task_priority, NULL, NULL);
						}
					}
				}
				else
				{
					if (keysite_database [sub_type].oca_target)
					{
						if (!entity_is_object_of_task (objective, ENTITY_SUB_TYPE_TASK_OCA_STRIKE, task_side))
						{
							new_task = create_oca_strike_task (task_side, objective, NULL, TRUE, task_database [ENTITY_SUB_TYPE_TASK_OCA_STRIKE].task_priority, NULL, NULL);
	
						}
					
						if (!entity_is_object_of_task (objective, ENTITY_SUB_TYPE_TASK_OCA_SWEEP, task_side))
						{
							new_task = create_oca_sweep_task (task_side, objective, NULL, TRUE, task_database [ENTITY_SUB_TYPE_TASK_OCA_SWEEP].task_priority, NULL, NULL);
		
						}
					}
				}
	
				if (keysite_database [sub_type].ship_strike_target)
				{
					new_task = create_anti_ship_strike_task (task_side, objective, NULL, TRUE, task_database [ENTITY_SUB_TYPE_TASK_ANTI_SHIP_STRIKE].task_priority, NULL, NULL);
	
				}
			}
			break;
		}
		
		case ENTITY_TYPE_GROUP:
		{
			switch (sub_type)
			{
				case ENTITY_SUB_TYPE_GROUP_ANTI_AIRCRAFT:
				{
					int
						member_count;

					member_count = get_local_entity_int_value (objective, INT_TYPE_MEMBER_COUNT);

					if (member_count > 0)
					{
						if (!entity_is_object_of_task (objective, ENTITY_SUB_TYPE_TASK_SEAD, task_side))
						{
							new_task = create_sead_task (task_side, objective, NULL, TRUE, task_database [ENTITY_SUB_TYPE_TASK_SEAD].task_priority, NULL, NULL);
	
						}	
					}
					break;
				}
			
				case ENTITY_SUB_TYPE_GROUP_PRIMARY_FRONTLINE:
				case ENTITY_SUB_TYPE_GROUP_SECONDARY_FRONTLINE:
				case ENTITY_SUB_TYPE_GROUP_SELF_PROPELLED_ARTILLERY:
				case ENTITY_SUB_TYPE_GROUP_SELF_PROPELLED_MLRS:
				{
					int
						member_count;

					member_count = get_local_entity_int_value (objective, INT_TYPE_MEMBER_COUNT);

					if (member_count > 0)
					{
						if (!entity_is_object_of_task (objective, ENTITY_SUB_TYPE_TASK_BAI, task_side))
						{
							new_task = create_bai_task (task_side, objective, NULL, TRUE, task_database [ENTITY_SUB_TYPE_TASK_BAI].task_priority, NULL, NULL);

						}	
					}
					break;
				}

				case ENTITY_SUB_TYPE_GROUP_ATTACK_HELICOPTER:
				case ENTITY_SUB_TYPE_GROUP_MARINE_ATTACK_HELICOPTER:
				case ENTITY_SUB_TYPE_GROUP_ASSAULT_HELICOPTER:
				case ENTITY_SUB_TYPE_GROUP_MARINE_ASSAULT_HELICOPTER:
				case ENTITY_SUB_TYPE_GROUP_RECON_HELICOPTER:
				case ENTITY_SUB_TYPE_GROUP_RECON_ATTACK_HELICOPTER:
				case ENTITY_SUB_TYPE_GROUP_MEDIUM_LIFT_TRANSPORT_HELICOPTER:
				case ENTITY_SUB_TYPE_GROUP_HEAVY_LIFT_TRANSPORT_HELICOPTER:
				case ENTITY_SUB_TYPE_GROUP_MULTI_ROLE_FIGHTER:
				case ENTITY_SUB_TYPE_GROUP_CARRIER_BORNE_ATTACK_AIRCRAFT:
				case ENTITY_SUB_TYPE_GROUP_CARRIER_BORNE_INTERCEPTOR:
				case ENTITY_SUB_TYPE_GROUP_CLOSE_AIR_SUPPORT_AIRCRAFT:
				case ENTITY_SUB_TYPE_GROUP_MEDIUM_LIFT_TRANSPORT_AIRCRAFT:
				case ENTITY_SUB_TYPE_GROUP_HEAVY_LIFT_TRANSPORT_AIRCRAFT:
				{
					if (!entity_is_object_of_task (objective, ENTITY_SUB_TYPE_TASK_CLOSE_AIR_SUPPORT, task_side))
					{
						new_task = create_close_air_support_task (task_side, objective, NULL, TRUE, task_database [ENTITY_SUB_TYPE_TASK_CLOSE_AIR_SUPPORT].task_priority, NULL, NULL);
					}
				}
				break;
			}
			break;
		}
	}
	
}

// Jabberwock 031007 ends



