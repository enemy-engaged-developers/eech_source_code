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

enum FLOAT_TYPES
{
	FLOAT_TYPE_AFTERBURNER_STATE,
	FLOAT_TYPE_AIRBRAKE_STATE,
	FLOAT_TYPE_AIR_RADAR_CONTACT_TIMEOUT,
	FLOAT_TYPE_AIR_SCAN_CEILING,
	FLOAT_TYPE_AIR_SCAN_FLOOR,
	FLOAT_TYPE_AIR_SCAN_RANGE,
	FLOAT_TYPE_ALTITUDE,
	FLOAT_TYPE_AMMO_ECONOMY,
	FLOAT_TYPE_AMMO_SUPPLY_LEVEL,
	FLOAT_TYPE_AMPLIFICATION,
	FLOAT_TYPE_SOUNDPITCH,
	FLOAT_TYPE_ANIMATION_FREQUENCY,
	FLOAT_TYPE_ASSIGN_TIMER,
	FLOAT_TYPE_ASSIST_TIMER,
	FLOAT_TYPE_ATTACK_ALTITUDE,
	FLOAT_TYPE_AVOIDANCE_RADIUS,
	FLOAT_TYPE_AXLE_LENGTH,
	FLOAT_TYPE_CARGO_DOOR_STATE,
	FLOAT_TYPE_CENTRE_OF_GRAVITY_TO_GROUND_DISTANCE,
	FLOAT_TYPE_CHASE_VIEW_MAX_DISTANCE,
	FLOAT_TYPE_CHASE_VIEW_MAX_DISTANCE_TEST,
	FLOAT_TYPE_CHASE_VIEW_MIN_DISTANCE,
	FLOAT_TYPE_CHASE_VIEW_MIN_DISTANCE_TEST,
	FLOAT_TYPE_CRATER_LIFETIME,
	FLOAT_TYPE_CRUISE_ALTITUDE,
	FLOAT_TYPE_CRUISE_VELOCITY,
	FLOAT_TYPE_CURRENT_MESSAGE_TIMER,
	FLOAT_TYPE_DEATH_TIMER,
	FLOAT_TYPE_DECOY_RELEASE_TIMER,
	FLOAT_TYPE_DECOY_TIMER,
	FLOAT_TYPE_DESIRED_VELOCITY,
	FLOAT_TYPE_DISTANCE,
	FLOAT_TYPE_EFFECT_LIFETIME,
	FLOAT_TYPE_EFFICIENCY,
	FLOAT_TYPE_ELAPSED_MISSION_TIME,
	FLOAT_TYPE_ELAPSED_TIME,
	FLOAT_TYPE_END_SCALE,
	FLOAT_TYPE_EXPIRE_TIMER,
	FLOAT_TYPE_EXPLOSION_STATE,
	FLOAT_TYPE_FIXED_OBJECT_IMPORTANCE,
	FLOAT_TYPE_FIXED_STRUCTURE_HEIGHT,
	FLOAT_TYPE_FLAP_STATE,
	FLOAT_TYPE_FLIGHT_TIME,
	FLOAT_TYPE_FOG_OF_WAR,
	FLOAT_TYPE_FOG_OF_WAR_MAXIMUM_VALUE,
	FLOAT_TYPE_FREQUENCY,
	FLOAT_TYPE_FUEL_DEFAULT_WEIGHT,
	FLOAT_TYPE_FUEL_ECONOMY,
	FLOAT_TYPE_FUEL_SUPPLY_LEVEL,
	FLOAT_TYPE_FUSELAGE_ANGLE,
	FLOAT_TYPE_GENERATOR_LIFETIME,
	FLOAT_TYPE_GUIDE_CRITERIA_VALUE,
	FLOAT_TYPE_HEADING,
	FLOAT_TYPE_HIGH_VELOCITY,
	FLOAT_TYPE_INITIAL_SPEED,
	FLOAT_TYPE_INVULNERABLE_TIMER,
	FLOAT_TYPE_KEYSITE_IMPORTANCE,
	FLOAT_TYPE_KEYSITE_MAXIMUM_STRENGTH,
	FLOAT_TYPE_KEYSITE_STRENGTH,
	FLOAT_TYPE_LAND_URGENCY,
	FLOAT_TYPE_LIFETIME,
	FLOAT_TYPE_LIGHTNING_TIMER,
	FLOAT_TYPE_LOADING_DOOR_STATE,
	FLOAT_TYPE_LOADING_DOOR_TIMER,
	FLOAT_TYPE_LOW_VELOCITY,
	FLOAT_TYPE_MAIN_ROTOR_BLADE_CONING_ANGLE,
	FLOAT_TYPE_MAIN_ROTOR_DIRECTION,
	FLOAT_TYPE_MAIN_ROTOR_BLADE_DROOP_ANGLE,
	FLOAT_TYPE_MAIN_ROTOR_PITCH,
	// Xhit: added FLOAT_TYPE_MAIN_ROTOR_RADIUS for downwash effect (030328)
	FLOAT_TYPE_MAIN_ROTOR_RADIUS,
	FLOAT_TYPE_MAIN_ROTOR_ROLL,
	FLOAT_TYPE_MAIN_ROTOR_RPM,
	FLOAT_TYPE_MAIN_ROTOR_SHAFT_ANGLE,
	FLOAT_TYPE_MAIN_ROTOR_SPIN_UP_TIMER,
	FLOAT_TYPE_MAX_3D_OBJECT_VISUAL_RANGE,
	FLOAT_TYPE_MAX_ACCELERATION,
	FLOAT_TYPE_MAX_TURN_RATE,
	FLOAT_TYPE_MAX_ROLL,
	FLOAT_TYPE_MAX_VERTICAL_TURN_ALLOWANCE,
	FLOAT_TYPE_MEDIUM_VELOCITY,
	FLOAT_TYPE_MINIMUM_EFFICIENCY,
	// Xhit: added FLOAT_TYPE_NUMBER_OF_MAIN_ROTORS for downwash effect (030328)
	FLOAT_TYPE_NUMBER_OF_MAIN_ROTORS,
	FLOAT_TYPE_PERSON_ANIMATION_STATE,
	FLOAT_TYPE_PITCH,
	// Jabberwock 050310 MP Cannon bug
	FLOAT_TYPE_PLAYER_WEAPON_HEADING,
	FLOAT_TYPE_PLAYER_WEAPON_PITCH,
	// Jabberwock 050310 ends
	FLOAT_TYPE_POPULATION_X_MIN,
	FLOAT_TYPE_POPULATION_X_MAX,
	FLOAT_TYPE_POPULATION_Z_MIN,
	FLOAT_TYPE_POPULATION_Z_MAX,
	FLOAT_TYPE_POTENTIAL_AIR_THREAT,
	FLOAT_TYPE_POTENTIAL_AIR_TO_AIR_THREAT,
	FLOAT_TYPE_POTENTIAL_AIR_TO_SURFACE_THREAT,
	FLOAT_TYPE_POTENTIAL_SURFACE_THREAT,
	FLOAT_TYPE_POTENTIAL_SURFACE_TO_AIR_THREAT,
	FLOAT_TYPE_POTENTIAL_SURFACE_TO_SURFACE_THREAT,
	FLOAT_TYPE_POWER_OUTPUT,
	FLOAT_TYPE_PROPELLOR_DIRECTION,
	FLOAT_TYPE_PROPELLOR_RPM,
	FLOAT_TYPE_PROTOTYPE_1,
	FLOAT_TYPE_PROTOTYPE_2,
	FLOAT_TYPE_PROTOTYPE_3,
	FLOAT_TYPE_PROTOTYPE_4,
	FLOAT_TYPE_RADAR_ALTITUDE,
	FLOAT_TYPE_RADAR_ROTATION_STATE,
	FLOAT_TYPE_RADAR_STEALTH_FACTOR,
	FLOAT_TYPE_RANGE,
	FLOAT_TYPE_RATING,
	FLOAT_TYPE_REARMING_TIME,
	FLOAT_TYPE_RECON_DISTANCE,
	FLOAT_TYPE_RECON_RADIUS,
	FLOAT_TYPE_REPAIR_TIMER,
	FLOAT_TYPE_ROLL,
	FLOAT_TYPE_RUDDER_STATE,
	FLOAT_TYPE_SCALE,
	FLOAT_TYPE_SECTOR_SIDE_MAX_VALUE,
	FLOAT_TYPE_SLEEP,
	FLOAT_TYPE_SMOKE_LIFETIME,
	FLOAT_TYPE_SMOKE_SLEEP,
	FLOAT_TYPE_SPEECH_CATEGORY_SILENCE_TIMER,
	FLOAT_TYPE_SPEECH_EXPIRE_TIME,
	FLOAT_TYPE_SPEECH_PRIORITY,
	FLOAT_TYPE_SPRITE_LIFETIME,
	FLOAT_TYPE_START_SCALE,
	FLOAT_TYPE_START_TIME,
	FLOAT_TYPE_STOP_TIMER,
	FLOAT_TYPE_SURFACE_SCAN_RANGE,
	FLOAT_TYPE_TAIL_ROTOR_DIRECTION,
	FLOAT_TYPE_TAIL_ROTOR_RPM,
	FLOAT_TYPE_TALLEST_STRUCTURE_HEIGHT,
	FLOAT_TYPE_TARGET_FIRE_TIMER,
	FLOAT_TYPE_TARGET_PRIORITY_AIR_ATTACK,
	FLOAT_TYPE_TARGET_PRIORITY_GROUND_ATTACK,
	FLOAT_TYPE_TARGET_SCAN_DELAY,
	FLOAT_TYPE_TARGET_SCAN_TIMER,
	FLOAT_TYPE_TASK_COST,
	FLOAT_TYPE_TASK_DEFAULT_PRIORITY,
	FLOAT_TYPE_TASK_PRIORITY,
	FLOAT_TYPE_TASK_SUCCESS_RATE,
	FLOAT_TYPE_TASK_USER_DATA,
	FLOAT_TYPE_TERRAIN_ELEVATION,
	FLOAT_TYPE_TIME_OF_DAY,
	FLOAT_TYPE_TIME_OF_DAY_ACCELERATION,
	FLOAT_TYPE_UNDERCARRIAGE_STATE,
	FLOAT_TYPE_URGENCY,
	FLOAT_TYPE_VALID_EFFECT_LIFETIME,
	FLOAT_TYPE_VELOCITY,
	FLOAT_TYPE_VERY_HIGH_VELOCITY,
	FLOAT_TYPE_VIEW_INTEREST_LEVEL,
	FLOAT_TYPE_WEAPON_BURST_TIMER,
	FLOAT_TYPE_WEAPON_LIFETIME,
	FLOAT_TYPE_WEAPON_SYSTEM_HEADING,
	FLOAT_TYPE_WEAPON_SYSTEM_PITCH,
	FLOAT_TYPE_WEAPON_SYSTEM_READY_STATE,
	FLOAT_TYPE_WEATHER_MODE_TRANSITIONAL_PERIOD,
	FLOAT_TYPE_WEATHER_MODE_TRANSITIONAL_STATUS,
	FLOAT_TYPE_WEATHER_RADIUS,
	FLOAT_TYPE_WEIGHT,
	FLOAT_TYPE_WIDTH_ADJUSTMENT,
	FLOAT_TYPE_WIND_EFFECT_RADIUS,
	FLOAT_TYPE_WIND_GUSTING_VALUE,
	FLOAT_TYPE_WIND_MAXIMUM_SPEED,
	FLOAT_TYPE_WIND_MINIMUM_SPEED,
	FLOAT_TYPE_ZERO_VOLUME_RANGE,
	NUM_FLOAT_TYPES
};

