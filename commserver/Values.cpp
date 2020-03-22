#include <math.h>

#include "lamp_structs.h"
#include "sharedmem.h"
#include "Values.h"

#ifndef M_PI
#define M_PI (3.14159265359)
#endif

#define pMem gPtrSharedMemory

enum GUNSHIP_TYPES	// stolen from global.h
{
	GUNSHIP_TYPE_APACHE,
	GUNSHIP_TYPE_HAVOC,
	GUNSHIP_TYPE_COMANCHE,
	GUNSHIP_TYPE_HOKUM,
	GUNSHIP_TYPE_BLACKHAWK,
	GUNSHIP_TYPE_HIND,
	GUNSHIP_TYPE_AH64A,
	GUNSHIP_TYPE_KA50,
	GUNSHIP_TYPE_VIPER,
	GUNSHIP_TYPE_KIOWA,
	NUM_GUNSHIP_TYPES
};

int heading(double value)
{
	int val = (int)(value * 1000);
	if (val < 0)
		val += 6295;
	return val * 0.05729578;
}

Value GetApacheSpecificData(int command)
{
	apache_lamp_flags lamp = pMem->cockpit_lamps.apache_lamps;

	switch (command)
	{
		case 501: return lamp.indicator_lamp_1;
		case 502: return lamp.indicator_lamp_2;
		case 503: return lamp.indicator_lamp_3;
		case 504: return lamp.indicator_lamp_4;
		case 505: return lamp.indicator_lamp_5;
		case 506: return lamp.indicator_lamp_6;
		case 507: return lamp.indicator_lamp_7;
		case 508: return lamp.indicator_lamp_8;
		case 509: return lamp.indicator_lamp_9;
		case 510: return lamp.engine_1_fire;
		case 511: return lamp.apu_fire;
		case 512: return lamp.engine_2_fire;
		case 513: return lamp.armament_lamp_1;
		case 514: return lamp.armament_lamp_2;
		case 515: return lamp.mfd_lamp_1;
		case 516: return lamp.mfd_lamp_2;
		default: break;
	}

	return "INVALID COMMAND FOR APACHE";
}

