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

#define LAST_FRAME																	((float) (1500.0))

#define CO_PILOT_COLLECTIVE_ANIM_START											((float) (0.0 / LAST_FRAME))
#define CO_PILOT_COLLECTIVE_ANIM_END											((float) (60.0 / LAST_FRAME))

#define CO_PILOT_LEG_ANIM_START													((float) (0.0 / LAST_FRAME))
#define CO_PILOT_LEG_ANIM_END														((float) (60.0 / LAST_FRAME))

#define CO_PILOT_HEAD_TILT_LEFT_TO_RIGHT_ANIM_START						((float) (0.0 / LAST_FRAME))
#define CO_PILOT_HEAD_TILT_LEFT_TO_RIGHT_ANIM_END							((float) (60.0 / LAST_FRAME))

#define CO_PILOT_CONTROLS_TO_REST_ANIM_START									((float) (61.0 / LAST_FRAME))
#define CO_PILOT_CONTROLS_TO_REST_ANIM_END									((float) (90.0 / LAST_FRAME))

#define CO_PILOT_RIGHT_HAND_FROM_REST_TO_RH_MFD_BUTTON_ANIM_START		((float) (90.0 / LAST_FRAME))
#define CO_PILOT_RIGHT_HAND_FROM_REST_TO_RH_MFD_BUTTON_ANIM_END		((float) (180.0 / LAST_FRAME))

#define CO_PILOT_LEFT_HAND_FROM_REST_TO_LH_MFD_BUTTON_ANIM_START		((float) (180.0 / LAST_FRAME))
#define CO_PILOT_LEFT_HAND_FROM_REST_TO_LH_MFD_BUTTON_ANIM_END			((float) (240.0 / LAST_FRAME))

#define CO_PILOT_RIGHT_HAND_FROM_REST_TO_RH_CONSOLE_ANIM_START	 		((float) (240.0 / LAST_FRAME))
#define CO_PILOT_RIGHT_HAND_FROM_REST_TO_RH_CONSOLE_ANIM_END			((float) (345.0 / LAST_FRAME))

#define CO_PILOT_RIGHT_HAND_FROM_REST_TO_CALCULATOR_ANIM_START	 		((float) (345.0 / LAST_FRAME))
#define CO_PILOT_RIGHT_HAND_FROM_REST_TO_CALCULATOR_ANIM_END			((float) (420.0 / LAST_FRAME))

#define CO_PILOT_LEFT_HAND_FROM_REST_TO_LH_CONSOLE_ANIM_START	 		((float) (420.0 / LAST_FRAME))
#define CO_PILOT_LEFT_HAND_FROM_REST_TO_LH_CONSOLE_ANIM_END				((float) (510.0 / LAST_FRAME))

#define CO_PILOT_LEFT_HAND_FROM_REST_TO_RH_SMALL_MFD_ANIM_START		((float) (510.0 / LAST_FRAME))
#define CO_PILOT_LEFT_HAND_FROM_REST_TO_RH_SMALL_MFD_ANIM_END			((float) (600.0 / LAST_FRAME))

#define CO_PILOT_LEFT_HAND_FROM_REST_TO_LH_MFD_TOP_BUTTON_ANIM_START	((float) (600.0 / LAST_FRAME))
#define CO_PILOT_LEFT_HAND_FROM_REST_TO_LH_MFD_TOP_BUTTON_ANIM_END	((float) (690.0 / LAST_FRAME))

// 690.0 to 1020.0 - no frames

#define CO_PILOT_HEAD_LOOK_DOWN_LEFT_ANIM_START                   	((float) (1020.0 / LAST_FRAME))
#define CO_PILOT_HEAD_LOOK_DOWN_LEFT_ANIM_END								((float) (1080.0 / LAST_FRAME))

#define CO_PILOT_HEAD_LOOK_DOWN_RIGHT_ANIM_START							((float) (1080.0 / LAST_FRAME))
#define CO_PILOT_HEAD_LOOK_DOWN_RIGHT_ANIM_END                    	((float) (1140.0 / LAST_FRAME))

#define CO_PILOT_HEAD_LOOK_DOWN_ANIM_START									((float) (1140.0 / LAST_FRAME))
#define CO_PILOT_HEAD_LOOK_DOWN_ANIM_END										((float) (1200.0 / LAST_FRAME))

