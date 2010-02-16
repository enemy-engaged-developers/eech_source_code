/*
 * ap_mfd_buttons.c
 *
 *  Created on: 05.sep.2009
 *      Author: arneh
 */

#include "project.h"

#include "ap_mfd_buttons.h"
#include "ap_mfd_button_sprites.h"
#include "ap_keyboard_unit.h"
#include "ap_coordinate_point.h"

#include "../common/co_adf.h"
#include "../../dynamics/common/co_fuel.h"
#include "entity/tacview/tacview.h"

#define string2mfd_width(x)  ((x) / 512.0 * 2.4)

typedef struct {
	int boxed;
	int barriered;
	char line1[20];
	char line2[20];
} mfd_button_label_decorations;

static const float button_spacing = 0.3;
static mfd_button_labels last_button_pressed = NO_BTN;

static mfd_locations
	pilot_mfd_focus,
	co_pilot_mfd_focus,
	current_mfd_focus;

static unsigned
	show_acquisition_source[NUM_MFD_LOCATIONS],
	show_acquisition_source_selection[NUM_MFD_LOCATIONS],
	accepting_coordinate_input,
	accepting_waypoint_input,
	accepting_target;

static int
	tsd_waypoint_offset;

static apache_coordinate_points
	*waypoint_to_add;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int set_new_page(mfd_push_button_types page, mfd_button_labels btn);
static int select_util_page(mfd_push_button_types page, mfd_button_labels btn);

static int select_menu_page(mfd_push_button_types page, mfd_button_labels btn);
static int set_new_checklist_page(mfd_push_button_types page, mfd_button_labels btn);
static int set_new_checklist_sub_page(mfd_push_button_types page, mfd_button_labels btn);
static int set_new_sub_page_number(mfd_push_button_types page, mfd_button_labels btn);
static int toggle_datum_adjust(mfd_push_button_types page, mfd_button_labels btn);
static int adjust_pitch_datum(mfd_push_button_types page, mfd_button_labels btn);

static int show_acquisition_source_menu(mfd_push_button_types page, mfd_button_labels btn);
static int select_acquisition_source(mfd_push_button_types page, mfd_button_labels btn);

static int select_tsd_sub_page(mfd_push_button_types page, mfd_button_labels btn);
static int tsd_button_action(mfd_push_button_types page, mfd_button_labels btn);
static int zoom_display(mfd_push_button_types page, mfd_button_labels btn);
static int tsd_scale_selection(mfd_push_button_types page, mfd_button_labels btn);
static int change_tsd_waypoint_page(mfd_push_button_types page, mfd_button_labels btn);
static int handle_waypoint_selection(mfd_push_button_types page, mfd_button_labels btn);
static int get_waypoint_input(mfd_push_button_types page, mfd_button_labels btn);
static int get_add_waypoint_input(mfd_push_button_types page, mfd_button_labels btn);
static int handle_tsd_waypoint_action(mfd_push_button_types page, mfd_button_labels btn);
static int set_waypoint_type(mfd_push_button_types page, mfd_button_labels btn);
static int edit_waypoint(mfd_push_button_types page, mfd_button_labels btn);

static int set_fuel_transfer_mode(mfd_push_button_types page, mfd_button_labels btn);
static int set_fuel_crossfeed(mfd_push_button_types page, mfd_button_labels btn);
static int set_fuel_type(mfd_push_button_types page, mfd_button_labels btn);
static int toggle_fuel_booster(mfd_push_button_types page, mfd_button_labels btn);

static int pan_radar_scan(mfd_push_button_types page, mfd_button_labels btn);
static int radar_function(mfd_push_button_types page, mfd_button_labels btn);
static int select_radar_next_target_to_shoot(mfd_push_button_types page, mfd_button_labels btn);
static int toggle_auto_scan_pan(mfd_push_button_types page, mfd_button_labels btn);

static int set_terrain_sensivity_sub_page(mfd_push_button_types page, mfd_button_labels btn);
static int select_terrain_sensivity_option(mfd_push_button_types page, mfd_button_labels btn);
static int change_radar_state(mfd_push_button_types page, mfd_button_labels btn);

static int set_mfd_weapon_mode(mfd_push_button_types page, mfd_button_labels btn);
static int set_burst_limit(mfd_push_button_types page, mfd_button_labels btn);
static int button_toggle_gun_mode(mfd_push_button_types page, mfd_button_labels btn);
static int set_rocket_salvo_size(mfd_push_button_types page, mfd_button_labels btn);
static int select_rocket_zone(mfd_push_button_types page, mfd_button_labels btn);

static int select_tpm_sub_menu(mfd_push_button_types page, mfd_button_labels btn);
static int select_tpm_prof_option(mfd_push_button_types page, mfd_button_labels btn);
static int select_tpm_lines_option(mfd_push_button_types page, mfd_button_labels btn);
static int select_tpm_clearance_option(mfd_push_button_types page, mfd_button_labels btn);
static int toggle_tpm_far_near_mode(mfd_push_button_types page, mfd_button_labels btn);

static int toggle_adf_on_off(mfd_push_button_types page, mfd_button_labels btn);
static int toggle_adf_preset_page(mfd_push_button_types page, mfd_button_labels btn);
static int toggle_adf_mode(mfd_push_button_types page, mfd_button_labels btn);
static int select_adf_station(mfd_push_button_types page, mfd_button_labels btn);
static int select_adf_test_mode(mfd_push_button_types page, mfd_button_labels btn);
static int select_adf_emergency_freqency(mfd_push_button_types page, mfd_button_labels btn);
static int select_adf_last_freqency(mfd_push_button_types page, mfd_button_labels btn);
static int tune_selected_adf_station(mfd_push_button_types page, mfd_button_labels btn);
static int toggle_adf_tone_play(mfd_push_button_types page, mfd_button_labels btn);
static int get_adf_input(mfd_push_button_types page, mfd_button_labels btn);