Value GetHavocSpecificData(int command)
{
	havoc_lamp_flags lamp = pMem->cockpit_lamps.havoc_lamps;

	switch (command)
	{
		case 501: return lamp.master_caution;
		case 502: return lamp.weapons_management_lh_outer_pylon_green;
		case 503: return lamp.weapons_management_lh_inner_pylon_green;
		case 504: return lamp.weapons_management_rh_inner_pylon_green;
		case 505: return lamp.weapons_management_rh_outer_pylon_green;
		case 506: return lamp.weapons_management_armour_piercing_cannon_green;
		case 507: return lamp.weapons_management_high_explosive_cannon_green;
		case 508: return lamp.weapons_management_lh_outer_pylon_red;
		case 509: return lamp.weapons_management_lh_inner_pylon_red;
		case 510: return lamp.weapons_management_rh_inner_pylon_red;
		case 511: return lamp.weapons_management_rh_outer_pylon_red;
		case 512: return lamp.weapons_management_armour_piercing_cannon_red;
		case 513: return lamp.weapons_management_high_explosive_cannon_red;
		case 514: return lamp.weapons_management_chaff_green;
		case 515: return lamp.weapons_management_flare_green;
		case 516: return lamp.weapons_management_chaff_red;
		case 517: return lamp.weapons_management_flare_red;
/*		case 518: return lamp.warning_1;
		case 519: return lamp.warning_2;
		case 520: return lamp.warning_3;
		case 521: return lamp.warning_4;
		case 522: return lamp.warning_5;
		case 523: return lamp.warning_6;
		case 524: return lamp.warning_7;
		case 525: return lamp.warning_8;	
		case 526: return lamp.status_1;
		case 527: return lamp.status_2;
		case 528: return lamp.status_3;
		case 529: return lamp.status_4;
		case 530: return lamp.status_5;
		case 531: return lamp.status_6;
		case 532: return lamp.status_7;
		case 533: return lamp.status_8;
		case 534: return lamp.status_9;
		case 535: return lamp.status_10;
		case 536: return lamp.status_11;
		case 537: return lamp.status_12;
		case 538: return lamp.status_13;
		case 539: return lamp.status_14;
		case 540: return lamp.status_15;
		case 541: return lamp.status_16;
		case 542: return lamp.status_17;
		case 543: return lamp.status_18;	*/
		case 544: return lamp.threat_warning_radar_type_1;
		case 545: return lamp.threat_warning_radar_type_2;
		case 546: return lamp.threat_warning_radar_type_3;
		case 547: return lamp.threat_warning_radar_type_4;
		case 548: return lamp.threat_warning_radar_type_5;
		case 549: return lamp.threat_warning_radar_type_6;
		case 550: return lamp.threat_warning_bearing_lh_rear;
		case 551: return lamp.threat_warning_bearing_rh_rear;
		case 552: return lamp.threat_warning_close_range_1;
		case 553: return lamp.threat_warning_close_range_2;
		case 554: return lamp.threat_warning_close_range_3;
		case 555: return lamp.threat_warning_close_range_4;
		case 556: return lamp.threat_warning_close_range_5;
		case 557: return lamp.threat_warning_close_range_6;
		case 558: return lamp.threat_warning_close_range_7;
		case 559: return lamp.threat_warning_close_range_8;
		case 560: return lamp.threat_warning_close_range_9;
		case 561: return lamp.threat_warning_close_range_5;
		case 562: return lamp.threat_warning_close_range_11;
		case 563: return lamp.threat_warning_close_range_12;
		case 564: return lamp.threat_warning_close_range_13;
		case 565: return lamp.threat_warning_close_range_14;
		case 566: return lamp.threat_warning_close_range_15;
		case 567: return lamp.threat_warning_bearing_lh_90_close_range;
		case 568: return lamp.threat_warning_bearing_lh_67_close_range;
		case 569: return lamp.threat_warning_bearing_lh_45_close_range;
		case 570: return lamp.threat_warning_bearing_lh_22_close_range;
		case 571: return lamp.threat_warning_bearing_rh_22_close_range;
		case 572: return lamp.threat_warning_bearing_rh_45_close_range;
		case 573: return lamp.threat_warning_bearing_rh_67_close_range;
		case 574: return lamp.threat_warning_bearing_rh_90_close_range;
		case 575: return lamp.threat_warning_bearing_lh_90;
		case 576: return lamp.threat_warning_bearing_lh_67;
		case 577: return lamp.threat_warning_bearing_lh_45;
		case 578: return lamp.threat_warning_bearing_lh_22;
		case 579: return lamp.threat_warning_bearing_rh_22;
		case 580: return lamp.threat_warning_bearing_rh_45;
		case 581: return lamp.threat_warning_bearing_rh_67;
		case 582: return lamp.threat_warning_bearing_rh_90;
		case 583: return lamp.threat_warning_missile_below;
		case 584: return lamp.threat_warning_missile_above;
		case 585: return lamp.threat_warning_missile_lh_lock;
		case 586: return lamp.threat_warning_missile_rh_lock;
		case 587: return lamp.threat_warning_bearing_lh_rear_close_range;
		case 588: return lamp.threat_warning_bearing_rh_rear_close_range;
		case 589: return lamp.radio;
		case 590: return lamp.lh_engine_oil_pressure_normal;
		case 591: return lamp.rh_engine_oil_pressure_normal;
		case 592: return lamp.lh_engine_oil_pressure_low;
		case 593: return lamp.rh_engine_oil_pressure_low;
		case 594: return lamp.lh_engine_oil_temperature_normal;
		case 595: return lamp.rh_engine_oil_temperature_normal;
		case 596: return lamp.lh_engine_oil_temperature_high;
		case 597: return lamp.rh_engine_oil_temperature_high;
		default: break;
	}

	return "INVALID COMMAND FOR HAVOC";
}

