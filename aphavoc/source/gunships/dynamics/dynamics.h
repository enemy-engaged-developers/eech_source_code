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
// MOVED FROM BELOW SO THAT THE TYPE IS AVAILABLE FOR common/co_dmg.h ///////////////////////////////////////////////////////////

enum DYNAMICS_OPTIONS_TYPES
{

	DYNAMICS_OPTIONS_CROSS_COUPLING,
	DYNAMICS_OPTIONS_DAMAGE,
	DYNAMICS_OPTIONS_DRAW_FLIGHT_PATH,
	DYNAMICS_OPTIONS_GROUND_COLLISIONS,
	DYNAMICS_OPTIONS_GROUND_EFFECT,
	DYNAMICS_OPTIONS_KEYBOARD_ASSISTANCE,
	DYNAMICS_OPTIONS_OBJECT_COLLISIONS,
	DYNAMICS_OPTIONS_OVER_TORQUE,
	DYNAMICS_OPTIONS_RETREATING_BLADE_STALL,
	DYNAMICS_OPTIONS_REVERSE_THROTTLE_INPUT,
	DYNAMICS_OPTIONS_TRANSITIONAL_LIFT,
	DYNAMICS_OPTIONS_VORTEX_RING,
	DYNAMICS_OPTIONS_WIND,
	NUM_DYNAMICS_OPTIONS_TYPES
};

typedef enum DYNAMICS_OPTIONS_TYPES dynamics_options_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "common/co_dyn.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// Remake from this directory downwards
//
// 1 - short watch messages
// 2 - long watch messages
//

#define DEBUG_DYNAMICS 									2

#define MODEL_FRAME_RATE 								50

#define NUMBER_OF_DYNAMIC_FORCES 					32

#define REFUELING_RATE									18.9  // 60 seconds for 2500lbs of fuel

#define FUEL_LEAK_RATE									0.945  // 1200 seconds for 2500lbs of fuel

#define DYNAMICS_LOW_ROTOR_RPM_SPEECH_TIME		(60 * ONE_SECOND)

#define DYNAMICS_LOW_FUEL_SPEECH_TIME				(60 * ONE_SECOND)

#define DYNAMICS_EXCEEDING_VNE_SPEECH_TIME 		(60 * ONE_SECOND)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEFAULT_DYNAMICS_MODEL	DYNAMICS_MODEL_ADVANCED

#define get_dynamics_auto_hover_state() (current_flight_dynamics->auto_hover)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if DEBUG_DYNAMICS

extern float
	delta_heading_per_sec,
	delta_pitch_per_sec,
	delta_roll_per_sec;

#endif

extern entity *current_flight_dynamics_landed_at_keysite;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum DYNAMICS_DESTROY_TYPES
{

	DYNAMICS_DESTROY_SHOT_DOWN,
	DYNAMICS_DESTROY_CRASH_LANDED,
	DYNAMICS_DESTROY_WATER_CRASH,
	NUM_DYNAMICS_DESTROY_TYPES
};

typedef enum DYNAMICS_DESTROY_TYPES dynamics_destroy_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern const char
	*dynamics_options_type_names [];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct DYNAMICS_FLOAT_VARIABLE
{

	float
		modifier,
		value,
		delta,
		min,
		max;

	unsigned short int
		damaged;
};

typedef struct DYNAMICS_FLOAT_VARIABLE dynamics_float_variable;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct DYNAMICS_OPTIONS_TYPE
{

	unsigned int
		dynamics_options_cross_coupling				: 1,
		dynamics_options_damage							: 1,
		dynamics_options_draw_flight_path			: 1,
		dynamics_options_ground_collisions			: 1,
		dynamics_options_ground_effect				: 1,
		dynamics_options_keyboard_assistance		: 1,
		dynamics_options_object_collisions			: 1,
		dynamics_options_over_torque					: 1,
		dynamics_options_retreating_blade_stall	: 1,
		dynamics_options_reverse_throttle_input	: 1,
		dynamics_options_transitional_lift			: 1,
		dynamics_options_vortex_ring					: 1,
		dynamics_options_wind							: 1;
};