#define CO_PILOT_HEAD_LOOK_UP_ANIM_START                          	((float) (1200.0 / LAST_FRAME))
#define CO_PILOT_HEAD_LOOK_UP_ANIM_END                            	((float) (1260.0 / LAST_FRAME))

#define CO_PILOT_HEAD_LOOK_LEFT_ANIM_START      	               	((float) (1260.0 / LAST_FRAME))
#define CO_PILOT_HEAD_LOOK_LEFT_ANIM_END           	            	((float) (1320.0 / LAST_FRAME))

#define CO_PILOT_HEAD_LOOK_RIGHT_ANIM_START									((float) (1320.0 / LAST_FRAME))
#define CO_PILOT_HEAD_LOOK_RIGHT_ANIM_END       	               	((float) (1380.0 / LAST_FRAME))

#define CO_PILOT_HEAD_LOOK_UP_LEFT_ANIM_START     	               	((float) (1380.0 / LAST_FRAME))
#define CO_PILOT_HEAD_LOOK_UP_LEFT_ANIM_END          	            	((float) (1440.0 / LAST_FRAME))

#define CO_PILOT_HEAD_LOOK_UP_RIGHT_ANIM_START								((float) (1440.0 / LAST_FRAME))
#define CO_PILOT_HEAD_LOOK_UP_RIGHT_ANIM_END      	               	((float) (1500.0 / LAST_FRAME))

