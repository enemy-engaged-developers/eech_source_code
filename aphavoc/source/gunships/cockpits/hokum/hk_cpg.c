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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE 0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ANIMATION FRAMES
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define LAST_FRAME																		((float) (3000.0))

#define CO_PILOT_COLLECTIVE_ANIM_START												((float) (0.0 / 1500.0))
#define CO_PILOT_COLLECTIVE_ANIM_END												((float) (60.0 / 1500.0))

#define CO_PILOT_PEDAL_ANIM_START													((float) (0.0 / 1500.0))
#define CO_PILOT_PEDAL_ANIM_END														((float) (60.0 / 1500.0))

#define CO_PILOT_LEG_ANIM_START														((float) (0.0 / 1500.0))
#define CO_PILOT_LEG_ANIM_END															((float) (60.0 / 1500.0))

#define CO_PILOT_HEAD_TILT_RIGHT_ANIM_START										((float) (0.0 / LAST_FRAME))
#define CO_PILOT_HEAD_TILT_RIGHT_ANIM_END											((float) (15.0 / LAST_FRAME))

#define CO_PILOT_HEAD_TILT_LEFT_ANIM_START										((float) (30.0 / LAST_FRAME))
#define CO_PILOT_HEAD_TILT_LEFT_ANIM_END											((float) (45.0 / LAST_FRAME))

// 60.0 to 120.0 - no frames

#define CO_PILOT_CONTROLS_TO_REST_ANIM_START										((float) (120.0 / LAST_FRAME))
#define CO_PILOT_CONTROLS_TO_REST_ANIM_END										((float) (180.0 / LAST_FRAME))

#define CO_PILOT_LEFT_HAND_FROM_REST_TO_UPPER_SWITCH_ANIM_START			((float) (180.0 / LAST_FRAME))
#define CO_PILOT_LEFT_HAND_FROM_REST_TO_UPPER_SWITCH_ANIM_END				((float) (300.0 / LAST_FRAME))

#define CO_PILOT_LEFT_HAND_FROM_REST_TO_CALCULATOR_ANIM_START				((float) (300.0 / LAST_FRAME))
#define CO_PILOT_LEFT_HAND_FROM_REST_TO_CALCULATOR_ANIM_END					((float) (420.0 / LAST_FRAME))

#define CO_PILOT_LEFT_HAND_FROM_REST_TO_MASTER_ARM_SWITCH_ANIM_START		((float) (420.0 / LAST_FRAME))
#define CO_PILOT_LEFT_HAND_FROM_REST_TO_MASTER_ARM_SWITCH_ANIM_END  		((float) (540.0 / LAST_FRAME))

#define CO_PILOT_LEFT_HAND_FROM_REST_TO_NVG_ANIM_START						((float) (540.0 / LAST_FRAME))
#define CO_PILOT_LEFT_HAND_FROM_REST_TO_NVG_ANIM_END							((float) (660.0 / LAST_FRAME))

#define CO_PILOT_BOTH_HANDS_FROM_REST_TO_PULL_EJECT_ANIM_START				((float) (660.0 / LAST_FRAME))
#define CO_PILOT_BOTH_HANDS_FROM_REST_TO_PULL_EJECT_ANIM_END				((float) (750.0 / LAST_FRAME))

// 750.0 to 780.0 - no frames

#define CO_PILOT_BOTH_HANDS_FROM_CONTROLS_TO_PULL_EJECT_ANIM_START		((float) (780.0 / LAST_FRAME))
#define CO_PILOT_BOTH_HANDS_FROM_CONTROLS_TO_PULL_EJECT_ANIM_END			((float) (870.0 / LAST_FRAME))

// 870.0 to 900.0 - no frames

#define CO_PILOT_LEFT_HAND_FROM_COLLECTIVE_TO_NVG_ANIM_START				((float) (900.0 / LAST_FRAME))
#define CO_PILOT_LEFT_HAND_FROM_COLLECTIVE_TO_NVG_ANIM_END					((float) (1020.0 / LAST_FRAME))

#define CO_PILOT_HEAD_LOOK_DOWN_LEFT_ANIM_START                   		((float) (1020.0 / LAST_FRAME))
#define CO_PILOT_HEAD_LOOK_DOWN_LEFT_ANIM_END									((float) (1080.0 / LAST_FRAME))

#define CO_PILOT_HEAD_LOOK_DOWN_RIGHT_ANIM_START								((float) (1080.0 / LAST_FRAME))
#define CO_PILOT_HEAD_LOOK_DOWN_RIGHT_ANIM_END                    		((float) (1140.0 / LAST_FRAME))

#define CO_PILOT_HEAD_LOOK_DOWN_ANIM_START										((float) (1140.0 / LAST_FRAME))
#define CO_PILOT_HEAD_LOOK_DOWN_ANIM_END											((float) (1200.0 / LAST_FRAME))

#define CO_PILOT_HEAD_LOOK_UP_ANIM_START                          		((float) (1200.0 / LAST_FRAME))
#define CO_PILOT_HEAD_LOOK_UP_ANIM_END                            		((float) (1260.0 / LAST_FRAME))

#define CO_PILOT_HEAD_LOOK_LEFT_ANIM_START      	               		((float) (1260.0 / LAST_FRAME))
#define CO_PILOT_HEAD_LOOK_LEFT_ANIM_END           	            		((float) (1320.0 / LAST_FRAME))

#define CO_PILOT_HEAD_LOOK_RIGHT_ANIM_START										((float) (1320.0 / LAST_FRAME))
#define CO_PILOT_HEAD_LOOK_RIGHT_ANIM_END       	               		((float) (1380.0 / LAST_FRAME))

#define CO_PILOT_HEAD_LOOK_UP_LEFT_ANIM_START     	               		((float) (1380.0 / LAST_FRAME))
#define CO_PILOT_HEAD_LOOK_UP_LEFT_ANIM_END          	            		((float) (1440.0 / LAST_FRAME))

#define CO_PILOT_HEAD_LOOK_UP_RIGHT_ANIM_START									((float) (1440.0 / LAST_FRAME))
#define CO_PILOT_HEAD_LOOK_UP_RIGHT_ANIM_END										((float) (1500.0 / LAST_FRAME))

#define CO_PILOT_LEAN_FORWARD_TO_SCOPE_ANIM_START								((float) (1500.0 / LAST_FRAME))
#define CO_PILOT_LEAN_FORWARD_TO_SCOPE_ANIM_END									((float) (1560.0 / LAST_FRAME))

#define CO_PILOT_LEFT_HAND_FROM_SCOPE_TO_MASTER_ARM_SWITCH_ANIM_START	((float) (1560.0 / LAST_FRAME))
#define CO_PILOT_LEFT_HAND_FROM_SCOPE_TO_MASTER_ARM_SWITCH_ANIM_END		((float) (1680.0 / LAST_FRAME))

#define CO_PILOT_RIGHT_HAND_FROM_SCOPE_TO_CYCLIC_ANIM_START					((float) (1680.0 / LAST_FRAME))
#define CO_PILOT_RIGHT_HAND_FROM_SCOPE_TO_CYCLIC_ANIM_END 					((float) (1740.0 / LAST_FRAME))

#define CO_PILOT_THUMB_TO_CYCLIC_BUTTON_1_ANIM_START							((float) (1740.0 / LAST_FRAME))
#define CO_PILOT_THUMB_TO_CYCLIC_BUTTON_1_ANIM_END								((float) (1770.0 / LAST_FRAME))

#define CO_PILOT_THUMB_TO_CYCLIC_BUTTON_2_ANIM_START							((float) (1770.0 / LAST_FRAME))
#define CO_PILOT_THUMB_TO_CYCLIC_BUTTON_2_ANIM_END								((float) (1800.0 / LAST_FRAME))

#define CO_PILOT_RIGHT_HAND_FROM_CYCLIC_TO_SCOPE_ANIM_START					((float) (1800.0 / LAST_FRAME))
#define CO_PILOT_RIGHT_HAND_FROM_CYCLIC_TO_SCOPE_ANIM_END 					((float) (1860.0 / LAST_FRAME))

#define CO_PILOT_LEFT_HAND_FROM_SCOPE_TO_THUMBS_UP_ANIM_START				((float) (1860.0 / LAST_FRAME))
#define CO_PILOT_LEFT_HAND_FROM_SCOPE_TO_THUMBS_UP_ANIM_END					((float) (1980.0 / LAST_FRAME))

// 1980.0 to 2400.0 - no frames

#define CO_PILOT_LEAN_BACK_FROM_SCOPE_ANIM_START								((float) (2400.0 / LAST_FRAME))
#define CO_PILOT_LEAN_BACK_FROM_SCOPE_ANIM_END									((float) (2460.0 / LAST_FRAME))

// 2460.0 to 3000.0 - no frames