typedef enum FLOAT_TYPES float_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define NUM_FLOAT_TYPE_PACK_BITS (8)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum FLOAT_PACK_TYPES
{
	FLOAT_PACK_TYPE_UNPACKED,
	FLOAT_PACK_TYPE_SIGNED_ANGLE,
	FLOAT_PACK_TYPE_UNSIGNED_ANGLE,
	FLOAT_PACK_TYPE_SIGNED_VALUE,
	FLOAT_PACK_TYPE_UNSIGNED_VALUE,
	NUM_FLOAT_PACK_TYPES
};

typedef enum FLOAT_PACK_TYPES float_pack_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define AIR_RADAR_CONTACT_TIMEOUT_INVALID	((float) 1000000.0)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define NO_RADAR_STEALTH_FACTOR	((float) 1.0)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct FLOAT_TYPE_DATA
{
	char
		*name;

	float_pack_types
		pack_type;

	int
		pack_num_whole_bits,
		pack_num_fractional_bits,
		debug_pack,
		fast_track;
};

typedef struct FLOAT_TYPE_DATA float_type_data;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern float_type_data
	float_type_database[NUM_FLOAT_TYPES];

#define get_float_type_name(FLOAT_TYPE) (float_type_database[(FLOAT_TYPE)].name)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern const char
	*overload_invalid_float_type_message,
	*debug_fatal_invalid_float_type_message;

