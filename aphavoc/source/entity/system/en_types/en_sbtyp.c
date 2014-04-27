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

const char *entity_sub_type_aircraft_names [] =
{

	"AIRCRAFT_AH64D_APACHE_LONGBOW",
	"AIRCRAFT_MI28N_HAVOC_B",
	"AIRCRAFT_RAH66_COMANCHE",
	"AIRCRAFT_KA52_HOKUM_B",
	"AIRCRAFT_UH60_BLACK_HAWK",
	"AIRCRAFT_MI24D_HIND",
	"AIRCRAFT_CH46E_SEA_KNIGHT",
	"AIRCRAFT_KA29_HELIX_B",
	"AIRCRAFT_CH3_JOLLY_GREEN_GIANT",
	"AIRCRAFT_MI17_HIP",
	"AIRCRAFT_CH47D_CHINOOK",
	"AIRCRAFT_MI6_HOOK",
	"AIRCRAFT_A10A_THUNDERBOLT",
	"AIRCRAFT_SU25_FROGFOOT",
	"AIRCRAFT_F16_FIGHTING_FALCON",
	"AIRCRAFT_MIG29_FULCRUM",
	"AIRCRAFT_AV8B_HARRIER",
	"AIRCRAFT_YAK41_FREESTYLE",
	"AIRCRAFT_FA18_HORNET",
	"AIRCRAFT_SU33_FLANKER",
	"AIRCRAFT_AH64A_APACHE",
	"AIRCRAFT_KA50_HOKUM",
	"AIRCRAFT_OH58D_KIOWA_WARRIOR",
	"AIRCRAFT_MV22_OSPREY",
	"AIRCRAFT_AH1T_SEACOBRA",
	"AIRCRAFT_AH1W_SUPERCOBRA",
	"AIRCRAFT_CH53E_SUPER_STALLION",
	"AIRCRAFT_C17_GLOBEMASTER_III",
	"AIRCRAFT_IL76MD_CANDID_B",
	"AIRCRAFT_C130J_HERCULES_II",
	"AIRCRAFT_AN12B_CUB",
	"AIRCRAFT_AH1Z_VIPER",

	"NUM_ENTITY_SUB_TYPE_AIRCRAFT"
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char *entity_sub_type_bridge_names [] =
{
	"BRIDGE_BOAT",
	"BRIDGE_CAUSEWAY",
	"BRIDGE_CONCRETE_ARCH",
	"BRIDGE_CONCRETE_WIDE",
	"BRIDGE_DESERT",
	"BRIDGE_GIRDER",
	"BRIDGE_STONE",
	"BRIDGE_SUSPENSION",

	"NUM_ENTITY_SUB_TYPE_BRIDGES"
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char *entity_sub_type_cargo_names [] =
{
	"CARGO_AMMO",
	"CARGO_FUEL",
	"CARGO_SUPPLIES",

	"NUM_ENTITY_SUB_TYPE_CARGOS"
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char *entity_sub_type_division_names [] =
{
	"DIVISION_AIRBORNE_HELICOPTER_DIVISION",
	"DIVISION_AIRBORNE_FIXED_WING_DIVISION",
	"DIVISION_AIRBORNE_TRANSPORT_DIVISION",
	"DIVISION_ARMOURED_DIVISION",
	"DIVISION_CARRIER_DIVISION",
	"DIVISION_INFANTRY_DIVISION",

	"DIVISION_HC_ATTACK_COMPANY",
	"DIVISION_HC_TRANSPORT_COMPANY",
	"DIVISION_FW_ATTACK_COMPANY",
	"DIVISION_FW_FIGHTER_COMPANY",
	"DIVISION_FW_TRANSPORT_COMPANY",

	"DIVISION_ADA_COMPANY",
	"DIVISION_ARMOURED_COMPANY",
	"DIVISION_ARTILLERY_COMPANY",
	"DIVISION_CARRIER_COMPANY",
	"DIVISION_INFANTRY_COMPANY",
	"DIVISION_SPECIAL_FORCES_COMPANY",

	"NUM_ENTITY_SUB_TYPE_DIVISIONS"
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char *entity_sub_type_effect_names [] =
{
	"EFFECT_PARTICLE",

	"EFFECT_SMOKE_LIST_DOWNWASH",
	"EFFECT_SMOKE_LIST_EXPLOSION_PARTICLE",
	"EFFECT_SMOKE_LIST_EXPLOSION_TRAIL",
	"EFFECT_SMOKE_LIST_FIRE",
	"EFFECT_SMOKE_LIST_LIGHT_DAMAGE_MOVING",
	"EFFECT_SMOKE_LIST_HEAVY_DAMAGE_MOVING",
	"EFFECT_SMOKE_LIST_LIGHT_DAMAGE_STATIC",
	"EFFECT_SMOKE_LIST_HEAVY_DAMAGE_STATIC",
	"EFFECT_SMOKE_LIST_MISSILE_TRAIL",
	"EFFECT_SMOKE_LIST_VEHICLE_WAKE",
	"EFFECT_SMOKE_LIST_GUN_SMOKE",

	"EFFECT_SOUND_AMBIENT_HEAVY_RAIN",
	"EFFECT_SOUND_AMBIENT_HEAVY_WIND",
	"EFFECT_SOUND_AMBIENT_LIGHT_RAIN",
	"EFFECT_SOUND_AMBIENT_LIGHT_WIND",
	"EFFECT_SOUND_AMBIENT_JUNGLE",
	"EFFECT_SOUND_AMBIENT_SEA",
	"EFFECT_SOUND_CHAIN_GUN",
	"EFFECT_SOUND_GATLING_GUN",
	"EFFECT_SOUND_GUN_PODS",
	"EFFECT_SOUND_CPG_MESSAGE",
	"EFFECT_SOUND_ENGINE",
	"EFFECT_SOUND_ENGINE_LOOPING1",
	"EFFECT_SOUND_ENGINE_LOOPING2",
	"EFFECT_SOUND_INCOMING_MISSILE_WARNING",
	"EFFECT_SOUND_LOCK_ON_TONE",
	"EFFECT_SOUND_MCA",
	"EFFECT_SOUND_MISC",
	"EFFECT_SOUND_MISC_SPEECH",
	"EFFECT_SOUND_RADAR_LOCKED",
	"EFFECT_SOUND_RADAR_TRACKED",
	"EFFECT_SOUND_RADIO_MESSAGE",
	"EFFECT_SOUND_ROTOR_LOOPING",
	"EFFECT_SOUND_APU_TURBINE",
	"EFFECT_SOUND_ROTOR_TURBINE1",
	"EFFECT_SOUND_ROTOR_TURBINE2",
	"EFFECT_SOUND_ROTOR_SLAP",
	"EFFECT_SOUND_ROTOR_WIND_DOWN1",
	"EFFECT_SOUND_ROTOR_WIND_DOWN2",
	"EFFECT_SOUND_ROTOR_WIND_UP1",
	"EFFECT_SOUND_ROTOR_WIND_UP2",
	"EFFECT_SOUND_WARNING_MESSAGE",

	"EFFECT_SPRITE",

	"EFFECT_SOUND_AMB1",
	"EFFECT_SOUND_AMB2",
	"EFFECT_SOUND_AMB3",
	"EFFECT_SOUND_AMB4",

	"NUM_ENTITY_SUB_TYPE_EFFECTS"
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char *entity_sub_type_fixed_names [] =
{

	"FIXED_UNKNOWN",
	"FIXED_BRIDGE_END_SECTION",
	"FIXED_BRIDGE_SUPPORTED_MID_SECTION",
	"FIXED_BRIDGE_UNSUPPORTED_MID_SECTION",
	"FIXED_CITY",
	"FIXED_CITY_BUILDING",
	"FIXED_CRATER",
	"FIXED_ELECTRICITY_PYLON_END_TERMINATOR",
	"FIXED_ELECTRICITY_PYLON_STANDARD",
	"FIXED_ELECTRICITY_PYLON_START_TERMINATOR",
	"FIXED_ELECTRICITY_STATION",
	"FIXED_ELECTRICITY_SUBSTATION",
	"FIXED_MILITARY_BUILDING",
	"FIXED_SCENIC_OBJECT",
	"FIXED_TERRAIN_OBJECT",
	"NUM_ENTITY_SUB_TYPE_FIXED"
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char *entity_sub_type_group_names [] =
{
	"GROUP_ATTACK_HELICOPTER",
	"GROUP_MARINE_ATTACK_HELICOPTER",
	"GROUP_ASSAULT_HELICOPTER",
	"GROUP_MARINE_ASSAULT_HELICOPTER",
	"GROUP_RECON_HELICOPTER",
	"GROUP_RECON_ATTACK_HELICOPTER",
	"GROUP_MEDIUM_LIFT_TRANSPORT_HELICOPTER",
	"GROUP_HEAVY_LIFT_TRANSPORT_HELICOPTER",

	"GROUP_MULTI_ROLE_FIGHTER",
	"GROUP_CARRIER_BORNE_ATTACK_AIRCRAFT",
	"GROUP_CARRIER_BORNE_INTERCEPTOR",
	"GROUP_CLOSE_AIR_SUPPORT_AIRCRAFT",
	"GROUP_MEDIUM_LIFT_TRANSPORT_AIRCRAFT",
	"GROUP_HEAVY_LIFT_TRANSPORT_AIRCRAFT",

	"GROUP_ANTI_AIRCRAFT",
	"GROUP_PRIMARY_FRONTLINE",
	"GROUP_SECONDARY_FRONTLINE",
	"GROUP_SELF_PROPELLED_ARTILLERY",
	"GROUP_SELF_PROPELLED_MLRS",
	"GROUP_STATIC_INFANTRY",
	"GROUP_INFANTRY",
	"GROUP_INFANTRY_PATROL",
	"GROUP_ASSAULT_SHIP",
	"GROUP_FRIGATE",
	"GROUP_LANDING_CRAFT",
	"GROUP_BUILDINGS",

	"NUM_ENTITY_SUB_TYPE_GROUPS"
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char *entity_sub_type_guide_names [] =
{
	"GUIDE_NAVIGATION_DIRECT",
	"GUIDE_NAVIGATION_VIRTUAL",
	"GUIDE_NAVIGATION_ROUTED",
	"GUIDE_NAVIGATION_ALTITUDE",

	"GUIDE_LANDING_DIRECT",

	"GUIDE_LANDED",

	"GUIDE_ATTACK_AA_MOVE_SIX",
	"GUIDE_ATTACK_AA_MOVE_CIRCLE",
	"GUIDE_ATTACK_AA_FIRE_INTERCEPT",

	"GUIDE_ATTACK_AG_APPROACH",
	"GUIDE_ATTACK_AG_SEEK_COVER",
	"GUIDE_ATTACK_AG_FLY_TO_COVER",
	"GUIDE_ATTACK_AG_TAKE_COVER",
	"GUIDE_ATTACK_AG_CLIMB",
	"GUIDE_ATTACK_AG_DIVE",
	"GUIDE_ATTACK_AG_FIRE",
	"GUIDE_ATTACK_AG_FIRE_VIRTUAL",
	"GUIDE_ATTACK_AG_DISENGAGE",
	"GUIDE_ATTACK_AG_DISENGAGE_VIRTUAL",
	"GUIDE_ATTACK_AG_EGRESS",

	"GUIDE_ATTACK_AG_HASTY_FIRE",
	"GUIDE_ATTACK_AG_HASTY_TAKE_COVER",

	"NUM_ENTITY_SUB_TYPE_GUIDES"
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char *entity_sub_type_hierarchy_names [] =
{
	"HIERARCHY_ARMY",
	"HIERARCHY_CORPS",
	"HIERARCHY_DIVISION",
	"HIERARCHY_REGIMENT",
	"HIERARCHY_BATALLION",
	"HIERARCHY_COMPANY",
	"HIERARCHY_PLATOON",
	"HIERARCHY_SECTION",
	"NUM_ENTITY_SUB_TYPE_HIERARCHYS"
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char *entity_sub_type_keysite_names [] =
{

	"KEYSITE_AIRBASE",
	"KEYSITE_ANCHORAGE",
	"KEYSITE_FACTORY",
	"KEYSITE_FARP",
	"KEYSITE_MILITARY_BASE",
	"KEYSITE_PORT",
	"KEYSITE_POWER_STATION",
	"KEYSITE_OIL_REFINERY",
	"KEYSITE_RADIO_TRANSMITTER",
	"NUM_ENTITY_SUB_TYPE_KEYSITES"
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char *entity_sub_type_landing_names [] =
{

	"LANDING_FIXED_WING",
	"LANDING_FIXED_WING_TRANSPORT",
	"LANDING_HELICOPTER",
	"LANDING_GROUND",
	"LANDING_PEOPLE",
	"LANDING_SEA",
	"NUM_ENTITY_SUB_TYPE_LANDINGS"
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char *entity_sub_type_pilot_names [] =
{
	"PILOT_PILOT",
	"PILOT_CO_PILOT",
	"NUM_ENTITY_SUB_TYPE_PILOTS"
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char *entity_sub_type_regen_names [] =
{
	"REGEN_FIXED_WING",
	"REGEN_HELICOPTER",
	"REGEN_GROUND",
	"REGEN_PEOPLE",
	"REGEN_SEA",
	"REGEN_NONE",
	"NUM_ENTITY_SUB_TYPE_REGENS"
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char *entity_sub_type_site_names [] =
{
	"SITE_BUILDING",
	"SITE_CONTROL_TOWER",
	"SITE_FLAT_BUILDING",
	"SITE_HANGAR",
	"SITE_SKY_SCRAPER1",
	"SITE_KIEV_CLASS",
	"SITE_TARAWA",
	"SITE_OLIVER_HAZARD_PERRY_CLASS",
	"SITE_KRIVAK_II_CLASS",
	"SITE_TARAWA_LANDING_CRAFT",
	"SITE_LCAC",
	"SITE_AIST_CLASS",
	"SITE_AIRFIELD",
	"SITE_CITY1",
	"NUM_ENTITY_SUB_TYPE_SITES"
};

int entity_sub_type_site_object_numbers [] =
{
	OBJECT_3D_KIEV_CLASS,
	OBJECT_3D_TARAWA,
	OBJECT_3D_OLIVER_HAZARD_PERRY,
	OBJECT_3D_KRIVAK_2,
	OBJECT_3D_TARAWA_LANDING_CRAFT,
	OBJECT_3D_LCAC,
	OBJECT_3D_AIST_HOVERCRAFT,
	OBJECT_3D_LAST
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char *entity_sub_type_task_names [] =
{

	"TASK_NOTHING",
	"TASK_ADVANCE",
	"TASK_ANTI_SHIP_STRIKE",
	"TASK_BAI",
	"TASK_BARCAP",
	"TASK_BDA",
	"TASK_CLOSE_AIR_SUPPORT",
	"TASK_COASTAL_PATROL",
	"TASK_COMBAT_AIR_PATROL",
	"TASK_ENGAGE",
	"TASK_ESCORT",
	"TASK_FREE_FLIGHT",
	"TASK_GROUND_STRIKE",
	"TASK_LANDING",
	"TASK_LANDING_HOLDING",
	"TASK_OCA_STRIKE",
	"TASK_OCA_SWEEP",
	"TASK_RECON",
	"TASK_REPAIR",
	"TASK_RETREAT",
	"TASK_SEAD",
	"TASK_SUPPLY",
	"TASK_TAKEOFF",
	"TASK_TAKEOFF_HOLDING",
	"TASK_TRANSFER_FIXED_WING",
	"TASK_TRANSFER_HELICOPTER",
	"TASK_TROOP_INSERTION",
	"TASK_TROOP_MOVEMENT_INSERT_CAPTURE",
	"TASK_TROOP_MOVEMENT_INSERT_DEFEND",
	"TASK_TROOP_MOVEMENT_PATROL",
	"NUM_ENTITY_SUB_TYPE_TASKS"
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char *entity_sub_type_vehicle_names [] =
{

	"VEHICLE_M1A2_ABRAMS",
	"VEHICLE_T80U",
	"VEHICLE_M2A2_BRADLEY",
	"VEHICLE_BMP2",
	"VEHICLE_BMP3",
	"VEHICLE_M113A2",
	"VEHICLE_BTR80",
	"VEHICLE_M1025_HUMVEE",
	"VEHICLE_BRDM2",
	"VEHICLE_M109A2",
	"VEHICLE_2S19",
	"VEHICLE_M270_MLRS",
	"VEHICLE_BM21_GRAD",
	"VEHICLE_M163_VULCAN",
	"VEHICLE_SA19_GRISON",
	"VEHICLE_M1037_AVENGER",
	"VEHICLE_M48A1_CHAPARRAL",
	"VEHICLE_SA13_GOPHER",
	"VEHICLE_M998_HUMVEE",
	"VEHICLE_UAZ469B",
	"VEHICLE_M923A1_BIG_FOOT",
	"VEHICLE_M923A1_BIG_FOOT_COVERED",
	"VEHICLE_URAL_4320",
	"VEHICLE_M978_HEMTT",
	"VEHICLE_URAL_FUEL_TANKER",
	"VEHICLE_TARAWA_CLASS",
	"VEHICLE_KIEV_CLASS",
	"VEHICLE_OLIVER_HAZARD_PERRY_CLASS",
	"VEHICLE_KRIVAK_II_CLASS",
	"VEHICLE_LCU",
	"VEHICLE_LCAC",
	"VEHICLE_AIST_CLASS",
	"VEHICLE_US_INFANTRY",
	"VEHICLE_US_INFANTRY_SAM_STANDING",
	"VEHICLE_US_INFANTRY_SAM_KNEELING",
	"VEHICLE_CIS_INFANTRY",
	"VEHICLE_CIS_INFANTRY_SAM_STANDING",
	"VEHICLE_CIS_INFANTRY_SAM_KNEELING",
	"NUM_ENTITY_SUB_TYPE_VEHICLES"
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char *entity_sub_type_waypoint_names [] =
{
	"WAYPOINT_APPROACH",
	"WAYPOINT_ATTACK",
	"WAYPOINT_CAP_LOOP",
	"WAYPOINT_CAP_START",
	"WAYPOINT_CONVOY",
	"WAYPOINT_DEFEND",
	"WAYPOINT_DROP_OFF",
	"WAYPOINT_END",
	"WAYPOINT_ESCORT",
	"WAYPOINT_FINISH_DROP_OFF",
	"WAYPOINT_HOLDING",
	"WAYPOINT_HOLDING_LOOP",
	"WAYPOINT_IMPOSSIBLE",
	"WAYPOINT_LAND",
	"WAYPOINT_LANDED",
	"WAYPOINT_LIFT_OFF",
	"WAYPOINT_LOWER_UNDERCARRIAGE",
	"WAYPOINT_NAVIGATION",
	"WAYPOINT_PREPARE_FOR_DROP_OFF",
	"WAYPOINT_PICK_UP",
	"WAYPOINT_RAISE_UNDERCARRIAGE",
	"WAYPOINT_RECON",
	"WAYPOINT_REPAIR",
	"WAYPOINT_REVERSE_CONVOY",
	"WAYPOINT_START_UP",
	"WAYPOINT_SUB_ROUTE_NAVIGATION",
	"WAYPOINT_TAKEN_OFF",
	"WAYPOINT_TARGET",
	"WAYPOINT_TAXI",
	"WAYPOINT_TOUCH_DOWN",
	"WAYPOINT_TROOP_CAPTURE",
	"WAYPOINT_TROOP_DEFEND",
	"WAYPOINT_TROOP_INSERT",
	"WAYPOINT_TROOP_PICKUP_POINT_END",
	"WAYPOINT_TROOP_PICKUP_POINT_START",
	"WAYPOINT_TROOP_PUTDOWN_POINT",
	"WAYPOINT_WAIT",

	"NUM_ENTITY_SUB_TYPE_WAYPOINTS"
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char *entity_sub_type_weapon_names [] =
{
	"WEAPON_NO_WEAPON",
	"WEAPON_M2_12P7MM_ROUND",
	"WEAPON_M61A1_20MM_ROUND",
	"WEAPON_M61A1_CIWS_20MM_ROUND",
	"WEAPON_M197_20MM_ROUND",
	"WEAPON_GAU12U_25MM_ROUND",
	"WEAPON_M242_25MM_ROUND",
	"WEAPON_GAU8A_30MM_ROUND",
	"WEAPON_M230_30MM_ROUND",
	"WEAPON_M75_76MM_ROUND",
	"WEAPON_M256_120MM_ROUND",
	"WEAPON_M284_155MM_ROUND",
	"WEAPON_M270_227MM_ROCKET",
	"WEAPON_NSV_12P7MM_ROUND",
	"WEAPON_9A642_12P7MM_ROUND",
	"WEAPON_KPV_14P5MM_ROUND",
	"WEAPON_GSH23_23MM_ROUND",
	"WEAPON_GSH301_30MM_ROUND",
	"WEAPON_2A38M_30MM_ROUND",
	"WEAPON_2A42_30MM_ROUND",
	"WEAPON_2A42_30MM_HE_ROUND",
	"WEAPON_2A42_30MM_AP_ROUND",
	"WEAPON_2A72_30MM_ROUND",
	"WEAPON_AO17A_30MM_ROUND",
	"WEAPON_ADMG_630_30MM_ROUND",
	"WEAPON_CIS_NAVAL_76MM_ROUND",
	"WEAPON_CIS_NAVAL_100MM_ROUND",
	"WEAPON_2K23_100MM_ROUND",
	"WEAPON_BM21_122MM_ROCKET",
	"WEAPON_2A46M1_125MM_ROUND",
	"WEAPON_2A65_152MM_ROUND",
	"WEAPON_HYDRA70_M255",
	"WEAPON_HYDRA70_M261",
	"WEAPON_LAU69A",
	"WEAPON_S5",
	"WEAPON_S8",
	"WEAPON_S13",
	"WEAPON_AIM92_STINGER",
	"WEAPON_AIM9M_SIDEWINDER",
	"WEAPON_AIM120_AMRAAM",
	"WEAPON_IGLA_V",
	"WEAPON_AA8A_APHID",
	"WEAPON_AA8B_APHID",
	"WEAPON_AA10A_ALAMO",
	"WEAPON_AA10B_ALAMO",
	"WEAPON_AA11_ARCHER",
	"WEAPON_AGM114L_LONGBOW_HELLFIRE",
	"WEAPON_AGM114K_HELLFIRE_II",
	"WEAPON_AGM65D_MAVERICK",
	"WEAPON_AGM65F_MAVERICK",
	"WEAPON_ATAKA",
	"WEAPON_VIKHR",
	"WEAPON_AT6_SPIRAL",
	"WEAPON_AS10_KAREN",
	"WEAPON_AS14_KEDGE",
	"WEAPON_CHAPARRAL",
	"WEAPON_FIM92A_STINGER",
	"WEAPON_SM1MR_STANDARD",
	"WEAPON_SEA_SPARROW",
	"WEAPON_SA7_GRAIL",
	"WEAPON_SA13_GOPHER",
	"WEAPON_SA19_GRISON",
	"WEAPON_SAN3_GOBLET",
	"WEAPON_SAN4_GECKO",
	"WEAPON_M220_TOW2B",
	"WEAPON_AT5_SPANDREL",
	"WEAPON_AT10_STABBER",
	"WEAPON_AT11_SNIPER",
	"WEAPON_CHAFF",
	"WEAPON_FLARE",
	"WEAPON_SMOKE_GRENADE",
	"WEAPON_CRATE",
	"WEAPON_HOKUM_BLADE",
	"WEAPON_HOKUM_PILOT",
	"WEAPON_HOKUM_CO_PILOT",
	"WEAPON_HOKUM_LH_DOOR",
	"WEAPON_HOKUM_RH_DOOR",
	"NUM_ENTITY_SUB_TYPE_WEAPONS"
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef DEBUG
const char* get_sub_type_name(entity* en)
{
	entity_sub_types sub_type;

	if (!en)
		return "NULL";

	sub_type = get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE);
 
	switch (en->type)
	{
	case ENTITY_TYPE_UNKNOWN:
		return "Unknown";
	case ENTITY_TYPE_BRIDGE:
		return entity_sub_type_bridge_names[sub_type];
	case ENTITY_TYPE_CAMERA:
		return "Camera";
	case ENTITY_TYPE_CARGO:
		return entity_sub_type_cargo_names[sub_type];
	case ENTITY_TYPE_CITY:
		return "City";
	case ENTITY_TYPE_CITY_BUILDING:
		return "City building";
	case ENTITY_TYPE_CRATER:
		return "Crater";
	case ENTITY_TYPE_DIVISION:
		return entity_sub_type_division_names[sub_type];
	case ENTITY_TYPE_EXPLOSION:
		return "Explosion";
	case ENTITY_TYPE_FIXED_WING:
	case ENTITY_TYPE_HELICOPTER:
		return entity_sub_type_aircraft_names[sub_type];
	case ENTITY_TYPE_FORCE:
		return "Force";
	case ENTITY_TYPE_GROUP:
		return entity_sub_type_group_names[sub_type];
	case ENTITY_TYPE_GUIDE:
		return entity_sub_type_guide_names[sub_type];
	case ENTITY_TYPE_KEYSITE:
		return entity_sub_type_keysite_names[sub_type];
	case ENTITY_TYPE_LANDING:
		return entity_sub_type_landing_names[sub_type];
	case ENTITY_TYPE_OBJECT:
		return "Object";
	case ENTITY_TYPE_PARTICLE:
		return "Particle";
	case ENTITY_TYPE_PERSON:
		return "Person";
	case ENTITY_TYPE_PILOT:
		return entity_sub_type_pilot_names[sub_type];
	case ENTITY_TYPE_PYLON:
		return "Pylon";
	case ENTITY_TYPE_REGEN:
		return entity_sub_type_regen_names[sub_type];
	case ENTITY_TYPE_ANTI_AIRCRAFT:
	case ENTITY_TYPE_ROUTED_VEHICLE:
		return entity_sub_type_vehicle_names[sub_type];
	case ENTITY_TYPE_SCENIC:
		return "Scenic";
	case ENTITY_TYPE_SECTOR:
		return "Sector";
	case ENTITY_TYPE_SEGMENT:
		return "Segment";
	case ENTITY_TYPE_SESSION:
		return "Session";
	case ENTITY_TYPE_SHIP_VEHICLE:
		return entity_sub_type_vehicle_names[sub_type];
	case ENTITY_TYPE_SITE:
		return entity_sub_type_site_names[sub_type];
	case ENTITY_TYPE_SITE_UPDATABLE:
		return "Updatedable";
	case ENTITY_TYPE_SMOKE_LIST:
		return "Smoke list";
	case ENTITY_TYPE_SOUND_EFFECT:
		return "Sound effect";
	case ENTITY_TYPE_SPRITE:
		return "Sprite";
	case ENTITY_TYPE_TASK:
		return entity_sub_type_task_names[sub_type];
	case ENTITY_TYPE_UPDATE:
		return "Update";
	case ENTITY_TYPE_WAYPOINT:
		return entity_sub_type_waypoint_names[sub_type];
	case ENTITY_TYPE_WEAPON:
		return entity_sub_type_weapon_names[sub_type];
	}

	return "Unknown";
}
#endif // DEBUG
