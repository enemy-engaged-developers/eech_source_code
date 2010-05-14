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

//VJ 051029 toggle high LOD setting
static void toggle_high_LOD_event (event *ev)
{
	if (command_line_high_lod_hack == 1)
		command_line_high_lod_hack = 0;
	else
		command_line_high_lod_hack = 1;		
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_next_hud_colour_event (event *ev)
{
	gunship_types type = get_global_gunship_type();
	
	if (type >= (sizeof(hud_code) / sizeof(hud_code[0])))
		type = GUNSHIP_TYPE_AH64A;
	
	set_next_hud_colour ();

	//VJ 060211 hud_code: store hud info
	hud_code[(int)type][HUD_CODES_COLOUR] = get_global_hud_colour();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//VJ 050205 hijacked this key for HUD background colour
/*static void set_prev_hud_colour_event (event *ev)
{
	set_prev_hud_colour ();
}*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//VJ 050205 hijacked this key for HUD background colour
static void set_next_hud_alpha_event (event *ev)
{
	gunship_types type = get_global_gunship_type();
	
	if (type >= (sizeof(hud_code) / sizeof(hud_code[0])))
		type = GUNSHIP_TYPE_AH64A;

	global_hud_alpha += 16;	   
	if (global_hud_alpha > 160)
		global_hud_alpha = 0;
		
	//VJ 060211 hud_code: store hud info
	hud_code[(int)type][HUD_CODES_ALPHA] = global_hud_alpha;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//VJ 050205 HUD size mod
static void toggle_hud_enlarge_event (event *ev)
{

	set_global_hud_enlarge (get_global_hud_enlarge () ^ 1);
	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//VJ 050518 different PNVS brighness levels
static void toggle_PNVS_level_event (event *ev)
{
	global_PNVS_level++;
	if (global_PNVS_level > 2)
		global_PNVS_level = 0;
}	

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void toggle_wiper_on_event (event *ev)
{
	toggle_wiper_on ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void toggle_intermittent_wipe_event (event *ev)
{
	toggle_intermittent_wipe ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_next_waypoint_event (event *ev)
{
	set_next_waypoint ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_prev_waypoint_event (event *ev)
{
	set_prev_waypoint ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void toggle_blurred_main_rotors_visible_from_cockpit_event (event *ev)
{
	if (get_global_blurred_main_rotors_visible_from_cockpit ())
	{
		set_global_blurred_main_rotors_visible_from_cockpit (FALSE);

		set_status_message (get_trans ("Cockpit blurred rotors OFF"), STATUS_MESSAGE_TYPE_NONE);
	}
	else
	{
		set_global_blurred_main_rotors_visible_from_cockpit (TRUE);

		set_status_message (get_trans ("Cockpit blurred rotors ON"), STATUS_MESSAGE_TYPE_NONE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void launch_weapon_event (event *ev)
{
	entity
		*en;

	entity_sub_types
		weapon_sub_type;

	en = get_gunship_entity ();

	if (en)
	{
		weapon_sub_type = get_local_entity_int_value (en, INT_TYPE_SELECTED_WEAPON);

		if (ev->state == KEY_STATE_DOWN)
		{
			if (weapon_database[weapon_sub_type].rate_of_fire == FIRE_SINGLE_WEAPON)
			{
				fire_single_weapon++;
			}
			else
			{
				fire_continuous_weapon = TRUE;
			}
		}
		else
		{
			if (fire_continuous_weapon)
			{
				//
				// required to stop chaingun sound effects
				//

				pause_client_server_continuous_weapon_sound_effect (en, weapon_sub_type);
			}

			fire_continuous_weapon = FALSE;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void launch_chaff_event (event *ev)
{
	launch_client_server_weapon (get_gunship_entity (), ENTITY_SUB_TYPE_WEAPON_CHAFF);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void launch_flare_event (event *ev)
{
	launch_client_server_weapon (get_gunship_entity (), ENTITY_SUB_TYPE_WEAPON_FLARE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void fire_extinguisher_release_event (event *ev)
{
	if (fire_extinguisher_used < 2)
	{
		fire_extinguisher_used++;

		set_dynamics_damage_repair_type (DYNAMICS_DAMAGE_LEFT_ENGINE_FIRE | DYNAMICS_DAMAGE_RIGHT_ENGINE_FIRE);

		if (fire_extinguisher_used == 2)
			dynamics_damage_model (DYNAMICS_DAMAGE_FIRE_EXTINGUISHER, FALSE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void select_next_weapon_event (event *ev)
{
	set_gunship_weapon (get_next_available_weapon_sub_type (get_gunship_entity ()));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void select_previous_weapon_event (event *ev)
{
	set_gunship_weapon (get_previous_available_weapon_sub_type (get_gunship_entity ()));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void increase_rocket_salvo_size_event (event *ev)
{
	increase_rocket_salvo_size ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void decrease_rocket_salvo_size_event (event *ev)
{
	decrease_rocket_salvo_size ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void weapons_safe_event (event *ev)
{
	set_gunship_weapon (ENTITY_SUB_TYPE_WEAPON_NO_WEAPON);

	switch (get_global_gunship_type ())
	{
		////////////////////////////////////////
		// JB 030313 Fly any aircraft
//		default:
		case GUNSHIP_TYPE_APACHE:
		////////////////////////////////////////
		{
			if (target_acquisition_system == TARGET_ACQUISITION_SYSTEM_IHADSS)
			{
				select_apache_target_acquisition_system (TARGET_ACQUISITION_SYSTEM_OFF);
			}

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_HAVOC:
		////////////////////////////////////////
		{
			if (target_acquisition_system == TARGET_ACQUISITION_SYSTEM_HMS)
			{
				select_havoc_target_acquisition_system (TARGET_ACQUISITION_SYSTEM_OFF);
			}

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_COMANCHE:
		////////////////////////////////////////
		{
			if (target_acquisition_system == TARGET_ACQUISITION_SYSTEM_HIDSS)
			{
				select_comanche_target_acquisition_system (TARGET_ACQUISITION_SYSTEM_OFF);
			}

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_HOKUM:
		////////////////////////////////////////
		{
			if (target_acquisition_system == TARGET_ACQUISITION_SYSTEM_HMS)
			{
				select_hokum_target_acquisition_system (TARGET_ACQUISITION_SYSTEM_OFF);
			}

			break;
		}
		////Moje 030518 Start
		case GUNSHIP_TYPE_BLACKHAWK:
		////////////////////////////////////////
		{
			if (target_acquisition_system == TARGET_ACQUISITION_SYSTEM_IHADSS)
			{
				select_blackhawk_target_acquisition_system (TARGET_ACQUISITION_SYSTEM_OFF);
			}

			break;
		}

		////Moje 030518 End
		////Moje 030612 Start
		////////////////////////////////////////
		case GUNSHIP_TYPE_HIND:
		////////////////////////////////////////
		{
			if (target_acquisition_system == TARGET_ACQUISITION_SYSTEM_HMS)
			{
				select_hind_target_acquisition_system (TARGET_ACQUISITION_SYSTEM_OFF);
			}
			break;
		}
		////Moje 030612 End
		////Moje 030816 Start
		case GUNSHIP_TYPE_AH64A:
		////////////////////////////////////////
		{
			if (target_acquisition_system == TARGET_ACQUISITION_SYSTEM_IHADSS)
			{
				select_ah64a_target_acquisition_system (TARGET_ACQUISITION_SYSTEM_OFF);
			}
			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_KA50:
		////////////////////////////////////////
		{
			if (target_acquisition_system == TARGET_ACQUISITION_SYSTEM_HMS)
			{
				select_ka50_target_acquisition_system (TARGET_ACQUISITION_SYSTEM_OFF);
			}
			break;
		}
		////Moje 030816 End

		case GUNSHIP_TYPE_VIPER:
		////////////////////////////////////////
		// GCsDriver  08-12-2007
		default:
		////////////////////////////////////////
		{
			if (target_acquisition_system == TARGET_ACQUISITION_SYSTEM_IHADSS)
			{
				select_default_target_acquisition_system (TARGET_ACQUISITION_SYSTEM_OFF);
			}

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void toggle_auto_countermeasures_event (event *ev)
{
	if (get_global_auto_counter_measures ())
	{
		set_global_auto_counter_measures (FALSE);
	}
	else
	{
		set_global_auto_counter_measures (TRUE);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void rearm_refuel_repair_event (event *ev)
{
	#if DEMO_VERSION

	set_status_message ("Feature disabled in demo version", STATUS_MESSAGE_TYPE_NONE);

	#else

	weapon_config_types
		config_type;

	ASSERT (get_session_entity ());

	ASSERT (get_gunship_entity ());

	ASSERT (current_flight_dynamics);

	if (get_local_entity_int_value (get_session_entity (), INT_TYPE_CHEATS_ENABLED))
	{
		//
		// re-arm
		//
	
		config_type = (weapon_config_types) get_local_entity_int_value (get_gunship_entity (), INT_TYPE_WEAPON_CONFIG_TYPE);
	
		set_client_server_entity_int_value (get_gunship_entity (), INT_TYPE_WEAPON_CONFIG_TYPE, config_type);
	
		//
		// refuel
		//
	
		current_flight_dynamics->fuel_weight.value = current_flight_dynamics->fuel_weight.max;
	
		//
		// repair
		//
	
		fully_repair_local_entity_avionics (get_gunship_entity ());
	
		repair_damage_model (DYNAMICS_DAMAGE_ALL);
	
		set_status_message (get_trans ("Rearmed, refuelled and repaired"), STATUS_MESSAGE_TYPE_NONE);
	}
	
	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void load_air_to_ground_weapons_event (event *ev)
{
	#if DEMO_VERSION

	set_status_message ("Feature disabled in demo version", STATUS_MESSAGE_TYPE_NONE);

	#else

	weapon_config_types
		config_type;

	ASSERT (get_session_entity ());

	ASSERT (get_gunship_entity ());

	if (get_local_entity_int_value (get_session_entity (), INT_TYPE_CHEATS_ENABLED))
	{
		config_type = (weapon_config_types) get_local_entity_int_value (get_gunship_entity (), INT_TYPE_AIR_TO_SURFACE_WEAPON_CONFIG_TYPE);
	
		set_client_server_entity_int_value (get_gunship_entity (), INT_TYPE_WEAPON_CONFIG_TYPE, config_type);
	
		set_status_message (get_trans ("Loaded air-to-ground weapons"), STATUS_MESSAGE_TYPE_NONE);
	}
	
	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void load_air_to_air_weapons_event (event *ev)
{
	#if DEMO_VERSION

	set_status_message ("Feature disabled in demo version", STATUS_MESSAGE_TYPE_NONE);

	#else

	weapon_config_types
		config_type;

	ASSERT (get_session_entity ());

	ASSERT (get_gunship_entity ());

	if (get_local_entity_int_value (get_session_entity (), INT_TYPE_CHEATS_ENABLED))
	{
		config_type = (weapon_config_types) get_local_entity_int_value (get_gunship_entity (), INT_TYPE_AIR_TO_AIR_WEAPON_CONFIG_TYPE);
	
		set_client_server_entity_int_value (get_gunship_entity (), INT_TYPE_WEAPON_CONFIG_TYPE, config_type);
	
		set_status_message (get_trans ("Loaded air-to-air weapons"), STATUS_MESSAGE_TYPE_NONE);
	}
	
	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void load_scout_weapons_event (event *ev)
{
	#if DEMO_VERSION

	set_status_message ("Feature disabled in demo version", STATUS_MESSAGE_TYPE_NONE);

	#else

	weapon_config_types
		config_type;

	ASSERT (get_session_entity ());

	ASSERT (get_gunship_entity ());

	if (get_local_entity_int_value (get_session_entity (), INT_TYPE_CHEATS_ENABLED))
	{
		config_type = (weapon_config_types) get_local_entity_int_value (get_gunship_entity (), INT_TYPE_SCOUT_WEAPON_CONFIG_TYPE);
	
		set_client_server_entity_int_value (get_gunship_entity (), INT_TYPE_WEAPON_CONFIG_TYPE, config_type);
	
		set_status_message (get_trans ("Loaded scout mission weapons"), STATUS_MESSAGE_TYPE_NONE);
	}
	
	#endif
}


// Jabberwock 030930 FLIR mouse control
// Retro 27Nov2004 - new mouselook enum

static void mouse_next_target_event (event *ev)
{
	if ((command_line_mouse_look == MOUSELOOK_OFF) || (command_line_mouse_look == MOUSELOOK_EXTERNAL) ||
		(query_TIR_active() == TRUE))
	{
		single_target_acquisition_system_select_next_target_key++;
	}
}


static void mouse_lock_target_event (event *ev)
{
	if ((command_line_mouse_look == MOUSELOOK_OFF) || (command_line_mouse_look == MOUSELOOK_EXTERNAL) ||
		(query_TIR_active() == TRUE))
	{
		toggle_comanche_lock_target ();
	}
}

static void mouse_left_event (event *ev)
{
	if ((command_line_mouse_look == MOUSELOOK_OFF) || (command_line_mouse_look == MOUSELOOK_EXTERNAL) ||
		(query_TIR_active() == TRUE))
	{
		mouse_move_left++;
	}
}
	
static void mouse_right_event (event *ev)
{
	if ((command_line_mouse_look == MOUSELOOK_OFF) || (command_line_mouse_look == MOUSELOOK_EXTERNAL) ||
		(query_TIR_active() == TRUE))
	{
		mouse_move_right++;
	}
}

static void mouse_up_event (event *ev)
{
	if ((command_line_mouse_look == MOUSELOOK_OFF) || (command_line_mouse_look == MOUSELOOK_EXTERNAL) ||
		(query_TIR_active() == TRUE))
	{
		mouse_move_down++;
	}
}

static void mouse_down_event (event *ev)
{
	if ((command_line_mouse_look == MOUSELOOK_OFF) || (command_line_mouse_look == MOUSELOOK_EXTERNAL) ||
		(query_TIR_active() == TRUE))
	{
		mouse_move_up++;
	}
}

static void mouse_wheel_down_event (event *ev)
{
	if ((command_line_eo_zoom_joystick_index == -1)/*&&(command_line_eo_zoom_joystick_axis == -1)*/)	// Retro 12Dez2004
		mouse_wheel_down++;
}