typedef struct DYNAMICS_OPTIONS_TYPE dynamics_options_type;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct INPUT_VARIABLE_TYPE
{

	// cyclic data

	dynamics_float_variable
		cyclic_x,
		cyclic_y,
		cyclic_x_trim,
		cyclic_y_trim,
		cyclic_vertical_pressure,
		cyclic_horizontal_pressure;

	int
		cyclic_joystick_device_index,
		collective_joystick_device_index,
		pedal_joystick_device_index;

	struct JOYSTICK_DEVICE_INFO
		cyclic_joystick_device,
		collective_joystick_device,
		pedal_joystick_device;

	int
		cyclic_input_pressure;

	// collective data

	dynamics_float_variable
		collective,
		collective_pressure;

	int
		collective_input_pressure;

	// pedal data

	dynamics_float_variable
		pedal,
		pedal_trim,
		pedal_pressure;

	int
		pedal_input_pressure;
};

typedef struct INPUT_VARIABLE_TYPE input_variable_type;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum FLIGHT_PATH_ACTION_TYPE
{

	FLIGHT_PATH_ACTION_USER_NAVIGATING,
	FLIGHT_PATH_ACTION_AUTOPILOT_NAVIGATING,
	FLIGHT_PATH_ACTION_LAUNCH_WEAPON,
	FLIGHT_PATH_ACTION_HIT,
	FLIGHT_PATH_ACTION_DESTROYED,
	FLIGHT_PATH_ACTION_LANDED,
	NUM_FLIGHT_PATH_ACTION_TYPES
};

typedef enum FLIGHT_PATH_ACTION_TYPE flight_path_action_type;

extern const char
	*flight_path_action_names [];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct FLIGHT_PATH_DATA
{

	flight_path_action_type
		action;

	float
		x,
		z;

	struct FLIGHT_PATH_DATA
		*next;
};

typedef struct FLIGHT_PATH_DATA flight_path_data;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct DYNAMICS_TYPE
{

	gunship_types
		gunship;

	entity_sub_types
		sub_type;

	char
		filename [128];

	int
		model_frame_rate,
		model_iterations;

	float
		model_delta_time;

	double_vec3d
		old_position,
		position;

	vec3d
		rotation_origin;

	matrix3x3
		attitude;

	// control inputs

	input_variable_type
		input_data;

	// dynamic data

	vec3d
		centre_of_gravity, // referenced from the rotor hub.
		model_motion_vector,
		world_motion_vector,
		model_acceleration_vector,
		world_acceleration_vector;

	dynamics_float_variable
		undercarriage_state,
		left_engine_rpm,
		left_engine_n1_rpm,
		left_engine_torque,
		left_engine_temp,

		right_engine_rpm,
		right_engine_n1_rpm,
		right_engine_torque,
		right_engine_temp,

		apu_rpm,

		main_rotor_number_of_blades,
		main_rotor_induced_air,
		main_rotor_induced_vortex_air_flow,
		main_rotor_diameter,
		main_rotor_area,
		main_rotor_thrust,
		main_rotor_roll_angle,
		main_rotor_pitch_angle,
		main_rotor_rpm,
		main_rotor_rps,
		main_rotor_coning_angle,
		main_rotor_angular_position,
		main_rotor_angular_increment,
		main_blade_pitch,
		main_blade_x_pitch,
		main_blade_y_pitch,
		main_rotor_swash_plate_pitch,
		main_rotor_swash_plate_roll,

		tail_rotor_induced_air,
		tail_rotor_diameter,
		tail_rotor_thrust,
		tail_rotor_rpm,
		tail_rotor_rps,
		tail_rotor_angular_position,
		tail_blade_pitch,
		tail_boom_length,
		cross_coupling_effect,

		power_avaliable,
		power_required,
		power_induced,
		power_profile,
		power_parasite,
		power_surplus,

		velocity_x,
		velocity_y,
		velocity_z,
		acceleration_x,
		acceleration_y,
		acceleration_z,
		world_velocity_x,
		world_velocity_y,
		world_velocity_z,

		air_density,
		pitch,
		roll,
		heading,
		lift,													// modifier alters translational lift
		translational_lift,								// only modifier used
		altitude,
		drag_x,
		drag_y,
		drag_z,
		heading_inertia,
		pitch_inertia,
		roll_inertia,
		heading_moment,
		pitch_moment,
		roll_moment,
		heading_moment_reaction,
		pitch_moment_reaction,
		roll_moment_reaction,
		angular_heading_acceleration,
		angular_pitch_acceleration,
		angular_roll_acceleration,
		angular_heading_velocity,
		angular_pitch_velocity,
		angular_roll_velocity,
		landing_quality,
		mass, 												// modifier alters weapon-mass effect
		weapon_mass, 										// only modifier used
		ground_effect,										// only modifier used

		// for instruments

		indicated_airspeed,
		indicated_slip,
		barometric_altitude,
		radar_altitude,
		g_force,
		combined_engine_rpm,
		combined_engine_torque,
		fuel_weight;

	//
	// Collision
	//

	dynamics_collision_type
		*fixed_collision_points,
		*last_frame_fixed_collision_points,
		*moving_collision_points,
		*last_frame_moving_collision_points;

	int
		valid_last_frame_fixed_collision_points,
		valid_last_frame_moving_collision_points,
		number_of_dynamic_forces,
		max_number_of_dynamic_forces,
		number_of_fixed_collision_points,
		number_of_moving_collision_points;

	dynamic_force_type
		*dynamic_forces;

	terrain_3d_point_data
		terrain_info;

	flight_path_data
		*flight_path;

	//
	// Flags
	//

	dynamics_options_type
		dynamics_options;

	float
		damage_repair_time;

	short int
		rotor_rotation_direction; // 1 = clockwise (russian), -1 anti-clockwise (usa)

	unsigned int
		repairing_damage,
		dynamics_damage;


	unsigned int
		left_overtorque				: 1,
		right_overtorque				: 1,
		refueling						: 1,
		repairing						: 1,
		dying								: 1,
		rotor_brake						: 1,
		wheel_brake						: 1,
		auto_hover						: 3,
		model_paused					: 1,
		left_engine_starter_active		: 1,
		right_engine_starter_active		: 1;

	float
		main_rotor_governor_rpm,
		main_rotor_idle_rpm,
		main_rotor_max_rpm,
		engine_idle_rpm,
		engine_start_timer;
};

