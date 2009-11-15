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

// 2 levels of debug

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void destroy_local (entity *en)
{

	ship_vehicle
		*raw;

	////////////////////////////////////////
	//
	// PRE-AMBLE
	//
	////////////////////////////////////////

	#if DEBUG_MODULE >= 2

	debug_log_entity_args (ENTITY_DEBUG_LOCAL, ENTITY_DEBUG_DESTROY, en);

	#endif

	raw = (ship_vehicle *) get_local_entity_data (en);

	set_local_entity_int_value (en, INT_TYPE_ALIVE, FALSE);

	////////////////////////////////////////
	//
	// VALIDATE
	//
	////////////////////////////////////////

	////////////////////////////////////////
	//
	// DESTROY COMPONENTS
	//
	////////////////////////////////////////

	destruct_3d_object (raw->vh.inst3d);

	free_mem (raw->vh.weapon_package_status_array);

	if (raw->vh.sound_effect_data)
	{

		destroy_system_sound_effect (raw->vh.sound_effect_data);
	}

	////////////////////////////////////////
	//
	// UNLINK FROM SYSTEM
	//
	////////////////////////////////////////

	//
	// ship_vehicle
	//

	//
	// vehicle
	//

	unlink_local_entity_children (en, LIST_TYPE_TASK_DEPENDENT);

	unlink_local_entity_children (en, LIST_TYPE_LAUNCHED_WEAPON);

	unlink_local_entity_children (en, LIST_TYPE_MOVEMENT_DEPENDENT);

	delete_local_entity_from_parents_child_list (en, LIST_TYPE_MOVEMENT_DEPENDENT);

	delete_local_entity_from_parents_child_list (en, LIST_TYPE_FOLLOWER);

	delete_local_entity_from_parents_child_list (en, LIST_TYPE_DESIGNATED_TARGET); // Jabberwock 031107 Designated targets

	delete_local_entity_from_parents_child_list (en, LIST_TYPE_GUNSHIP_TARGET);

	delete_local_entity_from_parents_child_list (en, LIST_TYPE_MEMBER);

	delete_local_entity_from_parents_child_list (en, LIST_TYPE_VIEW);

	delete_local_entity_from_parents_child_list (en, LIST_TYPE_TAKEOFF_QUEUE);

	//
	// mobile
	//

	unlink_local_entity_children (en, LIST_TYPE_SPECIAL_EFFECT);

	unlink_local_entity_children (en, LIST_TYPE_TARGET);

	delete_local_entity_from_parents_child_list (en, LIST_TYPE_PADLOCK);

	delete_local_entity_from_parents_child_list (en, LIST_TYPE_SECTOR);

	delete_local_entity_from_parents_child_list (en, LIST_TYPE_TARGET);

	delete_local_entity_from_parents_child_list (en, LIST_TYPE_UPDATE);

	#if LANDING_ROUTE_CHECK

	destroy_debug_entity_landing_route_check (en);

	#endif

	////////////////////////////////////////
	//
	// FREE ENTITY DATA
	//
	////////////////////////////////////////

	free_mem (raw);

	set_free_entity (en);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void destroy_remote (entity *en)
{
	#if DEBUG_MODULE >= 2

	debug_log_entity_args (ENTITY_DEBUG_REMOTE, ENTITY_DEBUG_DESTROY, en);

	#endif

	transmit_entity_comms_message (ENTITY_COMMS_DESTROY, en);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void destroy_server (entity *en)
{
	//
	// destroy remote entity first (keeping local entity valid)
	//

	validate_client_server_remote_fn ();

	destroy_remote (en);

	validate_client_server_local_fn ();

	//
	// destroy local using 'full' function
	//

	destroy_local_entity (en);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void destroy_client (entity *en)
{
	if (get_comms_data_flow () == COMMS_DATA_FLOW_TX)
	{
		validate_client_server_remote_fn ();

		destroy_remote (en);
	}
	else
	{
		validate_client_server_local_fn ();

		//
		// destroy local using 'full' function
		//

		destroy_local_entity (en);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void destroy_local_family (entity *en)
{
	destroy_local_entity_children (en, LIST_TYPE_MOVEMENT_DEPENDENT);

	destroy_local_sound_effects (en);

	destroy_local_entity (en);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void destroy_server_family (entity *en)
{
	destroy_client_server_entity_children (en, LIST_TYPE_MOVEMENT_DEPENDENT);

	destroy_client_server_sound_effects (en);

	destroy_client_server_entity (en);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void destroy_client_family (entity *en)
{
	#if DEBUG_MODULE >= 2

	debug_log_entity_args (ENTITY_DEBUG_REMOTE, ENTITY_DEBUG_DESTROY_FAMILY, en);

	#endif

	transmit_entity_comms_message (ENTITY_COMMS_DESTROY_FAMILY, en);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void kill_local (entity *en)
{

	int
		losses;

	entity
		*task,
		*group,
		*keysite,
		*destroy_task;

	ship_vehicle
		*raw;

	////////////////////////////////////////
	//
	// PRE-AMBLE
	//
	////////////////////////////////////////

	#if DEBUG_MODULE >= 2

	debug_log_entity_args (ENTITY_DEBUG_LOCAL, ENTITY_DEBUG_KILL, en);

	#endif

	if (!get_local_entity_int_value (en, INT_TYPE_ALIVE))
	{
		return;
	}

	raw = (ship_vehicle *) get_local_entity_data (en);

	group = get_local_entity_parent (en, LIST_TYPE_MEMBER);

	ASSERT (group);

	keysite = NULL;

	if (tacview_is_logging())
		write_tacview_unit_event(en, TACVIEW_UNIT_DESTROYED, NULL);

	//
	// update force info
	//

	remove_from_force_info (get_local_force_entity ((entity_sides) raw->vh.mob.side), en);

	////////////////////////////////////////
	//
	// VALIDATE
	//
	////////////////////////////////////////

	////////////////////////////////////////
	//
	// DESTROY COMPONENTS
	//
	////////////////////////////////////////

	if (get_comms_model () == COMMS_MODEL_SERVER)
	{
		task = get_local_entity_first_child (en, LIST_TYPE_TASK_DEPENDENT);

		while (task)
		{
			destroy_task = task;

			task = get_local_entity_child_succ (task, LIST_TYPE_TASK_DEPENDENT);

			if (destroy_task->type == ENTITY_TYPE_TASK)
			{
				#if DEBUG_MODULE

				debug_log ("SH_DSTRY: killing ship, notifying task %s complete", entity_sub_type_task_names [get_local_entity_int_value (destroy_task, INT_TYPE_ENTITY_SUB_TYPE)]);

				#endif

				notify_local_entity (ENTITY_MESSAGE_TASK_COMPLETED, destroy_task, en, TASK_TERMINATED_OBJECTIVE_MESSAGE);
			}
		}

		//
		// Release landing lock (if any)
		//

		release_mobile_entity_landing_locks (en);

		////////////////////////////////////////
		//
		// UNLINK FROM SYSTEM
		//
		////////////////////////////////////////

		//
		// Destroy keysite entity if ship is carrier
		//

		keysite = get_local_entity_first_child (en, LIST_TYPE_MOVEMENT_DEPENDENT);

		while (keysite)
		{
			if (get_local_entity_type (keysite) == ENTITY_TYPE_KEYSITE)
			{
				break;
			}

			keysite = get_local_entity_child_succ (keysite, LIST_TYPE_MOVEMENT_DEPENDENT);
		}
	}

	//
	// ship_vehicle
	//

	//
	// vehicle
	//

	unlink_local_entity_children (en, LIST_TYPE_TASK_DEPENDENT);

	unlink_local_entity_children (en, LIST_TYPE_MOVEMENT_DEPENDENT);

	delete_local_entity_from_parents_child_list (en, LIST_TYPE_MEMBER);

	delete_local_entity_from_parents_child_list (en, LIST_TYPE_MOVEMENT_DEPENDENT);

	delete_local_entity_from_parents_child_list (en, LIST_TYPE_FOLLOWER);

	// gunship_target_link

	// member_link

	// view_link

	delete_local_entity_from_parents_child_list (en, LIST_TYPE_TAKEOFF_QUEUE);

	//
	// mobile
	//

	//
	// kill weapon sound effects
	//

	kill_local_entity_sound_type (en, ENTITY_SUB_TYPE_EFFECT_SOUND_CHAIN_GUN);

	//
	// kill engine sound effects
	//

	kill_local_entity_sound_type (en, ENTITY_SUB_TYPE_EFFECT_SOUND_ENGINE_LOOPING1);
	kill_local_entity_sound_type (en, ENTITY_SUB_TYPE_EFFECT_SOUND_ENGINE_LOOPING2);

	unlink_local_entity_children (en, LIST_TYPE_TARGET);

	delete_local_entity_from_parents_child_list (en, LIST_TYPE_PADLOCK);

	// sector_link

	delete_local_entity_from_parents_child_list (en, LIST_TYPE_TARGET);

	// update_link

	set_local_entity_int_value (en, INT_TYPE_OPERATIONAL_STATE, OPERATIONAL_STATE_STOPPED);

	////////////////////////////////////////
	//
	// KILL
	//
	////////////////////////////////////////

	// must be done before alive flag set
	remove_mobile_values_from_sector (get_local_entity_parent (en, LIST_TYPE_SECTOR), en);

	set_local_entity_int_value (en, INT_TYPE_ALIVE, FALSE);

	damage_ship_3d_object (en);

	//
	// group losses
	//

	losses = get_local_entity_int_value (group, INT_TYPE_LOSSES);

	losses ++;

	set_local_entity_int_value (group, INT_TYPE_LOSSES, losses);

	//
	// task losses
	//

	task = get_local_group_primary_task (group);

	if (task)
	{
		losses = get_local_entity_int_value (task, INT_TYPE_LOSSES);

		losses ++;

		set_local_entity_int_value (task, INT_TYPE_LOSSES, losses);
	}

	//
	// Notify Campaign Screen
	//

	notify_campaign_screen (CAMPAIGN_SCREEN_GROUP_REMOVE_MEMBER, group);

	if (get_comms_model () == COMMS_MODEL_SERVER)
	{
		//
		// Notify the GROUP that the mobile has been killed  (N.B. must be done AFTER mobile is unlinked from member list)
		//

		notify_local_entity (ENTITY_MESSAGE_MOBILE_KILLED, group, en);

		//
		// Kill the keysite if ship is the carrier (N.B. must be done AFTER ships alive flag cleared)
		//

		if (keysite)
		{
			kill_client_server_entity (keysite);
		}
	}

	////////////////////////////////////////
	//
	// SPECIAL EFFECTS
	//
	////////////////////////////////////////

	if (get_comms_model () == COMMS_MODEL_SERVER)
	{
		create_client_server_object_killed_explosion_effect (en);
	}

	#if LANDING_ROUTE_CHECK

	destroy_debug_entity_landing_route_check (en);

	#endif

	/////////////////////////////////////////////////////////////////
	//
	// SPECIAL_EFFECT_HOOK FOR BEING_DESTROYED
	//
	/////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////
	//
	//
	/////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void kill_remote (entity *en)
{
	#if DEBUG_MODULE >= 2

	debug_log_entity_args (ENTITY_DEBUG_REMOTE, ENTITY_DEBUG_KILL, en);

	#endif

	transmit_entity_comms_message (ENTITY_COMMS_KILL, en);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void kill_server (entity *en)
{
	//
	// kill remote entity first (keeping local entity valid)
	//

	validate_client_server_remote_fn ();

	kill_remote (en);

	validate_client_server_local_fn ();

	//
	// kill local using 'full' function
	//

	kill_local_entity (en);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void kill_client (entity *en)
{
	if (get_comms_data_flow () == COMMS_DATA_FLOW_TX)
	{
		validate_client_server_remote_fn ();

		kill_remote (en);
	}
	else
	{
		validate_client_server_local_fn ();

		//
		// kill local using 'full' function
		//

		kill_local_entity (en);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_ship_vehicle_destroy_functions (void)
{
	fn_destroy_local_entity						[ENTITY_TYPE_SHIP_VEHICLE]								= destroy_local;
	fn_destroy_client_server_entity			[ENTITY_TYPE_SHIP_VEHICLE][COMMS_MODEL_SERVER]	= destroy_server;
	fn_destroy_client_server_entity			[ENTITY_TYPE_SHIP_VEHICLE][COMMS_MODEL_CLIENT]	= destroy_client;

	fn_destroy_local_entity_family			[ENTITY_TYPE_SHIP_VEHICLE]								= destroy_local_family;
	fn_destroy_client_server_entity_family	[ENTITY_TYPE_SHIP_VEHICLE][COMMS_MODEL_SERVER]	= destroy_server_family;
	fn_destroy_client_server_entity_family	[ENTITY_TYPE_SHIP_VEHICLE][COMMS_MODEL_CLIENT]	= destroy_client_family;

	fn_kill_local_entity							[ENTITY_TYPE_SHIP_VEHICLE]								= kill_local;
	fn_kill_client_server_entity				[ENTITY_TYPE_SHIP_VEHICLE][COMMS_MODEL_SERVER]	= kill_server;
	fn_kill_client_server_entity				[ENTITY_TYPE_SHIP_VEHICLE][COMMS_MODEL_CLIENT]	= kill_client;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