#define CO_PILOT_DATUM_AT_REST				  										(CO_PILOT_CONTROLS_TO_REST_ANIM_END)
#define CO_PILOT_DATUM_AT_SCOPE				  										(CO_PILOT_LEAN_FORWARD_TO_SCOPE_ANIM_END)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct CO_PILOT_ANIM_DATA
{
	float
		start_frame,
		end_frame;

	unsigned int
		datum_at_rest					:1,
		datum_at_scope					:1,
		animate_head 					:1,
		animate_chest	  				:1,
		animate_left_arm	  			:1,
		animate_right_arm				:1,
		animate_legs		 			:1,
		animate_eject_handle			:1,
		animate_master_arm_switch	:1;
};

typedef struct CO_PILOT_ANIM_DATA co_pilot_anim_data;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define NO_CO_PILOT_HEAD_ANIMATION	((float) (-1.0))

static float
	co_pilot_head_anim_frame,
	co_pilot_head_anim_pause,
	previous_co_pilot_head_tilt_angle;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define NVG_OFF	((float) (0.0))
#define NVG_ON		((float) (1.0))

static float
	co_pilot_nvg_anim_frame;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static float
	eject_timer;

static int
	eject_stage;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// CO-PILOT ANIMATIONS
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum CO_PILOT_ANIM_MODES
{
	CO_PILOT_ANIM_MODE_DATUM_AT_REST,
	CO_PILOT_ANIM_MODE_DATUM_AT_SCOPE,
	CO_PILOT_ANIM_MODE_LEAN_FORWARD_TO_SCOPE,
	CO_PILOT_ANIM_MODE_LEAN_BACK_FROM_SCOPE,
	CO_PILOT_ANIM_MODE_LEFT_HAND_FROM_REST_TO_UPPER_SWITCH,
	CO_PILOT_ANIM_MODE_LEFT_HAND_FROM_REST_TO_CALCULATOR,
	CO_PILOT_ANIM_MODE_LEFT_HAND_FROM_REST_TO_MASTER_ARM_SWITCH,
	CO_PILOT_ANIM_MODE_LEFT_HAND_FROM_REST_TO_NVG,
	CO_PILOT_ANIM_MODE_BOTH_HANDS_PULL_EJECT,
	CO_PILOT_ANIM_MODE_LEFT_HAND_FROM_SCOPE_TO_MASTER_ARM_SWITCH,
	CO_PILOT_ANIM_MODE_LEFT_HAND_FROM_SCOPE_TO_THUMBS_UP,
	CO_PILOT_ANIM_MODE_RIGHT_HAND_FROM_SCOPE_TO_CYCLIC,
	CO_PILOT_ANIM_MODE_RIGHT_HAND_THUMB_BUTTON1,
	CO_PILOT_ANIM_MODE_RIGHT_HAND_THUMB_BUTTON2,
	CO_PILOT_ANIM_MODE_RIGHT_HAND_FROM_CYCLIC_TO_SCOPE,
	CO_PILOT_ANIM_MODE_HEAD_LOOK_DOWN,
	CO_PILOT_ANIM_MODE_HEAD_LOOK_DOWN_LEFT,
	CO_PILOT_ANIM_MODE_HEAD_LOOK_DOWN_RIGHT,
	CO_PILOT_ANIM_MODE_HEAD_LOOK_UP,
	CO_PILOT_ANIM_MODE_HEAD_LOOK_UP_LEFT,
	CO_PILOT_ANIM_MODE_HEAD_LOOK_UP_RIGHT,
	CO_PILOT_ANIM_MODE_HEAD_LOOK_LEFT,
	CO_PILOT_ANIM_MODE_HEAD_LOOK_RIGHT,
	NUM_CO_PILOT_ANIM_MODES
};

typedef enum CO_PILOT_ANIM_MODES co_pilot_anim_modes;

static co_pilot_anim_modes
	co_pilot_anim_mode;

static float
	co_pilot_anim_frame,
	co_pilot_anim_delay;

////////////////////////////////////////
//
// CO_PILOT_ANIM_MODE_DATUM_AT_REST
//
////////////////////////////////////////

static co_pilot_anim_data
	co_pilot_anim_mode_datum_at_rest_anim_data =
	{
		0.0,																					// start_frame
		0.0,																					// end_frame
		TRUE,				  																	// datum_at_rest
		FALSE,																				// datum_at_scope
		FALSE,																				// animate_head
		FALSE,																				// animate_chest
		FALSE,																				// animate_left_arm
		FALSE,																				// animate_right_arm
		FALSE,																				// animate_legs
		FALSE,																				// animate_eject_handle
		FALSE,																				// animate_master_arm_switch
	};

////////////////////////////////////////
//
// CO_PILOT_ANIM_MODE_DATUM_AT_SCOPE
//
////////////////////////////////////////

static co_pilot_anim_data
	co_pilot_anim_mode_datum_at_scope_anim_data =
	{
		0.0,																					// start_frame
		0.0,																					// end_frame
		FALSE,																				// datum_at_rest
		TRUE,				 																	// datum_at_scope
		FALSE,																				// animate_head
		FALSE,																				// animate_chest
		FALSE,																				// animate_left_arm
		FALSE,																				// animate_right_arm
		FALSE,																				// animate_legs
		FALSE,																				// animate_eject_handle
		FALSE,																				// animate_master_arm_switch
	};

////////////////////////////////////////
//
// CO_PILOT_ANIM_MODE_LEAN_FORWARD_TO_SCOPE
//
////////////////////////////////////////

static co_pilot_anim_data
	co_pilot_anim_mode_lean_forward_to_scope_anim_data =
	{
		CO_PILOT_LEAN_FORWARD_TO_SCOPE_ANIM_START,								// start_frame
		CO_PILOT_LEAN_FORWARD_TO_SCOPE_ANIM_END,									// end_frame
		TRUE,																					// datum_at_rest
		FALSE,																				// datum_at_scope
		TRUE,			 																		// animate_head
		TRUE,																					// animate_chest
		TRUE,																					// animate_left_arm
		TRUE,			 																		// animate_right_arm
		FALSE,																				// animate_legs
		FALSE,																				// animate_eject_handle
		FALSE,																				// animate_master_arm_switch
	};

////////////////////////////////////////
//
// CO_PILOT_ANIM_MODE_LEAN_BACK_FROM_SCOPE
//
////////////////////////////////////////

static co_pilot_anim_data
	co_pilot_anim_mode_lean_back_from_scope_anim_data =
	{
		CO_PILOT_LEAN_BACK_FROM_SCOPE_ANIM_START,									// start_frame
		CO_PILOT_LEAN_BACK_FROM_SCOPE_ANIM_END,									// end_frame
		FALSE,																				// datum_at_rest
		TRUE,				  																	// datum_at_scope
		TRUE,				  																	// animate_head
		TRUE,																					// animate_chest
		TRUE,																					// animate_left_arm
		TRUE,																					// animate_right_arm
		FALSE,																				// animate_legs
		FALSE,																				// animate_eject_handle
		FALSE,																				// animate_master_arm_switch
	};

////////////////////////////////////////
//
// CO_PILOT_ANIM_MODE_LEFT_HAND_FROM_REST_TO_UPPER_SWITCH
//
////////////////////////////////////////

static co_pilot_anim_data
	co_pilot_anim_mode_left_hand_from_rest_to_upper_switch_anim_data =
	{
		CO_PILOT_LEFT_HAND_FROM_REST_TO_UPPER_SWITCH_ANIM_START,				// start_frame
		CO_PILOT_LEFT_HAND_FROM_REST_TO_UPPER_SWITCH_ANIM_END,				// end_frame
		TRUE,																					// datum_at_rest
		FALSE,			  																	// datum_at_scope
		TRUE,				  																	// animate_head
		FALSE,																				// animate_chest
		TRUE,																					// animate_left_arm
		FALSE,																				// animate_right_arm
		FALSE,																				// animate_legs
		FALSE,																				// animate_eject_handle
		FALSE,																				// animate_master_arm_switch
	};

////////////////////////////////////////
//
// CO_PILOT_ANIM_MODE_LEFT_HAND_FROM_REST_TO_CALCULATOR
//
////////////////////////////////////////

static co_pilot_anim_data
	co_pilot_anim_mode_left_hand_from_rest_to_calculator_anim_data =
	{
		CO_PILOT_LEFT_HAND_FROM_REST_TO_CALCULATOR_ANIM_START,				// start_frame
		CO_PILOT_LEFT_HAND_FROM_REST_TO_CALCULATOR_ANIM_END,	 				// end_frame
		TRUE,																					// datum_at_rest
		FALSE,			  																	// datum_at_scope
		TRUE,				  																	// animate_head
		TRUE,				 																	// animate_chest
		TRUE,																					// animate_left_arm
		TRUE,																					// animate_right_arm
		FALSE,																				// animate_legs
		FALSE,																				// animate_eject_handle
		FALSE,																				// animate_master_arm_switch
	};