Value GetComancheSpecificData(int command)
{
	comanche_lamp_flags lamp = pMem->cockpit_lamps.comanche_lamps;

	switch (command)
	{
		case 501: return lamp.master_caution;
		case 502: return lamp.left_engine_ignition;
		case 503: return lamp.apu_ignition;
		case 504: return lamp.right_engine_ignition;
		case 505: return lamp.left_engine_fire;
		case 506: return lamp.apu_fire;
		case 507: return lamp.right_engine_fire;
		case 508: return lamp.left_engine_fire_extinguiser;
		case 509: return lamp.right_engine_fire_extinguiser;
		case 510: return lamp.hydraulic_pressure;
		case 511: return lamp.oil_pressure;
		case 512: return lamp.oil_temperature;
		case 513: return lamp.overtorque;
		case 514: return lamp.rotor_rpm;
		case 515: return lamp.fuel_low;
		case 516: return lamp.rotor_brake;
		case 517: return lamp.wheel_brake;
		case 518: return lamp.navigation_lights;
		case 519: return lamp.hover_hold;
		case 520: return lamp.altitude_hold;
		case 521: return lamp.auto_pilot;
		case 522: return lamp.radar;
		case 523: return lamp.laser;
		case 524: return lamp.radar_jammer;
		case 525: return lamp.ir_jammer;
		case 526: return lamp.auto_counter_measures;
		case 527: return lamp.ase_auto_page;
		case 528: return lamp.config_stub_wings;
		case 529: return lamp.config_bay_doors;
		case 530: return lamp.config_gear;
		case 531: return lamp.config_gun;
		case 532: return lamp.gear_damaged;
		case 533: return lamp.gear_status;
		case 534: return lamp.gear_red;
		case 535: return lamp.gear_transition;
		case 536: return lamp.pilot_lh_main_mfd_focus;
		case 537: return lamp.pilot_rh_main_mfd_focus;
		case 538: return lamp.co_pilot_lh_main_mfd_focus;
		case 539: return lamp.co_pilot_rh_main_mfd_focus;
		default: break;
	}

	return "INVALID COMMAND FOR COMANCHE";
}

Value GetHokumSpecificData(int command)
{
	hokum_lamp_flags lamp = pMem->cockpit_lamps.hokum_lamps;

	switch (command)
	{
		case 501: return lamp.master_caution;
		case 502: return lamp.left_engine_fire;
		case 503: return lamp.apu_fire;
		case 504: return lamp.right_engine_fire;
		case 505: return lamp.altitude_hold;
		case 506: return lamp.fire_extinguiser;
		case 507: return lamp.hydraulic_pressure;
		case 508: return lamp.oil_pressure;
		case 509: return lamp.oil_temperature;
		case 510: return lamp.rotor_brake;
		case 511: return lamp.overtorque;
		case 512: return lamp.fuel_low;
		case 513: return lamp.rotor_rpm;
		case 514: return lamp.wheel_brake;
		case 515: return lamp.navigation_lights;
		case 516: return lamp.hover_hold;
		case 517: return lamp.altitude_hold;
		case 518: return lamp.auto_pilot;
		case 519: return lamp.radar;
		case 520: return lamp.laser;
		case 521: return lamp.radar_jammer;
		case 522: return lamp.ir_jammer;
		case 523: return lamp.auto_counter_measures;
		case 524: return lamp.ase_auto_page;
		case 525: return lamp.gear_damaged;
		case 526: return lamp.gear_status;
		case 527: return lamp.gear_red;
		case 528: return lamp.pilot_lh_mfd_focus;
		case 529: return lamp.pilot_rh_mfd_focus;
		case 530: return lamp.co_pilot_lh_mfd_focus;
		case 531: return lamp.co_pilot_rh_mfd_focus;
		default: break;
	}

	return "INVALID COMMAND FOR HOKUM";
}

