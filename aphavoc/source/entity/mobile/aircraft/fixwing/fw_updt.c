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

static void update_propellors (entity *en)
{

	fixed_wing
		*raw;

	entity
		*group;

	raw = (fixed_wing *) get_local_entity_data (en);

	group = get_local_entity_parent (en, LIST_TYPE_MEMBER);

	ASSERT (group);

	if (!in_flight_articulation_test)
	{
		if (get_local_entity_int_value (en, INT_TYPE_LANDED))
		{
			raw->propellor_rpm -= 5.0 * get_delta_time ();
		}
		else
		{
			raw->propellor_rpm += 5.0 * get_delta_time ();
		}
	}

	raw->propellor_rpm = bound (raw->propellor_rpm, 0.0, 100.0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_server (entity *en)
{
	fixed_wing
		*raw;

	int
		loop;

	aircraft_damage_types
		damage_type;

	raw = (fixed_wing *) get_local_entity_data (en);

	update_local_entity_view_interest_level (en);

	damage_type = aircraft_critically_damaged (en);

	if (raw->ac.mob.alive)
	{

		////////////////////////////////////////

		for (loop = 0; loop < get_entity_movement_iterations (); loop ++)
		{

			if (!get_local_entity_int_value (en, INT_TYPE_LANDED))
			{

				ASSERT(point_inside_map_area(&raw->ac.mob.position));

				get_3d_terrain_point_data (raw->ac.mob.position.x, raw->ac.mob.position.z, &raw->ac.terrain_info);
			}

			basic_fixed_wing_movement (en);
		}

		////////////////////////////////////////

		update_propellors (en);

		update_fixed_wing_afterburners (en);

		update_fixed_wing_airbrakes (en);

		update_fixed_wing_flaps (en);

		update_aircraft_loading_doors (en);

		update_aircraft_cargo_doors (en);

		update_aircraft_undercarriage (en);

		update_aircraft_rudder (en);

		////////////////////////////////////////
		//
		// ORDER IS CRITICAL
		//

		update_aircraft_target_scan (en);

		update_aircraft_weapon_system_ready (en);

		update_entity_weapon_systems (en);

		update_entity_weapon_system_weapon_and_target_vectors (en);

		update_aircraft_weapon_fire (en);

		update_aircraft_decoy_release (en);

		//
		////////////////////////////////////////

		update_fixed_wing_crate_dropping (en);

		if (tacview_is_logging() && raw->ac.mob.alive)
		{
			int
				moved = get_local_entity_int_value(en, INT_TYPE_MOBILE_MOVING),
				rotated = get_local_entity_int_value(en, INT_TYPE_ROTATED);

			if (moved || rotated || command_line_tacview_logging < 3)
				write_tacview_unit_update(en, moved, rotated, FALSE);
		}
		
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
	else
	{
		update_fixed_wing_afterburners (en);

		if (get_local_entity_int_value (en, INT_TYPE_OPERATIONAL_STATE) == OPERATIONAL_STATE_DEAD)
		{
			raw->ac.death_timer += get_delta_time ();

			if (!((int)(raw->ac.death_timer + 1) % 300))
				if (raw->ac.death_timer >= calculate_mobile_death_timer_value (en))
				{
					destroy_client_server_entity_family (en);
				}
		}
		else
		{
			for (loop = 0; loop < get_entity_movement_iterations (); loop ++)
			{
				basic_fixed_wing_death_movement (en);
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_client (entity *en)
{
	fixed_wing
		*raw;

	int
		loop;

	raw = (fixed_wing *) get_local_entity_data (en);

	update_local_entity_view_interest_level (en);

	if (raw->ac.mob.alive)
	{

		////////////////////////////////////////

		for (loop = 0; loop < get_entity_movement_iterations (); loop ++)
		{

			if (!get_local_entity_int_value (en, INT_TYPE_LANDED))
			{

				ASSERT(point_inside_map_area(&raw->ac.mob.position));

				get_3d_terrain_point_data (raw->ac.mob.position.x, raw->ac.mob.position.z, &raw->ac.terrain_info);
			}

			basic_fixed_wing_movement (en);
		}

		////////////////////////////////////////

		update_propellors (en);

		update_fixed_wing_afterburners (en);

		update_fixed_wing_airbrakes (en);

		update_fixed_wing_flaps (en);

		update_aircraft_loading_doors (en);

		update_aircraft_cargo_doors (en);

		update_aircraft_undercarriage (en);

		update_aircraft_rudder (en);

		////////////////////////////////////////
		//
		// ORDER IS CRITICAL
		//

		update_aircraft_weapon_system_ready (en);

		update_entity_weapon_systems (en);

		update_entity_weapon_system_weapon_and_target_vectors (en);

		//
		////////////////////////////////////////

		if (tacview_is_logging() && raw->ac.mob.alive)
		{
			int
				moved = get_local_entity_int_value(en, INT_TYPE_MOBILE_MOVING),
				rotated = get_local_entity_int_value(en, INT_TYPE_ROTATED);

			if (moved || rotated || command_line_tacview_logging < 3)
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
				basic_fixed_wing_death_movement (en);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_fixed_wing_update_functions (void)
{
	fn_update_client_server_entity[ENTITY_TYPE_FIXED_WING][COMMS_MODEL_SERVER]  	= update_server;

	fn_update_client_server_entity[ENTITY_TYPE_FIXED_WING][COMMS_MODEL_CLIENT]  	= update_client;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
