/*
 * co_fuel.c
 *
 *  Created on: 12.sep.2009
 *      Author: arneh
 */

#include "project.h"

#include "co_fuel.h"

#define DYNAMICS_LOW_FUEL_SPEECH_TIME				(20 * ONE_SECOND)

static float fuel_quantity[NUM_FUEL_TANKS];
static float fuel_tank_capacity[NUM_FUEL_TANKS];
static float low_fuel_warning[NUM_FUEL_TANKS];
static float transfer_rate = 2.0;  // kg/s
static float forward_tank_fuel_ratio = 1.0;
static float allowed_fuel_inbalance = 0.01;

static fuel_tank_positions feeding_tank[3];  // APU and two engines
static fuel_tank_positions fuel_transfer[NUM_FUEL_TANKS];  // index by from tank, value is to tank

static int auto_fuel_transfer;
static int fuel_booster_pump_on;
static int low_fuel_fwd, low_fuel_aft;

static int has_low_fuel_warned[NUM_FUEL_TANKS];

int aft_fuel_tank_low_fuel(void)
{
	return low_fuel_aft;
}

int forward_fuel_tank_low_fuel(void)
{
	return low_fuel_fwd;
}

void initialise_fuel_system(void)
{
	fuel_tank_positions tank;

	low_fuel_fwd = low_fuel_aft = FALSE;

	feeding_tank[0] = FUEL_TANK_FWD;
	feeding_tank[1] = FUEL_TANK_FWD;
	feeding_tank[2] = FUEL_TANK_FWD;

	for (tank = FUEL_TANK_FWD; tank < NUM_FUEL_TANKS; tank++)
	{
		fuel_quantity[tank] = fuel_tank_capacity[tank] = low_fuel_warning[tank] = 0.0;
		fuel_transfer[tank] = FUEL_TANK_NONE;
		has_low_fuel_warned[tank] = FALSE;
	}

	// put all fuel in forward tank if we don't know distribution
	fuel_quantity[FUEL_TANK_FWD] = fuel_tank_capacity[FUEL_TANK_FWD] = current_flight_dynamics->fuel_weight.max;
	fuel_booster_pump_on = FALSE;
	auto_fuel_transfer = TRUE;

	switch (get_global_gunship_type())
	{
	case GUNSHIP_TYPE_APACHE:
		fuel_quantity[FUEL_TANK_FWD] = fuel_tank_capacity[FUEL_TANK_FWD] = pounds_to_kilograms(1012.0);
		fuel_quantity[FUEL_TANK_AFT] = fuel_tank_capacity[FUEL_TANK_AFT] = pounds_to_kilograms(1430.0);

		low_fuel_warning[FUEL_TANK_FWD] = pounds_to_kilograms(280.0);
		low_fuel_warning[FUEL_TANK_AFT] = pounds_to_kilograms(240.0);

		feeding_tank[0] = FUEL_TANK_AFT;
		feeding_tank[1] = FUEL_TANK_FWD;
		feeding_tank[2] = FUEL_TANK_AFT;

		break;
	}

	forward_tank_fuel_ratio = fuel_tank_capacity[FUEL_TANK_FWD] / fuel_tank_capacity[FUEL_TANK_AFT];
}

void update_fuel_system(void)
{
	int engine_no;
	fuel_tank_positions tank;

	// engine consumtion
	for (engine_no = 0; engine_no <= 2; engine_no++)
	{
		float fuel_flow = get_fuel_flow(engine_no);

		fuel_quantity[feeding_tank[engine_no]] -= fuel_flow  * get_delta_time();

		if (fuel_quantity[feeding_tank[engine_no]] <= 0.0)
		{
			fuel_quantity[feeding_tank[engine_no]] = 0.0;
			set_current_flight_dynamics_auto_pilot (FALSE);
		}
	}

	current_flight_dynamics->fuel_weight.value = get_total_fuel_quantity();

	low_fuel_fwd = fuel_quantity[FUEL_TANK_FWD] < low_fuel_warning[FUEL_TANK_FWD];
	low_fuel_aft = fuel_quantity[FUEL_TANK_AFT] < low_fuel_warning[FUEL_TANK_AFT];

	// low fuel warning
	if (low_fuel_fwd || low_fuel_aft)
	{
		static float
			time = 0.0;

		if (get_global_gunship_type() == GUNSHIP_TYPE_APACHE)
		{
			if (low_fuel_fwd && !has_low_fuel_warned[FUEL_TANK_FWD])
			{
				add_apache_advisory("FWD LOW FUEL");
				has_low_fuel_warned[FUEL_TANK_FWD] = TRUE;
			}

			if (low_fuel_aft && !has_low_fuel_warned[FUEL_TANK_AFT])
			{
				add_apache_advisory("AFT LOW FUEL");
				has_low_fuel_warned[FUEL_TANK_AFT] = TRUE;
			}
		}

		time -= get_delta_time ();

		if (time <= 0.0)
		{
			play_client_server_warning_message (get_gunship_entity (), SPEECH_SYSTEM_FUEL_LOW);
			time = DYNAMICS_LOW_FUEL_SPEECH_TIME;
		}
	}

	// auto fuel levelling
	if (auto_fuel_transfer)
	{
		float current_fuel_ratio = fuel_quantity[FUEL_TANK_FWD] / fuel_quantity[FUEL_TANK_AFT];

		if ((forward_tank_fuel_ratio - current_fuel_ratio) > allowed_fuel_inbalance)  // Too much fuel aft, pump it forward
		{
			fuel_transfer[FUEL_TANK_AFT] = FUEL_TANK_FWD;
			fuel_transfer[FUEL_TANK_FWD] = FUEL_TANK_NONE;
		}
		else if ((current_fuel_ratio - forward_tank_fuel_ratio) > allowed_fuel_inbalance)  // Too much fuel forward, pump it aft
		{
			fuel_transfer[FUEL_TANK_FWD] = FUEL_TANK_AFT;
			fuel_transfer[FUEL_TANK_AFT] = FUEL_TANK_NONE;
		}
		else
		{
			fuel_transfer[FUEL_TANK_FWD] = FUEL_TANK_NONE;
			fuel_transfer[FUEL_TANK_AFT] = FUEL_TANK_NONE;
		}
	}

	// fuel transfer
	for (tank = FUEL_TANK_FWD; tank < NUM_FUEL_TANKS; tank++)
	{
		if (fuel_transfer[tank] != FUEL_TANK_NONE)
		{
			fuel_tank_positions to_tank = fuel_transfer[tank];
			float transfer_amount = transfer_rate * get_delta_time();
			float space_available = fuel_tank_capacity[to_tank] - fuel_quantity[to_tank];

			if (transfer_amount > fuel_quantity[tank])
				transfer_amount = fuel_quantity[tank];
			if (transfer_amount > space_available)
				transfer_amount = space_available;

			fuel_quantity[tank] -= transfer_amount;
			fuel_quantity[to_tank] += transfer_amount;

			if (fuel_quantity[to_tank] > low_fuel_warning[to_tank])
				has_low_fuel_warned[to_tank] = FALSE;
		}
	}
}

