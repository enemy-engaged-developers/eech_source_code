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


#ifndef GUARD_EN_SBTYP_H
#define GUARD_EN_SBTYP_H


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef int entity_sub_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define ENTITY_SUB_TYPE_UNKNOWN			(0)

#define ENTITY_SUB_TYPE_UNINITIALISED	(-1)

#define ENTITY_SUB_TYPE_NONE				(-1)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum ENTITY_SUB_TYPE_AIRCRAFT
{
	ENTITY_SUB_TYPE_AIRCRAFT_AH64D_APACHE_LONGBOW,
	ENTITY_SUB_TYPE_AIRCRAFT_MI28N_HAVOC_B,
	ENTITY_SUB_TYPE_AIRCRAFT_RAH66_COMANCHE,
	ENTITY_SUB_TYPE_AIRCRAFT_KA52_HOKUM_B,
	ENTITY_SUB_TYPE_AIRCRAFT_UH60_BLACK_HAWK,
	ENTITY_SUB_TYPE_AIRCRAFT_MI24D_HIND,
	ENTITY_SUB_TYPE_AIRCRAFT_CH46E_SEA_KNIGHT,
	ENTITY_SUB_TYPE_AIRCRAFT_KA29_HELIX_B,
	ENTITY_SUB_TYPE_AIRCRAFT_CH3_JOLLY_GREEN_GIANT,
	ENTITY_SUB_TYPE_AIRCRAFT_MI17_HIP,
	ENTITY_SUB_TYPE_AIRCRAFT_CH47D_CHINOOK,
	ENTITY_SUB_TYPE_AIRCRAFT_MI6_HOOK,
	ENTITY_SUB_TYPE_AIRCRAFT_A10A_THUNDERBOLT,
	ENTITY_SUB_TYPE_AIRCRAFT_SU25_FROGFOOT,
	ENTITY_SUB_TYPE_AIRCRAFT_F16_FIGHTING_FALCON,
	ENTITY_SUB_TYPE_AIRCRAFT_MIG29_FULCRUM,
	ENTITY_SUB_TYPE_AIRCRAFT_AV8B_HARRIER,
	ENTITY_SUB_TYPE_AIRCRAFT_YAK41_FREESTYLE,
	ENTITY_SUB_TYPE_AIRCRAFT_FA18_HORNET,
	ENTITY_SUB_TYPE_AIRCRAFT_SU33_FLANKER,

	////////////////////////////////////////
	//
	// COMANCHE HOKUM
	//
	////////////////////////////////////////

	ENTITY_SUB_TYPE_AIRCRAFT_AH64A_APACHE,
	ENTITY_SUB_TYPE_AIRCRAFT_KA50_HOKUM,
	ENTITY_SUB_TYPE_AIRCRAFT_OH58D_KIOWA_WARRIOR,
	ENTITY_SUB_TYPE_AIRCRAFT_MV22_OSPREY,
	ENTITY_SUB_TYPE_AIRCRAFT_AH1T_SEACOBRA,
	ENTITY_SUB_TYPE_AIRCRAFT_AH1W_SUPERCOBRA,
	ENTITY_SUB_TYPE_AIRCRAFT_CH53E_SUPER_STALLION,
	ENTITY_SUB_TYPE_AIRCRAFT_C17_GLOBEMASTER_III,
	ENTITY_SUB_TYPE_AIRCRAFT_IL76MD_CANDID_B,
	ENTITY_SUB_TYPE_AIRCRAFT_C130J_HERCULES_II,
	ENTITY_SUB_TYPE_AIRCRAFT_AN12B_CUB,

	NUM_ENTITY_SUB_TYPE_AIRCRAFT
};

#define entity_sub_type_aircraft_valid(SUB_TYPE) (((SUB_TYPE) >= 0) && ((SUB_TYPE) < NUM_ENTITY_SUB_TYPE_AIRCRAFT))

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// remember to update route\bridge.pop to get the correct bridges in each warzone

enum ENTITY_SUB_TYPE_BRIDGES
{
	ENTITY_SUB_TYPE_BRIDGE_BOAT,
	ENTITY_SUB_TYPE_BRIDGE_CAUSEWAY,
	ENTITY_SUB_TYPE_BRIDGE_CONCRETE_ARCH,
	ENTITY_SUB_TYPE_BRIDGE_CONCRETE_WIDE,
	ENTITY_SUB_TYPE_BRIDGE_DESERT,
	ENTITY_SUB_TYPE_BRIDGE_GIRDER,
	ENTITY_SUB_TYPE_BRIDGE_STONE,
	ENTITY_SUB_TYPE_BRIDGE_SUSPENSION,

	NUM_ENTITY_SUB_TYPE_BRIDGES
};

#define entity_sub_type_bridge_valid(SUB_TYPE) (((SUB_TYPE) >= 0) && ((SUB_TYPE) < NUM_ENTITY_SUB_TYPE_BRIDGES))

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum ENTITY_SUB_TYPE_CARGO
{
	ENTITY_SUB_TYPE_CARGO_AMMO,
	ENTITY_SUB_TYPE_CARGO_FUEL,
	ENTITY_SUB_TYPE_CARGO_SUPPLIES,

	NUM_ENTITY_SUB_TYPE_CARGOS
};

