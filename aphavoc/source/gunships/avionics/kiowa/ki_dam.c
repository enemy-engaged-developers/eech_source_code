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

kiowa_damage_flags
	kiowa_damage;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_kiowa_weapon_damage_status (void)
{
	entity
		*en = nullptr;

	entity_sub_types
		weapon_sub_type;

	en = get_gunship_entity ();

	set_client_server_entity_weapon_damage (en, KIOWA_LHS_PYLON, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, kiowa_damage.lh_pylon);
	set_client_server_entity_weapon_damage (en, KIOWA_RHS_PYLON, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, kiowa_damage.rh_pylon);
	set_client_server_entity_weapon_damage (en, KIOWA_CHAFF_DISPENSER, ENTITY_SUB_TYPE_WEAPON_CHAFF, kiowa_damage.chaff_dispenser);
	set_client_server_entity_weapon_damage (en, KIOWA_FLARE_DISPENSER, ENTITY_SUB_TYPE_WEAPON_FLARE, kiowa_damage.flare_dispenser);

	//
	// check if selected weapon is still available, if not, select next
	//

	weapon_sub_type = get_local_entity_int_value (en, INT_TYPE_SELECTED_WEAPON);

	if (weapon_sub_type != ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
	{
		if (!get_local_entity_weapon_available (en, weapon_sub_type))
		{
			weapon_sub_type = get_next_available_weapon_sub_type (en);

			set_gunship_weapon (weapon_sub_type);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void fully_repair_kiowa_damage (void)
{
	fire_extinguisher_used = FALSE;

	////////////////////////////////////////

	kiowa_damage.flir = FALSE;

	////////////////////////////////////////

	kiowa_damage.dtv = FALSE;

	////////////////////////////////////////

	kiowa_damage.laser_designator = FALSE;

	////////////////////////////////////////

	kiowa_damage.infra_red_jammer = FALSE;

	////////////////////////////////////////

	kiowa_damage.navigation_computer = FALSE;

	////////////////////////////////////////

	kiowa_damage.communications = FALSE;

	////////////////////////////////////////

	kiowa_damage.radar_warning_system = FALSE;

	////////////////////////////////////////

	if (kiowa_damage.co_pilot_main_mfd)
	{
		kiowa_damage.co_pilot_main_mfd = FALSE;

		select_kiowa_main_mfd_mode (KIOWA_MAIN_MFD_MODE_OFF, KIOWA_MAIN_MFD_LOCATION_PILOT);
	}

	////////////////////////////////////////

	if (kiowa_damage.pilot_main_mfd)
	{
		kiowa_damage.pilot_main_mfd = FALSE;

		select_kiowa_main_mfd_mode (KIOWA_MAIN_MFD_MODE_OFF, KIOWA_MAIN_MFD_LOCATION_PILOT);
	}

	////////////////////////////////////////

	if (kiowa_damage.center_main_mfd)
	{
		kiowa_damage.center_main_mfd = FALSE;

		select_kiowa_main_mfd_mode (KIOWA_MAIN_MFD_MODE_OFF, KIOWA_MAIN_MFD_LOCATION_CENTER);
	}

	////////////////////////////////////////

	kiowa_damage.pnvs = FALSE;

	////////////////////////////////////////

	kiowa_damage.lh_pylon = FALSE;

	////////////////////////////////////////

	kiowa_damage.rh_pylon = FALSE;

	////////////////////////////////////////

	kiowa_damage.chaff_dispenser = FALSE;

	////////////////////////////////////////

	kiowa_damage.flare_dispenser = FALSE;

	////////////////////////////////////////

	kiowa_damage.hud = FALSE;

	////////////////////////////////////////

	set_kiowa_weapon_damage_status ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void partially_repair_kiowa_damage (void)
{
	fire_extinguisher_used = FALSE;

	////////////////////////////////////////

	if (kiowa_damage.flir)
	{
		kiowa_damage.flir = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (kiowa_damage.dtv)
	{
		kiowa_damage.dtv = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (kiowa_damage.laser_designator)
	{
		kiowa_damage.laser_designator = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (kiowa_damage.infra_red_jammer)
	{
		kiowa_damage.infra_red_jammer = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (kiowa_damage.navigation_computer)
	{
		kiowa_damage.navigation_computer = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (kiowa_damage.communications)
	{
		kiowa_damage.communications = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (kiowa_damage.radar_warning_system)
	{
		kiowa_damage.radar_warning_system = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (kiowa_damage.co_pilot_main_mfd)
	{
		kiowa_damage.co_pilot_main_mfd = frand1 () > 0.90;

		if (!kiowa_damage.co_pilot_main_mfd)
		{
			select_kiowa_main_mfd_mode (KIOWA_MAIN_MFD_MODE_OFF, KIOWA_MAIN_MFD_LOCATION_CO_PILOT);
		}
	}

	////////////////////////////////////////

	if (kiowa_damage.pilot_main_mfd)
	{
		kiowa_damage.pilot_main_mfd = frand1 () > 0.90;

		if (!kiowa_damage.pilot_main_mfd)
		{
			select_kiowa_main_mfd_mode (KIOWA_MAIN_MFD_MODE_OFF, KIOWA_MAIN_MFD_LOCATION_PILOT);
		}
	}

	////////////////////////////////////////

	if (kiowa_damage.center_main_mfd)
	{
		kiowa_damage.center_main_mfd = frand1 () > 0.90;

		if (!kiowa_damage.center_main_mfd)
		{
			select_kiowa_main_mfd_mode (KIOWA_MAIN_MFD_MODE_OFF, KIOWA_MAIN_MFD_LOCATION_CENTER);
		}
	}

	////////////////////////////////////////

	if (kiowa_damage.pnvs)
	{
		kiowa_damage.pnvs = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (kiowa_damage.lh_pylon)
	{
		kiowa_damage.lh_pylon = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (kiowa_damage.rh_pylon)
	{
		kiowa_damage.rh_pylon = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (kiowa_damage.chaff_dispenser)
	{
		kiowa_damage.chaff_dispenser = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (kiowa_damage.flare_dispenser)
	{
		kiowa_damage.flare_dispenser = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (kiowa_damage.hud)
	{
		kiowa_damage.hud = frand1 () > 0.90;
	}

	////////////////////////////////////////

	set_kiowa_weapon_damage_status ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void repair_kiowa_weapon_damage (void)
{
	kiowa_damage.lh_pylon			= FALSE;
	kiowa_damage.rh_pylon			= FALSE;
	kiowa_damage.chaff_dispenser				= FALSE;
	kiowa_damage.flare_dispenser				= FALSE;

	set_kiowa_weapon_damage_status ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void damage_systems (kiowa_damage_flags damage)
{
	entity
		*en = nullptr;

	en = get_gunship_entity ();

	////////////////////////////////////////

	if (damage.flir)
	{
		if (!kiowa_damage.flir)
		{
			activate_kiowa_master_caution ();

			kiowa_damage.flir = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			play_client_server_warning_message (en, SPEECH_SYSTEM_FLIR_FAILURE);

			if (target_acquisition_system == TARGET_ACQUISITION_SYSTEM_FLIR)
			{
				select_kiowa_target_acquisition_system (TARGET_ACQUISITION_SYSTEM_OFF);
			}
		}
	}

	////////////////////////////////////////

	if (damage.dtv)
	{
		if (!kiowa_damage.dtv)
		{
			activate_kiowa_master_caution ();

			kiowa_damage.dtv = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			play_client_server_warning_message (en, SPEECH_SYSTEM_DTV_FAILURE);

			if (target_acquisition_system == TARGET_ACQUISITION_SYSTEM_DTV)
			{
				select_kiowa_target_acquisition_system (TARGET_ACQUISITION_SYSTEM_OFF);
			}
		}
	}

	////////////////////////////////////////

	if (damage.laser_designator)
	{
		if (!kiowa_damage.laser_designator)
		{
			activate_kiowa_master_caution ();

			kiowa_damage.laser_designator = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_laser_is_active(FALSE);

			play_client_server_warning_message (en, SPEECH_SYSTEM_LASER_DESIGNATOR_FAILURE);
		}
	}

	////////////////////////////////////////

	if (damage.infra_red_jammer)
	{
		if (!kiowa_damage.infra_red_jammer)
		{
			activate_kiowa_master_caution ();

			kiowa_damage.infra_red_jammer = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			play_client_server_warning_message (en, SPEECH_SYSTEM_IR_JAMMER_FAILURE);

			if (get_local_entity_int_value (get_gunship_entity (), INT_TYPE_INFRA_RED_JAMMER_ON))
			{
				set_client_server_entity_int_value (get_gunship_entity (), INT_TYPE_INFRA_RED_JAMMER_ON, FALSE);
			}
		}
	}

	////////////////////////////////////////

	if (damage.navigation_computer)
	{
		if (!kiowa_damage.navigation_computer)
		{
			activate_kiowa_master_caution ();

			kiowa_damage.navigation_computer = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			play_client_server_warning_message (en, SPEECH_SYSTEM_NAV_COMPUTER_FAILURE);
		}
	}

	////////////////////////////////////////

	if (damage.communications)
	{
		if (!kiowa_damage.communications)
		{
			activate_kiowa_master_caution ();

			kiowa_damage.communications = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			play_client_server_warning_message (en, SPEECH_SYSTEM_COMMS_FAILURE);
		}
	}

	////////////////////////////////////////

	if (damage.radar_warning_system)
	{
		if (!kiowa_damage.radar_warning_system)
		{
			activate_kiowa_master_caution ();

			kiowa_damage.radar_warning_system = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			play_client_server_warning_message (en, SPEECH_SYSTEM_RADAR_WARNING_FAILURE);
		}
	}

	////////////////////////////////////////

	if (damage.co_pilot_main_mfd)
	{
		if (!kiowa_damage.co_pilot_main_mfd)
		{
			activate_kiowa_master_caution ();

			kiowa_damage.co_pilot_main_mfd = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			play_client_server_warning_message (en, SPEECH_SYSTEM_MFD_FAILURE);

			select_kiowa_main_mfd_mode (KIOWA_MAIN_MFD_MODE_DAMAGED, KIOWA_MAIN_MFD_LOCATION_CO_PILOT);
		}
	}

	////////////////////////////////////////

	if (damage.pilot_main_mfd)
	{
		if (!kiowa_damage.pilot_main_mfd)
		{
			activate_kiowa_master_caution ();

			kiowa_damage.pilot_main_mfd = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			play_client_server_warning_message (en, SPEECH_SYSTEM_MFD_FAILURE);

			select_kiowa_main_mfd_mode (KIOWA_MAIN_MFD_MODE_DAMAGED, KIOWA_MAIN_MFD_LOCATION_PILOT);
		}
	}

	////////////////////////////////////////

	if (damage.center_main_mfd)
	{
		if (!kiowa_damage.center_main_mfd)
		{
			activate_kiowa_master_caution ();

			kiowa_damage.center_main_mfd = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			play_client_server_warning_message (en, SPEECH_SYSTEM_MFD_FAILURE);

			select_kiowa_main_mfd_mode (KIOWA_MAIN_MFD_MODE_DAMAGED, KIOWA_MAIN_MFD_LOCATION_CENTER);
		}
	}

	////////////////////////////////////////

	if (damage.pnvs)
	{
		if (!kiowa_damage.pnvs)
		{
			activate_kiowa_master_caution ();

			kiowa_damage.pnvs = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			play_client_server_warning_message (en, SPEECH_SYSTEM_PNVS_FAILURE);

			night_vision_system_active = FALSE;
		}
	}

	////////////////////////////////////////

	if (damage.lh_pylon)
	{
		if (!kiowa_damage.lh_pylon)
		{
			activate_kiowa_master_caution ();

			kiowa_damage.lh_pylon = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			play_client_server_warning_message (en, SPEECH_SYSTEM_HARDPOINT_DAMAGED);
		}
	}

	////////////////////////////////////////

	if (damage.rh_pylon)
	{
		if (!kiowa_damage.rh_pylon)
		{
			activate_kiowa_master_caution ();

			kiowa_damage.rh_pylon = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			play_client_server_warning_message (en, SPEECH_SYSTEM_HARDPOINT_DAMAGED);
		}
	}

	////////////////////////////////////////

	if (damage.chaff_dispenser)
	{
		if (!kiowa_damage.chaff_dispenser)
		{
			activate_kiowa_master_caution ();

			kiowa_damage.chaff_dispenser = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			play_client_server_warning_message (en, SPEECH_SYSTEM_CHAFF_DISPENSER_DAMAGED);
		}
	}

	////////////////////////////////////////

	if (damage.flare_dispenser)
	{
		if (!kiowa_damage.flare_dispenser)
		{
			activate_kiowa_master_caution ();

			kiowa_damage.flare_dispenser = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			play_client_server_warning_message (en, SPEECH_SYSTEM_FLARE_DISPENSER_DAMAGED);
		}
	}
	////////////////////////////////////////

	if (damage.hud)
	{
		if (!kiowa_damage.hud)
		{
			activate_kiowa_master_caution ();

			kiowa_damage.hud = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			play_client_server_warning_message (en, SPEECH_SYSTEM_HUD_FAILURE);
		}
	}

	////////////////////////////////////////

	set_kiowa_weapon_damage_status ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void damage_kiowa (gunship_damage_levels damage_level)
{
	unsigned int
		damage;

	kiowa_damage_flags
		kiowa_damage;

	damage = 0;

	switch (damage_level)
	{
		case GUNSHIP_DAMAGE_LEVEL_LIGHT:
		{
			damage |= 1 << (rand16 () & 0x1f);

			break;
		}
		case GUNSHIP_DAMAGE_LEVEL_MEDIUM:
		{
			damage |= 1 << (rand16 () & 0x1f);
			damage |= 1 << (rand16 () & 0x1f);

			break;
		}
		case GUNSHIP_DAMAGE_LEVEL_HEAVY:
		{
			damage |= 1 << (rand16 () & 0x1f);
			damage |= 1 << (rand16 () & 0x1f);
			damage |= 1 << (rand16 () & 0x1f);

			break;
		}
		default:
		{
			debug_fatal ("Invalid damage_level = %d", damage_level);

			break;
		}
	}

	kiowa_damage.flags = damage;

	damage_systems (kiowa_damage);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_kiowa_avionics_of_dynamics_fault (unsigned int damage)
{
	if (damage & DYNAMICS_DAMAGE_MAIN_ROTOR)
	{
		activate_kiowa_master_caution ();
	}

	if (damage & DYNAMICS_DAMAGE_TAIL_ROTOR)
	{
		activate_kiowa_master_caution ();
	}

	if (damage & DYNAMICS_DAMAGE_LEFT_ENGINE)
	{
		activate_kiowa_master_caution ();
	}

	if (damage & DYNAMICS_DAMAGE_LEFT_ENGINE_FIRE)
	{
		activate_kiowa_master_caution ();
	}

	if (damage & DYNAMICS_DAMAGE_LOW_HYDRAULICS)
	{
		activate_kiowa_master_caution ();
	}

	if (damage & DYNAMICS_DAMAGE_SECONDARY_HYDRAULICS)
	{
		activate_kiowa_master_caution ();
	}

	if (damage & DYNAMICS_DAMAGE_STABILISER)
	{
		activate_kiowa_master_caution ();
	}

	if (damage & DYNAMICS_DAMAGE_FUEL_LEAK)
	{
		activate_kiowa_master_caution ();
	}

	if (damage & DYNAMICS_DAMAGE_LOW_OIL_PRESSURE)
	{
		activate_kiowa_master_caution ();
	}

	if (damage & DYNAMICS_DAMAGE_HIGH_OIL_PRESSURE)
	{
		activate_kiowa_master_caution ();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
