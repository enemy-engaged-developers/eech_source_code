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

typedef enum
{

	SPEECH_ARRAY_NUMBERS,
	SPEECH_ARRAY_HEADINGS,
	SPEECH_ARRAY_DISTANCES,
	SPEECH_ARRAY_CALLSIGNS,
	SPEECH_ARRAY_ATC_MESSAGES,
	SPEECH_ARRAY_GC_MESSAGES,
	SPEECH_ARRAY_FAC_MESSAGES,
	SPEECH_ARRAY_WINGMAN_MESSAGES,
	SPEECH_ARRAY_SYSTEM_MESSAGES,
	SPEECH_ARRAY_CPG_MESSAGES,

	NUM_SPEECH_ARRAY_TYPES

} speech_array_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef enum
{

	SPEECH_ORIGINATOR_SYSTEM,
	SPEECH_ORIGINATOR_CO_PILOT,
	SPEECH_ORIGINATOR_WINGMAN1,
	SPEECH_ORIGINATOR_WINGMAN2,
	SPEECH_ORIGINATOR_AIR_TRAFFIC_CONTROLLER,
	SPEECH_ORIGINATOR_FORWARD_AIR_CONTROLLER,
	SPEECH_ORIGINATOR_GROUND_CONTROLLER,

	NUM_SPEECH_ORIGINATOR_TYPES,

} speech_originator_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef enum
{
	SPEECH_CATEGORY_MISC,
	SPEECH_CATEGORY_AMMO_LOW,
	SPEECH_CATEGORY_ATTACKING_TARGETS,
	SPEECH_CATEGORY_COMMENT,
	SPEECH_CATEGORY_CPG_SYSTEMS,
	SPEECH_CATEGORY_DECOY_REQUEST,
	SPEECH_CATEGORY_DESTROYED_TARGETS,
	SPEECH_CATEGORY_FIRING,
	SPEECH_CATEGORY_LANDING_TAKING_OFF,
	SPEECH_CATEGORY_IN_POSITION,
	SPEECH_CATEGORY_MISSION_RELATED,
	SPEECH_CATEGORY_MOVING,
	SPEECH_CATEGORY_RADIO_RESPONSE,
	SPEECH_CATEGORY_RETURNING_TO_BASE,
	SPEECH_CATEGORY_SIGHTED_TARGETS,
	SPEECH_CATEGORY_TARGET_LOCK,
	SPEECH_CATEGORY_TARGETED,
	SPEECH_CATEGORY_UNDER_ATTACK,
	SPEECH_CATEGORY_WARNING_SYSTEM,
	SPEECH_CATEGORY_WAYPOINT,
	SPEECH_CATEGORY_WEAPONS_SYSTEMS,

	NUM_SPEECH_CATEGORY_TYPES

} speech_category_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef enum
{

	SPEECH_NUMBER_ZERO,
	SPEECH_NUMBER_ONE,
	SPEECH_NUMBER_TWO,
	SPEECH_NUMBER_THREE,
	SPEECH_NUMBER_FOUR,
	SPEECH_NUMBER_FIVE,
	SPEECH_NUMBER_SIX,
	SPEECH_NUMBER_SEVEN,
	SPEECH_NUMBER_EIGHT,
	SPEECH_NUMBER_NINE,
	SPEECH_NUMBER_ONE_HUNDRED,

	NUM_SPEECH_NUMBERS

} speech_number_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef enum
{

	SPEECH_HEADING_ONE_O_CLOCK,
	SPEECH_HEADING_TWO_O_CLOCK,
	SPEECH_HEADING_THREE_O_CLOCK,
	SPEECH_HEADING_FOUR_O_CLOCK,
	SPEECH_HEADING_FIVE_O_CLOCK,
	SPEECH_HEADING_SIX_O_CLOCK,
	SPEECH_HEADING_SEVEN_O_CLOCK,
	SPEECH_HEADING_EIGHT_O_CLOCK,
	SPEECH_HEADING_NINE_O_CLOCK,
	SPEECH_HEADING_TEN_O_CLOCK,
	SPEECH_HEADING_ELEVEN_O_CLOCK,
	SPEECH_HEADING_TWELVE_O_CLOCK,

	NUM_SPEECH_HEADINGS

} speech_heading_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef enum
{

	SPEECH_DISTANCE_HALF_KILOMETRE,
	SPEECH_DISTANCE_ONE_KILOMETRE,
	SPEECH_DISTANCE_TWO_KILOMETRE,
	SPEECH_DISTANCE_THREE_KILOMETRE,
	SPEECH_DISTANCE_FOUR_KILOMETRE,
	SPEECH_DISTANCE_FIVE_KILOMETRE,
	SPEECH_DISTANCE_SIX_KILOMETRE,
	SPEECH_DISTANCE_SEVEN_KILOMETRE,
	SPEECH_DISTANCE_EIGHT_KILOMETRE,
	SPEECH_DISTANCE_NINE_KILOMETRE,
	SPEECH_DISTANCE_TEN_KILOMETRE,
	SPEECH_DISTANCE_ELEVEN_KILOMETRE,
	SPEECH_DISTANCE_TWELVE_KILOMETRE,

	NUM_SPEECH_DISTANCES

} speech_distance_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef enum
{

	SPEECH_UNITS_RANGE,
	SPEECH_UNITS_BEARING,
	SPEECH_UNITS_SPEED,
	SPEECH_UNITS_KNOT,
	SPEECH_UNITS_KNOTS,

	NUM_SPEECH_UNITS

} speech_units_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef enum
{

	SPEECH_SYSTEM_RADAR_FAILURE,
	SPEECH_SYSTEM_FLIR_FAILURE,
	SPEECH_SYSTEM_DTV_FAILURE,
	SPEECH_SYSTEM_LLLTV_FAILURE,
	SPEECH_SYSTEM_DVO_FAILURE,
	SPEECH_SYSTEM_PERISCOPE_DAMAGED,
	SPEECH_SYSTEM_LASER_DESIGNATOR_FAILURE,
	SPEECH_SYSTEM_LASER_RANGE_FINDER_FAILURE,
	SPEECH_SYSTEM_RADAR_JAMMER_FAILURE,
	SPEECH_SYSTEM_IR_JAMMER_FAILURE,
	SPEECH_SYSTEM_NAV_COMPUTER_FAILURE,
	SPEECH_SYSTEM_COMMS_FAILURE,
	SPEECH_SYSTEM_RADAR_WARNING_FAILURE,
	SPEECH_SYSTEM_IHADSS_FAILURE,
	SPEECH_SYSTEM_HIDSS_FAILURE,
	SPEECH_SYSTEM_HUD_FAILURE,
	SPEECH_SYSTEM_HELMET_MOUNTED_SIGHT_FAILURE,
	SPEECH_SYSTEM_MFD_FAILURE,
	SPEECH_SYSTEM_DISPLAY_FAILURE,
	SPEECH_SYSTEM_TV_DISPLAY_FAILURE,
	SPEECH_SYSTEM_THREAT_WARNING_DISPLAY_FAILURE,
	SPEECH_SYSTEM_PNVS_FAILURE,
	SPEECH_SYSTEM_NIGHT_VISION_GOGGLES_FAILURE,
	SPEECH_SYSTEM_GUN_JAMMED,
	SPEECH_SYSTEM_HARDPOINT_DAMAGED,
	SPEECH_SYSTEM_CHAFF_DISPENSER_DAMAGED,
	SPEECH_SYSTEM_FLARE_DISPENSER_DAMAGED,
	SPEECH_SYSTEM_MAIN_ROTOR_DAMAGED,
	SPEECH_SYSTEM_TAIL_ROTOR_DAMAGED,
	SPEECH_SYSTEM_LEFT_ENGINE_FAILURE,
	SPEECH_SYSTEM_RIGHT_ENGINE_FAILURE,
	SPEECH_SYSTEM_LEFT_ENGINE_FIRE,
	SPEECH_SYSTEM_RIGHT_ENGINE_FIRE,
	SPEECH_SYSTEM_HYDRAULIC_PRESSURE_FAILURE,
	SPEECH_SYSTEM_STABILISER_DAMAGED,
	SPEECH_SYSTEM_FUEL_LEAK,
	SPEECH_SYSTEM_LOW_ENGINE_OIL_PRESSURE,
	SPEECH_SYSTEM_HIGH_ENGINE_OIL_TEMPERATURE,
	SPEECH_SYSTEM_GEAR_DAMAGED,
	SPEECH_SYSTEM_FUEL_LOW,
	SPEECH_SYSTEM_ENGINE_OVERTORQUE,
	SPEECH_SYSTEM_LOW_ROTOR_RPM,
	SPEECH_SYSTEM_ROTOR_OVERSPEED,

	NUM_SPEECH_SYSTEM_MESSAGES

} speech_system_message_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef enum
{
	SPEECH_CPG_AFFIRMATIVE,
	SPEECH_CPG_NEGATIVE,

	//
	// Systems
	//

	SPEECH_CPG_GEAR_DOWN,
	SPEECH_CPG_GEAR_UP,
	SPEECH_CPG_AUTOPILOT_ON,
	SPEECH_CPG_AUTOPILOT_OFF,
	SPEECH_CPG_AUTOPILOT_TOO_LOW1,
	SPEECH_CPG_AUTOPILOT_TOO_LOW2,
	SPEECH_CPG_HOVER_HOLD_ON,
	SPEECH_CPG_HOVER_HOLD_OFF,
	SPEECH_CPG_HOVER_HOLD_TOO_FAST1,
	SPEECH_CPG_HOVER_HOLD_TOO_FAST2,
	SPEECH_CPG_ALTITUDE_HOLD_ON,
	SPEECH_CPG_ALTITUDE_HOLD_OFF,
	SPEECH_CPG_RADAR_ON,
	SPEECH_CPG_RADAR_OFF,
	SPEECH_CPG_IR_JAMMER_ON,
	SPEECH_CPG_IR_JAMMER_OFF,
	SPEECH_CPG_RADAR_JAMMER_ON,
	SPEECH_CPG_RADAR_JAMMER_OFF,
	SPEECH_CPG_RADAR_DAMAGED,
	SPEECH_CPG_FLIR_DAMAGED,
	SPEECH_CPG_DTV_DAMAGED,
	SPEECH_CPG_LLLTV_DAMAGED,
	SPEECH_CPG_DVO_DAMAGED,
	SPEECH_CPG_PERISCOPE_DAMAGED,
	SPEECH_CPG_RADAR_JAMMER_DAMAGED,
	SPEECH_CPG_IR_JAMMER_DAMAGED,
	SPEECH_CPG_PNVS_DAMAGED,
	SPEECH_CPG_NIGHT_VISION_GOGGLES_DAMAGED,
	SPEECH_CPG_CONTROL_SYSTEMS_DAMAGED,

	//
	// Weapons
	//

	SPEECH_CPG_SWITCHING_TO_CHAINGUN,
	SPEECH_CPG_SWITCHING_TO_CANNON,
	SPEECH_CPG_SWITCHING_TO_CANNON_PODS,
	SPEECH_CPG_SWITCHING_TO_STINGERS,
	SPEECH_CPG_SWITCHING_TO_IGLA,
	SPEECH_CPG_SWITCHING_TO_HELLFIRES,
	SPEECH_CPG_SWITCHING_TO_ATAKA,
	SPEECH_CPG_SWITCHING_TO_VIKHR,
	SPEECH_CPG_SWITCHING_TO_ROCKETS,

	SPEECH_CPG_SELECTING_CHAINGUN,
	SPEECH_CPG_SELECTING_CANNON,
	SPEECH_CPG_SELECTING_CANNON_PODS,
	SPEECH_CPG_SELECTING_STINGERS,
	SPEECH_CPG_SELECTING_IGLA,
	SPEECH_CPG_SELECTING_HELLFIRES,
	SPEECH_CPG_SELECTING_ATAKA,
	SPEECH_CPG_SELECTING_VIKHR,
	SPEECH_CPG_SELECTING_ROCKETS,

	SPEECH_CPG_FIRING_CHAINGUN,
	SPEECH_CPG_FIRING_CANNON,
	SPEECH_CPG_FIRING_ROCKETS,
	SPEECH_CPG_FIRING_STINGER,
	SPEECH_CPG_FIRING_HELLFIRE,
	SPEECH_CPG_FIRING_IGLA,
	SPEECH_CPG_FIRING_ATAKA,
	SPEECH_CPG_FIRING_VIKHR,

	SPEECH_CPG_ENGAGING_WITH_CHAINGUN,
	SPEECH_CPG_ENGAGING_WITH_CANNON,
	SPEECH_CPG_ENGAGING_WITH_ROCKETS,

	SPEECH_CPG_CANNON_LOW,
	SPEECH_CPG_ROCKETS_LOW,
	SPEECH_CPG_HELLFIRES_LOW,
	SPEECH_CPG_STINGERS_LOW,
	SPEECH_CPG_IGLAS_LOW,
	SPEECH_CPG_VIKHRS_LOW,
	SPEECH_CPG_ATAKAS_LOW,
	SPEECH_CPG_CHAFF_LOW,
	SPEECH_CPG_FLARES_LOW,

	SPEECH_CPG_CANNON_OUT,
	SPEECH_CPG_ROCKETS_OUT,
	SPEECH_CPG_HELLFIRES_OUT,
	SPEECH_CPG_STINGERS_OUT,
	SPEECH_CPG_IGLAS_OUT,
	SPEECH_CPG_VIKHRS_OUT,
	SPEECH_CPG_ATAKAS_OUT,
	SPEECH_CPG_CHAFF_OUT,
	SPEECH_CPG_FLARES_OUT,

	SPEECH_CPG_NO_TARGETING_SYSTEM,
	SPEECH_CPG_NO_TARGET,
	SPEECH_CPG_NO_WEAPON,

	//
	//
	//

	SPEECH_CPG_INVALID_TARGET,
	SPEECH_CPG_TARGET_OUTSIDE_SEEKER_LIMIT,
	SPEECH_CPG_NO_LOS,
	SPEECH_CPG_TARGET_OUT_OF_RANGE,
	SPEECH_CPG_GOOD_TONE,
	SPEECH_CPG_TALLY_SPOT_ENGAGING,
	SPEECH_CPG_TARGET_LASED_WEAPONS_HOT,
	SPEECH_CPG_EXECUTE_SPOT,
	SPEECH_CPG_SPOT_ON,
	SPEECH_CPG_SWITCHING_TO_LOAL,
	SPEECH_CPG_SWITCHING_TO_LOBL,

	SPEECH_CPG_FRIENDLY_FIRE1,
	SPEECH_CPG_FRIENDLY_FIRE2,

	SPEECH_CPG_APPROACHING_ENGAGEMENT_AREA,
	SPEECH_CPG_APPROACHING_BATTLE_POSITION,
	SPEECH_CPG_APPROACHING_RP,
	SPEECH_CPG_OBJECTIVE_IN_RANGE_RECON,
	SPEECH_CPG_TRANSMITTING_RECON,
	SPEECH_CPG_MISSION_COMPLETED1,
	SPEECH_CPG_MISSION_COMPLETED2,
	SPEECH_CPG_ON_FINALS_CHECK_GEAR,
	SPEECH_CPG_PRIMARY_TARGET,
	SPEECH_CPG_MISSION_OBJECTIVE,
	SPEECH_CPG_INCOMING,
	SPEECH_CPG_INCOMING_MISSILE,
	SPEECH_CPG_RECEIVING_SMALL_ARMS_FIRE,
	SPEECH_CPG_TARGET_HIT,
	SPEECH_CPG_TARGET_MISSED,
	SPEECH_CPG_TARGET_DESTROYED,
	SPEECH_CPG_TARGET_IS_DOWN,
	SPEECH_CPG_KILL_CONFIRMED,
	SPEECH_CPG_GOOD_KILL,
	SPEECH_CPG_ENEMY,
	SPEECH_CPG_FRIENDLY,
	SPEECH_CPG_CHOPPERS,
	SPEECH_CPG_FAST_MOVERS,
	SPEECH_CPG_CARGO_BIRD,
	SPEECH_CPG_HEAVY_METAL,
	SPEECH_CPG_TANKS,
	SPEECH_CPG_ARMOUR,
	SPEECH_CPG_ARTILLERY,
	SPEECH_CPG_TRUCKS,
	SPEECH_CPG_SAM,
	SPEECH_CPG_TRIPLE_A,
	SPEECH_CPG_WARSHIPS,
	SPEECH_CPG_INFANTRY,

	NUM_SPEECH_CPG_MESSAGES

} speech_cpg_message_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef enum
{
	SPEECH_WINGMAN_INTRODUCTION,
	SPEECH_WINGMAN_NEGATIVE,
	SPEECH_WINGMAN_AFFIRMATIVE,
	SPEECH_WINGMAN_AT_GRID,
	SPEECH_WINGMAN_TALLY_SPOT,
	SPEECH_WINGMAN_TARGET_LASED,
	SPEECH_WINGMAN_EXECUTE_SPOT,
	SPEECH_WINGMAN_SPOT_ON,

	SPEECH_WINGMAN_APPROACHING_ENGAGEMENT_AREA,
	SPEECH_WINGMAN_APPROACHING_BATTLE_POSITION,
	SPEECH_WINGMAN_APPROACHING_RP,

	SPEECH_WINGMAN_MISSION_COMPLETE1,
	SPEECH_WINGMAN_MISSION_COMPLETE2,

	//
	// Engaging targets
	//

	SPEECH_WINGMAN_INCOMING,
	SPEECH_WINGMAN_INCOMING_MISSILE,
	SPEECH_WINGMAN_TAKING_HITS,
	SPEECH_WINGMAN_GOING_DOWN,

	SPEECH_WINGMAN_TARGET_HIT,
	SPEECH_WINGMAN_TARGET_MISSED,
	SPEECH_WINGMAN_TARGET_DESTROYED,

	//
	// Radio command responses
	//

	SPEECH_WINGMAN_BOBBING_UP,
	SPEECH_WINGMAN_ENGAGING_TARGET,
	SPEECH_WINGMAN_ROGER_MAINTAINING_POSITION,
	SPEECH_WINGMAN_ROGER_REJOINING_FORMATION,
	SPEECH_WINGMAN_ROGER_BOBBING_UP,
	SPEECH_WINGMAN_ROGER_RETURNING_TO_BASE,
	SPEECH_WINGMAN_ROGER_WEAPONS_HOLD,
	SPEECH_WINGMAN_ROGER_WEAPONS_FREE,
	SPEECH_WINGMAN_ROGER_ENGAGING_TARGET,
	SPEECH_WINGMAN_ROGER_COMING_TO_ASSIST,
	SPEECH_WINGMAN_ROGER_MOVING_INTO_ORDERED_POSITION,

	SPEECH_WINGMAN_WE_HAVE,
	SPEECH_WINGMAN_AIR_TO_GROUND_MISSILES,
	SPEECH_WINGMAN_AIR_TO_AIR_MISSILES,
	SPEECH_WINGMAN_PERCENT,
	SPEECH_WINGMAN_ROCKETS,
	SPEECH_WINGMAN_CANNON_AMMO,
	SPEECH_WINGMAN_FULLY_MISSION_CAPABLE,
	SPEECH_WINGMAN_MINOR_DAMAGE,
	SPEECH_WINGMAN_SOME_DAMAGE,
	SPEECH_WINGMAN_MAJOR_DAMAGE,

	//
	// Weapons
	//

	SPEECH_WINGMAN_LAUNCHING_MISSILE,
	SPEECH_WINGMAN_MISSILE_AWAY,
	SPEECH_WINGMAN_FIRING_ROCKETS,
	SPEECH_WINGMAN_ROCKETS_AWAY,
	SPEECH_WINGMAN_FIRING_CANNON,
	SPEECH_WINGMAN_ENGAGING_WITH_CANNON,

	SPEECH_WINGMAN_ACKNOWLEDGE,
	SPEECH_WINGMAN_UNABLE_TO_COMPLY,
	SPEECH_WINGMAN_REQUEST_PERMISSION_TO_LAND,
	SPEECH_WINGMAN_REQUEST_PERMISSION_TO_TAKEOFF,
	SPEECH_WINGMAN_TRANSMITTING_RECON_DATA,

	SPEECH_WINGMAN_SEEKING_COVER,
	SPEECH_WINGMAN_FLYING_TO_COVER,
	SPEECH_WINGMAN_IN_POSITION,

	SPEECH_WINGMAN_UNDER_ATTACK_AIRCRAFT,
	SPEECH_WINGMAN_UNDER_ATTACK_ARMOUR,
	SPEECH_WINGMAN_REQUEST_ASSISTANCE,

	NUM_SPEECH_WINGMAN_MESSAGES

} speech_wingman_message_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef enum
{
	SPEECH_FAC_INTRODUCTION,

	SPEECH_FAC_ENEMY_AIRCRAFT_DETECTED,
	SPEECH_FAC_REQUEST_ACCEPTED,
	SPEECH_FAC_REQUEST_DENIED,
	SPEECH_FAC_RETURN_TO_BASE,
	SPEECH_FAC_BASE_UNDER_ATTACK,

	NUM_SPEECH_FAC_MESSAGES

} speech_fac_message_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef enum
{
	SPEECH_GC_INTRODUCTION,

	SPEECH_GC_REQUEST_SUPPORT_AT,
	SPEECH_GC_PINNED_DOWN_AT,
	SPEECH_GC_NEED_AIR_SUPPORT_AT,
	SPEECH_GC_UNDER_HEAVY_FIRE,

	SPEECH_GC_INCOMING_ENEMY_AIRCRAFT_HEADING,
	SPEECH_GC_INCOMING_ENEMY_GROUND_UNITS_AT,

	SPEECH_GC_ADVANCING_TO,
	SPEECH_GC_RETREATING_TO,

	//
	// response to request artillery
	//

	SPEECH_GC_FIRE_MISSION_RECEIVED,
	SPEECH_GC_ARTILLERY_SHIFTING_POSITION,
	SPEECH_GC_ARTILLERY_BUSY,

	NUM_SPEECH_GC_MESSAGES

} speech_gc_message_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef enum
{
	SPEECH_ATC_INTRODUCTION,
	SPEECH_ATC_CLEAR_FOR_TAKEOFF1,
	SPEECH_ATC_PROCEED_TO_HOLDING_ROUTE,
	SPEECH_ATC_CLEAR_FOR_LANDING,
	SPEECH_ATC_WINDS,
	SPEECH_ATC_AT,
	SPEECH_ATC_AT_5_KNOTS,
	SPEECH_ATC_AT_10_KNOTS,
	SPEECH_ATC_AT_15_KNOTS,
	SPEECH_ATC_AT_20_KNOTS,
	SPEECH_ATC_AT_25_KNOTS,
	SPEECH_ATC_AT_30_KNOTS,

	NUM_SPEECH_ATC_MESSAGES

} speech_atc_message_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef enum
{
	SPEECH_INTRODUCTION_NEVER,
	SPEECH_INTRODUCTION_SOMETIMES,
	SPEECH_INTRODUCTION_ALWAYS,

	NUM_SPEECH_INTRO_TYPES

} speech_intro_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct SPEECH_INDEX_LIST_TYPE
{
	int
		num_items;

	sound_sample_indices
		*sample_indices;
};

