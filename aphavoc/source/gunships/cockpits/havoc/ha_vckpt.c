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

static object_3d_instance
	*virtual_cockpit_level1_inst3d,
	*virtual_cockpit_level2_inst3d,
	*virtual_cockpit_level3_inst3d,
	*virtual_cockpit_fillet_level1_inst3d,
	*virtual_cockpit_fillet_level2_inst3d,
	*virtual_cockpit_fillet_level3_inst3d,
#ifndef OGRE_EE
	*virtual_cockpit_hud_glass_inst3d,
#endif
	*virtual_cockpit_hud_glass_level1_inst3d,
	*virtual_cockpit_hud_glass_level2_inst3d,
	*virtual_cockpit_hud_glass_level3_inst3d,
#ifndef OGRE_EE
	*virtual_cockpit_large_hud_glass_inst3d,
#endif
	*virtual_cockpit_large_hud_glass_level1_inst3d,
	*virtual_cockpit_large_hud_glass_level2_inst3d,
	*virtual_cockpit_large_hud_glass_level3_inst3d,
	*virtual_cockpit_hud_display_inst3d,
	*virtual_cockpit_main_rotor_inst3d,
	*virtual_cockpit_large_hud_main_rotor_inst3d,
	*virtual_cockpit_adi_inst3d,
#ifndef OGRE_EE
	*virtual_cockpit_hsi_inst3d,
#endif
	*virtual_cockpit_hsi_level1_inst3d,
	*virtual_cockpit_hsi_level2_inst3d,
	*virtual_cockpit_hsi_direction_finder_inst3d,
	*virtual_cockpit_hsi_flight_path_inst3d,
	*virtual_cockpit_hsi_drift_inst3d,
	*virtual_cockpit_ekran_display_inst3d,
	*virtual_cockpit_crt_display_inst3d,
#ifndef OGRE_EE
	*virtual_cockpit_compass_inst3d,
#endif
	*virtual_cockpit_compass_level1_inst3d,
	*virtual_cockpit_compass_level2_inst3d,
	*virtual_cockpit_instrument_needles_inst3d;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//TODO make Havoc threat lamps
#ifndef OGRE_EE
static object_3d_sub_instance
#else
static struct OgreGameObjectSceneElement
#endif
	*rwr_above_light,
	*rwr_airborne_light,
	*rwr_below_light,
	*rwr_left10_light,
	*rwr_left30_light,
	*rwr_left50_light,
	*rwr_left90_light,
	*rwr_left_rear_light,
	*rwr_long_range_light,
	*rwr_medium_range_light,
	*rwr_missile_launch_light,
	*rwr_right10_light,
	*rwr_right30_light,
	*rwr_right50_light,
	*rwr_right90_light,
	*rwr_right_rear_light,
	*rwr_short_range_light,
	*rwr_signal_strength1,
	*rwr_signal_strength10,
	*rwr_signal_strength11,
	*rwr_signal_strength12,
	*rwr_signal_strength13,
	*rwr_signal_strength14,
	*rwr_signal_strength15,
	*rwr_signal_strength2,
	*rwr_signal_strength3,
	*rwr_signal_strength4,
	*rwr_signal_strength5,
	*rwr_signal_strength6,
	*rwr_signal_strength7,
	*rwr_signal_strength8,
	*rwr_signal_strength9,

	// Status Lamps
	*radar_lmp,
	*flir_lmp,
	*llltv_lmp,
	*lsr_lmp,
	*rjam_lmp,
	*ijam_lmp,
	*nav_comp_lmp,
	*comm_lmp,
	*rws_lmp,
	*hud_lmp,
	*hms_lmp,
	*tv_disp_lmp,
	*tw_disp_lmp,
	*nvg_lmp,
	*fire_ex_lmp,
	*rtr_brk_lmp,
	*whl_brk_lmp,
	*acm_lmp,

	// Warning Lamps
	*leng_warn_lamp,
	*reng_warn_lamp,
	*trq_warn_lamp,
	*rdr_warn_lamp,
	*ap_warn_lamp,
	*hvr_warn_lamp,
	*rjam_warn_lamp,
	*ijam_warn_lamp,
	*mast_caut_lamp,

	// Weapon Status Lamps
	*chaff_lamp,
	*flare_lamp,
	*chaff_dmg_lamp,
	*flare_dmg_lamp;

