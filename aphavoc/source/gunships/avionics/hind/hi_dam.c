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

hind_damage_flags
	hind_damage;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_hind_weapon_damage_status (void)
{
	entity
		*en = nullptr;

	entity_sub_types
		weapon_sub_type;

	en = get_gunship_entity ();

	set_client_server_entity_weapon_damage (en, HIND_CANNON_TURRET, ENTITY_SUB_TYPE_WEAPON_YAK_B_12P7MM_ROUND, hind_damage.gun_jammed);

	set_client_server_entity_weapon_damage (en, HIND_LHS_WING_TIP_MOUNT, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, hind_damage.lh_wing_tip_mount);
	set_client_server_entity_weapon_damage (en, HIND_LHS_OUTER_PYLON, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, hind_damage.lh_outer_pylon);
	set_client_server_entity_weapon_damage (en, HIND_LHS_INNER_PYLON, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, hind_damage.lh_inner_pylon);

	set_client_server_entity_weapon_damage (en, HIND_RHS_WING_TIP_MOUNT, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, hind_damage.rh_wing_tip_mount);
	set_client_server_entity_weapon_damage (en, HIND_RHS_OUTER_PYLON, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, hind_damage.rh_outer_pylon);
	set_client_server_entity_weapon_damage (en, HIND_RHS_INNER_PYLON, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, hind_damage.rh_inner_pylon);

	set_client_server_entity_weapon_damage (en, HIND_LHS_CHAFF_DISPENSER, ENTITY_SUB_TYPE_WEAPON_CHAFF, hind_damage.lhs_chaff_dispensers);
	set_client_server_entity_weapon_damage (en, HIND_RHS_CHAFF_DISPENSER, ENTITY_SUB_TYPE_WEAPON_CHAFF, hind_damage.rhs_chaff_dispensers);

	set_client_server_entity_weapon_damage (en, HIND_LHS_FLARE_DISPENSER, ENTITY_SUB_TYPE_WEAPON_FLARE, hind_damage.lhs_flare_dispensers);
	set_client_server_entity_weapon_damage (en, HIND_RHS_FLARE_DISPENSER, ENTITY_SUB_TYPE_WEAPON_FLARE, hind_damage.rhs_flare_dispensers);

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

void fully_repair_hind_damage (void)
{
	set_hind_ekran_display_text ("", "", NULL, NULL);

	fire_extinguisher_used = FALSE;

	////////////////////////////////////////

	hind_damage.radar = FALSE;

	////////////////////////////////////////

	hind_damage.dtv = FALSE;

	////////////////////////////////////////

	hind_damage.llltv = FALSE;

	////////////////////////////////////////

	hind_damage.laser_range_finder = FALSE;

	////////////////////////////////////////

	hind_damage.radar_jammer = FALSE;

	////////////////////////////////////////

	hind_damage.infra_red_jammer = FALSE;

	////////////////////////////////////////

	hind_damage.navigation_computer = FALSE;

	////////////////////////////////////////

	hind_damage.communications = FALSE;

	////////////////////////////////////////

	hind_damage.radar_warning_system = FALSE;

	////////////////////////////////////////

	hind_damage.head_up_display = FALSE;

	////////////////////////////////////////

	hind_damage.helmet_mounted_sight = FALSE;

	////////////////////////////////////////

	hind_damage.tv_display = FALSE;

	////////////////////////////////////////

	hind_damage.threat_warning_display = FALSE;

	////////////////////////////////////////

	hind_damage.night_vision_goggles = FALSE;

	////////////////////////////////////////

	hind_damage.gun_jammed = FALSE;

	////////////////////////////////////////

	hind_damage.lh_wing_tip_mount = FALSE;

	////////////////////////////////////////

	////////////////////////////////////////

	hind_damage.lh_outer_pylon = FALSE;

	////////////////////////////////////////

	hind_damage.lh_inner_pylon = FALSE;

	////////////////////////////////////////

	hind_damage.rh_wing_tip_mount = FALSE;

	////////////////////////////////////////

	////////////////////////////////////////

	hind_damage.rh_outer_pylon = FALSE;

	////////////////////////////////////////

	hind_damage.rh_inner_pylon = FALSE;

	////////////////////////////////////////

	hind_damage.lhs_chaff_dispensers = FALSE;

	////////////////////////////////////////

	hind_damage.rhs_chaff_dispensers = FALSE;

	////////////////////////////////////////

	hind_damage.lhs_flare_dispensers = FALSE;

	////////////////////////////////////////

	hind_damage.rhs_flare_dispensers = FALSE;

	////////////////////////////////////////

	set_hind_weapon_damage_status ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void partially_repair_hind_damage (void)
{
	set_hind_ekran_display_text ("", "", NULL, NULL);

	fire_extinguisher_used = FALSE;

	////////////////////////////////////////

	if (hind_damage.radar)
	{
		hind_damage.radar = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (hind_damage.dtv)
	{
		hind_damage.dtv = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (hind_damage.llltv)
	{
		hind_damage.llltv = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (hind_damage.laser_range_finder)
	{
		hind_damage.laser_range_finder = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (hind_damage.radar_jammer)
	{
		hind_damage.radar_jammer = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (hind_damage.infra_red_jammer)
	{
		hind_damage.infra_red_jammer = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (hind_damage.navigation_computer)
	{
		hind_damage.navigation_computer = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (hind_damage.communications)
	{
		hind_damage.communications = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (hind_damage.radar_warning_system)
	{
		hind_damage.radar_warning_system = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (hind_damage.head_up_display)
	{
		hind_damage.head_up_display = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (hind_damage.helmet_mounted_sight)
	{
		hind_damage.helmet_mounted_sight = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (hind_damage.tv_display)
	{
		hind_damage.tv_display = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (hind_damage.threat_warning_display)
	{
		hind_damage.threat_warning_display = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (hind_damage.night_vision_goggles)
	{
		hind_damage.night_vision_goggles = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (hind_damage.gun_jammed)
	{
		hind_damage.gun_jammed = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (hind_damage.lh_wing_tip_mount)
	{
		hind_damage.lh_wing_tip_mount = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (hind_damage.lh_outer_pylon)
	{
		hind_damage.lh_outer_pylon = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (hind_damage.lh_inner_pylon)
	{
		hind_damage.lh_inner_pylon = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (hind_damage.rh_wing_tip_mount)
	{
		hind_damage.rh_wing_tip_mount = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (hind_damage.rh_outer_pylon)
	{
		hind_damage.rh_outer_pylon = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (hind_damage.rh_inner_pylon)
	{
		hind_damage.rh_inner_pylon = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (hind_damage.lhs_chaff_dispensers)
	{
		hind_damage.lhs_chaff_dispensers = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (hind_damage.rhs_chaff_dispensers)
	{
		hind_damage.rhs_chaff_dispensers = frand1 () > 0.90;
	}

	////////////////////////////////////////
	if (hind_damage.lhs_flare_dispensers)
	{
		hind_damage.lhs_flare_dispensers = frand1 () > 0.90;
	}

	////////////////////////////////////////
	if (hind_damage.rhs_flare_dispensers)
	{
		hind_damage.rhs_flare_dispensers = frand1 () > 0.90;
	}

	////////////////////////////////////////

	set_hind_weapon_damage_status ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void repair_hind_weapon_damage (void)
{
	set_hind_ekran_display_text ("", "", NULL, NULL);

	hind_damage.gun_jammed		= FALSE;
	hind_damage.lh_wing_tip_mount	= FALSE;
	hind_damage.lh_outer_pylon	= FALSE;
	hind_damage.lh_inner_pylon	= FALSE;
	hind_damage.rh_wing_tip_mount	= FALSE;
	hind_damage.rh_outer_pylon	= FALSE;
	hind_damage.rh_inner_pylon	= FALSE;
	hind_damage.lhs_chaff_dispensers	= FALSE;
	hind_damage.lhs_flare_dispensers	= FALSE;
	hind_damage.rhs_chaff_dispensers	= FALSE;
	hind_damage.rhs_flare_dispensers	= FALSE;

	set_hind_weapon_damage_status ();
}
////Moje break
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void damage_systems (hind_damage_flags damage)
{
	entity
		*en = nullptr;

	en = get_gunship_entity ();

	////////////////////////////////////////

	if (damage.radar)
	{
		if (!hind_damage.radar)
		{
			activate_hind_master_caution_lamp ();

			hind_damage.radar = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_hind_ekran_display_text ("RADAR", "FAILURE", NULL, NULL);

			play_client_server_warning_message (en, SPEECH_SYSTEM_RADAR_FAILURE);

			if
			(
				(target_acquisition_system == TARGET_ACQUISITION_SYSTEM_GROUND_RADAR) ||
				(target_acquisition_system == TARGET_ACQUISITION_SYSTEM_AIR_RADAR)
			)
			{
				select_hind_target_acquisition_system (TARGET_ACQUISITION_SYSTEM_OFF);
			}
		}
	}

	////////////////////////////////////////

	if (damage.dtv)
	{
		if (!hind_damage.dtv)
		{
			activate_hind_master_caution_lamp ();

			hind_damage.dtv = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_hind_ekran_display_text ("DTV", "FAILURE", NULL, NULL);

			play_client_server_warning_message (en, SPEECH_SYSTEM_DTV_FAILURE);

			if (target_acquisition_system == TARGET_ACQUISITION_SYSTEM_DTV)
			{
				select_hind_target_acquisition_system (TARGET_ACQUISITION_SYSTEM_OFF);
			}
		}
	}

	////////////////////////////////////////

	if (damage.llltv)
	{
		if (!hind_damage.llltv)
		{
			activate_hind_master_caution_lamp ();

			hind_damage.llltv = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_hind_ekran_display_text ("LLLTV", "FAILURE", NULL, NULL);

			play_client_server_warning_message (en, SPEECH_SYSTEM_LLLTV_FAILURE);

			if (target_acquisition_system == TARGET_ACQUISITION_SYSTEM_LLLTV)
			{
				select_hind_target_acquisition_system (TARGET_ACQUISITION_SYSTEM_OFF);
			}
		}
	}

	////////////////////////////////////////

	if (damage.laser_range_finder)
	{
		if (!hind_damage.laser_range_finder)
		{
			activate_hind_master_caution_lamp ();

			hind_damage.laser_range_finder = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_hind_ekran_display_text ("LASER", "FAILURE", NULL, NULL);

			play_client_server_warning_message (en, SPEECH_SYSTEM_LASER_RANGE_FINDER_FAILURE);
		}
	}

	////////////////////////////////////////

	if (damage.radar_jammer)
	{
		if (!hind_damage.radar_jammer)
		{
			activate_hind_master_caution_lamp ();

			hind_damage.radar_jammer = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_hind_ekran_display_text ("RD JAMMER", "FAILURE", NULL, NULL);

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
		if (!hind_damage.infra_red_jammer)
		{
			activate_hind_master_caution_lamp ();

			hind_damage.infra_red_jammer = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_hind_ekran_display_text ("IR JAMMER", "FAILURE", NULL, NULL);

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
		if (!hind_damage.navigation_computer)
		{
			activate_hind_master_caution_lamp ();

			hind_damage.navigation_computer = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_hind_ekran_display_text ("NAV COMP", "FAILURE", NULL, NULL);

			play_client_server_warning_message (en, SPEECH_SYSTEM_NAV_COMPUTER_FAILURE);
		}
	}

	////////////////////////////////////////

	if (damage.communications)
	{
		if (!hind_damage.communications)
		{
			activate_hind_master_caution_lamp ();

			hind_damage.communications = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_hind_ekran_display_text ("COMMS", "FAILURE", NULL, NULL);

			play_client_server_warning_message (en, SPEECH_SYSTEM_COMMS_FAILURE);
		}
	}

	////////////////////////////////////////

	if (damage.radar_warning_system)
	{
		if (!hind_damage.radar_warning_system)
		{
			activate_hind_master_caution_lamp ();

			hind_damage.radar_warning_system = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_hind_ekran_display_text ("RWS", "FAILURE", NULL, NULL);

			play_client_server_warning_message (en, SPEECH_SYSTEM_RADAR_WARNING_FAILURE);
		}
	}

	////////////////////////////////////////

	if (get_global_avionics_realism_level () > AVIONICS_REALISM_LEVEL_SIMPLE)
	{
		if (damage.head_up_display)
		{
			if (!hind_damage.head_up_display)
			{
				activate_hind_master_caution_lamp ();

				hind_damage.head_up_display = TRUE;

				dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

				set_hind_ekran_display_text ("HUD", "FAILURE", NULL, NULL);

				play_client_server_warning_message (en, SPEECH_SYSTEM_HUD_FAILURE);
			}
		}
	}

	////////////////////////////////////////

	if (get_global_avionics_realism_level () > AVIONICS_REALISM_LEVEL_SIMPLE)
	{
		if (damage.helmet_mounted_sight)
		{
			if (!hind_damage.helmet_mounted_sight)
			{
				activate_hind_master_caution_lamp ();

				hind_damage.helmet_mounted_sight = TRUE;

				dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

				set_hind_ekran_display_text ("HMS", "FAILURE", NULL, NULL);

				play_client_server_warning_message (en, SPEECH_SYSTEM_HELMET_MOUNTED_SIGHT_FAILURE);

				if (target_acquisition_system == TARGET_ACQUISITION_SYSTEM_HMS)
				{
					select_hind_target_acquisition_system (TARGET_ACQUISITION_SYSTEM_OFF);
				}
			}
		}
	}

	////////////////////////////////////////

	if (damage.tv_display)
	{
		if (!hind_damage.tv_display)
		{
			activate_hind_master_caution_lamp ();

			hind_damage.tv_display = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_hind_ekran_display_text ("TV", "FAILURE", NULL, NULL);

			play_client_server_warning_message (en, SPEECH_SYSTEM_TV_DISPLAY_FAILURE);
		}
	}

	////////////////////////////////////////

	if (damage.threat_warning_display)
	{
		if (!hind_damage.threat_warning_display)
		{
			activate_hind_master_caution_lamp ();

			hind_damage.threat_warning_display = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_hind_ekran_display_text ("TWD", "FAILURE", NULL, NULL);

			play_client_server_warning_message (en, SPEECH_SYSTEM_THREAT_WARNING_DISPLAY_FAILURE);
		}
	}

	////////////////////////////////////////

	if (damage.night_vision_goggles)
	{
		if (!hind_damage.night_vision_goggles)
		{
			activate_hind_master_caution_lamp ();

			hind_damage.night_vision_goggles = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_hind_ekran_display_text ("NVG", "DAMAGED", NULL, NULL);

			play_client_server_warning_message (en, SPEECH_SYSTEM_NIGHT_VISION_GOGGLES_FAILURE);

			night_vision_system_active = FALSE;
		}
	}

	////////////////////////////////////////

	if (damage.gun_jammed)
	{
		if (!hind_damage.gun_jammed)
		{
			activate_hind_master_caution_lamp ();

			hind_damage.gun_jammed = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_hind_ekran_display_text ("GUN", "JAMMED", NULL, NULL);

			play_client_server_warning_message (en, SPEECH_SYSTEM_GUN_JAMMED);
		}
	}

	////////////////////////////////////////

	if (damage.lh_outer_pylon)
	{
		if (!hind_damage.lh_outer_pylon)
		{
			activate_hind_master_caution_lamp ();

			hind_damage.lh_outer_pylon = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_hind_ekran_display_text ("HARDPOINT", "DAMAGED", NULL, NULL);

			play_client_server_warning_message (en, SPEECH_SYSTEM_HARDPOINT_DAMAGED);
		}
	}

	////////////////////////////////////////

	if (damage.lh_inner_pylon)
	{
		if (!hind_damage.lh_inner_pylon)
		{
			activate_hind_master_caution_lamp ();

			hind_damage.lh_inner_pylon = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_hind_ekran_display_text ("HARDPOINT", "DAMAGED", NULL, NULL);

			play_client_server_warning_message (en, SPEECH_SYSTEM_HARDPOINT_DAMAGED);
		}
	}

	////////////////////////////////////////

	if (damage.rh_outer_pylon)
	{
		if (!hind_damage.rh_outer_pylon)
		{
			activate_hind_master_caution_lamp ();

			hind_damage.rh_outer_pylon = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_hind_ekran_display_text ("HARDPOINT", "DAMAGED", NULL, NULL);

			play_client_server_warning_message (en, SPEECH_SYSTEM_HARDPOINT_DAMAGED);
		}
	}

	////////////////////////////////////////

	if (damage.rh_inner_pylon)
	{
		if (!hind_damage.rh_inner_pylon)
		{
			activate_hind_master_caution_lamp ();

			hind_damage.rh_inner_pylon = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_hind_ekran_display_text ("HARDPOINT", "DAMAGED", NULL, NULL);

			play_client_server_warning_message (en, SPEECH_SYSTEM_HARDPOINT_DAMAGED);
		}
	}

	////////////////////////////////////////

	if (damage.lhs_chaff_dispensers)
	{
		if (!hind_damage.lhs_chaff_dispensers)
		{
			activate_hind_master_caution_lamp ();

			hind_damage.lhs_chaff_dispensers = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_hind_ekran_display_text ("CHAFF", "DAMAGED", NULL, NULL);

			play_client_server_warning_message (en, SPEECH_SYSTEM_CHAFF_DISPENSER_DAMAGED);
		}
	}

	////////////////////////////////////////

	if (damage.lhs_flare_dispensers)
	{
		if (!hind_damage.lhs_flare_dispensers)
		{
			activate_hind_master_caution_lamp ();

			hind_damage.lhs_flare_dispensers = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_hind_ekran_display_text ("FLARES", "DAMAGED", NULL, NULL);

			play_client_server_warning_message (en, SPEECH_SYSTEM_FLARE_DISPENSER_DAMAGED);
		}
	}
	////////////////////////////////////////

	if (damage.rhs_chaff_dispensers)
	{
		if (!hind_damage.rhs_chaff_dispensers)
		{
			activate_hind_master_caution_lamp ();

			hind_damage.rhs_chaff_dispensers = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_hind_ekran_display_text ("CHAFF", "DAMAGED", NULL, NULL);

			play_client_server_warning_message (en, SPEECH_SYSTEM_CHAFF_DISPENSER_DAMAGED);
		}
	}

	////////////////////////////////////////

	if (damage.rhs_flare_dispensers)
	{
		if (!hind_damage.rhs_flare_dispensers)
		{
			activate_hind_master_caution_lamp ();

			hind_damage.rhs_flare_dispensers = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_hind_ekran_display_text ("FLARES", "DAMAGED", NULL, NULL);

			play_client_server_warning_message (en, SPEECH_SYSTEM_FLARE_DISPENSER_DAMAGED);
		}
	}
	////////////////////////////////////////

	set_hind_weapon_damage_status ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void damage_hind (gunship_damage_levels damage_level)
{
	unsigned int
		damage;

	hind_damage_flags
		hind_damage;

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

	hind_damage.flags = damage;

	damage_systems (hind_damage);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_hind_avionics_of_dynamics_fault (unsigned int damage)
{
	if (damage & DYNAMICS_DAMAGE_MAIN_ROTOR)
	{
		activate_hind_master_caution_lamp ();

		set_hind_ekran_display_text ("MAIN RTR", "DAMAGED", NULL, NULL);
	}

	if (damage & DYNAMICS_DAMAGE_TAIL_ROTOR)
	{
		activate_hind_master_caution_lamp ();

		set_hind_ekran_display_text ("TAIL RTR", "DAMAGED", NULL, NULL);
	}

	if (damage & DYNAMICS_DAMAGE_LEFT_ENGINE)
	{
		activate_hind_master_caution_lamp ();

		set_hind_ekran_display_text ("ENGINE 1", "DAMAGED", NULL, NULL);
	}

	if (damage & DYNAMICS_DAMAGE_RIGHT_ENGINE)
	{
		activate_hind_master_caution_lamp ();

		set_hind_ekran_display_text ("ENGINE 2", "DAMAGED", NULL, NULL);
	}

	if (damage & DYNAMICS_DAMAGE_LEFT_ENGINE_FIRE)
	{
		activate_hind_master_caution_lamp ();

		set_hind_ekran_display_text ("ENGINE 1", "FIRE", NULL, NULL);
	}

	if (damage & DYNAMICS_DAMAGE_RIGHT_ENGINE_FIRE)
	{
		activate_hind_master_caution_lamp ();

		set_hind_ekran_display_text ("ENGINE 2", "FIRE", NULL, NULL);
	}

	if (damage & DYNAMICS_DAMAGE_LOW_HYDRAULICS)
	{
		activate_hind_master_caution_lamp ();

		set_hind_ekran_display_text ("LOW HYDRA", "PRESSURE", NULL, NULL);
	}

	if (damage & DYNAMICS_DAMAGE_SECONDARY_HYDRAULICS)
	{
		activate_hind_master_caution_lamp ();

		set_hind_ekran_display_text ("SEC HYDR", "FAILURE", NULL, NULL);
	}

	if (damage & DYNAMICS_DAMAGE_STABILISER)
	{
		activate_hind_master_caution_lamp ();

		set_hind_ekran_display_text ("STABILISR", "FAILURE", NULL, NULL);
	}

	if (damage & DYNAMICS_DAMAGE_FUEL_LEAK)
	{
		activate_hind_master_caution_lamp ();

		set_hind_ekran_display_text ("FUEL LEAK", "", NULL, NULL);
	}

	if (damage & DYNAMICS_DAMAGE_LOW_OIL_PRESSURE)
	{
		activate_hind_master_caution_lamp ();

		set_hind_ekran_display_text ("LOW OIL", "PRESSURE", NULL, NULL);
	}

	if (damage & DYNAMICS_DAMAGE_HIGH_OIL_PRESSURE)
	{
		activate_hind_master_caution_lamp ();

		set_hind_ekran_display_text ("HIGH OIL", "PRESSURE", NULL, NULL);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
