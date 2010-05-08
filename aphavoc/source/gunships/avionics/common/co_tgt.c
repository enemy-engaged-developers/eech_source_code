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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MAX_TARGET_RANGE		(35000.0)
#define SQR_MAX_TARGET_RANGE	(MAX_TARGET_RANGE * MAX_TARGET_RANGE)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

target_acquisition_systems
	target_acquisition_system;

int
	target_locked;

float
	cpg_identify_target_delay;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char
	*target_acquisition_system_names[NUM_TARGET_ACQUISITION_SYSTEMS] =
	{
		"OFF",				// TARGET_ACQUISITION_SYSTEM_OFF
		"GROUND RADAR",	// TARGET_ACQUISITION_SYSTEM_GROUND_RADAR
		"AIR RADAR",		// TARGET_ACQUISITION_SYSTEM_AIR_RADAR
		"FLIR",	 			// TARGET_ACQUISITION_SYSTEM_FLIR
		"DTV",				// TARGET_ACQUISITION_SYSTEM_DTV
		"DVO",  				// TARGET_ACQUISITION_SYSTEM_DVO
		"LLLTV",	  			// TARGET_ACQUISITION_SYSTEM_LLLTV
		"PERISCOPE",		// TARGET_ACQUISITION_SYSTEM_PERISCOPE
		"IHADSS",  			// TARGET_ACQUISITION_SYSTEM_IHADSS
		"HIDSS",				// TARGET_ACQUISITION_SYSTEM_HIDSS
		"HMS",	  			// TARGET_ACQUISITION_SYSTEM_HMS
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
	continuous_target_acquisition_system_steer_left_key,
	continuous_target_acquisition_system_steer_right_key,
	continuous_target_acquisition_system_steer_up_key,
	continuous_target_acquisition_system_steer_down_key;

int
	single_target_acquisition_system_steer_left_key,
	single_target_acquisition_system_steer_right_key,
	single_target_acquisition_system_steer_up_key,
	single_target_acquisition_system_steer_down_key,
	single_target_acquisition_system_inc_range_key,
	single_target_acquisition_system_dec_range_key,
	single_target_acquisition_system_inc_target_priority_key,
	single_target_acquisition_system_dec_target_priority_key,
	single_target_acquisition_system_select_next_target_key,
	single_target_acquisition_system_select_previous_target_key,
	single_target_acquisition_system_select_next_designated_key, // Jabberwock 031107 Designated targets
	single_target_acquisition_system_select_previous_designated_key;

int
	continuous_target_acquisition_system_steer_left_fast_key,
	continuous_target_acquisition_system_steer_right_fast_key,
	continuous_target_acquisition_system_steer_up_fast_key,
	continuous_target_acquisition_system_steer_down_fast_key;

int
	single_target_acquisition_system_steer_left_fast_key,
	single_target_acquisition_system_steer_right_fast_key,
	single_target_acquisition_system_steer_up_fast_key,
	single_target_acquisition_system_steer_down_fast_key,
	single_target_acquisition_system_inc_range_fast_key,
	single_target_acquisition_system_dec_range_fast_key,
	single_target_acquisition_system_inc_target_priority_fast_key,
	single_target_acquisition_system_dec_target_priority_fast_key;

int
	continuous_target_acquisition_system_steer_left_fine_key,
	continuous_target_acquisition_system_steer_right_fine_key,
	continuous_target_acquisition_system_steer_up_fine_key,
	continuous_target_acquisition_system_steer_down_fine_key;

int
	toggle_ground_stabilisation_key;

int
	// Jabberwock 030930 Mouse functions
	mouse_move_left,
	mouse_move_right,
	mouse_move_up,
	mouse_move_down,
	mouse_wheel_up,
	mouse_wheel_down;
	


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_common_target_acquisition_systems (void)
{
	set_gunship_target (NULL);

	target_acquisition_system = TARGET_ACQUISITION_SYSTEM_OFF;

	target_locked = FALSE;

	cpg_identify_target_delay = 0.0;

	weapon_lock_type = WEAPON_LOCK_NO_ACQUIRE;

	reset_common_target_acquisition_system_keys ();

	initialise_common_radar ();

	initialise_common_eo ();

	initialise_common_hms ();

	#if DEBUG_MODULE

	debug_colour_watch (DEBUG_COLOUR_AMBER, "target_acquisition_system = %d", MT_INT, &target_acquisition_system);

	debug_colour_watch (DEBUG_COLOUR_AMBER, "target_locked = %d", MT_INT, &target_locked);

	debug_colour_watch (DEBUG_COLOUR_AMBER, "ground_radar.target_locked = %d", MT_INT, &ground_radar.target_locked);

	debug_colour_watch (DEBUG_COLOUR_AMBER, "air_radar.target_locked = %d", MT_INT, &air_radar.target_locked);

	debug_colour_watch (DEBUG_COLOUR_AMBER, "eo_target_locked = %d", MT_INT, &eo_target_locked);

	debug_colour_watch (DEBUG_COLOUR_AMBER, "eo_on_target = %d", MT_INT, &eo_on_target);

	debug_colour_watch (DEBUG_COLOUR_AMBER, "eo_low_light = %d", MT_INT, &eo_low_light);

	debug_colour_watch (DEBUG_COLOUR_AMBER, "eo_sensor = %d", MT_INT, &eo_sensor);

	debug_colour_watch (DEBUG_COLOUR_AMBER, "hms_target_locked = %d", MT_INT, &hms_target_locked);

	debug_colour_watch (DEBUG_COLOUR_AMBER, "cpg_identify_target_delay = %.2f", MT_FLOAT, &cpg_identify_target_delay);

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_common_target_acquisition_systems (void)
{
	//
	// unlink targets
	//

	set_gunship_target (NULL);

	unlink_local_entity_children (get_gunship_entity (), LIST_TYPE_GUNSHIP_TARGET);
	
	unlink_local_entity_children (get_gunship_entity (), LIST_TYPE_DESIGNATED_TARGET); // Jabberwock Designated targets

	//
	// deinitialise sensors
	//

	deinitialise_common_radar ();

	deinitialise_common_eo ();

	deinitialise_common_hms ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_gunship_target_list (void)
{
	int
		remove_target;

	float
		sqr_target_range,
		timeout;

	entity
		*source,
		*target,
		*current_target,
		*succ;

	vec3d
		*source_position,
		*target_position;

	source = get_gunship_entity ();
	source_position = get_local_entity_vec3d_ptr (source, VEC3D_TYPE_POSITION);

	if (target_acquisition_system != TARGET_ACQUISITION_SYSTEM_AIR_RADAR &&
		target_acquisition_system != TARGET_ACQUISITION_SYSTEM_GROUND_RADAR)
	{
		cpg_scan_for_eo_targets();
	}

	target = get_local_entity_first_child (source, LIST_TYPE_GUNSHIP_TARGET);
	current_target = get_local_entity_parent (source, LIST_TYPE_TARGET);

	while (target)
	{
		remove_target = FALSE;

		//
		// check range
		//

		succ = get_local_entity_child_succ (target, LIST_TYPE_GUNSHIP_TARGET);

		target_position = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

		sqr_target_range = get_sqr_3d_range (source_position, target_position);

		if (sqr_target_range > SQR_MAX_TARGET_RANGE)
		{
			remove_target = TRUE;
		}

		//
		// check air radar contact timeout
		//

		timeout = get_local_entity_float_value (target, FLOAT_TYPE_AIR_RADAR_CONTACT_TIMEOUT);

		if (timeout != AIR_RADAR_CONTACT_TIMEOUT_INVALID)
		{
			timeout -= get_delta_time ();

			if (timeout <= 0.0)
			{
				//
				// reset timeout to prevent repeatedly testing if the target is valid for air radar
				//

				timeout = AIR_RADAR_CONTACT_TIMEOUT;

				if (get_gunship_target_valid_for_air_radar (target))
				{
					if (!((target == current_target) && (target_acquisition_system != TARGET_ACQUISITION_SYSTEM_AIR_RADAR)))
					{
						remove_target = TRUE;
					}
				}
			}

			set_local_entity_float_value (target, FLOAT_TYPE_AIR_RADAR_CONTACT_TIMEOUT, timeout);
		}

		if (remove_target)
		{
			//
			// if unlinking the gunship target then do this client/server
			//

			if (target == current_target)
			{
				set_gunship_target (NULL);

				current_target = NULL;
			}

			delete_local_entity_from_parents_child_list (target, LIST_TYPE_GUNSHIP_TARGET);
		}

		target = succ;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_cpg_identify_target (void)
{
	int
		los_clear;

	entity
		*target;

	target = get_local_entity_parent (get_gunship_entity (), LIST_TYPE_TARGET);

	if (target)
	{
		if (eo_on_target)
		{
			if ((target_acquisition_system == TARGET_ACQUISITION_SYSTEM_GROUND_RADAR) || (target_acquisition_system == TARGET_ACQUISITION_SYSTEM_AIR_RADAR))
			{
				los_clear = get_local_entity_int_value (target, INT_TYPE_GUNSHIP_RADAR_LOS_CLEAR);
			}
			else
			{
				los_clear = TRUE;
			}

			if (los_clear)
			{
				if (cpg_identify_target_delay > 0.0)
				{
					cpg_identify_target_delay -= get_delta_time ();

					if (cpg_identify_target_delay < 0.0)
					{
						cpg_identify_target_delay = 0.0;

						set_local_entity_int_value (target, INT_TYPE_CPG_IDENTIFIED, TRUE);
						
            cpg_report_identified_target(target); //ataribaby 4/1/2009 added CPG next/prev target lock and ID
					}
				}
			}
		}
	}
	else
	{
		cpg_identify_target_delay = 0.0;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_common_target_acquisition_systems (void)
{
	update_common_hud ();

	update_gunship_target_list ();

	update_cpg_identify_target ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reset_common_target_acquisition_system_keys (void)
{
	continuous_target_acquisition_system_steer_left_key						= FALSE;
	continuous_target_acquisition_system_steer_right_key						= FALSE;
	continuous_target_acquisition_system_steer_up_key							= FALSE;
	continuous_target_acquisition_system_steer_down_key						= FALSE;

	single_target_acquisition_system_steer_left_key								= 0;
	single_target_acquisition_system_steer_right_key							= 0;
	single_target_acquisition_system_steer_up_key								= 0;
	single_target_acquisition_system_steer_down_key								= 0;
	single_target_acquisition_system_inc_range_key								= 0;
	single_target_acquisition_system_dec_range_key								= 0;
	single_target_acquisition_system_inc_target_priority_key					= 0;
	single_target_acquisition_system_dec_target_priority_key					= 0;
	single_target_acquisition_system_select_next_target_key					= 0;
	single_target_acquisition_system_select_previous_target_key				= 0;
	single_target_acquisition_system_select_next_designated_key					= 0;
	single_target_acquisition_system_select_previous_designated_key				= 0;


	continuous_target_acquisition_system_steer_left_fast_key					= FALSE;
	continuous_target_acquisition_system_steer_right_fast_key				= FALSE;
	continuous_target_acquisition_system_steer_up_fast_key					= FALSE;
	continuous_target_acquisition_system_steer_down_fast_key					= FALSE;

	single_target_acquisition_system_steer_left_fast_key						= 0;
	single_target_acquisition_system_steer_right_fast_key						= 0;
	single_target_acquisition_system_steer_up_fast_key							= 0;
	single_target_acquisition_system_steer_down_fast_key						= 0;
	single_target_acquisition_system_inc_range_fast_key						= 0;
	single_target_acquisition_system_dec_range_fast_key						= 0;
	single_target_acquisition_system_inc_target_priority_fast_key			= 0;
	single_target_acquisition_system_dec_target_priority_fast_key			= 0;

	continuous_target_acquisition_system_steer_left_fine_key					= FALSE;
	continuous_target_acquisition_system_steer_right_fine_key 				= FALSE;
	continuous_target_acquisition_system_steer_up_fine_key					= FALSE;
	continuous_target_acquisition_system_steer_down_fine_key					= FALSE;

	toggle_ground_stabilisation_key													= 0;
	
	// Jabberwock 030930 Mouse functions
	mouse_move_left															= 0;
	mouse_move_right														= 0;
	mouse_move_up															= 0;
	mouse_move_down															= 0;
	mouse_wheel_up															= 0; 
	mouse_wheel_down														= 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_common_target_acquisition_system_lock_target (int lock)
{
	ASSERT (get_gunship_entity ());

	switch (get_global_gunship_type ())
	{
		// JB 030313 Fly any aircraft
//		default:
		case GUNSHIP_TYPE_APACHE:
		{
			set_apache_lock_target (lock);

			break;
		}
		case GUNSHIP_TYPE_HAVOC:
		{
			set_havoc_lock_target (lock);

			break;
		}
		case GUNSHIP_TYPE_COMANCHE:
		{
			set_comanche_lock_target (lock);

			break;
		}
		case GUNSHIP_TYPE_HOKUM:
		{
			set_hokum_lock_target (lock);

			break;
		}
		////Moje 030519 Start
		case GUNSHIP_TYPE_BLACKHAWK:
		{
			set_blackhawk_lock_target (lock);

			break;
		}
		////Moje 030519 End
		////Moje 030612 start
		case GUNSHIP_TYPE_HIND:
		{
			set_hind_lock_target (lock);

			break;
		}
		////Moje 030612 end
		////Moje 030816 Start
		case GUNSHIP_TYPE_AH64A:
		{
			set_ah64a_lock_target (lock);

			break;
		}
		case GUNSHIP_TYPE_KA50:
		{
			set_ka50_lock_target (lock);
			break;
		}
		////Moje 030816 end

		//  GCsDriver  08-12-2007
		default:
		{
			set_default_lock_target (lock);

			break;
		}

	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_gunship_target (entity *target)
{
	vec3d
		*source_position,
		*target_position;

	float
		range;

	ASSERT (get_gunship_entity ());

	if (target != get_local_entity_parent (get_gunship_entity (), LIST_TYPE_TARGET))
	{
		#if 0

		////////////////////////////////////////
		//
		// this only works locally
		//
		////////////////////////////////////////

		delete_local_entity_from_parents_child_list (get_gunship_entity (), LIST_TYPE_TARGET);

		if (target)
		{
			insert_local_entity_into_parents_child_list (get_gunship_entity (), LIST_TYPE_TARGET, target, NULL);
		}

		#else

		////////////////////////////////////////
		//
		// this works client/server but assumes that targets can only be 'killed' and not 'destroyed'
		//
		////////////////////////////////////////

		set_client_server_entity_parent (get_gunship_entity (), LIST_TYPE_TARGET, target);

		#endif

		////////////////////////////////////////
		//
		// CP/G identify delay
		//
		////////////////////////////////////////

		cpg_identify_target_delay = 0.0;

		if (target)
		{
			if (!get_local_entity_int_value (target, INT_TYPE_CPG_IDENTIFIED))
			{
				source_position = get_local_entity_vec3d_ptr (get_gunship_entity (), VEC3D_TYPE_POSITION);

				target_position = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

				range = get_3d_range (source_position, target_position);

				if (range < 5000.0)
					cpg_identify_target_delay = (min (range, 5000.0f) * 0.0004) + (frand1 () * 1.0) + 0.25;
				else  // really long ID time for targets beyond 5KM
					cpg_identify_target_delay = (min (range, 8000.0f) * 0.001) + (frand1 () * 1.0) + 60.0;
			}
		}
	}

	if (!target  && !eo_is_tracking_point())
	{
		target_locked = FALSE;
		if (command_line_manual_laser_radar && !eo_is_tracking_point())
			set_laser_is_active(FALSE);  // laser can only be active when we have a target
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char *get_target_display_name (entity *target, char *buffer, int large_display)
{
	int
		allied;

	const char
		*target_name = NULL;

	ASSERT (buffer);

	switch (get_global_cpg_assist_type ())
	{
		////////////////////////////////////////
		case CPG_ASSIST_TYPE_NONE:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case CPG_ASSIST_TYPE_EASY:
		////////////////////////////////////////
		{
			if (target)
			{
				if (large_display)
				{
					if (get_local_entity_int_value (target, INT_TYPE_IDENTIFY_MOBILE))
					{
						allied = get_local_entity_int_value (get_gunship_entity (), INT_TYPE_SIDE) == get_local_entity_int_value (target, INT_TYPE_SIDE);

						if (allied)
						{
							sprintf (buffer, "ALLIED %s", get_local_entity_string (target, STRING_TYPE_EASY_DISPLAY_NAME));
						}
						else
						{
							sprintf (buffer, "ENEMY %s", get_local_entity_string (target, STRING_TYPE_EASY_DISPLAY_NAME));
						}
					}
					else
					{
						sprintf (buffer, "%s", get_local_entity_string (target, STRING_TYPE_EASY_DISPLAY_NAME));
					}
				}
				else
				{
					if (get_local_entity_int_value (target, INT_TYPE_IDENTIFY_MOBILE))
					{
						allied = get_local_entity_int_value (get_gunship_entity (), INT_TYPE_SIDE) == get_local_entity_int_value (target, INT_TYPE_SIDE);

						if (allied)
						{
							sprintf (buffer, "A/%s", get_local_entity_string (target, STRING_TYPE_EASY_DISPLAY_NAME));
						}
						else
						{
							sprintf (buffer, "E/%s", get_local_entity_string (target, STRING_TYPE_EASY_DISPLAY_NAME));
						}
					}
					else
					{
						sprintf (buffer, "%s", get_local_entity_string (target, STRING_TYPE_EASY_DISPLAY_NAME));
					}
				}

				target_name = buffer;
			}
			else
			{
				target_name = "NO TARGET";
			}

			break;
		}
		////////////////////////////////////////
		case CPG_ASSIST_TYPE_REAL:
		////////////////////////////////////////
		{
			if (large_display)
			{
				if (target)
				{
					if (eo_low_light)
					{
						target_name = "LOW LIGHT";
					}
					else
					{
						if (cpg_identify_target_delay > 0.0)
						{
							target_name = "CP/G IDENTIFYING...";
						}
						else
						{
							target_name = get_local_entity_string (target, STRING_TYPE_LONG_DISPLAY_NAME);
						}
					}
				}
			}
			else
			{
				if (target)
				{
					if (eo_low_light)
					{
						target_name = "LOW LIGHT";
					}
					else
					{
						if (cpg_identify_target_delay > 0.0)
						{
							target_name = "CP/G ID...";
						}
						else
						{
							target_name = get_local_entity_string (target, STRING_TYPE_SHORT_DISPLAY_NAME);
						}
					}
				}
			}

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			debug_fatal ("Invalid cpg assist type = %d", get_global_cpg_assist_type ());

			break;
		}
	}

	return (target_name);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// FUNCTIONS FOR HANDING OFF TARGETS (only tx mobiles to minimise data transfer)
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_number_of_valid_gunship_targets (entity *receiver)
{
	int
		count;

	float
		sqr_target_range;

	entity
		*target;

	vec3d
		*receiver_position,
		*target_position;

	ASSERT (receiver);

	count = 0;

	receiver_position = get_local_entity_vec3d_ptr (receiver, VEC3D_TYPE_POSITION);

	target = get_local_entity_first_child (get_gunship_entity (), LIST_TYPE_GUNSHIP_TARGET);

	while (target)
	{
		if (get_local_entity_int_value (target, INT_TYPE_IDENTIFY_MOBILE))
		{
			target_position = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

			sqr_target_range = get_sqr_3d_range (receiver_position, target_position);

			if (sqr_target_range < SQR_MAX_TARGET_RANGE)
			{
				count++;
			}
		}

		target = get_local_entity_child_succ (target, LIST_TYPE_GUNSHIP_TARGET);
	}

	return (count);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_valid_gunship_target_safe_index (entity *receiver, int depth)
{
	int
		count;

	float
		sqr_target_range;

	entity
		*target;

	vec3d
		*receiver_position,
		*target_position;

	ASSERT (receiver);

	ASSERT (depth >= 0);

	count = 0;

	receiver_position = get_local_entity_vec3d_ptr (receiver, VEC3D_TYPE_POSITION);

	target = get_local_entity_first_child (get_gunship_entity (), LIST_TYPE_GUNSHIP_TARGET);

	while (target)
	{
		if (get_local_entity_int_value (target, INT_TYPE_IDENTIFY_MOBILE))
		{
			target_position = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

			sqr_target_range = get_sqr_3d_range (receiver_position, target_position);

			if (sqr_target_range < SQR_MAX_TARGET_RANGE)
			{
				if (count == depth)
				{
				 	return (get_local_entity_safe_index (target));
				}

				count++;
			}
		}

		target = get_local_entity_child_succ (target, LIST_TYPE_GUNSHIP_TARGET);
	}

	debug_fatal ("Cannot find valid gunship target (count = %d, depth = %d)", count, depth);

	return (0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_valid_gunship_target_safe_index (int index)
{
	entity
		*target;

	target = get_local_entity_safe_ptr (index);

	ASSERT (target);

	if (target != get_gunship_entity ())
	{
		if (!get_local_entity_parent (target, LIST_TYPE_GUNSHIP_TARGET))
		{
			insert_local_entity_into_parents_child_list (target, LIST_TYPE_GUNSHIP_TARGET, get_gunship_entity (), NULL);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_simple_avionics_target_acquisition_system (void)
{
	switch (get_global_gunship_type ())
	{
		////////////////////////////////////////
		// JB 030313 Fly any aircraft
//		default:
		case GUNSHIP_TYPE_APACHE:
		////////////////////////////////////////
		{
			select_apache_target_acquisition_system (TARGET_ACQUISITION_SYSTEM_IHADSS);

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_HAVOC:
		////////////////////////////////////////
		{
			select_havoc_target_acquisition_system (TARGET_ACQUISITION_SYSTEM_HMS);

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_COMANCHE:
		////////////////////////////////////////
		{
			select_comanche_target_acquisition_system (TARGET_ACQUISITION_SYSTEM_HIDSS);

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_HOKUM:
		////////////////////////////////////////
		{
			select_hokum_target_acquisition_system (TARGET_ACQUISITION_SYSTEM_HMS);

			break;
		}
		////Moje 030519 Start
		case GUNSHIP_TYPE_BLACKHAWK:
		{
			select_blackhawk_target_acquisition_system (TARGET_ACQUISITION_SYSTEM_IHADSS);
			break;
		}
		////Moje 030519 End
		////Moje 030612 start
		////////////////////////////////////////
		case GUNSHIP_TYPE_HIND:
		////////////////////////////////////////
		{
			select_hind_target_acquisition_system (TARGET_ACQUISITION_SYSTEM_HMS);

			break;
		}
		////Moje 030612 end
		////Moje 030816 Start
		case GUNSHIP_TYPE_AH64A:
		{
			select_ah64a_target_acquisition_system (TARGET_ACQUISITION_SYSTEM_IHADSS);
			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_KA50:
		////////////////////////////////////////
		{
			select_ka50_target_acquisition_system (TARGET_ACQUISITION_SYSTEM_HMS);
			break;
		}
		////Moje 030816 end

		////////////////////////////////////////
		//  GCsDriver  08-12-2007
		default:
		////////////////////////////////////////
		{
			select_default_target_acquisition_system (TARGET_ACQUISITION_SYSTEM_IHADSS);

			break;
		}

	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void play_common_cpg_target_acquisition_system_speech (target_acquisition_systems new_system, target_acquisition_systems old_system, int damaged)
{
	switch (new_system)
	{
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_OFF:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_GROUND_RADAR:
		case TARGET_ACQUISITION_SYSTEM_AIR_RADAR:
		////////////////////////////////////////
		{
			if (damaged)
			{
				play_client_server_cpg_message (get_gunship_entity (), 0.5, 1.0, SPEECH_CATEGORY_CPG_SYSTEMS, 1.0, SPEECH_CPG_RADAR_DAMAGED);
			}
			else
			{
				if (!command_line_manual_laser_radar && (old_system != TARGET_ACQUISITION_SYSTEM_GROUND_RADAR) && (old_system != TARGET_ACQUISITION_SYSTEM_AIR_RADAR))
				{
					play_client_server_cpg_message (get_gunship_entity (), 0.5, 1.0, SPEECH_CATEGORY_CPG_SYSTEMS, 1.0, SPEECH_CPG_RADAR_ON);
				}
			}

			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_FLIR:
		////////////////////////////////////////
		{
			if (damaged)
			{
				play_client_server_cpg_message (get_gunship_entity (), 0.5, 1.0, SPEECH_CATEGORY_CPG_SYSTEMS, 1.0, SPEECH_CPG_FLIR_DAMAGED);
			}

			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_DTV:
		////////////////////////////////////////
		{
			if (damaged)
			{
				play_client_server_cpg_message (get_gunship_entity (), 0.5, 1.0, SPEECH_CATEGORY_CPG_SYSTEMS, 1.0, SPEECH_CPG_DTV_DAMAGED);
			}

			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_DVO:
		////////////////////////////////////////
		{
			if (damaged)
			{
				play_client_server_cpg_message (get_gunship_entity (), 0.5, 1.0, SPEECH_CATEGORY_CPG_SYSTEMS, 1.0, SPEECH_CPG_DVO_DAMAGED);
			}

			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_LLLTV:
		////////////////////////////////////////
		{
			if (damaged)
			{
				play_client_server_cpg_message (get_gunship_entity (), 0.5, 1.0, SPEECH_CATEGORY_CPG_SYSTEMS, 1.0, SPEECH_CPG_LLLTV_DAMAGED);
			}

			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_PERISCOPE:
		////////////////////////////////////////
		{
			if (damaged)
			{
				play_client_server_cpg_message (get_gunship_entity (), 0.5, 1.0, SPEECH_CATEGORY_CPG_SYSTEMS, 1.0, SPEECH_CPG_PERISCOPE_DAMAGED);
			}

			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_IHADSS:
		case TARGET_ACQUISITION_SYSTEM_HIDSS:
		case TARGET_ACQUISITION_SYSTEM_HMS:
		////////////////////////////////////////
		{
			if (damaged)
			{
				play_client_server_cpg_message (get_gunship_entity (), 0.5, 1.0, SPEECH_CATEGORY_CPG_SYSTEMS, 1.0, SPEECH_CPG_NEGATIVE);
			}

			break;
		}
	}

	if (!damaged)
	{
		if ((new_system != TARGET_ACQUISITION_SYSTEM_GROUND_RADAR) && (new_system != TARGET_ACQUISITION_SYSTEM_AIR_RADAR))
		{
			if (!command_line_manual_laser_radar && (old_system == TARGET_ACQUISITION_SYSTEM_GROUND_RADAR || old_system == TARGET_ACQUISITION_SYSTEM_AIR_RADAR))
			{
				play_client_server_cpg_message (get_gunship_entity (), 0.5, 1.0, SPEECH_CATEGORY_CPG_SYSTEMS, 1.0, SPEECH_CPG_RADAR_OFF);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// Jabberwock 031107 Designated targets

void toggle_designated_target (void)
{
	entity
		*current_target;
	
	current_target = get_local_entity_parent (get_gunship_entity (), LIST_TYPE_TARGET);
	
	if (command_line_designated_targets)
	{
		if (current_target)
		{	
			if (get_local_entity_parent (current_target, LIST_TYPE_DESIGNATED_TARGET))
			{
				delete_local_entity_from_parents_child_list (current_target, LIST_TYPE_DESIGNATED_TARGET);
			}
			else
			{
				insert_local_entity_into_parents_child_list (current_target, LIST_TYPE_DESIGNATED_TARGET, get_gunship_entity (), NULL);
			}
		}
	}
}

// Jabberwock 031107 ends

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

rangefinding_system get_range_finder(void)
{
	if (target_acquisition_system == TARGET_ACQUISITION_SYSTEM_GROUND_RADAR
		|| target_acquisition_system == TARGET_ACQUISITION_SYSTEM_AIR_RADAR)
	{
		return RANGEFINDER_FCR;	
	}
	else if (laser_is_active())
		return RANGEFINDER_LASER;

	return RANGEFINDER_TRIANGULATION;
}

float get_target_range(vec3d* target_position, rangefinding_system* rf_system)
{
	rangefinding_system system = get_range_finder();
	vec3d* source_position = get_local_entity_vec3d_ptr (get_gunship_entity(), VEC3D_TYPE_POSITION);

	if (!target_position)
		return 0.0;

	if (rf_system)
		*rf_system = system;

	if (get_range_finder() != RANGEFINDER_TRIANGULATION)
		return get_3d_range(source_position, target_position);
	else
		return get_triangulated_by_position_range(source_position, target_position);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void cpg_report_target(entity* target)
{
	switch (get_local_entity_int_value (target, INT_TYPE_THREAT_TYPE))
	{
		////////////////////////////////////////
		case THREAT_TYPE_INVALID:
		case THREAT_TYPE_RF_MISSILE:
		case THREAT_TYPE_IR_MISSILE:
		case THREAT_TYPE_LASER_MISSILE:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case THREAT_TYPE_AIRBORNE_RADAR:
		////////////////////////////////////////
		{
				if (get_local_entity_int_value (target, INT_TYPE_IDENTIFY_HELICOPTER))
				{
					play_client_server_cpg_contact_message
					(
						get_gunship_entity (),
						SPEECH_CPG_CHOPPERS,
						get_speech_heading_type (get_gunship_entity (), target),
						get_speech_distance_type (get_gunship_entity (), target)
					);
				}
				else if (get_local_entity_int_value (target, INT_TYPE_IDENTIFY_FIXED_WING))
				{
					play_client_server_cpg_contact_message
					(
						get_gunship_entity (),
						SPEECH_CPG_FAST_MOVERS,
						get_speech_heading_type (get_gunship_entity (), target),
						get_speech_distance_type (get_gunship_entity (), target)
					);
				}

			break;
		}
		////////////////////////////////////////
		case THREAT_TYPE_SAM:
		////////////////////////////////////////
		{
				if (get_local_entity_int_value (target, INT_TYPE_IDENTIFY_SHIP_VEHICLE))
				{
					play_client_server_cpg_contact_message
					(
						get_gunship_entity (),
						SPEECH_CPG_WARSHIPS,
						get_speech_heading_type (get_gunship_entity (), target),
						get_speech_distance_type (get_gunship_entity (), target)
					);
				}
				else
				{
					play_client_server_cpg_contact_message
					(
						get_gunship_entity (),
						SPEECH_CPG_SAM,
						get_speech_heading_type (get_gunship_entity (), target),
						get_speech_distance_type (get_gunship_entity (), target)
					);
				}

			break;
		}
		////////////////////////////////////////
		case THREAT_TYPE_AAA:
		////////////////////////////////////////
		{
				if (get_local_entity_int_value (target, INT_TYPE_IDENTIFY_SHIP_VEHICLE))
				{
					play_client_server_cpg_contact_message
					(
						get_gunship_entity (),
						SPEECH_CPG_WARSHIPS,
						get_speech_heading_type (get_gunship_entity (), target),
						get_speech_distance_type (get_gunship_entity (), target)
					);
				}
				else
				{
					play_client_server_cpg_contact_message
					(
						get_gunship_entity (),
						SPEECH_CPG_TRIPLE_A,
						get_speech_heading_type (get_gunship_entity (), target),
						get_speech_distance_type (get_gunship_entity (), target)
					);
				}

			break;
		}
		////////////////////////////////////////
		case THREAT_TYPE_EARLY_WARNING_RADAR:
		////////////////////////////////////////
		{
			break;
		}
	}
}
