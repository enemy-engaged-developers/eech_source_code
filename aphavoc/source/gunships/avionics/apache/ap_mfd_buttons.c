/*
 * ap_mfd_buttons.c
 *
 *  Created on: 05.sep.2009
 *      Author: arneh
 */

#include "project.h"

#include "ap_mfd_buttons.h"
#include "ap_mfd_button_sprites.h"

#include "../../dynamics/common/co_fuel.h"

#define string2mfd_width(x)  ((x) / 512.0 * 2.4)

typedef struct {
	int boxed;
	int barriered;
} mfd_button_label_decorations;

static const float button_spacing = 0.3;
static mfd_button_labels last_button_pressed = NO_BTN;

static mfd_locations current_mfd_focus = MFD_LOCATION_PILOT_RHS;

static int set_new_page(mfd_push_button_types page);
static int select_menu_page(mfd_push_button_types page);
static int set_new_checklist_page(mfd_push_button_types page);
static int set_new_checklist_sub_page(mfd_push_button_types page);
static int set_new_sub_page_number(mfd_push_button_types page);
static int toggle_datum_adjust(mfd_push_button_types page);
static int adjust_pitch_datum(mfd_push_button_types page);

static int set_fuel_transfer_mode(mfd_push_button_types page);
static int set_fuel_crossfeed(mfd_push_button_types page);
static int set_fuel_type(mfd_push_button_types page);
static int toggle_fuel_booster(mfd_push_button_types page);

enum {
	NO_BOXING,
	NORM_BOXING,
	SINGLE_BOXING
};

char button_scratchpad[20][20];

// label line 1,    label line 2, page arrow, vertical, box, click handler
static mfd_push_button mfd_push_button_definitions[NUM_PUSHBUTTON_TYPES] = {
	// main menu buttons
	{ NULL,	"ADF",		NULL,	TRUE, FALSE, FALSE, set_new_page },
	{ NULL,	"ASE",		NULL,	TRUE, FALSE, FALSE, set_new_page },
	{ NULL,	"CL",			NULL,	TRUE, FALSE, FALSE, set_new_page },
	{ NULL,	"DMS",		NULL,	TRUE, FALSE, FALSE, set_new_page },
	{ NULL,	"FUEL",		NULL,	TRUE, FALSE, FALSE, set_new_page },
	{ NULL,	"ENG",		NULL,	TRUE, FALSE, FALSE, set_new_page },
	{ NULL,	"FLT",		NULL,	TRUE, FALSE, FALSE, set_new_page },
	{ NULL,	"PERF",		NULL,	TRUE, FALSE, FALSE, set_new_page },
	{ NULL,	"UTIL",		NULL,	TRUE, FALSE, FALSE, set_new_page },
	{ NULL,	"VERS",		NULL,	TRUE, FALSE, FALSE, set_new_page },
	{ NULL,	"WPN",		NULL,	TRUE, FALSE, FALSE, set_new_page },

	// buttons returning to main menu
	{ NULL,	"CL", 		NULL, 	TRUE, FALSE, FALSE, select_menu_page },   // checklist
	{ NULL,	"FLT", 		NULL, 	TRUE, FALSE, FALSE, select_menu_page },   // flight

	// page buttons
	{ NULL,	"PG", 		"1", 	FALSE, FALSE, FALSE, set_new_sub_page_number },
	{ NULL,	"PG", 		"2", 	FALSE, FALSE, FALSE, set_new_sub_page_number },
	{ NULL,	"PG", 		"3", 	FALSE, FALSE, FALSE, set_new_sub_page_number },
	{ NULL,	"PG", 		"4", 	FALSE, FALSE, FALSE, set_new_sub_page_number },

	{ NULL,	"SET", 		NULL, 	FALSE, FALSE, FALSE, NULL },
	{ NULL,	"-W-", 		NULL, 	FALSE, FALSE, TRUE, toggle_datum_adjust },

	{ left_arrow, left_arrow_mask, left_arrow_background, FALSE, FALSE, FALSE, NULL },
	{ right_arrow, right_arrow_mask, right_arrow_background, FALSE, FALSE, FALSE, NULL },
	{ up_arrow, up_arrow_mask, NULL, FALSE, FALSE, FALSE, adjust_pitch_datum },
	{ down_arrow, down_arrow_mask, NULL, FALSE, FALSE, FALSE, adjust_pitch_datum },

	// fuel buttons
	{ NULL,	"L AUX", 	NULL, 	FALSE, FALSE, NORM_BOXING, NULL },
	{ NULL,	"R AUX", 	NULL, 	FALSE, FALSE, NORM_BOXING, NULL },
	{ NULL,	"FWD", 		NULL, 	FALSE, FALSE, NO_BOXING, set_fuel_transfer_mode },
	{ NULL,	"OFF", 		NULL, 	FALSE, FALSE, NO_BOXING, set_fuel_transfer_mode },
	{ NULL,	"AFT", 		NULL, 	FALSE, FALSE, NO_BOXING, set_fuel_transfer_mode },
	{ NULL,	"AUTO", 	"MAN", 	FALSE, FALSE, SINGLE_BOXING, set_fuel_transfer_mode },
	{ NULL,	"AUX", 		"GAL", 	FALSE, FALSE, NO_BOXING, NULL },

	{ NULL,	"BOOST", 	NULL, 	FALSE, FALSE, NO_BOXING, toggle_fuel_booster },
	{ NULL,	"FWD", 		NULL, 	FALSE, FALSE, NO_BOXING, set_fuel_crossfeed },
	{ NULL,	"NORM", 	NULL, 	FALSE, FALSE, NO_BOXING, set_fuel_crossfeed },
	{ NULL,	"AFT", 		NULL, 	FALSE, FALSE, NO_BOXING, set_fuel_crossfeed },
	{ NULL,	"TYP",		button_scratchpad[0], 	FALSE, FALSE, NO_BOXING, set_fuel_type },
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
	};

