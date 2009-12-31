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

enum INT_TYPES
{
	INT_TYPE_ADDITIVE,
	INT_TYPE_AIR_ATTACK_STRENGTH,
	INT_TYPE_AIR_TO_AIR_WEAPON_CONFIG_TYPE,
	INT_TYPE_AIR_TO_SURFACE_WEAPON_CONFIG_TYPE,
	INT_TYPE_AIRBORNE_AIRCRAFT,
	INT_TYPE_AIRCRAFT_GROUP,
	INT_TYPE_ALIGN_WITH_TERRAIN,
	INT_TYPE_ALIVE,
	INT_TYPE_ANIMATED_TEXTURE,
	INT_TYPE_APPROXIMATION_OBJECT_3D_SHAPE,
	INT_TYPE_ASSESS_LANDING,
	INT_TYPE_AUTO_ASSIGN_GUNSHIP,
	INT_TYPE_AUTO_PILOT,
	INT_TYPE_AWARDED_MEDALS,
	INT_TYPE_AWARDED_PROMOTION,
	INT_TYPE_BRIDGE_SEGMENT_TYPE,
	INT_TYPE_CAMERA_MODE,
	INT_TYPE_CAMPAIGN_CRITERIA_COUNT,
	INT_TYPE_CAMPAIGN_CRITERIA_RESULT,
	INT_TYPE_CAMPAIGN_CRITERIA_TYPE,
	INT_TYPE_CAMPAIGN_CRITERIA_VALUE,
	INT_TYPE_CAMPAIGN_MEDAL,
	INT_TYPE_CAMPAIGN_REQUIRES_APACHE_HAVOC,
	INT_TYPE_CHEATS_ENABLED,
	INT_TYPE_CHECK_WAYPOINT_ACTION,
	INT_TYPE_CHILD_COUNT,
	INT_TYPE_COLLISION_TEST_FIXED,
	INT_TYPE_COLLISION_TEST_MOBILE,
	INT_TYPE_COLOUR,
	INT_TYPE_COLOUR_ALPHA,
	INT_TYPE_COLOUR_BLUE,
	INT_TYPE_COLOUR_GREEN,
	INT_TYPE_COLOUR_RED,
	INT_TYPE_COUNT,
	INT_TYPE_CPG_IDENTIFIED,
	INT_TYPE_CREW_ROLE,
	INT_TYPE_CRITICAL_TASK,
	INT_TYPE_DAMAGE_LEVEL,
	INT_TYPE_DAY,
	INT_TYPE_DAY_SEGMENT_TYPE,
	INT_TYPE_DELAY_TASK_ASSIGNMENT,
	INT_TYPE_DEFAULT_3D_SHAPE,
	INT_TYPE_DEFAULT_ENGAGE_ENEMY,
	INT_TYPE_DEFAULT_GROUP_LIST_TYPE,
	INT_TYPE_DEFAULT_WEAPON_CONFIG_TYPE,
	INT_TYPE_DEFAULT_WEAPON_TYPE,
	INT_TYPE_DESTROYED_3D_SHAPE,
	INT_TYPE_DIFFICULTY_LEVEL,
	INT_TYPE_DIVISION_ID,
	INT_TYPE_EJECTED,
	INT_TYPE_END_NODE,
	INT_TYPE_ENGAGE_ENEMY,
	INT_TYPE_ENTITY_SUB_TYPE,
	INT_TYPE_EVADE_FIRE,
	INT_TYPE_EXPLOSIVE_POWER,
	INT_TYPE_EXPLOSIVE_QUALITY,
	INT_TYPE_EXPOSURE_LEVEL,
	INT_TYPE_FOLLOW_FORMATION,
	INT_TYPE_FORCE,
	INT_TYPE_FORCE_ATTITUDE,
	INT_TYPE_FORCE_INFO_CATAGORY,
	INT_TYPE_FORCE_SECTOR_COUNT,
	INT_TYPE_FORMATION_POSITION,
	INT_TYPE_FORMATION_POSITIONS,
	INT_TYPE_FREE_LANDING_SITES,
	INT_TYPE_FRONTLINE,
	INT_TYPE_GROUND_RADAR_CLUTTER,
	INT_TYPE_GROUP_AMALGAMATE,
	INT_TYPE_GROUP_CALLSIGN,
	INT_TYPE_GROUP_CATEGORY,
	INT_TYPE_GROUP_DEFAULT_FORMATION,
	INT_TYPE_GROUP_FORMATION,
	INT_TYPE_GROUP_LEADER,
	INT_TYPE_GROUP_LIST_TYPE,
	INT_TYPE_GROUP_MEMBER_ID,
	INT_TYPE_GROUP_MEMBER_NUMBER,
	INT_TYPE_GROUP_MEMBER_STATE,
	INT_TYPE_GROUP_MODE,
	INT_TYPE_GUIDE_CRITERIA_TYPE,
	INT_TYPE_GUIDE_POSITION_TYPE,
	INT_TYPE_GUNSHIP_RADAR_LOS_CLEAR,
	INT_TYPE_GUNSHIP_RADAR_TARGET_INDEX,
	INT_TYPE_GUNSHIP_TYPE,
	INT_TYPE_HAND_OFF_TARGET_COUNT,
	INT_TYPE_HARD_DAMAGE_CAPABILITY,
	INT_TYPE_HELICOPTER_DAMAGE_FLAGS,
	INT_TYPE_HELICOPTER_DAMAGE_LEVEL,
	INT_TYPE_HIDDEN_BY_FOG_OF_WAR,
	INT_TYPE_IDENTIFY_AIRCRAFT,
	INT_TYPE_IDENTIFY_ANTI_AIRCRAFT,
	INT_TYPE_IDENTIFY_CARGO,
	INT_TYPE_IDENTIFY_FIXED,
	INT_TYPE_IDENTIFY_FIXED_WING,
	INT_TYPE_IDENTIFY_HELICOPTER,
	INT_TYPE_IDENTIFY_MOBILE,
	INT_TYPE_IDENTIFY_ROUTED,
	INT_TYPE_IDENTIFY_SHIP_VEHICLE,
	INT_TYPE_IDENTIFY_VEHICLE,
	INT_TYPE_IDENTIFY_WAYPOINT,
	INT_TYPE_IDENTIFY_WEAPON,
	INT_TYPE_ID_NUMBER,
	INT_TYPE_ID_NUMBER_SIGNIFICANT_DIGITS,
	INT_TYPE_INFINITE_FUEL,
	INT_TYPE_INFINITE_GENERATOR,
	INT_TYPE_INFINITE_WEAPONS,
	INT_TYPE_INFRA_RED_JAMMER_ON,
	INT_TYPE_INITIAL_DAMAGE_LEVEL,
	INT_TYPE_INSIDE_HANGAR,
	INT_TYPE_INVULNERABLE_FROM_COLLISIONS,
	INT_TYPE_INVULNERABLE_FROM_WEAPONS,
	INT_TYPE_IN_USE,
	INT_TYPE_KEYSITE_COUNT,
	INT_TYPE_KEYSITE_ID,
	INT_TYPE_KEYSITE_USABLE_STATE,
	INT_TYPE_KILL_NEXT_UPDATE,
	INT_TYPE_KILLS,
	INT_TYPE_LANDED,
	INT_TYPE_LANDED_LOCK,
	INT_TYPE_LANDED_ON_CARRIER,
	INT_TYPE_LANDING_LOCK,
	INT_TYPE_LANDING_TYPES,
	INT_TYPE_LASER_ON,
	INT_TYPE_LENGTH,
	INT_TYPE_LIGHTS_ON,
	INT_TYPE_LOCAL_EFFECT_COUNT,
	INT_TYPE_LOCAL_ONLY_GROUP,
	INT_TYPE_LOCAL_WEATHER_MODEL,
	INT_TYPE_LOCK_ON_AFTER_LAUNCH,
	INT_TYPE_LOSSES,
	INT_TYPE_LOS_TO_TARGET,
	INT_TYPE_MAIN_ROTOR_DAMAGED,
	INT_TYPE_MAP_ICON,
	INT_TYPE_MAXIMUM_MEMBER_COUNT,
	INT_TYPE_MAXIMUM_VOLUME,
	INT_TYPE_MAX_WEAPON_CONFIG_TYPE,
	INT_TYPE_MEMBER_COUNT,
	INT_TYPE_MESSAGE_TEXT_TYPE,
	INT_TYPE_META_EXPLOSION_TYPE,
	INT_TYPE_META_SMOKE_LIST_TYPE,
	INT_TYPE_MINIMUM_IDLE_COUNT,
	INT_TYPE_MINIMUM_MEMBER_COUNT,
	INT_TYPE_MIN_WEAPON_CONFIG_TYPE,
	INT_TYPE_MOBILE_FOLLOW_WAYPOINT_OFFSET,
	INT_TYPE_MOBILE_MOVING,
	INT_TYPE_MOVED,
	INT_TYPE_MOVEMENT_TYPE,
	INT_TYPE_MULTIPLAYER_GROUP,
	INT_TYPE_OBJECT_3D_SHAPE,
	INT_TYPE_OBJECT_DRAWN_ONCE_THIS_FRAME,
	INT_TYPE_OBJECT_INDEX,
	INT_TYPE_OBJECT_SCALING,
	INT_TYPE_OFFENSIVE_CAPABILITY,
	INT_TYPE_OPERATIONAL_STATE,
	INT_TYPE_PARTICLE_COUNT,
	INT_TYPE_PERFORM_DEBRIEF,
	INT_TYPE_PILOT_RANK,
	INT_TYPE_PLANNER_MOVEABLE,
	INT_TYPE_PLAYER,
	INT_TYPE_PLAYER_CONTROLLABLE,
	INT_TYPE_PLAYER_TASK,
	INT_TYPE_POINTS_VALUE,
	INT_TYPE_POSITION_HOLD,
	INT_TYPE_POSITION_TYPE,
	INT_TYPE_POTENTIAL_CAMPAIGN_OBJECTIVE,
	INT_TYPE_PRIMARY_TASK,
	INT_TYPE_PROTOTYPE_1,
	INT_TYPE_PROTOTYPE_2,
	INT_TYPE_PROTOTYPE_3,
	INT_TYPE_PROTOTYPE_4,
	INT_TYPE_RADAR_JAMMER_ON,
	INT_TYPE_RADAR_ON,
	INT_TYPE_RADIO_MESSAGE_TYPE,
	INT_TYPE_RADIO_MESSAGE_VALUE,
	INT_TYPE_REARMING,
	INT_TYPE_REGEN_CREATION_SUB_TYPE,
	INT_TYPE_REGISTRY_LIST_TYPE,
	INT_TYPE_RESERVED_LANDING_SITES,
	INT_TYPE_RESUPPLY_SOURCE,
	INT_TYPE_ROTATED,
	INT_TYPE_ROUTE_CHECK_SUM,
	INT_TYPE_ROUTE_LENGTH,
	INT_TYPE_ROUTE_NODE,
	INT_TYPE_RULES_OF_ENGAGEMENT,
	INT_TYPE_SCOUT_WEAPON_CONFIG_TYPE,
	INT_TYPE_SECTOR_SIDE,
	INT_TYPE_SELECTED_WEAPON,
	INT_TYPE_SELECTED_WEAPON_SYSTEM_READY,
	INT_TYPE_SESSION_COMPLETE,
	INT_TYPE_SIDE,
	INT_TYPE_SKIP_NIGHT_TIME,
	INT_TYPE_SMOKE_TYPE,
	INT_TYPE_SOFT_DAMAGE_CAPABILITY,
	INT_TYPE_SOLO_TASK,
	INT_TYPE_SOUND_CHANNEL,
	INT_TYPE_SOUND_EFFECT_INDEX,
	INT_TYPE_SOUND_EFFECT_LOOPING,
	INT_TYPE_SOUND_EFFECT_PANNING,
	INT_TYPE_SOUND_EFFECT_RATE,
	INT_TYPE_SOUND_EFFECT_SEQUENCE_COUNT,
	INT_TYPE_SOUND_LIST_VALID,
	INT_TYPE_SOUND_LOCALITY,
	INT_TYPE_SPEECH_CATEGORY,
	INT_TYPE_SPEECH_INDEX,
	INT_TYPE_START_NODE,
	INT_TYPE_STRATEGY,
	INT_TYPE_STRATEGY_LEVEL,
	INT_TYPE_SUB_OBJECT_DEPTH,
	INT_TYPE_SUB_OBJECT_TYPE,
	INT_TYPE_SUB_WAYPOINT_COUNT,
	INT_TYPE_SUPPRESS_AI_FIRE,
	INT_TYPE_TACVIEW_LOGGING,
	INT_TYPE_TAIL_ROTOR_DAMAGED,
	INT_TYPE_TAKEOFF_LOCK,
	INT_TYPE_TARGET_PRIORITY_TYPE,
	INT_TYPE_TARGET_SYMBOL_TYPE,
	INT_TYPE_TARGET_TYPE,
	INT_TYPE_TARGET_WEATHER_MODE,
	INT_TYPE_TASK_CATEGORY,
	INT_TYPE_TASK_COMPLETED,
	INT_TYPE_TASK_DIFFICULTY,
	INT_TYPE_TASK_GENERATION,
	INT_TYPE_TASK_ID,
	INT_TYPE_TASK_LEADER,
	INT_TYPE_TASK_OBJECTIVE_PREVIEW_TYPE,
	INT_TYPE_TASK_PASS_PERCENTAGE_PARTIAL,
	INT_TYPE_TASK_PASS_PERCENTAGE_SUCCESS,
	INT_TYPE_TASK_ROUTE_SEARCH,
	INT_TYPE_TASK_SCORE,
	INT_TYPE_TASK_STATE,
	INT_TYPE_TASK_TARGET_CLASS,
	INT_TYPE_TASK_TARGET_SOURCE,
	INT_TYPE_TASK_TARGET_TYPE,
	INT_TYPE_TASK_TERMINATED,
	INT_TYPE_TERRAIN_FOLLOW_MODE,
	INT_TYPE_THREAT_TYPE,
	INT_TYPE_TIMER,
	INT_TYPE_TOTAL_LANDING_SITES,
	INT_TYPE_TRACK_ENTITY_ON_MAP,
	INT_TYPE_UNIQUE_ID,
	INT_TYPE_UPDATED,
	INT_TYPE_VALID,
	INT_TYPE_VALID_GUIDE_MEMBERS,
	INT_TYPE_VALID_SOUND_EFFECT,
	INT_TYPE_VALUE,
	INT_TYPE_VEHICLE_GROUP,
	INT_TYPE_VERBOSE_OPERATIONAL_STATE,
	INT_TYPE_VERSION_NUMBER,
	INT_TYPE_VIEW_CATEGORY,
	INT_TYPE_VIEW_TYPE,
	INT_TYPE_VIEWABLE,
	INT_TYPE_VIEWABLE_WEAPON,
	INT_TYPE_VISIBLE_TASK,
	INT_TYPE_WAIT_FOR_END_TASK,
	INT_TYPE_WARHEAD_EFFECTIVE_CLASS,
	INT_TYPE_WAYPOINT_COUNT,
	INT_TYPE_WAYPOINT_FORMATION,
	INT_TYPE_WAYPOINT_GUIDE_TYPE,
	INT_TYPE_WAYPOINT_NEXT_INDEX,
	INT_TYPE_WAYPOINT_THIS_INDEX,
	INT_TYPE_WEAPON_AND_TARGET_VECTORS_VALID,
	INT_TYPE_WEAPON_BURST_SIZE,
	INT_TYPE_WEAPON_CAMERA_PRIMED,
	INT_TYPE_WEAPON_CONFIG_TYPE,
	INT_TYPE_WEAPON_DECOY_TYPE,
	INT_TYPE_WEAPON_GUIDANCE_TYPE,
	INT_TYPE_WEAPON_KILL_CODE,
	INT_TYPE_WEAPON_MISSILE_PHASE,
	INT_TYPE_WEAPON_ON_GROUND,
	INT_TYPE_WEAPON_PACKAGE_DAMAGED,
	INT_TYPE_WEAPON_PACKAGE_HEADING_DEPTH,
	INT_TYPE_WEAPON_PACKAGE_NUMBER,
	INT_TYPE_WEAPON_SMOKE_TRAIL_TYPE,
	INT_TYPE_WEAPON_SYSTEM_READY,
	INT_TYPE_WEAPON_WARHEAD_TYPE,
	INT_TYPE_WEAPONS_HOLD,
	INT_TYPE_WEATHER_INCREASING,
	INT_TYPE_WEATHER_MODE,
	INT_TYPE_WIND_INCREASING,
	INT_TYPE_X_SECTOR,
	INT_TYPE_Z_SECTOR,