typedef struct SPEECH_INDEX_LIST_TYPE speech_index_list_type;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct SPEECH_DATA_SAMPLE_INITIALISATION_TYPE
{
	int
		speech_index;

	sound_sample_indices
		blue_force_sample_index,
		red_force_sample_index;
};

typedef struct SPEECH_DATA_SAMPLE_INITIALISATION_TYPE speech_data_sample_initialisation_type;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct SPEECH_DATA_ORIGINATOR_INITIALISATION_TYPE
{
	speech_originator_types
		originator;

	speech_data_sample_initialisation_type
		*sample_data;
};

typedef struct SPEECH_DATA_ORIGINATOR_INITIALISATION_TYPE speech_data_originator_initialisation_type;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct SPEECH_DATA_INITIALISATION_TYPE
{
	speech_array_types
		array_type;

	int
		max_items;

	speech_data_originator_initialisation_type
		*originator_data;
};

typedef struct SPEECH_DATA_INITIALISATION_TYPE speech_data_initialisation_type;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct SPEECH_INSTANCE_TYPE
{
	int
		speech_index;

	speech_array_types
		array_type;

	int
		frequency;

	speech_intro_types
		introduction;
};

typedef struct SPEECH_INSTANCE_TYPE speech_instance_type;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern int
	speech_sector_coordinates [6];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern int play_client_server_speech