static mfd_push_button* mfd_button_handlers[4][BTN_B5 + 1] = { 0 };
static mfd_button_label_decorations button_label_decorations[4][BTN_B5 + 1] = { 0 };

static int select_menu_page(mfd_push_button_types page)
{
	select_apache_mfd_mode(MFD_MODE_MENU, current_mfd_focus);

	return TRUE;
}

static int set_new_page(mfd_push_button_types page)
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

	}

	if (mode != MFD_MODE_MENU)
	{
		select_apache_mfd_mode(mode, current_mfd_focus);
		return TRUE;
	}

	return FALSE;
}

static int set_new_checklist_page(mfd_push_button_types page)
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


static int set_new_checklist_sub_page(mfd_push_button_types page)
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

static int toggle_datum_adjust(mfd_push_button_types page)
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

static int adjust_pitch_datum(mfd_push_button_types page)
{
	float adjust = 0.01;

	if (page == MFD_BUTTON_DOWN_ARROW)
		adjust = -adjust;

	adjust_apache_pitch_ladder_datum_position(adjust);

	return TRUE;
}

static int set_new_sub_page_number(mfd_push_button_types page)
{
	int number = page - MFD_BUTTON_PAGE1 + 1;
	set_apache_mfd_sub_page(current_mfd_focus, number);

	return TRUE;
}