static void mouse_wheel_up_event (event *ev)
{
	if ((command_line_eo_zoom_joystick_index == -1)/*&&(command_line_eo_zoom_joystick_axis == -1)*/)	// Retro 12Dez2004
		mouse_wheel_up++;
}



// Jabberwock 030930 ends

static void mouse_left_button_event (event* ev)
{
	switch (target_acquisition_system)
	{

	case TARGET_ACQUISITION_SYSTEM_FLIR:
	case TARGET_ACQUISITION_SYSTEM_DTV:
	case TARGET_ACQUISITION_SYSTEM_DVO:
	case TARGET_ACQUISITION_SYSTEM_LLLTV:
	case TARGET_ACQUISITION_SYSTEM_PERISCOPE:
		if (get_global_gunship_type() != GUNSHIP_TYPE_APACHE || !command_line_mouse_tsd_target_select)
		{
			if (ev->state == BUTTON_STATE_DOWN)
				mouse_lock_target_event(ev);
			break;
		}
		// fall through
	default:
		store_point_left_event(ev);
		break;
	}
}

static void mouse_right_button_event (event* ev)
{
	switch (target_acquisition_system)
	{
	case TARGET_ACQUISITION_SYSTEM_FLIR:
	case TARGET_ACQUISITION_SYSTEM_DTV:
	case TARGET_ACQUISITION_SYSTEM_DVO:
	case TARGET_ACQUISITION_SYSTEM_LLLTV:
	case TARGET_ACQUISITION_SYSTEM_PERISCOPE:
		if (ev->state == BUTTON_STATE_DOWN)
			mouse_next_target_event(ev);
		break;
	default:
		store_point_right_event(ev);
	}
}