Value GetBlackhawkSpecificData(int command)
{
	blackhawk_lamp_flags lamp = pMem->cockpit_lamps.blackhawk_lamps;

	switch (command)
	{
		case 501: return lamp.indicator_lamp_1;
		case 502: return lamp.indicator_lamp_2;
		case 503: return lamp.indicator_lamp_3;
		case 504: return lamp.indicator_lamp_4;
		case 505: return lamp.indicator_lamp_5;
		case 506: return lamp.indicator_lamp_6;
		case 507: return lamp.indicator_lamp_7;
		case 508: return lamp.indicator_lamp_8;
		case 509: return lamp.indicator_lamp_9;
		case 510: return lamp.engine_1_fire;
		case 511: return lamp.apu_fire;
		case 512: return lamp.engine_2_fire;
		case 513: return lamp.armament_lamp_1;
		case 514: return lamp.armament_lamp_2;
		case 515: return lamp.mfd_lamp_1;
		case 516: return lamp.mfd_lamp_2;
		default: break;
	}

	return "INVALID COMMAND FOR BLACKHAWK";
}

Value GetHindSpecificData(int command)
{
	hind_lamp_flags lamp = pMem->cockpit_lamps.hind_lamps;

	switch (command)
	{
		case 501: return lamp.master_caution;
		case 502: return lamp.weapons_management_lh_outer_pylon_green;
		case 503: return lamp.weapons_management_lh_inner_pylon_green;
		case 504: return lamp.weapons_management_rh_inner_pylon_green;
		case 505: return lamp.weapons_management_rh_outer_pylon_green;
		case 506: return lamp.weapons_management_armour_piercing_cannon_green;
		case 507: return lamp.weapons_management_high_explosive_cannon_green;
		case 508: return lamp.weapons_management_lh_outer_pylon_red;
		case 509: return lamp.weapons_management_lh_inner_pylon_red;
		case 510: return lamp.weapons_management_rh_inner_pylon_red;
		case 511: return lamp.weapons_management_rh_outer_pylon_red;
		case 512: return lamp.weapons_management_armour_piercing_cannon_red;
		case 513: return lamp.weapons_management_high_explosive_cannon_red;
		case 514: return lamp.weapons_management_chaff_green;
		case 515: return lamp.weapons_management_flare_green;
		case 516: return lamp.weapons_management_chaff_red;
		case 517: return lamp.weapons_management_flare_red;
		case 518: return lamp.warning_1;
		case 519: return lamp.warning_2;
		case 520: return lamp.warning_3;
		case 521: return lamp.warning_4;
		case 522: return lamp.warning_5;
		case 523: return lamp.warning_6;
		case 524: return lamp.warning_7;
		case 525: return lamp.warning_8;
		case 526: return lamp.status_1;
		case 527: return lamp.status_2;
		case 528: return lamp.status_3;
		case 529: return lamp.status_4;
		case 530: return lamp.status_5;
		case 531: return lamp.status_6;
		case 532: return lamp.status_7;
		case 533: return lamp.status_8;
		case 534: return lamp.status_9;
		case 535: return lamp.status_10;
		case 536: return lamp.status_11;
		case 537: return lamp.status_12;
		case 538: return lamp.status_13;
		case 539: return lamp.status_14;
		case 540: return lamp.status_15;
		case 541: return lamp.status_16;
		case 542: return lamp.status_17;
		case 543: return lamp.status_18;
		case 544: return lamp.threat_warning_radar_type_1;
		case 545: return lamp.threat_warning_radar_type_2;
		case 546: return lamp.threat_warning_radar_type_3;
		case 547: return lamp.threat_warning_radar_type_4;
		case 548: return lamp.threat_warning_radar_type_5;
		case 549: return lamp.threat_warning_radar_type_6;
		case 550: return lamp.threat_warning_bearing_lh_rear;
		case 551: return lamp.threat_warning_bearing_rh_rear;
		case 552: return lamp.threat_warning_close_range_1;
		case 553: return lamp.threat_warning_close_range_2;
		case 554: return lamp.threat_warning_close_range_3;
		case 555: return lamp.threat_warning_close_range_4;
		case 556: return lamp.threat_warning_close_range_5;
		case 557: return lamp.threat_warning_close_range_6;
		case 558: return lamp.threat_warning_close_range_7;
		case 559: return lamp.threat_warning_close_range_8;
		case 560: return lamp.threat_warning_close_range_9;
		case 561: return lamp.threat_warning_close_range_5;
		case 562: return lamp.threat_warning_close_range_11;
		case 563: return lamp.threat_warning_close_range_12;
		case 564: return lamp.threat_warning_close_range_13;
		case 565: return lamp.threat_warning_close_range_14;
		case 566: return lamp.threat_warning_close_range_15;
		case 567: return lamp.threat_warning_bearing_lh_90_close_range;
		case 568: return lamp.threat_warning_bearing_lh_50_close_range;
		case 569: return lamp.threat_warning_bearing_lh_30_close_range;
		case 570: return lamp.threat_warning_bearing_lh_10_close_range;
		case 571: return lamp.threat_warning_bearing_rh_10_close_range;
		case 572: return lamp.threat_warning_bearing_rh_30_close_range;
		case 573: return lamp.threat_warning_bearing_rh_50_close_range;
		case 574: return lamp.threat_warning_bearing_rh_90_close_range;
		case 575: return lamp.threat_warning_bearing_lh_90;
		case 576: return lamp.threat_warning_bearing_lh_50;
		case 577: return lamp.threat_warning_bearing_lh_30;
		case 578: return lamp.threat_warning_bearing_lh_10;
		case 579: return lamp.threat_warning_bearing_rh_10;
		case 580: return lamp.threat_warning_bearing_rh_30;
		case 581: return lamp.threat_warning_bearing_rh_50;
		case 582: return lamp.threat_warning_bearing_rh_90;
		case 583: return lamp.threat_warning_missile_below;
		case 584: return lamp.threat_warning_missile_above;
		case 585: return lamp.threat_warning_missile_lh_lock;
		case 586: return lamp.threat_warning_missile_rh_lock;
		case 587: return lamp.threat_warning_bearing_lh_rear_close_range;
		case 588: return lamp.threat_warning_bearing_rh_rear_close_range;
		case 589: return lamp.radio;
		case 590: return lamp.lh_engine_oil_pressure_normal;
		case 591: return lamp.rh_engine_oil_pressure_normal;
		case 592: return lamp.lh_engine_oil_pressure_low;
		case 593: return lamp.rh_engine_oil_pressure_low;
		case 594: return lamp.lh_engine_oil_temperature_normal;
		case 595: return lamp.rh_engine_oil_temperature_normal;
		case 596: return lamp.lh_engine_oil_temperature_high;
		case 597: return lamp.rh_engine_oil_temperature_high;
		default: break;
	}

	return "INVALID COMMAND FOR HIND";
}

