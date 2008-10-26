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
#include "3d/3dsubobj.h"

#include "hi_3dwiper.h"
#include "../../dynamics/common/co_undercarriage.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define SHUTOFF_MOVEMENT_RATE rad(120.0)
#define ROTOR_BRAKE_MOVEMENT_RATE rad(120.0)
#define COLLECTIVE_THROTTLE_MOVEMENT_RATE rad(120.0)
#define GEAR_LEVER_MOVEMENT_RATE rad(270.0)
#define ELECTRICAL_GAUGE_MOVEMENT_RATE rad(480.0)

static object_3d_instance
	*virtual_pilot_cockpit_inst3d,
	*virtual_cockpit_canopy_inst3d,
	*virtual_cockpit_pilot_door_inst3d,

	*virtual_cockpit_hud_glass_inst3d,
	*virtual_cockpit_hud_display_inst3d,
	*virtual_cockpit_map_display_inst3d,
	*virtual_cockpit_pilot_instruments_inst3d,
	*virtual_cockpit_pilot_secondary_instruments_inst3d,
	*virtual_cockpit_warning_lamps_inst3d,
	*virtual_cockpit_main_rotor_inst3d,
	*virtual_cockpit_adi_inst3d,
	*virtual_cockpit_hsi_inst3d,
	*virtual_cockpit_ekran_display_inst3d,
	*virtual_cockpit_compass_inst3d;

static object_3d_sub_instance
	*high_detail,
	*door_high_detail,
	*door_handle,
	*fan_object,
	*spinning_fan_object,
	*compass_object,
	*airspeed_needle,
	*vvi_needle,
	*radar_altimeter,
	*barometric_altimeter_short,
	*barometric_altimeter_long,
	*bank_indicator,
	*hover_indicator_speed,
	*hover_indicator_sideways,
	*hover_indicator_vvi,
	*pitch_ladder_pitch,
	*pitch_ladder_roll,
	*horizon_ball,
	*pilot_head_object,
	*hud_view_object,
	*map_view_object,
	*shutoff_valve_left,
	*shutoff_valve_right,
	*rotor_brake,
	*rotor_rpm,
	*left_n1_rpm,
	*right_n1_rpm,
	*left_temperature,
	*left_temperature_small,
	*right_temperature,
	*right_temperature_small,
	*radio_compass,
	*compass_waypoint_needle,
	*compass_waypoint_heading_needle,
	*epr_limits,
	*left_epr_needle,
	*right_epr_needle,
	*blade_pitch_needle,
	*g_force,
	*sidewind,
	*fuel_quantity,
	*primary_hydraulic_psi,
	*secondary_hydraulic_psi,
	*gear_hydraulic_psi,
	*clock_hour_hand,
	*clock_minute_hand,
	*clock_second_hand,

	*gear_lever,
	*collective,
	*collective_throttle,
	*pedal_link,
	*left_pedal,
	*right_pedal,

	*apu_rpm_needle,
	*apu_start_switch,
	*apu_stop_switch,
	*apu_ready_light,
	*apu_rpm_light,
	*apu_bleedair_lights,
	*engine_start_switch,
	*engine_select_switch,
	*engine_start_light,

	*left_battery_ammeter,
	*right_battery_ammeter,
	*apu_ammeter,
	*voltmeter,
	*left_generator_ammeter,
	*right_generator_ammeter,

	*left_wheel_down_light,
	*right_wheel_down_light,
	*nose_wheel_down_light,
	*wheels_up_light,
	*gear_operational_light,
	*gear_fail_light,
	*cockpit_open_light,
	*cockpit_sealed_light,
	*park_brake_light,
	*auto_hover_light,
	*auto_pilot_light,
	*auto_pilot_off_light,
	*auto_altitude_light,
	*auto_altitude_off_light,
	*external_light_lamps,
	*left_outer_pylon_light,
	*left_inner_pylon_light,
	*right_inner_pylon_light,
	*right_outer_pylon_light,

	*fire_light,
	*left_engine_fire_light,
	*right_engine_fire_light,
	*left_engine_fail_light,
	*right_engine_fail_light,
	*over_stress_light,
	*low_fuel_lights,
	*gyre_fail_lights,

	*fuel_switches,
	*external_light_switches,
	*radio_navigation_switches,
	*weapon_select_switch,
	*master_arm_switches,
	*rocket_salvo_switch
	;

cockpit_switch
    switch_animations[3];

// crew position in first dimension, min/max limit in second
static vec3d head_limits[2][2];

static int
	cockpit_fan_enabled = FALSE,
	open_door = TRUE;

static float
	door_handle_timer = 0.0,
	door_state = 0.0;

