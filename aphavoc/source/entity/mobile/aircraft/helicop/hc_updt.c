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

#include "entity/tacview/tacview.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void interpolate_entity_position (entity *en);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_rotors (entity *en)
{
	helicopter
		*raw;

	raw = (helicopter *) get_local_entity_data (en);

	if (!get_local_entity_parent (en, LIST_TYPE_FOLLOWER))
	{
		raw->main_rotor_rpm -= 5.0 * get_delta_time ();

		raw->main_rotor_rpm = bound (raw->main_rotor_rpm, 0.0, 100.0);

		raw->tail_rotor_rpm = raw->main_rotor_rpm;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_fuel_weight (entity *en)
{
	helicopter
		*raw;
	float fuel_delta, fuel_economy;
	
	if (get_comms_model() != COMMS_MODEL_SERVER || !get_local_entity_int_value (en, INT_TYPE_MOBILE_MOVING) || get_local_entity_int_value (en, INT_TYPE_LANDED))
		return;

	raw = (helicopter *) get_local_entity_data (en);

	fuel_economy = get_local_entity_float_value (en, FLOAT_TYPE_FUEL_ECONOMY);
	fuel_delta = fuel_economy / 60.0 * get_delta_time ();
	fuel_delta *= raw->main_rotor_rpm / 50.0;

	raw->fuel_supply_level -= fuel_delta;

	// OUT OF FUEL, TAKE HELICOPTER DOWN
	if (raw->fuel_supply_level <= 0.0) {
		kill_client_server_entity (en);

		#if DEBUG_MODULE || DEBUG_SUPPLY
		debug_log ("HC_UPDT: %s out of fuel", get_local_entity_string (en, STRING_TYPE_FULL_NAME));
		#endif
	}
	
	// 20 MINS FUEL RESERVE RETURN HOME
	else if ((raw->fuel_supply_level / fuel_economy) <= 20.0) {
		entity
			*group,
			*guide,
			*task,
			*wp,
			*current_wp;

		group = get_local_entity_parent (en, LIST_TYPE_MEMBER);

		if (group) {
			guide = get_local_group_primary_guide (group);
			if (guide) {
				task = get_local_entity_parent (guide, LIST_TYPE_GUIDE);
				if (task) {
					switch (get_local_entity_int_value (task, INT_TYPE_ENTITY_SUB_TYPE)) {
						case ENTITY_SUB_TYPE_TASK_NOTHING:
						case ENTITY_SUB_TYPE_TASK_ADVANCE:
						case ENTITY_SUB_TYPE_TASK_ANTI_SHIP_STRIKE:
						case ENTITY_SUB_TYPE_TASK_BAI:
						case ENTITY_SUB_TYPE_TASK_BARCAP:
						case ENTITY_SUB_TYPE_TASK_BDA:
						case ENTITY_SUB_TYPE_TASK_CLOSE_AIR_SUPPORT:
						case ENTITY_SUB_TYPE_TASK_COASTAL_PATROL:
						case ENTITY_SUB_TYPE_TASK_COMBAT_AIR_PATROL:
						//case ENTITY_SUB_TYPE_TASK_ENGAGE:
						case ENTITY_SUB_TYPE_TASK_ESCORT:
						case ENTITY_SUB_TYPE_TASK_FREE_FLIGHT:
						case ENTITY_SUB_TYPE_TASK_GROUND_STRIKE:
						//case ENTITY_SUB_TYPE_TASK_LANDING:
						//case ENTITY_SUB_TYPE_TASK_LANDING_HOLDING:
						case ENTITY_SUB_TYPE_TASK_OCA_STRIKE:
						case ENTITY_SUB_TYPE_TASK_OCA_SWEEP:
						case ENTITY_SUB_TYPE_TASK_RECON:
						case ENTITY_SUB_TYPE_TASK_REPAIR:
						//case ENTITY_SUB_TYPE_TASK_RETREAT:
						case ENTITY_SUB_TYPE_TASK_SEAD:
						case ENTITY_SUB_TYPE_TASK_SUPPLY:
						//case ENTITY_SUB_TYPE_TASK_TAKEOFF:
						//case ENTITY_SUB_TYPE_TASK_TAKEOFF_HOLDING:
						//case ENTITY_SUB_TYPE_TASK_TRANSFER_FIXED_WING:
						//case ENTITY_SUB_TYPE_TASK_TRANSFER_HELICOPTER:
						case ENTITY_SUB_TYPE_TASK_TROOP_INSERTION:
							current_wp = get_local_entity_parent (guide, LIST_TYPE_CURRENT_WAYPOINT);
							ASSERT (current_wp);
							wp = current_wp;

							while (get_local_entity_child_succ (wp, LIST_TYPE_WAYPOINT)) {
								wp = get_local_entity_child_succ (wp, LIST_TYPE_WAYPOINT);
							}

							// CHECK IF GROUP HEADING HOME ALREADY
							if (current_wp == wp || !get_local_entity_child_pred (current_wp, LIST_TYPE_WAYPOINT) || get_local_entity_child_pred (current_wp, LIST_TYPE_WAYPOINT) == wp)
								break;

							#if DEBUG_MODULE
							debug_log ("HC_UPDT: %s low fuel, task %s cancelled", get_local_entity_string (en, STRING_TYPE_FULL_NAME), get_local_entity_string (task, STRING_TYPE_FULL_NAME));
							#endif

							group_return_to_base (group);
							break;
					}
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_server (entity *en)
{
	entity
		*group;

	helicopter
		*raw;

	int
		loop;

	aircraft_damage_types
		damage_type;

	raw = (helicopter *) get_local_entity_data (en);

	update_local_entity_view_interest_level (en);

	update_local_helicopter_rotor_sounds (en);

	damage_type = aircraft_critically_damaged (en);
	
	if (raw->ac.mob.alive)
	{
		switch (raw->player)
		{
			////////////////////////////////////////
			case ENTITY_PLAYER_AI:
			////////////////////////////////////////
			{

				////////////////////////////////////////

				for (loop = 0; loop < get_entity_movement_iterations (); loop ++)
				{

					if (get_local_entity_int_value (en, INT_TYPE_EJECTED) || raw->main_rotor_rpm < 50 && get_local_entity_int_value (en, INT_TYPE_AIRBORNE_AIRCRAFT))
					{

						helicopter_death_movement (en);
					}
					else
					{

						if (!get_local_entity_int_value (en, INT_TYPE_LANDED))
						{

							ASSERT(point_inside_map_area(&raw->ac.mob.position));

							get_3d_terrain_point_data (raw->ac.mob.position.x, raw->ac.mob.position.z, &raw->ac.terrain_info);
						}

						helicopter_movement (en);
					}
				}

				// provide resync for AI wingmen

				group = get_local_entity_parent (en, LIST_TYPE_MEMBER);

				if (group)
				{

					if ((get_local_entity_int_value (en, INT_TYPE_OPERATIONAL_STATE) != OPERATIONAL_STATE_LANDED) &&
							(get_local_entity_int_value (group, INT_TYPE_MULTIPLAYER_GROUP)))
					{

						transmit_entity_comms_message (ENTITY_COMMS_UPDATE, en);
					}
				}

				////////////////////////////////////////
				//
				// ORDER IS CRITICAL
				//

				if (raw->ac.mob.alive)
				{
					update_rotors (en);

					update_fuel_weight (en);
					
					update_aircraft_loading_doors (en);

					update_aircraft_cargo_doors (en);

					update_aircraft_undercarriage (en);

					update_aircraft_rudder (en);

					update_aircraft_target_scan (en);

					update_aircraft_weapon_system_ready (en);

					update_entity_weapon_systems (en);

					update_entity_weapon_system_weapon_and_target_vectors (en);

					update_aircraft_weapon_fire (en);

					update_aircraft_decoy_release (en);

					if (damage_type > AIRCRAFT_DAMAGE_NONE)
						if (frand1() < pow((float)damage_type, 4) * get_delta_time())
						{
							int damage_level = max(0, get_local_entity_int_value (en, INT_TYPE_DAMAGE_LEVEL) - 1);

							set_client_server_entity_int_value (en, INT_TYPE_DAMAGE_LEVEL, damage_level);
							
							if (damage_level <= 0)
								kill_client_server_entity (en);
							
							return;
						}
				}

				//
				////////////////////////////////////////

				break;
			}
			////////////////////////////////////////
			case ENTITY_PLAYER_LOCAL:
			////////////////////////////////////////
			{
				vec3d* pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);
				entity* sec = NULL;

				ASSERT (en == get_gunship_entity ());

				if (raw->invulnerable_timer > 0.0)
				{

					raw->invulnerable_timer -= get_delta_time ();
				}

				if (pos)
				{
					sec = get_local_sector_entity(pos);
					gunship_current_sector = (sector *) get_local_entity_data(sec);
				}

				update_current_flight_dynamics_fuel_weight ();

				update_current_flight_dynamics_flight_time ();

				////////////////////////////////////////
				if ((!get_local_entity_int_value (en, INT_TYPE_AUTO_PILOT)) && (!get_local_entity_int_value (en, INT_TYPE_EJECTED)))
				{

					update_flight_dynamics ();

					update_player_helicopter_waypoint_distance (en);
				}
				else
				{
					if ((damage_type == AIRCRAFT_DAMAGE_CRITICAL) || (get_local_entity_int_value (en, INT_TYPE_EJECTED)) || (get_local_entity_int_value (en, INT_TYPE_LANDED)))
					{

						set_current_flight_dynamics_auto_pilot (FALSE);

						if (get_local_entity_int_value (en, INT_TYPE_LANDED))
						{

							set_current_flight_dynamics_rotor_brake (TRUE);

							current_flight_dynamics->input_data.collective.value = 0.0;
						}
					}

					for (loop = 0; loop < get_entity_movement_iterations (); loop ++)
					{

						if (get_local_entity_int_value (en, INT_TYPE_EJECTED) || raw->main_rotor_rpm < 50 && get_local_entity_int_value (en, INT_TYPE_AIRBORNE_AIRCRAFT))
						{

							helicopter_death_movement (en);
						}
						else
						{

							ASSERT(point_inside_map_area(&raw->ac.mob.position));

							get_3d_terrain_point_data (raw->ac.mob.position.x, raw->ac.mob.position.z, &raw->ac.terrain_info);

							helicopter_movement (en);

							if (get_local_entity_int_value (en, INT_TYPE_AUTO_PILOT))
							{

								set_dynamics_entity_values (en);
							}
						}
					}
				}
				////////////////////////////////////////

				transmit_entity_comms_message (ENTITY_COMMS_UPDATE, en);

				////////////////////////////////////////
				//
				// ORDER IS CRITICAL
				//

				if (raw->ac.mob.alive)
				{
					update_aircraft_loading_doors (en);

					update_aircraft_cargo_doors (en);

					update_aircraft_undercarriage (en);

					update_aircraft_weapon_system_ready (en);

					update_entity_weapon_systems (en);

					update_entity_weapon_system_weapon_and_target_vectors (en);

					update_avionics ();

					update_cockpits ();

					update_aircraft_decoy_release (en);
				}

				//
				////////////////////////////////////////

				//
				// Check if gunship has a task - if not then set gunship entity to NULL
				//
// arneh 20061223 - removed this to stop helicopter going to outside view after landing a successful mission
/*
				if (!get_local_entity_parent (en, LIST_TYPE_FOLLOWER))
				{
					if (!get_local_entity_int_value (en, INT_TYPE_EJECTED))
					{
						if ((en == get_gunship_entity ()) && (get_game_type () != GAME_TYPE_FREE_FLIGHT)) // Jabberwock 030201 - but not in free flight
						{
							set_gunship_entity (NULL);
						}
					}
				}
*/
				break;
			}
			////////////////////////////////////////
			case ENTITY_PLAYER_REMOTE:
			////////////////////////////////////////
			{

				////////////////////////////////////////

				if (raw->invulnerable_timer > 0.0)
				{

					raw->invulnerable_timer -= get_delta_time ();
				}

				if ((get_local_entity_int_value (en, INT_TYPE_AUTO_PILOT)) || (get_local_entity_int_value (en, INT_TYPE_EJECTED)))
				{

					for (loop = 0; loop < get_entity_movement_iterations (); loop ++)
					{

						if (get_local_entity_int_value (en, INT_TYPE_EJECTED) || raw->main_rotor_rpm < 50 && get_local_entity_int_value (en, INT_TYPE_AIRBORNE_AIRCRAFT))
						{

							helicopter_death_movement (en);
						}
						else
						{

							if (!get_local_entity_int_value (en, INT_TYPE_LANDED))
							{

								ASSERT(point_inside_map_area(&raw->ac.mob.position));

								get_3d_terrain_point_data (raw->ac.mob.position.x, raw->ac.mob.position.z, &raw->ac.terrain_info);
							}

							helicopter_movement (en);
						}
					}

					#if DEBUG_MODULE

					debug_log ("HC_UPDT: SERVER: moving client %d using AUTO PILOT", get_local_entity_index (en));

					#endif
				}
				else
				{

					interpolate_entity_position (en);

					update_player_helicopter_waypoint_distance (en);
				}

				////////////////////////////////////////
				//
				// ORDER IS CRITICAL
				//

				if (raw->ac.mob.alive)
				{
					update_aircraft_loading_doors (en);

					update_aircraft_cargo_doors (en);

					update_aircraft_undercarriage (en);

					update_aircraft_weapon_system_ready (en);

					update_entity_weapon_systems (en);

					update_entity_weapon_system_weapon_and_target_vectors (en);
				}

				//
				////////////////////////////////////////

				break;
			}
		}

		if (tacview_is_logging() && raw->ac.mob.alive)
		{
			int
				moved = get_local_entity_int_value(en, INT_TYPE_MOBILE_MOVING),
				rotated = get_local_entity_int_value(en, INT_TYPE_ROTATED);

			if (en == get_gunship_entity())
				tacview_update_gunship();

			if (moved || rotated || command_line_tacview_logging < 3)
				write_tacview_unit_update(en, moved, rotated, FALSE);
		}
	}
	else
	{
		if (get_local_entity_int_value (en, INT_TYPE_OPERATIONAL_STATE) == OPERATIONAL_STATE_DEAD)
		{
			raw->ac.death_timer += get_delta_time ();

			if (!((int)(raw->ac.death_timer + 1) % 300))
				if (raw->ac.death_timer >= calculate_mobile_death_timer_value (en))
				{
					if (get_local_entity_int_value (en, INT_TYPE_PLAYER) == ENTITY_PLAYER_AI)
					{
						//
						// don't destroy helicopters while they are still occupied by players (otherwise avionics / pilot-entity etc. don't get deinitialised)
						//

						destroy_client_server_entity_family (en);
					}
					else
					{
						raw->ac.death_timer = 0.0;
					}
				}
		}
		else
		{
			for (loop = 0; loop < get_entity_movement_iterations (); loop ++)
			{
				helicopter_death_movement (en);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_client (entity *en)
{
	helicopter
		*raw;

	int
		loop;

	aircraft_damage_types
		damage_type;

	raw = (helicopter *) get_local_entity_data (en);

	update_local_entity_view_interest_level (en);

	update_local_helicopter_rotor_sounds (en);

	damage_type = aircraft_critically_damaged (en);

	if (raw->ac.mob.alive)
	{
		switch (raw->player)
		{
			////////////////////////////////////////
			case ENTITY_PLAYER_AI:
			////////////////////////////////////////
			{

				////////////////////////////////////////

				for (loop = 0; loop < get_entity_movement_iterations (); loop ++)
				{

					if (get_local_entity_int_value (en, INT_TYPE_EJECTED) || raw->main_rotor_rpm < 50 && get_local_entity_int_value (en, INT_TYPE_AIRBORNE_AIRCRAFT))
					{

						helicopter_death_movement (en);
					}
					else
					{

						if (!get_local_entity_int_value (en, INT_TYPE_LANDED))
						{

							ASSERT(point_inside_map_area(&raw->ac.mob.position));

							get_3d_terrain_point_data (raw->ac.mob.position.x, raw->ac.mob.position.z, &raw->ac.terrain_info);
						}

						helicopter_movement (en);
					}
				}

				////////////////////////////////////////

				////////////////////////////////////////
				//
				// ORDER IS CRITICAL
				//

				if (raw->ac.mob.alive)
				{
					update_rotors (en);

					update_aircraft_loading_doors (en);

					update_aircraft_cargo_doors (en);

					update_aircraft_undercarriage (en);

					update_aircraft_weapon_system_ready (en);

					update_entity_weapon_systems (en);

					update_entity_weapon_system_weapon_and_target_vectors (en);
				}

				//
				////////////////////////////////////////

				break;
			}
			////////////////////////////////////////
			case ENTITY_PLAYER_LOCAL:
			////////////////////////////////////////
			{

				if (en != get_gunship_entity ())
				{

					//
					// Client might be waiting for server to set old gunship to AI controlled.
					//

					return;
				}

				if (raw->invulnerable_timer > 0.0)
				{

					raw->invulnerable_timer -= get_delta_time ();
				}

				update_current_flight_dynamics_fuel_weight ();

				if ((!fire_continuous_weapon) && (get_local_entity_sound_type_valid (en, weapon_database [raw->ac.selected_weapon].launch_sound_effect_sub_type)))
				{
					pause_client_server_continuous_weapon_sound_effect (en, raw->ac.selected_weapon);
				}

				//helicopter_death_movement (en);
				////////////////////////////////////////
				if ((!get_local_entity_int_value (en, INT_TYPE_AUTO_PILOT)) && (!get_local_entity_int_value (en, INT_TYPE_EJECTED)))
				{

					update_flight_dynamics ();

					transmit_entity_comms_message (ENTITY_COMMS_UPDATE, en);
				}
				else
				{

					if (get_local_entity_int_value (en, INT_TYPE_LANDED))
					{

						if (get_local_entity_int_value (en, INT_TYPE_AUTO_PILOT))
						{

							set_current_flight_dynamics_rotor_brake (TRUE);

							set_current_flight_dynamics_auto_pilot (FALSE);

							current_flight_dynamics->input_data.collective.value = 0.0;
						}
					}

					if ((damage_type == AIRCRAFT_DAMAGE_CRITICAL) || (get_local_entity_int_value (en, INT_TYPE_EJECTED)) || (get_local_entity_int_value (en, INT_TYPE_LANDED)))
					{

						set_current_flight_dynamics_auto_pilot (FALSE);
					}

					for (loop = 0; loop < get_entity_movement_iterations (); loop ++)
					{

						if (get_local_entity_int_value (en, INT_TYPE_EJECTED) || raw->main_rotor_rpm < 50 && get_local_entity_int_value (en, INT_TYPE_AIRBORNE_AIRCRAFT))
						{

							helicopter_death_movement (en);
						}
						else
						{

							if (!get_local_entity_int_value (en, INT_TYPE_LANDED))
							{

								ASSERT(point_inside_map_area(&raw->ac.mob.position));

								get_3d_terrain_point_data (raw->ac.mob.position.x, raw->ac.mob.position.z, &raw->ac.terrain_info);
							}

							helicopter_movement (en);

							if (get_local_entity_int_value (en, INT_TYPE_AUTO_PILOT))
							{

								set_dynamics_entity_values (get_gunship_entity ());
							}
						}
					}
				}

				////////////////////////////////////////
				//
				// ORDER IS CRITICAL
				//

				if (raw->ac.mob.alive)
				{
					update_aircraft_loading_doors (en);

					update_aircraft_cargo_doors (en);

					update_aircraft_undercarriage (en);

					update_aircraft_weapon_system_ready (en);

					update_entity_weapon_systems (en);

					update_entity_weapon_system_weapon_and_target_vectors (en);

					update_avionics ();

					update_cockpits ();

					update_aircraft_decoy_release (en);
				}

				//
				////////////////////////////////////////

				//
				// Check if gunship has a task - if not then set gunship entity to NULL
				//

				if (!get_local_entity_parent (en, LIST_TYPE_FOLLOWER))
				{
					if (!get_local_entity_int_value (en, INT_TYPE_EJECTED))
					{
						if ((en == get_gunship_entity ()) && (get_game_type () != GAME_TYPE_FREE_FLIGHT)) // Jabberwock 040201 - but not in free flight
						{
							set_gunship_entity (NULL);
						}
					}
				}

				break;
			}
			////////////////////////////////////////
			case ENTITY_PLAYER_REMOTE:
			////////////////////////////////////////
			{
				////////////////////////////////////////
				//
				// ORDER IS CRITICAL
				//

				if (raw->ac.mob.alive)
				{
					update_aircraft_loading_doors (en);

					update_aircraft_cargo_doors (en);

					update_aircraft_undercarriage (en);

					update_aircraft_weapon_system_ready (en);

					update_entity_weapon_systems (en);

					update_entity_weapon_system_weapon_and_target_vectors (en);
				}

				if ((get_local_entity_int_value (en, INT_TYPE_AUTO_PILOT)) || (get_local_entity_int_value (en, INT_TYPE_EJECTED)))
				{

					for (loop = 0; loop < get_entity_movement_iterations (); loop ++)
					{

						// no need for death_movement as if the remote_player is damaged it will default back to manual flight.
						if (get_local_entity_int_value (en, INT_TYPE_EJECTED))
						{

							helicopter_death_movement (en);
						}
						else
						{

							if (!get_local_entity_int_value (en, INT_TYPE_LANDED))
							{

								ASSERT(point_inside_map_area(&raw->ac.mob.position));

								get_3d_terrain_point_data (raw->ac.mob.position.x, raw->ac.mob.position.z, &raw->ac.terrain_info);
							}

							helicopter_movement (en);
						}
					}
				}
				else
				{

					interpolate_entity_position (en);
				}

				//
				////////////////////////////////////////

				break;
			}
		}

		if (tacview_is_logging() && raw->ac.mob.alive)
		{
			int
				moved = get_local_entity_int_value(en, INT_TYPE_MOVED),
				rotated = get_local_entity_int_value(en, INT_TYPE_ROTATED);

			if (en == get_gunship_entity())
				tacview_update_gunship();

			if (moved || rotated)
				write_tacview_unit_update(en, moved, rotated, FALSE);
		}

	}
	else
	{
		if (get_local_entity_int_value (en, INT_TYPE_OPERATIONAL_STATE) == OPERATIONAL_STATE_DEAD)
		{
			raw->ac.death_timer += get_delta_time ();
		}
		else
		{
			for (loop = 0; loop < get_entity_movement_iterations (); loop ++)
			{
				helicopter_death_movement (en);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_helicopter_update_functions (void)
{
	fn_update_client_server_entity[ENTITY_TYPE_HELICOPTER][COMMS_MODEL_SERVER]  	= update_server;

	fn_update_client_server_entity[ENTITY_TYPE_HELICOPTER][COMMS_MODEL_CLIENT]  	= update_client;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reset_interpolation_timer (void)
{

	connection_list_type
		*connection;

	if (get_comms_model () == COMMS_MODEL_CLIENT)
	{

		connection = get_connection_list_item (get_server_id ());

		if (connection)
		{

			connection->interpolation_time = get_system_time ();
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void interpolate_entity_position (entity *en)
{

	vec3d
		new_position,
		*motion_vector,
		*position;

	connection_list_type
		*connection;

	float
		delta_time;

	if ((!command_line_comms_interpolate_gunships) || (get_local_entity_int_value (en, INT_TYPE_LANDED)))
	{

		return;
	}

	position = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

	motion_vector = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_MOTION_VECTOR);

	if (get_comms_model () == COMMS_MODEL_CLIENT)
	{

		connection = get_connection_list_item (get_server_id ());
	}
	else
	{

		connection = get_gunships_connection_list_item (en);
	}

	if (connection)
	{

		delta_time = (float) (get_system_time () - connection->interpolation_time) / TIME_1_SECOND;

		new_position.x = position->x + motion_vector->x * delta_time;
		new_position.y = position->y + motion_vector->y * delta_time;
		new_position.z = position->z + motion_vector->z * delta_time;

		set_local_entity_vec3d (en, VEC3D_TYPE_POSITION, &new_position);

		if (get_comms_model () == COMMS_MODEL_SERVER)
		{

			connection->interpolation_time = get_system_time ();
		}

		#if DEBUG_MODULE

		debug_log ("SERVER: interpolating entity %s (%d) old [%f, %f, %f], new [%f, %f, %f], motion_vector [%f, %f, %f], deltatime %f",
						get_local_entity_string (en, STRING_TYPE_FULL_NAME),
						get_local_entity_index (en),
						position->x, position->y, position->z,
						new_position.x, new_position.y, new_position.z,
						motion_vector->x, motion_vector->y, motion_vector->z,
						delta_time);

		#endif
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
