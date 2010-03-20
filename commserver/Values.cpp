#include <math.h>

#include "lamp_structs.h"
#include "sharedmem.h"

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
	NUM_GUNSHIP_TYPES
};

float getApacheSpecificData(int commandID)
{
	apache_lamp_flags lamp = pMem->cockpit_lamps.apache_lamps;

	switch (commandID)
	{
		case 501: return static_cast<float>(lamp.indicator_lamp_1);
		case 502: return static_cast<float>(lamp.indicator_lamp_2);
		case 503: return static_cast<float>(lamp.indicator_lamp_3);
		case 504: return static_cast<float>(lamp.indicator_lamp_4);
		case 505: return static_cast<float>(lamp.indicator_lamp_5);
		case 506: return static_cast<float>(lamp.indicator_lamp_6);
		case 507: return static_cast<float>(lamp.indicator_lamp_7);
		case 508: return static_cast<float>(lamp.indicator_lamp_8);
		case 509: return static_cast<float>(lamp.indicator_lamp_9);
		case 510: return static_cast<float>(lamp.engine_1_fire);
		case 511: return static_cast<float>(lamp.apu_fire);
		case 512: return static_cast<float>(lamp.engine_2_fire);
		case 513: return static_cast<float>(lamp.armament_lamp_1);
		case 514: return static_cast<float>(lamp.armament_lamp_2);
		case 515: return static_cast<float>(lamp.mfd_lamp_1);
		case 516: return static_cast<float>(lamp.mfd_lamp_2);
		default: break;
	}

	return 0.0f;
}

