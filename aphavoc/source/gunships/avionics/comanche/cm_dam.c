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

comanche_damage_flags
	comanche_damage;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_comanche_weapon_damage_status (void)
{
	entity
		*en;

	entity_sub_types
		weapon_sub_type;

	en = get_gunship_entity ();

	set_client_server_entity_weapon_damage (en, COMANCHE_CANNON_TURRET, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, comanche_damage.gun_jammed);

	set_client_server_entity_weapon_damage (en, COMANCHE_LHS_STUB_WING, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, comanche_damage.lh_stub_wing_pylon);
	set_client_server_entity_weapon_damage (en, COMANCHE_LHS_BAY_DOOR_INNER, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, comanche_damage.lh_bay_door_inner_pylon);
	set_client_server_entity_weapon_damage (en, COMANCHE_LHS_BAY_DOOR_MIDDLE, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, comanche_damage.lh_bay_door_middle_pylon);
	set_client_server_entity_weapon_damage (en, COMANCHE_LHS_BAY_DOOR_OUTER, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, comanche_damage.lh_bay_door_outer_pylon);

	set_client_server_entity_weapon_damage (en, COMANCHE_RHS_STUB_WING, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, comanche_damage.rh_stub_wing_pylon);
	set_client_server_entity_weapon_damage (en, COMANCHE_RHS_BAY_DOOR_INNER, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, comanche_damage.rh_bay_door_inner_pylon);
	set_client_server_entity_weapon_damage (en, COMANCHE_RHS_BAY_DOOR_MIDDLE, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, comanche_damage.rh_bay_door_middle_pylon);
	set_client_server_entity_weapon_damage (en, COMANCHE_RHS_BAY_DOOR_OUTER, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON, comanche_damage.rh_bay_door_outer_pylon);

	set_client_server_entity_weapon_damage (en, COMANCHE_LHS_CHAFF_DISPENSER, ENTITY_SUB_TYPE_WEAPON_CHAFF, comanche_damage.chaff_dispensers);
	set_client_server_entity_weapon_damage (en, COMANCHE_RHS_CHAFF_DISPENSER, ENTITY_SUB_TYPE_WEAPON_CHAFF, comanche_damage.chaff_dispensers);

	set_client_server_entity_weapon_damage (en, COMANCHE_LHS_FLARE_DISPENSER, ENTITY_SUB_TYPE_WEAPON_FLARE, comanche_damage.flare_dispensers);
	set_client_server_entity_weapon_damage (en, COMANCHE_RHS_FLARE_DISPENSER, ENTITY_SUB_TYPE_WEAPON_FLARE, comanche_damage.flare_dispensers);

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

void fully_repair_comanche_damage (void)
{
	set_comanche_text_display_text ("", "");

	fire_extinguisher_used = FALSE;

	////////////////////////////////////////

	comanche_damage.radar = FALSE;

	////////////////////////////////////////

	comanche_damage.flir = FALSE;

	////////////////////////////////////////

	comanche_damage.dtv = FALSE;

	////////////////////////////////////////

	comanche_damage.dvo = FALSE;

	////////////////////////////////////////

	comanche_damage.laser_designator = FALSE;

	////////////////////////////////////////

	comanche_damage.radar_jammer = FALSE;

	////////////////////////////////////////

	comanche_damage.infra_red_jammer = FALSE;

	////////////////////////////////////////

	comanche_damage.navigation_computer = FALSE;

	////////////////////////////////////////

	comanche_damage.communications = FALSE;

	////////////////////////////////////////

	comanche_damage.radar_warning_system = FALSE;

	////////////////////////////////////////

	comanche_damage.hidss = FALSE;

	////////////////////////////////////////

	if (comanche_damage.pilot_lh_main_mfd)
	{
		comanche_damage.pilot_lh_main_mfd = FALSE;

		select_comanche_main_mfd_mode (COMANCHE_MAIN_MFD_MODE_OFF, COMANCHE_MAIN_MFD_LOCATION_PILOT_LHS);
	}

	////////////////////////////////////////

	if (comanche_damage.pilot_rh_main_mfd)
	{
		comanche_damage.pilot_rh_main_mfd = FALSE;

		select_comanche_main_mfd_mode (COMANCHE_MAIN_MFD_MODE_OFF, COMANCHE_MAIN_MFD_LOCATION_PILOT_RHS);
	}

	////////////////////////////////////////

	if (comanche_damage.pilot_lh_side_mfd)
	{
		comanche_damage.pilot_lh_side_mfd = FALSE;

		select_comanche_side_mfd_mode (COMANCHE_SIDE_MFD_MODE_OFF, COMANCHE_SIDE_MFD_LOCATION_PILOT_LHS);
	}

	////////////////////////////////////////

	if (comanche_damage.pilot_rh_side_mfd)
	{
		comanche_damage.pilot_rh_side_mfd = FALSE;

		select_comanche_side_mfd_mode (COMANCHE_SIDE_MFD_MODE_OFF, COMANCHE_SIDE_MFD_LOCATION_PILOT_RHS);
	}

	////////////////////////////////////////

	if (comanche_damage.co_pilot_lh_main_mfd)
	{
		comanche_damage.co_pilot_lh_main_mfd = FALSE;

		select_comanche_main_mfd_mode (COMANCHE_MAIN_MFD_MODE_OFF, COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_LHS);
	}

	////////////////////////////////////////

	if (comanche_damage.co_pilot_rh_main_mfd)
	{
		comanche_damage.co_pilot_rh_main_mfd = FALSE;

		select_comanche_main_mfd_mode (COMANCHE_MAIN_MFD_MODE_OFF, COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_RHS);
	}

	////////////////////////////////////////

	if (comanche_damage.co_pilot_lh_side_mfd)
	{
		comanche_damage.co_pilot_lh_side_mfd = FALSE;

		select_comanche_side_mfd_mode (COMANCHE_SIDE_MFD_MODE_OFF, COMANCHE_SIDE_MFD_LOCATION_CO_PILOT_LHS);
	}

	////////////////////////////////////////

	if (comanche_damage.co_pilot_rh_side_mfd)
	{
		comanche_damage.co_pilot_rh_side_mfd = FALSE;

		select_comanche_side_mfd_mode (COMANCHE_SIDE_MFD_MODE_OFF, COMANCHE_SIDE_MFD_LOCATION_CO_PILOT_RHS);
	}

	////////////////////////////////////////

	comanche_damage.pnvs = FALSE;

	////////////////////////////////////////

	comanche_damage.gun_jammed = FALSE;

	////////////////////////////////////////

	comanche_damage.lh_stub_wing_pylon = FALSE;

	////////////////////////////////////////

	comanche_damage.lh_bay_door_inner_pylon = FALSE;

	////////////////////////////////////////

	comanche_damage.lh_bay_door_middle_pylon = FALSE;

	////////////////////////////////////////

	comanche_damage.lh_bay_door_outer_pylon = FALSE;

	////////////////////////////////////////

	comanche_damage.rh_stub_wing_pylon = FALSE;

	////////////////////////////////////////

	comanche_damage.rh_bay_door_inner_pylon = FALSE;

	////////////////////////////////////////

	comanche_damage.rh_bay_door_middle_pylon = FALSE;

	////////////////////////////////////////

	comanche_damage.rh_bay_door_outer_pylon = FALSE;

	////////////////////////////////////////

	comanche_damage.chaff_dispensers = FALSE;

	////////////////////////////////////////

	comanche_damage.flare_dispensers = FALSE;

	////////////////////////////////////////

	set_comanche_weapon_damage_status ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void partially_repair_comanche_damage (void)
{
	set_comanche_text_display_text ("", "");

	fire_extinguisher_used = FALSE;

	////////////////////////////////////////

	if (comanche_damage.radar)
	{
		comanche_damage.radar = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (comanche_damage.flir)
	{
		comanche_damage.flir = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (comanche_damage.dtv)
	{
		comanche_damage.dtv = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (comanche_damage.dvo)
	{
		comanche_damage.dvo = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (comanche_damage.laser_designator)
	{
		comanche_damage.laser_designator = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (comanche_damage.radar_jammer)
	{
		comanche_damage.radar_jammer = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (comanche_damage.infra_red_jammer)
	{
		comanche_damage.infra_red_jammer = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (comanche_damage.navigation_computer)
	{
		comanche_damage.navigation_computer = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (comanche_damage.communications)
	{
		comanche_damage.communications = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (comanche_damage.radar_warning_system)
	{
		comanche_damage.radar_warning_system = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (comanche_damage.hidss)
	{
		comanche_damage.hidss = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (comanche_damage.pilot_lh_main_mfd)
	{
		comanche_damage.pilot_lh_main_mfd = frand1 () > 0.90;

		if (!comanche_damage.pilot_lh_main_mfd)
		{
			select_comanche_main_mfd_mode (COMANCHE_MAIN_MFD_MODE_OFF, COMANCHE_MAIN_MFD_LOCATION_PILOT_LHS);
		}
	}

	////////////////////////////////////////

	if (comanche_damage.pilot_rh_main_mfd)
	{
		comanche_damage.pilot_rh_main_mfd = frand1 () > 0.90;

		if (!comanche_damage.pilot_rh_main_mfd)
		{
			select_comanche_main_mfd_mode (COMANCHE_MAIN_MFD_MODE_OFF, COMANCHE_MAIN_MFD_LOCATION_PILOT_RHS);
		}
	}

	////////////////////////////////////////

	if (comanche_damage.pilot_lh_side_mfd)
	{
		comanche_damage.pilot_lh_side_mfd = frand1 () > 0.90;

		if (!comanche_damage.pilot_lh_side_mfd)
		{
			select_comanche_side_mfd_mode (COMANCHE_SIDE_MFD_MODE_OFF, COMANCHE_SIDE_MFD_LOCATION_PILOT_LHS);
		}
	}

	////////////////////////////////////////

	if (comanche_damage.pilot_rh_side_mfd)
	{
		comanche_damage.pilot_rh_side_mfd = frand1 () > 0.90;

		if (!comanche_damage.pilot_rh_side_mfd)
		{
			select_comanche_side_mfd_mode (COMANCHE_SIDE_MFD_MODE_OFF, COMANCHE_SIDE_MFD_LOCATION_PILOT_RHS);
		}
	}

	////////////////////////////////////////

	if (comanche_damage.co_pilot_lh_main_mfd)
	{
		comanche_damage.co_pilot_lh_main_mfd = frand1 () > 0.90;

		if (!comanche_damage.co_pilot_lh_main_mfd)
		{
			select_comanche_main_mfd_mode (COMANCHE_MAIN_MFD_MODE_OFF, COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_LHS);
		}
	}

	////////////////////////////////////////

	if (comanche_damage.co_pilot_rh_main_mfd)
	{
		comanche_damage.co_pilot_rh_main_mfd = frand1 () > 0.90;

		if (!comanche_damage.co_pilot_rh_main_mfd)
		{
			select_comanche_main_mfd_mode (COMANCHE_MAIN_MFD_MODE_OFF, COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_RHS);
		}
	}

	////////////////////////////////////////

	if (comanche_damage.co_pilot_lh_side_mfd)
	{
		comanche_damage.co_pilot_lh_side_mfd = frand1 () > 0.90;

		if (!comanche_damage.co_pilot_lh_side_mfd)
		{
			select_comanche_side_mfd_mode (COMANCHE_SIDE_MFD_MODE_OFF, COMANCHE_SIDE_MFD_LOCATION_CO_PILOT_LHS);
		}
	}

	////////////////////////////////////////

	if (comanche_damage.co_pilot_rh_side_mfd)
	{
		comanche_damage.co_pilot_rh_side_mfd = frand1 () > 0.90;

		if (!comanche_damage.co_pilot_rh_side_mfd)
		{
			select_comanche_side_mfd_mode (COMANCHE_SIDE_MFD_MODE_OFF, COMANCHE_SIDE_MFD_LOCATION_CO_PILOT_RHS);
		}
	}

	////////////////////////////////////////

	if (comanche_damage.pnvs)
	{
		comanche_damage.pnvs = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (comanche_damage.gun_jammed)
	{
		comanche_damage.gun_jammed = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (comanche_damage.lh_stub_wing_pylon)
	{
		comanche_damage.lh_stub_wing_pylon = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (comanche_damage.lh_bay_door_inner_pylon)
	{
		comanche_damage.lh_bay_door_inner_pylon = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (comanche_damage.lh_bay_door_middle_pylon)
	{
		comanche_damage.lh_bay_door_middle_pylon = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (comanche_damage.lh_bay_door_outer_pylon)
	{
		comanche_damage.lh_bay_door_outer_pylon = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (comanche_damage.rh_stub_wing_pylon)
	{
		comanche_damage.rh_stub_wing_pylon = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (comanche_damage.rh_bay_door_inner_pylon)
	{
		comanche_damage.rh_bay_door_inner_pylon = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (comanche_damage.rh_bay_door_middle_pylon)
	{
		comanche_damage.rh_bay_door_middle_pylon = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (comanche_damage.rh_bay_door_outer_pylon)
	{
		comanche_damage.rh_bay_door_outer_pylon = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (comanche_damage.chaff_dispensers)
	{
		comanche_damage.chaff_dispensers = frand1 () > 0.90;
	}

	////////////////////////////////////////

	if (comanche_damage.flare_dispensers)
	{
		comanche_damage.flare_dispensers = frand1 () > 0.90;
	}

	////////////////////////////////////////

	set_comanche_weapon_damage_status ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void repair_comanche_weapon_damage (void)
{
	set_comanche_text_display_text ("", "");

	comanche_damage.gun_jammed						= FALSE;
	comanche_damage.lh_stub_wing_pylon			= FALSE;
	comanche_damage.lh_bay_door_inner_pylon	= FALSE;
	comanche_damage.lh_bay_door_middle_pylon	= FALSE;
	comanche_damage.lh_bay_door_outer_pylon	= FALSE;
	comanche_damage.rh_stub_wing_pylon			= FALSE;
	comanche_damage.rh_bay_door_inner_pylon	= FALSE;
	comanche_damage.rh_bay_door_middle_pylon	= FALSE;
	comanche_damage.rh_bay_door_outer_pylon	= FALSE;
	comanche_damage.chaff_dispensers				= FALSE;
	comanche_damage.flare_dispensers				= FALSE;

	set_comanche_weapon_damage_status ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void damage_systems (comanche_damage_flags damage)
{
	entity
		*en;

	en = get_gunship_entity ();

	////////////////////////////////////////

	if (damage.radar)
	{
		if (!comanche_damage.radar)
		{
			activate_comanche_master_caution ();

			comanche_damage.radar = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_comanche_text_display_text ("RADAR FAILURE", "");

			play_client_server_warning_message (en, SPEECH_SYSTEM_RADAR_FAILURE);

			if
			(
				(target_acquisition_system == TARGET_ACQUISITION_SYSTEM_GROUND_RADAR) ||
				(target_acquisition_system == TARGET_ACQUISITION_SYSTEM_AIR_RADAR)
			)
			{
				select_comanche_target_acquisition_system (TARGET_ACQUISITION_SYSTEM_OFF);
			}
		}
	}

	////////////////////////////////////////

	if (damage.flir)
	{
		if (!comanche_damage.flir)
		{
			activate_comanche_master_caution ();

			comanche_damage.flir = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_comanche_text_display_text ("FLIR FAILURE", "");

			play_client_server_warning_message (en, SPEECH_SYSTEM_FLIR_FAILURE);

			if (target_acquisition_system == TARGET_ACQUISITION_SYSTEM_FLIR)
			{
				select_comanche_target_acquisition_system (TARGET_ACQUISITION_SYSTEM_OFF);
			}
		}
	}

	////////////////////////////////////////

	if (damage.dtv)
	{
		if (!comanche_damage.dtv)
		{
			activate_comanche_master_caution ();

			comanche_damage.dtv = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_comanche_text_display_text ("DTV FAILURE", "");

			play_client_server_warning_message (en, SPEECH_SYSTEM_DTV_FAILURE);

			if (target_acquisition_system == TARGET_ACQUISITION_SYSTEM_DTV)
			{
				select_comanche_target_acquisition_system (TARGET_ACQUISITION_SYSTEM_OFF);
			}
		}
	}

	////////////////////////////////////////

	//DVO REMOVED//
	/*
	if (damage.dvo)
	{
		if (!comanche_damage.dvo)
		{
			activate_comanche_master_caution ();

			comanche_damage.dvo = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_comanche_text_display_text ("DVO FAILURE", "");

			play_client_server_warning_message (en, SPEECH_SYSTEM_DVO_FAILURE);

			if (target_acquisition_system == TARGET_ACQUISITION_SYSTEM_DVO)
			{
				select_comanche_target_acquisition_system (TARGET_ACQUISITION_SYSTEM_OFF);
			}
		}
	}
	*/
	//DVO REMOVED//

	////////////////////////////////////////

	if (damage.laser_designator)
	{
		if (!comanche_damage.laser_designator)
		{
			activate_comanche_master_caution ();

			comanche_damage.laser_designator = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_comanche_text_display_text ("LASER DESIGNATOR", "FAILURE");

			play_client_server_warning_message (en, SPEECH_SYSTEM_LASER_DESIGNATOR_FAILURE);
		}
	}

	////////////////////////////////////////

	if (damage.radar_jammer)
	{
		if (!comanche_damage.radar_jammer)
		{
			activate_comanche_master_caution ();

			comanche_damage.radar_jammer = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_comanche_text_display_text ("RADAR JAMMER", "FAILURE");

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
		if (!comanche_damage.infra_red_jammer)
		{
			activate_comanche_master_caution ();

			comanche_damage.infra_red_jammer = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_comanche_text_display_text ("IR JAMMER", "FAILURE");

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
		if (!comanche_damage.navigation_computer)
		{
			activate_comanche_master_caution ();

			comanche_damage.navigation_computer = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_comanche_text_display_text ("NAV COMPUTER", "FAILURE");

			play_client_server_warning_message (en, SPEECH_SYSTEM_NAV_COMPUTER_FAILURE);
		}
	}

	////////////////////////////////////////

	if (damage.communications)
	{
		if (!comanche_damage.communications)
		{
			activate_comanche_master_caution ();

			comanche_damage.communications = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_comanche_text_display_text ("COMMS FAILURE", "");

			play_client_server_warning_message (en, SPEECH_SYSTEM_COMMS_FAILURE);
		}
	}

	////////////////////////////////////////

	if (damage.radar_warning_system)
	{
		if (!comanche_damage.radar_warning_system)
		{
			activate_comanche_master_caution ();

			comanche_damage.radar_warning_system = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_comanche_text_display_text ("RADAR WARNING", "FAILURE");

			play_client_server_warning_message (en, SPEECH_SYSTEM_RADAR_WARNING_FAILURE);
		}
	}

	////////////////////////////////////////

	if (!get_global_simple_avionics ())
	{
		if (damage.hidss)
		{
			if (!comanche_damage.hidss)
			{
				activate_comanche_master_caution ();

				comanche_damage.hidss = TRUE;

				dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

				set_comanche_text_display_text ("HIDSS FAILURE", "");

				play_client_server_warning_message (en, SPEECH_SYSTEM_HIDSS_FAILURE);

				if (target_acquisition_system == TARGET_ACQUISITION_SYSTEM_HIDSS)
				{
					select_comanche_target_acquisition_system (TARGET_ACQUISITION_SYSTEM_OFF);
				}
			}
		}
	}

	////////////////////////////////////////

	if (damage.pilot_lh_main_mfd)
	{
		if (!comanche_damage.pilot_lh_main_mfd)
		{
			activate_comanche_master_caution ();

			comanche_damage.pilot_lh_main_mfd = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_comanche_text_display_text ("MFD FAILURE", "");

			play_client_server_warning_message (en, SPEECH_SYSTEM_MFD_FAILURE);

			select_comanche_main_mfd_mode (COMANCHE_MAIN_MFD_MODE_DAMAGED, COMANCHE_MAIN_MFD_LOCATION_PILOT_LHS);
		}
	}

	////////////////////////////////////////

	if (damage.pilot_rh_main_mfd)
	{
		if (!comanche_damage.pilot_rh_main_mfd)
		{
			activate_comanche_master_caution ();

			comanche_damage.pilot_rh_main_mfd = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_comanche_text_display_text ("MFD FAILURE", "");

			play_client_server_warning_message (en, SPEECH_SYSTEM_MFD_FAILURE);

			select_comanche_main_mfd_mode (COMANCHE_MAIN_MFD_MODE_DAMAGED, COMANCHE_MAIN_MFD_LOCATION_PILOT_RHS);
		}
	}

	////////////////////////////////////////

	if (damage.pilot_lh_side_mfd)
	{
		if (!comanche_damage.pilot_lh_side_mfd)
		{
			activate_comanche_master_caution ();

			comanche_damage.pilot_lh_side_mfd = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_comanche_text_display_text ("MFD FAILURE", "");

			play_client_server_warning_message (en, SPEECH_SYSTEM_MFD_FAILURE);

			select_comanche_side_mfd_mode (COMANCHE_SIDE_MFD_MODE_DAMAGED, COMANCHE_SIDE_MFD_LOCATION_PILOT_LHS);
		}
	}

	////////////////////////////////////////

	if (damage.pilot_rh_side_mfd)
	{
		if (!comanche_damage.pilot_rh_side_mfd)
		{
			activate_comanche_master_caution ();

			comanche_damage.pilot_rh_side_mfd = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_comanche_text_display_text ("MFD FAILURE", "");

			play_client_server_warning_message (en, SPEECH_SYSTEM_MFD_FAILURE);

			select_comanche_side_mfd_mode (COMANCHE_SIDE_MFD_MODE_DAMAGED, COMANCHE_SIDE_MFD_LOCATION_PILOT_RHS);
		}
	}

	////////////////////////////////////////

	if (damage.co_pilot_lh_main_mfd)
	{
		if (!comanche_damage.co_pilot_lh_main_mfd)
		{
			activate_comanche_master_caution ();

			comanche_damage.co_pilot_lh_main_mfd = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_comanche_text_display_text ("MFD FAILURE", "");

			play_client_server_warning_message (en, SPEECH_SYSTEM_MFD_FAILURE);

			select_comanche_main_mfd_mode (COMANCHE_MAIN_MFD_MODE_DAMAGED, COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_LHS);
		}
	}

	////////////////////////////////////////

	if (damage.co_pilot_rh_main_mfd)
	{
		if (!comanche_damage.co_pilot_rh_main_mfd)
		{
			activate_comanche_master_caution ();

			comanche_damage.co_pilot_rh_main_mfd = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_comanche_text_display_text ("MFD FAILURE", "");

			play_client_server_warning_message (en, SPEECH_SYSTEM_MFD_FAILURE);

			select_comanche_main_mfd_mode (COMANCHE_MAIN_MFD_MODE_DAMAGED, COMANCHE_MAIN_MFD_LOCATION_CO_PILOT_RHS);
		}
	}

	////////////////////////////////////////

	if (damage.co_pilot_lh_side_mfd)
	{
		if (!comanche_damage.co_pilot_lh_side_mfd)
		{
			activate_comanche_master_caution ();

			comanche_damage.co_pilot_lh_side_mfd = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_comanche_text_display_text ("MFD FAILURE", "");

			play_client_server_warning_message (en, SPEECH_SYSTEM_MFD_FAILURE);

			select_comanche_side_mfd_mode (COMANCHE_SIDE_MFD_MODE_DAMAGED, COMANCHE_SIDE_MFD_LOCATION_CO_PILOT_LHS);
		}
	}

	////////////////////////////////////////

	if (damage.co_pilot_rh_side_mfd)
	{
		if (!comanche_damage.co_pilot_rh_side_mfd)
		{
			activate_comanche_master_caution ();

			comanche_damage.co_pilot_rh_side_mfd = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_comanche_text_display_text ("MFD FAILURE", "");

			play_client_server_warning_message (en, SPEECH_SYSTEM_MFD_FAILURE);

			select_comanche_side_mfd_mode (COMANCHE_SIDE_MFD_MODE_DAMAGED, COMANCHE_SIDE_MFD_LOCATION_CO_PILOT_RHS);
		}
	}

	////////////////////////////////////////

	if (damage.pnvs)
	{
		if (!comanche_damage.pnvs)
		{
			activate_comanche_master_caution ();

			comanche_damage.pnvs = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_comanche_text_display_text ("PNVS FAILURE", "");

			play_client_server_warning_message (en, SPEECH_SYSTEM_PNVS_FAILURE);

			night_vision_system_active = FALSE;
		}
	}

	////////////////////////////////////////

	if (damage.gun_jammed)
	{
		if (!comanche_damage.gun_jammed)
		{
			activate_comanche_master_caution ();

			comanche_damage.gun_jammed = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_comanche_text_display_text ("GUN JAMMED", "");

			play_client_server_warning_message (en, SPEECH_SYSTEM_GUN_JAMMED);
		}
	}

	////////////////////////////////////////

	if (damage.lh_stub_wing_pylon)
	{
		if (!comanche_damage.lh_stub_wing_pylon)
		{
			activate_comanche_master_caution ();

			comanche_damage.lh_stub_wing_pylon = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_comanche_text_display_text ("HARDPOINT DAMAGED", "");

			play_client_server_warning_message (en, SPEECH_SYSTEM_HARDPOINT_DAMAGED);
		}
	}

	////////////////////////////////////////

	if (damage.lh_bay_door_inner_pylon)
	{
		if (!comanche_damage.lh_bay_door_inner_pylon)
		{
			activate_comanche_master_caution ();

			comanche_damage.lh_bay_door_inner_pylon = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_comanche_text_display_text ("HARDPOINT DAMAGED", "");

			play_client_server_warning_message (en, SPEECH_SYSTEM_HARDPOINT_DAMAGED);
		}
	}

	////////////////////////////////////////

	if (damage.lh_bay_door_middle_pylon)
	{
		if (!comanche_damage.lh_bay_door_middle_pylon)
		{
			activate_comanche_master_caution ();

			comanche_damage.lh_bay_door_middle_pylon = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_comanche_text_display_text ("HARDPOINT DAMAGED", "");

			play_client_server_warning_message (en, SPEECH_SYSTEM_HARDPOINT_DAMAGED);
		}
	}

	////////////////////////////////////////

	if (damage.lh_bay_door_outer_pylon)
	{
		if (!comanche_damage.lh_bay_door_outer_pylon)
		{
			activate_comanche_master_caution ();

			comanche_damage.lh_bay_door_outer_pylon = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_comanche_text_display_text ("HARDPOINT DAMAGED", "");

			play_client_server_warning_message (en, SPEECH_SYSTEM_HARDPOINT_DAMAGED);
		}
	}

	////////////////////////////////////////

	if (damage.rh_stub_wing_pylon)
	{
		if (!comanche_damage.rh_stub_wing_pylon)
		{
			activate_comanche_master_caution ();

			comanche_damage.rh_stub_wing_pylon = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_comanche_text_display_text ("HARDPOINT DAMAGED", "");

			play_client_server_warning_message (en, SPEECH_SYSTEM_HARDPOINT_DAMAGED);
		}
	}

	////////////////////////////////////////

	if (damage.rh_bay_door_inner_pylon)
	{
		if (!comanche_damage.rh_bay_door_inner_pylon)
		{
			activate_comanche_master_caution ();

			comanche_damage.rh_bay_door_inner_pylon = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_comanche_text_display_text ("HARDPOINT DAMAGED", "");

			play_client_server_warning_message (en, SPEECH_SYSTEM_HARDPOINT_DAMAGED);
		}
	}

	////////////////////////////////////////

	if (damage.rh_bay_door_middle_pylon)
	{
		if (!comanche_damage.rh_bay_door_middle_pylon)
		{
			activate_comanche_master_caution ();

			comanche_damage.rh_bay_door_middle_pylon = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_comanche_text_display_text ("HARDPOINT DAMAGED", "");

			play_client_server_warning_message (en, SPEECH_SYSTEM_HARDPOINT_DAMAGED);
		}
	}

	////////////////////////////////////////

	if (damage.rh_bay_door_outer_pylon)
	{
		if (!comanche_damage.rh_bay_door_outer_pylon)
		{
			activate_comanche_master_caution ();

			comanche_damage.rh_bay_door_outer_pylon = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_comanche_text_display_text ("HARDPOINT DAMAGED", "");

			play_client_server_warning_message (en, SPEECH_SYSTEM_HARDPOINT_DAMAGED);
		}
	}

	////////////////////////////////////////

	if (damage.chaff_dispensers)
	{
		if (!comanche_damage.chaff_dispensers)
		{
			activate_comanche_master_caution ();

			comanche_damage.chaff_dispensers = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_comanche_text_display_text ("CHAFF DISPENSER", "DAMAGED");

			play_client_server_warning_message (en, SPEECH_SYSTEM_CHAFF_DISPENSER_DAMAGED);
		}
	}

	////////////////////////////////////////

	if (damage.flare_dispensers)
	{
		if (!comanche_damage.flare_dispensers)
		{
			activate_comanche_master_caution ();

			comanche_damage.flare_dispensers = TRUE;

			dynamics_damage_model (DYNAMICS_DAMAGE_AVIONICS, FALSE);

			set_comanche_text_display_text ("FLARE DISPENSER", "DAMAGED");

			play_client_server_warning_message (en, SPEECH_SYSTEM_FLARE_DISPENSER_DAMAGED);
		}
	}

	////////////////////////////////////////

	set_comanche_weapon_damage_status ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void damage_comanche (gunship_damage_levels damage_level)
{
	unsigned int
		damage;

	comanche_damage_flags
		comanche_damage;

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

	comanche_damage.flags = damage;

	damage_systems (comanche_damage);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void notify_comanche_avionics_of_dynamics_fault (unsigned int damage)
{
	if (damage & DYNAMICS_DAMAGE_MAIN_ROTOR)
	{
		activate_comanche_master_caution ();

		set_comanche_text_display_text ("MAIN ROTOR", "DAMAGED");
	}

	if (damage & DYNAMICS_DAMAGE_TAIL_ROTOR)
	{
		activate_comanche_master_caution ();

		set_comanche_text_display_text ("TAIL ROTOR", "DAMAGED");
	}

	if (damage & DYNAMICS_DAMAGE_LEFT_ENGINE)
	{
		activate_comanche_master_caution ();

		set_comanche_text_display_text ("LEFT ENGINE", "DAMAGED");
	}

	if (damage & DYNAMICS_DAMAGE_RIGHT_ENGINE)
	{
		activate_comanche_master_caution ();

		set_comanche_text_display_text ("RIGHT ENGINE", "DAMAGED");
	}

	if (damage & DYNAMICS_DAMAGE_LEFT_ENGINE_FIRE)
	{
		activate_comanche_master_caution ();

		set_comanche_text_display_text ("LEFT ENGINE FIRE", "");
	}

	if (damage & DYNAMICS_DAMAGE_RIGHT_ENGINE_FIRE)
	{
		activate_comanche_master_caution ();

		set_comanche_text_display_text ("RIGHT ENGINE FIRE", "");
	}

	if (damage & DYNAMICS_DAMAGE_LOW_HYDRAULICS)
	{
		activate_comanche_master_caution ();

		set_comanche_text_display_text ("HYDRAULICS", "PRESSURE LOW");
	}

	if (damage & DYNAMICS_DAMAGE_STABILISER)
	{
		activate_comanche_master_caution ();

		set_comanche_text_display_text ("STABILISER", "FAILURE");
	}

	if (damage & DYNAMICS_DAMAGE_FUEL_LEAK)
	{
		activate_comanche_master_caution ();

		set_comanche_text_display_text ("FUEL LEAK", "");
	}

	if (damage & DYNAMICS_DAMAGE_LOW_OIL_PRESSURE)
	{
		activate_comanche_master_caution ();

		set_comanche_text_display_text ("LOW OIL", "PRESSURE");
	}

	if (damage & DYNAMICS_DAMAGE_HIGH_OIL_PRESSURE)
	{
		activate_comanche_master_caution ();

		set_comanche_text_display_text ("HIGH OIL", "PRESSURE");
	}

	if (damage & DYNAMICS_DAMAGE_UNDERCARRIAGE)
	{
		activate_comanche_master_caution ();

		set_comanche_text_display_text ("GEAR DAMAGED", "");
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
