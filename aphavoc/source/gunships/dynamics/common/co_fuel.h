/*
 * co_fuel.h
 *
 *  Created on: 12.sep.2009
 *      Author: arneh
 */

#ifndef CO_FUEL_H_
#define CO_FUEL_H_

typedef enum {
	FUEL_TANK_NONE,
	FUEL_TANK_FWD,
	FUEL_TANK_AFT,
	FUEL_TANK_EXTERNAL_L1,
	FUEL_TANK_EXTERNAL_L2,
	FUEL_TANK_EXTERNAL_R1,
	FUEL_TANK_EXTERNAL_R2,
	NUM_FUEL_TANKS
} fuel_tank_positions;

typedef enum {
	FUEL_TYPE_JP4,
	FUEL_TYPE_JP5,
	FUEL_TYPE_JP8
} fuel_types;

void initialise_fuel_system(void);
void update_fuel_system(void);

int engine_has_fuel_supply(unsigned engine_no);

float get_total_fuel_quantity(void);
float get_fuel_quantity(fuel_tank_positions);
void change_fuel_quantity(fuel_tank_positions tank, float amount);
void refuel_helicopter(float amount);

float get_fuel_flow(unsigned engine_no);

fuel_tank_positions get_feeding_tank(unsigned engine_number);
void set_feeding_tank(unsigned engine_number, fuel_tank_positions tank);

int get_auto_fuel_transfer(void);
void set_auto_fuel_transfer(int auto_transfer);
void set_fuel_transfer(fuel_tank_positions from_tank, fuel_tank_positions to_tank);
fuel_tank_positions get_fuel_transfer(fuel_tank_positions from_tank);

int get_fuel_booster_pump_status(void);
void set_fuel_booster_pump_status(int turn_on);

int aft_fuel_tank_low_fuel(void);
int forward_fuel_tank_low_fuel(void);

#endif /* CO_FUEL_H_ */
