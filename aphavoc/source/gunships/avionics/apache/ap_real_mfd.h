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

typedef struct APACHE_COORDINATE_POINTS apache_coordinate_points;

typedef enum {
	TADS_DIGITAL_ZOOM_WIDE,
	TADS_DIGITAL_ZOOM_NORMAL,
	TADS_DIGITAL_ZOOM_ZOOM,
} tads_digital_zoom_levels;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void initialise_apache_mfd (void);

extern void deinitialise_apache_mfd (void);

extern void select_apache_mfd_mode (mfd_modes mode, mfd_locations location);

extern void draw_apache_mfd_on_cockpit (float x_org, float y_org, int large_mfd, int draw_translucent_background, mfd_locations location);

extern void draw_apache_mfd_on_texture (mfd_locations location);

extern void draw_apache_virtual_cockpit_ort_view (int x_min, int x_max);

extern void draw_overlaid_apache_mfd (float x_org, float y_org, float size, mfd_locations location);

extern void select_next_apache_tsd_ase_range (void);

extern void select_previous_apache_tsd_ase_range (void);

extern void select_next_apache_tsd_declutter_level (void);

extern void select_previous_apache_tsd_declutter_level (void);

extern void select_next_tsd_underlay_level (void);

extern void select_next_apache_lhs_mfd (void);

extern void select_previous_apache_lhs_mfd (void);

extern void select_next_apache_rhs_mfd (void);

extern void select_previous_apache_rhs_mfd (void);

extern void select_apache_ground_radar_mfd (void);

extern void select_apache_air_radar_mfd (void);

extern void select_apache_tads_mfd (void);

extern void toggle_apache_ase_auto_page (void);

extern void auto_page_apache_ase_mfd (void);

extern void toggle_apache_lhs_mfd_on_off (void);

extern void toggle_apache_rhs_mfd_on_off (void);

extern void toggle_apache_ort_on_off(void);

extern int get_apache_mfd_has_focus (mfd_locations mfd_location);

extern int get_apache_tads_display_visible (void);

extern void create_apache_pfz(int is_nfz);

extern void draw_apache_virtual_cockpit_ort_symbology(void);

mfd_modes get_apache_current_mfd_mode(mfd_locations location);

void set_apache_mfd_sub_mode(mfd_locations location, int sub_mode);
int get_apache_mfd_sub_mode(mfd_locations location);
void set_apache_mfd_sub_page(mfd_locations location, int page);
int get_apache_mfd_sub_page(mfd_locations location);
int apache_mfd_has_more_sub_pages(mfd_locations location);

void adjust_apache_pitch_ladder_datum_position(float adjustment);

int get_apache_tsd_phase_is_atk(mfd_locations location);
float get_apache_tsd_range(mfd_locations location);
void set_apache_tsd_range(mfd_locations location, float range);

void set_apache_tsd_phase_nav(mfd_locations location);
void set_apache_tsd_phase_atk(mfd_locations location);

unsigned get_apache_tsd_is_zoomed(mfd_locations location);
void toggle_apache_tsd_zoom(mfd_locations location);

unsigned get_apache_tsd_is_centered(mfd_locations location);
void toggle_apache_tsd_is_centered(mfd_locations location);

unsigned get_apache_tsd_frozen(mfd_locations location);
void set_apache_tsd_frozen(mfd_locations location, int frozen);
void toggle_apache_tsd_frozen(mfd_locations location);

void set_apache_tsd_show_waypoint_review(mfd_locations location, apache_coordinate_points* wpt);
unsigned get_apache_tsd_display_present_position_status(mfd_locations location);
void toggle_apache_tsd_display_present_position_status(mfd_locations location);

apache_coordinate_points*  get_apache_tsd_show_waypoint_review(mfd_locations location);
void set_apache_tsd_show_waypoint_review(mfd_locations location, apache_coordinate_points* wpt);

tads_digital_zoom_levels get_tads_digital_zoom_level(void);
void set_tads_digital_zoom_level(tads_digital_zoom_levels zoom);

apache_coordinate_points* get_apache_clicked_point(mfd_locations location, float pointer_pos_x, float pointer_pos_y, unsigned waypoints_only);
entity* get_apache_clicked_target(mfd_locations location, float pointer_pos_x, float pointer_pos_y);
int get_apache_clicked_map_coordinate(mfd_locations location, float pointer_pos_x, float pointer_pos_y, vec3d* map_coordinate, float* range, float* scale);

void draw_apache_radar_target_symbol(entity* target, float dx, float dy, int los_clear, int moving, rgb_colour target_symbol_colour, rgb_colour target_symbol_background_colour, rgb_colour bg_colour);

// selects target under pointer on TSD, or if EO is active and no target under pointer, makes a point lock at position
//extern void apache_select_clicked_target();

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