#define entity_sub_type_cargo_valid(SUB_TYPE) (((SUB_TYPE) >= 0) && ((SUB_TYPE) < NUM_ENTITY_SUB_TYPE_CARGOS))

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum ENTITY_SUB_TYPE_DIVISION
{
	ENTITY_SUB_TYPE_DIVISION_AIRBORNE_HELICOPTER_DIVISION,
	ENTITY_SUB_TYPE_DIVISION_AIRBORNE_FIXED_WING_DIVISION,
	ENTITY_SUB_TYPE_DIVISION_AIRBORNE_TRANSPORT_DIVISION,
	ENTITY_SUB_TYPE_DIVISION_ARMOURED_DIVISION,
	ENTITY_SUB_TYPE_DIVISION_CARRIER_DIVISION,
	ENTITY_SUB_TYPE_DIVISION_INFANTRY_DIVISION,

	ENTITY_SUB_TYPE_DIVISION_HC_ATTACK_COMPANY,
	ENTITY_SUB_TYPE_DIVISION_HC_TRANSPORT_COMPANY,
	ENTITY_SUB_TYPE_DIVISION_FW_ATTACK_COMPANY,
	ENTITY_SUB_TYPE_DIVISION_FW_FIGHTER_COMPANY,
	ENTITY_SUB_TYPE_DIVISION_FW_TRANSPORT_COMPANY,

	ENTITY_SUB_TYPE_DIVISION_ADA_COMPANY,
	ENTITY_SUB_TYPE_DIVISION_ARMOURED_COMPANY,
	ENTITY_SUB_TYPE_DIVISION_ARTILLERY_COMPANY,
	ENTITY_SUB_TYPE_DIVISION_CARRIER_COMPANY,
	ENTITY_SUB_TYPE_DIVISION_INFANTRY_COMPANY,
	ENTITY_SUB_TYPE_DIVISION_SPECIAL_FORCES_COMPANY,

	NUM_ENTITY_SUB_TYPE_DIVISIONS
};

#define entity_sub_type_division_valid(SUB_TYPE) (((SUB_TYPE) >= 0) && ((SUB_TYPE) < NUM_ENTITY_SUB_TYPE_DIVISIONS))

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum ENTITY_SUB_TYPE_EFFECTS
{
	ENTITY_SUB_TYPE_EFFECT_PARTICLE,
	// Xhit: added entity sub type downwash. (030328)
	ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_DOWNWASH,
	ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_EXPLOSION_PARTICLE,
	ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_EXPLOSION_TRAIL,
	ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_FIRE,
	ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_LIGHT_DAMAGE,
	ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_MEDIUM_DAMAGE,
	ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_MISSILE_TRAIL,
	ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_HEAVY_DAMAGE,
	ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_VEHICLE_WAKE,
	ENTITY_SUB_TYPE_EFFECT_SOUND_AMBIENT_HEAVY_RAIN,
	ENTITY_SUB_TYPE_EFFECT_SOUND_AMBIENT_HEAVY_WIND,
	ENTITY_SUB_TYPE_EFFECT_SOUND_AMBIENT_LIGHT_RAIN,
	ENTITY_SUB_TYPE_EFFECT_SOUND_AMBIENT_LIGHT_WIND,
	ENTITY_SUB_TYPE_EFFECT_SOUND_AMBIENT_JUNGLE,
	ENTITY_SUB_TYPE_EFFECT_SOUND_AMBIENT_SEA,
	ENTITY_SUB_TYPE_EFFECT_SOUND_CHAIN_GUN,
	ENTITY_SUB_TYPE_EFFECT_SOUND_CPG_MESSAGE,
	ENTITY_SUB_TYPE_EFFECT_SOUND_ENGINE,
	ENTITY_SUB_TYPE_EFFECT_SOUND_ENGINE_LOOPING1,
	ENTITY_SUB_TYPE_EFFECT_SOUND_ENGINE_LOOPING2,
	ENTITY_SUB_TYPE_EFFECT_SOUND_INCOMING_MISSILE_WARNING,
	ENTITY_SUB_TYPE_EFFECT_SOUND_LOCK_ON_TONE,
	ENTITY_SUB_TYPE_EFFECT_SOUND_MCA,
	ENTITY_SUB_TYPE_EFFECT_SOUND_MISC,
	ENTITY_SUB_TYPE_EFFECT_SOUND_MISC_SPEECH,
	ENTITY_SUB_TYPE_EFFECT_SOUND_RADAR_LOCKED,
	ENTITY_SUB_TYPE_EFFECT_SOUND_RADAR_TRACKED,
	ENTITY_SUB_TYPE_EFFECT_SOUND_RADIO_MESSAGE,
	ENTITY_SUB_TYPE_EFFECT_SOUND_ROTOR_LOOPING,
	ENTITY_SUB_TYPE_EFFECT_SOUND_ROTOR_TURBINE,
	ENTITY_SUB_TYPE_EFFECT_SOUND_ROTOR_SLAP,
	ENTITY_SUB_TYPE_EFFECT_SOUND_ROTOR_WIND_DOWN,
	ENTITY_SUB_TYPE_EFFECT_SOUND_ROTOR_WIND_UP,
	ENTITY_SUB_TYPE_EFFECT_SOUND_WARNING_MESSAGE,
	ENTITY_SUB_TYPE_EFFECT_SPRITE,

	NUM_ENTITY_SUB_TYPE_EFFECTS
};