float getHavocSpecificData(int commandID)
{
	havoc_lamp_flags lamp = pMem->cockpit_lamps.havoc_lamps;

	switch (commandID)
	{
		case 501: return static_cast<float>(lamp.master_caution);
		case 502: return static_cast<float>(lamp.weapons_management_lh_outer_pylon_green);
		case 503: return static_cast<float>(lamp.weapons_management_lh_inner_pylon_green);
		case 504: return static_cast<float>(lamp.weapons_management_rh_inner_pylon_green);
		case 505: return static_cast<float>(lamp.weapons_management_rh_outer_pylon_green);
		case 506: return static_cast<float>(lamp.weapons_management_armour_piercing_cannon_green);
		case 507: return static_cast<float>(lamp.weapons_management_high_explosive_cannon_green);
		case 508: return static_cast<float>(lamp.weapons_management_lh_outer_pylon_red);
		case 509: return static_cast<float>(lamp.weapons_management_lh_inner_pylon_red);
		case 510: return static_cast<float>(lamp.weapons_management_rh_inner_pylon_red);
		case 511: return static_cast<float>(lamp.weapons_management_rh_outer_pylon_red);
		case 512: return static_cast<float>(lamp.weapons_management_armour_piercing_cannon_red);
		case 513: return static_cast<float>(lamp.weapons_management_high_explosive_cannon_red);
		case 514: return static_cast<float>(lamp.weapons_management_chaff_green);
		case 515: return static_cast<float>(lamp.weapons_management_flare_green);
		case 516: return static_cast<float>(lamp.weapons_management_chaff_red);
		case 517: return static_cast<float>(lamp.weapons_management_flare_red);
		case 518: return static_cast<float>(lamp.warning_1);
		case 519: return static_cast<float>(lamp.warning_2);
		case 520: return static_cast<float>(lamp.warning_3);
		case 521: return static_cast<float>(lamp.warning_4);
		case 522: return static_cast<float>(lamp.warning_5);
		case 523: return static_cast<float>(lamp.warning_6);
		case 524: return static_cast<float>(lamp.warning_7);
		case 525: return static_cast<float>(lamp.warning_8);
		case 526: return static_cast<float>(lamp.status_1);
		case 527: return static_cast<float>(lamp.status_2);
		case 528: return static_cast<float>(lamp.status_3);
		case 529: return static_cast<float>(lamp.status_4);
		case 530: return static_cast<float>(lamp.status_5);
		case 531: return static_cast<float>(lamp.status_6);
		case 532: return static_cast<float>(lamp.status_7);
		case 533: return static_cast<float>(lamp.status_8);
		case 534: return static_cast<float>(lamp.status_9);
		case 535: return static_cast<float>(lamp.status_10);
		case 536: return static_cast<float>(lamp.status_11);
		case 537: return static_cast<float>(lamp.status_12);
		case 538: return static_cast<float>(lamp.status_13);
		case 539: return static_cast<float>(lamp.status_14);
		case 540: return static_cast<float>(lamp.status_15);
		case 541: return static_cast<float>(lamp.status_16);
		case 542: return static_cast<float>(lamp.status_17);
		case 543: return static_cast<float>(lamp.status_18);
		case 544: return static_cast<float>(lamp.threat_warning_radar_type_1);
		case 545: return static_cast<float>(lamp.threat_warning_radar_type_2);
		case 546: return static_cast<float>(lamp.threat_warning_radar_type_3);
		case 547: return static_cast<float>(lamp.threat_warning_radar_type_4);
		case 548: return static_cast<float>(lamp.threat_warning_radar_type_5);
		case 549: return static_cast<float>(lamp.threat_warning_radar_type_6);
		case 550: return static_cast<float>(lamp.threat_warning_bearing_lh_rear);
		case 551: return static_cast<float>(lamp.threat_warning_bearing_rh_rear);
		case 552: return static_cast<float>(lamp.threat_warning_close_range_1);
		case 553: return static_cast<float>(lamp.threat_warning_close_range_2);
		case 554: return static_cast<float>(lamp.threat_warning_close_range_3);
		case 555: return static_cast<float>(lamp.threat_warning_close_range_4);
		case 556: return static_cast<float>(lamp.threat_warning_close_range_5);
		case 557: return static_cast<float>(lamp.threat_warning_close_range_6);
		case 558: return static_cast<float>(lamp.threat_warning_close_range_7);
		case 559: return static_cast<float>(lamp.threat_warning_close_range_8);
		case 560: return static_cast<float>(lamp.threat_warning_close_range_9);
		case 561: return static_cast<float>(lamp.threat_warning_close_range_5);
		case 562: return static_cast<float>(lamp.threat_warning_close_range_11);
		case 563: return static_cast<float>(lamp.threat_warning_close_range_12);
		case 564: return static_cast<float>(lamp.threat_warning_close_range_13);
		case 565: return static_cast<float>(lamp.threat_warning_close_range_14);
		case 566: return static_cast<float>(lamp.threat_warning_close_range_15);
		case 567: return static_cast<float>(lamp.threat_warning_bearing_lh_90_close_range);
		case 568: return static_cast<float>(lamp.threat_warning_bearing_lh_67_close_range);
		case 569: return static_cast<float>(lamp.threat_warning_bearing_lh_45_close_range);
		case 570: return static_cast<float>(lamp.threat_warning_bearing_lh_22_close_range);
		case 571: return static_cast<float>(lamp.threat_warning_bearing_rh_22_close_range);
		case 572: return static_cast<float>(lamp.threat_warning_bearing_rh_45_close_range);
		case 573: return static_cast<float>(lamp.threat_warning_bearing_rh_67_close_range);
		case 574: return static_cast<float>(lamp.threat_warning_bearing_rh_90_close_range);
		case 575: return static_cast<float>(lamp.threat_warning_bearing_lh_90);
		case 576: return static_cast<float>(lamp.threat_warning_bearing_lh_67);
		case 577: return static_cast<float>(lamp.threat_warning_bearing_lh_45);
		case 578: return static_cast<float>(lamp.threat_warning_bearing_lh_22);
		case 579: return static_cast<float>(lamp.threat_warning_bearing_rh_22);
		case 580: return static_cast<float>(lamp.threat_warning_bearing_rh_45);
		case 581: return static_cast<float>(lamp.threat_warning_bearing_rh_67);
		case 582: return static_cast<float>(lamp.threat_warning_bearing_rh_90);
		case 583: return static_cast<float>(lamp.threat_warning_missile_below);
		case 584: return static_cast<float>(lamp.threat_warning_missile_above);
		case 585: return static_cast<float>(lamp.threat_warning_missile_lh_lock);
		case 586: return static_cast<float>(lamp.threat_warning_missile_rh_lock);
		case 587: return static_cast<float>(lamp.threat_warning_bearing_lh_rear_close_range);
		case 588: return static_cast<float>(lamp.threat_warning_bearing_rh_rear_close_range);
		case 589: return static_cast<float>(lamp.radio);
		case 590: return static_cast<float>(lamp.lh_engine_oil_pressure_normal);
		case 591: return static_cast<float>(lamp.rh_engine_oil_pressure_normal);
		case 592: return static_cast<float>(lamp.lh_engine_oil_pressure_low);
		case 593: return static_cast<float>(lamp.rh_engine_oil_pressure_low);
		case 594: return static_cast<float>(lamp.lh_engine_oil_temperature_normal);
		case 595: return static_cast<float>(lamp.rh_engine_oil_temperature_normal);
		case 596: return static_cast<float>(lamp.lh_engine_oil_temperature_high);
		case 597: return static_cast<float>(lamp.rh_engine_oil_temperature_high);
		case 598: return static_cast<float>(lamp.warning_3);
		default: break;
	}

	return 0.0f;
}

