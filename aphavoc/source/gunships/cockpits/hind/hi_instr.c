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

struct SCALE_DATA
{
	short int
		x,
		y;

	float
		value;
};

typedef struct SCALE_DATA scale_data;

#define SWITCH_MOVEMENT_RATE   rad(300.0)   // 30 deg in 0.1 sec

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static rgb_colour
	white_needle_colour,
	yellow_needle_colour,
	orange_needle_colour,
	red_needle_colour,
	white_digit_colour,
	yellow_digit_colour;

static rgb_colour
	white_needle_colour_level1,
	yellow_needle_colour_level1,
	orange_needle_colour_level1,
	red_needle_colour_level1,
	white_digit_colour_level1,
	yellow_digit_colour_level1,
	white_needle_colour_level2,
	yellow_needle_colour_level2,
	orange_needle_colour_level2,
	red_needle_colour_level2,
	white_digit_colour_level2,
	yellow_digit_colour_level2,
	white_needle_colour_level3,
	yellow_needle_colour_level3,
	orange_needle_colour_level3,
	red_needle_colour_level3,
	white_digit_colour_level3,
	yellow_digit_colour_level3;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static char
	*instrument_error = "Cannot draw instrument on panel";

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "hi_aspd.h"

#include "hi_balt.h"

#include "hi_clock.h"

#include "hi_erpm.h"

#include "hi_etmp.h"

#include "hi_etrq.h"

#include "hi_fuel.h"

#include "hi_gmtr.h"

#include "hi_ralt.h"

#include "hi_rrpm.h"