(
	entity *parent,
	entity *sender,
	entity_sides side,
	entity_sub_types sub_type,
	sound_locality_types locality,
	float delay,
	float priority,
	float expire_time,
	speech_originator_types originator,
	speech_category_types category,
	float category_silence_timer,
	...
);

extern void update_speech_buffers (void);

extern void remove_speech_category_from_buffers (entity_sides side, speech_originator_types originator, speech_category_types category);

extern void initialise_speech_buffers (void);

extern void deinitialise_speech_buffers (void);

extern void notify_speech_buffers_entity_killed (entity *en);

extern void initialise_speech_index_table (void);

extern void deinitialise_speech_index_table (void);

extern void initialise_sample_index_array (speech_array_types array_type, speech_originator_types originator, int max_items);

extern void initialise_speech_data (speech_array_types array_type, speech_originator_types originator, int speech_index, sound_sample_indices blue_force_sample_index, sound_sample_indices red_force_sample_index);

extern int get_speech_random_value (speech_instance_type *speech_list, int num_choices, int last_played);

extern int play_client_server_radio_message
(
	entity *en,
	entity_sides side,
	float priority,
	float expire_time,
	speech_originator_types originator,
	speech_category_types category,
	float category_silence_timer,
	speech_intro_types play_intro,
	speech_array_types main_array_type,
	int main_speech_index
);