#ifndef OGRE_EE
static void update_threat_warning_lights(void);
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_havoc_virtual_cockpit (void)
{
	//
	// 3D instances
	//

	virtual_cockpit_inst3d = NULL;

	pilot_head_pitch_datum = 0.0;

	co_pilot_head_pitch_datum = 0.0;

	virtual_cockpit_level1_inst3d = construct_3d_object (OBJECT_3D_HAVOC_VIRTUAL_COCKPIT_LEVEL1);

	virtual_cockpit_level2_inst3d = construct_3d_object (OBJECT_3D_HAVOC_VIRTUAL_COCKPIT_LEVEL2);

	virtual_cockpit_level3_inst3d = construct_3d_object (OBJECT_3D_HAVOC_VIRTUAL_COCKPIT_LEVEL3);

	virtual_cockpit_fillet_level1_inst3d = construct_3d_object (OBJECT_3D_HAVOC_VIRTUAL_COCKPIT_LEVEL1_FILLET);

	virtual_cockpit_fillet_level2_inst3d = construct_3d_object (OBJECT_3D_HAVOC_VIRTUAL_COCKPIT_LEVEL2_FILLET);

	virtual_cockpit_fillet_level3_inst3d = construct_3d_object (OBJECT_3D_HAVOC_VIRTUAL_COCKPIT_LEVEL3_FILLET);

	virtual_cockpit_hud_glass_level1_inst3d = construct_3d_object (OBJECT_3D_HAVOC_VIRTUAL_COCKPIT_HUD_GLASS_LEVEL1);

	virtual_cockpit_hud_glass_level2_inst3d = construct_3d_object (OBJECT_3D_HAVOC_VIRTUAL_COCKPIT_HUD_GLASS_LEVEL2);

	virtual_cockpit_hud_glass_level3_inst3d = construct_3d_object (OBJECT_3D_HAVOC_VIRTUAL_COCKPIT_HUD_GLASS_LEVEL3);

	virtual_cockpit_large_hud_glass_level1_inst3d = construct_3d_object (OBJECT_3D_HAVOC_VIRTUAL_COCKPIT_LARGE_HUD_GLASS_LEVEL1);

	virtual_cockpit_large_hud_glass_level2_inst3d = construct_3d_object (OBJECT_3D_HAVOC_VIRTUAL_COCKPIT_LARGE_HUD_GLASS_LEVEL2);

	virtual_cockpit_large_hud_glass_level3_inst3d = construct_3d_object (OBJECT_3D_HAVOC_VIRTUAL_COCKPIT_LARGE_HUD_GLASS_LEVEL3);

	virtual_cockpit_hud_display_inst3d = construct_3d_object (OBJECT_3D_HAVOC_VIRTUAL_COCKPIT_HUD_DISPLAY);

	virtual_cockpit_main_rotor_inst3d = construct_3d_object (OBJECT_3D_HAVOC_VIRTUAL_COCKPIT_MAIN_ROTOR);

	virtual_cockpit_large_hud_main_rotor_inst3d = construct_3d_object (OBJECT_3D_HAVOC_VIRTUAL_COCKPIT_MAIN_ROTOR_HUD);

	virtual_cockpit_adi_inst3d = construct_3d_object (OBJECT_3D_HAVOC_VIRTUAL_COCKPIT_INSTRUMENTS_ADI);

	virtual_cockpit_hsi_level1_inst3d = construct_3d_object (OBJECT_3D_HAVOC_VIRTUAL_COCKPIT_INSTRUMENTS_HSI_LEVEL1);

	virtual_cockpit_hsi_level2_inst3d = construct_3d_object (OBJECT_3D_HAVOC_VIRTUAL_COCKPIT_INSTRUMENTS_HSI_LEVEL2);

	virtual_cockpit_hsi_direction_finder_inst3d = construct_3d_object (OBJECT_3D_HAVOC_VIRTUAL_COCKPIT_INSTRUMENTS_HSI_ARROW_LONG);

	virtual_cockpit_hsi_flight_path_inst3d = construct_3d_object (OBJECT_3D_HAVOC_VIRTUAL_COCKPIT_INSTRUMENTS_HSI_ARROW_DOUBLE);

	virtual_cockpit_hsi_drift_inst3d = construct_3d_object (OBJECT_3D_HAVOC_VIRTUAL_COCKPIT_INSTRUMENTS_HSI_ARROW_SHORT);

	virtual_cockpit_ekran_display_inst3d = construct_3d_object (OBJECT_3D_HAVOC_VIRTUAL_COCKPIT_DISPLAYS_EKRAN);

	virtual_cockpit_crt_display_inst3d = construct_3d_object (OBJECT_3D_HAVOC_VIRTUAL_COCKPIT_DISPLAYS_CRT);

	virtual_cockpit_compass_level1_inst3d = construct_3d_object (OBJECT_3D_HAVOC_VIRTUAL_COCKPIT_INSTRUMENTS_COMPASS_LEVEL1);

	virtual_cockpit_compass_level2_inst3d = construct_3d_object (OBJECT_3D_HAVOC_VIRTUAL_COCKPIT_INSTRUMENTS_COMPASS_LEVEL2);

	virtual_cockpit_instrument_needles_inst3d = construct_3d_object (OBJECT_3D_HAVOC_VIRTUAL_COCKPIT_INSTRUMENT_NEEDLES);

	rwr_above_light = find_sub_object(virtual_cockpit_instrument_needles_inst3d, OBJECT_3D_SUB_OBJECT_RWR_ABOVE_LIGHT);
	rwr_airborne_light = find_sub_object(virtual_cockpit_instrument_needles_inst3d, OBJECT_3D_SUB_OBJECT_RWR_AIRBORNE_LIGHT);
	rwr_below_light = find_sub_object(virtual_cockpit_instrument_needles_inst3d, OBJECT_3D_SUB_OBJECT_RWR_BELOW_LIGHT);
	rwr_left10_light = find_sub_object(virtual_cockpit_instrument_needles_inst3d, OBJECT_3D_SUB_OBJECT_RWR_LEFT10_LIGHT);
	rwr_left30_light = find_sub_object(virtual_cockpit_instrument_needles_inst3d, OBJECT_3D_SUB_OBJECT_RWR_LEFT30_LIGHT);
	rwr_left50_light = find_sub_object(virtual_cockpit_instrument_needles_inst3d, OBJECT_3D_SUB_OBJECT_RWR_LEFT50_LIGHT);
	rwr_left90_light = find_sub_object(virtual_cockpit_instrument_needles_inst3d, OBJECT_3D_SUB_OBJECT_RWR_LEFT90_LIGHT);
	rwr_left_rear_light = find_sub_object(virtual_cockpit_instrument_needles_inst3d, OBJECT_3D_SUB_OBJECT_RWR_LEFT_REAR_LIGHT);
	rwr_long_range_light = find_sub_object(virtual_cockpit_instrument_needles_inst3d, OBJECT_3D_SUB_OBJECT_RWR_LONG_RANGE_LIGHT);
	rwr_medium_range_light = find_sub_object(virtual_cockpit_instrument_needles_inst3d, OBJECT_3D_SUB_OBJECT_RWR_MEDIUM_RANGE_LIGHT);
	rwr_missile_launch_light = find_sub_object(virtual_cockpit_instrument_needles_inst3d, OBJECT_3D_SUB_OBJECT_RWR_MISSILE_LAUNCH_LIGHT);
	rwr_right10_light = find_sub_object(virtual_cockpit_instrument_needles_inst3d, OBJECT_3D_SUB_OBJECT_RWR_RIGHT10_LIGHT);
	rwr_right30_light = find_sub_object(virtual_cockpit_instrument_needles_inst3d, OBJECT_3D_SUB_OBJECT_RWR_RIGHT30_LIGHT);
	rwr_right50_light = find_sub_object(virtual_cockpit_instrument_needles_inst3d, OBJECT_3D_SUB_OBJECT_RWR_RIGHT50_LIGHT);
	rwr_right90_light = find_sub_object(virtual_cockpit_instrument_needles_inst3d, OBJECT_3D_SUB_OBJECT_RWR_RIGHT90_LIGHT);
	rwr_right_rear_light = find_sub_object(virtual_cockpit_instrument_needles_inst3d, OBJECT_3D_SUB_OBJECT_RWR_RIGHT_REAR_LIGHT);
	rwr_short_range_light = find_sub_object(virtual_cockpit_instrument_needles_inst3d, OBJECT_3D_SUB_OBJECT_RWR_SHORT_RANGE_LIGHT);
	rwr_signal_strength1 = find_sub_object(virtual_cockpit_instrument_needles_inst3d, OBJECT_3D_SUB_OBJECT_RWR_SIGNAL_STRENGTH1_LIGHT);
	rwr_signal_strength10 = find_sub_object(virtual_cockpit_instrument_needles_inst3d, OBJECT_3D_SUB_OBJECT_RWR_SIGNAL_STRENGTH10_LIGHT);
	rwr_signal_strength11 = find_sub_object(virtual_cockpit_instrument_needles_inst3d, OBJECT_3D_SUB_OBJECT_RWR_SIGNAL_STRENGTH11_LIGHT);
	rwr_signal_strength12 = find_sub_object(virtual_cockpit_instrument_needles_inst3d, OBJECT_3D_SUB_OBJECT_RWR_SIGNAL_STRENGTH12_LIGHT);
	rwr_signal_strength13 = find_sub_object(virtual_cockpit_instrument_needles_inst3d, OBJECT_3D_SUB_OBJECT_RWR_SIGNAL_STRENGTH13_LIGHT);
	rwr_signal_strength14 = find_sub_object(virtual_cockpit_instrument_needles_inst3d, OBJECT_3D_SUB_OBJECT_RWR_SIGNAL_STRENGTH14_LIGHT);
	rwr_signal_strength15 = find_sub_object(virtual_cockpit_instrument_needles_inst3d, OBJECT_3D_SUB_OBJECT_RWR_SIGNAL_STRENGTH15_LIGHT);
	rwr_signal_strength2 = find_sub_object(virtual_cockpit_instrument_needles_inst3d, OBJECT_3D_SUB_OBJECT_RWR_SIGNAL_STRENGTH2_LIGHT);
	rwr_signal_strength3 = find_sub_object(virtual_cockpit_instrument_needles_inst3d, OBJECT_3D_SUB_OBJECT_RWR_SIGNAL_STRENGTH3_LIGHT);
	rwr_signal_strength4 = find_sub_object(virtual_cockpit_instrument_needles_inst3d, OBJECT_3D_SUB_OBJECT_RWR_SIGNAL_STRENGTH4_LIGHT);
	rwr_signal_strength5 = find_sub_object(virtual_cockpit_instrument_needles_inst3d, OBJECT_3D_SUB_OBJECT_RWR_SIGNAL_STRENGTH5_LIGHT);
	rwr_signal_strength6 = find_sub_object(virtual_cockpit_instrument_needles_inst3d, OBJECT_3D_SUB_OBJECT_RWR_SIGNAL_STRENGTH6_LIGHT);
	rwr_signal_strength7 = find_sub_object(virtual_cockpit_instrument_needles_inst3d, OBJECT_3D_SUB_OBJECT_RWR_SIGNAL_STRENGTH7_LIGHT);
	rwr_signal_strength8 = find_sub_object(virtual_cockpit_instrument_needles_inst3d, OBJECT_3D_SUB_OBJECT_RWR_SIGNAL_STRENGTH8_LIGHT);
	rwr_signal_strength9 = find_sub_object(virtual_cockpit_instrument_needles_inst3d, OBJECT_3D_SUB_OBJECT_RWR_SIGNAL_STRENGTH9_LIGHT);

	// Status Lamps
	radar_lmp = find_sub_object(virtual_cockpit_instrument_needles_inst3d, OBJECT_3D_SUB_OBJECT_HAVOC_RDR_LAMP);
	flir_lmp = find_sub_object(virtual_cockpit_instrument_needles_inst3d, OBJECT_3D_SUB_OBJECT_HAVOC_FLIR_LAMP);
	llltv_lmp = find_sub_object(virtual_cockpit_instrument_needles_inst3d, OBJECT_3D_SUB_OBJECT_HAVOC_LLLTV_LAMP);
	lsr_lmp = find_sub_object(virtual_cockpit_instrument_needles_inst3d, OBJECT_3D_SUB_OBJECT_HAVOC_LSR_LAMP);
	rjam_lmp = find_sub_object(virtual_cockpit_instrument_needles_inst3d, OBJECT_3D_SUB_OBJECT_HAVOC_RJAM_LAMP);
	ijam_lmp = find_sub_object(virtual_cockpit_instrument_needles_inst3d, OBJECT_3D_SUB_OBJECT_HAVOC_IJAM_LAMP);
	nav_comp_lmp = find_sub_object(virtual_cockpit_instrument_needles_inst3d, OBJECT_3D_SUB_OBJECT_HAVOC_NAV_LAMP);
	comm_lmp = find_sub_object(virtual_cockpit_instrument_needles_inst3d, OBJECT_3D_SUB_OBJECT_HAVOC_COMM_LAMP);
	rws_lmp = find_sub_object(virtual_cockpit_instrument_needles_inst3d, OBJECT_3D_SUB_OBJECT_HAVOC_RWS_LAMP);
	hud_lmp = find_sub_object(virtual_cockpit_instrument_needles_inst3d, OBJECT_3D_SUB_OBJECT_HAVOC_HUD_LAMP);
	hms_lmp = find_sub_object(virtual_cockpit_instrument_needles_inst3d, OBJECT_3D_SUB_OBJECT_HAVOC_HMS_LAMP);
	tv_disp_lmp = find_sub_object(virtual_cockpit_instrument_needles_inst3d, OBJECT_3D_SUB_OBJECT_HAVOC_TV_LAMP);
	tw_disp_lmp = find_sub_object(virtual_cockpit_instrument_needles_inst3d, OBJECT_3D_SUB_OBJECT_HAVOC_TWD_LAMP);
	nvg_lmp = find_sub_object(virtual_cockpit_instrument_needles_inst3d, OBJECT_3D_SUB_OBJECT_HAVOC_NVG_LAMP);
	fire_ex_lmp = find_sub_object(virtual_cockpit_instrument_needles_inst3d, OBJECT_3D_SUB_OBJECT_HAVOC_FRX_LAMP);
	rtr_brk_lmp = find_sub_object(virtual_cockpit_instrument_needles_inst3d, OBJECT_3D_SUB_OBJECT_HAVOC_RTR_BRK_LAMP);
	whl_brk_lmp = find_sub_object(virtual_cockpit_instrument_needles_inst3d, OBJECT_3D_SUB_OBJECT_HAVOC_WL_BRK_LAMP);
	acm_lmp = find_sub_object(virtual_cockpit_instrument_needles_inst3d, OBJECT_3D_SUB_OBJECT_HAVOC_AC_LAMP);

	// Warning Lamps
	leng_warn_lamp = find_sub_object(virtual_cockpit_instrument_needles_inst3d, OBJECT_3D_SUB_OBJECT_HAVOC_LENG_WARN_LAMP);
	reng_warn_lamp = find_sub_object(virtual_cockpit_instrument_needles_inst3d, OBJECT_3D_SUB_OBJECT_HAVOC_RENG_WARN_LAMP);
	trq_warn_lamp = find_sub_object(virtual_cockpit_instrument_needles_inst3d, OBJECT_3D_SUB_OBJECT_HAVOC_TRQ_WARN_LAMP);
	rdr_warn_lamp = find_sub_object(virtual_cockpit_instrument_needles_inst3d, OBJECT_3D_SUB_OBJECT_HAVOC_RDR_WARN_LAMP);
	ap_warn_lamp = find_sub_object(virtual_cockpit_instrument_needles_inst3d, OBJECT_3D_SUB_OBJECT_HAVOC_AP_WARN_LAMP);
	hvr_warn_lamp = find_sub_object(virtual_cockpit_instrument_needles_inst3d, OBJECT_3D_SUB_OBJECT_HAVOC_HVR_WARN_LAMP);
	rjam_warn_lamp = find_sub_object(virtual_cockpit_instrument_needles_inst3d, OBJECT_3D_SUB_OBJECT_HAVOC_RJAM_WARN_LAMP);
	ijam_warn_lamp = find_sub_object(virtual_cockpit_instrument_needles_inst3d, OBJECT_3D_SUB_OBJECT_HAVOC_IJAM_WARN_LAMP);
	mast_caut_lamp = find_sub_object(virtual_cockpit_instrument_needles_inst3d, OBJECT_3D_SUB_OBJECT_HAVOC_MSTR_CAUT_LAMP);

	// Weapon Status Lamps
	chaff_lamp = find_sub_object(virtual_cockpit_instrument_needles_inst3d, OBJECT_3D_SUB_OBJECT_HAVOC_CHAFF_LAMP);
	flare_lamp = find_sub_object(virtual_cockpit_instrument_needles_inst3d, OBJECT_3D_SUB_OBJECT_HAVOC_FLARE_LAMP);
	chaff_dmg_lamp = find_sub_object(virtual_cockpit_instrument_needles_inst3d, OBJECT_3D_SUB_OBJECT_HAVOC_CHAFF_DMG_LAMP);
	flare_dmg_lamp = find_sub_object(virtual_cockpit_instrument_needles_inst3d, OBJECT_3D_SUB_OBJECT_HAVOC_FLARE_DMG_LAMP);

	//
	// wipers and rain
	//

	initialise_havoc_virtual_cockpit_wiper_and_rain_effect ();

	//
	// virtual cockpit cameras
	//

	initialise_common_virtual_cockpit_cameras ();

//VJ 050208 cleaing up wideview
	wide_cockpit_nr = WIDEVIEW_HAVOC_PILOT;
//VJ wideview mod, date: 20-mar-03
//start up in normal view because when you switch to wideview the parameters are read
	set_global_wide_cockpit(FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_havoc_virtual_cockpit (void)
{
	//
	// 3D instances
	//

	destruct_3d_object (virtual_cockpit_level1_inst3d);

	destruct_3d_object (virtual_cockpit_level2_inst3d);

	destruct_3d_object (virtual_cockpit_level3_inst3d);

	destruct_3d_object (virtual_cockpit_fillet_level1_inst3d);

	destruct_3d_object (virtual_cockpit_fillet_level2_inst3d);

	destruct_3d_object (virtual_cockpit_fillet_level3_inst3d);

	destruct_3d_object (virtual_cockpit_hud_glass_level1_inst3d);

	destruct_3d_object (virtual_cockpit_hud_glass_level2_inst3d);

	destruct_3d_object (virtual_cockpit_hud_glass_level3_inst3d);

	destruct_3d_object (virtual_cockpit_large_hud_glass_level1_inst3d);

	destruct_3d_object (virtual_cockpit_large_hud_glass_level2_inst3d);

	destruct_3d_object (virtual_cockpit_large_hud_glass_level3_inst3d);

	destruct_3d_object (virtual_cockpit_hud_display_inst3d);

	destruct_3d_object (virtual_cockpit_main_rotor_inst3d);

	destruct_3d_object (virtual_cockpit_large_hud_main_rotor_inst3d);

	destruct_3d_object (virtual_cockpit_adi_inst3d);

	destruct_3d_object (virtual_cockpit_hsi_level1_inst3d);

	destruct_3d_object (virtual_cockpit_hsi_level2_inst3d);

	destruct_3d_object (virtual_cockpit_hsi_direction_finder_inst3d);

	destruct_3d_object (virtual_cockpit_hsi_flight_path_inst3d);

	destruct_3d_object (virtual_cockpit_hsi_drift_inst3d);

	destruct_3d_object (virtual_cockpit_ekran_display_inst3d);

	destruct_3d_object (virtual_cockpit_crt_display_inst3d);

	destruct_3d_object (virtual_cockpit_compass_level1_inst3d);

	destruct_3d_object (virtual_cockpit_compass_level2_inst3d);

	destruct_3d_object(virtual_cockpit_instrument_needles_inst3d);

	//
	// wipers and rain
	//

	deinitialise_havoc_virtual_cockpit_wiper_and_rain_effect ();

	//
	// virtual cockpit cameras
	//

	deinitialise_common_virtual_cockpit_cameras ();

	clear_head_movement_data();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_havoc_virtual_cockpit (void)
{
	#ifndef OGRE_EE
	update_threat_warning_lights();
	update_status_lamps();
	update_warning_lamps();
	update_chaff_flare_status_lamps();
	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef OGRE_EE
static void set_cockpit_lighting (matrix3x3 attitude)
{
	matrix3x3
		directional_light_rotation,
		result;

	vec3d
		directional_light_direction;

	light_colour
		ambient_light_colour,
		directional_light_colour;

	float
		directional_light_heading,
		directional_light_pitch,
		directional_light_roll;

	switch (get_local_entity_int_value (get_session_entity (), INT_TYPE_DAY_SEGMENT_TYPE))
	{
		////////////////////////////////////////
		case DAY_SEGMENT_TYPE_DAWN:
		////////////////////////////////////////
		{
			ambient_light_colour.red		 		= 0.0;
			ambient_light_colour.green		  		= 0.0;
			ambient_light_colour.blue		  		= 0.0;

			directional_light_colour.red			= 1.0;
			directional_light_colour.green		= 0.574;
			directional_light_colour.blue			= 0.0;

			directional_light_heading 				= rad (0.0);
			directional_light_pitch 				= rad (-15.0);
			directional_light_roll 					= rad (0.0);

			break;
		}
		////////////////////////////////////////
		case DAY_SEGMENT_TYPE_DAY:
		////////////////////////////////////////
		{
			ambient_light_colour.red		 		= 0.0;
			ambient_light_colour.green		  		= 0.0;
			ambient_light_colour.blue		  		= 0.0;

			directional_light_colour.red			= 1.0;
			directional_light_colour.green		= 1.0;
			directional_light_colour.blue			= 1.0;

			directional_light_heading 				= rad (0.0);
			directional_light_pitch 				= rad (-30.0);
			directional_light_roll 					= rad (0.0);

			break;
		}
		////////////////////////////////////////
		case DAY_SEGMENT_TYPE_DUSK:
		////////////////////////////////////////
		{
			ambient_light_colour.red		 		= 0.0;
			ambient_light_colour.green		  		= 0.0;
			ambient_light_colour.blue		  		= 0.0;

			directional_light_colour.red			= 1.0;
			directional_light_colour.green		= 0.574;
			directional_light_colour.blue			= 0.0;

			directional_light_heading 				= rad (0.0);
			directional_light_pitch 				= rad (-15.0);
			directional_light_roll 					= rad (0.0);

			break;
		}
		////////////////////////////////////////
		case DAY_SEGMENT_TYPE_NIGHT:
		////////////////////////////////////////
		{
			ambient_light_colour.red		 		= 0.0;
			ambient_light_colour.green		  		= 0.0;
			ambient_light_colour.blue		  		= 0.0;

			directional_light_colour.red			= 1.0;
			directional_light_colour.green		= 0.703;
			directional_light_colour.blue			= 0.0;

			directional_light_heading 				= rad (0.0);
			directional_light_pitch 				= rad (-15.0);
			directional_light_roll 					= rad (0.0);

			break;
		}
	}

	#if DEMO_VERSION

	ambient_light_colour.red		 		= 0.0;
	ambient_light_colour.green		  		= 0.0;
	ambient_light_colour.blue		  		= 0.0;

	directional_light_colour.red			= 1.0;
	directional_light_colour.green		= 1.0;
	directional_light_colour.blue			= 1.0;

	directional_light_heading 				= rad (0.0);
	directional_light_pitch 				= rad (-30.0);
	directional_light_roll 					= rad (0.0);

	#endif

	set_3d_ambient_light (main_3d_single_light_env, &ambient_light_colour);

	get_3d_transformation_matrix (directional_light_rotation, directional_light_heading, directional_light_pitch, directional_light_roll);

	multiply_matrix3x3_matrix3x3 (result, directional_light_rotation, attitude);

	directional_light_direction.x = -result[2][0];
	directional_light_direction.y = -result[2][1];
	directional_light_direction.z = -result[2][2];

	set_3d_main_light_source (main_3d_single_light_env, &directional_light_colour, &directional_light_direction, FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void get_display_viewpoint (view_modes mode, viewpoint *display_viewpoint)
{
	object_3d_sub_object_index_numbers
		index;

	object_3d_sub_object_search_data
		search;

	viewpoint
		vp;

	ASSERT (display_viewpoint);

	if (mode == VIEW_MODE_COCKPIT_PANEL_SPECIAL_HAVOC_TV)
	{
		index = OBJECT_3D_SUB_OBJECT_HAVOC_COCKPIT_CRT_CAMERA;
	}
	else if (mode == VIEW_MODE_COCKPIT_PANEL_SPECIAL_HAVOC_HUD)
	{
		index = OBJECT_3D_SUB_OBJECT_HAVOC_COCKPIT_HUD_CAMERA;
	}
	else
	{
		debug_fatal ("Invalid view mode = %d", mode);
	}

	virtual_cockpit_inst3d = virtual_cockpit_level1_inst3d;

	search.search_depth = 0;
	search.search_object = virtual_cockpit_inst3d;
	search.sub_object_index = index;

	if (find_object_3d_sub_object (&search) != SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		debug_fatal ("Failed to locate display viewpoint in virtual cockpit");
	}

	virtual_cockpit_inst3d->vp.position.x = 0.0;
	virtual_cockpit_inst3d->vp.position.y = 0.0;
	virtual_cockpit_inst3d->vp.position.z = 0.0;

	get_local_entity_attitude_matrix (get_gunship_entity (), virtual_cockpit_inst3d->vp.attitude);

	get_3d_sub_object_world_viewpoint (&search, &vp);

	get_local_entity_vec3d (get_gunship_entity (), VEC3D_TYPE_POSITION, &main_vp.position);

	main_vp.x += vp.x;
	main_vp.y += vp.y;
	main_vp.z += vp.z;

	memcpy (main_vp.attitude, vp.attitude, sizeof (matrix3x3));

	vp.x = -vp.x;
	vp.y = -vp.y;
	vp.z = -vp.z;

	multiply_transpose_matrix3x3_vec3d (&virtual_cockpit_inst3d->vp.position, vp.attitude, &vp.position);

	memcpy (display_viewpoint, &virtual_cockpit_inst3d->vp, sizeof (viewpoint));
}
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_havoc_internal_virtual_cockpit (unsigned int flags)
{
#ifndef OGRE_EE
	viewpoint
		vp;

	object_3d_sub_object_search_data
		search;

	object_3d_instance
		*virtual_cockpit_inst3d;

	////////////////////////////////////////
	//
	// virtual cockpit viewpoint is placed at the main object origin
	//
	////////////////////////////////////////

	if (get_view_mode () == VIEW_MODE_COCKPIT_PANEL_SPECIAL_HAVOC_TV)
	{
		get_display_viewpoint (VIEW_MODE_COCKPIT_PANEL_SPECIAL_HAVOC_TV, &vp);
	}
	else if (get_view_mode () == VIEW_MODE_COCKPIT_PANEL_SPECIAL_HAVOC_HUD)
	{
		get_display_viewpoint (VIEW_MODE_COCKPIT_PANEL_SPECIAL_HAVOC_HUD, &vp);
	}
	else
	{
		matrix3x3 head_rotation;
		vec3d vp_position, vp_world_position;

		vp_position.x = 0.0;
		vp_position.y = 0.0;
		vp_position.z = 0.0;

//VJ wideview mod, date: 18-mar-03
		if (get_global_wide_cockpit ())
		{
		   vp_position.x = wide_cockpit_position[wide_cockpit_nr].c.x;
		   vp_position.y = wide_cockpit_position[wide_cockpit_nr].c.y;
		   vp_position.z = wide_cockpit_position[wide_cockpit_nr].c.z;
			//VJ 050207 included head pitch in fixed view setting
			pilot_head_pitch_datum = rad ( wide_cockpit_position[wide_cockpit_nr].c.p );
			if (edit_wide_cockpit)
				pilot_head_pitch = pilot_head_pitch_datum;
		}

		vp_position.x += current_custom_cockpit_viewpoint.x;
		vp_position.y += current_custom_cockpit_viewpoint.y;
		vp_position.z += current_custom_cockpit_viewpoint.z;

		get_forces_acting_on_pilot(&vp_position.x, &vp_position.y, &vp_position.z, FALSE, TRUE);

		get_local_entity_attitude_matrix (get_gunship_entity (), vp.attitude);
		get_3d_transformation_matrix(head_rotation, pilot_head_heading, -pilot_head_pitch, 0.0);

		multiply_matrix3x3_vec3d(&vp_world_position, head_rotation, &vp_position);

		vp.x = vp_world_position.x;
		vp.y = vp_world_position.y;
		vp.z = vp_world_position.z;
	}

	////////////////////////////////////////
	//
	// render displays onto textures (before draw 3D scenes)
	//
	////////////////////////////////////////

	if (flags & VIRTUAL_COCKPIT_HUD_DISPLAY)
	{
		draw_havoc_hud_on_texture ();
	}

	if (flags & VIRTUAL_COCKPIT_EKRAN_DISPLAY)
	{
		draw_havoc_ekran_display_on_texture ();
	}

	if (flags & VIRTUAL_COCKPIT_CRT_DISPLAY)
	{
		draw_havoc_mfd_on_texture ();
	}

	////////////////////////////////////////
	//
	// draw 3D scene with lighting
	//
	////////////////////////////////////////

	if (flags & (VIRTUAL_COCKPIT_COCKPIT | VIRTUAL_COCKPIT_INSTRUMENT_NEEDLES))
	{
		set_cockpit_lighting (vp.attitude);

		set_3d_active_environment (main_3d_single_light_env);

		set_3d_view_distances (main_3d_single_light_env, 10.0, 0.3, 1.0, 0.0);

//VJ wideview mod, date: 18-mar-03
		if (get_global_wide_cockpit ()&&
	      !(flags & (VIRTUAL_COCKPIT_HUD_GLASS | VIRTUAL_COCKPIT_HUD_DISPLAY | VIRTUAL_COCKPIT_EKRAN_DISPLAY | VIRTUAL_COCKPIT_CRT_DISPLAY))
	   )
		{
		   vp.y = wide_cockpit_position[wide_cockpit_nr].c.y;
		   vp.z = wide_cockpit_position[wide_cockpit_nr].c.z;
		}

		realise_3d_clip_extents (main_3d_single_light_env);

		clear_zbuffer_screen ();

		if (begin_3d_scene ())
		{
			//
			// virtual cockpit
			//

			if (flags & VIRTUAL_COCKPIT_COCKPIT)
			{
				switch (get_local_entity_int_value (get_session_entity (), INT_TYPE_DAY_SEGMENT_TYPE))
				{
					////////////////////////////////////////
					case DAY_SEGMENT_TYPE_DAWN:
					////////////////////////////////////////
					{
						virtual_cockpit_inst3d = virtual_cockpit_level2_inst3d;

						break;
					}
					////////////////////////////////////////
					case DAY_SEGMENT_TYPE_DAY:
					////////////////////////////////////////
					{
						virtual_cockpit_inst3d = virtual_cockpit_level1_inst3d;

						break;
					}
					////////////////////////////////////////
					case DAY_SEGMENT_TYPE_DUSK:
					////////////////////////////////////////
					{
						virtual_cockpit_inst3d = virtual_cockpit_level2_inst3d;

						break;
					}
					////////////////////////////////////////
					case DAY_SEGMENT_TYPE_NIGHT:
					////////////////////////////////////////
					{
						virtual_cockpit_inst3d = virtual_cockpit_level3_inst3d;

						break;
					}
				}

				#if DEMO_VERSION

				virtual_cockpit_inst3d = virtual_cockpit_level1_inst3d;

				#endif

				memcpy (&virtual_cockpit_inst3d->vp, &vp, sizeof (viewpoint));

				insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_inst3d->vp.position, virtual_cockpit_inst3d);
			}

			//
			// instrument needles
			//

			if (flags & VIRTUAL_COCKPIT_INSTRUMENT_NEEDLES)
			{
				//
				// HSI
				//

				{
					float
						direction_finder,
						flight_path,
						drift;

					get_havoc_virtual_cockpit_hsi_needle_values (&direction_finder, &flight_path, &drift);

					//
					// flight path
					//

					search.search_depth = 0;
					search.search_object = virtual_cockpit_hsi_flight_path_inst3d;
					search.sub_object_index = OBJECT_3D_SUB_OBJECT_HAVOC_VIRTUAL_COCKPIT_HSI_ARROW_DOUBLE;

					if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
					{
						search.result_sub_object->relative_roll = flight_path;
					}

					memcpy (&virtual_cockpit_hsi_flight_path_inst3d->vp, &vp, sizeof (viewpoint));

					insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_hsi_flight_path_inst3d->vp.position, virtual_cockpit_hsi_flight_path_inst3d);

					//
					// direction finder
					//

					search.search_depth = 0;
					search.search_object = virtual_cockpit_hsi_direction_finder_inst3d;
					search.sub_object_index = OBJECT_3D_SUB_OBJECT_HAVOC_VIRTUAL_COCKPIT_HSI_ARROW_LONG;

					if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
					{
						search.result_sub_object->relative_roll = direction_finder;
					}

					memcpy (&virtual_cockpit_hsi_direction_finder_inst3d->vp, &vp, sizeof (viewpoint));

					insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_hsi_direction_finder_inst3d->vp.position, virtual_cockpit_hsi_direction_finder_inst3d);

					//
					// drift
					//

					search.search_depth = 0;
					search.search_object = virtual_cockpit_hsi_drift_inst3d;
					search.sub_object_index = OBJECT_3D_SUB_OBJECT_HAVOC_VIRTUAL_COCKPIT_HSI_ARROW_SHORT;

					if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
					{
						search.result_sub_object->relative_roll = drift;
					}

					memcpy (&virtual_cockpit_hsi_drift_inst3d->vp, &vp, sizeof (viewpoint));

					insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_hsi_drift_inst3d->vp.position, virtual_cockpit_hsi_drift_inst3d);

					//VJ wideview mod, date: 18-mar-03
					// re-insert compass here (internal is draw after external
					if (get_global_wide_cockpit ())
					{
					    insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_compass_inst3d->vp.position, virtual_cockpit_compass_inst3d);
					}
				}

				////////////////////////////////////////
				//
				// G METER
				//
				////////////////////////////////////////

				search.search_depth = 0;
				search.search_object = virtual_cockpit_instrument_needles_inst3d;
				search.sub_object_index = OBJECT_3D_SUB_OBJECT_HAVOC_GMETER_NEEDLE;

				if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
				{
					float
						gforce;

					gforce = bound((current_flight_dynamics->g_force.value), -2.0, 4.0);

					gforce *= rad (360.0) / 7.0;

					search.result_sub_object->relative_roll = -gforce;
				}

				////////////////////////////////////////
				//
				// RADAR ALTIMETER
				//
				////////////////////////////////////////

				search.search_depth = 0;
				search.search_object = virtual_cockpit_instrument_needles_inst3d;
				search.sub_object_index = OBJECT_3D_SUB_OBJECT_HAVOC_RAD_ALT_NEEDLE;

				if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
				{
					float
						altitude;

					altitude = bound((current_flight_dynamics->radar_altitude.value), 0.0, 300.00);

					if (altitude < 100.0)
						altitude *= rad (360.0) / 160.0;
					else
						altitude = altitude * rad (180.0) / 400.0 + rad (180.0);

					search.result_sub_object->relative_roll = -altitude;
				}

				////////////////////////////////////////
				//
				// ROTOR RPM
				//
				////////////////////////////////////////

				search.search_depth = 0;
				search.search_object = virtual_cockpit_instrument_needles_inst3d;
				search.sub_object_index = OBJECT_3D_SUB_OBJECT_HAVOC_ROTOR_RPM_NEEDLE;

				if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
				{
					float
						rotor_rpm;

					rotor_rpm = bound((current_flight_dynamics->main_rotor_rpm.value), 0.0, 110.0);

					rotor_rpm *= rad (360.0) / 120.0;

					search.result_sub_object->relative_roll = -rotor_rpm;
				}

				////////////////////////////////////////
				//
				// LEFT ENGINE NG
				//
				////////////////////////////////////////

				search.search_depth = 0;
				search.search_object = virtual_cockpit_instrument_needles_inst3d;
				search.sub_object_index = OBJECT_3D_SUB_OBJECT_HAVOC_LEFT_ENG_RPM_NEEDLE;

				if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
				{
					float
						leng_rpm;

					leng_rpm = bound((current_flight_dynamics->left_engine_rpm.value), 0.0, 110.0);

					leng_rpm *= rad (360.0) / 100.0;

					search.result_sub_object->relative_roll = -leng_rpm;
				}

				////////////////////////////////////////
				//
				// RIGHT ENGINE NG
				//
				////////////////////////////////////////

				search.search_depth = 0;
				search.search_object = virtual_cockpit_instrument_needles_inst3d;
				search.sub_object_index = OBJECT_3D_SUB_OBJECT_HAVOC_RIGHT_ENG_RPM_NEEDLE;

				if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
				{
					float
						reng_rpm;

					reng_rpm = bound((current_flight_dynamics->right_engine_rpm.value), 0.0, 110.0);

					reng_rpm *= rad (360.0) / 100.0;

					search.result_sub_object->relative_roll = -reng_rpm;
				}

				////////////////////////////////////////
				//
				// BAROMETRIC ALTIMETER
				//
				////////////////////////////////////////

				search.search_depth = 0;
				search.search_object = virtual_cockpit_instrument_needles_inst3d;
				search.sub_object_index = OBJECT_3D_SUB_OBJECT_HAVOC_BAR_ALT_LRG_NEEDLE;

				if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
				{
					float
						lrg_altitude;

					lrg_altitude = fmod (current_flight_dynamics->barometric_altitude.value, 1000.0f);

					lrg_altitude *= rad (360.0) / 1000.0;

					search.result_sub_object->relative_roll = -lrg_altitude;
				}

				search.search_depth = 0;
				search.search_object = virtual_cockpit_instrument_needles_inst3d;
				search.sub_object_index = OBJECT_3D_SUB_OBJECT_HAVOC_BAR_ALT_SML_NEEDLE;

				if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
				{
					float
						sml_altitude;

					sml_altitude = fmod (current_flight_dynamics->barometric_altitude.value, 10000.0f);

					sml_altitude *= rad (-360.0) / 10000.0;

					search.result_sub_object->relative_roll = sml_altitude;
				}

				////////////////////////////////////////
				//
				// AIRSPEED
				//
				////////////////////////////////////////

				search.search_depth = 0;
				search.search_object = virtual_cockpit_instrument_needles_inst3d;
				search.sub_object_index = OBJECT_3D_SUB_OBJECT_HAVOC_AIRSPEED_NEEDLE;

				if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
				{
					float
						airspeed;

					airspeed = bound(kilometres_per_hour (current_flight_dynamics->indicated_airspeed.value), -50.0, 450.0);

					airspeed *= rad (180.0) / 400.0;

					search.result_sub_object->relative_roll = -airspeed;
				}

				////////////////////////////////////////
				//
				// SLIP
				//
				////////////////////////////////////////

				search.search_depth = 0;
				search.search_object = virtual_cockpit_instrument_needles_inst3d;
				search.sub_object_index = OBJECT_3D_SUB_OBJECT_HAVOC_SIDE_SLIP_NEEDLE;

				if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
				{
					float
						slip;

					slip = bound(kilometres_per_hour (current_flight_dynamics->indicated_slip.value), -100.0, 100.0);

					slip *= rad (45.0) / 100.0;

					search.result_sub_object->relative_roll = -slip;
				}

				////////////////////////////////////////
				//
				// VERTICAL SPEED INDICATOR
				//
				////////////////////////////////////////

				search.search_depth = 0;
				search.search_object = virtual_cockpit_instrument_needles_inst3d;
				search.sub_object_index = OBJECT_3D_SUB_OBJECT_HAVOC_VSI_NEEDLE;

				if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
				{
					float
						vert_speed;

					vert_speed = bound(metres_per_minute (current_flight_dynamics->world_velocity_y.value), -300.0, 300.0);
					vert_speed *= rad (180.0) / 300.0;

					search.result_sub_object->relative_roll = -vert_speed;
				}

				////////////////////////////////////////
				//
				// CLOCK
				//
				////////////////////////////////////////

				{
					float
						tod,
						hour_hand_value,
						minute_hand_value,
						second_hand_value;

					tod = get_local_entity_float_value (get_session_entity (), FLOAT_TYPE_TIME_OF_DAY);
					get_analogue_clock_values (tod, &hour_hand_value, &minute_hand_value, &second_hand_value);

					// Hour Hand

					search.search_depth = 0;
					search.search_object = virtual_cockpit_instrument_needles_inst3d;
					search.sub_object_index = OBJECT_3D_SUB_OBJECT_HAVOC_CLOCK_HOUR_NEEDLE;

					if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
					{
						float
							hour;

						hour = hour_hand_value * rad (360.0) / 12.0;

						search.result_sub_object->relative_roll = -hour;
					}

					// Minute Hand

					search.search_depth = 0;
					search.search_object = virtual_cockpit_instrument_needles_inst3d;
					search.sub_object_index = OBJECT_3D_SUB_OBJECT_HAVOC_CLOCK_MINUTE_NEEDLE;

					if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
					{
						float
							minute;

						minute = minute_hand_value * rad (360.0) / 60.0;

						search.result_sub_object->relative_roll = -minute;
					}

					// Second Hand

					search.search_depth = 0;
					search.search_object = virtual_cockpit_instrument_needles_inst3d;
					search.sub_object_index = OBJECT_3D_SUB_OBJECT_HAVOC_CLOCK_SECOND_NEEDLE;

					if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
					{
						float
							second;

						second = second_hand_value * rad (360.0) / 60.0;

						search.result_sub_object->relative_roll = -second;
					}
				}

				////////////////////////////////////////
				//
				// FUEL GAUGE
				//
				////////////////////////////////////////

				search.search_depth = 0;
				search.search_object = virtual_cockpit_instrument_needles_inst3d;
				search.sub_object_index = OBJECT_3D_SUB_OBJECT_HAVOC_FUEL_NEEDLE;

				if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
				{
					float
						fuel_value;

					fuel_value = bound((current_flight_dynamics->fuel_weight.value), 0.0, 1600.0);
					fuel_value = (fuel_value - 750.0) * rad (360.0) / 2000.0;

					search.result_sub_object->relative_roll = -fuel_value;
				}

				memcpy (&virtual_cockpit_instrument_needles_inst3d->vp, &vp, sizeof (viewpoint));

				insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_instrument_needles_inst3d->vp.position, virtual_cockpit_instrument_needles_inst3d);
			}

			draw_3d_scene ();

			print_edit_wide_cockpit ();
			print_repairing_status();

			end_3d_scene ();
		}
	}

	////////////////////////////////////////
	//
	// draw 3D scene without lighting
	//
	////////////////////////////////////////

	if (flags & (VIRTUAL_COCKPIT_HUD_GLASS | VIRTUAL_COCKPIT_HUD_DISPLAY | VIRTUAL_COCKPIT_EKRAN_DISPLAY | VIRTUAL_COCKPIT_CRT_DISPLAY))
	{
		set_3d_active_environment (main_3d_env);

		set_3d_view_distances (main_3d_env, 10.0, 0.3, 1.0, 0.0);

		realise_3d_clip_extents (main_3d_env);

		recalculate_3d_environment_settings (main_3d_env);

		clear_zbuffer_screen ();

		if (begin_3d_scene ())
		{
			//
			// HUD glass
			//

			if (flags & VIRTUAL_COCKPIT_HUD_GLASS)
			{
				if (flags & VIRTUAL_COCKPIT_LARGE_HUD)
				{
					switch (get_local_entity_int_value (get_session_entity (), INT_TYPE_DAY_SEGMENT_TYPE))
					{
						////////////////////////////////////////
						case DAY_SEGMENT_TYPE_DAWN:
						////////////////////////////////////////
						{
							virtual_cockpit_large_hud_glass_inst3d = virtual_cockpit_large_hud_glass_level2_inst3d;

							break;
						}
						////////////////////////////////////////
						case DAY_SEGMENT_TYPE_DAY:
						////////////////////////////////////////
						{
							virtual_cockpit_large_hud_glass_inst3d = virtual_cockpit_large_hud_glass_level1_inst3d;

							break;
						}
						////////////////////////////////////////
						case DAY_SEGMENT_TYPE_DUSK:
						////////////////////////////////////////
						{
							virtual_cockpit_large_hud_glass_inst3d = virtual_cockpit_large_hud_glass_level2_inst3d;

							break;
						}
						////////////////////////////////////////
						case DAY_SEGMENT_TYPE_NIGHT:
						////////////////////////////////////////
						{
							virtual_cockpit_large_hud_glass_inst3d = virtual_cockpit_large_hud_glass_level3_inst3d;

							break;
						}
					}

					#if DEMO_VERSION

					virtual_cockpit_large_hud_glass_inst3d = virtual_cockpit_large_hud_glass_level1_inst3d;

					#endif

					memcpy (&virtual_cockpit_large_hud_glass_inst3d->vp, &vp, sizeof (viewpoint));

					insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_large_hud_glass_inst3d->vp.position, virtual_cockpit_large_hud_glass_inst3d);
				}
				else
				{
					switch (get_local_entity_int_value (get_session_entity (), INT_TYPE_DAY_SEGMENT_TYPE))
					{
						////////////////////////////////////////
						case DAY_SEGMENT_TYPE_DAWN:
						////////////////////////////////////////
						{
							virtual_cockpit_hud_glass_inst3d = virtual_cockpit_hud_glass_level2_inst3d;

							break;
						}
						////////////////////////////////////////
						case DAY_SEGMENT_TYPE_DAY:
						////////////////////////////////////////
						{
							virtual_cockpit_hud_glass_inst3d = virtual_cockpit_hud_glass_level1_inst3d;

							break;
						}
						////////////////////////////////////////
						case DAY_SEGMENT_TYPE_DUSK:
						////////////////////////////////////////
						{
							virtual_cockpit_hud_glass_inst3d = virtual_cockpit_hud_glass_level2_inst3d;

							break;
						}
						////////////////////////////////////////
						case DAY_SEGMENT_TYPE_NIGHT:
						////////////////////////////////////////
						{
							virtual_cockpit_hud_glass_inst3d = virtual_cockpit_hud_glass_level3_inst3d;

							break;
						}
					}

					#if DEMO_VERSION

					virtual_cockpit_hud_glass_inst3d = virtual_cockpit_hud_glass_level1_inst3d;

					#endif

					memcpy (&virtual_cockpit_hud_glass_inst3d->vp, &vp, sizeof (viewpoint));

					insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_hud_glass_inst3d->vp.position, virtual_cockpit_hud_glass_inst3d);
				}
			}

			//
			// HUD display
			//

			if (flags & VIRTUAL_COCKPIT_HUD_DISPLAY)
			{
				memcpy (&virtual_cockpit_hud_display_inst3d->vp, &vp, sizeof (viewpoint));

				insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_hud_display_inst3d->vp.position, virtual_cockpit_hud_display_inst3d);
			}

			//
			// EKRAN display
			//

			if (flags & VIRTUAL_COCKPIT_EKRAN_DISPLAY)
			{
				memcpy (&virtual_cockpit_ekran_display_inst3d->vp, &vp, sizeof (viewpoint));

				insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_ekran_display_inst3d->vp.position, virtual_cockpit_ekran_display_inst3d);
			}

			//
			// CRT display
			//

			if (flags & VIRTUAL_COCKPIT_CRT_DISPLAY)
			{
				memcpy (&virtual_cockpit_crt_display_inst3d->vp, &vp, sizeof (viewpoint));

				insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_crt_display_inst3d->vp.position, virtual_cockpit_crt_display_inst3d);
			}

			draw_3d_scene ();

			end_3d_scene ();
		}
	}

	////////////////////////////////////////
	//
	// draw 3D scene with lighting
	//
	////////////////////////////////////////

	//
	// draw fillet to mask EO display
	//

	if
	(
		(get_havoc_eo_display_visible ()) &&
		(flags & (VIRTUAL_COCKPIT_COCKPIT)) &&
		(flags & (VIRTUAL_COCKPIT_CRT_DISPLAY))
	)
	{
		set_cockpit_lighting (vp.attitude);

		set_3d_active_environment (main_3d_single_light_env);

		set_3d_view_distances (main_3d_single_light_env, 10.0, 0.1, 1.0, 0.0);

		realise_3d_clip_extents (main_3d_single_light_env);

		clear_zbuffer_screen ();

		if (begin_3d_scene ())
		{
			switch (get_local_entity_int_value (get_session_entity (), INT_TYPE_DAY_SEGMENT_TYPE))
			{
				////////////////////////////////////////
				case DAY_SEGMENT_TYPE_DAWN:
				////////////////////////////////////////
				{
					virtual_cockpit_inst3d = virtual_cockpit_fillet_level2_inst3d;

					break;
				}
				////////////////////////////////////////
				case DAY_SEGMENT_TYPE_DAY:
				////////////////////////////////////////
				{
					virtual_cockpit_inst3d = virtual_cockpit_fillet_level1_inst3d;

					break;
				}
				////////////////////////////////////////
				case DAY_SEGMENT_TYPE_DUSK:
				////////////////////////////////////////
				{
					virtual_cockpit_inst3d = virtual_cockpit_fillet_level2_inst3d;

					break;
				}
				////////////////////////////////////////
				case DAY_SEGMENT_TYPE_NIGHT:
				////////////////////////////////////////
				{
					virtual_cockpit_inst3d = virtual_cockpit_fillet_level3_inst3d;

					break;
				}
			}

			#if DEMO_VERSION

			virtual_cockpit_inst3d = virtual_cockpit_fillet_level1_inst3d;

			#endif

			memcpy (&virtual_cockpit_inst3d->vp, &vp, sizeof (viewpoint));

			insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_inst3d->vp.position, virtual_cockpit_inst3d);

			draw_3d_scene ();

			end_3d_scene ();
		}
	}

	////////////////////////////////////////
	//
	// tidy up
	//
	////////////////////////////////////////

	#if RECOGNITION_GUIDE

	set_3d_view_distances (main_3d_env, 10000.0, 100.0, 1.0, 0.0);

	#else

	set_3d_view_distances (main_3d_env, 10000.0, 1.0, 1.0, 0.0);

	#endif

	realise_3d_clip_extents (main_3d_env);
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_havoc_external_virtual_cockpit (unsigned int flags, unsigned char *wiper_rle_graphic)
{
#ifndef OGRE_EE
	viewpoint
		vp;

	object_3d_sub_object_search_data
		search;

	object_3d_instance
		*inst3d;

	////////////////////////////////////////
	//
	// virtual cockpit viewpoint is placed at the main object origin
	//
	////////////////////////////////////////

	if (get_view_mode () == VIEW_MODE_COCKPIT_PANEL_SPECIAL_HAVOC_TV)
	{
		get_display_viewpoint (VIEW_MODE_COCKPIT_PANEL_SPECIAL_HAVOC_TV, &vp);
	}
	else if (get_view_mode () == VIEW_MODE_COCKPIT_PANEL_SPECIAL_HAVOC_HUD)
	{
		get_display_viewpoint (VIEW_MODE_COCKPIT_PANEL_SPECIAL_HAVOC_HUD, &vp);
	}
	else
	{
		matrix3x3 head_rotation;
		vec3d vp_position, vp_world_position;

		vp_position.x = 0.0;
		vp_position.y = 0.0;
		vp_position.z = 0.0;

//VJ wideview mod, date: 18-mar-03
		if (get_global_wide_cockpit ())
		{
		   vp_position.x = wide_cockpit_position[wide_cockpit_nr].c.x;
		   vp_position.y = wide_cockpit_position[wide_cockpit_nr].c.y;
		   vp_position.z = wide_cockpit_position[wide_cockpit_nr].c.z;
			//VJ 050207 included head pitch in fixed view setting
			pilot_head_pitch_datum = rad ( wide_cockpit_position[wide_cockpit_nr].c.p );
			if (edit_wide_cockpit)
				pilot_head_pitch = pilot_head_pitch_datum;
		}

		vp_position.x += current_custom_cockpit_viewpoint.x;
		vp_position.y += current_custom_cockpit_viewpoint.y;
		vp_position.z += current_custom_cockpit_viewpoint.z;

		get_forces_acting_on_pilot(&vp_position.x, &vp_position.y, &vp_position.z, FALSE, TRUE);

		get_local_entity_attitude_matrix (get_gunship_entity (), vp.attitude);
		get_3d_transformation_matrix(head_rotation, pilot_head_heading, -pilot_head_pitch, 0.0);

		multiply_matrix3x3_vec3d(&vp_world_position, head_rotation, &vp_position);

		vp.x = vp_world_position.x;
		vp.y = vp_world_position.y;
		vp.z = vp_world_position.z;
	}

	////////////////////////////////////////
	//
	// draw 3D scene without lighting
	//
	////////////////////////////////////////

	if (flags & (VIRTUAL_COCKPIT_MAIN_ROTOR | VIRTUAL_COCKPIT_STOWED_WIPER | VIRTUAL_COCKPIT_MOVING_WIPER))
	{
		set_3d_active_environment (main_3d_env);

		set_3d_view_distances (main_3d_env, 10.0, 0.1, 1.0, 0.0);

		realise_3d_clip_extents (main_3d_env);

		recalculate_3d_environment_settings (main_3d_env);

		clear_zbuffer_screen ();

		if (begin_3d_scene ())
		{
			//
			// main rotor
			//

			if (flags & VIRTUAL_COCKPIT_MAIN_ROTOR)
			{
				if (!(get_helicopter_main_rotors_blurred (get_gunship_entity ()) && (!get_global_blurred_main_rotors_visible_from_cockpit ())))
				{
					inst3d = (object_3d_instance *) get_local_entity_ptr_value (get_gunship_entity (), PTR_TYPE_INSTANCE_3D_OBJECT);

					if (flags & VIRTUAL_COCKPIT_LARGE_HUD)
					{
						animate_helicopter_virtual_cockpit_main_rotors (get_gunship_entity (), virtual_cockpit_large_hud_main_rotor_inst3d, inst3d);

						memcpy (&virtual_cockpit_large_hud_main_rotor_inst3d->vp, &vp, sizeof (viewpoint));

						insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_large_hud_main_rotor_inst3d->vp.position, virtual_cockpit_large_hud_main_rotor_inst3d);
					}
					else
					{
						animate_helicopter_virtual_cockpit_main_rotors (get_gunship_entity (), virtual_cockpit_main_rotor_inst3d, inst3d);

						memcpy (&virtual_cockpit_main_rotor_inst3d->vp, &vp, sizeof (viewpoint));

						insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_main_rotor_inst3d->vp.position, virtual_cockpit_main_rotor_inst3d);
					}
				}
			}

			//
			// wiper
			//

			if (wiper_mode == WIPER_MODE_STOWED)
			{
				if (flags & VIRTUAL_COCKPIT_STOWED_WIPER)
				{
					draw_havoc_virtual_cockpit_wiper (&vp, flags & VIRTUAL_COCKPIT_LARGE_HUD);
				}
			}
			else
			{
				if (flags & VIRTUAL_COCKPIT_MOVING_WIPER)
				{
					draw_havoc_virtual_cockpit_wiper (&vp, flags & VIRTUAL_COCKPIT_LARGE_HUD);
				}
			}

			draw_3d_scene ();

			end_3d_scene ();
		}
	}

	////////////////////////////////////////
	//
	// draw 3D scene with lighting
	//
	////////////////////////////////////////

	if (flags & (VIRTUAL_COCKPIT_ADI | VIRTUAL_COCKPIT_HSI | VIRTUAL_COCKPIT_COMPASS))
	{
		set_cockpit_lighting (vp.attitude);

		set_3d_active_environment (main_3d_single_light_env);

		set_3d_view_distances (main_3d_single_light_env, 10.0, 0.1, 1.0, 0.0);

		realise_3d_clip_extents (main_3d_single_light_env);

		clear_zbuffer_screen ();

		if (begin_3d_scene ())
		{
			//
			// ADI
			//

			if (flags & VIRTUAL_COCKPIT_ADI)
			{
				search.search_depth = 0;
				search.search_object = virtual_cockpit_adi_inst3d;
				search.sub_object_index = OBJECT_3D_SUB_OBJECT_HAVOC_VIRTUAL_COCKPIT_ADI;

				if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
				{
					float
						heading,
						pitch,
						roll;

					get_havoc_virtual_cockpit_adi_angles (vp.attitude, &heading, &pitch, &roll);

					search.result_sub_object->relative_heading = -heading;

					search.result_sub_object->relative_pitch = pitch;

					search.result_sub_object->relative_roll = -roll;
				}

				memcpy (&virtual_cockpit_adi_inst3d->vp, &vp, sizeof (viewpoint));

				insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_adi_inst3d->vp.position, virtual_cockpit_adi_inst3d);
			}

			//
			// HSI
			//

			if (flags & VIRTUAL_COCKPIT_HSI)
			{
				switch (get_local_entity_int_value (get_session_entity (), INT_TYPE_DAY_SEGMENT_TYPE))
				{
					////////////////////////////////////////
					case DAY_SEGMENT_TYPE_DAWN:
					////////////////////////////////////////
					{
						virtual_cockpit_hsi_inst3d = virtual_cockpit_hsi_level2_inst3d;

						break;
					}
					////////////////////////////////////////
					case DAY_SEGMENT_TYPE_DAY:
					////////////////////////////////////////
					{
						virtual_cockpit_hsi_inst3d = virtual_cockpit_hsi_level1_inst3d;

						break;
					}
					////////////////////////////////////////
					case DAY_SEGMENT_TYPE_DUSK:
					////////////////////////////////////////
					{
						virtual_cockpit_hsi_inst3d = virtual_cockpit_hsi_level2_inst3d;

						break;
					}
					////////////////////////////////////////
					case DAY_SEGMENT_TYPE_NIGHT:
					////////////////////////////////////////
					{
						virtual_cockpit_hsi_inst3d = virtual_cockpit_hsi_level2_inst3d;

						break;
					}
				}

				#if DEMO_VERSION

				virtual_cockpit_hsi_inst3d = virtual_cockpit_hsi_level1_inst3d;

				#endif

				search.search_depth = 0;
				search.search_object = virtual_cockpit_hsi_inst3d;
				search.sub_object_index = OBJECT_3D_SUB_OBJECT_HAVOC_VIRTUAL_COCKPIT_HSI;

				if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
				{
					search.result_sub_object->relative_roll = current_flight_dynamics->heading.value;
				}

				memcpy (&virtual_cockpit_hsi_inst3d->vp, &vp, sizeof (viewpoint));

				insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_hsi_inst3d->vp.position, virtual_cockpit_hsi_inst3d);
			}

			//
			// compass
			//

			if (flags & VIRTUAL_COCKPIT_COMPASS)
			{
				switch (get_local_entity_int_value (get_session_entity (), INT_TYPE_DAY_SEGMENT_TYPE))
				{
					////////////////////////////////////////
					case DAY_SEGMENT_TYPE_DAWN:
					////////////////////////////////////////
					{
						virtual_cockpit_compass_inst3d = virtual_cockpit_compass_level2_inst3d;

						break;
					}
					////////////////////////////////////////
					case DAY_SEGMENT_TYPE_DAY:
					////////////////////////////////////////
					{
						virtual_cockpit_compass_inst3d = virtual_cockpit_compass_level1_inst3d;

						break;
					}
					////////////////////////////////////////
					case DAY_SEGMENT_TYPE_DUSK:
					////////////////////////////////////////
					{
						virtual_cockpit_compass_inst3d = virtual_cockpit_compass_level2_inst3d;

						break;
					}
					////////////////////////////////////////
					case DAY_SEGMENT_TYPE_NIGHT:
					////////////////////////////////////////
					{
						virtual_cockpit_compass_inst3d = virtual_cockpit_compass_level2_inst3d;

						break;
					}
				}

				#if DEMO_VERSION

				virtual_cockpit_compass_inst3d = virtual_cockpit_compass_level1_inst3d;

				#endif

				search.search_depth = 0;
				search.search_object = virtual_cockpit_compass_inst3d;
				search.sub_object_index = OBJECT_3D_SUB_OBJECT_HAVOC_VIRTUAL_COCKPIT_COMPASS_HEADING_NULL;

				if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
				{
					search.result_sub_object->relative_heading = -current_flight_dynamics->heading.value;
				}

				memcpy (&virtual_cockpit_compass_inst3d->vp, &vp, sizeof (viewpoint));

				insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_compass_inst3d->vp.position, virtual_cockpit_compass_inst3d);
			}

			draw_3d_scene ();

			end_3d_scene ();
		}
	}