//static void animate_shutoff_valve(object3d_sub_instance* inst, int closed);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_hind_3d_cockpit (void)
{
	int switch_no = 0;
	//
	// 3D instances
	//

	virtual_pilot_cockpit_inst3d = construct_3d_object (OBJECT_3D_MI24V_PILOT_COCKPIT);
	virtual_cockpit_inst3d = virtual_pilot_cockpit_inst3d;
	virtual_cockpit_canopy_inst3d = construct_3d_object (OBJECT_3D_MI24V_CANOPY);
	virtual_cockpit_pilot_door_inst3d = construct_3d_object(OBJECT_3D_MI24V_PILOT_DOOR);

	virtual_cockpit_hud_display_inst3d = construct_3d_object (OBJECT_3D_MI24V_HUD_DISPLAY);
	virtual_cockpit_map_display_inst3d = construct_3d_object (OBJECT_3D_MI24V_MAP_DISPLAY);

	virtual_cockpit_pilot_instruments_inst3d = construct_3d_object (OBJECT_3D_MI24V_PILOT_INSTRUMENTS);
	virtual_cockpit_pilot_secondary_instruments_inst3d = construct_3d_object (OBJECT_3D_MI24V_PILOT_SECONDARY_INSTRUMENTS);
	virtual_cockpit_warning_lamps_inst3d = construct_3d_object (OBJECT_3D_MI24V_PILOT_WARNING_LAMPS);

	pilot_head_pitch_datum = 0.0;

	co_pilot_head_pitch_datum = 0.0;

	virtual_cockpit_hud_glass_inst3d = construct_3d_object (OBJECT_3D_HAVOC_VIRTUAL_COCKPIT_HUD_GLASS_LEVEL1);
	virtual_cockpit_main_rotor_inst3d = construct_3d_object (OBJECT_3D_HAVOC_VIRTUAL_COCKPIT_MAIN_ROTOR);
	virtual_cockpit_adi_inst3d = construct_3d_object (OBJECT_3D_HAVOC_VIRTUAL_COCKPIT_INSTRUMENTS_ADI);

	virtual_cockpit_main_rotor_inst3d->sub_objects[0].relative_position.z = -2.9;
	virtual_cockpit_main_rotor_inst3d->sub_objects[0].relative_position.y = 1.6;

	virtual_cockpit_hsi_inst3d = construct_3d_object (OBJECT_3D_HAVOC_VIRTUAL_COCKPIT_INSTRUMENTS_HSI_LEVEL1);
	virtual_cockpit_ekran_display_inst3d = construct_3d_object (OBJECT_3D_HAVOC_VIRTUAL_COCKPIT_DISPLAYS_EKRAN);
	virtual_cockpit_compass_inst3d = construct_3d_object (OBJECT_3D_HAVOC_VIRTUAL_COCKPIT_INSTRUMENTS_COMPASS_LEVEL1);

	//
	// wipers and rain
	//

	initialise_hind_3d_cockpit_wiper ();

	//
	// virtual cockpit cameras
	//

	initialise_common_virtual_cockpit_cameras ();

	pilot_head_object = find_sub_object(virtual_pilot_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_PILOT_HEAD);
	hud_view_object = find_sub_object(virtual_pilot_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_COCKPIT_VIEW_MFD_FL);
	map_view_object = find_sub_object(virtual_pilot_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_COCKPIT_VIEW_MFD_FR);

	high_detail = find_sub_object(virtual_pilot_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_HIGH_DETAIL);
	door_high_detail = find_sub_object(virtual_cockpit_pilot_door_inst3d, OBJECT_3D_SUB_OBJECT_HIGH_DETAIL);
	door_handle = find_sub_object(virtual_cockpit_pilot_door_inst3d, OBJECT_3D_SUB_OBJECT_DOOR_HANDLE);
	compass_object = find_sub_object(virtual_pilot_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_HAVOC_VIRTUAL_COCKPIT_COMPASS_HEADING_NULL);
	fan_object = find_sub_object(virtual_pilot_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_FAN);
	spinning_fan_object = find_sub_object(virtual_pilot_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_SPINNING_FAN);
	airspeed_needle = find_sub_object(virtual_cockpit_pilot_instruments_inst3d, OBJECT_3D_SUB_OBJECT_AIRSPEED_NEEDLE);
	vvi_needle = find_sub_object(virtual_cockpit_pilot_instruments_inst3d, OBJECT_3D_SUB_OBJECT_VERTICAL_VELOCITY_NEEDLE);
	radar_altimeter = find_sub_object(virtual_cockpit_pilot_instruments_inst3d, OBJECT_3D_SUB_OBJECT_RADAR_ALTIMETER);
	barometric_altimeter_short = find_sub_object(virtual_cockpit_pilot_instruments_inst3d, OBJECT_3D_SUB_OBJECT_BAROMETRIC_ALTIMETER_SHORT);
	barometric_altimeter_long = find_sub_object(virtual_cockpit_pilot_instruments_inst3d, OBJECT_3D_SUB_OBJECT_BAROMETRIC_ALTIMETER_LONG);
	bank_indicator = find_sub_object(virtual_cockpit_pilot_instruments_inst3d, OBJECT_3D_SUB_OBJECT_BANK_INDICATOR);

	hover_indicator_speed = find_sub_object(virtual_cockpit_pilot_instruments_inst3d, OBJECT_3D_SUB_OBJECT_HOVER_INDICATOR_LONGITUDINAL);
	hover_indicator_sideways = find_sub_object(virtual_cockpit_pilot_instruments_inst3d, OBJECT_3D_SUB_OBJECT_HOVER_INDICATOR_SIDWAYS);
	hover_indicator_vvi = find_sub_object(virtual_cockpit_pilot_instruments_inst3d, OBJECT_3D_SUB_OBJECT_HOVER_INDICATOR_VVI);

	pitch_ladder_pitch = find_sub_object(virtual_cockpit_pilot_instruments_inst3d, OBJECT_3D_SUB_OBJECT_COCKPIT_ADI);
	pitch_ladder_roll = find_sub_object(virtual_cockpit_pilot_instruments_inst3d, OBJECT_3D_SUB_OBJECT_COCKPIT_ADI_PITCH_NULL);
	horizon_ball = find_sub_object(virtual_cockpit_pilot_instruments_inst3d, OBJECT_3D_SUB_OBJECT_HAVOC_VIRTUAL_COCKPIT_ADI);

	shutoff_valve_left = find_sub_object(virtual_cockpit_pilot_instruments_inst3d, OBJECT_3D_SUB_OBJECT_SHUTOFFVALVE_LEFT);
	shutoff_valve_right = find_sub_object(virtual_cockpit_pilot_instruments_inst3d, OBJECT_3D_SUB_OBJECT_SHUTOFFVALVE_RIGHT);
	rotor_brake = find_sub_object(virtual_cockpit_pilot_instruments_inst3d, OBJECT_3D_SUB_OBJECT_ROTOR_BRAKE);

	rotor_rpm = find_sub_object(virtual_cockpit_pilot_instruments_inst3d, OBJECT_3D_SUB_OBJECT_ROTOR_RPM_NEEDLE);
	left_n1_rpm = find_sub_object(virtual_cockpit_pilot_instruments_inst3d, OBJECT_3D_SUB_OBJECT_LEFT_N1_RPM_NEEDLE);
	right_n1_rpm = find_sub_object(virtual_cockpit_pilot_instruments_inst3d, OBJECT_3D_SUB_OBJECT_RIGHT_N1_RPM_NEEDLE);

	left_temperature = find_sub_object(virtual_cockpit_pilot_instruments_inst3d, OBJECT_3D_SUB_OBJECT_LEFT_TEMPERATURE_NEEDLE);
	left_temperature_small = find_sub_object(virtual_cockpit_pilot_instruments_inst3d, OBJECT_3D_SUB_OBJECT_LEFT_TEMPERATURE_SMALL_NEEDLE);
	right_temperature = find_sub_object(virtual_cockpit_pilot_instruments_inst3d, OBJECT_3D_SUB_OBJECT_RIGHT_TEMPERATURE_NEEDLE);
	right_temperature_small = find_sub_object(virtual_cockpit_pilot_instruments_inst3d, OBJECT_3D_SUB_OBJECT_RIGHT_TEMPERATURE_SMALL_NEEDLE);

	radio_compass = find_sub_object(virtual_cockpit_pilot_instruments_inst3d, OBJECT_3D_SUB_OBJECT_COMPASS_ROSE);
	compass_waypoint_needle = find_sub_object(virtual_cockpit_pilot_instruments_inst3d, OBJECT_3D_SUB_OBJECT_COMPASS_WAYPOINT_NEEDLE);
	compass_waypoint_heading_needle = find_sub_object(virtual_cockpit_pilot_instruments_inst3d, OBJECT_3D_SUB_OBJECT_COMPASS_WAYPOINT_HEADING_NEEDLE);

	epr_limits = find_sub_object(virtual_cockpit_pilot_instruments_inst3d, OBJECT_3D_SUB_OBJECT_EPR_LIMITS);
	left_epr_needle = find_sub_object(virtual_cockpit_pilot_instruments_inst3d, OBJECT_3D_SUB_OBJECT_LEFT_EPR_NEEDLE);
	right_epr_needle = find_sub_object(virtual_cockpit_pilot_instruments_inst3d, OBJECT_3D_SUB_OBJECT_RIGHT_EPR_NEEDLE);

	blade_pitch_needle = find_sub_object(virtual_cockpit_pilot_instruments_inst3d, OBJECT_3D_SUB_OBJECT_BLADE_PITCH_NEEDLE);
	g_force = find_sub_object(virtual_cockpit_pilot_instruments_inst3d, OBJECT_3D_SUB_OBJECT_G_FORCE_NEEDLE);
	sidewind = find_sub_object(virtual_cockpit_pilot_instruments_inst3d, OBJECT_3D_SUB_OBJECT_SIDEWIND_NEEDLE);
	fuel_quantity = find_sub_object(virtual_cockpit_pilot_instruments_inst3d, OBJECT_3D_SUB_OBJECT_FUEL_QUANTITY_NEEDLE);
	primary_hydraulic_psi = find_sub_object(virtual_cockpit_pilot_instruments_inst3d, OBJECT_3D_SUB_OBJECT_PRIMARY_HYDRAULIC_NEEDLE);
	secondary_hydraulic_psi = find_sub_object(virtual_cockpit_pilot_instruments_inst3d, OBJECT_3D_SUB_OBJECT_SECONDARY_HYDRAULIC_NEEDLE);
	gear_hydraulic_psi = find_sub_object(virtual_cockpit_pilot_instruments_inst3d, OBJECT_3D_SUB_OBJECT_GEAR_HYDRAULIC_NEEDLE);


	clock_hour_hand = find_sub_object(virtual_cockpit_pilot_instruments_inst3d, OBJECT_3D_SUB_OBJECT_CLOCK_HOUR_HAND);
	clock_minute_hand = find_sub_object(virtual_cockpit_pilot_instruments_inst3d, OBJECT_3D_SUB_OBJECT_CLOCK_MINUTE_HAND);
	clock_second_hand = find_sub_object(virtual_cockpit_pilot_instruments_inst3d, OBJECT_3D_SUB_OBJECT_CLOCK_SECOND_HAND);

	gear_lever = find_sub_object(virtual_cockpit_pilot_instruments_inst3d, OBJECT_3D_SUB_OBJECT_GEAR_LEVER);
	collective = find_sub_object(virtual_cockpit_pilot_instruments_inst3d, OBJECT_3D_SUB_OBJECT_COLLECTIVE);
	collective_throttle = find_sub_object(virtual_cockpit_pilot_instruments_inst3d, OBJECT_3D_SUB_OBJECT_COLLECTIVE_THROTTLE);

	pedal_link = find_sub_object(virtual_cockpit_pilot_instruments_inst3d, OBJECT_3D_SUB_OBJECT_PEDAL_LINK);
	left_pedal = find_sub_object(virtual_cockpit_pilot_instruments_inst3d, OBJECT_3D_SUB_OBJECT_LEFT_PEDAL);
	right_pedal = find_sub_object(virtual_cockpit_pilot_instruments_inst3d, OBJECT_3D_SUB_OBJECT_RIGHT_PEDAL);

	left_battery_ammeter = find_sub_object(virtual_cockpit_pilot_instruments_inst3d, OBJECT_3D_SUB_OBJECT_LEFT_BATTERY_AMMETER_NEEDLE);
	right_battery_ammeter = find_sub_object(virtual_cockpit_pilot_instruments_inst3d, OBJECT_3D_SUB_OBJECT_RIGHT_BATTERY_AMMETER_NEEDLE);
	apu_ammeter = find_sub_object(virtual_cockpit_pilot_instruments_inst3d, OBJECT_3D_SUB_OBJECT_APU_AMMETER_NEEDLE);
	voltmeter = find_sub_object(virtual_cockpit_pilot_instruments_inst3d, OBJECT_3D_SUB_OBJECT_VOLTMETER_NEEDLE);
	left_generator_ammeter = find_sub_object(virtual_cockpit_pilot_instruments_inst3d, OBJECT_3D_SUB_OBJECT_LEFT_GENERATOR_AMMETER_NEEDLE);
	right_generator_ammeter = find_sub_object(virtual_cockpit_pilot_instruments_inst3d, OBJECT_3D_SUB_OBJECT_RIGHT_GENERATOR_AMMETER_NEEDLE);

	apu_rpm_needle = find_sub_object(virtual_cockpit_pilot_instruments_inst3d, OBJECT_3D_SUB_OBJECT_APU_RPM_NEEDLE);
	engine_select_switch = find_sub_object(virtual_cockpit_pilot_instruments_inst3d, OBJECT_3D_SUB_OBJECT_ENGINE_SELECT_SWITCH);
	engine_start_switch = find_sub_object(virtual_cockpit_pilot_instruments_inst3d, OBJECT_3D_SUB_OBJECT_ENGINE_START_SWITCH);
	apu_start_switch = find_sub_object(virtual_cockpit_pilot_instruments_inst3d, OBJECT_3D_SUB_OBJECT_APU_START_SWITCH);
	apu_stop_switch = find_sub_object(virtual_cockpit_pilot_instruments_inst3d, OBJECT_3D_SUB_OBJECT_APU_STOP_SWITCH);

	initialise_switch(&switch_animations[switch_no], &engine_start_switch->relative_position.x, -0.0065, 0.3, 0.25);
	engine_start_switch_animation_object = &switch_animations[switch_no];
	initialise_switch(&switch_animations[++switch_no], &apu_start_switch->relative_position.x, -0.0065, 0.3, 0.0);
	apu_start_switch_animation_object = &switch_animations[switch_no];
	initialise_switch(&switch_animations[++switch_no], &apu_stop_switch->relative_position.x, -0.0065, 0.3, 0.0);
	apu_stop_switch_animation_object = &switch_animations[switch_no];

	apu_ready_light = find_sub_object(virtual_cockpit_warning_lamps_inst3d, OBJECT_3D_SUB_OBJECT_APU_READY_LIGHT);
	apu_rpm_light = find_sub_object(virtual_cockpit_warning_lamps_inst3d, OBJECT_3D_SUB_OBJECT_APU_RPM_LIGHT);
	apu_bleedair_lights = find_sub_object(virtual_cockpit_warning_lamps_inst3d, OBJECT_3D_SUB_OBJECT_APU_BLEEDAIR_LIGHT);
	engine_start_light = find_sub_object(virtual_cockpit_warning_lamps_inst3d, OBJECT_3D_SUB_OBJECT_ENGINE_START_LIGHT);

	left_wheel_down_light = find_sub_object(virtual_cockpit_warning_lamps_inst3d, OBJECT_3D_SUB_OBJECT_LEFT_WHEEL_DOWN_LIGHT);
	right_wheel_down_light = find_sub_object(virtual_cockpit_warning_lamps_inst3d, OBJECT_3D_SUB_OBJECT_RIGHT_WHEEL_DOWN_LIGHT);
	nose_wheel_down_light = find_sub_object(virtual_cockpit_warning_lamps_inst3d, OBJECT_3D_SUB_OBJECT_NOSE_WHEEL_DOWN_LIGHT);
	wheels_up_light = find_sub_object(virtual_cockpit_warning_lamps_inst3d, OBJECT_3D_SUB_OBJECT_WHEELS_UP_LIGHT);
	gear_operational_light = find_sub_object(virtual_cockpit_warning_lamps_inst3d, OBJECT_3D_SUB_OBJECT_GEAR_OPERATIONAL_LIGHT);
	gear_fail_light = find_sub_object(virtual_cockpit_warning_lamps_inst3d, OBJECT_3D_SUB_OBJECT_GEAR_FAIL_LIGHT);
	cockpit_open_light = find_sub_object(virtual_cockpit_warning_lamps_inst3d, OBJECT_3D_SUB_OBJECT_COCKPIT_OPEN_LIGHT);
	cockpit_sealed_light = find_sub_object(virtual_cockpit_warning_lamps_inst3d, OBJECT_3D_SUB_OBJECT_COCKPIT_SEALED_LIGHT);
	park_brake_light = find_sub_object(virtual_cockpit_warning_lamps_inst3d, OBJECT_3D_SUB_OBJECT_PARK_BRAKE_LIGHT);
	auto_hover_light = find_sub_object(virtual_cockpit_warning_lamps_inst3d, OBJECT_3D_SUB_OBJECT_AUTO_HOVER_LIGHT);
	auto_pilot_light = find_sub_object(virtual_cockpit_warning_lamps_inst3d, OBJECT_3D_SUB_OBJECT_AUTO_PILOT_LIGHT);
	auto_pilot_off_light = find_sub_object(virtual_cockpit_warning_lamps_inst3d, OBJECT_3D_SUB_OBJECT_AUTO_PILOT_OFF_LIGHT);
	auto_altitude_light = find_sub_object(virtual_cockpit_warning_lamps_inst3d, OBJECT_3D_SUB_OBJECT_ALTITUDE_HOLD_LIGHT);
	auto_altitude_off_light = find_sub_object(virtual_cockpit_warning_lamps_inst3d, OBJECT_3D_SUB_OBJECT_ALTITUDE_HOLD_OFF_LIGHT);
	external_light_lamps = find_sub_object(virtual_cockpit_warning_lamps_inst3d, OBJECT_3D_SUB_OBJECT_EXTERNAL_LIGHT_LAMPS);
	left_outer_pylon_light = find_sub_object(virtual_cockpit_warning_lamps_inst3d, OBJECT_3D_SUB_OBJECT_LEFT_OUTER_PYLON_LIGHT);
	left_inner_pylon_light = find_sub_object(virtual_cockpit_warning_lamps_inst3d, OBJECT_3D_SUB_OBJECT_LEFT_INNER_PYLON_LIGHT);
	right_inner_pylon_light = find_sub_object(virtual_cockpit_warning_lamps_inst3d, OBJECT_3D_SUB_OBJECT_RIGHT_INNER_PYLON_LIGHT);
	right_outer_pylon_light = find_sub_object(virtual_cockpit_warning_lamps_inst3d, OBJECT_3D_SUB_OBJECT_RIGHT_OUTER_PYLON_LIGHT);

	fire_light = find_sub_object(virtual_cockpit_warning_lamps_inst3d, OBJECT_3D_SUB_OBJECT_FIRE_LIGHT);
	left_engine_fire_light = find_sub_object(virtual_cockpit_warning_lamps_inst3d, OBJECT_3D_SUB_OBJECT_LEFT_ENGINE_FIRE_LIGHT);
	right_engine_fire_light = find_sub_object(virtual_cockpit_warning_lamps_inst3d, OBJECT_3D_SUB_OBJECT_RIGHT_ENGINE_FIRE_LIGHT);
	left_engine_fail_light = find_sub_object(virtual_cockpit_warning_lamps_inst3d, OBJECT_3D_SUB_OBJECT_LEFT_ENGINE_FAIL_LIGHT);
	right_engine_fail_light = find_sub_object(virtual_cockpit_warning_lamps_inst3d, OBJECT_3D_SUB_OBJECT_RIGHT_ENGINE_FAIL_LIGHT);
	over_stress_light = find_sub_object(virtual_cockpit_warning_lamps_inst3d, OBJECT_3D_SUB_OBJECT_OVER_STRESS_LIGHT);
	low_fuel_lights = find_sub_object(virtual_cockpit_warning_lamps_inst3d, OBJECT_3D_SUB_OBJECT_LOW_FUEL_LIGHTS);
	gyre_fail_lights = find_sub_object(virtual_cockpit_warning_lamps_inst3d, OBJECT_3D_SUB_OBJECT_GYRO_FAIL_LIGHTS);

	fuel_switches = find_sub_object(virtual_cockpit_pilot_secondary_instruments_inst3d, OBJECT_3D_SUB_OBJECT_FUEL_SWITCHES);
	external_light_switches = find_sub_object(virtual_cockpit_pilot_secondary_instruments_inst3d, OBJECT_3D_SUB_OBJECT_EXTERNAL_LIGHT_SWITCHES);
	radio_navigation_switches = find_sub_object(virtual_cockpit_pilot_secondary_instruments_inst3d, OBJECT_3D_SUB_OBJECT_RADIO_NAVIGATION_SWITCHES);
	weapon_select_switch = find_sub_object(virtual_cockpit_pilot_instruments_inst3d, OBJECT_3D_SUB_OBJECT_WEAPON_SELECT_SWITCH);
	rocket_salvo_switch = find_sub_object(virtual_cockpit_pilot_instruments_inst3d, OBJECT_3D_SUB_OBJECT_ROCKET_SALVO_SWITCH);
	master_arm_switches = find_sub_object(virtual_cockpit_pilot_secondary_instruments_inst3d, OBJECT_3D_SUB_OBJECT_MASTER_ARM_SWITCHES);

	ASSERT(switch_no == ARRAY_LENGTH(switch_animations) - 1);
	//ASSERT(FALSE);
#ifdef DEBUG  // don't limit in debug (for all practical purposes
	// pilot limits
	head_limits[0][0].x = -10;
	head_limits[0][1].x =  10;
	head_limits[0][0].y = -10;
	head_limits[0][1].y =  10;
	head_limits[0][0].z = -10;
	head_limits[0][1].z =  10;

	// co-pilot limits
	head_limits[1][0].x = -10;
	head_limits[1][1].x =  10;
	head_limits[1][0].y = -10;
	head_limits[1][1].y =  10;
	head_limits[1][0].z = -10;
	head_limits[1][1].z =  10;
#else
	// pilot limits
	head_limits[0][0].x = -0.25;
	head_limits[0][1].x =  0.25;
	head_limits[0][0].y = -0.3;
	head_limits[0][1].y =  0.3;
	head_limits[0][0].z = -0.10;
	head_limits[0][1].z =  0.50;

	// co-pilot limits
	head_limits[1][0].x = -0.2;
	head_limits[1][1].x =  0.2;
	head_limits[1][0].y = -0.2;
	head_limits[1][1].y =  0.2;
	head_limits[1][0].z = -0.05;
	head_limits[1][1].z =  0.3;
#endif

	open_door = !get_local_entity_int_value(get_gunship_entity(), INT_TYPE_AIRBORNE_AIRCRAFT) && command_line_dynamics_engine_startup;
	wide_cockpit_nr = WIDEVIEW_HIND_PILOT;
	set_global_wide_cockpit(TRUE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_hind_3d_cockpit (void)
{
	//
	// 3D instances
	//

	destruct_3d_object (virtual_pilot_cockpit_inst3d);
	destruct_3d_object (virtual_cockpit_canopy_inst3d);
	destruct_3d_object (virtual_cockpit_pilot_door_inst3d);

	destruct_3d_object (virtual_cockpit_hud_glass_inst3d);
	destruct_3d_object (virtual_cockpit_hud_display_inst3d);
	destruct_3d_object (virtual_cockpit_map_display_inst3d);
	destruct_3d_object (virtual_cockpit_main_rotor_inst3d);
	destruct_3d_object (virtual_cockpit_pilot_instruments_inst3d);
	destruct_3d_object (virtual_cockpit_pilot_secondary_instruments_inst3d);
	destruct_3d_object (virtual_cockpit_warning_lamps_inst3d);
	destruct_3d_object (virtual_cockpit_adi_inst3d);
	destruct_3d_object (virtual_cockpit_hsi_inst3d);
	destruct_3d_object (virtual_cockpit_ekran_display_inst3d);
	destruct_3d_object (virtual_cockpit_compass_inst3d);

	pilot_head_object = NULL;

	//
	// wipers and rain
	//

	deinitialise_hind_3d_cockpit_wiper();

	//
	// virtual cockpit cameras
	//

	deinitialise_common_virtual_cockpit_cameras ();
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void toggle_mi24_cockpit_fan(void)
{
	cockpit_fan_enabled = !cockpit_fan_enabled;
}

#define FAN_ROTATION_SPEED   (PI2 * 4.0)
#define FAN_BLUR_TRESHOLD    (PI2 * 2.0)

static void animate_fan(void)
{
	static float fan_speed = 0.0;

	ASSERT(fan_object);

	if (fan_speed < FAN_ROTATION_SPEED && cockpit_fan_enabled && electrical_system_active())
	{
		fan_speed += FAN_ROTATION_SPEED * get_delta_time();
		if (fan_speed > FAN_ROTATION_SPEED)
			fan_speed = FAN_ROTATION_SPEED;
	}
	else if (fan_speed > 0.0 && (!cockpit_fan_enabled || !electrical_system_active()))
	{
		fan_speed -= FAN_ROTATION_SPEED * 0.4 * get_delta_time();
		if (fan_speed < 0.0)
			fan_speed = 0.0;
	}

	fan_object->relative_roll -= fan_speed * get_delta_time();
	while (fan_object->relative_roll < 0.0)
		fan_object->relative_roll += PI2;
	spinning_fan_object->relative_roll = fan_object->relative_roll;

	if (fan_speed > FAN_BLUR_TRESHOLD)
	{
		fan_object->visible_object = FALSE;
		spinning_fan_object->visible_object = TRUE;
	}
	else
	{
		fan_object->visible_object = TRUE;
		spinning_fan_object->visible_object = FALSE;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void animate_rotor_brake(int enabled)
{
	float
		max_movement = ROTOR_BRAKE_MOVEMENT_RATE * get_delta_time(),
		brake_angle = 0.0;

	if (enabled)
		brake_angle = rad(-35.0);

	rotor_brake->relative_pitch += bound(brake_angle - rotor_brake->relative_pitch, -max_movement, max_movement);
}

static void animate_electrical_instruments(void)
{
	float
		max_movement = ELECTRICAL_GAUGE_MOVEMENT_RATE * get_delta_time(),
		angle = rad(98.0);

	if (electrical_system_active())
		angle = rad(-60.0);

	left_battery_ammeter->relative_roll += bound(angle - left_battery_ammeter->relative_roll, -max_movement, max_movement);
	right_battery_ammeter->relative_roll = left_battery_ammeter->relative_roll;
	apu_ammeter->relative_roll = left_battery_ammeter->relative_roll;
	voltmeter->relative_roll = left_battery_ammeter->relative_roll;
	left_generator_ammeter->relative_roll = left_battery_ammeter->relative_roll;
	right_generator_ammeter->relative_roll = left_battery_ammeter->relative_roll;
}

static void animate_collective_throttle(void)
{
	float
		max_movement = COLLECTIVE_THROTTLE_MOVEMENT_RATE * get_delta_time(),
		throttle_position = (current_flight_dynamics->main_rotor_governor_rpm - current_flight_dynamics->main_rotor_idle_rpm)
				/ (current_flight_dynamics->main_rotor_max_rpm - current_flight_dynamics->main_rotor_idle_rpm),
		angle = rad(-65.0) * throttle_position;

	collective_throttle->relative_roll += bound(angle - collective_throttle->relative_roll, -max_movement, max_movement);
}

static void animate_gear_lever(void)
{
	float
		max_movement = GEAR_LEVER_MOVEMENT_RATE * get_delta_time(),
		angle = 0.0;

	int uc_state = get_local_entity_undercarriage_state(get_gunship_entity());

	if (uc_state == AIRCRAFT_UNDERCARRIAGE_UP || uc_state == AIRCRAFT_UNDERCARRIAGE_RAISING)
		angle = rad(75.0);

	gear_lever->relative_roll += bound(angle - gear_lever->relative_roll, -max_movement, max_movement);
}

static void animate_weapon_switch(entity_sub_types selected_weapon)
{
	float
		max_movement = rad(360.0) * get_delta_time(),
		angle = 0.0;

	switch (selected_weapon)
	{
	case ENTITY_SUB_TYPE_WEAPON_9A642_12P7MM_ROUND:
		angle = rad(-82.0);
		break;
	case ENTITY_SUB_TYPE_WEAPON_S5:
	case ENTITY_SUB_TYPE_WEAPON_S8:
	case ENTITY_SUB_TYPE_WEAPON_S13:
		angle = rad(-110.0);
		break;
	case ENTITY_SUB_TYPE_WEAPON_GSH23L_23MM_ROUND:
		angle = rad(-170.0);
		break;
	case ENTITY_SUB_TYPE_WEAPON_ATAKA:
	case ENTITY_SUB_TYPE_WEAPON_AT6_SPIRAL:
	default:
		angle = rad(58.0);
		break;
	}

	weapon_select_switch->relative_roll += bound(angle - weapon_select_switch->relative_roll, -max_movement, max_movement);
}

void toggle_mi24_cockpit_doors(void)
{
	open_door = !open_door;

	if (open_door && door_handle_timer <= 0.0)
		door_handle_timer = 0.6;
}

static void animate_doors(void)
{
	const float door_movement_rate = 0.7 * get_delta_time();
	float new_state = door_state;

	if (open_door && door_handle_timer < 0.4)
		new_state += max(-door_state, -door_movement_rate);
	else
		new_state += min(1.0 - door_state, door_movement_rate);


	if (new_state != door_state)
	{
		door_state = new_state;
		animate_keyframed_sub_object_type(virtual_cockpit_pilot_door_inst3d, OBJECT_3D_SUB_OBJECT_CANOPY_DOORS, door_state);
		animate_keyframed_sub_object_type(virtual_cockpit_canopy_inst3d, OBJECT_3D_SUB_OBJECT_CANOPY_DOORS, door_state);
	}

	if (door_handle_timer > 0.0)
	{
		if (door_handle_timer > 0.4)  // pushing down
			door_handle->relative_pitch = (0.6 - door_handle_timer) * rad(-150.0);
		else if (door_handle_timer < 0.2)
			door_handle->relative_pitch = door_handle_timer * rad(-150.0);

		door_handle_timer -= get_delta_time();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_hind_3d_cockpit (void)
{
	animate_fan();
	animate_collective_throttle();
	animate_gear_lever();
	animate_electrical_instruments();
	animate_doors();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if 0
static void set_cockpit_white_lighting (matrix3x3 attitude)
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

	directional_light_colour.red		= 0.3;
	directional_light_colour.green	= 0.3;
	directional_light_colour.blue		= 0.3;

	directional_light_heading 			= rad (0.0);
	directional_light_pitch 			= rad (0.0);
	directional_light_roll 				= rad (0.0);

	switch (get_local_entity_int_value (get_session_entity (), INT_TYPE_DAY_SEGMENT_TYPE))
	{
		////////////////////////////////////////
		case DAY_SEGMENT_TYPE_DAWN:
		////////////////////////////////////////
		{
			ambient_light_colour.red		 		= 0.70;
			ambient_light_colour.green		  		= 0.70;
			ambient_light_colour.blue		  		= 0.70;

			directional_light_heading 				= rad (0.0);
			directional_light_pitch 				= rad (-15.0);
			directional_light_roll 					= rad (0.0);

			break;
		}
		////////////////////////////////////////
		case DAY_SEGMENT_TYPE_DAY:
		////////////////////////////////////////
		{
			ambient_light_colour.red		 		= 0.85;
			ambient_light_colour.green		  		= 0.85;
			ambient_light_colour.blue		  		= 0.85;

			directional_light_heading 				= rad (0.0);
			directional_light_pitch 				= rad (-40.0);
			directional_light_roll 					= rad (0.0);

			directional_light_pitch 				= rad (0.0);

			break;
		}
		////////////////////////////////////////
		case DAY_SEGMENT_TYPE_DUSK:
		////////////////////////////////////////
		{
			ambient_light_colour.red		 		= 0.65;
			ambient_light_colour.green		  		= 0.50;
			ambient_light_colour.blue		  		= 0.50;

			directional_light_heading 				= rad (0.0);
			directional_light_pitch 				= rad (-15.0);
			directional_light_roll 					= rad (0.0);

			break;
		}
		////////////////////////////////////////
		case DAY_SEGMENT_TYPE_NIGHT:
		////////////////////////////////////////
		{
			ambient_light_colour.red		 		= 0.45;
			ambient_light_colour.green		  		= 0.45;
			ambient_light_colour.blue		  		= 0.55;

			directional_light_heading 				= rad (0.0);
			directional_light_pitch 				= rad (-15.0);
			directional_light_roll 					= rad (0.0);

			break;
		}
	}

	set_3d_ambient_light (main_3d_single_light_env, &ambient_light_colour);

	get_3d_transformation_matrix (directional_light_rotation, directional_light_heading, directional_light_pitch, directional_light_roll);

	multiply_matrix3x3_matrix3x3 (result, directional_light_rotation, attitude);

	directional_light_direction.x = -result[2][0];
	directional_light_direction.y = -result[2][1];
	directional_light_direction.z = -result[2][2];

	set_3d_main_light_source (main_3d_single_light_env, &directional_light_colour, &directional_light_direction, FALSE);
}
#endif

static void set_cockpit_lighting (matrix3x3 attitude)
{
	light_colour
		ambient_light_colour,
		directional_light_colour;

	ambient_light_colour.red = 0.3 + ambient_3d_light.colour.red;
	ambient_light_colour.green = 0.3 + ambient_3d_light.colour.green;
	ambient_light_colour.blue = 0.3 + ambient_3d_light.colour.blue;

	set_3d_ambient_light (main_3d_single_light_env, &ambient_light_colour);

	directional_light_colour.red = bound(current_3d_sun->colour.red * 1.2, 0.0, 1.0);
	directional_light_colour.green = bound(current_3d_sun->colour.green * 1.2, 0.0, 1.0);
	directional_light_colour.blue = bound(current_3d_sun->colour.blue * 1.2, 0.0, 1.0);

	set_3d_main_light_source (main_3d_single_light_env, &directional_light_colour, &current_3d_sun->light_direction, FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_hind_3d_cockpit_hud_view_position(float* x, float* y, float* z)
{
	*x = hud_view_object->relative_position.x;
	*y = hud_view_object->relative_position.y;
	*z = hud_view_object->relative_position.z;
}

static void get_crew_viewpoint (viewpoint *crew_viewpoint)
{
	int is_copilot = get_local_entity_int_value (get_pilot_entity (), INT_TYPE_CREW_ROLE) == CREW_ROLE_CO_PILOT;

	viewpoint
		vp;

	object_3d_sub_instance*
		head_object;

	ASSERT (crew_viewpoint);

	// TODO: add co-pilot
	virtual_cockpit_inst3d = virtual_pilot_cockpit_inst3d;

	switch (get_view_mode())
		{
		case VIEW_MODE_COCKPIT_PANEL_SPECIAL_HAVOC_TV:
			head_object = map_view_object;
			break;

		case VIEW_MODE_COCKPIT_PANEL_SPECIAL_HAVOC_HUD:
			head_object = hud_view_object;
			break;

		default:
			head_object = pilot_head_object;
			break;
		}

	virtual_cockpit_inst3d->vp.x = 0.0;
	virtual_cockpit_inst3d->vp.y = 0.0;
	virtual_cockpit_inst3d->vp.z = 0.0;

	switch (get_view_mode())
	{
	case VIEW_MODE_COCKPIT_PANEL_SPECIAL_HAVOC_TV:
		head_object->relative_pitch = rad(10.0);
		break;
	case VIEW_MODE_COCKPIT_PANEL_SPECIAL_HAVOC_HUD:
		head_object->relative_pitch = rad(-5.0);
		break;

	default:
		// adjust pitch according to user preferance
		if (edit_wide_cockpit)
			pilot_head_pitch = rad ( wide_cockpit_position[wide_cockpit_nr].p );

		// rotate head
		head_object->relative_heading = -pilot_head_heading;
		head_object->relative_pitch = -pilot_head_pitch;

		// adjust position according to user preferance
		head_object->relative_position.x = wide_cockpit_position[wide_cockpit_nr].x;
		head_object->relative_position.y = wide_cockpit_position[wide_cockpit_nr].y;
		head_object->relative_position.z = wide_cockpit_position[wide_cockpit_nr].z;

		// adjust for track-IR position
		if (query_TIR_active())
		{
			head_object->relative_position.x -= current_custom_cockpit_viewpoint.x;
			head_object->relative_position.y -= current_custom_cockpit_viewpoint.y;
			head_object->relative_position.z -= current_custom_cockpit_viewpoint.z;
		}

		// keep head inside reasonable limimts
		head_object->relative_position.x = bound(head_object->relative_position.x, head_limits[is_copilot][0].x, head_limits[is_copilot][1].x);
		head_object->relative_position.y = bound(head_object->relative_position.y, head_limits[is_copilot][0].y, head_limits[is_copilot][1].y);
		head_object->relative_position.z = bound(head_object->relative_position.z, head_limits[is_copilot][0].z, head_limits[is_copilot][1].z);

#if 0
		if (is_copilot)
		{
			// adjust for offset of co-pilot's cockpit compared to pilot's
			head_object->relative_position.y += -0.30;
			head_object->relative_position.z += 1.32;
		}
#endif
	}

	get_local_entity_attitude_matrix (get_gunship_entity (), virtual_cockpit_inst3d->vp.attitude);
	get_3d_sub_object_world_viewpoint (head_object, &vp);
	get_local_entity_vec3d (get_gunship_entity (), VEC3D_TYPE_POSITION, &main_vp.position);

	main_vp.x += vp.x;
	main_vp.y += vp.y;
	main_vp.z += vp.z;

	memcpy (main_vp.attitude, vp.attitude, sizeof (matrix3x3));

	vp.x = -vp.x;
	vp.y = -vp.y;
	vp.z = -vp.z;

	multiply_transpose_matrix3x3_vec3d (&virtual_cockpit_inst3d->vp.position, vp.attitude, &vp.position);

	*crew_viewpoint = virtual_cockpit_inst3d->vp;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_hind_internal_3d_cockpit (unsigned int flags)
{
	viewpoint
		vp;

	object_3d_instance
		*virtual_cockpit_inst3d;

//VJ wideview mod, date: 18-mar-03
    char buffer[128];

	flags = (unsigned)-1;


	////////////////////////////////////////
	//
	// virtual cockpit viewpoint is placed at the main object origin
	//
	////////////////////////////////////////

	get_crew_viewpoint(&vp);

	////////////////////////////////////////
	//
	// render displays onto textures (before draw 3D scenes)
	//
	////////////////////////////////////////

	draw_hind_hud_on_texture ();

	if (flags & VIRTUAL_COCKPIT_CRT_DISPLAY)
	{
		draw_hind_mfd_on_texture ();
	}

	// Casm 10SEP05 Havoc Instruments - temporary used for Hind
	if (flags & VIRTUAL_COCKPIT_INSTRUMENT_NEEDLES)
	{
		memcpy (&havoc_lamps, &hind_lamps, sizeof (havoc_lamps));
		draw_havoc_virtual_cockpit_instruments_on_texture ();
	}

	////////////////////////////////////////
	//
	// draw 3D scene with lighting
	//
	////////////////////////////////////////

	{
		set_cockpit_lighting (vp.attitude);
		set_3d_active_environment (main_3d_single_light_env);
		set_3d_view_distances (main_3d_single_light_env, 10.0, 0.1, 1.0, 0.0);
		realise_3d_clip_extents (main_3d_single_light_env);
		clear_zbuffer_screen ();

		if (begin_3d_scene ())
		{
			float dummy;  // TODO: remove
			entity_sub_types selected_weapon = get_local_entity_int_value (get_gunship_entity(), INT_TYPE_SELECTED_WEAPON);

			//
			// map first, otherwise transparency doesn't work properly
			//
			memcpy (&virtual_cockpit_map_display_inst3d->vp, &vp, sizeof (viewpoint));
			insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_map_display_inst3d->vp.position, virtual_cockpit_map_display_inst3d);

			// cockpit
			high_detail->visible_object = get_global_cockpit_detail_level () != COCKPIT_DETAIL_LEVEL_LOW;
			virtual_cockpit_inst3d = virtual_pilot_cockpit_inst3d;
			memcpy (&virtual_cockpit_inst3d->vp, &vp, sizeof (viewpoint));
			insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_inst3d->vp.position, virtual_cockpit_inst3d);

			memcpy (&virtual_cockpit_hud_display_inst3d->vp, &vp, sizeof (viewpoint));
			insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_hud_display_inst3d->vp.position, virtual_cockpit_hud_display_inst3d);

			door_high_detail->visible_object = get_global_cockpit_detail_level () != COCKPIT_DETAIL_LEVEL_LOW;
			memcpy (&virtual_cockpit_pilot_door_inst3d->vp, &vp, sizeof (viewpoint));
			insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_pilot_door_inst3d->vp.position, virtual_cockpit_pilot_door_inst3d);

			//
			// instrument needles
			//

			compass_object->relative_heading = -current_flight_dynamics->heading.value;

			airspeed_needle->relative_roll = get_mi24_airspeed_needle_value();
			vvi_needle->relative_roll = get_mi24_vertical_velocity_needle_value();

			get_mi24_hover_indicator_speed(&hover_indicator_speed->relative_position.x, &hover_indicator_sideways->relative_position.y);
			hover_indicator_vvi->relative_roll = get_mi24_hover_indicator_vvi_needle_value();
			radar_altimeter->relative_roll = get_mi24_radar_altimeter_needle_value();
			get_mi24_barometric_altimeter_needle_values(&barometric_altimeter_short->relative_roll, &barometric_altimeter_long->relative_roll);

			if (electrical_system_active())
			{
				bank_indicator->relative_roll = current_flight_dynamics->roll.value;
				pitch_ladder_roll->relative_roll = current_flight_dynamics->roll.value;
				pitch_ladder_pitch->relative_position.y = get_mi24_pitch_ladder_dispacement();
				horizon_ball->relative_pitch = -current_flight_dynamics->roll.value;
				horizon_ball->relative_roll = -current_flight_dynamics->pitch.value;

				if (!hind_damage.navigation_computer)
				{
					radio_compass->relative_roll = current_flight_dynamics->heading.value;
					get_hind_virtual_cockpit_hsi_needle_values(&compass_waypoint_needle->relative_roll, &compass_waypoint_heading_needle->relative_roll, &dummy);
				}
			}

			animate_shutoff_valve(shutoff_valve_left, current_flight_dynamics->right_engine_n1_rpm.max < 60.0);
			animate_shutoff_valve(shutoff_valve_right, current_flight_dynamics->left_engine_n1_rpm.max < 60.0);
			animate_rotor_brake(current_flight_dynamics->rotor_brake);

			apu_rpm_needle->relative_roll = get_mi24_apu_rpm_needle_value();
			get_mi24_engine_select_switch_value(&engine_select_switch->relative_pitch);

			rotor_rpm->relative_roll = get_mi24_rpm_needle_value(current_flight_dynamics->main_rotor_rpm.value);
			left_n1_rpm->relative_roll = get_mi24_rpm_needle_value(current_flight_dynamics->left_engine_n1_rpm.value);
			right_n1_rpm->relative_roll = get_mi24_rpm_needle_value(current_flight_dynamics->right_engine_n1_rpm.value);

			get_mi24_temperature_needle_values(current_flight_dynamics->left_engine_temp.value, &left_temperature->relative_roll, &left_temperature_small->relative_roll);
			get_mi24_temperature_needle_values(current_flight_dynamics->right_engine_temp.value, &right_temperature->relative_roll, &right_temperature_small->relative_roll);

			get_mi24_epr_needle_values(&epr_limits->relative_pitch, &left_epr_needle->relative_pitch, &right_epr_needle->relative_pitch);

			sidewind->relative_roll = get_mi24_sidewind_needle_value();
			fuel_quantity->relative_roll = get_mi24_fuel_quantity_needle_value();

			blade_pitch_needle->relative_roll = rad(98) - rad(185.0) *
				(current_flight_dynamics->main_blade_pitch.value - current_flight_dynamics->main_blade_pitch.min)
					/ (current_flight_dynamics->main_blade_pitch.max - current_flight_dynamics->main_blade_pitch.min);

			g_force->relative_roll = bound(rad(-59.5) * current_flight_dynamics->g_force.value, rad(-210.0), rad(90.0));
			get_mi24_clock_hand_values(&clock_hour_hand->relative_roll, &clock_minute_hand->relative_roll, &clock_second_hand->relative_roll);

			get_mi24_hydraulic_pressure_values(&gear_hydraulic_psi->relative_roll, &primary_hydraulic_psi->relative_roll, &secondary_hydraulic_psi->relative_roll);

			collective->relative_pitch = rad(-25.0) - rad(20) * current_flight_dynamics->input_data.collective.value * 0.01;
			pedal_link->relative_heading = rad(-15.0) * current_flight_dynamics->input_data.pedal.value * 0.01;
			left_pedal->relative_heading = right_pedal->relative_heading = -pedal_link->relative_heading;

			animate_weapon_switch(selected_weapon);
			rocket_salvo_switch->relative_pitch = get_mi24_rocket_salvo_switch_value();

			{
				int i;
				for (i=0; i < ARRAY_LENGTH(switch_animations); i++)
					animate_switch(&switch_animations[i]);
			}

			memcpy (&virtual_cockpit_pilot_instruments_inst3d->vp, &vp, sizeof (viewpoint));
			insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_pilot_instruments_inst3d->vp.position, virtual_cockpit_pilot_instruments_inst3d);

			// warning lamps
			if (electrical_system_active())
			{
				int hover_hold_mode = current_flight_dynamics->auto_hover;

				apu_ready_light->visible_object = !current_flight_dynamics->apu_rpm.damaged;
				apu_rpm_light->visible_object = current_flight_dynamics->apu_rpm.value > 90.0;
				apu_bleedair_lights->visible_object = current_flight_dynamics->apu_rpm.value > 60.0;
				engine_start_light->visible_object = (current_flight_dynamics->left_engine_starter_active || current_flight_dynamics->right_engine_starter_active);

				cockpit_sealed_light->visible_object = get_local_entity_loading_door_state(get_gunship_entity ()) == 0;
				cockpit_open_light->visible_object = !cockpit_sealed_light->visible_object;
				park_brake_light->visible_object = !!current_flight_dynamics->wheel_brake;

				gear_operational_light->visible_object = !(current_flight_dynamics->dynamics_damage & DYNAMICS_DAMAGE_UNDERCARRIAGE);
				gear_fail_light->visible_object = !gear_operational_light->visible_object;

				if (get_local_entity_undercarriage_state(get_gunship_entity()) == AIRCRAFT_UNDERCARRIAGE_DOWN)
				{
					wheels_up_light->visible_object = FALSE;
					if (gear_operational_light->visible_object)
					{
						left_wheel_down_light->visible_object = left_main_wheel_locked_down();
						right_wheel_down_light->visible_object = right_main_wheel_locked_down();
						nose_wheel_down_light->visible_object = nose_wheel_locked_down();
					}
				}
				else
				{
					wheels_up_light->visible_object = get_local_entity_undercarriage_state(get_gunship_entity()) == AIRCRAFT_UNDERCARRIAGE_UP;
					left_wheel_down_light->visible_object = FALSE;
					right_wheel_down_light->visible_object = FALSE;
					nose_wheel_down_light->visible_object = FALSE;
				}

				auto_hover_light->visible_object = hover_hold_mode == HOVER_HOLD_NORMAL || hover_hold_mode == HOVER_HOLD_STABLE;
				auto_pilot_light->visible_object = get_current_flight_dynamics_auto_pilot();
				auto_pilot_off_light->visible_object = !auto_hover_light->visible_object && !auto_pilot_light->visible_object;
				auto_altitude_light->visible_object = hover_hold_mode == HOVER_HOLD_STABLE || hover_hold_mode == HOVER_HOLD_ALTITUDE_LOCK;
				auto_altitude_off_light->visible_object = !auto_altitude_light->visible_object;

				external_light_lamps->visible_object = get_local_entity_int_value(get_gunship_entity(), INT_TYPE_LIGHTS_ON);

				left_engine_fire_light->visible_object = (current_flight_dynamics->dynamics_damage & DYNAMICS_DAMAGE_LEFT_ENGINE_FIRE) != 0;
				right_engine_fire_light->visible_object = (current_flight_dynamics->dynamics_damage & DYNAMICS_DAMAGE_RIGHT_ENGINE_FIRE) != 0;
				fire_light->visible_object = left_engine_fire_light->visible_object || right_engine_fire_light->visible_object;
				left_engine_fail_light->visible_object = (current_flight_dynamics->dynamics_damage & DYNAMICS_DAMAGE_LEFT_ENGINE) != 0;
				right_engine_fail_light->visible_object = (current_flight_dynamics->dynamics_damage & DYNAMICS_DAMAGE_RIGHT_ENGINE) != 0;
				over_stress_light->visible_object = current_flight_dynamics->g_force.value > 1.8;
				low_fuel_lights->visible_object = current_flight_dynamics->fuel_weight.value < current_flight_dynamics->fuel_weight.max * 0.25;
				gyre_fail_lights->visible_object = hind_damage.navigation_computer;

				// weapon pylon lights
				{
					int pylon;

					for (pylon = HAVOC_LHS_INNER_PYLON; pylon <= HAVOC_RHS_OUTER_PYLON; pylon++)
					{
						entity_sub_types weapon_sub_type;
						int number, damaged;

						if (get_local_entity_weapon_hardpoint_info (get_gunship_entity(),
							pylon, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON,
							&weapon_sub_type, &number, &damaged))
						{
							switch (pylon)
							{
							case HAVOC_LHS_OUTER_PYLON:
								left_outer_pylon_light->visible_object = (!damaged && weapon_sub_type == selected_weapon);
								break;
							case HAVOC_LHS_INNER_PYLON:
								left_inner_pylon_light->visible_object = (!damaged && weapon_sub_type == selected_weapon);
								break;
							case HAVOC_RHS_INNER_PYLON:
								right_inner_pylon_light->visible_object = (!damaged && weapon_sub_type == selected_weapon);
								break;
							case HAVOC_RHS_OUTER_PYLON:
								right_outer_pylon_light->visible_object = (!damaged && weapon_sub_type == selected_weapon);
								break;
							}
						}
					}
				}

				memcpy (&virtual_cockpit_warning_lamps_inst3d->vp, &vp, sizeof (viewpoint));
				insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_warning_lamps_inst3d->vp.position, virtual_cockpit_warning_lamps_inst3d);
			}

			// secondary instruments
			if (get_global_cockpit_detail_level () != COCKPIT_DETAIL_LEVEL_LOW)
			{
				fuel_switches->relative_roll = electrical_system_active() ? rad(90.0) : 0.0;
				radio_navigation_switches->relative_roll = fuel_switches->relative_roll;
				external_light_switches->relative_roll = get_local_entity_int_value(get_gunship_entity(), INT_TYPE_LIGHTS_ON) ? rad(90.0) : 0.0;
				master_arm_switches->relative_pitch = (get_local_entity_int_value(get_gunship_entity(), INT_TYPE_SELECTED_WEAPON) == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON) ? 0.0 : rad(90.0);

				memcpy (&virtual_cockpit_pilot_secondary_instruments_inst3d->vp, &vp, sizeof (viewpoint));
				insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_pilot_secondary_instruments_inst3d->vp.position, virtual_cockpit_pilot_secondary_instruments_inst3d);
			}

			draw_3d_scene ();

//VJ wideview mod, date: 18-mar-03
         if (edit_wide_cockpit)
       	{
				sprintf(buffer,"HIND wide cockpit mod edit (set freelook off):");
				ui_display_text (buffer, 10, 40);
				sprintf(buffer,"Y: num 8/2; Z: num 4/6; pitch: num 7/9; Restore: num 0; Ctrl-\\ Leave");
				ui_display_text (buffer, 10, 60);
				sprintf(buffer,"x=%.3f, y=%.3f, z=%.3f, pitch=%.3f",wide_cockpit_position[wide_cockpit_nr].x, wide_cockpit_position[wide_cockpit_nr].y, wide_cockpit_position[wide_cockpit_nr].z, wide_cockpit_position[wide_cockpit_nr].p);
				ui_display_text (buffer, 10, 100);
         }

			end_3d_scene ();
		}
	}

	////////////////////////////////////////
	//
	// draw 3D scene without lighting
	//
	////////////////////////////////////////

#if 0
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
#endif
	////////////////////////////////////////
	//
	// draw 3D scene with lighting
	//
	////////////////////////////////////////

	//
	// draw fillet to mask EO display
	//

#if 0
	if
	(
		(d3d_can_render_to_texture) &&
		(get_hind_eo_display_visible ()) &&
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
#endif
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
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_hind_external_3d_cockpit (unsigned int flags, unsigned char *wiper_rle_graphic)
{
	viewpoint
		vp;

	float
		theta;

	object_3d_instance
		*inst3d;


	////////////////////////////////////////
	//
	// virtual cockpit viewpoint is placed at the main object origin
	//
	////////////////////////////////////////

	get_crew_viewpoint(&vp);

	////////////////////////////////////////
	//
	// draw 3D scene without lighting
	//
	////////////////////////////////////////

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
//			if (flags & VIRTUAL_COCKPIT_MAIN_ROTOR)
			{
				if (!(get_helicopter_main_rotors_blurred (get_gunship_entity ()) && (!get_global_blurred_main_rotors_visible_from_cockpit ())))
				{
					if (get_local_entity_int_value (get_gunship_entity (), INT_TYPE_MAIN_ROTOR_DAMAGED))
					{
						animate_damaged_helicopter_main_rotors (get_gunship_entity (), TRUE);
					}
					else
					{
						animate_helicopter_main_rotors (get_gunship_entity (), TRUE, FALSE);
					}

					inst3d = get_local_entity_ptr_value (get_gunship_entity (), PTR_TYPE_INSTANCE_3D_OBJECT);

					theta = get_rotation_angle_of_helicopter_main_rotors (inst3d);

					{
						set_rotation_angle_of_helicopter_main_rotors (virtual_cockpit_main_rotor_inst3d, theta);

						animate_helicopter_virtual_cockpit_main_rotors (get_gunship_entity (), virtual_cockpit_main_rotor_inst3d);

						memcpy (&virtual_cockpit_main_rotor_inst3d->vp, &vp, sizeof (viewpoint));

						insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_main_rotor_inst3d->vp.position, virtual_cockpit_main_rotor_inst3d);
					}
				}
			}

			//
			// wiper
			//

			draw_hind_3d_cockpit_wiper (&vp);

			draw_3d_scene ();

			end_3d_scene ();
		}
	}

	////////////////////////////////////////
	//
	// draw 3D scene with lighting
	//
	////////////////////////////////////////

#if 0
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

					get_hind_virtual_cockpit_adi_angles (vp.attitude, &heading, &pitch, &roll);

					search.result_sub_object->relative_heading = -heading;

					search.result_sub_object->relative_pitch = pitch;

					search.result_sub_object->relative_roll = -roll;
				}

//VJ wideview mod, date: 18-mar-03
				if (get_global_wide_cockpit ())
				{
				    vp.y = wide_cockpit_position[wide_cockpit_nr].y+0.01;
				    vp.z = wide_cockpit_position[wide_cockpit_nr].z;
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

	#endif

	////////////////////////////////////////
	//
	// rendered wiper
	//
	////////////////////////////////////////
#if 0
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

	if (rain_mode != RAIN_MODE_DRY)
	{
		set_3d_active_environment (main_3d_env);
		set_3d_view_distances (main_3d_env, 10.0, 0.1, 1.0, 0.0);
		realise_3d_clip_extents (main_3d_env);

		recalculate_3d_environment_settings (main_3d_env);

		clear_zbuffer_screen ();

		if (begin_3d_scene ())
		{
			memcpy (&virtual_cockpit_canopy_inst3d->vp, &vp, sizeof (viewpoint));
			insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_canopy_inst3d->vp.position, virtual_cockpit_canopy_inst3d);

			draw_3d_scene ();
			end_3d_scene ();
		}
	}

	//VJ wideview mod, date: 18-mar-03
	////////////////////////////////////////
	//
	// wide cockpit position edit
	//
	////////////////////////////////////////

	if (edit_wide_cockpit)
	{
		//VJ 50208 added pilot head pitch
		if (check_key(DIK_NUMPAD7))
		{
            wide_cockpit_position[wide_cockpit_nr].p += 0.5;
      }
		if (check_key(DIK_NUMPAD9))
		{
            wide_cockpit_position[wide_cockpit_nr].p -= 0.5;
      }
		if (check_key(DIK_NUMPAD6))
		{
            wide_cockpit_position[wide_cockpit_nr].z += 0.005;
      }
		if (check_key(DIK_NUMPAD4))
		{
            wide_cockpit_position[wide_cockpit_nr].z -= 0.005;
      }
		if (check_key(DIK_NUMPAD8))
		{
            wide_cockpit_position[wide_cockpit_nr].y += 0.005;
      }
		if (check_key(DIK_NUMPAD2))
		{
            wide_cockpit_position[wide_cockpit_nr].y -= 0.005;
      }
		if (check_key(DIK_NUMPAD1))
		{
            wide_cockpit_position[wide_cockpit_nr].x -= 0.005;
      }
		if (check_key(DIK_NUMPAD3))
		{
            wide_cockpit_position[wide_cockpit_nr].x += 0.005;
      }
		if (check_key(DIK_NUMPAD0))
		{
			wide_cockpit_position[wide_cockpit_nr].x = 0.0;
			wide_cockpit_position[wide_cockpit_nr].y = 0.0;
			wide_cockpit_position[wide_cockpit_nr].z = 0.0;
			wide_cockpit_position[wide_cockpit_nr].p = -5.0;
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
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void damage_hind_3d_cockpit_main_rotors (int seed)
{
	float
		theta;

	object_3d_instance
		*inst3d;

	ASSERT (get_gunship_entity ());

	ASSERT (virtual_cockpit_main_rotor_inst3d);

	inst3d = get_local_entity_ptr_value (get_gunship_entity (), PTR_TYPE_INSTANCE_3D_OBJECT);

	ASSERT (inst3d);

	theta = get_rotation_angle_of_helicopter_main_rotors (inst3d);

	set_rotation_angle_of_helicopter_main_rotors (virtual_cockpit_main_rotor_inst3d, theta);

	animate_helicopter_virtual_cockpit_main_rotors (get_gunship_entity (), virtual_cockpit_main_rotor_inst3d);

	damage_helicopter_main_rotor_inst3d (virtual_cockpit_main_rotor_inst3d, seed);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void restore_hind_3d_cockpit_main_rotors (void)
{
	float
		theta;

	object_3d_instance
		*inst3d;

	ASSERT (get_gunship_entity ());

	ASSERT (virtual_cockpit_main_rotor_inst3d);

	inst3d = get_local_entity_ptr_value (get_gunship_entity (), PTR_TYPE_INSTANCE_3D_OBJECT);

	ASSERT (inst3d);

	theta = get_rotation_angle_of_helicopter_main_rotors (inst3d);

	set_rotation_angle_of_helicopter_main_rotors (virtual_cockpit_main_rotor_inst3d, theta);

	animate_helicopter_virtual_cockpit_main_rotors (get_gunship_entity (), virtual_cockpit_main_rotor_inst3d);

	restore_helicopter_main_rotor_inst3d (virtual_cockpit_main_rotor_inst3d);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void animate_shutoff_valve(object_3d_sub_instance* inst, int closed)
{
	float
		max_movement = SHUTOFF_MOVEMENT_RATE * get_delta_time(),
		valve_angle = 0.0;

	// left throttle
	if (!closed)  // idle at -45 deg
		valve_angle = rad(45.0);

	inst->relative_pitch += bound(valve_angle - inst->relative_pitch, -max_movement, max_movement);
}
