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

#define LAST_FRAME																((float) (1500.0))

#define PILOT_COLLECTIVE_ANIM_START											((float) (0.0 / LAST_FRAME))
#define PILOT_COLLECTIVE_ANIM_END											((float) (60.0 / LAST_FRAME))

#define PILOT_LEG_ANIM_START													((float) (0.0 / LAST_FRAME))
#define PILOT_LEG_ANIM_END														((float) (60.0 / LAST_FRAME))

#define PILOT_HEAD_TILT_LEFT_TO_RIGHT_ANIM_START						((float) (0.0 / LAST_FRAME))
#define PILOT_HEAD_TILT_LEFT_TO_RIGHT_ANIM_END							((float) (60.0 / LAST_FRAME))

#define PILOT_CONTROLS_TO_REST_ANIM_START									((float) (61.0 / LAST_FRAME))
#define PILOT_CONTROLS_TO_REST_ANIM_END									((float) (90.0 / LAST_FRAME))

#define PILOT_RIGHT_HAND_FROM_REST_TO_RH_MFD_BUTTON_ANIM_START		((float) (90.0 / LAST_FRAME))
#define PILOT_RIGHT_HAND_FROM_REST_TO_RH_MFD_BUTTON_ANIM_END		((float) (180.0 / LAST_FRAME))

#define PILOT_LEFT_HAND_FROM_REST_TO_LH_MFD_BUTTON_ANIM_START		((float) (180.0 / LAST_FRAME))
#define PILOT_LEFT_HAND_FROM_REST_TO_LH_MFD_BUTTON_ANIM_END			((float) (240.0 / LAST_FRAME))

#define PILOT_RIGHT_HAND_FROM_REST_TO_RH_CONSOLE_ANIM_START	 		((float) (240.0 / LAST_FRAME))
#define PILOT_RIGHT_HAND_FROM_REST_TO_RH_CONSOLE_ANIM_END			((float) (345.0 / LAST_FRAME))

#define PILOT_RIGHT_HAND_FROM_REST_TO_CALCULATOR_ANIM_START	 		((float) (345.0 / LAST_FRAME))
#define PILOT_RIGHT_HAND_FROM_REST_TO_CALCULATOR_ANIM_END			((float) (420.0 / LAST_FRAME))

#define PILOT_LEFT_HAND_FROM_REST_TO_LH_CONSOLE_ANIM_START	 		((float) (420.0 / LAST_FRAME))
#define PILOT_LEFT_HAND_FROM_REST_TO_LH_CONSOLE_ANIM_END				((float) (510.0 / LAST_FRAME))

#define PILOT_LEFT_HAND_FROM_REST_TO_RH_SMALL_MFD_ANIM_START		((float) (510.0 / LAST_FRAME))
#define PILOT_LEFT_HAND_FROM_REST_TO_RH_SMALL_MFD_ANIM_END			((float) (600.0 / LAST_FRAME))

#define PILOT_LEFT_HAND_FROM_REST_TO_LH_MFD_TOP_BUTTON_ANIM_START	((float) (600.0 / LAST_FRAME))
#define PILOT_LEFT_HAND_FROM_REST_TO_LH_MFD_TOP_BUTTON_ANIM_END	((float) (690.0 / LAST_FRAME))

// 690.0 to 1020.0 - no frames

#define PILOT_HEAD_LOOK_DOWN_LEFT_ANIM_START                   	((float) (1020.0 / LAST_FRAME))
#define PILOT_HEAD_LOOK_DOWN_LEFT_ANIM_END								((float) (1080.0 / LAST_FRAME))

#define PILOT_HEAD_LOOK_DOWN_RIGHT_ANIM_START							((float) (1080.0 / LAST_FRAME))
#define PILOT_HEAD_LOOK_DOWN_RIGHT_ANIM_END                    	((float) (1140.0 / LAST_FRAME))

#define PILOT_HEAD_LOOK_DOWN_ANIM_START									((float) (1140.0 / LAST_FRAME))
#define PILOT_HEAD_LOOK_DOWN_ANIM_END										((float) (1200.0 / LAST_FRAME))

#define PILOT_HEAD_LOOK_UP_ANIM_START                          	((float) (1200.0 / LAST_FRAME))
#define PILOT_HEAD_LOOK_UP_ANIM_END                            	((float) (1260.0 / LAST_FRAME))

#define PILOT_HEAD_LOOK_LEFT_ANIM_START      	               	((float) (1260.0 / LAST_FRAME))
#define PILOT_HEAD_LOOK_LEFT_ANIM_END           	            	((float) (1320.0 / LAST_FRAME))

#define PILOT_HEAD_LOOK_RIGHT_ANIM_START									((float) (1320.0 / LAST_FRAME))
#define PILOT_HEAD_LOOK_RIGHT_ANIM_END       	               	((float) (1380.0 / LAST_FRAME))

#define PILOT_HEAD_LOOK_UP_LEFT_ANIM_START     	               	((float) (1380.0 / LAST_FRAME))
#define PILOT_HEAD_LOOK_UP_LEFT_ANIM_END          	            	((float) (1440.0 / LAST_FRAME))

#define PILOT_HEAD_LOOK_UP_RIGHT_ANIM_START								((float) (1440.0 / LAST_FRAME))
#define PILOT_HEAD_LOOK_UP_RIGHT_ANIM_END      	               	((float) (1500.0 / LAST_FRAME))

#define PILOT_ANIM_DEFAULT														(PILOT_CONTROLS_TO_REST_ANIM_END)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct PILOT_ANIM_DATA
{
	float
		start_frame,
		end_frame,
		cyclic_x_position,
		cyclic_y_position,
		collective_position,
		pedal_position;

	unsigned int
		right_hand_on_cyclic,		:1,
		left_hand_on_collective,	:1,
		feet_on_pedals,				:1,
		animate_head 					:1,
		animate_chest	  				:1,
		animate_left_arm	  			:1,
		animate_right_arm				:1,
		animate_legs		 			:1;
};

typedef struct PILOT_ANIM_DATA pilot_anim_data;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int
	pilot_animation_updated;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define NO_PILOT_HEAD_ANIMATION	((float) (-1.0))

static float
	pilot_head_anim_frame,
	pilot_head_anim_pause,
	previous_pilot_head_tilt_angle;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// PILOT MAIN ANIMATIONS
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum PILOT_MAIN_ANIM_MODES
{
	PILOT_MAIN_ANIM_MODE_HANDS_OFF_CONTROLS,
	PILOT_MAIN_ANIM_MODE_TAKING_CONTROLS,
	PILOT_MAIN_ANIM_MODE_MOVING_CONTROLS_FROM_CENTRE1,
	PILOT_MAIN_ANIM_MODE_MOVING_CONTROLS_FROM_CENTRE2,
	PILOT_MAIN_ANIM_MODE_HANDS_ON_CONTROLS,
	PILOT_MAIN_ANIM_MODE_MOVING_CONTROLS_TO_CENTRE1,
	PILOT_MAIN_ANIM_MODE_MOVING_CONTROLS_TO_CENTRE2,
	PILOT_MAIN_ANIM_MODE_RELEASING_CONTROLS,
	NUM_PILOT_MAIN_ANIM_MODES
};

typedef enum PILOT_MAIN_ANIM_MODES pilot_main_anim_modes;

static pilot_main_anim_modes
	pilot_main_anim_mode;

static float
	pilot_main_anim_frame;

static float
	cyclic_x_position,
	cyclic_y_position,
	collective_position,
	pedal_position,
	previous_cyclic_x_position,
	previous_cyclic_y_position,
	previous_collective_position,
	previous_pedal_position;

////////////////////////////////////////
//
// PILOT_MAIN_ANIM_MODE_HANDS_OFF_CONTROLS
//
////////////////////////////////////////

//
// see PILOT REST ANIMATIONS
//

////////////////////////////////////////
//
// PILOT_MAIN_ANIM_MODE_TAKING_CONTROLS
//
////////////////////////////////////////

static pilot_anim_data
	pilot_main_anim_mode_taking_controls_anim_data =
	{
		PILOT_CONTROLS_TO_REST_ANIM_START,			 								// start_frame
		PILOT_CONTROLS_TO_REST_ANIM_END,				 								// end_frame
		0.5,													 								// cyclic_x_position
		0.5,													 								// cyclic_y_position
		0.5,													 								// collective_position
		0.5,													 								// pedal_position
		FALSE,																				// right_hand_on_cyclic
		FALSE,																				// left_hand_on_collective
		FALSE,																				// feet_on_pedals
		FALSE,												 								// animate_head
		FALSE,												 								// animate_chest
		TRUE,													 								// animate_left_arm
		TRUE,													 								// animate_right_arm
		FALSE,																				// animate_legs
	};

////////////////////////////////////////
//
// PILOT_MAIN_ANIM_MODE_MOVING_CONTROLS_FROM_CENTRE1
//
////////////////////////////////////////

static pilot_anim_data
	pilot_main_anim_mode_moving_controls_from_centre1_anim_data =
	{
		0.0,																					// start_frame
		0.0,																					// end_frame
		0.5,																					// cyclic_x_position
		0.5,																					// cyclic_y_position
		0.5,																					// collective_position
		0.5,																					// pedal_position
		TRUE,																					// right_hand_on_cyclic
		TRUE,																					// left_hand_on_collective
		TRUE,																					// feet_on_pedals
		FALSE,																				// animate_head
		FALSE,																				// animate_chest
		FALSE,																				// animate_left_arm
		FALSE,																				// animate_right_arm
		FALSE,																				// animate_legs
	};

////////////////////////////////////////
//
// PILOT_MAIN_ANIM_MODE_MOVING_CONTROLS_FROM_CENTRE2
//
////////////////////////////////////////

