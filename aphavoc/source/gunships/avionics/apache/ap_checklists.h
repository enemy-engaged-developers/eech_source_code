/*
 * ap_checklists.h
 *
 *  Created on: 07.sep.2009
 *      Author: arneh
 */

#ifndef AP_CHECKLISTS_H_
#define AP_CHECKLISTS_H_


static const char* checklist_menu[] = {
	"CHECKLISTS",
	"",
	"AFTER STARTING APU",
	"BEFORE STARTING ENGINES",
	"STARTING ENGINES",
	"BEFORE TAXI",
	"TAXI",
	"BEFORE TAKEOFF",
	"BEFORE LANDING",
	"AFTER LANDING",
	"ENGINE SHUTDOWN"
};

static const char* tf_checklist_menu[] = {
	"THROUGH FLIGHT CHECKLISTS",
	"",
	"TF AFTER STARTING APU",
	"TF BEFORE STARTING ENGINES",
	"TF STARTING ENGINES",
	"TF BEFORE TAXI",
	"TF TAXI",
	"TF BEFORE TAKEOFF",
	"TF BEFORE LANDING",
};

static const char* perf_data1_checklist_menu[] = {
	"PERF DATA 1",
	"",
	"RAPID REFUELING",
	"RAPID REARMING",
	"STARTING ENGINE",
	"FCR OPERATIONAL CHECK",
	"PILOT IHADSS BORESIGHT",
	"FLIR OPERATIONAL CHECK"
};

static const char* perf_data2_checklist_menu[] = {
	"PERF DATA 1",
	"",
	"MANUAL DRIFT NULL",
	"PECHAN REALIGNMENT",
	"CUE UPDATE PROC",
	"TADS OPERATIONAL CHECK",
	"TADS OUTFRONT BORESIGHT",
	"FLIGHT CONTROL TEST"
};

static const char* checklist_after_starting_apu[] = {
	"AFTER STARTING APU",
	"",
	"PNVS - AS DESIRED",
	"STANDBY ATT IND - UNCAGE",
	"MPD PAGES - AS DESIRED",
	"RADAR ALTIMETER - ON",
	"AVIONICS - AS DESIRED",
	"CANOPY DOOR - SECURE",
	// "FCC" ?
	"CONTROL SWEEP - CHECK",
	"STABILIATOR - CHECK",
	// "HARS" ?
	"BUCS - CHECK",
	"IHADSS BORESIGHT - AS REQ",
	"FLIR - CHECK",
	"RADAR ALTIMETER - TEST"
};

static const char* checklist_before_starting_engines[] = {
	"BEFORE STARTING ENGINES",
	"",
	"SHAFT DRIVEN COMP - NO WARN",
	"ANTI COL - AS DESIRED"
};

static const char* checklist_starting_engines[] = {
	"STARTING ENGINES",
	"",
	"AREA - CLEAR",
	"RTR BK - OFF OR LOCK",
	"START SWITCH - START",
	"PWR LEVEL - IDLE",
	"ENG OIL - MONITOR",
	"TGT - MONITOR",
	"NG RPM - MONITOR",
	"REPEAT FOR SECOND ENGINE",
	"RTR BK - OFF",
	"PWR LEVERS - FLY",
	"NP AND NT - 100%",
	"CAUTION/WARNINGS - CHECK",
	"ANTI-ICE - AS REQUIRED",
	"APU - OFF"
};

static const char* checklist_before_taxi[] = {
	"BEFORE TAXI",
	"",
	"PYLON SAFETY PINS - REMOVED",
	"ARM SAFETY PINS - REMOVED",
	"CHOCKS - REMOVED",
	"ICS CORDS - REMOVED",
	// HARS
	"DASE - AS DESIRED",
	// HIT
	"ASE SETTINGS - AS DESIRED",
	"EXT LT - AS DESIRED",
	"PARK BRAKE - RELEASE",
	"TAIL WHEEL - UNLOCK"
};

static const char* checklist_taxi[] = {
	"TAXI",
	"",
	"WHEEL BRAKES - CHECK",
	"ENGINE/ROTOR INSTR - CHECK",
	"FLIGHT INSTR - CHECK",
	"INCR COLLECTIVE - 20-24% TRQ",
	"MOVE CYCLIC FORWARD",
};

static const char* checklist_before_to[] = {
	"BEFORE TAKE OFF",
	"",
	// HARS
	"WPN - SAFE",
	"TAIL WHEEL - LOCK",
	"PARK BRAKE - AS DESIRED",
	"FUEL - CHECK",
	"ENGINE - CHECK",
	"CAUTION/WARNING - CHECK",
	"PWR LEVERS - FLY",
	"POWER CHECK"
};

static const char* checklist_before_landing[] = {
	"BEFORE LANDING",
	"",
	"WPN - SAFE",
	"TAIL WHEEL - LCOK",
	"PARK BRAKE - AS REQUIRED"
};

static const char* checklist_after_landing[] = {
	"AFTER LANDING",
	"",
	"TAIL WHEEL - AS REQUIRED",
	"EXT LT - AS REQUIRED",
	"AVIONICS - AS REQUIRED",
	"ANTI-ICE - OFF",
	"TADS/PNVS - OFF",
	"ASE - AS REQUIRED",
};

static const char* checklist_engine_shutdown[] = {
	"ENGINE SHUTDOWN",
	"",
	"TAIL WHEEL - LOCK",
	"PARK BRAKE - SET",
	"APU - START THEN RELEASE",
	"TGT SYSTEM - OFF",
	"PNVS - OFF",
	"WPN - SAFE",
	"DASE - RELEASE",
	"STANDBY ATTITUDE IND - CAGE",
	"MPDS - OFF",
	"RADAR ALTIMETER - OFF",
	// HARS
	"APU ON",
	"SHAFT DRIVEN COMP - NO WARN",
	"PWR LEVERS - IDLE",
	"COOL ENGINES FOR 2 MIN",
	"PWR LEVERS - OFF",
	"FUEL EXT TANK - OFF",
	"FUEL TRANS - OFF",
	"FUEL CROSSFEED - NORM",
	"TGT - MONITOR",
	"RTR BRAKE - BRAKE BELOW 50%NR",
	"AVIONICS - OFF",
	"STABILIZER - 0 DEG",
	"RTR BK - OFF WHEN ROTOR STOPS",
	"SRCH LT - STOW",
	"CONTROL LOCKS - INSTALL",
	"GEN 1 AND GEN 2 - OFF",
	"APU - OFF",
	"BATT/EXT PWR - OFF",
	"IGNITION KEY - OFF",
	"CANOPY JETTS PIN - INSTALL",
	"LIGHT SWITCHES - OFF",
};

#endif /* AP_CHECKLISTS_H_ */
