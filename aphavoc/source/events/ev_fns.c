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



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "project.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ui_events (void)
{

	//
	// general keys
	//

	set_event (DIK_X, MODIFIER_LEFT_CONTROL, KEY_STATE_UP, exit_apache_havoc);

	//
	// mouse buttons
	//

	set_event (MOUSE_LEFT_BUTTON, MODIFIER_NONE, BUTTON_STATE_EITHER, ui_left_mouse_button);

	set_event (MOUSE_RIGHT_BUTTON, MODIFIER_NONE, BUTTON_STATE_EITHER, ui_right_mouse_button);

	//
	// debug
	//

	#ifndef COMMERCIAL

	set_event (DIK_SCROLL, MODIFIER_NONE, KEY_STATE_UP, breakout);

	set_ui_debug_events ();

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if DEMO_VERSION

static void feature_disabled_event (event *ev)
{
	set_status_message ("Feature disabled in demo version", STATUS_MESSAGE_TYPE_NONE);
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void flight_events (void)
{

	//
	// Mouse buttons
	//

	set_event (MOUSE_LEFT_BUTTON, MODIFIER_NONE, BUTTON_STATE_EITHER, ui_left_mouse_button);

	set_event (MOUSE_RIGHT_BUTTON, MODIFIER_NONE, BUTTON_STATE_EITHER, ui_right_mouse_button);

	//
	// General
	//

	set_event (DIK_X, MODIFIER_LEFT_CONTROL, KEY_STATE_UP, exit_apache_havoc);

	set_event (DIK_Q, MODIFIER_LEFT_CONTROL, KEY_STATE_UP, ingame_quit_function);

   set_event (DIK_RETURN, MODIFIER_NONE, KEY_STATE_DOWN, toggle_in_flight_game_modes);

   set_event (DIK_RETURN, MODIFIER_LEFT_SHIFT, KEY_STATE_DOWN, campaign_screen_show_external_view_entity);

	#if DEMO_VERSION

	set_event (DIK_U, MODIFIER_NONE, KEY_STATE_DOWN, feature_disabled_event);

	#else

	set_event (DIK_U, MODIFIER_NONE, KEY_STATE_DOWN, set_gunship_entity_to_external_view_entity);

	#endif

	//
	// time acceleration
	//

   set_event (DIK_EQUALS, MODIFIER_LEFT_CONTROL, KEY_STATE_DOWN, set_small_inc_time_acceleration);

   set_event (DIK_MINUS, MODIFIER_LEFT_CONTROL, KEY_STATE_DOWN, set_small_dec_time_acceleration);

	// for keyboards that don't support the +/- in the normal place (Japanese?)
   set_event (DIK_NUMPADPLUS, MODIFIER_LEFT_CONTROL, KEY_STATE_DOWN, set_small_inc_time_acceleration);

   set_event (DIK_NUMPADMINUS, MODIFIER_LEFT_CONTROL, KEY_STATE_DOWN, set_small_dec_time_acceleration);

   set_event (DIK_P, MODIFIER_NONE, KEY_STATE_DOWN, toggle_pause_time_acceleration);

	//
	// screen shots
	//

	set_event (DIK_SYSRQ, MODIFIER_NONE, KEY_STATE_DOWN, save_screen_image_event);

	//
	// messaging system
	//

	set_event (DIK_TAB, MODIFIER_NONE, KEY_STATE_DOWN, start_messaging_system);

	set_event (DIK_TAB, MODIFIER_LEFT_CONTROL, KEY_STATE_DOWN, display_last_received_message);

	#ifndef COMMERCIAL

   set_event (DIK_SCROLL, MODIFIER_NONE, KEY_STATE_DOWN, breakout);

	set_flight_debug_events ();

	// debug time acceleration

   //set_event (DIK_MINUS, MODIFIER_RIGHT_SHIFT, KEY_STATE_DOWN, set_min_time_acceleration);

   //set_event (DIK_EQUALS, MODIFIER_RIGHT_SHIFT, KEY_STATE_DOWN, set_big_inc_time_acceleration);

   //set_event (DIK_EQUALS, MODIFIER_RIGHT_CONTROL, KEY_STATE_DOWN, set_small_inc_time_acceleration);

   //set_event (DIK_MINUS, MODIFIER_RIGHT_CONTROL, KEY_STATE_DOWN, set_small_dec_time_acceleration);

	#endif

   process_user_defined_flight_events ();

	generate_key_bound_triggers ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void demo_events (void)
{
	//
	// General
	//

   set_event (DIK_ESCAPE, MODIFIER_NONE, KEY_STATE_UP, exit_game);

	set_event (DIK_Q, MODIFIER_LEFT_CONTROL, KEY_STATE_UP, exit_game);

	set_event (DIK_X, MODIFIER_LEFT_CONTROL, KEY_STATE_UP, exit_apache_havoc);

	//
	// time acceleration
	//

   set_event (DIK_EQUALS, MODIFIER_LEFT_CONTROL, KEY_STATE_DOWN, set_small_inc_time_acceleration);

   set_event (DIK_MINUS, MODIFIER_LEFT_CONTROL, KEY_STATE_DOWN, set_small_dec_time_acceleration);

   set_event (DIK_P, MODIFIER_NONE, KEY_STATE_DOWN, toggle_pause_time_acceleration);

	//
	//
	//

#if ( OEM_3DLABS_VERSION )

	set_event ( DIK_1, MODIFIER_NONE, KEY_STATE_DOWN, increase_3d_resolutions );

	set_event ( DIK_1, MODIFIER_LEFT_SHIFT, KEY_STATE_DOWN, decrease_3d_resolutions );

	set_event ( DIK_2, MODIFIER_NONE, KEY_STATE_DOWN, cycle_3d_colourdepth );

	set_event ( DIK_3, MODIFIER_NONE, KEY_STATE_DOWN, toggle_3d_object_lod_calculations );

	set_event ( DIK_I, MODIFIER_NONE, KEY_STATE_DOWN, toggle_3d_information );

#endif

	set_demo_view_mode_events ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
