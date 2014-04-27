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

havoc_damage_flags
	havoc_damage;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_havoc_weapon_damage_status (void)
{
	entity
		*en;

	entity_sub_types
		weapon_sub_type;

	en = get_gunship_entity ();

	set_client_server_entity_weapon_damage (en, HAVOC_CANNON_TURRET, ENTITY_SUB_TYPE_WEAPON_2A42_30MM_HE_ROUND, havoc_damage.gun_jammed);
	set_client_server_entity_weapon_damage (en, HAVOC_CANNON_TURRET, ENTITY_SUB_TYPE_WEAPON_2A42_30MM_AP_ROUND, havoc_damage.gun_jammed);

	set_client_server_entity_weapon_damage (en, HAVOC_LHS_OUTER_PYLON, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, havoc_damage.lh_outer_pylon);
	set_client_server_entity_weapon_damage (en, HAVOC_LHS_INNER_PYLON, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, havoc_damage.lh_inner_pylon);

	set_client_server_entity_weapon_damage (en, HAVOC_RHS_OUTER_PYLON, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, havoc_damage.rh_outer_pylon);
	set_client_server_entity_weapon_damage (en, HAVOC_RHS_INNER_PYLON, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, havoc_damage.rh_inner_pylon);

	set_client_server_entity_weapon_damage (en, HAVOC_LHS_CHAFF_DISPENSER, ENTITY_SUB_TYPE_WEAPON_CHAFF, havoc_damage.chaff_dispenser);
	set_client_server_entity_weapon_damage (en, HAVOC_LHS_FLARE_DISPENSER, ENTITY_SUB_TYPE_WEAPON_FLARE, havoc_damage.flare_dispenser);
	set_client_server_entity_weapon_damage (en, HAVOC_RHS_CHAFF_DISPENSER, ENTITY_SUB_TYPE_WEAPON_CHAFF, havoc_damage.chaff_dispenser);
	set_client_server_entity_weapon_damage (en, HAVOC_RHS_FLARE_DISPENSER, ENTITY_SUB_TYPE_WEAPON_FLARE, havoc_damage.flare_dispenser);

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

void fully_repair_havoc_damage (void)
{
	set_havoc_ekran_display_text ("", "", NULL, NULL);

	fire_extinguisher_used = FALSE;

	////////////////////////////////////////

	havoc_damage.radar = FALSE;

	////////////////////////////////////////

	havoc_damage.flir = FALSE;

	////////////////////////////////////////

	havoc_damage.llltv = FALSE;

	////////////////////////////////////////

	havoc_damage.laser_range_finder = FALSE;

	////////////////////////////////////////

	havoc_damage.radar_jammer = FALSE;

	////////////////////////////////////////

	havoc_damage.infra_red_jammer = FALSE;

	////////////////////////////////////////

	havoc_damage.navigation_computer = FALSE;

	////////////////////////////////////////

	havoc_damage.communications = FALSE;

	////////////////////////////////////////

	havoc_damage.radar_warning_system = FALSE;

	////////////////////////////////////////

	havoc_damage.head_up_display = FALSE;

	////////////////////////////////////////

	havoc_damage.helmet_mounted_sight = FALSE;

	////////////////////////////////////////

	havoc_damage.tv_display = FALSE;

	////////////////////////////////////////

	havoc_damage.threat_warning_display = FALSE;

	////////////////////////////////////////

	havoc_damage.night_vision_goggles = FALSE;

	////////////////////////////////////////

	havoc_damage.gun_jammed = FALSE;

	////////////////////////////////////////

	havoc_damage.lh_outer_pylon = FALSE;

	////////////////////////////////////////

	havoc_damage.lh_inner_pylon = FALSE;

	////////////////////////////////////////

	havoc_damage.rh_outer_pylon = FALSE;

	////////////////////////////////////////

	havoc_damage.rh_inner_pylon = FALSE;

	////////////////////////////////////////

	havoc_damage.chaff_dispenser = FALSE;

	////////////////////////////////////////

	havoc_damage.flare_dispenser = FALSE;

	////////////////////////////////////////

	set_havoc_weapon_damage_status ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void partially_repair_havoc_damage (void)
{
	set_havoc_ekran_display_text ("", "", NULL, NULL);

	fire_extinguisher_used = FALSE;

	////////////////////////////////////////

	if (havoc_damage.radar)
	{
		havoc_damage.radar = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (havoc_damage.flir)
	{
		havoc_damage.flir = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (havoc_damage.llltv)
	{
		havoc_damage.llltv = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (havoc_damage.laser_range_finder)
	{
		havoc_damage.laser_range_finder = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (havoc_damage.radar_jammer)
	{
		havoc_damage.radar_jammer = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (havoc_damage.infra_red_jammer)
	{
		havoc_damage.infra_red_jammer = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (havoc_damage.navigation_computer)
	{
		havoc_damage.navigation_computer = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (havoc_damage.communications)
	{
		havoc_damage.communications = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (havoc_damage.radar_warning_system)
	{
		havoc_damage.radar_warning_system = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (havoc_damage.head_up_display)
	{
		havoc_damage.head_up_display = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (havoc_damage.helmet_mounted_sight)
	{
		havoc_damage.helmet_mounted_sight = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (havoc_damage.tv_display)
	{
		havoc_damage.tv_display = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (havoc_damage.threat_warning_display)
	{
		havoc_damage.threat_warning_display = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (havoc_damage.night_vision_goggles)
	{
		havoc_damage.night_vision_goggles = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (havoc_damage.gun_jammed)
	{
		havoc_damage.gun_jammed = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (havoc_damage.lh_outer_pylon)
	{
		havoc_damage.lh_outer_pylon = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (havoc_damage.lh_inner_pylon)
	{
		havoc_damage.lh_inner_pylon = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (havoc_damage.rh_outer_pylon)
	{
		havoc_damage.rh_outer_pylon = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (havoc_damage.rh_inner_pylon)
	{
		havoc_damage.rh_inner_pylon = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (havoc_damage.chaff_dispenser)
	{
		havoc_damage.chaff_dispenser = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (havoc_damage.flare_dispenser)
	{
		havoc_damage.flare_dispenser = frand1 () > 0.90;
	}

	////////////////////////////////////////

	set_havoc_weapon_damage_status ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void repair_havoc_weapon_damage (void)
{
	set_havoc_ekran_display_text ("", "", NULL, NULL);

	havoc_damage.gun_jammed			= FALSE;
	havoc_damage.lh_outer_pylon	= FALSE;
	havoc_damage.lh_inner_pylon	= FALSE;
	havoc_damage.rh_outer_pylon	= FALSE;
	havoc_damage.rh_inner_pylon	= FALSE;
	havoc_damage.chaff_dispenser	= FALSE;
	havoc_damage.flare_dispenser	= FALSE;

	set_havoc_weapon_damage_status ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void damage_systems (havoc_damage_flags damage)
{
	entity
		*en;

	en = get_gunship_entity ();

	////////////////////////////////////////

	if (damage.radar)
	{
		if (!havoc_damage.radar)
		{
			activate_havoc_master_caution_lamp ();

			havoc_damage.radar = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_havoc_ekran_display_text ("RADAR", "FAILURE", NULL, NULL);

			set_ground_radar_is_active(FALSE);
			set_air_radar_is_active(FALSE);

			play_client_server_warning_message (en, SPEECH_SYSTEM_RADAR_FAILURE);

			if
			(
				(target_acquisition_system == TARGET_ACQUISITION_SYSTEM_GROUND_RADAR) ||
				(target_acquisition_system == TARGET_ACQUISITION_SYSTEM_AIR_RADAR)
			)
			{
				select_havoc_target_acquisition_system (TARGET_ACQUISITION_SYSTEM_OFF);
			}
		}
	}

	////////////////////////////////////////

	if (damage.flir)
	{
		if (!havoc_damage.flir)
		{
			activate_havoc_master_caution_lamp ();

			havoc_damage.flir = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_havoc_ekran_display_text ("FLIR", "FAILURE", NULL, NULL);

			play_client_server_warning_message (en, SPEECH_SYSTEM_FLIR_FAILURE);

			if (target_acquisition_system == TARGET_ACQUISITION_SYSTEM_FLIR)
			{
				select_havoc_target_acquisition_system (TARGET_ACQUISITION_SYSTEM_OFF);
			}
		}
	}

	////////////////////////////////////////

	if (damage.llltv)
	{
		if (!havoc_damage.llltv)
		{
			activate_havoc_master_caution_lamp ();

			havoc_damage.llltv = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_havoc_ekran_display_text ("LLLTV", "FAILURE", NULL, NULL);

			play_client_server_warning_message (en, SPEECH_SYSTEM_LLLTV_FAILURE);

			if (target_acquisition_system == TARGET_ACQUISITION_SYSTEM_LLLTV)
			{
				select_havoc_target_acquisition_system (TARGET_ACQUISITION_SYSTEM_OFF);
			}
		}
	}

	////////////////////////////////////////

	if (damage.laser_range_finder)
	{
		if (!havoc_damage.laser_range_finder)
		{
			activate_havoc_master_caution_lamp ();

			havoc_damage.laser_range_finder = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_laser_is_active(FALSE);

			set_havoc_ekran_display_text ("LASER", "FAILURE", NULL, NULL);

			play_client_server_warning_message (en, SPEECH_SYSTEM_LASER_RANGE_FINDER_FAILURE);
		}
	}

	////////////////////////////////////////

	if (damage.radar_jammer)
	{
		if (!havoc_damage.radar_jammer)
		{
			activate_havoc_master_caution_lamp ();

			havoc_damage.radar_jammer = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_havoc_ekran_display_text ("RD JAMMER", "FAILURE", NULL, NULL);

			play_client_server_warning_message (en, SPEECH_SYSTEM_RADAR_JAMMER_FAILURE);

			if (get_local_entity_int_value (get_gunship_entity (), INT_TYPE_RADAR_JAMMER_ON))
			{
				set_client_server_entity_int_value (get_gunship_entity (), INT_TYPE_RADAR_JAMMER_ON, FALSE);
			}
		}
	}

	////////////////////////////////////////

	if (damage.infra_red_jammer)
	{
		if (!havoc_damage.infra_red_jammer)
		{
			activate_havoc_master_caution_lamp ();

			havoc_damage.infra_red_jammer = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_havoc_ekran_display_text ("IR JAMMER", "FAILURE", NULL, NULL);

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
		if (!havoc_damage.navigation_computer)
		{
			activate_havoc_master_caution_lamp ();

			havoc_damage.navigation_computer = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_havoc_ekran_display_text ("NAV COMP", "FAILURE", NULL, NULL);

			play_client_server_warning_message (en, SPEECH_SYSTEM_NAV_COMPUTER_FAILURE);
		}
	}

	////////////////////////////////////////

	if (damage.communications)
	{
		if (!havoc_damage.communications)
		{
			activate_havoc_master_caution_lamp ();

			havoc_damage.communications = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_havoc_ekran_display_text ("COMMS", "FAILURE", NULL, NULL);

			play_client_server_warning_message (en, SPEECH_SYSTEM_COMMS_FAILURE);
		}
	}

	////////////////////////////////////////

	if (damage.radar_warning_system)
	{
		if (!havoc_damage.radar_warning_system)
		{
			activate_havoc_master_caution_lamp ();

			havoc_damage.radar_warning_system = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_havoc_ekran_display_text ("RWS", "FAILURE", NULL, NULL);

			play_client_server_warning_message (en, SPEECH_SYSTEM_RADAR_WARNING_FAILURE);
		}
	}

	////////////////////////////////////////

	if (!get_global_simple_avionics ())
	{
		if (damage.head_up_display)
		{
			if (!havoc_damage.head_up_display)
			{
				activate_havoc_master_caution_lamp ();

				havoc_damage.head_up_display = TRUE;

				dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

				set_havoc_ekran_display_text ("HUD", "FAILURE", NULL, NULL);

				play_client_server_warning_message (en, SPEECH_SYSTEM_HUD_FAILURE);
			}
		}
	}

	////////////////////////////////////////

	if (!get_global_simple_avionics ())
	{
		if (damage.helmet_mounted_sight)
		{
			if (!havoc_damage.helmet_mounted_sight)
			{
				activate_havoc_master_caution_lamp ();

				havoc_damage.helmet_mounted_sight = TRUE;

				dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

				set_havoc_ekran_display_text ("HMS", "FAILURE", NULL, NULL);

				play_client_server_warning_message (en, SPEECH_SYSTEM_HELMET_MOUNTED_SIGHT_FAILURE);

				if (target_acquisition_system == TARGET_ACQUISITION_SYSTEM_HMS)
				{
					select_havoc_target_acquisition_system (TARGET_ACQUISITION_SYSTEM_OFF);
				}
			}
		}
	}

	////////////////////////////////////////

	if (damage.tv_display)
	{
		if (!havoc_damage.tv_display)
		{
			activate_havoc_master_caution_lamp ();

			havoc_damage.tv_display = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_havoc_ekran_display_text ("TV", "FAILURE", NULL, NULL);

			play_client_server_warning_message (en, SPEECH_SYSTEM_TV_DISPLAY_FAILURE);
		}
	}

	////////////////////////////////////////

	if (damage.threat_warning_display)
	{
		if (!havoc_damage.threat_warning_display)
		{
			activate_havoc_master_caution_lamp ();

			havoc_damage.threat_warning_display = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_havoc_ekran_display_text ("TWD", "FAILURE", NULL, NULL);

			play_client_server_warning_message (en, SPEECH_SYSTEM_THREAT_WARNING_DISPLAY_FAILURE);
		}
	}

	////////////////////////////////////////

	if (damage.night_vision_goggles)
	{
		if (!havoc_damage.night_vision_goggles)
		{
			activate_havoc_master_caution_lamp ();

			havoc_damage.night_vision_goggles = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_havoc_ekran_display_text ("NVG", "DAMAGED", NULL, NULL);

			play_client_server_warning_message (en, SPEECH_SYSTEM_NIGHT_VISION_GOGGLES_FAILURE);

			night_vision_system_active = FALSE;
		}
	}

	////////////////////////////////////////

	if (damage.gun_jammed)
	{
		if (!havoc_damage.gun_jammed)
		{
			activate_havoc_master_caution_lamp ();

			havoc_damage.gun_jammed = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_havoc_ekran_display_text ("GUN", "JAMMED", NULL, NULL);

			play_client_server_warning_message (en, SPEECH_SYSTEM_GUN_JAMMED);
		}
	}

	////////////////////////////////////////

	if (damage.lh_outer_pylon)
	{
		if (!havoc_damage.lh_outer_pylon)
		{
			activate_havoc_master_caution_lamp ();

			havoc_damage.lh_outer_pylon = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_havoc_ekran_display_text ("HARDPOINT", "DAMAGED", NULL, NULL);

			play_client_server_warning_message (en, SPEECH_SYSTEM_HARDPOINT_DAMAGED);
		}
	}

	////////////////////////////////////////

	if (damage.lh_inner_pylon)
	{
		if (!havoc_damage.lh_inner_pylon)
		{
			activate_havoc_master_caution_lamp ();

			havoc_damage.lh_inner_pylon = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_havoc_ekran_display_text ("HARDPOINT", "DAMAGED", NULL, NULL);

			play_client_server_warning_message (en, SPEECH_SYSTEM_HARDPOINT_DAMAGED);
		}
	}

	////////////////////////////////////////

	if (damage.rh_outer_pylon)
	{
		if (!havoc_damage.rh_outer_pylon)
		{
			activate_havoc_master_caution_lamp ();

			havoc_damage.rh_outer_pylon = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_havoc_ekran_display_text ("HARDPOINT", "DAMAGED", NULL, NULL);

			play_client_server_warning_message (en, SPEECH_SYSTEM_HARDPOINT_DAMAGED);
		}
	}

	////////////////////////////////////////

	if (damage.rh_inner_pylon)
	{
		if (!havoc_damage.rh_inner_pylon)
		{
			activate_havoc_master_caution_lamp ();

			havoc_damage.rh_inner_pylon = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_havoc_ekran_display_text ("HARDPOINT", "DAMAGED", NULL, NULL);

			play_client_server_warning_message (en, SPEECH_SYSTEM_HARDPOINT_DAMAGED);
		}
	}

	////////////////////////////////////////

	if (damage.chaff_dispenser)
	{
		if (!havoc_damage.chaff_dispenser)
		{
			activate_havoc_master_caution_lamp ();

			havoc_damage.chaff_dispenser = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_havoc_ekran_display_text ("CHAFF", "DAMAGED", NULL, NULL);

			play_client_server_warning_message (en, SPEECH_SYSTEM_CHAFF_DISPENSER_DAMAGED);
		}
	}

	////////////////////////////////////////

	if (damage.flare_dispenser)
	{
		if (!havoc_damage.flare_dispenser)
		{
			activate_havoc_master_caution_lamp ();

			havoc_damage.flare_dispenser = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_havoc_ekran_display_text ("FLARES", "DAMAGED", NULL, NULL);

			play_client_server_warning_message (en, SPEECH_SYSTEM_FLARE_DISPENSER_DAMAGED);
		}
	}

	////////////////////////////////////////

	set_havoc_weapon_damage_status ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void damage_havoc (gunship_damage_levels damage_level)
{
	unsigned int
		damage;

	havoc_damage_flags
		havoc_damage;

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

	havoc_damage.flags = damage;

	damage_systems (havoc_damage);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_havoc_avionics_of_dynamics_fault (unsigned int damage)
{
	if (damage & DYNAMICS_DAMAGE_MAIN_ROTOR)
	{
		activate_havoc_master_caution_lamp ();

		set_havoc_ekran_display_text ("MAIN RTR", "DAMAGED", NULL, NULL);
	}

	if (damage & DYNAMICS_DAMAGE_TAIL_ROTOR)
	{
		activate_havoc_master_caution_lamp ();

		set_havoc_ekran_display_text ("TAIL RTR", "DAMAGED", NULL, NULL);
	}

	if (damage & DYNAMICS_DAMAGE_LEFT_ENGINE)
	{
		activate_havoc_master_caution_lamp ();

		set_havoc_ekran_display_text ("ENGINE 1", "DAMAGED", NULL, NULL);
	}

	if (damage & DYNAMICS_DAMAGE_RIGHT_ENGINE)
	{
		activate_havoc_master_caution_lamp ();

		set_havoc_ekran_display_text ("ENGINE 2", "DAMAGED", NULL, NULL);
	}

	if (damage & DYNAMICS_DAMAGE_LEFT_ENGINE_FIRE)
	{
		activate_havoc_master_caution_lamp ();

		set_havoc_ekran_display_text ("ENGINE 1", "FIRE", NULL, NULL);
	}

	if (damage & DYNAMICS_DAMAGE_RIGHT_ENGINE_FIRE)
	{
		activate_havoc_master_caution_lamp ();

		set_havoc_ekran_display_text ("ENGINE 2", "FIRE", NULL, NULL);
	}

	if (damage & DYNAMICS_DAMAGE_LOW_HYDRAULICS)
	{
		activate_havoc_master_caution_lamp ();

		set_havoc_ekran_display_text ("LOW HYDR", "PRESSURE", NULL, NULL);
	}

	if (damage & DYNAMICS_DAMAGE_SECONDARY_HYDRAULICS)
	{
		activate_havoc_master_caution_lamp ();

		set_havoc_ekran_display_text ("SEC HYDR", "DAMAGED", NULL, NULL);
	}

	if (damage & DYNAMICS_DAMAGE_STABILISER)
	{
		activate_havoc_master_caution_lamp ();

		set_havoc_ekran_display_text ("STABILISR", "FAILURE", NULL, NULL);
	}

	if (damage & DYNAMICS_DAMAGE_FUEL_LEAK)
	{
		activate_havoc_master_caution_lamp ();

		set_havoc_ekran_display_text ("FUEL LEAK", "", NULL, NULL);
	}

	if (damage & DYNAMICS_DAMAGE_LOW_OIL_PRESSURE)
	{
		activate_havoc_master_caution_lamp ();

		set_havoc_ekran_display_text ("LOW OIL", "PRESSURE", NULL, NULL);
	}

	if (damage & DYNAMICS_DAMAGE_HIGH_OIL_PRESSURE)
	{
		activate_havoc_master_caution_lamp ();

		set_havoc_ekran_display_text ("HIGH OIL", "PRESSURE", NULL, NULL);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