float getComancheSpecificData(int commandID)
{
	comanche_lamp_flags lamp = pMem->cockpit_lamps.comanche_lamps;

	switch (commandID)
	{
		case 501: return static_cast<float>(lamp.master_caution);
		case 502: return static_cast<float>(lamp.left_engine_ignition);
		case 503: return static_cast<float>(lamp.apu_ignition);
		case 504: return static_cast<float>(lamp.right_engine_ignition);
		case 505: return static_cast<float>(lamp.left_engine_fire);
		case 506: return static_cast<float>(lamp.apu_fire);
		case 507: return static_cast<float>(lamp.right_engine_fire);
		case 508: return static_cast<float>(lamp.left_engine_fire_extinguiser);
		case 509: return static_cast<float>(lamp.right_engine_fire_extinguiser);
		case 510: return static_cast<float>(lamp.hydraulic_pressure);
		case 511: return static_cast<float>(lamp.oil_pressure);
		case 512: return static_cast<float>(lamp.oil_temperature);
		case 513: return static_cast<float>(lamp.overtorque);
		case 514: return static_cast<float>(lamp.rotor_rpm);
		case 515: return static_cast<float>(lamp.fuel_low);
		case 516: return static_cast<float>(lamp.rotor_brake);
		case 517: return static_cast<float>(lamp.wheel_brake);
		case 518: return static_cast<float>(lamp.navigation_lights);
		case 519: return static_cast<float>(lamp.hover_hold);
		case 520: return static_cast<float>(lamp.altitude_hold);
		case 521: return static_cast<float>(lamp.auto_pilot);
		case 522: return static_cast<float>(lamp.radar);
		case 523: return static_cast<float>(lamp.laser);
		case 524: return static_cast<float>(lamp.radar_jammer);
		case 525: return static_cast<float>(lamp.ir_jammer);
		case 526: return static_cast<float>(lamp.auto_counter_measures);
		case 527: return static_cast<float>(lamp.ase_auto_page);
		case 528: return static_cast<float>(lamp.config_stub_wings);
		case 529: return static_cast<float>(lamp.config_bay_doors);
		case 530: return static_cast<float>(lamp.config_gear);
		case 531: return static_cast<float>(lamp.config_gun);
		case 532: return static_cast<float>(lamp.gear_damaged);
		case 533: return static_cast<float>(lamp.gear_status);
		case 534: return static_cast<float>(lamp.gear_red);
		case 535: return static_cast<float>(lamp.gear_transition);
		case 536: return static_cast<float>(lamp.pilot_lh_main_mfd_focus);
		case 537: return static_cast<float>(lamp.pilot_rh_main_mfd_focus);
		case 538: return static_cast<float>(lamp.co_pilot_lh_main_mfd_focus);
		case 539: return static_cast<float>(lamp.co_pilot_rh_main_mfd_focus);
		case 540: return static_cast<float>(lamp.altitude_hold);
		default: break;
	}

	return 0.0f;
}