enum {
	NO_BOXING,
	NORM_BOXING,
	SINGLE_BOXING
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// label line 1,    label line 2, page arrow, vertical, box, click handler
static mfd_push_button mfd_push_button_definitions[NUM_PUSHBUTTON_TYPES] = {
	// main menu buttons
	{ NULL,	"ADF",		NULL,	TRUE, FALSE, FALSE, set_new_page },
	{ NULL,	"ASE",		NULL,	TRUE, FALSE, FALSE, set_new_page },
	{ NULL,	"CHAN",		NULL,	TRUE, FALSE, FALSE, set_new_page },
	{ NULL,	"CHECK",	NULL,	TRUE, FALSE, FALSE, set_new_page },
	{ NULL,	"CODE",		NULL,	TRUE, FALSE, FALSE, set_new_page },
	{ NULL,	"DMS",		NULL,	TRUE, FALSE, FALSE, set_new_page },
	{ NULL,	"EFT",		NULL,	TRUE, FALSE, FALSE, set_new_page },
	{ NULL,	"FUEL",		NULL,	TRUE, FALSE, FALSE, set_new_page },
	{ NULL,	"ENG",		NULL,	TRUE, FALSE, FALSE, set_new_page },
	{ NULL,	"FLT",		NULL,	TRUE, FALSE, FALSE, set_new_page },
	{ NULL,	"PERF",		NULL,	TRUE, FALSE, FALSE, set_new_page },
	{ NULL,	"SYS",		NULL,	TRUE, FALSE, FALSE, set_new_page },
	{ NULL,	"UTIL",		NULL,	TRUE, FALSE, FALSE, select_util_page },
	{ NULL,	"VERS",		NULL,	TRUE, FALSE, FALSE, set_new_page },
	{ NULL,	"WCA",		NULL,	TRUE, FALSE, FALSE, set_new_page },
	{ NULL,	"WPN",		NULL,	TRUE, FALSE, FALSE, set_new_page },

	// buttons returning to main menu
	{ NULL,	"TSD", 		NULL, 	TRUE, FALSE, FALSE, select_menu_page },
	{ NULL,	"ENG", 		NULL, 	TRUE, FALSE, FALSE, select_menu_page },
	{ NULL,	"CHECK",	NULL, 	TRUE, FALSE, FALSE, select_menu_page },
	{ NULL,	"FLT", 		NULL, 	TRUE, FALSE, FALSE, select_menu_page },
	{ NULL,	"FUEL", 		NULL, 	TRUE, FALSE, FALSE, select_menu_page },
	{ NULL,	"ADF", 		NULL, 	TRUE, FALSE, FALSE, select_menu_page },
	{ NULL,	"WPN", 		NULL, 	TRUE, FALSE, FALSE, select_menu_page },

	// page buttons
	{ NULL,	"PG", 		"1", 	FALSE, FALSE, FALSE, set_new_sub_page_number },
	{ NULL,	"PG", 		"2", 	FALSE, FALSE, FALSE, set_new_sub_page_number },
	{ NULL,	"PG", 		"3", 	FALSE, FALSE, FALSE, set_new_sub_page_number },
	{ NULL,	"PG", 		"4", 	FALSE, FALSE, FALSE, set_new_sub_page_number },

	// Aquisition source
	{ NULL,	"ACQ", 		"", FALSE, FALSE, FALSE, show_acquisition_source_menu },
	{ NULL,	"PHS", 		NULL, FALSE, FALSE, FALSE, select_acquisition_source },
	{ NULL,	"GHS", 		NULL, FALSE, FALSE, FALSE, select_acquisition_source },
	{ NULL,	"SKR", 		NULL, FALSE, FALSE, FALSE, select_acquisition_source },
	{ NULL,	"RFI", 		NULL, FALSE, FALSE, FALSE, select_acquisition_source },
	{ NULL,	"FCR", 		NULL, FALSE, FALSE, FALSE, select_acquisition_source },
	{ NULL,	"FXD", 		NULL, FALSE, FALSE, FALSE, select_acquisition_source },
	{ NULL,	"TADS",		NULL, FALSE, FALSE, FALSE, select_acquisition_source },
	{ NULL,	"", 		NULL, FALSE, FALSE, FALSE, select_acquisition_source },

	// TSD page
	{ NULL,	"RPT", 		NULL, 	TRUE, FALSE, FALSE, NULL },
	{ NULL,	"PSN", 		NULL, 	FALSE, FALSE, FALSE, NULL },
	{ NULL,	"PP", 		NULL, 	FALSE, FALSE, FALSE, tsd_button_action },
	{ NULL,	"COORD",	NULL, 	TRUE, FALSE, FALSE, select_tsd_sub_page },
	{ NULL,	"UTIL", 	NULL, 	TRUE, FALSE, FALSE, select_tsd_sub_page },
	{ NULL,	"HDG", 		NULL, 	FALSE, TRUE, FALSE, NULL },
	{ NULL,	"REC", 		NULL, 	FALSE, TRUE, FALSE, NULL },
	{ NULL,	"JAM", 		NULL, 	FALSE, TRUE, FALSE, NULL },
	{ NULL,	"SHOW",		NULL, 	TRUE,  TRUE, FALSE, select_tsd_sub_page },
	{ NULL,	"SC", 		NULL, 	FALSE, FALSE, FALSE, tsd_button_action },
	{ NULL,	"CTR", 		NULL, 	FALSE, FALSE, FALSE, tsd_button_action },
	{ NULL,	"FRZ", 		NULL, 	FALSE, FALSE, FALSE, tsd_button_action },
	{ NULL,	"PHASE",	"NAV", 	FALSE, FALSE, FALSE, tsd_button_action },
	{ NULL,	"PHASE",	"ATK", 	FALSE, FALSE, FALSE, tsd_button_action },
	{ NULL,	"ZN", 		NULL, 	TRUE, FALSE, FALSE, select_tsd_sub_page },
	{ NULL,	"WPT", 		NULL, 	TRUE, FALSE, FALSE, select_tsd_sub_page },
	{ NULL,	"RTE", 		NULL, 	TRUE, FALSE, FALSE, select_tsd_sub_page },
	{ NULL,	"THRT", 	NULL, 	TRUE, FALSE, FALSE, select_tsd_sub_page },

	{ NULL,	"50", 		NULL, 	FALSE, FALSE, FALSE, tsd_scale_selection },
	{ NULL,	"25", 		NULL, 	FALSE, FALSE, FALSE, tsd_scale_selection },
	{ NULL,	"10", 		NULL, 	FALSE, FALSE, FALSE, tsd_scale_selection },
	{ NULL,	"5", 		NULL, 	FALSE, FALSE, FALSE, tsd_scale_selection },

	{ NULL,	"POINT>",	NULL, 	FALSE, FALSE, FALSE, get_waypoint_input },
	{ NULL,	"IDENT>",	NULL, 	FALSE, FALSE, FALSE, get_add_waypoint_input },
	{ NULL,	"FREE>",	NULL, 	FALSE, FALSE, FALSE, get_add_waypoint_input },
	{ NULL,	"ADD", 		NULL, 	FALSE, FALSE, FALSE, handle_waypoint_selection },
	{ NULL,	"DEL", 		NULL, 	FALSE, FALSE, FALSE, handle_waypoint_selection },
	{ NULL,	"DELETE",	NULL, 	FALSE, FALSE, FALSE, NULL },
	{ NULL,	"NEW", 		NULL, 	FALSE, FALSE, FALSE, NULL },
	{ NULL,	"END", 		NULL, 	FALSE, FALSE, FALSE, NULL },
	{ NULL,	"EDT", 		NULL, 	FALSE, FALSE, FALSE, edit_waypoint },
	{ NULL,	"XMIT",		NULL, 	FALSE, FALSE, FALSE, NULL },
	{ NULL,	"SEND",		NULL, 	FALSE, FALSE, FALSE, NULL },
	{ NULL,	"YES", 		NULL, 	FALSE, FALSE, FALSE, handle_tsd_waypoint_action },
	{ NULL,	"NO", 		NULL, 	FALSE, FALSE, FALSE, handle_tsd_waypoint_action },
	{ NULL,	"NOW",		NULL, 	FALSE, FALSE, FALSE, handle_tsd_waypoint_action },
	{ NULL,	"STO",		NULL, 	FALSE, FALSE, FALSE, handle_tsd_waypoint_action },
	{ NULL,	"UP",		NULL, 	FALSE, FALSE, FALSE, change_tsd_waypoint_page },
	{ NULL,	"DOWN",		NULL, 	FALSE, FALSE, FALSE, change_tsd_waypoint_page },
	{ NULL,	NULL,		NULL,	FALSE, FALSE, FALSE, handle_waypoint_selection },

	{ NULL,	"DIR", 		NULL, 	FALSE, FALSE, TRUE, handle_waypoint_selection },
	{ NULL,	"RVW", 		NULL, 	FALSE, FALSE, FALSE, handle_waypoint_selection },
	{ NULL,	"RTM", 		NULL, 	FALSE, FALSE, FALSE, NULL },
	{ NULL,	"REVERSE ROUTE",	NULL, 	FALSE, FALSE, FALSE, NULL },

	{ NULL,	"WP",		NULL, 	FALSE, FALSE, FALSE, set_waypoint_type },
	{ NULL,	"HZ",		NULL, 	FALSE, FALSE, FALSE, set_waypoint_type },
	{ NULL,	"CM",		NULL, 	FALSE, FALSE, FALSE, set_waypoint_type },

	// radar page
	{ NULL,	"C SCP",	NULL, 	FALSE, FALSE, TRUE, radar_function },
	{ NULL,	"NTS",		NULL, 	FALSE, TRUE, FALSE, select_radar_next_target_to_shoot },
	{ NULL,	"TGT",		NULL, 	FALSE, TRUE, FALSE, NULL },
	{ NULL,	"ELEV",		"AUTO",	FALSE, FALSE, FALSE, NULL },
	{ NULL,	"ZOOM",		NULL, 	FALSE, TRUE, FALSE, zoom_display },
	{ NULL,	"RF",		"HO", 	FALSE, FALSE, FALSE, NULL },

	{ NULL,	"PROF",		NULL, 	FALSE, FALSE, FALSE, select_tpm_sub_menu },
	{ NULL,	"GEOM",		NULL, 	FALSE, FALSE, FALSE, select_tpm_prof_option },
	{ NULL,	"ARITH",	NULL, 	FALSE, FALSE, FALSE, select_tpm_prof_option },
	{ NULL,	"TEST",		NULL, 	FALSE, FALSE, FALSE, select_tpm_prof_option },
	{ NULL,	"LINES",	NULL, 	FALSE, FALSE, FALSE, select_tpm_sub_menu },
	{ NULL,	"0",		NULL, 	FALSE, FALSE, FALSE, select_tpm_lines_option },
	{ NULL,	"1",		NULL, 	FALSE, FALSE, FALSE, select_tpm_lines_option },
	{ NULL,	"2",		NULL, 	FALSE, FALSE, FALSE, select_tpm_lines_option },
	{ NULL,	"3",		NULL, 	FALSE, FALSE, FALSE, select_tpm_lines_option },
	{ NULL,	"4",		NULL, 	FALSE, FALSE, FALSE, select_tpm_lines_option },
	{ NULL,	"CLEARANCE",	NULL, FALSE, FALSE, FALSE, select_tpm_sub_menu },
	{ NULL,	"20",		NULL, 	FALSE, FALSE, FALSE, select_tpm_clearance_option },
	{ NULL,	"50",		NULL, 	FALSE, FALSE, FALSE, select_tpm_clearance_option },
	{ NULL,	"100",		NULL, 	FALSE, FALSE, FALSE, select_tpm_clearance_option },
	{ NULL,	"200",		NULL, 	FALSE, FALSE, FALSE, select_tpm_clearance_option },
	{ NULL,	"ELEV",		"NEAR", FALSE, FALSE, FALSE, toggle_tpm_far_near_mode },
	{ NULL,	"ELEV",		"FAR", 	FALSE, FALSE, FALSE, toggle_tpm_far_near_mode },

	{ NULL,	"RFI",		NULL, 	FALSE, FALSE, FALSE, change_radar_state },
	{ NULL,	"FCR",		NULL, 	FALSE, FALSE, FALSE, change_radar_state },
	{ NULL,	"RFI MODE",	"ALL", 	FALSE, FALSE, FALSE, change_radar_state },
	{ NULL,	"RFI MODE",	"HOSTILE", 	FALSE, FALSE, FALSE, change_radar_state },
	{ NULL,	"PRIORITY",	NULL, 	FALSE, FALSE, FALSE, NULL },
	{ NULL,	"TERRAIN",	NULL, 	FALSE, FALSE, FALSE, set_terrain_sensivity_sub_page },
	{ NULL,	"MMA",		"PINNED", 	FALSE, FALSE, FALSE, change_radar_state },
	{ NULL,	"MMA",		"NORM",	FALSE, FALSE, FALSE, change_radar_state },

	{ NULL,	"AUTO",		NULL, 	FALSE, FALSE, FALSE, select_terrain_sensivity_option },
	{ NULL,	"1",		NULL, 	FALSE, FALSE, FALSE, select_terrain_sensivity_option },
	{ NULL,	"2",		NULL, 	FALSE, FALSE, FALSE, select_terrain_sensivity_option },
	{ NULL,	"3",		NULL, 	FALSE, FALSE, FALSE, select_terrain_sensivity_option },
	{ NULL,	"4",		NULL, 	FALSE, FALSE, FALSE, select_terrain_sensivity_option },
	{ NULL,	"5",		NULL, 	FALSE, FALSE, FALSE, select_terrain_sensivity_option },
	{ NULL,	"6",		NULL, 	FALSE, FALSE, FALSE, select_terrain_sensivity_option },

	// weapon page
	{ NULL,	"TRAIN",	NULL, 	FALSE, FALSE, FALSE, NULL },
	{ NULL,	"LRFD",		"FIRST", FALSE, FALSE, FALSE, NULL },
	{ NULL,	"LRFD",		"LAST",	FALSE, FALSE, FALSE, NULL },
	{ NULL,	"GUN",		NULL, 	FALSE, FALSE, FALSE, set_mfd_weapon_mode },
	{ NULL,	"MSL",		NULL,	FALSE, FALSE, FALSE, set_mfd_weapon_mode },
	{ NULL,	"ATA",		NULL, 	FALSE, FALSE, FALSE, set_mfd_weapon_mode },
	{ NULL,	"RKT",		NULL, 	FALSE, FALSE, FALSE, set_mfd_weapon_mode },
	{ NULL,	"MANRNG>",	"", 	FALSE, FALSE, FALSE, NULL },

	{ NULL,	"10",		NULL, 	FALSE, FALSE, FALSE, set_burst_limit },
	{ NULL,	"20",		NULL, 	FALSE, FALSE, FALSE, set_burst_limit },
	{ NULL,	"50",		NULL, 	FALSE, FALSE, FALSE, set_burst_limit },
	{ NULL,	"100",		NULL, 	FALSE, FALSE, FALSE, set_burst_limit },
	{ NULL,	"ALL",		NULL, 	FALSE, FALSE, FALSE, set_burst_limit },
	{ NULL,	"MODE",		"NORM",	FALSE, FALSE, FALSE, button_toggle_gun_mode },
	{ NULL,	"MODE",		"FXD", 	FALSE, FALSE, FALSE, button_toggle_gun_mode },
	{ NULL,	"RANGE",	NULL, 	FALSE, FALSE, FALSE, NULL },

	{ NULL,	"QTY",		NULL, 	FALSE, FALSE, FALSE, set_rocket_salvo_size },
	{ NULL,	"1",		NULL, 	FALSE, FALSE, FALSE, set_rocket_salvo_size },
	{ NULL,	"2",		NULL, 	FALSE, FALSE, FALSE, set_rocket_salvo_size },
	{ NULL,	"4",		NULL, 	FALSE, FALSE, FALSE, set_rocket_salvo_size },
	{ NULL,	"8",		NULL, 	FALSE, FALSE, FALSE, set_rocket_salvo_size },
	{ NULL,	"12",		NULL, 	FALSE, FALSE, FALSE, set_rocket_salvo_size },
	{ NULL,	"24",		NULL, 	FALSE, FALSE, FALSE, set_rocket_salvo_size },
	{ NULL,	"ALL",		NULL, 	FALSE, FALSE, FALSE, set_rocket_salvo_size },

	{ rocket_pod_centre_zone, rocket_pod_centre_zone_mask, NULL, 	FALSE, FALSE, FALSE, select_rocket_zone },
	{ rocket_pod_quad_zone, rocket_pod_quad_zone_mask, NULL, 	FALSE, FALSE, FALSE, select_rocket_zone },
	{ rocket_pod_perimiter_zone, rocket_pod_perimiter_zone_mask, NULL, 	FALSE, FALSE, FALSE, select_rocket_zone },

	{ NULL,	"ALL",		NULL, 	FALSE, FALSE, FALSE, NULL },
	{ NULL,	"AUTO",		NULL, 	FALSE, FALSE, FALSE, NULL },
	{ NULL,	"NONE",		NULL, 	FALSE, FALSE, FALSE, NULL },
	{ NULL,	"SAL",		"AUTO",	FALSE, FALSE, FALSE, NULL },
	{ NULL,	"LOBL INHIBIT",	NULL, 	FALSE, FALSE, FALSE, NULL },
	{ NULL,	"2ND TARGET INHIBIT",	NULL, 	FALSE, FALSE, FALSE, NULL },
	{ NULL,	"TYPE",		"RF", 	FALSE, FALSE, FALSE, NULL },
	{ NULL,	"TYPE",		"SAL", 	FALSE, FALSE, FALSE, NULL },
	{ NULL,	"MODE",		"NORM",	FALSE, FALSE, FALSE, NULL },
	{ NULL,	"MODE",		"RIPL",	FALSE, FALSE, FALSE, NULL },
	{ NULL,	"MODE",		"MAN",	FALSE, FALSE, FALSE, NULL },

	// flight page
	{ NULL,	"SET", 		NULL, 	FALSE, FALSE, FALSE, NULL },
	{ NULL,	"-W-", 		NULL, 	FALSE, FALSE, TRUE, toggle_datum_adjust },

	{ left_arrow, left_arrow_mask, left_arrow_background, FALSE, FALSE, FALSE, pan_radar_scan },
	{ right_arrow, right_arrow_mask, right_arrow_background, FALSE, FALSE, FALSE, pan_radar_scan },
	{ up_arrow, up_arrow_mask, NULL, FALSE, FALSE, FALSE, adjust_pitch_datum },
	{ down_arrow, down_arrow_mask, NULL, FALSE, FALSE, FALSE, adjust_pitch_datum },

	// fuel buttons
	{ NULL,	"L AUX", 	NULL, 	FALSE, FALSE, NORM_BOXING, NULL },
	{ NULL,	"R AUX", 	NULL, 	FALSE, FALSE, NORM_BOXING, NULL },
	{ NULL,	"FWD", 		NULL, 	FALSE, FALSE, NO_BOXING, set_fuel_transfer_mode },
	{ NULL,	"OFF", 		NULL, 	FALSE, FALSE, NO_BOXING, set_fuel_transfer_mode },
	{ NULL,	"AFT", 		NULL, 	FALSE, FALSE, NO_BOXING, set_fuel_transfer_mode },
	{ NULL,	"XFER", 	"MAN", 	FALSE, FALSE, NO_BOXING, set_fuel_transfer_mode },
	{ NULL,	"XFER", 	"AUTO",	FALSE, FALSE, NO_BOXING, set_fuel_transfer_mode },
	{ NULL,	"AUX", 		"GAL", 	FALSE, FALSE, NO_BOXING, NULL },

	{ NULL,	"BOOST", 	NULL, 	FALSE, FALSE, NO_BOXING, toggle_fuel_booster },
	{ NULL,	"FWD", 		NULL, 	FALSE, FALSE, NO_BOXING, set_fuel_crossfeed },
	{ NULL,	"NORM", 	NULL, 	FALSE, FALSE, NO_BOXING, set_fuel_crossfeed },
	{ NULL,	"AFT", 		NULL, 	FALSE, FALSE, NO_BOXING, set_fuel_crossfeed },
	{ NULL,	"TYP",		NULL, 	FALSE, FALSE, NO_BOXING, set_fuel_type },
	{ NULL,	"JP4",		NULL, 	FALSE, FALSE, NO_BOXING, set_fuel_type },
	{ NULL,	"JP5",		NULL, 	FALSE, FALSE, NO_BOXING, set_fuel_type },
	{ NULL,	"JP8",		NULL, 	FALSE, FALSE, NO_BOXING, set_fuel_type },

	// checklist buttons
	{ NULL,	"THRU", 		"FLT", 	TRUE, FALSE, TRUE, set_new_checklist_page },   // THRU FLT
	{ NULL,	"PERF", 		"DAT1", TRUE, FALSE, TRUE, set_new_checklist_page },
	{ NULL,	"PERF", 		"DAT2", TRUE, FALSE, TRUE, set_new_checklist_page },
	{ NULL,	"AFT", 		"APU", 	FALSE, FALSE, TRUE, set_new_checklist_sub_page },
	{ NULL,	"BF",			"ENG", 	FALSE, FALSE, TRUE, set_new_checklist_sub_page },
	{ NULL,	"ENG", 		NULL, 	FALSE, FALSE, TRUE, set_new_checklist_sub_page },
	{ NULL,	"BF",			"TAXI", FALSE, FALSE, TRUE, set_new_checklist_sub_page },
	{ NULL,	"TAXI", 		NULL, 	FALSE, FALSE, TRUE, set_new_checklist_sub_page },
	{ NULL,	"BF",			"TO", 	FALSE, FALSE, TRUE, set_new_checklist_sub_page },
	{ NULL,	"BF",			"LAND", FALSE, FALSE, TRUE, set_new_checklist_sub_page },
	{ NULL,	"AFT",		"LAND", FALSE, FALSE, TRUE, set_new_checklist_sub_page },
	{ NULL,	"SHUT",		"DOWN", FALSE, FALSE, TRUE, set_new_checklist_sub_page },
	{ NULL,	"RAPID REFUELING", NULL, FALSE, FALSE, TRUE, set_new_checklist_sub_page },
	{ NULL,	"RAPID REARMING", NULL, FALSE, FALSE, TRUE, set_new_checklist_sub_page },
	{ NULL,	"FCR OPR CHECK", NULL, FALSE, FALSE, TRUE, set_new_checklist_sub_page },
	{ NULL,	"PILOT IHADDS BORE", NULL, FALSE, FALSE, TRUE, set_new_checklist_sub_page },
	{ NULL,	"FLIR OPR CHECK", NULL, FALSE, FALSE, TRUE, set_new_checklist_sub_page },
	{ NULL,	"MANUAL DRIFT NULL", NULL, FALSE, FALSE, TRUE, set_new_checklist_sub_page },
	{ NULL,	"PECHAN REALLIGN", NULL, FALSE, FALSE, TRUE, set_new_checklist_sub_page },
	{ NULL,	"CUE UPDATE PROC", NULL, FALSE, FALSE, TRUE, set_new_checklist_sub_page },
	{ NULL,	"TADS OPR CHECK", NULL, FALSE, FALSE, TRUE, set_new_checklist_sub_page },
	{ NULL,	"TADS OUTFR BORE", NULL, FALSE, FALSE, TRUE, set_new_checklist_sub_page },
	{ NULL,	"FLIGHT CONTROL", NULL, FALSE, FALSE, TRUE, set_new_checklist_sub_page },
	{ NULL,	"CL", 			NULL, 	TRUE, FALSE, TRUE, set_new_checklist_sub_page },   // checklist return

	// ADF buttons
	{ NULL,	"TUNE", 	NULL, FALSE, FALSE, FALSE, tune_selected_adf_station },
	{ NULL,	"TONE", 	NULL, FALSE, FALSE, TRUE, toggle_adf_tone_play },
	{ NULL,	"IDENTIFY",	NULL, FALSE, FALSE, FALSE, NULL },
	{ NULL,	"ADF", 		NULL, FALSE, FALSE, FALSE, toggle_adf_on_off },
	{ NULL,	"MODE", 	"ANT", FALSE, FALSE, FALSE, toggle_adf_mode },
	{ NULL,	"MODE", 	"ADF", FALSE, FALSE, FALSE, toggle_adf_mode },
	{ NULL,	"FREQ>", 	NULL, FALSE, FALSE, FALSE, get_adf_input },
	{ NULL,	"TEST", 	NULL, FALSE, FALSE, FALSE, select_adf_test_mode },
	{ NULL,	"LAST", 	NULL, FALSE, FALSE, FALSE, select_adf_last_freqency },
	{ NULL,	"PRSET", 	NULL, TRUE, FALSE, TRUE, toggle_adf_preset_page },
	{ NULL,	"ID>", 		NULL, FALSE, FALSE, FALSE, get_adf_input },
	{ NULL,	"500", 		NULL, FALSE, FALSE, FALSE, select_adf_emergency_freqency },
	{ NULL,	"2182", 	NULL, FALSE, FALSE, FALSE, select_adf_emergency_freqency },
	{ NULL,	"", 		NULL, FALSE, FALSE, FALSE, select_adf_station },

	};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static mfd_push_button* mfd_button_handlers[4][BTN_B5 + 1] = { 0 };
static mfd_button_label_decorations button_label_decorations[4][BTN_B5 + 1] = { 0 };

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int select_menu_page(mfd_push_button_types page, mfd_button_labels btn)
{
	select_apache_mfd_mode(MFD_MODE_MENU, current_mfd_focus);

	return TRUE;
}

static int select_util_page(mfd_push_button_types page, mfd_button_labels btn)
{
	int sub_mode = get_apache_mfd_sub_mode(current_mfd_focus);

	switch (get_apache_current_mfd_mode(current_mfd_focus))
	{
	case MFD_MODE_GROUND_RADAR:
		set_apache_mfd_sub_mode(current_mfd_focus, sub_mode == 1 ? 0 : 1);
		break;
	}

	return TRUE;
}

static int set_new_page(mfd_push_button_types page, mfd_button_labels btn)
{
	mfd_modes mode = MFD_MODE_MENU;

	switch (page)
	{
	case MFD_BUTTON_ASE:
		mode = MFD_MODE_ASE;
		break;
	case MFD_BUTTON_CL:
		mode = MFD_MODE_CHECKLIST;
		break;
	case MFD_BUTTON_ENG:
		mode = MFD_MODE_ENGINE;
		break;
	case MFD_BUTTON_FLT:
		mode = MFD_MODE_FLIGHT;
		break;
	case MFD_BUTTON_FUEL:
		mode = MFD_MODE_FUEL;
		break;
	case MFD_BUTTON_WPN:
		mode = MFD_MODE_WEAPON;
		break;
	case MFD_BUTTON_ADF:
		mode = MFD_MODE_ADF;
		break;
	}

	if (mode != MFD_MODE_MENU)
	{
		select_apache_mfd_mode(mode, current_mfd_focus);
		return TRUE;
	}

	return FALSE;
}


static int set_new_sub_page_number(mfd_push_button_types page, mfd_button_labels btn)
{
	int number = page - MFD_BUTTON_PAGE1 + 1;
	set_apache_mfd_sub_page(current_mfd_focus, number);

	return TRUE;
}

static int show_acquisition_source_menu(mfd_push_button_types page, mfd_button_labels btn)
{
	show_acquisition_source_selection[current_mfd_focus] = TRUE;

	return TRUE;
}

static int select_acquisition_source(mfd_push_button_types page, mfd_button_labels btn)
{
	select_apache_acquisition_source(TARGET_ACQUISITION_SOURCE_PHS + (page - MFD_BUTTON_ACQ_PHS));

	// reset buttons
	setup_apache_mfd_buttons(get_apache_current_mfd_mode(current_mfd_focus), current_mfd_focus, TRUE);

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// functions for validating input from the keyboard input unit

/* Returns the inputed float in f if it is valid and between min and max values */
static int validate_float_input(const char* input, mfd_locations location, mfd_modes mfd_mode, float* f, float min_val, float max_val)
{
	const char* tmp;

	// Focus or mfd page may have changed from when we requested input.  Abort if so
	if (location != current_mfd_focus || get_apache_current_mfd_mode(location) != mfd_mode)
		return FALSE;

	for (tmp = input; *tmp; tmp++)
		if (*tmp != '.' && (*tmp < '0' || *tmp > '9'))
			return FALSE;

	if (sscanf(input, "%f", f) != 1)
		return FALSE;

	if (*f < min_val || *f > max_val)
		return FALSE;

	return TRUE;
}

static int validate_string_input(const char* input, mfd_locations location, mfd_modes mode, char* string, unsigned max_len)
{
	if (location != current_mfd_focus || get_apache_current_mfd_mode(current_mfd_focus) != mode)
		return FALSE;

	if (!input)
		return FALSE;

	strncpy(string, input, max_len-1);
	string[max_len-1] = 0;

	return TRUE;
}

static int validate_coordinate_input(const char* input, mfd_locations location, mfd_modes mode, vec3d* position)
{
	const char* tmp;
	int is_grid = TRUE;

	if (location != current_mfd_focus || get_apache_current_mfd_mode(current_mfd_focus) != mode)
		return FALSE;

	if (!input)
		return FALSE;

	while (isspace(*input))
		input++;

	tmp = input;
	while (isdigit(*tmp))
		tmp++;

	if (*tmp == '\'')
		is_grid = FALSE;

	if (is_grid)
	{
		float x, z;

		if (sscanf(input, "%f %f", &x, &z) != 2)
			return FALSE;

		position->x = x * 4000.0;
		position->z = z * 4000.0;
	}
	else
	{
		int lat_deg, lat_m, lat_s, long_deg, long_m, long_s;
		double latitude, longitude;
		char north_south, east_west;

		if (sscanf(input, "%d'%d\"%d%c %d'%d\"%d%c", &lat_deg, &lat_m, &lat_s, &north_south, &long_deg, &long_m, &long_s, &east_west) != 8)
			return FALSE;

		if (north_south == 'S')
			lat_deg = -lat_deg;
		else if (north_south != 'N')
			return FALSE;

		if (east_west == 'W')
			long_deg = -long_deg;
		else if (east_west != 'E')
			return FALSE;

		latitude = rad((double)lat_deg + lat_m / 60.0 + lat_s / 3600.0);
		longitude = rad((double)long_deg + long_m / 60.0 + long_s / 3600.0);

		get_position_from_latitude_longitude(
				latitude,
				longitude,
				position);
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// TSD page

static int select_tsd_sub_page(mfd_push_button_types page, mfd_button_labels btn)
{
	mfd_modes current_mode = get_apache_current_mfd_mode(current_mfd_focus);
	mfd_modes mode = MFD_MODE_OFF;

	switch (page)
	{
	case MFD_BUTTON_WPT:
		mode = MFD_MODE_TSD_WPT;
		break;
	case MFD_BUTTON_TSD_UTIL:
		mode = MFD_MODE_TSD_UTIL;
		break;
	case MFD_BUTTON_RTE:
		mode = MFD_MODE_TSD_RTE;
		break;
	case MFD_BUTTON_THRT:
		mode = MFD_MODE_TSD_THRT;
		break;
	case MFD_BUTTON_COORD:
		mode = MFD_MODE_TSD_COORD;
		break;
	case MFD_BUTTON_SHOW:
		mode = MFD_MODE_TSD_SHOW;
		break;
	case MFD_BUTTON_ZN:
		mode = MFD_MODE_TSD_ZONE;
		break;
	default:
		ASSERT(FALSE);
		break;
	}

	// if repressing button, go back to main TSD page
	if (mode == current_mode)
		mode = MFD_MODE_TSD;

	select_apache_mfd_mode(mode, current_mfd_focus);

	return TRUE;
}

static int tsd_button_action(mfd_push_button_types page, mfd_button_labels btn)
{
	if (page == MFD_BUTTON_CTR)
		toggle_apache_tsd_is_centered(current_mfd_focus);
	else if (page == MFD_BUTTON_PHASE_ATK)
		set_apache_tsd_phase_nav(current_mfd_focus);
	else if (page == MFD_BUTTON_PHASE_NAV)
		set_apache_tsd_phase_atk(current_mfd_focus);
	else if (page == MFD_BUTTON_SC)
	{
		set_apache_mfd_sub_mode(current_mfd_focus, 1);
		setup_apache_mfd_buttons(MFD_MODE_TSD, current_mfd_focus, TRUE);
	}
	else if (page == MFD_BUTTON_FRZ)
		toggle_apache_tsd_frozen(current_mfd_focus);
	else if (page == MFD_BUTTON_PP)
		toggle_apache_tsd_display_present_position_status(current_mfd_focus);

	return TRUE;
}

static int tsd_scale_selection(mfd_push_button_types page, mfd_button_labels btn)
{
	float range = 50000.0;

	switch (page)
	{
	case MFD_BUTTON_TSD_SCALE_50:
		range = 50000.0;
		break;
	case MFD_BUTTON_TSD_SCALE_25:
		range = 25000.0;
		break;
	case MFD_BUTTON_TSD_SCALE_10:
		range = 10000.0;
		break;
	case MFD_BUTTON_TSD_SCALE_5:
		range = 5000.0;
		break;
	}

	set_apache_tsd_range(current_mfd_focus, range);

	set_apache_mfd_sub_mode(current_mfd_focus, 0);
	setup_apache_mfd_buttons(MFD_MODE_TSD, current_mfd_focus, TRUE);

	return TRUE;
}

static int change_tsd_waypoint_page(mfd_push_button_types page, mfd_button_labels btn)
{
	int current_waypoint = get_current_apache_waypoint_number();

	if (current_waypoint == -1)
		current_waypoint = 0;

	if (page == MFD_BUTTON_UP)
	{
		unsigned max_wp = get_current_apache_last_waypoint_number() - current_waypoint;
		tsd_waypoint_offset = min(tsd_waypoint_offset + 4, max_wp);

	}
	else
		tsd_waypoint_offset = max(tsd_waypoint_offset - 4, -current_waypoint);

	return TRUE;
}

static void select_waypoint(apache_coordinate_points* wpnt)
{
	unsigned i;
	unsigned reset_decorations = TRUE;
	mfd_button_labels btn = NO_BTN;
	mfd_push_button** handler = mfd_button_handlers[current_mfd_focus];
	mfd_push_button_types selection_type;
	mfd_modes current_mode = get_apache_current_mfd_mode(current_mfd_focus);

	for (btn = BTN_L1; btn <= BTN_L6; btn++)
		if (button_label_decorations[current_mfd_focus][btn].boxed == 3)
			break;

	if (btn < BTN_R1)
		selection_type = handler[btn] - mfd_push_button_definitions;
//		handler = mfd_button_handlers[current_mfd_focus][btn];
	else
		selection_type = handler[BTN_L1] - mfd_push_button_definitions;
//		handler = mfd_button_handlers[current_mfd_focus][BTN_L1];

//	selection_type = handler - mfd_push_button_definitions;

	switch (selection_type)
	{
	case MFD_BUTTON_ADD:  // ADD
		if (waypoint_to_add)
		{
			apache_insert_waypoint_into_route(waypoint_to_add, wpnt);
			waypoint_to_add = NULL;
		}
		else
		{
			waypoint_to_add = wpnt;

			// toggle waypoint select buttons
			for (i = BTN_R1; i <= BTN_R6; i++)
				button_label_decorations[current_mfd_focus][i].barriered = FALSE;

			reset_decorations = FALSE;
		}
		break;
	case MFD_BUTTON_DEL:
		if (current_mode == MFD_MODE_TSD_RTE)
		{
			// remove waypoint from EECH map waypoints
			if (wpnt->waypoint_entity)
				map_delete_waypoint_event(wpnt->waypoint_entity);

			// delete waypoint on WPT page, just remove from route if on RTE page
			apache_remove_waypoint_from_route(wpnt);
		}

		break;
	case MFD_BUTTON_RTE_DIR:
		set_apache_direct_navigation_waypoint(wpnt);
		break;
	case MFD_BUTTON_POINT_INPUT:
		if (current_mode != MFD_MODE_TSD_WPT)
			break;
		// fallthrough
	case MFD_BUTTON_RTE_RVW:
		set_apache_tsd_show_waypoint_review(current_mfd_focus, wpnt);
		reset_decorations = FALSE;
		break;
	}

	// reset decorations
	if (reset_decorations)
	{
		button_label_decorations[current_mfd_focus][btn].boxed = 0;
		for (i = BTN_R1; i <= BTN_R6; i++)
			button_label_decorations[current_mfd_focus][i].barriered = TRUE;
		tsd_waypoint_offset = 3;
		accepting_waypoint_input = FALSE;
	}
}

static int edit_waypoint(mfd_push_button_types page, mfd_button_labels btn)
{
	unsigned was_selected = button_label_decorations[current_mfd_focus][btn].boxed == 3;
	unsigned dummy;
	apache_coordinate_points* wp = get_apache_tsd_show_waypoint_review(current_mfd_focus);
	mfd_push_button** handler = mfd_button_handlers[current_mfd_focus];

	button_label_decorations[current_mfd_focus][btn].boxed = was_selected ? 0 : 3;

	if (was_selected)
	{
		handler[BTN_L1] = &mfd_push_button_definitions[MFD_BUTTON_POINT_INPUT];
		return TRUE;
	}

	if (!wp)
	{
		wp = get_current_apache_navigation_point(&dummy);
		if (wp)
			set_apache_tsd_show_waypoint_review(current_mfd_focus, wp);
	}

	if (wp)
	{
		handler[BTN_L1] = &mfd_push_button_definitions[MFD_BUTTON_FREE_INPUT];

		return TRUE;
	}
	else
		return FALSE;
}

static int handle_waypoint_selection(mfd_push_button_types page, mfd_button_labels btn)
{
	unsigned i;
	unsigned was_selected = button_label_decorations[current_mfd_focus][btn].boxed == 3;
	mfd_modes current_mode = get_apache_current_mfd_mode(current_mfd_focus);
	mfd_push_button** handler = mfd_button_handlers[current_mfd_focus];

	switch (page)
	{
	case MFD_BUTTON_DEL:
		if (current_mode == MFD_MODE_TSD_WPT)
		{
			handler[BTN_L1] = &mfd_push_button_definitions[MFD_BUTTON_POINT_INPUT];
			handler[BTN_L2] = NULL;
			handler[BTN_L3] = &mfd_push_button_definitions[MFD_BUTTON_YES];
			handler[BTN_L4] = &mfd_push_button_definitions[MFD_BUTTON_NO];
			handler[BTN_L5] = NULL;
			handler[BTN_L6] = NULL;
			break;
		}
	case MFD_BUTTON_RTE_DIR:
	case MFD_BUTTON_RTE_RVW:
		button_label_decorations[current_mfd_focus][btn].boxed = was_selected ? 0 : 3;

		// deselect any other button
		for (i = BTN_L1; i <= BTN_L6; i++)
			if (i != btn)
				button_label_decorations[current_mfd_focus][i].boxed = 0;

		// toggle waypoint select buttons
		for (i = BTN_R1; i <= BTN_R6; i++)
			button_label_decorations[current_mfd_focus][i].barriered = was_selected;

		accepting_waypoint_input = !was_selected && page == MFD_BUTTON_RTE_DIR;

		break;
	case MFD_BUTTON_ADD:
		button_label_decorations[current_mfd_focus][btn].boxed = was_selected ? 0 : 3;

		// deselect any other button
		for (i = BTN_L1; i <= BTN_L6; i++)
			if (i != btn)
				button_label_decorations[current_mfd_focus][i].boxed = 0;

		// toggle waypoint select buttons
		for (i = BTN_R1; i <= BTN_R6; i++)
			button_label_decorations[current_mfd_focus][i].barriered = TRUE;

		if (current_mode == MFD_MODE_TSD_WPT)
		{
			if (!was_selected)
			{
				apache_coordinate_points* new_wp = get_next_free_waypoint();

				if (new_wp)
				{
					set_apache_tsd_show_waypoint_review(current_mfd_focus, new_wp);

					get_local_entity_vec3d(get_gunship_entity(), VEC3D_TYPE_POSITION, &new_wp->position);
					new_wp->position.y -= current_flight_dynamics->radar_altitude.value;

					handler[BTN_L1] = &mfd_push_button_definitions[MFD_BUTTON_IDENT_INPUT];
					handler[BTN_L3] = NULL;
					handler[BTN_L4] = &mfd_push_button_definitions[MFD_BUTTON_WPT_TYPE_WP];
					handler[BTN_L5] = &mfd_push_button_definitions[MFD_BUTTON_WPT_TYPE_HZ];
					handler[BTN_L6] = &mfd_push_button_definitions[MFD_BUTTON_WPT_TYPE_CM];
					button_label_decorations[current_mfd_focus][BTN_L4].boxed = 3;
				}
			}
			else
			{
				set_apache_tsd_show_waypoint_review(current_mfd_focus, NULL);

				handler[BTN_L1] = &mfd_push_button_definitions[MFD_BUTTON_POINT_INPUT];
//				handler[BTN_L2] = &mfd_push_button_definitions[MFD_BUTTON_ADD];
				handler[BTN_L3] = &mfd_push_button_definitions[MFD_BUTTON_DEL];
				handler[BTN_L4] = &mfd_push_button_definitions[MFD_BUTTON_EDT];
				handler[BTN_L5] = &mfd_push_button_definitions[MFD_BUTTON_STO];
				handler[BTN_L6] = &mfd_push_button_definitions[MFD_BUTTON_XMIT];
			}
		}
		else
		{
			accepting_waypoint_input = !was_selected;

			mfd_button_handlers[current_mfd_focus][BTN_L1] = &mfd_push_button_definitions[MFD_BUTTON_POINT_INPUT];
		}

		break;
	case MFD_BUTTON_TSD_WAYPOINT_SELECT:
		{
			int wp_no;
			unsigned last_waypoint;
			apache_coordinate_points** route = get_current_apache_navigation_route(&last_waypoint, &wp_no);


			// find which waypoint was selected:
			if (wp_no == -1)
				wp_no = 0;

			wp_no += tsd_waypoint_offset - (btn - BTN_R2);

			ASSERT(wp_no >= 0 && wp_no <= last_waypoint);
			if (wp_no >= 0 && wp_no <= last_waypoint)
			{
				apache_coordinate_points* wpt = route[wp_no];
				if (wpt && wpt->valid)
					select_waypoint(wpt);
			}

			break;
		}
	}

	return TRUE;
}

static void handle_coordinate_point_input(const char* input, mfd_locations location, mfd_modes mfd_mode)
{
	char entered_wpt[4], type;
	int number;
	apache_coordinate_points* wpt = NULL;

	if (!validate_string_input(input, location, mfd_mode, entered_wpt, sizeof(entered_wpt)))
		return;

	// validate input
	type = entered_wpt[0];
	if (type != 'T' && type != 'W' && type != 'C')
		return;

	if (!isdigit(entered_wpt[1]) || !isdigit(entered_wpt[2]))
		return;

	number = atoi(&entered_wpt[1]);

	if (type == 'T')  // target point
	{
		if (number >= NUM_APACHE_TARGET_POINTS)
			return;

		wpt = &apache_target_points[number];
	}
	else
	{
		if (number >= NUM_APACHE_WAYPOINT_CM_POINTS)
			return;

		if ((type == 'W' && number >= 50) || (type == 'C' && number < 50))
			return;

		wpt = &apache_waypoint_hazard_points[number];
	}

	select_waypoint(wpt);
}

static int get_waypoint_input(mfd_push_button_types page, mfd_button_labels btn)
{
	get_apache_keyboard_unit_input("POINT", current_mfd_focus, get_apache_current_mfd_mode(current_mfd_focus), handle_coordinate_point_input);
	toggle_apache_keyboard_unit_active(TRUE);

	return TRUE;
}

static void handle_new_waypoint_altitude_input(const char* input, mfd_locations location, mfd_modes mfd_mode)
{
	apache_coordinate_points* wp = get_apache_tsd_show_waypoint_review(current_mfd_focus);

	if (wp)
	{
		float metres_asl;

		if (validate_float_input(input, location, mfd_mode, &metres_asl, 0.0, 20000.0))
			wp->position.y = feet_to_metres(metres_asl);

		store_apache_coordinate_point(wp);

		// reset buttons
		set_apache_tsd_show_waypoint_review(current_mfd_focus, NULL);
		setup_apache_mfd_buttons(MFD_MODE_TSD_WPT, current_mfd_focus, FALSE);
	}
}

static void handle_new_waypoint_position_input(const char* input, mfd_locations location, mfd_modes mfd_mode)
{
	apache_coordinate_points* wp = get_apache_tsd_show_waypoint_review(current_mfd_focus);

	if (wp)
	{
		validate_coordinate_input(input, location, mfd_mode, &wp->position);

		// get altitude
		get_apache_keyboard_unit_input("ALTITUDE", current_mfd_focus, get_apache_current_mfd_mode(current_mfd_focus), handle_new_waypoint_altitude_input);
		toggle_apache_keyboard_unit_active(TRUE);
	}
}

static void handle_new_waypoint_input(const char* input, mfd_locations location, mfd_modes mfd_mode)
{
	apache_coordinate_points* wp = get_apache_tsd_show_waypoint_review(current_mfd_focus);

	if (!input)
		wp->free_text[0] = 0;

	if (wp)
	{
		validate_string_input(input, location, mfd_mode, wp->free_text, sizeof(wp->free_text));

		wp->valid = TRUE;

		// get coordinate
		get_apache_keyboard_unit_input("UTM LT/LG", current_mfd_focus, get_apache_current_mfd_mode(current_mfd_focus), handle_new_waypoint_position_input);
		toggle_apache_keyboard_unit_active(TRUE);
	}
}

static int get_add_waypoint_input(mfd_push_button_types page, mfd_button_labels btn)
{
	apache_coordinate_points* wp = get_apache_tsd_show_waypoint_review(current_mfd_focus);

	if (wp)
	{
		char* prompt = (page == MFD_BUTTON_IDENT_INPUT) ? "IDENT" : "FREE";

		accepting_coordinate_input = accepting_waypoint_input = accepting_target = FALSE;

		get_apache_keyboard_unit_input(prompt, current_mfd_focus, get_apache_current_mfd_mode(current_mfd_focus), handle_new_waypoint_input);
		toggle_apache_keyboard_unit_active(TRUE);
	}

	return TRUE;
}

static int handle_tsd_waypoint_action(mfd_push_button_types page, mfd_button_labels btn)
{
	mfd_push_button** handler = mfd_button_handlers[current_mfd_focus];

	switch (page)
	{
	case MFD_BUTTON_STO:
		if (button_label_decorations[current_mfd_focus][BTN_L5].boxed)  // already are storing, disable
		{
			set_apache_tsd_show_waypoint_review(current_mfd_focus, NULL);

			button_label_decorations[current_mfd_focus][BTN_L5].boxed = 0;
			handler[BTN_L1] = &mfd_push_button_definitions[MFD_BUTTON_POINT_INPUT];
		}
		else
		{
			apache_coordinate_points* store_point = get_next_free_waypoint();
			if (store_point)
				set_apache_tsd_show_waypoint_review(current_mfd_focus, store_point);

			button_label_decorations[current_mfd_focus][BTN_L5].boxed = 3;
			handler[BTN_L1] = &mfd_push_button_definitions[MFD_BUTTON_NOW];
		}
		break;
	case MFD_BUTTON_NOW:
		{
			apache_coordinate_points* store_point = get_apache_tsd_show_waypoint_review(current_mfd_focus);

			ASSERT(store_point);
			get_local_entity_vec3d(get_gunship_entity(), VEC3D_TYPE_POSITION, &store_point->position);
			store_point->position.y -= current_flight_dynamics->radar_altitude.value;
			store_apache_coordinate_point(store_point);

			button_label_decorations[current_mfd_focus][BTN_L5].boxed = 0;
			handler[BTN_L1] = &mfd_push_button_definitions[MFD_BUTTON_POINT_INPUT];
		}
		break;
	case MFD_BUTTON_YES:  // delete waypoint
		{
			apache_coordinate_points* wpnt = get_apache_tsd_show_waypoint_review(current_mfd_focus);

			if (wpnt)
			{
				// remove waypoint from EECH map waypoints
				if (wpnt->waypoint_entity)
					map_delete_waypoint_event(wpnt->waypoint_entity);

				// delete waypoint on WPT page
				apache_delete_coordinate_point(wpnt);
			}
		}
		// fallthrough
	case MFD_BUTTON_NO:
		// reset page
		ASSERT(get_apache_current_mfd_mode(current_mfd_focus == MFD_MODE_TSD_WPT));

		setup_apache_mfd_buttons(MFD_MODE_TSD_WPT, current_mfd_focus, FALSE);

		break;
	}

	return TRUE;
}

static int set_waypoint_type(mfd_push_button_types page, mfd_button_labels btn)
{
	int b;

	apache_coordinate_points
		*wp,
		*new_wp;

	wp = new_wp = get_apache_tsd_show_waypoint_review(current_mfd_focus);

	for (b = BTN_L4; b <= BTN_L6; b++)
		button_label_decorations[current_mfd_focus][b].boxed = 0;

	button_label_decorations[current_mfd_focus][btn].boxed = 3;

	if (btn == BTN_L6)
	{
		if (!wp || wp->type != 'C')
			new_wp = get_next_free_control_measure_point();
	}
	else if (!wp || wp->type != 'W')
		new_wp = get_next_free_waypoint();

	if (wp && new_wp && new_wp != wp)
	{
		strcpy(new_wp->free_text, wp->free_text);
		new_wp->position = wp->position;
	}

	if (wp != new_wp)
		set_apache_tsd_show_waypoint_review(current_mfd_focus, new_wp);

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// weapon page

static int set_mfd_weapon_mode(mfd_push_button_types page, mfd_button_labels btn)
{
	mfd_modes mode = MFD_MODE_WEAPON + (btn - BTN_M);

	if (mode == get_apache_current_mfd_mode(current_mfd_focus))
		mode = MFD_MODE_WEAPON;  // return to main weapons page

	select_apache_mfd_mode(mode, current_mfd_focus);

	return TRUE;
}

static int set_burst_limit(mfd_push_button_types page, mfd_button_labels btn)
{
	switch (page)
	{
	case MFD_BUTTON_GUN_BURST_10:
		set_gun_burst_size(10);
		break;
	case MFD_BUTTON_GUN_BURST_20:
		set_gun_burst_size(20);
		break;
	case MFD_BUTTON_GUN_BURST_50:
		set_gun_burst_size(50);
		break;
	case MFD_BUTTON_GUN_BURST_100:
		set_gun_burst_size(100);
		break;
	case MFD_BUTTON_GUN_BURST_ALL:
		set_gun_burst_size(0);
		break;
	default:
		ASSERT(FALSE);
		break;
	}

	return TRUE;
}

static int button_toggle_gun_mode(mfd_push_button_types page, mfd_button_labels btn)
{
	toggle_gun_mode();

	return TRUE;
}

static int set_rocket_salvo_size(mfd_push_button_types page, mfd_button_labels btn)
{
	if (page == MFD_BUTTON_RKT_QTY)
		set_apache_mfd_sub_mode(current_mfd_focus, 1);
	else
	{
		switch (page)
		{
		case MFD_BUTTON_RKT_QTY_1:
			rocket_salvo_size = 1;
			break;
		case MFD_BUTTON_RKT_QTY_2:
			rocket_salvo_size = 2;
			break;
		case MFD_BUTTON_RKT_QTY_4:
			rocket_salvo_size = 4;
			break;
		case MFD_BUTTON_RKT_QTY_8:
			rocket_salvo_size = 8;
			break;
		case MFD_BUTTON_RKT_QTY_12:
			rocket_salvo_size = 12;
			break;
		case MFD_BUTTON_RKT_QTY_24:
			rocket_salvo_size = 24;
			break;
		case MFD_BUTTON_RKT_QTY_ALL:
			rocket_salvo_size = 38;
			break;
		}

		set_apache_mfd_sub_mode(current_mfd_focus, 0);
	}

	setup_apache_mfd_buttons(MFD_MODE_WEAPON_RKT, current_mfd_focus, TRUE);

	return TRUE;
}

static int select_rocket_zone(mfd_push_button_types page, mfd_button_labels btn)
{
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// checklist page

static int set_new_checklist_page(mfd_push_button_types page, mfd_button_labels btn)
{
	switch (page)
	{
	case MFD_BUTTON_CHECKLIST_THROUGH_FLIGHT:
	case MFD_BUTTON_CHECKLIST_PERF_DATA1:
	case MFD_BUTTON_CHECKLIST_PERF_DATA2:
		{
			mfd_modes mode = MFD_MODE_CHECKLIST_THROUGH_FLIGHT;

			if (page == MFD_BUTTON_CHECKLIST_PERF_DATA1)
				mode = MFD_MODE_CHECKLIST_PERF_DATA1;
			else if (page == MFD_BUTTON_CHECKLIST_PERF_DATA2)
				mode = MFD_MODE_CHECKLIST_PERF_DATA2;

			// repressing button takes you back to main checklist page
			if (get_apache_current_mfd_mode(current_mfd_focus) == mode)
				mode = MFD_MODE_CHECKLIST;

			select_apache_mfd_mode(mode, current_mfd_focus);

			break;
		}
	default:
		ASSERT(FALSE);
		return FALSE;
	}

	return TRUE;
}


static int set_new_checklist_sub_page(mfd_push_button_types page, mfd_button_labels btn)
{
	int current_sub_mode = get_apache_mfd_sub_mode(current_mfd_focus);

	// repressing buttons takes you back to main page
	if (page == current_sub_mode)
		page = 0;
	// other buttons are disable except from main page
	else if (current_sub_mode != 0)
		return FALSE;

	set_apache_mfd_sub_mode(current_mfd_focus, page);
	setup_apache_mfd_buttons(get_apache_current_mfd_mode(current_mfd_focus), current_mfd_focus, TRUE);
#if 0
	case MFD_BUTTON_CHECKLIST_AFTER_STARTING_APU:
	case MFD_BUTTON_CHECKLIST_BEFORE_STARTING_ENG:
	case MFD_BUTTON_CHECKLIST_STARTING_ENG:
	case MFD_BUTTON_CHECKLIST_BEFORE_TAXI:
	case MFD_BUTTON_CHECKLIST_TAXI:
	case MFD_BUTTON_CHECKLIST_BEFORE_TO:
	case MFD_BUTTON_CHECKLIST_BEFORE_LANDING:
	case MFD_BUTTON_CHECKLIST_AFTER_LANDING:
	case MFD_BUTTON_CHECKLIST_ENGINE_SHUTDOWN:
	case MFD_BUTTON_CHECKLIST_RAPID_REFUELING:
	case MFD_BUTTON_CHECKLIST_RAPID_REARMING:
	case MFD_BUTTON_CHECKLIST_FCR_OPR_CHECK:
	case MFD_BUTTON_CHECKLIST_PILOT_IHADDS_BORE:
	case MFD_BUTTON_CHECKLIST_FLIR_OPR_CHECK:
	case MFD_BUTTON_CHECKLIST_MANUAL_DRIFT_NULL:
	case MFD_BUTTON_CHECKLIST_PECHAN_REALLIGN:
	case MFD_BUTTON_CHECKLIST_CUE_UPDATE_PROC:
	case MFD_BUTTON_CHECKLIST_TADS_OPR_CHECK:
	case MFD_BUTTON_CHECKLIST_TADS_OUTFR_BORE:
	case MFD_BUTTON_CHECKLIST_FLIGHT_CONTROL:
		break;
#endif

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// flight page

static int toggle_datum_adjust(mfd_push_button_types page, mfd_button_labels btn)
{
	if (mfd_button_handlers[current_mfd_focus][BTN_L3])
	{
		mfd_button_handlers[current_mfd_focus][BTN_L3] = NULL;
		mfd_button_handlers[current_mfd_focus][BTN_L4] = NULL;
//		button_label_decorations[BTN_L5].boxed = FALSE;
	}
	else
	{
		mfd_push_button** handler = mfd_button_handlers[current_mfd_focus];
		handler[BTN_L3] = &mfd_push_button_definitions[MFD_BUTTON_UP_ARROW];
		handler[BTN_L4] = &mfd_push_button_definitions[MFD_BUTTON_DOWN_ARROW];
//		button_label_decorations[BTN_L5].boxed = TRUE;
	}

	return TRUE;
}

static int adjust_pitch_datum(mfd_push_button_types page, mfd_button_labels btn)
{
	float adjust = 0.01;

	if (page == MFD_BUTTON_DOWN_ARROW)
		adjust = -adjust;

	adjust_apache_pitch_ladder_datum_position(adjust);

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// fuel page

static int set_fuel_transfer_mode(mfd_push_button_types page, mfd_button_labels btn)
{
	if (page == MFD_BUTTON_FUEL_TRANS_XFER_AUTO)
	{
		set_auto_fuel_transfer(FALSE);
		return TRUE;
	}
	else if (page == MFD_BUTTON_FUEL_TRANS_XFER_MAN)
	{
		set_auto_fuel_transfer(TRUE);
		return TRUE;
	}

	set_auto_fuel_transfer(FALSE);
	if (page == MFD_BUTTON_FUEL_TRANS_FWD)
	{
		set_fuel_transfer(FUEL_TANK_FWD, FUEL_TANK_NONE);
		set_fuel_transfer(FUEL_TANK_AFT, FUEL_TANK_FWD);
	}
	else if (page == MFD_BUTTON_FUEL_TRANS_AFT)
	{
		set_fuel_transfer(FUEL_TANK_FWD, FUEL_TANK_AFT);
		set_fuel_transfer(FUEL_TANK_AFT, FUEL_TANK_NONE);
	}
	else
	{
		set_fuel_transfer(FUEL_TANK_FWD, FUEL_TANK_NONE);
		set_fuel_transfer(FUEL_TANK_AFT, FUEL_TANK_NONE);
	}

	return TRUE;
}

static int set_fuel_crossfeed(mfd_push_button_types page, mfd_button_labels btn)
{
	if (page == MFD_BUTTON_FUEL_CROSS_FWD)
	{
		set_feeding_tank(1, FUEL_TANK_FWD);
		set_feeding_tank(2, FUEL_TANK_FWD);
	}
	else if (page == MFD_BUTTON_FUEL_CROSS_AFT)
	{
		set_feeding_tank(1, FUEL_TANK_AFT);
		set_feeding_tank(2, FUEL_TANK_AFT);
	}
	else
	{
		set_feeding_tank(1, FUEL_TANK_FWD);
		set_feeding_tank(2, FUEL_TANK_AFT);
	}

	return TRUE;
}

static int set_fuel_type(mfd_push_button_types page, mfd_button_labels btn)
{
	return TRUE;
}

static int toggle_fuel_booster(mfd_push_button_types page, mfd_button_labels btn)
{
	set_fuel_booster_pump_status(!get_fuel_booster_pump_status());

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Radar page

static int zoom_display(mfd_push_button_types page, mfd_button_labels btn)
{
	if (get_apache_current_mfd_mode(current_mfd_focus) == MFD_MODE_TSD)
		toggle_apache_tsd_zoom(current_mfd_focus);
	else if (get_apache_current_mfd_mode(current_mfd_focus) == MFD_MODE_GROUND_RADAR)
	{
		if (button_label_decorations[current_mfd_focus][BTN_R1].boxed)
			set_radar_zoomed(FALSE);
		else
			set_radar_zoomed(TRUE);
	}

	return TRUE;
}

static int pan_radar_scan(mfd_push_button_types page, mfd_button_labels btn)
{
	if (page == MFD_BUTTON_LEFT_ARROW)
		rotate_radar_scan_datum(-APACHE_GROUND_RADAR_SCAN_DATUM_ROTATE_STEP);
	else
		rotate_radar_scan_datum(APACHE_GROUND_RADAR_SCAN_DATUM_ROTATE_STEP);

	return TRUE;
}

static int select_radar_next_target_to_shoot(mfd_push_button_types page, mfd_button_labels btn)
{
	if (target_acquisition_system == TARGET_ACQUISITION_SYSTEM_GROUND_RADAR)
		get_next_ground_radar_target();

	return TRUE;
}

static int radar_function(mfd_push_button_types page, mfd_button_labels btn)
{
	toggle_apache_c_scope();

	return TRUE;
}

static int set_terrain_sensivity_sub_page(mfd_push_button_types page, mfd_button_labels btn)
{
	set_apache_mfd_sub_mode(current_mfd_focus, 2);

	return TRUE;
}

static int select_terrain_sensivity_option(mfd_push_button_types page, mfd_button_labels btn)
{
	unsigned sensivity;

	if (page == MFD_BUTTON_FCR_TERRAIN_SENSIVITY_AUTO)
		sensivity = 0;
	else
		sensivity = page - MFD_BUTTON_FCR_TERRAIN_SENSIVITY_1 + 1;

	set_radar_terrain_sensivity(sensivity);

	set_apache_mfd_sub_mode(current_mfd_focus, 1);

	return TRUE;
}

/*
static int toggle_auto_scan_pan(mfd_push_button_types page, mfd_button_labels btn)
{
	toggle_radar_auto_pan_scan_datum();

	return TRUE;
}
*/

static int change_radar_state(mfd_push_button_types page, mfd_button_labels btn)
{
	if (page == MFD_BUTTON_FCR_FCR)
		toggle_fcr_power();
	else if (page == MFD_BUTTON_FCR_RFI)
		toggle_rfi_power();
	else if (page == MFD_BUTTON_FCR_RFI_MODE_HOSTILE || page == MFD_BUTTON_FCR_RFI_MODE_ALL)
		toggle_rfi_show_hostile_only();
	else
		toggle_radar_mma_pinned();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// TPM page

static int select_tpm_sub_menu(mfd_push_button_types page, mfd_button_labels btn)
{
	if (page == MFD_BUTTON_TPM_PROF)
		set_apache_mfd_sub_mode(current_mfd_focus, 4);
	else if (page == MFD_BUTTON_TPM_LINES)
		set_apache_mfd_sub_mode(current_mfd_focus, 5);
	else if (page == MFD_BUTTON_TPM_CLEARANCE)
		set_apache_mfd_sub_mode(current_mfd_focus, 6);

	return TRUE;
}

static int select_tpm_prof_option(mfd_push_button_types page, mfd_button_labels btn)
{
	radar_tpm_profile_modes mode = RADAR_TPM_PROFILE_GEOM;

	if (page == MFD_BUTTON_TPM_PROF_ARITH)
		mode = RADAR_TPM_PROFILE_ARITH;
	else if (page == MFD_BUTTON_TPM_PROF_TEST)
		mode = RADAR_TPM_PROFILE_TEST;

	set_tpm_profile_mode(mode);

	set_apache_mfd_sub_mode(current_mfd_focus, 0);

	return TRUE;
}

static int select_tpm_lines_option(mfd_push_button_types page, mfd_button_labels btn)
{
	unsigned lines = page - MFD_BUTTON_TPM_LINES_0;

	set_tpm_profile_lines(lines);

	set_apache_mfd_sub_mode(current_mfd_focus, 0);

	return TRUE;
}

static int select_tpm_clearance_option(mfd_push_button_types page, mfd_button_labels btn)
{
	float clr = 20;

	if (page == MFD_BUTTON_TPM_CLEARANCE_50)
		clr = 50;
	else if (page == MFD_BUTTON_TPM_CLEARANCE_100)
		clr = 100;
	else if (page == MFD_BUTTON_TPM_CLEARANCE_200)
		clr = 200;

	set_tpm_clearance_height(feet_to_metres(clr));

	set_apache_mfd_sub_mode(current_mfd_focus, 0);

	return TRUE;
}

static int toggle_tpm_far_near_mode(mfd_push_button_types page, mfd_button_labels btn)
{
	toggle_radar_tpm_far_near_mode();

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// ADF buttons

static int toggle_adf_on_off(mfd_push_button_types page, mfd_button_labels btn)
{
	toggle_adf_enabled();

	setup_apache_mfd_buttons(MFD_MODE_ADF, current_mfd_focus, TRUE);

	return TRUE;
}

static int toggle_adf_preset_page(mfd_push_button_types page, mfd_button_labels btn)
{
	int mode = get_apache_mfd_sub_mode(current_mfd_focus) == 0 ? 1 : 0;
	set_apache_mfd_sub_mode(current_mfd_focus, mode);

	setup_apache_mfd_buttons(MFD_MODE_ADF, current_mfd_focus, TRUE);

	return TRUE;
}

static int toggle_adf_mode(mfd_push_button_types page, mfd_button_labels btn)
{
	mfd_push_button** handler = mfd_button_handlers[current_mfd_focus];

	if (get_adf_mode() == ADF_MODE_ADF)
	{
		set_adf_mode(ADF_MODE_ANT);
		handler[BTN_R2] = &mfd_push_button_definitions[MFD_BUTTON_ADF_MODE_ANT];
	}
	else
	{
		set_adf_mode(ADF_MODE_ADF);
		handler[BTN_R2] = &mfd_push_button_definitions[MFD_BUTTON_ADF_MODE_ADF];
	}

	return TRUE;
}

static int select_adf_station(mfd_push_button_types page, mfd_button_labels btn)
{
	unsigned station = 0;
	unsigned current_station = get_apache_mfd_sub_page(current_mfd_focus);

	ASSERT(btn >= BTN_L1);

	if (btn <= BTN_L6)
		station = 1 + btn - BTN_L2;
	else
		station = 6 + btn - BTN_R2;

	if (current_station != station)
		set_apache_mfd_sub_page(current_mfd_focus, station);
	else
		set_apache_mfd_sub_page(current_mfd_focus, 0);

	return TRUE;
}

static int tune_selected_adf_station(mfd_push_button_types page, mfd_button_labels btn)
{
	unsigned ntransmitters;
	ndb_instrument_transmitter* trans = get_instrument_transmitters(&ntransmitters);
	int station = get_apache_mfd_sub_page(current_mfd_focus) - 1;

	if (station >= 0 && station <= ntransmitters)
	{
		set_current_adf_station(&trans[station]);
		set_apache_mfd_sub_page(current_mfd_focus, 0);
	}

	return TRUE;
}

static int select_adf_test_mode(mfd_push_button_types page, mfd_button_labels btn)
{
	set_adf_test_mode();

	return TRUE;
}

static int select_adf_emergency_freqency(mfd_push_button_types page, mfd_button_labels btn)
{
	if (page == MFD_BUTTON_ADF_500)
		set_current_adf_frequency(500000);
	else
		set_current_adf_frequency(2182000);

	return TRUE;
}

static int select_adf_last_freqency(mfd_push_button_types page, mfd_button_labels btn)
{
	swap_to_last_adf_frequency();

	return TRUE;
}

static int toggle_adf_tone_play(mfd_push_button_types page, mfd_button_labels btn)
{
	toggle_adf_tone();

	return TRUE;
}

static void handle_adf_freq_input(const char* input, mfd_locations location, mfd_modes mfd_mode)
{
	float freq;
	unsigned int_freq;

	if (!validate_float_input(input, location, mfd_mode, &freq, 100.0, 2200.0))
		return;

	// input is in kHz as a float, while we store it as unsigneds in Hz
	int_freq = (unsigned)(freq * 1000);

	if (get_apache_mfd_sub_mode(location) == 0)
		set_current_adf_frequency(int_freq);
	else
	{
		// set the frequency of the selected station
		int transmitter_no = get_apache_mfd_sub_page(location) - 1;
		unsigned ntransmitters;
		ndb_instrument_transmitter
			*selected,
			*transmitters = get_instrument_transmitters(&ntransmitters);

		if (transmitter_no < 0 || transmitter_no >= ntransmitters )
			return;

		selected = &transmitters[transmitter_no];
		selected->radio_frequency = int_freq;
		selected->transmitter = get_ndb_transmitter_from_frequency(int_freq);
	}
}

static void handle_adf_id_input(const char* input, mfd_locations location, mfd_modes mfd_mode)
{
	if (mfd_mode == get_apache_current_mfd_mode(location) && get_apache_mfd_sub_mode(location) == 1)
	{
		int transmitter_no = get_apache_mfd_sub_page(location) - 1;
		unsigned ntransmitters;
		ndb_instrument_transmitter
			*transmitters = get_instrument_transmitters(&ntransmitters);

		if (transmitter_no < 0 || transmitter_no >= ntransmitters )
			return;

		if (!validate_string_input(input, location, MFD_MODE_ADF, transmitters[transmitter_no].code, sizeof(transmitters[transmitter_no].code)))
			return;

		// TODO: code the actual morse code
		transmitters[transmitter_no].morse_code[0] = 0;
	}
}

static int get_adf_input(mfd_push_button_types page, mfd_button_labels btn)
{
	// on preset page we must have selected a station first
	if (get_apache_mfd_sub_mode(current_mfd_focus) == 1 && get_apache_mfd_sub_page(current_mfd_focus) == 0)
		return FALSE;

	if (page == MFD_BUTTON_ADF_FREQ)
		get_apache_keyboard_unit_input("FREQ kHz", current_mfd_focus, get_apache_current_mfd_mode(current_mfd_focus), handle_adf_freq_input);
	else if (page == MFD_BUTTON_ADF_ID)
		get_apache_keyboard_unit_input("IDENT", current_mfd_focus, get_apache_current_mfd_mode(current_mfd_focus), handle_adf_id_input);

	toggle_apache_keyboard_unit_active(TRUE);

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


static void decorate_checklist_buttons(mfd_locations location, int current_button)
{
	int btn;

	for (btn = BTN_L1; btn <= BTN_R6; btn++)
	{
		mfd_push_button* handler = mfd_button_handlers[location][btn];
		if (current_button && handler && handler != &mfd_push_button_definitions[current_button])
			button_label_decorations[location][btn].barriered = TRUE;
		else
			button_label_decorations[location][btn].barriered = FALSE;
	}
}

static void draw_menu_arrow(float width, float x, float y, rgb_colour fg_col, rgb_colour bg_col)
{
	draw_2d_mono_sprite (menu_arrow_mask, x + 0.5 * width, y, bg_col);
	draw_2d_mono_sprite (menu_arrow, x + 0.5 * width, y, fg_col);

	draw_2d_half_thick_line(x - 0.5 * width, y, x + 0.45 * width, y, fg_col);
}

static void render_rocket_inventory(rgb_colour fg_col)
{
	char
		buffer[64],
		*inner_pylons_warhead = NULL,
		*outer_pylons_warhead = NULL;


	entity_sub_types
		weapon_sub_type;

	int
		number,
		damaged;

	unsigned
		left_inner_pylons_quantity = 0,
		right_inner_pylons_quantity = 0,
		left_outer_pylons_quantity = 0,
		right_outer_pylons_quantity = 0;

	// EECH is currently limited to only one type of rocket per pod.  Change this code
	// if this limitation is removed
	if (get_local_entity_weapon_hardpoint_info (get_gunship_entity(),
		APACHE_LHS_INNER_PYLON, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON,
		&weapon_sub_type, &number, &damaged))
	{
		unsigned check_right = TRUE;

		if (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_HYDRA70_M255)  // really M247
		{
			inner_pylons_warhead = "PD";
			if (!damaged)
				left_inner_pylons_quantity += number;
		}
		else if (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_HYDRA70_M261)
		{
			inner_pylons_warhead = "MP";
			if (!damaged)
				left_inner_pylons_quantity += number;
		}
		else
			check_right = FALSE;

		if (check_right
			&& get_local_entity_weapon_hardpoint_info (get_gunship_entity(),
			APACHE_RHS_INNER_PYLON, weapon_sub_type,
			&weapon_sub_type, &number, &damaged))
		{
			if (!damaged)
				right_inner_pylons_quantity += number;
		}
	}

	if (get_local_entity_weapon_hardpoint_info (get_gunship_entity(),
		APACHE_LHS_OUTER_PYLON, ENTITY_SUB_TYPE_WEAPON_NO_WEAPON,
		&weapon_sub_type, &number, &damaged))
	{
		unsigned check_right = TRUE;

		if (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_HYDRA70_M255)  // really M247
		{
			outer_pylons_warhead = "PD";
			if (!damaged)
				left_outer_pylons_quantity += number;
		}
		else if (weapon_sub_type == ENTITY_SUB_TYPE_WEAPON_HYDRA70_M261)
		{
			outer_pylons_warhead = "MP";
			if (!damaged)
				left_outer_pylons_quantity += number;
		}
		else
			check_right = FALSE;

		if (check_right &&
			get_local_entity_weapon_hardpoint_info (get_gunship_entity(),
			APACHE_RHS_OUTER_PYLON, weapon_sub_type,
			&weapon_sub_type, &number, &damaged))
		{
			if (!damaged)
				right_outer_pylons_quantity += number;
		}
	}

	// centre zone for combined for all pods
	if (inner_pylons_warhead || outer_pylons_warhead)
	{
		number = 0;

		if (left_inner_pylons_quantity >= 3)
		{
			number += 3;
			left_inner_pylons_quantity -= 3;
		}
		else
		{
			number += left_inner_pylons_quantity;
			left_inner_pylons_quantity = 0;
		}

		if (right_inner_pylons_quantity >= 3)
		{
			number += 3;
			right_inner_pylons_quantity -= 3;
		}
		else
		{
			number += right_inner_pylons_quantity;
			right_inner_pylons_quantity = 0;
		}

		if (left_outer_pylons_quantity >= 3)
		{
			number += 3;
			left_outer_pylons_quantity -= 3;
		}
		else
		{
			number += left_outer_pylons_quantity;
			left_outer_pylons_quantity = 0;
		}

		if (right_outer_pylons_quantity >= 3)
		{
			number += 3;
			right_outer_pylons_quantity -= 3;
		}
		else
		{
			number += right_outer_pylons_quantity;
			right_outer_pylons_quantity = 0;
		}

		sprintf(buffer, "%s %d", inner_pylons_warhead ? inner_pylons_warhead : outer_pylons_warhead, number);

		set_2d_mono_font_position(-1.2, 0.0);
		set_mono_font_rel_position (0.0, -18.0);
		print_mono_font_string(buffer);
	}

	if (inner_pylons_warhead)
	{
		unsigned
			left_qty = min(4, left_inner_pylons_quantity),
			right_qty = min(4, right_inner_pylons_quantity);

		// quad:
		left_inner_pylons_quantity -= left_qty;
		right_inner_pylons_quantity -= right_qty;

		sprintf(buffer, "%s %d", inner_pylons_warhead, left_qty + right_qty);

		set_2d_mono_font_position(-1.2, 0.3);
		set_mono_font_rel_position (0.0, -18.0);
		print_mono_font_string(buffer);

		// perimiter
		sprintf(buffer, "%s %d", inner_pylons_warhead, left_inner_pylons_quantity + right_inner_pylons_quantity);

		set_2d_mono_font_position(-1.2, 0.6);
		set_mono_font_rel_position (0.0, -18.0);
		print_mono_font_string(buffer);
	}

	if (outer_pylons_warhead)
	{
		unsigned
			left_qty = min(4, left_outer_pylons_quantity),
			right_qty = min(4, right_outer_pylons_quantity);

		// quad:
		left_outer_pylons_quantity -= left_qty;
		right_outer_pylons_quantity -= right_qty;

		sprintf(buffer, "%s %d", outer_pylons_warhead, left_qty + right_qty);

		set_2d_mono_font_position(-1.2, -0.3);
		set_mono_font_rel_position (0.0, -18.0);
		print_mono_font_string(buffer);

		// perimiter
		sprintf(buffer, "%s %d", outer_pylons_warhead, left_outer_pylons_quantity + right_outer_pylons_quantity);

		set_2d_mono_font_position(-1.2, -0.6);
		set_mono_font_rel_position (0.0, -18.0);
		print_mono_font_string(buffer);
	}


	// line drawings
	draw_2d_half_thick_line(-1.2,  0.9, -0.85, 0.9, fg_col);

	draw_2d_half_thick_line(-0.85, 0.9, -0.85, 0.78, fg_col);
	draw_2d_half_thick_line(-0.85, 0.37, -0.85, 0.25, fg_col);

	draw_2d_half_thick_line(-0.95, 0.15, -0.85, 0.25, fg_col);
	draw_2d_half_thick_line(-0.95, 0.15, -0.85, 0.055, fg_col);

	draw_2d_half_thick_line(-0.85,-0.09, -0.85, 0.055, fg_col);
	draw_2d_half_thick_line(-0.85,-0.57, -0.85, -0.65, fg_col);

	draw_2d_half_thick_line(-1.2, -0.65, -0.85, -0.65, fg_col);

	print_vertical_mono_font_string(-0.85, 0.6, "INBD", -0.5, TRUE);
	print_vertical_mono_font_string(-0.85, -0.3, "OUTBD", -0.5, TRUE);
}

static void render_mode_specfic_buttons(mfd_modes mfd_mode, mfd_locations location, rgb_colour fg_col, rgb_colour bg_col)
{
	mfd_push_button** handler = mfd_button_handlers[location];
	unsigned sub_mode = get_apache_mfd_sub_mode(location);

	if (location == MFD_LOCATION_PILOT_RHS)
		debug_log("sub_mode: %d", sub_mode);

	switch (mfd_mode)
	{
	case MFD_MODE_TSD:
		{
			float tsd_range = get_apache_tsd_range(location);

			if (get_apache_tsd_phase_is_atk(location))
				handler[BTN_B1] = &mfd_push_button_definitions[MFD_BUTTON_PHASE_ATK];
			else
				handler[BTN_B1] = &mfd_push_button_definitions[MFD_BUTTON_PHASE_NAV];

			if (sub_mode == 0)
			{
				button_label_decorations[location][BTN_T4].boxed = get_apache_tsd_display_present_position_status(location);
				button_label_decorations[location][BTN_R3].boxed = get_apache_tsd_is_centered(location);
				button_label_decorations[location][BTN_R1].boxed = get_apache_tsd_is_zoomed(location);
				sprintf(button_label_decorations[location][BTN_R2].line2, "%.0f", tsd_range / 1000.0);
			}
			else if (sub_mode == 1)
			{
				button_label_decorations[location][BTN_T4].boxed = FALSE;
				button_label_decorations[location][BTN_R1].boxed = FALSE;
				button_label_decorations[location][BTN_R2].line2[0] = 0;
				button_label_decorations[location][BTN_R3].boxed = FALSE;

				draw_2d_half_thick_line(0.95, 0.6, 1.2, 0.6, fg_col);
				draw_2d_half_thick_line(0.95, -0.6, 1.2, -0.6, fg_col);
			}

			break;
		}
	case MFD_MODE_TSD_WPT:
		break;
	case MFD_MODE_TSD_RTE:
		{
			int
				i,
				first,
				current_waypoint_index;

			unsigned
				last_waypoint;

			apache_coordinate_points
				**route = get_current_apache_navigation_route(&last_waypoint, &current_waypoint_index);

			if (current_waypoint_index == -1)
				current_waypoint_index = 0;

			first = current_waypoint_index + tsd_waypoint_offset;

			if (first < 3 || first > last_waypoint)
			{
				first = min(3, last_waypoint);
				tsd_waypoint_offset = first - current_waypoint_index;
			}

			for (i=0; i<4; i++)
			{
				int index = first - i;
				if (index >= 0 && index <= last_waypoint)
				{
					apache_coordinate_points* wp = route[index];

					sprintf(button_label_decorations[location][BTN_R2 + i].line1, "%c%02d", wp->type, wp->number);
					strcpy(button_label_decorations[location][BTN_R2 + i].line2, wp->free_text);
					handler[BTN_R2 + i] = &mfd_push_button_definitions[MFD_BUTTON_TSD_WAYPOINT_SELECT];
				}
				else
					handler[BTN_R2 + i] = NULL;
			}

			break;
		}
	case MFD_MODE_FUEL:
		{
			mfd_button_labels btn;

			// boost pump
			button_label_decorations[location][BTN_R2].boxed = get_fuel_booster_pump_status() ? 3 : 0;

			// fuel transfer
			for (btn = BTN_L2; btn <= BTN_L4; btn++)
				button_label_decorations[location][btn].boxed = 0;

			if (!get_auto_fuel_transfer())
			{
				if (get_fuel_transfer(FUEL_TANK_AFT) == FUEL_TANK_FWD)
					button_label_decorations[location][BTN_L2].boxed = 3;
				else if (get_fuel_transfer(FUEL_TANK_FWD) == FUEL_TANK_AFT)
					button_label_decorations[location][BTN_L4].boxed = 3;
				else
					button_label_decorations[location][BTN_L3].boxed = 3;

				handler[BTN_L2] = &mfd_push_button_definitions[MFD_BUTTON_FUEL_TRANS_FWD];
				handler[BTN_L3] = &mfd_push_button_definitions[MFD_BUTTON_FUEL_TRANS_OFF];
				handler[BTN_L4] = &mfd_push_button_definitions[MFD_BUTTON_FUEL_TRANS_AFT];
				handler[BTN_L5] = &mfd_push_button_definitions[MFD_BUTTON_FUEL_TRANS_XFER_MAN];
			}
			else
			{
				handler[BTN_L2] = handler[BTN_L3] = handler[BTN_L4] = NULL;
				handler[BTN_L5] = &mfd_push_button_definitions[MFD_BUTTON_FUEL_TRANS_XFER_AUTO];
			}

			// cross feed
			for (btn = BTN_R3; btn <= BTN_R5; btn++)
				button_label_decorations[location][btn].boxed = 0;

			if (get_feeding_tank(1) == FUEL_TANK_AFT)
				button_label_decorations[location][BTN_R5].boxed = 3;
			else if (get_feeding_tank(2) == FUEL_TANK_FWD)
				button_label_decorations[location][BTN_R3].boxed = 3;
			else  // NORM
				button_label_decorations[location][BTN_R4].boxed = 3;

			break;
		}
	case MFD_MODE_GROUND_RADAR:
	case MFD_MODE_AIR_RADAR:
		{
			int sub_mode = get_apache_mfd_sub_mode(location);
			int is_util_page = sub_mode >= 1 && sub_mode <= 3;
			clear_buttons(location, TRUE);

			handler[BTN_T1] = &mfd_push_button_definitions[MFD_BUTTON_C_SCP];
			button_label_decorations[location][BTN_T1].boxed = get_apache_c_scope_enabled() ? 3 : 0;
			handler[BTN_T6] = &mfd_push_button_definitions[MFD_BUTTON_UTIL];
			button_label_decorations[location][BTN_T6].boxed = is_util_page ? 3 : 0;
			show_acquisition_source[location] = FALSE;

			if (is_util_page)
			{
				handler[BTN_L2] = &mfd_push_button_definitions[MFD_BUTTON_FCR_RFI];
				handler[BTN_L3] = &mfd_push_button_definitions[MFD_BUTTON_FCR_FCR];

				if (sub_mode == 2)
				{
					handler[BTN_T6] = &mfd_push_button_definitions[MFD_BUTTON_FCR_TERRAIN_SENSIVITY_AUTO];
					button_label_decorations[location][BTN_T6].boxed = 0;

					handler[BTN_R1] = &mfd_push_button_definitions[MFD_BUTTON_FCR_TERRAIN_SENSIVITY_1];
					handler[BTN_R2] = &mfd_push_button_definitions[MFD_BUTTON_FCR_TERRAIN_SENSIVITY_2];
					handler[BTN_R3] = &mfd_push_button_definitions[MFD_BUTTON_FCR_TERRAIN_SENSIVITY_3];
					handler[BTN_R4] = &mfd_push_button_definitions[MFD_BUTTON_FCR_TERRAIN_SENSIVITY_4];
					handler[BTN_R5] = &mfd_push_button_definitions[MFD_BUTTON_FCR_TERRAIN_SENSIVITY_5];
					handler[BTN_R6] = &mfd_push_button_definitions[MFD_BUTTON_FCR_TERRAIN_SENSIVITY_6];
				}
				else
				{
					unsigned sensivity = get_radar_terrain_sensivity();

					if (get_rfi_show_hostile_only())
						handler[BTN_R2] = &mfd_push_button_definitions[MFD_BUTTON_FCR_RFI_MODE_HOSTILE];
					else
						handler[BTN_R2] = &mfd_push_button_definitions[MFD_BUTTON_FCR_RFI_MODE_ALL];
					handler[BTN_R4] = &mfd_push_button_definitions[MFD_BUTTON_FCR_PRIORITY_SCHEME];
					handler[BTN_R5] = &mfd_push_button_definitions[MFD_BUTTON_FCR_TERRAIN_SENSIVITY];
					if (get_radar_mma_pinned())
						handler[BTN_R6] = &mfd_push_button_definitions[MFD_BUTTON_FCR_MMA_PINNED];
					else
						handler[BTN_R6] = &mfd_push_button_definitions[MFD_BUTTON_FCR_MMA_NORM];

					if (sensivity == 0)
						strcpy(button_label_decorations[location][BTN_R5].line2, "AUTO");
					else
						sprintf(button_label_decorations[location][BTN_R5].line2, "%d", sensivity);
				}
			}
			else if (get_radar_mode() == RADAR_MODE_TPM)
			{
				if (sub_mode == 0)
				{
					handler[BTN_L1] = &mfd_push_button_definitions[MFD_BUTTON_TPM_PROF];
					handler[BTN_L2] = &mfd_push_button_definitions[MFD_BUTTON_TPM_LINES];
					sprintf(button_label_decorations[location][BTN_L1].line2, "%s", get_tpm_profile_mode_name());
					sprintf(button_label_decorations[location][BTN_L2].line2, " %d", get_tpm_profile_lines());

					handler[BTN_R1] = &mfd_push_button_definitions[MFD_BUTTON_TPM_CLEARANCE];
					if (get_radar_tpm_near_mode())
						handler[BTN_R2] = &mfd_push_button_definitions[MFD_BUTTON_ELEV_NEAR];
					else
						handler[BTN_R2] = &mfd_push_button_definitions[MFD_BUTTON_ELEV_FAR];
					sprintf(button_label_decorations[location][BTN_R1].line2, "%.0f", feet(get_tpm_clearance_height()));
				}
				else if (sub_mode == 4)
				{
					handler[BTN_L1] = &mfd_push_button_definitions[MFD_BUTTON_TPM_PROF_GEOM];
					handler[BTN_L2] = &mfd_push_button_definitions[MFD_BUTTON_TPM_PROF_ARITH];
					handler[BTN_L3] = &mfd_push_button_definitions[MFD_BUTTON_TPM_PROF_TEST];

					draw_2d_half_thick_line(-1.2, 0.9, -0.8, 0.9, fg_col);
					draw_2d_half_thick_line(-1.2, 0.0, -0.8, 0.0, fg_col);
					draw_2d_half_thick_line(-0.8, 0.9, -0.8, 0.0, fg_col);
				}
				else if (sub_mode == 5)
				{
					handler[BTN_L1] = &mfd_push_button_definitions[MFD_BUTTON_TPM_LINES_0];
					handler[BTN_L2] = &mfd_push_button_definitions[MFD_BUTTON_TPM_LINES_1];
					handler[BTN_L3] = &mfd_push_button_definitions[MFD_BUTTON_TPM_LINES_2];
					handler[BTN_L4] = &mfd_push_button_definitions[MFD_BUTTON_TPM_LINES_3];
					handler[BTN_L5] = &mfd_push_button_definitions[MFD_BUTTON_TPM_LINES_4];

					draw_2d_half_thick_line(-1.2, 0.9, -1.05, 0.9, fg_col);
					draw_2d_half_thick_line(-1.2,-0.6, -1.05,-0.6, fg_col);
					draw_2d_half_thick_line(-1.05, 0.9, -1.05,-0.6, fg_col);
				}
				else if (sub_mode == 6)
				{
					handler[BTN_R1] = &mfd_push_button_definitions[MFD_BUTTON_TPM_CLEARANCE_20];
					handler[BTN_R2] = &mfd_push_button_definitions[MFD_BUTTON_TPM_CLEARANCE_50];
					handler[BTN_R3] = &mfd_push_button_definitions[MFD_BUTTON_TPM_CLEARANCE_100];
					handler[BTN_R4] = &mfd_push_button_definitions[MFD_BUTTON_TPM_CLEARANCE_200];

					draw_2d_half_thick_line(1.2, 0.9, 0.95, 0.9, fg_col);
					draw_2d_half_thick_line(1.2,-0.3, 0.95,-0.3, fg_col);
					draw_2d_half_thick_line(0.95, 0.9, 0.95,-0.3, fg_col);
				}
			}
			else
			{
				handler[BTN_L1] = &mfd_push_button_definitions[MFD_BUTTON_NTS];
				handler[BTN_L2] = &mfd_push_button_definitions[MFD_BUTTON_LEFT_ARROW];
				handler[BTN_L4] = &mfd_push_button_definitions[MFD_BUTTON_TGT];
				handler[BTN_L5] = &mfd_push_button_definitions[MFD_BUTTON_ELEV_AUTO];

				handler[BTN_R1] = &mfd_push_button_definitions[MFD_BUTTON_ZOOM];
				handler[BTN_R2] = &mfd_push_button_definitions[MFD_BUTTON_RIGHT_ARROW];
				handler[BTN_R4] = &mfd_push_button_definitions[MFD_BUTTON_RF_HO];
				handler[BTN_R6] = &mfd_push_button_definitions[MFD_BUTTON_ACQ_SRC];
				show_acquisition_source[location] = TRUE;

				button_label_decorations[location][BTN_R1].boxed = get_radar_zoomed() ? 3 : 0;
				// TODO:
				button_label_decorations[location][BTN_L5].boxed = 2;
				button_label_decorations[location][BTN_R6].boxed = get_radar_auto_pan_scan_datum() ? 1 : 2;
			}

			break;
		}
	case MFD_MODE_WEAPON_GUN:
		{
			mfd_push_button_types mode = (get_gun_mode() == GUN_MODE_NORMAL) ? MFD_BUTTON_GUN_MODE_NORM : MFD_BUTTON_GUN_MODE_FXD;
			unsigned btn;

			for (btn = BTN_L1; btn <= BTN_L5; btn++)
				button_label_decorations[location][btn].boxed = 0;

			handler[BTN_R2] = &mfd_push_button_definitions[mode];

			switch (get_gun_burst_size())
			{
			case 10:
				btn = BTN_L1;
				break;
			case 20:
				btn = BTN_L2;
				break;
			case 50:
				btn = BTN_L3;
				break;
			case 100:
				btn = BTN_L4;
				break;
			default:
				ASSERT(FALSE);
			case 0:
				btn = BTN_L5;
				break;
			}

			button_label_decorations[location][btn].boxed = 3;

			break;
		}

	case MFD_MODE_WEAPON_RKT:
		{
			if (sub_mode == 1)
			{
				button_label_decorations[location][BTN_R2].line2[0] = 0;
			}
			else
				if (rocket_salvo_size <= 24)
					sprintf(button_label_decorations[location][BTN_R2].line2, "%d", rocket_salvo_size);
				else
					strcpy(button_label_decorations[location][BTN_R2].line2, "ALL");

			render_rocket_inventory(fg_col);

			break;
		}
	}

	if (show_acquisition_source[location])
	{
		if (show_acquisition_source_selection[location])
		{
			int btn;

			for (btn = BTN_R1; btn <= BTN_R6; btn++)
				button_label_decorations[location][BTN_R6].boxed = 0;
			button_label_decorations[location][BTN_B4].boxed = 0;
			button_label_decorations[location][BTN_B5].boxed = 0;

			handler[BTN_R1] = &mfd_push_button_definitions[MFD_BUTTON_ACQ_PHS];
			handler[BTN_R2] = &mfd_push_button_definitions[MFD_BUTTON_ACQ_GHS];
			handler[BTN_R3] = &mfd_push_button_definitions[MFD_BUTTON_ACQ_SKR];
			handler[BTN_R4] = &mfd_push_button_definitions[MFD_BUTTON_ACQ_RFI];
			handler[BTN_R5] = &mfd_push_button_definitions[MFD_BUTTON_ACQ_FCR];
			handler[BTN_R6] = &mfd_push_button_definitions[MFD_BUTTON_ACQ_FXD];
			handler[BTN_B5] = &mfd_push_button_definitions[MFD_BUTTON_ACQ_TADS];
			handler[BTN_B4] = &mfd_push_button_definitions[MFD_BUTTON_ACQ_WPT_TP];

			/*
			draw_2d_half_thick_line(1.2, 0.9, 0.9, 0.9, fg_col);
			draw_2d_half_thick_line(0.9, 0.9, 0.9, -1.0, fg_col);
			draw_2d_half_thick_line(0.9, 0.9, 0.9, -1.0, fg_col);
			draw_2d_half_thick_line(0.3, -1.0, 0.9, -1.0, fg_col);
			draw_2d_half_thick_line(0.3, -1.0, 0.3, -1.2, fg_col);
			*/
		}
		else //if (handler[BTN_R6] == &mfd_push_button_definitions[MFD_BUTTON_ACQ_SRC])
		{
			button_label_decorations[location][BTN_R6].boxed = 2;
			strcpy(button_label_decorations[location][BTN_R6].line2, get_apache_acquisition_source_abreviation());
		}
	}
}

void draw_apache_mfd_page_number_buttons(mfd_locations location, int backward, int forward)
{
	mfd_push_button** handler = mfd_button_handlers[location];

	// next/prev page buttons if necessary
	if (backward > 0)
		handler[BTN_R2] = &mfd_push_button_definitions[MFD_BUTTON_PAGE1 + backward - 1];
	else
		handler[BTN_R2] = NULL;

	if (forward)
		handler[BTN_R3] = &mfd_push_button_definitions[MFD_BUTTON_PAGE1 + forward - 1];
	else
		handler[BTN_R3] = NULL;
}

static mfd_button_labels get_clicked_button(void)
{
	if (pointer_position_x < -1.0 || pointer_position_x > 1.0)
	{
		float btn_limit = button_spacing * 3.0;
		mfd_button_labels btn, end_btn;

		if (pointer_position_y <= btn_limit)
		{
			btn_limit -= button_spacing;

			if (pointer_position_x > 1.0)
			{
				btn = BTN_R1;
				end_btn = BTN_R6;
			}
			else
			{
				btn = BTN_L1;
				end_btn = BTN_L6;
			}

			for (; btn <= end_btn; btn++, btn_limit -= button_spacing)
			{
				if (pointer_position_y > btn_limit)
					return btn;
			}
		}
	}
	else if (pointer_position_y < -1.0 || pointer_position_y > 1.0)
	{
		float btn_limit = button_spacing * -3.0;
		mfd_button_labels btn, end_btn;

		if (pointer_position_x >= btn_limit)
		{
			btn_limit += button_spacing;

			if (pointer_position_y > 1.0)
			{
				btn = BTN_T1;
				end_btn = BTN_T6;
			}
			else
			{
				btn = BTN_M;
				end_btn = BTN_B5;
			}

			for (; btn <= end_btn; btn++, btn_limit += button_spacing)
			{
				if (pointer_position_x < btn_limit)
					return btn;
			}
		}
	}

	// special buttons

	if (pointer_position_x < -1.1 && pointer_position_y < -1.1)
		return BTN_WPN;

	if (pointer_position_x < -1.0 && pointer_position_y < -0.9 && pointer_position_x < pointer_position_y)
		return BTN_FCR;

	if (pointer_position_x < -0.9 && pointer_position_y < -1.0 && pointer_position_y < pointer_position_x)
		return BTN_TSD;

	if (pointer_position_x > 1.1 && pointer_position_y < -1.1)
		return BTN_COM;

	if (pointer_position_x > 1.0 && pointer_position_y < -0.9 && -pointer_position_x < pointer_position_y)
		return BTN_VID;

	if (pointer_position_x > 0.9 && pointer_position_y < -1.0 && pointer_position_y < -pointer_position_x)
		return BTN_AC;

	return NO_BTN;
}

void clear_buttons(mfd_locations location, int clear_decorations)
{
	int i;
	for (i=0; i <= BTN_B5; i++)
	{
		mfd_button_handlers[location][i] = NULL;
		if (clear_decorations)
		{
			button_label_decorations[location][i].boxed = 0;
			button_label_decorations[location][i].barriered = FALSE;
			button_label_decorations[location][i].line1[0] = 0;
			button_label_decorations[location][i].line2[0] = 0;
		}
	}

	button_label_decorations[location][BTN_M].boxed = 3;
}

void initialise_apache_pushbuttons(void)
{
	mfd_locations loc;

	for (loc = MFD_LOCATION_PILOT_LHS; loc <= MFD_LOCATION_CPG_RHS; loc++)
		clear_buttons(loc, TRUE);

	current_mfd_focus = pilot_mfd_focus = MFD_LOCATION_PILOT_LHS;
	co_pilot_mfd_focus = MFD_LOCATION_CPG_LHS;
	waypoint_to_add = NULL;
}

void handle_apache_mfd_click(void)
{
	mfd_button_labels clicked_btn = get_clicked_button();

	if (clicked_btn <= BTN_B5)
	{
		mfd_push_button* handler = mfd_button_handlers[current_mfd_focus][clicked_btn];

		last_button_pressed = clicked_btn;

		if (handler && handler->push_function && !button_label_decorations[current_mfd_focus][clicked_btn].barriered)
		{
			int is_boxed = button_label_decorations[current_mfd_focus][clicked_btn].boxed;
			mfd_push_button_types btn_type = handler - mfd_push_button_definitions;
			int success = handler->push_function(btn_type, clicked_btn);

			if (success && handler->box_on_click)
			{
				if (is_boxed)
					button_label_decorations[current_mfd_focus][clicked_btn].boxed = 0;
				else
					button_label_decorations[current_mfd_focus][clicked_btn].boxed = 3;
			}
		}
		else if (clicked_btn == BTN_M)
			select_apache_mfd_mode(MFD_MODE_MENU, current_mfd_focus);
		last_button_pressed = NO_BTN;
	}
	else
	{
		mfd_modes mode = MFD_MODE_OFF;
		// special buttons remaining
		switch (clicked_btn)
		{
		case BTN_FCR:
			mode = MFD_MODE_GROUND_RADAR;
			break;
		case BTN_WPN:
			mode = MFD_MODE_WEAPON;
			break;
		case BTN_TSD:
			mode = MFD_MODE_TSD;
			break;
		case BTN_AC:
		case BTN_COM:
			break;
		case BTN_VID:
			mode = MFD_MODE_FLIR;
			break;
		}

		if (mode != MFD_MODE_OFF)
			select_apache_mfd_mode(mode, current_mfd_focus);
		else if (accepting_waypoint_input)
		{
			apache_coordinate_points* wpt = get_apache_clicked_point(current_mfd_focus, pointer_position_x, pointer_position_y, TRUE);
			select_waypoint(wpt);
		}
		else if (accepting_target)
		{

		}
		else if (accepting_coordinate_input)
		{
			apache_coordinate_points* wpt = get_apache_clicked_point(current_mfd_focus, pointer_position_x, pointer_position_y, FALSE);
			select_waypoint(wpt);
		}
	}
}

void setup_apache_mfd_buttons(mfd_modes mfd_mode, mfd_locations location, int is_sub_mode)
{
	mfd_push_button** handler = mfd_button_handlers[location];
	unsigned sub_mode = get_apache_mfd_sub_mode(location);

	ASSERT(location != MFD_LOCATION_ORT);

	clear_buttons(location, !is_sub_mode);
	if (!is_sub_mode)
		set_apache_mfd_sub_mode(location, 0);

	accepting_coordinate_input = accepting_waypoint_input = accepting_target = FALSE;
	waypoint_to_add = NULL;
	show_acquisition_source[location] = show_acquisition_source_selection[location] = FALSE;

	switch (mfd_mode)
	{
	case MFD_MODE_MENU:
		handler[BTN_T2] = &mfd_push_button_definitions[MFD_BUTTON_ASE];
		handler[BTN_T4] = &mfd_push_button_definitions[MFD_BUTTON_CL];
		handler[BTN_T5] = &mfd_push_button_definitions[MFD_BUTTON_VERS];

		handler[BTN_L1] = &mfd_push_button_definitions[MFD_BUTTON_ADF];
		handler[BTN_L6] = &mfd_push_button_definitions[MFD_BUTTON_WPN];

		handler[BTN_B1] = &mfd_push_button_definitions[MFD_BUTTON_DMS];
		handler[BTN_B2] = &mfd_push_button_definitions[MFD_BUTTON_ENG];  // uncertain
		handler[BTN_B3] = &mfd_push_button_definitions[MFD_BUTTON_FLT];  // unknown
		handler[BTN_B4] = &mfd_push_button_definitions[MFD_BUTTON_FUEL]; // uncertain
		handler[BTN_B5] = &mfd_push_button_definitions[MFD_BUTTON_PERF]; // unknown

		break;
	case MFD_MODE_GROUND_RADAR:
	case MFD_MODE_AIR_RADAR:

		break;
	case MFD_MODE_TSD:
		{
			handler[BTN_T1] = &mfd_push_button_definitions[MFD_BUTTON_RPT];
			handler[BTN_T2] = &mfd_push_button_definitions[MFD_BUTTON_ASE];
//				handler[BTN_T3] = &mfd_push_button_definitions[MFD_BUTTON_PSN];
			handler[BTN_T4] = &mfd_push_button_definitions[MFD_BUTTON_PP];
			handler[BTN_T5] = &mfd_push_button_definitions[MFD_BUTTON_COORD];
			handler[BTN_T6] = &mfd_push_button_definitions[MFD_BUTTON_TSD_UTIL];

			handler[BTN_L1] = &mfd_push_button_definitions[MFD_BUTTON_ADF];
//				handler[BTN_L2] = &mfd_push_button_definitions[MFD_BUTTON_HDG];
//				handler[BTN_L4] = &mfd_push_button_definitions[MFD_BUTTON_REC];
			handler[BTN_L5] = &mfd_push_button_definitions[MFD_BUTTON_JAM];
			handler[BTN_L6] = &mfd_push_button_definitions[MFD_BUTTON_SHOW];

			if (sub_mode == 1)
			{
				handler[BTN_R2] = &mfd_push_button_definitions[MFD_BUTTON_TSD_SCALE_50];
				handler[BTN_R3] = &mfd_push_button_definitions[MFD_BUTTON_TSD_SCALE_25];
				handler[BTN_R4] = &mfd_push_button_definitions[MFD_BUTTON_TSD_SCALE_10];
				handler[BTN_R5] = &mfd_push_button_definitions[MFD_BUTTON_TSD_SCALE_5];
			}
			else
			{
				handler[BTN_R1] = &mfd_push_button_definitions[MFD_BUTTON_ZOOM];
				handler[BTN_R2] = &mfd_push_button_definitions[MFD_BUTTON_SC];
				handler[BTN_R3] = &mfd_push_button_definitions[MFD_BUTTON_CTR];
				handler[BTN_R5] = &mfd_push_button_definitions[MFD_BUTTON_FRZ];
				handler[BTN_R6] = &mfd_push_button_definitions[MFD_BUTTON_ACQ_SRC];
				show_acquisition_source[location] = TRUE;
			}

			handler[BTN_M] = &mfd_push_button_definitions[MFD_BUTTON_MENU_TSD];
			handler[BTN_B2] = &mfd_push_button_definitions[MFD_BUTTON_ZN];
			handler[BTN_B3] = &mfd_push_button_definitions[MFD_BUTTON_WPT];
			handler[BTN_B4] = &mfd_push_button_definitions[MFD_BUTTON_RTE];
			handler[BTN_B5] = &mfd_push_button_definitions[MFD_BUTTON_THRT];

			break;
		}
	case MFD_MODE_TSD_RTE:
		{
			unsigned i;

			handler[BTN_T5] = &mfd_push_button_definitions[MFD_BUTTON_COORD];
			handler[BTN_T6] = &mfd_push_button_definitions[MFD_BUTTON_TSD_UTIL];

			handler[BTN_L1] = &mfd_push_button_definitions[MFD_BUTTON_POINT_INPUT];
			handler[BTN_L2] = &mfd_push_button_definitions[MFD_BUTTON_ADD];
			handler[BTN_L3] = &mfd_push_button_definitions[MFD_BUTTON_DEL];
			handler[BTN_L4] = &mfd_push_button_definitions[MFD_BUTTON_RTE_DIR];
			handler[BTN_L5] = &mfd_push_button_definitions[MFD_BUTTON_RTE_RVW];
			handler[BTN_L6] = &mfd_push_button_definitions[MFD_BUTTON_RTE_RTM];

			handler[BTN_R1] = &mfd_push_button_definitions[MFD_BUTTON_UP];
			handler[BTN_R6] = &mfd_push_button_definitions[MFD_BUTTON_DOWN];

			for (i=BTN_R1; i <= BTN_R6; i++)
				button_label_decorations[location][i].barriered = TRUE;

			handler[BTN_B2] = &mfd_push_button_definitions[MFD_BUTTON_ZN];
			handler[BTN_B3] = &mfd_push_button_definitions[MFD_BUTTON_WPT];
			handler[BTN_B4] = &mfd_push_button_definitions[MFD_BUTTON_RTE];
			handler[BTN_B5] = &mfd_push_button_definitions[MFD_BUTTON_THRT];
			button_label_decorations[location][BTN_B4].boxed = 3;

			handler[BTN_M] = &mfd_push_button_definitions[MFD_BUTTON_MENU_TSD];

			tsd_waypoint_offset = 3;
			set_apache_tsd_show_waypoint_review(current_mfd_focus, NULL);

			break;
		}
	case MFD_MODE_TSD_WPT:
		{
			handler[BTN_T5] = &mfd_push_button_definitions[MFD_BUTTON_COORD];
			handler[BTN_T6] = &mfd_push_button_definitions[MFD_BUTTON_TSD_UTIL];

			handler[BTN_L1] = &mfd_push_button_definitions[MFD_BUTTON_POINT_INPUT];
			handler[BTN_L2] = &mfd_push_button_definitions[MFD_BUTTON_ADD];
			handler[BTN_L3] = &mfd_push_button_definitions[MFD_BUTTON_DEL];
			handler[BTN_L4] = &mfd_push_button_definitions[MFD_BUTTON_EDT];
			handler[BTN_L5] = &mfd_push_button_definitions[MFD_BUTTON_STO];
			handler[BTN_L6] = &mfd_push_button_definitions[MFD_BUTTON_XMIT];

			handler[BTN_B2] = &mfd_push_button_definitions[MFD_BUTTON_ZN];
			handler[BTN_B3] = &mfd_push_button_definitions[MFD_BUTTON_WPT];
			handler[BTN_B4] = &mfd_push_button_definitions[MFD_BUTTON_RTE];
			handler[BTN_B5] = &mfd_push_button_definitions[MFD_BUTTON_THRT];
			button_label_decorations[location][BTN_B3].boxed = 3;

			handler[BTN_M] = &mfd_push_button_definitions[MFD_BUTTON_MENU_TSD];
			set_apache_tsd_show_waypoint_review(current_mfd_focus, NULL);

			accepting_coordinate_input = TRUE;

			break;
		}
	case MFD_MODE_WEAPON:
	case MFD_MODE_WEAPON_GUN:
	case MFD_MODE_WEAPON_MSL:
	case MFD_MODE_WEAPON_ATA:
	case MFD_MODE_WEAPON_RKT:
	{
			unsigned i;

			handler[BTN_T1] = &mfd_push_button_definitions[MFD_BUTTON_CHAN];
			handler[BTN_T2] = &mfd_push_button_definitions[MFD_BUTTON_ASE];
			handler[BTN_T4] = &mfd_push_button_definitions[MFD_BUTTON_CODE];
			handler[BTN_T5] = &mfd_push_button_definitions[MFD_BUTTON_COORD];
			handler[BTN_T6] = &mfd_push_button_definitions[MFD_BUTTON_UTIL];

			handler[BTN_R5] = &mfd_push_button_definitions[MFD_BUTTON_LRFD_LAST];
			handler[BTN_R6] = &mfd_push_button_definitions[MFD_BUTTON_ACQ_SRC];
			show_acquisition_source[location] = TRUE;

			handler[BTN_M] = &mfd_push_button_definitions[MFD_BUTTON_MENU_WPN];
			handler[BTN_B1] = &mfd_push_button_definitions[MFD_BUTTON_GUN];
			handler[BTN_B2] = &mfd_push_button_definitions[MFD_BUTTON_MSL];
			handler[BTN_B3] = &mfd_push_button_definitions[MFD_BUTTON_ATA];
			handler[BTN_B4] = &mfd_push_button_definitions[MFD_BUTTON_RKT];
			handler[BTN_B5] = &mfd_push_button_definitions[MFD_BUTTON_MANRNG_INPUT];

			for (i=BTN_B1; i <= BTN_B5; i++)
				button_label_decorations[location][i].boxed = 0;

			switch (mfd_mode)
			{
			case MFD_MODE_WEAPON:
				break;
			case MFD_MODE_WEAPON_GUN:
				handler[BTN_L1] = &mfd_push_button_definitions[MFD_BUTTON_GUN_BURST_10];
				handler[BTN_L2] = &mfd_push_button_definitions[MFD_BUTTON_GUN_BURST_20];
				handler[BTN_L3] = &mfd_push_button_definitions[MFD_BUTTON_GUN_BURST_50];
				handler[BTN_L4] = &mfd_push_button_definitions[MFD_BUTTON_GUN_BURST_100];
				handler[BTN_L5] = &mfd_push_button_definitions[MFD_BUTTON_GUN_BURST_ALL];

				button_label_decorations[location][BTN_B1].boxed = 3;

				break;
			case MFD_MODE_WEAPON_MSL:
				button_label_decorations[location][BTN_B2].boxed = 3;

				break;
			case MFD_MODE_WEAPON_ATA:
				button_label_decorations[location][BTN_B3].boxed = 3;

				break;
			case MFD_MODE_WEAPON_RKT:
				handler[BTN_L1] = &mfd_push_button_definitions[MFD_BUTTON_RKT_ZONE_PERIMITER];
				handler[BTN_L2] = &mfd_push_button_definitions[MFD_BUTTON_RKT_ZONE_QUAD];
				handler[BTN_L3] = &mfd_push_button_definitions[MFD_BUTTON_RKT_ZONE_CTR];
				handler[BTN_L4] = &mfd_push_button_definitions[MFD_BUTTON_RKT_ZONE_QUAD];
				handler[BTN_L5] = &mfd_push_button_definitions[MFD_BUTTON_RKT_ZONE_PERIMITER];

				if (sub_mode == 1)
				{
					handler[BTN_R1] = &mfd_push_button_definitions[MFD_BUTTON_RKT_QTY_1];
					handler[BTN_R2] = &mfd_push_button_definitions[MFD_BUTTON_RKT_QTY_2];
					handler[BTN_R3] = &mfd_push_button_definitions[MFD_BUTTON_RKT_QTY_4];
					handler[BTN_R4] = &mfd_push_button_definitions[MFD_BUTTON_RKT_QTY_8];
					handler[BTN_R5] = &mfd_push_button_definitions[MFD_BUTTON_RKT_QTY_12];
					handler[BTN_R6] = &mfd_push_button_definitions[MFD_BUTTON_RKT_QTY_24];
					handler[BTN_B5] = &mfd_push_button_definitions[MFD_BUTTON_RKT_QTY_ALL];

					show_acquisition_source[location] = FALSE;
					button_label_decorations[location][BTN_R6].line2[0] = 0;
					button_label_decorations[location][BTN_R6].boxed = 0;
				}
				else
					handler[BTN_R2] = &mfd_push_button_definitions[MFD_BUTTON_RKT_QTY];

				button_label_decorations[location][BTN_B4].boxed = 3;

				break;
			}

			if (show_acquisition_source[location])
				button_label_decorations[location][BTN_R6].boxed = 2;

			break;
		}
	case MFD_MODE_ENGINE:
		handler[BTN_T2] = &mfd_push_button_definitions[MFD_BUTTON_FLT];
		handler[BTN_T3] = &mfd_push_button_definitions[MFD_BUTTON_FUEL];
		handler[BTN_T4] = &mfd_push_button_definitions[MFD_BUTTON_PERF];
		handler[BTN_T6] = &mfd_push_button_definitions[MFD_BUTTON_UTIL];

		handler[BTN_M] = &mfd_push_button_definitions[MFD_BUTTON_MENU_ENG];
		handler[BTN_B1] = &mfd_push_button_definitions[MFD_BUTTON_SYS];
		handler[BTN_B2] = &mfd_push_button_definitions[MFD_BUTTON_ETF];
		handler[BTN_B5] = &mfd_push_button_definitions[MFD_BUTTON_WCA];

		// TODO show correct acquistion source, not always fixed
		handler[BTN_R6] = &mfd_push_button_definitions[MFD_BUTTON_ACQ_FXD];
		show_acquisition_source[location] = TRUE;
		//button_label_decorations[location][BTN_R6].boxed = 2;

		break;
	case MFD_MODE_FLIGHT:
		handler[BTN_T1] = &mfd_push_button_definitions[MFD_BUTTON_ENG];
		handler[BTN_T3] = &mfd_push_button_definitions[MFD_BUTTON_FUEL];
		handler[BTN_T4] = &mfd_push_button_definitions[MFD_BUTTON_PERF];
		handler[BTN_T6] = &mfd_push_button_definitions[MFD_BUTTON_UTIL];

		handler[BTN_L5] = &mfd_push_button_definitions[MFD_BUTTON_PITCH_W];

		handler[BTN_M] = &mfd_push_button_definitions[MFD_BUTTON_MENU_FLT];
		handler[BTN_B5] = &mfd_push_button_definitions[MFD_BUTTON_SET];

		break;
	case MFD_MODE_FUEL:
		handler[BTN_T1] = &mfd_push_button_definitions[MFD_BUTTON_ENG];
		handler[BTN_T2] = &mfd_push_button_definitions[MFD_BUTTON_FLT];
		handler[BTN_T3] = &mfd_push_button_definitions[MFD_BUTTON_FUEL];
		button_label_decorations[location][BTN_T3].boxed = 3;
		handler[BTN_T4] = &mfd_push_button_definitions[MFD_BUTTON_PERF];
		handler[BTN_T6] = &mfd_push_button_definitions[MFD_BUTTON_UTIL];

#ifdef EXTERNAL_TANKS
		handler[BTN_L1] = &mfd_push_button_definitions[MFD_BUTTON_L_AUX];
		handler[BTN_R1] = &mfd_push_button_definitions[MFD_BUTTON_R_AUX];
		handler[BTN_L6] = &mfd_push_button_definitions[MFD_BUTTON_AUX_GAL];
#endif

		handler[BTN_R2] = &mfd_push_button_definitions[MFD_BUTTON_BOOST];
		handler[BTN_R3] = &mfd_push_button_definitions[MFD_BUTTON_FUEL_CROSS_FWD];
		handler[BTN_R4] = &mfd_push_button_definitions[MFD_BUTTON_FUEL_CROSS_NORM];
		handler[BTN_R5] = &mfd_push_button_definitions[MFD_BUTTON_FUEL_CROSS_AFT];
		handler[BTN_R6] = &mfd_push_button_definitions[MFD_BUTTON_FUEL_TYPE];
		strcpy(button_label_decorations[location][BTN_R6].line2, "JP8");

		handler[BTN_M] = &mfd_push_button_definitions[MFD_BUTTON_MENU_FUEL];
		handler[BTN_B5] = &mfd_push_button_definitions[MFD_BUTTON_CL];

		button_label_decorations[location][BTN_L5].boxed = 2;
		button_label_decorations[location][BTN_R6].boxed = 2;
		break;
	case MFD_MODE_CHECKLIST:
	case MFD_MODE_CHECKLIST_THROUGH_FLIGHT:
	{
		int current_sub_mode = get_apache_mfd_sub_mode(location);

		handler[BTN_T3] = &mfd_push_button_definitions[MFD_BUTTON_CHECKLIST_THROUGH_FLIGHT];
		handler[BTN_T4] = &mfd_push_button_definitions[MFD_BUTTON_CHECKLIST_PERF_DATA1];
		handler[BTN_T5] = &mfd_push_button_definitions[MFD_BUTTON_CHECKLIST_PERF_DATA2];

		handler[BTN_L1] = &mfd_push_button_definitions[MFD_BUTTON_CHECKLIST_AFTER_STARTING_APU];
		handler[BTN_L2] = &mfd_push_button_definitions[MFD_BUTTON_CHECKLIST_BEFORE_STARTING_ENG];
		handler[BTN_L3] = &mfd_push_button_definitions[MFD_BUTTON_CHECKLIST_STARTING_ENG];
		handler[BTN_L4] = &mfd_push_button_definitions[MFD_BUTTON_CHECKLIST_BEFORE_TAXI];
		handler[BTN_L5] = &mfd_push_button_definitions[MFD_BUTTON_CHECKLIST_TAXI];
		handler[BTN_L6] = &mfd_push_button_definitions[MFD_BUTTON_CHECKLIST_BEFORE_TO];

		if (mfd_mode == MFD_MODE_CHECKLIST)
		{
			handler[BTN_R4] = &mfd_push_button_definitions[MFD_BUTTON_CHECKLIST_AFTER_LANDING];
			handler[BTN_R5] = &mfd_push_button_definitions[MFD_BUTTON_CHECKLIST_ENGINE_SHUTDOWN];
		}

		handler[BTN_M] = &mfd_push_button_definitions[MFD_BUTTON_MENU_CHECKLIST];

		decorate_checklist_buttons(location, current_sub_mode);

		break;
	}
	case MFD_MODE_CHECKLIST_PERF_DATA1:
	case MFD_MODE_CHECKLIST_PERF_DATA2:
	{
		handler[BTN_T3] = &mfd_push_button_definitions[MFD_BUTTON_CHECKLIST_THROUGH_FLIGHT];
		handler[BTN_T4] = &mfd_push_button_definitions[MFD_BUTTON_CHECKLIST_PERF_DATA1];
		handler[BTN_T5] = &mfd_push_button_definitions[MFD_BUTTON_CHECKLIST_PERF_DATA2];

		handler[BTN_M] = &mfd_push_button_definitions[MFD_BUTTON_MENU_CHECKLIST];

		break;
	}
	case MFD_MODE_ADF:
	{
		set_apache_mfd_sub_page(location, 0);

		if (get_apache_mfd_sub_mode(location) == 0)
			handler[BTN_R1] = &mfd_push_button_definitions[MFD_BUTTON_ADF_ON_OFF];

		if (get_adf_enabled())
		{
			if (get_apache_mfd_sub_mode(location) == 0)
			{
				handler[BTN_L4] = &mfd_push_button_definitions[MFD_BUTTON_ADF_TONE];
				handler[BTN_L5] = &mfd_push_button_definitions[MFD_BUTTON_ADF_IDENTIFY];

				if (get_adf_mode() == ADF_MODE_ADF)
					handler[BTN_R2] = &mfd_push_button_definitions[MFD_BUTTON_ADF_MODE_ADF];
				else
					handler[BTN_R2] = &mfd_push_button_definitions[MFD_BUTTON_ADF_MODE_ANT];
				handler[BTN_R3] = &mfd_push_button_definitions[MFD_BUTTON_ADF_FREQ];
				handler[BTN_R4] = &mfd_push_button_definitions[MFD_BUTTON_ADF_TEST];
				handler[BTN_R5] = &mfd_push_button_definitions[MFD_BUTTON_ADF_LAST];

				handler[BTN_B2] = &mfd_push_button_definitions[MFD_BUTTON_ADF_500];
				handler[BTN_B3] = &mfd_push_button_definitions[MFD_BUTTON_ADF_2182];
			}
			else
			{
				mfd_button_labels btn;

				handler[BTN_T5] = &mfd_push_button_definitions[MFD_BUTTON_ADF_TUNE];

				handler[BTN_B2] = &mfd_push_button_definitions[MFD_BUTTON_ADF_ID];
				handler[BTN_B3] = &mfd_push_button_definitions[MFD_BUTTON_ADF_FREQ];

				for (btn = BTN_L2; btn <= BTN_L6; btn++)
					handler[btn] = &mfd_push_button_definitions[MFD_BUTTON_ADF_PRSET_SELECT];
				for (btn = BTN_R2; btn <= BTN_R6; btn++)
					handler[btn] = &mfd_push_button_definitions[MFD_BUTTON_ADF_PRSET_SELECT];
			}

			handler[BTN_B5] = &mfd_push_button_definitions[MFD_BUTTON_ADF_PRSET];
		}

		handler[BTN_M] = &mfd_push_button_definitions[MFD_BUTTON_MENU_ADF];
	}
	default:
		break;
	}
}

void render_apache_mfd_buttons(mfd_modes mfd_mode, mfd_locations location, rgb_colour fg_col, rgb_colour bg_col, rgb_colour clear_col, int shade_background)
{
	const float margin = 0.01;
	int btn;
	float x = -2.5 * button_spacing;
	float y = 1.12;
	float alignment = -0.5, v_alignment = -2.0;
	float two_row_align_adj = 0.0;
	float upper_y = y;
	int row = BTN_T1;

	ASSERT(location != MFD_LOCATION_ORT);

	set_mono_font_colour(fg_col);
	set_mono_font_type (MONO_FONT_TYPE_12X20);

	render_mode_specfic_buttons(mfd_mode, location, fg_col, bg_col);

	for (btn = BTN_T1; btn <= BTN_B5; btn++)
	{
		const mfd_push_button* button = mfd_button_handlers[location][btn];

		if (btn == BTN_L1)
		{
			x = -1.15;
			y = 2.5 * button_spacing;
			alignment = 0.0;
			two_row_align_adj = -10.0;
			row = BTN_L1;
		}
		else if (btn == BTN_R1)
		{
			x = 1.15;
			y = 2.5 * button_spacing;
			alignment = -1.0;
			row = BTN_R1;
		}
		else if (btn == BTN_M)
		{
			x = -2.5 * button_spacing;
			y = -1.12;
			alignment = -0.5;
			two_row_align_adj = -17.0;
			row = BTN_B1;
		}

		if (button)
		{
			if (button->sprite)
			{
				if (button->label2)
					draw_2d_mono_sprite(button->label2, x, y, clear_col);
				if (button->label)
					draw_2d_mono_sprite(button->label, x, y, bg_col);
				draw_2d_mono_sprite(button->sprite, x, y, fg_col);
			}
			else
			{
				int width;
				int width2 = 0;
				int boxed_status = button_label_decorations[location][btn].boxed;
				float label_width;
				float label_width2 = 0.0;
				float height = 18.0;
				float v_align = v_alignment;
				const char
					*label = button->label,
					*label2 = button->label2;

				if (*button_label_decorations[location][btn].line1)
					label = &button_label_decorations[location][btn].line1;
				if (*button_label_decorations[location][btn].line2)
					label2 = &button_label_decorations[location][btn].line2;

				width = get_mono_font_string_width(label);
				label_width = string2mfd_width(width);

				ASSERT(label);

				if (button->vertical)
				{
					width = get_mono_font_string_width(" ");
					label_width = string2mfd_width(width);
					height = 19.0 * strlen(label);
					v_align = -0.5 * height + 8.0;

					if (btn == BTN_L6 || btn == BTN_R6)
						y -= 0.07;

					upper_y = y + (-v_align / 512.0 * 2.4) + margin;

					if (shade_background)
						draw_2d_box(x + alignment * label_width - margin,
									upper_y,
									x + (1.0 + alignment) * label_width + margin,
									upper_y - string2mfd_width(height) - margin,
									TRUE, FALSE, clear_col);

					print_vertical_mono_font_string(x, y, label, alignment, TRUE);
				}
				else
				{
					if (label2)
						v_align += two_row_align_adj;
					upper_y = y + (-v_align / 512.0 * 2.4) + margin;

					set_2d_mono_font_position(x, y);
					set_mono_font_rel_position (alignment * width, v_align);

					if (label2)
					{
						width2 = get_mono_font_string_width(label2);
						label_width2 = string2mfd_width(width2);

						if (shade_background)
							draw_2d_box(x + alignment * max(label_width, label_width2) - margin,
										upper_y,
										x + (1.0 + alignment) * max(label_width, label_width2) + margin,
										upper_y - string2mfd_width(height + 19.0) - margin,
										TRUE, FALSE, clear_col);

						print_mono_font_string(label);

						set_2d_mono_font_position(x, y);
						set_mono_font_rel_position (alignment * get_mono_font_string_width(label2), v_align + 19);
						print_mono_font_string(label2);
					}
					else
					{
						if (shade_background)
							draw_2d_box(x + alignment * label_width - margin,
										upper_y,
										x + (1.0 + alignment) * label_width + margin,
										upper_y - string2mfd_width(height) - margin,
										TRUE, FALSE, clear_col);

						print_mono_font_string(label);
					}
				}

				if (button->new_page_arrow && *label && btn != BTN_M && !button_label_decorations[location][btn].boxed)
					draw_menu_arrow(label_width, string2mfd_width((0.5 + alignment) * width) + x, y + string2mfd_width(4.0 - v_align), fg_col, bg_col);

				if (boxed_status)
				{
					if (boxed_status == 1)  // only select first line
					{
					}
					else if (boxed_status == 2)  // only select second line
					{
						label_width = label_width2;
						upper_y -= string2mfd_width(19.0);
					}
					else if (label2)
					{
						height += 19.0;
						label_width = max(label_width, label_width2);
					}

					height = string2mfd_width(height);

					draw_2d_box(x + alignment * label_width - margin,
								upper_y,
								x + (1.0 + alignment) * label_width + margin,
								upper_y - height - margin,
								FALSE, TRUE, fg_col);
				}

				if (button_label_decorations[location][btn].barriered)
				{
					switch (row)
					{
					case BTN_T1:
						draw_2d_box(x - 0.1, 1.2, x + 0.1, 1.17, TRUE, FALSE, fg_col);
						break;
					case BTN_L1:
						draw_2d_box(-1.2, y + 0.1, -1.17, y - 0.1, TRUE, FALSE, fg_col);
						break;
					case BTN_R1:
						draw_2d_box(1.2, y + 0.1, 1.17, y - 0.1, TRUE, FALSE, fg_col);
						break;
					case BTN_B1:
						draw_2d_box(x - 0.1, -1.2, x + 0.1, -1.17, TRUE, FALSE, fg_col);
						break;
					default:
						ASSERT(FALSE);
						break;
					}
				}
			}

		}

		if (btn <= BTN_T6 || btn >= BTN_M)
			x += button_spacing;
		else
			y -= button_spacing;
	}

	if (location == current_mfd_focus)
	{
		// pointer
		draw_2d_mono_sprite (pointer_mask, bound(pointer_position_x, -1.2, 1.2), pointer_position_y, bg_col);
		draw_2d_mono_sprite (pointer, bound(pointer_position_x, -1.2, 1.2), pointer_position_y, fg_col);
	}
}

void swap_apache_mfd_focus(void)
{
	if (get_local_entity_int_value (get_pilot_entity (), INT_TYPE_CREW_ROLE) == CREW_ROLE_PILOT)
	{
		if (current_mfd_focus == MFD_LOCATION_PILOT_LHS)
			current_mfd_focus = MFD_LOCATION_PILOT_RHS;
		else
			current_mfd_focus = MFD_LOCATION_PILOT_LHS;
	}
	else
	{
		if (current_mfd_focus == MFD_LOCATION_CPG_LHS)
			current_mfd_focus = MFD_LOCATION_CPG_RHS;
		else
			current_mfd_focus = MFD_LOCATION_CPG_LHS;
	}
}

void swap_apache_seat_mfd_focus(void)
{
	if (get_local_entity_int_value (get_pilot_entity (), INT_TYPE_CREW_ROLE) == CREW_ROLE_PILOT)
	{
		co_pilot_mfd_focus = current_mfd_focus;
		current_mfd_focus = pilot_mfd_focus;
	}
	else
	{
		pilot_mfd_focus = current_mfd_focus;
		current_mfd_focus = co_pilot_mfd_focus;
	}
}