#define entity_sub_type_effect_valid(SUB_TYPE) (((SUB_TYPE) >= 0) && ((SUB_TYPE) < NUM_ENTITY_SUB_TYPE_EFFECTS))

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum ENTITY_SUB_TYPE_FIXED
{
	ENTITY_SUB_TYPE_FIXED_UNKNOWN,
	ENTITY_SUB_TYPE_FIXED_BRIDGE_END_SECTION,
	ENTITY_SUB_TYPE_FIXED_BRIDGE_SUPPORTED_MID_SECTION,
	ENTITY_SUB_TYPE_FIXED_BRIDGE_UNSUPPORTED_MID_SECTION,
	ENTITY_SUB_TYPE_FIXED_CITY,
	ENTITY_SUB_TYPE_FIXED_CITY_BUILDING,
	ENTITY_SUB_TYPE_FIXED_CRATER,
	ENTITY_SUB_TYPE_FIXED_ELECTRICITY_PYLON_END_TERMINATOR,
	ENTITY_SUB_TYPE_FIXED_ELECTRICITY_PYLON_STANDARD,
	ENTITY_SUB_TYPE_FIXED_ELECTRICITY_PYLON_START_TERMINATOR,
	ENTITY_SUB_TYPE_FIXED_ELECTRICITY_STATION,
	ENTITY_SUB_TYPE_FIXED_ELECTRICITY_SUBSTATION,
	ENTITY_SUB_TYPE_FIXED_MILITARY_BUILDING,
	ENTITY_SUB_TYPE_FIXED_SCENIC_OBJECT,
	ENTITY_SUB_TYPE_FIXED_TERRAIN_OBJECT,
	NUM_ENTITY_SUB_TYPE_FIXED
};

#define entity_sub_type_fixed_valid(SUB_TYPE) (((SUB_TYPE) >= 0) && ((SUB_TYPE) < NUM_ENTITY_SUB_TYPE_FIXED))

#define NUM_ENTITY_SUB_TYPE_FIXED_BITS	(8)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum ENTITY_SUB_TYPE_GROUPS
{
	ENTITY_SUB_TYPE_GROUP_ATTACK_HELICOPTER,
	ENTITY_SUB_TYPE_GROUP_MARINE_ATTACK_HELICOPTER,
	ENTITY_SUB_TYPE_GROUP_ASSAULT_HELICOPTER,
	ENTITY_SUB_TYPE_GROUP_MARINE_ASSAULT_HELICOPTER,
	ENTITY_SUB_TYPE_GROUP_RECON_HELICOPTER,
	ENTITY_SUB_TYPE_GROUP_RECON_ATTACK_HELICOPTER,
	ENTITY_SUB_TYPE_GROUP_MEDIUM_LIFT_TRANSPORT_HELICOPTER,
	ENTITY_SUB_TYPE_GROUP_HEAVY_LIFT_TRANSPORT_HELICOPTER,

	ENTITY_SUB_TYPE_GROUP_MULTI_ROLE_FIGHTER,
	ENTITY_SUB_TYPE_GROUP_CARRIER_BORNE_ATTACK_AIRCRAFT,
	ENTITY_SUB_TYPE_GROUP_CARRIER_BORNE_INTERCEPTOR,
	ENTITY_SUB_TYPE_GROUP_CLOSE_AIR_SUPPORT_AIRCRAFT,
	ENTITY_SUB_TYPE_GROUP_MEDIUM_LIFT_TRANSPORT_AIRCRAFT,
	ENTITY_SUB_TYPE_GROUP_HEAVY_LIFT_TRANSPORT_AIRCRAFT,

	ENTITY_SUB_TYPE_GROUP_ANTI_AIRCRAFT,
	ENTITY_SUB_TYPE_GROUP_PRIMARY_FRONTLINE,
	ENTITY_SUB_TYPE_GROUP_SECONDARY_FRONTLINE,
	ENTITY_SUB_TYPE_GROUP_SELF_PROPELLED_ARTILLERY,
	ENTITY_SUB_TYPE_GROUP_SELF_PROPELLED_MLRS,
	ENTITY_SUB_TYPE_GROUP_STATIC_INFANTRY,
	ENTITY_SUB_TYPE_GROUP_INFANTRY,
	ENTITY_SUB_TYPE_GROUP_INFANTRY_PATROL,
	ENTITY_SUB_TYPE_GROUP_ASSAULT_SHIP,
	ENTITY_SUB_TYPE_GROUP_FRIGATE,
	ENTITY_SUB_TYPE_GROUP_LANDING_CRAFT,
	ENTITY_SUB_TYPE_GROUP_BUILDINGS,

	NUM_ENTITY_SUB_TYPE_GROUPS
};