#include "hi_vsi.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void get_hsi_needle_values (float *direction_finder, float *flight_path, float *drift)
{
	float
		direction_finder_needle_value,
		flight_path_needle_value,
		drift_needle_value,
		dx,
		dz,
		heading,
		bearing,
		length1,
		length2,
		dot_product,
		cross_product;

	entity
		*en,
		*wp,
		*prev_wp;

	vec3d
		*motion_vector,
		wind_vector,
		*en_position,
		wp_position,
		prev_wp_position;

	vec2d
		v1,
		v2;

	ASSERT (direction_finder);

	ASSERT (flight_path);

	ASSERT (drift);

	direction_finder_needle_value = 0.0;

	flight_path_needle_value = 0.0;

	drift_needle_value = 0.0;

	if (test_cockpit_instruments)
	{
		static float
			direction_finder_value = rad (0.0),
			flight_path_value = rad (90.0),
			drift_value = rad (-20.0);

		//
		// automatic direction finder
		//

		direction_finder_value += rad (5.0);

		if (direction_finder_value > rad (360.0))
		{
			direction_finder_value -= rad (360.0);
		}

		direction_finder_needle_value = direction_finder_value;

		//
		// flight path
		//

		flight_path_value += rad (3.0);

		if (flight_path_value > rad (360.0))
		{
			flight_path_value -= rad (360.0);
		}

		flight_path_needle_value = flight_path_value;

		//
		// drift
		//

		drift_value += rad (1.0);

		if (drift_value > rad (35.0))
		{
			drift_value = rad (-35.0);
		}

		drift_needle_value = drift_value;
	}
	else
	{
		if (!hind_damage.navigation_computer)
		{
			en = get_gunship_entity ();

			wp = get_local_entity_current_waypoint (en);

			if (wp)
			{
				//
				// automatic direction finder
				//

				heading = get_local_entity_float_value (en, FLOAT_TYPE_HEADING);

				en_position = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

				get_waypoint_display_position (en, wp, &wp_position);

				dx = wp_position.x - en_position->x;
				dz = wp_position.z - en_position->z;

				bearing = atan2 (dx, dz);

				direction_finder_needle_value = bearing - heading;

				//
				// flight path
				//

				prev_wp = get_local_entity_prev_waypoint (en);

				if ((prev_wp) && (prev_wp != wp))
				{
					get_waypoint_display_position (en, prev_wp, &prev_wp_position);

					dx = wp_position.x - prev_wp_position.x;
					dz = wp_position.z - prev_wp_position.z;

					bearing = atan2 (dx, dz);

					flight_path_needle_value = bearing - heading;
				}
				else
				{
					flight_path_needle_value = direction_finder_needle_value;
				}

				//
				// drift
				//

				drift_needle_value = 0.0;

				motion_vector = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_MOTION_VECTOR);

				v1.x = motion_vector->x;
				v1.y = motion_vector->z;

				length1 = (v1.x * v1.x) + (v1.y * v1.y);

				if (length1 > 0.001)
				{
					length1 = sqrt (length1);

					v1.x /= length1;
					v1.y /= length1;

					get_session_wind_velocity_at_point (en_position, &wind_vector);

					v2.x = motion_vector->x + wind_vector.x;
					v2.y = motion_vector->z + wind_vector.z;

					length2 = (v2.x * v2.x) + (v2.y * v2.y);

					if (length2 > 0.001)
					{
						length2 = sqrt (length2);

						v2.x /= length2;
						v2.y /= length2;

						dot_product = get_2d_unit_vector_dot_product (&v1, &v2);

						drift_needle_value = acos (dot_product);

						cross_product = (v1.x * v2.y) - (v2.x * v1.y);

						if (cross_product > 0.0)
						{
							drift_needle_value = -drift_needle_value;
						}
					}
				}
			}
		}
	}

	drift_needle_value = bound (drift_needle_value, rad (-30.0), rad (30.0));

	*direction_finder = direction_finder_needle_value;

	*flight_path = flight_path_needle_value;

	*drift = drift_needle_value;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_hind_virtual_cockpit_hsi_needle_values (float *direction_finder, float *flight_path, float *drift)
{
	float
		max_movement = rad(270) * get_delta_time(),
		direction_finder_needle_value,
		flight_path_needle_value,
		drift_needle_value;

	ASSERT  (direction_finder);

	ASSERT (flight_path);

	ASSERT (drift);

	get_hsi_needle_values (&direction_finder_needle_value, &flight_path_needle_value, &drift_needle_value);

	*direction_finder += bound(-direction_finder_needle_value - *direction_finder, -max_movement, max_movement);

	*flight_path += bound(-direction_finder_needle_value - *flight_path, -max_movement, max_movement);

	*drift = -drift_needle_value;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_mi24_airspeed_needle_value(void)
{
	float airspeed = bound(kilometres_per_hour(current_flight_dynamics->indicated_airspeed.value), 0.0, 450.0);
	float roll = -4.0;

	if (airspeed < 50.0)
		roll = rad(-4.0) + airspeed / 50 * rad(20.0);
	else if (airspeed < 100.0)
		roll = rad(16.0) + (airspeed - 50) / 50 * rad(37.5);
	else if (airspeed < 250.0)
		roll = rad(53.5) + (airspeed - 100) / 150 * rad(126.5);
	else
		roll = rad(180.0) + (airspeed - 250) / 200 * rad(164.0);
	return -roll;
}

float get_mi24_vertical_velocity_needle_value(void)
{
	float vvi = bound(current_flight_dynamics->world_velocity_y.value, -30.0, 30.0);
	int negative = vvi < 0.0;
	float roll = 0.0;

	vvi = fabs(vvi);

	if (vvi < 5.0)
		roll = vvi / 5.0 * rad(42.0);
	else if (vvi < 10.0)
		roll = rad(42.0) + (vvi - 5.0) / 5.0 * rad(38.5);
	else if (vvi < 20.0)
		roll = rad(80.5) + (vvi - 10.0) / 10.0 * rad(60.0);
	else
		roll = rad(140.5) + (vvi - 20.0) / 10.0 * rad(39.5);

	if (negative)
		return rad(90) + roll;
	else
		return rad(90) - roll;
}

float get_mi24_pitch_ladder_dispacement(void)
{
	float pitch = current_flight_dynamics->pitch.value;

	return deg(-pitch) * 0.001;
}

void get_mi24_hover_indicator_speed(float* longitudinal, float* sideways)
{
#define HOVER_SPEED_SCALING  0.000725  // 0.725 mm per kph
	*longitudinal = bound(kilometres_per_hour(current_flight_dynamics->velocity_z.value), -30.0, 55.0);
	*sideways = bound(kilometres_per_hour(-current_flight_dynamics->velocity_x.value), -30.0, 30.0);

	*longitudinal *= HOVER_SPEED_SCALING;
	*sideways *= HOVER_SPEED_SCALING;
}

float get_mi24_hover_indicator_vvi_needle_value(void)
{
	float vvi = bound(current_flight_dynamics->world_velocity_y.value, -10.0, 10.0);

	return (3.0 - vvi) * rad(3.85);
}

float get_mi24_radar_altimeter_needle_value(void)
{
	float alt = bound(current_flight_dynamics->radar_altitude.value, 0.0, 700.0);
	float roll = 0.0;

	if (!electrical_system_active())
		alt = 0.0;

	if (alt < 20.0)
		roll = alt / 20.0 * rad(29.0);
	else if (alt < 60.0)
		roll = rad(29.0) + (alt - 20.0) / 40.0 * rad(64.0);
	else if (alt < 100.0)
		roll = rad(93.0) + (alt - 60.0) / 40.0 * rad(62.0);
	else if (alt < 500.0)
		roll = rad(155.0) + (alt - 100.0) / 400.0 * rad(105.0);
	else
		roll = rad(260.0) + (alt - 500.0) / 200.0 * rad(49.0);

	return -roll;
}

void get_mi24_barometric_altimeter_needle_values(float* shrt, float* lng)
{
	float alt = current_flight_dynamics->barometric_altitude.value;

	*shrt = -(alt / 10000.0) * 2 * PI;
	*lng = -(alt / 1000.0) * 2 * PI;
}

float get_mi24_apu_rpm_needle_value(void)
{
	float val = rad(113);

	return val + rad(-1.85) * current_flight_dynamics->apu_rpm.value;
}

void get_mi24_engine_select_switch_value(float* current_val)
{
	float val = rad(5.0);
	float max_step = SWITCH_MOVEMENT_RATE * get_delta_time();

	if (current_flight_dynamics->left_engine_starter_active)
		val = rad(50.0);
	else if (current_flight_dynamics->right_engine_starter_active)
		val = -rad(40.0);

	*current_val += bound(val - *current_val, -max_step, max_step);
}

float get_mi24_rpm_needle_value(float rpm)
{
	float ret = rad(-46.0);

	return ret + rpm * rad(-3.13);
}

void get_mi24_temperature_needle_values(float temp, float* big_needle, float* small_needle)
{
	temp = bound(temp, 0.0, 1200.0);

	*big_needle = rad(131) - rad(0.2183) * temp;
	*small_needle = rad(180) - 0.02 * PI * temp;
}

float get_mi24_compass_waypoint_needle_value(void)
{
	return 0.0;
}

float get_mi24_compass_waypoint_needle_heading_value(void)
{
	return 0.0;
}

void get_mi24_epr_needle_values(float* limits, float* left, float* right)
{
	float ambient_pressure = get_air_density(current_flight_dynamics->barometric_altitude.value);
	float engine_power_ratio;

	*limits = rad(15) * max(ambient_pressure - 0.5, 0.0) * 2;

	engine_power_ratio = (current_flight_dynamics->left_engine_n1_rpm.value - current_flight_dynamics->engine_idle_rpm - 8.0)
		* current_flight_dynamics->left_engine_rpm.value / 1900;
	*left = bound(engine_power_ratio * rad(19) * max(ambient_pressure - 0.5, 0.0) * 2, 0.0, rad(25));;

	engine_power_ratio = (current_flight_dynamics->right_engine_n1_rpm.value - current_flight_dynamics->engine_idle_rpm - 8.0)
		* current_flight_dynamics->right_engine_rpm.value / 1900;
	*right = bound(engine_power_ratio * rad(19) * max(ambient_pressure - 0.5, 0.0) * 2, 0.0, rad(25));;
}

float get_mi24_rocket_salvo_switch_value(void)
{
	float angle = rad(-22.0);

	if (rocket_salvo_size == 2)
		angle += rad(90.0);
	else if (rocket_salvo_size != 4)
		angle += rad(45.0);

	return angle;
}

float get_mi24_sidewind_needle_value(void)
{
	float angle = 0.0;

	if (get_current_dynamics_options (DYNAMICS_OPTIONS_WIND))
	{
		vec3d position, wind, relative_wind;

		position.x = current_flight_dynamics->position.x;
		position.y = current_flight_dynamics->position.y;
		position.z = current_flight_dynamics->position.z;

		get_session_wind_velocity_at_point(&position, &wind);
		multiply_matrix3x3_vec3d(&relative_wind, current_flight_dynamics->attitude, &wind);

		angle = bound(relative_wind.x * rad(-9.7), rad(-130.0), rad(130.0));
	}

	return angle;
}

float get_mi24_fuel_quantity_needle_value(void)
{
	float angle = rad(149.0);

	angle += rad(-0.1196) * current_flight_dynamics->fuel_weight.value * 1.39;  // gauge uses liters, 1.39 liters per kilo

	return angle;
}

void get_mi24_clock_hand_values(float* hour_hand, float* minute_hand, float* second_hand)
{
	float
		time_of_day,
		hour_hand_value,
		minute_hand_value,
		second_hand_value;

	time_of_day = get_local_entity_float_value (get_session_entity (), FLOAT_TYPE_TIME_OF_DAY);
	get_analogue_clock_values (time_of_day, &hour_hand_value, &minute_hand_value, &second_hand_value);

	*hour_hand = hour_hand_value * rad(-30.0);
	*minute_hand = minute_hand_value * rad(-6.0);
	*second_hand = floor(second_hand_value) * rad(-6.0);
}

void get_mi24_hydraulic_pressure_values(float* gear, float* primary, float* secondary)
{
	float
		max_movement = rad(180) * get_delta_time(),
		gear_psi = rad(52.0),
		primary_psi = rad(52.0),
		secondary_psi = rad(52.0);

	if (electrical_system_active())
	{
		if (!(current_flight_dynamics->dynamics_damage & DYNAMICS_DAMAGE_UNDERCARRIAGE))
			gear_psi -= rad(115.0);

		if (!(current_flight_dynamics->dynamics_damage & DYNAMICS_DAMAGE_SECONDARY_HYDRAULICS))
			secondary_psi -= rad(115.0);

		primary_psi -= get_hydraulic_pressure() * rad(115.0);
	}

	*gear += bound(gear_psi - *gear, -max_movement, max_movement);
	*primary += bound(primary_psi - *primary, -max_movement, max_movement);
	*secondary += bound(secondary_psi - *secondary, -max_movement, max_movement);
}

void update_mi24_waypoint_indicator(float* indicator)
{
	entity* wp = get_local_entity_current_waypoint (get_gunship_entity ());

	if (wp)
	{
		float pitch = rad(-75.0);
		char wpnt = get_local_entity_char_value(wp, CHAR_TYPE_TAG);
		float max_movement = rad(120) * get_delta_time();

		pitch += (wpnt - 'A') * rad(-360.0 / 26.0);

		*indicator += bound(pitch - *indicator, -max_movement, max_movement);
	}
}

void update_mi24_weapon_status_lights(object_3d_sub_instance* ready, object_3d_sub_instance* not_ready, object_3d_sub_instance* min_range)
{
	entity_sub_types
		weapon_sub_type;

	weapon_sub_type = get_local_entity_int_value (get_gunship_entity (), INT_TYPE_SELECTED_WEAPON);

	if (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
	{
		ready->visible_object = FALSE;
		not_ready->visible_object = FALSE;
		min_range->visible_object = FALSE;
		return;
	}

	switch (weapon_lock_type)
	{
		case WEAPON_LOCK_NO_WEAPON:
			ASSERT(FALSE);
		case WEAPON_LOCK_NO_ACQUIRE:
		case WEAPON_LOCK_NO_TARGET:
		case WEAPON_LOCK_INVALID_TARGET:
		case WEAPON_LOCK_NO_LOS:
		case WEAPON_LOCK_SEEKER_LIMIT:
		case WEAPON_LOCK_NO_BORESIGHT:
			// don't need valid target to fire unguided weapons
			ready->visible_object = weapon_database[weapon_sub_type].guidance_type == WEAPON_GUIDANCE_TYPE_NONE;
			not_ready->visible_object = !ready->visible_object;
			break;
		case WEAPON_LOCK_MIN_RANGE:
		case WEAPON_LOCK_MAX_RANGE:
		case WEAPON_LOCK_VALID:
			ready->visible_object = TRUE;
			not_ready->visible_object = FALSE;
			break;
	}

	min_range->visible_object = get_hud_aiming_range() < weapon_database[weapon_sub_type].min_range;
}

void update_mi24_engine_gauges(float* left_temp, float* right_temp, float* left_pressure, float* right_pressure)
{
	float
		max_temp_movement = rad(5) * get_delta_time(),
		max_pressure_movement = rad(60) * get_delta_time(),
		temp,
		lpres,
		rpres;

	temp = bound(current_flight_dynamics->left_engine_temp.value * 0.001, 0.0, 1.0);
	*left_temp += bound((rad(100) - rad(70) * temp) - *left_temp, -max_temp_movement, max_temp_movement);

	temp = bound(current_flight_dynamics->right_engine_temp.value * 0.001, 0.0, 1.0);
	*right_temp += bound((rad(100) - rad(70) * temp) - *right_temp, -max_temp_movement, max_temp_movement);

	if (electrical_system_active())
	{
		if ((current_flight_dynamics->dynamics_damage & DYNAMICS_DAMAGE_LEFT_ENGINE) != 0)
			lpres = 0.0;
		else if ((current_flight_dynamics->dynamics_damage & DYNAMICS_DAMAGE_LOW_OIL_PRESSURE) != 0)
			lpres = 0.5;
		else if ((current_flight_dynamics->dynamics_damage & DYNAMICS_DAMAGE_HIGH_OIL_PRESSURE) != 0)
			lpres = 1.2;
		else
			lpres = 1.0;

		if ((current_flight_dynamics->dynamics_damage & DYNAMICS_DAMAGE_RIGHT_ENGINE) != 0)
			rpres = 0.0;
		else if ((current_flight_dynamics->dynamics_damage & DYNAMICS_DAMAGE_LOW_OIL_PRESSURE) != 0)
			rpres = 0.5;
		else if ((current_flight_dynamics->dynamics_damage & DYNAMICS_DAMAGE_HIGH_OIL_PRESSURE) != 0)
			rpres = 1.2;
		else
			rpres = 1.0;
	}
	else
		lpres = rpres = 0.0;

	*left_pressure += bound((rad(-150) + rad(100) * lpres) - *left_pressure, -max_pressure_movement*0.9, max_pressure_movement);
	*right_pressure += bound((rad(-150) + rad(100) * rpres) - *right_pressure, -max_pressure_movement, max_pressure_movement*0.9);
}