////////////////////////////////////////
//
// CO_PILOT_ANIM_MODE_LEFT_HAND_FROM_REST_TO_MASTER_ARM_SWITCH
//
////////////////////////////////////////

static co_pilot_anim_data
	co_pilot_anim_mode_left_hand_from_rest_to_master_arm_switch_anim_data =
	{
		CO_PILOT_LEFT_HAND_FROM_REST_TO_MASTER_ARM_SWITCH_ANIM_START,		// start_frame
		CO_PILOT_LEFT_HAND_FROM_REST_TO_MASTER_ARM_SWITCH_ANIM_END,			// end_frame
		TRUE,																					// datum_at_rest
		FALSE,			  																	// datum_at_scope
		TRUE,				  																	// animate_head
		TRUE,				 																	// animate_chest
		TRUE,																					// animate_left_arm
		TRUE,			  																		// animate_right_arm
		FALSE,																				// animate_legs
		FALSE,																				// animate_eject_handle
		TRUE,																					// animate_master_arm_switch
	};

////////////////////////////////////////
//
// CO_PILOT_ANIM_MODE_LEFT_HAND_FROM_REST_TO_NVG
//
////////////////////////////////////////

static co_pilot_anim_data
	co_pilot_anim_mode_left_hand_from_rest_to_nvg_anim_data =
	{
		CO_PILOT_LEFT_HAND_FROM_REST_TO_NVG_ANIM_START,							// start_frame
		CO_PILOT_LEFT_HAND_FROM_REST_TO_NVG_ANIM_END,							// end_frame
		TRUE,																					// datum_at_rest
		FALSE,			  																	// datum_at_scope
		FALSE,																				// animate_head
		FALSE,																				// animate_chest
		TRUE,																					// animate_left_arm
		FALSE,																				// animate_right_arm
		FALSE,																				// animate_legs
		FALSE,																				// animate_eject_handle
		FALSE,																				// animate_master_arm_switch
	};

////////////////////////////////////////
//
// CO_PILOT_ANIM_MODE_BOTH_HANDS_PULL_EJECT
//
////////////////////////////////////////

static co_pilot_anim_data
	co_pilot_anim_mode_both_hands_pull_eject_anim_data =
	{
		CO_PILOT_BOTH_HANDS_FROM_REST_TO_PULL_EJECT_ANIM_START,				// start_frame
		CO_PILOT_BOTH_HANDS_FROM_REST_TO_PULL_EJECT_ANIM_END,					// end_frame
		TRUE,																					// datum_at_rest
		FALSE,			  																	// datum_at_scope
		TRUE,																					// animate_head
		FALSE,																				// animate_chest
		TRUE,																					// animate_left_arm
		TRUE,																					// animate_right_arm
		TRUE,																					// animate_legs
		TRUE,																					// animate_eject_handle
		FALSE,																				// animate_master_arm_switch
	};

////////////////////////////////////////
//
// CO_PILOT_ANIM_MODE_LEFT_HAND_FROM_SCOPE_TO_MASTER_ARM_SWITCH
//
////////////////////////////////////////

static co_pilot_anim_data
	co_pilot_anim_mode_left_hand_from_scope_to_master_arm_switch_anim_data =
	{
		CO_PILOT_LEFT_HAND_FROM_SCOPE_TO_MASTER_ARM_SWITCH_ANIM_START,		// start_frame
		CO_PILOT_LEFT_HAND_FROM_SCOPE_TO_MASTER_ARM_SWITCH_ANIM_END,		// end_frame
		FALSE, 																				// datum_at_rest
		TRUE,	 			  																	// datum_at_scope
		FALSE,			  																	// animate_head
		FALSE,			 																	// animate_chest
		TRUE,																					// animate_left_arm
		FALSE,		  																		// animate_right_arm
		FALSE,																				// animate_legs
		FALSE,																				// animate_eject_handle
		TRUE,																					// animate_master_arm_switch
	};

////////////////////////////////////////
//
// CO_PILOT_ANIM_MODE_LEFT_HAND_FROM_SCOPE_TO_THUMBS_UP
//
////////////////////////////////////////

static co_pilot_anim_data
	co_pilot_anim_mode_left_hand_from_scope_to_thumbs_up_anim_data =
	{
		CO_PILOT_LEFT_HAND_FROM_SCOPE_TO_THUMBS_UP_ANIM_START,				// start_frame
		CO_PILOT_LEFT_HAND_FROM_SCOPE_TO_THUMBS_UP_ANIM_END,					// end_frame
		FALSE, 																				// datum_at_rest
		TRUE,	 			  																	// datum_at_scope
		FALSE,			  																	// animate_head
		FALSE,			 																	// animate_chest
		TRUE,																					// animate_left_arm
		FALSE,		  																		// animate_right_arm
		FALSE,																				// animate_legs
		FALSE,																				// animate_eject_handle
		FALSE, 																				// animate_master_arm_switch
	};

////////////////////////////////////////
//
// CO_PILOT_ANIM_MODE_RIGHT_HAND_FROM_SCOPE_TO_CYCLIC
//
////////////////////////////////////////

static co_pilot_anim_data
	co_pilot_anim_mode_right_hand_from_scope_to_cyclic_anim_data =
	{
		CO_PILOT_RIGHT_HAND_FROM_SCOPE_TO_CYCLIC_ANIM_START,					// start_frame
		CO_PILOT_RIGHT_HAND_FROM_SCOPE_TO_CYCLIC_ANIM_END,			  			// end_frame
		FALSE, 																				// datum_at_rest
		TRUE,	 			  																	// datum_at_scope
		FALSE,			  																	// animate_head
		FALSE,			 																	// animate_chest
		FALSE,		 																		// animate_left_arm
		TRUE,		  																			// animate_right_arm
		FALSE,																				// animate_legs
		FALSE,																				// animate_eject_handle
		FALSE, 																				// animate_master_arm_switch
	};

////////////////////////////////////////
//
// CO_PILOT_ANIM_MODE_RIGHT_HAND_THUMB_BUTTON1
//
////////////////////////////////////////

static co_pilot_anim_data
	co_pilot_anim_mode_right_hand_thumb_button1_anim_data =
	{
		CO_PILOT_THUMB_TO_CYCLIC_BUTTON_1_ANIM_START,	 						// start_frame
		CO_PILOT_THUMB_TO_CYCLIC_BUTTON_1_ANIM_END,	 							// end_frame
		FALSE, 																				// datum_at_rest
		TRUE,	 			  																	// datum_at_scope
		FALSE,			  																	// animate_head
		FALSE,			 																	// animate_chest
		FALSE,		 																		// animate_left_arm
		TRUE,		  																			// animate_right_arm
		FALSE,																				// animate_legs
		FALSE,																				// animate_eject_handle
		FALSE, 																				// animate_master_arm_switch
	};

////////////////////////////////////////
//
// CO_PILOT_ANIM_MODE_RIGHT_HAND_THUMB_BUTTON2
//
////////////////////////////////////////

static co_pilot_anim_data
	co_pilot_anim_mode_right_hand_thumb_button2_anim_data =
	{
		CO_PILOT_THUMB_TO_CYCLIC_BUTTON_2_ANIM_START, 							// start_frame
		CO_PILOT_THUMB_TO_CYCLIC_BUTTON_2_ANIM_END, 								// end_frame
		FALSE, 																				// datum_at_rest
		TRUE,	 			  																	// datum_at_scope
		FALSE,			  																	// animate_head
		FALSE,			 																	// animate_chest
		FALSE,		 																		// animate_left_arm
		TRUE,		  																			// animate_right_arm
		FALSE,																				// animate_legs
		FALSE,																				// animate_eject_handle
		FALSE, 																				// animate_master_arm_switch
	};

////////////////////////////////////////
//
// CO_PILOT_ANIM_MODE_RIGHT_HAND_FROM_CYCLIC_TO_SCOPE
//
////////////////////////////////////////

static co_pilot_anim_data
	co_pilot_anim_mode_right_hand_from_cyclic_to_scope_anim_data =
	{
		CO_PILOT_RIGHT_HAND_FROM_CYCLIC_TO_SCOPE_ANIM_START,					// start_frame
		CO_PILOT_RIGHT_HAND_FROM_CYCLIC_TO_SCOPE_ANIM_END,						// end_frame
		FALSE, 																				// datum_at_rest
		TRUE,	 			  																	// datum_at_scope
		FALSE,			  																	// animate_head
		FALSE,			 																	// animate_chest
		FALSE,		 																		// animate_left_arm
		TRUE,		  																			// animate_right_arm
		FALSE,																				// animate_legs
		FALSE,																				// animate_eject_handle
		FALSE, 																				// animate_master_arm_switch
	};