#define entity_sub_type_group_valid(SUB_TYPE) (((SUB_TYPE) >= 0) && ((SUB_TYPE) < NUM_ENTITY_SUB_TYPE_GROUPS))

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum ENTITY_SUB_TYPE_GUIDES
{
	ENTITY_SUB_TYPE_GUIDE_NAVIGATION_DIRECT,
	ENTITY_SUB_TYPE_GUIDE_NAVIGATION_VIRTUAL,
	ENTITY_SUB_TYPE_GUIDE_NAVIGATION_ROUTED,
	ENTITY_SUB_TYPE_GUIDE_NAVIGATION_ALTITUDE,

	ENTITY_SUB_TYPE_GUIDE_LANDING_DIRECT,

	ENTITY_SUB_TYPE_GUIDE_LANDED,

	ENTITY_SUB_TYPE_GUIDE_ATTACK_AA_MOVE_SIX,
	ENTITY_SUB_TYPE_GUIDE_ATTACK_AA_MOVE_CIRCLE,
	ENTITY_SUB_TYPE_GUIDE_ATTACK_AA_FIRE_INTERCEPT,

	ENTITY_SUB_TYPE_GUIDE_ATTACK_AG_APPROACH,
	ENTITY_SUB_TYPE_GUIDE_ATTACK_AG_SEEK_COVER,
	ENTITY_SUB_TYPE_GUIDE_ATTACK_AG_FLY_TO_COVER,
	ENTITY_SUB_TYPE_GUIDE_ATTACK_AG_TAKE_COVER,
	ENTITY_SUB_TYPE_GUIDE_ATTACK_AG_CLIMB,
	ENTITY_SUB_TYPE_GUIDE_ATTACK_AG_DIVE,
	ENTITY_SUB_TYPE_GUIDE_ATTACK_AG_FIRE,
	ENTITY_SUB_TYPE_GUIDE_ATTACK_AG_FIRE_VIRTUAL,
	ENTITY_SUB_TYPE_GUIDE_ATTACK_AG_DISENGAGE,
	ENTITY_SUB_TYPE_GUIDE_ATTACK_AG_DISENGAGE_VIRTUAL,
	ENTITY_SUB_TYPE_GUIDE_ATTACK_AG_EGRESS,

	ENTITY_SUB_TYPE_GUIDE_ATTACK_AG_HASTY_FIRE,
	ENTITY_SUB_TYPE_GUIDE_ATTACK_AG_HASTY_TAKE_COVER,

	NUM_ENTITY_SUB_TYPE_GUIDES
};

#define entity_sub_type_guide_valid(SUB_TYPE) (((SUB_TYPE) >= 0) && ((SUB_TYPE) < NUM_ENTITY_SUB_TYPE_GUIDES))

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum ENTITY_SUB_TYPE_HIERARCHY
{
	ENTITY_SUB_TYPE_HIERARCHY_ARMY,
	ENTITY_SUB_TYPE_HIERARCHY_CORPS,
	ENTITY_SUB_TYPE_HIERARCHY_DIVISION,
	ENTITY_SUB_TYPE_HIERARCHY_REGIMENT,
	ENTITY_SUB_TYPE_HIERARCHY_BATALLION,
	ENTITY_SUB_TYPE_HIERARCHY_COMPANY,
	ENTITY_SUB_TYPE_HIERARCHY_PLATOON,
	ENTITY_SUB_TYPE_HIERARCHY_SECTION,
	NUM_ENTITY_SUB_TYPE_HIERARCHYS
};

#define entity_sub_type_hierarchy_valid(SUB_TYPE) (((SUB_TYPE) >= 0) && ((SUB_TYPE) < NUM_ENTITY_SUB_TYPE_HIERARCHYS))

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum ENTITY_SUB_TYPE_KEYSITES
{
	ENTITY_SUB_TYPE_KEYSITE_AIRBASE,
	ENTITY_SUB_TYPE_KEYSITE_ANCHORAGE,
	ENTITY_SUB_TYPE_KEYSITE_FACTORY,
	ENTITY_SUB_TYPE_KEYSITE_FARP,
	ENTITY_SUB_TYPE_KEYSITE_MILITARY_BASE,
	ENTITY_SUB_TYPE_KEYSITE_PORT,
	ENTITY_SUB_TYPE_KEYSITE_POWER_STATION,
	ENTITY_SUB_TYPE_KEYSITE_OIL_REFINERY,
	ENTITY_SUB_TYPE_KEYSITE_RADIO_TRANSMITTER,
	NUM_ENTITY_SUB_TYPE_KEYSITES
};

#define entity_sub_type_keysite_valid(SUB_TYPE) (((SUB_TYPE) >= 0) && ((SUB_TYPE) < NUM_ENTITY_SUB_TYPE_KEYSITES))

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum ENTITY_SUB_TYPE_LANDING
{
	ENTITY_SUB_TYPE_LANDING_FIXED_WING,
	ENTITY_SUB_TYPE_LANDING_FIXED_WING_TRANSPORT,
	ENTITY_SUB_TYPE_LANDING_HELICOPTER,
	ENTITY_SUB_TYPE_LANDING_GROUND,
	ENTITY_SUB_TYPE_LANDING_PEOPLE,
	ENTITY_SUB_TYPE_LANDING_SEA,
	NUM_ENTITY_SUB_TYPE_LANDINGS
};

#define entity_sub_type_landing_valid(SUB_TYPE) (((SUB_TYPE) >= 0) && ((SUB_TYPE) < NUM_ENTITY_SUB_TYPE_LANDINGS))

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum ENTITY_SUB_TYPE_PILOT
{
	ENTITY_SUB_TYPE_PILOT_PILOT,
	ENTITY_SUB_TYPE_PILOT_CO_PILOT,
	NUM_ENTITY_SUB_TYPE_PILOTS
};

