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

enum TARGET_ACQUISITION_SYSTEMS
{
	TARGET_ACQUISITION_SYSTEM_OFF,
	TARGET_ACQUISITION_SYSTEM_GROUND_RADAR,
	TARGET_ACQUISITION_SYSTEM_AIR_RADAR,
	TARGET_ACQUISITION_SYSTEM_FLIR,				// forward looking infra-red
	TARGET_ACQUISITION_SYSTEM_DTV,				// daytime TV
	TARGET_ACQUISITION_SYSTEM_DVO,				// direct view optics
	TARGET_ACQUISITION_SYSTEM_LLLTV,				// low light level TV
	TARGET_ACQUISITION_SYSTEM_PERISCOPE,		// periscope
	TARGET_ACQUISITION_SYSTEM_IHADSS,			// integrated helmet and display sighting system
	TARGET_ACQUISITION_SYSTEM_HIDSS,				// helmet integrated display sight system
	TARGET_ACQUISITION_SYSTEM_HMS,				// helmet mounted sight
	NUM_TARGET_ACQUISITION_SYSTEMS
};

typedef enum 
{
	RANGEFINDER_FCR,
	RANGEFINDER_LASER,
	RANGEFINDER_TRIANGULATION
} rangefinding_system;

typedef enum TARGET_ACQUISITION_SYSTEMS target_acquisition_systems;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern target_acquisition_systems
	target_acquisition_system;

extern int
	target_locked;

extern float
	cpg_identify_target_delay;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern const char
	*target_acquisition_system_names[NUM_TARGET_ACQUISITION_SYSTEMS];

#define get_selected_target_acquisition_system_name() (target_acquisition_system_names[target_acquisition_system])

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern int
	continuous_target_acquisition_system_steer_left_key,
	continuous_target_acquisition_system_steer_right_key,
	continuous_target_acquisition_system_steer_up_key,
	continuous_target_acquisition_system_steer_down_key;

extern int
	single_target_acquisition_system_steer_left_key,
	single_target_acquisition_system_steer_right_key,
	single_target_acquisition_system_steer_up_key,
	single_target_acquisition_system_steer_down_key,
	single_target_acquisition_system_inc_range_key,
	single_target_acquisition_system_dec_range_key,
	single_target_acquisition_system_inc_target_priority_key,
	single_target_acquisition_system_dec_target_priority_key,
	single_target_acquisition_system_select_next_target_key,
	single_target_acquisition_system_select_previous_target_key,
	single_target_acquisition_system_select_next_designated_key, // Jabberwock 031107 Designated targets
	single_target_acquisition_system_select_previous_designated_key;

extern int
	continuous_target_acquisition_system_steer_left_fast_key,
	continuous_target_acquisition_system_steer_right_fast_key,
	continuous_target_acquisition_system_steer_up_fast_key,
	continuous_target_acquisition_system_steer_down_fast_key;

extern int
	single_target_acquisition_system_steer_left_fast_key,
	single_target_acquisition_system_steer_right_fast_key,
	single_target_acquisition_system_steer_up_fast_key,
	single_target_acquisition_system_steer_down_fast_key,
	single_target_acquisition_system_inc_range_fast_key,
	single_target_acquisition_system_dec_range_fast_key,
	single_target_acquisition_system_inc_target_priority_fast_key,
	single_target_acquisition_system_dec_target_priority_fast_key;

extern int
	continuous_target_acquisition_system_steer_left_fine_key,
	continuous_target_acquisition_system_steer_right_fine_key,
	continuous_target_acquisition_system_steer_up_fine_key,
	continuous_target_acquisition_system_steer_down_fine_key;

extern int
	toggle_ground_stabilisation_key;

// Jabberwock 030930 - Mouse functions	
extern int
	mouse_move_left,
	mouse_move_right,
	mouse_move_up,
	mouse_move_down,
	mouse_wheel_up, 
	mouse_wheel_down;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void initialise_common_target_acquisition_systems (void);

extern void deinitialise_common_target_acquisition_systems (void);

extern void update_common_target_acquisition_systems (void);

extern void reset_common_target_acquisition_system_keys (void);

extern void set_common_target_acquisition_system_lock_target (int lock);

extern void set_gunship_target (entity *target);

extern void toggle_designated_target (void); // Jabberwock 031108 Designated targets

extern entity *get_local_entity_boresight_target (entity *source, vec3d *boresight_unit_vector, float range, float field_of_view);

extern const char *get_target_display_name (entity *target, char *buffer, int large_display);

extern int get_number_of_valid_gunship_targets (entity *receiver);

extern int get_valid_gunship_target_safe_index (entity *receiver, int depth);

extern void set_valid_gunship_target_safe_index (int index);

//extern void select_simple_avionics_target_acquisition_system (void);

extern void play_common_cpg_target_acquisition_system_speech (target_acquisition_systems new_system, target_acquisition_systems old_system, int damaged);

extern rangefinding_system get_range_finder(void);

extern float get_target_range(vec3d* target_position, rangefinding_system* rf_system);

extern void cpg_report_target(entity* target);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