Value GetAH64ASpecificData(int command)
{
	ah64a_lamp_flags lamp = pMem->cockpit_lamps.ah64a_lamps;

	switch (command)
	{
		case 501: return lamp.indicator_lamp_1;
		case 502: return lamp.indicator_lamp_2;
		case 503: return lamp.indicator_lamp_3;
		case 504: return lamp.indicator_lamp_4;
		case 505: return lamp.indicator_lamp_5;
		case 506: return lamp.indicator_lamp_6;
		case 507: return lamp.indicator_lamp_7;
		case 508: return lamp.indicator_lamp_8;
		case 509: return lamp.indicator_lamp_9;
		case 510: return lamp.engine_1_fire;
		case 511: return lamp.apu_fire;
		case 512: return lamp.engine_2_fire;
		case 513: return lamp.armament_lamp_1;
		case 514: return lamp.armament_lamp_2;
		case 515: return lamp.mfd_lamp_1;
		case 516: return lamp.mfd_lamp_2;
		default: break;
	}

	return "INVALID COMMAND FOR AH64A";
}

Value GetKa50SpecificData(int command)
{
	ka50_lamp_flags lamp = pMem->cockpit_lamps.ka50_lamps;

	switch (command)
	{
		case 501: return lamp.master_caution;
		case 502: return lamp.left_engine_fire;
		case 503: return lamp.apu_fire;
		case 504: return lamp.right_engine_fire;
		case 505: return lamp.altitude_hold;
		case 506: return lamp.fire_extinguiser;
		case 507: return lamp.hydraulic_pressure;
		case 508: return lamp.oil_pressure;
		case 509: return lamp.oil_temperature;
		case 510: return lamp.rotor_brake;
		case 511: return lamp.overtorque;
		case 512: return lamp.fuel_low;
		case 513: return lamp.rotor_rpm;
		case 514: return lamp.wheel_brake;
		case 515: return lamp.navigation_lights;
		case 516: return lamp.hover_hold;
		case 517: return lamp.altitude_hold;
		case 518: return lamp.auto_pilot;
		case 519: return lamp.laser;
		case 520: return lamp.radar_jammer;
		case 521: return lamp.ir_jammer;
		case 522: return lamp.auto_counter_measures;
		case 523: return lamp.ase_auto_page;
		case 524: return lamp.gear_damaged;
		case 525: return lamp.gear_status;
		case 526: return lamp.gear_red;
		case 527: return lamp.leng_overtorque;
		case 528: return lamp.reng_overtorque;
		default: break;
	}

	return "INVALID COMMAND FOR KA50";
}