#define CO_PILOT_ANIM_DEFAULT														(CO_PILOT_CONTROLS_TO_REST_ANIM_END)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct CO_PILOT_ANIM_DATA
{
	float
		start_frame,
		end_frame;

	unsigned int
		animate_head		:1,
		animate_chest		:1,
		animate_left_arm	:1,
		animate_right_arm	:1,
		animate_legs		:1;
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
//
// CO-PILOT ANIMATIONS
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum CO_PILOT_ANIM_MODES
{
	CO_PILOT_ANIM_MODE_NONE,
	CO_PILOT_ANIM_MODE_RIGHT_HAND_TO_RH_MFD_BUTTON,
	CO_PILOT_ANIM_MODE_LEFT_HAND_TO_LH_MFD_BUTTON,
	CO_PILOT_ANIM_MODE_RIGHT_HAND_TO_RH_CONSOLE,
	CO_PILOT_ANIM_MODE_LEFT_HAND_TO_LH_CONSOLE,
	CO_PILOT_ANIM_MODE_RIGHT_HAND_TO_CALCULATOR,
	CO_PILOT_ANIM_MODE_LEFT_HAND_TO_RH_SMALL_MFD_BUTTON,
	CO_PILOT_ANIM_MODE_LEFT_HAND_TO_LH_MFD_TOP_BUTTON,
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
// CO_PILOT_ANIM_MODE_NONE
//
////////////////////////////////////////

static co_pilot_anim_data
	co_pilot_anim_mode_none_anim_data =
	{
		0.0,																					// start_frame
		0.0,																					// end_frame
		FALSE,																				// animate_head
		FALSE,																				// animate_chest
		FALSE,																				// animate_left_arm
		FALSE,																				// animate_right_arm
		FALSE,																				// animate_legs
	};

////////////////////////////////////////
//
// CO_PILOT_ANIM_MODE_RIGHT_HAND_TO_RH_MFD_BUTTON
//
////////////////////////////////////////

static co_pilot_anim_data
	co_pilot_anim_mode_right_hand_to_rh_mfd_button_anim_data =
	{
		CO_PILOT_RIGHT_HAND_FROM_REST_TO_RH_MFD_BUTTON_ANIM_START,			// start_frame
		CO_PILOT_RIGHT_HAND_FROM_REST_TO_RH_MFD_BUTTON_ANIM_END,				// end_frame
		TRUE,																					// animate_head
		TRUE,																					// animate_chest
		TRUE,																					// animate_left_arm
		TRUE,																					// animate_right_arm
		FALSE,																				// animate_legs
	};

////////////////////////////////////////
//
// CO_PILOT_ANIM_MODE_LEFT_HAND_TO_LH_MFD_BUTTON
//
////////////////////////////////////////

static co_pilot_anim_data
	co_pilot_anim_mode_left_hand_to_lh_mfd_button_anim_data =
	{
		CO_PILOT_LEFT_HAND_FROM_REST_TO_LH_MFD_BUTTON_ANIM_START,			// start_frame
		CO_PILOT_LEFT_HAND_FROM_REST_TO_LH_MFD_BUTTON_ANIM_END,				// end_frame
		TRUE,																					// animate_head
		TRUE,			  																		// animate_chest
		TRUE,																					// animate_left_arm
		TRUE,																					// animate_right_arm
		FALSE,																				// animate_legs
	};

////////////////////////////////////////
//
// CO_PILOT_ANIM_MODE_RIGHT_HAND_TO_RH_CONSOLE
//
////////////////////////////////////////

static co_pilot_anim_data
	co_pilot_anim_mode_right_hand_to_rh_console_anim_data =
	{
		CO_PILOT_RIGHT_HAND_FROM_REST_TO_RH_CONSOLE_ANIM_START,				// start_frame
		CO_PILOT_RIGHT_HAND_FROM_REST_TO_RH_CONSOLE_ANIM_END,					// end_frame
		TRUE,																					// animate_head
		TRUE,			  																		// animate_chest
		TRUE,																					// animate_left_arm
		TRUE,																					// animate_right_arm
		FALSE,																				// animate_legs
	};

////////////////////////////////////////
//
// CO_PILOT_ANIM_MODE_LEFT_HAND_TO_LH_CONSOLE
//
////////////////////////////////////////

static co_pilot_anim_data
	co_pilot_anim_mode_left_hand_to_lh_console_anim_data =
	{
		CO_PILOT_LEFT_HAND_FROM_REST_TO_LH_CONSOLE_ANIM_START,				// start_frame
		CO_PILOT_LEFT_HAND_FROM_REST_TO_LH_CONSOLE_ANIM_END,					// end_frame
		TRUE,																					// animate_head
		TRUE,																					// animate_chest
		TRUE,																					// animate_left_arm
		TRUE,																					// animate_right_arm
		FALSE,																				// animate_legs
	};

////////////////////////////////////////
//
// CO_PILOT_ANIM_MODE_RIGHT_HAND_TO_CALCULATOR
//
////////////////////////////////////////

static co_pilot_anim_data
	co_pilot_anim_mode_right_hand_to_calculator_anim_data =
	{
		CO_PILOT_RIGHT_HAND_FROM_REST_TO_CALCULATOR_ANIM_START,				// start_frame
		CO_PILOT_RIGHT_HAND_FROM_REST_TO_CALCULATOR_ANIM_END,					// end_frame
		TRUE,																					// animate_head
		TRUE,			  																		// animate_chest
		TRUE,																					// animate_left_arm
		TRUE,																					// animate_right_arm
		FALSE,																				// animate_legs
	};

////////////////////////////////////////
//
// CO_PILOT_ANIM_MODE_LEFT_HAND_TO_RH_SMALL_MFD_BUTTON
//
////////////////////////////////////////

static co_pilot_anim_data
	co_pilot_anim_mode_left_hand_to_rh_small_mfd_button_anim_data =
	{
		CO_PILOT_LEFT_HAND_FROM_REST_TO_RH_SMALL_MFD_ANIM_START,				// start_frame
		CO_PILOT_LEFT_HAND_FROM_REST_TO_RH_SMALL_MFD_ANIM_END,				// end_frame
		TRUE,																					// animate_head
		TRUE,																					// animate_chest
		TRUE,																					// animate_left_arm
		TRUE,																					// animate_right_arm
		FALSE,																				// animate_legs
	};

////////////////////////////////////////
//
// CO_PILOT_ANIM_MODE_LEFT_HAND_TO_LH_MFD_TOP_BUTTON
//
////////////////////////////////////////

static co_pilot_anim_data
	co_pilot_anim_mode_left_hand_to_lh_mfd_top_button_anim_data =
	{
		CO_PILOT_LEFT_HAND_FROM_REST_TO_LH_MFD_TOP_BUTTON_ANIM_START,		// start_frame
		CO_PILOT_LEFT_HAND_FROM_REST_TO_LH_MFD_TOP_BUTTON_ANIM_END,			// end_frame
		TRUE,																					// animate_head
		TRUE,																					// animate_chest
		TRUE,																					// animate_left_arm
		TRUE,																					// animate_right_arm
		FALSE,																				// animate_legs
	};

////////////////////////////////////////
//
// CO_PILOT_ANIM_MODE_HEAD_LOOK_DOWN
//
////////////////////////////////////////

static co_pilot_anim_data
	co_pilot_anim_mode_head_look_down_anim_data =
	{
		CO_PILOT_HEAD_LOOK_DOWN_ANIM_START,											// start_frame
		CO_PILOT_HEAD_LOOK_DOWN_ANIM_END,											// end_frame
		TRUE,																					// animate_head
		FALSE,																				// animate_chest
		FALSE,																				// animate_left_arm
		FALSE,																				// animate_right_arm
		FALSE,																				// animate_legs
	};

////////////////////////////////////////
//
// CO_PILOT_ANIM_MODE_HEAD_LOOK_DOWN_LEFT
//
////////////////////////////////////////

static co_pilot_anim_data
	co_pilot_anim_mode_head_look_down_left_anim_data =
	{
		CO_PILOT_HEAD_LOOK_DOWN_LEFT_ANIM_START,									// start_frame
		CO_PILOT_HEAD_LOOK_DOWN_LEFT_ANIM_END,										// end_frame
		TRUE,																					// animate_head
		FALSE,																				// animate_chest
		FALSE,																				// animate_left_arm
		FALSE,																				// animate_right_arm
		FALSE,																				// animate_legs
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
		TRUE,																					// animate_head
		FALSE,																				// animate_chest
		FALSE,																				// animate_left_arm
		FALSE,																				// animate_right_arm
		FALSE,																				// animate_legs
	};

////////////////////////////////////////
//
// CO_PILOT_ANIM_MODE_HEAD_LOOK_UP
//
////////////////////////////////////////

static co_pilot_anim_data
	co_pilot_anim_mode_head_look_up_anim_data =
	{
		CO_PILOT_HEAD_LOOK_UP_ANIM_START,											// start_frame
		CO_PILOT_HEAD_LOOK_UP_ANIM_END,			 									// end_frame
		TRUE,																					// animate_head
		FALSE,																				// animate_chest
		FALSE,																				// animate_left_arm
		FALSE,																				// animate_right_arm
		FALSE,																				// animate_legs
	};

////////////////////////////////////////
//
// CO_PILOT_ANIM_MODE_HEAD_LOOK_UP_LEFT
//
////////////////////////////////////////

static co_pilot_anim_data
	co_pilot_anim_mode_head_look_up_left_anim_data =
	{
		CO_PILOT_HEAD_LOOK_UP_LEFT_ANIM_START,										// start_frame
		CO_PILOT_HEAD_LOOK_UP_LEFT_ANIM_END,										// end_frame
		TRUE,																					// animate_head
		FALSE,																				// animate_chest
		FALSE,																				// animate_left_arm
		FALSE,																				// animate_right_arm
		FALSE,																				// animate_legs
	};

////////////////////////////////////////
//
// CO_PILOT_ANIM_MODE_HEAD_LOOK_UP_RIGHT
//
////////////////////////////////////////

static co_pilot_anim_data
	co_pilot_anim_mode_head_look_up_right_anim_data =
	{
		CO_PILOT_HEAD_LOOK_UP_RIGHT_ANIM_START,									// start_frame
		CO_PILOT_HEAD_LOOK_UP_RIGHT_ANIM_END,										// end_frame
		TRUE,																					// animate_head
		FALSE,																				// animate_chest
		FALSE,																				// animate_left_arm
		FALSE,																				// animate_right_arm
		FALSE,																				// animate_legs
	};

////////////////////////////////////////
//
// CO_PILOT_ANIM_MODE_HEAD_LOOK_LEFT
//
////////////////////////////////////////

static co_pilot_anim_data
	co_pilot_anim_mode_head_look_left_anim_data =
	{
		CO_PILOT_HEAD_LOOK_LEFT_ANIM_START,											// start_frame
		CO_PILOT_HEAD_LOOK_LEFT_ANIM_END,											// end_frame
		TRUE,																					// animate_head
		FALSE,																				// animate_chest
		FALSE,																				// animate_left_arm
		FALSE,																				// animate_right_arm
		FALSE,																				// animate_legs
	};

////////////////////////////////////////
//
// CO_PILOT_ANIM_MODE_HEAD_LOOK_RIGHT
//
////////////////////////////////////////

static co_pilot_anim_data
	co_pilot_anim_mode_head_look_right_anim_data =
	{
		CO_PILOT_HEAD_LOOK_RIGHT_ANIM_START,										// start_frame
		CO_PILOT_HEAD_LOOK_RIGHT_ANIM_END,											// end_frame
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
//
// SET CO-PILOT ANIMATION
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_co_pilot_animation (co_pilot_anim_data *anim, float frame)
{
	float
		anim_frame;

	ASSERT (anim);

	set_co_pilot_static_right_hand_on_cyclic_visibility (FALSE);

	set_co_pilot_collective_position (0.5);

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
		animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_WSO_CHEST, anim_frame);
	}
	else
	{
		animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_WSO_CHEST, CO_PILOT_ANIM_DEFAULT);
	}

	////////////////////////////////////////

	if (anim->animate_left_arm)
	{
		animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_WSO_L_SHOULDER, anim_frame);

		animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_WSO_L_FOREARM, anim_frame);

		animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_WSO_L_HAND, anim_frame);

		animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_WSO_L_FINGER, anim_frame);

		animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_WSO_L_THUMB, anim_frame);
	}
	else
	{
		animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_WSO_L_SHOULDER, CO_PILOT_ANIM_DEFAULT);

		animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_WSO_L_FOREARM, CO_PILOT_ANIM_DEFAULT);

		animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_WSO_L_HAND, CO_PILOT_ANIM_DEFAULT);

		animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_WSO_L_FINGER, CO_PILOT_ANIM_DEFAULT);

		animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_WSO_L_THUMB, CO_PILOT_ANIM_DEFAULT);
	}

	////////////////////////////////////////

	if (anim->animate_right_arm)
	{
		animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_WSO_R_SHOULDER, anim_frame);

		animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_WSO_R_FOREARM, anim_frame);

		animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_WSO_R_HAND, anim_frame);

		animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_WSO_R_FINGER, anim_frame);

		animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_WSO_R_THUMB, anim_frame);
	}
	else
	{
		animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_WSO_R_SHOULDER, CO_PILOT_ANIM_DEFAULT);

		animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_WSO_R_FOREARM, CO_PILOT_ANIM_DEFAULT);

		animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_WSO_R_HAND, CO_PILOT_ANIM_DEFAULT);

		animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_WSO_R_FINGER, CO_PILOT_ANIM_DEFAULT);

		animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_WSO_R_THUMB, CO_PILOT_ANIM_DEFAULT);
	}

	////////////////////////////////////////

	if (anim->animate_legs)
	{
		animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_WSO_LEG, anim_frame);
	}
	else
	{
		animate_entity_simple_keyframed_sub_objects (virtual_cockpit_inst3d, OBJECT_3D_SUB_OBJECT_WSO_LEG, CO_PILOT_ANIM_DEFAULT);
	}
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

