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

enum EO_FOV_LEVELS
{
	EO_FOV_ZOOM,
	EO_FOV_NARROW,
	EO_FOV_MEDIUM,
	EO_FOV_WIDE,
	NUM_EO_FOV_LEVELS
};

typedef enum EO_FOV_LEVELS eo_fov_levels;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct EO_PARAMS
{
	int
		field_of_view,
		min_field_of_view,
		max_field_of_view;
};

typedef struct EO_PARAMS eo_params;

// 030319 loke
// This struct contains information about the eo zoom level when using the new zoom method

struct EO_PARAMS_DYNAMIC_MOVE
{
	float
		zoom,
		min_zoom,
		max_zoom;
};

typedef struct EO_PARAMS_DYNAMIC_MOVE eo_params_dynamic_move;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern int
//	eo_target_locked,
	eo_on_target,
	eo_low_light,
	eo_ground_stabilised;

extern target_acquisition_systems
	eo_sensor;

extern float
	eo_azimuth,
	eo_min_azimuth,
	eo_max_azimuth,
	eo_elevation,
	eo_min_elevation,
	eo_max_elevation,
	eo_max_visual_range;

extern viewpoint
	eo_vp;

extern int
	draw_eo_boresight,
	draw_eo_terrain_los_markers;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void initialise_common_eo (void);

extern void deinitialise_common_eo (void);

extern void update_common_eo (void);

extern void activate_common_eo (void);

extern void deactivate_common_eo (void);

extern void slew_eo_to_direction(float elevation, float azimuth);

extern void slave_common_eo_to_current_target (void);
extern void slave_common_eo_to_position (vec3d* target_position);

extern void select_next_eo_target (void);

extern void select_previous_eo_target (void);

extern void select_next_designated_eo_target (void); // Jabberwock 031108 Designated targets

extern void select_previous_designated_eo_target (void);

extern float convert_linear_view_value (eo_params_dynamic_move *eo);

extern float make_panning_offset_from_axis (long state);

extern void copy_eo_zoom(eo_params_dynamic_move* from, eo_params_dynamic_move* to);

// returns range to point as return value, point in parameter
extern float get_eo_los_intercept_point(vec3d* intercept_point);

extern int laser_is_active(void);
extern void set_laser_is_active(int is_active);

extern float get_triangulated_range(entity* target);
extern float get_triangulated_by_position_range(vec3d* source, vec3d* target);

extern int electrical_system_active(void);
extern void set_electrical_system_active(int active);

extern int eo_is_tracking_point(void);
extern vec3d* get_eo_tracking_point(void);
extern void eo_start_tracking(vec3d* tracking_point);
extern void eo_stop_tracking(void);
extern int eo_tracking_point_valid(vec3d* tracking_point);

extern float get_range_to_target(void);

extern void keyboard_slew_eo_system(float fine_slew_rate, float medium_slew_rate, float coarse_slew_rate);
extern void joystick_slew_eo_system(float slew_rate);

extern int is_using_eo_system(int include_hms);
extern int eo_is_locked(void);
extern void toggle_eo_lock(void);
extern void set_eo_lock(int locked);

extern void set_eo_slave_target(entity* target);

extern void cpg_scan_for_eo_targets(void);

extern void get_eo_azimuth_and_elevation(float* az, float* el);

extern void cpg_report_next_prev_target(entity* target); //ataribaby 4/1/2009 added CPG next/prev target lock and ID
extern void cpg_report_identified_target(entity* target); //ataribaby 4/1/2009 added CPG next/prev target lock and ID

extern void update_eo_max_visual_range(void);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