static pilot_anim_data
	pilot_main_anim_mode_moving_controls_from_centre2_anim_data =
	{
		0.0,																					// start_frame
		0.0,																					// end_frame
		0.0,																					// cyclic_x_position
		0.0,																					// cyclic_y_position
		0.0,																					// collective_position
		0.0,																					// pedal_position
		TRUE,																					// right_hand_on_cyclic
		TRUE,																					// left_hand_on_collective
		TRUE,																					// feet_on_pedals
		FALSE,																				// animate_head
		FALSE,																				// animate_chest
		FALSE,																				// animate_left_arm
		FALSE,																				// animate_right_arm
		FALSE,																				// animate_legs
	};

////////////////////////////////////////
//
// PILOT_MAIN_ANIM_MODE_HANDS_ON_CONTROLS
//
////////////////////////////////////////

static pilot_anim_data
	pilot_main_anim_mode_hands_on_controls_anim_data =
	{
		0.0,																					// start_frame
		0.0,																					// end_frame
		0.0,																					// cyclic_x_position
		0.0,																					// cyclic_y_position
		0.0,																					// collective_position
		0.0,																					// pedal_position
		TRUE,																					// right_hand_on_cyclic
		TRUE,																					// left_hand_on_collective
		TRUE,																					// feet_on_pedals
		FALSE,																				// animate_head
		FALSE,																				// animate_chest
		FALSE,																				// animate_left_arm
		FALSE,																				// animate_right_arm
		FALSE,																				// animate_legs
	};

////////////////////////////////////////
//
// PILOT_MAIN_ANIM_MODE_MOVING_CONTROLS_TO_CENTRE1
//
////////////////////////////////////////

static pilot_anim_data
	pilot_main_anim_mode_moving_controls_to_centre1_anim_data =
	{
		0.0,																					// start_frame
		0.0,																					// end_frame
		0.0,																					// cyclic_x_position
		0.0,																					// cyclic_y_position
		0.0,																					// collective_position
		0.0,																					// pedal_position
		TRUE,																					// right_hand_on_cyclic
		TRUE,																					// left_hand_on_collective
		TRUE,																					// feet_on_pedals
		FALSE,																				// animate_head
		FALSE,																				// animate_chest
		FALSE,																				// animate_left_arm
		FALSE,																				// animate_right_arm
		FALSE,																				// animate_legs
	};

////////////////////////////////////////
//
// PILOT_MAIN_ANIM_MODE_MOVING_CONTROLS_TO_CENTRE2
//
////////////////////////////////////////

static pilot_anim_data
	pilot_main_anim_mode_moving_controls_to_centre2_anim_data =
	{
		0.0,																					// start_frame
		0.0,																					// end_frame
		0.5,																					// cyclic_x_position
		0.5,																					// cyclic_y_position
		0.5,																					// collective_position
		0.5,																					// pedal_position
		TRUE,																					// right_hand_on_cyclic
		TRUE,																					// left_hand_on_collective
		TRUE,																					// feet_on_pedals
		FALSE,																				// animate_head
		FALSE,																				// animate_chest
		FALSE,																				// animate_left_arm
		FALSE,																				// animate_right_arm
		FALSE,																				// animate_legs
	};

////////////////////////////////////////
//
// PILOT_MAIN_ANIM_MODE_RELEASING_CONTROLS
//
////////////////////////////////////////

