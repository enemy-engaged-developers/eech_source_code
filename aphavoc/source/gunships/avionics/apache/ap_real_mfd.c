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

#include "ap_mfd_buttons.h"
#include "ap_checklists.h"
#include "ap_mfd_sprites.h"
#include "ap_coordinate_point.h"
#include "ap_hud_mfd_common.h"

#include "../common/co_adf.h"
#include "../../dynamics/common/co_fuel.h"
#include "entity/tacview/tacview.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float tads_digital_zoom_fov[] = {
	0.95,
	0.75,
	0.50
};

static tads_digital_zoom_levels tads_digital_zoom_level;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void copy_export_mfd(screen* export_left, screen* export_right);

static mfd_modes
	lhs_mfd_mode = MFD_MODE_OFF,
	rhs_mfd_mode = MFD_MODE_OFF,
	cpg_lhs_mfd_mode = MFD_MODE_OFF,
	cpg_rhs_mfd_mode = MFD_MODE_OFF,
	ort_mode = MFD_MODE_OFF;

static int
	mfd_sub_page[4],
	mfd_has_more_sub_pages[4],
	mfd_sub_mode[4];

static void draw_high_action_display (entity* target, int fill_boxes);
static void display_waypoint_information (rgb_colour box_colour, float x_pos, float y_pos);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//VJ 030423 TSD render mod
static rgb_colour
	mfd_colours[20];

#define MFD_COLOUR1 		  		(mfd_colours[0])
#define MFD_COLOUR2 		  		(mfd_colours[1])
#define MFD_COLOUR3 		  		(mfd_colours[2])
#define MFD_COLOUR4	  	  		(mfd_colours[3])
#define MFD_COLOUR5				(mfd_colours[4])
#define MFD_COLOUR6				(mfd_colours[5])
#define MFD_CONTOUR_COLOUR		(mfd_colours[6])
#define MFD_RIVER_COLOUR		(mfd_colours[7])
#define MFD_ROAD_COLOUR			(mfd_colours[8])
#define MFD_BACKGROUND_COLOUR	(mfd_colours[9])
#define MFD_COLOUR7				(mfd_colours[10])
#define MFD_COLOUR8				(mfd_colours[11])
#define MFD_COLOUR_BLUE			(mfd_colours[12])
#define MFD_COLOUR_YELLOW		(mfd_colours[13])
#define MFD_COLOUR_DARK_YELLOW	(mfd_colours[14])
#define MFD_COLOUR_RED			(mfd_colours[15])
#define MFD_COLOUR_CYAN			(mfd_colours[16])
#define MFD_COLOUR_DARK_BLUE	(mfd_colours[17])
#define MFD_COLOUR_DARK_RED		(mfd_colours[18])
#define MFD_CLEAR_COLOUR		(mfd_colours[19])

static rgb_colour
	text_display_colours[2];

#define TEXT_COLOUR1					(text_display_colours[0])
#define TEXT_BACKGROUND_COLOUR	(text_display_colours[1])

static void (*draw_line_func)(float, float, float, float, const rgb_colour) = NULL;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//
// main 2D environment
//
////////////////////////////////////////
//Maverick fix the apache MFD font

#define MFD_WINDOW_X_MIN				(-1.2)
#define MFD_WINDOW_Y_MIN				(-1.2)
#define MFD_WINDOW_X_MAX				(1.200)
#define MFD_WINDOW_Y_MAX				(1.200)

#define MFD_VIEWPORT_SIZE		(512)
#define MFD_TEXTURE_SIZE			(512)

#define ALNUM_DISPLAY_WIDTH   256
#define ALNUM_DISPLAY_HEIGHT   64
//#define MFD_TEXTURE_SIZE			(128)

//#define MFD_VIEWPORT_TEXTURE_X_ORG	(MFD_TEXTURE_SIZE / 2)
//#define MFD_VIEWPORT_TEXTURE_Y_ORG	(MFD_TEXTURE_SIZE / 2)

static env_2d
	*mfd_env;

static float
	mfd_viewport_size,
	mfd_viewport_x_org,
	mfd_viewport_y_org,
	mfd_viewport_x_min,
	mfd_viewport_y_min,
	mfd_viewport_x_max,
	mfd_viewport_y_max;

static int
	mfd_texture_size,
	mfd_viewport_texture_x_org,
	mfd_viewport_texture_y_org;

static float
	i_translate_3d,
	j_translate_3d,
	i_scale_3d,
	j_scale_3d;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define LHS_OVERLAID_MFD_TEXTURE_INDEX (TEXTURE_INDEX_COMANCHE_MFD1)
#define RHS_OVERLAID_MFD_TEXTURE_INDEX (TEXTURE_INDEX_COMANCHE_MFD4)

static screen
	*lhs_mfd_texture_screen,
	*rhs_mfd_texture_screen,
	*cpg_lhs_mfd_texture_screen,
	*cpg_rhs_mfd_texture_screen,
	*ort_texture_screen,
	*lhs_overlaid_mfd_texture_screen,
	*rhs_overlaid_mfd_texture_screen,
	*alnum_display_screen,
	*eo_3d_texture_screen;

static rgb_colour
	off_mfd_colour,
	clear_mfd_colour,
	clear_green_mfd_colour;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//
// TSD and ASE
//
////////////////////////////////////////

#define TSD_ASE_RANGE_5000		((float) 5000.0)
#define TSD_ASE_RANGE_10000	((float) 10000.0)
#define TSD_ASE_RANGE_25000	((float) 25000.0)
#define TSD_ASE_RANGE_50000		((float) 50000.0)

#define TSD_AREA_WIDTH 1.8

static float
	pilot_tsd_ase_range,
	cpg_tsd_ase_range;

enum TSD_DECLUTTER_LEVELS
{
	TSD_DECLUTTER_LEVEL_ALL,
	TSD_DECLUTTER_LEVEL_TARGET,
	TSD_DECLUTTER_LEVEL_NAVIGATION,
	NUM_TSD_DECLUTTER_LEVELS
};

typedef enum TSD_DECLUTTER_LEVELS tsd_declutter_levels;

static tsd_declutter_levels
	pilot_tsd_declutter_level,
	cpg_tsd_declutter_level;

enum TSD_UNDERLAY_LEVELS
{
	TSD_UNDERLAY_NONE,
	TSD_UNDERLAY_MAP,
	TSD_UNDERLAY_TADS
};

typedef enum TSD_UNDERLAY_LEVELS tsd_underlay_levels;

static tsd_underlay_levels
	pilot_tsd_underlay,
	cpg_tsd_underlay;

static unsigned
	pilot_tsd_frozen,
	cpg_tsd_frozen,
	pilot_tsd_centered,
	cpg_tsd_centered,
	pilot_tsd_zoomed,
	cpg_tsd_zoomed,
	pilot_tsd_display_present_position,
	cpg_tsd_display_present_position,
	tsd_tads_underlay_active = FALSE;

static vec3d
	pilot_frozen_tsd_position,
	cpg_frozen_tsd_position;

static float
	pilot_frozen_tsd_heading,
	cpg_frozen_tsd_heading;

#define TSD_THREAT_LINE_FLASH_RATE	(0.1)

static float
	tsd_threat_line_flash_timer;

static int
	tsd_draw_threat_line_status;

#define ASE_THREAT_LINE_FLASH_RATE	(0.1)

static float
	ase_threat_line_flash_timer;

static int
	ase_draw_threat_line_status;

static float
	pitch_ladder_datum_position;

apache_coordinate_points
	*pilot_tsd_show_waypoint_review,
	*cpg_tsd_show_waypoint_review;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_apache_tsd_phase_is_atk(mfd_locations location)
{
	int is_pilot = location <= MFD_LOCATION_PILOT_RHS;
	tsd_declutter_levels tsd_declutter_level = is_pilot ? pilot_tsd_declutter_level : cpg_tsd_declutter_level;

	return tsd_declutter_level == TSD_DECLUTTER_LEVEL_TARGET;
}

void set_apache_tsd_phase_nav(mfd_locations location)
{
	int is_pilot = location <= MFD_LOCATION_PILOT_RHS;

	if (is_pilot)
		pilot_tsd_declutter_level = TSD_DECLUTTER_LEVEL_NAVIGATION;
	else
		cpg_tsd_declutter_level = TSD_DECLUTTER_LEVEL_NAVIGATION;
}

void set_apache_tsd_phase_atk(mfd_locations location)
{
	int is_pilot = location <= MFD_LOCATION_PILOT_RHS;

	if (is_pilot)
		pilot_tsd_declutter_level = TSD_DECLUTTER_LEVEL_TARGET;
	else
		cpg_tsd_declutter_level = TSD_DECLUTTER_LEVEL_TARGET;
}

float get_apache_tsd_range(mfd_locations location)
{
	int is_pilot = location <= MFD_LOCATION_PILOT_RHS;

	return is_pilot ? pilot_tsd_ase_range : cpg_tsd_ase_range;
}

void set_apache_tsd_range(mfd_locations location, float range)
{
	int is_pilot = location <= MFD_LOCATION_PILOT_RHS;

	if (is_pilot)
		pilot_tsd_ase_range = range;
	else
		cpg_tsd_ase_range = range;
}

unsigned get_apache_tsd_is_centered(mfd_locations location)
{
	int is_pilot = location <= MFD_LOCATION_PILOT_RHS;

	return is_pilot ? pilot_tsd_centered : cpg_tsd_centered;
}

void toggle_apache_tsd_is_centered(mfd_locations location)
{
	int is_pilot = location <= MFD_LOCATION_PILOT_RHS;

	if (is_pilot)
		pilot_tsd_centered = !pilot_tsd_centered;
	else
		cpg_tsd_centered = !cpg_tsd_centered;
}

unsigned get_apache_tsd_is_zoomed(mfd_locations location)
{
	int is_pilot = location <= MFD_LOCATION_PILOT_RHS;

	return is_pilot ? pilot_tsd_zoomed : cpg_tsd_zoomed;
}

void toggle_apache_tsd_zoom(mfd_locations location)
{
	int is_pilot = location <= MFD_LOCATION_PILOT_RHS;

	if (is_pilot)
		pilot_tsd_zoomed = !pilot_tsd_zoomed;
	else
		cpg_tsd_zoomed = !cpg_tsd_zoomed;
}

unsigned get_apache_tsd_frozen(mfd_locations location)
{
	int is_pilot = location <= MFD_LOCATION_PILOT_RHS;

	return is_pilot ? pilot_tsd_frozen : cpg_tsd_frozen;
}

void set_apache_tsd_frozen(mfd_locations location, int frozen)
{
	int is_pilot = location <= MFD_LOCATION_PILOT_RHS;

	if (is_pilot)
	{
		pilot_tsd_frozen = frozen;
		if (frozen)
		{
			pilot_frozen_tsd_position.x = current_flight_dynamics->position.x;
			pilot_frozen_tsd_position.y = 0.0;
			pilot_frozen_tsd_position.z = current_flight_dynamics->position.z;
			pilot_frozen_tsd_heading = current_flight_dynamics->heading.value;
		}
	}
	else
	{
		cpg_tsd_frozen = frozen;
		if (frozen)
		{
			cpg_frozen_tsd_position.x = current_flight_dynamics->position.x;
			cpg_frozen_tsd_position.y = 0.0;
			cpg_frozen_tsd_position.z = current_flight_dynamics->position.z;
			cpg_frozen_tsd_heading = current_flight_dynamics->heading.value;
		}
	}
}

void toggle_apache_tsd_frozen(mfd_locations location)
{
	int is_pilot = location <= MFD_LOCATION_PILOT_RHS;

	set_apache_tsd_frozen(location, !(is_pilot ? pilot_tsd_frozen : cpg_tsd_frozen));
}

apache_coordinate_points*  get_apache_tsd_show_waypoint_review(mfd_locations location)
{
	int is_pilot = location <= MFD_LOCATION_PILOT_RHS;

	return is_pilot ? pilot_tsd_show_waypoint_review : cpg_tsd_show_waypoint_review;
}

void set_apache_tsd_show_waypoint_review(mfd_locations location, apache_coordinate_points* wpt)
{
	int is_pilot = location <= MFD_LOCATION_PILOT_RHS;

	if (is_pilot)
		pilot_tsd_show_waypoint_review = wpt;
	else
		cpg_tsd_show_waypoint_review = wpt;
}

unsigned get_apache_tsd_display_present_position_status(mfd_locations location)
{
	int is_pilot = location <= MFD_LOCATION_PILOT_RHS;

	return is_pilot ? pilot_tsd_display_present_position : cpg_tsd_display_present_position;
}

void toggle_apache_tsd_display_present_position_status(mfd_locations location)
{
	int is_pilot = location <= MFD_LOCATION_PILOT_RHS;

	if (is_pilot)
		pilot_tsd_display_present_position = !pilot_tsd_display_present_position;
	else
		cpg_tsd_display_present_position = !cpg_tsd_display_present_position;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static vec3d get_relative_vec_from_tsd_coordinate (float x, float y, float scale)
{
	float x_origin, y_origin;
	float rel_x, rel_y;
	vec3d position;

	// match ground radar origin
	x_origin = 0.0;
	y_origin = -0.65;

	rel_x = x - x_origin;
	rel_y = y - y_origin;

	position.x = rel_x / scale;
	position.y = 0.0;
	position.z = rel_y / scale;  // yes, y coordinates in MFD translates to Z-coordinates in 3D

	return position;
}

static void get_tsd_coordinate_from_relative_vec (vec3d* vec, float* x, float* y, float scale)
{
	float x_origin, y_origin;

	// match ground radar origin
	x_origin = 0.0;
	y_origin = -0.65;

	*x = vec->x * scale;
	*y = vec->z * scale;

	*x += x_origin;
	*y += y_origin;
}

#define RADIUS	(ROOT2 - 0.05)
static void draw_pfz(int pfz_number, int is_nfz, matrix3x3 rotation_matrix, float scale)
{
	vec3d relative_coord;
	float x1, x2, x3, x4, y1, y2, y3, y4, centre_x, centre_y;
	char s[20];
	rgb_colour pfz_colour;
	pfz* current_zone;

	if (is_nfz)
	{
		current_zone = get_nfz(pfz_number);
		pfz_colour = MFD_COLOUR_BLUE;
	}
	else
	{
		current_zone = get_pfz(pfz_number);

		if (pfz_number == current_pfz)
			pfz_colour = MFD_COLOUR_RED;
		else
			pfz_colour = MFD_COLOUR_DARK_RED;
	}

	// get coordinates and draw box
	world_coordinate_to_relative_position(&current_zone->corner1, &relative_coord, rotation_matrix);
	get_tsd_coordinate_from_relative_vec (&relative_coord, &x1, &y1, scale);

	world_coordinate_to_relative_position(&current_zone->corner2, &relative_coord, rotation_matrix);
	get_tsd_coordinate_from_relative_vec (&relative_coord, &x2, &y2, scale);

	world_coordinate_to_relative_position(&current_zone->corner3, &relative_coord, rotation_matrix);
	get_tsd_coordinate_from_relative_vec (&relative_coord, &x3, &y3, scale);

	world_coordinate_to_relative_position(&current_zone->corner4, &relative_coord, rotation_matrix);
	get_tsd_coordinate_from_relative_vec (&relative_coord, &x4, &y4, scale);

	draw_2d_line(x1, y1, x2, y2, pfz_colour);
	draw_2d_line(x2, y2, x3, y3, pfz_colour);
	draw_2d_line(x3, y3, x4, y4, pfz_colour);
	draw_2d_line(x4, y4, x1, y1, pfz_colour);

	// PFZ label
	set_mono_font_colour(pfz_colour);
	set_mono_font_type (MONO_FONT_TYPE_6X10);

	if (is_nfz)
		sprintf(s, "NF%d", pfz_number+1);
	else
		sprintf(s, "PF%d", pfz_number+1);

	centre_x = (x1 + x3) * 0.5;
	centre_y = (y1 + y3) * 0.5;

	set_2d_mono_font_position (centre_x, centre_y);
	set_mono_font_rel_position (-0.5 * get_mono_font_string_width(s), -4.0);

	print_mono_font_string (s);
}

static void draw_pfzs(void)
{
	int i;
	matrix3x3 rotation_matrix;
	float scale;

	if (get_local_entity_int_value (get_pilot_entity (), INT_TYPE_CREW_ROLE) == CREW_ROLE_PILOT)
		scale = RADIUS / pilot_tsd_ase_range;
	else
		scale = RADIUS / cpg_tsd_ase_range;

	get_3d_transformation_matrix(rotation_matrix, -current_flight_dynamics->heading.value, 0.0, 0.0);

	for (i=0; i < next_free_nfz; i++)
		draw_pfz(i, TRUE, rotation_matrix, scale);

	for (i=0; i < next_free_pfz; i++)
		if (i != current_pfz)  // draw current PFZ last
			draw_pfz(i, FALSE, rotation_matrix, scale);

	if (current_pfz != NO_PFZ)
		draw_pfz(current_pfz, FALSE, rotation_matrix, scale);
}


void create_apache_pfz(int is_nfz)
{
	matrix3x3 rotation_matrix;
	vec3d relative_position;
	vec3d position1, position2, position3, position4;
	float scale;

	if (get_local_entity_int_value (get_pilot_entity (), INT_TYPE_CREW_ROLE) == CREW_ROLE_PILOT)
		scale = RADIUS / pilot_tsd_ase_range;
	else
		scale = RADIUS / cpg_tsd_ase_range;

	// don't create too small pfzs
	if (fabs(pointer_position_x - clicked_position_x) < 0.05
		|| fabs(pointer_position_y - clicked_position_y) < 0.05)
		return;

	get_3d_transformation_matrix(rotation_matrix, current_flight_dynamics->heading.value, 0.0, 0.0);

	relative_position = get_relative_vec_from_tsd_coordinate(pointer_position_x, pointer_position_y, scale);
	relative_position_to_world_coordinate(&relative_position, &position1, rotation_matrix);

	relative_position = get_relative_vec_from_tsd_coordinate(pointer_position_x, clicked_position_y, scale);
	relative_position_to_world_coordinate(&relative_position, &position2, rotation_matrix);

	relative_position = get_relative_vec_from_tsd_coordinate(clicked_position_x, clicked_position_y, scale);
	relative_position_to_world_coordinate(&relative_position, &position3, rotation_matrix);

	relative_position = get_relative_vec_from_tsd_coordinate(clicked_position_x, pointer_position_y, scale);
	relative_position_to_world_coordinate(&relative_position, &position4, rotation_matrix);

	if (is_nfz)
		add_nfz(&position1, &position2, &position3, &position4);
	else
	{
		add_pfz(&position1, &position2, &position3, &position4);
		current_pfz = next_free_pfz - 1;
	}

	if (!ground_radar_is_active())
		update_common_radar (TRUE);  // to make suretarget list is correct with new restrictions
}
#undef RADIUS


////////////////////////////////////////
//
// ENGINE
//
////////////////////////////////////////

//static void draw_box(float x1_c, float y1_c, float x2_c, float y2_c, int filled, rgb_colour colour);
//static void draw_bordered_box(float x1_c, float y1_c, float x2_c, float y2_c, rgb_colour fill_colour, rgb_colour border_colour);


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int pointer_active (void)
{
	if (lhs_mfd_mode != MFD_MODE_TSD && rhs_mfd_mode != MFD_MODE_TSD)
		return FALSE;

	if ((command_line_mouse_look == MOUSELOOK_ON
		 || command_line_mouse_look == MOUSELOOK_INTERNAL)
		&& !query_TIR_active())
	{
		return FALSE;
	}

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_apache_mfd (void)
{
	initialise_apache_pushbuttons();

	if (command_line_dynamics_engine_startup)
	{
		select_apache_mfd_mode (MFD_MODE_OFF, MFD_LOCATION_LHS);
		select_apache_mfd_mode (MFD_MODE_OFF, MFD_LOCATION_RHS);
	}
	else
	{
		select_apache_mfd_mode (MFD_MODE_ENGINE, MFD_LOCATION_LHS);
//		select_apache_mfd_mode (MFD_MODE_TSD, MFD_LOCATION_RHS);
//		select_apache_mfd_mode (MFD_MODE_MENU, MFD_LOCATION_RHS);
//		select_apache_mfd_mode (MFD_MODE_FLIGHT, MFD_LOCATION_LHS);
		select_apache_mfd_mode (MFD_MODE_WEAPON_GUN, MFD_LOCATION_RHS);
	}

	select_apache_mfd_mode (MFD_MODE_WEAPON, MFD_LOCATION_CPG_LHS);
	select_apache_mfd_mode (MFD_MODE_TSD, MFD_LOCATION_CPG_RHS);
	select_apache_mfd_mode (MFD_MODE_FLIR, MFD_LOCATION_ORT);

	pilot_tsd_ase_range = TSD_ASE_RANGE_5000;
	cpg_tsd_ase_range = TSD_ASE_RANGE_5000;

	pilot_tsd_declutter_level = TSD_DECLUTTER_LEVEL_ALL;
	cpg_tsd_declutter_level = TSD_DECLUTTER_LEVEL_TARGET;

	pilot_tsd_underlay = TSD_UNDERLAY_NONE;
	cpg_tsd_underlay = TSD_UNDERLAY_NONE;

	pilot_tsd_centered = cpg_tsd_centered = FALSE;
	pilot_tsd_zoomed = cpg_tsd_zoomed = FALSE;
	pilot_tsd_display_present_position = cpg_tsd_display_present_position = FALSE;

	pilot_tsd_show_waypoint_review = NULL;
	cpg_tsd_show_waypoint_review = NULL;

	current_pfz = NO_PFZ;
	next_free_pfz = 0;
	next_free_nfz = 0;

	tads_digital_zoom_level = TADS_DIGITAL_ZOOM_NORMAL;

	tsd_threat_line_flash_timer = TSD_THREAT_LINE_FLASH_RATE;
	tsd_draw_threat_line_status = 0;

	ase_threat_line_flash_timer = ASE_THREAT_LINE_FLASH_RATE;
	ase_draw_threat_line_status = 0;

	pitch_ladder_datum_position = 0.0;

	mfd_env = create_2d_environment ();

	mfd_viewport_size = MFD_VIEWPORT_SIZE;
	mfd_texture_size = MFD_TEXTURE_SIZE;
	eo_3d_texture_screen = very_large_eo_3d_texture_screen;
	draw_line_func = draw_2d_half_thick_line;

	mfd_viewport_texture_x_org = mfd_texture_size / 2;
	mfd_viewport_texture_y_org = mfd_texture_size / 2;

	lhs_mfd_texture_screen = create_system_texture_screen (mfd_texture_size, mfd_texture_size, TEXTURE_INDEX_AVCKPT_DISPLAY_LHS_MFD, TEXTURE_TYPE_NOALPHA);
	rhs_mfd_texture_screen = create_system_texture_screen (mfd_texture_size, mfd_texture_size, TEXTURE_INDEX_AVCKPT_DISPLAY_RHS_MFD, TEXTURE_TYPE_NOALPHA);
	cpg_lhs_mfd_texture_screen = create_system_texture_screen (mfd_texture_size, mfd_texture_size, TEXTURE_INDEX_AVCKPT_DISPLAY_CPG_LHS_MFD, TEXTURE_TYPE_NOALPHA);
	cpg_rhs_mfd_texture_screen = create_system_texture_screen (mfd_texture_size, mfd_texture_size, TEXTURE_INDEX_AVCKPT_DISPLAY_CPG_RHS_MFD, TEXTURE_TYPE_NOALPHA);
	ort_texture_screen = create_system_texture_screen (mfd_texture_size, mfd_texture_size, TEXTURE_INDEX_AVCKPT_DISPLAY_ORT, TEXTURE_TYPE_SCREEN);

	lhs_overlaid_mfd_texture_screen = create_system_texture_screen (mfd_texture_size, mfd_texture_size, LHS_OVERLAID_MFD_TEXTURE_INDEX, TEXTURE_TYPE_SINGLEALPHA);
	rhs_overlaid_mfd_texture_screen = create_system_texture_screen (mfd_texture_size, mfd_texture_size, RHS_OVERLAID_MFD_TEXTURE_INDEX, TEXTURE_TYPE_SINGLEALPHA);

	alnum_display_screen = create_system_texture_screen(ALNUM_DISPLAY_WIDTH, ALNUM_DISPLAY_HEIGHT, TEXTURE_INDEX_AVCKPT_ALNUM_DISPLAY, TEXTURE_TYPE_NOALPHA);

	set_rgb_colour (MFD_COLOUR1,   0, 255,  0, 255);
	set_rgb_colour (MFD_COLOUR2,   0, 200,   0, 255);
	set_rgb_colour (MFD_COLOUR3,   0, 176,   0, 255);
	set_rgb_colour (MFD_COLOUR4,   0, 151,   0, 255);
	set_rgb_colour (MFD_COLOUR5,   0, 149,   0, 255);
	set_rgb_colour (MFD_COLOUR6,  40,  68,  56, 255);

	set_rgb_colour (clear_green_mfd_colour, 5, 12, 5, 255);
	set_rgb_colour (off_mfd_colour, 0, 8, 0, 255);

	//set_rgb_colour(clear_mfd_colour, 0, 255, 0, 0);
	clear_mfd_colour=clear_green_mfd_colour;

	//VJ 030423 TSd render mod
	set_rgb_colour (MFD_COLOUR1,              0, 255,   0, 255);
	set_rgb_colour (MFD_COLOUR2,              0, 200,   0, 255);
	set_rgb_colour (MFD_COLOUR3,              0, 176,   0, 255);
	set_rgb_colour (MFD_COLOUR4,              0, 151,   0, 255);
	set_rgb_colour (MFD_COLOUR5,              0, 128,   0, 255);
	set_rgb_colour (MFD_COLOUR6,              0,  68,   0, 255);
	set_rgb_colour (MFD_CONTOUR_COLOUR,     255, 100,   0, 255);
	set_rgb_colour (MFD_RIVER_COLOUR,        50,  75, 225, 255);
	set_rgb_colour (MFD_ROAD_COLOUR,        255, 200,   0, 255);
	set_rgb_colour (MFD_BACKGROUND_COLOUR,   15,  24,  16, 255);
	set_rgb_colour (MFD_CLEAR_COLOUR,         0,   0,   0,   0);

	if (command_line_colour_mfd)
	{
		set_rgb_colour (MFD_COLOUR_BLUE,          60, 160, 255,  255);
		set_rgb_colour (MFD_COLOUR_DARK_BLUE,	   0,   0,  96,  255);
		set_rgb_colour (MFD_COLOUR_YELLOW,       230, 230,  40,  255);
		set_rgb_colour (MFD_COLOUR_DARK_YELLOW,  165, 165,  30,  255);
		set_rgb_colour (MFD_COLOUR_RED,          220,  40,  30,  255);
		set_rgb_colour (MFD_COLOUR_DARK_RED,	 148,  32,   0,  255);
		set_rgb_colour (MFD_COLOUR_CYAN,          60, 255, 230,  255);
	}
	else
	{
		MFD_COLOUR_BLUE = MFD_COLOUR1;
		MFD_COLOUR_DARK_BLUE = MFD_COLOUR5;
		MFD_COLOUR_YELLOW = MFD_COLOUR1;
		MFD_COLOUR_RED = MFD_COLOUR1;
		MFD_COLOUR_DARK_RED = MFD_COLOUR5;
		MFD_COLOUR_CYAN = MFD_COLOUR1;
	}

	set_rgb_colour (TEXT_COLOUR1,           254, 204,   1, 255);
	set_rgb_colour (TEXT_BACKGROUND_COLOUR,  66,  35,  11, 255);

	Initialise_TSD_render_terrain();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_apache_mfd (void)
{
	destroy_2d_environment (mfd_env);

	destroy_screen (lhs_mfd_texture_screen);
	destroy_screen (rhs_mfd_texture_screen);
	destroy_screen (cpg_lhs_mfd_texture_screen);
	destroy_screen (cpg_rhs_mfd_texture_screen);
	destroy_screen (ort_texture_screen);

	destroy_screen (lhs_overlaid_mfd_texture_screen);
	destroy_screen (rhs_overlaid_mfd_texture_screen);

	destroy_screen (alnum_display_screen);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_apache_mfd_mode (mfd_modes mfd_mode, mfd_locations location)
{
	ASSERT ((mfd_mode >= MFD_MODE_OFF) && (mfd_mode < NUM_MFD_MODES));

	ASSERT (mfd_mode != MFD_MODE_LLLTV);

	if (get_local_entity_int_value (get_pilot_entity (), INT_TYPE_CREW_ROLE) == CREW_ROLE_CO_PILOT)
	{
		if (location == MFD_LOCATION_PILOT_LHS)
			location = MFD_LOCATION_CPG_LHS;
		else if (location == MFD_LOCATION_PILOT_RHS)
			location = MFD_LOCATION_CPG_RHS;
	}

	ASSERT ((location == MFD_LOCATION_PILOT_LHS) || (location == MFD_LOCATION_PILOT_RHS)
			|| (location == MFD_LOCATION_CPG_LHS) || (location == MFD_LOCATION_CPG_RHS)
			|| (location == MFD_LOCATION_ORT));

	// don't let both a MFD show TADS, and have TADS as TSD underlay for pilot (co-pilot can't have TADS as underlay)
	if (((location == MFD_LOCATION_PILOT_LHS) || (location == MFD_LOCATION_PILOT_RHS))
		&&
		(mfd_mode == MFD_MODE_DVO
		 || mfd_mode == MFD_MODE_DTV
		 || mfd_mode == MFD_MODE_FLIR)
		&& pilot_tsd_underlay == TSD_UNDERLAY_TADS)
	{
		pilot_tsd_underlay = TSD_UNDERLAY_NONE;
	}

	if (location == MFD_LOCATION_PILOT_LHS)
	{
		if ((mfd_mode == MFD_MODE_DAMAGED) && (lhs_mfd_mode == MFD_MODE_OFF) || lhs_mfd_mode == mfd_mode)
			return;

		if (apache_damage.lh_mfd && mfd_mode != MFD_MODE_OFF)
			mfd_mode = MFD_MODE_DAMAGED;

		lhs_mfd_mode = mfd_mode;
	}
	else if (location == MFD_LOCATION_PILOT_RHS)
	{
		if ((mfd_mode == MFD_MODE_DAMAGED) && (rhs_mfd_mode == MFD_MODE_OFF) || rhs_mfd_mode == mfd_mode)
			return;

		if (apache_damage.rh_mfd && mfd_mode != MFD_MODE_OFF)
			mfd_mode = MFD_MODE_DAMAGED;

		rhs_mfd_mode = mfd_mode;
	}
	else if (location == MFD_LOCATION_CPG_LHS)
	{
		if ((mfd_mode == MFD_MODE_DAMAGED) && (cpg_lhs_mfd_mode == MFD_MODE_OFF) || cpg_lhs_mfd_mode == mfd_mode)
			return;

		if (apache_damage.cpg_lh_mfd && mfd_mode != MFD_MODE_OFF)
			mfd_mode = MFD_MODE_DAMAGED;

		cpg_lhs_mfd_mode = mfd_mode;
	}
	else if (location == MFD_LOCATION_CPG_RHS)
	{
		if ((mfd_mode == MFD_MODE_DAMAGED) && (cpg_rhs_mfd_mode == MFD_MODE_OFF) || cpg_rhs_mfd_mode == mfd_mode)
			return;

		if (apache_damage.cpg_rh_mfd && mfd_mode != MFD_MODE_OFF)
			mfd_mode = MFD_MODE_DAMAGED;

		cpg_rhs_mfd_mode = mfd_mode;
	}
	else if (location == MFD_LOCATION_ORT)
	{
		if ((mfd_mode == MFD_MODE_DAMAGED) && (ort_mode == MFD_MODE_OFF))
			return;

		ort_mode = mfd_mode;
	}
	else
		debug_fatal("Unknown MFD location");


	switch (mfd_mode)
	{
	case MFD_MODE_TSD:
		set_apache_tsd_frozen(location, FALSE);
		break;
	case MFD_MODE_TSD_RTE:
	case MFD_MODE_TSD_WPT:
	case MFD_MODE_TSD_SHOW:
	case MFD_MODE_TSD_ZONE:
		set_apache_tsd_frozen(location, TRUE);
		break;
	}


	if (location != MFD_LOCATION_ORT)
	{
		setup_apache_mfd_buttons(mfd_mode, location, FALSE);
		mfd_sub_mode[location] = 0;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// LAYOUT GRID
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_layout_grid (void)
{
	float
		x,
		y;

	if (display_mfd_layout_grid)
	{
		for (x = -1.0; x <= 1.0; x += 0.1)
		{
			draw_2d_line (x, -1.0, x, 1.0, sys_col_red);
		}

		for (y = -1.0; y <= 1.0; y += 0.1)
		{
			draw_2d_line (-1.0, y, 1.0, y, sys_col_red);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// DAMAGED
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_damaged_mfd (void)
{
	int
		count,
		max_lines,
		i;

	rgb_colour
		col;

	float
		x_centre,
		x_delta,
		x_left,
		x_right,
		y;

	col.r = 0;
	col.g = 0;
	col.b = 0;
	col.a = 255;

	max_lines = 150;

	for (count = 0; count < max_lines; count++)
	{
		convert_float_to_int (frand1 () * 127.0, &i);

		col.g = i + 128;

		x_centre = sfrand1 ();

		x_delta = (frand1 () * 0.5) + 0.25;

		x_left = x_centre - x_delta;

		x_right = x_centre + x_delta;

		y = sfrand1 ();

		draw_2d_line (x_left, y, x_right, y, col);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// HEADING SCALE
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_heading_scale(int is_tads, float pos_y)
{
	float
		heading = get_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_HEADING),
		heading_width_ratio,
		heading_tick_x_spacing,
		x_adjust_single,
		x_adjust_double,
		y_adjust,
		tick_10_deg_top,
		tick_10_deg_bottom,
		tick_30_deg_top,
		tick_30_deg_bottom,
		tick_datum_top,
		tick_datum_bottom,
		mfd_vp_x_min,
		mfd_vp_x_max,
		x,
		heading_step_10,
		mod_heading_step_10;

	int
		loop,
		int_heading_step_10,
		tick_type;

	char
		buffer[16];

	//
	// sort large and small mfd differences
	//

	set_mono_font_type (MONO_FONT_TYPE_10X16);

	heading_width_ratio		= 0.4;

	heading_tick_x_spacing	= 0.4 / 6.5;

	x_adjust_single  			= -5.0;
	x_adjust_double  			= -10.0;
	y_adjust			  		= -13.0;

	tick_10_deg_top			= pos_y - 0.040;
	tick_10_deg_bottom  		= pos_y - 0.075;
	tick_30_deg_top	  		= pos_y;
	tick_30_deg_bottom  		= pos_y - 0.075;
	tick_datum_top		  		= pos_y - 0.075 - 0.010;
	tick_datum_bottom	  		= pos_y - 0.075 - 0.010 - 0.060;

	//
	// adjust 2D environment for heading scale clipping
	//
	heading_width_ratio = 0.5;
	set_2d_window (mfd_env, MFD_WINDOW_X_MIN * heading_width_ratio, MFD_WINDOW_Y_MIN, MFD_WINDOW_X_MAX * heading_width_ratio, MFD_WINDOW_Y_MAX);

	mfd_vp_x_min = mfd_viewport_x_org - (mfd_viewport_size * (heading_width_ratio * 0.5));

	mfd_vp_x_max = mfd_viewport_x_org + (mfd_viewport_size * (heading_width_ratio * 0.5)) - 0.001;

	set_2d_viewport (mfd_env, mfd_vp_x_min, mfd_viewport_y_min, mfd_vp_x_max, mfd_viewport_y_max);

	//
	// draw heading datum tick
	//

	draw_2d_half_thick_line (0.0, tick_datum_top, 0.0, tick_datum_bottom, MFD_COLOUR1);

	//
	// draw command heading carat
	//

	{
		float
			bearing = 0.0f,
			command_heading = 0.0f;

		if (is_tads)
		{
			float elevation;
			get_eo_azimuth_and_elevation(&command_heading, &elevation);
		}
		else if (!apache_damage.navigation_computer)
		{
			entity
				*wp;

			wp = get_local_entity_current_waypoint (get_gunship_entity ());

			if (wp)
			{
				vec3d
					*gunship_position,
					waypoint_position;

				float
					dx,
					dz,
					bearing;

				gunship_position = get_local_entity_vec3d_ptr (get_gunship_entity (), VEC3D_TYPE_POSITION);

				get_waypoint_display_position (get_gunship_entity (), wp, &waypoint_position);

				dx = waypoint_position.x - gunship_position->x;
				dz = waypoint_position.z - gunship_position->z;

				bearing = atan2 (dx, dz);

			}

			command_heading = bearing - heading;

			if (command_heading > rad (180.0))
				command_heading -= rad (360.0);
			else if (command_heading < rad (-180.0))
				command_heading += rad (360.0);
		}

		command_heading = bound (command_heading, rad (-90.0), rad (90.0));
		draw_2d_mono_sprite (command_heading_carat, (deg(command_heading) * heading_tick_x_spacing * 0.1), tick_datum_top, MFD_COLOUR1);

		get_opposite_crew_head_vector(&command_heading, &bearing);
		draw_2d_mono_sprite(crew_sensor_heading_carat, (deg(command_heading) * heading_tick_x_spacing * 0.1), tick_datum_top, MFD_COLOUR1);
	}

	//
	// draw heading scale
	//

	heading_step_10 = deg (heading * 0.1);

	int_heading_step_10 = (int) heading_step_10;

	mod_heading_step_10 = heading_step_10 - (float) int_heading_step_10;

	int_heading_step_10 -= 10;

	if (int_heading_step_10 < 0)
	{
		int_heading_step_10 += 36;
	}

	// tick type:-
	//
	//		0 = long tick (30 degs)
	//		1 = short tick (10 degs)
	//		2 = short tick (20 degs)

	tick_type = int_heading_step_10 % 3;

	x = - (10.0 + mod_heading_step_10) * heading_tick_x_spacing;

	for (loop = 0; loop <= 20; loop++)
	{
		if (tick_type == 0)
		{
			draw_2d_half_thick_line (x, tick_30_deg_top, x, tick_30_deg_bottom, MFD_COLOUR1);

			set_2d_mono_font_position (x, tick_30_deg_top);

			switch (int_heading_step_10)
			{
				////////////////////////////////////////
				case 0:
				////////////////////////////////////////
				{
					set_mono_font_rel_position (x_adjust_single, y_adjust);

					print_mono_font_char ('N');

					break;
				}
				////////////////////////////////////////
				case 9:
				////////////////////////////////////////
				{
					set_mono_font_rel_position (x_adjust_single, y_adjust);

					print_mono_font_char ('E');

					break;
				}
				////////////////////////////////////////
				case 18:
				////////////////////////////////////////
				{
					set_mono_font_rel_position (x_adjust_single, y_adjust);

					print_mono_font_char ('S');

					break;
				}
				////////////////////////////////////////
				case 27:
				////////////////////////////////////////
				{
					set_mono_font_rel_position (x_adjust_single, y_adjust);

					print_mono_font_char ('W');

					break;
				}
				////////////////////////////////////////
				default:
				////////////////////////////////////////
				{
					if (int_heading_step_10 < 10)
					{
						set_mono_font_rel_position (x_adjust_single, y_adjust);

						print_mono_font_char ('0' + int_heading_step_10);
					}
					else
					{
						set_mono_font_rel_position (x_adjust_double, y_adjust);

						print_mono_font_char ('0' + int_heading_step_10 / 10);

						print_mono_font_char ('0' + int_heading_step_10 % 10);
					}

					break;
				}
			}
		}
		else
		{
			draw_2d_line (x, tick_10_deg_top, x, tick_10_deg_bottom, MFD_COLOUR1);
		}

		int_heading_step_10 = (++int_heading_step_10 == 36) ? 0 : int_heading_step_10;

		tick_type = (++tick_type == 3) ? 0 : tick_type;

		x += heading_tick_x_spacing;
	}

	//
	// restore 2D environment
	//

	set_2d_window (mfd_env, MFD_WINDOW_X_MIN, MFD_WINDOW_Y_MIN, MFD_WINDOW_X_MAX, MFD_WINDOW_Y_MAX);

	set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

	draw_2d_box(-0.11, tick_30_deg_top, 0.11, tick_30_deg_top + 0.1, TRUE, FALSE, clear_mfd_colour);

	heading = deg(heading);
	if (heading < 0.5)
		heading += 360.0;
	sprintf(buffer, "%03.0f", heading);

	set_mono_font_type (MONO_FONT_TYPE_14X21);
	set_2d_mono_font_position (0.0, tick_30_deg_top);
	set_mono_font_rel_position (-0.5 * get_mono_font_string_width(buffer), -20.0);
	print_mono_font_string(buffer);

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// FIELD OF REGARD AND VIEW BOXES
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if 0
static void draw_field_of_regard_and_view_boxes (void)
{
	float
		y_pos = -0.945,
		x,
		y;

	draw_2d_box(-0.3, y_pos, 0.3, y_pos - 0.225, FALSE, TRUE, MFD_COLOUR1);

	draw_2d_line ( 0.0000, y_pos,  0.0000, y_pos - 0.020, MFD_COLOUR1);
	draw_2d_line (-0.2250, y_pos, -0.2250, y_pos - 0.020, MFD_COLOUR1);
	draw_2d_line ( 0.2250, y_pos,  0.2250, y_pos - 0.020, MFD_COLOUR1);

	draw_2d_line ( 0.0000, y_pos - 0.205,  0.0000, y_pos - 0.225, MFD_COLOUR1);
	draw_2d_line (-0.2250, y_pos - 0.205, -0.2250, y_pos - 0.225, MFD_COLOUR1);
	draw_2d_line ( 0.2250, y_pos - 0.205,  0.2250, y_pos - 0.225, MFD_COLOUR1);

	draw_2d_line (-0.3000, y_pos - 0.075, -0.2800, y_pos - 0.075, MFD_COLOUR1);
	draw_2d_line ( 0.3000, y_pos - 0.075,  0.2800, y_pos - 0.075, MFD_COLOUR1);

	x = eo_azimuth / eo_max_azimuth * 0.3;
	y = (eo_elevation / eo_min_elevation * -0.15) + y_pos - 0.075;

	draw_2d_box(x - 0.04, y - 0.03, x + 0.04, y + 0.03, FALSE, TRUE, MFD_COLOUR1);
}
#endif
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// GROUND AND AIR RADAR
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void display_radar_scan_range (float scan_range, int ground_radar)
{
//VJ 030807 radar range adjustable
	char
		s[8];

	float
		width,
		y_adjust;

	sprintf(s, "%.0f", scan_range/1000);

	width = get_mono_font_string_width (s);

	y_adjust = 8.0;
	set_2d_mono_font_position (1.12, 1.06);
	set_mono_font_rel_position (-width, y_adjust);
	print_mono_font_string (s);

	draw_2d_box(0.92, 0.93, 1.13, 1.03, FALSE, TRUE, MFD_COLOUR1);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void display_radar_target_details (entity *target, float target_range, radar_params *radar)
{
	const char
		*s;
	char
		buffer[200];

	float
		y_adjust,
		width;

	ASSERT (radar);

	if (apache_damage.radar)
	{
		return;
	}

	y_adjust = -12.0;

	//
	// name
	//

	s = get_target_display_name (target, buffer, TRUE);

	if (s)
	{
		set_2d_mono_font_position (-0.8, -1.0);

		set_mono_font_rel_position (1.0, y_adjust);

		print_mono_font_string (s);
	}

	if (target)
	{
		//
		// range
		//

		if ((target_range < 1000.0) && (!apache_damage.laser_designator))
		{
			sprintf (buffer, "%dm", (int) target_range);
		}
		else
		{
			sprintf (buffer, "%.1fKm", target_range * (1.0 / 1000.0));
		}

		width = get_mono_font_string_width (buffer);

		set_2d_mono_font_position (0.8, -1.0);

		set_mono_font_rel_position (-width, y_adjust);

		print_mono_font_string (buffer);

		//
		// no line of sight
		//

		if (!get_local_entity_int_value (target, INT_TYPE_GUNSHIP_RADAR_LOS_CLEAR))
		{
			y_adjust = -25.0;

			width = get_mono_font_string_width ("NO LOS");

			set_2d_mono_font_position (0.8, -1.0);

			set_mono_font_rel_position (-width, y_adjust);

			print_mono_font_string ("NO LOS");
		}
	}

	//
	// auto
	//

	if (radar->auto_target)
	{
		y_adjust = 18.0;

		set_2d_mono_font_position (-0.9, 1.0);

		set_mono_font_rel_position (1.0, y_adjust);

		print_mono_font_string ("AUTO");
	}

	//
	// locked
	//

	if (radar->target_locked)
	{
		y_adjust = -25.0;

		set_2d_mono_font_position (-0.8, -1.0);

		set_mono_font_rel_position (1.0, y_adjust);

		print_mono_font_string ("LOCKED");
	}
// Jabberwock 031107 Designated targets

	target = get_local_entity_parent (get_gunship_entity (), LIST_TYPE_TARGET);

	if (target && get_local_entity_parent (target, LIST_TYPE_DESIGNATED_TARGET))
	{
		y_adjust = -25.0;

		width = get_mono_font_string_width ("MARKED");

		set_2d_mono_font_position (1.0, -1.0);

		set_mono_font_rel_position (-width -1.0, y_adjust);

		print_mono_font_string ("MARKED");
	}
// Jabberwock 031107 ends
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_radar_arc (float arc_size, float radius, rgb_colour colour)
{
	int
		num_segments;

	float
		theta,
		sin_theta,
		cos_theta,
		x1,
		y1,
		x2,
		y2;

	num_segments = (int) (arc_size * (1.0f / APACHE_RADAR_SCAN_ARC_SEGMENT_SIZE));

	if (num_segments > 0)
	{
		theta = arc_size * 0.5;

		sine_cosine (theta, &sin_theta, &cos_theta);

		x1 = -radius * sin_theta;
		y1 = radius * cos_theta;

		while (num_segments--)
		{
			theta -= APACHE_RADAR_SCAN_ARC_SEGMENT_SIZE;

			sine_cosine (theta, &sin_theta, &cos_theta);

			x2 = -radius * sin_theta;
			y2 = radius * cos_theta;

			draw_2d_half_thick_line (x1, y1, x2, y2, colour);

			x1 = x2;
			y1 = y2;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//VJ 030423 TSD render mod, added display_on_tsd

void draw_apache_radar_target_symbol(entity* target, float dx, float dy, int los_clear, int moving, rgb_colour target_symbol_colour, rgb_colour target_symbol_background_colour, rgb_colour bg_colour)
{
	target_symbol_types
		target_symbol_type;

	target_symbol_type = get_local_entity_int_value (target, INT_TYPE_TARGET_SYMBOL_TYPE);
	ASSERT ((target_symbol_type >= 0) && (target_symbol_type < NUM_TARGET_SYMBOL_TYPES));

	if (los_clear)
	{
		if (target_symbol_background_colour.a > 0)
			draw_2d_mono_sprite (large_display_target_symbols_los_mask[target_symbol_type], dx, dy, target_symbol_background_colour);
		draw_2d_mono_sprite (large_display_target_symbols_los[target_symbol_type], dx, dy, target_symbol_colour);

		if (moving)
		{
			if (target_symbol_background_colour.a > 0)
				draw_2d_mono_sprite (large_display_moving_target_symbol_mask, dx, dy, target_symbol_background_colour);
			draw_2d_mono_sprite (large_display_moving_target_symbol, dx, dy, bg_colour);
		}
	}
	else
	{
		if (target_symbol_background_colour.a > 0)
			draw_2d_mono_sprite (large_display_target_symbols_no_los_mask[target_symbol_type], dx, dy, target_symbol_background_colour);
		draw_2d_mono_sprite (large_display_target_symbols_no_los[target_symbol_type], dx, dy, target_symbol_colour);
	}
}

static void internal_draw_radar_target_symbol(
		entity* target,
		float dx,
		float dy,
		float scale,
		int selected_target,
		int los_clear,
		int display_on_tsd,
		int display_on_ase,
		rgb_colour target_symbol_colour,
		rgb_colour target_symbol_background_colour)
{
	entity_sides
		source_side;
	entity
		*source;

	float target_true_velocity;

	source = get_gunship_entity ();
	source_side = get_local_entity_int_value (source, INT_TYPE_SIDE);

	// TODO use contact information, not actual movement
	target_true_velocity = get_local_entity_vec3d_magnitude (target, VEC3D_TYPE_MOTION_VECTOR);
	draw_apache_radar_target_symbol(target, dx, dy, los_clear, target_true_velocity > 2.0, target_symbol_colour, target_symbol_background_colour, MFD_BACKGROUND_COLOUR);

	if (display_on_ase)
	{
		// display threat radar ID below symbol
		char* id = get_threat_id_number(target);

		if (id)
		{
			float x_offset = get_mono_font_string_width(id) * -0.5;

			set_mono_font_colour(target_symbol_colour);
			set_2d_mono_font_position (dx, dy);
			set_mono_font_rel_position (x_offset, 10.0);

			print_mono_font_string(id);
		}
	}

	if (selected_target)
	{
		draw_2d_mono_sprite (large_display_target_symbol_selected_target_mask, dx, dy, target_symbol_background_colour);
		draw_2d_mono_sprite (large_display_target_symbol_selected_target, dx, dy, target_symbol_colour);
	}
}

static void draw_tsd_target_symbol (entity *target, vec3d *source_position, float scale, int selected_target, int display_on_tsd, int display_on_ase)
{
	vec3d
		*target_position = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

	float
		dx,
		dy;

	rgb_colour
		fg_col,
		bg_col;

	int
		los_clear = get_local_entity_int_value (target, INT_TYPE_GUNSHIP_RADAR_LOS_CLEAR);

	// figure out correct colours to use
	if (display_on_tsd)
	{
		fg_col = MFD_COLOUR_RED;
		bg_col = MFD_COLOUR_DARK_RED;
	}
	else
	{
		ASSERT(display_on_ase);

		if (get_local_entity_int_value (target, INT_TYPE_THREAT_TYPE) == THREAT_TYPE_AAA)
		{
			fg_col = MFD_COLOUR_YELLOW;
			bg_col = MFD_COLOUR_DARK_YELLOW;
		}
		else
		{
			fg_col = MFD_COLOUR_RED;
			bg_col = MFD_COLOUR_DARK_RED;
		}
	}

	dx = (target_position->x - source_position->x) * scale;
	dy = (target_position->z - source_position->z) * scale;

	internal_draw_radar_target_symbol(target, dx, dy, scale, selected_target, los_clear, display_on_tsd, display_on_ase, fg_col, bg_col);
}

static void draw_radar_contact_symbol(radar_contact* contact, float scale, int selected_target)
{
	float
		dx,
		dy;

	dx = contact->display_position.x * scale;
	dy = contact->display_position.y * scale;

	internal_draw_radar_target_symbol(contact->en, dx, dy, scale, selected_target, contact->age > 1, FALSE, FALSE, MFD_COLOUR3, MFD_COLOUR5);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// GROUND RADAR
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_ground_radar_clutter (entity *target, vec3d *source_position, float scale)
{
	float
		dx,
		dy,
		radius;

	vec3d
		*target_position,
		*bounding_box_min,
		*bounding_box_max;

	ASSERT (target);

	ASSERT (source_position);

	ASSERT (get_local_entity_type (target) == ENTITY_TYPE_CITY);

	target_position = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

	dx = (target_position->x - source_position->x) * scale;
	dy = (target_position->z - source_position->z) * scale;

	bounding_box_min = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_BOUNDING_BOX_MIN);
	bounding_box_max = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_BOUNDING_BOX_MAX);

	radius = get_approx_2d_range (bounding_box_min, bounding_box_max);

	//
	// radius check to ignore oil pipelines and overly large city blocks
	//

	if (radius < 2000.0)
	{
		radius = max (50.0, radius);

		draw_2d_hatched_circle (dx, dy, radius * scale, MFD_COLOUR5);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_radar_elevation_scale(radar_params* radar)
{
	const float top = -0.8, bottom = -1.1;
	float relative_elev = (radar->elevation - MIN_RADAR_ELEVATION_ANGLE) / (MAX_RADAR_ELEVATION_ANGLE - MIN_RADAR_ELEVATION_ANGLE);
	float elev_y = relative_elev * (top - bottom) + bottom;
	float y_step = (bottom - top) / 8.0, y;

	draw_2d_half_thick_line(-1.15, top, -1.1, top, MFD_COLOUR1);
	draw_2d_half_thick_line(-1.15, bottom, -1.1, bottom, MFD_COLOUR1);

	for (y = top + y_step; y > bottom + 0.001; y += y_step)
		draw_2d_half_thick_line(-1.15, y, -1.13, y, MFD_COLOUR1);

	draw_2d_mono_sprite(small_left_carret, -1.13, elev_y, MFD_COLOUR1);
}

static void draw_ground_radar_mfd (int sub_mode)
{
	float
		centre_y,
		u,
		v,
		source_heading,
		radius,
		scale;

	entity
		*source,
		*target,
		*selected_target;

	vec3d
		*source_position;

	radar_modes
		radar_mode = get_radar_mode();

	radar_params
		*radar = get_current_radar_params();

	int
		radar_zoomed = get_radar_zoomed();

	source = get_gunship_entity ();

	source_position = get_local_entity_vec3d_ptr (source, VEC3D_TYPE_POSITION);

	source_heading = get_local_entity_float_value (source, FLOAT_TYPE_HEADING);

	if (radar_mode == RADAR_MODE_TPM)
		radius = 1.05;
	else
		radius = 1.55;

	if (radar_zoomed)
		scale = 0.004;  // 1/250 ==  250m in each axis direction from selected target
	else
		scale = radius / radar->scan_range;

	selected_target = get_local_entity_parent (source, LIST_TYPE_TARGET);

	if (radar_mode == RADAR_MODE_TPM)
		centre_y = -0.85;
	else
		centre_y = radar_zoomed ? 0.0 : -0.9;

	get_2d_float_screen_coordinates (0.0, centre_y, &u, &v);
	u -= mfd_viewport_x_min;
	v -= mfd_viewport_y_min;

	////////////////////////////////////////
	//
	// draw radar clutter
	//
	////////////////////////////////////////

	if (!apache_damage.radar)
	{
		if (radar_mode == RADAR_MODE_RMAP || radar_mode == RADAR_MODE_TPM)
			draw_terrain_radar_returns(source_position, centre_y, scale);


		set_hatched_pattern (radar_clutter_hatch_pattern);

		set_2d_viewport_origin (mfd_env, u, v);

		set_2d_window_rotation (mfd_env, source_heading);

		target = get_local_entity_first_child (source, LIST_TYPE_GUNSHIP_TARGET);

		while (target)
		{
			if (get_local_entity_int_value (target, INT_TYPE_GROUND_RADAR_CLUTTER))
			{
				draw_ground_radar_clutter (target, source_position, scale);
			}

			target = get_local_entity_child_succ (target, LIST_TYPE_GUNSHIP_TARGET);
		}

		set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

		set_2d_window_rotation (mfd_env, 0.0);
	}

	////////////////////////////////////////
	//
	// text
	//
	////////////////////////////////////////

	set_mono_font_colour (MFD_COLOUR1);

	set_mono_font_type (MONO_FONT_TYPE_14X21);

	//
	// declutter status
	//
#if 0
	y_adjust = 5.0;

	set_2d_mono_font_position (-0.9, 1.0);

	set_mono_font_rel_position (1.0, y_adjust);

	switch (ground_radar.target_priority_type)
	{
		case TARGET_PRIORITY_UNKNOWN:
		{
			print_mono_font_string ("ALL");

			break;
		}
		case TARGET_PRIORITY_LOW:
		{
			print_mono_font_string ("LOW");

			break;
		}
		case TARGET_PRIORITY_MEDIUM:
		{
			print_mono_font_string ("MEDIUM");

			break;
		}
		case TARGET_PRIORITY_HIGH:
		{
			print_mono_font_string ("HIGH");

			break;
		}
		// Jabberwock 031107 Designated targets
		case TARGET_PRIORITY_DESIGNATED:
		{
			print_mono_font_string ("MARK");

			break;
		}
		// Jabberwock 031107 ends
	}

	if (ground_radar.sweep_mode == RADAR_SWEEP_MODE_SINGLE_ACTIVE || ground_radar.sweep_mode == RADAR_SWEEP_MODE_SINGLE_INACTIVE)
	{
		set_2d_mono_font_position (-0.9, 0.8);
		print_mono_font_string ("SGL");
	}
#endif
	//
	// scan range
	//

	display_radar_scan_range (ground_radar.scan_range, TRUE);

	draw_radar_elevation_scale(radar);

	////////////////////////////////////////
	//
	// draw heading scale
	//
	////////////////////////////////////////

	draw_heading_scale(FALSE, 1.05);

	////////////////////////////////////////
	//
	// draw field of regard and view boxes
	//
	////////////////////////////////////////

	target = get_local_entity_parent (get_gunship_entity (), LIST_TYPE_TARGET);
	draw_apache_high_action_display(RENDER_TARGET_FCR, MFD_COLOUR1);

	////////////////////////////////////////
	//
	// line graphics
	//
	////////////////////////////////////////

	set_2d_viewport_origin (mfd_env, u, v);

	//
	// max scan limits
	//

	if (!radar_zoomed)
	{
		int angle;

		if (radar_mode != RADAR_MODE_TPM)
		{
			float arc_size = APACHE_RADAR_SCAN_ARC_SIZE_90;

			draw_2d_half_thick_line (-0.075, 0.075, -radius * ONE_OVER_ROOT2, radius * ONE_OVER_ROOT2, MFD_COLOUR4);

			draw_2d_half_thick_line (0.075, 0.075, radius * ONE_OVER_ROOT2, radius * ONE_OVER_ROOT2, MFD_COLOUR4);

			draw_radar_arc(arc_size, radius, MFD_COLOUR4);
		}
		else
		{
			draw_2d_line (0.0, 0.05, 0.0, radius, MFD_COLOUR4);
		}

		//
		// scan limits and range markers
		//

		set_2d_window_rotation (mfd_env, -radar->scan_datum);

		if (radar_mode != RADAR_MODE_TPM)
		{
			draw_radar_arc (radar->scan_arc_size, radius * 0.25, MFD_COLOUR4);
			draw_radar_arc (radar->scan_arc_size, radius * 0.50, MFD_COLOUR4);
			draw_radar_arc (radar->scan_arc_size, radius * 0.75, MFD_COLOUR4);
		}
		else
		{
			draw_radar_arc (radar->scan_arc_size, radius * 100 / radar->scan_range, MFD_COLOUR4);
			draw_radar_arc (radar->scan_arc_size, radius * 1000 / radar->scan_range, MFD_COLOUR4);
			draw_radar_arc (radar->scan_arc_size, radius * 2000 / radar->scan_range, MFD_COLOUR4);
		}

		draw_radar_arc (radar->scan_arc_size, radius, MFD_COLOUR1);

		set_2d_window_rotation (mfd_env, -(radar->scan_datum - (radar->scan_arc_size * 0.5)));
		draw_2d_half_thick_line (0.0, 0.075, 0.0, radius, MFD_COLOUR1);

		if (radar_mode != RADAR_MODE_TPM)
		{
			draw_2d_half_thick_line (0.0, radius * 0.875, 0.02, radius * 0.875, MFD_COLOUR4);
			draw_2d_half_thick_line (0.0, radius * 0.625, 0.02, radius * 0.625, MFD_COLOUR4);
			draw_2d_half_thick_line (0.0, radius * 0.375, 0.02, radius * 0.375, MFD_COLOUR4);
			draw_2d_half_thick_line (0.0, radius * 0.125, 0.02, radius * 0.125, MFD_COLOUR4);
		}

		set_2d_window_rotation (mfd_env, -(radar->scan_datum + (radar->scan_arc_size * 0.5)));
		draw_2d_half_thick_line (0.0, 0.075, 0.0, radius, MFD_COLOUR1);

		if (radar_mode != RADAR_MODE_TPM)
		{
			draw_2d_half_thick_line (0.0, radius * 0.875, -0.02, radius * 0.875, MFD_COLOUR4);
			draw_2d_half_thick_line (0.0, radius * 0.625, -0.02, radius * 0.625, MFD_COLOUR4);
			draw_2d_half_thick_line (0.0, radius * 0.375, -0.02, radius * 0.375, MFD_COLOUR4);
			draw_2d_half_thick_line (0.0, radius * 0.125, -0.02, radius * 0.125, MFD_COLOUR4);
		}

		for (angle = -30; angle <= 30; angle += 10)
		{
			set_2d_window_rotation (mfd_env, rad(angle));
			draw_2d_half_thick_line (0.0, radius, 0.0, radius - 0.02, MFD_COLOUR4);
		}

		//
		// sweep
		//

		if (get_radar_active())
		{
			float y1 = 0.1, y2 = radius;

			if (radar->bar_scan > 1)
			{
				if (radar->bar & 1)
					y2 = radius * 0.5;
				else
					y1 = radius * 0.5;
			}

			set_2d_window_rotation (mfd_env, -(radar->scan_datum + radar->sweep_offset));
			draw_2d_half_thick_line (0.0, y1, 0.0, y2, MFD_COLOUR1);
		}

		set_2d_window_rotation (mfd_env, 0.0);
	}

	set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);



	////////////////////////////////////////
	//
	// targets
	//
	////////////////////////////////////////

	set_2d_viewport_origin (mfd_env, u, v);

	if (!apache_damage.radar)
	{
		unsigned ncontacts = 0;
		radar_contact* contact = get_radar_contacts(&ncontacts);
		radar_contact* selected = NULL;
		float sqr_range_limit = get_current_radar_params()->scan_range;

		sqr_range_limit *= sqr_range_limit;

		for (; ncontacts; ncontacts--, contact++)
		{
			float contact_range_sqr = (contact->display_position.x * contact->display_position.x) + (contact->display_position.y * contact->display_position.y);

			// don't draw contacts outside of range
			if (contact_range_sqr > sqr_range_limit)
				continue;

//			if (get_time_acceleration() != TIME_ACCELERATION_PAUSE)
//				debug_log("tgt: %s ncontacts: %d, [%d]: %.0f, %.0f", get_sub_type_name(contact->en), ncontacts, get_local_entity_int_value(contact->en, INT_TYPE_GUNSHIP_RADAR_TARGET_INDEX), contact->display_position.x, contact->display_position.y);
			if (contact->en == selected_target)
				selected = contact;
			else // if (get_target_matches_ground_radar_declutter_criteria (contact->en))  // TODO
				draw_radar_contact_symbol(contact, scale, FALSE);
		}

		// draw selected target last
		if (selected)
			draw_radar_contact_symbol(selected, scale, TRUE);

		//		set_2d_window_rotation (mfd_env, source_heading);
	}

	set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

	////////////////////////////////////////
	//
	// damaged
	//
	////////////////////////////////////////

	if (apache_damage.radar)
	{
		draw_2d_line (-0.5, -0.5,  0.5, 0.5, MFD_COLOUR1);
		draw_2d_line ( 0.5, -0.5, -0.5, 0.5, MFD_COLOUR1);
	}

	// Util page on/off symbols
	if (sub_mode > 0 && sub_mode < 4)
	{
		if (get_fcr_powered() || fcr_being_powered_up())
		{
			draw_2d_mono_sprite(on_indicator_mask, -0.91, 0.13, MFD_COLOUR5);
			draw_2d_mono_sprite(on_indicator, -0.91, 0.13, MFD_COLOUR1);
		}
		else
		{
			draw_2d_mono_sprite(off_indicator_mask, -0.91, 0.13, MFD_COLOUR5);
			draw_2d_mono_sprite(off_indicator, -0.91, 0.13, MFD_COLOUR1);
		}

		if (get_rfi_powered())
		{
			draw_2d_mono_sprite(on_indicator_mask, -0.91, 0.43, MFD_COLOUR5);
			draw_2d_mono_sprite(on_indicator, -0.91, 0.43, MFD_COLOUR1);
		}
		else
		{
			draw_2d_mono_sprite(off_indicator_mask, -0.91, 0.43, MFD_COLOUR5);
			draw_2d_mono_sprite(off_indicator, -0.91, 0.43, MFD_COLOUR1);
		}
	}

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// AIR RADAR
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define RADIUS	(0.8)
#define TICK1	(RADIUS * 0.90)
#define TICK2	(RADIUS * 0.99)

static void draw_air_radar_mfd (void)
{
	entity_sides
		source_side;

	float
		source_heading,
		scale,
		target_range,
		y_adjust;

	entity
		*source,
		*target;

	vec3d
		*source_position,
		*target_position;

	source = get_gunship_entity ();

	source_position = get_local_entity_vec3d_ptr (source, VEC3D_TYPE_POSITION);

	source_side = get_local_entity_int_value (source, INT_TYPE_SIDE);

	////////////////////////////////////////
	//
	// text
	//
	////////////////////////////////////////

	set_mono_font_colour (MFD_COLOUR1);

	set_mono_font_type (MONO_FONT_TYPE_7X12);

	//
	// declutter status
	//

	y_adjust = 5.0;

	set_2d_mono_font_position (-0.8, 1.0);

	set_mono_font_rel_position (1.0, y_adjust);

	if (air_radar.show_allied_targets)
	{
		print_mono_font_string ("ALL");
	}
	else
	{
		print_mono_font_string ("ENEMY");
	}

/*
	if (air_radar.sweep_mode == RADAR_SWEEP_MODE_SINGLE_ACTIVE || air_radar.sweep_mode == RADAR_SWEEP_MODE_SINGLE_INACTIVE)
	{
		set_2d_mono_font_position (-0.8, 0.8);
		set_mono_font_rel_position (1.0, y_adjust);
		print_mono_font_string ("SGL");
	}
*/
	//
	// scan range
	//

	display_radar_scan_range (air_radar.scan_range, FALSE);

	//
	// target details
	//

	if (target_acquisition_system == TARGET_ACQUISITION_SYSTEM_AIR_RADAR)
	{
		target = get_local_entity_parent (source, LIST_TYPE_TARGET);

		if (target)
		{
			target_position = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

			target_range = get_3d_range (source_position, target_position);
		}
		else
		{
			target_range = 0.0;
		}

		display_radar_target_details (target, target_range, &air_radar);
	}

	////////////////////////////////////////
	//
	// line graphics
	//
	////////////////////////////////////////

	//
	// datum markers
	//

	draw_2d_line ( 0.00,  TICK1,  0.00,  TICK2, MFD_COLOUR4);
	draw_2d_line ( TICK1,  0.00,  TICK2,  0.00, MFD_COLOUR4);
	draw_2d_line ( 0.00, -TICK1,  0.00, -TICK2, MFD_COLOUR4);
	draw_2d_line (-TICK1,  0.00, -TICK2,  0.00, MFD_COLOUR4);

	//
	// range markers
	//

	draw_2d_circle (0.0, 0.0, RADIUS * 0.25, MFD_COLOUR4);
	draw_2d_circle (0.0, 0.0, RADIUS * 0.50, MFD_COLOUR4);
	draw_2d_circle (0.0, 0.0, RADIUS * 0.75, MFD_COLOUR4);

	draw_radar_elevation_scale(&air_radar);

	//
	// scan limits
	//

	if (air_radar.scan_arc_size == APACHE_RADAR_SCAN_ARC_SIZE_360)
	{
		draw_2d_circle (0.0, 0.0, RADIUS, MFD_COLOUR1);
	}
	else
	{
		draw_2d_circle (0.0, 0.0, RADIUS, MFD_COLOUR4);

		set_2d_window_rotation (mfd_env, -air_radar.scan_datum);

		draw_radar_arc (air_radar.scan_arc_size, RADIUS, MFD_COLOUR1);

		draw_2d_line (0.0, 0.0, 0.0, RADIUS, MFD_COLOUR1);

		set_2d_window_rotation (mfd_env, -(air_radar.scan_datum - (air_radar.scan_arc_size * 0.5)));

		draw_2d_line (0.0, 0.0, 0.0, RADIUS, MFD_COLOUR1);

		set_2d_window_rotation (mfd_env, -(air_radar.scan_datum + (air_radar.scan_arc_size * 0.5)));

		draw_2d_line (0.0, 0.0, 0.0, RADIUS, MFD_COLOUR1);
	}

	//
	// sweep
	//

	if (air_radar_is_active())
	{
		set_2d_window_rotation (mfd_env, -(air_radar.scan_datum + air_radar.sweep_offset));

		draw_2d_line (0.0, 0.0, 0.0, RADIUS, MFD_COLOUR1);
	}

	set_2d_window_rotation (mfd_env, 0.0);

	////////////////////////////////////////
	//
	// draw targets
	//
	////////////////////////////////////////

	if (!apache_damage.radar && air_radar_is_active())
	{
		source_heading = get_local_entity_float_value (source, FLOAT_TYPE_HEADING);

		set_2d_window_rotation (mfd_env, source_heading);

		scale = RADIUS / air_radar.scan_range;

		target = get_local_entity_first_child (source, LIST_TYPE_GUNSHIP_TARGET);

		while (target)
		{
			if (get_gunship_target_valid_for_air_radar (target))
			{
				if (get_target_matches_air_radar_declutter_criteria (target, source_side))
				{
					draw_tsd_target_symbol (target, source_position, scale, FALSE, FALSE, FALSE);
				}
			}

			target = get_local_entity_child_succ (target, LIST_TYPE_GUNSHIP_TARGET);
		}

		//
		// draw selected target last
		//

		if (target_acquisition_system == TARGET_ACQUISITION_SYSTEM_AIR_RADAR)
		{
			target = get_local_entity_parent (source, LIST_TYPE_TARGET);

			if (target)
			{
				draw_tsd_target_symbol (target, source_position, scale, TRUE, FALSE, FALSE);
			}
		}

		set_2d_window_rotation (mfd_env, 0.0);
	}

	////////////////////////////////////////
	//
	// damaged
	//
	////////////////////////////////////////

	if (apache_damage.radar)
	{
		draw_2d_line (-0.5, -0.5,  0.5, 0.5, MFD_COLOUR1);
		draw_2d_line ( 0.5, -0.5, -0.5, 0.5, MFD_COLOUR1);
	}
}

#undef RADIUS
#undef TICK1
#undef TICK2

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// EO
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//
// FLIR
//
////////////////////////////////////////

static display_3d_light_levels
	flir_light_levels[WEATHERMODE_LAST][NUM_DAY_SEGMENT_TYPES] =
	{
		// WEATHERMODE_INVALID
		{
			DISPLAY_3D_LIGHT_LEVEL_HIGH,		// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_LIGHT_LEVEL_HIGH,		// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_LIGHT_LEVEL_HIGH,		// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_LIGHT_LEVEL_HIGH,		// DAY_SEGMENT_TYPE_NIGHT
		},
		// WEATHERMODE_DRY
		{
			DISPLAY_3D_LIGHT_LEVEL_HIGH,		// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_LIGHT_LEVEL_HIGH,		// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_LIGHT_LEVEL_HIGH,		// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_LIGHT_LEVEL_HIGH,		// DAY_SEGMENT_TYPE_NIGHT
		},
		// WEATHERMODE_LIGHT_RAIN
		{
			DISPLAY_3D_LIGHT_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_LIGHT_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_LIGHT_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_LIGHT_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_NIGHT
		},
		// WEATHERMODE_HEAVY_RAIN
		{
			DISPLAY_3D_LIGHT_LEVEL_LOW,		// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_LIGHT_LEVEL_LOW,		// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_LIGHT_LEVEL_LOW,		// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_LIGHT_LEVEL_LOW,		// DAY_SEGMENT_TYPE_NIGHT
		},
		// WEATHERMODE_SNOW
		{
			DISPLAY_3D_LIGHT_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_LIGHT_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_LIGHT_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_LIGHT_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_NIGHT
		},
	};

static display_3d_noise_levels
	flir_noise_levels[WEATHERMODE_LAST][NUM_DAY_SEGMENT_TYPES] =
	{
		// WEATHERMODE_INVALID
		{
			DISPLAY_3D_NOISE_LEVEL_LOW,		// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_NOISE_LEVEL_LOW,		// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_NOISE_LEVEL_LOW,		// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_NOISE_LEVEL_LOW,		// DAY_SEGMENT_TYPE_NIGHT
		},
		// WEATHERMODE_DRY
		{
			DISPLAY_3D_NOISE_LEVEL_LOW,		// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_NOISE_LEVEL_LOW,		// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_NOISE_LEVEL_LOW,		// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_NOISE_LEVEL_LOW,		// DAY_SEGMENT_TYPE_NIGHT
		},
		// WEATHERMODE_LIGHT_RAIN
		{
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_NIGHT
		},
		// WEATHERMODE_HEAVY_RAIN
		{
			DISPLAY_3D_NOISE_LEVEL_HIGH,		// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_NOISE_LEVEL_HIGH,		// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_NOISE_LEVEL_HIGH,		// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_NOISE_LEVEL_HIGH,		// DAY_SEGMENT_TYPE_NIGHT
		},
		// WEATHERMODE_SNOW
		{
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_NIGHT
		},
	};

////////////////////////////////////////
//
// DTV
//
////////////////////////////////////////

static display_3d_light_levels
	dtv_light_levels[WEATHERMODE_LAST][NUM_DAY_SEGMENT_TYPES] =
	{
		// WEATHERMODE_INVALID
		{
			DISPLAY_3D_LIGHT_LEVEL_HIGH,		// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_LIGHT_LEVEL_HIGH,		// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_LIGHT_LEVEL_HIGH,		// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_LIGHT_LEVEL_HIGH,		// DAY_SEGMENT_TYPE_NIGHT
		},
		// WEATHERMODE_DRY
		{
			DISPLAY_3D_LIGHT_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_LIGHT_LEVEL_HIGH,	 	// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_LIGHT_LEVEL_MEDIUM, 	// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_LIGHT_LEVEL_LOW,		// DAY_SEGMENT_TYPE_NIGHT
		},
		// WEATHERMODE_LIGHT_RAIN
		{
			DISPLAY_3D_LIGHT_LEVEL_LOW,		// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_LIGHT_LEVEL_MEDIUM, 	// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_LIGHT_LEVEL_LOW, 		// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_LIGHT_LEVEL_LOW,		// DAY_SEGMENT_TYPE_NIGHT
		},
		// WEATHERMODE_HEAVY_RAIN
		{
			DISPLAY_3D_LIGHT_LEVEL_LOW,		// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_LIGHT_LEVEL_LOW, 		// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_LIGHT_LEVEL_LOW,		// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_LIGHT_LEVEL_LOW,		// DAY_SEGMENT_TYPE_NIGHT
		},
		// WEATHERMODE_SNOW
		{
			DISPLAY_3D_LIGHT_LEVEL_LOW,		// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_LIGHT_LEVEL_MEDIUM, 	// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_LIGHT_LEVEL_LOW, 		// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_LIGHT_LEVEL_LOW,		// DAY_SEGMENT_TYPE_NIGHT
		},
	};

static display_3d_noise_levels
	dtv_noise_levels[WEATHERMODE_LAST][NUM_DAY_SEGMENT_TYPES] =
	{
		// WEATHERMODE_INVALID
		{
			DISPLAY_3D_NOISE_LEVEL_LOW,		// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_NOISE_LEVEL_LOW,		// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_NOISE_LEVEL_LOW,		// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_NOISE_LEVEL_LOW,		// DAY_SEGMENT_TYPE_NIGHT
		},
		// WEATHERMODE_DRY
		{
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_NOISE_LEVEL_LOW,		// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_NOISE_LEVEL_HIGH,		// DAY_SEGMENT_TYPE_NIGHT
		},
		// WEATHERMODE_LIGHT_RAIN
		{
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_NOISE_LEVEL_LOW,		// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_NOISE_LEVEL_HIGH,		// DAY_SEGMENT_TYPE_NIGHT
		},
		// WEATHERMODE_HEAVY_RAIN
		{
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_NOISE_LEVEL_LOW,		// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_NOISE_LEVEL_HIGH,		// DAY_SEGMENT_TYPE_NIGHT
		},
		// WEATHERMODE_SNOW
		{
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_NOISE_LEVEL_LOW,		// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_NOISE_LEVEL_HIGH,		// DAY_SEGMENT_TYPE_NIGHT
		},
	};

////////////////////////////////////////
//
// DVO
//
////////////////////////////////////////

static display_3d_light_levels
	dvo_light_levels[WEATHERMODE_LAST][NUM_DAY_SEGMENT_TYPES] =
	{
		// WEATHERMODE_INVALID
		{
			DISPLAY_3D_LIGHT_LEVEL_HIGH,		// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_LIGHT_LEVEL_HIGH,		// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_LIGHT_LEVEL_HIGH,		// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_LIGHT_LEVEL_HIGH,		// DAY_SEGMENT_TYPE_NIGHT
		},
		// WEATHERMODE_DRY
		{
			DISPLAY_3D_LIGHT_LEVEL_LOW,		// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_LIGHT_LEVEL_HIGH,	 	// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_LIGHT_LEVEL_LOW, 		// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_LIGHT_LEVEL_LOW,		// DAY_SEGMENT_TYPE_NIGHT
		},
		// WEATHERMODE_LIGHT_RAIN
		{
			DISPLAY_3D_LIGHT_LEVEL_LOW,		// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_LIGHT_LEVEL_MEDIUM, 	// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_LIGHT_LEVEL_LOW, 		// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_LIGHT_LEVEL_LOW,		// DAY_SEGMENT_TYPE_NIGHT
		},
		// WEATHERMODE_HEAVY_RAIN
		{
			DISPLAY_3D_LIGHT_LEVEL_LOW,		// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_LIGHT_LEVEL_LOW, 		// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_LIGHT_LEVEL_LOW,		// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_LIGHT_LEVEL_LOW,		// DAY_SEGMENT_TYPE_NIGHT
		},
		// WEATHERMODE_SNOW
		{
			DISPLAY_3D_LIGHT_LEVEL_LOW,		// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_LIGHT_LEVEL_MEDIUM, 	// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_LIGHT_LEVEL_LOW, 		// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_LIGHT_LEVEL_LOW,		// DAY_SEGMENT_TYPE_NIGHT
		},
	};

static display_3d_noise_levels
	dvo_noise_levels[WEATHERMODE_LAST][NUM_DAY_SEGMENT_TYPES] =
	{
		// WEATHERMODE_INVALID
		{
			DISPLAY_3D_NOISE_LEVEL_LOW,		// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_NOISE_LEVEL_LOW,		// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_NOISE_LEVEL_LOW,		// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_NOISE_LEVEL_LOW,		// DAY_SEGMENT_TYPE_NIGHT
		},
		// WEATHERMODE_DRY
		{
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_NOISE_LEVEL_LOW,		// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_NOISE_LEVEL_HIGH,		// DAY_SEGMENT_TYPE_NIGHT
		},
		// WEATHERMODE_LIGHT_RAIN
		{
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_NOISE_LEVEL_LOW,		// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_NOISE_LEVEL_HIGH,		// DAY_SEGMENT_TYPE_NIGHT
		},
		// WEATHERMODE_HEAVY_RAIN
		{
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_NOISE_LEVEL_LOW,		// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_NOISE_LEVEL_HIGH,		// DAY_SEGMENT_TYPE_NIGHT
		},
		// WEATHERMODE_SNOW
		{
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DAWN
			DISPLAY_3D_NOISE_LEVEL_LOW,		// DAY_SEGMENT_TYPE_DAY
			DISPLAY_3D_NOISE_LEVEL_MEDIUM,	// DAY_SEGMENT_TYPE_DUSK
			DISPLAY_3D_NOISE_LEVEL_HIGH,		// DAY_SEGMENT_TYPE_NIGHT
		},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

tads_digital_zoom_levels get_tads_digital_zoom_level(void)
{
	return tads_digital_zoom_level;
}

void set_tads_digital_zoom_level(tads_digital_zoom_levels zoom)
{
	tads_digital_zoom_level = zoom;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define ONE_OVER_SQRT2 0.707106

static float get_eo_sensor_fov(eo_fov_levels fov_level, target_acquisition_systems system, BOOL is_ort)
{
	float fov = 10.0;

	switch (fov_level)
	{
		case EO_FOV_ZOOM:
		{
			if (system == TARGET_ACQUISITION_SYSTEM_FLIR)
				fov = 1.6 * ONE_OVER_SQRT2;
			else  // DTV
				fov = 0.45 * ONE_OVER_SQRT2;

			break;
		}
		case EO_FOV_NARROW:
		{
			if (system == TARGET_ACQUISITION_SYSTEM_FLIR)
				fov = 3.1 * ONE_OVER_SQRT2;
			else  // DTV
				fov = 0.9 * ONE_OVER_SQRT2;

			break;
		}
		case EO_FOV_MEDIUM:
		{
			if (system == TARGET_ACQUISITION_SYSTEM_FLIR)
				fov = 10.1 * ONE_OVER_SQRT2;
			else  // DTV or DVO
				fov = 4.0 * ONE_OVER_SQRT2;

			break;
		}
		case EO_FOV_WIDE:
		{
			if (system == TARGET_ACQUISITION_SYSTEM_FLIR)
				fov = 50.0 * ONE_OVER_SQRT2;
			else  // DVO
				fov = 18.0 * ONE_OVER_SQRT2;

			break;
		}
		default:
		{
			debug_fatal ("Invalid field of view = %d", fov_level);

			break;
		}
	}

	if (!is_ort)
		fov *= tads_digital_zoom_fov[tads_digital_zoom_level];

	return fov;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_eo_view_params(target_acquisition_systems system, int x_min, int y_min, int x_max, int y_max, float xfov, float yfov)
{
	display_3d_light_levels
		light_level;

	display_3d_noise_levels
		noise_level;

	vec3d
		*position;

	weathermodes
		weather_mode;

	day_segment_types
		day_segment_type;

	int
		tint;

	position = get_local_entity_vec3d_ptr (get_gunship_entity (), VEC3D_TYPE_POSITION);

	weather_mode = get_simple_session_weather_at_point (position);
	ASSERT ((weather_mode > WEATHERMODE_INVALID) && (weather_mode < WEATHERMODE_LAST));

	day_segment_type = get_local_entity_int_value (get_session_entity (), INT_TYPE_DAY_SEGMENT_TYPE);
	ASSERT ((day_segment_type >= 0) && (day_segment_type < NUM_DAY_SEGMENT_TYPES));

	switch (system)
	{
		case TARGET_ACQUISITION_SYSTEM_FLIR:
		{
			light_level = flir_light_levels[weather_mode][day_segment_type];
			noise_level = flir_noise_levels[weather_mode][day_segment_type];
			tint = DISPLAY_3D_TINT_GREEN;

			break;
		}
		case TARGET_ACQUISITION_SYSTEM_DTV:
		{
			light_level = dtv_light_levels[weather_mode][day_segment_type];
			noise_level = dtv_noise_levels[weather_mode][day_segment_type];
			tint = DISPLAY_3D_TINT_GREEN_VISUAL;

			break;
		}
		case TARGET_ACQUISITION_SYSTEM_DVO:
		{
			light_level = dvo_light_levels[weather_mode][day_segment_type];
			noise_level = dvo_noise_levels[weather_mode][day_segment_type];
			tint = DISPLAY_3D_TINT_CLEAR;

			break;
		}
		default:
		{
			debug_fatal ("Invalid target acquisition system = %d", system);

			break;
		}
	}

	set_main_3d_params (tint, light_level, noise_level, x_min, y_min, x_max, y_max, xfov, yfov);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_apache_virtual_cockpit_ort_view (int x_min, int x_max)
{
	float
		fov;

	eo_params*
		eo;

	target_acquisition_systems
		system;

	rgb_colour
		black;

	int
		damaged = FALSE;

	switch (get_mfd_mode_for_eo_sensor())
	{
	default:
	case MFD_MODE_FLIR:
		eo = &apache_flir;
		system = TARGET_ACQUISITION_SYSTEM_FLIR;
		damaged = apache_damage.flir;
		break;
	case MFD_MODE_DTV:
		eo = &apache_dtv;
		system = TARGET_ACQUISITION_SYSTEM_DTV;
		damaged = apache_damage.dtv;
		break;
	case MFD_MODE_DVO:
		eo = &apache_dvo;
		system = TARGET_ACQUISITION_SYSTEM_DVO;
		damaged = apache_damage.dvo;
		break;
	}

	black.r = 0;
	black.g = 0;
	black.b = 0;
	black.a = 255;

	// clear background, since we won't be drawing the 3D view over the entire screen
	set_block(0, 0, full_screen_x_max, full_screen_y_max, black);

	if (!damaged)
	{
		fov = rad(get_eo_sensor_fov(eo->field_of_view, system, TRUE));

		set_eo_view_params(system, x_min, full_screen_y_min, x_max, full_screen_y_max, fov, fov);

		draw_eo_3d_scene = TRUE;
		draw_main_3d_scene (&eo_vp);
		draw_eo_3d_scene = FALSE;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if 0
static void draw_3d_eo_display (eo_params *eo, target_acquisition_systems system, mfd_locations location)
{
	float
		fov = 18.0;

	ASSERT (eo);

	fov = rad(get_eo_sensor_fov(eo, system));

	set_eo_view_params(system, mfd_viewport_x_min - 1.5, mfd_viewport_y_min - 1.5, MFD_VIEWPORT_SIZE, MFD_VIEWPORT_SIZE, fov, fov);

	draw_eo_3d_scene = TRUE;
	draw_main_3d_scene (&eo_vp);
	draw_eo_3d_scene = FALSE;
}
#endif
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_3d_eo_display_on_texture (eo_params *eo, target_acquisition_systems system)
{
	float
		fov;

	display_3d_light_levels
		light_level;

	display_3d_noise_levels
		noise_level;

	vec3d
		*position;

	weathermodes
		weather_mode;

	day_segment_types
		day_segment_type;

	int
		tint;

	ASSERT (eo);

	ASSERT (eo_3d_texture_screen);

	ASSERT (d3d_can_render_to_texture);

	fov = get_eo_sensor_fov(eo->field_of_view, system, FALSE);

	position = get_local_entity_vec3d_ptr (get_gunship_entity (), VEC3D_TYPE_POSITION);

	weather_mode = get_simple_session_weather_at_point (position);

	ASSERT ((weather_mode > WEATHERMODE_INVALID) && (weather_mode < WEATHERMODE_LAST));

	day_segment_type = get_local_entity_int_value (get_session_entity (), INT_TYPE_DAY_SEGMENT_TYPE);

	ASSERT ((day_segment_type >= 0) && (day_segment_type < NUM_DAY_SEGMENT_TYPES));

	switch (system)
	{
		case TARGET_ACQUISITION_SYSTEM_FLIR:
		{
			light_level = flir_light_levels[weather_mode][day_segment_type];

			noise_level = flir_noise_levels[weather_mode][day_segment_type];

			tint = DISPLAY_3D_TINT_GREEN;

			break;
		}
		case TARGET_ACQUISITION_SYSTEM_DTV:
		{
			light_level = dtv_light_levels[weather_mode][day_segment_type];

			noise_level = dtv_noise_levels[weather_mode][day_segment_type];

			tint = DISPLAY_3D_TINT_GREEN_VISUAL;

			break;
		}
		case TARGET_ACQUISITION_SYSTEM_DVO:
		{
			light_level = dvo_light_levels[weather_mode][day_segment_type];

			noise_level = dvo_noise_levels[weather_mode][day_segment_type];

			tint = DISPLAY_3D_TINT_GREEN_VISUAL;

			break;
		}
		default:
		{
			debug_fatal ("Invalid target acquisition system = %d", system);

			break;
		}
	}

	set_3d_render_target (eo_3d_texture_screen);

	set_active_screen (eo_3d_texture_screen);

	set_main_3d_params (tint, light_level, noise_level, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_size, mfd_viewport_size, rad (fov), rad(fov));

	draw_eo_3d_scene = TRUE;

	draw_main_3d_scene (&eo_vp);

	draw_eo_3d_scene = FALSE;

	finalise_3d_render_target_texture (eo_3d_texture_screen);

	set_3d_render_target (video_screen);

	set_active_screen (video_screen);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_overlaid_3d_eo_display (eo_params *eo, target_acquisition_systems system, float x, float y, float size)
{
	float
		zoom;

	display_3d_light_levels
		light_level;

	display_3d_noise_levels
		noise_level;

	vec3d
		*position;

	weathermodes
		weather_mode;

	day_segment_types
		day_segment_type;

	ASSERT (eo);

	switch (eo->field_of_view)
	{
		case EO_FOV_ZOOM:
		{
			zoom = 1.0 / 128.0;

			break;
		}
		case EO_FOV_NARROW:
		{
			zoom = 1.0 / 32.0;

			break;
		}
		case EO_FOV_MEDIUM:
		{
			zoom = 1.0 / 8.0;

			break;
		}
		case EO_FOV_WIDE:
		{
			zoom = 1.0;

			break;
		}
		default:
		{
			debug_fatal ("Invalid field of view = %d", eo->field_of_view);

			break;
		}
	}

	position = get_local_entity_vec3d_ptr (get_gunship_entity (), VEC3D_TYPE_POSITION);

	weather_mode = get_simple_session_weather_at_point (position);

	ASSERT ((weather_mode > WEATHERMODE_INVALID) && (weather_mode < WEATHERMODE_LAST));

	day_segment_type = get_local_entity_int_value (get_session_entity (), INT_TYPE_DAY_SEGMENT_TYPE);

	ASSERT ((day_segment_type >= 0) && (day_segment_type < NUM_DAY_SEGMENT_TYPES));

	switch (system)
	{
		case TARGET_ACQUISITION_SYSTEM_FLIR:
		{
			light_level = flir_light_levels[weather_mode][day_segment_type];

			noise_level = flir_noise_levels[weather_mode][day_segment_type];

			break;
		}
		case TARGET_ACQUISITION_SYSTEM_DTV:
		{
			light_level = dtv_light_levels[weather_mode][day_segment_type];

			noise_level = dtv_noise_levels[weather_mode][day_segment_type];

			break;
		}
		case TARGET_ACQUISITION_SYSTEM_DVO:
		{
			light_level = dvo_light_levels[weather_mode][day_segment_type];

			noise_level = dvo_noise_levels[weather_mode][day_segment_type];

			break;
		}
		default:
		{
			debug_fatal ("Invalid target acquisition system = %d", system);

			break;
		}
	}

	set_main_3d_params (DISPLAY_3D_TINT_GREEN, light_level, noise_level, x, y, size, size, rad (59.99) * zoom, rad (59.99) * zoom);

	draw_eo_3d_scene = TRUE;

	draw_main_3d_scene (&eo_vp);

	draw_eo_3d_scene = FALSE;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if 0
static void draw_high_action_display (entity* target, int fill_boxes)
{
	const char* s;
	char buffer[200];
	float y_pos = -0.97;

	rangefinding_system rangefinder = get_range_finder();

	float target_range = get_range_to_target();
	int x_adjust, width;

	set_mono_font_type (MONO_FONT_TYPE_8X14);

	if (fill_boxes == 2)
	{
		rgb_colour bg_colour;

		set_rgb_colour (bg_colour, 0, 40, 0, 255);

		draw_2d_box(-0.98, y_pos, -0.35, y_pos - 0.2, TRUE, FALSE, bg_colour);
		draw_2d_box(0.98, y_pos, 0.35, y_pos - 0.2, TRUE, FALSE, bg_colour);
	}

	if (fill_boxes >= 1)
	{
		draw_2d_box(-0.98, y_pos, -0.35, y_pos - 0.2, FALSE, TRUE, MFD_COLOUR1);
		draw_2d_box(0.98, y_pos, 0.35, y_pos - 0.2, FALSE, TRUE, MFD_COLOUR1);
	}

// Jabberwock 031107 Designated targets
	target = get_local_entity_parent (get_gunship_entity (), LIST_TYPE_TARGET);

	if (target && get_local_entity_parent (target, LIST_TYPE_DESIGNATED_TARGET) == get_gunship_entity())
	{
		set_2d_mono_font_position (0.7, y_pos + 0.1);
		set_mono_font_rel_position (0, 0);
		print_mono_font_string ("MARKED");
	}
// Jabberwock 031107 ends

	//
	// target name
	//

	s = get_target_display_name (target, buffer, TRUE);

	if (s)
	{
		width = get_mono_font_string_width (s);
		set_2d_mono_font_position (0.0, y_pos + 0.1);
		set_mono_font_rel_position (-width * 0.5, 0);
		print_mono_font_string (s);
	}

	// airspeed and altitude
	{
		int airspeed = (int)knots(current_flight_dynamics->velocity_z.value);
		int altitude = get_apache_display_radar_altitude();

		sprintf(buffer, "%3d", airspeed);
		set_2d_mono_font_position (-0.7, y_pos + 0.08);
		set_mono_font_rel_position (0, 0);
		print_mono_font_string (buffer);

		if (altitude <= feet(get_low_altitude_warning_limit()))
			set_mono_font_colour(MFD_COLOUR_RED);
		else if (altitude >= feet(get_high_altitude_warning_limit()))
			set_mono_font_colour(MFD_COLOUR_YELLOW);

		if (altitude < 1500.0)
		{
			sprintf(buffer, "%4d", altitude);
			set_2d_mono_font_position (0.4, y_pos + 0.08);
			set_mono_font_rel_position (0, 0);
			print_mono_font_string (buffer);
		}

		set_mono_font_colour(MFD_COLOUR1);
	}

	// lower left box:
	// rang finder    range
	// targeting status

	switch (rangefinder)
	{
	case RANGEFINDER_FCR:
		s = "FCR";
		sprintf(buffer, "R%.1f", target_range * 0.001);
		break;
	case RANGEFINDER_LASER:
		s = "TADS";
		sprintf(buffer, "L%04.0f", target_range);
		break;
	case RANGEFINDER_TRIANGULATION:
		if (target_acquisition_system != TARGET_ACQUISITION_SYSTEM_OFF)
			s = "TADS";
		else
			s = "NONE";

		if (target_range > 0.0)
			sprintf(buffer, "A%.1f", target_range * 0.001);
		else
			sprintf(buffer, "AX.X");

		break;
	}

	set_2d_mono_font_position (-0.95, y_pos - 0.03);
	x_adjust = 0; //get_mono_font_string_width (s) * -0.5;
	set_mono_font_rel_position (x_adjust, 0);
	print_mono_font_string (s);

	set_2d_mono_font_position (-0.40, y_pos - 0.03);
	x_adjust = -get_mono_font_string_width (buffer); // * 0.5;
	set_mono_font_rel_position (x_adjust, 0);
	print_mono_font_string (buffer);

	// targeting status

	switch (weapon_lock_type)
	{
		case WEAPON_LOCK_NO_ACQUIRE:
			s = "NO ACQUIRE";
			break;
		case WEAPON_LOCK_NO_WEAPON:
			s = "NO WEAPON";
			break;
		case WEAPON_LOCK_NO_TARGET:
			s = "NO TARGET";
			break;
		case WEAPON_LOCK_INVALID_TARGET:
			s = "INVALID TGT";
			break;
		case WEAPON_LOCK_SEEKER_LIMIT:
			s = "SKR LIMIT";
			break;
		case WEAPON_LOCK_NO_LOS:
			s = "NO LOS";
			break;
		case WEAPON_LOCK_MIN_RANGE:
			if (rangefinder != RANGEFINDER_TRIANGULATION)
			{
				s = "MIN RNG";
				break;
			}
		case WEAPON_LOCK_MAX_RANGE:
			if (rangefinder != RANGEFINDER_TRIANGULATION)
			{
				s = "MAX RNG";
				break;
			}
		case WEAPON_LOCK_NO_BORESIGHT:
		case WEAPON_LOCK_VALID:
		case WEAPON_LOCK_BURST_LIMIT:
			s = "VALID LOCK";
			break;
		default:
			debug_fatal ("Invalid weapon lock type = %d", weapon_lock_type);
			break;
	}

	set_2d_mono_font_position (-0.95, y_pos - 0.03);
	x_adjust = 0; //get_mono_font_string_width (s) * -0.5;
	set_mono_font_rel_position (x_adjust, 10);
	print_mono_font_string (s);

	// lower right box:
	// weapon type
	// launch mode

	s = get_weapon_status(buffer, sizeof(buffer));

	set_2d_mono_font_position (0.37, y_pos - 0.03);
	x_adjust = 0; //get_mono_font_string_width (s) * -0.5;
	set_mono_font_rel_position (x_adjust, 0);
	print_mono_font_string (s);

	if (get_local_entity_int_value (get_gunship_entity (), INT_TYPE_LOCK_ON_AFTER_LAUNCH))
		s = "LOAL-HI";
	else
		s = "LOBL";

	set_2d_mono_font_position (0.37, y_pos - 0.03);
	x_adjust = 0; //get_mono_font_string_width (s) * -0.5;
	set_mono_font_rel_position (x_adjust, 9);
	print_mono_font_string (s);

	////////////////////////////////////////
	//
	// draw field of regard and view boxes
	//
	////////////////////////////////////////

	draw_field_of_regard_and_view_boxes ();
}
#endif
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_2d_eo_display (eo_params *eo, target_acquisition_systems system, int damaged, int valid_3d, int scaled_3d, int is_ort)
{
	float
		y_adjust,
		i,
		j,
		x,
		y;

	entity
		*source,
		*target;

	vec3d
		target_point;

	viewpoint
		tmp;

	object_3d_visibility
		visibility;

	ASSERT (eo);


	source = get_gunship_entity ();
	target = get_local_entity_parent (source, LIST_TYPE_TARGET);

	////////////////////////////////////////
	//
	// text
	//
	////////////////////////////////////////

	set_mono_font_colour (MFD_COLOUR1);

	set_mono_font_type (MONO_FONT_TYPE_12X20);

	//
	// sensor type
	//

	y_adjust = 5.0;
	set_2d_mono_font_position (-0.9, 0.7);
	set_mono_font_rel_position (1.0, y_adjust);

	switch (system)
	{
		case TARGET_ACQUISITION_SYSTEM_FLIR:
		{
			print_mono_font_string ("FLIR");

			break;
		}
		case TARGET_ACQUISITION_SYSTEM_DTV:
		{
			print_mono_font_string ("DTV");

			break;
		}
		case TARGET_ACQUISITION_SYSTEM_DVO:
		{
			print_mono_font_string ("DVO");

			break;
		}
		default:
		{
			ASSERT(FALSE);

			break;
		}
	}

	//
	// damaged
	//

	if (damaged)
	{
		draw_2d_line (-0.5, -0.5,  0.5, 0.5, MFD_COLOUR1);
		draw_2d_line ( 0.5, -0.5, -0.5, 0.5, MFD_COLOUR1);

		return;
	}

	draw_apache_high_action_display(RENDER_TARGET_TADS, MFD_COLOUR1);

	////////////////////////////////////////
	//
	// draw heading scale
	//
	////////////////////////////////////////

	draw_heading_scale(TRUE, 0.9);

	////////////////////////////////////////
	//
	// line graphics
	//
	////////////////////////////////////////

	//
	// datum
	//

	{
		// TODO flash with malfunction
		draw_2d_line (-0.25, 0.0, -0.050, 0.0, MFD_COLOUR1);
		draw_2d_line (0.050, 0.0, 0.25, 0.0, MFD_COLOUR1);
		draw_2d_line (0.0, -0.20, 0.0, -0.050, MFD_COLOUR1);
		draw_2d_line (0.0, 0.050, 0.0, 0.2, MFD_COLOUR1);
	}

	tmp = main_vp;
	main_vp = eo_vp;
	draw_apache_acquisition_source_symbology(&eo_vp, MFD_COLOUR1, 0.16, rad(get_eo_sensor_fov(eo->field_of_view, system, is_ort) * 0.25));
	if (get_apache_c_scope_enabled())
		draw_c_scope_symbology(FALSE, MFD_COLOUR1, MFD_CLEAR_COLOUR);
	main_vp = tmp;

	//
	// FOV gates
	//

	if (eo->field_of_view > EO_FOV_ZOOM)
	{
		float
			fov = get_eo_sensor_fov(eo->field_of_view, system, is_ort),
			fov_next = get_eo_sensor_fov(eo->field_of_view - 1, system, is_ort),
			ratio = 1.2 * fov_next / fov,
			line_length = ratio * 0.3;

		draw_2d_half_thick_line(ratio, ratio, ratio - line_length, ratio, MFD_COLOUR1);
		draw_2d_half_thick_line(ratio, ratio, ratio, ratio - line_length, MFD_COLOUR1);

		draw_2d_half_thick_line(-ratio, ratio, -ratio + line_length, ratio, MFD_COLOUR1);
		draw_2d_half_thick_line(-ratio, ratio, -ratio, ratio - line_length, MFD_COLOUR1);

		draw_2d_half_thick_line(-ratio, -ratio, -ratio + line_length, -ratio, MFD_COLOUR1);
		draw_2d_half_thick_line(-ratio, -ratio, -ratio, -ratio + line_length, MFD_COLOUR1);

		draw_2d_half_thick_line(ratio, -ratio, ratio - line_length, -ratio, MFD_COLOUR1);
		draw_2d_half_thick_line(ratio, -ratio, ratio, -ratio + line_length, MFD_COLOUR1);
	}

	// weapon targeting info
	if (target)
	{
		float
			offset_x,
			offset_y,
			heading_offset,
			pitch_offset;

		if (get_local_entity_selected_weapon_to_target_offsets(source, &heading_offset, &pitch_offset))
		{
			entity_sub_types selected_weapon_type = get_local_entity_int_value (source, INT_TYPE_SELECTED_WEAPON);

			float
				scale = 0.55 / weapon_database[ENTITY_SUB_TYPE_WEAPON_AGM114L_LONGBOW_HELLFIRE].max_launch_angle_error;

			if (selected_weapon_type == ENTITY_SUB_TYPE_WEAPON_HYDRA70_M255 || selected_weapon_type == ENTITY_SUB_TYPE_WEAPON_HYDRA70_M261)
				scale = 1.0 / rad(10.0);

			offset_x = bound(heading_offset * scale, -1.1, 1.1);
			offset_y = bound(pitch_offset * scale, -1.1, 1.1);;

			switch (selected_weapon_type)
			{
				case ENTITY_SUB_TYPE_WEAPON_HYDRA70_M255:
				case ENTITY_SUB_TYPE_WEAPON_HYDRA70_M261:
				{
					if (weapon_lock_type == WEAPON_LOCK_VALID)
						draw_solid_i_beam(offset_x, offset_y, MFD_COLOUR1);
					else
						draw_dashed_i_beam(offset_x, offset_y, MFD_COLOUR1);
					break;
				}
				////////////////////////////////////////
				case ENTITY_SUB_TYPE_WEAPON_AGM114L_LONGBOW_HELLFIRE:
				case ENTITY_SUB_TYPE_WEAPON_AGM114K_HELLFIRE_II:
				////////////////////////////////////////
				{
					if (!get_local_entity_int_value (source, INT_TYPE_LOCK_ON_AFTER_LAUNCH))
					{
						if (weapon_lock_type == WEAPON_LOCK_VALID)
							draw_hellfire_lobl_solid_target_marker(offset_x, offset_y, MFD_COLOUR1);
						else
							draw_hellfire_lobl_dashed_target_marker(offset_x, offset_y, MFD_COLOUR1, &MFD_COLOUR6);
					}
					else
					{
						if (weapon_lock_type == WEAPON_LOCK_VALID)
							draw_hellfire_loal_solid_target_marker(offset_x, offset_y, MFD_COLOUR1);
						else
							draw_hellfire_loal_dashed_target_marker(offset_x, offset_y, MFD_COLOUR1, &MFD_COLOUR6);
					}

					break;
				}
			}
		}
	}

	// IAT tracking gates
	if (target && eo_is_locked())
	{
		if (valid_3d)
		{
			tmp = main_vp;
			main_vp = eo_vp;

			get_local_entity_target_point (target, &target_point);
			visibility = get_position_3d_screen_coordinates (&target_point, &i, &j);

			if ((visibility == OBJECT_3D_COMPLETELY_VISIBLE) || (visibility == OBJECT_3D_PARTIALLY_VISIBLE))
			{
				if (scaled_3d)
				{
					i -= i_translate_3d;
					j -= j_translate_3d;

					i *= i_scale_3d;
					j *= j_scale_3d;
				}

				get_2d_world_position (i, j, &x, &y);

				draw_2d_half_thick_line (x - 0.25, y + 0.15, x - 0.20, y + 0.15, MFD_COLOUR1);
				draw_2d_half_thick_line (x + 0.25, y + 0.15, x + 0.20, y + 0.15, MFD_COLOUR1);
				draw_2d_half_thick_line (x - 0.25, y - 0.15, x - 0.20, y - 0.15, MFD_COLOUR1);
				draw_2d_half_thick_line (x + 0.25, y - 0.15, x + 0.20, y - 0.15, MFD_COLOUR1);
				draw_2d_half_thick_line (x - 0.25, y + 0.15, x - 0.25, y + 0.10, MFD_COLOUR1);
				draw_2d_half_thick_line (x - 0.25, y - 0.15, x - 0.25, y - 0.10, MFD_COLOUR1);
				draw_2d_half_thick_line (x + 0.25, y + 0.15, x + 0.25, y + 0.10, MFD_COLOUR1);
				draw_2d_half_thick_line (x + 0.25, y - 0.15, x + 0.25, y - 0.10, MFD_COLOUR1);
			}

			main_vp = tmp;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// FLIR
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if 0
static void draw_3d_flir_mfd (mfd_locations location)
{
	if (!apache_damage.flir)
	{
		draw_3d_eo_display (&apache_flir, TARGET_ACQUISITION_SYSTEM_FLIR, location);
	}
}
#endif
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_2d_flir_mfd (int valid_3d, int scaled_3d, int is_ort)
{
	draw_2d_eo_display (&apache_flir, TARGET_ACQUISITION_SYSTEM_FLIR, apache_damage.flir, valid_3d, scaled_3d, is_ort);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// DTV
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if 0
static void draw_3d_dtv_mfd (mfd_locations location)
{
	if (!apache_damage.dtv)
	{
		draw_3d_eo_display (&apache_dtv, TARGET_ACQUISITION_SYSTEM_DTV, location);
	}
}
#endif
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_2d_dtv_mfd (int valid_3d, int scaled_3d, int is_ort)
{
	draw_2d_eo_display (&apache_dtv, TARGET_ACQUISITION_SYSTEM_DTV, apache_damage.dtv, valid_3d, scaled_3d, is_ort);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// DVO
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if 0
static void draw_3d_dvo_mfd (mfd_locations location)
{
	if (!apache_damage.dvo)
	{
		draw_3d_eo_display (&apache_dvo, TARGET_ACQUISITION_SYSTEM_DVO, location);
	}
}
#endif
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_2d_dvo_mfd (int valid_3d, int scaled_3d, int is_ort)
{
	ASSERT(is_ort);  // DVO only viewable through ORT
	draw_2d_eo_display (&apache_dvo, TARGET_ACQUISITION_SYSTEM_DVO, apache_damage.dvo, valid_3d, scaled_3d, is_ort);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TSD
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//
// match ground radar radius
//

#define RADIUS	(ROOT2 - 0.05)

// TODO update for new scale and radar position
void apache_select_clicked_target()
{
	entity
		*target,
		*best_target = NULL;

	matrix3x3
		rotation_matrix;

	vec3d
		position,
		relative_position;

	int
		is_pilot = (get_local_entity_int_value (get_pilot_entity (), INT_TYPE_CREW_ROLE) == CREW_ROLE_PILOT);

	float
		selection_range_limit_sqr,
		tsd_ase_range,
		scale;


	if (fabs(pointer_position_x - clicked_position_x) > 0.05
		|| fabs(pointer_position_y - clicked_position_y) > 0.05)
	{
		return;
	}

	tsd_ase_range = is_pilot ? pilot_tsd_ase_range : cpg_tsd_ase_range;
	scale = RADIUS / tsd_ase_range;
	selection_range_limit_sqr = (tsd_ase_range * 0.05);
	selection_range_limit_sqr *= selection_range_limit_sqr;

	get_3d_transformation_matrix(rotation_matrix, current_flight_dynamics->heading.value, 0.0, 0.0);

	relative_position = get_relative_vec_from_tsd_coordinate(clicked_position_x, clicked_position_y, scale);
	relative_position_to_world_coordinate(&relative_position, &position, rotation_matrix);

	// find target which best corresponds with clicked position
	target = get_local_entity_first_child (get_gunship_entity(), LIST_TYPE_GUNSHIP_TARGET);
	while (target)
	{
		if (!get_local_entity_int_value (target, INT_TYPE_GROUND_RADAR_CLUTTER))
		{
			vec3d*
				target_position = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

			float range_sqr = get_sqr_2d_range(&position, target_position);

			if (range_sqr < selection_range_limit_sqr)
			{
				best_target = target;
				selection_range_limit_sqr = range_sqr;
			}
		}

		target = get_local_entity_child_succ (target, LIST_TYPE_GUNSHIP_TARGET);
	}

	if (best_target)
	{
		if (is_using_eo_system(FALSE))
			set_eo_slave_target(best_target);
		else
		{
			set_gunship_target(best_target);
			set_apache_lock_target(1);
		}
	}
	// didn't find any target under pointer, but if using EO do a point lock on position
	else if (is_using_eo_system(FALSE) && point_inside_map_area(&position))
	{
		helicopter *raw = get_local_entity_data(get_gunship_entity());

		position.y = get_3d_terrain_point_data(position.x, position.z, &raw->ac.terrain_info);

		eo_start_tracking(&position);
	}
}

apache_coordinate_points* get_apache_clicked_point(mfd_locations location, float pointer_pos_x, float pointer_pos_y, unsigned waypoints_only)
{
	const float
		radius = 0.08;

	vec3d
		position;

	apache_coordinate_points
		*array = apache_waypoint_hazard_points,
		*best_wpt = NULL;

	float
		range,
		best_distance = 0.0,
		scale,
		selection_range_limit_sqr;

	int i, upto;

	if (!get_apache_clicked_map_coordinate(location, pointer_pos_x, pointer_pos_y, &position, &range, &scale))
		return NULL;

	selection_range_limit_sqr = (radius / scale);
	selection_range_limit_sqr *= selection_range_limit_sqr;


	if (waypoints_only)
		upto = NUM_APACHE_WAYPOINTS;
	else
		upto = NUM_APACHE_WAYPOINT_CM_POINTS;

	for (i=0; i < upto; i++)
	{
		apache_coordinate_points* wpt = &array[i];

		if (wpt->valid)
		{
			float distance = get_sqr_2d_range(&array[i].position, &position);

			if (distance < selection_range_limit_sqr)
				if (!best_wpt || distance < best_distance)
				{
					best_wpt = wpt;
					best_distance = distance;
				}
		}
	}

	return best_wpt;
}

entity* get_apache_clicked_target(mfd_locations location, float pointer_pos_x, float pointer_pos_y)
{
	return NULL;
}

int get_apache_clicked_map_coordinate(mfd_locations location, float pointer_pos_x, float pointer_pos_y, vec3d* map_coordinate, float* range, float* scale)
{
	float
		centre_y = 0.0,
		centre_x = 0.0,
		heading = current_flight_dynamics->heading.value;

	vec3d
		relative_position,
		*gunship_position = get_local_entity_vec3d_ptr(get_gunship_entity(), VEC3D_TYPE_POSITION),
		*centre_position = gunship_position;

	matrix3x3
		rotation_matrix;

	int
		is_pilot = location <= MFD_LOCATION_PILOT_RHS;

	switch (get_apache_current_mfd_mode(location))
	{
	case MFD_MODE_TSD:
	case MFD_MODE_TSD_WPT:
	case MFD_MODE_TSD_UTIL:
	case MFD_MODE_TSD_RTE:
	case MFD_MODE_TSD_THRT:
	case MFD_MODE_TSD_COORD:
	case MFD_MODE_TSD_SHOW:
	case MFD_MODE_TSD_ZONE:
		if (is_pilot)
		{
			*range = pilot_tsd_ase_range;
			if (pilot_tsd_zoomed)
				*range *= 0.833;

			if (pilot_tsd_frozen)
			{
				centre_position = &pilot_frozen_tsd_position;
				heading = pilot_frozen_tsd_heading;
			}

			if (!pilot_tsd_centered)
				centre_y = -0.65;
		}
		else
		{
			*range = cpg_tsd_ase_range;
			if (cpg_tsd_zoomed)
				*range *= 0.833;

			if (cpg_tsd_frozen)
			{
				centre_position = &cpg_frozen_tsd_position;
				heading = pilot_frozen_tsd_heading;
			}

			if (!cpg_tsd_centered)
				centre_y = -0.65;
		}
		break;
	default:
		return FALSE;
	}


	*scale = TSD_AREA_WIDTH / *range;

	get_3d_transformation_matrix(rotation_matrix, heading, 0.0, 0.0);


	// relative position
	relative_position.x = (pointer_pos_x - centre_x) / *scale;
	relative_position.y = 0.0;
	relative_position.z = (pointer_pos_y - centre_y) / *scale;  // yes, y coordinates in MFD translates to Z-coordinates in 3D

	multiply_matrix3x3_vec3d(&relative_position, rotation_matrix, &relative_position);

	map_coordinate->x = centre_position->x + relative_position.x;
	map_coordinate->y = 0.0;
	map_coordinate->z = centre_position->z + relative_position.z;

	return TRUE;
}

static void display_coordinate_marker(apache_coordinate_points* wp, vec3d* source_position, float scale, rgb_colour fg_col, rgb_colour bg_col)
{
	const float wp_radius = 0.08;
	vec3d rel_position;
	char buffer[16];

	set_mono_font_type (MONO_FONT_TYPE_10X16);
	set_mono_font_colour(fg_col);

	rel_position.x = (wp->position.x - source_position->x) * scale;
	rel_position.z = (wp->position.z - source_position->z) * scale;

	draw_2d_mono_sprite (waypoint_marker, rel_position.x, rel_position.z, bg_col);
	draw_2d_circle(rel_position.x, rel_position.z, wp_radius, fg_col);

	set_2d_mono_font_position (rel_position.x, rel_position.z);
	set_mono_font_rel_position(-0.5 * get_mono_font_string_width(wp->free_text), -11.0);
	print_mono_font_string(wp->free_text);

	sprintf(buffer, "%02d", wp->number);
	set_2d_mono_font_position (rel_position.x, rel_position.z);
	set_mono_font_rel_position (-10.0, 2.0);
	print_mono_font_string(buffer);
}

static void draw_tactical_situation_display_mfd (mfd_modes mfd_mode)
{
	char
		buffer[200];

	entity_sides
		source_side;

	float
		tsd_viewport_x_min = -0.95,
		tsd_viewport_y_min = -0.95,
		tsd_viewport_x_max = 0.95,
		tsd_viewport_y_max = 0.95,
		mfd_vp_x_min = mfd_viewport_x_org - (mfd_viewport_size * (0.95 / 2.4)),
		mfd_vp_x_max = mfd_viewport_x_org + (mfd_viewport_size * (0.95 / 2.4)) - 0.001,
		mfd_vp_y_min = mfd_viewport_y_org - (mfd_viewport_size * (0.95 / 2.4)),
		mfd_vp_y_max = mfd_viewport_y_org + (mfd_viewport_size * (0.95 / 2.4)) - 0.001,
		u,
		v,
		scale,
		x_origin,
		y_origin,
		width,
		y_adjust,
		tsd_ase_range,
		actual_tsd_ase_range,
		source_heading;

	entity
		*source,
		*source_target;

	vec3d
		*source_position;

	int
		display_present_position = FALSE,
		tsd_frozen = FALSE,
		tsd_zoomed = FALSE,
		tick,
		is_pilot = (get_local_entity_int_value (get_pilot_entity (), INT_TYPE_CREW_ROLE) == CREW_ROLE_PILOT);

	tsd_underlay_levels
		tsd_underlay = is_pilot ? pilot_tsd_underlay : cpg_tsd_underlay;

	tsd_declutter_levels
		tsd_declutter_level = is_pilot ? pilot_tsd_declutter_level : cpg_tsd_declutter_level;

	rgb_colour tsd_basic_colour = MFD_COLOUR1;

	apache_coordinate_points*
		review_waypoint = NULL;

	source = get_gunship_entity ();
	source_side = get_local_entity_int_value (source, INT_TYPE_SIDE);
	source_heading = get_local_entity_float_value (source, FLOAT_TYPE_HEADING);
	source_position = get_local_entity_vec3d_ptr (source, VEC3D_TYPE_POSITION);
	source_target = get_local_entity_parent (source, LIST_TYPE_TARGET);

	//
	// match ground radar origin
	//

	x_origin = 0.0;
	y_origin = -0.65;

	if (is_pilot)
	{
		actual_tsd_ase_range = tsd_ase_range = pilot_tsd_ase_range;
		tsd_zoomed = pilot_tsd_zoomed;
		tsd_frozen = pilot_tsd_frozen;
		review_waypoint = pilot_tsd_show_waypoint_review;
		display_present_position = pilot_tsd_display_present_position;

		if (pilot_tsd_centered)
			y_origin = 0.0;

		if (tsd_frozen)
		{
			source_position = &pilot_frozen_tsd_position;
			source_heading = pilot_frozen_tsd_heading;
		}
	}
	else
	{
		actual_tsd_ase_range = tsd_ase_range = cpg_tsd_ase_range;
		tsd_zoomed = cpg_tsd_zoomed;
		tsd_frozen = cpg_tsd_frozen;
		review_waypoint = cpg_tsd_show_waypoint_review;
		display_present_position = cpg_tsd_display_present_position;

		if (cpg_tsd_centered)
			y_origin = 0.0;

		if (tsd_frozen)
		{
			source_position = &cpg_frozen_tsd_position;
			source_heading = cpg_frozen_tsd_heading;
		}
	}

	if (tsd_zoomed)
		tsd_ase_range *= 0.833;
	scale = TSD_AREA_WIDTH / tsd_ase_range;

	////////////////////////////////////////
	//
	//VJ 030423 TSD RENDER MOD
	//
	////////////////////////////////////////

	if (tsd_underlay == TSD_UNDERLAY_MAP && !apache_damage.navigation_computer)
	{
		if (tsd_render_mode != TSD_RENDER_CONTOUR_MODE)
		{
//			tsd_basic_colour = MFD_COLOUR_DARK_BLUE;
			draw_tsd_terrain_map (mfd_env, -y_origin, actual_tsd_ase_range, scale, source_position, source_heading, FALSE);
		}

//VJ 030423 TSD render mod, added mfd_env
		draw_tsd_contour_map (mfd_env, -y_origin, actual_tsd_ase_range, scale, source_position, source_heading, TRUE, FALSE);
	}


	set_2d_window (mfd_env, tsd_viewport_x_min, tsd_viewport_y_min, tsd_viewport_x_max, tsd_viewport_y_max);
	set_2d_viewport (mfd_env, mfd_vp_x_min, mfd_vp_y_min, mfd_vp_x_max, mfd_vp_y_max);


	get_2d_float_screen_coordinates (x_origin, y_origin, &u, &v);

	u -= mfd_vp_x_min;
	v -= mfd_vp_y_min;

	////////////////////////////////////////
	//
	// radar scan
	//
	////////////////////////////////////////

	if (tsd_declutter_level != TSD_DECLUTTER_LEVEL_NAVIGATION)
	{
		float
			radius;

		radar_params* radar = get_current_radar_params();

		set_2d_viewport_origin (mfd_env, u, v);

		radius = radar->scan_range * scale;

		if (radar->scan_arc_size == APACHE_RADAR_SCAN_ARC_SIZE_360)
			draw_2d_circle (0.0, 0.0, radius, tsd_basic_colour);
		else
		{
			set_2d_window_rotation (mfd_env, -radar->scan_datum);
			draw_radar_arc(radar->scan_arc_size, radius, tsd_basic_colour);

			if (radar->scan_arc_size > rad(90))
				draw_2d_half_thick_line (0.0, 0.0, 0.0, radius, tsd_basic_colour);

			set_2d_window_rotation (mfd_env, -(radar->scan_datum - (radar->scan_arc_size * 0.5)));
			draw_2d_half_thick_line (0.0, 0.0, 0.0, radius, tsd_basic_colour);

			set_2d_window_rotation (mfd_env, -(radar->scan_datum + (radar->scan_arc_size * 0.5)));
			draw_2d_half_thick_line (0.0, 0.0, 0.0, radius, tsd_basic_colour);

//			set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);
			set_2d_viewport (mfd_env, mfd_vp_x_min, mfd_vp_y_min, mfd_vp_x_max, mfd_vp_y_max);

			set_2d_window_rotation (mfd_env, 0.0);
		}
	}

	////////////////////////////////////////
	//
	// waypoint route
	//
	////////////////////////////////////////

	if (tsd_declutter_level != TSD_DECLUTTER_LEVEL_TARGET && !apache_damage.navigation_computer)
	{
		vec3d
			wp1_rel_position,
			wp2_rel_position;

		rgb_colour waypoint_colour = MFD_COLOUR2;

		int current_waypoint_index;

		unsigned next = 0, last_waypoint, is_direct_waypoint;

		apache_coordinate_points
			*current_waypoint = get_current_apache_navigation_point(&is_direct_waypoint),
			*wp2 = NULL,
			*wp1 = NULL,
			**route = get_current_apache_navigation_route(&last_waypoint, &current_waypoint_index);

		float
			min_x, max_x, min_y, max_y;

		max_x = 1.0 / scale;
		min_x = -max_x;
		min_y = (-1.0 + y_origin) / scale;
		max_y = (1.0 - y_origin) / scale;

//		if (tsd_underlay == TSD_UNDERLAY_MAP)
//			waypoint_colour = tsd_basic_colour;

		if (is_direct_waypoint)
			waypoint_colour = MFD_COLOUR5;

		set_2d_viewport_origin (mfd_env, u, v);
		set_2d_window_rotation (mfd_env, source_heading);

		if (route)
		{
			wp1 = route[next++];
			if (wp1)
			{
				//
				// waypoint route
				//

				wp1_rel_position = wp1->position;

				wp1_rel_position.x = (wp1_rel_position.x - source_position->x) * scale;
				wp1_rel_position.z = (wp1_rel_position.z - source_position->z) * scale;

				wp2 = route[next++];

				while (wp2)
				{
					wp2_rel_position = wp2->position;

					wp2_rel_position.x = (wp2_rel_position.x - source_position->x) * scale;
					wp2_rel_position.z = (wp2_rel_position.z - source_position->z) * scale;

					draw_2d_half_thick_line (wp1_rel_position.x, wp1_rel_position.z, wp2_rel_position.x, wp2_rel_position.z, waypoint_colour);  // 5

					wp1 = wp2;
					wp1_rel_position = wp2_rel_position;
					wp2 = route[next++];
				}
			}
		}

		if (is_direct_waypoint && current_waypoint)
		{
			wp1_rel_position.x = (current_waypoint->position.x - source_position->x) * scale;
			wp1_rel_position.z = (current_waypoint->position.z - source_position->z) * scale;

			draw_2d_half_thick_line (0.0, 0.0, wp1_rel_position.x, wp1_rel_position.z, MFD_COLOUR1);
		}

		if (mfd_mode == MFD_MODE_TSD_WPT && !review_waypoint)
			review_waypoint = current_waypoint;

		//
		// coordinate markers
		//

		for (next = 0; next < NUM_APACHE_WAYPOINT_CM_POINTS; next++)
		{
			wp1 = &apache_waypoint_hazard_points[next];

			if (!wp1->valid)
				continue;

			display_coordinate_marker(wp1, source_position, scale, waypoint_colour, clear_mfd_colour);
		}

		if (is_direct_waypoint && current_waypoint)
			display_coordinate_marker(current_waypoint, source_position, scale, waypoint_colour, clear_mfd_colour);

		if (review_waypoint)
			display_coordinate_marker(review_waypoint, source_position, scale, clear_mfd_colour, waypoint_colour);

		set_2d_viewport (mfd_env, mfd_vp_x_min, mfd_vp_y_min, mfd_vp_x_max, mfd_vp_y_max);
		set_2d_window_rotation (mfd_env, 0.0);
	}

	////////////////////////////////////////
	//
	// targets
	//
	////////////////////////////////////////

	{
		entity
			*target,
			*launched_weapon;

		vec3d
			*target_position;

		threat_types
			threat_type;

		int
			draw_threat_line;

		float
			air_scan_range,
			dx,
			dy;

		if (tsd_declutter_level != TSD_DECLUTTER_LEVEL_NAVIGATION)
		{
			draw_pfzs();

			tsd_threat_line_flash_timer -= get_delta_time ();

			if (tsd_threat_line_flash_timer < 0.0)
			{
				tsd_threat_line_flash_timer = TSD_THREAT_LINE_FLASH_RATE;

				tsd_draw_threat_line_status ^= 1;
			}

			set_2d_viewport_origin (mfd_env, u, v);

			set_2d_window_rotation (mfd_env, source_heading);

			//
			// display enemy SAM and AAA threat range circles
			//

			target = get_local_entity_first_child (source, LIST_TYPE_GUNSHIP_TARGET);

			while (target)
			{
				if (!get_local_entity_int_value (target, INT_TYPE_GROUND_RADAR_CLUTTER))
				{
					if (source_side != get_local_entity_int_value (target, INT_TYPE_SIDE))
					{
						threat_type = get_local_entity_int_value (target, INT_TYPE_THREAT_TYPE);

						if ((threat_type == THREAT_TYPE_SAM) || (threat_type == THREAT_TYPE_AAA))
						{
							target_position = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

							dx = (target_position->x - source_position->x) * scale;
							dy = (target_position->z - source_position->z) * scale;

							air_scan_range = get_local_entity_float_value (target, FLOAT_TYPE_AIR_SCAN_RANGE) * scale;

							draw_2d_circle (dx, dy, air_scan_range, MFD_COLOUR_DARK_RED);
						}
					}
				}

				target = get_local_entity_child_succ (target, LIST_TYPE_GUNSHIP_TARGET);
			}

			//
			// display all gunship targets (do not show ground radar clutter)
			//

			target = get_local_entity_first_child (source, LIST_TYPE_GUNSHIP_TARGET);

			while (target)
			{
				if (!get_local_entity_int_value (target, INT_TYPE_GROUND_RADAR_CLUTTER))
				{
					//VJ 030423 TSD render mod
					if (tsd_render_mode == TSD_RENDER_CONTOUR_MODE)
						draw_tsd_target_symbol (target, source_position, scale, FALSE, FALSE, FALSE);
					else
						draw_tsd_target_symbol (target, source_position, scale, FALSE, TRUE, FALSE);
				}

				target = get_local_entity_child_succ (target, LIST_TYPE_GUNSHIP_TARGET);
			}

			//
			// draw selected target last
			//

			if (source_target)
			{
				//VJ 030423 TSD render mod
				if (tsd_render_mode == TSD_RENDER_CONTOUR_MODE)
					draw_tsd_target_symbol (source_target, source_position, scale, TRUE, FALSE, FALSE);
				else
					draw_tsd_target_symbol (source_target, source_position, scale, TRUE, TRUE, FALSE);
			}

			//
			// draw threat line if gunship is targetted (flash if missile fired)
			//

			target = get_local_entity_first_child (source, LIST_TYPE_GUNSHIP_TARGET);

			while (target)
			{
				if (!get_local_entity_int_value (target, INT_TYPE_GROUND_RADAR_CLUTTER))
				{
					if (source_side != get_local_entity_int_value (target, INT_TYPE_SIDE))
					{
						if (get_local_entity_int_value (target, INT_TYPE_RADAR_ON))
						{
							threat_type = get_local_entity_int_value (target, INT_TYPE_THREAT_TYPE);

							if ((threat_type == THREAT_TYPE_SAM) || (threat_type == THREAT_TYPE_AAA) || (threat_type == THREAT_TYPE_AIRBORNE_RADAR))
							{
								if (get_local_entity_parent (target, LIST_TYPE_TARGET) == source)
								{
									draw_threat_line = TRUE;

									launched_weapon = get_local_entity_first_child (target, LIST_TYPE_LAUNCHED_WEAPON);

									while (launched_weapon)
									{
										if (get_local_entity_int_value (launched_weapon, INT_TYPE_WEAPON_GUIDANCE_TYPE) != WEAPON_GUIDANCE_TYPE_NONE)
										{
											if (get_local_entity_parent (launched_weapon, LIST_TYPE_TARGET) == source)
											{
												draw_threat_line = tsd_draw_threat_line_status;

												break;
											}
										}

										launched_weapon = get_local_entity_child_succ (launched_weapon, LIST_TYPE_LAUNCHED_WEAPON);
									}

									if (draw_threat_line)
									{
										target_position = get_local_entity_vec3d_ptr (target, VEC3D_TYPE_POSITION);

										dx = (target_position->x - source_position->x) * scale;
										dy = (target_position->z - source_position->z) * scale;

										draw_2d_line (0.0, 0.0, dx, dy, MFD_COLOUR1);
									}
								}
							}
						}
					}
				}

				target = get_local_entity_child_succ (target, LIST_TYPE_GUNSHIP_TARGET);
			}

//			set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);
			set_2d_viewport (mfd_env, mfd_vp_x_min, mfd_vp_y_min, mfd_vp_x_max, mfd_vp_y_max);

			set_2d_window_rotation (mfd_env, 0.0);
		}
	}

	////////////////////////////////////////
	//
	// aircraft datum symbol
	//
	////////////////////////////////////////

	draw_2d_mono_sprite (large_tsd_ase_aircraft_datum_mask, x_origin, y_origin, MFD_COLOUR_DARK_BLUE);  // 6
	draw_2d_mono_sprite (large_tsd_ase_aircraft_datum, x_origin, y_origin, MFD_COLOUR_BLUE);  // 1

	////////////////////////////////////////
	//
	// text
	//
	////////////////////////////////////////

	set_mono_font_colour (tsd_basic_colour);

	set_mono_font_type (MONO_FONT_TYPE_7X12);

	//
	// target range
	//

	if (tsd_declutter_level != TSD_DECLUTTER_LEVEL_NAVIGATION)
	{
		if (source_target)
		{
			rangefinding_system rangefinder = get_range_finder();

			float
				target_range = get_range_to_target();

			if (rangefinder == RANGEFINDER_LASER)
				sprintf (buffer, "%dm", (int) target_range);
			else
				sprintf (buffer, "%.1fkm", target_range * (1.0 / 1000.0));

			width = get_mono_font_string_width (buffer);

			y_adjust = -12.0;

			set_2d_mono_font_position (0.8, -1.0);

			set_mono_font_rel_position (-width, y_adjust);

			print_mono_font_string (buffer);
		}
	}

	//
	// waypoint information
	//

	if (tsd_declutter_level != TSD_DECLUTTER_LEVEL_NAVIGATION)
	{
		// pointer
//		draw_2d_mono_sprite (large_tsd_pointer_cross_mask, pointer_position_x, pointer_position_y, MFD_COLOUR4);
//		draw_2d_mono_sprite (large_tsd_pointer_cross, pointer_position_x, pointer_position_y, MFD_COLOUR1);


		if (is_holding_left_button())   // is creating a pfz
			draw_2d_box(clicked_position_x, clicked_position_y, pointer_position_x, pointer_position_y, FALSE, FALSE, MFD_COLOUR_RED);
		if (is_holding_right_button())  // is creating a nfz
			draw_2d_box(clicked_position_x, clicked_position_y, pointer_position_x, pointer_position_y, FALSE, FALSE, MFD_COLOUR_BLUE);
	}

	set_2d_window (mfd_env, MFD_WINDOW_X_MIN, MFD_WINDOW_Y_MIN, MFD_WINDOW_X_MAX, MFD_WINDOW_Y_MAX);
	set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

	// TODO - not really
	// Draw border around area.  Border is dashed when radar is frozen
	if (tsd_frozen)
	{
		float min_x = -0.955, max_x = 0.96;
		float min_y = -0.96, max_y = 0.955;
		float x1, x2, y1, y2;
		float step = (max_x - min_x) / 9.0;

		x1 = min_x;
		for (x2 = x1 + step; x1 < max_x; x1 += 2 * step, x2 = x1 + step)
		{
			draw_2d_half_thick_line(x1, max_y, x2, max_y, MFD_COLOUR1);
			draw_2d_half_thick_line(x1, min_y, x2, min_y, MFD_COLOUR1);
			if (x2 < (max_x - 0.5 * step))
			{
				draw_2d_half_thick_line(x2, max_y, x2 + step, max_y, MFD_COLOUR6);
				draw_2d_half_thick_line(x2, min_y, x2 + step, min_y, MFD_COLOUR6);
			}
		}

		y1 = min_y;
		for (y2 = y1 + step; y1 < max_y; y1 += 2 * step, y2 = y1 + step)
		{
			draw_2d_half_thick_line(max_x, y1, max_x, y2, MFD_COLOUR1);
			draw_2d_half_thick_line(min_x, y1, min_x, y2, MFD_COLOUR1);
			if (y2 < (max_y - 0.5 * step))
			{
				draw_2d_half_thick_line(max_x, y2, max_x, y2 + step, MFD_COLOUR6);
				draw_2d_half_thick_line(min_x, y2, min_x, y2 + step, MFD_COLOUR6);
			}
		}
	}
	else
//		draw_2d_box(-1.0, -1.0, 1.0, 1.0, FALSE, TRUE, MFD_COLOUR1);
		draw_2d_box(-0.955, -0.955, 0.955, 0.955, FALSE, TRUE, MFD_COLOUR1);

	set_mono_font_type (MONO_FONT_TYPE_12X20);

	// draw range tick marks along left and bottom edge
	for (tick = 0; tick < 6; tick++)
	{
		float range, pos;

		if (tsd_ase_range == TSD_ASE_RANGE_10000)
			range = tick * actual_tsd_ase_range * 0.25;
		else
			range = tick * actual_tsd_ase_range * 0.20;

		pos = range * scale;

		if (y_origin + pos < 0.95)
		{
			draw_2d_line(-0.98, y_origin + pos, -0.95, y_origin + pos, MFD_COLOUR1);
			if ((tick & 1) == 0)
			{
				sprintf(buffer, "%.0f", range * 0.001);
				set_2d_mono_font_position(-0.93, y_origin + pos);
				set_mono_font_rel_position (0, -8.0);
				print_mono_font_string(buffer);
			}
		}

		if (y_origin - pos > -0.95)
		{
			draw_2d_line(-0.98, y_origin - pos, -0.95, y_origin - pos, MFD_COLOUR1);
			if ((tick & 1) == 0)
			{
				sprintf(buffer, "%.0f", range * 0.001);
				set_2d_mono_font_position(-0.93, y_origin - pos);
				set_mono_font_rel_position (0, -8.0);
				print_mono_font_string(buffer);
			}
		}


		if (pos > -0.95 && pos < 0.95)
		{
			draw_2d_line(x_origin + pos, -0.92, x_origin + pos, -0.95, MFD_COLOUR1);
			draw_2d_line(x_origin - pos, -0.92, x_origin - pos, -0.95, MFD_COLOUR1);
		}
	}

	if (tsd_declutter_level != TSD_DECLUTTER_LEVEL_TARGET && !apache_damage.navigation_computer)
	{
		if ((mfd_mode == MFD_MODE_TSD_WPT || mfd_mode == MFD_MODE_TSD_RTE)&& review_waypoint)
			display_coordinate_review_status_window(review_waypoint);
		else
			display_waypoint_information (MFD_COLOUR1, -0.85, -0.6);
	}

	if (display_present_position)
		display_present_position_status_window();
}

#undef RADIUS

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ASE
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static entity *get_closest_missile (entity *source, vec3d *source_position, threat_types threat_type, float *closest_missile_time_to_impact)
{
	entity
		*threat,
		*closest_missile;

	int
		overshot;

	float
		threat_range,
		threat_velocity,
		time_to_impact,
		length,
		cos_error;

	vec3d
		*threat_position,
		uvec_threat_to_target;

	matrix3x3
		*attitude;

	ASSERT (source);

	ASSERT (source_position);

	ASSERT ((threat_type == THREAT_TYPE_RF_MISSILE) || (threat_type == THREAT_TYPE_IR_MISSILE) || (threat_type == THREAT_TYPE_LASER_MISSILE));

	closest_missile = NULL;

	*closest_missile_time_to_impact = 1000000.0;

	threat = get_local_entity_first_child (get_gunship_entity (), LIST_TYPE_TARGET);

	while (threat)
	{
		if (get_local_entity_int_value (threat, INT_TYPE_THREAT_TYPE) == threat_type)
		{
			threat_position = get_local_entity_vec3d_ptr (threat, VEC3D_TYPE_POSITION);

			threat_range = get_3d_range (source_position, threat_position);

			threat_velocity = get_local_entity_float_value (threat, FLOAT_TYPE_VELOCITY);

			time_to_impact = threat_range / max (threat_velocity, 1.0);

			//
			// guard against 'overshot target' to prevent spurious indications
			//

			overshot = FALSE;

			if (time_to_impact < 1.0)
			{
				uvec_threat_to_target.x = source_position->x - threat_position->x;
				uvec_threat_to_target.y = source_position->y - threat_position->y;
				uvec_threat_to_target.z = source_position->z - threat_position->z;

				length = get_3d_vector_magnitude (&uvec_threat_to_target);

				if (length > 1.0)
				{
					normalise_3d_vector_given_magnitude (&uvec_threat_to_target, length);

					attitude = get_local_entity_attitude_matrix_ptr (threat);

					cos_error = get_3d_unit_vector_dot_product ((vec3d *) &((*attitude) [2][0]), &uvec_threat_to_target);

					if (cos_error < 0.0)
					{
						overshot = TRUE;
					}
				}
				else
				{
					overshot = TRUE;
				}
			}

			if (!overshot)
			{
				if (time_to_impact < *closest_missile_time_to_impact)
				{
					closest_missile = threat;

					*closest_missile_time_to_impact = time_to_impact;
				}
			}
		}

		threat = get_local_entity_child_succ (threat, LIST_TYPE_TARGET);
	}

	return (closest_missile);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define RADIUS	(0.8)

static void draw_aircraft_survivability_equipment_display_mfd (void)
{
	char
		*s,
		buffer[200];

	entity_sides
		source_side;

	float
		tsd_ase_range,
		scale,
		width,
		y_adjust,
		source_heading;

	entity
		*source,
		*source_target;

	vec3d
		*source_position;

	rgb_colour
		fg_colour,
		bg_colour;

	source = get_gunship_entity ();

	source_side = get_local_entity_int_value (source, INT_TYPE_SIDE);

	source_heading = get_local_entity_float_value (source, FLOAT_TYPE_HEADING);

	source_position = get_local_entity_vec3d_ptr (source, VEC3D_TYPE_POSITION);

	source_target = get_local_entity_parent (source, LIST_TYPE_TARGET);

	if (get_local_entity_int_value (get_pilot_entity (), INT_TYPE_CREW_ROLE) == CREW_ROLE_PILOT)
		tsd_ase_range = pilot_tsd_ase_range;
	else
		tsd_ase_range = cpg_tsd_ase_range;

	scale = RADIUS / tsd_ase_range;

	////////////////////////////////////////
	//
	// threats
	//
	////////////////////////////////////////

	{
		entity
			*threat,
			*launched_weapon;

		vec3d
			*threat_position;

		threat_types
			threat_type;

		int
			draw_threat_line;

		float
			air_scan_range,
			dx,
			dy;

		ase_threat_line_flash_timer -= get_delta_time ();

		if (ase_threat_line_flash_timer < 0.0)
		{
			ase_threat_line_flash_timer = ASE_THREAT_LINE_FLASH_RATE;

			ase_draw_threat_line_status ^= 1;
		}

		set_2d_window_rotation (mfd_env, source_heading);

		//
		// display enemy SAM and AAA threat range circles
		//
		// (use the gunship target list so that threats which are not targetting the player are still visible)
		//

		threat = get_local_entity_first_child (source, LIST_TYPE_GUNSHIP_TARGET);

		while (threat)
		{
			if (!get_local_entity_int_value (threat, INT_TYPE_GROUND_RADAR_CLUTTER))
			{
				if (source_side != get_local_entity_int_value (threat, INT_TYPE_SIDE))
				{
					threat_type = get_local_entity_int_value (threat, INT_TYPE_THREAT_TYPE);

					if ((threat_type == THREAT_TYPE_SAM) || (threat_type == THREAT_TYPE_AAA))
					{
						threat_position = get_local_entity_vec3d_ptr (threat, VEC3D_TYPE_POSITION);

						dx = (threat_position->x - source_position->x) * scale;
						dy = (threat_position->z - source_position->z) * scale;

						air_scan_range = get_local_entity_float_value (threat, FLOAT_TYPE_AIR_SCAN_RANGE) * scale;

						if (threat_type == THREAT_TYPE_SAM)
							draw_2d_circle (dx, dy, air_scan_range, MFD_COLOUR_RED);
						else
							draw_2d_circle (dx, dy, air_scan_range, MFD_COLOUR_YELLOW);
					}
				}
			}

			threat = get_local_entity_child_succ (threat, LIST_TYPE_GUNSHIP_TARGET);
		}

		//
		// display enemy SAM, AAA and AIRBORNE_RADAR threats
		//

		threat = get_local_entity_first_child (source, LIST_TYPE_GUNSHIP_TARGET);

		while (threat)
		{
			if (!get_local_entity_int_value (threat, INT_TYPE_GROUND_RADAR_CLUTTER))
			{
				if (source_side != get_local_entity_int_value (threat, INT_TYPE_SIDE))
				{
					threat_type = get_local_entity_int_value (threat, INT_TYPE_THREAT_TYPE);

					if ((threat_type == THREAT_TYPE_SAM) || (threat_type == THREAT_TYPE_AAA) || (threat_type == THREAT_TYPE_AIRBORNE_RADAR))
					{
						draw_tsd_target_symbol (threat, source_position, scale, FALSE, FALSE, TRUE);
					}
				}
			}

			threat = get_local_entity_child_succ (threat, LIST_TYPE_GUNSHIP_TARGET);
		}

		//
		// draw threat line if gunship is targetted (flash if missile fired)
		//

		threat = get_local_entity_first_child (source, LIST_TYPE_GUNSHIP_TARGET);

		while (threat)
		{
			if (!get_local_entity_int_value (threat, INT_TYPE_GROUND_RADAR_CLUTTER))
			{
				if (source_side != get_local_entity_int_value (threat, INT_TYPE_SIDE))
				{
					if (get_local_entity_int_value (threat, INT_TYPE_RADAR_ON))
					{
						threat_type = get_local_entity_int_value (threat, INT_TYPE_THREAT_TYPE);

						if ((threat_type == THREAT_TYPE_SAM) || (threat_type == THREAT_TYPE_AAA) || (threat_type == THREAT_TYPE_AIRBORNE_RADAR))
						{
							if (get_local_entity_parent (threat, LIST_TYPE_TARGET) == source)
							{
								draw_threat_line = TRUE;

								launched_weapon = get_local_entity_first_child (threat, LIST_TYPE_LAUNCHED_WEAPON);

								while (launched_weapon)
								{
									if (get_local_entity_int_value (launched_weapon, INT_TYPE_WEAPON_GUIDANCE_TYPE) != WEAPON_GUIDANCE_TYPE_NONE)
									{
										if (get_local_entity_parent (launched_weapon, LIST_TYPE_TARGET) == source)
										{
											draw_threat_line = ase_draw_threat_line_status;

											break;
										}
									}

									launched_weapon = get_local_entity_child_succ (launched_weapon, LIST_TYPE_LAUNCHED_WEAPON);
								}

								if (draw_threat_line)
								{
									threat_position = get_local_entity_vec3d_ptr (threat, VEC3D_TYPE_POSITION);

									dx = (threat_position->x - source_position->x) * scale;
									dy = (threat_position->z - source_position->z) * scale;

									draw_2d_line (0.0, 0.0, dx, dy, MFD_COLOUR1);
								}
							}
						}
					}
				}
			}

			threat = get_local_entity_child_succ (threat, LIST_TYPE_GUNSHIP_TARGET);
		}

		//
		// draw incoming missiles
		//

		threat = get_local_entity_first_child (source, LIST_TYPE_TARGET);

		while (threat)
		{
			threat_type = get_local_entity_int_value (threat, INT_TYPE_THREAT_TYPE);

			if ((threat_type == THREAT_TYPE_RF_MISSILE) || (threat_type == THREAT_TYPE_IR_MISSILE) || (threat_type == THREAT_TYPE_LASER_MISSILE))
			{
				threat_position = get_local_entity_vec3d_ptr (threat, VEC3D_TYPE_POSITION);

				dx = (threat_position->x - source_position->x) * scale;
				dy = (threat_position->z - source_position->z) * scale;

				if (threat_type == THREAT_TYPE_RF_MISSILE)
				{
					fg_colour = MFD_COLOUR_YELLOW;
					bg_colour = MFD_COLOUR_DARK_YELLOW;
				}
				else if (threat_type == THREAT_TYPE_IR_MISSILE)
				{
					fg_colour = MFD_COLOUR_RED;
					bg_colour = MFD_COLOUR_DARK_RED;
				}
				else
				{
					fg_colour = MFD_COLOUR_BLUE;
					bg_colour = MFD_COLOUR_DARK_BLUE;
				}

				draw_2d_mono_sprite (large_ase_missile_mask, dx, dy, bg_colour);
				draw_2d_mono_sprite (large_ase_missile, dx, dy, fg_colour);
			}

			threat = get_local_entity_child_succ (threat, LIST_TYPE_TARGET);
		}

		set_2d_window_rotation (mfd_env, 0.0);
	}

	////////////////////////////////////////
	//
	// aircraft datum symbol
	//
	////////////////////////////////////////

	draw_2d_mono_sprite (large_tsd_ase_aircraft_datum_mask, 0.0, 0.0, MFD_COLOUR6);
	draw_2d_mono_sprite (large_tsd_ase_aircraft_datum, 0.0, 0.0, MFD_COLOUR1);

	set_mono_font_colour (MFD_COLOUR1);

	set_mono_font_type (MONO_FONT_TYPE_7X12);

	////////////////////////////////////////
	//
	// text
	//
	////////////////////////////////////////

	//
	// closest incoming missile
	//

	{
		entity
			*closest_missile;

		float
			time_to_impact;

		y_adjust = 5.0;

		set_mono_font_colour(MFD_COLOUR1);
		set_2d_mono_font_position (-0.8, 1.0);

		set_mono_font_rel_position (1.0, y_adjust);

		closest_missile = get_closest_missile (source, source_position, THREAT_TYPE_IR_MISSILE, &time_to_impact);

		if (closest_missile)
		{
			sprintf (buffer, "IR MSL:%.1f", time_to_impact);

			print_mono_font_string (buffer);

			y_adjust = 2.0;

			set_2d_mono_font_position (-0.8, 0.9);

			set_mono_font_rel_position (1.0, y_adjust);
		}

		closest_missile = get_closest_missile (source, source_position, THREAT_TYPE_RF_MISSILE, &time_to_impact);

		if (closest_missile)
		{
			sprintf (buffer, "RF MSL:%.1f", time_to_impact);

			print_mono_font_string (buffer);

			y_adjust = -2.0;

			set_2d_mono_font_position (-0.8, 0.8);

			set_mono_font_rel_position (1.0, y_adjust);
		}

		closest_missile = get_closest_missile (source, source_position, THREAT_TYPE_LASER_MISSILE, &time_to_impact);

		if (closest_missile)
		{
			sprintf (buffer, "LS MSL:%.1f", time_to_impact);

			print_mono_font_string (buffer);
		}
	}

	//
	// jammers
	//

	{
		if (apache_damage.infra_red_jammer)
		{
			s = "IR JAM XXX";
		}
		else
		{
			if (get_local_entity_int_value (source, INT_TYPE_INFRA_RED_JAMMER_ON))
			{
				s = "IR JAM ON";
			}
			else
			{
				s = "IR JAM OFF";
			}
		}

		y_adjust = -25.0;
	}

	set_2d_mono_font_position (-0.8, -1.0);

	set_mono_font_rel_position (1.0, y_adjust);

	print_mono_font_string (s);

	{
		if (apache_damage.radar_jammer)
		{
			s = "RD JAM XXX";
		}
		else
		{
			if (get_local_entity_int_value (source, INT_TYPE_RADAR_JAMMER_ON))
			{
				s = "RD JAM ON";
			}
			else
			{
				s = "RD JAM OFF";
			}
		}

		y_adjust = -12.0;
	}

	set_2d_mono_font_position (-0.8, -1.0);

	set_mono_font_rel_position (1.0, y_adjust);

	print_mono_font_string (s);

	//
	// auto-countermeasures
	//

	if (get_global_auto_counter_measures() || get_global_ase_auto_page())
	{

		y_adjust = -38.0;

		if (get_global_auto_counter_measures())
		{
			s = "AUTO C/M";
			width = get_mono_font_string_width (s);

			set_2d_mono_font_position (0.8, -1.0);
			set_mono_font_rel_position (-width, y_adjust);

			print_mono_font_string(s);
		}

		if (get_global_ase_auto_page())
		{
			s = "AUTO PAGE";
			width = get_mono_font_string_width (s);

			set_2d_mono_font_position (0.9, 0.9);
			set_mono_font_rel_position (-width, 5.0);

			print_mono_font_string (s);
		}
	}

	//
	// chaff
	//

	{
		if (apache_damage.chaff_dispenser)
		{
			sprintf (buffer, "CHAFF:XX");
		}
		else
		{
			sprintf (buffer, "CHAFF:%02d", get_local_entity_weapon_count (source, ENTITY_SUB_TYPE_WEAPON_CHAFF));
		}

		y_adjust = -25.0;
	}

	width = get_mono_font_string_width (buffer);

	set_2d_mono_font_position (0.8, -1.0);

	set_mono_font_rel_position (-width, y_adjust);

	print_mono_font_string (buffer);

	//
	// flares
	//

	{
		if (apache_damage.flare_dispenser)
		{
			sprintf (buffer, "FLARE:XX");
		}
		else
		{
			sprintf (buffer, "FLARE:%02d", get_local_entity_weapon_count (source, ENTITY_SUB_TYPE_WEAPON_FLARE));
		}

		y_adjust = -12.0;
	}

	width = get_mono_font_string_width (buffer);

	set_2d_mono_font_position (0.8, -1.0);

	set_mono_font_rel_position (-width, y_adjust);

	print_mono_font_string (buffer);
}

#undef RADIUS

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// WEAPON
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if 0
static rgb_alpha_masked_sprite_data
	weapon_sprite;

static unsigned char
	*weapon_sprite_data,
	*weapon_mask_data;

static int
	weapon_x_offset,
	weapon_y_offset,
	weapon_draw_on_texture;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_sprite (int x, int y, int u, int v, int width, int height)
{
	ASSERT (x >= 0);
	ASSERT (y >= 0);

	weapon_sprite.x = weapon_x_offset + x;

	weapon_sprite.y = weapon_y_offset + y;

	weapon_sprite.u = u;

	weapon_sprite.v = v;

	weapon_sprite.width = width;

	weapon_sprite.height = height;

	// JB 030311 Disable EEAH check
	if (!weapon_sprite_data)
		return;

	if (weapon_draw_on_texture)
	{
		blit_rgb_alpha_masked_sprite_zero_mask_value_onto_texture (weapon_sprite_data, weapon_mask_data, &weapon_sprite, video_screen);
	}
	else
	{
		blit_rgb_alpha_masked_sprite_zero_mask_value (weapon_sprite_data, weapon_mask_data, &weapon_sprite);
	}
}
#endif
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if 0
static void draw_weapon_hardpoint_info (int heading_depth, entity_sub_types given_weapon, entity_sub_types selected_weapon)
{
	char
		buffer[80];

	int
		number,
		damaged,
		hardpoint_x,
		hardpoint_y,
		u,
		v;

	entity_sub_types
		weapon_sub_type;

	if (!get_local_entity_weapon_hardpoint_info (get_gunship_entity (), heading_depth, given_weapon, &weapon_sub_type, &number, &damaged))
	{
		return;
	}

	if (draw_large_mfd)
		return;

	////////////////////////////////////////////////////////////////////////////////
	//
	// Chain Gun
	//
	////////////////////////////////////////////////////////////////////////////////

	if (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_M230_30MM_ROUND)
	{
		if (draw_large_mfd)
		{
			////////////////////////////////////////
			//
			// LARGE
			//
			////////////////////////////////////////

			//
			// chain gun
			//

			if (number == 0)
			{
				if ((weapon_sub_type == selected_weapon) && (!damaged))
				{
					draw_sprite (118, 200, 262, 134, 28, 27);
				}
			}
			else
			{
				if ((weapon_sub_type == selected_weapon) && (!damaged))
				{
					draw_sprite (118, 200, 292, 134, 28, 27);
				}
				else
				{
					draw_sprite (118, 200, 322, 134, 27, 27);
				}
			}

			//
			// digits
			//

			hardpoint_x = 115;
			hardpoint_y = 234;

			sprintf (buffer, "%04d", number);

			if ((weapon_sub_type == selected_weapon) && (!damaged))
			{
				v = 32;
			}
			else
			{
				v = 47;
			}

			if (buffer[0] == '0')
			{
				u = 364 + (9 * 10);
			}
			else
			{
				u = 364 + ((buffer[0] - '1') * 10);
			}

			draw_sprite (hardpoint_x, hardpoint_y, u, v, 8, 12);

			if (buffer[1] == '0')
			{
				u = 364 + (9 * 10);
			}
			else
			{
				u = 364 + ((buffer[1] - '1') * 10);
			}

			draw_sprite (hardpoint_x + 9, hardpoint_y, u, v, 8, 12);

			if (buffer[2] == '0')
			{
				u = 364 + (9 * 10);
			}
			else
			{
				u = 364 + ((buffer[2] - '1') * 10);
			}

			draw_sprite (hardpoint_x + 18, hardpoint_y, u, v, 8, 12);

			if (buffer[3] == '0')
			{
				u = 364 + (9 * 10);
			}
			else
			{
				u = 364 + ((buffer[3] - '1') * 10);
			}

			draw_sprite (hardpoint_x + 27, hardpoint_y, u, v, 8, 12);

			//
			// damage cross
			//

			if (damaged)
			{
				draw_sprite (116, 203, 334, 61, 32, 32);
			}
		}
		else
		{
			////////////////////////////////////////
			//
			// SMALL
			//
			////////////////////////////////////////

			//
			// chain gun
			//

			if (number == 0)
			{
				if ((weapon_sub_type == selected_weapon) && (!damaged))
				{
					draw_sprite (61, 360, 133, 327, 14, 13);
				}
			}
			else
			{
				if ((weapon_sub_type == selected_weapon) && (!damaged))
				{
					draw_sprite (61, 360, 148, 327, 14, 13);
				}
				else
				{
					draw_sprite (61, 360, 163, 327, 13, 13);
				}
			}

			//
			// digits
			//

			hardpoint_x = 60;
			hardpoint_y = 377;

			sprintf (buffer, "%04d", number);

			if ((weapon_sub_type == selected_weapon) && (!damaged))
			{
				v = 276;
			}
			else
			{
				v = 283;
			}

			if (buffer[0] == '0')
			{
				u = 184 + (9 * 5);
			}
			else
			{
				u = 184 + ((buffer[0] - '1') * 5);
			}

			draw_sprite (hardpoint_x, hardpoint_y, u, v, 4, 6);

			if (buffer[1] == '0')
			{
				u = 184 + (9 * 5);
			}
			else
			{
				u = 184 + ((buffer[1] - '1') * 5);
			}

			draw_sprite (hardpoint_x + 4, hardpoint_y, u, v, 4, 6);

			if (buffer[2] == '0')
			{
				u = 184 + (9 * 5);
			}
			else
			{
				u = 184 + ((buffer[2] - '1') * 5);
			}

			draw_sprite (hardpoint_x + 8, hardpoint_y, u, v, 4, 6);

			if (buffer[3] == '0')
			{
				u = 184 + (9 * 5);
			}
			else
			{
				u = 184 + ((buffer[3] - '1') * 5);
			}

			draw_sprite (hardpoint_x + 12, hardpoint_y, u, v, 4, 6);

			//
			// damage cross
			//

			if (damaged)
			{
				draw_sprite (60, 361, 169, 290, 16, 16);
			}
		}
	}

	////////////////////////////////////////////////////////////////////////////////
	//
	// Hydras
	//
	////////////////////////////////////////////////////////////////////////////////

	if ((weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_HYDRA70_M255) || (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_HYDRA70_M261))
	{
		if (draw_large_mfd)
		{
			////////////////////////////////////////
			//
			// LARGE
			//
			////////////////////////////////////////

			//
			// rocket pod
			//

			switch (heading_depth)
			{
				case APACHE_LHS_INNER_PYLON:
				{
					hardpoint_x = 50;
					hardpoint_y = 177;

					break;
				}
				case APACHE_RHS_INNER_PYLON:
				{
					hardpoint_x = 188;
					hardpoint_y = 177;

					break;
				}
				case APACHE_LHS_OUTER_PYLON:
				{
					hardpoint_x = 18;
					hardpoint_y = 177;

					break;
				}
				case APACHE_RHS_OUTER_PYLON:
				{
					hardpoint_x = 220;
					hardpoint_y = 177;

					break;
				}
			}

			if (number == 0)
			{
				if ((weapon_sub_type == selected_weapon) && (!damaged))
				{
					draw_sprite (hardpoint_x, hardpoint_y, 262, 99, 26, 33);
				}
				else
				{
					draw_sprite (hardpoint_x, hardpoint_y, 319, 99, 26, 33);
				}
			}
			else
			{
				if ((weapon_sub_type == selected_weapon) && (!damaged))
				{
					draw_sprite (hardpoint_x, hardpoint_y, 291, 99, 26, 33);
				}
				else
				{
					draw_sprite (hardpoint_x, hardpoint_y, 347, 99, 26, 33);
				}

				//
				// digits
				//

				hardpoint_x += 4;
				hardpoint_y += 14;

				sprintf (buffer, "%02d", number);

				if ((weapon_sub_type == selected_weapon) && (!damaged))
				{
					v = 32;
				}
				else
				{
					v = 47;
				}

				if (buffer[0] == '0')
				{
					u = 263 + (9 * 10);
				}
				else
				{
					u = 263 + ((buffer[0] - '1') * 10);
				}

				draw_sprite (hardpoint_x, hardpoint_y, u, v, 8, 12);

				if (buffer[1] == '0')
				{
					u = 263 + (9 * 10);
				}
				else
				{
					u = 263 + ((buffer[1] - '1') * 10);
				}

				draw_sprite (hardpoint_x + 8, hardpoint_y, u, v, 8, 12);
			}

			//
			// damage cross
			//

			if (damaged)
			{
				switch (heading_depth)
				{
					case APACHE_LHS_INNER_PYLON:
					{
						draw_sprite (47, 181, 334, 61, 32, 32);

						break;
					}
					case APACHE_RHS_INNER_PYLON:
					{
						draw_sprite (185, 181, 334, 61, 32, 32);

						break;
					}
					case APACHE_LHS_OUTER_PYLON:
					{
						draw_sprite (15, 181, 334, 61, 32, 32);

						break;
					}
					case APACHE_RHS_OUTER_PYLON:
					{
						draw_sprite (217, 181, 334, 61, 32, 32);

						break;
					}
				}
			}

			//
			// type
			//

			switch (heading_depth)
			{
				case APACHE_LHS_INNER_PYLON:
				{
					hardpoint_x = 47;
					hardpoint_y = 234;

					break;
				}
				case APACHE_RHS_INNER_PYLON:
				{
					hardpoint_x = 185;
					hardpoint_y = 234;

					break;
				}
				case APACHE_LHS_OUTER_PYLON:
				{
					hardpoint_x = 15;
					hardpoint_y = 234;

					break;
				}
				case APACHE_RHS_OUTER_PYLON:
				{
					hardpoint_x = 217;
					hardpoint_y = 234;

					break;
				}
			}

			if (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_HYDRA70_M255)
			{
				if ((weapon_sub_type == selected_weapon) && (!damaged))
				{
					draw_sprite (hardpoint_x, hardpoint_y, 262, 17, 31, 12);
				}
				else
				{
					draw_sprite (hardpoint_x, hardpoint_y, 342, 17, 31, 12);
				}
			}
			else
			{
				if ((weapon_sub_type == selected_weapon) && (!damaged))
				{
					draw_sprite (hardpoint_x, hardpoint_y, 295, 17, 31, 12);
				}
				else
				{
					draw_sprite (hardpoint_x, hardpoint_y, 375, 17, 31, 12);
				}
			}
		}
		else
		{
			////////////////////////////////////////
			//
			// SMALL
			//
			////////////////////////////////////////

			//
			// rocket pod
			//

			switch (heading_depth)
			{
				case APACHE_LHS_INNER_PYLON:
				{
					hardpoint_x = 27;
					hardpoint_y = 348;

					break;
				}
				case APACHE_RHS_INNER_PYLON:
				{
					hardpoint_x = 96;
					hardpoint_y = 348;

					break;
				}
				case APACHE_LHS_OUTER_PYLON:
				{
					hardpoint_x = 11;
					hardpoint_y = 348;

					break;
				}
				case APACHE_RHS_OUTER_PYLON:
				{
					hardpoint_x = 112;
					hardpoint_y = 348;

					break;
				}
			}

			if (number == 0)
			{
				if ((weapon_sub_type == selected_weapon) && (!damaged))
				{
					draw_sprite (hardpoint_x, hardpoint_y, 133, 309, 13, 17);
				}
				else
				{
					draw_sprite (hardpoint_x, hardpoint_y, 161, 309, 13, 17);
				}
			}
			else
			{
				if ((weapon_sub_type == selected_weapon) && (!damaged))
				{
					draw_sprite (hardpoint_x, hardpoint_y, 147, 309, 13, 17);
				}
				else
				{
					draw_sprite (hardpoint_x, hardpoint_y, 175, 309, 13, 17);
				}

				//
				// digits
				//

				hardpoint_x += 2;
				hardpoint_y += 7;

				sprintf (buffer, "%02d", number);

				if ((weapon_sub_type == selected_weapon) && (!damaged))
				{
					v = 276;
				}
				else
				{
					v = 283;
				}

				if (buffer[0] == '0')
				{
					u = 133 + (9 * 5);
				}
				else
				{
					u = 133 + ((buffer[0] - '1') * 5);
				}

				draw_sprite (hardpoint_x, hardpoint_y, u, v, 4, 6);

				if (buffer[1] == '0')
				{
					u = 133 + (9 * 5);
				}
				else
				{
					u = 133 + ((buffer[1] - '1') * 5);
				}

				draw_sprite (hardpoint_x + 4, hardpoint_y, u, v, 4, 6);
			}

			//
			// damage cross
			//

			if (damaged)
			{
				switch (heading_depth)
				{
					case APACHE_LHS_INNER_PYLON:
					{
						draw_sprite (26, 350, 169, 290, 16, 16);

						break;
					}
					case APACHE_RHS_INNER_PYLON:
					{
						draw_sprite (95, 350, 169, 290, 16, 16);

						break;
					}
					case APACHE_LHS_OUTER_PYLON:
					{
						draw_sprite (10, 350, 169, 290, 16, 16);

						break;
					}
					case APACHE_RHS_OUTER_PYLON:
					{
						draw_sprite (111, 350, 169, 290, 16, 16);

						break;
					}
				}
			}

			//
			// type
			//

			switch (heading_depth)
			{
				case APACHE_LHS_INNER_PYLON:
				{
					hardpoint_x = 26;
					hardpoint_y = 377;

					break;
				}
				case APACHE_RHS_INNER_PYLON:
				{
					hardpoint_x = 95;
					hardpoint_y = 377;

					break;
				}
				case APACHE_LHS_OUTER_PYLON:
				{
					hardpoint_x = 10;
					hardpoint_y = 377;

					break;
				}
				case APACHE_RHS_OUTER_PYLON:
				{
					hardpoint_x = 111;
					hardpoint_y = 377;

					break;
				}
			}

			if (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_HYDRA70_M255)
			{
				if ((weapon_sub_type == selected_weapon) && (!damaged))
				{
					draw_sprite (hardpoint_x, hardpoint_y, 133, 268, 15, 6);
				}
				else
				{
					draw_sprite (hardpoint_x, hardpoint_y, 173, 268, 15, 6);
				}
			}
			else
			{
				if ((weapon_sub_type == selected_weapon) && (!damaged))
				{
					draw_sprite (hardpoint_x, hardpoint_y, 149, 268, 15, 6);
				}
				else
				{
					draw_sprite (hardpoint_x, hardpoint_y, 189, 268, 15, 6);
				}
			}
		}
	}

	////////////////////////////////////////////////////////////////////////////////
	//
	// Hellfires
	//
	////////////////////////////////////////////////////////////////////////////////

	if ((weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_AGM114L_LONGBOW_HELLFIRE) || (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_AGM114K_HELLFIRE_II))
	{
		if (draw_large_mfd)
		{
			////////////////////////////////////////
			//
			// LARGE
			//
			////////////////////////////////////////

			//
			// pylon
			//

			switch (heading_depth)
			{
				case APACHE_LHS_INNER_PYLON:
				{
					hardpoint_x = 53;
					hardpoint_y = 177;

					break;
				}
				case APACHE_RHS_INNER_PYLON:
				{
					hardpoint_x = 191;
					hardpoint_y = 177;

					break;
				}
				case APACHE_LHS_OUTER_PYLON:
				{
					hardpoint_x = 21;
					hardpoint_y = 177;

					break;
				}
				case APACHE_RHS_OUTER_PYLON:
				{
					hardpoint_x = 223;
					hardpoint_y = 177;

					break;
				}
			}

			if ((weapon_sub_type == selected_weapon) && (!damaged))
			{
				draw_sprite (hardpoint_x, hardpoint_y, 262, 79, 20, 18);
			}
			else
			{
				draw_sprite (hardpoint_x, hardpoint_y, 284, 79, 20, 18);
			}

			//
			// missiles
			//

			switch (heading_depth)
			{
				case APACHE_LHS_INNER_PYLON:
				case APACHE_LHS_OUTER_PYLON:
				{
					if (number > 3)
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (hardpoint_x - 6, hardpoint_y + 19, 280, 61, 16, 16);
						}
						else
						{
							draw_sprite (hardpoint_x - 6, hardpoint_y + 19, 316, 61, 16, 16);
						}
					}
					else
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (hardpoint_x - 6, hardpoint_y + 19, 262, 61, 16, 16);
						}
						else
						{
							draw_sprite (hardpoint_x - 6, hardpoint_y + 19, 298, 61, 16, 16);
						}
					}

					if (number > 2)
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (hardpoint_x + 10, hardpoint_y + 19, 280, 61, 16, 16);
						}
						else
						{
							draw_sprite (hardpoint_x + 10, hardpoint_y + 19, 316, 61, 16, 16);
						}
					}
					else
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (hardpoint_x + 10, hardpoint_y + 19, 262, 61, 16, 16);
						}
						else
						{
							draw_sprite (hardpoint_x + 10, hardpoint_y + 19, 298, 61, 16, 16);
						}
					}

					if (number > 1)
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (hardpoint_x - 6, hardpoint_y + 35, 280, 61, 16, 16);
						}
						else
						{
							draw_sprite (hardpoint_x - 6, hardpoint_y + 35, 316, 61, 16, 16);
						}
					}
					else
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (hardpoint_x - 6, hardpoint_y + 35, 262, 61, 16, 16);
						}
						else
						{
							draw_sprite (hardpoint_x - 6, hardpoint_y + 35, 298, 61, 16, 16);
						}
					}

					if (number > 0)
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (hardpoint_x + 10, hardpoint_y + 35, 280, 61, 16, 16);
						}
						else
						{
							draw_sprite (hardpoint_x + 10, hardpoint_y + 35, 316, 61, 16, 16);
						}
					}
					else
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (hardpoint_x + 10, hardpoint_y + 35, 262, 61, 16, 16);
						}
						else
						{
							draw_sprite (hardpoint_x + 10, hardpoint_y + 35, 298, 61, 16, 16);
						}
					}

					break;
				}
				case APACHE_RHS_INNER_PYLON:
				case APACHE_RHS_OUTER_PYLON:
				{
					if (number > 3)
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (hardpoint_x + 10, hardpoint_y + 19, 280, 61, 16, 16);
						}
						else
						{
							draw_sprite (hardpoint_x + 10, hardpoint_y + 19, 316, 61, 16, 16);
						}
					}
					else
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (hardpoint_x + 10, hardpoint_y + 19, 262, 61, 16, 16);
						}
						else
						{
							draw_sprite (hardpoint_x + 10, hardpoint_y + 19, 298, 61, 16, 16);
						}
					}

					if (number > 2)
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (hardpoint_x - 6, hardpoint_y + 19, 280, 61, 16, 16);
						}
						else
						{
							draw_sprite (hardpoint_x - 6, hardpoint_y + 19, 316, 61, 16, 16);
						}
					}
					else
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (hardpoint_x - 6, hardpoint_y + 19, 262, 61, 16, 16);
						}
						else
						{
							draw_sprite (hardpoint_x - 6, hardpoint_y + 19, 298, 61, 16, 16);
						}
					}

					if (number > 1)
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (hardpoint_x + 10, hardpoint_y + 35, 280, 61, 16, 16);
						}
						else
						{
							draw_sprite (hardpoint_x + 10, hardpoint_y + 35, 316, 61, 16, 16);
						}
					}
					else
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (hardpoint_x + 10, hardpoint_y + 35, 262, 61, 16, 16);
						}
						else
						{
							draw_sprite (hardpoint_x + 10, hardpoint_y + 35, 298, 61, 16, 16);
						}
					}

					if (number > 0)
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (hardpoint_x - 6, hardpoint_y + 35, 280, 61, 16, 16);
						}
						else
						{
							draw_sprite (hardpoint_x - 6, hardpoint_y + 35, 316, 61, 16, 16);
						}
					}
					else
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (hardpoint_x - 6, hardpoint_y + 35, 262, 61, 16, 16);
						}
						else
						{
							draw_sprite (hardpoint_x - 6, hardpoint_y + 35, 298, 61, 16, 16);
						}
					}

					break;
				}
			}

			//
			// damage cross
			//

			if (damaged)
			{
				switch (heading_depth)
				{
					case APACHE_LHS_INNER_PYLON:
					{
						draw_sprite (47, 196, 334, 61, 32, 32);

						break;
					}
					case APACHE_RHS_INNER_PYLON:
					{
						draw_sprite (185, 196, 334, 61, 32, 32);

						break;
					}
					case APACHE_LHS_OUTER_PYLON:
					{
						draw_sprite (15, 196, 334, 61, 32, 32);

						break;
					}
					case APACHE_RHS_OUTER_PYLON:
					{
						draw_sprite (217, 196, 334, 61, 32, 32);

						break;
					}
				}
			}

			//
			// type
			//

			switch (heading_depth)
			{
				case APACHE_LHS_INNER_PYLON:
				{
					hardpoint_x = 47;
					hardpoint_y = 234;

					break;
				}
				case APACHE_RHS_INNER_PYLON:
				{
					hardpoint_x = 185;
					hardpoint_y = 234;

					break;
				}
				case APACHE_LHS_OUTER_PYLON:
				{
					hardpoint_x = 15;
					hardpoint_y = 234;

					break;
				}
				case APACHE_RHS_OUTER_PYLON:
				{
					hardpoint_x = 217;
					hardpoint_y = 234;

					break;
				}
			}

			if (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_AGM114K_HELLFIRE_II)
			{
				if ((weapon_sub_type == selected_weapon) && (!damaged))
				{
					draw_sprite (hardpoint_x, hardpoint_y, 262, 3, 31, 12);
				}
				else
				{
					draw_sprite (hardpoint_x, hardpoint_y, 342, 3, 31, 12);
				}
			}
			else
			{
				if ((weapon_sub_type == selected_weapon) && (!damaged))
				{
					draw_sprite (hardpoint_x, hardpoint_y, 295, 3, 31, 12);
				}
				else
				{
					draw_sprite (hardpoint_x, hardpoint_y, 375, 3, 31, 12);
				}
			}
		}
		else
		{
			////////////////////////////////////////
			//
			// SMALL
			//
			////////////////////////////////////////

			//
			// pylon
			//

			switch (heading_depth)
			{
				case APACHE_LHS_INNER_PYLON:
				{
					hardpoint_x = 29;
					hardpoint_y = 348;

					break;
				}
				case APACHE_RHS_INNER_PYLON:
				{
					hardpoint_x = 98;
					hardpoint_y = 348;

					break;
				}
				case APACHE_LHS_OUTER_PYLON:
				{
					hardpoint_x = 13;
					hardpoint_y = 348;

					break;
				}
				case APACHE_RHS_OUTER_PYLON:
				{
					hardpoint_x = 114;
					hardpoint_y = 348;

					break;
				}
			}

			if ((weapon_sub_type == selected_weapon) && (!damaged))
			{
				draw_sprite (hardpoint_x, hardpoint_y, 133, 299, 10, 9);
			}
			else
			{
				draw_sprite (hardpoint_x, hardpoint_y, 144, 299, 10, 9);
			}

			//
			// missiles
			//

			switch (heading_depth)
			{
				case APACHE_LHS_INNER_PYLON:
				case APACHE_LHS_OUTER_PYLON:
				{
					if (number > 3)
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (hardpoint_x - 3, hardpoint_y + 10, 142, 290, 8, 8);
						}
						else
						{
							draw_sprite (hardpoint_x - 3, hardpoint_y + 10, 160, 290, 8, 8);
						}
					}
					else
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (hardpoint_x - 3, hardpoint_y + 10, 133, 290, 8, 8);
						}
						else
						{
							draw_sprite (hardpoint_x - 3, hardpoint_y + 10, 151, 290, 8, 8);
						}
					}

					if (number > 2)
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (hardpoint_x + 5, hardpoint_y + 10, 142, 290, 8, 8);
						}
						else
						{
							draw_sprite (hardpoint_x + 5, hardpoint_y + 10, 160, 290, 8, 8);
						}
					}
					else
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (hardpoint_x + 5, hardpoint_y + 10, 133, 290, 8, 8);
						}
						else
						{
							draw_sprite (hardpoint_x + 5, hardpoint_y + 10, 151, 290, 8, 8);
						}
					}

					if (number > 1)
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (hardpoint_x - 3, hardpoint_y + 18, 142, 290, 8, 8);
						}
						else
						{
							draw_sprite (hardpoint_x - 3, hardpoint_y + 18, 160, 290, 8, 8);
						}
					}
					else
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (hardpoint_x - 3, hardpoint_y + 18, 133, 290, 8, 8);
						}
						else
						{
							draw_sprite (hardpoint_x - 3, hardpoint_y + 18, 151, 290, 8, 8);
						}
					}

					if (number > 0)
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (hardpoint_x + 5, hardpoint_y + 18, 142, 290, 8, 8);
						}
						else
						{
							draw_sprite (hardpoint_x + 5, hardpoint_y + 18, 160, 290, 8, 8);
						}
					}
					else
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (hardpoint_x + 5, hardpoint_y + 18, 133, 290, 8, 8);
						}
						else
						{
							draw_sprite (hardpoint_x + 5, hardpoint_y + 18, 151, 290, 8, 8);
						}
					}

					break;
				}
				case APACHE_RHS_INNER_PYLON:
				case APACHE_RHS_OUTER_PYLON:
				{
					if (number > 3)
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (hardpoint_x + 5, hardpoint_y + 10, 142, 290, 8, 8);
						}
						else
						{
							draw_sprite (hardpoint_x + 5, hardpoint_y + 10, 160, 290, 8, 8);
						}
					}
					else
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (hardpoint_x + 5, hardpoint_y + 10, 133, 290, 8, 8);
						}
						else
						{
							draw_sprite (hardpoint_x + 5, hardpoint_y + 10, 151, 290, 8, 8);
						}
					}

					if (number > 2)
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (hardpoint_x - 3, hardpoint_y + 10, 142, 290, 8, 8);
						}
						else
						{
							draw_sprite (hardpoint_x - 3, hardpoint_y + 10, 160, 290, 8, 8);
						}
					}
					else
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (hardpoint_x - 3, hardpoint_y + 10, 133, 290, 8, 8);
						}
						else
						{
							draw_sprite (hardpoint_x - 3, hardpoint_y + 10, 151, 290, 8, 8);
						}
					}

					if (number > 1)
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (hardpoint_x + 5, hardpoint_y + 18, 142, 290, 8, 8);
						}
						else
						{
							draw_sprite (hardpoint_x + 5, hardpoint_y + 18, 160, 290, 8, 8);
						}
					}
					else
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (hardpoint_x + 5, hardpoint_y + 18, 133, 290, 8, 8);
						}
						else
						{
							draw_sprite (hardpoint_x + 5, hardpoint_y + 18, 151, 290, 8, 8);
						}
					}

					if (number > 0)
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (hardpoint_x - 3, hardpoint_y + 18, 142, 290, 8, 8);
						}
						else
						{
							draw_sprite (hardpoint_x - 3, hardpoint_y + 18, 160, 290, 8, 8);
						}
					}
					else
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (hardpoint_x - 3, hardpoint_y + 18, 133, 290, 8, 8);
						}
						else
						{
							draw_sprite (hardpoint_x - 3, hardpoint_y + 18, 151, 290, 8, 8);
						}
					}

					break;
				}
			}

			//
			// damage cross
			//

			if (damaged)
			{
				switch (heading_depth)
				{
					case APACHE_LHS_INNER_PYLON:
					{
						draw_sprite (26, 358, 169, 290, 16, 16);

						break;
					}
					case APACHE_RHS_INNER_PYLON:
					{
						draw_sprite (95, 358, 169, 290, 16, 16);

						break;
					}
					case APACHE_LHS_OUTER_PYLON:
					{
						draw_sprite (10, 358, 169, 290, 16, 16);

						break;
					}
					case APACHE_RHS_OUTER_PYLON:
					{
						draw_sprite (111, 358, 169, 290, 16, 16);

						break;
					}
				}
			}

			//
			// type
			//

			switch (heading_depth)
			{
				case APACHE_LHS_INNER_PYLON:
				{
					hardpoint_x = 26;
					hardpoint_y = 377;

					break;
				}
				case APACHE_RHS_INNER_PYLON:
				{
					hardpoint_x = 95;
					hardpoint_y = 377;

					break;
				}
				case APACHE_LHS_OUTER_PYLON:
				{
					hardpoint_x = 10;
					hardpoint_y = 377;

					break;
				}
				case APACHE_RHS_OUTER_PYLON:
				{
					hardpoint_x = 111;
					hardpoint_y = 377;

					break;
				}
			}

			if (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_AGM114K_HELLFIRE_II)
			{
				if ((weapon_sub_type == selected_weapon) && (!damaged))
				{
					draw_sprite (hardpoint_x, hardpoint_y, 133, 261, 15, 6);
				}
				else
				{
					draw_sprite (hardpoint_x, hardpoint_y, 173, 261, 15, 6);
				}
			}
			else
			{
				if ((weapon_sub_type == selected_weapon) && (!damaged))
				{
					draw_sprite (hardpoint_x, hardpoint_y, 149, 261, 15, 6);
				}
				else
				{
					draw_sprite (hardpoint_x, hardpoint_y, 189, 261, 15, 6);
				}
			}
		}
	}

	////////////////////////////////////////////////////////////////////////////////
	//
	// Stingers
	//
	////////////////////////////////////////////////////////////////////////////////

	if (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_AIM92_STINGER)
	{
		if (draw_large_mfd)
		{
			////////////////////////////////////////
			//
			// LARGE
			//
			////////////////////////////////////////

			//
			// missiles
			//

			switch (heading_depth)
			{
				case APACHE_LHS_WING_TIP_MOUNT:
				{
					if (number > 1)
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (6, 144, 280, 61, 16, 16);
						}
						else
						{
							draw_sprite (6, 144, 316, 61, 16, 16);
						}
					}
					else
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (6, 144, 262, 61, 16, 16);
						}
						else
						{
							draw_sprite (6, 144, 298, 61, 16, 16);
						}
					}

					if (number > 0)
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (6, 161, 280, 61, 16, 16);
						}
						else
						{
							draw_sprite (6, 161, 316, 61, 16, 16);
						}
					}
					else
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (6, 161, 262, 61, 16, 16);
						}
						else
						{
							draw_sprite (6, 161, 298, 61, 16, 16);
						}
					}

					break;
				}
				case APACHE_RHS_WING_TIP_MOUNT:
				{
					if (number > 1)
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (242, 144, 280, 61, 16, 16);
						}
						else
						{
							draw_sprite (242, 144, 316, 61, 16, 16);
						}
					}
					else
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (242, 144, 262, 61, 16, 16);
						}
						else
						{
							draw_sprite (242, 144, 298, 61, 16, 16);
						}
					}

					if (number > 0)
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (242, 161, 280, 61, 16, 16);
						}
						else
						{
							draw_sprite (242, 161, 316, 61, 16, 16);
						}
					}
					else
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (242, 161, 262, 61, 16, 16);
						}
						else
						{
							draw_sprite (242, 161, 298, 61, 16, 16);
						}
					}

					break;
				}
			}

			//
			// damage cross
			//

			if (damaged)
			{
				switch (heading_depth)
				{
					case APACHE_LHS_WING_TIP_MOUNT:
					{
						draw_sprite (6, 144, 368, 61, 17, 33);

						break;
					}
					case APACHE_RHS_WING_TIP_MOUNT:
					{
						draw_sprite (241, 144, 368, 61, 17, 33);

						break;
					}
				}
			}
		}
		else
		{
			////////////////////////////////////////
			//
			// SMALL
			//
			////////////////////////////////////////

			//
			// missiles
			//

			switch (heading_depth)
			{
				case APACHE_LHS_WING_TIP_MOUNT:
				{
					if (number > 1)
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (5, 332, 142, 290, 8, 8);
						}
						else
						{
							draw_sprite (5, 332, 160, 290, 8, 8);
						}
					}
					else
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (5, 332, 133, 290, 8, 8);
						}
						else
						{
							draw_sprite (5, 332, 151, 290, 8, 8);
						}
					}

					if (number > 0)
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (5, 340, 142, 290, 8, 8);
						}
						else
						{
							draw_sprite (5, 340, 160, 290, 8, 8);
						}
					}
					else
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (5, 340, 133, 290, 8, 8);
						}
						else
						{
							draw_sprite (5, 340, 151, 290, 8, 8);
						}
					}

					break;
				}
				case APACHE_RHS_WING_TIP_MOUNT:
				{
					if (number > 1)
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (123, 332, 142, 290, 8, 8);
						}
						else
						{
							draw_sprite (123, 332, 160, 290, 8, 8);
						}
					}
					else
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (123, 332, 133, 290, 8, 8);
						}
						else
						{
							draw_sprite (123, 332, 151, 290, 8, 8);
						}
					}

					if (number > 0)
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (123, 340, 142, 290, 8, 8);
						}
						else
						{
							draw_sprite (123, 340, 160, 290, 8, 8);
						}
					}
					else
					{
						if ((weapon_sub_type == selected_weapon) && (!damaged))
						{
							draw_sprite (123, 340, 133, 290, 8, 8);
						}
						else
						{
							draw_sprite (123, 340, 151, 290, 8, 8);
						}
					}

					break;
				}
			}

			//
			// damage cross
			//

			if (damaged)
			{
				switch (heading_depth)
				{
					case APACHE_LHS_WING_TIP_MOUNT:
					{
						draw_sprite (5, 332, 186, 290, 8, 17);

						break;
					}
					case APACHE_RHS_WING_TIP_MOUNT:
					{
						draw_sprite (122, 332, 186, 290, 8, 17);

						break;
					}
				}
			}
		}
	}

	////////////////////////////////////////////////////////////////////////////////
	//
	// Chaff
	//
	////////////////////////////////////////////////////////////////////////////////

	if (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_CHAFF)
	{
		if (draw_large_mfd)
		{
			////////////////////////////////////////
			//
			// LARGE
			//
			////////////////////////////////////////

			//
			// digits
			//

			if ((number > 0) && (!damaged))
			{
				draw_sprite (94, 160, 483, 3, 18, 14);

				v = 32;
			}
			else
			{
				v = 47;
			}

			sprintf (buffer, "%02d", number);

			if (buffer[0] == '0')
			{
				u = 364 + (9 * 10);
			}
			else
			{
				u = 364 + ((buffer[0] - '1') * 10);
			}

			draw_sprite (112, 161, u, v, 8, 12);

			if (buffer[1] == '0')
			{
				u = 364 + (9 * 10);
			}
			else
			{
				u = 364 + ((buffer[1] - '1') * 10);
			}

			draw_sprite (121, 161, u, v, 8, 12);

			//
			// damage cross
			//

			if (damaged)
			{
				draw_sprite (96, 159, 387, 61, 33, 17);
			}
		}
		else
		{
			////////////////////////////////////////
			//
			// SMALL
			//
			////////////////////////////////////////

			//
			// digits
			//

			if ((number > 0) && (!damaged))
			{
				draw_sprite (49, 340, 243, 261, 9, 7);

				v = 276;
			}
			else
			{
				v = 283;
			}

			sprintf (buffer, "%02d", number);

			if (buffer[0] == '0')
			{
				u = 184 + (9 * 5);
			}
			else
			{
				u = 184 + ((buffer[0] - '1') * 5);
			}

			draw_sprite (58, 341, u, v, 4, 6);

			if (buffer[1] == '0')
			{
				u = 184 + (9 * 5);
			}
			else
			{
				u = 184 + ((buffer[1] - '1') * 5);
			}

			draw_sprite (62, 341, u, v, 4, 6);

			//
			// damage cross
			//

			if (damaged)
			{
				draw_sprite (49, 339, 196, 290, 17, 9);
			}
		}
	}

	////////////////////////////////////////////////////////////////////////////////
	//
	// Flare
	//
	////////////////////////////////////////////////////////////////////////////////

	if (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_FLARE)
	{
		if (draw_large_mfd)
		{
			////////////////////////////////////////
			//
			// LARGE
			//
			////////////////////////////////////////

			//
			// digits
			//

			if ((number > 0) && (!damaged))
			{
				draw_sprite (134, 160, 503, 3, 15, 14);

				v = 32;
			}
			else
			{
				v = 47;
			}

			sprintf (buffer, "%02d", number);

			if (buffer[0] == '0')
			{
				u = 364 + (9 * 10);
			}
			else
			{
				u = 364 + ((buffer[0] - '1') * 10);
			}

			draw_sprite (149, 161, u, v, 8, 12);

			if (buffer[1] == '0')
			{
				u = 364 + (9 * 10);
			}
			else
			{
				u = 364 + ((buffer[1] - '1') * 10);
			}

			draw_sprite (158, 161, u, v, 8, 12);

			//
			// damage cross
			//

			if (damaged)
			{
				draw_sprite (135, 159, 387, 61, 33, 17);
			}
		}
		else
		{
			////////////////////////////////////////
			//
			// SMALL
			//
			////////////////////////////////////////

			//
			// digits
			//

			if ((number > 0) && (!damaged))
			{
				draw_sprite (69, 340, 253, 261, 8, 7);

				v = 276;
			}
			else
			{
				v = 283;
			}

			sprintf (buffer, "%02d", number);

			if (buffer[0] == '0')
			{
				u = 184 + (9 * 5);
			}
			else
			{
				u = 184 + ((buffer[0] - '1') * 5);
			}

			draw_sprite (77, 341, u, v, 4, 6);

			if (buffer[1] == '0')
			{
				u = 184 + (9 * 5);
			}
			else
			{
				u = 184 + ((buffer[1] - '1') * 5);
			}

			draw_sprite (81, 341, u, v, 4, 6);

			//
			// damage cross
			//

			if (damaged)
			{
				draw_sprite (69, 339, 196, 290, 17, 9);
			}
		}
	}
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if 0
static void draw_bordered_box(float x1_c, float y1_c, float x2_c, float y2_c, rgb_colour fill_colour, rgb_colour border_colour)
{
	int x1, x2, y1, y2;
	int inner_x1, inner_x2, inner_y1, inner_y2;

	get_2d_int_screen_coordinates (min(x1_c, x2_c), max(y1_c, y2_c), &x1, &y1);
	get_2d_int_screen_coordinates (max(x1_c, x2_c), min(y1_c, y2_c), &x2, &y2);

	inner_x1 = x1+1;
	inner_x2 = x2-1;
	inner_y1 = y1+1;
	inner_y2 = y2-1;

	if (inner_x1 < inner_x2 && inner_y1 < inner_y2)
		set_block(inner_x1 * 2, inner_y1, inner_x2 * 2, inner_y2, fill_colour);

	draw_line(x1, y1, x2, y1, border_colour);
	draw_line(x1, y1, x1, y2, border_colour);
	draw_line(x1, y2, x2, y2, border_colour);
	draw_line(x2, y1, x2, y2, border_colour);
}

static void draw_box(float x1_c, float y1_c, float x2_c, float y2_c, int filled, rgb_colour colour)
{
	float x1, x2, y1, y2;

	get_2d_float_screen_coordinates (x1_c, y1_c, &x1, &y1);
	get_2d_float_screen_coordinates (x2_c, y2_c, &x2, &y2);

	if (filled)
	{
		float x_min = min(x1, x2), x_max = max(x1, x2);
		float y_min = min(y1, y2), y_max = max(y1, y2);

		// set block likes to have its smallest arguments first
		set_block(x_min, y_min, x_max, y_max, colour);
	}
	else
	{
		draw_line(x1, y1, x2, y1, colour);
		draw_line(x1, y1, x1, y2, colour);
		draw_line(x1, y2, x2, y2, colour);
		draw_line(x2, y1, x2, y2, colour);
	}
}
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_helicopter_diagram(int draw_engines)
{
	float y = draw_engines ? 0.0 : -0.3;

	draw_2d_mono_sprite(apache_diagram_nose_mask, 0.0, 1.0 + y, MFD_COLOUR5);
	draw_2d_mono_sprite(apache_diagram_nose, 0.0, 1.0 + y, MFD_COLOUR1);

	// wings
	draw_2d_half_thick_line(-0.24, 0.44 + y, -0.80, 0.42 + y, MFD_COLOUR1);
	draw_2d_half_thick_line(-0.80, 0.42 + y, -0.80, 0.15 + y, MFD_COLOUR1);

	draw_2d_half_thick_line( 0.24, 0.44 + y,  0.80, 0.42 + y, MFD_COLOUR1);
	draw_2d_half_thick_line( 0.80, 0.42 + y,  0.80, 0.15 + y, MFD_COLOUR1);

	// engines
	if (draw_engines)
	{
		// aft end of wings
		draw_2d_half_thick_line(-0.80, 0.15 + y, -0.39, 0.10 + y, MFD_COLOUR1);
		draw_2d_half_thick_line( 0.80, 0.15 + y,  0.39, 0.10 + y, MFD_COLOUR1);

		set_mono_font_colour(MFD_COLOUR1);
		// left engine
		draw_2d_mono_sprite(apache_diagram_engine_nascel_mask, -0.275, 0.25 + y, MFD_COLOUR5);
		draw_2d_mono_sprite(apache_diagram_engine_nascel, -0.275, 0.25 + y, MFD_COLOUR1);

		draw_2d_half_thick_line(-0.40, 0.25 + y, -0.15, 0.25 + y, MFD_COLOUR1);
		draw_2d_half_thick_line(-0.40, 0.25 + y, -0.37, 0.0 + y, MFD_COLOUR1);
		draw_2d_half_thick_line(-0.15, 0.25 + y, -0.18, 0.0 + y, MFD_COLOUR1);
		draw_2d_half_thick_line(-0.37, 0.0 + y,  -0.40, -0.25 + y, MFD_COLOUR1);
		draw_2d_half_thick_line(-0.18, 0.0 + y,  -0.15, -0.25 + y, MFD_COLOUR1);
		draw_2d_half_thick_line(-0.40, -0.25 + y,-0.15, -0.25 + y, MFD_COLOUR1);

		set_mono_font_type (MONO_FONT_TYPE_12X20);
		set_2d_mono_font_position(-0.27, 0.0 + y);
		set_mono_font_rel_position(-6.0, -8.0);
		print_mono_font_char('1');

		// right engine
		draw_2d_mono_sprite(apache_diagram_engine_nascel_mask, 0.275, 0.25 + y, MFD_COLOUR5);
		draw_2d_mono_sprite(apache_diagram_engine_nascel, 0.275, 0.25 + y, MFD_COLOUR1);

		draw_2d_half_thick_line( 0.40, 0.25 + y,  0.15, 0.25 + y, MFD_COLOUR1);
		draw_2d_half_thick_line( 0.40, 0.25 + y,  0.37, 0.0 + y, MFD_COLOUR1);
		draw_2d_half_thick_line( 0.15, 0.25 + y,  0.18, 0.0 + y, MFD_COLOUR1);
		draw_2d_half_thick_line( 0.37, 0.0 + y,   0.40, -0.25 + y, MFD_COLOUR1);
		draw_2d_half_thick_line( 0.18, 0.0 + y,   0.15, -0.25 + y, MFD_COLOUR1);
		draw_2d_half_thick_line( 0.40, -0.25 + y, 0.15, -0.25 + y, MFD_COLOUR1);

		set_2d_mono_font_position(0.27, 0.0 + y);
		set_mono_font_rel_position(-6.0, -8.0);
		print_mono_font_char('2');

		draw_2d_half_thick_line(-0.24, -0.25 + y, -0.24, -0.38 + y, MFD_COLOUR1);
		draw_2d_half_thick_line( 0.24, -0.25 + y,  0.24, -0.38 + y, MFD_COLOUR1);
		draw_2d_half_thick_line(-0.24, -0.38 + y, 0.24, -0.38 + y, MFD_COLOUR1);
	}
	else
	{
		// aft end of wings
		draw_2d_half_thick_line(-0.80, 0.15 + y, -0.24, 0.08 + y, MFD_COLOUR1);
		draw_2d_half_thick_line( 0.80, 0.15 + y,  0.24, 0.08 + y, MFD_COLOUR1);

		// afterbody
		draw_2d_half_thick_line(-0.24, 0.08 + y, -0.24, -0.32 + y, MFD_COLOUR1);
		draw_2d_half_thick_line( 0.24, 0.08 + y,  0.24, -0.32 + y, MFD_COLOUR1);
		draw_2d_half_thick_line(-0.24, -0.32 + y, 0.24, -0.32 + y, MFD_COLOUR1);
	}
}

static void draw_fuel_page_mfd(void)
{
	char buffer[80];
	char* s = NULL;
	float fuel_flow1, fuel_flow2;
	float internal_fuel, total_fuel;
	float endurance;
	rgb_colour colour = MFD_COLOUR1;

	draw_helicopter_diagram(TRUE);

	if (forward_fuel_tank_low_fuel())
		colour = MFD_COLOUR_YELLOW;

	// forward tank
	draw_2d_box(-0.20, 0.8, 0.20, 0.6, FALSE, TRUE, colour);

	set_mono_font_type (MONO_FONT_TYPE_14X21);
	set_mono_font_colour(colour);

	sprintf(buffer, "%3.0f0", kilograms_to_pounds(get_fuel_quantity(FUEL_TANK_FWD)) * 0.1);
	set_2d_mono_font_position(-0.14, 0.7);
	set_mono_font_rel_position (0.0, -10.0);
	print_mono_font_string(buffer);

	if (aft_fuel_tank_low_fuel())
		colour = MFD_COLOUR_YELLOW;
	else
		colour = MFD_COLOUR1;
	set_mono_font_colour(colour);

	// aft tank
	draw_2d_box(-0.15, -0.01, 0.15, -0.35, FALSE, TRUE, colour);

	sprintf(buffer, "%3.0f0", kilograms_to_pounds(get_fuel_quantity(FUEL_TANK_AFT)) * 0.1);
	set_2d_mono_font_position(-0.14, -0.2);
	set_mono_font_rel_position (0.0, -10.0);
	print_mono_font_string(buffer);

	set_mono_font_type (MONO_FONT_TYPE_12X20);
	set_mono_font_colour(MFD_COLOUR1);

	// transfer box
	if (!get_auto_fuel_transfer())
	{
		s = "XFER";
		set_2d_mono_font_position(0.0, 0.3);
		set_mono_font_rel_position(-0.5 * get_mono_font_string_width(s), -8.0);
		print_mono_font_string(s);

		if (get_fuel_transfer(FUEL_TANK_AFT) == FUEL_TANK_FWD)
		{
			draw_2d_mono_sprite(fuel_transfer_fwd_open_mask, 0.0, 0.38, MFD_COLOUR5);
			draw_2d_mono_sprite(fuel_transfer_fwd_open, 0.0, 0.38, MFD_COLOUR1);
		}
		else
		{
			draw_2d_mono_sprite(fuel_transfer_fwd_closed_mask, 0.0, 0.38, MFD_COLOUR5);
			draw_2d_mono_sprite(fuel_transfer_fwd_closed, 0.0, 0.38, MFD_COLOUR1);
		}

		if (get_fuel_transfer(FUEL_TANK_FWD) == FUEL_TANK_AFT)
		{
			draw_2d_mono_sprite(fuel_transfer_aft_open_mask, 0.0, 0.22, MFD_COLOUR5);
			draw_2d_mono_sprite(fuel_transfer_aft_open, 0.0, 0.22, MFD_COLOUR1);
		}
		else
		{
			draw_2d_mono_sprite(fuel_transfer_aft_closed_mask, 0.0, 0.22, MFD_COLOUR5);
			draw_2d_mono_sprite(fuel_transfer_aft_closed, 0.0, 0.22, MFD_COLOUR1);
		}

		draw_2d_half_thick_line(-1.2, 0.90, -0.9, 0.90, MFD_COLOUR1);
		draw_2d_half_thick_line(-1.2, 0.0, -0.9, 0.0, MFD_COLOUR1);

		print_vertical_mono_font_string(-0.9, 0.82, "TRANSFER", -0.5, FALSE);

		draw_2d_half_thick_line(-0.9, 0.9, -0.9, 0.82, MFD_COLOUR1);
		draw_2d_half_thick_line(-0.9, -0.0, -0.9, 0.08, MFD_COLOUR1);
	}

	// crossfeed box
	draw_2d_half_thick_line(1.2, 0.30, 0.85, 0.30, MFD_COLOUR1);
	draw_2d_half_thick_line(1.2, -0.60, 0.85, -0.60, MFD_COLOUR1);

	print_vertical_mono_font_string(0.85, -0.13, "CROSSFEED", -0.5, TRUE);

	draw_2d_half_thick_line(0.85, 0.3, 0.85, 0.25, MFD_COLOUR1);
	draw_2d_half_thick_line(0.85, -0.6, 0.85, -0.55, MFD_COLOUR1);

	// fuel feed
	if (get_feeding_tank(1) == FUEL_TANK_FWD)
	{
		draw_2d_box(-0.38, 0.25, -0.36, 0.65, TRUE, FALSE, MFD_COLOUR1);
		draw_2d_box(-0.36, 0.65, -0.20, 0.63, TRUE, FALSE, MFD_COLOUR1);
	}
	else
	{
		draw_2d_box(-0.38, -0.25, -0.36, -0.44, TRUE, FALSE, MFD_COLOUR1);
		draw_2d_box(-0.38, -0.44, -0.06, -0.42, TRUE, FALSE, MFD_COLOUR1);
		draw_2d_box(-0.06, -0.44, -0.04, -0.35, TRUE, FALSE, MFD_COLOUR1);
	}

	if (get_feeding_tank(2) == FUEL_TANK_FWD)
	{
		draw_2d_box( 0.38, 0.25,  0.36, 0.65, TRUE, FALSE, MFD_COLOUR1);
		draw_2d_box( 0.36, 0.65,  0.20, 0.63, TRUE, FALSE, MFD_COLOUR1);
	}
	else
	{
		draw_2d_box( 0.38, -0.25,  0.36, -0.44, TRUE, FALSE, MFD_COLOUR1);
		draw_2d_box( 0.38, -0.44,  0.06, -0.42, TRUE, FALSE, MFD_COLOUR1);
		draw_2d_box( 0.06, -0.44,  0.04, -0.35, TRUE, FALSE, MFD_COLOUR1);
	}

	// fuel flow
	draw_2d_box(0.45, -0.6, -0.45, -1.1, FALSE, TRUE, MFD_COLOUR1);

	s = "CALC FLOW";
	set_2d_mono_font_position(0.0, -0.65);
	set_mono_font_rel_position(-0.5 * get_mono_font_string_width(s), -8.0);
	print_mono_font_string(s);

	s = "1";
	set_2d_mono_font_position(-0.25, -0.81);
	set_mono_font_rel_position(-get_mono_font_string_width(s), -8.0);
	print_mono_font_string(s);

	s = "LB/HR";
	set_2d_mono_font_position(0.15, -0.81);
	set_mono_font_rel_position(0.0, -8.0);
	print_mono_font_string(s);

	s = "2";
	set_2d_mono_font_position(-0.25, -0.93);
	set_mono_font_rel_position(-get_mono_font_string_width(s), -8.0);
	print_mono_font_string(s);

	s = "LB/HR";
	set_2d_mono_font_position(0.15, -0.93);
	set_mono_font_rel_position(0.0, -8.0);
	print_mono_font_string(s);

	s = "TOT";
	set_2d_mono_font_position(-0.25, -1.05);
	set_mono_font_rel_position(-get_mono_font_string_width(s), -8.0);
	print_mono_font_string(s);

	s = "LB/HR";
	set_2d_mono_font_position(0.15, -1.05);
	set_mono_font_rel_position(0.0, -8.0);
	print_mono_font_string(s);

	set_mono_font_type (MONO_FONT_TYPE_14X21);

	fuel_flow1 = get_fuel_flow(1);
	sprintf(buffer, "%d", ((int)(kilograms_to_pounds(fuel_flow1) * 3600.0 * 0.2)) * 5);
	set_2d_mono_font_position(0.12, -0.81);
	set_mono_font_rel_position(-get_mono_font_string_width(buffer), -12.0);
	print_mono_font_string(buffer);

	fuel_flow2 = get_fuel_flow(2);
	sprintf(buffer, "%d", ((int)(kilograms_to_pounds(fuel_flow2) * 3600.0 * 0.2)) * 5);
	set_2d_mono_font_position(0.12, -0.93);
	set_mono_font_rel_position(-get_mono_font_string_width(buffer), -12.0);
	print_mono_font_string(buffer);

	sprintf(buffer, "%d", ((int)(kilograms_to_pounds(fuel_flow1 + fuel_flow2) * 3600.0 * 0.2)) * 5);
	set_2d_mono_font_position(0.12, -1.05);
	set_mono_font_rel_position(-get_mono_font_string_width(buffer), -12.0);
	print_mono_font_string(buffer);

	// fuel weight
	draw_2d_box(-1.11, -0.75, -0.49, -1.0, FALSE, TRUE, MFD_COLOUR1);

	internal_fuel = get_fuel_quantity(FUEL_TANK_FWD) + get_fuel_quantity(FUEL_TANK_AFT);
	total_fuel = get_total_fuel_quantity();

	set_mono_font_type (MONO_FONT_TYPE_12X20);
	s = "INT     LB";
	set_2d_mono_font_position(-1.1, -0.82);
	set_mono_font_rel_position(0.0, -8.0);
	print_mono_font_string(s);

	if (total_fuel - internal_fuel > 1.0)
	{
		s = "TOT     LB";
		set_2d_mono_font_position(-1.1, -0.95);
		set_mono_font_rel_position(0.0, -8.0);
		print_mono_font_string(s);
	}

	set_mono_font_type (MONO_FONT_TYPE_14X21);

	sprintf(buffer, "%3.0f0", (kilograms_to_pounds(internal_fuel) * 0.1));
	set_2d_mono_font_position(-0.89, -0.82);
	set_mono_font_rel_position(0.0, -12.0);
	print_mono_font_string(buffer);

	if (total_fuel - internal_fuel > 1.0)
	{
		sprintf(buffer, "%3.0f0", (kilograms_to_pounds(total_fuel) * 0.1));
		set_2d_mono_font_position(-0.89, -0.95);
		set_mono_font_rel_position(0.0, -12.0);
		print_mono_font_string(buffer);
	}

	// endurance
	draw_2d_box(0.49, -0.65, 0.94, -1.0, FALSE, TRUE, MFD_COLOUR1);

	set_mono_font_type (MONO_FONT_TYPE_12X20);
	s = "ENDR";
	set_2d_mono_font_position(0.7, -0.7);
	set_mono_font_rel_position(-0.5 * get_mono_font_string_width(s), -8.0);
	print_mono_font_string(s);

	set_mono_font_type (MONO_FONT_TYPE_14X21);

	if (fuel_flow1 > 0.04 || fuel_flow2 > 0.04)
	{
		endurance = internal_fuel / (fuel_flow1 + fuel_flow2);
		sprintf(buffer, "%.0f:%02.0f", floor(endurance/3600.0), fmod(floor(endurance / 60.0), 60.0));
		set_2d_mono_font_position(0.9, -0.82);
		set_mono_font_rel_position(-get_mono_font_string_width(buffer), -12.0);
		print_mono_font_string(buffer);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_weapon_display_mfd (mfd_locations location, mfd_modes mfd_mode)
{
	float x1, x2, x3, x4, y1, y2, y3;
//	float forward_wing, rear_wing, wing_tip_left, wing_tip_right;
	char s[80];
	const char *s_ptr;
	float x_adjust;
	int number, damaged, selected_weapon, pylon;
	entity_sub_types weapon_sub_type;


	selected_weapon = get_local_entity_int_value(get_gunship_entity (), INT_TYPE_SELECTED_WEAPON);

	draw_helicopter_diagram(FALSE);

	// cannon
	if (get_local_entity_weapon_hardpoint_info (get_gunship_entity (),
		APACHE_CHAIN_GUN_TURRET, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON,
		&weapon_sub_type, &number, &damaged))
	{
		int selected = (weapon_sub_type == selected_weapon) && !damaged;

		get_2d_float_screen_coordinates (-0.01, 0.675, &x1, &y1);
		get_2d_float_screen_x_coordinate (0.01, &x2);
		get_2d_float_screen_y_coordinate (0.45, &y2);
		get_2d_float_screen_x_coordinate (-0.08, &x3);
		get_2d_float_screen_x_coordinate (0.08, &x4);
		get_2d_float_screen_y_coordinate (0.3, &y3);

		if (selected)
		{
			set_block (x1, y1, x2, y2, MFD_COLOUR1);
			set_block (x3, y2, x4, y3, MFD_COLOUR1);
		}
		else
		{
			draw_half_thick_line (x1, y1, x2, y1, MFD_COLOUR1);
			draw_half_thick_line (x1, y1, x1, y2, MFD_COLOUR1);
			draw_half_thick_line (x2, y1, x2, y2, MFD_COLOUR1);
			draw_half_thick_line (x1, y2, x3, y2, MFD_COLOUR1);
			draw_half_thick_line (x2, y2, x4, y2, MFD_COLOUR1);
			draw_half_thick_line (x3, y2, x3, y3, MFD_COLOUR1);
			draw_half_thick_line (x4, y2, x4, y3, MFD_COLOUR1);
		}

		get_2d_float_screen_coordinates (-0.2, 0.3, &x1, &y1);
		get_2d_float_screen_coordinates (0.2, 0.15, &x2, &y2);

		set_mono_font_type (MONO_FONT_TYPE_17X26);
		set_mono_font_colour (MFD_COLOUR1);
		draw_half_thick_line (x1, y1, x2, y1, MFD_COLOUR1);
		draw_half_thick_line (x1, y1, x1, y2, MFD_COLOUR1);
		draw_half_thick_line (x1, y2, x2, y2, MFD_COLOUR1);
		draw_half_thick_line (x2, y1, x2, y2, MFD_COLOUR1);

		set_2d_mono_font_position (0.0, 0.25);

		if (!damaged)
			sprintf (s, "%4d", number);
		else
			sprintf (s, "XXXX");

		x_adjust = get_mono_font_string_width (s) * -0.5;
		set_mono_font_rel_position (x_adjust, -8.0);
		print_mono_font_string (s);
	}

	// counter measures mode
	draw_2d_box(-0.2, -0.17, 0.2, 0.03, FALSE, TRUE, MFD_COLOUR1);

	switch (get_global_counter_measures_mode())
	{
	case COUNTER_MEASURES_MODE_AUTO:
		s_ptr = "AUTO";
		break;
	case COUNTER_MEASURES_MODE_SEMI:
		s_ptr = "SEMI";
		break;
	case COUNTER_MEASURES_MODE_MANUAL:
		s_ptr = "MAN";
		break;
	case COUNTER_MEASURES_MODE_SAFE:
		s_ptr = "SAFE";
		break;
	}

	set_2d_mono_font_position (0.0, -0.02);
	x_adjust = get_mono_font_string_width (s_ptr) * -0.5;
	set_mono_font_rel_position (x_adjust, 0.0);
	print_mono_font_string (s_ptr);

	set_mono_font_type (MONO_FONT_TYPE_12X20);

	// flare
	set_2d_mono_font_position (0.0, -0.2);

	s_ptr = "FLARE";

	x_adjust = get_mono_font_string_width (s_ptr) * -0.5;
	set_mono_font_rel_position (x_adjust, 0.0);
	print_mono_font_string (s_ptr);

	set_2d_mono_font_position (0.0, -0.3);

	if (get_local_entity_weapon_hardpoint_info (get_gunship_entity (),
		APACHE_FLARE_DISPENSER, ENTITY_SUB_TYPE_WEAPON_FLARE,
		&weapon_sub_type, &number, &damaged))
	{
		if (!damaged)
			sprintf (s, "%2d", number);
		else
			sprintf (s, "XX");

		x_adjust = get_mono_font_string_width (s) * -0.5;
		set_mono_font_rel_position (x_adjust, 0.0);
		print_mono_font_string (s);
	}

	// chaff
	set_2d_mono_font_position (0.0, -0.4);

	s_ptr = "CHAFF";

	x_adjust = get_mono_font_string_width (s_ptr) * -0.5;
	set_mono_font_rel_position (x_adjust, 0.0);
	print_mono_font_string (s_ptr);

	set_2d_mono_font_position (0.0, -0.5);

	if (get_local_entity_weapon_hardpoint_info (get_gunship_entity (),
		APACHE_CHAFF_DISPENSER, ENTITY_SUB_TYPE_WEAPON_CHAFF,
		&weapon_sub_type, &number, &damaged))
	{
		if (!damaged)
			sprintf (s, "%2d", number);
		else
			sprintf (s, "XX");

		x_adjust = get_mono_font_string_width (s) * -0.5;
		set_mono_font_rel_position (x_adjust, 0.0);
		print_mono_font_string (s);
	}


	// master arm box

	set_mono_font_type (MONO_FONT_TYPE_17X26);

	set_2d_mono_font_position (0.0, 0.9);

	if (selected_weapon != ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
	{
		draw_2d_box(-0.25, 0.73, 0.25, 1.03, TRUE, FALSE, MFD_COLOUR1);

		set_mono_font_colour (clear_mfd_colour);
		s_ptr = "ARM";

		draw_2d_box(-0.14, 0.96,-0.09, 1.03, TRUE, FALSE, clear_mfd_colour);
		draw_2d_box(-0.03, 0.96, 0.03, 1.03, TRUE, FALSE, clear_mfd_colour);
		draw_2d_box( 0.10, 0.96, 0.15, 1.03, TRUE, FALSE, clear_mfd_colour);
		draw_2d_box(-0.25, 0.96,-0.19, 0.91, TRUE, FALSE, clear_mfd_colour);
		draw_2d_box(-0.25, 0.80,-0.19, 0.85, TRUE, FALSE, clear_mfd_colour);
		draw_2d_box( 0.25, 0.96, 0.19, 0.91, TRUE, FALSE, clear_mfd_colour);
		draw_2d_box( 0.25, 0.80, 0.19, 0.85, TRUE, FALSE, clear_mfd_colour);
		draw_2d_box(-0.14, 0.80,-0.09, 0.73, TRUE, FALSE, clear_mfd_colour);
		draw_2d_box(-0.03, 0.80, 0.03, 0.73, TRUE, FALSE, clear_mfd_colour);
		draw_2d_box( 0.10, 0.80, 0.15, 0.73, TRUE, FALSE, clear_mfd_colour);

		draw_2d_box(-0.25, 0.73, 0.25, 1.03, FALSE, TRUE, MFD_COLOUR1);
	}
	else
	{
		draw_2d_box(-0.25, 0.73, 0.25, 1.03, FALSE, TRUE, MFD_COLOUR1);
		s_ptr = "SAFE";
	}

	x_adjust = get_mono_font_string_width (s_ptr) * -0.5;
	set_mono_font_rel_position (x_adjust, -7.0);
	print_mono_font_string (s_ptr);

	set_mono_font_type (MONO_FONT_TYPE_14X21);

	// targeting system
	draw_2d_box(-0.7, 0.9, -0.3, 0.65, FALSE, TRUE, MFD_COLOUR1);

	set_mono_font_colour (MFD_COLOUR1);
	s_ptr = "SIGHT";
	set_2d_mono_font_position (-0.5, 0.8);
	x_adjust = get_mono_font_string_width (s_ptr) * -0.5;
	set_mono_font_rel_position (x_adjust, -15.0);
	print_mono_font_string (s_ptr);

	switch (target_acquisition_system)
	{
	case TARGET_ACQUISITION_SYSTEM_GROUND_RADAR:
	case TARGET_ACQUISITION_SYSTEM_AIR_RADAR:
		s_ptr = "FCR";
		break;
	case TARGET_ACQUISITION_SYSTEM_FLIR:
	case TARGET_ACQUISITION_SYSTEM_DTV:
	case TARGET_ACQUISITION_SYSTEM_DVO:
		s_ptr = "TADS";
		break;
	case TARGET_ACQUISITION_SYSTEM_IHADSS:
		s_ptr = "IHADSS";
		break;
	case TARGET_ACQUISITION_SYSTEM_OFF:
	default:
		s_ptr = "NONE";
		break;
	}

	set_2d_mono_font_position (-0.5, 0.7);
	x_adjust = get_mono_font_string_width (s_ptr) * -0.5;
	set_mono_font_rel_position (x_adjust, -15.0);
	print_mono_font_string (s_ptr);

	// acquisition system
	draw_2d_box(0.7, 0.9, 0.3, 0.65, FALSE, TRUE, MFD_COLOUR1);

	s_ptr = "ACQ";
	set_2d_mono_font_position (0.5, 0.8);
	x_adjust = get_mono_font_string_width (s_ptr) * -0.5;
	set_mono_font_rel_position (x_adjust, -15.0);
	print_mono_font_string (s_ptr);


	// TODO
	s_ptr = get_apache_acquisition_source_abreviation();

	set_2d_mono_font_position (0.5, 0.7);
	x_adjust = get_mono_font_string_width (s_ptr) * -0.5;
	set_mono_font_rel_position (x_adjust, -15.0);
	print_mono_font_string (s_ptr);

	// LST
	draw_2d_box(-0.7, 0.6, -0.4, 0.35, FALSE, TRUE, MFD_COLOUR1);

	s_ptr = "LST";
	set_2d_mono_font_position (-0.55, 0.5);
	x_adjust = get_mono_font_string_width (s_ptr) * -0.5;
	set_mono_font_rel_position (x_adjust, -15.0);
	print_mono_font_string (s_ptr);

	s_ptr = "A";  // TODO
	set_2d_mono_font_position (-0.55, 0.4);
	x_adjust = get_mono_font_string_width (s_ptr) * -0.5;
	set_mono_font_rel_position (x_adjust, -15.0);
	print_mono_font_string (s_ptr);

	// LRFD
	draw_2d_box(0.7, 0.6, 0.4, 0.35, FALSE, TRUE, MFD_COLOUR1);

	s_ptr = "LRFD";
	set_2d_mono_font_position (0.55, 0.5);
	x_adjust = get_mono_font_string_width (s_ptr) * -0.5;
	set_mono_font_rel_position (x_adjust, -15.0);
	print_mono_font_string (s_ptr);

	s_ptr = "C";  // TODO
	set_2d_mono_font_position (0.55, 0.4);
	x_adjust = get_mono_font_string_width (s_ptr) * -0.5;
	set_mono_font_rel_position (x_adjust, -15.0);
	print_mono_font_string (s_ptr);

#if 0
	// launch mode
	draw_2d_box(-0.9, 0.45, -0.45, 0.2, FALSE, FALSE, MFD_COLOUR1);

	set_2d_mono_font_position (-0.65, 0.35);

	if (get_local_entity_int_value (get_gunship_entity (), INT_TYPE_LOCK_ON_AFTER_LAUNCH))
		s_ptr = "LOAL";
	else
		s_ptr = "LOBL";

	x_adjust = get_mono_font_string_width (s_ptr) * -0.5;
	set_mono_font_rel_position (x_adjust, 0.0);
	print_mono_font_string (s_ptr);
#endif
	// weapon pylons
	for (pylon = APACHE_LHS_INNER_PYLON; pylon <= APACHE_RHS_WING_TIP_MOUNT; pylon++)
	{
		float pylon_x, pylon_y;

		pylon_y = -0.05 + debug_var_y * 0.05;
		switch (pylon)
		{
		case APACHE_LHS_INNER_PYLON:
			pylon_x = -0.39 + debug_var_x * 0.05;
			break;
		case APACHE_RHS_INNER_PYLON:
			pylon_x = 0.39;
			break;
		case APACHE_LHS_OUTER_PYLON:
			pylon_x = -0.62;
			break;
		case APACHE_RHS_OUTER_PYLON:
			pylon_x = 0.62;
			break;
		case APACHE_LHS_WING_TIP_MOUNT:
			pylon_x = -0.97;
			break;
		case APACHE_RHS_WING_TIP_MOUNT:
			pylon_x = 0.97;
			break;
		}

		if (get_local_entity_weapon_hardpoint_info (get_gunship_entity (),
			pylon, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON,
			&weapon_sub_type, &number, &damaged))
		{
			if ((weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_AGM114L_LONGBOW_HELLFIRE) || (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_AGM114K_HELLFIRE_II))
			{
#if 0
				int i;
				float last_offset;  // is last missile on the left or right side of pylon

				if (pylon == APACHE_LHS_INNER_PYLON || pylon == APACHE_LHS_OUTER_PYLON)
					last_offset = 0.07;
				else
					last_offset = -0.07;

				for (i = 1; i <= number; i++)
				{
					float missile_x, missile_y;

					switch(i)
					{
						case 1:
							missile_x = pylon_x + last_offset;
							missile_y = pylon_y - 0.18;
							break;
						case 2:
							missile_x = pylon_x - last_offset;
							missile_y = pylon_y - 0.18;
							break;
						case 3:
							missile_x = pylon_x + last_offset;
							missile_y = pylon_y + 0.22;
							break;
						case 4:
							missile_x = pylon_x - last_offset;
							missile_y = pylon_y + 0.22;
							break;
						default:
							ASSERT(!"more than 4 hellfires on Apache pylon");
					}

					// remove wing
					get_2d_float_screen_x_coordinate(missile_x + 0.06, &x1);
					get_2d_float_screen_x_coordinate(missile_x - 0.06, &x2);

					if (missile_y > pylon_y)
						draw_line(x1, forward_wing, x2, forward_wing, clear_mfd_colour);
					else
						draw_line(x1, rear_wing, x2, rear_wing, clear_mfd_colour);

					// draw missile
					if ((weapon_sub_type == selected_weapon) && !damaged)
					{
						draw_2d_mono_sprite(inverted_hellfire_missile_data, missile_x, missile_y, MFD_COLOUR1);
						set_mono_font_colour (clear_mfd_colour);
					}
					else
					{
						draw_2d_mono_sprite(hellfire_missile_data, missile_x, missile_y, MFD_COLOUR1);
						set_mono_font_colour (MFD_COLOUR1);
					}
					set_mono_font_type (MONO_FONT_TYPE_7X12);
					set_2d_mono_font_position (missile_x, missile_y-0.05);

					if (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_AGM114L_LONGBOW_HELLFIRE)
						sprintf(s, "R");
					else
						sprintf(s, "L");

					x_adjust = get_mono_font_string_width (s) * -0.4;
					set_mono_font_rel_position (x_adjust, 0.0);
					print_mono_font_string (s);
				}
#endif
			}
			else if (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_HYDRA70_M255 ||
					 weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_HYDRA70_M261)
			{
				int selected = (weapon_sub_type == selected_weapon) && !damaged;
				rgb_colour text_colour = selected ? clear_mfd_colour : MFD_COLOUR1;

				// draw pod (background)
				draw_2d_box(pylon_x - 0.10, pylon_y + 0.25, pylon_x + 0.10, pylon_y - 0.25, TRUE, FALSE, selected ? MFD_COLOUR1 : clear_mfd_colour);
				if (!selected)
					draw_2d_box(pylon_x - 0.10, pylon_y + 0.25, pylon_x + 0.10, pylon_y - 0.25, FALSE, TRUE, MFD_COLOUR1);

				set_mono_font_colour (text_colour);

#if 0
//				set_mono_font_type (MONO_FONT_TYPE_7X12);
				set_2d_mono_font_position (pylon_x, pylon_y);


				if (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_HYDRA70_M255)
					sprintf(s, "MP");
				else
					sprintf(s, "RC");

				x_adjust = get_mono_font_string_width (s) * -0.4;
				set_mono_font_rel_position (x_adjust, 0.0);
				print_mono_font_string (s);
#endif
				set_2d_mono_font_position (pylon_x, pylon_y + 0.1);
				sprintf(s, "%2d", number);
				x_adjust = get_mono_font_string_width (s) * -0.4;
				set_mono_font_rel_position (x_adjust, 0.0);
				print_mono_font_string (s);

				set_mono_font_colour (MFD_COLOUR1);
			}
			else if (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_AIM92_STINGER)
			{
#if 0
				int selected = (weapon_sub_type == selected_weapon) && !damaged;
				int left_tip = pylon == APACHE_LHS_WING_TIP_MOUNT;
				float tip;

				if (number == 2)
				{
					// remove wing drawing
					if (left_tip)
					{
						tip = wing_tip_left;
						get_2d_float_screen_x_coordinate(-0.93, &x1);
						get_2d_float_screen_y_coordinate(-0.22, &y1);
					}
					else
					{
						tip = wing_tip_right;
						get_2d_float_screen_x_coordinate(0.93, &x1);
						get_2d_float_screen_y_coordinate(-0.22, &y1);
					}
					draw_line(x1, forward_wing, tip, forward_wing, clear_mfd_colour);
					draw_line(tip, forward_wing, tip, y1, clear_mfd_colour);

					// draw missile
					if (selected)
						draw_2d_mono_sprite(inverted_stinger_missile_data, pylon_x, pylon_y + 0.25, MFD_COLOUR1);
					else
						draw_2d_mono_sprite(stinger_missile_data, pylon_x, pylon_y + 0.25, MFD_COLOUR1);
				}

				if (number >= 1)
				{
					// remove wing drawing
					if (left_tip)
					{
						tip = wing_tip_left;
						get_2d_float_screen_x_coordinate(-0.91, &x1);
						get_2d_float_screen_y_coordinate(-0.27, &y1);
					}
					else
					{
						tip = wing_tip_right;
						get_2d_float_screen_x_coordinate(0.91, &x1);
						get_2d_float_screen_y_coordinate(-0.27, &y1);
					}
					draw_line(x1, rear_wing, tip, rear_wing, clear_mfd_colour);
					draw_line(tip, rear_wing, tip, y1, clear_mfd_colour);

					// draw missile
					if (selected)
						draw_2d_mono_sprite(inverted_stinger_missile_data, pylon_x, pylon_y - 0.05, MFD_COLOUR1);
					else
						draw_2d_mono_sprite(stinger_missile_data, pylon_x, pylon_y - 0.05, MFD_COLOUR1);
				}
#endif
			}

			// if damaged, draw X across pylon
			if (damaged)
			{
				float width, height = 0.7, x1, y1, x2, y2, y_offset = 0.0;

				if (pylon == APACHE_LHS_WING_TIP_MOUNT || pylon == APACHE_RHS_WING_TIP_MOUNT)
				{
					// stingers are narrower and drawn more forward than other pylons
					y_offset = 0.1;
					width = 0.125;
				}
				else
					width = 0.25;

				get_2d_float_screen_coordinates(pylon_x - 0.5 * width, pylon_y - 0.5 * height, &x1, &y1);
				get_2d_float_screen_coordinates(pylon_x + 0.5 * width, pylon_y + y_offset + 0.5 * height, &x2, &y2);

				draw_half_thick_line(x1, y1, x2, y2, MFD_COLOUR1);
				draw_half_thick_line(x1, y2, x2, y1, MFD_COLOUR1);
			}
		}
	}

	switch (mfd_mode)
	{
	case MFD_MODE_WEAPON_GUN:
		draw_2d_half_thick_line(-1.2, 0.9, -0.9, 0.9, MFD_COLOUR1);
		draw_2d_half_thick_line(-1.2, -0.6, -0.9, -0.6, MFD_COLOUR1);

		print_vertical_mono_font_string(-0.9, 0.19, "BURST LIMIT", -0.5, TRUE);

		draw_2d_half_thick_line(-0.9, 0.9, -0.9, 0.67, MFD_COLOUR1);
		draw_2d_half_thick_line(-0.9, -0.6, -0.9, -0.37, MFD_COLOUR1);

		break;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// SYSTEM
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static float print_system_message (char *equipment, char *warning, int fail, float y_adjust)
{
	char
		*status;

	float
		width;

	ASSERT (equipment);

	ASSERT (warning);

	set_2d_mono_font_position (-0.8, 0.90);

	set_mono_font_rel_position (1.0, y_adjust);

	print_mono_font_string (equipment);

	if (fail)
	{
		status = warning;
	}
	else
	{
		status = "OK";
	}

	width = get_mono_font_string_width (status);

	set_2d_mono_font_position (0.8, 0.90);

	set_mono_font_rel_position (-width, y_adjust);

	print_mono_font_string (status);

	y_adjust += get_mono_font_char_height ('X') + 2;

	return (y_adjust);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_system_display_mfd (void)
{
	float
		y_adjust;

	set_mono_font_colour (MFD_COLOUR1);

	set_mono_font_type (MONO_FONT_TYPE_6X10);
	y_adjust = 2.0;

	y_adjust = print_system_message ("RADAR", "FAIL", apache_damage.radar, y_adjust);

	y_adjust = print_system_message ("FLIR", "FAIL", apache_damage.flir, y_adjust);

	y_adjust = print_system_message ("DTV", "FAIL", apache_damage.dtv, y_adjust);

	y_adjust = print_system_message ("DVO", "FAIL", apache_damage.dvo, y_adjust);

	y_adjust = print_system_message ("LASER DESIGNATOR", "FAIL", apache_damage.laser_designator, y_adjust);

	y_adjust = print_system_message ("RADAR JAMMER", "FAIL", apache_damage.radar_jammer, y_adjust);

	y_adjust = print_system_message ("IR JAMMER", "FAIL", apache_damage.infra_red_jammer, y_adjust);

	y_adjust = print_system_message ("NAVIGATION COMPUTER", "FAIL", apache_damage.navigation_computer, y_adjust);

	y_adjust = print_system_message ("COMMUNICATIONS", "FAIL", apache_damage.communications, y_adjust);

	y_adjust = print_system_message ("RADAR WARNING SYSTEM", "FAIL", apache_damage.radar_warning_system, y_adjust);

	y_adjust = print_system_message ("IHADSS", "FAIL", apache_damage.ihadss, y_adjust);

	y_adjust = print_system_message ("PNVS", "FAIL", apache_damage.pnvs, y_adjust);

	y_adjust = print_system_message ("STABILISER", "FAIL", get_dynamics_damage_type (DYNAMICS_DAMAGE_STABILISER), y_adjust);

	y_adjust = print_system_message ("MAIN ROTOR", "FAIL", get_dynamics_damage_type (DYNAMICS_DAMAGE_MAIN_ROTOR), y_adjust);

	y_adjust = print_system_message ("TAIL ROTOR", "DAMAGED", get_dynamics_damage_type (DYNAMICS_DAMAGE_TAIL_ROTOR), y_adjust);

	y_adjust = print_system_message ("ENGINE 1", "DAMAGED", get_dynamics_damage_type (DYNAMICS_DAMAGE_LEFT_ENGINE), y_adjust);

	y_adjust = print_system_message ("ENGINE 2", "DAMAGED", get_dynamics_damage_type (DYNAMICS_DAMAGE_RIGHT_ENGINE), y_adjust);

	{
		char* failure_msg = "";
		int
			pri_dmg = get_dynamics_damage_type (DYNAMICS_DAMAGE_LOW_HYDRAULICS),
			sec_dmg = get_dynamics_damage_type (DYNAMICS_DAMAGE_SECONDARY_HYDRAULICS);

		if (pri_dmg && sec_dmg)
			failure_msg = "FAILURE";
		else if (pri_dmg)
			failure_msg = "PRI LOW";
		else if (sec_dmg)
			failure_msg = "SEC FAIL";

		y_adjust = print_system_message ("HYDRAULICS", failure_msg, pri_dmg || sec_dmg, y_adjust);
	}

	if (get_dynamics_damage_type (DYNAMICS_DAMAGE_LOW_OIL_PRESSURE))
	{
		y_adjust = print_system_message ("OIL PRESSURE", "LOW", get_dynamics_damage_type (DYNAMICS_DAMAGE_LOW_OIL_PRESSURE), y_adjust);
	}
	else
	{
		y_adjust = print_system_message ("OIL PRESSURE", "HIGH", get_dynamics_damage_type (DYNAMICS_DAMAGE_HIGH_OIL_PRESSURE), y_adjust);
	}

	//
	// fire extinguisher
	//

	y_adjust += 14;

	y_adjust = print_system_message ("FIRE EXTINGUISHER", "USED", fire_extinguisher_used, y_adjust);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_list(float x, float y, const char** list, int first_entry, int num_entries, rgb_colour col)
{
	const float line_spacing = 0.1;
	int i=0;

	ASSERT(first_entry >= 0 && num_entries > 0);

	set_mono_font_colour(col);
	set_mono_font_type (MONO_FONT_TYPE_12X20);

	for (i=first_entry; i < first_entry + num_entries; i++, y -= line_spacing)
	{
		set_2d_mono_font_position(x, y);
		set_mono_font_rel_position (0.0, -6.0);

		print_mono_font_string(list[i]);
	}
}

// returns true if there are more pages
static int draw_checklist(mfd_modes mode, mfd_locations location)
{
	int num_entries = 0;
	int more_pages = FALSE;
	int sub_mode = mfd_sub_mode[location];
	const char** checklist = NULL;
	const int num_entries_per_page = 18;

	if (mode == MFD_MODE_CHECKLIST)
	{
		switch(sub_mode)
		{
		case 0:
			checklist = checklist_menu;
			num_entries = ARRAY_LENGTH(checklist_menu);
			break;
		case MFD_BUTTON_CHECKLIST_AFTER_STARTING_APU:
			checklist = checklist_after_starting_apu;
			num_entries = ARRAY_LENGTH(checklist_after_starting_apu);
			break;
		case MFD_BUTTON_CHECKLIST_BEFORE_STARTING_ENG:
			checklist = checklist_before_starting_engines;
			num_entries = ARRAY_LENGTH(checklist_before_starting_engines);
			break;
		case MFD_BUTTON_CHECKLIST_STARTING_ENG:
			checklist = checklist_starting_engines;
			num_entries = ARRAY_LENGTH(checklist_starting_engines);
			break;
		case MFD_BUTTON_CHECKLIST_BEFORE_TAXI:
			checklist = checklist_before_taxi;
			num_entries = ARRAY_LENGTH(checklist_before_taxi);
			break;
		case MFD_BUTTON_CHECKLIST_TAXI:
			checklist = checklist_taxi;
			num_entries = ARRAY_LENGTH(checklist_taxi);
			break;
		case MFD_BUTTON_CHECKLIST_BEFORE_TO:
			checklist = checklist_before_to;
			num_entries = ARRAY_LENGTH(checklist_before_to);
			break;
		case MFD_BUTTON_CHECKLIST_BEFORE_LANDING:
			checklist = checklist_before_landing;
			num_entries = ARRAY_LENGTH(checklist_before_landing);
			break;
		case MFD_BUTTON_CHECKLIST_AFTER_LANDING:
			checklist = checklist_after_landing;
			num_entries = ARRAY_LENGTH(checklist_after_landing);
			break;
		case MFD_BUTTON_CHECKLIST_ENGINE_SHUTDOWN:
			checklist = checklist_engine_shutdown;
			num_entries = ARRAY_LENGTH(checklist_engine_shutdown);
			break;
			break;
		default:
			ASSERT(FALSE);
			break;
		}
	}
	else if (mode == MFD_MODE_CHECKLIST_THROUGH_FLIGHT)
	{
		switch(sub_mode)
		{
		case 0:
			checklist = tf_checklist_menu;
			num_entries = ARRAY_LENGTH(tf_checklist_menu);
			break;
		}
	}
	else if (mode == MFD_MODE_CHECKLIST_PERF_DATA1)
	{
		switch(sub_mode)
		{
		case 0:
			checklist = perf_data1_checklist_menu;
			num_entries = ARRAY_LENGTH(perf_data1_checklist_menu);
			break;
		}
	}
	else if (mode == MFD_MODE_CHECKLIST_PERF_DATA2)
	{
		switch(sub_mode)
		{
		case 0:
			checklist = perf_data2_checklist_menu;
			num_entries = ARRAY_LENGTH(perf_data2_checklist_menu);
			break;
		}
	}

	if (checklist)
	{
		int first_entry = (mfd_sub_page[location] - 1) * num_entries_per_page;
		num_entries -= first_entry;

		if (num_entries > num_entries_per_page)
		{
			more_pages = TRUE;
			num_entries = num_entries_per_page;
		}

		if (num_entries > 0)
			draw_list(-0.85, 0.8, checklist, first_entry, num_entries, MFD_COLOUR1);
	}

	draw_apache_mfd_page_number_buttons(location, mfd_sub_page[location] - 1, more_pages ? mfd_sub_page[location] + 1 : 0);

	return more_pages;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_hsi(float centre_y, float scale, float* adf_bearing)
{
//	float u, v;
	float aircraft_heading = get_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_HEADING);
	int hdg;

//	get_2d_float_screen_coordinates (0.0, centre_y, &u, &v);

	set_mono_font_colour (MFD_COLOUR1);
	set_mono_font_type (MONO_FONT_TYPE_10X16);

	// heading tick
	draw_2d_half_thick_line(0.0, scale * 0.8, 0.0, scale, MFD_COLOUR1);

	// aircraft symbol
	draw_2d_half_thick_line(0.0, scale * 0.07, 0.0, scale * -0.15, MFD_COLOUR1);
	draw_2d_half_thick_line(-0.1, 0.0, 0.1, 0.0, MFD_COLOUR1);
	draw_2d_half_thick_line(-0.03, scale * -0.12, 0.03, scale * -0.12, MFD_COLOUR1);


	// compass rose

	set_2d_instance_position (mfd_env, 0.0, centre_y);
	set_2d_instance_rotation (mfd_env, aircraft_heading);

	for (hdg = 0; hdg < 360; hdg+=5)
	{
		set_2d_instance_rotation (mfd_env, aircraft_heading - rad(hdg));
		switch (hdg)
		{
		case 0:
		case 90:
		case 180:
		case 270:
		case 30:
		case 60:
		case 120:
		case 150:
		case 210:
		case 240:
		case 300:
		case 330:
			{
				char label[16];

				if (hdg == 0)
					sprintf(label, "N");
				else if (hdg == 90)
					sprintf(label, "E");
				else if (hdg == 180)
					sprintf(label, "S");
				else if (hdg == 270)
					sprintf(label, "W");
				else
					sprintf(label, "%d", hdg / 10);

				set_2d_mono_font_position(0.0, scale * 0.8);
				set_mono_font_rel_position(-0.5 * get_mono_font_string_width(label), -5);
				print_mono_font_string(label);

				draw_2d_half_thick_line(0.0, scale * 0.9, 0.0, scale, MFD_COLOUR1);
				break;
			}
		default:
			if (hdg % 10 == 0)
				draw_2d_line(0.0, scale * 0.9, 0.0, scale, MFD_COLOUR1);
			else
				draw_2d_line(0.0, scale * 0.95, 0.0, scale, MFD_COLOUR1);
			break;
		}
	}

	// ADF bearing pointer
	if (adf_bearing)
	{
		set_2d_instance_rotation (mfd_env, aircraft_heading - *adf_bearing);

		draw_2d_half_thick_line(0.0, scale * 0.7, 0.0, scale * 0.4, MFD_COLOUR1);
		draw_2d_half_thick_line(0.0, scale * 0.9, 0.06, scale * 0.7, MFD_COLOUR1);
		draw_2d_half_thick_line(0.0, scale * 0.9, -0.06, scale * 0.7, MFD_COLOUR1);
		draw_2d_half_thick_line(0.06, scale * 0.7, -0.06, scale * 0.7, MFD_COLOUR1);
		draw_2d_half_thick_line(0.0, -scale * 0.9, 0.0, -scale * 0.4, MFD_COLOUR1);
	}

	reset_2d_instance (mfd_env);

	set_2d_window (mfd_env, MFD_WINDOW_X_MIN, MFD_WINDOW_Y_MIN, MFD_WINDOW_X_MAX, MFD_WINDOW_Y_MAX);
	set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);
}

static void draw_adf_page(mfd_locations location)
{
	set_mono_font_colour (MFD_COLOUR1);
	set_mono_font_type (MONO_FONT_TYPE_12X20);

	if (mfd_sub_mode[location] == 1 && get_adf_enabled())
	{
		float x = -1.15, y = 0.45, align = 0.0;
		unsigned ntransmitters;
		unsigned i;
		ndb_instrument_transmitter* trans = get_instrument_transmitters(&ntransmitters);

		for (i=0; i < 10; i++, trans++)
		{
			char buffer[80];

			if (i < ntransmitters)
			{
				set_2d_mono_font_position(x, y);
				set_mono_font_rel_position(align * get_mono_font_string_width(trans->code), -10);
				print_mono_font_string(trans->code);

				if (*trans->code || trans->radio_frequency > 0.0)
				{
					sprintf(buffer, "%.1f", trans->radio_frequency * 0.001);
					set_2d_mono_font_position(x, y);
					set_mono_font_rel_position(align * get_mono_font_string_width(buffer), 6);
					print_mono_font_string(buffer);
				}
			}

			if (i + 1 == mfd_sub_page[location])
				draw_2d_box(x * 1.02, y + 0.07, x * 0.72, y - 0.11, FALSE, TRUE, MFD_COLOUR1);

			y -= 0.3;
			if (y < -1.0)
			{
				y = 0.45;
				x = 1.15;
				align = -1.0;
			}
		}
	}
	else
	{
		// draw on/off button
		const char *sprite, *sprite_mask;

		if (get_adf_enabled())
		{
			sprite = on_indicator;
			sprite_mask = on_indicator_mask;
		}
		else
		{
			sprite = off_indicator;
			sprite_mask = off_indicator_mask;
		}

		draw_2d_mono_sprite(sprite_mask, 0.91, 0.73, MFD_COLOUR5);
		draw_2d_mono_sprite(sprite, 0.91, 0.73, MFD_COLOUR1);

		// draw emergency box
		if (get_adf_enabled())
		{
			set_2d_mono_font_position(0.0, -1.05);
			set_mono_font_rel_position(-0.5 * get_mono_font_string_width("EMER"), -6);
			print_mono_font_string("EMER");

			draw_2d_half_thick_line(-0.4, -1.2, -0.4, -1.05, MFD_COLOUR1);
			draw_2d_half_thick_line( 0.4, -1.2,  0.4, -1.05, MFD_COLOUR1);
			draw_2d_half_thick_line(-0.4, -1.05, -0.15, -1.05, MFD_COLOUR1);
			draw_2d_half_thick_line( 0.4, -1.05,  0.15, -1.05, MFD_COLOUR1);
		}
	}

	// draw current ADF station info
	{
		ndb_instrument_transmitter* transmitter = get_current_adf_station();
		float bearing;
		int has_bearing = FALSE;
		char buffer[20];

		if (transmitter)
			sprintf(buffer, "%3s %6.1f KHZ", transmitter->code, transmitter->radio_frequency * 0.001);
		else
			sprintf(buffer, "    %6.1f KHZ", get_current_adf_frequency() * 0.001);

		set_2d_mono_font_position(-0.03, -0.8);
		set_mono_font_rel_position(0.0, -6);
		print_mono_font_string(buffer);

		if (transmitter)
		{
			set_mono_font_colour (MFD_COLOUR1);
			set_mono_font_type (MONO_FONT_TYPE_10X16);

			set_2d_mono_font_position(-0.03, -0.8);
			set_mono_font_rel_position(0.0, 10);
			print_mono_font_string(transmitter->morse_code);

		}

		if (has_bearing = has_adf_bearing())
			bearing = get_adf_bearing();

		draw_2d_box(-0.05, -0.75, 0.83, -0.95, FALSE, TRUE, MFD_COLOUR1);

		draw_hsi(0.05, 0.75, has_bearing ? &bearing : NULL);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ENGINE
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_2d_engine_bar(float f_x1, float f_y1, float f_x2, float f_y2, float fvalue, rgb_colour col)
{
	int x1, x2, y1, y2;

	get_2d_int_screen_coordinates (f_x1, f_y2 + (fvalue * (f_y1 - f_y2)), &x1, &y1);
	get_2d_int_screen_coordinates (f_x2, f_y2, &x2, &y2);
	set_block (x1, y1, x2, y2, col);
}

static void draw_engine_value(float x, float y, const char* format, float value, float warning_min_limit, float warning_max_limit, float danger_min_limit, float danger_max_limit)
{
	float readout_half_width;
	rgb_colour col;
	unsigned box = TRUE;
	char buffer[20];

	if (value < danger_min_limit || value > danger_max_limit)
		col = MFD_COLOUR_RED;
	else if (value < warning_min_limit || value > warning_max_limit)
		col = MFD_COLOUR_YELLOW;
	else
	{
		box = FALSE;
		col = MFD_COLOUR1;
	}

	set_mono_font_colour(col);
	set_mono_font_type (MONO_FONT_TYPE_14X21);

	sprintf (buffer, format, value);
	set_2d_mono_font_position (x, y);
	set_mono_font_rel_position (-0.5 * get_mono_font_string_width(buffer), -21.0);
	print_mono_font_string (buffer);

	if (box)
	{
		readout_half_width = 0.037 * strlen(buffer);
		draw_2d_box(x - readout_half_width, y, x + readout_half_width, y + 0.1, FALSE, TRUE, col);
	}

	set_mono_font_colour (MFD_COLOUR1);
	set_mono_font_type (MONO_FONT_TYPE_10X16);
}

static void draw_engine_bar(float x, float y, float value, float split_value, float max_value, float warning_min_limit, float warning_max_limit, float danger_min_limit, float danger_max_limit, int print_readout)
{
	rgb_colour col;
	unsigned box = TRUE;

	if (value < danger_min_limit || value > danger_max_limit)
		col = MFD_COLOUR_RED;
	else if (value < warning_min_limit || value > warning_max_limit)
		col = MFD_COLOUR_YELLOW;
	else
	{
		box = FALSE;
		col = MFD_COLOUR1;
	}

	if (value > split_value)
	{
		float from = print_readout ? y + 0.1 : y;

		draw_2d_engine_bar(x - 0.04, y, x + 0.04, -0.1, 1.0, col);
		draw_2d_engine_bar(x - 0.04, 0.9, x + 0.04, from, (value - split_value) / (max_value - split_value), col);
	}
	else
		draw_2d_engine_bar(x - 0.04, y, x + 0.04, -0.1, value / split_value, col);

	if (print_readout)
		draw_engine_value(x, y, "%3.0f", value, warning_min_limit, warning_max_limit, danger_min_limit, danger_max_limit);
}

static void draw_rotor_rpm_bar(float value, float x, float y)
{
	rgb_colour col;
	unsigned box = TRUE;
	char buffer[20];

	if (value > 110.0 || value < 94.0)
		col = MFD_COLOUR_RED;
	else if (value > 104.0)
		col = MFD_COLOUR_YELLOW;
	else
	{
		box = FALSE;
		col = MFD_COLOUR1;
	}

	// draw the downward pointing bar up to 94%
	{
		/*  1 _ _ 2   top
		 *  |  3  |   top_centre
		 *  |     |
		 *  4 _ _ 5   bottom
		 *     6      bottom_centre
		 */

		float
			left = x - 0.1,
			centre = x,
			right = x + 0.1,
			top,
			top_centre,
			bottom = -0.04,
			bottom_centre = -0.1,
			height;

		height = (min(value, 94.0) / 94.0) * 0.45;
		top = bottom + height;
		top_centre = bottom_centre + height;

		// have to draw as triangles.  Numbers corresponds to ascii drawing above
		// 1, 6, 4
		draw_2d_filled_triangle(left, top, centre, bottom_centre, left, bottom, col);
		// 1, 3, 6
		draw_2d_filled_triangle(left, top, centre, top_centre, centre, bottom_centre, col);
		// 3, 2, 6
		draw_2d_filled_triangle(centre, top_centre, right, top, centre, bottom_centre, col);
		// 2, 5, 6
		draw_2d_filled_triangle(right, top, right, bottom, centre, bottom_centre, col);

		if (value > 94.0)
		{
			height = min(value - 94.0, 6.0) / 6.0 * 0.15;
			draw_2d_box(centre - 0.06, top_centre, centre + 0.06, top_centre + height, TRUE, FALSE, col);
		}

		bottom_centre = 0.6;
		bottom = bottom_centre - 0.06;

		draw_2d_half_thick_line(centre, 0.78, left + 0.01, 0.72, MFD_COLOUR_RED);
		draw_2d_half_thick_line(centre, 0.78, right, 0.72, MFD_COLOUR_RED);

		if (value > 100.0)
		{
			top_centre = 0.6;
			top = top_centre - 0.04;

			height = min(value - 100.0, 4.0) / 4.0 * 0.12;
			draw_2d_filled_triangle(centre, top_centre + height,
									centre + min(0.06, height / 0.6), top_centre + max(height - 0.036, 0.0),
									centre - min(0.06, height / 0.6), top_centre + max(height - 0.036, 0.0),
									col);

			if (height > 0.036)
			draw_2d_box(centre - 0.06, top_centre, centre + 0.06, top_centre + height - 0.036, TRUE, FALSE, col);

			// draw upward point bar above 104%
			if (value > 104.0)
			{
				/*   _1_    top_centre
				 *  2   3   top
				 *  |_4_|   bottom_centre
				 *  5   6   bottom
				 */

				bottom_centre = 0.72;
				bottom = bottom_centre - 0.06;
				height = (value - 104.0) / 16.0 * 0.18;
				top = bottom + height;
				top_centre = bottom_centre + height;

				// 2, 1, 4
				draw_2d_filled_triangle(left, top, centre, top_centre, centre, bottom_centre, col);
				// 2, 4, 5
				draw_2d_filled_triangle(left, top, centre, bottom_centre, left, bottom, col);
				// 1, 3, 4
				draw_2d_filled_triangle(centre, top_centre, right, top, centre, bottom_centre, col);
				// 4, 3, 6
				draw_2d_filled_triangle(centre, bottom_centre, right, top, right, bottom, col);
			}
		}
	}


	if (value > 104.0)
		draw_2d_box(x - 0.11, y, x + 0.11, y + 0.1, FALSE, TRUE, col);

	set_mono_font_colour(col);
	set_mono_font_type (MONO_FONT_TYPE_14X21);

	sprintf (buffer, "%3.0f", value);
	set_2d_mono_font_position (x, y);
	set_mono_font_rel_position (-0.5 * get_mono_font_string_width(buffer), -21.0);
	print_mono_font_string (buffer);

	set_mono_font_colour (MFD_COLOUR1);
	set_mono_font_type (MONO_FONT_TYPE_10X16);
}

static void draw_engine_display_mfd (void)
{
	int
		box,
		i;

	float
		val,
		x,
		y,
		split,
		bar_limit,
		digital_readout;

	rgb_colour
		col;

	set_mono_font_colour (MFD_COLOUR1);
	set_mono_font_type (MONO_FONT_TYPE_10X16);

	////////////////////////////////////////
	//
	// engine torque
	//
	////////////////////////////////////////

	set_2d_mono_font_position (-0.9, 0.95);
	set_mono_font_rel_position (-0.5 * get_mono_font_string_width("TORQUE %"), -16.0);
	print_mono_font_string ("TORQUE %");

	if (current_flight_dynamics->main_rotor_rpm.value < 50.0)
	{
		split = 30.0;
		y = 0.08;
		bar_limit = y + 0.11;
	}
	else if (current_flight_dynamics->main_rotor_rpm.value < 90.0)
	{
		split = 70.0;
		y = 0.32;
		bar_limit = y + 0.11;
	}
	else
	{
		y = 0.5;
		split = 100.0;
		bar_limit = y + 0.25;  // 115%, max dual engine transient
	}

	draw_2d_half_thick_line(-1.15, bar_limit, -0.7, bar_limit, MFD_COLOUR_RED);
	draw_2d_mono_sprite (large_engine_bar_marker, -0.925, bar_limit, MFD_COLOUR_RED);

	//
	// engine 1 torque
	//

	digital_readout = bound (current_flight_dynamics->left_engine_torque.value, 0.0, 120.0);
	convert_float_to_int (digital_readout, &i);

	x = -1.05;
	draw_engine_bar(x, y, digital_readout, split, 130.0, 0.0, split, 0.0, 100.0, TRUE);

	set_2d_mono_font_position (x, -0.1);
	set_mono_font_rel_position (-0.5 * get_mono_font_string_width(" "), 8.0);
	print_mono_font_string("1");

	//
	// engine 2 torque
	//

	digital_readout = bound (current_flight_dynamics->right_engine_torque.value, 0.0, 120.0);
	convert_float_to_int (digital_readout, &i);

	box = TRUE;
	if (digital_readout > 100.0)
		col = MFD_COLOUR_RED;
	else if (digital_readout > split)
		col = MFD_COLOUR_YELLOW;
	else
	{
		box = FALSE;
		col = MFD_COLOUR1;
	}

	x = -0.8;
	draw_engine_bar(x, y, digital_readout, split, 130.0, 0.0, split, 0.0, 100.0, TRUE);

	set_2d_mono_font_position (x, -0.1);
	set_mono_font_rel_position (-0.5 * get_mono_font_string_width(" "), 8.0);
	print_mono_font_string("2");

	////////////////////////////////////////
	//
	// engine temperature
	//
	////////////////////////////////////////

	set_2d_mono_font_position (-0.35, 0.95);
	set_mono_font_rel_position (-0.5 * get_mono_font_string_width("TGT C"), -16.0);
	print_mono_font_string ("TGT C");

	y = 0.5;
	split = 800.0;

	draw_2d_half_thick_line(-0.55, y + 0.178, -0.35, y + 0.178, MFD_COLOUR_YELLOW); // 30 min limit
	draw_2d_half_thick_line(-0.3, y + 0.178, -0.1, y + 0.178, MFD_COLOUR_YELLOW); // 30 min limit

	draw_2d_half_thick_line(-0.55, y + 0.213, -0.35, y + 0.213, MFD_COLOUR_YELLOW); // 10 min limit
	draw_2d_half_thick_line(-0.3, y + 0.213, -0.1, y + 0.213, MFD_COLOUR_YELLOW); // 10 min limit

	draw_2d_half_thick_line(-0.55, y + 0.325, -0.1, y + 0.325, MFD_COLOUR_RED);     // 901 deg, 12 sec transient limit
	draw_2d_mono_sprite (large_engine_bar_marker, -0.325, y + 0.325, MFD_COLOUR_RED);

	//
	// engine 1 temperature
	//

	digital_readout = bound (current_flight_dynamics->left_engine_temp.value, 0.0, 999.0);

	x = -0.45;
	draw_engine_bar(x, y, digital_readout, split, 1000.0, 0.0, split, 0.0, 867.0, TRUE);

	set_2d_mono_font_position (x, -0.1);
	set_mono_font_rel_position (-0.5 * get_mono_font_string_width(" "), 8.0);
	print_mono_font_string("1");

	//
	// engine 2 temperature
	//

	digital_readout = bound (current_flight_dynamics->right_engine_temp.value, 0.0, 999.0);

	x = -0.2;
	draw_engine_bar(x, y, digital_readout, split, 1000.0, 0.0, split, 0.0, 867.0, TRUE);

	set_2d_mono_font_position (x, -0.1);
	set_mono_font_rel_position (-0.5 * get_mono_font_string_width(" "), 8.0);
	print_mono_font_string("2");

	////////////////////////////////////////
	//
	// engine and rotor rpm
	//
	////////////////////////////////////////

	set_2d_mono_font_position (0.3, 0.95);
	set_mono_font_rel_position (-0.5 * get_mono_font_string_width("NP% NR% NP%"), -16.0);
	print_mono_font_string ("N % N % N %");

	set_2d_mono_font_position (0.3, 0.95);
	set_mono_font_rel_position (-0.5 * get_mono_font_string_width("NP% NR% NP%"), -13.0);
	print_mono_font_string (" P   R   P ");


	set_2d_mono_font_position (0.9, 0.25);
	set_mono_font_rel_position (-0.5 * get_mono_font_string_width("NP%"), -16.0);
	print_mono_font_string ("N %");

	set_2d_mono_font_position (0.9, 0.25);
	set_mono_font_rel_position (-0.5 * get_mono_font_string_width("NP%"), -13.0);
	print_mono_font_string (" P ");

	// labels for numeric reading on right side
	set_2d_mono_font_position (0.9, -0.0);
	set_mono_font_rel_position (-0.5 * get_mono_font_string_width("NG%"), -16.0);
	print_mono_font_string ("N %");

	set_2d_mono_font_position (0.9, -0.0);
	set_mono_font_rel_position (-0.5 * get_mono_font_string_width("NG%"), -13.0);
	print_mono_font_string (" G ");


	set_2d_mono_font_position (0.9, -0.1);
	set_mono_font_rel_position (-0.5 * get_mono_font_string_width("1    2"), 8.0);
	print_mono_font_string ("1    2");

	y = 0.5;
	split = 100.0;

	//
	// engine 1 rpm
	//

	digital_readout = bound (current_flight_dynamics->left_engine_rpm.value, 0.0, 120.0);

	x = 0.1;
	draw_engine_bar(x, y, digital_readout, split, 120.0, 98.0, 104.0, 94.0, 110.0, FALSE);
	draw_engine_value(0.75, 0.15, "%3.0f", digital_readout, 98.0, 104.0, 94.0, 110.0);
	draw_2d_mono_sprite (large_engine_bar_marker, x + 0.06, 0.75, MFD_COLOUR_RED);

	set_2d_mono_font_position (x, -0.1);
	set_mono_font_rel_position (-0.5 * get_mono_font_string_width(" "), 8.0);
	print_mono_font_string("1");

	//
	// engine 2 rpm
	//

	digital_readout = bound (current_flight_dynamics->right_engine_rpm.value, 0.0, 120.0);

	x = 0.5;
	draw_engine_bar(x, y, digital_readout, split, 120.0, 98.0, 104.0, 94.0, 110.0, FALSE);
	draw_engine_value(1.05, 0.15, "%3.0f", digital_readout, 98.0, 104.0, 94.0, 110.0);
	draw_2d_mono_sprite (large_engine_bar_marker, x - 0.06, 0.75, MFD_COLOUR_RED);

	set_2d_mono_font_position (x, -0.1);
	set_mono_font_rel_position (-0.5 * get_mono_font_string_width(" "), 8.0);
	print_mono_font_string("2");

	//
	// rotor rpm
	//

	x = 0.3;
	y = 0.5;
	split = 100.0;

	digital_readout = bound (current_flight_dynamics->main_rotor_rpm.value, 0.0, 125.0);
	draw_rotor_rpm_bar(digital_readout, x, y);

	////////////////////////////////////////
	//
	// NG RPM left engine
	//
	////////////////////////////////////////

	digital_readout = bound (current_flight_dynamics->left_engine_n1_rpm.value, 0.0, 120.0);
	draw_engine_value(0.75, -0.1, "%3.0f", digital_readout, 0.0, 99.0, 63.0, 102.0);

	////////////////////////////////////////
	//
	// NG RPM right engine
	//
	////////////////////////////////////////

	digital_readout = bound (current_flight_dynamics->right_engine_n1_rpm.value, 0.0, 120.0);
	draw_engine_value(1.05, -0.1, "%3.0f", digital_readout, 0.0, 99.0, 63.0, 102.0);


	// engine starters
	if (current_flight_dynamics->left_engine_starter_active || current_flight_dynamics->right_engine_starter_active)
	{
		draw_2d_box(0.62, 0.1, 1.18, -0.4, FALSE, TRUE, MFD_COLOUR1);

		set_mono_font_colour(MFD_COLOUR_YELLOW);
		set_mono_font_type (MONO_FONT_TYPE_14X21);

		if (current_flight_dynamics->left_engine_starter_active)
		{
			set_2d_mono_font_position (0.75, -0.32);
			set_mono_font_rel_position (-0.5 * get_mono_font_string_width("ON"), -21.0);
			print_mono_font_string("ON");
		}

		if (current_flight_dynamics->right_engine_starter_active)
		{
			set_2d_mono_font_position (1.05, -0.32);
			set_mono_font_rel_position (-0.5 * get_mono_font_string_width("ON"), -21.0);
			print_mono_font_string("ON");
		}

		set_mono_font_colour (MFD_COLOUR1);
		set_mono_font_type (MONO_FONT_TYPE_10X16);

		set_2d_mono_font_position (0.9, -0.42);
		set_mono_font_rel_position (-0.5 * get_mono_font_string_width("START"), -21.0);
		print_mono_font_string ("START");
	}

	// In startup mode (engines not up to speed) show some extra information in bottom half
	if (current_flight_dynamics->left_engine_n1_rpm.value < current_flight_dynamics->engine_idle_rpm
		|| current_flight_dynamics->right_engine_n1_rpm.value < current_flight_dynamics->engine_idle_rpm)
	{
		// hydraulic pressure

		draw_2d_box(-0.1, -0.35, 0.55, -0.77, FALSE, TRUE, MFD_COLOUR1);

		set_2d_mono_font_position (-0.08, -0.45);
		set_mono_font_rel_position (2.0, -16.0);
		print_mono_font_string ("HYD PSI");

		set_2d_mono_font_position (-0.05, -0.55);
		set_mono_font_rel_position (2.0, -16.0);
		print_mono_font_string ("PRI");

		set_2d_mono_font_position (-0.05, -0.65);
		set_mono_font_rel_position (2.0, -16.0);
		print_mono_font_string ("UTIL");

		set_2d_mono_font_position (-0.05, -0.75);
		set_mono_font_rel_position (2.0, -16.0);
		print_mono_font_string ("ACC");

		digital_readout = get_hydraulic_pressure() * (300.0 + ((int)(get_gunship_entity()) & 0xff) * 0.1);
		draw_engine_value(0.38, -0.55, "%3.0f0", digital_readout, 275.0, 325.0, 250.0, 325.0);

		if (current_flight_dynamics->dynamics_damage & DYNAMICS_DAMAGE_SECONDARY_HYDRAULICS)
			val = 0.0;
		else
			val = 304.0;

		draw_engine_value(0.38, -0.65, "%3.0f0", val, 275.0, 325.0, 250.0, 325.0);

		draw_engine_value(0.38, -0.75, "%3.0f0", max(digital_readout, val), 275.0, 325.0, 250.0, 325.0);

		// engine oil psi

		draw_2d_box(-0.7, -0.35, -0.15, -0.77, FALSE, TRUE, MFD_COLOUR1);

		set_2d_mono_font_position (-0.68, -0.45);
		set_mono_font_rel_position (2.0, -16.0);
		print_mono_font_string ("ENGINE");

		set_2d_mono_font_position (-0.64, -0.52);
		set_mono_font_rel_position (2.0, -16.0);
		print_mono_font_string ("OIL PSI");

		set_2d_mono_font_position (-0.425, -0.75);
		set_mono_font_rel_position (-0.5 * get_mono_font_string_width("1    2"), -16.0);
		print_mono_font_string ("1    2");

		{
			float lpres, rpres;

			if ((current_flight_dynamics->dynamics_damage & DYNAMICS_DAMAGE_LEFT_ENGINE) != 0)
				lpres = 0.0;
			else if ((current_flight_dynamics->dynamics_damage & DYNAMICS_DAMAGE_LOW_OIL_PRESSURE) != 0)
				lpres = 15.0;
			else if ((current_flight_dynamics->dynamics_damage & DYNAMICS_DAMAGE_HIGH_OIL_PRESSURE) != 0)
				lpres = 115.0;
			else
				lpres = 22.0 + max(current_flight_dynamics->left_engine_temp.value, 500) * current_flight_dynamics->left_engine_n1_rpm.value * 0.001;

			draw_engine_value(-0.55, -0.65, "%3.0f", lpres, 28.0, 100.0, 22.0, 120.0);

			if ((current_flight_dynamics->dynamics_damage & DYNAMICS_DAMAGE_RIGHT_ENGINE) != 0)
				rpres = 0.0;
			else if ((current_flight_dynamics->dynamics_damage & DYNAMICS_DAMAGE_LOW_OIL_PRESSURE) != 0)
				rpres = 15.0;
			else if ((current_flight_dynamics->dynamics_damage & DYNAMICS_DAMAGE_HIGH_OIL_PRESSURE) != 0)
				rpres = 115.0;
			else
				rpres = 22.0 + max(current_flight_dynamics->right_engine_temp.value, 500) * current_flight_dynamics->right_engine_n1_rpm.value * 0.001;

			draw_engine_value(-0.3, -0.65, "%3.0f", rpres, 28.0, 100.0, 22.0, 120.0);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// DRAW MFD ON COCKPIT
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_apache_mfd_on_cockpit (float x_org, float y_org, int large_mfd, int draw_translucent_background, mfd_locations location)
{
#if 0
	mfd_modes
		*mfd_mode;

	ASSERT ((location == MFD_LOCATION_PILOT_LHS) || (location == MFD_LOCATION_PILOT_RHS)
			|| (location == MFD_LOCATION_CPG_LHS) || (location == MFD_LOCATION_CPG_RHS));

	update_pointer_position();

	if (location == MFD_LOCATION_PILOT_LHS)
		mfd_mode = &lhs_mfd_mode;
	else if (location == MFD_LOCATION_PILOT_RHS)
		mfd_mode = &rhs_mfd_mode;
	else if (location == MFD_LOCATION_CPG_LHS)
		mfd_mode = &cpg_lhs_mfd_mode;
	else
		mfd_mode = &cpg_rhs_mfd_mode;

	////////////////////////////////////////
	//
	// set up MFD 2D environment
	//
	////////////////////////////////////////

	set_2d_active_environment (mfd_env);

	//
	// window
	//

	set_2d_window (mfd_env, MFD_WINDOW_X_MIN, MFD_WINDOW_Y_MIN, MFD_WINDOW_X_MAX, MFD_WINDOW_Y_MAX);

	//
	// viewport
	//

	mfd_viewport_size = MFD_VIEWPORT_SIZE;

	mfd_viewport_x_org = x_org;

	mfd_viewport_y_org = y_org;

	mfd_viewport_x_min = mfd_viewport_x_org - (mfd_viewport_size * 0.5);

	mfd_viewport_y_min = mfd_viewport_y_org - (mfd_viewport_size * 0.5);

	mfd_viewport_x_max = mfd_viewport_x_org + (mfd_viewport_size * 0.5) - 0.001;

	mfd_viewport_y_max = mfd_viewport_y_org + (mfd_viewport_size * 0.5) - 0.001;

	set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

	////////////////////////////////////////
	//
	// draw MFD
	//
	////////////////////////////////////////

	switch (*mfd_mode)
	{
		////////////////////////////////////////
		case MFD_MODE_OFF:
		////////////////////////////////////////
		{
			if (lock_screen (active_screen))
			{
				draw_layout_grid ();

				unlock_screen (active_screen);
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_DAMAGED:
		////////////////////////////////////////
		{
			if (lock_screen (active_screen))
			{
				draw_layout_grid ();

				draw_damaged_mfd ();

				unlock_screen (active_screen);
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_GROUND_RADAR:
		////////////////////////////////////////
		{
			if (lock_screen (active_screen))
			{
				draw_layout_grid ();

				draw_ground_radar_mfd ();

				unlock_screen (active_screen);
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_AIR_RADAR:
		////////////////////////////////////////
		{
			if (lock_screen (active_screen))
			{
				draw_layout_grid ();

				draw_air_radar_mfd ();

				unlock_screen (active_screen);
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_FLIR:
		////////////////////////////////////////
		{
			draw_3d_flir_mfd (location);

			if (lock_screen (active_screen))
			{
				draw_layout_grid ();

				draw_2d_flir_mfd (TRUE, FALSE);

				unlock_screen (active_screen);
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_DTV:
		////////////////////////////////////////
		{
			draw_3d_dtv_mfd (location);

			if (lock_screen (active_screen))
			{
				draw_layout_grid ();

				draw_2d_dtv_mfd (TRUE, FALSE);

				unlock_screen (active_screen);
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_DVO:
		////////////////////////////////////////
		{
			draw_3d_dvo_mfd (location);

			if (lock_screen (active_screen))
			{
				draw_layout_grid ();

				draw_2d_dvo_mfd (TRUE, FALSE);

				unlock_screen (active_screen);
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_TSD:
		////////////////////////////////////////
		{
			if (lock_screen (active_screen))
			{
				draw_layout_grid ();

				draw_tactical_situation_display_mfd ();

				unlock_screen (active_screen);
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_ASE:
		////////////////////////////////////////
		{
			if (lock_screen (active_screen))
			{
				draw_layout_grid ();

				draw_aircraft_survivability_equipment_display_mfd ();

				unlock_screen (active_screen);
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_WEAPON:
		////////////////////////////////////////
		{
			if (lock_screen (active_screen))
			{
				draw_layout_grid ();

				draw_weapon_display_mfd (location, FALSE);

				unlock_screen (active_screen);
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_SYSTEM:
		////////////////////////////////////////
		{
			if (lock_screen (active_screen))
			{
				draw_layout_grid ();

				draw_system_display_mfd ();

				unlock_screen (active_screen);
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_ENGINE:
		////////////////////////////////////////
		{
			if (lock_screen (active_screen))
			{
				draw_layout_grid ();

				draw_engine_display_mfd ();

				unlock_screen (active_screen);
			}

			break;
		}
	}
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// FLIGHT
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//
// pitch ladder
//
////////////////////////////////////////

#define PITCH_DATUM_X	(x_centre)
#define PITCH_DATUM_Y	((float) -0.1)

//									P9 O (+ve)
//
//
//    P1    P2    P3    P4    P5    P6    P7
//     O-----O     O-----O     O-----O-----O
//     |
//     |
//     |
// P8  O					 	   P10 O (-ve)

#define PITCH_BAR_X1		((float) (+0.075) * pitch_bar_scale)
#define PITCH_BAR_Y1		((float) (+0.000) * pitch_bar_scale)
#define PITCH_BAR_X2		((float) (+0.140) * pitch_bar_scale)
#define PITCH_BAR_Y2		((float) (+0.000) * pitch_bar_scale)
#define PITCH_BAR_X3		((float) (+0.170) * pitch_bar_scale)
#define PITCH_BAR_Y3		((float) (+0.000) * pitch_bar_scale)
#define PITCH_BAR_X4		((float) (+0.225) * pitch_bar_scale)
#define PITCH_BAR_Y4		((float) (+0.000) * pitch_bar_scale)
#define PITCH_BAR_X5		((float) (+0.260) * pitch_bar_scale)
#define PITCH_BAR_Y5		((float) (+0.000) * pitch_bar_scale)
#define PITCH_BAR_X6		((float) (+0.315) * pitch_bar_scale)
#define PITCH_BAR_Y6		((float) (+0.000) * pitch_bar_scale)
#define PITCH_BAR_X7		((float) (+1.000) * pitch_bar_scale)
#define PITCH_BAR_Y7		((float) (+0.000) * pitch_bar_scale)
#define PITCH_BAR_X8		PITCH_BAR_X6 //((float) (+0.125) * pitch_bar_scale)
#define PITCH_BAR_Y8		((float) (-0.050) * pitch_bar_scale)
#define PITCH_BAR_X9		((float) (+0.430) * pitch_bar_scale)
#define PITCH_BAR_Y9		((float) (+0.000) * pitch_bar_scale)
#define PITCH_BAR_X10	((float) (+0.430) * pitch_bar_scale)
#define PITCH_BAR_Y10	((float) (-0.000) * pitch_bar_scale)
#define PITCH_BAR_X11	((float) (+0.040) * pitch_bar_scale)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int limit_pitch (int pitch, int *step_direction)
{
	if (pitch > 9)
	{
		pitch -= 18;

		pitch = -pitch;

		*step_direction = -(*step_direction);
	}
	else if (pitch < -9)
	{
		pitch += 18;

		pitch = -pitch;

		*step_direction = -(*step_direction);
	}

	return (pitch);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_pitch_ladder (void)
{
	char
		s[20];

	int
		int_roll,
		int_pitch,
		step_direction,
		loop;

	float
		y_adjust_above_line,
		y_adjust_below_line,
		x_centre,
		size,
		roll_size,
		vp_u_size,
		vp_v_size,
		pitch,
		mod_pitch,
		tan_mod_pitch,
		pitch_bar_scale,
		roll,
		u,
		v,
		x,
		y,
		x_scale,
		y_scale,
		x_horizon,
		y_horizon,
		x_10_deg_step,
		y_10_deg_step,
		x_adjust;

	{
		set_mono_font_type (MONO_FONT_TYPE_10X16);

		y_adjust_above_line = -6.0;
		y_adjust_below_line = -6.0;
	}

	x_centre = 0.0;
	size = 0.6;
	pitch_bar_scale = 0.6;

	get_2d_float_screen_coordinates (PITCH_DATUM_X, PITCH_DATUM_Y, &u, &v);

	//
	// roll
	//

	roll = get_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_ROLL);

	set_2d_instance_position (mfd_env, PITCH_DATUM_X, PITCH_DATUM_Y);
	roll_size = size + 0.25;

	set_2d_instance_rotation (mfd_env, rad (0.0));
	draw_2d_half_thick_line (0.0, roll_size, 0.0, roll_size - 0.05, MFD_COLOUR_YELLOW);

	for (int_roll = 10; int_roll <= 90; int_roll += 10)
	{
		if (int_roll <= 30)
		{
			set_2d_instance_rotation (mfd_env, rad (int_roll - 5));
			draw_2d_line (0.0, roll_size, 0.0, roll_size - 0.025, MFD_COLOUR_YELLOW);
			set_2d_instance_rotation (mfd_env, rad (-(int_roll - 5)));
			draw_2d_line (0.0, roll_size, 0.0, roll_size - 0.025, MFD_COLOUR_YELLOW);
		}

		if (int_roll <= 30 || deg(roll) > 30.0)
		{
			set_2d_instance_rotation (mfd_env, rad (int_roll));
			draw_2d_half_thick_line (0.0, roll_size, 0.0, roll_size - 0.05, MFD_COLOUR_YELLOW);
		}

		if (int_roll <= 30 || deg(roll) < -30.0)
		{

			set_2d_instance_rotation (mfd_env, rad (-int_roll));
			draw_2d_half_thick_line (0.0, roll_size, 0.0, roll_size - 0.05, MFD_COLOUR_YELLOW);
		}
	}

	set_2d_instance_rotation (mfd_env, bound (roll, rad (-90.0), rad (90.0)));
	draw_2d_half_thick_line (0.0, roll_size - 0.1, 0.0, roll_size, MFD_COLOUR_YELLOW);


	//
	// set 2D environment
	//

	set_2d_window (mfd_env, MFD_WINDOW_X_MIN * size, MFD_WINDOW_Y_MIN * size, MFD_WINDOW_X_MAX * size, MFD_WINDOW_Y_MAX * size);

	vp_u_size = mfd_viewport_size * size * 0.45;
	vp_v_size = mfd_viewport_size * size * 0.4;

	set_2d_viewport (mfd_env, u - vp_u_size, v - vp_v_size, u + vp_u_size - 0.001, v + vp_v_size - 0.001);

	//
	// pitch
	//

	pitch = get_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_PITCH);

	mod_pitch = fmod (pitch, rad (10.0));

	tan_mod_pitch = -tan (mod_pitch);

	int_pitch = (int) (pitch * (1.0 / rad (10.0)));

	//
	// get x and y scale factors
	//

	x_scale = -sin (roll) * 2.0 * pitch_bar_scale;

	y_scale = cos (roll) * 2.0 * pitch_bar_scale;

	x_horizon = tan_mod_pitch * x_scale;
	y_horizon = tan_mod_pitch * y_scale;

	x_10_deg_step = tan (rad (10.0)) * x_scale;
	y_10_deg_step = tan (rad (10.0)) * y_scale;

	////////////////////////////////////////
	//
	// draw pitch ladder
	//
	////////////////////////////////////////

	step_direction = -1;

	int_pitch = limit_pitch (int_pitch + 4, &step_direction);

	x = x_horizon + x_10_deg_step * 4.0;
	y = y_horizon + y_10_deg_step * 4.0;

	set_2d_instance_rotation (mfd_env, roll);

	for (loop = 0; loop < 9; loop++)
	{
		float p_factor = 0.02 * abs(int_pitch);

		set_2d_instance_position (mfd_env, x, y);

		switch (int_pitch)
		{
			////////////////////////////////////////
			case 0:
			////////////////////////////////////////
			{
				set_mono_font_colour (MFD_COLOUR_RED);
				draw_2d_half_thick_line (+PITCH_BAR_X7, +PITCH_BAR_Y7, -PITCH_BAR_X7, +PITCH_BAR_Y7, MFD_COLOUR_RED);

				break;
			}
			////////////////////////////////////////
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:
			////////////////////////////////////////
			{
				set_mono_font_colour (MFD_COLOUR_BLUE);

				if (step_direction == -1)
				{
					draw_2d_half_thick_line (p_factor+PITCH_BAR_X1, +PITCH_BAR_Y1, p_factor+PITCH_BAR_X6, +PITCH_BAR_Y6, MFD_COLOUR_BLUE);
					draw_2d_half_thick_line (-p_factor - PITCH_BAR_X1, +PITCH_BAR_Y1, -p_factor - PITCH_BAR_X6, +PITCH_BAR_Y6, MFD_COLOUR_BLUE);

					draw_2d_half_thick_line (p_factor + PITCH_BAR_X6, +PITCH_BAR_Y6, p_factor + PITCH_BAR_X8, +PITCH_BAR_Y8, MFD_COLOUR_BLUE);
					draw_2d_half_thick_line (-p_factor - PITCH_BAR_X6, +PITCH_BAR_Y6, -p_factor - PITCH_BAR_X8, +PITCH_BAR_Y8, MFD_COLOUR_BLUE);
				}
				else
				{
					draw_2d_half_thick_line (-p_factor - PITCH_BAR_X1, -PITCH_BAR_Y1, -p_factor - PITCH_BAR_X6, -PITCH_BAR_Y6, MFD_COLOUR_BLUE);
					draw_2d_half_thick_line (p_factor + PITCH_BAR_X1, -PITCH_BAR_Y1, p_factor + PITCH_BAR_X6, -PITCH_BAR_Y6, MFD_COLOUR_BLUE);

					draw_2d_half_thick_line (-p_factor - PITCH_BAR_X6, -PITCH_BAR_Y6, -p_factor - PITCH_BAR_X8, -PITCH_BAR_Y8, MFD_COLOUR_BLUE);
					draw_2d_half_thick_line (p_factor + PITCH_BAR_X6, -PITCH_BAR_Y6, p_factor + PITCH_BAR_X8, -PITCH_BAR_Y8, MFD_COLOUR_BLUE);
				}

				sprintf (s, "%d0", int_pitch);

				x_adjust = get_mono_font_string_width (s) * -0.5;

				set_2d_mono_font_position (p_factor + PITCH_BAR_X9, +PITCH_BAR_Y9);

				set_mono_font_rel_position (x_adjust, y_adjust_above_line);

				print_mono_font_string (s);

				set_2d_mono_font_position (-p_factor - PITCH_BAR_X9, +PITCH_BAR_Y9);

				set_mono_font_rel_position (x_adjust, y_adjust_above_line);

				print_mono_font_string (s);

				break;
			}
			////////////////////////////////////////
			case 9:
			////////////////////////////////////////
			{
				draw_2d_half_thick_line (p_factor + PITCH_BAR_X1, +PITCH_BAR_Y1, p_factor + PITCH_BAR_X6, +PITCH_BAR_Y6, MFD_COLOUR_BLUE);
				draw_2d_half_thick_line (-p_factor - PITCH_BAR_X1, +PITCH_BAR_Y1, -p_factor - PITCH_BAR_X6, +PITCH_BAR_Y6, MFD_COLOUR_BLUE);

				break;
			}
			////////////////////////////////////////
			case -1:
			case -2:
			case -3:
			case -4:
			case -5:
			case -6:
			case -7:
			case -8:
			////////////////////////////////////////
			{
				set_mono_font_colour (MFD_COLOUR_RED);
				if (step_direction == -1)
				{
					draw_2d_half_thick_line (p_factor + PITCH_BAR_X1, +PITCH_BAR_Y1, p_factor + PITCH_BAR_X2, +PITCH_BAR_Y2, MFD_COLOUR_RED);
					draw_2d_half_thick_line (-p_factor - PITCH_BAR_X1, +PITCH_BAR_Y1, -p_factor - PITCH_BAR_X2, +PITCH_BAR_Y2, MFD_COLOUR_RED);

					draw_2d_half_thick_line (p_factor + PITCH_BAR_X3, +PITCH_BAR_Y3, p_factor + PITCH_BAR_X4, +PITCH_BAR_Y4, MFD_COLOUR_RED);
					draw_2d_half_thick_line (-p_factor - PITCH_BAR_X3, +PITCH_BAR_Y3, -p_factor - PITCH_BAR_X4, +PITCH_BAR_Y4, MFD_COLOUR_RED);

					draw_2d_half_thick_line (p_factor + PITCH_BAR_X5, +PITCH_BAR_Y5, p_factor + PITCH_BAR_X6, +PITCH_BAR_Y6, MFD_COLOUR_RED);
					draw_2d_half_thick_line (-p_factor - PITCH_BAR_X5, +PITCH_BAR_Y5, -p_factor - PITCH_BAR_X6, +PITCH_BAR_Y6, MFD_COLOUR_RED);

					draw_2d_half_thick_line (p_factor + PITCH_BAR_X6, +PITCH_BAR_Y6, p_factor + PITCH_BAR_X8, -PITCH_BAR_Y8, MFD_COLOUR_RED);
					draw_2d_half_thick_line (-p_factor - PITCH_BAR_X6, +PITCH_BAR_Y6, -p_factor - PITCH_BAR_X8, -PITCH_BAR_Y8, MFD_COLOUR_RED);
				}
				else
				{
					draw_2d_half_thick_line (-p_factor - PITCH_BAR_X1, -PITCH_BAR_Y1, -p_factor - PITCH_BAR_X2, -PITCH_BAR_Y2, MFD_COLOUR_RED);
					draw_2d_half_thick_line (p_factor + PITCH_BAR_X1, -PITCH_BAR_Y1, p_factor + PITCH_BAR_X2, -PITCH_BAR_Y2, MFD_COLOUR_RED);

					draw_2d_half_thick_line (-p_factor - PITCH_BAR_X3, -PITCH_BAR_Y3, -p_factor - PITCH_BAR_X4, -PITCH_BAR_Y4, MFD_COLOUR_RED);
					draw_2d_half_thick_line (p_factor + PITCH_BAR_X3, -PITCH_BAR_Y3, p_factor + PITCH_BAR_X4, -PITCH_BAR_Y4, MFD_COLOUR_RED);

					draw_2d_half_thick_line (-p_factor - PITCH_BAR_X5, -PITCH_BAR_Y5, -p_factor - PITCH_BAR_X6, -PITCH_BAR_Y6, MFD_COLOUR_RED);
					draw_2d_half_thick_line (p_factor + PITCH_BAR_X5, -PITCH_BAR_Y5, p_factor + PITCH_BAR_X6, -PITCH_BAR_Y6, MFD_COLOUR_RED);

					draw_2d_half_thick_line (-p_factor - PITCH_BAR_X6, -PITCH_BAR_Y6, -p_factor - PITCH_BAR_X8, +PITCH_BAR_Y8, MFD_COLOUR_RED);
					draw_2d_half_thick_line (p_factor + PITCH_BAR_X6, -PITCH_BAR_Y6, p_factor + PITCH_BAR_X8, +PITCH_BAR_Y8, MFD_COLOUR_RED);
				}

				sprintf (s, "%d0", abs(int_pitch));

				x_adjust = get_mono_font_string_width (s) * -0.5;

				set_2d_mono_font_position (p_factor + PITCH_BAR_X10, +PITCH_BAR_Y10);

				set_mono_font_rel_position (x_adjust, y_adjust_below_line);

				print_mono_font_string (s);

				set_2d_mono_font_position (-p_factor - PITCH_BAR_X10, +PITCH_BAR_Y10);

				set_mono_font_rel_position (x_adjust, y_adjust_below_line);

				print_mono_font_string (s);

				break;
			}
			////////////////////////////////////////
			case -9:
			////////////////////////////////////////
			{
				draw_2d_half_thick_line (p_factor + PITCH_BAR_X1, +PITCH_BAR_Y1, p_factor + PITCH_BAR_X2, +PITCH_BAR_Y2, MFD_COLOUR_RED);
				draw_2d_half_thick_line (-p_factor - PITCH_BAR_X1, +PITCH_BAR_Y1, -p_factor - PITCH_BAR_X2, +PITCH_BAR_Y2, MFD_COLOUR_RED);

				draw_2d_half_thick_line (p_factor + PITCH_BAR_X3, +PITCH_BAR_Y3, p_factor + PITCH_BAR_X4, +PITCH_BAR_Y4, MFD_COLOUR_RED);
				draw_2d_half_thick_line (-p_factor - PITCH_BAR_X3, +PITCH_BAR_Y3, -p_factor - PITCH_BAR_X4, +PITCH_BAR_Y4, MFD_COLOUR_RED);

				draw_2d_half_thick_line (p_factor + PITCH_BAR_X5, +PITCH_BAR_Y5, p_factor + PITCH_BAR_X6, +PITCH_BAR_Y6, MFD_COLOUR_RED);
				draw_2d_half_thick_line (-p_factor - PITCH_BAR_X5, +PITCH_BAR_Y5, -p_factor - PITCH_BAR_X6, +PITCH_BAR_Y6, MFD_COLOUR_RED);

				break;
			}
		}

		int_pitch = limit_pitch (int_pitch + step_direction, &step_direction);

		x -= x_10_deg_step;
		y -= y_10_deg_step;
	}

	//
	// restore 2D environment
	//

	set_mono_font_colour (MFD_COLOUR1);

	reset_2d_instance (mfd_env);

	// centre datum

	draw_2d_half_thick_line (-0.25, pitch_ladder_datum_position, -0.08, pitch_ladder_datum_position, MFD_COLOUR_YELLOW);
	draw_2d_half_thick_line ( 0.25, pitch_ladder_datum_position,  0.08, pitch_ladder_datum_position, MFD_COLOUR_YELLOW);

	draw_2d_half_thick_line (-0.08, pitch_ladder_datum_position, -0.04, pitch_ladder_datum_position - 0.08, MFD_COLOUR_YELLOW);
	draw_2d_half_thick_line ( 0.08, pitch_ladder_datum_position,  0.04, pitch_ladder_datum_position - 0.08, MFD_COLOUR_YELLOW);

	draw_2d_half_thick_line (0.0, pitch_ladder_datum_position, -0.04, pitch_ladder_datum_position - 0.08, MFD_COLOUR_YELLOW);
	draw_2d_half_thick_line (0.0, pitch_ladder_datum_position,  0.04, pitch_ladder_datum_position - 0.08, MFD_COLOUR_YELLOW);

	set_2d_window (mfd_env, MFD_WINDOW_X_MIN, MFD_WINDOW_Y_MIN, MFD_WINDOW_X_MAX, MFD_WINDOW_Y_MAX);

	set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_sideslip(void)
{
	static float last_turn_rate = 0.0;
	const float slip_line_pos = -1.15;
	const float scale = 0.28;
	const float slot_scale = 0.035;
	const float turn_rate_scale_bottom = -1.07;
	const float turn_rate_scale_top = turn_rate_scale_bottom + 0.05;

	float slip = bound(current_flight_dynamics->velocity_x.value, -20.0, 20.0) / 20.0;
	float turn_rate = bound(deg(current_flight_dynamics->angular_heading_velocity.value) / 30.0, -1.0, 1.0);
	float use_turn_rate = 0.1 * turn_rate + 0.9 * last_turn_rate;
	last_turn_rate = turn_rate;

	// slip ball
	draw_2d_half_thick_line(-scale, slip_line_pos, scale, slip_line_pos, MFD_COLOUR1);
	draw_2d_half_thick_line(-slot_scale, slip_line_pos, -slot_scale, slip_line_pos + 2 * slot_scale, MFD_COLOUR1);
	draw_2d_half_thick_line( slot_scale, slip_line_pos,  slot_scale, slip_line_pos + 2 * slot_scale, MFD_COLOUR1);

	draw_2d_mono_sprite(large_tsd_waypoint_marker, slip * scale, slip_line_pos + slot_scale, MFD_COLOUR1);

	// turn rate
	draw_2d_line(- scale, turn_rate_scale_bottom, -scale, turn_rate_scale_top, MFD_COLOUR1);
	draw_2d_line(-(scale * 5.0 / 7.0), turn_rate_scale_bottom, -(scale * 5.0 / 7.0), turn_rate_scale_top, MFD_COLOUR1);
	draw_2d_line(-(scale * 3.0 / 7.0), turn_rate_scale_bottom, -(scale * 3.0 / 7.0), turn_rate_scale_top, MFD_COLOUR1);
	draw_2d_line(-(scale * 1.0 / 7.0), turn_rate_scale_bottom, -(scale * 1.0 / 7.0), turn_rate_scale_top, MFD_COLOUR1);
	draw_2d_line(  scale, turn_rate_scale_bottom,  scale, turn_rate_scale_top, MFD_COLOUR1);
	draw_2d_line( (scale * 5.0 / 7.0), turn_rate_scale_bottom,  (scale * 5.0 / 7.0), turn_rate_scale_top, MFD_COLOUR1);
	draw_2d_line( (scale * 3.0 / 7.0), turn_rate_scale_bottom,  (scale * 3.0 / 7.0), turn_rate_scale_top, MFD_COLOUR1);
	draw_2d_line( (scale * 1.0 / 7.0), turn_rate_scale_bottom,  (scale * 1.0 / 7.0), turn_rate_scale_top, MFD_COLOUR1);

	draw_2d_mono_sprite(large_tsd_waypoint_marker, -use_turn_rate * scale, turn_rate_scale_bottom + 0.025, MFD_COLOUR1);

	draw_2d_mono_sprite(turn_rate_hat, 0, turn_rate_scale_top, MFD_COLOUR1);
	draw_2d_mono_sprite(turn_rate_hat, (scale * 4.0 / 7.0), turn_rate_scale_top, MFD_COLOUR1);
	draw_2d_mono_sprite(turn_rate_hat, (scale * -4.0 / 7.0), turn_rate_scale_top, MFD_COLOUR1);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void display_true_airspeed (void)
{
	float
		true_airspeed;

	char
		s[20];

	true_airspeed = current_flight_dynamics->velocity_z.value;

	true_airspeed = knots (true_airspeed);

	sprintf (s, "%d", (int) true_airspeed);

	set_2d_mono_font_position (-1.0, -0.1);

	set_mono_font_type (MONO_FONT_TYPE_14X21);
	set_mono_font_rel_position (1.0, -8.0);

	print_mono_font_string (s);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void display_altitude (void)
{
	float
		radar_altitude,
		width;

	char
		s[20];

	radar_altitude = feet (current_flight_dynamics->radar_altitude.value);

	if (radar_altitude <= 1500.0)
	{
		sprintf (s, "R%d", get_apache_display_radar_altitude());
	}
	else
	{
		int barometric_altitude = 10 * (int)((feet(current_flight_dynamics->barometric_altitude.value) + 5.0) / 10.0);

		sprintf (s, "%d", (int) barometric_altitude);
	}

	width = get_mono_font_string_width (s);

	set_2d_mono_font_position (1.1, 0.85);

	set_mono_font_type (MONO_FONT_TYPE_14X21);
	set_mono_font_rel_position (-width - 2.0, -4.0);

	print_mono_font_string (s);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
//
// rate of climb scale
//
////////////////////////////////////////

#define CLIMB_SCALE_FSD					((float) 0.6)

#define CLIMB_SCALE_MAJOR_TICK_X1	((float) (1.000) + x_adjust)
#define CLIMB_SCALE_MAJOR_TICK_X2	((float) (1.05) + x_adjust)
#define CLIMB_SCALE_MAJOR_TICK_X3	((float) (1.100) + x_adjust)
#define CLIMB_SCALE_MAJOR_TICK_X4	((float) (1.15) + x_adjust)
#define CLIMB_SCALE_X1  ((float)(1.05) + x_adjust)
#define CLIMB_SCALE_X2  CLIMB_SCALE_MAJOR_TICK_X3

#define CLIMB_SCALE_MINOR_TICK_X1	((float) (1.05) + x_adjust)
#define CLIMB_SCALE_MINOR_TICK_X2	((float) (1.02) + x_adjust)
#define CLIMB_SCALE_MINOR_TICK_X3	((float) (1.10) + x_adjust)
#define CLIMB_SCALE_MINOR_TICK_X4	((float) (1.13) + x_adjust)

static char rate_of_climb_scale_pointer[] =
{
	7,
	13,
	-7,
	-6,
	1,0,0,0,0,0,0,
	1,1,0,0,0,0,0,
	1,1,1,0,0,0,0,
	1,1,1,1,0,0,0,
	1,1,1,1,1,0,0,
	1,1,1,1,1,1,0,
	1,1,1,1,1,1,1,
	1,1,1,1,1,1,0,
	1,1,1,1,1,0,0,
	1,1,1,1,0,0,0,
	1,1,1,0,0,0,0,
	1,1,0,0,0,0,0,
	1,0,0,0,0,0,0,
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_rate_of_climb_scale (void)
{
	float
		radar_altitude,
		rate_of_climb,
		x,
		y,
		y1,
		y2,
		x_adjust;

//	if (draw_main_display)
	{
		x_adjust = -0.05;
	}
/*	else
	{
		x_adjust = -0.85;
	}*/

	//
	// draw scale
	//

	draw_2d_half_thick_line (CLIMB_SCALE_MAJOR_TICK_X1, (CLIMB_SCALE_FSD * +1.0) - 0.1, CLIMB_SCALE_MAJOR_TICK_X2, (CLIMB_SCALE_FSD * +1.0) - 0.1, MFD_COLOUR1);
	draw_2d_half_thick_line (CLIMB_SCALE_MAJOR_TICK_X3, (CLIMB_SCALE_FSD * +1.0) - 0.1, CLIMB_SCALE_MAJOR_TICK_X4, (CLIMB_SCALE_FSD * +1.0) - 0.1, MFD_COLOUR1);

	draw_2d_half_thick_line (CLIMB_SCALE_MAJOR_TICK_X1, (CLIMB_SCALE_FSD * +0.5) - 0.1, CLIMB_SCALE_MAJOR_TICK_X2, (CLIMB_SCALE_FSD * +0.5) - 0.1, MFD_COLOUR1);
	draw_2d_half_thick_line (CLIMB_SCALE_MAJOR_TICK_X3, (CLIMB_SCALE_FSD * +0.5) - 0.1, CLIMB_SCALE_MAJOR_TICK_X4, (CLIMB_SCALE_FSD * +0.5) - 0.1, MFD_COLOUR1);

	draw_2d_line (CLIMB_SCALE_MINOR_TICK_X1, (CLIMB_SCALE_FSD * +0.4) - 0.1, CLIMB_SCALE_MINOR_TICK_X2, (CLIMB_SCALE_FSD * +0.4) - 0.1, MFD_COLOUR1);

	draw_2d_line (CLIMB_SCALE_MINOR_TICK_X1, (CLIMB_SCALE_FSD * +0.3) - 0.1, CLIMB_SCALE_MINOR_TICK_X2, (CLIMB_SCALE_FSD * +0.3) - 0.1, MFD_COLOUR1);

	draw_2d_line (CLIMB_SCALE_MINOR_TICK_X1, (CLIMB_SCALE_FSD * +0.2) - 0.1, CLIMB_SCALE_MINOR_TICK_X2, (CLIMB_SCALE_FSD * +0.2) - 0.1, MFD_COLOUR1);

	draw_2d_line (CLIMB_SCALE_MINOR_TICK_X1, (CLIMB_SCALE_FSD * +0.1) - 0.1, CLIMB_SCALE_MINOR_TICK_X2, (CLIMB_SCALE_FSD * +0.1) - 0.1, MFD_COLOUR1);

	draw_2d_half_thick_line (CLIMB_SCALE_MAJOR_TICK_X1, (CLIMB_SCALE_FSD * +0.0) - 0.1, CLIMB_SCALE_MAJOR_TICK_X2, (CLIMB_SCALE_FSD * +0.0) - 0.1, MFD_COLOUR1);
	draw_2d_half_thick_line (CLIMB_SCALE_MAJOR_TICK_X3, (CLIMB_SCALE_FSD * +0.0) - 0.1, CLIMB_SCALE_MAJOR_TICK_X4, (CLIMB_SCALE_FSD * +0.0) - 0.1, MFD_COLOUR1);

	draw_2d_line (CLIMB_SCALE_MINOR_TICK_X1, (CLIMB_SCALE_FSD * -0.1) - 0.1, CLIMB_SCALE_MINOR_TICK_X2, (CLIMB_SCALE_FSD * -0.1) - 0.1, MFD_COLOUR1);

	draw_2d_line (CLIMB_SCALE_MINOR_TICK_X1, (CLIMB_SCALE_FSD * -0.2) - 0.1, CLIMB_SCALE_MINOR_TICK_X2, (CLIMB_SCALE_FSD * -0.2) - 0.1, MFD_COLOUR1);

	draw_2d_line (CLIMB_SCALE_MINOR_TICK_X1, (CLIMB_SCALE_FSD * -0.3) - 0.1, CLIMB_SCALE_MINOR_TICK_X2, (CLIMB_SCALE_FSD * -0.3) - 0.1, MFD_COLOUR1);

	draw_2d_line (CLIMB_SCALE_MINOR_TICK_X1, (CLIMB_SCALE_FSD * -0.4) - 0.1, CLIMB_SCALE_MINOR_TICK_X2, (CLIMB_SCALE_FSD * -0.4) - 0.1, MFD_COLOUR1);

	draw_2d_half_thick_line (CLIMB_SCALE_MAJOR_TICK_X1, (CLIMB_SCALE_FSD * -0.5) - 0.1, CLIMB_SCALE_MAJOR_TICK_X2, (CLIMB_SCALE_FSD * -0.5) - 0.1, MFD_COLOUR1);
	draw_2d_half_thick_line (CLIMB_SCALE_MAJOR_TICK_X3, (CLIMB_SCALE_FSD * -0.5) - 0.1, CLIMB_SCALE_MAJOR_TICK_X4, (CLIMB_SCALE_FSD * -0.5) - 0.1, MFD_COLOUR1);

	draw_2d_line (CLIMB_SCALE_MINOR_TICK_X3, (CLIMB_SCALE_FSD * -0.6) - 0.1, CLIMB_SCALE_MINOR_TICK_X4, (CLIMB_SCALE_FSD * -0.6) - 0.1, MFD_COLOUR1);

	draw_2d_line (CLIMB_SCALE_MINOR_TICK_X3, (CLIMB_SCALE_FSD * -0.7) - 0.1, CLIMB_SCALE_MINOR_TICK_X4, (CLIMB_SCALE_FSD * -0.7) - 0.1, MFD_COLOUR1);

	draw_2d_line (CLIMB_SCALE_MINOR_TICK_X3, (CLIMB_SCALE_FSD * -0.8) - 0.1, CLIMB_SCALE_MINOR_TICK_X4, (CLIMB_SCALE_FSD * -0.8) - 0.1, MFD_COLOUR1);

	draw_2d_line (CLIMB_SCALE_MINOR_TICK_X3, (CLIMB_SCALE_FSD * -0.9) - 0.1, CLIMB_SCALE_MINOR_TICK_X4, (CLIMB_SCALE_FSD * -0.9) - 0.1, MFD_COLOUR1);

	draw_2d_half_thick_line (CLIMB_SCALE_MAJOR_TICK_X1, (CLIMB_SCALE_FSD * -1.0) - 0.1, CLIMB_SCALE_MAJOR_TICK_X4, (CLIMB_SCALE_FSD * -1.0) - 0.1, MFD_COLOUR1);
//	draw_2d_half_thick_line (CLIMB_SCALE_MAJOR_TICK_X3, (CLIMB_SCALE_FSD * -1.0) - 0.1, CLIMB_SCALE_MAJOR_TICK_X4, (CLIMB_SCALE_FSD * -1.0) - 0.1, MFD_COLOUR1);

	//
	// display analogue radar altitude
	//

	radar_altitude = feet (current_flight_dynamics->radar_altitude.value);

	if (radar_altitude <= 200.0)
	{
		y1 = -CLIMB_SCALE_FSD - 0.1;

		y2 = -CLIMB_SCALE_FSD - 0.1 + radar_altitude * ((CLIMB_SCALE_FSD * 2.0) / 200.0);

		draw_2d_box(CLIMB_SCALE_X1, y1, CLIMB_SCALE_X2, y2, TRUE, FALSE, MFD_COLOUR1);
#if 0
		get_2d_float_screen_coordinates (CLIMB_SCALE_MAJOR_TICK_X2, y1, &x, &y1);

		get_2d_float_screen_coordinates (CLIMB_SCALE_MAJOR_TICK_X2, y2, &x, &y2);

		{
			draw_line (x + 1.0, y1, x + 1.0, y2, MFD_COLOUR1);
			draw_line (x + 2.0, y1, x + 2.0, y2, MFD_COLOUR1);
			draw_line (x + 3.0, y1, x + 3.0, y2, MFD_COLOUR1);
			draw_line (x + 4.0, y1, x + 4.0, y2, MFD_COLOUR1);
			draw_line (x + 5.0, y1, x + 5.0, y2, MFD_COLOUR1);
			draw_line (x + 6.0, y1, x + 6.0, y2, MFD_COLOUR1);
		}
#endif
	}

	//
	// draw rate of climb scale pointer
	//

	rate_of_climb = current_flight_dynamics->world_velocity_y.value;

	rate_of_climb = feet_per_minute (rate_of_climb);

	rate_of_climb = bound (rate_of_climb, -1000.0, 1000.0);

	x = CLIMB_SCALE_MAJOR_TICK_X1;

	y = rate_of_climb * (CLIMB_SCALE_FSD / 1000.0) - 0.1;

	draw_2d_mono_sprite (rate_of_climb_scale_pointer, x, y, MFD_COLOUR1);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void display_engine_torque (void)
{
	char
		s[20];

	sprintf (s, "%d%%", (int) current_flight_dynamics->combined_engine_torque.value);

	set_2d_mono_font_position (-1.05, 0.85);

//	if (draw_main_display)
	{
		set_mono_font_type (MONO_FONT_TYPE_14X21);
		set_mono_font_rel_position (1.0, -8.0);
	}
/*	else
	{
		if (draw_large_mfd)
		{
			set_mono_font_type (MONO_FONT_TYPE_7X12);

			set_mono_font_rel_position (1.0, -4.0);
		}
		else
		{
			set_mono_font_type (MONO_FONT_TYPE_5X7);

			set_mono_font_rel_position (1.0, -2.0);
		}
	}*/

	print_mono_font_string (s);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void display_waypoint_information (rgb_colour box_colour, float x_pos, float y_pos)
{
	unsigned is_direct_waypoint;
	apache_coordinate_points* wp = get_current_apache_navigation_point(&is_direct_waypoint);

	draw_2d_box(x_pos, y_pos, x_pos + 0.7, y_pos - 0.2, TRUE, FALSE, clear_mfd_colour);
	draw_2d_box(x_pos, y_pos, x_pos + 0.7, y_pos - 0.2, FALSE, TRUE, box_colour);

	if (wp && !apache_damage.navigation_computer)
	{
		char
			buffer2[16],
			buffer[16];

		vec3d
			*gunship_position;

		float
			waypoint_range;

		set_mono_font_type (MONO_FONT_TYPE_12X20);

		gunship_position = get_local_entity_vec3d_ptr (get_gunship_entity (), VEC3D_TYPE_POSITION);

		//
		// waypoint id & range
		//

		waypoint_range = get_2d_range(gunship_position, &wp->position);

		sprintf (buffer, "%c%02d      KM", wp->type, wp->number);
		if (waypoint_range < 100000.0)
		{
			int
				i;

			float
				f;

			//
			// this is required to prevent rounding errors around the 100Km mark
			//

			i = (int) waypoint_range * (1.0 / 100.0);
			f = (float) i * (1.0 / 10.0);

			sprintf(buffer2, "%5.1f", f);
		}
		else
			sprintf(buffer2, "%5.1f", waypoint_range * 0.001);

		set_2d_mono_font_position (x_pos + 0.01, y_pos - 0.03);
		set_mono_font_rel_position (1.0, 0.0);
		print_mono_font_string (buffer);

		set_mono_font_type (MONO_FONT_TYPE_14X21);

		set_2d_mono_font_position (x_pos + 0.21, y_pos - 0.03);
		set_mono_font_rel_position (0.0, -3.0);
		print_mono_font_string (buffer2);

		//
		// time to go
		//

		if ((current_flight_dynamics->velocity_z.value > 0.1) && (!apache_damage.navigation_computer))
		{
			float
				time_to_go,
				hours,
				minutes,
				seconds;

			time_to_go = waypoint_range / current_flight_dynamics->velocity_z.value;
			get_digital_clock_values (time_to_go, &hours, &minutes, &seconds);

			sprintf(buffer, "%3s %02d:%02d", wp->free_text, (int) hours, (int) minutes);
		}
		else
		{
			sprintf(buffer, "%3s  -:--", wp->free_text);
		}

		set_2d_mono_font_position (x_pos + 0.01, y_pos - 0.1);
		set_mono_font_rel_position (1.0, 0.0);
		print_mono_font_string (buffer);
	}
}

static void get_display_latitude_longitude(vec3d* position, float* lat_deg, float* lat_min, float* lat_sec, char* north_south, float* long_deg, float* long_min, float* long_sec, char* east_west)
{
	double
		latitude = 0.0,	longitude = 0.0;

	get_latitude_longitude(position, &latitude, &longitude);

	*north_south = (latitude > 0.0) ? 'N' : 'S';
	latitude = fabs(deg(latitude));
	*lat_deg = floor(latitude);
	*lat_min = fmod(latitude * 60.0, 60.0);
	*lat_sec = fmod(latitude * 3600.0, 60.0);

	*east_west = (longitude > 0.0) ? 'E' : 'W';
	longitude = fabs(deg(longitude));
	*long_deg = floor(longitude);
	*long_min = fmod(longitude * 60.0, 60.0);
	*long_sec = fmod(longitude * 3600.0, 60.0);
}

static void display_present_position_status_window(void)
{
	vec3d
		*gunship_position = get_local_entity_vec3d_ptr (get_gunship_entity (), VEC3D_TYPE_POSITION);

	float
		start_x = -0.5,
		start_y = 0.95,
		lat_deg, lat_min, lat_sec,
		long_deg, long_min, long_sec;

	char
		north_south,
		east_west,
		buffer[64];

	draw_2d_box(start_x, start_y, start_x + 1.32, start_y - 0.18, TRUE, FALSE, clear_mfd_colour);
	draw_2d_box(start_x, start_y, start_x + 1.32, start_y - 0.18, FALSE, TRUE, MFD_COLOUR1);

	get_display_latitude_longitude(
			gunship_position,
			&lat_deg,  &lat_min,  &lat_sec,  &north_south,
			&long_deg, &long_min, &long_sec, &east_west);

	set_mono_font_type (MONO_FONT_TYPE_12X20);

	sprintf(buffer, "%07.3f %07.3f  %4.0f",
			gunship_position->x * 0.00025,
			gunship_position->z * 0.00025,
			min(feet(gunship_position->y - current_flight_dynamics->radar_altitude.value), 9999.0));

	set_2d_mono_font_position (start_x + 0.02, start_y - 0.05);
	set_mono_font_rel_position (1.0, -8.0);
	print_mono_font_string (buffer);

	sprintf(buffer, "%2.0f'%02.0f\"%02.0f%c %3.0f'%02.0f\"%02.0f%c",
			lat_deg, lat_min, lat_sec,
			north_south,
			long_deg, long_min, long_sec,
			east_west);

	set_2d_mono_font_position (start_x + 0.02, start_y - 0.13);
	set_mono_font_rel_position (1.0, -8.0);
	print_mono_font_string (buffer);
}

static void display_coordinate_review_status_window(apache_coordinate_points* coord)
{
	float
		time_of_day = get_local_entity_float_value (get_session_entity (), FLOAT_TYPE_TIME_OF_DAY),
		waypoint_range = 0.0,
		bearing = 0.0,
		elevation,
		lat_deg = 0.0, lat_min = 0.0, lat_sec = 0.0,
		long_deg = 0.0, long_min = 0.0, long_sec = 0.0,
		grid_x = 0.0,
		grid_z = 0.0,
		eta_h = 23.0, eta_m = 59.0, eta_s = 59.0,
		ete_m = 99.0, ete_s = 59.0,
		start_x = -0.93,
		start_y = -0.6;

	char
		north_south = 'N',
		east_west = 'S',
		buffer[64];

	vec3d
		*gunship_position = get_local_entity_vec3d_ptr (get_gunship_entity (), VEC3D_TYPE_POSITION);

	draw_2d_box(start_x, start_y, start_x + 1.86, start_y - 0.26, TRUE, FALSE, clear_mfd_colour);
	draw_2d_box(start_x, start_y, start_x + 1.86, start_y - 0.26, FALSE, TRUE, MFD_COLOUR1);

	if (coord->valid)
	{
		waypoint_range = get_2d_range(gunship_position, &coord->position);
		bearing = atan2(coord->position.x - gunship_position->x, coord->position.z - gunship_position->z);
		if (bearing < 0.0)
			bearing += rad(360.0);
		elevation = coord->position.y;

		get_display_latitude_longitude(
				&coord->position,
				&lat_deg,  &lat_min,  &lat_sec,  &north_south,
				&long_deg, &long_min, &long_sec, &east_west);

		grid_x = coord->position.x * 0.00025;
		grid_z = coord->position.z * 0.00025;
	}
	else
		elevation = gunship_position->y - current_flight_dynamics->radar_altitude.value;

	if ((current_flight_dynamics->velocity_z.value > 0.1) && (!apache_damage.navigation_computer))
	{
		float time_to_go = waypoint_range / current_flight_dynamics->velocity_z.value;
		get_digital_clock_values (time_of_day + time_to_go, &eta_h, &eta_m, &eta_s);
		while (eta_h > 24.0)
			eta_h -= 24.0;

		time_to_go = min(time_to_go, 99.9 * 60);

		ete_m = time_to_go / 60.0;
		ete_s = fmod(time_to_go * 60, 60);
	}

	set_mono_font_type (MONO_FONT_TYPE_12X20);
	// Line 1: ID, number, type, free text, ETE, ETA
	sprintf(buffer, "%c%02d %-3s ETE %2.0f:%02.0f ETA %2.0f:%02.0f:%02.0f",
		coord->type,
		coord->number,
		coord->free_text,
		ete_m, ete_s,
		eta_h, eta_m, eta_s
		);

	set_2d_mono_font_position (start_x + 0.02, start_y - 0.05);
	set_mono_font_rel_position (1.0, -8.0);
	print_mono_font_string (buffer);

	// Line 2: map grid (in real life: sphearoid, datum, utm), bearing, distance (km)
	sprintf(buffer, "  %07.3f %07.3f    %03.0f %5.1f",
			grid_x,
			grid_z,
			deg(bearing),
			min(waypoint_range * 0.001, 999.9));

	set_2d_mono_font_position (start_x + 0.02, start_y - 0.13);
	set_mono_font_rel_position (1.0, -8.0);
	print_mono_font_string (buffer);

	// Line 3: latitude, longitude, altitude, distance (nm)
	sprintf(buffer, "%2.0f'%02.0f\"%02.0f%c%3.0f'%02.0f\"%02.0f%c %4.0f %5.1f",
			lat_deg, lat_min, lat_sec,
			north_south,
			long_deg, long_min, long_sec,
			east_west,
			min(feet(elevation), 9999.0),
			min(nautical_miles(waypoint_range), 999.9));

	set_2d_mono_font_position (start_x + 0.02, start_y - 0.21);
	set_mono_font_rel_position (1.0, -8.0);
	print_mono_font_string (buffer);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_flight_display_mfd (void)
{
	set_mono_font_colour (MFD_COLOUR1);

	draw_pitch_ladder ();

	draw_sideslip();

	draw_heading_scale(FALSE, 0.9375);

	display_true_airspeed ();

	display_altitude ();

	draw_rate_of_climb_scale ();

	display_engine_torque ();

	if (!apache_damage.navigation_computer)
		display_waypoint_information (MFD_COLOUR4, -1.1, -0.75);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_menu_page(void)
{
	char* s;

	set_mono_font_type (MONO_FONT_TYPE_12X20);
	set_mono_font_colour(MFD_COLOUR1);

	// mission
	draw_2d_half_thick_line(-1.2, 0.30, -0.9, 0.30, MFD_COLOUR1);
	draw_2d_half_thick_line(-1.2, -0.90, -0.9, -0.90, MFD_COLOUR1);

	print_vertical_mono_font_string(-0.9, -0.30, "MISSION", -0.5, TRUE);

	draw_2d_half_thick_line(-0.9, 0.30, -0.9, 0.02, MFD_COLOUR1);
	draw_2d_half_thick_line(-0.9, -0.90, -0.9, -0.62, MFD_COLOUR1);

	// communication box
	draw_2d_half_thick_line(1.2, 0.90, 0.85, 0.90, MFD_COLOUR1);
	draw_2d_half_thick_line(1.2, -0.90, 0.85, -0.90, MFD_COLOUR1);

	print_vertical_mono_font_string(0.85, 0.0, "COMMUNICATION", -0.5, TRUE);

	draw_2d_half_thick_line(0.85, 0.90, 0.85, 0.59, MFD_COLOUR1);
	draw_2d_half_thick_line(0.85, -0.90, 0.85, -0.59, MFD_COLOUR1);

	// aircraft box
	draw_2d_half_thick_line(-0.60, -1.20, -0.60, -1.00, MFD_COLOUR1);
	draw_2d_half_thick_line( 0.90, -1.20,  0.90, -1.00, MFD_COLOUR1);

	s = "AIRCRAFT";
	set_2d_mono_font_position(0.15, -1.00);
	set_mono_font_rel_position(-0.5 * get_mono_font_string_width(s), -8.0);
	print_mono_font_string(s);

	draw_2d_half_thick_line(-0.60, -1.00, -0.1, -1.00, MFD_COLOUR1);
	draw_2d_half_thick_line( 0.90, -1.00,  0.4, -1.00, MFD_COLOUR1);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_alnum_weapons(void)
{
	int pylon;
	char weapons_status[8][4];  // all missile positions.  two rows of eight missiles, two chars per missile
	int selected_weapon = get_local_entity_int_value(get_gunship_entity(), INT_TYPE_SELECTED_WEAPON);
	int i,j;
	float x, y;
	int string_width = get_mono_font_string_width("1234567");

	memset(weapons_status, ' ', sizeof(weapons_status));

	for (pylon = APACHE_LHS_INNER_PYLON; pylon <= APACHE_RHS_OUTER_PYLON; pylon++)
	{
		entity_sub_types weapon_sub_type;
		int number, damaged;
		int pylon_index = 0;

		if (get_local_entity_weapon_hardpoint_info (get_gunship_entity (),
			pylon, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON,
			&weapon_sub_type, &number, &damaged))
		{
			switch (pylon)
			{
			case APACHE_LHS_OUTER_PYLON:
				pylon_index = 0;
				break;
			case APACHE_LHS_INNER_PYLON:
				pylon_index = 2;
				break;
			case APACHE_RHS_INNER_PYLON:
				pylon_index = 4;
				break;
			case APACHE_RHS_OUTER_PYLON:
				pylon_index = 6;
				break;
			}

			if ((weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_AGM114L_LONGBOW_HELLFIRE) || (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_AGM114K_HELLFIRE_II))
			{
				// outer missiles are fired first, so need to know which side the pylon is on
				int right_side = pylon == APACHE_RHS_INNER_PYLON || pylon == APACHE_RHS_OUTER_PYLON;

				if (damaged || selected_weapon == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
				{
					char* status = damaged ? "FAIL" : "SAFE";
					for (i=0; i<4; i++)
					{
						weapons_status[pylon_index    ][i] = status[i];
						weapons_status[pylon_index + 1][i] = status[i];
					}
				}
				else
				{
					// From AH-64A flight manual.  First letter is type (L for Laser, R for Radar), second is status (T for Tracking, R for Ready)
					char type = (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_AGM114L_LONGBOW_HELLFIRE) ? 'R' : 'L';
					char status = ((type == 'L') && weapon_sub_type == selected_weapon && (weapon_lock_type == WEAPON_LOCK_VALID)) ? 'T' : 'R';

					switch (number)
					{
					case 4:
						weapons_status[pylon_index + right_side][0] = type;
						weapons_status[pylon_index + right_side][1] = status;
					case 3:
						weapons_status[pylon_index + !right_side][0] = type;
						weapons_status[pylon_index + !right_side][1] = status;
					case 2:
						weapons_status[pylon_index + right_side][2] = type;
						weapons_status[pylon_index + right_side][3] = status;
					case 1:
						weapons_status[pylon_index + !right_side][2] = type;
						weapons_status[pylon_index + !right_side][3] = status;
					}
				}
			}
		}
	}

	// print the missiles statuses
	y = 0.8;
	for (j = 0; j < 4; j++)
	{
		float line_height = 0.45;
		char buffer[20];

		// left side missiles
		x = -0.85;
		sprintf(buffer, "%c %c %c %c", weapons_status[0][j], weapons_status[1][j], weapons_status[2][j], weapons_status[3][j]);
		set_2d_mono_font_position(x, y);
		set_mono_font_rel_position(-string_width / 2, 0);
		print_mono_font_string(buffer);

		// right side missiles
		x = -x;
		sprintf(buffer, "%c %c %c %c", weapons_status[4][j], weapons_status[5][j], weapons_status[6][j], weapons_status[7][j]);
		set_2d_mono_font_position(x, y);
		set_mono_font_rel_position(-string_width / 2, 0);
		print_mono_font_string(buffer);

		y -= line_height;
	}
}

static const char* get_sight_status(void)
{
	// sight status
	switch (eo_sensor)
	{
	case TARGET_ACQUISITION_SYSTEM_FLIR:
		if (apache_damage.flir)
			return "FLIR FAIL";
		break;
	case TARGET_ACQUISITION_SYSTEM_DTV:
		if (apache_damage.dtv)
			return "TV FAIL";
		break;
	case TARGET_ACQUISITION_SYSTEM_DVO:
		if (apache_damage.dvo)
			return "DVO FAIL";
		break;
	}

	if (target_acquisition_system == TARGET_ACQUISITION_SYSTEM_FLIR
		|| target_acquisition_system == TARGET_ACQUISITION_SYSTEM_DTV
		|| target_acquisition_system == TARGET_ACQUISITION_SYSTEM_DVO)
	{
		if (eo_is_locked())
			return "RECORDING";
		else
			return "BORESIGHT";
	}
	else
		return "SLAVE TG";
}

#if 0
static const char* get_weapon_status(char* buffer, unsigned buffer_len)
{
	int selected_weapon = get_local_entity_int_value(get_gunship_entity(), INT_TYPE_SELECTED_WEAPON);

	switch (selected_weapon)
	{
	case ENTITY_SUB_TYPE_WEAPON_M230_30MM_ROUND:
		{
			int number = get_local_entity_weapon_count (get_gunship_entity (), selected_weapon);
			if (apache_damage.gun_jammed)
				return "GUN FAIL";

			snprintf(buffer, buffer_len, "RNDS%4d", number);
			return buffer;
		}
		break;
	case ENTITY_SUB_TYPE_WEAPON_HYDRA70_M261:
	case ENTITY_SUB_TYPE_WEAPON_HYDRA70_M255:
		return "ROCKETS";
		break;
	case ENTITY_SUB_TYPE_WEAPON_AGM114L_LONGBOW_HELLFIRE:
	case ENTITY_SUB_TYPE_WEAPON_AGM114K_HELLFIRE_II:
		{
			float flight_time;

			flight_time = get_missile_flight_time();
			if (flight_time <= 0.0)  // no missiles in flight
				return "MSL";

			snprintf(buffer, buffer_len, "TOF=%d", (int)(flight_time + 0.5));
			return buffer;
		}
		break;
	case ENTITY_SUB_TYPE_WEAPON_AIM92_STINGER:
		return "ATA";
		break;
	}

	return "";
}
#endif
static const char* get_tracker_status(void)
{
	if (target_acquisition_system == TARGET_ACQUISITION_SYSTEM_FLIR
		|| target_acquisition_system == TARGET_ACQUISITION_SYSTEM_DTV
		|| target_acquisition_system == TARGET_ACQUISITION_SYSTEM_DVO)
	{
		if (laser_is_active())
			return "LASE...TARGET";
		if (eo_is_tracking_point())
			return "IAT OFFSET";
		if (eo_is_locked())
			return "IAT TRACKING";
	}

	return "TADS FORWARD";

	// TODO add Laser spot tracking if we implement tracking other units' lasers
}

static const char* get_lst_and_lrf_codes_status(void)
{
#if 0  // enable this if we add laser spot tracker
	if (laser_spot_tracker_is_active())
		return "LST=C RFD=D";
	else
#endif

	if (!apache_damage.laser_designator)
		return "RFD=D";
	else
		return "";
}

static void draw_apache_ort_symbology(int dummy)
{
	// TODO: check for damage
	switch (eo_sensor)
	{
	case TARGET_ACQUISITION_SYSTEM_FLIR:
		draw_2d_flir_mfd(TRUE, TRUE, TRUE);
		break;
	case TARGET_ACQUISITION_SYSTEM_DTV:
		draw_2d_dtv_mfd(TRUE, TRUE, TRUE);
		break;
	case TARGET_ACQUISITION_SYSTEM_DVO:
		{
			// DVO doesn't have symbology over image, just a simple cross
			draw_2d_line (-1.00, 0.0, -0.10, 0.0, sys_col_white);
			draw_2d_line (0.10, 0.0, 1.00, 0.0, sys_col_white);
			draw_2d_line (0.0, -1.00, 0.0, -0.10, sys_col_white);
			draw_2d_line (0.0, 0.10, 0.0, 1.00, sys_col_white);
		}

		break;
	}
}

static void draw_apache_tads_alnum_display(int dummy)
{
	draw_2d_line(-1.1, 1.1, 1.1, 1.1, sys_col_white);
	draw_2d_line(-1.1, -1.1, -1.1, 1.1, sys_col_white);
	draw_2d_line(-1.1, -1.1, -1.1, 1.1, sys_col_white);
	draw_2d_line(1.1, -1.1, 1.1, 1.1, sys_col_white);

	draw_2d_line(-0.6, -1.1, -0.6, 1.1, sys_col_white);
	draw_2d_line(0.6, -1.1, 0.6, 1.1, sys_col_white);

	set_mono_font_colour(sys_col_white);
	set_mono_font_type(MONO_FONT_TYPE_5X9);

	// weapons
	draw_alnum_weapons();

	// text status displays
	{
		char buffer[80];
		const char *s = NULL;
		float x = -0.55;
		float y = 0.8;
		float line_height = 0.45;

		s = get_sight_status();
		set_2d_mono_font_position(x, y);
		set_mono_font_rel_position(0, 0);
		print_mono_font_string(s);

#if 0  // TODO
		// weapon status
		s = get_weapon_status(buffer, sizeof(buffer));
		set_2d_mono_font_position(0.0, y);
		print_mono_font_string(s);
#endif
		y -= line_height;

		// tracker status
		s = get_tracker_status();
		set_2d_mono_font_position(x, y);
		print_mono_font_string(s);

		y -= line_height;

		// get spot tracker and range finder codes
		s = get_lst_and_lrf_codes_status();
		set_2d_mono_font_position(x, y);
		print_mono_font_string(s);
	}
}

void draw_apache_virtual_cockpit_ort_symbology(void)
{
	int
		mfd_screen_x_min, mfd_screen_y_min, mfd_screen_x_max, mfd_screen_y_max;

	rgb_colour
		background_colour,
		symbology_colour;

	set_3d_active_environment (main_3d_env);

	//
	// set up MFD 2D environment
	//

	set_2d_active_environment (mfd_env);
	set_2d_window (mfd_env, MFD_WINDOW_X_MIN, MFD_WINDOW_Y_MIN, MFD_WINDOW_X_MAX, MFD_WINDOW_Y_MAX);

	mfd_viewport_size = MFD_VIEWPORT_SIZE;

	mfd_viewport_x_org = MFD_VIEWPORT_SIZE * 0.5;
	mfd_viewport_y_org = MFD_VIEWPORT_SIZE * 0.5;

	mfd_viewport_x_min = 0.0;
	mfd_viewport_y_min = 0.0;

	mfd_viewport_x_max = MFD_VIEWPORT_SIZE - 0.001;
	mfd_viewport_y_max = MFD_VIEWPORT_SIZE - 0.001;

	set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

	mfd_screen_x_min = full_screen_x_mid - ((256.0 / (640.0 * 2.0)) * full_screen_width);
	mfd_screen_y_min = full_screen_y_mid - ((256.0 / (480.0 * 2.0)) * full_screen_height);

	mfd_screen_x_max = full_screen_x_mid + ((256.0 / (640.0 * 2.0)) * full_screen_width) - 0.001;
	mfd_screen_y_max = full_screen_y_mid + ((256.0 / (480.0 * 2.0)) * full_screen_height) - 0.001;

	i_translate_3d = mfd_screen_x_min;
	j_translate_3d = mfd_screen_y_min;

	i_scale_3d = 640.0 / full_screen_width;
	j_scale_3d = 480.0 / full_screen_height;

	if (eo_sensor == TARGET_ACQUISITION_SYSTEM_DVO)
	{
		set_rgb_colour(symbology_colour, 160, 160, 160, 192);
	}
	else
	{
		set_rgb_colour(symbology_colour, 96, 192, 96, 255);
	}
	set_rgb_colour(background_colour, 255, 255, 255, 0);

	set_system_texture_screen (rhs_mfd_texture_screen, TEXTURE_INDEX_AVCKPT_DISPLAY_RHS_MFD);

	draw_symbology_to_texture(
		rhs_mfd_texture_screen,
		TEXTURE_INDEX_AVCKPT_DISPLAY_RHS_MFD,
		mfd_viewport_size,
		mfd_viewport_size,
		mfd_screen_x_min,
		mfd_screen_y_min,
		mfd_screen_x_max,
		mfd_screen_y_max,
		symbology_colour,
		background_colour,
		draw_apache_ort_symbology);


	// Draw alphanumerical display part of ORT view	set_2d_window (mfd_env, MFD_WINDOW_X_MIN, MFD_WINDOW_Y_MIN, MFD_WINDOW_X_MAX, MFD_WINDOW_Y_MAX);

	mfd_viewport_x_org = ALNUM_DISPLAY_WIDTH * 0.5;
	mfd_viewport_y_org = ALNUM_DISPLAY_HEIGHT * 0.5;

	mfd_viewport_x_min = 0.0;
	mfd_viewport_y_min = 0.0;

	mfd_viewport_x_max = ALNUM_DISPLAY_WIDTH - 0.001;
	mfd_viewport_y_max = ALNUM_DISPLAY_HEIGHT - 0.001;

	set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

	mfd_screen_x_min = full_screen_x_mid - ((256.0 / (640.0 * 2.0)) * full_screen_width);
	mfd_screen_y_min = full_screen_y_max - ((128.0 / (480.0 * 2.0)) * full_screen_height);

	mfd_screen_x_max = full_screen_x_mid + ((256.0 / (640.0 * 2.0)) * full_screen_width) - 0.001;
	mfd_screen_y_max = full_screen_y_max - 0.001;

	set_rgb_colour(symbology_colour, 220, 64, 64, 255);
	set_rgb_colour(background_colour, 0, 0, 0, 255);

	draw_symbology_to_texture(
		alnum_display_screen,
		TEXTURE_INDEX_AVCKPT_ALNUM_DISPLAY,
		ALNUM_DISPLAY_WIDTH,
		ALNUM_DISPLAY_HEIGHT,
		mfd_screen_x_min,
		mfd_screen_y_min,
		mfd_screen_x_max,
		mfd_screen_y_max,
		symbology_colour,
		background_colour,
		draw_apache_tads_alnum_display);
}

mfd_modes get_apache_current_mfd_mode(mfd_locations location)
{
	switch (location)
	{
	case MFD_LOCATION_PILOT_LHS:
		return lhs_mfd_mode;
	case MFD_LOCATION_PILOT_RHS:
		return rhs_mfd_mode;
	case MFD_LOCATION_CPG_LHS:
		return cpg_lhs_mfd_mode;
	case MFD_LOCATION_CPG_RHS:
		return cpg_rhs_mfd_mode;
	case MFD_LOCATION_ORT:
	{
		ASSERT(location == MFD_LOCATION_ORT);

		if (ort_mode != MFD_MODE_DAMAGED && ort_mode != MFD_MODE_OFF && !current_apache_eo_sensor_damaged())
			return get_mfd_mode_for_eo_sensor();
		return ort_mode;
	}
	default:
		ASSERT(FALSE);
		break;
	}

	return MFD_MODE_OFF;
}

void set_apache_mfd_sub_mode(mfd_locations location, int sub_mode)
{
	ASSERT(location < MFD_LOCATION_ORT);
	mfd_has_more_sub_pages[location] = FALSE;
	mfd_sub_page[location] = 1;
	mfd_sub_mode[location] = sub_mode;
}

int get_apache_mfd_sub_mode(mfd_locations location)
{
	ASSERT(location < MFD_LOCATION_ORT);
	return mfd_sub_mode[location];
}

void set_apache_mfd_sub_page(mfd_locations location, int page)
{
	ASSERT(location < MFD_LOCATION_ORT);
	mfd_has_more_sub_pages[location] = FALSE;
	mfd_sub_page[location] = page;
}

int get_apache_mfd_sub_page(mfd_locations location)
{
	ASSERT(location < MFD_LOCATION_ORT);
	return mfd_sub_page[location];
}

int apache_mfd_has_more_sub_pages(mfd_locations location)
{
	ASSERT(location < MFD_LOCATION_ORT);
	return mfd_has_more_sub_pages[location];
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// DRAW MFD ON TEXTURE
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_apache_mfd_on_texture (mfd_locations location)
{
	mfd_modes
		*mfd_mode;

	int
		sub_mode,
		sub_page;

	screen
		*mfd_texture_screen,
		*export_screen;

	int
		is_pilot = (get_local_entity_int_value (get_pilot_entity (), INT_TYPE_CREW_ROLE) == CREW_ROLE_PILOT);

	ASSERT ((location == MFD_LOCATION_PILOT_LHS) || (location == MFD_LOCATION_PILOT_RHS)
			|| (location == MFD_LOCATION_CPG_LHS) || (location == MFD_LOCATION_CPG_RHS)
			|| (location == MFD_LOCATION_ORT));

	update_pointer_position();

	if (location == MFD_LOCATION_PILOT_LHS)
	{
		mfd_mode = &lhs_mfd_mode;
		sub_mode = mfd_sub_mode[MFD_LOCATION_PILOT_LHS];
		sub_page = mfd_sub_page[MFD_LOCATION_PILOT_LHS];
		mfd_texture_screen = lhs_mfd_texture_screen;
		set_system_texture_screen (mfd_texture_screen, TEXTURE_INDEX_AVCKPT_DISPLAY_LHS_MFD);
	}
	else if (location == MFD_LOCATION_PILOT_RHS)
	{
		mfd_mode = &rhs_mfd_mode;
		sub_mode = mfd_sub_mode[MFD_LOCATION_PILOT_RHS];
		sub_page = mfd_sub_page[MFD_LOCATION_PILOT_RHS];
		mfd_texture_screen = rhs_mfd_texture_screen;
		set_system_texture_screen (mfd_texture_screen, TEXTURE_INDEX_AVCKPT_DISPLAY_RHS_MFD);
	}
	else if (location == MFD_LOCATION_CPG_LHS)
	{
		mfd_mode = &cpg_lhs_mfd_mode;
		sub_mode = mfd_sub_mode[MFD_LOCATION_CPG_LHS];
		sub_page = mfd_sub_page[MFD_LOCATION_CPG_LHS];
		mfd_texture_screen = cpg_lhs_mfd_texture_screen;
		set_system_texture_screen (mfd_texture_screen, TEXTURE_INDEX_AVCKPT_DISPLAY_CPG_LHS_MFD);
	}
	else if (location == MFD_LOCATION_CPG_RHS)
	{
		mfd_mode = &cpg_rhs_mfd_mode;
		sub_mode = mfd_sub_mode[MFD_LOCATION_CPG_RHS];
		sub_page = mfd_sub_page[MFD_LOCATION_CPG_RHS];
		mfd_texture_screen = cpg_rhs_mfd_texture_screen;
		set_system_texture_screen (mfd_texture_screen, TEXTURE_INDEX_AVCKPT_DISPLAY_CPG_RHS_MFD);
	}
	else
	{
		int use_3d_texture = ort_mode != MFD_MODE_DAMAGED && ort_mode != MFD_MODE_OFF && !current_apache_eo_sensor_damaged();
		ASSERT(location == MFD_LOCATION_ORT);

		if (use_3d_texture)
		{
			ort_mode = get_mfd_mode_for_eo_sensor();
			mfd_texture_screen = eo_3d_texture_screen;
		}
		else
			mfd_texture_screen = ort_texture_screen;
		mfd_mode = &ort_mode;
		sub_mode = 0;
		sub_page = 0;

		set_system_texture_screen (mfd_texture_screen, TEXTURE_INDEX_AVCKPT_DISPLAY_ORT);

		if (use_3d_texture)
			if (cpg_lhs_mfd_mode == ort_mode || cpg_rhs_mfd_mode == ort_mode)
			{
				// use same texture as MFD if it also shows TADS
				return;
			}
	}

	if (is_pilot
		&& pilot_tsd_underlay == TSD_UNDERLAY_TADS
		&& (d3d_can_render_to_texture)
		&& !current_apache_eo_sensor_damaged())
	{
		switch (lhs_mfd_mode)
		{
		case MFD_MODE_TSD:
		case MFD_MODE_TSD_WPT:
		case MFD_MODE_TSD_UTIL:
		case MFD_MODE_TSD_RTE:
		case MFD_MODE_TSD_THRT:
		case MFD_MODE_TSD_COORD:
		case MFD_MODE_TSD_SHOW:
		case MFD_MODE_TSD_ZONE:
			tsd_tads_underlay_active = TRUE;
			break;
		}

		switch (rhs_mfd_mode)
		{
		case MFD_MODE_TSD:
		case MFD_MODE_TSD_WPT:
		case MFD_MODE_TSD_UTIL:
		case MFD_MODE_TSD_RTE:
		case MFD_MODE_TSD_THRT:
		case MFD_MODE_TSD_COORD:
		case MFD_MODE_TSD_SHOW:
		case MFD_MODE_TSD_ZONE:
			tsd_tads_underlay_active = TRUE;
			break;
		}
	}
	else
		tsd_tads_underlay_active = FALSE;

	////////////////////////////////////////
	//
	// set up MFD 2D environment
	//
	////////////////////////////////////////

	set_2d_active_environment (mfd_env);

	//
	// window
	//

	set_2d_window (mfd_env, MFD_WINDOW_X_MIN, MFD_WINDOW_Y_MIN, MFD_WINDOW_X_MAX, MFD_WINDOW_Y_MAX);

	//
	// viewport
	//

	ASSERT (mfd_viewport_size <= mfd_texture_size);

	mfd_viewport_x_org = mfd_viewport_texture_x_org;

	mfd_viewport_y_org = mfd_viewport_texture_y_org;

	mfd_viewport_x_min = mfd_viewport_x_org - (mfd_viewport_size * 0.5);

	mfd_viewport_y_min = mfd_viewport_y_org - (mfd_viewport_size * 0.5);

	mfd_viewport_x_max = mfd_viewport_x_org + (mfd_viewport_size * 0.5) - 0.001;

	mfd_viewport_y_max = mfd_viewport_y_org + (mfd_viewport_size * 0.5) - 0.001;

	set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

	if (*mfd_mode == MFD_MODE_AIR_RADAR && target_acquisition_system == TARGET_ACQUISITION_SYSTEM_GROUND_RADAR)
		*mfd_mode = MFD_MODE_GROUND_RADAR;
	else if (*mfd_mode == MFD_MODE_GROUND_RADAR && target_acquisition_system == TARGET_ACQUISITION_SYSTEM_AIR_RADAR)
		*mfd_mode = MFD_MODE_AIR_RADAR;

	////////////////////////////////////////
	//
	// draw MFD display
	//
	////////////////////////////////////////

	switch (*mfd_mode)
	{
		////////////////////////////////////////
		case MFD_MODE_OFF:
		////////////////////////////////////////
		{
			set_active_screen (mfd_texture_screen);

			if (lock_screen (mfd_texture_screen))
			{
				int width;
				if (location == MFD_LOCATION_ORT)
					width = mfd_texture_size * 2 - 1;
				else
					width = mfd_texture_size - 1;

				set_block (0, 0, width, mfd_texture_size - 1, off_mfd_colour);

				draw_layout_grid ();

				flush_screen_texture_graphics (mfd_texture_screen);

				unlock_screen (mfd_texture_screen);
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_DAMAGED:
		////////////////////////////////////////
		{
			set_active_screen (mfd_texture_screen);

			if (lock_screen (mfd_texture_screen))
			{
				set_block (0, 0, mfd_texture_size - 1, mfd_texture_size - 1, clear_mfd_colour);

				draw_layout_grid ();

				draw_damaged_mfd ();

				flush_screen_texture_graphics (mfd_texture_screen);

				unlock_screen (mfd_texture_screen);
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_GROUND_RADAR:
		////////////////////////////////////////
		{
			set_active_screen (mfd_texture_screen);

			if (lock_screen (mfd_texture_screen))
			{
				set_block (0, 0, mfd_texture_size - 1, mfd_texture_size - 1, clear_mfd_colour);

				draw_layout_grid ();

				draw_ground_radar_mfd (sub_mode);

				render_apache_mfd_buttons(*mfd_mode, location, MFD_COLOUR1, MFD_COLOUR5, clear_mfd_colour, TRUE);

				flush_screen_texture_graphics (mfd_texture_screen);

				unlock_screen (mfd_texture_screen);
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_AIR_RADAR:
		////////////////////////////////////////
		{
			set_active_screen (mfd_texture_screen);

			if (lock_screen (mfd_texture_screen))
			{
				set_block (0, 0, mfd_texture_size - 1, mfd_texture_size - 1, clear_mfd_colour);

				draw_layout_grid ();

				draw_air_radar_mfd ();

				render_apache_mfd_buttons(*mfd_mode, location, MFD_COLOUR1, MFD_COLOUR5, clear_mfd_colour, TRUE);

				flush_screen_texture_graphics (mfd_texture_screen);

				unlock_screen (mfd_texture_screen);
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_FLIR:
		case MFD_MODE_DTV:
		case MFD_MODE_DVO:
		////////////////////////////////////////
		{
			int damaged;

			switch (eo_sensor)
			{
			case TARGET_ACQUISITION_SYSTEM_FLIR:
				*mfd_mode = MFD_MODE_FLIR;
				damaged = apache_damage.flir;
				break;
			case TARGET_ACQUISITION_SYSTEM_DTV:
				*mfd_mode = MFD_MODE_DTV;
				damaged = apache_damage.dtv;
				break;
			case TARGET_ACQUISITION_SYSTEM_DVO:
				ASSERT(location == MFD_LOCATION_ORT);  // only ORT can view DVO
				*mfd_mode = MFD_MODE_DVO;
				damaged = apache_damage.dvo;
				break;
			}

			if ((d3d_can_render_to_texture) && !damaged)
			{
				ASSERT (eo_3d_texture_screen);

				if (location == MFD_LOCATION_PILOT_LHS)
					set_system_texture_screen (eo_3d_texture_screen, TEXTURE_INDEX_AVCKPT_DISPLAY_LHS_MFD);
				else if (location == MFD_LOCATION_PILOT_RHS)
					set_system_texture_screen (eo_3d_texture_screen, TEXTURE_INDEX_AVCKPT_DISPLAY_RHS_MFD);
				else if (location == MFD_LOCATION_CPG_LHS)
					set_system_texture_screen (eo_3d_texture_screen, TEXTURE_INDEX_AVCKPT_DISPLAY_CPG_LHS_MFD);
				else if (location == MFD_LOCATION_CPG_RHS)
					set_system_texture_screen (eo_3d_texture_screen, TEXTURE_INDEX_AVCKPT_DISPLAY_CPG_RHS_MFD);
				else if (location == MFD_LOCATION_ORT)
					set_system_texture_screen (eo_3d_texture_screen, TEXTURE_INDEX_AVCKPT_DISPLAY_ORT);

				if (*mfd_mode == MFD_MODE_FLIR)
					draw_3d_eo_display_on_texture (&apache_flir, TARGET_ACQUISITION_SYSTEM_FLIR);
				else if (*mfd_mode == MFD_MODE_DTV)
					draw_3d_eo_display_on_texture (&apache_dtv, TARGET_ACQUISITION_SYSTEM_DTV);
				else
					draw_3d_eo_display_on_texture (&apache_dvo, TARGET_ACQUISITION_SYSTEM_DVO);

				set_active_screen (eo_3d_texture_screen);

				if (lock_screen (eo_3d_texture_screen))
				{
					int is_ort = location == MFD_LOCATION_ORT;

					draw_layout_grid ();

					if (*mfd_mode == MFD_MODE_FLIR)
						draw_2d_flir_mfd (TRUE, FALSE, is_ort);
					else if (*mfd_mode == MFD_MODE_DTV)
						draw_2d_dtv_mfd (TRUE, FALSE, is_ort);
					else
						draw_2d_dvo_mfd (TRUE, FALSE, is_ort);

					if (!is_ort)
						render_apache_mfd_buttons(*mfd_mode, location, MFD_COLOUR1, MFD_COLOUR5, clear_mfd_colour, FALSE);

					flush_screen_texture_graphics (eo_3d_texture_screen);
					unlock_screen (eo_3d_texture_screen);
				}

				set_pilots_full_screen_params (FALSE);
			}
			else
			{
				set_active_screen (mfd_texture_screen);

				if (lock_screen (mfd_texture_screen))
				{
					int width;
					if (location == MFD_LOCATION_ORT)
						width = mfd_texture_size * 2 - 1;
					else
						width = mfd_texture_size - 1;

					set_block (0, 0, width, mfd_texture_size - 1, clear_mfd_colour);

					draw_layout_grid ();

					if (*mfd_mode == MFD_MODE_FLIR)
						draw_2d_flir_mfd (FALSE, FALSE, FALSE);
					else if (*mfd_mode == MFD_MODE_DTV)
						draw_2d_dtv_mfd (FALSE, FALSE, FALSE);
					else
						draw_2d_dvo_mfd (FALSE, FALSE, FALSE);

					render_apache_mfd_buttons(*mfd_mode, location, MFD_COLOUR1, MFD_COLOUR5, clear_mfd_colour, FALSE);

					flush_screen_texture_graphics (mfd_texture_screen);

					unlock_screen (mfd_texture_screen);
				}
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_TSD:
		case MFD_MODE_TSD_WPT:
		case MFD_MODE_TSD_UTIL:
		case MFD_MODE_TSD_RTE:
		case MFD_MODE_TSD_THRT:
		case MFD_MODE_TSD_COORD:
		case MFD_MODE_TSD_SHOW:
		case MFD_MODE_TSD_ZONE:
		////////////////////////////////////////
		{
			int shade = (is_pilot ? pilot_tsd_underlay : cpg_tsd_underlay) != TSD_UNDERLAY_TADS;

			if (tsd_tads_underlay_active)
			{
				if (location == MFD_LOCATION_PILOT_LHS)
					set_system_texture_screen (eo_3d_texture_screen, TEXTURE_INDEX_AVCKPT_DISPLAY_LHS_MFD);
				else if (location == MFD_LOCATION_PILOT_RHS)
					set_system_texture_screen (eo_3d_texture_screen, TEXTURE_INDEX_AVCKPT_DISPLAY_RHS_MFD);
				else
					debug_fatal("Only pilot's MFDs support TADS underlay!");

				if (eo_sensor == TARGET_ACQUISITION_SYSTEM_FLIR)
					draw_3d_eo_display_on_texture (&apache_flir, TARGET_ACQUISITION_SYSTEM_FLIR);
				else
					draw_3d_eo_display_on_texture (&apache_dtv, TARGET_ACQUISITION_SYSTEM_DTV);

				mfd_texture_screen = eo_3d_texture_screen;
			}

			set_active_screen (mfd_texture_screen);

			if (lock_screen (mfd_texture_screen))
			{
				if (!tsd_tads_underlay_active)
					set_block (0, 0, mfd_texture_size - 1, mfd_texture_size - 1, clear_green_mfd_colour);

				draw_tactical_situation_display_mfd (*mfd_mode);

				render_apache_mfd_buttons(*mfd_mode, location, MFD_COLOUR1, MFD_COLOUR5, clear_mfd_colour, shade);

				flush_screen_texture_graphics (mfd_texture_screen);

				unlock_screen (mfd_texture_screen);
			}

			if (tsd_tads_underlay_active)
				set_pilots_full_screen_params (FALSE);

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_ASE:
		////////////////////////////////////////
		{
			set_active_screen (mfd_texture_screen);

			if (lock_screen (mfd_texture_screen))
			{
				set_block (0, 0, mfd_texture_size - 1, mfd_texture_size - 1, clear_green_mfd_colour);

				draw_layout_grid ();

				draw_aircraft_survivability_equipment_display_mfd ();

				flush_screen_texture_graphics (mfd_texture_screen);

				unlock_screen (mfd_texture_screen);
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_WEAPON:
		case MFD_MODE_WEAPON_GUN:
		case MFD_MODE_WEAPON_MSL:
		case MFD_MODE_WEAPON_ATA:
		case MFD_MODE_WEAPON_RKT:
		////////////////////////////////////////
		{
			set_active_screen (mfd_texture_screen);

			if (lock_screen (mfd_texture_screen))
			{
				set_block (0, 0, mfd_texture_size - 1, mfd_texture_size - 1, clear_mfd_colour);

				draw_layout_grid ();

				draw_weapon_display_mfd (location, *mfd_mode);

				render_apache_mfd_buttons(*mfd_mode, location, MFD_COLOUR1, MFD_COLOUR5, clear_mfd_colour, FALSE);

				flush_screen_texture_graphics (mfd_texture_screen);

				unlock_screen (mfd_texture_screen);
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_SYSTEM:
		////////////////////////////////////////
		{
			set_active_screen (mfd_texture_screen);

			if (lock_screen (mfd_texture_screen))
			{
				set_block (0, 0, mfd_texture_size - 1, mfd_texture_size - 1, clear_mfd_colour);

				draw_layout_grid ();

				draw_system_display_mfd ();

				flush_screen_texture_graphics (mfd_texture_screen);

				unlock_screen (mfd_texture_screen);
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_ENGINE:
		////////////////////////////////////////
		{
			set_active_screen (mfd_texture_screen);

			if (lock_screen (mfd_texture_screen))
			{
				set_block (0, 0, mfd_texture_size - 1, mfd_texture_size - 1, clear_mfd_colour);

				draw_layout_grid ();

				draw_engine_display_mfd ();

				render_apache_mfd_buttons(*mfd_mode, location, MFD_COLOUR1, MFD_COLOUR5, clear_mfd_colour, FALSE);

				flush_screen_texture_graphics (mfd_texture_screen);

				unlock_screen (mfd_texture_screen);
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_FLIGHT:
		////////////////////////////////////////
		{
			set_active_screen (mfd_texture_screen);

			if (lock_screen (mfd_texture_screen))
			{
				set_block (0, 0, mfd_texture_size - 1, mfd_texture_size - 1, clear_green_mfd_colour);

				draw_layout_grid ();

				draw_flight_display_mfd();

				render_apache_mfd_buttons(*mfd_mode, location, MFD_COLOUR1, MFD_COLOUR5, clear_mfd_colour, FALSE);

				flush_screen_texture_graphics (mfd_texture_screen);

				unlock_screen (mfd_texture_screen);
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_FUEL:
		////////////////////////////////////////
		{
			set_active_screen (mfd_texture_screen);

			if (lock_screen (mfd_texture_screen))
			{
				set_block (0, 0, mfd_texture_size - 1, mfd_texture_size - 1, clear_green_mfd_colour);

				draw_layout_grid ();

				draw_fuel_page_mfd();

				render_apache_mfd_buttons(*mfd_mode, location, MFD_COLOUR1, MFD_COLOUR5, clear_mfd_colour, FALSE);

				flush_screen_texture_graphics (mfd_texture_screen);

				unlock_screen (mfd_texture_screen);
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_MENU:
		////////////////////////////////////////
		{
			set_active_screen (mfd_texture_screen);

			if (lock_screen (mfd_texture_screen))
			{
				set_block (0, 0, mfd_texture_size - 1, mfd_texture_size - 1, clear_mfd_colour);

				draw_layout_grid ();

				draw_menu_page();

				render_apache_mfd_buttons(*mfd_mode, location, MFD_COLOUR1, MFD_COLOUR5, clear_mfd_colour, FALSE);

				flush_screen_texture_graphics (mfd_texture_screen);

				unlock_screen (mfd_texture_screen);
			}
			break;
		}
		////////////////////////////////////////
		case MFD_MODE_CHECKLIST:
		case MFD_MODE_CHECKLIST_THROUGH_FLIGHT:
		case MFD_MODE_CHECKLIST_PERF_DATA1:
		case MFD_MODE_CHECKLIST_PERF_DATA2:
		////////////////////////////////////////
		{
			set_active_screen (mfd_texture_screen);

			if (lock_screen (mfd_texture_screen))
			{
				set_block (0, 0, mfd_texture_size - 1, mfd_texture_size - 1, clear_mfd_colour);

				draw_layout_grid ();

				draw_checklist(*mfd_mode, location);

				render_apache_mfd_buttons(*mfd_mode, location, MFD_COLOUR1, MFD_COLOUR5, clear_mfd_colour, FALSE);

				flush_screen_texture_graphics (mfd_texture_screen);

				unlock_screen (mfd_texture_screen);
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_ADF:
		////////////////////////////////////////
		{
			set_active_screen (mfd_texture_screen);

			if (lock_screen (mfd_texture_screen))
			{
				set_block (0, 0, mfd_texture_size - 1, mfd_texture_size - 1, clear_mfd_colour);

				draw_layout_grid ();

				draw_adf_page(location);

				render_apache_mfd_buttons(*mfd_mode, location, MFD_COLOUR1, MFD_COLOUR5, clear_mfd_colour, FALSE);

				flush_screen_texture_graphics (mfd_texture_screen);

				unlock_screen (mfd_texture_screen);
			}

			break;
		}
	}

	set_active_screen (video_screen);
	if(command_line_export_mfd)
	{
		switch(location)
		{
		case MFD_LOCATION_PILOT_LHS:
			export_screen=create_screen_for_system_texture (TEXTURE_INDEX_AVCKPT_DISPLAY_LHS_MFD);
			copy_export_mfd(export_screen,NULL);
			break;
		case MFD_LOCATION_PILOT_RHS:
			export_screen=create_screen_for_system_texture (TEXTURE_INDEX_AVCKPT_DISPLAY_RHS_MFD);
			copy_export_mfd(NULL,export_screen);
			break;
		case MFD_LOCATION_CPG_LHS:
			export_screen=create_screen_for_system_texture (TEXTURE_INDEX_AVCKPT_DISPLAY_CPG_LHS_MFD);
			copy_export_mfd(export_screen,NULL);
			break;
		case MFD_LOCATION_CPG_RHS:
			export_screen=create_screen_for_system_texture (TEXTURE_INDEX_AVCKPT_DISPLAY_CPG_RHS_MFD);
			copy_export_mfd(NULL,export_screen);
			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// DRAW OVERLAID MFD
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_translucent_mfd_background (float x_min, float y_min, float x_max, float y_max)
{
	vertex
		quad[4];

	real_colour
		colour,
		specular;

	set_3d_active_environment (main_3d_env);

	if (begin_3d_scene ())
	{
		colour.red = 0;
		colour.green = 0;
		colour.blue = 0;
		colour.alpha = 64;

		specular.red = 0;
		specular.green = 0;
		specular.blue = 0;
		specular.alpha = 255;

		set_d3d_transparency_on ();

		set_d3d_zbuffer_comparison (FALSE);

		set_d3d_plain_renderstate ();

		set_d3d_culling (FALSE);

		quad[0].i = x_min;
		quad[0].j = y_min;
		quad[0].z = 0.5;
		quad[0].q = 0.5;
		quad[0].next_vertex = &quad[1];

		quad[1].i = x_max;
		quad[1].j = y_min;
		quad[1].z = 0.5;
		quad[1].q = 0.5;
		quad[1].next_vertex = &quad[2];

		quad[2].i = x_max;
		quad[2].j = y_max;
		quad[2].z = 0.5;
		quad[2].q = 0.5;
		quad[2].next_vertex = &quad[3];

		quad[3].i = x_min;
		quad[3].j = y_max;
		quad[3].z = 0.5;
		quad[3].q = 0.5;
		quad[3].next_vertex = NULL;

		draw_wbuffered_plain_polygon (quad, colour, specular);

		set_d3d_transparency_off ();

		set_d3d_zbuffer_comparison (TRUE);

		end_3d_scene ();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_overlaid_apache_mfd (float x_org, float y_org, float size, mfd_locations location)
{
	mfd_modes
		*mfd_mode;

	int
		sub_page,
		sub_mode;

	screen
		*mfd_texture_screen;

	texture_index_numbers
		texture_index;

	float
		mfd_screen_size,
		mfd_screen_half_size,
		mfd_screen_x_org,
		mfd_screen_y_org,
		mfd_screen_x_min,
		mfd_screen_y_min,
		mfd_screen_x_max,
		mfd_screen_y_max;

	ASSERT ((location == MFD_LOCATION_PILOT_LHS) || (location == MFD_LOCATION_PILOT_RHS)
			|| (location == MFD_LOCATION_CPG_LHS) || (location == MFD_LOCATION_CPG_RHS));

	update_pointer_position();

	if (location == MFD_LOCATION_LHS)
	{
		mfd_mode = &lhs_mfd_mode;
		sub_mode = mfd_sub_mode[MFD_LOCATION_LHS];
		sub_page = mfd_sub_page[MFD_LOCATION_LHS];

		mfd_texture_screen = lhs_overlaid_mfd_texture_screen;

		texture_index = LHS_OVERLAID_MFD_TEXTURE_INDEX;
	}
	else
	{
		mfd_mode = &rhs_mfd_mode;
		sub_mode = mfd_sub_mode[MFD_LOCATION_RHS];
		sub_page = mfd_sub_page[MFD_LOCATION_RHS];

		mfd_texture_screen = rhs_overlaid_mfd_texture_screen;

		texture_index = RHS_OVERLAID_MFD_TEXTURE_INDEX;
	}

	if (*mfd_mode == MFD_MODE_OFF)
	{
		return;
	}

	////////////////////////////////////////
	//
	// scale position and size wrt screen resolution
	//
	////////////////////////////////////////

/*	if (get_global_unscaled_displays ())
	{
		float
			org_offset;

		mfd_screen_size = size;

		mfd_screen_half_size = mfd_screen_size * 0.5;

		mfd_screen_x_org = x_org * full_screen_width * (1.0 / 640.0);
		mfd_screen_y_org = y_org * full_screen_height * (1.0 / 480.0);

		org_offset = ((size * full_screen_width * (1.0 / 640.0)) - size) * 0.5;

		if (location == MFD_LOCATION_LHS)
		{
			mfd_screen_x_org -= org_offset;
		}
		else
		{
			mfd_screen_x_org += org_offset;
		}

		mfd_screen_y_org += org_offset;

		mfd_screen_x_min = mfd_screen_x_org - mfd_screen_half_size;
		mfd_screen_y_min = mfd_screen_y_org - mfd_screen_half_size;
		mfd_screen_x_max = mfd_screen_x_org + mfd_screen_half_size - 0.001;
		mfd_screen_y_max = mfd_screen_y_org + mfd_screen_half_size - 0.001;
	}
	else*/
	{
		float
			scalex,
			scaley,
			org_offset;

		scalex = full_screen_width * (1.0 / 640.0);
		scaley = full_screen_height * (1.0 / 480.0);

		mfd_screen_size = size * global_mfd_size * scalex;
		mfd_screen_half_size = mfd_screen_size * 0.5;

		mfd_screen_x_org = x_org * scalex;
		mfd_screen_y_org = y_org * scaley;

		org_offset = size * scalex * 0.5 - mfd_screen_half_size;
		mfd_screen_x_org += location == MFD_LOCATION_LHS ? -org_offset : org_offset;
		mfd_screen_y_org += size * scaley * 0.5 - mfd_screen_half_size;

		mfd_screen_x_min = mfd_screen_x_org - mfd_screen_half_size;
		mfd_screen_y_min = mfd_screen_y_org - mfd_screen_half_size;
		mfd_screen_x_max = mfd_screen_x_org + mfd_screen_half_size - 0.001;
		mfd_screen_y_max = mfd_screen_y_org + mfd_screen_half_size - 0.001;
	}

	//
	// translate & scale values (EO 3D display does not match texture)
	//

	i_translate_3d = mfd_screen_x_min;
	j_translate_3d = mfd_screen_y_min;

	i_scale_3d = mfd_texture_size / mfd_screen_size;
	j_scale_3d = mfd_texture_size / mfd_screen_size;

	////////////////////////////////////////
	//
	// set up MFD 2D environment
	//
	////////////////////////////////////////

	set_2d_active_environment (mfd_env);

	//
	// window
	//

	set_2d_window (mfd_env, MFD_WINDOW_X_MIN, MFD_WINDOW_Y_MIN, MFD_WINDOW_X_MAX, MFD_WINDOW_Y_MAX);

	//
	// viewport
	//

	mfd_viewport_size = MFD_VIEWPORT_SIZE;

	ASSERT (mfd_viewport_size <= mfd_texture_size);

	mfd_viewport_x_org = mfd_viewport_texture_x_org;

	mfd_viewport_y_org = mfd_viewport_texture_y_org;

	mfd_viewport_x_min = mfd_viewport_x_org - (mfd_viewport_size * 0.5);

	mfd_viewport_y_min = mfd_viewport_y_org - (mfd_viewport_size * 0.5);

	mfd_viewport_x_max = mfd_viewport_x_org + (mfd_viewport_size * 0.5) - 0.001;

	mfd_viewport_y_max = mfd_viewport_y_org + (mfd_viewport_size * 0.5) - 0.001;

	////////////////////////////////////////
	//
	// draw MFD display
	//
	////////////////////////////////////////

	switch (*mfd_mode)
	{
		////////////////////////////////////////
		case MFD_MODE_OFF:
		////////////////////////////////////////
		{
			set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

			set_active_screen (mfd_texture_screen);

			if (lock_screen (mfd_texture_screen))
			{
				set_block (0, 0, mfd_texture_size - 1, mfd_texture_size - 1, clear_mfd_colour);

				draw_layout_grid ();

				flush_screen_texture_graphics (mfd_texture_screen);

				unlock_screen (mfd_texture_screen);
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_DAMAGED:
		////////////////////////////////////////
		{
			draw_translucent_mfd_background (mfd_screen_x_min, mfd_screen_y_min, mfd_screen_x_max, mfd_screen_y_max);

			set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

			set_active_screen (mfd_texture_screen);

			if (lock_screen (mfd_texture_screen))
			{
				set_block (0, 0, mfd_texture_size - 1, mfd_texture_size - 1, clear_mfd_colour);

				draw_layout_grid ();

				draw_damaged_mfd ();

				flush_screen_texture_graphics (mfd_texture_screen);

				unlock_screen (mfd_texture_screen);
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_GROUND_RADAR:
		////////////////////////////////////////
		{
			draw_translucent_mfd_background (mfd_screen_x_min, mfd_screen_y_min, mfd_screen_x_max, mfd_screen_y_max);

			set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

			set_active_screen (mfd_texture_screen);

			if (lock_screen (mfd_texture_screen))
			{
				set_block (0, 0, mfd_texture_size - 1, mfd_texture_size - 1, clear_mfd_colour);

				draw_layout_grid ();

				draw_ground_radar_mfd (sub_mode);

				flush_screen_texture_graphics (mfd_texture_screen);

				unlock_screen (mfd_texture_screen);
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_AIR_RADAR:
		////////////////////////////////////////
		{
			draw_translucent_mfd_background (mfd_screen_x_min, mfd_screen_y_min, mfd_screen_x_max, mfd_screen_y_max);

			set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

			set_active_screen (mfd_texture_screen);

			if (lock_screen (mfd_texture_screen))
			{
				set_block (0, 0, mfd_texture_size - 1, mfd_texture_size - 1, clear_mfd_colour);

				draw_layout_grid ();

				draw_air_radar_mfd ();

				flush_screen_texture_graphics (mfd_texture_screen);

				unlock_screen (mfd_texture_screen);
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_FLIR:
		case MFD_MODE_DTV:
		case MFD_MODE_DVO:
		////////////////////////////////////////
		{
			if (!apache_damage.flir)
			{
				if (*mfd_mode == MFD_MODE_FLIR)
					draw_overlaid_3d_eo_display (&apache_flir, TARGET_ACQUISITION_SYSTEM_FLIR, mfd_screen_x_min, mfd_screen_y_min, mfd_screen_size);
				else if (*mfd_mode == MFD_MODE_DTV)
					draw_overlaid_3d_eo_display (&apache_dtv, TARGET_ACQUISITION_SYSTEM_DTV, mfd_screen_x_min, mfd_screen_y_min, mfd_screen_size);
				else
					draw_overlaid_3d_eo_display (&apache_dvo, TARGET_ACQUISITION_SYSTEM_DVO, mfd_screen_x_min, mfd_screen_y_min, mfd_screen_size);
			}
			else
				draw_translucent_mfd_background (mfd_screen_x_min, mfd_screen_y_min, mfd_screen_x_max, mfd_screen_y_max);

			set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);
			set_active_screen (mfd_texture_screen);

			if (lock_screen (mfd_texture_screen))
			{
				set_block (0, 0, mfd_texture_size - 1, mfd_texture_size - 1, clear_mfd_colour);

				draw_layout_grid ();

				if (*mfd_mode == MFD_MODE_FLIR)
					draw_2d_flir_mfd (TRUE, TRUE, FALSE);
				else if (*mfd_mode == MFD_MODE_DTV)
					draw_2d_dtv_mfd (TRUE, TRUE, FALSE);
				else
					draw_2d_dvo_mfd (TRUE, TRUE, FALSE);

				flush_screen_texture_graphics (mfd_texture_screen);
				unlock_screen (mfd_texture_screen);
			}

			set_pilots_full_screen_params (FALSE);

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_TSD:
		////////////////////////////////////////
		{

/*			if (tsd_tads_underlay_active)
			{
				if (eo_sensor == TARGET_ACQUISITION_SYSTEM_FLIR)
					draw_overlaid_3d_eo_display (&apache_flir, TARGET_ACQUISITION_SYSTEM_FLIR, mfd_screen_x_min, mfd_screen_y_min, mfd_screen_size);
				else
					draw_overlaid_3d_eo_display (&apache_dtv, TARGET_ACQUISITION_SYSTEM_DTV, mfd_screen_x_min, mfd_screen_y_min, mfd_screen_size);
			}
			else */
				draw_translucent_mfd_background (mfd_screen_x_min, mfd_screen_y_min, mfd_screen_x_max, mfd_screen_y_max);

			set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);
			set_active_screen (mfd_texture_screen);

			if (lock_screen (mfd_texture_screen))
			{
				set_block (0, 0, mfd_texture_size - 1, mfd_texture_size - 1, clear_green_mfd_colour);

				draw_tactical_situation_display_mfd (*mfd_mode);

				flush_screen_texture_graphics (mfd_texture_screen);

				unlock_screen (mfd_texture_screen);
			}

			if (tsd_tads_underlay_active)
				set_pilots_full_screen_params (FALSE);

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_ASE:
		////////////////////////////////////////
		{
			draw_translucent_mfd_background (mfd_screen_x_min, mfd_screen_y_min, mfd_screen_x_max, mfd_screen_y_max);

			set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

			set_active_screen (mfd_texture_screen);

			if (lock_screen (mfd_texture_screen))
			{
				set_block (0, 0, mfd_texture_size - 1, mfd_texture_size - 1, clear_green_mfd_colour);

				draw_layout_grid ();

				draw_aircraft_survivability_equipment_display_mfd ();

				flush_screen_texture_graphics (mfd_texture_screen);

				unlock_screen (mfd_texture_screen);
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_WEAPON:
		////////////////////////////////////////
		{
			draw_translucent_mfd_background (mfd_screen_x_min, mfd_screen_y_min, mfd_screen_x_max, mfd_screen_y_max);

			set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

			set_active_screen (mfd_texture_screen);

			if (lock_screen (mfd_texture_screen))
			{
				set_block (0, 0, mfd_texture_size - 1, mfd_texture_size - 1, clear_mfd_colour);

				draw_layout_grid ();

				draw_weapon_display_mfd (location, *mfd_mode);

				flush_screen_texture_graphics (mfd_texture_screen);

				unlock_screen (mfd_texture_screen);
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_SYSTEM:
		////////////////////////////////////////
		{
			draw_translucent_mfd_background (mfd_screen_x_min, mfd_screen_y_min, mfd_screen_x_max, mfd_screen_y_max);

			set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

			set_active_screen (mfd_texture_screen);

			if (lock_screen (mfd_texture_screen))
			{
				set_block (0, 0, mfd_texture_size - 1, mfd_texture_size - 1, clear_mfd_colour);

				draw_layout_grid ();

				draw_system_display_mfd ();

				flush_screen_texture_graphics (mfd_texture_screen);

				unlock_screen (mfd_texture_screen);
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_ENGINE:
		////////////////////////////////////////
		{
			draw_translucent_mfd_background (mfd_screen_x_min, mfd_screen_y_min, mfd_screen_x_max, mfd_screen_y_max);

			set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

			set_active_screen (mfd_texture_screen);

			if (lock_screen (mfd_texture_screen))
			{
				set_block (0, 0, mfd_texture_size - 1, mfd_texture_size - 1, clear_mfd_colour);

				draw_layout_grid ();

				draw_engine_display_mfd ();

				flush_screen_texture_graphics (mfd_texture_screen);

				unlock_screen (mfd_texture_screen);
			}

			break;
		}
		////////////////////////////////////////
		case MFD_MODE_FLIGHT:
		////////////////////////////////////////
		{
			draw_translucent_mfd_background (mfd_screen_x_min, mfd_screen_y_min, mfd_screen_x_max, mfd_screen_y_max);

			set_2d_viewport (mfd_env, mfd_viewport_x_min, mfd_viewport_y_min, mfd_viewport_x_max, mfd_viewport_y_max);

			set_active_screen (mfd_texture_screen);

			if (lock_screen (mfd_texture_screen))
			{
				set_block (0, 0, mfd_texture_size - 1, mfd_texture_size - 1, clear_green_mfd_colour);

				draw_layout_grid ();

				draw_flight_display_mfd();

				flush_screen_texture_graphics (mfd_texture_screen);

				unlock_screen (mfd_texture_screen);
			}

			break;
		}
	}

	set_active_screen (video_screen);

	////////////////////////////////////////
	//
	// render MFD to screen
	//
	////////////////////////////////////////
	{
		vertex
			quad[4];

		real_colour
			colour,
			specular;

		set_3d_active_environment (main_3d_env);

		if (begin_3d_scene ())
		{
			set_d3d_transparency_on ();

			set_d3d_zbuffer_comparison (FALSE);

			set_d3d_culling (FALSE);

			set_d3d_texture_wrapping (0, FALSE);

/*			if ((application_video_width == 640) || (get_global_unscaled_displays ()))
			{
				set_d3d_texture_mag_filtering (FALSE);
				set_d3d_texture_min_filtering (FALSE);
				set_d3d_texture_mip_filtering (FALSE);
			}
			else */
			{
				set_d3d_texture_mag_filtering (TRUE);
				set_d3d_texture_min_filtering (TRUE);
				set_d3d_texture_mip_filtering (FALSE);
			}

			set_d3d_flat_shaded_textured_renderstate (get_system_texture_ptr (texture_index));

			////////////////////////////////////////
			//

			colour.red	 			= 255;
			colour.green			= 255;
			colour.blue	 			= 255;
			colour.alpha  			= 255;

			specular.red 			= 0;
			specular.green	 		= 0;
			specular.blue 			= 0;
			specular.alpha	  		= 255;

			quad[0].i 				= mfd_screen_x_min;
			quad[0].j  				= mfd_screen_y_min;
			quad[0].z  				= 0.5;
			quad[0].q  				= 0.5;
			quad[0].u  				= 0.0;
			quad[0].v				= 0.0;

			quad[1].i  				= mfd_screen_x_max;
			quad[1].j  				= mfd_screen_y_min;
			quad[1].z  				= 0.5;
			quad[1].q  				= 0.5;
			quad[1].u  				= 1.0;
			quad[1].v  				= 0.0;

			quad[2].i				= mfd_screen_x_max;
			quad[2].j  				= mfd_screen_y_max;
			quad[2].z  				= 0.5;
			quad[2].q  				= 0.5;
			quad[2].u  				= 1.0;
			quad[2].v  				= 1.0;

			quad[3].i  				= mfd_screen_x_min;
			quad[3].j  				= mfd_screen_y_max;
			quad[3].z  				= 0.5;
			quad[3].q  				= 0.5;
			quad[3].u				= 0.0;
			quad[3].v				= 1.0;

			quad[0].next_vertex	= &quad[1];
			quad[1].next_vertex	= &quad[2];
			quad[2].next_vertex	= &quad[3];
			quad[3].next_vertex	= NULL;

			//
			////////////////////////////////////////

			draw_wbuffered_flat_shaded_textured_polygon (quad, colour, specular);

			set_d3d_transparency_off ();

			set_d3d_zbuffer_comparison (TRUE);

			set_d3d_culling (TRUE);

			end_3d_scene ();
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// EVENTS & MFD SWITCHING
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

mfd_modes get_mfd_mode_for_eo_sensor (void)
{
	mfd_modes
		mfd_mode;

	if (eo_sensor == TARGET_ACQUISITION_SYSTEM_FLIR)
	{
		mfd_mode = MFD_MODE_FLIR;
	}
	else if (eo_sensor == TARGET_ACQUISITION_SYSTEM_DTV)
	{
		mfd_mode = MFD_MODE_DTV;
	}
	else if (eo_sensor == TARGET_ACQUISITION_SYSTEM_DVO)
	{
		mfd_mode = MFD_MODE_DVO;
	}
	else
	{
		debug_fatal ("Invalid EO sensor = %d", eo_sensor);
	}

	return (mfd_mode);
}

static mfd_modes get_mfd_mode_for_radar (void)
{
	if (target_acquisition_system == TARGET_ACQUISITION_SYSTEM_AIR_RADAR || air_radar_is_active())
		return MFD_MODE_AIR_RADAR;

	return MFD_MODE_GROUND_RADAR;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_next_apache_tsd_ase_range (void)
{
	float *tsd_ase_range;

	if (get_local_entity_int_value (get_pilot_entity (), INT_TYPE_CREW_ROLE) == CREW_ROLE_PILOT)
		tsd_ase_range = &pilot_tsd_ase_range;
	else
		tsd_ase_range = &cpg_tsd_ase_range;

	if (*tsd_ase_range == TSD_ASE_RANGE_5000)
		*tsd_ase_range = TSD_ASE_RANGE_10000;
	else if (*tsd_ase_range == TSD_ASE_RANGE_10000)
		*tsd_ase_range = TSD_ASE_RANGE_25000;
	else if (*tsd_ase_range == TSD_ASE_RANGE_25000)
		*tsd_ase_range = TSD_ASE_RANGE_50000;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_previous_apache_tsd_ase_range (void)
{
	float *tsd_ase_range;

	if (get_local_entity_int_value (get_pilot_entity (), INT_TYPE_CREW_ROLE) == CREW_ROLE_PILOT)
		tsd_ase_range = &pilot_tsd_ase_range;
	else
		tsd_ase_range = &cpg_tsd_ase_range;

	if (*tsd_ase_range == TSD_ASE_RANGE_50000)
		*tsd_ase_range = TSD_ASE_RANGE_25000;
	else if (*tsd_ase_range == TSD_ASE_RANGE_25000)
		*tsd_ase_range = TSD_ASE_RANGE_10000;
	else if (*tsd_ase_range == TSD_ASE_RANGE_10000)
		*tsd_ase_range = TSD_ASE_RANGE_5000;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_next_apache_tsd_declutter_level (void)
{
	tsd_declutter_levels *tsd_declutter_level;

	if (get_local_entity_int_value (get_pilot_entity (), INT_TYPE_CREW_ROLE) == CREW_ROLE_PILOT)
		tsd_declutter_level = &pilot_tsd_declutter_level;
	else
		tsd_declutter_level = &cpg_tsd_declutter_level;

	if (*tsd_declutter_level == TSD_DECLUTTER_LEVEL_ALL)
		*tsd_declutter_level = TSD_DECLUTTER_LEVEL_TARGET;
	else if (*tsd_declutter_level == TSD_DECLUTTER_LEVEL_TARGET)
		*tsd_declutter_level = TSD_DECLUTTER_LEVEL_NAVIGATION;
	else
		*tsd_declutter_level = TSD_DECLUTTER_LEVEL_ALL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_previous_apache_tsd_declutter_level (void)
{
	tsd_declutter_levels *tsd_declutter_level;

	if (get_local_entity_int_value (get_pilot_entity (), INT_TYPE_CREW_ROLE) == CREW_ROLE_PILOT)
		tsd_declutter_level = &pilot_tsd_declutter_level;
	else
		tsd_declutter_level = &cpg_tsd_declutter_level;

	if (*tsd_declutter_level == TSD_DECLUTTER_LEVEL_ALL)
		*tsd_declutter_level = TSD_DECLUTTER_LEVEL_NAVIGATION;
	else if (*tsd_declutter_level == TSD_DECLUTTER_LEVEL_TARGET)
		*tsd_declutter_level = TSD_DECLUTTER_LEVEL_ALL;
	else
		*tsd_declutter_level = TSD_DECLUTTER_LEVEL_TARGET;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_next_tsd_underlay_level(void)
{
	if (get_local_entity_int_value (get_pilot_entity (), INT_TYPE_CREW_ROLE) == CREW_ROLE_PILOT)
	{
		int tads_active = (lhs_mfd_mode == MFD_MODE_DVO
			 || lhs_mfd_mode == MFD_MODE_DTV
			 || lhs_mfd_mode == MFD_MODE_FLIR
			 || rhs_mfd_mode == MFD_MODE_DVO
			 || rhs_mfd_mode == MFD_MODE_DTV
			 || rhs_mfd_mode == MFD_MODE_FLIR);

		if (pilot_tsd_underlay == TSD_UNDERLAY_NONE)
			pilot_tsd_underlay = TSD_UNDERLAY_MAP;
		else if (pilot_tsd_underlay == TSD_UNDERLAY_MAP && !tads_active)
			pilot_tsd_underlay = TSD_UNDERLAY_TADS;
		else
			pilot_tsd_underlay = TSD_UNDERLAY_NONE;
	}
	else  // co-pilot.  doesn't have tads underlay (co-pilot can just use ORT for TADS instead)
	{
		if (cpg_tsd_underlay == TSD_UNDERLAY_NONE)
			cpg_tsd_underlay = TSD_UNDERLAY_MAP;
		else
			cpg_tsd_underlay = TSD_UNDERLAY_NONE;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static mfd_modes get_next_mfd_mode (mfd_modes mfd_mode)
{
	mfd_modes
		next_mfd_mode;

	switch (mfd_mode)
	{
		case MFD_MODE_OFF:
		{
			next_mfd_mode = MFD_MODE_MENU;
			//next_mfd_mode = MFD_MODE_ENGINE;

			break;
		}
		case MFD_MODE_DAMAGED:
		{
			next_mfd_mode = MFD_MODE_DAMAGED;

			break;
		}
		case MFD_MODE_GROUND_RADAR:
		case MFD_MODE_AIR_RADAR:
		{
			if (tsd_tads_underlay_active)
				next_mfd_mode = MFD_MODE_TSD;
			else
				next_mfd_mode = get_mfd_mode_for_eo_sensor ();

			break;
		}
		case MFD_MODE_FLIR:
		case MFD_MODE_DTV:
		case MFD_MODE_DVO:
		{
			next_mfd_mode = MFD_MODE_TSD;

			break;
		}
		case MFD_MODE_TSD:
		{
			next_mfd_mode = MFD_MODE_ASE;

			break;
		}
		case MFD_MODE_ASE:
		{
			next_mfd_mode = MFD_MODE_WEAPON;

			break;
		}
		case MFD_MODE_WEAPON:
		{
			next_mfd_mode = MFD_MODE_SYSTEM;

			break;
		}
		case MFD_MODE_SYSTEM:
		{
			next_mfd_mode = MFD_MODE_ENGINE;

			break;
		}
		case MFD_MODE_ENGINE:
		{
			next_mfd_mode = MFD_MODE_FLIGHT;

			break;
		}
		case MFD_MODE_FLIGHT:
		{
			next_mfd_mode = get_mfd_mode_for_radar();

			break;
		}
		default:
		{
			debug_fatal ("Invalid mfd mode = %d", mfd_mode);

			break;
		}
	}

	return (next_mfd_mode);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static mfd_modes get_previous_mfd_mode (mfd_modes mfd_mode)
{
	mfd_modes
		previous_mfd_mode = MFD_MODE_OFF;

	switch (mfd_mode)
	{
		case MFD_MODE_OFF:
		{
			previous_mfd_mode = MFD_MODE_TSD;

			break;
		}
		case MFD_MODE_DAMAGED:
		{
			previous_mfd_mode = MFD_MODE_DAMAGED;

			break;
		}
		case MFD_MODE_GROUND_RADAR:
		case MFD_MODE_AIR_RADAR:
		{
			previous_mfd_mode = MFD_MODE_FLIGHT;

			break;
		}
		case MFD_MODE_FLIR:
		case MFD_MODE_DTV:
		case MFD_MODE_DVO:
		{
			previous_mfd_mode = get_mfd_mode_for_radar();

			break;
		}
		case MFD_MODE_TSD:
		{
			if (tsd_tads_underlay_active)
				previous_mfd_mode = get_mfd_mode_for_radar();
			else
				previous_mfd_mode = get_mfd_mode_for_eo_sensor ();

			break;
		}
		case MFD_MODE_ASE:
		{
			previous_mfd_mode = MFD_MODE_TSD;

			break;
		}
		case MFD_MODE_WEAPON:
		{
			previous_mfd_mode = MFD_MODE_ASE;

			break;
		}
		case MFD_MODE_SYSTEM:
		{
			previous_mfd_mode = MFD_MODE_WEAPON;

			break;
		}
		case MFD_MODE_ENGINE:
		{
			previous_mfd_mode = MFD_MODE_SYSTEM;

			break;
		}
		case MFD_MODE_FLIGHT:
		{
			previous_mfd_mode = MFD_MODE_ENGINE;

			break;
		}
		default:
		{
			debug_fatal ("Invalid mfd mode = %d", mfd_mode);

			break;
		}
	}

	return (previous_mfd_mode);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void cycle_apache_mfd (int forward, mfd_locations location)
{
	mfd_modes*
		change_mfd;

	mfd_modes
		oposite_mode,
		next_mfd_mode;

	if (location == MFD_LOCATION_PILOT_LHS)
	{
		change_mfd = &lhs_mfd_mode;
		oposite_mode = rhs_mfd_mode;
	}
	else if (location == MFD_LOCATION_CPG_LHS)
	{
		change_mfd = &cpg_lhs_mfd_mode;
		oposite_mode = cpg_rhs_mfd_mode;
	}
	else if (location == MFD_LOCATION_PILOT_RHS)
	{
		change_mfd = &rhs_mfd_mode;
		oposite_mode = lhs_mfd_mode;
	}
	else
	{
		change_mfd = &cpg_rhs_mfd_mode;
		oposite_mode = cpg_lhs_mfd_mode;
	}

	if (forward)
		next_mfd_mode = get_next_mfd_mode(*change_mfd);
	else
		next_mfd_mode = get_previous_mfd_mode(*change_mfd);

	if (next_mfd_mode != MFD_MODE_DAMAGED)
	{
		if (next_mfd_mode == oposite_mode)
			if (forward)
				next_mfd_mode = get_next_mfd_mode(next_mfd_mode);
			else
				next_mfd_mode = get_previous_mfd_mode(next_mfd_mode);

		ASSERT (next_mfd_mode != oposite_mode);
	}

	select_apache_mfd_mode (next_mfd_mode, location);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_next_apache_lhs_mfd (void)
{
	if (get_local_entity_int_value (get_pilot_entity (), INT_TYPE_CREW_ROLE) == CREW_ROLE_PILOT)
		cycle_apache_mfd(TRUE, MFD_LOCATION_PILOT_LHS);
	else
		cycle_apache_mfd(TRUE, MFD_LOCATION_CPG_LHS);
}

void select_previous_apache_lhs_mfd (void)
{
	if (get_local_entity_int_value (get_pilot_entity (), INT_TYPE_CREW_ROLE) == CREW_ROLE_PILOT)
		cycle_apache_mfd(FALSE, MFD_LOCATION_PILOT_LHS);
	else
		cycle_apache_mfd(FALSE, MFD_LOCATION_CPG_LHS);
}

void select_next_apache_rhs_mfd (void)
{
	if (get_local_entity_int_value (get_pilot_entity (), INT_TYPE_CREW_ROLE) == CREW_ROLE_PILOT)
		cycle_apache_mfd(TRUE, MFD_LOCATION_PILOT_RHS);
	else
		cycle_apache_mfd(TRUE, MFD_LOCATION_CPG_RHS);
}

void select_previous_apache_rhs_mfd (void)
{
	if (get_local_entity_int_value (get_pilot_entity (), INT_TYPE_CREW_ROLE) == CREW_ROLE_PILOT)
		cycle_apache_mfd(FALSE, MFD_LOCATION_PILOT_RHS);
	else
		cycle_apache_mfd(FALSE, MFD_LOCATION_CPG_RHS);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_apache_ground_radar_mfd (void)
{
	if (get_view_mode () == VIEW_MODE_COCKPIT_PANEL_SPECIAL_APACHE_LHS_MFD)
	{
		if (!apache_damage.lh_mfd)
		{
			select_apache_mfd_mode (MFD_MODE_GROUND_RADAR, MFD_LOCATION_LHS);

			return;
		}
	}

	if (get_view_mode () == VIEW_MODE_COCKPIT_PANEL_SPECIAL_APACHE_RHS_MFD)
	{
		if (!apache_damage.rh_mfd)
		{
			select_apache_mfd_mode (MFD_MODE_GROUND_RADAR, MFD_LOCATION_RHS);

			return;
		}
	}

	if (lhs_mfd_mode == MFD_MODE_GROUND_RADAR || rhs_mfd_mode == MFD_MODE_GROUND_RADAR)
		return;

	if (lhs_mfd_mode == MFD_MODE_AIR_RADAR)
	{
		select_apache_mfd_mode (MFD_MODE_GROUND_RADAR, MFD_LOCATION_LHS);

		return;
	}

	if (rhs_mfd_mode == MFD_MODE_AIR_RADAR)
	{
		select_apache_mfd_mode (MFD_MODE_GROUND_RADAR, MFD_LOCATION_RHS);

		return;
	}

	if ((lhs_mfd_mode == MFD_MODE_OFF) && (!apache_damage.lh_mfd))
	{
		select_apache_mfd_mode (MFD_MODE_GROUND_RADAR, MFD_LOCATION_LHS);

		return;
	}

	if ((rhs_mfd_mode == MFD_MODE_OFF) && (!apache_damage.rh_mfd))
	{
		select_apache_mfd_mode (MFD_MODE_GROUND_RADAR, MFD_LOCATION_RHS);

		return;
	}

	if (!apache_damage.lh_mfd)
	{
		select_apache_mfd_mode (MFD_MODE_GROUND_RADAR, MFD_LOCATION_LHS);

		return;
	}

	if (!apache_damage.rh_mfd)
	{
		select_apache_mfd_mode (MFD_MODE_GROUND_RADAR, MFD_LOCATION_RHS);

		return;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_apache_air_radar_mfd (void)
{
	if (get_view_mode () == VIEW_MODE_COCKPIT_PANEL_SPECIAL_APACHE_LHS_MFD)
	{
		if (!apache_damage.lh_mfd)
		{
			select_apache_mfd_mode (MFD_MODE_AIR_RADAR, MFD_LOCATION_LHS);

			return;
		}
	}

	if (get_view_mode () == VIEW_MODE_COCKPIT_PANEL_SPECIAL_APACHE_RHS_MFD)
	{
		if (!apache_damage.rh_mfd)
		{
			select_apache_mfd_mode (MFD_MODE_AIR_RADAR, MFD_LOCATION_RHS);

			return;
		}
	}

	if (lhs_mfd_mode == MFD_MODE_AIR_RADAR)
	{
		return;
	}

	if (rhs_mfd_mode == MFD_MODE_AIR_RADAR)
	{
		return;
	}

	if (lhs_mfd_mode == MFD_MODE_GROUND_RADAR)
	{
		select_apache_mfd_mode (MFD_MODE_AIR_RADAR, MFD_LOCATION_LHS);

		return;
	}

	if (rhs_mfd_mode == MFD_MODE_GROUND_RADAR)
	{
		select_apache_mfd_mode (MFD_MODE_AIR_RADAR, MFD_LOCATION_RHS);

		return;
	}

	if ((lhs_mfd_mode == MFD_MODE_OFF) && (!apache_damage.lh_mfd))
	{
		select_apache_mfd_mode (MFD_MODE_AIR_RADAR, MFD_LOCATION_LHS);

		return;
	}

	if ((rhs_mfd_mode == MFD_MODE_OFF) && (!apache_damage.rh_mfd))
	{
		select_apache_mfd_mode (MFD_MODE_AIR_RADAR, MFD_LOCATION_RHS);

		return;
	}

	if (!apache_damage.lh_mfd)
	{
		select_apache_mfd_mode (MFD_MODE_AIR_RADAR, MFD_LOCATION_LHS);

		return;
	}

	if (!apache_damage.rh_mfd)
	{
		select_apache_mfd_mode (MFD_MODE_AIR_RADAR, MFD_LOCATION_RHS);

		return;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_apache_tads_mfd (void)
{
	// co-pilot has ORT as TADS display, doesn't need to use a MFD
	if (get_local_entity_int_value (get_pilot_entity (), INT_TYPE_CREW_ROLE) == CREW_ROLE_CO_PILOT)
		return;

	if (get_view_mode () == VIEW_MODE_COCKPIT_PANEL_SPECIAL_APACHE_LHS_MFD)
	{
		if (!apache_damage.lh_mfd)
		{
			select_apache_mfd_mode (get_mfd_mode_for_eo_sensor (), MFD_LOCATION_LHS);

			return;
		}
	}

	if (get_view_mode () == VIEW_MODE_COCKPIT_PANEL_SPECIAL_APACHE_RHS_MFD)
	{
		if (!apache_damage.rh_mfd)
		{
			select_apache_mfd_mode (get_mfd_mode_for_eo_sensor (), MFD_LOCATION_RHS);

			return;
		}
	}

	if (tsd_tads_underlay_active)
		pilot_tsd_underlay = TSD_UNDERLAY_NONE;

	if ((lhs_mfd_mode == MFD_MODE_FLIR) || (lhs_mfd_mode == MFD_MODE_DTV) || (lhs_mfd_mode == MFD_MODE_DVO))
	{
		select_apache_mfd_mode (get_mfd_mode_for_eo_sensor (), MFD_LOCATION_LHS);

		return;
	}

	if ((rhs_mfd_mode == MFD_MODE_FLIR) || (rhs_mfd_mode == MFD_MODE_DTV) || (rhs_mfd_mode == MFD_MODE_DVO))
	{
		select_apache_mfd_mode (get_mfd_mode_for_eo_sensor (), MFD_LOCATION_RHS);

		return;
	}

	if ((lhs_mfd_mode == MFD_MODE_OFF) && (!apache_damage.lh_mfd))
	{
		select_apache_mfd_mode (get_mfd_mode_for_eo_sensor (), MFD_LOCATION_LHS);

		return;
	}

	if ((rhs_mfd_mode == MFD_MODE_OFF) && (!apache_damage.rh_mfd))
	{
		select_apache_mfd_mode (get_mfd_mode_for_eo_sensor (), MFD_LOCATION_RHS);

		return;
	}

	if (!apache_damage.lh_mfd)
	{
		select_apache_mfd_mode (get_mfd_mode_for_eo_sensor (), MFD_LOCATION_LHS);

		return;
	}

	if (!apache_damage.rh_mfd)
	{
		select_apache_mfd_mode (get_mfd_mode_for_eo_sensor (), MFD_LOCATION_RHS);

		return;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void toggle_apache_ase_auto_page (void)
{
	set_global_ase_auto_page (get_global_ase_auto_page () ^ 1);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void auto_page_apache_ase_mfd (void)
{
	if (!get_global_ase_auto_page ())
	{
		return;
	}

	////////////////////////////////////////
	//
	// select viewed large MFD
	//
	////////////////////////////////////////

	if (get_view_mode () == VIEW_MODE_COCKPIT_PANEL_SPECIAL_APACHE_LHS_MFD)
	{
		if (!apache_damage.lh_mfd)
		{
			select_apache_mfd_mode (MFD_MODE_ASE, MFD_LOCATION_LHS);

			return;
		}
	}

	if (get_view_mode () == VIEW_MODE_COCKPIT_PANEL_SPECIAL_APACHE_RHS_MFD)
	{
		if (!apache_damage.rh_mfd)
		{
			select_apache_mfd_mode (MFD_MODE_ASE, MFD_LOCATION_RHS);

			return;
		}
	}

	////////////////////////////////////////
	//
	// check if already displayed
	//
	////////////////////////////////////////

	if (lhs_mfd_mode == MFD_MODE_ASE)
	{
		return;
	}

	if (rhs_mfd_mode == MFD_MODE_ASE)
	{
		return;
	}

	////////////////////////////////////////
	//
	// select undamaged off MFD
	//
	////////////////////////////////////////

	if ((lhs_mfd_mode == MFD_MODE_OFF) && (!apache_damage.lh_mfd))
	{
		select_apache_mfd_mode (MFD_MODE_ASE, MFD_LOCATION_LHS);

		return;
	}

	if ((rhs_mfd_mode == MFD_MODE_OFF) && (!apache_damage.rh_mfd))
	{
		select_apache_mfd_mode (MFD_MODE_ASE, MFD_LOCATION_RHS);

		return;
	}

	////////////////////////////////////////
	//
	// select unfocused MFD
	//
	////////////////////////////////////////

	if ((!get_apache_mfd_has_focus (MFD_LOCATION_LHS)) && (!apache_damage.lh_mfd))
	{
		select_apache_mfd_mode (MFD_MODE_ASE, MFD_LOCATION_LHS);

		return;
	}

	if ((!get_apache_mfd_has_focus (MFD_LOCATION_RHS)) && (!apache_damage.rh_mfd))
	{
		select_apache_mfd_mode (MFD_MODE_ASE, MFD_LOCATION_RHS);

		return;
	}

	////////////////////////////////////////
	//
	// select undamaged MFD
	//
	////////////////////////////////////////

	if (!apache_damage.lh_mfd)
	{
		select_apache_mfd_mode (MFD_MODE_ASE, MFD_LOCATION_LHS);

		return;
	}

	if (!apache_damage.rh_mfd)
	{
		select_apache_mfd_mode (MFD_MODE_ASE, MFD_LOCATION_RHS);

		return;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void toggle_apache_lhs_mfd_on_off (void)
{
	mfd_locations location;
	mfd_modes mfd_mode;

	if (get_local_entity_int_value (get_pilot_entity (), INT_TYPE_CREW_ROLE) == CREW_ROLE_PILOT)
	{
		location = MFD_LOCATION_PILOT_LHS;
		mfd_mode = lhs_mfd_mode;
	}
	else
	{
		location = MFD_LOCATION_CPG_LHS;
		mfd_mode = cpg_lhs_mfd_mode;
	}

	if (mfd_mode != MFD_MODE_OFF)
		select_apache_mfd_mode (MFD_MODE_OFF, location);
	else
		select_apache_mfd_mode (MFD_MODE_ENGINE, location);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void toggle_apache_rhs_mfd_on_off (void)
{
	mfd_locations location;
	mfd_modes mfd_mode;

	if (get_local_entity_int_value (get_pilot_entity (), INT_TYPE_CREW_ROLE) == CREW_ROLE_PILOT)
	{
		location = MFD_LOCATION_PILOT_RHS;
		mfd_mode = rhs_mfd_mode;
	}
	else
	{
		location = MFD_LOCATION_CPG_RHS;
		mfd_mode = cpg_rhs_mfd_mode;
	}

	if (mfd_mode != MFD_MODE_OFF)
		select_apache_mfd_mode (MFD_MODE_OFF, location);
	else
		select_apache_mfd_mode (MFD_MODE_FLIGHT, location);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void toggle_apache_ort_on_off(void)
{
	if (get_local_entity_int_value (get_pilot_entity (), INT_TYPE_CREW_ROLE) != CREW_ROLE_CO_PILOT)
		return;

	if (ort_mode != MFD_MODE_OFF)
		select_apache_mfd_mode (MFD_MODE_OFF, MFD_LOCATION_ORT);
	else
		select_apache_mfd_mode (get_mfd_mode_for_eo_sensor(), MFD_LOCATION_ORT);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_apache_mfd_has_focus (mfd_locations mfd_location)
{
	int
		result;

	mfd_modes
		mfd_mode;

	if (mfd_location == MFD_LOCATION_PILOT_LHS)
		mfd_mode = lhs_mfd_mode;
	else if (mfd_location == MFD_LOCATION_PILOT_RHS)
		mfd_mode = rhs_mfd_mode;
	else if (mfd_location == MFD_LOCATION_CPG_LHS)
		mfd_mode = cpg_lhs_mfd_mode;
	else if (mfd_location == MFD_LOCATION_CPG_RHS)
		mfd_mode = cpg_rhs_mfd_mode;

	switch (target_acquisition_system)
	{
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_GROUND_RADAR:
		////////////////////////////////////////
		{
			result = (mfd_mode == MFD_MODE_GROUND_RADAR);

			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_AIR_RADAR:
		////////////////////////////////////////
		{
			result = (mfd_mode == MFD_MODE_AIR_RADAR);

			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_FLIR:
		////////////////////////////////////////
		{
			result = (mfd_mode == MFD_MODE_FLIR);

			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_DTV:
		////////////////////////////////////////
		{
			result = (mfd_mode == MFD_MODE_DTV);

			break;
		}
		////////////////////////////////////////
		case TARGET_ACQUISITION_SYSTEM_DVO:
		////////////////////////////////////////
		{
			result = (mfd_mode == MFD_MODE_DVO);

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			result = FALSE;

			break;
		}
	}

	return (result);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_apache_tads_display_visible (void)
{
	return
	(
		(lhs_mfd_mode == MFD_MODE_FLIR) ||
		(lhs_mfd_mode == MFD_MODE_DTV) ||
		(lhs_mfd_mode == MFD_MODE_DVO) ||
		(rhs_mfd_mode == MFD_MODE_FLIR) ||
		(rhs_mfd_mode == MFD_MODE_DTV) ||
		(rhs_mfd_mode == MFD_MODE_DVO)
	);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void adjust_apache_pitch_ladder_datum_position(float adjustment)
{
	pitch_ladder_datum_position = bound(pitch_ladder_datum_position + adjustment, -0.2, 0.2);
}