    /*
     :ADDING NEW INT TYPES:
     There are a few steps to follow when adding new int types to be consistent with past development practices.

     1) Add your type here.
     2) Add a preprocessor define in the next section to indicate the number of bits to pack your new type.
        This is used in networked games and save files.
     3) Add a section to the end of the int_type_database defined in file en_int.c; using the other entries as examples.
        Use the preprocessor define you declare below for the number of pack bits.
     4) Add a compile time check to the debug_check_pack_types() function in file en_int.c , again use the other
        entries as examples.
     5) Consider whether it is appropriate to add a default value to the function default_get_entity_int_value() also
        in file en_int.c. This function is also an appropriate place to possibly assert your int type lookup, to
        see that it is only used in appropriate ways.
     */
	NUM_INT_TYPES
};

typedef enum INT_TYPES int_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define NUM_INT_TYPE_PACK_BITS (9)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define NUM_ADDITIVE_BITS									(1)
#define NUM_AIRBORNE_AIRCRAFT_BITS						(1)
#define NUM_ALIGN_WITH_TERRAIN_BITS						(1)
#define NUM_ALIVE_BITS										(1)
#define NUM_ANIMATED_TEXTURE_BITS						(8)
#define NUM_AUTO_ASSIGN_GUNSHIP_BITS					(1)
#define NUM_AUTO_PILOT_BITS								(1)
#define NUM_AWARDED_MEDALS_BITS							(16)
#define NUM_AWARDED_PROMOTION_BITS						(16)
#define NUM_CAMPAIGN_CRITERIA_COUNT_BITS				(8)
#define NUM_CAMPAIGN_CRITERIA_RESULT_BITS				(8)
#define NUM_CAMPAIGN_CRITERIA_TYPE_BITS				(8)
#define NUM_CAMPAIGN_CRITERIA_VALUE_BITS				(16)
#define NUM_CAMPAIGN_MEDAL_BITS							(16)
#define NUM_CAMPAIGN_REQUIRES_APACHE_HAVOC_BITS		(1)
#define NUM_CHEATS_ENABLED_BITS							(1)
#define NUM_CHECK_WAYPOINT_ACTION_BITS					(1)
#define NUM_CHILD_COUNT_BITS								(16)
#define NUM_COLOUR_BITS										(4)
#define NUM_COLOUR_COMPONENT_BITS						(8)
#define NUM_CPG_IDENTIFIED_BITS							(1)
#define NUM_CREW_ROLE_BITS									(1)
#define NUM_CRITICAL_TASK_BITS							(1)
#define NUM_DAMAGE_BITS										(32)
#define NUM_DAY_BITS											(16)
#define NUM_DAY_SEGMENT_TYPE_BITS						(3)
#define NUM_DIFFICULTY_LEVEL_BITS						(2)
#define NUM_DIVISION_ID_BITS								(12)
#define NUM_EJECTED_BITS									(1)
#define NUM_ELAPSED_DAY_BITS								(9)
#define NUM_ENGAGE_ENEMY_BITS								(1)
#define NUM_ENTITY_SUB_TYPE_BITS							(10)
#define NUM_EXPLOSIVE_POWER_BITS							(4)
#define NUM_EXPLOSIVE_QUALITY_BITS						(4)
#define NUM_FINAL_TASK_WAYPOINT_BITS					(8)
#define NUM_FORCE_ATTITUDE_BITS							(8)
#define NUM_FORCE_INFO_CATAGORY_BITS					(5)
#define NUM_FORCE_SECTOR_COUNT_BITS						(16)
#define NUM_FORMATION_BITS									(32)
#define NUM_FORMATION_POSITION_BITS						(5)
#define NUM_FORMATION_POSITIONS_BITS					(32)
#define NUM_FRONTLINE_BITS									(2)
#define NUM_GROUP_CALLSIGN_BITS							(8)
#define NUM_GROUP_FORMATION_BITS							(16)
#define NUM_GROUP_LEADER_BITS								(1)
#define NUM_GROUP_MEMBER_NUMBER_BITS					(5)
#define NUM_GROUP_MODE_BITS								(2)
#define NUM_GUIDE_CRITERIA_TYPE_BITS					(3)
#define NUM_GUIDE_POSITION_TYPE_BITS					(3)
#define NUM_GUNSHIP_RADAR_LOS_CLEAR_BITS				(1)
#define NUM_GUNSHIP_RADAR_TARGET_INDEX_BITS				(8)
#define NUM_GUNSHIP_TYPE_BITS								(5)
#define NUM_HAND_OFF_TARGET_COUNT_BITS					(8)
#define NUM_HELICOPTER_DAMAGE_FLAGS_BITS				(32)
#define NUM_HELICOPTER_DAMAGE_LEVEL_BITS				(2)
#define NUM_ID_NUMBER_SIGNIFICANT_DIGIT_BITS			(3)
#define NUM_INFINITE_FUEL_BITS							(1)
#define NUM_INFINITE_WEAPONS_BITS						(1)
#define NUM_INFRA_RED_JAMMER_ON_BITS					(1)
#define NUM_INSIDE_HANGAR_BITS							(32)
#define NUM_INVULNERABLE_BITS								(1)
#define NUM_IN_USE_BITS										(1)
#define NUM_KEYSITE_ID_BITS								(8)
#define NUM_KEYSITE_USABLE_STATE_BITS					(3)
#define NUM_KILL_NEXT_UPDATE_BITS						(2)
#define NUM_KILLS_BITS										(12)
#define NUM_LANDING_TYPE_BITS								(4)
#define NUM_LASER_ON_BITS									(1)
#define NUM_LENGTH_BITS										(16)
#define NUM_LIGHTS_ON_BITS									(1)
#define NUM_LOCAL_EFFECT_COUNT_BITS						(4)
#define NUM_LOCAL_ONLY_GROUP_BITS						(1)
#define NUM_LOCAL_WEATHER_MODEL_BITS					(1)
#define NUM_LOCK_ON_AFTER_LAUNCH_BITS					(1)
#define NUM_LOSSES_BITS										(10)
#define NUM_LOS_TO_TARGET_BITS							(1)
#define NUM_MAP_ICON_BITS									(6)
#define NUM_MEMBER_COUNT_BITS								(6)
#define NUM_MESSAGE_TEXT_TYPE_BITS						(4)
#define NUM_META_EXPLOSION_TYPE_BITS					(6)
#define NUM_META_SMOKE_LIST_TYPE_BITS					(6)
#define NUM_MISSIONS_FLOWN_BITS							(5)
#define NUM_MOBILE_MOVING_BITS							(1)
#define NUM_MOVEMENT_TYPE_BITS							(3)
#define NUM_MULTIPLAYER_GROUP_BITS						(1)
#define NUM_OBJECT_3D_SHADOW_BITS						(1)
#define NUM_OBJECT_3D_SHAPE_BITS							(12)
#define NUM_OBJECT_DRAWN_ONCE_THIS_FRAME_BITS		(1)
#define NUM_OBJECT_INDEX_BITS								(12)
#define NUM_OPERATIONAL_STATE_BITS						(5)
#define NUM_PARTICLE_COUNT_BITS							(6)
#define NUM_PERFORM_DEBRIEF_BITS							(1)
#define NUM_PLAYER_BITS										(2)
#define NUM_PLAYER_TASK_BITS								(1)
#define NUM_PILOT_EXPERIENCE_BITS						(16)
#define NUM_PILOT_LEVEL_BITS								(4)
#define NUM_PILOT_RANK_BITS								(3)
#define NUM_POSITION_HOLD_BITS							(1)
#define NUM_POSITION_TYPE_BITS							(2)
#define NUM_RADAR_JAMMER_ON_BITS							(1)
#define NUM_RADAR_ON_BITS									(1)
#define NUM_RADIO_MESSAGE_TYPE_BITS						(8)
#define NUM_RADIO_MESSAGE_VALUE_BITS					(32)
#define NUM_READY_TO_FIRE_BITS							(1)
#define NUM_REARMING_BITS									(1)
#define NUM_RESUPPLY_SOURCE_BITS							(3)
#define NUM_ROUTE_NODE_BITS								(10)
#define NUM_ROUTE_CHECK_SUM_BITS							(8)
#define NUM_ROUTE_LENGTH_BITS								(16)
#define NUM_SECTOR_BITS										(8)
#define NUM_SELECTED_WEAPON_SYSTEM_READY_BITS		(1)
#define NUM_SESSION_COMPLETE_BITS						(2)
#define NUM_SIDE_BITS										(2)
#define NUM_SKIP_NIGHT_TIME_BITS							(1)
#define NUM_SMOKE_TYPE_BITS								(6)
#define NUM_SOUND_CHANNEL_BITS							(4)
#define NUM_SOUND_EFFECT_INDEX_BITS						(16)
#define NUM_SOUND_EFFECT_LOOPING_BITS					(1)
#define NUM_SOUND_EFFECT_PANNING_BITS					(1)
#define NUM_SOUND_EFFECT_RATE_BITS						(16)
#define NUM_SOUND_EFFECT_SEQUENCE_COUNT_BITS			(4)
#define NUM_SOUND_LOCALITY_BITS							(2)
#define NUM_SPEECH_CATEGORY_BITS							(5)
#define NUM_SPEECH_INDEX_BITS								(8)
#define NUM_SUB_WAYPOINT_COUNT_BITS						(10)
#define NUM_SUPPRESS_AI_FIRE_BITS						(1)
#define NUM_TAG_BITS											(8)
#define NUM_TASK_COMPLETED_BITS							(3)
#define NUM_TASK_DIFFICULTY_BITS							(4)
#define NUM_TASK_GENERATION_BITS							(32)
#define NUM_TASK_ID_BITS									(12)
#define NUM_TASK_LEADER_BITS								(1)
#define NUM_TASK_ROE_TYPE_BITS							(2)
#define NUM_TASK_SCORE_BITS								(16)
#define NUM_TASK_START_WAYPOINT_BITS					(8)
#define NUM_TASK_STATE_BITS								(2)
#define NUM_TASK_STOP_WAYPOINT_BITS						(8)
#define NUM_TASK_TARGET_CLASS_BITS						(2)
#define NUM_TASK_TARGET_SOURCE_BITS						(4)
#define NUM_TASK_TARGET_TYPE_BITS						(32)
#define NUM_TASK_TERMINATED_BITS							(4)
#define NUM_UNIQUE_ID_BITS									(32)
#define NUM_UPDATED_BITS									(1)
#define NUM_VALID_BITS										(1)
#define NUM_VALID_GUIDE_MEMBERS_BITS					(32)
#define NUM_VALID_SOUND_EFFECT_BITS						(1)
#define NUM_VERBOSE_OPERATIONAL_STATE_BITS			(6)
#define NUM_VERSION_NUMBER_BITS							(16)	//***** DO NOT CHANGE *****//
#define NUM_WAYPOINT_COUNT_BITS							(8)
#define NUM_WAYPOINT_FORMATION_BITS						(16)
#define NUM_WAYPOINT_INDEX_BITS							(10)
#define NUM_WAYPOINT_REACHED_BITS						(4)
#define NUM_WEAPON_AND_TARGET_VECTORS_VALID_BITS	(1)
#define NUM_WEAPON_CONFIG_TYPE_BITS						(10)
#define NUM_WEAPON_KILL_CODE_BITS						(3)
#define NUM_WEAPON_MISSILE_PHASE_BITS					(3)
#define NUM_WEAPON_ON_GROUND_BITS						(1)
#define NUM_WEAPON_PACKAGE_DAMAGED_BITS				(1)
#define NUM_WEAPON_PACKAGE_HEADING_DEPTH_BITS		(5)
#define NUM_WEAPON_PACKAGE_NUMBER_BITS					(12)
#define NUM_WEAPON_BURST_SIZE_BITS						(NUM_WEAPON_PACKAGE_NUMBER_BITS)
#define NUM_WEAPONS_HOLD_BITS								(1)
#define NUM_WEATHER_INCREASING_BITS						(1)
#define NUM_WEATHER_MODE_BITS								(3)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum INT_PACK_TYPES
{
	INT_PACK_TYPE_SIGNED,
	INT_PACK_TYPE_UNSIGNED,
	NUM_INT_PACK_TYPES
};