extern int play_client_server_cpg_message (entity *en, float priority, float expire_time, int speech_category, float category_silence_timer, int speech_index);

extern int play_client_server_cpg_contact_message (entity *en, int target_speech_index, int heading_speech_index, int range_speech_index);

extern int play_client_server_warning_message (entity *en, int speech_index);

extern speech_originator_types get_wingman_speech_originator (entity *en);

extern int play_client_server_wingman_message
(
	entity *en,
	float priority,
	float expire_time,
	speech_category_types category,
	float category_silence_timer,
	speech_intro_types play_intro,
	speech_array_types main_array_type,
	int main_speech_index
);

extern int *get_speech_sector_coordinates (vec3d *pos);

extern speech_heading_types get_speech_heading_type (entity *source, entity *target);

extern speech_distance_types get_speech_distance_type (entity *source, entity *target);

extern speech_atc_message_types get_speech_atc_wind_speed (entity *en);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void initialise_speech_number_data (void);
extern void initialise_speech_headings_data (void);
extern void initialise_speech_distances_data (void);
extern void initialise_speech_callsign_data (void);
extern void initialise_speech_atc_data (void);
extern void initialise_speech_gc_data (void);
extern void initialise_speech_fac_data (void);
extern void initialise_speech_wingman_data (void);
extern void initialise_speech_system_data (void);
extern void initialise_speech_cpg_data (void);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