#define entity_sub_type_pilot_valid(SUB_TYPE) (((SUB_TYPE) >= 0) && ((SUB_TYPE) < NUM_ENTITY_SUB_TYPE_PILOTS))

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum ENTITY_SUB_TYPE_REGEN
{
	ENTITY_SUB_TYPE_REGEN_FIXED_WING,
	ENTITY_SUB_TYPE_REGEN_HELICOPTER,
	ENTITY_SUB_TYPE_REGEN_GROUND,
	ENTITY_SUB_TYPE_REGEN_PEOPLE,
	ENTITY_SUB_TYPE_REGEN_SEA,
	ENTITY_SUB_TYPE_REGEN_NONE,
	NUM_ENTITY_SUB_TYPE_REGENS
};

#define entity_sub_type_regen_valid(SUB_TYPE) (((SUB_TYPE) >= 0) && ((SUB_TYPE) < NUM_ENTITY_SUB_TYPE_REGENS))

extern int
	entity_sub_type_regen_object_numbers [];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum ENTITY_SUB_TYPE_SITES
{
	ENTITY_SUB_TYPE_SITE_KIEV_CLASS,
	ENTITY_SUB_TYPE_SITE_TARAWA,
	ENTITY_SUB_TYPE_SITE_OLIVER_HAZARD_PERRY_CLASS,
	ENTITY_SUB_TYPE_SITE_KRIVAK_II_CLASS,
	ENTITY_SUB_TYPE_SITE_LANDING_CRAFT,
	ENTITY_SUB_TYPE_SITE_LCAC,
	ENTITY_SUB_TYPE_SITE_AIST_CLASS,
	NUM_ENTITY_SUB_TYPE_SITES
};

#define entity_sub_type_site_valid(SUB_TYPE) (((SUB_TYPE) >= 0) && ((SUB_TYPE) < NUM_ENTITY_SUB_TYPE_SITES))

extern int
	entity_sub_type_site_object_numbers [];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum ENTITY_SUB_TYPE_TASKS
{
	ENTITY_SUB_TYPE_TASK_NOTHING,											// nothing
	ENTITY_SUB_TYPE_TASK_ADVANCE,											// scan for targets
	ENTITY_SUB_TYPE_TASK_ANTI_SHIP_STRIKE,
	ENTITY_SUB_TYPE_TASK_BAI,												// given target
	ENTITY_SUB_TYPE_TASK_BARCAP,
	ENTITY_SUB_TYPE_TASK_BDA,												// no engage
	ENTITY_SUB_TYPE_TASK_CLOSE_AIR_SUPPORT, 							// given target
	ENTITY_SUB_TYPE_TASK_COASTAL_PATROL, 								// no engage
	ENTITY_SUB_TYPE_TASK_COMBAT_AIR_PATROL,							// scan for targets
	ENTITY_SUB_TYPE_TASK_ENGAGE, 											// given target
	ENTITY_SUB_TYPE_TASK_ESCORT, 											// notified of target
	ENTITY_SUB_TYPE_TASK_FREE_FLIGHT, 									// no engage
	ENTITY_SUB_TYPE_TASK_GROUND_STRIKE, 								// given target
	ENTITY_SUB_TYPE_TASK_LANDING,				 							// no engage
	ENTITY_SUB_TYPE_TASK_LANDING_HOLDING, 								// no engage
	ENTITY_SUB_TYPE_TASK_OCA_STRIKE,
	ENTITY_SUB_TYPE_TASK_OCA_SWEEP,
	ENTITY_SUB_TYPE_TASK_RECON, 											// no engage
	ENTITY_SUB_TYPE_TASK_REPAIR, 											// no engage
	ENTITY_SUB_TYPE_TASK_RETREAT,											// scan for targets
	ENTITY_SUB_TYPE_TASK_SEAD,												// given target
	ENTITY_SUB_TYPE_TASK_SUPPLY, 											// no engage
	ENTITY_SUB_TYPE_TASK_TAKEOFF, 										// no engage
	ENTITY_SUB_TYPE_TASK_TAKEOFF_HOLDING, 								// no engage
	ENTITY_SUB_TYPE_TASK_TRANSFER_FIXED_WING,							// no engage
	ENTITY_SUB_TYPE_TASK_TRANSFER_HELICOPTER,	 						// no engage
	ENTITY_SUB_TYPE_TASK_TROOP_INSERTION,								// scan for targets
	ENTITY_SUB_TYPE_TASK_TROOP_MOVEMENT_INSERT_CAPTURE,			// scan for targets
	ENTITY_SUB_TYPE_TASK_TROOP_MOVEMENT_INSERT_DEFEND,				// scan for targets
	ENTITY_SUB_TYPE_TASK_TROOP_MOVEMENT_PATROL,						// scan for targets

	NUM_ENTITY_SUB_TYPE_TASKS
};