static void mouselook_toggle (event *ev)
{
	// Retro 27Nov2004 - FIXME: cycle through all modes ?
	if (command_line_mouse_look != MOUSELOOK_OFF)
	{
		command_line_mouse_look = MOUSELOOK_OFF;
	}
	else
	{
		command_line_mouse_look = MOUSELOOK_ON;		
	}
}

// Jabberwock 031107 Designated target

static void designate_toggle_event (event *ev)
{
	toggle_designated_target ();
}

static void select_next_designated_target_event (event *ev)
{
	single_target_acquisition_system_select_next_designated_key++;
}

static void select_previous_designated_target_event (event *ev)
{
	single_target_acquisition_system_select_previous_designated_key++;
}

static void toggle_electrical_sytem_event(event* ev)
{
	set_electrical_system_active(!electrical_system_active());	
}


#ifdef DEBUG
float debug_var_x = 0.0;
float debug_var_y = 0.0;
float debug_var_z = 0.0;

static void inc_debug_var_x(event* ev)
{
	debug_var_x += 1.0;
}

static void inc_debug_var_x_fine(event* ev)
{
	debug_var_x += 0.1;
}
static void dec_debug_var_x(event* ev)
{
	debug_var_x -= 1.0;
}
static void dec_debug_var_x_fine(event* ev)
{
	debug_var_x -= 0.1;
}