static co_pilot_anim_modes get_random_co_pilot_anim_mode (void)
{
	static int
		previous_n = -1;

	int
		n;

	co_pilot_anim_modes
		mode;

	n = rand16 () % 15;

	if (n == previous_n)
	{
		n = rand16 () % 15;

		if (n == previous_n)
		{
			n = rand16 () % 15;
		}
	}

	previous_n = n;

	switch (n)
	{
		case 0:
		{
			mode = CO_PILOT_ANIM_MODE_RIGHT_HAND_TO_RH_MFD_BUTTON;

			break;
		}
		case 1:
		{
			mode = CO_PILOT_ANIM_MODE_LEFT_HAND_TO_LH_MFD_BUTTON;

			break;
		}
		case 2:
		{
			mode = CO_PILOT_ANIM_MODE_RIGHT_HAND_TO_RH_CONSOLE;

			break;
		}
		case 3:
		{
			mode = CO_PILOT_ANIM_MODE_LEFT_HAND_TO_LH_CONSOLE;

			break;
		}
		case 4:
		{
			mode = CO_PILOT_ANIM_MODE_RIGHT_HAND_TO_CALCULATOR;

			break;
		}
		case 5:
		{
			mode = CO_PILOT_ANIM_MODE_LEFT_HAND_TO_RH_SMALL_MFD_BUTTON;

			break;
		}
		case 6:
		{
			mode = CO_PILOT_ANIM_MODE_LEFT_HAND_TO_LH_MFD_TOP_BUTTON;

			break;
		}
		case 7:
		{
			mode = CO_PILOT_ANIM_MODE_HEAD_LOOK_DOWN;

			break;
		}
		case 8:
		{
			mode = CO_PILOT_ANIM_MODE_HEAD_LOOK_DOWN_LEFT;

			break;
		}
		case 9:
		{
			mode = CO_PILOT_ANIM_MODE_HEAD_LOOK_DOWN_RIGHT;

			break;
		}
		case 10:
		{
			mode = CO_PILOT_ANIM_MODE_HEAD_LOOK_UP;

			break;
		}
		case 11:
		{
			mode = CO_PILOT_ANIM_MODE_HEAD_LOOK_UP_LEFT;

			break;
		}
		case 12:
		{
			mode = CO_PILOT_ANIM_MODE_HEAD_LOOK_UP_RIGHT;

			break;
		}
		case 13:
		{
			mode = CO_PILOT_ANIM_MODE_HEAD_LOOK_LEFT;

			break;
		}
		case 14:
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

			co_pilot_anim_mode = CO_PILOT_ANIM_MODE_NONE;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_co_pilot_animation (void)
{
	co_pilot_anim_data
		*anim_data = nullptr;

	//
	// cancel any animation while the player is the co-pilot (to stop the head moving around)
	//

	if (get_co_pilot_viewpoint_virtual_cockpit ())
	{
		co_pilot_anim_mode = CO_PILOT_ANIM_MODE_NONE;

		co_pilot_anim_frame = 0.0;

		co_pilot_anim_delay = get_reset_co_pilot_anim_delay ();

		co_pilot_head_anim_frame = NO_CO_PILOT_HEAD_ANIMATION;

		co_pilot_head_anim_pause = 0.0;
	}

	switch (co_pilot_anim_mode)
	{
		////////////////////////////////////////
		case CO_PILOT_ANIM_MODE_NONE:
		////////////////////////////////////////
		{
			anim_data = &co_pilot_anim_mode_none_anim_data;

			co_pilot_anim_delay -= get_delta_time ();

			if (co_pilot_anim_delay <= 0.0)
			{
				co_pilot_anim_mode = get_random_co_pilot_anim_mode ();

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
		case CO_PILOT_ANIM_MODE_RIGHT_HAND_TO_RH_MFD_BUTTON:
		////////////////////////////////////////
		{
			anim_data = &co_pilot_anim_mode_right_hand_to_rh_mfd_button_anim_data;

			co_pilot_anim_frame += get_delta_time () * (1.0 / 3.0);

			if (co_pilot_anim_frame >= 1.0)
			{
				co_pilot_anim_frame = 1.0;

				co_pilot_anim_mode = CO_PILOT_ANIM_MODE_NONE;
			}

			break;
		}
		////////////////////////////////////////
		case CO_PILOT_ANIM_MODE_LEFT_HAND_TO_LH_MFD_BUTTON:
		////////////////////////////////////////
		{
			anim_data = &co_pilot_anim_mode_left_hand_to_lh_mfd_button_anim_data;

			co_pilot_anim_frame += get_delta_time () * (1.0 / 2.0);

			if (co_pilot_anim_frame >= 1.0)
			{
				co_pilot_anim_frame = 1.0;

				co_pilot_anim_mode = CO_PILOT_ANIM_MODE_NONE;
			}

			break;
		}
		////////////////////////////////////////
		case CO_PILOT_ANIM_MODE_RIGHT_HAND_TO_RH_CONSOLE:
		////////////////////////////////////////
		{
			anim_data = &co_pilot_anim_mode_right_hand_to_rh_console_anim_data;

			co_pilot_anim_frame += get_delta_time () * (1.0 / 3.5);

			if (co_pilot_anim_frame >= 1.0)
			{
				co_pilot_anim_frame = 1.0;

				co_pilot_anim_mode = CO_PILOT_ANIM_MODE_NONE;
			}

			break;
		}
		////////////////////////////////////////
		case CO_PILOT_ANIM_MODE_LEFT_HAND_TO_LH_CONSOLE:
		////////////////////////////////////////
		{
			anim_data = &co_pilot_anim_mode_left_hand_to_lh_console_anim_data;

			co_pilot_anim_frame += get_delta_time () * (1.0 / 3.0);

			if (co_pilot_anim_frame >= 1.0)
			{
				co_pilot_anim_frame = 1.0;

				co_pilot_anim_mode = CO_PILOT_ANIM_MODE_NONE;
			}

			break;
		}
		////////////////////////////////////////
		case CO_PILOT_ANIM_MODE_RIGHT_HAND_TO_CALCULATOR:
		////////////////////////////////////////
		{
			anim_data = &co_pilot_anim_mode_right_hand_to_calculator_anim_data;

			co_pilot_anim_frame += get_delta_time () * (1.0 / 2.5);

			if (co_pilot_anim_frame >= 1.0)
			{
				co_pilot_anim_frame = 1.0;

				co_pilot_anim_mode = CO_PILOT_ANIM_MODE_NONE;
			}

			break;
		}
		////////////////////////////////////////
		case CO_PILOT_ANIM_MODE_LEFT_HAND_TO_RH_SMALL_MFD_BUTTON:
		////////////////////////////////////////
		{
			anim_data = &co_pilot_anim_mode_left_hand_to_rh_small_mfd_button_anim_data;

			co_pilot_anim_frame += get_delta_time () * (1.0 / 3.0);

			if (co_pilot_anim_frame >= 1.0)
			{
				co_pilot_anim_frame = 1.0;

				co_pilot_anim_mode = CO_PILOT_ANIM_MODE_NONE;
			}

			break;
		}
		////////////////////////////////////////
		case CO_PILOT_ANIM_MODE_LEFT_HAND_TO_LH_MFD_TOP_BUTTON:
		////////////////////////////////////////
		{
			anim_data = &co_pilot_anim_mode_left_hand_to_lh_mfd_top_button_anim_data;

			co_pilot_anim_frame += get_delta_time () * (1.0 / 3.0);

			if (co_pilot_anim_frame >= 1.0)
			{
				co_pilot_anim_frame = 1.0;

				co_pilot_anim_mode = CO_PILOT_ANIM_MODE_NONE;
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

	ASSERT (co_pilot_anim_mode == CO_PILOT_ANIM_MODE_NONE);

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

	frame = (co_pilot_head_tilt_angle * (0.5 / MAX_ROLL)) + 0.5;

	anim_frame = ((CO_PILOT_HEAD_TILT_LEFT_TO_RIGHT_ANIM_END - CO_PILOT_HEAD_TILT_LEFT_TO_RIGHT_ANIM_START) * frame) + CO_PILOT_HEAD_TILT_LEFT_TO_RIGHT_ANIM_START;

	anim_frame = bound (anim_frame, CO_PILOT_HEAD_TILT_LEFT_TO_RIGHT_ANIM_START, CO_PILOT_HEAD_TILT_LEFT_TO_RIGHT_ANIM_END);

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

void initialise_viper_co_pilot_animation (void)
{
	#if DEBUG_MODULE

	debug_colour_watch (COLOUR_AMBER, "co_pilot_anim_mode = %d", MT_INT, &co_pilot_anim_mode);
	debug_colour_watch (COLOUR_AMBER, "co_pilot_anim_frame = %.2f", MT_FLOAT, &co_pilot_anim_frame);
	debug_colour_watch (COLOUR_AMBER, "co_pilot_anim_delay = %.2f", MT_FLOAT, &co_pilot_anim_delay);

	debug_colour_watch (COLOUR_AMBER, "co_pilot_head_anim_frame = %.2f", MT_FLOAT, &co_pilot_head_anim_frame);
	debug_colour_watch (COLOUR_AMBER, "co_pilot_head_anim_pause = %.2f", MT_FLOAT, &co_pilot_head_anim_pause);

	#endif

	co_pilot_anim_mode			 				= CO_PILOT_ANIM_MODE_NONE;
	co_pilot_anim_frame  			  			= 0.0;
	co_pilot_anim_delay  						= get_reset_co_pilot_anim_delay ();

	co_pilot_head_anim_frame					= NO_CO_PILOT_HEAD_ANIMATION;
	co_pilot_head_anim_pause					= 0.0;

	previous_co_pilot_head_tilt_angle		= 0.0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_viper_co_pilot_animation (void)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_viper_co_pilot_animation (void)
{
	ASSERT (get_gunship_entity ());

	ASSERT (current_flight_dynamics);

	ASSERT (virtual_cockpit_inst3d);

	update_co_pilot_animation ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_viper_co_pilot_head_position (void)
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
				if (co_pilot_anim_mode == CO_PILOT_ANIM_MODE_NONE)
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

float get_viper_co_pilot_head_pitch_datum (void)
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
