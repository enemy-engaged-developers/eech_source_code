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

struct HIND_LAMP_FLAGS
{
	unsigned int

		//
		// master caution
		//

		master_caution	:1,

		//
		// weapons management panel
		//

		weapons_management_lh_outer_pylon_green			:1,
		weapons_management_lh_inner_pylon_green			:1,
		weapons_management_rh_inner_pylon_green			:1,
		weapons_management_rh_outer_pylon_green			:1,
		weapons_management_armour_piercing_cannon_green	:1,
		weapons_management_high_explosive_cannon_green	:1,
		weapons_management_lh_outer_pylon_red				:1,
		weapons_management_lh_inner_pylon_red				:1,
		weapons_management_rh_inner_pylon_red				:1,
		weapons_management_rh_outer_pylon_red				:1,
		weapons_management_armour_piercing_cannon_red	:1,
		weapons_management_high_explosive_cannon_red		:1,
		weapons_management_chaff_green						:1,
		weapons_management_flare_green						:1,
		weapons_management_chaff_red							:1,
		weapons_management_flare_red							:1,

		//
		// warning panel
		//

		warning_1	:1,
		warning_2	:1,
		warning_3	:1,
		warning_4	:1,
		warning_5	:1,
		warning_6	:1,
		warning_7	:1,
		warning_8	:1,

		//
		// status panel
		//

		status_1		:1,
		status_2		:1,
		status_3		:1,
		status_4		:1,
		status_5		:1,
		status_6		:1,
		status_7		:1,
		status_8		:1,
		status_9		:1,
		status_10	:1,
		status_11	:1,
		status_12	:1,
		status_13	:1,
		status_14	:1,
		status_15	:1,
		status_16	:1,
		status_17	:1,
		status_18	:1,

		//
		// threat warning display
		//

		threat_warning_radar_type_1						:1,
		threat_warning_radar_type_2						:1,
		threat_warning_radar_type_3						:1,
		threat_warning_radar_type_4						:1,
		threat_warning_radar_type_5						:1,
		threat_warning_radar_type_6						:1,
		threat_warning_bearing_lh_rear					:1,
		threat_warning_bearing_rh_rear					:1,
		threat_warning_close_range_1						:1,
		threat_warning_close_range_2						:1,
		threat_warning_close_range_3						:1,
		threat_warning_close_range_4						:1,
		threat_warning_close_range_5						:1,
		threat_warning_close_range_6						:1,
		threat_warning_close_range_7						:1,
		threat_warning_close_range_8						:1,
		threat_warning_close_range_9						:1,
		threat_warning_close_range_10						:1,
		threat_warning_close_range_11						:1,
		threat_warning_close_range_12						:1,
		threat_warning_close_range_13						:1,
		threat_warning_close_range_14						:1,
		threat_warning_close_range_15						:1,
		threat_warning_bearing_lh_90_close_range		:1,
		threat_warning_bearing_lh_50_close_range		:1,
		threat_warning_bearing_lh_30_close_range		:1,
		threat_warning_bearing_lh_10_close_range		:1,
		threat_warning_bearing_rh_10_close_range		:1,
		threat_warning_bearing_rh_30_close_range		:1,
		threat_warning_bearing_rh_50_close_range		:1,
		threat_warning_bearing_rh_90_close_range		:1,
		threat_warning_bearing_lh_90						:1,
		threat_warning_bearing_lh_50						:1,
		threat_warning_bearing_lh_30						:1,
		threat_warning_bearing_lh_10						:1,
		threat_warning_bearing_rh_10						:1,
		threat_warning_bearing_rh_30						:1,
		threat_warning_bearing_rh_50						:1,
		threat_warning_bearing_rh_90						:1,
		threat_warning_missile_below						:1,
		threat_warning_missile_above						:1,
		threat_warning_missile_lh_lock					:1,
		threat_warning_missile_rh_lock					:1,
		threat_warning_bearing_lh_rear_close_range	:1,
		threat_warning_bearing_rh_rear_close_range	:1,

		//
		// radio
		//

		radio	:1,

		//
		// oil gauges
		//

		lh_engine_oil_pressure_normal		:1,
		rh_engine_oil_pressure_normal		:1,
		lh_engine_oil_pressure_low			:1,
		rh_engine_oil_pressure_low			:1,
		lh_engine_oil_temperature_normal	:1,
		rh_engine_oil_temperature_normal	:1,
		lh_engine_oil_temperature_high	:1,
		rh_engine_oil_temperature_high	:1;
};

typedef struct HIND_LAMP_FLAGS hind_lamp_flags;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern hind_lamp_flags
	hind_lamps;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void initialise_hind_lamps (void);

extern void draw_hind_weapons_management_panel_lamps (cockpit_panels panel);

extern void draw_hind_status_panel_lamps (cockpit_panels panel);

extern void draw_hind_threat_warning_display (cockpit_panels panel);

extern void draw_hind_master_caution_lamp (cockpit_panels panel);

extern void draw_hind_warning_panel_lamps (cockpit_panels panel);

extern void draw_hind_radio_lamp (cockpit_panels panel);

extern void draw_hind_oil_gauges (cockpit_panels panel);

extern void draw_overlaid_hind_threat_warning_display (int x_org, int y_org);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
