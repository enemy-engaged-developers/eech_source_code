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

static int
	initialised = FALSE;

static gunship_types
	gunship_type;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_avionics (void)
{
	ASSERT (!initialised);

	if (!get_gunship_entity ())
	{
		return;
	}

	initialised = TRUE;

	gunship_type = get_global_gunship_type ();

	switch (gunship_type)
	{
		////////////////////////////////////////
		// JB 030313 Fly any aircraft
//		default:
		case GUNSHIP_TYPE_APACHE:
		////////////////////////////////////////
		{
			load_gunship_avionics_damage ();

			initialise_common_hud ();

			initialise_common_mfd ();

			initialise_common_weapon_systems ();

			initialise_common_target_acquisition_systems ();

			initialise_common_night_vision_system ();

			initialise_apache_hud ();

			initialise_apache_mfd ();

			initialise_apache_weapon_systems ();

			initialise_apache_upfront_display ();

			initialise_apache_target_acquisition_systems ();

			initialise_apache_lamp_avionics ();

			initialise_apache_threat_warning_system ();

			//
			// push events after avionics have been initialised
			//

			push_event_overlay (set_common_avionics_events, "common avionics events");

			push_event_overlay (set_apache_avionics_events, "apache avionics events");

			push_event_overlay (set_gunship_view_mode_events, "gunship view mode events");

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_HAVOC:
		////////////////////////////////////////
		{
			load_gunship_avionics_damage ();

			initialise_common_hud ();

			initialise_common_mfd ();

			initialise_common_weapon_systems ();

			initialise_common_target_acquisition_systems ();

			initialise_common_night_vision_system ();

			initialise_havoc_hud ();

			initialise_havoc_mfd ();

			initialise_havoc_ekran_display ();

			initialise_havoc_target_acquisition_systems ();

			initialise_havoc_lamp_avionics ();

			initialise_havoc_threat_warning_system ();

#if 0
			// Casm 10SEP05 Havoc Instruments
 			initialise_havoc_instruments ();
#endif

			//
			// push events after avionics have been initialised
			//

			push_event_overlay (set_common_avionics_events, "common avionics events");

			push_event_overlay (set_havoc_avionics_events, "havoc avionics events");

			push_event_overlay (set_gunship_view_mode_events, "gunship view mode events");

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_COMANCHE:
		////////////////////////////////////////
		{
			load_gunship_avionics_damage ();

			initialise_common_hud ();

			initialise_common_mfd ();

			initialise_common_weapon_systems ();

			initialise_common_target_acquisition_systems ();

			initialise_common_night_vision_system ();

			initialise_comanche_hud ();

			initialise_comanche_mfd ();

			initialise_comanche_weapon_systems ();

			initialise_comanche_target_acquisition_systems ();

			initialise_comanche_lamp_avionics ();

			initialise_comanche_threat_warning_system ();

			//
			// push events after avionics have been initialised
			//

			push_event_overlay (set_common_avionics_events, "common avionics events");

			push_event_overlay (set_comanche_avionics_events, "comanche avionics events");

			push_event_overlay (set_gunship_view_mode_events, "gunship view mode events");

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_HOKUM:
		////////////////////////////////////////
		{
			load_gunship_avionics_damage ();

			initialise_common_hud ();

			initialise_common_mfd ();

			initialise_common_weapon_systems ();

			initialise_common_target_acquisition_systems ();

			initialise_common_night_vision_system ();

			initialise_hokum_hud ();

			initialise_hokum_mfd ();

			initialise_hokum_target_acquisition_systems ();

			initialise_hokum_lamp_avionics ();

			initialise_hokum_threat_warning_system ();

			//
			// push events after avionics have been initialised
			//

			push_event_overlay (set_common_avionics_events, "common avionics events");

			push_event_overlay (set_hokum_avionics_events, "hokum avionics events");

			push_event_overlay (set_gunship_view_mode_events, "gunship view mode events");

			break;
		}
		////////////////////////////////////////
		//////Moje 030517 Whole case inserted 3 times Start 1st time
		case GUNSHIP_TYPE_BLACKHAWK:
		////////////////////////////////////////
		{
			load_gunship_avionics_damage ();

			initialise_common_hud ();

			initialise_common_mfd ();

			initialise_common_weapon_systems ();

			initialise_common_target_acquisition_systems ();

			initialise_common_night_vision_system ();

			initialise_blackhawk_hud ();

			initialise_blackhawk_mfd ();

			initialise_blackhawk_weapon_systems ();

			initialise_blackhawk_upfront_display ();

			initialise_blackhawk_target_acquisition_systems ();

			initialise_blackhawk_lamp_avionics ();

			initialise_blackhawk_threat_warning_system ();

			//
			// push events after avionics have been initialised
			//

			push_event_overlay (set_common_avionics_events, "common avionics events");

			push_event_overlay (set_blackhawk_avionics_events, "blackhawk avionics events");

			push_event_overlay (set_gunship_view_mode_events, "gunship view mode events");

			break;
		}
		////Moje 030517 End of insertion 1
		////Moje 030612 start
		////////////////////////////////////////
		case GUNSHIP_TYPE_HIND:
		////////////////////////////////////////
		{
			load_gunship_avionics_damage ();

			initialise_common_hud ();

			initialise_common_mfd ();

			initialise_common_weapon_systems ();

			initialise_common_target_acquisition_systems ();

			initialise_common_night_vision_system ();

			initialise_hind_hud ();

			initialise_hind_mfd ();

			initialise_hind_ekran_display ();

			initialise_hind_target_acquisition_systems ();

			initialise_hind_lamp_avionics ();

			initialise_hind_threat_warning_system ();

			//
			// push events after avionics have been initialised
			//

			push_event_overlay (set_common_avionics_events, "common avionics events");

			push_event_overlay (set_hind_avionics_events, "hind avionics events");

			push_event_overlay (set_gunship_view_mode_events, "gunship view mode events");

			break;
		}
		////Moje 030612 end
		////Moje 030815 Start
		case GUNSHIP_TYPE_AH64A:
		////////////////////////////////////////
		{
			load_gunship_avionics_damage ();

			initialise_common_hud ();

			initialise_common_mfd ();

			initialise_common_weapon_systems ();

			initialise_common_target_acquisition_systems ();

			initialise_common_night_vision_system ();

			initialise_ah64a_hud ();

			initialise_ah64a_mfd ();

			initialise_ah64a_weapon_systems ();

			initialise_ah64a_upfront_display ();

			initialise_ah64a_target_acquisition_systems ();

			initialise_ah64a_lamp_avionics ();

			initialise_ah64a_threat_warning_system ();

			//
			// push events after avionics have been initialised
			//

			push_event_overlay (set_common_avionics_events, "common avionics events");

			push_event_overlay (set_ah64a_avionics_events, "ah64a avionics events");

			push_event_overlay (set_gunship_view_mode_events, "gunship view mode events");

			break;
		}
		case GUNSHIP_TYPE_KA50:
		////////////////////////////////////////
		{
			load_gunship_avionics_damage ();

			initialise_common_hud ();

			initialise_common_mfd ();

			initialise_common_weapon_systems ();

			initialise_common_target_acquisition_systems ();

			initialise_common_night_vision_system ();

			initialise_ka50_hud ();

			initialise_ka50_mfd ();

			initialise_ka50_target_acquisition_systems ();

			initialise_ka50_lamp_avionics ();

			initialise_ka50_threat_warning_system ();

			//
			// push events after avionics have been initialised
			//

			push_event_overlay (set_common_avionics_events, "common avionics events");

			push_event_overlay (set_ka50_avionics_events, "ka50 avionics events");

			push_event_overlay (set_gunship_view_mode_events, "gunship view mode events");

			break;
		}
		////Moje 030815 End

		////////////////////////////////////////
		case GUNSHIP_TYPE_VIPER:
		////////////////////////////////////////
		{
			load_gunship_avionics_damage ();

			initialise_common_hud ();

			initialise_common_mfd ();

			initialise_common_weapon_systems ();

			initialise_common_target_acquisition_systems ();

			initialise_common_night_vision_system ();

			initialise_viper_hud ();

			initialise_viper_mfd ();

			initialise_viper_weapon_systems ();

			initialise_viper_target_acquisition_systems ();

			initialise_viper_lamp_avionics ();

			initialise_viper_threat_warning_system ();

			//
			// push events after avionics have been initialised
			//

			push_event_overlay (set_common_avionics_events, "common avionics events");

			push_event_overlay (set_viper_avionics_events, "viper avionics events");

			push_event_overlay (set_gunship_view_mode_events, "gunship view mode events");

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_KIOWA:
		////////////////////////////////////////
		{
			load_gunship_avionics_damage ();

			initialise_common_hud ();

			initialise_common_mfd ();

			initialise_common_weapon_systems ();

			initialise_common_target_acquisition_systems ();

			initialise_common_night_vision_system ();

			initialise_kiowa_hud ();

			initialise_kiowa_mfd ();

			initialise_kiowa_weapon_systems ();

			initialise_kiowa_target_acquisition_systems ();

			initialise_kiowa_lamp_avionics ();

			initialise_kiowa_threat_warning_system ();

			//
			// push events after avionics have been initialised
			//

			push_event_overlay (set_common_avionics_events, "common avionics events");

			push_event_overlay (set_kiowa_avionics_events, "kiowa avionics events");

			push_event_overlay (set_gunship_view_mode_events, "gunship view mode events");

			break;
		}
		////////////////////////////////////////
		// GCsDriver  08-12-2007
		default:
		////////////////////////////////////////
		{
			load_gunship_avionics_damage ();

			initialise_common_hud ();

			initialise_common_mfd ();

			initialise_common_weapon_systems ();

			initialise_common_target_acquisition_systems ();

			initialise_common_night_vision_system ();

			initialise_default_hud ();

			initialise_default_mfd ();

			initialise_default_weapon_systems ();

			initialise_default_upfront_display ();

			initialise_default_target_acquisition_systems ();

			initialise_default_lamp_avionics ();

			initialise_default_threat_warning_system ();

			//
			// push events after avionics have been initialised
			//

			push_event_overlay (set_common_avionics_events, "common avionics events");

			push_event_overlay (set_default_avionics_events, "default avionics events");

			push_event_overlay (set_gunship_view_mode_events, "gunship view mode events");

			break;
		}

	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_avionics (void)
{
	if (!initialised)
	{
		return;
	}

	initialised = FALSE;

	switch (gunship_type)
	{
		////////////////////////////////////////
		// JB 030313 Fly any aircraft
//		default:
		case GUNSHIP_TYPE_APACHE:
		////////////////////////////////////////
		{
			//
			// pop 'overlaid' target acquisition events first
			//

			deinitialise_common_target_acquisition_systems ();

			//
			// pop events before avionics are de-initialised
			//

			pop_event (set_gunship_view_mode_events);

			pop_event (set_apache_avionics_events);

			pop_event (set_common_avionics_events);

			save_gunship_avionics_damage (gunship_type);

			deinitialise_common_hud ();

			deinitialise_common_mfd ();

			deinitialise_common_weapon_systems ();

			deinitialise_common_night_vision_system ();

			deinitialise_apache_hud ();

			deinitialise_apache_mfd ();

			deinitialise_apache_upfront_display ();

			deinitialise_apache_target_acquisition_systems ();

			deinitialise_apache_lamp_avionics ();

			deinitialise_apache_threat_warning_system ();

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_HAVOC:
		////////////////////////////////////////
		{
			//
			// pop 'overlaid' target acquisition events first
			//

			deinitialise_common_target_acquisition_systems ();

			//
			// pop events before avionics are de-initialised
			//

			pop_event (set_gunship_view_mode_events);

			pop_event (set_havoc_avionics_events);

			pop_event (set_common_avionics_events);

			save_gunship_avionics_damage (gunship_type);

			deinitialise_common_hud ();

			deinitialise_common_mfd ();

			deinitialise_common_weapon_systems ();

			deinitialise_common_night_vision_system ();

			deinitialise_havoc_hud ();

			deinitialise_havoc_mfd ();

			deinitialise_havoc_ekran_display ();

			deinitialise_havoc_target_acquisition_systems ();

			deinitialise_havoc_lamp_avionics ();

			deinitialise_havoc_threat_warning_system ();

#if 0
			// Casm 10SEP05 Havoc Instruments
 			deinitialise_havoc_instruments ();
#endif

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_COMANCHE:
		////////////////////////////////////////
		{
			//
			// pop 'overlaid' target acquisition events first
			//

			deinitialise_common_target_acquisition_systems ();

			//
			// pop events before avionics are de-initialised
			//

			pop_event (set_gunship_view_mode_events);

			pop_event (set_comanche_avionics_events);

			pop_event (set_common_avionics_events);

			save_gunship_avionics_damage (gunship_type);

			deinitialise_common_hud ();

			deinitialise_common_mfd ();

			deinitialise_common_weapon_systems ();

			deinitialise_common_night_vision_system ();

			deinitialise_comanche_hud ();

			deinitialise_comanche_mfd ();

			deinitialise_comanche_target_acquisition_systems ();

			deinitialise_comanche_lamp_avionics ();

			deinitialise_comanche_threat_warning_system ();

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_HOKUM:
		////////////////////////////////////////
		{
			//
			// pop 'overlaid' target acquisition events first
			//

			deinitialise_common_target_acquisition_systems ();

			//
			// pop events before avionics are de-initialised
			//

			pop_event (set_gunship_view_mode_events);

			pop_event (set_hokum_avionics_events);

			pop_event (set_common_avionics_events);

			save_gunship_avionics_damage (gunship_type);

			deinitialise_common_hud ();

			deinitialise_common_mfd ();

			deinitialise_common_weapon_systems ();

			deinitialise_common_night_vision_system ();

			deinitialise_hokum_hud ();

			deinitialise_hokum_mfd ();

			deinitialise_hokum_target_acquisition_systems ();

			deinitialise_hokum_lamp_avionics ();

			deinitialise_hokum_threat_warning_system ();

			break;
		}
		////////////////////////////////////////
		//// Moje 030517 start insertion 2
		case GUNSHIP_TYPE_BLACKHAWK:
		////////////////////////////////////////
		{
			//
			// pop 'overlaid' target acquisition events first
			//

			deinitialise_common_target_acquisition_systems ();

			//
			// pop events before avionics are de-initialised
			//

			pop_event (set_gunship_view_mode_events);

			pop_event (set_blackhawk_avionics_events);

			pop_event (set_common_avionics_events);

			save_gunship_avionics_damage (gunship_type);

			deinitialise_common_hud ();

			deinitialise_common_mfd ();

			deinitialise_common_weapon_systems ();

			deinitialise_common_night_vision_system ();

			deinitialise_blackhawk_hud ();

			deinitialise_blackhawk_mfd ();

			deinitialise_blackhawk_upfront_display ();

			deinitialise_blackhawk_target_acquisition_systems ();

			deinitialise_blackhawk_lamp_avionics ();

			deinitialise_blackhawk_threat_warning_system ();

			break;
		}
		//// Moje 030517 End of insertion 2
		////Moje 030612 start
		////////////////////////////////////////
		case GUNSHIP_TYPE_HIND:
		////////////////////////////////////////
		{
			//
			// pop 'overlaid' target acquisition events first
			//

			deinitialise_common_target_acquisition_systems ();

			//
			// pop events before avionics are de-initialised
			//

			pop_event (set_gunship_view_mode_events);

			pop_event (set_hind_avionics_events);

			pop_event (set_common_avionics_events);

			save_gunship_avionics_damage (gunship_type);

			deinitialise_common_hud ();

			deinitialise_common_mfd ();

			deinitialise_common_weapon_systems ();

			deinitialise_common_night_vision_system ();

			deinitialise_hind_hud ();

			deinitialise_hind_mfd ();

			deinitialise_hind_ekran_display ();

			deinitialise_hind_target_acquisition_systems ();

			deinitialise_hind_lamp_avionics ();

			deinitialise_hind_threat_warning_system ();

			break;
		}
		////Moje 030612 end
		//// Moje 030815 start insertion 2
		case GUNSHIP_TYPE_AH64A:
		////////////////////////////////////////
		{
			//
			// pop 'overlaid' target acquisition events first
			//

			deinitialise_common_target_acquisition_systems ();

			//
			// pop events before avionics are de-initialised
			//

			pop_event (set_gunship_view_mode_events);

			pop_event (set_ah64a_avionics_events);

			pop_event (set_common_avionics_events);

			save_gunship_avionics_damage (gunship_type);

			deinitialise_common_hud ();

			deinitialise_common_mfd ();

			deinitialise_common_weapon_systems ();

			deinitialise_common_night_vision_system ();

			deinitialise_ah64a_hud ();

			deinitialise_ah64a_mfd ();

			deinitialise_ah64a_upfront_display ();

			deinitialise_ah64a_target_acquisition_systems ();

			deinitialise_ah64a_lamp_avionics ();

			deinitialise_ah64a_threat_warning_system ();

			break;
		}
		case GUNSHIP_TYPE_KA50:
		////////////////////////////////////////
		{
			//
			// pop 'overlaid' target acquisition events first
			//

			deinitialise_common_target_acquisition_systems ();

			//
			// pop events before avionics are de-initialised
			//

			pop_event (set_gunship_view_mode_events);

			pop_event (set_ka50_avionics_events);

			pop_event (set_common_avionics_events);

			save_gunship_avionics_damage (gunship_type);

			deinitialise_common_hud ();

			deinitialise_common_mfd ();

			deinitialise_common_weapon_systems ();

			deinitialise_common_night_vision_system ();

			deinitialise_ka50_hud ();

			deinitialise_ka50_mfd ();

			deinitialise_ka50_target_acquisition_systems ();

			deinitialise_ka50_lamp_avionics ();

			deinitialise_ka50_threat_warning_system ();

			break;
		}
		//// Moje 030517 End of insertion 2

		////////////////////////////////////////
		case GUNSHIP_TYPE_VIPER:
		////////////////////////////////////////
		{
			//
			// pop 'overlaid' target acquisition events first
			//

			deinitialise_common_target_acquisition_systems ();

			//
			// pop events before avionics are de-initialised
			//

			pop_event (set_gunship_view_mode_events);

			pop_event (set_viper_avionics_events);

			pop_event (set_common_avionics_events);

			save_gunship_avionics_damage (gunship_type);

			deinitialise_common_hud ();

			deinitialise_common_mfd ();

			deinitialise_common_weapon_systems ();

			deinitialise_common_night_vision_system ();

			deinitialise_viper_hud ();

			deinitialise_viper_mfd ();

			deinitialise_viper_target_acquisition_systems ();

			deinitialise_viper_lamp_avionics ();

			deinitialise_viper_threat_warning_system ();

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_KIOWA:
		////////////////////////////////////////
		{
			//
			// pop 'overlaid' target acquisition events first
			//

			deinitialise_common_target_acquisition_systems ();

			//
			// pop events before avionics are de-initialised
			//

			pop_event (set_gunship_view_mode_events);

			pop_event (set_kiowa_avionics_events);

			pop_event (set_common_avionics_events);

			save_gunship_avionics_damage (gunship_type);

			deinitialise_common_hud ();

			deinitialise_common_mfd ();

			deinitialise_common_weapon_systems ();

			deinitialise_common_night_vision_system ();

			deinitialise_kiowa_hud ();

			deinitialise_kiowa_mfd ();

			deinitialise_kiowa_target_acquisition_systems ();

			deinitialise_kiowa_lamp_avionics ();

			deinitialise_kiowa_threat_warning_system ();

			break;
		}
		////////////////////////////////////////
		// GCsDriver  08-12-2007
		default:
		////////////////////////////////////////
		{
			//
			// pop 'overlaid' target acquisition events first
			//

			deinitialise_common_target_acquisition_systems ();

			//
			// pop events before avionics are de-initialised
			//

			pop_event (set_gunship_view_mode_events);

			pop_event (set_default_avionics_events);

			pop_event (set_common_avionics_events);

			save_gunship_avionics_damage (gunship_type);

			deinitialise_common_hud ();

			deinitialise_common_mfd ();

			deinitialise_common_weapon_systems ();

			deinitialise_common_night_vision_system ();

			deinitialise_default_hud ();

			deinitialise_default_mfd ();

			deinitialise_default_upfront_display ();

			deinitialise_default_target_acquisition_systems ();

			deinitialise_default_lamp_avionics ();

			deinitialise_default_threat_warning_system ();

			break;
		}


	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_avionics (void)
{
	if (!initialised)
	{
		return;
	}

	if (command_line_shared_mem_export != 0)
	{
		update_dynamics_shared_mem ();	// Retro 8Mar2005 - all this stuff should MAYBE get moved 2-3 calls up the call
										// stack to a place where it is also done if we are in the campaign map..
		update_waypoint_shared_mem();
		update_weapon_load_shared_mem();
	}

	switch (gunship_type)
	{
		////////////////////////////////////////
		// JB 030313 Fly any aircraft
//		default:
		case GUNSHIP_TYPE_APACHE:
		////////////////////////////////////////
		{
			update_common_target_acquisition_systems ();

			update_apache_target_acquisition_system ();

			update_apache_weapon_systems ();

			update_apache_lamp_avionics ();

			update_apache_threat_warning_system ();

			update_apache_upfront_display ();

			if (command_line_shared_mem_export != 0)
				update_apache_avionics_shared_mem ();	// Retro 8Mar2005

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_HAVOC:
		////////////////////////////////////////
		{
			update_common_target_acquisition_systems ();

			update_havoc_target_acquisition_system ();

			update_havoc_weapon_systems ();

			update_havoc_lamp_avionics ();

			update_havoc_threat_warning_system ();

			update_havoc_ekran_display ();

			if (command_line_shared_mem_export != 0)
				update_havoc_avionics_shared_mem ();	// Retro 8Mar2005

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_COMANCHE:
		////////////////////////////////////////
		{
			update_common_target_acquisition_systems ();

			update_comanche_target_acquisition_system ();

			update_comanche_weapon_systems ();

			update_comanche_lamp_avionics ();

			update_comanche_threat_warning_system ();

			if (command_line_shared_mem_export != 0)
				update_comanche_avionics_shared_mem ();	// Retro 8Mar2005

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_HOKUM:
		////////////////////////////////////////
		{
			update_common_target_acquisition_systems ();

			update_hokum_target_acquisition_system ();

			update_hokum_weapon_systems ();

			update_hokum_lamp_avionics ();

			update_hokum_threat_warning_system ();

			if (command_line_shared_mem_export != 0)
				update_hokum_avionics_shared_mem ();	// Retro 8Mar2005

			break;
		}
		////////////////////////////////////////
		////Moje 030517 start of 3rd insertion
		case GUNSHIP_TYPE_BLACKHAWK:
		////////////////////////////////////////
		{
			update_common_target_acquisition_systems ();

			update_blackhawk_target_acquisition_system ();

			update_blackhawk_weapon_systems ();

			update_blackhawk_lamp_avionics ();

			update_blackhawk_threat_warning_system ();

			update_blackhawk_upfront_display ();

			if (command_line_shared_mem_export != 0)
				update_blackhawk_avionics_shared_mem ();	// Retro 8Mar2005

			break;
		}
		////Moje 030517 End of 3rd insertion
		////Moje 030612 start
		////////////////////////////////////////
		case GUNSHIP_TYPE_HIND:
		////////////////////////////////////////
		{
			update_common_target_acquisition_systems ();

			update_hind_target_acquisition_system ();

			update_hind_weapon_systems ();

			update_hind_lamp_avionics ();

			update_hind_threat_warning_system ();

			update_hind_ekran_display ();

			if (command_line_shared_mem_export != 0)
				update_hind_avionics_shared_mem ();	// Retro 8Mar2005

			break;
		}
		////Moje 030612 end
		////Moje 030815 Start
		case GUNSHIP_TYPE_AH64A:
		////////////////////////////////////////
		{
			update_common_target_acquisition_systems ();

			update_ah64a_target_acquisition_system ();

			update_ah64a_weapon_systems ();

			update_ah64a_lamp_avionics ();

			update_ah64a_threat_warning_system ();

			update_ah64a_upfront_display ();

			if (command_line_shared_mem_export != 0)
				update_ah64a_avionics_shared_mem ();	// Retro 8Mar2005

			break;
		}
		case GUNSHIP_TYPE_KA50:
		////////////////////////////////////////
		{
			update_common_target_acquisition_systems ();

			update_ka50_target_acquisition_system ();

			update_ka50_weapon_systems ();

			update_ka50_lamp_avionics ();

			update_ka50_threat_warning_system ();

			update_ka50_ekran_display ();

			update_ka50_cannon_rounds_display ();

			if (command_line_shared_mem_export != 0)
				update_ka50_avionics_shared_mem ();	// Retro 8Mar2005

			break;
		}
		////Moje 030815 End of 3rd insertion

		////////////////////////////////////////
		case GUNSHIP_TYPE_VIPER:
		////////////////////////////////////////
		{
			update_common_target_acquisition_systems ();

			update_viper_target_acquisition_system ();

			update_viper_weapon_systems ();

			update_viper_lamp_avionics ();

			update_viper_threat_warning_system ();

			if (command_line_shared_mem_export != 0)
				update_viper_avionics_shared_mem ();

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_KIOWA:
		////////////////////////////////////////
		{
			update_common_target_acquisition_systems ();

			update_kiowa_target_acquisition_system ();

			update_kiowa_weapon_systems ();

			update_kiowa_lamp_avionics ();

			update_kiowa_threat_warning_system ();

			if (command_line_shared_mem_export != 0)
				update_kiowa_avionics_shared_mem ();

			break;
		}
		////////////////////////////////////////
		// GCsDriver  08-12-2007
		default:
		////////////////////////////////////////
		{
			update_common_target_acquisition_systems ();

			update_default_target_acquisition_system ();

			update_default_weapon_systems ();

			update_default_lamp_avionics ();

			update_default_threat_warning_system ();

			update_default_upfront_display ();

			if (command_line_shared_mem_export != 0)
				update_default_avionics_shared_mem ();	// Retro 8Mar2005

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