#ifdef DEBUG

#define validate_float_type(FLOAT_TYPE) ((((FLOAT_TYPE) >= 0) && ((FLOAT_TYPE) < NUM_FLOAT_TYPES)) ? ((FLOAT_TYPE)) : (process_assert (overload_invalid_float_type_message, __FILE__, __LINE__), 0))

#else

#define validate_float_type(FLOAT_TYPE) ((FLOAT_TYPE))

#endif

#define debug_fatal_invalid_float_type(EN,FLOAT_TYPE) (debug_fatal (debug_fatal_invalid_float_type_message, get_local_entity_type_name ((EN)), get_local_entity_index ((EN)), get_float_type_name ((FLOAT_TYPE)), __FILE__, __LINE__))

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void (*fn_set_local_entity_raw_float_value[NUM_ENTITY_TYPES][NUM_FLOAT_TYPES]) (entity *en, float_types type, float value);

#define set_local_entity_raw_float_value(EN,FLOAT_TYPE,VALUE) (fn_set_local_entity_raw_float_value[get_local_entity_type ((EN))][validate_float_type ((FLOAT_TYPE))] ((EN), (FLOAT_TYPE), (VALUE)))

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void (*fn_set_local_entity_float_value[NUM_ENTITY_TYPES][NUM_FLOAT_TYPES]) (entity *en, float_types type, float value);