#define entity_sub_type_task_valid(SUB_TYPE) (((SUB_TYPE) >= 0) && ((SUB_TYPE) < NUM_ENTITY_SUB_TYPE_TASKS))

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum ENTITY_SUB_TYPE_VEHICLES
{
	ENTITY_SUB_TYPE_VEHICLE_M1A2_ABRAMS,
	ENTITY_SUB_TYPE_VEHICLE_T80U,
	ENTITY_SUB_TYPE_VEHICLE_M2A2_BRADLEY,
	ENTITY_SUB_TYPE_VEHICLE_BMP2,
	ENTITY_SUB_TYPE_VEHICLE_BMP3,
	ENTITY_SUB_TYPE_VEHICLE_M113A2,
	ENTITY_SUB_TYPE_VEHICLE_BTR80,
	ENTITY_SUB_TYPE_VEHICLE_M1025_HUMVEE,
	ENTITY_SUB_TYPE_VEHICLE_BRDM2,
	ENTITY_SUB_TYPE_VEHICLE_M109A2,
	ENTITY_SUB_TYPE_VEHICLE_2S19,
	ENTITY_SUB_TYPE_VEHICLE_M270_MLRS,
	ENTITY_SUB_TYPE_VEHICLE_BM21_GRAD,
	ENTITY_SUB_TYPE_VEHICLE_M163_VULCAN,
	ENTITY_SUB_TYPE_VEHICLE_SA19_GRISON,
	ENTITY_SUB_TYPE_VEHICLE_M1037_AVENGER,
	ENTITY_SUB_TYPE_VEHICLE_M48A1_CHAPARRAL,
	ENTITY_SUB_TYPE_VEHICLE_SA13_GOPHER,
	ENTITY_SUB_TYPE_VEHICLE_M998_HUMVEE,
	ENTITY_SUB_TYPE_VEHICLE_UAZ469B,
	ENTITY_SUB_TYPE_VEHICLE_M923A1_BIG_FOOT,
	ENTITY_SUB_TYPE_VEHICLE_M923A1_BIG_FOOT_COVERED,
	ENTITY_SUB_TYPE_VEHICLE_URAL_4320,
	ENTITY_SUB_TYPE_VEHICLE_M978_HEMTT,
	ENTITY_SUB_TYPE_VEHICLE_URAL_FUEL_TANKER,
	ENTITY_SUB_TYPE_VEHICLE_TARAWA_CLASS,
	ENTITY_SUB_TYPE_VEHICLE_KIEV_CLASS,
	ENTITY_SUB_TYPE_VEHICLE_OLIVER_HAZARD_PERRY_CLASS,
	ENTITY_SUB_TYPE_VEHICLE_KRIVAK_II_CLASS,
	ENTITY_SUB_TYPE_VEHICLE_LCU,
	ENTITY_SUB_TYPE_VEHICLE_LCAC,
	ENTITY_SUB_TYPE_VEHICLE_AIST_CLASS,
	ENTITY_SUB_TYPE_VEHICLE_US_INFANTRY,
	ENTITY_SUB_TYPE_VEHICLE_US_INFANTRY_SAM_STANDING,
	ENTITY_SUB_TYPE_VEHICLE_US_INFANTRY_SAM_KNEELING,
	ENTITY_SUB_TYPE_VEHICLE_CIS_INFANTRY,
	ENTITY_SUB_TYPE_VEHICLE_CIS_INFANTRY_SAM_STANDING,
	ENTITY_SUB_TYPE_VEHICLE_CIS_INFANTRY_SAM_KNEELING,
	NUM_ENTITY_SUB_TYPE_VEHICLES
};

#define entity_sub_type_vehicle_valid(SUB_TYPE) (((SUB_TYPE) >= 0) && ((SUB_TYPE) < NUM_ENTITY_SUB_TYPE_VEHICLES))

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum ENTITY_SUB_TYPE_WAYPOINTS
{
	ENTITY_SUB_TYPE_WAYPOINT_APPROACH,
	ENTITY_SUB_TYPE_WAYPOINT_ATTACK,
	ENTITY_SUB_TYPE_WAYPOINT_CAP_LOOP,
	ENTITY_SUB_TYPE_WAYPOINT_CAP_START,
	ENTITY_SUB_TYPE_WAYPOINT_CONVOY,
	ENTITY_SUB_TYPE_WAYPOINT_DEFEND,
	ENTITY_SUB_TYPE_WAYPOINT_DROP_OFF,
	ENTITY_SUB_TYPE_WAYPOINT_END,
	ENTITY_SUB_TYPE_WAYPOINT_ESCORT,
	ENTITY_SUB_TYPE_WAYPOINT_FINISH_DROP_OFF,
	ENTITY_SUB_TYPE_WAYPOINT_HOLDING,
	ENTITY_SUB_TYPE_WAYPOINT_HOLDING_LOOP,
	ENTITY_SUB_TYPE_WAYPOINT_IMPOSSIBLE,
	ENTITY_SUB_TYPE_WAYPOINT_LAND,
	ENTITY_SUB_TYPE_WAYPOINT_LANDED,
	ENTITY_SUB_TYPE_WAYPOINT_LIFT_OFF,
	ENTITY_SUB_TYPE_WAYPOINT_LOWER_UNDERCARRIAGE,
	ENTITY_SUB_TYPE_WAYPOINT_NAVIGATION,
	ENTITY_SUB_TYPE_WAYPOINT_PREPARE_FOR_DROP_OFF,
	ENTITY_SUB_TYPE_WAYPOINT_PICK_UP,
	ENTITY_SUB_TYPE_WAYPOINT_RAISE_UNDERCARRIAGE,
	ENTITY_SUB_TYPE_WAYPOINT_RECON,
	ENTITY_SUB_TYPE_WAYPOINT_REPAIR,
	ENTITY_SUB_TYPE_WAYPOINT_REVERSE_CONVOY,
	ENTITY_SUB_TYPE_WAYPOINT_START_UP,
	ENTITY_SUB_TYPE_WAYPOINT_SUB_ROUTE_NAVIGATION,
	ENTITY_SUB_TYPE_WAYPOINT_TAKEN_OFF,
	ENTITY_SUB_TYPE_WAYPOINT_TARGET,
	ENTITY_SUB_TYPE_WAYPOINT_TAXI,
	ENTITY_SUB_TYPE_WAYPOINT_TOUCH_DOWN,
	ENTITY_SUB_TYPE_WAYPOINT_TROOP_CAPTURE,
	ENTITY_SUB_TYPE_WAYPOINT_TROOP_DEFEND,
	ENTITY_SUB_TYPE_WAYPOINT_TROOP_INSERT,
	ENTITY_SUB_TYPE_WAYPOINT_TROOP_PICKUP_POINT_END,
	ENTITY_SUB_TYPE_WAYPOINT_TROOP_PICKUP_POINT_START,
	ENTITY_SUB_TYPE_WAYPOINT_TROOP_PUTDOWN_POINT,
	ENTITY_SUB_TYPE_WAYPOINT_WAIT,

	NUM_ENTITY_SUB_TYPE_WAYPOINTS
};