float get_fuel_flow(unsigned engine_no)
{
	const float fuel_usage_factor = 0.5 / 85.0;
	const float apu_fuel_usage_factor = fuel_usage_factor * 0.117;  // Taken from Apache where APU uses 135 punds/hr
	float fuel_flow = current_flight_dynamics->fuel_weight.delta;

	// arneh - adjust for engine RPM.  Adjusted to 1 at 85% N1 RPM on both engines
	if (engine_no == 0)  // APU
		fuel_flow *= current_flight_dynamics->apu_rpm.value * apu_fuel_usage_factor;
	else if (engine_no == 1)
		fuel_flow *= current_flight_dynamics->left_engine_n1_rpm.value * fuel_usage_factor;
	else
		fuel_flow *= current_flight_dynamics->right_engine_n1_rpm.value * fuel_usage_factor;

	return fuel_flow;
}

float get_total_fuel_quantity(void)
{
	fuel_tank_positions tank;
	float fuel = 0.0;

	for (tank=FUEL_TANK_FWD; tank < NUM_FUEL_TANKS; tank++)
		fuel += fuel_quantity[tank];

	return fuel;
}

int engine_has_fuel_supply(unsigned engine_no)
{
	return fuel_quantity[feeding_tank[engine_no]] > 0.0;
}

float get_fuel_quantity(fuel_tank_positions tank)
{
	return fuel_quantity[tank];
}

void change_fuel_quantity(fuel_tank_positions tank, float amount)
{
	fuel_quantity[tank] = bound(fuel_quantity[tank] + amount, 0.0, fuel_tank_capacity[tank]);;
}

void refuel_helicopter(float amount)
{
	fuel_tank_positions tank;

	ASSERT(amount >= 0.0);

	for (tank = FUEL_TANK_FWD; tank < NUM_FUEL_TANKS; tank++)
	{
		if (amount + fuel_quantity[tank] > fuel_tank_capacity[tank])
			amount = fuel_tank_capacity[tank] - fuel_quantity[tank];
		fuel_quantity[tank] += amount;

		if (fuel_quantity[tank] > low_fuel_warning[tank])
			has_low_fuel_warned[tank] = FALSE;
	}
}

fuel_tank_positions get_feeding_tank(unsigned engine_number)
{
	ASSERT(engine_number <= 2);
	return feeding_tank[engine_number];
}

void set_feeding_tank(unsigned engine_number, fuel_tank_positions tank)
{
	ASSERT(engine_number <= 2);
	feeding_tank[engine_number] = tank;
}

int get_auto_fuel_transfer(void)
{
	return auto_fuel_transfer;
}

void set_auto_fuel_transfer(int auto_transfer)
{
	fuel_tank_positions tank;
	for (tank = FUEL_TANK_FWD; tank < NUM_FUEL_TANKS; tank++)
		fuel_transfer[tank] = FUEL_TANK_NONE;

	if (auto_fuel_transfer && !auto_transfer)  // switching from auto to manual
		add_apache_advisory("MAN XFERON");

	auto_fuel_transfer = auto_transfer;
}

void set_fuel_transfer(fuel_tank_positions from_tank, fuel_tank_positions to_tank)
{
	fuel_transfer[from_tank] = to_tank;
}

fuel_tank_positions get_fuel_transfer(fuel_tank_positions from_tank)
{
	return fuel_transfer[from_tank];
}

int get_fuel_booster_pump_status(void)
{
	return fuel_booster_pump_on;
}

void set_fuel_booster_pump_status(int turn_on)
{
	fuel_booster_pump_on = turn_on;
}