float getHokumSpecificData(int commandID)
{
	hokum_lamp_flags lamp = pMem->cockpit_lamps.hokum_lamps;

	switch (commandID)
	{
		case 501: return static_cast<float>(lamp.master_caution);
		case 502: return static_cast<float>(lamp.left_engine_fire);
		case 503: return static_cast<float>(lamp.apu_fire);
		case 504: return static_cast<float>(lamp.right_engine_fire);
		case 505: return static_cast<float>(lamp.altitude_hold);
		case 506: return static_cast<float>(lamp.fire_extinguiser);
		case 507: return static_cast<float>(lamp.hydraulic_pressure);
		case 508: return static_cast<float>(lamp.oil_pressure);
		case 509: return static_cast<float>(lamp.oil_temperature);
		case 510: return static_cast<float>(lamp.rotor_brake);
		case 511: return static_cast<float>(lamp.overtorque);
		case 512: return static_cast<float>(lamp.fuel_low);
		case 513: return static_cast<float>(lamp.rotor_rpm);
		case 514: return static_cast<float>(lamp.wheel_brake);
		case 515: return static_cast<float>(lamp.navigation_lights);
		case 516: return static_cast<float>(lamp.hover_hold);
		case 517: return static_cast<float>(lamp.altitude_hold);
		case 518: return static_cast<float>(lamp.auto_pilot);
		case 519: return static_cast<float>(lamp.radar);
		case 520: return static_cast<float>(lamp.laser);
		case 521: return static_cast<float>(lamp.radar_jammer);
		case 522: return static_cast<float>(lamp.ir_jammer);
		case 523: return static_cast<float>(lamp.auto_counter_measures);
		case 524: return static_cast<float>(lamp.ase_auto_page);
		case 525: return static_cast<float>(lamp.gear_damaged);
		case 526: return static_cast<float>(lamp.gear_status);
		case 527: return static_cast<float>(lamp.gear_red);
		case 528: return static_cast<float>(lamp.pilot_lh_mfd_focus);
		case 529: return static_cast<float>(lamp.pilot_rh_mfd_focus);
		case 530: return static_cast<float>(lamp.co_pilot_lh_mfd_focus);
		case 531: return static_cast<float>(lamp.co_pilot_rh_mfd_focus);
		case 532: return static_cast<float>(lamp.laser);
		default: break;
	}

	return 0.0f;
}

float getBlackhawkSpecificData(int commandID)
{
	switch (commandID)
	{
	case 0: return 0.0f;
	default: break;
	}

	return 0.0f;
}

float getHindSpecificData(int commandID)
{
	switch (commandID)
	{
	case 0: return 0.0f;
	default: break;
	}

	return 0.0f;
}

float getAH64ASpecificData(int commandID)
{
	switch (commandID)
	{
	case 0: return 0.0f;
	default: break;
	}

	return 0.0f;
}

float getKa50SpecificData(int commandID)
{
	switch (commandID)
	{
	case 0: return 0.0f;
	default: break;
	}

	return 0.0f;
}

float getValue(int commandID)
{
	if (pMem->version != SHARED_MEM_DATA_VERSION)
		return -100000.0f;

	if (commandID <= 500)
	{
		switch (commandID)
		{
		case 20: return pMem->time_of_day / 3600.f;
		case 30: return pMem->indicated_airspeed * 3.6f;
		case 32: return pMem->vertical_speed;
		case 34: return pMem->indicated_slip;
		case 40: return pMem->barometric_altitude;
		case 42: return pMem->heading * 180 / M_PI;
		case 46: return pMem->roll * 180 / -M_PI;
		case 48: return pMem->pitch * 180 / M_PI;
		case 50: return pMem->fuel_weight;
		case 52: return pMem->g_force;
		case 64: return pMem->left_engine_rpm;
		case 65: return pMem->right_engine_rpm;
		case 66: return pMem->left_engine_n1_rpm;
		case 67: return pMem->right_engine_n1_rpm;
		case 72: return pMem->left_engine_temp - 273.f;
		case 73: return pMem->right_engine_temp - 273.f;
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
		case GUNSHIP_TYPE_APACHE: return getApacheSpecificData(commandID);
		case GUNSHIP_TYPE_HAVOC: return getHavocSpecificData(commandID);
		case GUNSHIP_TYPE_COMANCHE: return getComancheSpecificData(commandID);
		case GUNSHIP_TYPE_HOKUM: return getHokumSpecificData(commandID);
		case GUNSHIP_TYPE_BLACKHAWK: return getBlackhawkSpecificData(commandID);
		case GUNSHIP_TYPE_HIND: return getHindSpecificData(commandID);
		case GUNSHIP_TYPE_AH64A: return getAH64ASpecificData(commandID);
		case GUNSHIP_TYPE_KA50: return getKa50SpecificData(commandID);
		default: break;
		}
	}

	return 0.0f;
}