Value GetViperSpecificData(int command)
{
	viper_lamp_flags lamp = pMem->cockpit_lamps.viper_lamps;

	switch (command)
	{
		case 501: return lamp.master_caution;
		case 502: return lamp.engine_ignition;
		case 503: return lamp.apu_ignition;
		case 504: return lamp.engine_fire;
		case 505: return lamp.apu_fire;
		case 506: return lamp.engine_fire_extinguiser;
		case 507: return lamp.hydraulic_pressure;
		case 508: return lamp.oil_pressure;
		case 509: return lamp.oil_temperature;
		case 510: return lamp.overtorque;
		case 511: return lamp.rotor_rpm;
		case 512: return lamp.fuel_low;
		case 513: return lamp.rotor_brake;
		case 514: return lamp.navigation_lights;
		case 515: return lamp.hover_hold;
		case 516: return lamp.altitude_hold;
		case 517: return lamp.auto_pilot;
		case 518: return lamp.laser;
		case 519: return lamp.ir_jammer;
		case 520: return lamp.auto_counter_measures;
		case 521: return lamp.ase_auto_page;
		case 522: return lamp.pilot_lh_mfd_focus;
		case 523: return lamp.pilot_rh_mfd_focus;
		case 524: return lamp.co_pilot_lh_mfd_focus;
		case 525: return lamp.co_pilot_rh_mfd_focus;
		default: break;
	}

	return "INVALID COMMAND FOR DEFAULT";
}

Value GetKiowaSpecificData(int command)
{
	kiowa_lamp_flags lamp = pMem->cockpit_lamps.kiowa_lamps;

	switch (command)
	{
		case 0:
		default: break;
	}

	return "INVALID COMMAND FOR KIOWA";
}

Value GetDefaultSpecificData(int command)
{
	default_lamp_flags lamp = pMem->cockpit_lamps.default_lamps;

	switch (command)
	{
		case 501: return lamp.indicator_lamp_1;
		case 502: return lamp.indicator_lamp_2;
		case 503: return lamp.indicator_lamp_3;
		case 504: return lamp.indicator_lamp_4;
		case 505: return lamp.indicator_lamp_5;
		case 506: return lamp.indicator_lamp_6;
		case 507: return lamp.indicator_lamp_7;
		case 508: return lamp.indicator_lamp_8;
		case 509: return lamp.indicator_lamp_9;
		case 510: return lamp.engine_1_fire;
		case 511: return lamp.apu_fire;
		case 512: return lamp.engine_2_fire;
		case 513: return lamp.armament_lamp_1;
		case 514: return lamp.armament_lamp_2;
		case 515: return lamp.mfd_lamp_1;
		case 516: return lamp.mfd_lamp_2;
		default: break;
	}

	return "INVALID COMMAND FOR DEFAULT";
}