////////////////////////////////////////
//
// CO_PILOT_ANIM_MODE_HEAD_LOOK_DOWN
//
////////////////////////////////////////

static co_pilot_anim_data
	co_pilot_anim_mode_head_look_down_anim_data =
	{
		CO_PILOT_HEAD_LOOK_DOWN_ANIM_START,			 								// start_frame
		CO_PILOT_HEAD_LOOK_DOWN_ANIM_END,											// end_frame
		TRUE,																					// datum_at_rest
		FALSE,			  																	// datum_at_scope
		TRUE,				  																	// animate_head
		FALSE,			 																	// animate_chest
		FALSE,			 																	// animate_left_arm
		FALSE,			 																	// animate_right_arm
		FALSE,																				// animate_legs
		FALSE,																				// animate_eject_handle
		FALSE,																				// animate_master_arm_switch
	};

////////////////////////////////////////
//
// CO_PILOT_ANIM_MODE_HEAD_LOOK_DOWN_LEFT
//
////////////////////////////////////////

static co_pilot_anim_data
	co_pilot_anim_mode_head_look_down_left_anim_data =
	{
		CO_PILOT_HEAD_LOOK_DOWN_LEFT_ANIM_START,	 								// start_frame
		CO_PILOT_HEAD_LOOK_DOWN_LEFT_ANIM_END,		 								// end_frame
		TRUE,																					// datum_at_rest
		FALSE,			  																	// datum_at_scope
		TRUE,				  																	// animate_head
		FALSE,			 																	// animate_chest
		FALSE,			 																	// animate_left_arm
		FALSE,			 																	// animate_right_arm
		FALSE,																				// animate_legs
		FALSE,																				// animate_eject_handle
		FALSE,																				// animate_master_arm_switch
	};

////////////////////////////////////////
//
// CO_PILOT_ANIM_MODE_HEAD_LOOK_DOWN_RIGHT
//
////////////////////////////////////////

static co_pilot_anim_data
	co_pilot_anim_mode_head_look_down_right_anim_data =
	{
		CO_PILOT_HEAD_LOOK_DOWN_RIGHT_ANIM_START,									// start_frame
		CO_PILOT_HEAD_LOOK_DOWN_RIGHT_ANIM_END,									// end_frame
		TRUE,																					// datum_at_rest
		FALSE,			  																	// datum_at_scope
		TRUE,				  																	// animate_head
		FALSE,			 																	// animate_chest
		FALSE,			 																	// animate_left_arm
		FALSE,			 																	// animate_right_arm
		FALSE,																				// animate_legs
		FALSE,																				// animate_eject_handle
		FALSE,																				// animate_master_arm_switch
	};

////////////////////////////////////////
//
// CO_PILOT_ANIM_MODE_HEAD_LOOK_UP
//
////////////////////////////////////////

static co_pilot_anim_data
	co_pilot_anim_mode_head_look_up_anim_data =
	{
		CO_PILOT_HEAD_LOOK_UP_ANIM_START,			 								// start_frame
		CO_PILOT_HEAD_LOOK_UP_ANIM_END,												// end_frame
		TRUE,																					// datum_at_rest
		FALSE,			  																	// datum_at_scope
		TRUE,				  																	// animate_head
		FALSE,			 																	// animate_chest
		FALSE,			 																	// animate_left_arm
		FALSE,			 																	// animate_right_arm
		FALSE,																				// animate_legs
		FALSE,																				// animate_eject_handle
		FALSE,																				// animate_master_arm_switch
	};

////////////////////////////////////////
//
// CO_PILOT_ANIM_MODE_HEAD_LOOK_UP_LEFT
//
////////////////////////////////////////

static co_pilot_anim_data
	co_pilot_anim_mode_head_look_up_left_anim_data =
	{
		CO_PILOT_HEAD_LOOK_UP_LEFT_ANIM_START,	 	 								// start_frame
		CO_PILOT_HEAD_LOOK_UP_LEFT_ANIM_END,	 									// end_frame
		TRUE,																					// datum_at_rest
		FALSE,			  																	// datum_at_scope
		TRUE,				  																	// animate_head
		FALSE,			 																	// animate_chest
		FALSE,			 																	// animate_left_arm
		FALSE,			 																	// animate_right_arm
		FALSE,																				// animate_legs
		FALSE,																				// animate_eject_handle
		FALSE,																				// animate_master_arm_switch
	};

////////////////////////////////////////
//
// CO_PILOT_ANIM_MODE_HEAD_LOOK_UP_RIGHT
//
////////////////////////////////////////

static co_pilot_anim_data
	co_pilot_anim_mode_head_look_up_right_anim_data =
	{
		CO_PILOT_HEAD_LOOK_UP_RIGHT_ANIM_START,  									// start_frame
		CO_PILOT_HEAD_LOOK_UP_RIGHT_ANIM_END,	 									// end_frame
		TRUE,																					// datum_at_rest
		FALSE,			  																	// datum_at_scope
		TRUE,				  																	// animate_head
		FALSE,			 																	// animate_chest
		FALSE,			 																	// animate_left_arm
		FALSE,			 																	// animate_right_arm
		FALSE,																				// animate_legs
		FALSE,																				// animate_eject_handle
		FALSE,																				// animate_master_arm_switch
	};

////////////////////////////////////////
//
// CO_PILOT_ANIM_MODE_HEAD_LOOK_LEFT
//
////////////////////////////////////////

static co_pilot_anim_data
	co_pilot_anim_mode_head_look_left_anim_data =
	{
		CO_PILOT_HEAD_LOOK_LEFT_ANIM_START,		 	 								// start_frame
		CO_PILOT_HEAD_LOOK_LEFT_ANIM_END,		  									// end_frame
		TRUE,																					// datum_at_rest
		FALSE,			  																	// datum_at_scope
		TRUE,				  																	// animate_head
		FALSE,			 																	// animate_chest
		FALSE,			 																	// animate_left_arm
		FALSE,			 																	// animate_right_arm
		FALSE,																				// animate_legs
		FALSE,																				// animate_eject_handle
		FALSE,																				// animate_master_arm_switch
	};

////////////////////////////////////////
//
// CO_PILOT_ANIM_MODE_HEAD_LOOK_RIGHT
//
////////////////////////////////////////