#define set_local_entity_float_value(EN,FLOAT_TYPE,VALUE) (fn_set_local_entity_float_value[get_local_entity_type ((EN))][validate_float_type ((FLOAT_TYPE))] ((EN), (FLOAT_TYPE), (VALUE)))

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void (*fn_set_client_server_entity_float_value[NUM_ENTITY_TYPES][NUM_FLOAT_TYPES][NUM_COMMS_MODEL_TYPES]) (entity *en, float_types type, float value);

#define set_client_server_entity_float_value(EN,FLOAT_TYPE,VALUE) (fn_set_client_server_entity_float_value[get_local_entity_type ((EN))][validate_float_type ((FLOAT_TYPE))][get_comms_model ()] ((EN), (FLOAT_TYPE), (VALUE)))

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern float (*fn_get_local_entity_float_value[NUM_ENTITY_TYPES][NUM_FLOAT_TYPES]) (entity *en, float_types type);

#define get_local_entity_float_value(EN,FLOAT_TYPE) (fn_get_local_entity_float_value[get_local_entity_type ((EN))][validate_float_type ((FLOAT_TYPE))] ((EN), (FLOAT_TYPE)))

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void initialise_entity_float_value_default_functions (void);

extern void pack_float_value (entity *en, float_types type, float value);

