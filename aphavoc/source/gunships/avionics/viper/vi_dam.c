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

viper_damage_flags
	viper_damage;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_viper_weapon_damage_status (void)
{
	entity
		*en;

	entity_sub_types
		weapon_sub_type;

	en = get_gunship_entity ();


	set_client_server_entity_weapon_damage (en, COBRA_CANNON_TURRET, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, viper_damage.gun_jammed);

	set_client_server_entity_weapon_damage (en, VIPER_LHS_WING_TIP_MOUNT, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, viper_damage.lh_wing_tip_mount);
	set_client_server_entity_weapon_damage (en, VIPER_LHS_OUTER_PYLON, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, viper_damage.lh_outer_pylon);
	set_client_server_entity_weapon_damage (en, VIPER_LHS_INNER_PYLON, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, viper_damage.lh_inner_pylon);

	set_client_server_entity_weapon_damage (en, VIPER_RHS_WING_TIP_MOUNT, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, viper_damage.rh_wing_tip_mount);
	set_client_server_entity_weapon_damage (en, VIPER_RHS_OUTER_PYLON, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, viper_damage.rh_outer_pylon);
	set_client_server_entity_weapon_damage (en, VIPER_RHS_INNER_PYLON, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, viper_damage.rh_inner_pylon);

	set_client_server_entity_weapon_damage (en, VIPER_LFHS_CHAFF_DISPENSER, ENTITY_SUB_TYPE_WEAPON_CHAFF, viper_damage.chaff_dispenser);
	set_client_server_entity_weapon_damage (en, VIPER_LBHS_CHAFF_DISPENSER, ENTITY_SUB_TYPE_WEAPON_CHAFF, viper_damage.chaff_dispenser);
	set_client_server_entity_weapon_damage (en, VIPER_RFHS_CHAFF_DISPENSER, ENTITY_SUB_TYPE_WEAPON_CHAFF, viper_damage.chaff_dispenser);
	set_client_server_entity_weapon_damage (en, VIPER_RBHS_CHAFF_DISPENSER, ENTITY_SUB_TYPE_WEAPON_CHAFF, viper_damage.chaff_dispenser);
	set_client_server_entity_weapon_damage (en, VIPER_LFHS_FLARE_DISPENSER, ENTITY_SUB_TYPE_WEAPON_FLARE, viper_damage.flare_dispenser);
	set_client_server_entity_weapon_damage (en, VIPER_LBHS_FLARE_DISPENSER, ENTITY_SUB_TYPE_WEAPON_FLARE, viper_damage.flare_dispenser);
	set_client_server_entity_weapon_damage (en, VIPER_RFHS_FLARE_DISPENSER, ENTITY_SUB_TYPE_WEAPON_FLARE, viper_damage.flare_dispenser);
	set_client_server_entity_weapon_damage (en, VIPER_RBHS_FLARE_DISPENSER, ENTITY_SUB_TYPE_WEAPON_FLARE, viper_damage.flare_dispenser);

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

void fully_repair_viper_damage (void)
{
	fire_extinguisher_used = FALSE;

	////////////////////////////////////////

	viper_damage.flir = FALSE;

	////////////////////////////////////////

	viper_damage.dtv = FALSE;

	////////////////////////////////////////

	viper_damage.laser_designator = FALSE;

	////////////////////////////////////////

	viper_damage.radar_jammer = FALSE;

	////////////////////////////////////////

	viper_damage.infra_red_jammer = FALSE;

	////////////////////////////////////////

	viper_damage.navigation_computer = FALSE;

	////////////////////////////////////////

	viper_damage.communications = FALSE;

	////////////////////////////////////////

	viper_damage.radar_warning_system = FALSE;

	////////////////////////////////////////

	viper_damage.hidss = FALSE;

	////////////////////////////////////////

	if (viper_damage.pilot_lh_mfd)
	{
		viper_damage.pilot_lh_mfd = FALSE;

		select_viper_mfd_mode (VIPER_MFD_MODE_OFF, VIPER_MFD_LOCATION_PILOT_LHS);
	}

	////////////////////////////////////////

	if (viper_damage.pilot_rh_mfd)
	{
		viper_damage.pilot_rh_mfd = FALSE;

		select_viper_mfd_mode (VIPER_MFD_MODE_OFF, VIPER_MFD_LOCATION_PILOT_RHS);
	}

	////////////////////////////////////////

	if (viper_damage.co_pilot_lh_mfd)
	{
		viper_damage.co_pilot_lh_mfd = FALSE;

		select_viper_mfd_mode (VIPER_MFD_MODE_OFF, VIPER_MFD_LOCATION_PILOT_LHS);
	}

	////////////////////////////////////////

	if (viper_damage.co_pilot_rh_mfd)
	{
		viper_damage.co_pilot_rh_mfd = FALSE;

		select_viper_mfd_mode (VIPER_MFD_MODE_OFF, VIPER_MFD_LOCATION_PILOT_RHS);
	}

	////////////////////////////////////////

	if (viper_damage.pilot_dfd)
	{
		viper_damage.pilot_dfd = FALSE;

		select_viper_mfd_mode (VIPER_MFD_MODE_OFF, VIPER_MFD_LOCATION_PILOT_DFD);
	}

	////////////////////////////////////////

	if (viper_damage.co_pilot_dfd)
	{
		viper_damage.co_pilot_dfd = FALSE;

		select_viper_mfd_mode (VIPER_MFD_MODE_OFF, VIPER_MFD_LOCATION_CO_PILOT_DFD);
	}

	////////////////////////////////////////

	viper_damage.pnvs = FALSE;

	////////////////////////////////////////

	viper_damage.gun_jammed = FALSE;

	////////////////////////////////////////

	viper_damage.lh_wing_tip_mount = FALSE;

	////////////////////////////////////////

	viper_damage.lh_outer_pylon = FALSE;

	////////////////////////////////////////

	viper_damage.lh_inner_pylon = FALSE;

	////////////////////////////////////////

	viper_damage.rh_wing_tip_mount = FALSE;

	////////////////////////////////////////

	viper_damage.rh_outer_pylon = FALSE;

	////////////////////////////////////////

	viper_damage.rh_inner_pylon = FALSE;

	////////////////////////////////////////

	viper_damage.chaff_dispenser = FALSE;

	////////////////////////////////////////

	viper_damage.flare_dispenser = FALSE;

	////////////////////////////////////////

	set_viper_weapon_damage_status ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void partially_repair_viper_damage (void)
{
	fire_extinguisher_used = FALSE;

	////////////////////////////////////////

	if (viper_damage.flir)
	{
		viper_damage.flir = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (viper_damage.dtv)
	{
		viper_damage.dtv = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (viper_damage.laser_designator)
	{
		viper_damage.laser_designator = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (viper_damage.radar_jammer)
	{
		viper_damage.radar_jammer = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (viper_damage.infra_red_jammer)
	{
		viper_damage.infra_red_jammer = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (viper_damage.navigation_computer)
	{
		viper_damage.navigation_computer = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (viper_damage.communications)
	{
		viper_damage.communications = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (viper_damage.radar_warning_system)
	{
		viper_damage.radar_warning_system = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (viper_damage.hidss)
	{
		viper_damage.hidss = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (viper_damage.pilot_lh_mfd)
	{
		viper_damage.pilot_lh_mfd = frand1 () > 0.90;

		if (!viper_damage.pilot_lh_mfd)
		{
			select_viper_mfd_mode (VIPER_MFD_MODE_OFF, VIPER_MFD_LOCATION_PILOT_LHS);
		}
	}

	////////////////////////////////////////

	if (viper_damage.pilot_rh_mfd)
	{
		viper_damage.pilot_rh_mfd = frand1 () > 0.90;

		if (!viper_damage.pilot_rh_mfd)
		{
			select_viper_mfd_mode (VIPER_MFD_MODE_OFF, VIPER_MFD_LOCATION_PILOT_RHS);
		}
	}

	////////////////////////////////////////

	if (viper_damage.co_pilot_lh_mfd)
	{
		viper_damage.co_pilot_lh_mfd = frand1 () > 0.90;

		if (!viper_damage.co_pilot_lh_mfd)
		{
			select_viper_mfd_mode (VIPER_MFD_MODE_OFF, VIPER_MFD_LOCATION_CO_PILOT_LHS);
		}
	}

	////////////////////////////////////////

	if (viper_damage.co_pilot_rh_mfd)
	{
		viper_damage.co_pilot_rh_mfd = frand1 () > 0.90;

		if (!viper_damage.co_pilot_rh_mfd)
		{
			select_viper_mfd_mode (VIPER_MFD_MODE_OFF, VIPER_MFD_LOCATION_CO_PILOT_RHS);
		}
	}

	////////////////////////////////////////

	if (viper_damage.pilot_dfd)
	{
		viper_damage.pilot_dfd = frand1 () > 0.90;

		if (!viper_damage.pilot_dfd)
		{
			select_viper_mfd_mode (VIPER_MFD_MODE_OFF, VIPER_MFD_LOCATION_PILOT_DFD);
		}
	}

	////////////////////////////////////////

	if (viper_damage.co_pilot_dfd)
	{
		viper_damage.co_pilot_dfd = frand1 () > 0.90;

		if (!viper_damage.co_pilot_dfd)
		{
			select_viper_mfd_mode (VIPER_MFD_MODE_OFF, VIPER_MFD_LOCATION_PILOT_DFD);
		}
	}

	////////////////////////////////////////

	if (viper_damage.pnvs)
	{
		viper_damage.pnvs = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (viper_damage.gun_jammed)
	{
		viper_damage.gun_jammed = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (viper_damage.lh_wing_tip_mount)
	{
		viper_damage.lh_wing_tip_mount = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (viper_damage.lh_outer_pylon)
	{
		viper_damage.lh_outer_pylon = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (viper_damage.lh_inner_pylon)
	{
		viper_damage.lh_inner_pylon = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (viper_damage.rh_wing_tip_mount)
	{
		viper_damage.rh_wing_tip_mount = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (viper_damage.rh_outer_pylon)
	{
		viper_damage.rh_outer_pylon = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (viper_damage.rh_inner_pylon)
	{
		viper_damage.rh_inner_pylon = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (viper_damage.chaff_dispenser)
	{
		viper_damage.chaff_dispenser = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (viper_damage.flare_dispenser)
	{
		viper_damage.flare_dispenser = frand1 () > 0.90;
	}

	////////////////////////////////////////

	set_viper_weapon_damage_status ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void repair_viper_weapon_damage (void)
{
	viper_damage.gun_jammed			= FALSE;
	viper_damage.lh_wing_tip_mount	= FALSE;
	viper_damage.lh_outer_pylon		= FALSE;
	viper_damage.lh_inner_pylon		= FALSE;
	viper_damage.rh_wing_tip_mount	= FALSE;
	viper_damage.rh_outer_pylon		= FALSE;
	viper_damage.rh_inner_pylon		= FALSE;
	viper_damage.chaff_dispenser		= FALSE;
	viper_damage.flare_dispenser		= FALSE;

	set_viper_weapon_damage_status ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void damage_systems (viper_damage_flags damage)
{
	entity
		*en;

	en = get_gunship_entity ();

	////////////////////////////////////////

	if (damage.flir)
	{
		if (!viper_damage.flir)
		{
			activate_viper_master_caution ();

			viper_damage.flir = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			play_client_server_warning_message (en, SPEECH_SYSTEM_FLIR_FAILURE);

			if (target_acquisition_system == TARGET_ACQUISITION_SYSTEM_FLIR)
			{
				select_viper_target_acquisition_system (TARGET_ACQUISITION_SYSTEM_OFF);
			}
		}
	}

	////////////////////////////////////////

	if (damage.dtv)
	{
		if (!viper_damage.dtv)
		{
			activate_viper_master_caution ();

			viper_damage.dtv = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			play_client_server_warning_message (en, SPEECH_SYSTEM_DTV_FAILURE);

			if (target_acquisition_system == TARGET_ACQUISITION_SYSTEM_DTV)
			{
				select_viper_target_acquisition_system (TARGET_ACQUISITION_SYSTEM_OFF);
			}
		}
	}

	////////////////////////////////////////

	if (damage.laser_designator)
	{
		if (!viper_damage.laser_designator)
		{
			activate_viper_master_caution ();

			viper_damage.laser_designator = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_laser_is_active(FALSE);

			play_client_server_warning_message (en, SPEECH_SYSTEM_LASER_DESIGNATOR_FAILURE);
		}
	}

	////////////////////////////////////////

	if (damage.radar_jammer)
	{
		if (!viper_damage.radar_jammer)
		{
			activate_viper_master_caution ();

			viper_damage.radar_jammer = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

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
		if (!viper_damage.infra_red_jammer)
		{
			activate_viper_master_caution ();

			viper_damage.infra_red_jammer = TRUE;

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
		if (!viper_damage.navigation_computer)
		{
			activate_viper_master_caution ();

			viper_damage.navigation_computer = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			play_client_server_warning_message (en, SPEECH_SYSTEM_NAV_COMPUTER_FAILURE);
		}
	}

	////////////////////////////////////////

	if (damage.communications)
	{
		if (!viper_damage.communications)
		{
			activate_viper_master_caution ();

			viper_damage.communications = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			play_client_server_warning_message (en, SPEECH_SYSTEM_COMMS_FAILURE);
		}
	}

	////////////////////////////////////////

	if (damage.radar_warning_system)
	{
		if (!viper_damage.radar_warning_system)
		{
			activate_viper_master_caution ();

			viper_damage.radar_warning_system = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			play_client_server_warning_message (en, SPEECH_SYSTEM_RADAR_WARNING_FAILURE);
		}
	}

	////////////////////////////////////////

	if (!get_global_simple_avionics ())
	{
		if (damage.hidss)
		{
			if (!viper_damage.hidss)
			{
				activate_viper_master_caution ();

				viper_damage.hidss = TRUE;

				dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

				play_client_server_warning_message (en, SPEECH_SYSTEM_HIDSS_FAILURE);

				if (target_acquisition_system == TARGET_ACQUISITION_SYSTEM_HIDSS)
				{
					select_viper_target_acquisition_system (TARGET_ACQUISITION_SYSTEM_OFF);
				}
			}
		}
	}

	////////////////////////////////////////

	if (damage.pilot_lh_mfd)
	{
		if (!viper_damage.pilot_lh_mfd)
		{
			activate_viper_master_caution ();

			viper_damage.pilot_lh_mfd = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			play_client_server_warning_message (en, SPEECH_SYSTEM_MFD_FAILURE);

			select_viper_mfd_mode (VIPER_MFD_MODE_DAMAGED, VIPER_MFD_LOCATION_PILOT_LHS);
		}
	}

	////////////////////////////////////////

	if (damage.pilot_rh_mfd)
	{
		if (!viper_damage.pilot_rh_mfd)
		{
			activate_viper_master_caution ();

			viper_damage.pilot_rh_mfd = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			play_client_server_warning_message (en, SPEECH_SYSTEM_MFD_FAILURE);

			select_viper_mfd_mode (VIPER_MFD_MODE_DAMAGED, VIPER_MFD_LOCATION_PILOT_RHS);
		}
	}

	////////////////////////////////////////

	if (damage.co_pilot_lh_mfd)
	{
		if (!viper_damage.co_pilot_lh_mfd)
		{
			activate_viper_master_caution ();

			viper_damage.co_pilot_lh_mfd = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			play_client_server_warning_message (en, SPEECH_SYSTEM_MFD_FAILURE);

			select_viper_mfd_mode (VIPER_MFD_MODE_DAMAGED, VIPER_MFD_LOCATION_CO_PILOT_LHS);
		}
	}

	////////////////////////////////////////

	if (damage.co_pilot_rh_mfd)
	{
		if (!viper_damage.co_pilot_rh_mfd)
		{
			activate_viper_master_caution ();

			viper_damage.co_pilot_rh_mfd = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			play_client_server_warning_message (en, SPEECH_SYSTEM_MFD_FAILURE);

			select_viper_mfd_mode (VIPER_MFD_MODE_DAMAGED, VIPER_MFD_LOCATION_CO_PILOT_RHS);
		}
	}

	////////////////////////////////////////

	if (damage.pilot_dfd)
	{
		if (!viper_damage.pilot_dfd)
		{
			activate_viper_master_caution ();

			viper_damage.pilot_dfd = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			play_client_server_warning_message (en, SPEECH_SYSTEM_MFD_FAILURE);

			select_viper_mfd_mode (VIPER_MFD_MODE_DAMAGED, VIPER_MFD_LOCATION_PILOT_DFD);
		}
	}

	////////////////////////////////////////

	if (damage.co_pilot_dfd)
	{
		if (!viper_damage.co_pilot_dfd)
		{
			activate_viper_master_caution ();

			viper_damage.co_pilot_dfd = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			play_client_server_warning_message (en, SPEECH_SYSTEM_MFD_FAILURE);

			select_viper_mfd_mode (VIPER_MFD_MODE_DAMAGED, VIPER_MFD_LOCATION_CO_PILOT_DFD);
		}
	}

	////////////////////////////////////////

	if (damage.pnvs)
	{
		if (!viper_damage.pnvs)
		{
			activate_viper_master_caution ();

			viper_damage.pnvs = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			play_client_server_warning_message (en, SPEECH_SYSTEM_PNVS_FAILURE);

			night_vision_system_active = FALSE;
		}
	}

	////////////////////////////////////////

	if (damage.gun_jammed)
	{
		if (!viper_damage.gun_jammed)
		{
			activate_viper_master_caution ();

			viper_damage.gun_jammed = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			play_client_server_warning_message (en, SPEECH_SYSTEM_GUN_JAMMED);
		}
	}

	////////////////////////////////////////

	if (damage.lh_wing_tip_mount)
	{
		if (!viper_damage.lh_wing_tip_mount)
		{
			activate_viper_master_caution ();

			viper_damage.lh_wing_tip_mount = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			play_client_server_warning_message (en, SPEECH_SYSTEM_HARDPOINT_DAMAGED);
		}
	}

	////////////////////////////////////////

	if (damage.lh_outer_pylon)
	{
		if (!viper_damage.lh_outer_pylon)
		{
			activate_viper_master_caution ();

			viper_damage.lh_outer_pylon = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			play_client_server_warning_message (en, SPEECH_SYSTEM_HARDPOINT_DAMAGED);
		}
	}

	////////////////////////////////////////

	if (damage.lh_inner_pylon)
	{
		if (!viper_damage.lh_inner_pylon)
		{
			activate_viper_master_caution ();

			viper_damage.lh_inner_pylon = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			play_client_server_warning_message (en, SPEECH_SYSTEM_HARDPOINT_DAMAGED);
		}
	}

	////////////////////////////////////////

	if (damage.rh_wing_tip_mount)
	{
		if (!viper_damage.rh_wing_tip_mount)
		{
			activate_viper_master_caution ();

			viper_damage.rh_wing_tip_mount = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			play_client_server_warning_message (en, SPEECH_SYSTEM_HARDPOINT_DAMAGED);
		}
	}

	////////////////////////////////////////

	if (damage.rh_outer_pylon)
	{
		if (!viper_damage.rh_outer_pylon)
		{
			activate_viper_master_caution ();

			viper_damage.rh_outer_pylon = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			play_client_server_warning_message (en, SPEECH_SYSTEM_HARDPOINT_DAMAGED);
		}
	}

	////////////////////////////////////////

	if (damage.rh_inner_pylon)
	{
		if (!viper_damage.rh_inner_pylon)
		{
			activate_viper_master_caution ();

			viper_damage.rh_inner_pylon = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			play_client_server_warning_message (en, SPEECH_SYSTEM_HARDPOINT_DAMAGED);
		}
	}

	////////////////////////////////////////

	if (damage.chaff_dispenser)
	{
		if (!viper_damage.chaff_dispenser)
		{
			activate_viper_master_caution ();

			viper_damage.chaff_dispenser = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			play_client_server_warning_message (en, SPEECH_SYSTEM_CHAFF_DISPENSER_DAMAGED);
		}
	}

	////////////////////////////////////////

	if (damage.flare_dispenser)
	{
		if (!viper_damage.flare_dispenser)
		{
			activate_viper_master_caution ();

			viper_damage.flare_dispenser = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			play_client_server_warning_message (en, SPEECH_SYSTEM_FLARE_DISPENSER_DAMAGED);
		}
	}

	////////////////////////////////////////

	set_viper_weapon_damage_status ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void damage_viper (gunship_damage_levels damage_level)
{
	unsigned int
		damage;

	viper_damage_flags
		viper_damage;

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

	viper_damage.flags = damage;

	damage_systems (viper_damage);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_viper_avionics_of_dynamics_fault (unsigned int damage)
{
	if (damage & DYNAMICS_DAMAGE_MAIN_ROTOR)
	{
		activate_viper_master_caution ();
	}

	if (damage & DYNAMICS_DAMAGE_TAIL_ROTOR)
	{
		activate_viper_master_caution ();
	}

	if (damage & DYNAMICS_DAMAGE_LEFT_ENGINE)
	{
		activate_viper_master_caution ();
	}

	if (damage & DYNAMICS_DAMAGE_RIGHT_ENGINE)
	{
		activate_viper_master_caution ();
	}

	if (damage & DYNAMICS_DAMAGE_LEFT_ENGINE_FIRE)
	{
		activate_viper_master_caution ();
	}

	if (damage & DYNAMICS_DAMAGE_RIGHT_ENGINE_FIRE)
	{
		activate_viper_master_caution ();
	}

	if (damage & DYNAMICS_DAMAGE_LOW_HYDRAULICS)
	{
		activate_viper_master_caution ();
	}

	if (damage & DYNAMICS_DAMAGE_SECONDARY_HYDRAULICS)
	{
		activate_viper_master_caution ();
	}

	if (damage & DYNAMICS_DAMAGE_STABILISER)
	{
		activate_viper_master_caution ();
	}

	if (damage & DYNAMICS_DAMAGE_FUEL_LEAK)
	{
		activate_viper_master_caution ();
	}

	if (damage & DYNAMICS_DAMAGE_LOW_OIL_PRESSURE)
	{
		activate_viper_master_caution ();
	}

	if (damage & DYNAMICS_DAMAGE_HIGH_OIL_PRESSURE)
	{
		activate_viper_master_caution ();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