typedef enum INT_PACK_TYPES int_pack_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct INT_TYPE_DATA
{
	const char
		*name;

	int_pack_types
		pack_type;

	int
		num_pack_bits,
		debug_pack,
		fast_track;
};

typedef struct INT_TYPE_DATA int_type_data;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern int_type_data
	int_type_database[NUM_INT_TYPES];

#define get_int_type_name(INT_TYPE) (int_type_database[(INT_TYPE)].name)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern const char
	*overload_invalid_int_type_message,
	*debug_fatal_invalid_int_type_message;

#ifdef DEBUG

#define validate_int_type(INT_TYPE) ((((INT_TYPE) >= 0) && ((INT_TYPE) < NUM_INT_TYPES)) ? ((INT_TYPE)) : (process_assert (overload_invalid_int_type_message, __FILE__, __LINE__), 0))

#else

#define validate_int_type(INT_TYPE) ((INT_TYPE))

#endif

#define debug_fatal_invalid_int_type(EN,INT_TYPE) (debug_fatal (debug_fatal_invalid_int_type_message, get_local_entity_type_name ((EN)), get_local_entity_index ((EN)), get_int_type_name ((INT_TYPE)), __FILE__, __LINE__))

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void debug_log_pack_overflow(const char* type, const char* name, unsigned int width, int value, float fvalue);

