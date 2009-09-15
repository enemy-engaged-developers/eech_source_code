/*
 * ap_mfd_buttons.h
 *
 *  Created on: 05.sep.2009
 *      Author: arneh
 */

#ifndef AP_MFD_BUTTONS_H_
#define AP_MFD_BUTTONS_H_

typedef enum {
	MFD_BUTTON_ADF,
	MFD_BUTTON_ASE,
	MFD_BUTTON_CL,
	MFD_BUTTON_DMS,
	MFD_BUTTON_FUEL,
	MFD_BUTTON_ENG,
	MFD_BUTTON_FLT,
	MFD_BUTTON_PERF,
	MFD_BUTTON_UTIL,
	MFD_BUTTON_VERS,
	MFD_BUTTON_WPN,

	MFD_BUTTON_MENU_CHECKLIST,
	MFD_BUTTON_MENU_FLT,

	MFD_BUTTON_PAGE1,
	MFD_BUTTON_PAGE2,
	MFD_BUTTON_PAGE3,
	MFD_BUTTON_PAGE4,

	// flight page buttons
	MFD_BUTTON_SET,
	MFD_BUTTON_PITCH_W,

	// arrow sprites
	MFD_BUTTON_LEFT_ARROW,
	MFD_BUTTON_RIGHT_ARROW,
	MFD_BUTTON_UP_ARROW,
	MFD_BUTTON_DOWN_ARROW,

	// fuel page buttons
	MFD_BUTTON_L_AUX,
	MFD_BUTTON_R_AUX,
	MFD_BUTTON_FUEL_TRANS_FWD,
	MFD_BUTTON_FUEL_TRANS_OFF,
	MFD_BUTTON_FUEL_TRANS_AFT,
	MFD_BUTTON_FUEL_TRANS_AUTO_MAN,
	MFD_BUTTON_AUX_GAL,
	MFD_BUTTON_BOOST,
	MFD_BUTTON_FUEL_CROSS_FWD,
	MFD_BUTTON_FUEL_CROSS_NORM,
	MFD_BUTTON_FUEL_CROSS_AFT,
	MFD_BUTTON_FUEL_TYPE,
	MFD_BUTTON_FUEL_JP4,
	MFD_BUTTON_FUEL_JP5,
	MFD_BUTTON_FUEL_JP8,

	// checklist buttons
	MFD_BUTTON_CHECKLIST_THROUGH_FLIGHT,
	MFD_BUTTON_CHECKLIST_PERF_DATA1,
	MFD_BUTTON_CHECKLIST_PERF_DATA2,
	MFD_BUTTON_CHECKLIST_AFTER_STARTING_APU,
	MFD_BUTTON_CHECKLIST_BEFORE_STARTING_ENG,
	MFD_BUTTON_CHECKLIST_STARTING_ENG,
	MFD_BUTTON_CHECKLIST_BEFORE_TAXI,
	MFD_BUTTON_CHECKLIST_TAXI,
	MFD_BUTTON_CHECKLIST_BEFORE_TO,
	MFD_BUTTON_CHECKLIST_BEFORE_LANDING,
	MFD_BUTTON_CHECKLIST_AFTER_LANDING,
	MFD_BUTTON_CHECKLIST_ENGINE_SHUTDOWN,
	MFD_BUTTON_CHECKLIST_RAPID_REFUELING,
	MFD_BUTTON_CHECKLIST_RAPID_REARMING,
	MFD_BUTTON_CHECKLIST_FCR_OPR_CHECK,
	MFD_BUTTON_CHECKLIST_PILOT_IHADDS_BORE,
	MFD_BUTTON_CHECKLIST_FLIR_OPR_CHECK,
	MFD_BUTTON_CHECKLIST_MANUAL_DRIFT_NULL,
	MFD_BUTTON_CHECKLIST_PECHAN_REALLIGN,
	MFD_BUTTON_CHECKLIST_CUE_UPDATE_PROC,
	MFD_BUTTON_CHECKLIST_TADS_OPR_CHECK,
	MFD_BUTTON_CHECKLIST_TADS_OUTFR_BORE,
	MFD_BUTTON_CHECKLIST_FLIGHT_CONTROL,
	MFD_BUTTON_CHECKLIST_RETURN,
	NUM_PUSHBUTTON_TYPES
} mfd_push_button_types;

typedef struct {
	const char* sprite;
	const char* label;
	const char* label2;
	int new_page_arrow;
	int vertical;
	int box_on_click;

	// returns TRUE if press was successful
	int (*push_function)(mfd_push_button_types);
} mfd_push_button;

//extern mfd_push_button mfd_push_button_definitions[NUM_PUSHBUTTON_TYPES];

typedef enum {
	// six each for top, left, right and bottom
	BTN_T1, BTN_T2, BTN_T3,	BTN_T4,	BTN_T5,	BTN_T6,
	BTN_L1,	BTN_L2,	BTN_L3,	BTN_L4,	BTN_L5,	BTN_L6,
	BTN_R1,	BTN_R2,	BTN_R3,	BTN_R4,	BTN_R5,	BTN_R6,
	BTN_M,  BTN_B1,	BTN_B2,	BTN_B3,	BTN_B4,	BTN_B5,  // M is menu button
	FCR_BTN, WPN_BTN, TSD_BTN, AC_BTN, COM_BTN, VID_BTN, NO_BTN,
	NUM_PUSHBUTTONS,
} mfd_button_labels;

// extern mfd_push_button* mfd_button_handlers[NUM_PUSHBUTTONS];

void initialise_apache_pushbuttons(void);

void setup_apache_mfd_buttons(mfd_modes mfd_mode, mfd_locations location, int is_sub_mode);

void render_apache_mfd_buttons(mfd_modes mfd_mode, mfd_locations location, rgb_colour fg_col, rgb_colour bg_col, rgb_colour clear_colour);
void draw_apache_mfd_page_number_buttons(mfd_locations location, int backward, int forward);

void handle_apache_mfd_click(void);

#endif /* AP_MFD_BUTTONS_H_ */