Value GetValue(int command)
{
	if (pMem->version != SHARED_MEM_DATA_VERSION)
		return "INVALID VERSION";

	if (command <= 500)
	{
		switch (command)
		{
		case 18: return pMem->num_flares;			//  Javelin  7/19
		case 19: return pMem->num_chaff;			//  Javelin  7/19
		case 20: return pMem->time_of_day / 3600.f;
		case 21: return pMem->time_of_day;
		case 22: break; // plane string
		case 24: break; // number of cockpits
		case 26: break; // current cockpit (0 - pilot's cockpit)
		case 28: return 2; // number of engines
		case 30: return pMem->indicated_airspeed * 3.6f;
		case 32: return pMem->vertical_speed;
		case 34: return pMem->indicated_slip;
		case 36: break; // -1 - rotating left, +1 - rotating right
		case 38: break; // angular speed
		case 40: return pMem->barometric_altitude;
		case 42: return heading(pMem->heading);
		case 44: return heading(pMem->waypoint_data.waypoint_bearing);
		case 46: return -pMem->roll * 180 / M_PI;
		case 48: return pMem->pitch * 180 / M_PI;
		case 50: return pMem->fuel_weight;
		case 52: return pMem->g_force;
		case 54: break; // shake level [0..1]
		case 56: break; // left gear position [0..1]
		case 58: break; // right gear position [0..1]
		case 60: break; // center gear position [0..1]
		case 64: return pMem->left_engine_rpm;
		case 65: return pMem->right_engine_rpm;
		case 66: return pMem->left_engine_n1_rpm;
		case 67: return pMem->right_engine_n1_rpm;
		case 72: return pMem->left_engine_temp - 273.f;
		case 73: return pMem->right_engine_temp - 273.f;

		case 80: return pMem->cockpit_strings.upfront_display[0];		//  Javelin  7/19	14 characters + null
		case 81: return pMem->cockpit_strings.upfront_display[1];		//  char *	
		case 82: return pMem->cockpit_strings.upfront_display[2];
		case 83: return pMem->cockpit_strings.upfront_display[3];
		case 84: return pMem->cockpit_strings.ekran_display[0];			//  Javelin  7/19	9 or 11 characters + null
		case 85: return pMem->cockpit_strings.ekran_display[1];			//  char *
		case 86: return pMem->cockpit_strings.ekran_display[2];
		case 87: return pMem->cockpit_strings.ekran_display[3];

		case 451: return pMem->radar_altitude;
		case 452: return pMem->combined_engine_rpm;
		case 453: return pMem->combined_engine_torque;
		case 454: return pMem->left_engine_torque;
		case 455: return pMem->right_engine_torque;
		default: break;
		}
	}
	else
	{
		switch (pMem->current_gunship)
		{
		case GUNSHIP_TYPE_APACHE: return GetApacheSpecificData(command);
		case GUNSHIP_TYPE_HAVOC: return GetHavocSpecificData(command);
		case GUNSHIP_TYPE_COMANCHE: return GetComancheSpecificData(command);
		case GUNSHIP_TYPE_HOKUM: return GetHokumSpecificData(command);
		case GUNSHIP_TYPE_BLACKHAWK: return GetBlackhawkSpecificData(command);
		case GUNSHIP_TYPE_HIND: return GetHindSpecificData(command);
		case GUNSHIP_TYPE_AH64A: return GetAH64ASpecificData(command);
		case GUNSHIP_TYPE_KA50: return GetKa50SpecificData(command);
		case GUNSHIP_TYPE_VIPER: return GetViperSpecificData(command);
		case GUNSHIP_TYPE_KIOWA: return GetKiowaSpecificData(command);
		case NUM_GUNSHIP_TYPES: return GetDefaultSpecificData(command);
		default: break;
		}
	}

	return "INVALID COMMAND";
}