static void inc_debug_var_y(event* ev)
{
	debug_var_y += 1.0;
}

static void inc_debug_var_y_fine(event* ev)
{
	debug_var_y += 0.1;
}
static void dec_debug_var_y(event* ev)
{
	debug_var_y -= 1.0;
}
static void dec_debug_var_y_fine(event* ev)
{
	debug_var_y -= 0.1;
}

static void inc_debug_var_z(event* ev)
{
	debug_var_z += 1.0;
}

static void inc_debug_var_z_fine(event* ev)
{
	debug_var_z += 0.1;
}
static void dec_debug_var_z(event* ev)
{
	debug_var_z -= 1.0;
}
static void dec_debug_var_z_fine(event* ev)
{
	debug_var_z -= 0.1;
}
#endif // DEBUG

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_common_avionics_events (void)
{
	if (!get_gunship_entity ())
	{
		return;
	}

	////////////////////////////////////////
	//
	// KEYBOARD EVENTS
	//
	////////////////////////////////////////

	set_event (DIK_7, MODIFIER_LEFT_SHIFT, KEY_STATE_DOWN, load_air_to_ground_weapons_event);

	////////////////////////////////////////

	set_event (DIK_8, MODIFIER_LEFT_SHIFT, KEY_STATE_DOWN, load_air_to_air_weapons_event);

	////////////////////////////////////////

	set_event (DIK_9, MODIFIER_LEFT_SHIFT, KEY_STATE_DOWN, load_scout_weapons_event);

	////////////////////////////////////////

	set_event (DIK_A, MODIFIER_LEFT_SHIFT, KEY_STATE_DOWN, comms_shortcut_attack_my_target);

	////////////////////////////////////////

	set_event (DIK_C, MODIFIER_NONE, KEY_STATE_DOWN, launch_chaff_event);

	set_event (DIK_C, MODIFIER_LEFT_CONTROL, KEY_STATE_DOWN, toggle_auto_countermeasures_event);

	////////////////////////////////////////

	set_event (DIK_F, MODIFIER_NONE, KEY_STATE_DOWN, launch_flare_event);

	set_event (DIK_F, MODIFIER_LEFT_CONTROL, KEY_STATE_DOWN, fire_extinguisher_release_event);

	////////////////////////////////////////

	set_event (DIK_K, MODIFIER_NONE, KEY_STATE_DOWN, set_next_hud_colour_event);

//	set_event (DIK_K, MODIFIER_LEFT_SHIFT, KEY_STATE_DOWN, set_prev_hud_colour_event);
//VJ 050205 hijacked this key for HUD background colour
	set_event (DIK_K, MODIFIER_LEFT_SHIFT, KEY_STATE_DOWN, set_next_hud_alpha_event);

	set_event (DIK_K, MODIFIER_LEFT_CONTROL, KEY_STATE_DOWN, toggle_hud_enlarge_event);

	////////////////////////////////////////

	set_event (DIK_R, MODIFIER_LEFT_CONTROL, KEY_STATE_DOWN, rearm_refuel_repair_event);

	set_event (DIK_R, MODIFIER_LEFT_ALT, KEY_STATE_DOWN, toggle_blurred_main_rotors_visible_from_cockpit_event);

	////////////////////////////////////////

	set_event (DIK_S, MODIFIER_NONE, KEY_STATE_DOWN, increase_rocket_salvo_size_event);

	set_event (DIK_S, MODIFIER_LEFT_SHIFT, KEY_STATE_DOWN, decrease_rocket_salvo_size_event);

	////////////////////////////////////////

	set_event (DIK_W, MODIFIER_NONE, KEY_STATE_DOWN, set_next_waypoint_event);

	set_event (DIK_W, MODIFIER_LEFT_SHIFT, KEY_STATE_DOWN, set_prev_waypoint_event);

	////////////////////////////////////////

	set_event (DIK_Y, MODIFIER_NONE, KEY_STATE_DOWN, toggle_wiper_on_event);

	set_event (DIK_Y, MODIFIER_LEFT_ALT, KEY_STATE_DOWN, toggle_intermittent_wipe_event);

	////////////////////////////////////////

	set_event (DIK_SPACE, MODIFIER_NONE, KEY_STATE_EITHER, launch_weapon_event);

	////////////////////////////////////////

	set_event (DIK_BACKSPACE, MODIFIER_NONE, KEY_STATE_DOWN, select_next_weapon_event);

	set_event (DIK_BACKSPACE, MODIFIER_LEFT_SHIFT, KEY_STATE_DOWN, select_previous_weapon_event);

	set_event (DIK_BACKSPACE, MODIFIER_LEFT_CONTROL, KEY_STATE_DOWN, weapons_safe_event);

	////////////////////////////////////////
	//
	// JOYSTICK EVENTS
	//
	////////////////////////////////////////

	set_event ((JOYSTICK_BUTTON + 1), MODIFIER_NONE, KEY_STATE_EITHER, launch_weapon_event);

	set_event ((JOYSTICK_BUTTON + 2), MODIFIER_NONE, KEY_STATE_DOWN, select_next_weapon_event);

	// Jabberwock 030930 Mouse FLIR control

	set_event (MOUSE_LEFT_BUTTON, MODIFIER_NONE, BUTTON_STATE_EITHER, mouse_left_button_event);
	set_event (MOUSE_RIGHT_BUTTON, MODIFIER_NONE, BUTTON_STATE_EITHER, mouse_right_button_event);

	set_event (MOUSE_MOVE_UP, MODIFIER_NONE, BUTTON_STATE_EITHER, mouse_up_event);
	set_event (MOUSE_MOVE_DOWN, MODIFIER_NONE, BUTTON_STATE_EITHER, mouse_down_event);
	set_event (MOUSE_MOVE_LEFT, MODIFIER_NONE, BUTTON_STATE_EITHER, mouse_left_event);
	set_event (MOUSE_MOVE_RIGHT, MODIFIER_NONE, BUTTON_STATE_EITHER, mouse_right_event);

	set_event (MOUSE_WHEEL_UP, MODIFIER_NONE, BUTTON_STATE_EITHER, mouse_wheel_up_event);
	set_event (MOUSE_WHEEL_DOWN, MODIFIER_NONE, BUTTON_STATE_EITHER, mouse_wheel_down_event);

	// Jabberwock 030930 ends
	
	// Jabberwock 031016 Mouselook toggle
	
	set_event (MOUSE_MIDDLE_BUTTON, MODIFIER_NONE, BUTTON_STATE_DOWN, mouselook_toggle);
	set_event (DIK_DELETE, MODIFIER_LEFT_CONTROL, KEY_STATE_DOWN, mouselook_toggle);
	
	// Jabberwock 031016 ends
	
	// Jabberwock 031107 Designated targets
	
	set_event (DIK_NUMPADENTER, MODIFIER_LEFT_ALT, KEY_STATE_DOWN, designate_toggle_event); 

	set_event (DIK_NUMPAD0, MODIFIER_LEFT_ALT, KEY_STATE_DOWN, select_next_designated_target_event);
	
	set_event (DIK_NUMPAD0, MODIFIER_LEFT_CONTROL, KEY_STATE_DOWN, select_previous_designated_target_event);

	set_event (DIK_N, MODIFIER_LEFT_CONTROL, KEY_STATE_DOWN, toggle_PNVS_level_event);

//VJ 051029 toggle high LOD setting
	set_event (DIK_L, MODIFIER_LEFT_ALT, KEY_STATE_DOWN, toggle_high_LOD_event);

// arneh 20070103 - electrical system
	set_event (DIK_K, MODIFIER_LEFT_CONTROL, KEY_STATE_DOWN, toggle_electrical_sytem_event);
#ifdef DEBUG
	set_event (DIK_RIGHT, MODIFIER_RIGHT_CONTROL, KEY_STATE_DOWN, inc_debug_var_x);
	set_event (DIK_RIGHT, MODIFIER_RIGHT_SHIFT, KEY_STATE_DOWN, inc_debug_var_x_fine);
	set_event (DIK_LEFT, MODIFIER_RIGHT_CONTROL, KEY_STATE_DOWN, dec_debug_var_x);
	set_event (DIK_LEFT, MODIFIER_RIGHT_SHIFT, KEY_STATE_DOWN, dec_debug_var_x_fine);

	set_event (DIK_UP, MODIFIER_RIGHT_CONTROL, KEY_STATE_DOWN, inc_debug_var_y);
	set_event (DIK_UP, MODIFIER_RIGHT_ALT, KEY_STATE_DOWN, inc_debug_var_y_fine);
	set_event (DIK_DOWN, MODIFIER_RIGHT_CONTROL, KEY_STATE_DOWN, dec_debug_var_y);
	set_event (DIK_DOWN, MODIFIER_RIGHT_ALT, KEY_STATE_DOWN, dec_debug_var_y_fine);

	set_event (DIK_INSERT, MODIFIER_RIGHT_CONTROL, KEY_STATE_DOWN, inc_debug_var_z);
	set_event (DIK_INSERT, MODIFIER_RIGHT_SHIFT, KEY_STATE_DOWN, inc_debug_var_z_fine);
	set_event (DIK_DELETE, MODIFIER_RIGHT_CONTROL, KEY_STATE_DOWN, dec_debug_var_z);
	set_event (DIK_DELETE, MODIFIER_RIGHT_SHIFT, KEY_STATE_DOWN, dec_debug_var_z_fine);
#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