typedef struct DYNAMICS_TYPE dynamics_type;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern dynamics_type
	*current_flight_dynamics;

#define set_model_delta_time(DELTA_TIME) (current_flight_dynamics->model_delta_time = (DELTA_TIME))

#define get_model_delta_time() (current_flight_dynamics->model_delta_time)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void update_apu_rpm_dynamics (void);
extern void update_engine_rpm_dynamics (int engine_num);
extern void update_engine_temperature_dynamics (int engine_num);

extern void initialise_flight_dynamics (entity *en);

extern void deinitialise_flight_dynamics (void);

extern void set_dynamics_entity_values (entity *en);

extern void update_helicopter_damage ();

extern void update_flight_dynamics (void);

extern void flight_model_pause (event *ev);

extern void move_cog (void *ev);

extern void save_dynamics_model (event *ev);

extern void load_dynamics_model (event *ev);

extern void update_dynamics_external_values (void);

extern void flight_dynamics_toggle_rotor_brake (event *ev);

extern void flight_dynamics_toggle_wheel_brake (event *ev);

extern void flight_dynamics_toggle_auto_hover (event *ev);

extern void set_current_flight_dynamics_auto_pilot (int flag);

extern int get_current_flight_dynamics_auto_pilot (void);

extern void flight_dynamics_toggle_auto_pilot (event *ev);

extern void flight_dynamics_toggle_bobup (event *ev);   //  Added by Javelin 5/18

extern void set_current_flight_dynamics_rotor_brake (int flag);

extern void set_current_flight_dynamics_wheel_brake (int flag);

extern void dynamics_takeoff (void);

extern void dynamics_land (void);

extern int get_current_dynamics_options (dynamics_options_types option);

extern float get_dynamics_normalised_fuel_value (void);

extern entity *get_keysite_currently_landed_at (void);

extern void set_keysite_currently_landed_at (entity *en);

extern float set_flight_dynamics_mass (void);

extern void update_current_flight_dynamics_fuel_weight (void);

extern void update_current_flight_dynamics_flight_time (void);

extern void dynamics_kill_model (dynamics_destroy_types type, entity *aggressor);

extern void add_flight_path_action (float x, float z, flight_path_action_type action);

extern void flight_dynamics_toggle_altitude_lock (event *ev);

extern void flight_dynamics_decrease_altitude_lock (event *ev);

extern void flight_dynamics_increase_altitude_lock (event *ev);

extern void flight_dynamics_toggle_autopilot_heading (event *ev);