#if 0
	////////////////////////////////////////
	//
	// rendered wiper
	//
	////////////////////////////////////////

	if (flags & VIRTUAL_COCKPIT_RENDERED_WIPER)
	{
		if (wiper_mode == WIPER_MODE_STOWED)
		{
			ASSERT (wiper_rle_graphic);

			if (lock_screen (active_screen))
			{
				blit_rle_graphic (wiper_rle_graphic, ix_640_480, iy_640_480);

				unlock_screen (active_screen);
			}
		}
	}
#endif

	////////////////////////////////////////
	//
	// rain effect
	//
	////////////////////////////////////////

	if (flags & VIRTUAL_COCKPIT_RAIN_EFFECT)
	{
		if (rain_mode != RAIN_MODE_DRY)
		{
			set_3d_active_environment (main_3d_env);

			set_3d_view_distances (main_3d_env, 10.0, 0.1, 1.0, 0.0);

			realise_3d_clip_extents (main_3d_env);

			recalculate_3d_environment_settings (main_3d_env);

			clear_zbuffer_screen ();

			if (begin_3d_scene ())
			{
				draw_havoc_virtual_cockpit_rain_effect (&vp, flags & VIRTUAL_COCKPIT_LARGE_HUD);

				draw_3d_scene ();

				end_3d_scene ();
			}
		}
	}

	move_edit_wide_cockpit ();



	////////////////////////////////////////
	//
	// tidy up
	//
	////////////////////////////////////////

	#if RECOGNITION_GUIDE

	set_3d_view_distances (main_3d_env, 10000.0, 100.0, 1.0, 0.0);

	#else

	set_3d_view_distances (main_3d_env, 10000.0, 1.0, 1.0, 0.0);

	#endif

	realise_3d_clip_extents (main_3d_env);
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef OGRE_EE
static void update_threat_warning_lights(void)
{
	rwr_above_light->visible_object = havoc_lamps.threat_warning_missile_above;
	rwr_below_light->visible_object = havoc_lamps.threat_warning_missile_below;
	rwr_missile_launch_light->visible_object = havoc_lamps.threat_warning_missile_lh_lock;

	rwr_left10_light->visible_object = havoc_lamps.threat_warning_bearing_lh_22;
	rwr_left30_light->visible_object = havoc_lamps.threat_warning_bearing_lh_45;
	rwr_left50_light->visible_object = havoc_lamps.threat_warning_bearing_lh_67;
	rwr_left90_light->visible_object = havoc_lamps.threat_warning_bearing_lh_90;
	rwr_left_rear_light->visible_object = havoc_lamps.threat_warning_bearing_lh_rear;
	rwr_right10_light->visible_object = havoc_lamps.threat_warning_bearing_rh_22;
	rwr_right30_light->visible_object = havoc_lamps.threat_warning_bearing_rh_45;
	rwr_right50_light->visible_object = havoc_lamps.threat_warning_bearing_rh_67;
	rwr_right90_light->visible_object = havoc_lamps.threat_warning_bearing_rh_90;
	rwr_right_rear_light->visible_object = havoc_lamps.threat_warning_bearing_rh_rear;

	rwr_airborne_light->visible_object = havoc_lamps.threat_warning_radar_type_1;
	rwr_long_range_light->visible_object = havoc_lamps.threat_warning_radar_type_2;
	rwr_medium_range_light->visible_object = havoc_lamps.threat_warning_radar_type_3;
	rwr_short_range_light->visible_object = havoc_lamps.threat_warning_radar_type_4;

	rwr_signal_strength1->visible_object = havoc_lamps.threat_warning_close_range_1;
	rwr_signal_strength2->visible_object = havoc_lamps.threat_warning_close_range_2;
	rwr_signal_strength3->visible_object = havoc_lamps.threat_warning_close_range_3;
	rwr_signal_strength4->visible_object = havoc_lamps.threat_warning_close_range_4;
	rwr_signal_strength5->visible_object = havoc_lamps.threat_warning_close_range_5;
	rwr_signal_strength6->visible_object = havoc_lamps.threat_warning_close_range_6;
	rwr_signal_strength7->visible_object = havoc_lamps.threat_warning_close_range_7;
	rwr_signal_strength8->visible_object = havoc_lamps.threat_warning_close_range_8;
	rwr_signal_strength9->visible_object = havoc_lamps.threat_warning_close_range_9;
	rwr_signal_strength10->visible_object = havoc_lamps.threat_warning_close_range_10;
	rwr_signal_strength11->visible_object = havoc_lamps.threat_warning_close_range_11;
	rwr_signal_strength12->visible_object = havoc_lamps.threat_warning_close_range_12;
	rwr_signal_strength13->visible_object = havoc_lamps.threat_warning_close_range_13;
	rwr_signal_strength14->visible_object = havoc_lamps.threat_warning_close_range_14;
	rwr_signal_strength15->visible_object = havoc_lamps.threat_warning_close_range_15;
}
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef OGRE_EE
void update_status_lamps(void)
{
	radar_lmp->visible_object = havoc_lamps.radar;
	flir_lmp->visible_object = havoc_lamps.flir;
	llltv_lmp->visible_object = havoc_lamps.llltv;
	lsr_lmp->visible_object = havoc_lamps.lsr;
	rjam_lmp->visible_object = havoc_lamps.rjam;
	ijam_lmp->visible_object = havoc_lamps.ijam;
	nav_comp_lmp->visible_object = havoc_lamps.nav_comp;
	comm_lmp->visible_object = havoc_lamps.comm;
	rws_lmp->visible_object = havoc_lamps.rws;
	hud_lmp->visible_object = havoc_lamps.hud;
	hms_lmp->visible_object = havoc_lamps.hms;
	tv_disp_lmp->visible_object = havoc_lamps.tv_disp;
	tw_disp_lmp->visible_object = havoc_lamps.tw_disp;
	nvg_lmp->visible_object = havoc_lamps.nvg;
	fire_ex_lmp->visible_object = havoc_lamps.fire_ex;
	rtr_brk_lmp->visible_object = havoc_lamps.rtr_brk;
	whl_brk_lmp->visible_object = havoc_lamps.whl_brk;
	acm_lmp->visible_object = havoc_lamps.acm;
}
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef OGRE_EE
void update_warning_lamps(void)
{
	leng_warn_lamp->visible_object = havoc_lamps.l_eng;
	reng_warn_lamp->visible_object = havoc_lamps.r_eng;
	trq_warn_lamp->visible_object = havoc_lamps.over_trq;
	rdr_warn_lamp->visible_object = havoc_lamps.rdr_on;
	ap_warn_lamp->visible_object = havoc_lamps.auto_pilot;
	hvr_warn_lamp->visible_object = havoc_lamps.auto_hvr;
	rjam_warn_lamp->visible_object = havoc_lamps.rdr_jam_on;
	ijam_warn_lamp->visible_object = havoc_lamps.ir_jam_on;
	mast_caut_lamp->visible_object = havoc_lamps.master_caution;
}
#endif

#ifndef OGRE_EE
void update_chaff_flare_status_lamps(void)
{
	chaff_lamp->visible_object = havoc_lamps.weapons_management_chaff_green;
	flare_lamp->visible_object = havoc_lamps.weapons_management_flare_green;
	chaff_dmg_lamp->visible_object = havoc_lamps.weapons_management_chaff_red;
	flare_dmg_lamp->visible_object = havoc_lamps.weapons_management_flare_red;
}
#endif
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