static pilot_anim_data
	pilot_main_anim_mode_releasing_controls_anim_data =
	{
		PILOT_CONTROLS_TO_REST_ANIM_START,									  		// start_frame
		PILOT_CONTROLS_TO_REST_ANIM_END,												// end_frame
		0.5,																					// cyclic_x_position
		0.5,																					// cyclic_y_position
		0.5,																					// collective_position
		0.5,																					// pedal_position
		FALSE,																				// right_hand_on_cyclic
		FALSE,																				// left_hand_on_collective
		FALSE,																				// feet_on_pedals
		FALSE,																				// animate_head
		FALSE,																				// animate_chest
		TRUE,																					// animate_left_arm
		TRUE,																					// animate_right_arm
		FALSE,																				// animate_legs
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_pilot_hands_off_controls (void);

static void update_pilot_taking_controls (void);

static void update_pilot_moving_controls_from_centre1 (void);

static void update_pilot_moving_controls_from_centre2 (void);

static void update_pilot_hands_on_controls (void);

static void update_pilot_moving_controls_to_centre1 (void);

static void update_pilot_moving_controls_to_centre2 (void);

static void update_pilot_releasing_controls (void);

static void update_pilot_collective_to_centre1 (void);

static void update_pilot_collective_to_centre2 (void);

static void update_pilot_collective_from_centre1 (void);

static void update_pilot_collective_from_centre1 (void);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// PILOT REST ANIMATIONS
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum PILOT_REST_ANIM_MODES
{
	PILOT_REST_ANIM_MODE_NONE,
	PILOT_REST_ANIM_MODE_RIGHT_HAND_TO_RH_MFD_BUTTON,
	PILOT_REST_ANIM_MODE_LEFT_HAND_TO_LH_MFD_BUTTON,
	PILOT_REST_ANIM_MODE_RIGHT_HAND_TO_RH_CONSOLE,
	PILOT_REST_ANIM_MODE_LEFT_HAND_TO_LH_CONSOLE,
	PILOT_REST_ANIM_MODE_RIGHT_HAND_TO_CALCULATOR,
	PILOT_REST_ANIM_MODE_LEFT_HAND_TO_RH_SMALL_MFD_BUTTON,
	PILOT_REST_ANIM_MODE_LEFT_HAND_TO_LH_MFD_TOP_BUTTON,
	PILOT_REST_ANIM_MODE_HEAD_LOOK_DOWN,
	PILOT_REST_ANIM_MODE_HEAD_LOOK_DOWN_LEFT,
	PILOT_REST_ANIM_MODE_HEAD_LOOK_DOWN_RIGHT,
	PILOT_REST_ANIM_MODE_HEAD_LOOK_UP,
	PILOT_REST_ANIM_MODE_HEAD_LOOK_UP_LEFT,
	PILOT_REST_ANIM_MODE_HEAD_LOOK_UP_RIGHT,
	PILOT_REST_ANIM_MODE_HEAD_LOOK_LEFT,
	PILOT_REST_ANIM_MODE_HEAD_LOOK_RIGHT,
	NUM_PILOT_REST_ANIM_MODES
};

typedef enum PILOT_REST_ANIM_MODES pilot_rest_anim_modes;

static pilot_rest_anim_modes
	pilot_rest_anim_mode,
	previous_random_pilot_rest_anim_mode;

static float
	pilot_rest_anim_frame,
	pilot_rest_anim_delay;

////////////////////////////////////////
//
// PILOT_REST_ANIM_MODE_NONE
//
////////////////////////////////////////

static pilot_anim_data
	pilot_rest_anim_mode_none_anim_data =
	{
		0.0,																					// start_frame
		0.0,																					// end_frame
		0.5,																					// cyclic_x_position
		0.5,																					// cyclic_y_position
		0.5,																					// collective_position
		0.5,																					// pedal_position
		FALSE,																				// right_hand_on_cyclic
		FALSE,																				// left_hand_on_collective
		FALSE,																				// feet_on_pedals
		FALSE,																				// animate_head
		FALSE,																				// animate_chest
		FALSE,																				// animate_left_arm
		FALSE,																				// animate_right_arm
		FALSE,																				// animate_legs
	};

////////////////////////////////////////
//
// PILOT_REST_ANIM_MODE_RIGHT_HAND_TO_RH_MFD_BUTTON
//
////////////////////////////////////////

static pilot_anim_data
	pilot_rest_anim_mode_right_hand_to_rh_mfd_button_anim_data =
	{
		PILOT_RIGHT_HAND_FROM_REST_TO_RH_MFD_BUTTON_ANIM_START,				// start_frame
		PILOT_RIGHT_HAND_FROM_REST_TO_RH_MFD_BUTTON_ANIM_END,					// end_frame
		0.5,																					// cyclic_x_position
		0.5,																					// cyclic_y_position
		0.5,																					// collective_position
		0.5,																					// pedal_position
		FALSE,																				// right_hand_on_cyclic
		FALSE,																				// left_hand_on_collective
		FALSE,																				// feet_on_pedals
		TRUE,																					// animate_head
		TRUE,																					// animate_chest
		TRUE,																					// animate_left_arm
		TRUE,																					// animate_right_arm
		FALSE,																				// animate_legs
	};

////////////////////////////////////////
//
// PILOT_REST_ANIM_MODE_LEFT_HAND_TO_LH_MFD_BUTTON
//
////////////////////////////////////////

static pilot_anim_data
	pilot_rest_anim_mode_left_hand_to_lh_mfd_button_anim_data =
	{
		PILOT_LEFT_HAND_FROM_REST_TO_LH_MFD_BUTTON_ANIM_START,				// start_frame
		PILOT_LEFT_HAND_FROM_REST_TO_LH_MFD_BUTTON_ANIM_END,					// end_frame
		0.5,																					// cyclic_x_position
		0.5,																					// cyclic_y_position
		0.5,																					// collective_position
		0.5,																					// pedal_position
		FALSE,																				// right_hand_on_cyclic
		FALSE,																				// left_hand_on_collective
		FALSE,																				// feet_on_pedals
		TRUE,																					// animate_head
		TRUE,			  																		// animate_chest
		TRUE,																					// animate_left_arm
		TRUE,																					// animate_right_arm
		FALSE,																				// animate_legs
	};

////////////////////////////////////////
//
// PILOT_REST_ANIM_MODE_RIGHT_HAND_TO_RH_CONSOLE
//
////////////////////////////////////////

static pilot_anim_data
	pilot_rest_anim_mode_right_hand_to_rh_console_anim_data =
	{
		PILOT_RIGHT_HAND_FROM_REST_TO_RH_CONSOLE_ANIM_START,					// start_frame
		PILOT_RIGHT_HAND_FROM_REST_TO_RH_CONSOLE_ANIM_END,						// end_frame
		0.5,																					// cyclic_x_position
		0.5,																					// cyclic_y_position
		0.5,																					// collective_position
		0.5,																					// pedal_position
		FALSE,																				// right_hand_on_cyclic
		FALSE,																				// left_hand_on_collective
		FALSE,																				// feet_on_pedals
		TRUE,																					// animate_head
		TRUE,			  																		// animate_chest
		TRUE,																					// animate_left_arm
		TRUE,																					// animate_right_arm
		FALSE,																				// animate_legs
	};

////////////////////////////////////////
//
// PILOT_REST_ANIM_MODE_LEFT_HAND_TO_LH_CONSOLE
//
////////////////////////////////////////

static pilot_anim_data
	pilot_rest_anim_mode_left_hand_to_lh_console_anim_data =
	{
		PILOT_LEFT_HAND_FROM_REST_TO_LH_CONSOLE_ANIM_START,					// start_frame
		PILOT_LEFT_HAND_FROM_REST_TO_LH_CONSOLE_ANIM_END,						// end_frame
		0.5,																					// cyclic_x_position
		0.5,																					// cyclic_y_position
		0.5,																					// collective_position
		0.5,																					// pedal_position
		FALSE,																				// right_hand_on_cyclic
		FALSE,																				// left_hand_on_collective
		FALSE,																				// feet_on_pedals
		TRUE,																					// animate_head
		TRUE,																					// animate_chest
		TRUE,																					// animate_left_arm
		TRUE,																					// animate_right_arm
		FALSE,																				// animate_legs
	};

////////////////////////////////////////
//
// PILOT_REST_ANIM_MODE_RIGHT_HAND_TO_CALCULATOR
//
////////////////////////////////////////

static pilot_anim_data
	pilot_rest_anim_mode_right_hand_to_calculator_anim_data =
	{
		PILOT_RIGHT_HAND_FROM_REST_TO_CALCULATOR_ANIM_START,					// start_frame
		PILOT_RIGHT_HAND_FROM_REST_TO_CALCULATOR_ANIM_END,						// end_frame
		0.5,																					// cyclic_x_position
		0.5,																					// cyclic_y_position
		0.5,																					// collective_position
		0.5,																					// pedal_position
		FALSE,																				// right_hand_on_cyclic
		FALSE,																				// left_hand_on_collective
		FALSE,																				// feet_on_pedals
		TRUE,																					// animate_head
		TRUE,			  																		// animate_chest
		TRUE,																					// animate_left_arm
		TRUE,																					// animate_right_arm
		FALSE,																				// animate_legs
	};

////////////////////////////////////////
//
// PILOT_REST_ANIM_MODE_LEFT_HAND_TO_RH_SMALL_MFD_BUTTON
//
////////////////////////////////////////

static pilot_anim_data
	pilot_rest_anim_mode_left_hand_to_rh_small_mfd_button_anim_data =
	{
		PILOT_LEFT_HAND_FROM_REST_TO_RH_SMALL_MFD_ANIM_START,					// start_frame
		PILOT_LEFT_HAND_FROM_REST_TO_RH_SMALL_MFD_ANIM_END,					// end_frame
		0.5,																					// cyclic_x_position
		0.5,																					// cyclic_y_position
		0.5,																					// collective_position
		0.5,																					// pedal_position
		FALSE,																				// right_hand_on_cyclic
		FALSE,																				// left_hand_on_collective
		FALSE,																				// feet_on_pedals
		TRUE,																					// animate_head
		TRUE,																					// animate_chest
		TRUE,																					// animate_left_arm
		TRUE,																					// animate_right_arm
		FALSE,																				// animate_legs
	};

////////////////////////////////////////
//
// PILOT_REST_ANIM_MODE_LEFT_HAND_TO_LH_MFD_TOP_BUTTON
//
////////////////////////////////////////

static pilot_anim_data
	pilot_rest_anim_mode_left_hand_to_lh_mfd_top_button_anim_data =
	{
		PILOT_LEFT_HAND_FROM_REST_TO_LH_MFD_TOP_BUTTON_ANIM_START,			// start_frame
		PILOT_LEFT_HAND_FROM_REST_TO_LH_MFD_TOP_BUTTON_ANIM_END,				// end_frame
		0.5,																					// cyclic_x_position
		0.5,																					// cyclic_y_position
		0.5,																					// collective_position
		0.5,																					// pedal_position
		FALSE,																				// right_hand_on_cyclic
		FALSE,																				// left_hand_on_collective
		FALSE,																				// feet_on_pedals
		TRUE,																					// animate_head
		TRUE,																					// animate_chest
		TRUE,																					// animate_left_arm
		TRUE,																					// animate_right_arm
		FALSE,																				// animate_legs
	};

////////////////////////////////////////
//
// PILOT_REST_ANIM_MODE_HEAD_LOOK_DOWN
//
////////////////////////////////////////

static pilot_anim_data
	pilot_rest_anim_mode_head_look_down_anim_data =
	{
		PILOT_HEAD_LOOK_DOWN_ANIM_START,												// start_frame
		PILOT_HEAD_LOOK_DOWN_ANIM_END,		  										// end_frame
		0.5,																					// cyclic_x_position
		0.5,																					// cyclic_y_position
		0.5,																					// collective_position
		0.5,																					// pedal_position
		FALSE,																				// right_hand_on_cyclic
		FALSE,																				// left_hand_on_collective
		FALSE,																				// feet_on_pedals
		TRUE,																					// animate_head
		FALSE,																				// animate_chest
		FALSE,																				// animate_left_arm
		FALSE,																				// animate_right_arm
		FALSE,																				// animate_legs
	};

////////////////////////////////////////
//
// PILOT_REST_ANIM_MODE_HEAD_LOOK_DOWN_LEFT
//
////////////////////////////////////////

static pilot_anim_data
	pilot_rest_anim_mode_head_look_down_left_anim_data =
	{
		PILOT_HEAD_LOOK_DOWN_LEFT_ANIM_START,										// start_frame
		PILOT_HEAD_LOOK_DOWN_LEFT_ANIM_END,	 										// end_frame
		0.5,																					// cyclic_x_position
		0.5,																					// cyclic_y_position
		0.5,																					// collective_position
		0.5,																					// pedal_position
		FALSE,																				// right_hand_on_cyclic
		FALSE,																				// left_hand_on_collective
		FALSE,																				// feet_on_pedals
		TRUE,																					// animate_head
		FALSE,																				// animate_chest
		FALSE,																				// animate_left_arm
		FALSE,																				// animate_right_arm
		FALSE,																				// animate_legs
	};

////////////////////////////////////////
//
// PILOT_REST_ANIM_MODE_HEAD_LOOK_DOWN_RIGHT
//
////////////////////////////////////////

static pilot_anim_data
	pilot_rest_anim_mode_head_look_down_right_anim_data =
	{
		PILOT_HEAD_LOOK_DOWN_RIGHT_ANIM_START,										// start_frame
		PILOT_HEAD_LOOK_DOWN_RIGHT_ANIM_END,  										// end_frame
		0.5,																					// cyclic_x_position
		0.5,																					// cyclic_y_position
		0.5,																					// collective_position
		0.5,																					// pedal_position
		FALSE,																				// right_hand_on_cyclic
		FALSE,																				// left_hand_on_collective
		FALSE,																				// feet_on_pedals
		TRUE,																					// animate_head
		FALSE,																				// animate_chest
		FALSE,																				// animate_left_arm
		FALSE,																				// animate_right_arm
		FALSE,																				// animate_legs
	};

////////////////////////////////////////
//
// PILOT_REST_ANIM_MODE_HEAD_LOOK_UP
//
////////////////////////////////////////

static pilot_anim_data
	pilot_rest_anim_mode_head_look_up_anim_data =
	{
		PILOT_HEAD_LOOK_UP_ANIM_START,												// start_frame
		PILOT_HEAD_LOOK_UP_ANIM_END,			 										// end_frame
		0.5,																					// cyclic_x_position
		0.5,																					// cyclic_y_position
		0.5,																					// collective_position
		0.5,																					// pedal_position
		FALSE,																				// right_hand_on_cyclic
		FALSE,																				// left_hand_on_collective
		FALSE,																				// feet_on_pedals
		TRUE,																					// animate_head
		FALSE,																				// animate_chest
		FALSE,																				// animate_left_arm
		FALSE,																				// animate_right_arm
		FALSE,																				// animate_legs
	};

////////////////////////////////////////
//
// PILOT_REST_ANIM_MODE_HEAD_LOOK_UP_LEFT
//
////////////////////////////////////////

static pilot_anim_data
	pilot_rest_anim_mode_head_look_up_left_anim_data =
	{
		PILOT_HEAD_LOOK_UP_LEFT_ANIM_START,											// start_frame
		PILOT_HEAD_LOOK_UP_LEFT_ANIM_END,			 								// end_frame
		0.5,																					// cyclic_x_position
		0.5,																					// cyclic_y_position
		0.5,																					// collective_position
		0.5,																					// pedal_position
		FALSE,																				// right_hand_on_cyclic
		FALSE,																				// left_hand_on_collective
		FALSE,																				// feet_on_pedals
		TRUE,																					// animate_head
		FALSE,																				// animate_chest
		FALSE,																				// animate_left_arm
		FALSE,																				// animate_right_arm
		FALSE,																				// animate_legs
	};

////////////////////////////////////////
//
// PILOT_REST_ANIM_MODE_HEAD_LOOK_UP_RIGHT
//
////////////////////////////////////////

static pilot_anim_data
	pilot_rest_anim_mode_head_look_up_right_anim_data =
	{
		PILOT_HEAD_LOOK_UP_RIGHT_ANIM_START,										// start_frame
		PILOT_HEAD_LOOK_UP_RIGHT_ANIM_END,			 								// end_frame
		0.5,																					// cyclic_x_position
		0.5,																					// cyclic_y_position
		0.5,																					// collective_position
		0.5,																					// pedal_position
		FALSE,																				// right_hand_on_cyclic
		FALSE,																				// left_hand_on_collective
		FALSE,																				// feet_on_pedals
		TRUE,																					// animate_head
		FALSE,																				// animate_chest
		FALSE,																				// animate_left_arm
		FALSE,																				// animate_right_arm
		FALSE,																				// animate_legs
	};

////////////////////////////////////////
//
// PILOT_REST_ANIM_MODE_HEAD_LOOK_LEFT
//
////////////////////////////////////////

static pilot_anim_data
	pilot_rest_anim_mode_head_look_left_anim_data =
	{
		PILOT_HEAD_LOOK_LEFT_ANIM_START,												// start_frame
		PILOT_HEAD_LOOK_LEFT_ANIM_END, 												// end_frame
		0.5,																					// cyclic_x_position
		0.5,																					// cyclic_y_position
		0.5,																					// collective_position
		0.5,																					// pedal_position
		FALSE,																				// right_hand_on_cyclic
		FALSE,																				// left_hand_on_collective
		FALSE,																				// feet_on_pedals
		TRUE,																					// animate_head
		FALSE,																				// animate_chest
		FALSE,																				// animate_left_arm
		FALSE,																				// animate_right_arm
		FALSE,																				// animate_legs
	};

////////////////////////////////////////
//
// PILOT_REST_ANIM_MODE_HEAD_LOOK_RIGHT
//
////////////////////////////////////////

static pilot_anim_data
	pilot_rest_anim_mode_head_look_right_anim_data =
	{
		PILOT_HEAD_LOOK_RIGHT_ANIM_START,											// start_frame
		PILOT_HEAD_LOOK_RIGHT_ANIM_END,		 										// end_frame
		0.5,																					// cyclic_x_position
		0.5,																					// cyclic_y_position
		0.5,																					// collective_position
		0.5,																					// pedal_position
		FALSE,																				// right_hand_on_cyclic
		FALSE,																				// left_hand_on_collective
		FALSE,																				// feet_on_pedals
		TRUE,																					// animate_head
		FALSE,																				// animate_chest
		FALSE,																				// animate_left_arm
		FALSE,																				// animate_right_arm
		FALSE,																				// animate_legs
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ANIMATE PILOT'S RIGHT ARM AND CYCLIC
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define NUM_RIGHT_ARM_X_FRAMES	(17)
#define NUM_RIGHT_ARM_Y_FRAMES	(17)

#define NUM_RIGHT_ARM_FRAMES		(NUM_RIGHT_ARM_X_FRAMES * NUM_RIGHT_ARM_Y_FRAMES)

static motion_data
	right_arm_joystick_motion[NUM_RIGHT_ARM_FRAMES],
	right_arm_forearm_motion[NUM_RIGHT_ARM_FRAMES],
	right_arm_shoulder_motion[NUM_RIGHT_ARM_FRAMES];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void initialise_pilot_right_arm_and_cyclic_animation (void)
{
	read_motion_values ("GRAPHICS\\COCKPITS\\COMANCHE\\JOYSTICK.MOT", NUM_RIGHT_ARM_FRAMES, right_arm_joystick_motion);

	read_motion_values ("GRAPHICS\\COCKPITS\\COMANCHE\\FOREARM.MOT", NUM_RIGHT_ARM_FRAMES, right_arm_forearm_motion);

	read_motion_values ("GRAPHICS\\COCKPITS\\COMANCHE\\SHOULDER.MOT", NUM_RIGHT_ARM_FRAMES, right_arm_shoulder_motion);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void deinitialise_pilot_right_arm_and_cyclic_animation (void)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_pilot_static_right_hand_on_cyclic_visibility (int visible)
{
	object_3d_sub_object_search_data
		search_data;

	search_data.search_depth = 0;
	search_data.search_object = virtual_cockpit_inst3d;
	search_data.sub_object_index = OBJECT_3D_SUB_OBJECT_PILOT_R_HAND;

	if (find_object_3d_sub_object (&search_data) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		search_data.result_sub_object->visible_object = !visible && !(get_global_wide_cockpit () && wide_cockpit_nr == WIDEVIEW_COMANCHE_PILOT);
	}

	search_data.search_depth = 0;
	search_data.search_object = virtual_cockpit_inst3d;
	search_data.sub_object_index = OBJECT_3D_SUB_OBJECT_COCKPIT_PILOT_HAND_STATIC;

	if (find_object_3d_sub_object (&search_data) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		search_data.result_sub_object->visible_object = visible && !(get_global_wide_cockpit () && wide_cockpit_nr == WIDEVIEW_COMANCHE_PILOT);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void get_pilot_cyclic_position (float *x, float *y)
{
	ASSERT (x);

	ASSERT (y);

	//
	// assume cyclic_x.min = -cyclic_x.max
	//

	*x = current_flight_dynamics->input_data.cyclic_x.value;

	*x /= current_flight_dynamics->input_data.cyclic_x.max;

	*x *= 0.5;

	*x += 0.5;

	*x = bound (*x, 0.0, 0.999);

	//
	// assume cyclic_y.min = -cyclic_y.max
	//

	*y = current_flight_dynamics->input_data.cyclic_y.value;

	*y /= current_flight_dynamics->input_data.cyclic_y.max;

	*y *= 0.5;

	*y += 0.5;

	*y = bound (*y, 0.0, 0.999);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_pilot_right_arm_and_cyclic_position (float x, float y)
{
	object_3d_sub_object_search_data
		search_data;

	motion_data
		result;

	x *= (NUM_RIGHT_ARM_X_FRAMES - 1);

	y *= (NUM_RIGHT_ARM_Y_FRAMES - 1);

	//
	// cyclic
	//

	search_data.search_depth = 0;
	search_data.search_object = virtual_cockpit_inst3d;
	search_data.sub_object_index = OBJECT_3D_SUB_OBJECT_COCKPIT_PILOT_JOYSTICK;

	if (find_object_3d_sub_object (&search_data) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		interpolate_motion_values (x, y, right_arm_joystick_motion, NUM_RIGHT_ARM_X_FRAMES, &result);

		search_data.result_sub_object->relative_position.x = result.x;
		search_data.result_sub_object->relative_position.y = result.y;
		search_data.result_sub_object->relative_position.z = result.z;

		search_data.result_sub_object->relative_heading = result.heading;
		search_data.result_sub_object->relative_pitch = result.pitch;
		search_data.result_sub_object->relative_roll = result.roll;
	}

	//
	// forearm
	//

	search_data.search_depth = 0;
	search_data.search_object = virtual_cockpit_inst3d;
	search_data.sub_object_index = OBJECT_3D_SUB_OBJECT_PILOT_R_FOREARM;

	if (find_object_3d_sub_object (&search_data) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		interpolate_motion_values (x, y, right_arm_forearm_motion, NUM_RIGHT_ARM_X_FRAMES, &result);

		search_data.result_sub_object->relative_position.x = result.x;
		search_data.result_sub_object->relative_position.y = result.y;
		search_data.result_sub_object->relative_position.z = result.z;

		search_data.result_sub_object->relative_heading = result.heading;
		search_data.result_sub_object->relative_pitch = result.pitch;
		search_data.result_sub_object->relative_roll = result.roll;
	}

	//
	// shoulder
	//

	search_data.search_depth = 0;
	search_data.search_object = virtual_cockpit_inst3d;
	search_data.sub_object_index = OBJECT_3D_SUB_OBJECT_PILOT_R_SHOULDER;

	if (find_object_3d_sub_object (&search_data) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		interpolate_motion_values (x, y, right_arm_shoulder_motion, NUM_RIGHT_ARM_X_FRAMES, &result);

		search_data.result_sub_object->relative_position.x = result.x;
		search_data.result_sub_object->relative_position.y = result.y;
		search_data.result_sub_object->relative_position.z = result.z;

		search_data.result_sub_object->relative_heading = result.heading;
		search_data.result_sub_object->relative_pitch = result.pitch;
		search_data.result_sub_object->relative_roll = result.roll;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_pilot_cyclic_position (float x, float y)
{
	object_3d_sub_object_search_data
		search_data;

	motion_data
		result;

	x *= (NUM_RIGHT_ARM_X_FRAMES - 1);

	y *= (NUM_RIGHT_ARM_Y_FRAMES - 1);

	search_data.search_depth = 0;
	search_data.search_object = virtual_cockpit_inst3d;
	search_data.sub_object_index = OBJECT_3D_SUB_OBJECT_COCKPIT_PILOT_JOYSTICK;

	if (find_object_3d_sub_object (&search_data) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		interpolate_motion_values (x, y, right_arm_joystick_motion, NUM_RIGHT_ARM_X_FRAMES, &result);

		search_data.result_sub_object->relative_position.x = result.x;
		search_data.result_sub_object->relative_position.y = result.y;
		search_data.result_sub_object->relative_position.z = result.z;

		search_data.result_sub_object->relative_heading = result.heading;
		search_data.result_sub_object->relative_pitch = result.pitch;
		search_data.result_sub_object->relative_roll = result.roll;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ANIMATE PILOT'S LEFT ARM AND COLLECTIVE
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static float get_pilot_collective_position (void)
{
	float
		collective;

	//
	// assume collective.min = 0.0
	//

	collective = current_flight_dynamics->input_data.collective.value;

	collective /= current_flight_dynamics->input_data.collective.max;

	collective = bound (collective, 0.0, 1.0);

	return (collective);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_pilot_left_arm_and_collective_position (float collective)
{
	float
		anim_frame;

	anim_frame = 1.0 - collective;

	anim_frame *= PILOT_COLLECTIVE_ANIM_END - PILOT_COLLECTIVE_ANIM_START;

	anim_frame += PILOT_COLLECTIVE_ANIM_START;

	anim_frame = bound (anim_frame, PILOT_COLLECTIVE_ANIM_START, PILOT_COLLECTIVE_ANIM_END);

	animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_PILOT_L_SHOULDER, anim_frame);

	animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_PILOT_L_FOREARM, anim_frame);

	animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_PILOT_L_HAND, anim_frame);

	animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_PILOT_L_FINGER, anim_frame);

	animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_PILOT_L_THUMB, anim_frame);

	animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_COCKPIT_PILOT_COLLECTIVE, anim_frame);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_pilot_collective_position (float collective)
{
	float
		anim_frame;

	anim_frame = 1.0 - collective;

	anim_frame *= PILOT_COLLECTIVE_ANIM_END - PILOT_COLLECTIVE_ANIM_START;

	anim_frame += PILOT_COLLECTIVE_ANIM_START;

	anim_frame = bound (anim_frame, PILOT_COLLECTIVE_ANIM_START, PILOT_COLLECTIVE_ANIM_END);

	animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_COCKPIT_PILOT_COLLECTIVE, anim_frame);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// ANIMATE PILOT'S LEGS AND PEDALS (IMAGINERY PEDALS)
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static float get_pilot_pedal_position (void)
{
	float
		pedal;

	//
	// assume pedal.min = -pedal.max
	//

	pedal = current_flight_dynamics->input_data.pedal.value;

	pedal /= current_flight_dynamics->input_data.pedal.max;

	pedal *= 0.5;

	pedal += 0.5;

	return (pedal);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_pilot_legs_and_pedal_position (float pedal)
{
	float
		anim_frame;

	anim_frame = pedal;

	anim_frame *= PILOT_LEG_ANIM_END - PILOT_LEG_ANIM_START;

	anim_frame += PILOT_LEG_ANIM_START;

	anim_frame = bound (anim_frame, PILOT_LEG_ANIM_START, PILOT_LEG_ANIM_END);

	animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_PILOT_LEG, anim_frame);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// SET PILOT ANIMATION
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_pilot_animation (pilot_anim_data *anim, float frame, int set_head_anim_only)
{
	float
		anim_frame;

	ASSERT (anim);

	anim_frame = ((anim->end_frame - anim->start_frame) * frame) + anim->start_frame;

	anim_frame = bound (anim_frame, anim->start_frame, anim->end_frame);

	////////////////////////////////////////

	if (set_head_anim_only)
	{
		if (anim->animate_head)
		{
			pilot_head_anim_frame = anim_frame;
		}
		else
		{
			pilot_head_anim_frame = NO_PILOT_HEAD_ANIMATION;
		}

		return;
	}

	////////////////////////////////////////

	if (anim->right_hand_on_cyclic)
	{
		set_pilot_static_right_hand_on_cyclic_visibility (TRUE);

		set_pilot_right_arm_and_cyclic_position (anim->cyclic_x_position, anim->cyclic_y_position);
	}
	else
	{
		set_pilot_static_right_hand_on_cyclic_visibility (FALSE);

		set_pilot_cyclic_position (anim->cyclic_x_position, anim->cyclic_y_position);
	}

	////////////////////////////////////////

	if (anim->left_hand_on_collective)
	{
		set_pilot_left_arm_and_collective_position (anim->collective_position);
	}
	else
	{
		set_pilot_collective_position (anim->collective_position);
	}

	////////////////////////////////////////

	if (anim->feet_on_pedals)
	{
		set_pilot_legs_and_pedal_position (anim->pedal_position);
	}

	////////////////////////////////////////

	if (anim->animate_head)
	{
		ASSERT (pilot_head_anim_frame == NO_PILOT_HEAD_ANIMATION);

		pilot_head_anim_frame = anim_frame;
	}

	////////////////////////////////////////

	if (anim->animate_chest)
	{
		animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_PILOT_CHEST, anim_frame);
	}
	else
	{
		animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_PILOT_CHEST, PILOT_ANIM_DEFAULT);
	}

	////////////////////////////////////////

	if (anim->animate_left_arm)
	{
		animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_PILOT_L_SHOULDER, anim_frame);

		animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_PILOT_L_FOREARM, anim_frame);

		animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_PILOT_L_HAND, anim_frame);

		animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_PILOT_L_FINGER, anim_frame);

		animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_PILOT_L_THUMB, anim_frame);
	}
	else
	{
		if (!anim->left_hand_on_collective)
		{
			animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_PILOT_L_SHOULDER, PILOT_ANIM_DEFAULT);

			animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_PILOT_L_FOREARM, PILOT_ANIM_DEFAULT);

			animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_PILOT_L_HAND, PILOT_ANIM_DEFAULT);

			animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_PILOT_L_FINGER, PILOT_ANIM_DEFAULT);

			animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_PILOT_L_THUMB, PILOT_ANIM_DEFAULT);
		}
	}

	////////////////////////////////////////

	if (anim->animate_right_arm)
	{
		animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_PILOT_R_SHOULDER, anim_frame);

		animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_PILOT_R_FOREARM, anim_frame);

		animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_PILOT_R_HAND, anim_frame);

		animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_PILOT_R_FINGER, anim_frame);

		animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_PILOT_R_THUMB, anim_frame);
	}
	else
	{
		if (!anim->right_hand_on_cyclic)
		{
			animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_PILOT_R_SHOULDER, PILOT_ANIM_DEFAULT);

			animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_PILOT_R_FOREARM, PILOT_ANIM_DEFAULT);

			animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_PILOT_R_HAND, PILOT_ANIM_DEFAULT);

			animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_PILOT_R_FINGER, PILOT_ANIM_DEFAULT);

			animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_PILOT_R_THUMB, PILOT_ANIM_DEFAULT);
		}
	}

	////////////////////////////////////////

	if (anim->animate_legs)
	{
		animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_PILOT_LEG, anim_frame);
	}
	else
	{
		if (!anim->feet_on_pedals)
		{
			animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_PILOT_LEG, PILOT_ANIM_DEFAULT);
		}
	}

	////////////////////////////////////////

	pilot_animation_updated = TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// UPDATE PILOT ANIMATION
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int get_pilot_viewpoint_virtual_cockpit (void)
{
	if (get_crew_role () == CREW_ROLE_PILOT)
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

static int get_pilot_rest_anim_mode_body_animation (void)
{
	switch (pilot_rest_anim_mode)
	{
		case PILOT_REST_ANIM_MODE_RIGHT_HAND_TO_RH_MFD_BUTTON:
		case PILOT_REST_ANIM_MODE_LEFT_HAND_TO_LH_MFD_BUTTON:
		case PILOT_REST_ANIM_MODE_RIGHT_HAND_TO_RH_CONSOLE:
		case PILOT_REST_ANIM_MODE_LEFT_HAND_TO_LH_CONSOLE:
		case PILOT_REST_ANIM_MODE_RIGHT_HAND_TO_CALCULATOR:
		case PILOT_REST_ANIM_MODE_LEFT_HAND_TO_RH_SMALL_MFD_BUTTON:
		case PILOT_REST_ANIM_MODE_LEFT_HAND_TO_LH_MFD_TOP_BUTTON:
		{
			return (TRUE);

			break;
		}
	}

	return (FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static float get_reset_pilot_rest_anim_delay (void)
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

static float get_reset_pilot_head_anim_pause (void)
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

static pilot_rest_anim_modes get_random_pilot_rest_anim_mode (void)
{
	int
		n;

	pilot_rest_anim_modes
		mode;

	n = -1;

	mode = PILOT_REST_ANIM_MODE_NONE;

	if (pilot_main_anim_mode == PILOT_MAIN_ANIM_MODE_HANDS_OFF_CONTROLS)
	{
		n = rand16 () % 15;
	}
	else
	{
		////////////////////////////////////////
		//
		// select head movement only
		//
		////////////////////////////////////////

		//
		// note: set previous_random_pilot_rest_anim_mode to PILOT_REST_ANIM_MODE_NONE to pass repetition check
		//

		#define DEAD_ZONE				((float) (0.1))
		#define LEFT_THRESHOLD		((float) (0.5 - DEAD_ZONE))
		#define RIGHT_THRESHOLD		((float) (0.5 + DEAD_ZONE))
		#define UP_THRESHOLD			((float) (0.5 - DEAD_ZONE))
		#define DOWN_THRESHOLD		((float) (0.5 + DEAD_ZONE))

		if (cyclic_x_position < LEFT_THRESHOLD)
		{
			if (cyclic_y_position < UP_THRESHOLD)
			{
				mode = PILOT_REST_ANIM_MODE_HEAD_LOOK_UP_LEFT;

				previous_random_pilot_rest_anim_mode = PILOT_REST_ANIM_MODE_NONE;
			}
			else if (cyclic_y_position > DOWN_THRESHOLD)
			{
				mode = PILOT_REST_ANIM_MODE_HEAD_LOOK_DOWN_LEFT;

				previous_random_pilot_rest_anim_mode = PILOT_REST_ANIM_MODE_NONE;
			}
			else
			{
				mode = PILOT_REST_ANIM_MODE_HEAD_LOOK_LEFT;

				previous_random_pilot_rest_anim_mode = PILOT_REST_ANIM_MODE_NONE;
			}
		}
		else if (cyclic_x_position > RIGHT_THRESHOLD)
		{
			if (cyclic_y_position < UP_THRESHOLD)
			{
				mode = PILOT_REST_ANIM_MODE_HEAD_LOOK_UP_RIGHT;

				previous_random_pilot_rest_anim_mode = PILOT_REST_ANIM_MODE_NONE;
			}
			else if (cyclic_y_position > DOWN_THRESHOLD)
			{
				mode = PILOT_REST_ANIM_MODE_HEAD_LOOK_DOWN_RIGHT;

				previous_random_pilot_rest_anim_mode = PILOT_REST_ANIM_MODE_NONE;
			}
			else
			{
				mode = PILOT_REST_ANIM_MODE_HEAD_LOOK_RIGHT;

				previous_random_pilot_rest_anim_mode = PILOT_REST_ANIM_MODE_NONE;
			}
		}
		else if (cyclic_y_position < UP_THRESHOLD)
		{
			mode = PILOT_REST_ANIM_MODE_HEAD_LOOK_UP;

			previous_random_pilot_rest_anim_mode = PILOT_REST_ANIM_MODE_NONE;
		}
		else if (cyclic_y_position > DOWN_THRESHOLD)
		{
			mode = PILOT_REST_ANIM_MODE_HEAD_LOOK_DOWN;

			previous_random_pilot_rest_anim_mode = PILOT_REST_ANIM_MODE_NONE;
		}
		else
		{
			n = (rand16 () % 8) + 7;
		}

		#undef DEAD_ZONE
		#undef LEFT_THRESHOLD
		#undef RIGHT_THRESHOLD
		#undef UP_THRESHOLD
		#undef DOWN_THRESHOLD
	}

	if (mode == PILOT_REST_ANIM_MODE_NONE)
	{
		switch (n)
		{
			case 0:
			{
				mode = PILOT_REST_ANIM_MODE_RIGHT_HAND_TO_RH_MFD_BUTTON;

				break;
			}
			case 1:
			{
				mode = PILOT_REST_ANIM_MODE_LEFT_HAND_TO_LH_MFD_BUTTON;

				break;
			}
			case 2:
			{
				mode = PILOT_REST_ANIM_MODE_RIGHT_HAND_TO_RH_CONSOLE;

				break;
			}
			case 3:
			{
				mode = PILOT_REST_ANIM_MODE_LEFT_HAND_TO_LH_CONSOLE;

				break;
			}
			case 4:
			{
				mode = PILOT_REST_ANIM_MODE_RIGHT_HAND_TO_CALCULATOR;

				break;
			}
			case 5:
			{
				mode = PILOT_REST_ANIM_MODE_LEFT_HAND_TO_RH_SMALL_MFD_BUTTON;

				break;
			}
			case 6:
			{
				mode = PILOT_REST_ANIM_MODE_LEFT_HAND_TO_LH_MFD_TOP_BUTTON;

				break;
			}
			case 7:
			{
				mode = PILOT_REST_ANIM_MODE_HEAD_LOOK_DOWN;

				break;
			}
			case 8:
			{
				mode = PILOT_REST_ANIM_MODE_HEAD_LOOK_DOWN_LEFT;

				break;
			}
			case 9:
			{
				mode = PILOT_REST_ANIM_MODE_HEAD_LOOK_DOWN_RIGHT;

				break;
			}
			case 10:
			{
				mode = PILOT_REST_ANIM_MODE_HEAD_LOOK_UP;

				break;
			}
			case 11:
			{
				mode = PILOT_REST_ANIM_MODE_HEAD_LOOK_UP_LEFT;

				break;
			}
			case 12:
			{
				mode = PILOT_REST_ANIM_MODE_HEAD_LOOK_UP_RIGHT;

				break;
			}
			case 13:
			{
				mode = PILOT_REST_ANIM_MODE_HEAD_LOOK_LEFT;

				break;
			}
			case 14:
			{
				mode = PILOT_REST_ANIM_MODE_HEAD_LOOK_RIGHT;

				break;
			}
			default:
			{
				debug_fatal ("Invalid rest animation mode = %d", n);

				break;
			}
		}
	}

	return (mode);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_pilot_head_animation (void)
{
	pilot_rest_anim_frame += get_delta_time () * 0.5;

	if ((pilot_rest_anim_frame >= 0.5) && (pilot_head_anim_pause > 0.0))
	{
		pilot_rest_anim_frame = 0.5;

		pilot_head_anim_pause -= get_delta_time ();

		if (pilot_head_anim_pause < 0.0)
		{
			pilot_head_anim_pause = 0.0;
		}
	}
	else
	{
		if (pilot_rest_anim_frame >= 1.0)
		{
			pilot_rest_anim_frame = 1.0;

			pilot_rest_anim_mode = PILOT_REST_ANIM_MODE_NONE;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_pilot_rest_animation (int head_anim_only)
{
	pilot_anim_data
		*anim_data;

	//
	// cancel any animation while the player is the pilot (to stop the head moving around)
	//

	if (get_pilot_viewpoint_virtual_cockpit ())
	{
		pilot_rest_anim_mode = PILOT_REST_ANIM_MODE_NONE;

		previous_random_pilot_rest_anim_mode = PILOT_REST_ANIM_MODE_NONE;

		pilot_rest_anim_frame = 0.0;

		pilot_rest_anim_delay = get_reset_pilot_rest_anim_delay ();

		pilot_head_anim_frame = NO_PILOT_HEAD_ANIMATION;

		pilot_head_anim_pause = 0.0;
	}

	switch (pilot_rest_anim_mode)
	{
		////////////////////////////////////////
		case PILOT_REST_ANIM_MODE_NONE:
		////////////////////////////////////////
		{
			anim_data = &pilot_rest_anim_mode_none_anim_data;

			pilot_rest_anim_delay -= get_delta_time ();

			if (pilot_rest_anim_delay <= 0.0)
			{
				pilot_rest_anim_mode = get_random_pilot_rest_anim_mode ();

				//
				// try and prevent repetition
				//

				if (pilot_rest_anim_mode == previous_random_pilot_rest_anim_mode)
				{
					pilot_rest_anim_mode = get_random_pilot_rest_anim_mode ();

	 				if (pilot_rest_anim_mode == previous_random_pilot_rest_anim_mode)
					{
						pilot_rest_anim_mode = get_random_pilot_rest_anim_mode ();
					}
				}

				previous_random_pilot_rest_anim_mode = pilot_rest_anim_mode;

				pilot_rest_anim_frame = 0.0;

				pilot_rest_anim_delay = get_reset_pilot_rest_anim_delay ();

				pilot_head_anim_frame = NO_PILOT_HEAD_ANIMATION;

				pilot_head_anim_pause = get_reset_pilot_head_anim_pause ();
			}
			else
			{
				pilot_rest_anim_frame = 0.0;
			}

			set_pilot_animation (anim_data, pilot_rest_anim_frame, head_anim_only);

			break;
		}
		////////////////////////////////////////
		case PILOT_REST_ANIM_MODE_RIGHT_HAND_TO_RH_MFD_BUTTON:
		////////////////////////////////////////
		{
			ASSERT (head_anim_only == FALSE);

			anim_data = &pilot_rest_anim_mode_right_hand_to_rh_mfd_button_anim_data;

			pilot_rest_anim_frame += get_delta_time () * (1.0 / 3.0);

			if (pilot_rest_anim_frame >= 1.0)
			{
				pilot_rest_anim_frame = 1.0;

				pilot_rest_anim_mode = PILOT_REST_ANIM_MODE_NONE;
			}

			set_pilot_animation (anim_data, pilot_rest_anim_frame, FALSE);

			break;
		}
		////////////////////////////////////////
		case PILOT_REST_ANIM_MODE_LEFT_HAND_TO_LH_MFD_BUTTON:
		////////////////////////////////////////
		{
			ASSERT (head_anim_only == FALSE);

			anim_data = &pilot_rest_anim_mode_left_hand_to_lh_mfd_button_anim_data;

			pilot_rest_anim_frame += get_delta_time () * (1.0 / 2.0);

			if (pilot_rest_anim_frame >= 1.0)
			{
				pilot_rest_anim_frame = 1.0;

				pilot_rest_anim_mode = PILOT_REST_ANIM_MODE_NONE;
			}

			set_pilot_animation (anim_data, pilot_rest_anim_frame, FALSE);

			break;
		}
		////////////////////////////////////////
		case PILOT_REST_ANIM_MODE_RIGHT_HAND_TO_RH_CONSOLE:
		////////////////////////////////////////
		{
			ASSERT (head_anim_only == FALSE);

			anim_data = &pilot_rest_anim_mode_right_hand_to_rh_console_anim_data;

			pilot_rest_anim_frame += get_delta_time () * (1.0 / 3.5);

			if (pilot_rest_anim_frame >= 1.0)
			{
				pilot_rest_anim_frame = 1.0;

				pilot_rest_anim_mode = PILOT_REST_ANIM_MODE_NONE;
			}

			set_pilot_animation (anim_data, pilot_rest_anim_frame, FALSE);

			break;
		}
		////////////////////////////////////////
		case PILOT_REST_ANIM_MODE_LEFT_HAND_TO_LH_CONSOLE:
		////////////////////////////////////////
		{
			ASSERT (head_anim_only == FALSE);

			anim_data = &pilot_rest_anim_mode_left_hand_to_lh_console_anim_data;

			pilot_rest_anim_frame += get_delta_time () * (1.0 / 3.0);

			if (pilot_rest_anim_frame >= 1.0)
			{
				pilot_rest_anim_frame = 1.0;

				pilot_rest_anim_mode = PILOT_REST_ANIM_MODE_NONE;
			}

			set_pilot_animation (anim_data, pilot_rest_anim_frame, FALSE);

			break;
		}
		////////////////////////////////////////
		case PILOT_REST_ANIM_MODE_RIGHT_HAND_TO_CALCULATOR:
		////////////////////////////////////////
		{
			ASSERT (head_anim_only == FALSE);

			anim_data = &pilot_rest_anim_mode_right_hand_to_calculator_anim_data;

			pilot_rest_anim_frame += get_delta_time () * (1.0 / 2.5);

			if (pilot_rest_anim_frame >= 1.0)
			{
				pilot_rest_anim_frame = 1.0;

				pilot_rest_anim_mode = PILOT_REST_ANIM_MODE_NONE;
			}

			set_pilot_animation (anim_data, pilot_rest_anim_frame, FALSE);

			break;
		}
		////////////////////////////////////////
		case PILOT_REST_ANIM_MODE_LEFT_HAND_TO_RH_SMALL_MFD_BUTTON:
		////////////////////////////////////////
		{
			ASSERT (head_anim_only == FALSE);

			anim_data = &pilot_rest_anim_mode_left_hand_to_rh_small_mfd_button_anim_data;

			pilot_rest_anim_frame += get_delta_time () * (1.0 / 3.0);

			if (pilot_rest_anim_frame >= 1.0)
			{
				pilot_rest_anim_frame = 1.0;

				pilot_rest_anim_mode = PILOT_REST_ANIM_MODE_NONE;
			}

			set_pilot_animation (anim_data, pilot_rest_anim_frame, FALSE);

			break;
		}
		////////////////////////////////////////
		case PILOT_REST_ANIM_MODE_LEFT_HAND_TO_LH_MFD_TOP_BUTTON:
		////////////////////////////////////////
		{
			ASSERT (head_anim_only == FALSE);

			anim_data = &pilot_rest_anim_mode_left_hand_to_lh_mfd_top_button_anim_data;

			pilot_rest_anim_frame += get_delta_time () * (1.0 / 3.0);

			if (pilot_rest_anim_frame >= 1.0)
			{
				pilot_rest_anim_frame = 1.0;

				pilot_rest_anim_mode = PILOT_REST_ANIM_MODE_NONE;
			}

			set_pilot_animation (anim_data, pilot_rest_anim_frame, FALSE);

			break;
		}
		////////////////////////////////////////
		case PILOT_REST_ANIM_MODE_HEAD_LOOK_DOWN:
		////////////////////////////////////////
		{
			anim_data = &pilot_rest_anim_mode_head_look_down_anim_data;

			update_pilot_head_animation ();

			set_pilot_animation (anim_data, pilot_rest_anim_frame, head_anim_only);

			break;
		}
		////////////////////////////////////////
		case PILOT_REST_ANIM_MODE_HEAD_LOOK_DOWN_LEFT:
		////////////////////////////////////////
		{
			anim_data = &pilot_rest_anim_mode_head_look_down_left_anim_data;

			update_pilot_head_animation ();

			set_pilot_animation (anim_data, pilot_rest_anim_frame, head_anim_only);

			break;
		}
		////////////////////////////////////////
		case PILOT_REST_ANIM_MODE_HEAD_LOOK_DOWN_RIGHT:
		////////////////////////////////////////
		{
			anim_data = &pilot_rest_anim_mode_head_look_down_right_anim_data;

			update_pilot_head_animation ();

			set_pilot_animation (anim_data, pilot_rest_anim_frame, head_anim_only);

			break;
		}
		////////////////////////////////////////
		case PILOT_REST_ANIM_MODE_HEAD_LOOK_UP:
		////////////////////////////////////////
		{
			anim_data = &pilot_rest_anim_mode_head_look_up_anim_data;

			update_pilot_head_animation ();

			set_pilot_animation (anim_data, pilot_rest_anim_frame, head_anim_only);

			break;
		}
		////////////////////////////////////////
		case PILOT_REST_ANIM_MODE_HEAD_LOOK_UP_LEFT:
		////////////////////////////////////////
		{
			anim_data = &pilot_rest_anim_mode_head_look_up_left_anim_data;

			update_pilot_head_animation ();

			set_pilot_animation (anim_data, pilot_rest_anim_frame, head_anim_only);

			break;
		}
		////////////////////////////////////////
		case PILOT_REST_ANIM_MODE_HEAD_LOOK_UP_RIGHT:
		////////////////////////////////////////
		{
			anim_data = &pilot_rest_anim_mode_head_look_up_right_anim_data;

			update_pilot_head_animation ();

			set_pilot_animation (anim_data, pilot_rest_anim_frame, head_anim_only);

			break;
		}
		////////////////////////////////////////
		case PILOT_REST_ANIM_MODE_HEAD_LOOK_LEFT:
		////////////////////////////////////////
		{
			anim_data = &pilot_rest_anim_mode_head_look_left_anim_data;

			update_pilot_head_animation ();

			set_pilot_animation (anim_data, pilot_rest_anim_frame, head_anim_only);

			break;
		}
		////////////////////////////////////////
		case PILOT_REST_ANIM_MODE_HEAD_LOOK_RIGHT:
		////////////////////////////////////////
		{
			anim_data = &pilot_rest_anim_mode_head_look_right_anim_data;

			update_pilot_head_animation ();

			set_pilot_animation (anim_data, pilot_rest_anim_frame, head_anim_only);

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_pilot_hands_off_controls (void)
{
	if (!get_local_entity_int_value (get_gunship_entity (), INT_TYPE_AUTO_PILOT))
	{
		if (!get_pilot_rest_anim_mode_body_animation ())
		{
			pilot_main_anim_mode = PILOT_MAIN_ANIM_MODE_TAKING_CONTROLS;

			pilot_head_anim_pause = 0.0;

			update_pilot_taking_controls ();

			return;
		}
	}

	update_pilot_rest_animation (FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_pilot_taking_controls (void)
{
	pilot_anim_data
		*anim_data;

	if (get_local_entity_int_value (get_gunship_entity (), INT_TYPE_AUTO_PILOT))
	{
		pilot_main_anim_mode = PILOT_MAIN_ANIM_MODE_RELEASING_CONTROLS;

		update_pilot_releasing_controls ();

		return;
	}

	anim_data = &pilot_main_anim_mode_taking_controls_anim_data;

	pilot_main_anim_frame -= get_delta_time ();

	pilot_main_anim_frame = max (pilot_main_anim_frame, 0.0f);

	update_pilot_rest_animation (TRUE);

	set_pilot_animation (anim_data, pilot_main_anim_frame, FALSE);

	if (pilot_main_anim_frame == 0.0)
	{
		pilot_main_anim_mode = PILOT_MAIN_ANIM_MODE_MOVING_CONTROLS_FROM_CENTRE1;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_pilot_moving_controls_from_centre1 (void)
{
	pilot_anim_data
		*anim_data;

	anim_data = &pilot_main_anim_mode_moving_controls_from_centre1_anim_data;

	update_pilot_rest_animation (TRUE);

	set_pilot_animation (anim_data, 0.0, FALSE);

	pilot_main_anim_mode = PILOT_MAIN_ANIM_MODE_MOVING_CONTROLS_FROM_CENTRE2;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_pilot_moving_controls_from_centre2 (void)
{
	pilot_anim_data
		*anim_data;

	anim_data = &pilot_main_anim_mode_moving_controls_from_centre2_anim_data;

	anim_data->cyclic_x_position = cyclic_x_position - ((cyclic_x_position - 0.5) * 0.5);

	anim_data->cyclic_y_position = cyclic_y_position - ((cyclic_y_position - 0.5) * 0.5);

	anim_data->collective_position = collective_position - ((collective_position - 0.5) * 0.5);

	anim_data->pedal_position = pedal_position - ((pedal_position - 0.5) * 0.5);

	update_pilot_rest_animation (TRUE);

	set_pilot_animation (anim_data, 0.0, FALSE);

	pilot_main_anim_mode = PILOT_MAIN_ANIM_MODE_HANDS_ON_CONTROLS;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_pilot_hands_on_controls (void)
{
	pilot_anim_data
		*anim_data;

	if (get_local_entity_int_value (get_gunship_entity (), INT_TYPE_AUTO_PILOT))
	{
		pilot_main_anim_mode = PILOT_MAIN_ANIM_MODE_MOVING_CONTROLS_TO_CENTRE1;

		pilot_head_anim_pause = 0.0;

		update_pilot_moving_controls_to_centre1 ();

		return;
	}

	anim_data = &pilot_main_anim_mode_hands_on_controls_anim_data;

	anim_data->cyclic_x_position = cyclic_x_position;

	anim_data->cyclic_y_position = cyclic_y_position;

	anim_data->collective_position = collective_position;

	anim_data->pedal_position = pedal_position;

	update_pilot_rest_animation (TRUE);

	set_pilot_animation (anim_data, 0.0, FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_pilot_moving_controls_to_centre1 (void)
{
	pilot_anim_data
		*anim_data;

	anim_data = &pilot_main_anim_mode_moving_controls_to_centre1_anim_data;

	anim_data->cyclic_x_position = previous_cyclic_x_position - ((previous_cyclic_x_position - 0.5) * 0.5);

	anim_data->cyclic_y_position = previous_cyclic_y_position - ((previous_cyclic_y_position - 0.5) * 0.5);

	anim_data->collective_position = previous_collective_position - ((previous_collective_position - 0.5) * 0.5);

	anim_data->pedal_position = previous_pedal_position - ((previous_pedal_position - 0.5) * 0.5);

	update_pilot_rest_animation (TRUE);

	set_pilot_animation (anim_data, 0.0, FALSE);

	pilot_main_anim_mode = PILOT_MAIN_ANIM_MODE_MOVING_CONTROLS_TO_CENTRE2;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_pilot_moving_controls_to_centre2 (void)
{
	pilot_anim_data
		*anim_data;

	anim_data = &pilot_main_anim_mode_moving_controls_to_centre2_anim_data;

	update_pilot_rest_animation (TRUE);

	set_pilot_animation (anim_data, 0.0, FALSE);

	pilot_main_anim_mode = PILOT_MAIN_ANIM_MODE_RELEASING_CONTROLS;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_pilot_releasing_controls (void)
{
	pilot_anim_data
		*anim_data;

	if (!get_local_entity_int_value (get_gunship_entity (), INT_TYPE_AUTO_PILOT))
	{
		pilot_main_anim_mode = PILOT_MAIN_ANIM_MODE_TAKING_CONTROLS;

		update_pilot_taking_controls ();

		return;
	}

	anim_data = &pilot_main_anim_mode_releasing_controls_anim_data;

	pilot_main_anim_frame += get_delta_time ();

	pilot_main_anim_frame = min (pilot_main_anim_frame, 1.0f);

	update_pilot_rest_animation (TRUE);

	set_pilot_animation (anim_data, pilot_main_anim_frame, FALSE);

	if (pilot_main_anim_frame == 1.0)
	{
		pilot_main_anim_mode = PILOT_MAIN_ANIM_MODE_HANDS_OFF_CONTROLS;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_pilot_animation (void)
{
	get_pilot_cyclic_position (&cyclic_x_position, &cyclic_y_position);

	collective_position = get_pilot_collective_position ();

	pedal_position = get_pilot_pedal_position ();

	////////////////////////////////////////

	pilot_animation_updated = FALSE;

	pilot_head_anim_frame = NO_PILOT_HEAD_ANIMATION;

	////////////////////////////////////////

	switch (pilot_main_anim_mode)
	{
		////////////////////////////////////////
		case PILOT_MAIN_ANIM_MODE_HANDS_OFF_CONTROLS:
		////////////////////////////////////////
		{
			update_pilot_hands_off_controls ();

			break;
		}
		////////////////////////////////////////
		case PILOT_MAIN_ANIM_MODE_TAKING_CONTROLS:
		////////////////////////////////////////
		{
			update_pilot_taking_controls ();

			break;
		}
		////////////////////////////////////////
		case PILOT_MAIN_ANIM_MODE_MOVING_CONTROLS_FROM_CENTRE1:
		////////////////////////////////////////
		{
			update_pilot_moving_controls_from_centre1 ();

			break;
		}
		////////////////////////////////////////
		case PILOT_MAIN_ANIM_MODE_MOVING_CONTROLS_FROM_CENTRE2:
		////////////////////////////////////////
		{
			update_pilot_moving_controls_from_centre2 ();

			break;
		}
		////////////////////////////////////////
		case PILOT_MAIN_ANIM_MODE_HANDS_ON_CONTROLS:
		////////////////////////////////////////
		{
			update_pilot_hands_on_controls ();

			break;
		}
		////////////////////////////////////////
		case PILOT_MAIN_ANIM_MODE_MOVING_CONTROLS_TO_CENTRE1:
		////////////////////////////////////////
		{
			update_pilot_moving_controls_to_centre1 ();

			break;
		}
		////////////////////////////////////////
		case PILOT_MAIN_ANIM_MODE_MOVING_CONTROLS_TO_CENTRE2:
		////////////////////////////////////////
		{
			update_pilot_moving_controls_to_centre2 ();

			break;
		}
		////////////////////////////////////////
		case PILOT_MAIN_ANIM_MODE_RELEASING_CONTROLS:
		////////////////////////////////////////
		{
			update_pilot_releasing_controls ();

			break;
		}
	}

	ASSERT (pilot_animation_updated);

	////////////////////////////////////////

	//
	// store previous values to use if auto-pilot has taken control
	//

	previous_cyclic_x_position = cyclic_x_position;

	previous_cyclic_y_position = cyclic_y_position;

	previous_collective_position = collective_position;

	previous_pedal_position = pedal_position;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MAX_ROLL	((float) (rad (10.0)))

static void update_pilot_head_tilt_animation (void)
{
	float
		pilot_head_tilt_angle,
		frame,
		anim_frame;

	ASSERT (pilot_rest_anim_mode == PILOT_REST_ANIM_MODE_NONE);

	if (pilot_rest_anim_delay < 1.0)
	{
		pilot_head_tilt_angle = 0.0;
	}
	else
	{
		pilot_head_tilt_angle = get_local_entity_float_value (get_gunship_entity (), FLOAT_TYPE_ROLL);
	}

	pilot_head_tilt_angle = bound (pilot_head_tilt_angle, -MAX_ROLL, MAX_ROLL);

	pilot_head_tilt_angle = (pilot_head_tilt_angle + previous_pilot_head_tilt_angle) * 0.5;

	frame = (pilot_head_tilt_angle * (0.5 / MAX_ROLL)) + 0.5;

	anim_frame = ((PILOT_HEAD_TILT_LEFT_TO_RIGHT_ANIM_END - PILOT_HEAD_TILT_LEFT_TO_RIGHT_ANIM_START) * frame) + PILOT_HEAD_TILT_LEFT_TO_RIGHT_ANIM_START;

	anim_frame = bound (anim_frame, PILOT_HEAD_TILT_LEFT_TO_RIGHT_ANIM_START, PILOT_HEAD_TILT_LEFT_TO_RIGHT_ANIM_END);

	animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_PILOT_HEAD, anim_frame);

	previous_pilot_head_tilt_angle = pilot_head_tilt_angle;
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

void initialise_comanche_pilot_animation (void)
{
	#if DEBUG_MODULE

	debug_colour_watch (COLOUR_AMBER, "pilot_main_anim_mode = %d", MT_INT, &pilot_main_anim_mode);
	debug_colour_watch (COLOUR_AMBER, "pilot_main_anim_frame = %.2f", MT_FLOAT, &pilot_main_anim_frame);

	debug_colour_watch (COLOUR_AMBER, "pilot_rest_anim_mode = %d", MT_INT, &pilot_rest_anim_mode);
	debug_colour_watch (COLOUR_AMBER, "previous_random_pilot_rest_anim_mode = %d", MT_INT, &previous_random_pilot_rest_anim_mode);
	debug_colour_watch (COLOUR_AMBER, "pilot_rest_anim_frame = %.2f", MT_FLOAT, &pilot_rest_anim_frame);
	debug_colour_watch (COLOUR_AMBER, "pilot_rest_anim_delay = %.2f", MT_FLOAT, &pilot_rest_anim_delay);

	debug_colour_watch (COLOUR_AMBER, "pilot_head_anim_frame = %.2f", MT_FLOAT, &pilot_head_anim_frame);
	debug_colour_watch (COLOUR_AMBER, "pilot_head_anim_pause = %.2f", MT_FLOAT, &pilot_head_anim_pause);

	debug_colour_watch (COLOUR_AMBER, "cyclic_x_position = %.2f", MT_FLOAT, &cyclic_x_position);
	debug_colour_watch (COLOUR_AMBER, "cyclic_y_position = %.2f", MT_FLOAT, &cyclic_y_position);
	debug_colour_watch (COLOUR_AMBER, "collective_position = %.2f", MT_FLOAT, &collective_position);
	debug_colour_watch (COLOUR_AMBER, "pedal_position = %.2f", MT_FLOAT, &pedal_position);

	#endif

	pilot_main_anim_mode							= PILOT_MAIN_ANIM_MODE_HANDS_OFF_CONTROLS;
	pilot_main_anim_frame			  			= 1.0;

	pilot_rest_anim_mode			 				= PILOT_REST_ANIM_MODE_NONE;
	previous_random_pilot_rest_anim_mode	= PILOT_REST_ANIM_MODE_NONE;
	pilot_rest_anim_frame  			  			= 0.0;
	pilot_rest_anim_delay  						= get_reset_pilot_rest_anim_delay ();

	pilot_head_anim_frame						= NO_PILOT_HEAD_ANIMATION;
	pilot_head_anim_pause						= 0.0;

	previous_pilot_head_tilt_angle			= 0.0;

	cyclic_x_position								= 0.5;
	cyclic_y_position			  			  		= 0.5;
	collective_position			 		 		= 0.5;
	pedal_position			 				  		= 0.5;
	previous_cyclic_x_position					= 0.5;
	previous_cyclic_y_position					= 0.5;
	previous_collective_position 				= 0.5;
	previous_pedal_position			  			= 0.5;

	initialise_pilot_right_arm_and_cyclic_animation ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_comanche_pilot_animation (void)
{
	deinitialise_pilot_right_arm_and_cyclic_animation ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_comanche_pilot_animation (void)
{
	ASSERT (get_gunship_entity ());

	ASSERT (current_flight_dynamics);

	ASSERT (virtual_cockpit_inst3d);

	update_pilot_animation ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_comanche_pilot_head_position (void)
{
	int
		show_pilot_head;

	object_3d_sub_object_search_data
		search;

	ASSERT (get_gunship_entity ());

	ASSERT (virtual_cockpit_inst3d);

	show_pilot_head = !get_pilot_viewpoint_virtual_cockpit ();

	search.search_depth = 0;
	search.search_object = virtual_cockpit_inst3d;
	search.sub_object_index = OBJECT_3D_SUB_OBJECT_PILOT_HEAD;

	if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		search.result_sub_object->visible_object = show_pilot_head;

		if (show_pilot_head)
		{
			if (pilot_head_anim_frame != NO_PILOT_HEAD_ANIMATION)
			{
				animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_PILOT_HEAD, pilot_head_anim_frame);
			}
			else
			{
				if (pilot_rest_anim_mode == PILOT_REST_ANIM_MODE_NONE)
				{
					update_pilot_head_tilt_animation ();
				}
				else
				{
					search.result_sub_object->relative_heading = 0.0;
					search.result_sub_object->relative_pitch = pilot_head_pitch_datum;
					search.result_sub_object->relative_roll = 0.0;

					previous_pilot_head_tilt_angle = 0.0;
				}
			}
		}
	}
	else
	{
		debug_fatal ("Failed to locate pilot's head in virtual cockpit");
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_comanche_pilot_head_pitch_datum (void)
{
	float
		relative_pitch;

	object_3d_sub_object_search_data
		search;

	ASSERT (get_gunship_entity ());

	ASSERT (virtual_cockpit_inst3d);

	search.search_depth = 0;
	search.search_object = virtual_cockpit_inst3d;
	search.sub_object_index = OBJECT_3D_SUB_OBJECT_PILOT_HEAD;

	if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		relative_pitch = search.result_sub_object->relative_pitch;
	}
	else
	{
		debug_fatal ("Failed to locate pilot's head in virtual cockpit");
	}

	return (relative_pitch);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