static int set_fuel_transfer_mode(mfd_push_button_types page)
{
	if (page == MFD_BUTTON_FUEL_TRANS_AUTO_MAN)
	{
		int auto_trans = !get_auto_fuel_transfer();
		set_auto_fuel_transfer(auto_trans);

		button_label_decorations[current_mfd_focus][BTN_L5].boxed = auto_trans ? 1 : 2;

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

static int set_fuel_crossfeed(mfd_push_button_types page)
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

static int set_fuel_type(mfd_push_button_types page)
{
	return TRUE;
}

static int toggle_fuel_booster(mfd_push_button_types page)
{
	set_fuel_booster_pump_status(!get_fuel_booster_pump_status());

	return TRUE;
}

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

static void render_mode_specfic_buttons(mfd_modes mfd_mode, mfd_locations location, rgb_colour fg_col, rgb_colour bg_col)
{
	switch (mfd_mode)
	{
	case MFD_MODE_FUEL:
		{
			mfd_button_labels btn;

			sprintf(button_scratchpad[0], "JP4");

			// boost pump
			button_label_decorations[location][BTN_R2].boxed = get_fuel_booster_pump_status() ? 3 : 0;

			// fuel transfer
			for (btn = BTN_L2; btn <= BTN_L5; btn++)
				button_label_decorations[location][btn].boxed = 0;

			if (!get_auto_fuel_transfer())
			{
				button_label_decorations[location][BTN_L5].boxed = 2;

				if (get_fuel_transfer(FUEL_TANK_AFT) == FUEL_TANK_FWD)
					button_label_decorations[location][BTN_L2].boxed = 3;
				else if (get_fuel_transfer(FUEL_TANK_FWD) == FUEL_TANK_AFT)
					button_label_decorations[location][BTN_L4].boxed = 3;
				else
					button_label_decorations[location][BTN_L3].boxed = 3;
			}
			else
				button_label_decorations[location][BTN_L5].boxed = 1;

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
		}
	}

	button_label_decorations[location][BTN_M].boxed = 3;
}

void initialise_apache_pushbuttons(void)
{
	mfd_locations loc;

	for (loc = MFD_LOCATION_PILOT_LHS; loc <= MFD_LOCATION_CPG_RHS; loc++)
		clear_buttons(loc, TRUE);
}

void handle_apache_mfd_click(void)
{
	mfd_button_labels clicked_btn = get_clicked_button();

	if (clicked_btn < BTN_B5)
	{
		mfd_push_button* handler = mfd_button_handlers[current_mfd_focus][clicked_btn];

		last_button_pressed = clicked_btn;

		if (handler && handler->push_function)
		{
			int is_boxed = button_label_decorations[current_mfd_focus][clicked_btn].boxed;
			mfd_push_button_types btn_type = handler - mfd_push_button_definitions;
			int success = handler->push_function(btn_type);

			if (success && handler->box_on_click)
			{
				if (is_boxed)
					button_label_decorations[current_mfd_focus][clicked_btn].boxed = 0;
				else
					button_label_decorations[current_mfd_focus][clicked_btn].boxed = 3;
			}
		}
		last_button_pressed = NO_BTN;
	}
}

void setup_apache_mfd_buttons(mfd_modes mfd_mode, mfd_locations location, int is_sub_mode)
{
	mfd_push_button** handler = mfd_button_handlers[location];

	ASSERT(location != MFD_LOCATION_ORT);

	clear_buttons(location, !is_sub_mode);
	if (!is_sub_mode)
		set_apache_mfd_sub_mode(location, 0);

	switch (mfd_mode)
	{
	case MFD_MODE_MENU:
		handler[BTN_T2] = &mfd_push_button_definitions[MFD_BUTTON_ASE];
		handler[BTN_T4] = &mfd_push_button_definitions[MFD_BUTTON_CL];
		handler[BTN_T5] = &mfd_push_button_definitions[MFD_BUTTON_VERS];

		handler[BTN_L1] = &mfd_push_button_definitions[MFD_BUTTON_ADF];  // unknown
		handler[BTN_L6] = &mfd_push_button_definitions[MFD_BUTTON_WPN];

		handler[BTN_B1] = &mfd_push_button_definitions[MFD_BUTTON_DMS];
		handler[BTN_B2] = &mfd_push_button_definitions[MFD_BUTTON_ENG];  // uncertain
		handler[BTN_B3] = &mfd_push_button_definitions[MFD_BUTTON_FLT];  // unknown
		handler[BTN_B4] = &mfd_push_button_definitions[MFD_BUTTON_FUEL]; // uncertain
		handler[BTN_B5] = &mfd_push_button_definitions[MFD_BUTTON_PERF]; // unknown

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
		handler[BTN_T3] = &mfd_push_button_definitions[MFD_BUTTON_FUEL];
		button_label_decorations[location][BTN_T3].boxed = 3;
		handler[BTN_T4] = &mfd_push_button_definitions[MFD_BUTTON_PERF];
		handler[BTN_T6] = &mfd_push_button_definitions[MFD_BUTTON_UTIL];

#ifdef EXTERNAL_TANKS
		handler[BTN_L1] = &mfd_push_button_definitions[MFD_BUTTON_L_AUX];
		handler[BTN_R1] = &mfd_push_button_definitions[MFD_BUTTON_R_AUX];
		handler[BTN_L6] = &mfd_push_button_definitions[MFD_BUTTON_AUX_GAL];
#endif

		handler[BTN_L2] = &mfd_push_button_definitions[MFD_BUTTON_FUEL_TRANS_FWD];
		handler[BTN_L3] = &mfd_push_button_definitions[MFD_BUTTON_FUEL_TRANS_OFF];
		handler[BTN_L4] = &mfd_push_button_definitions[MFD_BUTTON_FUEL_TRANS_AFT];
		handler[BTN_L5] = &mfd_push_button_definitions[MFD_BUTTON_FUEL_TRANS_AUTO_MAN];

		handler[BTN_R2] = &mfd_push_button_definitions[MFD_BUTTON_BOOST];
		handler[BTN_R3] = &mfd_push_button_definitions[MFD_BUTTON_FUEL_CROSS_FWD];
		handler[BTN_R4] = &mfd_push_button_definitions[MFD_BUTTON_FUEL_CROSS_NORM];
		handler[BTN_R5] = &mfd_push_button_definitions[MFD_BUTTON_FUEL_CROSS_AFT];
		handler[BTN_R6] = &mfd_push_button_definitions[MFD_BUTTON_FUEL_TYPE];

		handler[BTN_M] = &mfd_push_button_definitions[MFD_BUTTON_FLT];
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
	default:
		break;
	}
}

void render_apache_mfd_buttons(mfd_modes mfd_mode, mfd_locations location, rgb_colour fg_col, rgb_colour bg_col, rgb_colour clear_col)
{
	int btn;
	float x = -2.5 * button_spacing;
	float y = 1.12;
	float alignment = -0.5, v_alignment = -2.0;
	float two_row_align_adj = 0.0;
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
			two_row_align_adj = -8.0;
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
				int width = get_mono_font_string_width(button->label);
				int width2 = 0;
				int boxed_status = button_label_decorations[location][btn].boxed;
				float label_width = string2mfd_width(width);
				float label_width2 = 0.0;
				float height = 18.0;
				float v_align = v_alignment;

				ASSERT(button->label);

				if (button->label2)
					v_align += two_row_align_adj;

				set_2d_mono_font_position(x, y);
				set_mono_font_rel_position (alignment * width, v_align);

				print_mono_font_string(button->label);

				if (button->new_page_arrow && *button->label && btn != BTN_M && !button_label_decorations[location][btn].boxed)
					draw_menu_arrow(label_width, string2mfd_width((0.5 + alignment) * width) + x, y + string2mfd_width(4.0 - v_align), fg_col, bg_col);

				if (button->label2)
				{
					width2 = get_mono_font_string_width(button->label2);
					label_width2 = string2mfd_width(width2);

					set_2d_mono_font_position(x, y);
					set_mono_font_rel_position (alignment * get_mono_font_string_width(button->label2), v_align + 16);
					print_mono_font_string(button->label2);
				}

				if (boxed_status)
				{
					const float margin = 0.01;
					float upper_y = y + (-v_align / 512.0 * 2.4) + margin;

					if (boxed_status == 1)  // only select first line
					{
					}
					else if (boxed_status == 2)  // only select second line
					{
						label_width = label_width2;
						upper_y -= string2mfd_width(16.0);
					}
					else if (button->label2)
					{
						height += 16.0;
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

	// pointer
	draw_2d_mono_sprite (tsd_pointer_cross_mask, bound(pointer_position_x, -1.2, 1.2), pointer_position_y, bg_col);
	draw_2d_mono_sprite (tsd_pointer_cross, bound(pointer_position_x, -1.2, 1.2), pointer_position_y, fg_col);
}