extern void (*fn_set_local_entity_raw_int_value[NUM_ENTITY_TYPES][NUM_INT_TYPES]) (entity *en, int_types type, int value);

#define set_local_entity_raw_int_value(EN,INT_TYPE,VALUE) (fn_set_local_entity_raw_int_value[get_local_entity_type ((EN))][validate_int_type ((INT_TYPE))] ((EN), (INT_TYPE), (VALUE)))

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void (*fn_set_local_entity_int_value[NUM_ENTITY_TYPES][NUM_INT_TYPES]) (entity *en, int_types type, int value);

#define set_local_entity_int_value(EN,INT_TYPE,VALUE) (fn_set_local_entity_int_value[get_local_entity_type ((EN))][validate_int_type ((INT_TYPE))] ((EN), (INT_TYPE), (VALUE)))

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void (*fn_set_client_server_entity_int_value[NUM_ENTITY_TYPES][NUM_INT_TYPES][NUM_COMMS_MODEL_TYPES]) (entity *en, int_types type, int value);

#define set_client_server_entity_int_value(EN,INT_TYPE,VALUE) (fn_set_client_server_entity_int_value[get_local_entity_type ((EN))][validate_int_type ((INT_TYPE))][get_comms_model ()] ((EN), (INT_TYPE), (VALUE)))

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern int (*fn_get_local_entity_int_value[NUM_ENTITY_TYPES][NUM_INT_TYPES]) (entity *en, int_types type);

#define get_local_entity_int_value(EN,INT_TYPE) (fn_get_local_entity_int_value[get_local_entity_type ((EN))][validate_int_type ((INT_TYPE))] ((EN), (int_types)(INT_TYPE)))

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void initialise_entity_int_value_default_functions (void);

extern void pack_int_value (entity *en, int_types type, int value);

extern int unpack_int_value (entity *en, int_types type);

extern void pack_int_type (int_types type);

extern int_types unpack_int_type (void);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
