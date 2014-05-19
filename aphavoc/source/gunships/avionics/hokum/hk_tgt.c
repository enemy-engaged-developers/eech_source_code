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

#define DEBUG_MODULE	0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_hokum_target_acquisition_systems (void)
{
	initialise_hokum_radar ();

	initialise_hokum_eo ();

	initialise_hokum_hms ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_hokum_target_acquisition_systems (void)
{
	deinitialise_hokum_radar ();

	deinitialise_hokum_eo ();

	deinitialise_hokum_hms ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void deselect_hokum_target_acquisition_system (target_acquisition_systems system)
{
	switch (system)
	{
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_OFF:
		////////////////////////////////////////
		{
			// laser is on in all modes but OFF in automatic mode
			if (!command_line_manual_laser_radar)
				set_laser_is_active(TRUE);

			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_GROUND_RADAR:
		////////////////////////////////////////
		{
			if (!command_line_manual_laser_radar)
				deactivate_common_ground_radar ();

			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_AIR_RADAR:
		////////////////////////////////////////
		{
			if (!command_line_manual_laser_radar)
				deactivate_common_air_radar ();

			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_FLIR:
		////////////////////////////////////////
		{
			deactivate_common_eo ();
#ifdef OLD_EO
			copy_eo_zoom(&hokum_flir, &hokum_llltv);
			copy_eo_zoom(&hokum_flir, &hokum_periscope);
#endif

			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_LLLTV:
		////////////////////////////////////////
		{
			deactivate_common_eo ();
#ifdef OLD_EO
			copy_eo_zoom(&hokum_llltv, &hokum_flir);
			copy_eo_zoom(&hokum_llltv, &hokum_periscope);
#endif

			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_PERISCOPE:
		////////////////////////////////////////
		{
			deactivate_common_eo ();
#ifdef OLD_EO
			copy_eo_zoom(&hokum_periscope, &hokum_flir);
			copy_eo_zoom(&hokum_periscope, &hokum_llltv);
#endif

			if (get_view_mode () == VIEW_MODE_VIRTUAL_COCKPIT_PERISCOPE)
			{
				// start autoreturn to pilot by GCsDriver  08-12-2007					
				if(command_line_autoreturn_to_pilot_after_periscope){
					set_pilot_seat_position ();
				}
				// end autoreturn to pilot by GCsDriver	 08-12-2007				

				set_view_mode (VIEW_MODE_VIRTUAL_COCKPIT);
			}

			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_HMS:
		////////////////////////////////////////
		{
			deactivate_common_hms ();

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			debug_fatal ("Invalid target acquisition system = %d", system);

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_hokum_target_acquisition_system (target_acquisition_systems system)
{
	target_acquisition_systems
		new_system,
		old_system;

	int
		damaged;

	new_system = system;
	old_system = target_acquisition_system;

	damaged = FALSE;

	reset_common_target_acquisition_system_keys ();

	if (eo_is_tracking_point())
		eo_stop_tracking();
			
	deselect_hokum_target_acquisition_system (target_acquisition_system);

	switch (system)
	{
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_OFF:
		////////////////////////////////////////
		{
			target_acquisition_system = system;

			set_gunship_target (NULL);

			if (!command_line_manual_laser_radar)
				set_laser_is_active(FALSE);

			#if 0

			hud_mode = HUD_MODE_NAVIGATION;

			#endif

			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_GROUND_RADAR:
		////////////////////////////////////////
		{
			if (!hokum_damage.radar)
			{
				target_acquisition_system = system;

				deactivate_common_air_radar();
				if (!command_line_manual_laser_radar)
					activate_common_ground_radar ();

				if (command_line_targeting_system_auto_page)
					select_hokum_ground_radar_mfd ();

				hud_mode = HUD_MODE_WEAPON;
			}

			damaged = hokum_damage.radar;

			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_AIR_RADAR:
		////////////////////////////////////////
		{
			if (!hokum_damage.radar)
			{
				target_acquisition_system = system;

				deactivate_common_ground_radar();
				if (!command_line_manual_laser_radar)
					activate_common_air_radar ();

				if (command_line_targeting_system_auto_page)
					select_hokum_air_radar_mfd ();

				hud_mode = HUD_MODE_WEAPON;
			}

			damaged = hokum_damage.radar;

			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_FLIR:
		////////////////////////////////////////
		{
			if (!hokum_damage.flir)
			{
				target_acquisition_system = system;

				activate_common_eo ();

				if (command_line_targeting_system_auto_page)
					select_hokum_eo_mfd ();

				hud_mode = HUD_MODE_WEAPON;
			}

			damaged = hokum_damage.flir;

			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_LLLTV:
		////////////////////////////////////////
		{
			if (!hokum_damage.llltv)
			{
				target_acquisition_system = system;

				activate_common_eo ();

				if (command_line_targeting_system_auto_page)
					select_hokum_eo_mfd ();

				hud_mode = HUD_MODE_WEAPON;
			}

			damaged = hokum_damage.llltv;

			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_PERISCOPE:
		////////////////////////////////////////
		{
			if (!hokum_damage.periscope)
			{
				target_acquisition_system = system;

				activate_common_eo ();

	 			if (get_crew_role () == CREW_ROLE_PILOT)
				{
					// stay as pilot by GCsDriver  08-12-2007
					if(command_line_pilot_as_periscope_default){
					}else{
						set_co_pilot_seat_position ();
					}
					// stay as pilot by GCsDriver  08-12-2007
				}

				if (get_crew_role () == CREW_ROLE_CO_PILOT)
				{
					set_view_mode (VIEW_MODE_VIRTUAL_COCKPIT_PERISCOPE);
				}

				if (command_line_targeting_system_auto_page)
					select_hokum_eo_mfd ();

				hud_mode = HUD_MODE_WEAPON;
			}

			damaged = hokum_damage.periscope;

			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_HMS:
		////////////////////////////////////////
		{
			if (!hokum_damage.helmet_mounted_sight)
			{
				target_acquisition_system = system;

				activate_common_hms ();

				hud_mode = HUD_MODE_WEAPON;
			}

			damaged = hokum_damage.helmet_mounted_sight;

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			debug_fatal ("Invalid target acquisition system = %d", system);

			break;
		}
	}

	play_common_cpg_target_acquisition_system_speech (new_system, old_system, damaged);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_hokum_target_acquisition_system (void)
{
	if (hokum_damage.helmet_mounted_sight)
	{
		if (hud_mode == HUD_MODE_WEAPON)
		{
			hud_mode = HUD_MODE_NAVIGATION;
		}
	}

	if (ground_radar_is_active())
		update_common_ground_radar(FALSE);
	else if (air_radar_is_active())
		update_common_air_radar();

	switch (target_acquisition_system)
	{
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_OFF:
		////////////////////////////////////////
		{
			target_locked = FALSE;

			update_weapon_lock_type (TARGET_ACQUISITION_SYSTEM_OFF);

			slave_common_eo_to_current_target ();

			slave_hokum_eo_to_current_target ();

			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_GROUND_RADAR:
		////////////////////////////////////////
		{
			update_hokum_ground_radar ();

			update_weapon_lock_type (TARGET_ACQUISITION_SYSTEM_GROUND_RADAR);

			slave_common_eo_to_current_target ();

			slave_hokum_eo_to_current_target ();

			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_AIR_RADAR:
		////////////////////////////////////////
		{
			update_hokum_air_radar ();

			update_weapon_lock_type (TARGET_ACQUISITION_SYSTEM_AIR_RADAR);

			slave_common_eo_to_current_target ();

			slave_hokum_eo_to_current_target ();

			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_FLIR:
		////////////////////////////////////////
		{
			update_hokum_eo (&hokum_flir);

			update_common_eo ();

			update_weapon_lock_type (TARGET_ACQUISITION_SYSTEM_FLIR);

			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_LLLTV:
		////////////////////////////////////////
		{
			update_hokum_eo (&hokum_llltv);

			update_common_eo ();

			update_weapon_lock_type (TARGET_ACQUISITION_SYSTEM_LLLTV);

			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_PERISCOPE:
		////////////////////////////////////////
		{
			update_hokum_eo (&hokum_periscope);

			update_common_eo ();

			update_weapon_lock_type (TARGET_ACQUISITION_SYSTEM_PERISCOPE);

			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_HMS:
		////////////////////////////////////////
		{
			update_hokum_hms ();

			update_common_hms ();

			update_weapon_lock_type (TARGET_ACQUISITION_SYSTEM_HMS);

			slave_common_eo_to_current_target ();

			slave_hokum_eo_to_current_target ();

			break;
		}
	}

	////////////////////////////////////////
	//
	// radar / laser / los to target
	//
	////////////////////////////////////////

	{
		entity
			*source,
			*target;

		int
			radar_on,
			laser_on,
			los_to_target;

		source = get_gunship_entity ();

		target = get_local_entity_parent (source, LIST_TYPE_TARGET);

		//
		// radar on/off
		//

		radar_on = FALSE;

		if (ground_radar_is_active() && ground_radar.sweep_mode != RADAR_SWEEP_MODE_SINGLE_INACTIVE)
			radar_on = TRUE;

		else if (air_radar_is_active() && air_radar.sweep_mode != RADAR_SWEEP_MODE_SINGLE_INACTIVE)
			radar_on = TRUE;

		if (radar_on != get_local_entity_int_value (source, INT_TYPE_RADAR_ON))
			set_client_server_entity_int_value (source, INT_TYPE_RADAR_ON, radar_on);

		//
		// laser on/off
		//

		laser_on = laser_is_active() && !comanche_damage.laser_designator;

		if (laser_on != get_local_entity_int_value (source, INT_TYPE_LASER_ON))
		{
			set_client_server_entity_int_value (source, INT_TYPE_LASER_ON, laser_on);
		}


		//
		// line of sight to target
		//

		if (target)
		{
			switch (target_acquisition_system)
			{
				case TARGET_ACQUISITION_SYSTEM_OFF:
				{
					los_to_target = FALSE;

					break;
				}
				case TARGET_ACQUISITION_SYSTEM_GROUND_RADAR:
				case TARGET_ACQUISITION_SYSTEM_AIR_RADAR:
				{
					los_to_target = get_local_entity_int_value (target, INT_TYPE_GUNSHIP_RADAR_LOS_CLEAR);

					break;
				}
				case TARGET_ACQUISITION_SYSTEM_FLIR:
				case TARGET_ACQUISITION_SYSTEM_LLLTV:
				case TARGET_ACQUISITION_SYSTEM_PERISCOPE:
				{
					los_to_target = TRUE;

					break;
				}
				case TARGET_ACQUISITION_SYSTEM_HMS:
				{
					los_to_target = TRUE;

					break;
				}
			}
		}
		else
		{
			los_to_target = FALSE;
		}

		if (los_to_target != get_local_entity_int_value (source, INT_TYPE_LOS_TO_TARGET))
		{
			set_client_server_entity_int_value (source, INT_TYPE_LOS_TO_TARGET, los_to_target);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void centre_hokum_target_acquisition_system (void)
{
	switch (target_acquisition_system)
	{
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_OFF:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_GROUND_RADAR:
		////////////////////////////////////////
		{
			centre_hokum_ground_radar ();

			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_AIR_RADAR:
		////////////////////////////////////////
		{
			centre_hokum_air_radar ();

			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_FLIR:
		////////////////////////////////////////
		{
			centre_hokum_eo ();

			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_LLLTV:
		////////////////////////////////////////
		{
			centre_hokum_eo ();

			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_PERISCOPE:
		////////////////////////////////////////
		{
			centre_hokum_eo ();

			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_HMS:
		////////////////////////////////////////
		{
			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void toggle_hokum_show_allied_targets (void)
{
	switch (target_acquisition_system)
	{
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_OFF:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_GROUND_RADAR:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_AIR_RADAR:
		////////////////////////////////////////
		{
			air_radar.show_allied_targets ^= 1;

			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_FLIR:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_LLLTV:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_PERISCOPE:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_HMS:
		////////////////////////////////////////
		{
			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void toggle_hokum_auto_target (void)
{
	switch (target_acquisition_system)
	{
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_OFF:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_GROUND_RADAR:
		////////////////////////////////////////
		{
			ground_radar.auto_target ^= 1;

			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_AIR_RADAR:
		////////////////////////////////////////
		{
			air_radar.auto_target ^= 1;

			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_FLIR:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_LLLTV:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_PERISCOPE:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_HMS:
		////////////////////////////////////////
		{
			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void toggle_hokum_lock_target (void)
{
	switch (target_acquisition_system)
	{
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_OFF:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_GROUND_RADAR:
		////////////////////////////////////////
		{
			ground_radar.target_locked ^= 1;

			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_AIR_RADAR:
		////////////////////////////////////////
		{
			air_radar.target_locked ^= 1;

			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_FLIR:
		case TARGET_ACQUISITION_SYSTEM_LLLTV:
		case TARGET_ACQUISITION_SYSTEM_PERISCOPE:
		////////////////////////////////////////
		{
			toggle_eo_lock();

			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_HMS:
		////////////////////////////////////////
		{
			hms_target_locked ^= 1;

			if (hms_target_locked)
			{
				if (in_cockpit && !query_TIR_active())
				{
					set_view_mode (VIEW_MODE_VIRTUAL_COCKPIT_TRACK_TARGET);
				}
			}
			else
			{
				if (get_view_mode () == VIEW_MODE_VIRTUAL_COCKPIT_TRACK_TARGET)
				{
					select_padlock_view_event (PADLOCK_MODE_NONE);
				}
			}

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_hokum_lock_target (int lock)
{
	switch (target_acquisition_system)
	{
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_OFF:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_GROUND_RADAR:
		////////////////////////////////////////
		{
			ground_radar.target_locked = lock;

			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_AIR_RADAR:
		////////////////////////////////////////
		{
			air_radar.target_locked = lock;

			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_FLIR:
		case TARGET_ACQUISITION_SYSTEM_LLLTV:
		case TARGET_ACQUISITION_SYSTEM_PERISCOPE:
		////////////////////////////////////////
		{
			set_eo_lock(lock);

			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_HMS:
		////////////////////////////////////////
		{
			hms_target_locked = lock;

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void hokum_target_acquisition_system_misc_function1 (void)
{
	switch (target_acquisition_system)
	{
		case TARGET_ACQUISITION_SYSTEM_OFF:
		case TARGET_ACQUISITION_SYSTEM_GROUND_RADAR:
		case TARGET_ACQUISITION_SYSTEM_FLIR:
		case TARGET_ACQUISITION_SYSTEM_DTV:
		case TARGET_ACQUISITION_SYSTEM_DVO:
		case TARGET_ACQUISITION_SYSTEM_HMS:
		{
			if (hokum_damage.radar)
			{
				set_ground_radar_is_active(FALSE);
				set_air_radar_is_active(FALSE);
			}
			else if (ground_radar.sweep_mode == RADAR_SWEEP_MODE_CONTINUOUS)
			{
				if (ground_radar_is_active())
					ground_radar.sweep_mode = RADAR_SWEEP_MODE_SINGLE_ACTIVE;
				else
					ground_radar.sweep_mode = RADAR_SWEEP_MODE_SINGLE_INACTIVE;
			}
			else
			{
				set_ground_radar_is_active(ground_radar.sweep_mode == RADAR_SWEEP_MODE_SINGLE_ACTIVE);
				
				ground_radar.sweep_mode = RADAR_SWEEP_MODE_CONTINUOUS;
			}

			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_AIR_RADAR:
		////////////////////////////////////////
		{
			if (hokum_damage.radar)
			{
				set_ground_radar_is_active(FALSE);
				set_air_radar_is_active(FALSE);
			}
			else if (air_radar.sweep_mode == RADAR_SWEEP_MODE_CONTINUOUS)
			{
				if (air_radar_is_active())
					air_radar.sweep_mode = RADAR_SWEEP_MODE_SINGLE_ACTIVE;
				else
					air_radar.sweep_mode = RADAR_SWEEP_MODE_SINGLE_INACTIVE;
			}
			else
			{
				set_air_radar_is_active(air_radar.sweep_mode == RADAR_SWEEP_MODE_SINGLE_ACTIVE);
				
				air_radar.sweep_mode = RADAR_SWEEP_MODE_CONTINUOUS;
			}

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void hokum_target_acquisition_system_misc_function2 (void)
{
	switch (target_acquisition_system)
	{
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_OFF:
		case TARGET_ACQUISITION_SYSTEM_GROUND_RADAR:
		case TARGET_ACQUISITION_SYSTEM_FLIR:
		case TARGET_ACQUISITION_SYSTEM_DTV:
		case TARGET_ACQUISITION_SYSTEM_DVO:
		case TARGET_ACQUISITION_SYSTEM_HMS:
		////////////////////////////////////////
		{
			if (ground_radar.sweep_mode == RADAR_SWEEP_MODE_SINGLE_INACTIVE)
			{
				if (!hokum_damage.radar)
				{
					ground_radar.sweep_mode = RADAR_SWEEP_MODE_SINGLE_ACTIVE;
					set_ground_radar_is_active(TRUE);
				}
			}
			else if (ground_radar.sweep_mode == RADAR_SWEEP_MODE_SINGLE_ACTIVE)
			{
				ground_radar.sweep_mode = RADAR_SWEEP_MODE_SINGLE_INACTIVE;
				set_ground_radar_is_active(FALSE);
			}
			else if (!hokum_damage.radar)
				toggle_ground_radar_active();

			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_AIR_RADAR:
		////////////////////////////////////////
		{
			if (air_radar.sweep_mode == RADAR_SWEEP_MODE_SINGLE_INACTIVE)
			{
				if (!hokum_damage.radar)
				{
					air_radar.sweep_mode = RADAR_SWEEP_MODE_SINGLE_ACTIVE;
					set_air_radar_is_active(TRUE);
				}
			}
			else if (air_radar.sweep_mode == RADAR_SWEEP_MODE_SINGLE_ACTIVE)
			{
				air_radar.sweep_mode = RADAR_SWEEP_MODE_SINGLE_INACTIVE;
				set_air_radar_is_active(FALSE);
			}
			else if (!hokum_damage.radar)
				toggle_air_radar_active();

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