extern void create_rotor_vibration(float force);
extern void create_advanced_rotor_vibration(float force, int damaged);

extern void flight_dynamics_start_engine_ev (event* ev);
extern void flight_dynamics_throttle_engine_ev (event* ev);
extern void flight_dynamics_start_apu_ev (event* ev);
extern void flight_dynamics_decrease_governor_rpm(event* ev);
extern void flight_dynamics_increase_governor_rpm(event* ev);

#ifdef DEBUG
extern void debug_dynamics_event1(event* ev);
extern void debug_dynamics_event2(event* ev);
extern void debug_dynamics_event3(event* ev);
extern void debug_dynamics_event4(event* ev);
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern int
	flight_dynamics_lock_position_flag,
	flight_dynamics_autopilot_heading,
	flight_dynamics_autopilot_heading_active;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum DYNAMICS_HOVER_HOLD_TYPES
{

	HOVER_HOLD_NONE,
	HOVER_HOLD_NORMAL,
	HOVER_HOLD_STABLE,
	HOVER_HOLD_ALTITUDE_LOCK,
	HOVER_HOLD_AUTO_PILOT,
};

typedef enum DYNAMICS_HOVER_HOLD_TYPES dynamics_hover_hold_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define get_current_flight_dynamics_fuel_weight() (current_flight_dynamics->fuel_weight.value)

#define set_current_flight_dynamics_fuel_weight(FUEL) (current_flight_dynamics->fuel_weight.value = (FUEL))

#define get_current_flight_dynamics() (current_flight_dynamics)

#define set_current_flight_dynamics_lock_position(FLAG) (flight_dynamics_lock_position_flag = (FLAG))

#define toggle_flight_dynamics_autopilot_heading() (flight_dynamics_autopilot_heading = !flight_dynamics_autopilot_heading)

#define get_current_flight_dynamics_wheel_brake() (current_flight_dynamics->wheel_brake)

#define get_current_flight_dynamics_rotor_brake() (current_flight_dynamics->rotor_brake)

#define get_current_flight_dynamics_auto_hover() (((current_flight_dynamics->auto_hover == HOVER_HOLD_NORMAL) || (current_flight_dynamics->auto_hover == HOVER_HOLD_STABLE)) ? TRUE : FALSE)

#define set_current_flight_dynamics_auto_hover(FLAG) (current_flight_dynamics->auto_hover = (FLAG))

#define get_current_flight_dynamics_altitude_lock() ((current_flight_dynamics->auto_hover == HOVER_HOLD_ALTITUDE_LOCK) ? TRUE : FALSE)

#define get_current_flight_dynamics_overtorque() ((!get_current_flight_dynamics_auto_pilot ()) && (current_flight_dynamics->left_overtorque | current_flight_dynamics->right_overtorque))

#define get_current_flight_dynamics_leng_overtorque() ((!get_current_flight_dynamics_auto_pilot ()) && (current_flight_dynamics->left_overtorque))

#define get_current_flight_dynamics_reng_overtorque() ((!get_current_flight_dynamics_auto_pilot ()) && (current_flight_dynamics->right_overtorque))

#define get_current_flight_dynamics_low_rotor_rpm() (((!get_current_flight_dynamics_auto_pilot ()) && (current_flight_dynamics->main_rotor_rpm.value < 90.0)) ? TRUE : FALSE)

#define get_current_flight_dynamics_engine_damage_imminent() ((((current_flight_dynamics->left_engine_temp.value > (current_flight_dynamics->left_engine_temp.max * 0.80)) || (current_flight_dynamics->right_engine_temp.value > (current_flight_dynamics->right_engine_temp.max * 0.80))) ? TRUE : FALSE))

#define get_current_flight_dynamics_flight_path() (current_flight_dynamics->flight_path)

#define set_current_flight_dynamics_undercarriage_state(STATE) (current_flight_dynamics->undercarriage_state.value = bound ((STATE), current_flight_dynamics->undercarriage_state.min, current_flight_dynamics->undercarriage_state.max))

#define get_current_flight_dynamics_undercarriage_state() (current_flight_dynamics->undercarriage_state.value)

#define set_current_flight_dynamics_valid_collision_points(STATE) (current_flight_dynamics->valid_last_frame_fixed_collision_points = (STATE))

#define get_current_flight_dynamics_valid_collision_points() (current_flight_dynamics->valid_last_frame_fixed_collision_points)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