static co_pilot_anim_data
	co_pilot_anim_mode_head_look_right_anim_data =
	{
		CO_PILOT_HEAD_LOOK_RIGHT_ANIM_START,		 								// start_frame
		CO_PILOT_HEAD_LOOK_RIGHT_ANIM_END,											// end_frame
		TRUE,																					// datum_at_rest
		FALSE,			  																	// datum_at_scope
		TRUE,				  																	// animate_head
		FALSE,			 																	// animate_chest
		FALSE,			 																	// animate_left_arm
		FALSE,			 																	// animate_right_arm
		FALSE,																				// animate_legs
		FALSE,																				// animate_eject_handle
		FALSE,																				// animate_master_arm_switch
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// CONTROLS
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_co_pilot_static_right_hand_on_cyclic_visibility (int visible)
{
	object_3d_sub_object_search_data
		search_data;

	search_data.search_depth = 0;
	search_data.search_object = virtual_cockpit_inst3d;
	search_data.sub_object_index = OBJECT_3D_SUB_OBJECT_WSO_R_HAND;

	if (find_object_3d_sub_object (&search_data) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		search_data.result_sub_object->visible_object = !visible;
	}

	search_data.search_depth = 0;
	search_data.search_object = virtual_cockpit_inst3d;
	search_data.sub_object_index = OBJECT_3D_SUB_OBJECT_COCKPIT_WSO_HAND_STATIC;

	if (find_object_3d_sub_object (&search_data) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		search_data.result_sub_object->visible_object = visible;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_co_pilot_collective_position (float collective)
{
	float
		anim_frame;

	anim_frame = 1.0 - collective;

	anim_frame *= CO_PILOT_COLLECTIVE_ANIM_END - CO_PILOT_COLLECTIVE_ANIM_START;

	anim_frame += CO_PILOT_COLLECTIVE_ANIM_START;

	anim_frame = bound (anim_frame, CO_PILOT_COLLECTIVE_ANIM_START, CO_PILOT_COLLECTIVE_ANIM_END);

	animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_COCKPIT_WSO_COLLECTIVE, anim_frame);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_co_pilot_pedal_position (float pedal)
{
	float
		anim_frame;

	anim_frame = pedal;

	anim_frame *= CO_PILOT_PEDAL_ANIM_END - CO_PILOT_PEDAL_ANIM_START;

	anim_frame += CO_PILOT_PEDAL_ANIM_START;

	anim_frame = bound (anim_frame, CO_PILOT_PEDAL_ANIM_START, CO_PILOT_PEDAL_ANIM_END);

	animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_COCKPIT_WSO_PEDAL, anim_frame);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// SET CO-PILOT ANIMATION
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_co_pilot_animation (co_pilot_anim_data *anim, float frame)
{
	float
		anim_frame,
		n;

	ASSERT (anim);

	set_co_pilot_static_right_hand_on_cyclic_visibility (FALSE);

	set_co_pilot_collective_position (0.5);

	set_co_pilot_pedal_position (0.5);

	////////////////////////////////////////

	anim_frame = ((anim->end_frame - anim->start_frame) * frame) + anim->start_frame;

	anim_frame = bound (anim_frame, anim->start_frame, anim->end_frame);

	////////////////////////////////////////

	if (anim->animate_head)
	{
		co_pilot_head_anim_frame = anim_frame;
	}
	else
	{
		co_pilot_head_anim_frame = NO_CO_PILOT_HEAD_ANIMATION;
	}

	////////////////////////////////////////

	if (anim->animate_chest)
	{
		n = anim_frame;
	}
	else if (anim->datum_at_rest)
	{
		n = CO_PILOT_DATUM_AT_REST;
	}
	else
	{
		n = CO_PILOT_DATUM_AT_SCOPE;
	}

	animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_WSO_CHEST, n);

	////////////////////////////////////////

	if (anim->animate_left_arm)
	{
		n = anim_frame;
	}
	else if (anim->datum_at_rest)
	{
		n = CO_PILOT_DATUM_AT_REST;
	}
	else
	{
		n = CO_PILOT_DATUM_AT_SCOPE;
	}

	animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_WSO_L_SHOULDER, n);

	animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_WSO_L_FOREARM, n);

	animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_WSO_L_HAND, n);

	animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_WSO_L_FINGER, n);

	animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_WSO_L_THUMB, n);

	////////////////////////////////////////

	if (anim->animate_right_arm)
	{
		n = anim_frame;
	}
	else if (anim->datum_at_rest)
	{
		n = CO_PILOT_DATUM_AT_REST;
	}
	else
	{
		n = CO_PILOT_DATUM_AT_SCOPE;
	}

	animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_WSO_R_SHOULDER, n);

	animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_WSO_R_FOREARM, n);

	animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_WSO_R_HAND, n);

	animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_WSO_R_FINGER, n);

	animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_WSO_R_THUMB, n);

	////////////////////////////////////////

	if (anim->animate_legs)
	{
		n = anim_frame;
	}
	else if (anim->datum_at_rest)
	{
		n = CO_PILOT_DATUM_AT_REST;
	}
	else
	{
		n = CO_PILOT_DATUM_AT_SCOPE;
	}

	animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_WSO_LEG, n);

	////////////////////////////////////////

	if (anim->animate_eject_handle)
	{
		//
		// hardwired for eject handle ...
		//

		#define EJECT_HANDLE_START_FRAME ((float) (660.0 / 1500.0))
		#define EJECT_HANDLE_END_FRAME ((float) (750.0 / 1500.0))

		n = ((EJECT_HANDLE_END_FRAME - EJECT_HANDLE_START_FRAME) * frame) + EJECT_HANDLE_START_FRAME;

		n = bound (n, EJECT_HANDLE_START_FRAME, EJECT_HANDLE_END_FRAME);
	}
	else if (anim->datum_at_rest)
	{
		n = CO_PILOT_DATUM_AT_REST;
	}
	else
	{
		n = CO_PILOT_DATUM_AT_SCOPE;
	}

	animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_COCKPIT_WSO_EJECT_HANDLE, n);

	////////////////////////////////////////

	if (anim->animate_master_arm_switch)
	{
		n = anim_frame;
	}
	else if (anim->datum_at_rest)
	{
		n = CO_PILOT_DATUM_AT_REST;
	}
	else
	{
		n = CO_PILOT_DATUM_AT_SCOPE;
	}

	animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_COCKPIT_MASTER_ARM_SWITCH, n);

	////////////////////////////////////////

	n = ((CO_PILOT_LEFT_HAND_FROM_REST_TO_NVG_ANIM_END - CO_PILOT_LEFT_HAND_FROM_REST_TO_NVG_ANIM_START) * co_pilot_nvg_anim_frame) + CO_PILOT_LEFT_HAND_FROM_REST_TO_NVG_ANIM_START;

	n = bound (n, CO_PILOT_LEFT_HAND_FROM_REST_TO_NVG_ANIM_START, CO_PILOT_LEFT_HAND_FROM_REST_TO_NVG_ANIM_END);

	animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_WSO_NVG, n);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// UPDATE CO-PILOT ANIMATION
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int get_co_pilot_viewpoint_virtual_cockpit (void)
{
	if (get_crew_role () == CREW_ROLE_CO_PILOT)
	{
		if
		(
			(get_view_mode () == VIEW_MODE_VIRTUAL_COCKPIT) ||
			(get_view_mode () == VIEW_MODE_VIRTUAL_COCKPIT_PADLOCK) ||
			(get_view_mode () == VIEW_MODE_VIRTUAL_COCKPIT_TRACK_TARGET)
		)
		{
			return (TRUE);
		}
	}

	return (FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static float get_reset_co_pilot_anim_delay (void)
{
	if (frand1 () < 0.2)
	{
		return (0.0);
	}

	return ((frand1 () * 3.0) + 2.0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static float get_reset_co_pilot_head_anim_pause (void)
{
	float
		pause;

	//
	// chance of no pause (glance)
	//

	if (frand1 () < 0.15)
	{
		pause = 0.0;
	}
	else
	{
		pause = (frand1 () * 3.0) + 0.5;
	}

	return (pause);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static co_pilot_anim_modes get_random_co_pilot_datum_at_rest_anim_mode (void)
{
	static int
		previous_n = -1;

	int
		n;

	co_pilot_anim_modes
		mode;

	if (frand1 () < 0.2)
	{
		mode = CO_PILOT_ANIM_MODE_LEAN_FORWARD_TO_SCOPE;
	}
	else
	{
		n = rand16 () % 11;

		if (n == previous_n)
		{
			n = rand16 () % 11;

			if (n == previous_n)
			{
				n = rand16 () % 11;
			}
		}

		previous_n = n;

		switch (n)
		{
			case 0:
			{
				mode = CO_PILOT_ANIM_MODE_LEFT_HAND_FROM_REST_TO_UPPER_SWITCH;

				break;
			}
			case 1:
			{
				mode = CO_PILOT_ANIM_MODE_LEFT_HAND_FROM_REST_TO_CALCULATOR;

				break;
			}
			case 2:
			{
				mode = CO_PILOT_ANIM_MODE_LEFT_HAND_FROM_REST_TO_MASTER_ARM_SWITCH;

				break;
			}
			case 3:
			{
				mode = CO_PILOT_ANIM_MODE_HEAD_LOOK_DOWN;

				break;
			}
			case 4:
			{
				mode = CO_PILOT_ANIM_MODE_HEAD_LOOK_DOWN_LEFT;

				break;
			}
			case 5:
			{
				mode = CO_PILOT_ANIM_MODE_HEAD_LOOK_DOWN_RIGHT;

				break;
			}
			case 6:
			{
				mode = CO_PILOT_ANIM_MODE_HEAD_LOOK_UP;

				break;
			}
			case 7:
			{
				mode = CO_PILOT_ANIM_MODE_HEAD_LOOK_UP_LEFT;

				break;
			}
			case 8:
			{
				mode = CO_PILOT_ANIM_MODE_HEAD_LOOK_UP_RIGHT;

				break;
			}
			case 9:
			{
				mode = CO_PILOT_ANIM_MODE_HEAD_LOOK_LEFT;

				break;
			}
			case 10:
			{
				mode = CO_PILOT_ANIM_MODE_HEAD_LOOK_RIGHT;

				break;
			}
			default:
			{
				debug_fatal ("Invalid animation mode = %d", n);

				break;
			}
		}
	}

	return (mode);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static co_pilot_anim_modes get_random_co_pilot_datum_at_scope_anim_mode (void)
{
	static int
		previous_n = -1;

	int
		n;

	co_pilot_anim_modes
		mode;

	if (frand1 () < 0.25)
	{
		mode = CO_PILOT_ANIM_MODE_LEAN_BACK_FROM_SCOPE;
	}
	else
	{
		n = rand16 () % 3;

		if (n == previous_n)
		{
			n = rand16 () % 3;

			if (n == previous_n)
			{
				n = rand16 () % 3;
			}
		}

		previous_n = n;

		switch (n)
		{
			case 0:
			{
				mode = CO_PILOT_ANIM_MODE_LEFT_HAND_FROM_SCOPE_TO_MASTER_ARM_SWITCH;

				break;
			}
			case 1:
			{
				mode = CO_PILOT_ANIM_MODE_LEFT_HAND_FROM_SCOPE_TO_THUMBS_UP;

				break;
			}
			case 2:
			{
				mode = CO_PILOT_ANIM_MODE_RIGHT_HAND_FROM_SCOPE_TO_CYCLIC;

				break;
			}
			default:
			{
				debug_fatal ("Invalid animation mode = %d", n);

				break;
			}
		}
	}

	return (mode);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_co_pilot_head_animation (void)
{
	co_pilot_anim_frame += get_delta_time () * 0.5;

	if ((co_pilot_anim_frame >= 0.5) && (co_pilot_head_anim_pause > 0.0))
	{
		co_pilot_anim_frame = 0.5;

		co_pilot_head_anim_pause -= get_delta_time ();

		if (co_pilot_head_anim_pause < 0.0)
		{
			co_pilot_head_anim_pause = 0.0;
		}
	}
	else
	{
		if (co_pilot_anim_frame >= 1.0)
		{
			co_pilot_anim_frame = 1.0;

			co_pilot_anim_mode = CO_PILOT_ANIM_MODE_DATUM_AT_REST;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_co_pilot_animation (void)
{
	co_pilot_anim_data
		*anim_data;

	////////////////////////////////////////
	//
	// eject
	//
	////////////////////////////////////////

	if (get_local_entity_int_value (get_gunship_entity (), INT_TYPE_EJECTED))
	{
		if (get_crew_role () == CREW_ROLE_CO_PILOT)
		{
			if ((co_pilot_anim_mode != CO_PILOT_ANIM_MODE_BOTH_HANDS_PULL_EJECT) && (eject_stage == 0))
			{
				co_pilot_anim_mode = CO_PILOT_ANIM_MODE_BOTH_HANDS_PULL_EJECT;

				co_pilot_anim_frame = 0.0;

				co_pilot_anim_delay = get_reset_co_pilot_anim_delay ();

				co_pilot_head_anim_frame = NO_CO_PILOT_HEAD_ANIMATION;

				co_pilot_head_anim_pause = 0.0;

				if (night_vision_system_active)
				{
					co_pilot_nvg_anim_frame = NVG_ON;
				}
				else
				{
					co_pilot_nvg_anim_frame = NVG_OFF;
				}
			}
		}
	}

	//
	// cancel any animation while the player is the co-pilot (to stop the head moving around)
	//

	if (get_co_pilot_viewpoint_virtual_cockpit ())
	{
		co_pilot_anim_mode = CO_PILOT_ANIM_MODE_DATUM_AT_REST;

		co_pilot_anim_frame = 0.0;

		co_pilot_anim_delay = get_reset_co_pilot_anim_delay ();

		co_pilot_head_anim_frame = NO_CO_PILOT_HEAD_ANIMATION;

		co_pilot_head_anim_pause = 0.0;

		if (night_vision_system_active)
		{
			co_pilot_nvg_anim_frame = NVG_ON;
		}
		else
		{
			co_pilot_nvg_anim_frame = NVG_OFF;
		}
	}
	else
	{
		//
		// check for change NVG state
		//

		if (!get_local_entity_int_value (get_gunship_entity (), INT_TYPE_EJECTED))
		{
			if (co_pilot_anim_mode != CO_PILOT_ANIM_MODE_LEFT_HAND_FROM_REST_TO_NVG)
			{
				if
				(
					(night_vision_system_active && (co_pilot_nvg_anim_frame == NVG_OFF)) ||
					(!night_vision_system_active && (co_pilot_nvg_anim_frame == NVG_ON))
				)
				{
					if (co_pilot_anim_mode != CO_PILOT_ANIM_MODE_DATUM_AT_REST)
					{
						co_pilot_head_anim_pause = 0.0;
					}
					else
					{
						co_pilot_anim_mode = CO_PILOT_ANIM_MODE_LEFT_HAND_FROM_REST_TO_NVG;

						co_pilot_anim_frame = 0.0;

						co_pilot_anim_delay = get_reset_co_pilot_anim_delay ();

						co_pilot_head_anim_frame = NO_CO_PILOT_HEAD_ANIMATION;

						co_pilot_head_anim_pause = 0.0;
					}
				}
			}
		}
	}

	switch (co_pilot_anim_mode)
	{
		////////////////////////////////////////
		case CO_PILOT_ANIM_MODE_DATUM_AT_REST:
		////////////////////////////////////////
		{
			anim_data = &co_pilot_anim_mode_datum_at_rest_anim_data;

			co_pilot_anim_delay -= get_delta_time ();

			if (co_pilot_anim_delay <= 0.0)
			{
				co_pilot_anim_mode = get_random_co_pilot_datum_at_rest_anim_mode ();

				co_pilot_anim_frame = 0.0;

				co_pilot_anim_delay = get_reset_co_pilot_anim_delay ();

				co_pilot_head_anim_frame = NO_CO_PILOT_HEAD_ANIMATION;

				co_pilot_head_anim_pause = get_reset_co_pilot_head_anim_pause ();
			}
			else
			{
				co_pilot_anim_frame = 0.0;
			}

			break;
		}
		////////////////////////////////////////
		case CO_PILOT_ANIM_MODE_DATUM_AT_SCOPE:
		////////////////////////////////////////
		{
			anim_data = &co_pilot_anim_mode_datum_at_scope_anim_data;

			co_pilot_anim_delay -= get_delta_time ();

			if (co_pilot_anim_delay <= 0.0)
			{
				co_pilot_anim_mode = get_random_co_pilot_datum_at_scope_anim_mode ();

				co_pilot_anim_frame = 0.0;

				co_pilot_anim_delay = get_reset_co_pilot_anim_delay ();
			}
			else
			{
				co_pilot_anim_frame = 0.0;
			}

			break;
		}
		////////////////////////////////////////
		case CO_PILOT_ANIM_MODE_LEAN_FORWARD_TO_SCOPE:
		////////////////////////////////////////
		{
			if (co_pilot_nvg_anim_frame > NVG_OFF)
			{
				anim_data = &co_pilot_anim_mode_left_hand_from_rest_to_nvg_anim_data;

				co_pilot_nvg_anim_frame -= get_delta_time () * 0.5;

				if (co_pilot_nvg_anim_frame < NVG_OFF)
				{
					co_pilot_nvg_anim_frame = NVG_OFF;
				}

				co_pilot_anim_frame = co_pilot_nvg_anim_frame;
			}
			else
			{
				anim_data = &co_pilot_anim_mode_lean_forward_to_scope_anim_data;

				co_pilot_anim_frame += get_delta_time ();

				if (co_pilot_anim_frame >= 1.0)
				{
					co_pilot_anim_frame = 1.0;

					co_pilot_anim_mode = CO_PILOT_ANIM_MODE_DATUM_AT_SCOPE;
				}
			}

			break;
		}
		////////////////////////////////////////
		case CO_PILOT_ANIM_MODE_LEAN_BACK_FROM_SCOPE:
		////////////////////////////////////////
		{
			anim_data = &co_pilot_anim_mode_lean_back_from_scope_anim_data;

			co_pilot_anim_frame += get_delta_time ();

			if (co_pilot_anim_frame >= 1.0)
			{
				co_pilot_anim_frame = 1.0;

				co_pilot_anim_mode = CO_PILOT_ANIM_MODE_DATUM_AT_REST;
			}

			break;
		}
		////////////////////////////////////////
		case CO_PILOT_ANIM_MODE_LEFT_HAND_FROM_REST_TO_UPPER_SWITCH:
		////////////////////////////////////////
		{
			anim_data = &co_pilot_anim_mode_left_hand_from_rest_to_upper_switch_anim_data;

			co_pilot_anim_frame += get_delta_time () * 0.5;

			if (co_pilot_anim_frame >= 1.0)
			{
				co_pilot_anim_frame = 1.0;

				co_pilot_anim_mode = CO_PILOT_ANIM_MODE_DATUM_AT_REST;
			}

			break;
		}
		////////////////////////////////////////
		case CO_PILOT_ANIM_MODE_LEFT_HAND_FROM_REST_TO_CALCULATOR:
		////////////////////////////////////////
		{
			anim_data = &co_pilot_anim_mode_left_hand_from_rest_to_calculator_anim_data;

			co_pilot_anim_frame += get_delta_time () * 0.5;

			if (co_pilot_anim_frame >= 1.0)
			{
				co_pilot_anim_frame = 1.0;

				co_pilot_anim_mode = CO_PILOT_ANIM_MODE_DATUM_AT_REST;
			}

			break;
		}
		////////////////////////////////////////
		case CO_PILOT_ANIM_MODE_LEFT_HAND_FROM_REST_TO_MASTER_ARM_SWITCH:
		////////////////////////////////////////
		{
			anim_data = &co_pilot_anim_mode_left_hand_from_rest_to_master_arm_switch_anim_data;

			co_pilot_anim_frame += get_delta_time () * 0.5;

			if (co_pilot_anim_frame >= 1.0)
			{
				co_pilot_anim_frame = 1.0;

				co_pilot_anim_mode = CO_PILOT_ANIM_MODE_DATUM_AT_REST;
			}

			break;
		}
		////////////////////////////////////////
		case CO_PILOT_ANIM_MODE_LEFT_HAND_FROM_REST_TO_NVG:
		////////////////////////////////////////
		{
			anim_data = &co_pilot_anim_mode_left_hand_from_rest_to_nvg_anim_data;

			if (night_vision_system_active)
			{
				co_pilot_nvg_anim_frame += get_delta_time () * 0.5;

				if (co_pilot_nvg_anim_frame >= NVG_ON)
				{
					co_pilot_nvg_anim_frame = NVG_ON;

					co_pilot_anim_mode = CO_PILOT_ANIM_MODE_DATUM_AT_REST;
				}
			}
			else
			{
				co_pilot_nvg_anim_frame -= get_delta_time () * 0.5;

				if (co_pilot_nvg_anim_frame <= NVG_OFF)
				{
					co_pilot_nvg_anim_frame = NVG_OFF;

					co_pilot_anim_mode = CO_PILOT_ANIM_MODE_DATUM_AT_REST;
				}
			}

			co_pilot_anim_frame = co_pilot_nvg_anim_frame;

			break;
		}
		////////////////////////////////////////
		case CO_PILOT_ANIM_MODE_BOTH_HANDS_PULL_EJECT:
		////////////////////////////////////////
		{
			anim_data = &co_pilot_anim_mode_both_hands_pull_eject_anim_data;

			co_pilot_anim_frame += get_delta_time ();

			if (co_pilot_anim_frame >= 1.0)
			{
				//
				// (hold co-pilot anim at last frame until camera is outside)
				//

				co_pilot_anim_frame = 1.0;
			}

			//
			// eject sequence
			//

			eject_timer += get_delta_time ();

			switch (eject_stage)
			{
				////////////////////////////////////////
				case 0:
				////////////////////////////////////////
				{
					//
					// fire blades and doors after handle pulled
					//

					if (eject_timer > 1.0)
					{
						launch_client_server_weapon (get_gunship_entity (), ENTITY_SUB_TYPE_WEAPON_HOKUM_BLADE);
						launch_client_server_weapon (get_gunship_entity (), ENTITY_SUB_TYPE_WEAPON_HOKUM_LH_DOOR);
						launch_client_server_weapon (get_gunship_entity (), ENTITY_SUB_TYPE_WEAPON_HOKUM_RH_DOOR);

						eject_stage = 1;
					}

					break;
				}
				////////////////////////////////////////
				case 1:
				////////////////////////////////////////
				{
					//
					// delay then switch to external view
					//

					if (eject_timer > 1.5)
					{
						notify_local_entity (ENTITY_MESSAGE_SET_CAMERA_ACTION, get_camera_entity (), NULL, CAMERA_ACTION_EJECT);

						eject_stage = 2;
					}

					break;
				}
				////////////////////////////////////////
				case 2:
				////////////////////////////////////////
				{
					//
					// delay then eject crew
					//

					if (eject_timer > 2.0)
					{
						launch_client_server_weapon (get_gunship_entity (), ENTITY_SUB_TYPE_WEAPON_HOKUM_PILOT);
						launch_client_server_weapon (get_gunship_entity (), ENTITY_SUB_TYPE_WEAPON_HOKUM_CO_PILOT);

						co_pilot_anim_mode = CO_PILOT_ANIM_MODE_DATUM_AT_REST;

						eject_stage = 3;
					}

					break;
				}
				////////////////////////////////////////
				default:
				////////////////////////////////////////
				{
					debug_fatal ("Invalid eject stage = %d", eject_stage);

					break;
				}
			}

			break;
		}
		////////////////////////////////////////
		case CO_PILOT_ANIM_MODE_LEFT_HAND_FROM_SCOPE_TO_MASTER_ARM_SWITCH:
		////////////////////////////////////////
		{
			anim_data = &co_pilot_anim_mode_left_hand_from_scope_to_master_arm_switch_anim_data;

			co_pilot_anim_frame += get_delta_time () * 0.5;

			if (co_pilot_anim_frame >= 1.0)
			{
				co_pilot_anim_frame = 1.0;

				co_pilot_anim_mode = CO_PILOT_ANIM_MODE_DATUM_AT_SCOPE;
			}

			break;
		}
		////////////////////////////////////////
		case CO_PILOT_ANIM_MODE_LEFT_HAND_FROM_SCOPE_TO_THUMBS_UP:
		////////////////////////////////////////
		{
			anim_data = &co_pilot_anim_mode_left_hand_from_scope_to_thumbs_up_anim_data;

			co_pilot_anim_frame += get_delta_time () * 0.5;

			if (co_pilot_anim_frame >= 1.0)
			{
				co_pilot_anim_frame = 1.0;

				co_pilot_anim_mode = CO_PILOT_ANIM_MODE_DATUM_AT_SCOPE;
			}

			break;
		}
		////////////////////////////////////////
		case CO_PILOT_ANIM_MODE_RIGHT_HAND_FROM_SCOPE_TO_CYCLIC:
		////////////////////////////////////////
		{
			anim_data = &co_pilot_anim_mode_right_hand_from_scope_to_cyclic_anim_data;

			co_pilot_anim_frame += get_delta_time ();

			if (co_pilot_anim_frame >= 1.0)
			{
				co_pilot_anim_frame -= 1.0;

				if (co_pilot_anim_frame > 1.0)
				{
					co_pilot_anim_frame = 1.0;
				}

				if (rand16 () & 1)
				{
					anim_data = &co_pilot_anim_mode_right_hand_thumb_button1_anim_data;

					co_pilot_anim_mode = CO_PILOT_ANIM_MODE_RIGHT_HAND_THUMB_BUTTON1;
				}
				else
				{
					anim_data = &co_pilot_anim_mode_right_hand_thumb_button2_anim_data;

					co_pilot_anim_mode = CO_PILOT_ANIM_MODE_RIGHT_HAND_THUMB_BUTTON2;
				}
			}

			break;
		}
		////////////////////////////////////////
		case CO_PILOT_ANIM_MODE_RIGHT_HAND_THUMB_BUTTON1:
		////////////////////////////////////////
		{
			anim_data = &co_pilot_anim_mode_right_hand_thumb_button1_anim_data;

			co_pilot_anim_frame += get_delta_time ();

			if (co_pilot_anim_frame >= 1.0)
			{
				co_pilot_anim_frame -= 1.0;

				if (co_pilot_anim_frame > 1.0)
				{
					co_pilot_anim_frame = 1.0;
				}

				anim_data = &co_pilot_anim_mode_right_hand_from_cyclic_to_scope_anim_data;

				co_pilot_anim_mode = CO_PILOT_ANIM_MODE_RIGHT_HAND_FROM_CYCLIC_TO_SCOPE;
			}

			break;
		}
		////////////////////////////////////////
		case CO_PILOT_ANIM_MODE_RIGHT_HAND_THUMB_BUTTON2:
		////////////////////////////////////////
		{
			anim_data = &co_pilot_anim_mode_right_hand_thumb_button2_anim_data;

			co_pilot_anim_frame += get_delta_time ();

			if (co_pilot_anim_frame >= 1.0)
			{
				co_pilot_anim_frame -= 1.0;

				if (co_pilot_anim_frame > 1.0)
				{
					co_pilot_anim_frame = 1.0;
				}

				anim_data = &co_pilot_anim_mode_right_hand_from_cyclic_to_scope_anim_data;

				co_pilot_anim_mode = CO_PILOT_ANIM_MODE_RIGHT_HAND_FROM_CYCLIC_TO_SCOPE;
			}

			break;
		}
		////////////////////////////////////////
		case CO_PILOT_ANIM_MODE_RIGHT_HAND_FROM_CYCLIC_TO_SCOPE:
		////////////////////////////////////////
		{
			anim_data = &co_pilot_anim_mode_right_hand_from_cyclic_to_scope_anim_data;

			co_pilot_anim_frame += get_delta_time ();

			if (co_pilot_anim_frame >= 1.0)
			{
				co_pilot_anim_frame = 1.0;

				co_pilot_anim_mode = CO_PILOT_ANIM_MODE_DATUM_AT_SCOPE;
			}

			break;
		}
		////////////////////////////////////////
		case CO_PILOT_ANIM_MODE_HEAD_LOOK_DOWN:
		////////////////////////////////////////
		{
			anim_data = &co_pilot_anim_mode_head_look_down_anim_data;

			update_co_pilot_head_animation ();

			break;
		}
		////////////////////////////////////////
		case CO_PILOT_ANIM_MODE_HEAD_LOOK_DOWN_LEFT:
		////////////////////////////////////////
		{
			anim_data = &co_pilot_anim_mode_head_look_down_left_anim_data;

			update_co_pilot_head_animation ();

			break;
		}
		////////////////////////////////////////
		case CO_PILOT_ANIM_MODE_HEAD_LOOK_DOWN_RIGHT:
		////////////////////////////////////////
		{
			anim_data = &co_pilot_anim_mode_head_look_down_right_anim_data;

			update_co_pilot_head_animation ();

			break;
		}
		////////////////////////////////////////
		case CO_PILOT_ANIM_MODE_HEAD_LOOK_UP:
		////////////////////////////////////////
		{
			anim_data = &co_pilot_anim_mode_head_look_up_anim_data;

			update_co_pilot_head_animation ();

			break;
		}
		////////////////////////////////////////
		case CO_PILOT_ANIM_MODE_HEAD_LOOK_UP_LEFT:
		////////////////////////////////////////
		{
			anim_data = &co_pilot_anim_mode_head_look_up_left_anim_data;

			update_co_pilot_head_animation ();

			break;
		}
		////////////////////////////////////////
		case CO_PILOT_ANIM_MODE_HEAD_LOOK_UP_RIGHT:
		////////////////////////////////////////
		{
			anim_data = &co_pilot_anim_mode_head_look_up_right_anim_data;

			update_co_pilot_head_animation ();

			break;
		}
		////////////////////////////////////////
		case CO_PILOT_ANIM_MODE_HEAD_LOOK_LEFT:
		////////////////////////////////////////
		{
			anim_data = &co_pilot_anim_mode_head_look_left_anim_data;

			update_co_pilot_head_animation ();

			break;
		}
		////////////////////////////////////////
		case CO_PILOT_ANIM_MODE_HEAD_LOOK_RIGHT:
		////////////////////////////////////////
		{
			anim_data = &co_pilot_anim_mode_head_look_right_anim_data;

			update_co_pilot_head_animation ();

			break;
		}
	}

	set_co_pilot_animation (anim_data, co_pilot_anim_frame);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MAX_ROLL	((float) (rad (10.0)))

static void update_co_pilot_head_tilt_animation (void)
{
	float
		co_pilot_head_tilt_angle,
		frame,
		anim_frame;

	ASSERT (co_pilot_anim_mode == CO_PILOT_ANIM_MODE_DATUM_AT_REST);

	if (co_pilot_anim_delay < 1.0)
	{
		co_pilot_head_tilt_angle = 0.0;
	}
	else
	{
		co_pilot_head_tilt_angle = get_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_ROLL);
	}

	co_pilot_head_tilt_angle = bound (co_pilot_head_tilt_angle, -MAX_ROLL, MAX_ROLL);

	co_pilot_head_tilt_angle = (co_pilot_head_tilt_angle + previous_co_pilot_head_tilt_angle) * 0.5;

	if (co_pilot_head_tilt_angle >= 0.0)
	{
		frame = co_pilot_head_tilt_angle * (1.0 / MAX_ROLL);

		anim_frame = ((CO_PILOT_HEAD_TILT_RIGHT_ANIM_END - CO_PILOT_HEAD_TILT_RIGHT_ANIM_START) * frame) + CO_PILOT_HEAD_TILT_RIGHT_ANIM_START;

		anim_frame = bound (anim_frame, CO_PILOT_HEAD_TILT_RIGHT_ANIM_START, CO_PILOT_HEAD_TILT_RIGHT_ANIM_END);
	}
	else
	{
		frame = -co_pilot_head_tilt_angle * (1.0 / MAX_ROLL);

		anim_frame = ((CO_PILOT_HEAD_TILT_LEFT_ANIM_END - CO_PILOT_HEAD_TILT_LEFT_ANIM_START) * frame) + CO_PILOT_HEAD_TILT_LEFT_ANIM_START;

		anim_frame = bound (anim_frame, CO_PILOT_HEAD_TILT_LEFT_ANIM_START, CO_PILOT_HEAD_TILT_LEFT_ANIM_END);
	}

	animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_WSO_HEAD, anim_frame);

	previous_co_pilot_head_tilt_angle = co_pilot_head_tilt_angle;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// MAIN
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_hokum_co_pilot_animation (void)
{
	#if DEBUG_MODULE

	debug_colour_watch (COLOUR_AMBER, "co_pilot_anim_mode = %d", MT_INT, &co_pilot_anim_mode);
	debug_colour_watch (COLOUR_AMBER, "co_pilot_anim_frame = %.2f", MT_FLOAT, &co_pilot_anim_frame);
	debug_colour_watch (COLOUR_AMBER, "co_pilot_anim_delay = %.2f", MT_FLOAT, &co_pilot_anim_delay);

	debug_colour_watch (COLOUR_AMBER, "co_pilot_head_anim_frame = %.2f", MT_FLOAT, &co_pilot_head_anim_frame);
	debug_colour_watch (COLOUR_AMBER, "co_pilot_head_anim_pause = %.2f", MT_FLOAT, &co_pilot_head_anim_pause);

	debug_colour_watch (COLOUR_AMBER, "night_vision_system_active = %d", MT_INT, &night_vision_system_active);
	debug_colour_watch (COLOUR_AMBER, "co_pilot_nvg_anim_frame = %.2f", MT_FLOAT, &co_pilot_nvg_anim_frame);

	#endif

	co_pilot_anim_mode						= CO_PILOT_ANIM_MODE_DATUM_AT_REST;
	co_pilot_anim_frame						= 0.0;
	co_pilot_anim_delay						= get_reset_co_pilot_anim_delay ();

	co_pilot_head_anim_frame				= NO_CO_PILOT_HEAD_ANIMATION;
	co_pilot_head_anim_pause				= 0.0;

	previous_co_pilot_head_tilt_angle	= 0.0;

	co_pilot_nvg_anim_frame					= NVG_OFF;

	eject_timer									= 0.0;
	eject_stage									= 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_hokum_co_pilot_animation (void)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_hokum_co_pilot_animation (void)
{
	ASSERT (get_gunship_entity ());

	ASSERT (current_flight_dynamics);

	ASSERT (virtual_cockpit_inst3d);

	update_co_pilot_animation ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_hokum_co_pilot_head_position (void)
{
	int
		show_co_pilot_head;

	object_3d_sub_object_search_data
		search;

	ASSERT (get_gunship_entity ());

	ASSERT (virtual_cockpit_inst3d);

	show_co_pilot_head = !get_co_pilot_viewpoint_virtual_cockpit ();

	search.search_depth = 0;
	search.search_object = virtual_cockpit_inst3d;
	search.sub_object_index = OBJECT_3D_SUB_OBJECT_WSO_HEAD;

	if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		search.result_sub_object->visible_object = show_co_pilot_head;

		if (show_co_pilot_head)
		{
			if (co_pilot_head_anim_frame != NO_CO_PILOT_HEAD_ANIMATION)
			{
				animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_WSO_HEAD, co_pilot_head_anim_frame);
			}
			else
			{
				if (co_pilot_anim_mode == CO_PILOT_ANIM_MODE_DATUM_AT_REST)
				{
					update_co_pilot_head_tilt_animation ();
				}
				else
				{
					search.result_sub_object->relative_heading = 0.0;
					search.result_sub_object->relative_pitch = co_pilot_head_pitch_datum;
					search.result_sub_object->relative_roll = 0.0;

					previous_co_pilot_head_tilt_angle = 0.0;
				}
			}
		}
	}
	else
	{
		debug_fatal ("Failed to locate co-pilot's head in virtual cockpit");
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_hokum_co_pilot_head_pitch_datum (void)
{
	float
		relative_pitch;

	object_3d_sub_object_search_data
		search;

	ASSERT (get_gunship_entity ());

	ASSERT (virtual_cockpit_inst3d);

	search.search_depth = 0;
	search.search_object = virtual_cockpit_inst3d;
	search.sub_object_index = OBJECT_3D_SUB_OBJECT_WSO_HEAD;

	if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		relative_pitch = search.result_sub_object->relative_pitch;
	}
	else
	{
		debug_fatal ("Failed to locate co-pilot's head in virtual cockpit");
	}

	return (relative_pitch);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reset_hokum_co_pilot_eject_sequence (void)
{
	eject_timer = 0.0;

	eject_stage = 0;

	//
	// set anim
	//

	co_pilot_anim_mode = CO_PILOT_ANIM_MODE_DATUM_AT_REST;

	co_pilot_anim_frame = 0.0;

	co_pilot_anim_delay = get_reset_co_pilot_anim_delay ();

	co_pilot_head_anim_frame = NO_CO_PILOT_HEAD_ANIMATION;

	co_pilot_head_anim_pause = 0.0;

	if (night_vision_system_active)
	{
		co_pilot_nvg_anim_frame = NVG_ON;
	}
	else
	{
		co_pilot_nvg_anim_frame = NVG_OFF;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