#define entity_sub_type_waypoint_valid(SUB_TYPE) (((SUB_TYPE) >= 0) && ((SUB_TYPE) < NUM_ENTITY_SUB_TYPE_WAYPOINTS))

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum ENTITY_SUB_TYPE_WEAPONS
{
	ENTITY_SUB_TYPE_WEAPON_NO_WEAPON,

	////////////////////////////////////////
	//
	// BALLISTIC WEAPONS
	//
	////////////////////////////////////////

	// US

	ENTITY_SUB_TYPE_WEAPON_M2_12P7MM_ROUND,
	ENTITY_SUB_TYPE_WEAPON_M61A1_20MM_ROUND,
	ENTITY_SUB_TYPE_WEAPON_M197_20MM_ROUND,
	ENTITY_SUB_TYPE_WEAPON_GAU12U_25MM_ROUND,
	ENTITY_SUB_TYPE_WEAPON_M242_25MM_ROUND,
	ENTITY_SUB_TYPE_WEAPON_GAU8A_30MM_ROUND,
	ENTITY_SUB_TYPE_WEAPON_M230_30MM_ROUND,
	ENTITY_SUB_TYPE_WEAPON_M75_76MM_ROUND,
	ENTITY_SUB_TYPE_WEAPON_M256_120MM_ROUND,
	ENTITY_SUB_TYPE_WEAPON_M284_155MM_ROUND,
	ENTITY_SUB_TYPE_WEAPON_M270_227MM_ROCKET,

	// CIS

	ENTITY_SUB_TYPE_WEAPON_NSV_12P7MM_ROUND,
	ENTITY_SUB_TYPE_WEAPON_9A642_12P7MM_ROUND,
	ENTITY_SUB_TYPE_WEAPON_KPV_14P5MM_ROUND,
	ENTITY_SUB_TYPE_WEAPON_GSH23L_23MM_ROUND,
	ENTITY_SUB_TYPE_WEAPON_GSH301_30MM_ROUND,
	ENTITY_SUB_TYPE_WEAPON_2A38M_30MM_ROUND,
	ENTITY_SUB_TYPE_WEAPON_2A42_30MM_ROUND,
	ENTITY_SUB_TYPE_WEAPON_2A42_30MM_HE_ROUND,
	ENTITY_SUB_TYPE_WEAPON_2A42_30MM_AP_ROUND,
	ENTITY_SUB_TYPE_WEAPON_2A72_30MM_ROUND,
	ENTITY_SUB_TYPE_WEAPON_AO17A_30MM_ROUND,
	ENTITY_SUB_TYPE_WEAPON_ADMG_630_30MM_ROUND,
	ENTITY_SUB_TYPE_WEAPON_CIS_NAVAL_76MM_ROUND,
	ENTITY_SUB_TYPE_WEAPON_CIS_NAVAL_100MM_ROUND,
	ENTITY_SUB_TYPE_WEAPON_2K23_100MM_ROUND,
	ENTITY_SUB_TYPE_WEAPON_BM21_122MM_ROCKET,
	ENTITY_SUB_TYPE_WEAPON_2A46M1_125MM_ROUND,
	ENTITY_SUB_TYPE_WEAPON_2A65_152MM_ROUND,

	////////////////////////////////////////
	//
	// UNGUIDED ROCKETS
	//
	////////////////////////////////////////

	// US

	ENTITY_SUB_TYPE_WEAPON_HYDRA70_M255,
	ENTITY_SUB_TYPE_WEAPON_HYDRA70_M261,
	ENTITY_SUB_TYPE_WEAPON_LAU69A,

	// CIS

	ENTITY_SUB_TYPE_WEAPON_S5,
	ENTITY_SUB_TYPE_WEAPON_S8,
	ENTITY_SUB_TYPE_WEAPON_S13,

	////////////////////////////////////////
	//
	// AIR-TO-AIR GUIDED MISSILES
	//
	////////////////////////////////////////

	// US

	ENTITY_SUB_TYPE_WEAPON_AIM92_STINGER,
	ENTITY_SUB_TYPE_WEAPON_AIM9M_SIDEWINDER,
	ENTITY_SUB_TYPE_WEAPON_AIM120_AMRAAM,

	// CIS

	ENTITY_SUB_TYPE_WEAPON_IGLA_V,
	ENTITY_SUB_TYPE_WEAPON_AA8A_APHID,
	ENTITY_SUB_TYPE_WEAPON_AA8B_APHID,
	ENTITY_SUB_TYPE_WEAPON_AA10A_ALAMO,
	ENTITY_SUB_TYPE_WEAPON_AA10B_ALAMO,
	ENTITY_SUB_TYPE_WEAPON_AA11_ARCHER,

	////////////////////////////////////////
	//
	// AIR-TO-SURFACE GUIDED MISSILES
	//
	////////////////////////////////////////

	// US

	ENTITY_SUB_TYPE_WEAPON_AGM114L_LONGBOW_HELLFIRE,
	ENTITY_SUB_TYPE_WEAPON_AGM114K_HELLFIRE_II,
	ENTITY_SUB_TYPE_WEAPON_AGM65D_MAVERICK,
	ENTITY_SUB_TYPE_WEAPON_AGM65F_MAVERICK,

	// CIS

	ENTITY_SUB_TYPE_WEAPON_ATAKA,
	ENTITY_SUB_TYPE_WEAPON_VIKHR,
	ENTITY_SUB_TYPE_WEAPON_AT6_SPIRAL,
	ENTITY_SUB_TYPE_WEAPON_AS10_KAREN,
	ENTITY_SUB_TYPE_WEAPON_AS14_KEDGE,

	////////////////////////////////////////
	//
	// SURFACE-TO-AIR GUIDED MISSILES
	//
	////////////////////////////////////////

	// US

	ENTITY_SUB_TYPE_WEAPON_CHAPARRAL,
	ENTITY_SUB_TYPE_WEAPON_FIM92A_STINGER,
	ENTITY_SUB_TYPE_WEAPON_SM1MR_STANDARD,
	ENTITY_SUB_TYPE_WEAPON_SEA_SPARROW,

	// CIS

	ENTITY_SUB_TYPE_WEAPON_SA7_GRAIL,
	ENTITY_SUB_TYPE_WEAPON_SA13_GOPHER,
	ENTITY_SUB_TYPE_WEAPON_SA19_GRISON,
	ENTITY_SUB_TYPE_WEAPON_SAN3_GOBLET,
	ENTITY_SUB_TYPE_WEAPON_SAN4_GECKO,

	////////////////////////////////////////
	//
	// SURFACE-TO-SURFACE GUIDED MISSILES
	//
	////////////////////////////////////////

	// US

	ENTITY_SUB_TYPE_WEAPON_M220_TOW2B,

	// CIS

	ENTITY_SUB_TYPE_WEAPON_AT5_SPANDREL,
	ENTITY_SUB_TYPE_WEAPON_AT10_STABBER,
	ENTITY_SUB_TYPE_WEAPON_AT11_SNIPER,

	////////////////////////////////////////
	//
	// DECOYS
	//
	////////////////////////////////////////

	ENTITY_SUB_TYPE_WEAPON_CHAFF,
	ENTITY_SUB_TYPE_WEAPON_FLARE,
	ENTITY_SUB_TYPE_WEAPON_SMOKE_GRENADE,

	////////////////////////////////////////
	//
	// CARGO
	//
	////////////////////////////////////////

	ENTITY_SUB_TYPE_WEAPON_CRATE,

	////////////////////////////////////////
	//
	// DEBRIS
	//
	////////////////////////////////////////

	ENTITY_SUB_TYPE_WEAPON_HOKUM_BLADE,
	ENTITY_SUB_TYPE_WEAPON_HOKUM_PILOT,
	ENTITY_SUB_TYPE_WEAPON_HOKUM_CO_PILOT,
	ENTITY_SUB_TYPE_WEAPON_HOKUM_LH_DOOR,
	ENTITY_SUB_TYPE_WEAPON_HOKUM_RH_DOOR,

	NUM_ENTITY_SUB_TYPE_WEAPONS
};

#define entity_sub_type_weapon_valid(SUB_TYPE) (((SUB_TYPE) >= 0) && ((SUB_TYPE) < NUM_ENTITY_SUB_TYPE_WEAPONS))

#define NUM_ENTITY_SUB_TYPE_WEAPON_BITS	(7)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern const char
	*entity_sub_type_aircraft_names [],
	*entity_sub_type_bridge_names [],
	*entity_sub_type_cargo_names [],
	*entity_sub_type_division_names [],
	*entity_sub_type_effect_names [],
	*entity_sub_type_fixed_names [],
	*entity_sub_type_group_names [],
	*entity_sub_type_guide_names [],
	*entity_sub_type_hierarchy_names [],
	*entity_sub_type_keysite_names [],
	*entity_sub_type_landing_names [],
	*entity_sub_type_pilot_names [],
	*entity_sub_type_regen_names [],
	*entity_sub_type_site_names [],
	*entity_sub_type_vehicle_names [],
	*entity_sub_type_task_names [],
	*entity_sub_type_waypoint_names [],
	*entity_sub_type_weapon_names [];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // GUARD_EN_SBTYP_H