extern float unpack_float_value (entity *en, float_types type);

extern void pack_float_type (float_types type);

extern float_types unpack_float_type (void);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MAX_FRACTIONAL_BITS	(11)

#define pack_float_0_fractional_bits(VALUE,PACKED_VALUE) (convert_float_to_int ((VALUE), (PACKED_VALUE)))
#define pack_float_1_fractional_bits(VALUE,PACKED_VALUE) (convert_float_to_int ((VALUE) * (float) 2.0, (PACKED_VALUE)))
#define pack_float_2_fractional_bits(VALUE,PACKED_VALUE) (convert_float_to_int ((VALUE) * (float) 4.0, (PACKED_VALUE)))
#define pack_float_3_fractional_bits(VALUE,PACKED_VALUE) (convert_float_to_int ((VALUE) * (float) 8.0, (PACKED_VALUE)))
#define pack_float_4_fractional_bits(VALUE,PACKED_VALUE) (convert_float_to_int ((VALUE) * (float) 16.0, (PACKED_VALUE)))
#define pack_float_5_fractional_bits(VALUE,PACKED_VALUE) (convert_float_to_int ((VALUE) * (float) 32.0, (PACKED_VALUE)))
#define pack_float_6_fractional_bits(VALUE,PACKED_VALUE) (convert_float_to_int ((VALUE) * (float) 64.0, (PACKED_VALUE)))
#define pack_float_7_fractional_bits(VALUE,PACKED_VALUE) (convert_float_to_int ((VALUE) * (float) 128.0, (PACKED_VALUE)))
#define pack_float_8_fractional_bits(VALUE,PACKED_VALUE) (convert_float_to_int ((VALUE) * (float) 256.0, (PACKED_VALUE)))
#define pack_float_9_fractional_bits(VALUE,PACKED_VALUE) (convert_float_to_int ((VALUE) * (float) 512.0, (PACKED_VALUE)))
#define pack_float_10_fractional_bits(VALUE,PACKED_VALUE) (convert_float_to_int ((VALUE) * (float) 1024.0, (PACKED_VALUE)))
#define pack_float_11_fractional_bits(VALUE,PACKED_VALUE) (convert_float_to_int ((VALUE) * (float) 2048.0, (PACKED_VALUE)))

#define unpack_float_0_fractional_bits(PACKED_VALUE) ((float) (PACKED_VALUE))
#define unpack_float_1_fractional_bits(PACKED_VALUE) ((float) (PACKED_VALUE) * (float) (1.0 / 2.0))
#define unpack_float_2_fractional_bits(PACKED_VALUE) ((float) (PACKED_VALUE) * (float) (1.0 / 4.0))
#define unpack_float_3_fractional_bits(PACKED_VALUE) ((float) (PACKED_VALUE) * (float) (1.0 / 8.0))
#define unpack_float_4_fractional_bits(PACKED_VALUE) ((float) (PACKED_VALUE) * (float) (1.0 / 16.0))
#define unpack_float_5_fractional_bits(PACKED_VALUE) ((float) (PACKED_VALUE) * (float) (1.0 / 32.0))
#define unpack_float_6_fractional_bits(PACKED_VALUE) ((float) (PACKED_VALUE) * (float) (1.0 / 64.0))
#define unpack_float_7_fractional_bits(PACKED_VALUE) ((float) (PACKED_VALUE) * (float) (1.0 / 128.0))
#define unpack_float_8_fractional_bits(PACKED_VALUE) ((float) (PACKED_VALUE) * (float) (1.0 / 256.0))
#define unpack_float_9_fractional_bits(PACKED_VALUE) ((float) (PACKED_VALUE) * (float) (1.0 / 512.0))
#define unpack_float_10_fractional_bits(PACKED_VALUE) ((float) (PACKED_VALUE) * (float) (1.0 / 1024.0))
#define unpack_float_11_fractional_bits(PACKED_VALUE) ((float) (PACKED_VALUE) * (float) (1.0 / 2048.0))

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
