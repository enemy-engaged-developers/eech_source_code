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

#define DEBUG_MODULE						0

#define DEBUG_MODULE_SEAT_SWITCHING	0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// #define ROTATE_RATE	(rad (135.0)) // Jabberwock 031016 - variable POV speed

//VJ 050208 gives the possibility to look behind you (since you can't turn your body)
#define MAX_LOOK_ANGLE_LEFT_RIGHT1  135.0   //Comanche and Hokum
#define MAX_LOOK_ANGLE_LEFT_RIGHT2  100.0   //the rest
#define MAX_LOOK_ANGLE_UP1  75.0	//comanche, hokum   //was 45
#define MAX_LOOK_ANGLE_UP2  75.0 //rest              //was 40
#define MAX_LOOK_ANGLE_DOWN1  60.0 //comanche, hokum //was 45
#define MAX_LOOK_ANGLE_DOWN2  25.0 //rest            //was 20
#define MAX_LOOK_ANGLE_DOWN3  45.0 //apache

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static padlock_modes
	padlock_mode;
padlock_modes
	inset_mode;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static float get_rotate_left_limit (void)
{
	float
		limit;

	switch (get_global_gunship_type ())
	{
		////////////////////////////////////////
		case GUNSHIP_TYPE_APACHE:
		////////////////////////////////////////
		{
			if (command_line_3d_cockpit)
				limit = rad (MAX_LOOK_ANGLE_LEFT_RIGHT1);
			else
				limit = rad (MAX_LOOK_ANGLE_LEFT_RIGHT2);

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_HAVOC:
		////////////////////////////////////////
		{
			limit = rad (MAX_LOOK_ANGLE_LEFT_RIGHT2);

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_COMANCHE:
		////////////////////////////////////////
		{
			limit = rad (MAX_LOOK_ANGLE_LEFT_RIGHT1);

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_HOKUM:
		////////////////////////////////////////
		{
			limit = rad (MAX_LOOK_ANGLE_LEFT_RIGHT1);

			break;
		}
		////Moje 030518 Start
		////////////////////////////////////////
		case GUNSHIP_TYPE_BLACKHAWK:
		////////////////////////////////////////
		{
			limit = rad (MAX_LOOK_ANGLE_LEFT_RIGHT2);

			break;
		}
		////Moje 030518 End
		////Moje 030612 Start
		////////////////////////////////////////
		case GUNSHIP_TYPE_HIND:
		////////////////////////////////////////
		{
			limit = rad (MAX_LOOK_ANGLE_LEFT_RIGHT1);

			break;
		}
		////Moje 030612 End
		////Moje 030816 Start
		////////////////////////////////////////
		case GUNSHIP_TYPE_AH64A:
		////////////////////////////////////////
		{
			limit = rad (MAX_LOOK_ANGLE_LEFT_RIGHT2);

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_KA50:
		////////////////////////////////////////
		{
			limit = rad (MAX_LOOK_ANGLE_LEFT_RIGHT2);

			break;
		}
		////Moje 030816 End
		case GUNSHIP_TYPE_KIOWA:
		////////////////////////////////////////
		{
			limit = rad (MAX_LOOK_ANGLE_LEFT_RIGHT1);

			break;
		}
		////////////////////////////////////////
		////////////////////////////////////////
		case GUNSHIP_TYPE_VIPER:
		default:
		////////////////////////////////////////
		{
			// JB 030313 Fly any aircraft
			//limit = rad (135.0);
			limit = rad (MAX_LOOK_ANGLE_LEFT_RIGHT2);

			break;
		}
	}

	return (limit);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static float get_rotate_right_limit (void)
{
	float
		limit;

	switch (get_global_gunship_type ())
	{
		////////////////////////////////////////
		case GUNSHIP_TYPE_APACHE:
		////////////////////////////////////////
		{
			if (command_line_3d_cockpit)
				limit = rad (-MAX_LOOK_ANGLE_LEFT_RIGHT1);
			else
				limit = rad (-MAX_LOOK_ANGLE_LEFT_RIGHT2);

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_HAVOC:
		////////////////////////////////////////
		{
			limit = rad (-MAX_LOOK_ANGLE_LEFT_RIGHT2);

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_COMANCHE:
		////////////////////////////////////////
		{
			limit = rad (-MAX_LOOK_ANGLE_LEFT_RIGHT1);

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_HOKUM:
		////////////////////////////////////////
		{
			limit = rad (-MAX_LOOK_ANGLE_LEFT_RIGHT1);

			break;
		}
		////Moje 030518 Start
		////////////////////////////////////////
		case GUNSHIP_TYPE_BLACKHAWK:
		////////////////////////////////////////
		{
			limit = rad (-MAX_LOOK_ANGLE_LEFT_RIGHT2);

			break;
		}
		////Moje 030518 End
		////Moje 03061 2Start
		////////////////////////////////////////
		case GUNSHIP_TYPE_HIND:
		////////////////////////////////////////
		{
			limit = rad (-MAX_LOOK_ANGLE_LEFT_RIGHT1);

			break;
		}
		////Moje 030612 End
		////Moje 030816 Start
		////////////////////////////////////////
		case GUNSHIP_TYPE_AH64A:
		////////////////////////////////////////
		{
			limit = rad (-MAX_LOOK_ANGLE_LEFT_RIGHT2);

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_KA50:
		////////////////////////////////////////
		{
			limit = rad (-MAX_LOOK_ANGLE_LEFT_RIGHT2);

			break;
		}
		////Moje 030816 End
		////////////////////////////////////////
		case GUNSHIP_TYPE_KIOWA:
		////////////////////////////////////////
		{
			limit = rad (-MAX_LOOK_ANGLE_LEFT_RIGHT1);

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_VIPER:
		default:
		////////////////////////////////////////
		{
			// JB 030313 Fly any aircraft
			//limit = rad (-135.0);
			limit = rad (-MAX_LOOK_ANGLE_LEFT_RIGHT2);

			break;
		}
	}

	return (limit);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static float get_rotate_up_limit (void)
{
	float
		limit;

	switch (get_global_gunship_type ())
	{
		////////////////////////////////////////
		case GUNSHIP_TYPE_APACHE:
		////////////////////////////////////////
		{
			if (command_line_3d_cockpit)
				limit = rad (MAX_LOOK_ANGLE_UP1);
			else
				limit = rad (MAX_LOOK_ANGLE_UP2);

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_HAVOC:
		////////////////////////////////////////
		{
			limit = rad (MAX_LOOK_ANGLE_UP2);

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_COMANCHE:
		////////////////////////////////////////
		{
			limit = rad (MAX_LOOK_ANGLE_UP1);

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_HOKUM:
		////////////////////////////////////////
		{
			limit = rad (MAX_LOOK_ANGLE_UP1);

			break;
		}
		////Moje 030518 Start
		////////////////////////////////////////
		case GUNSHIP_TYPE_BLACKHAWK:
		////////////////////////////////////////
		{
			limit = rad (MAX_LOOK_ANGLE_UP1);

			break;
		}
		////Moje 030518 End
		////Moje 030612 Start
		////////////////////////////////////////
		case GUNSHIP_TYPE_HIND:
		////////////////////////////////////////
		{
			limit = rad (MAX_LOOK_ANGLE_UP2);

			break;
		}
		////Moje 030612 End
		////Moje 030816 Start
		////////////////////////////////////////
		case GUNSHIP_TYPE_AH64A:
		////////////////////////////////////////
		{
			limit = rad (MAX_LOOK_ANGLE_UP1);

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_KA50:
		////////////////////////////////////////
		{
			limit = rad (MAX_LOOK_ANGLE_UP2);

			break;
		}
		////Moje 030816 End
		////////////////////////////////////////
		case GUNSHIP_TYPE_KIOWA:
		////////////////////////////////////////
		{
			limit = rad (MAX_LOOK_ANGLE_UP1);

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_VIPER:
		default:
		////////////////////////////////////////
		{
			// JB 030313 Fly any aircraft
			limit = rad (MAX_LOOK_ANGLE_UP1);
			//limit = rad (0.0);

			break;
		}
	}

	return (limit);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static float get_rotate_down_limit (void)
{
	float
		limit;

	switch (get_global_gunship_type ())
	{
		////////////////////////////////////////
		case GUNSHIP_TYPE_APACHE:
		////////////////////////////////////////
		{
			limit = rad (-MAX_LOOK_ANGLE_DOWN3);

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_HAVOC:
		////////////////////////////////////////
		{
			limit = rad (-MAX_LOOK_ANGLE_DOWN2);

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_COMANCHE:
		////////////////////////////////////////
		{
			limit = rad (-MAX_LOOK_ANGLE_DOWN1);

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_HOKUM:
		////////////////////////////////////////
		{
			limit = rad (-MAX_LOOK_ANGLE_DOWN1);

			break;
		}
		////Moje 030518 Start
		////////////////////////////////////////
		case GUNSHIP_TYPE_BLACKHAWK:
		////////////////////////////////////////
		{
			limit = rad (-MAX_LOOK_ANGLE_DOWN2);

			break;
		}
		////Moje 030518 End
		////Moje 030612 Start
		////////////////////////////////////////
		case GUNSHIP_TYPE_HIND:
		////////////////////////////////////////
		{
			limit = rad (-MAX_LOOK_ANGLE_DOWN1);
			limit = rad(-90);

			break;
		}
		////Moje 030612 End
		////Moje 030816 Start
		////////////////////////////////////////
		case GUNSHIP_TYPE_AH64A:
		////////////////////////////////////////
		{
			limit = rad (-MAX_LOOK_ANGLE_DOWN2);

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_KA50:
		////////////////////////////////////////
		{
			limit = rad (-MAX_LOOK_ANGLE_DOWN2);

			break;
		}
		////Moje 030816 End
		////////////////////////////////////////
		case GUNSHIP_TYPE_KIOWA:
		////////////////////////////////////////
		{
			limit = rad (-MAX_LOOK_ANGLE_DOWN1);

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_VIPER:
		default:
		////////////////////////////////////////
		{
			// JB 030313 Fly any aircraft
			limit = rad (-MAX_LOOK_ANGLE_DOWN2);
			//limit = rad (0.0);

			break;
		}
	}

	return (limit);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_virtual_cockpit_view (void)
{
	pilot_head_vp.position.x = MID_MAP_X;
	pilot_head_vp.position.y = MID_MAP_Y;
	pilot_head_vp.position.z = MID_MAP_Z;

	current_custom_cockpit_viewpoint.x = 0.0;
	current_custom_cockpit_viewpoint.y = 0.0;
	current_custom_cockpit_viewpoint.z = 0.0;


	get_identity_matrix3x3 (pilot_head_vp.attitude);

	//
	// stored values
	//

	stored_pilot_head_heading = rad (0.0);
	stored_pilot_head_pitch = rad (0.0);

	stored_co_pilot_head_heading = rad (0.0);
	stored_co_pilot_head_pitch = rad (0.0);

	stored_pilot_view_mode = VIEW_MODE_VIRTUAL_COCKPIT;
	stored_co_pilot_view_mode = VIEW_MODE_VIRTUAL_COCKPIT;

	stored_pilot_padlock_mode = PADLOCK_MODE_NONE;
	stored_co_pilot_padlock_mode = PADLOCK_MODE_NONE;

	//
	// padlock
	//

	padlock_mode = PADLOCK_MODE_NONE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reinitialise_virtual_cockpit_view (void)
{
	pilot_head_vp.position.x = MID_MAP_X;
	pilot_head_vp.position.y = MID_MAP_Y;
	pilot_head_vp.position.z = MID_MAP_Z;

	get_identity_matrix3x3 (pilot_head_vp.attitude);

	//
	// stored values
	//

	stored_pilot_head_heading = rad (0.0);
	stored_pilot_head_pitch = rad (0.0);

	stored_co_pilot_head_heading = rad (0.0);
	stored_co_pilot_head_pitch = rad (0.0);

	stored_pilot_view_mode = VIEW_MODE_VIRTUAL_COCKPIT;
	stored_co_pilot_view_mode = VIEW_MODE_VIRTUAL_COCKPIT;

	stored_pilot_padlock_mode = PADLOCK_MODE_NONE;
	stored_co_pilot_padlock_mode = PADLOCK_MODE_NONE;

	//
	// padlock
	//

	if (get_gunship_entity ())
	{
		unlink_local_entity_children (get_gunship_entity (), LIST_TYPE_PADLOCK);

		switch (get_global_gunship_type())
		{
		case GUNSHIP_TYPE_APACHE:
			stored_pilot_head_pitch = rad(wide_cockpit_position[WIDEVIEW_APACHE_PILOT].c.p);
			stored_co_pilot_head_pitch = rad(wide_cockpit_position[WIDEVIEW_APACHE_COPILOT].c.p);
			break;
		}
	}

	padlock_mode = PADLOCK_MODE_NONE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_virtual_cockpit_view (void)
{
	//
	// padlock
	//

	if (get_gunship_entity ())
	{
		unlink_local_entity_children (get_gunship_entity (), LIST_TYPE_PADLOCK);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_virtual_cockpit_view (void)
{
	float
		ROTATE_RATE;

	ROTATE_RATE = (float) command_line_mouse_look_speed / 6.0; // Jabberwock 031016 - variable POV speed

	// lfriembichler 030317 start
	// enabled panning by mouse/trackir
	// trackir only works with mousepanning enabled AND the naturalpoint window
	// loaded BEFORE EECH is started !

	if ((command_line_mouse_look == MOUSELOOK_OFF)||	// ..if keyboard/POV panning.. (by me, stuff inside is (C) RW)
		(command_line_mouse_look == MOUSELOOK_EXTERNAL))
	{
		if (command_line_joylook_joystick_index != -1) // Jabberwock 030311 Joystick look
		{
			float
				stp,
				pos;

			stp = (float) command_line_joylook_step / 1000.0;

			pos = (float) get_joystick_axis (command_line_joylook_joystick_index, command_line_joylookh_joystick_axis);

			pos = ((get_rotate_right_limit ()) * pos) / 10000.0;

			if (((pilot_head_heading - (pos)) > stp) || ((pilot_head_heading - (pos) < -stp)))
			{
				pilot_head_heading = (pos);
			}

			pos = (float) get_joystick_axis (command_line_joylook_joystick_index, command_line_joylookv_joystick_axis);

			pos = (get_rotate_up_limit ()) * pos / 10000.0;

			if (((pilot_head_pitch - (pos)) > stp) || ((pilot_head_pitch - (pos)) < -stp))
			{
				pilot_head_pitch = (pos);
			}
		} // Jabberwock 030311 ends
		else
		{
			if (adjust_view_left_key || joystick_pov_left)
			{
				pilot_head_heading += ROTATE_RATE * get_delta_time ();

				pilot_head_heading = min (get_rotate_left_limit (), pilot_head_heading);
			}
			else if (adjust_view_right_key || joystick_pov_right)
			{
				pilot_head_heading -= ROTATE_RATE * get_delta_time ();

				pilot_head_heading = max (get_rotate_right_limit (), pilot_head_heading);
			}

			if (adjust_view_up_key || joystick_pov_up)
			{
				pilot_head_pitch += ROTATE_RATE * get_delta_time ();

				pilot_head_pitch = min (get_rotate_up_limit (), pilot_head_pitch);
			}
			else if (adjust_view_down_key || joystick_pov_down)
			{
				pilot_head_pitch -= (ROTATE_RATE * get_delta_time ());

				pilot_head_pitch = max (get_rotate_down_limit (), pilot_head_pitch);
			}
		}
	}
	else	// Use mouse/TIR, all by Retro 030317, 030318
	{
		float
			temp_p,
			temp_h;

		if (query_TIR_active() == FALSE)	// No TIR window, use mouse;
		{									// ..this also means it´s NOT possible to use TIR in relative mode !!
			static int previous_mouse_update_flag = 1;
			float dh, dp;

			if (previous_mouse_update_flag != get_mouse_update_flag())
			{
				dh = get_mouse_move_delta_x() * -MAX_LOOK_ANGLE_LEFT_RIGHT1 / 8000.0;
				dp = get_mouse_move_delta_y() * -45 / 8000.0;

				previous_mouse_update_flag = get_mouse_update_flag();

				pilot_head_heading += rad(dh);
				pilot_head_pitch += rad(dp);
			}
		}
		else	// TIR
		{
			temp_p = TIR_GetPitch();
			temp_h = TIR_GetYaw();

			temp_p = -45. * temp_p / 16383.;	// Those are the max-possible values as they are restriced above in this file
			temp_h = MAX_LOOK_ANGLE_LEFT_RIGHT1 * temp_h / 16383.;

			pilot_head_pitch = rad(temp_p);
			pilot_head_heading = rad(temp_h);
		}

		pilot_head_heading = min (get_rotate_left_limit (), pilot_head_heading);
		pilot_head_heading = max (get_rotate_right_limit (), pilot_head_heading);

		pilot_head_pitch = min (get_rotate_up_limit (), pilot_head_pitch);
		pilot_head_pitch = max (get_rotate_down_limit (), pilot_head_pitch);
	} // end Retro 030317


//VJ wideview mod, date: 27-mar-03
//VJ 050131 wideview mod, better
/*
	if (get_global_wide_cockpit () &&
		 !command_line_3d_cockpit &&
		 get_global_gunship_type () != GUNSHIP_TYPE_COMANCHE &&
		 get_global_gunship_type () != GUNSHIP_TYPE_HOKUM
		)
	{
         float max_pitch = -0.271*pilot_head_heading*pilot_head_heading - 0.05;

   		pilot_head_pitch = max (max_pitch, pilot_head_pitch);
		//debug_log("heading: %f    pitch %f [%f]",pilot_head_heading,pilot_head_pitch,max_pitch);
	}
	*/
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_virtual_cockpit_track_target_view (void)
{
	float
		old_heading,
		old_pitch,
		delta_heading,
		delta_pitch,
		frame_rotate_rate;

	entity
		*target;

	target = get_local_entity_parent (get_gunship_entity (), LIST_TYPE_TARGET);

	if (target)
	{
		old_heading = pilot_head_heading;

		old_pitch = pilot_head_pitch;

		get_pilot_head_heading_and_pitch_to_target (target);

		frame_rotate_rate = rad (45.0) * get_delta_time ();

		delta_heading = pilot_head_heading - old_heading;

		delta_heading = bound (delta_heading, -frame_rotate_rate, frame_rotate_rate);

		pilot_head_heading = old_heading + delta_heading;

		delta_pitch = pilot_head_pitch - old_pitch;

		delta_pitch = bound (delta_pitch, -frame_rotate_rate, frame_rotate_rate);

		pilot_head_pitch = old_pitch + delta_pitch;
	}
	else
	{
		frame_rotate_rate = rad (45.0) * get_delta_time ();

		delta_heading = bound (-pilot_head_heading, -frame_rotate_rate, frame_rotate_rate);

		pilot_head_heading += delta_heading;

		delta_pitch = bound (-pilot_head_pitch, -frame_rotate_rate, frame_rotate_rate);

		pilot_head_pitch += delta_pitch;

		if
		(
			(pilot_head_heading >= rad (-1.0)) &&
			(pilot_head_heading <= rad (1.0)) &&
			(pilot_head_pitch >= rad (-1.0)) &&
			(pilot_head_pitch <= rad (1.0))
		)
		{
			set_view_mode (VIEW_MODE_COCKPIT_PANEL_LEVEL_AHEAD);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_virtual_cockpit_crew_view (void)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_virtual_cockpit_hud_view (void)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_virtual_cockpit_periscope_view (void)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_virtual_cockpit_display_view (void)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_pilot_head_viewpoint (void)
{
	if (get_gunship_entity ())
	{
		switch (get_global_gunship_type ())
		{
			////////////////////////////////////////
			// JB 030313 Fly any aircraft
			case GUNSHIP_TYPE_VIPER:
			default:
			case GUNSHIP_TYPE_APACHE:
			////////////////////////////////////////
			{
				matrix3x3
					m;

				vec3d
					relative_position,
					world_relative_position;

				//
				// get aircraft position and attitude
				//

				get_local_entity_vec3d (get_gunship_entity (), VEC3D_TYPE_POSITION, &pilot_head_vp.position);

				get_local_entity_attitude_matrix (get_gunship_entity (), pilot_head_vp.attitude);
//VJ#
				relative_position.x = 0.0;
				relative_position.y = -1.2705;
				relative_position.z = 1.2325;

				multiply_matrix3x3_vec3d (&world_relative_position, pilot_head_vp.attitude, &relative_position);

				pilot_head_vp.position.x += world_relative_position.x;
				pilot_head_vp.position.y += world_relative_position.y;
				pilot_head_vp.position.z += world_relative_position.z;

				//
				// rotate view wrt pilot's head heading and pitch
				//

				get_arbitrary_rotation_matrix (m, &pilot_head_vp.yv, pilot_head_heading);

				multiply_matrix3x3_vec3d (&pilot_head_vp.xv, m, &pilot_head_vp.xv);

				multiply_matrix3x3_vec3d (&pilot_head_vp.zv, m, &pilot_head_vp.zv);

				get_arbitrary_rotation_matrix (m, &pilot_head_vp.xv, pilot_head_pitch);

				multiply_matrix3x3_vec3d (&pilot_head_vp.yv, m, &pilot_head_vp.yv);

				multiply_matrix3x3_vec3d (&pilot_head_vp.zv, m, &pilot_head_vp.zv);

				break;
			}
			////////////////////////////////////////
			case GUNSHIP_TYPE_HAVOC:
			////////////////////////////////////////
			{
				matrix3x3
					m;

				vec3d
					relative_position,
					world_relative_position;

				//
				// get aircraft position and attitude
				//

				get_local_entity_vec3d (get_gunship_entity (), VEC3D_TYPE_POSITION, &pilot_head_vp.position);

				get_local_entity_attitude_matrix (get_gunship_entity (), pilot_head_vp.attitude);

				relative_position.x = 0.0;
				relative_position.y = -0.86575;
				relative_position.z = 1.252;

				multiply_matrix3x3_vec3d (&world_relative_position, pilot_head_vp.attitude, &relative_position);

				pilot_head_vp.position.x += world_relative_position.x;
				pilot_head_vp.position.y += world_relative_position.y;
				pilot_head_vp.position.z += world_relative_position.z;

				//
				// rotate view wrt pilot's head heading and pitch
				//

				get_arbitrary_rotation_matrix (m, &pilot_head_vp.yv, pilot_head_heading);

				multiply_matrix3x3_vec3d (&pilot_head_vp.xv, m, &pilot_head_vp.xv);

				multiply_matrix3x3_vec3d (&pilot_head_vp.zv, m, &pilot_head_vp.zv);

				get_arbitrary_rotation_matrix (m, &pilot_head_vp.xv, pilot_head_pitch);

				multiply_matrix3x3_vec3d (&pilot_head_vp.yv, m, &pilot_head_vp.yv);

				multiply_matrix3x3_vec3d (&pilot_head_vp.zv, m, &pilot_head_vp.zv);

				break;
			}
			////////////////////////////////////////
			case GUNSHIP_TYPE_COMANCHE:
			////////////////////////////////////////
			{
//VJ#	this does the proper viepoint?
				get_comanche_crew_viewpoint ();

				break;
			}
			////////////////////////////////////////
			case GUNSHIP_TYPE_HOKUM:
			////////////////////////////////////////
			{
				get_hokum_crew_viewpoint ();

				break;
			}
			////Moje 030518 Start
			case GUNSHIP_TYPE_BLACKHAWK:
			////////////////////////////////////////
			{
				matrix3x3
					m;

				vec3d
					relative_position,
					world_relative_position;

				//
				// get aircraft position and attitude
				//

				get_local_entity_vec3d (get_gunship_entity (), VEC3D_TYPE_POSITION, &pilot_head_vp.position);

				get_local_entity_attitude_matrix (get_gunship_entity (), pilot_head_vp.attitude);

				relative_position.x = 0.0;
				relative_position.y = -1.2705;
				relative_position.z = 1.2325;

				multiply_matrix3x3_vec3d (&world_relative_position, pilot_head_vp.attitude, &relative_position);

				pilot_head_vp.position.x += world_relative_position.x;
				pilot_head_vp.position.y += world_relative_position.y;
				pilot_head_vp.position.z += world_relative_position.z;

				//
				// rotate view wrt pilot's head heading and pitch
				//

				get_arbitrary_rotation_matrix (m, &pilot_head_vp.yv, pilot_head_heading);

				multiply_matrix3x3_vec3d (&pilot_head_vp.xv, m, &pilot_head_vp.xv);

				multiply_matrix3x3_vec3d (&pilot_head_vp.zv, m, &pilot_head_vp.zv);

				get_arbitrary_rotation_matrix (m, &pilot_head_vp.xv, pilot_head_pitch);

				multiply_matrix3x3_vec3d (&pilot_head_vp.yv, m, &pilot_head_vp.yv);

				multiply_matrix3x3_vec3d (&pilot_head_vp.zv, m, &pilot_head_vp.zv);

				break;
			}

			////Moje 030518 End
			////Moje 030612 Start
			////////////////////////////////////////
			case GUNSHIP_TYPE_HIND:
			////////////////////////////////////////
			{
				matrix3x3
					m;

				vec3d
					relative_position,
					world_relative_position;

				//
				// get aircraft position and attitude
				//

				get_local_entity_vec3d (get_gunship_entity (), VEC3D_TYPE_POSITION, &pilot_head_vp.position);

				get_local_entity_attitude_matrix (get_gunship_entity (), pilot_head_vp.attitude);

				relative_position.x = 0.0;
				relative_position.y = -0.86575;
				relative_position.z = 1.252;

				multiply_matrix3x3_vec3d (&world_relative_position, pilot_head_vp.attitude, &relative_position);

				pilot_head_vp.position.x += world_relative_position.x;
				pilot_head_vp.position.y += world_relative_position.y;
				pilot_head_vp.position.z += world_relative_position.z;

				//
				// rotate view wrt pilot's head heading and pitch
				//

				get_arbitrary_rotation_matrix (m, &pilot_head_vp.yv, pilot_head_heading);

				multiply_matrix3x3_vec3d (&pilot_head_vp.xv, m, &pilot_head_vp.xv);

				multiply_matrix3x3_vec3d (&pilot_head_vp.zv, m, &pilot_head_vp.zv);

				get_arbitrary_rotation_matrix (m, &pilot_head_vp.xv, pilot_head_pitch);

				multiply_matrix3x3_vec3d (&pilot_head_vp.yv, m, &pilot_head_vp.yv);

				multiply_matrix3x3_vec3d (&pilot_head_vp.zv, m, &pilot_head_vp.zv);

				break;
			}
			////Moje 030612 End
			////Moje 030816 Start
			case GUNSHIP_TYPE_AH64A:
			////////////////////////////////////////
			{
				matrix3x3
					m;

				vec3d
					relative_position,
					world_relative_position;

				//
				// get aircraft position and attitude
				//

				get_local_entity_vec3d (get_gunship_entity (), VEC3D_TYPE_POSITION, &pilot_head_vp.position);

				get_local_entity_attitude_matrix (get_gunship_entity (), pilot_head_vp.attitude);

				relative_position.x = 0.0;
				relative_position.y = -1.2705;
				relative_position.z = 1.2325;

				multiply_matrix3x3_vec3d (&world_relative_position, pilot_head_vp.attitude, &relative_position);

				pilot_head_vp.position.x += world_relative_position.x;
				pilot_head_vp.position.y += world_relative_position.y;
				pilot_head_vp.position.z += world_relative_position.z;

				//
				// rotate view wrt pilot's head heading and pitch
				//

				get_arbitrary_rotation_matrix (m, &pilot_head_vp.yv, pilot_head_heading);

				multiply_matrix3x3_vec3d (&pilot_head_vp.xv, m, &pilot_head_vp.xv);

				multiply_matrix3x3_vec3d (&pilot_head_vp.zv, m, &pilot_head_vp.zv);

				get_arbitrary_rotation_matrix (m, &pilot_head_vp.xv, pilot_head_pitch);

				multiply_matrix3x3_vec3d (&pilot_head_vp.yv, m, &pilot_head_vp.yv);

				multiply_matrix3x3_vec3d (&pilot_head_vp.zv, m, &pilot_head_vp.zv);

				break;
			}
			////////////////////////////////////////
			case GUNSHIP_TYPE_KA50:
			////////////////////////////////////////
			{
				matrix3x3
					m;

				vec3d
					relative_position,
					world_relative_position;

				//
				// get aircraft position and attitude
				//

				get_local_entity_vec3d (get_gunship_entity (), VEC3D_TYPE_POSITION, &pilot_head_vp.position);

				get_local_entity_attitude_matrix (get_gunship_entity (), pilot_head_vp.attitude);

				relative_position.x = 0.0;
				relative_position.y = -0.86575;
				relative_position.z = 1.252;

				multiply_matrix3x3_vec3d (&world_relative_position, pilot_head_vp.attitude, &relative_position);

				pilot_head_vp.position.x += world_relative_position.x;
				pilot_head_vp.position.y += world_relative_position.y;
				pilot_head_vp.position.z += world_relative_position.z;

				//
				// rotate view wrt pilot's head heading and pitch
				//

				get_arbitrary_rotation_matrix (m, &pilot_head_vp.yv, pilot_head_heading);

				multiply_matrix3x3_vec3d (&pilot_head_vp.xv, m, &pilot_head_vp.xv);

				multiply_matrix3x3_vec3d (&pilot_head_vp.zv, m, &pilot_head_vp.zv);

				get_arbitrary_rotation_matrix (m, &pilot_head_vp.xv, pilot_head_pitch);

				multiply_matrix3x3_vec3d (&pilot_head_vp.yv, m, &pilot_head_vp.yv);

				multiply_matrix3x3_vec3d (&pilot_head_vp.zv, m, &pilot_head_vp.zv);

				break;
			}
			////Moje 030816 End
			case GUNSHIP_TYPE_KIOWA:
			////////////////////////////////////////
			{
//VJ#	this does the proper viepoint?
				get_kiowa_crew_viewpoint ();

				break;
			}
			////////////////////////////////////////
		}
	}
	else
	{
		pilot_head_vp.position.x = MID_MAP_X;
		pilot_head_vp.position.y = MID_MAP_Y;
		pilot_head_vp.position.z = MID_MAP_Z;

		get_identity_matrix3x3 (pilot_head_vp.attitude);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_pilot_head_heading_and_pitch_to_target (entity *target)
{
	float
		flat_range,
		heading,
		pitch;

	vec3d
		target_position,
		target_vector,
		offset_vector;

	ASSERT (target);

	pilot_head_heading = 0.0;

	pilot_head_pitch = 0.0;

	get_pilot_head_viewpoint ();

	if (!get_local_entity_int_value (target, INT_TYPE_IDENTIFY_WAYPOINT))
	{
		get_local_entity_target_point (target, &target_position);
	}
	else
	{
		//
		// assume that the target will only be a waypoint for padlock views
		//

		ASSERT (get_gunship_entity ());

		get_waypoint_display_position (get_gunship_entity (), target, &target_position);
	}

	target_vector.x = target_position.x - pilot_head_vp.position.x;
	target_vector.y = target_position.y - pilot_head_vp.position.y;
	target_vector.z = target_position.z - pilot_head_vp.position.z;

	multiply_transpose_matrix3x3_vec3d (&offset_vector, pilot_head_vp.attitude, &target_vector);

	heading = -atan2 (offset_vector.x, offset_vector.z);

	pilot_head_heading = bound (heading, get_rotate_right_limit (), get_rotate_left_limit ());

	flat_range = sqrt ((offset_vector.x * offset_vector.x) + (offset_vector.z * offset_vector.z));

	pitch = atan2 (offset_vector.y, flat_range);

	pilot_head_pitch = bound (pitch, get_rotate_down_limit (), get_rotate_up_limit ());
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_night_vision_mask (void)
{
	vertex
		quad[4];

	real_colour
		colour,
		specular;

	set_3d_active_environment (main_3d_env);

	if (begin_3d_scene ())
	{
		colour.red		= 255;
		colour.green	= 255;
		colour.blue		= 255;
		colour.alpha	= 192;

		specular.red	= 0;
		specular.green	= 0;
		specular.blue	= 0;
		specular.alpha	= 255;

		set_d3d_transparency_on ();

		set_d3d_zbuffer_comparison (FALSE);

		set_d3d_culling (FALSE);

		set_d3d_texture_wrapping (0, FALSE);

		set_d3d_texture_filtering (FALSE);

		set_d3d_flat_shaded_textured_renderstate (get_system_texture_ptr (TEXTURE_INDEX_HOKUM_COCKPIT_WSO_SCOPE_VIEW));

		////////////////////////////////////////
		//
		// top left
		//
		////////////////////////////////////////

		quad[0].i 				= full_screen_x_min;
		quad[0].j  				= full_screen_y_min;
		quad[0].z  				= 0.5;
		quad[0].q  				= 0.5;
		quad[0].u  				= 0.0;
		quad[0].v				= 0.0;

		quad[1].i  				= full_screen_x_mid;
		quad[1].j  				= full_screen_y_min;
		quad[1].z  				= 0.5;
		quad[1].q  				= 0.5;
		quad[1].u  				= 0.75; //1.0;
		quad[1].v  				= 0.0;

		quad[2].i				= full_screen_x_mid;
		quad[2].j  				= full_screen_y_mid;
		quad[2].z  				= 0.5;
		quad[2].q  				= 0.5;
		quad[2].u  				= 0.75; //1.0;
		quad[2].v  				= 1.0;

		quad[3].i  				= full_screen_x_min;
		quad[3].j  				= full_screen_y_mid;
		quad[3].z  				= 0.5;
		quad[3].q  				= 0.5;
		quad[3].u				= 0.0;
		quad[3].v				= 1.0;

		quad[0].next_vertex	= &quad[1];
		quad[1].next_vertex	= &quad[2];
		quad[2].next_vertex	= &quad[3];
		quad[3].next_vertex	= NULL;

		draw_wbuffered_flat_shaded_textured_polygon (quad, colour, specular);

		////////////////////////////////////////
		//
		// bottom left
		//
		////////////////////////////////////////

		quad[0].i 				= full_screen_x_min;
		quad[0].j  				= full_screen_y_mid;
		quad[0].z  				= 0.5;
		quad[0].q  				= 0.5;
		quad[0].u  				= 0.0;
		quad[0].v				= 1.0;

		quad[1].i  				= full_screen_x_mid;
		quad[1].j  				= full_screen_y_mid;
		quad[1].z  				= 0.5;
		quad[1].q  				= 0.5;
		quad[1].u  				= 0.75;
		quad[1].v  				= 1.0;

		quad[2].i				= full_screen_x_mid;
		quad[2].j  				= full_screen_y_max;
		quad[2].z  				= 0.5;
		quad[2].q  				= 0.5;
		quad[2].u  				= 0.75;
		quad[2].v  				= 0.0;

		quad[3].i  				= full_screen_x_min;
		quad[3].j  				= full_screen_y_max;
		quad[3].z  				= 0.5;
		quad[3].q  				= 0.5;
		quad[3].u				= 0.0;
		quad[3].v				= 0.0;

		quad[0].next_vertex	= &quad[1];
		quad[1].next_vertex	= &quad[2];
		quad[2].next_vertex	= &quad[3];
		quad[3].next_vertex	= NULL;

		draw_wbuffered_flat_shaded_textured_polygon (quad, colour, specular);

		////////////////////////////////////////
		//
		// top right
		//
		////////////////////////////////////////

		quad[0].i 				= full_screen_x_mid;
		quad[0].j  				= full_screen_y_min;
		quad[0].z  				= 0.5;
		quad[0].q  				= 0.5;
		quad[0].u  				= 0.75;
		quad[0].v				= 0.0;

		quad[1].i  				= full_screen_x_max;
		quad[1].j  				= full_screen_y_min;
		quad[1].z  				= 0.5;
		quad[1].q  				= 0.5;
		quad[1].u  				= 0.0;
		quad[1].v  				= 0.0;

		quad[2].i				= full_screen_x_max;
		quad[2].j  				= full_screen_y_mid;
		quad[2].z  				= 0.5;
		quad[2].q  				= 0.5;
		quad[2].u  				= 0.0;
		quad[2].v  				= 1.0;

		quad[3].i  				= full_screen_x_mid;
		quad[3].j  				= full_screen_y_mid;
		quad[3].z  				= 0.5;
		quad[3].q  				= 0.5;
		quad[3].u				= 0.75;
		quad[3].v				= 1.0;

		quad[0].next_vertex	= &quad[1];
		quad[1].next_vertex	= &quad[2];
		quad[2].next_vertex	= &quad[3];
		quad[3].next_vertex	= NULL;

		draw_wbuffered_flat_shaded_textured_polygon (quad, colour, specular);

		////////////////////////////////////////
		//
		// bottom right
		//
		////////////////////////////////////////

		quad[0].i 				= full_screen_x_mid;
		quad[0].j  				= full_screen_y_mid;
		quad[0].z  				= 0.5;
		quad[0].q  				= 0.5;
		quad[0].u  				= 0.75;
		quad[0].v				= 1.0;

		quad[1].i  				= full_screen_x_max;
		quad[1].j  				= full_screen_y_mid;
		quad[1].z  				= 0.5;
		quad[1].q  				= 0.5;
		quad[1].u  				= 0.0;
		quad[1].v  				= 1.0;

		quad[2].i				= full_screen_x_max;
		quad[2].j  				= full_screen_y_max;
		quad[2].z  				= 0.5;
		quad[2].q  				= 0.5;
		quad[2].u  				= 0.0;
		quad[2].v  				= 0.0;

		quad[3].i  				= full_screen_x_mid;
		quad[3].j  				= full_screen_y_max;
		quad[3].z  				= 0.5;
		quad[3].q  				= 0.5;
		quad[3].u				= 0.75;
		quad[3].v				= 0.0;

		quad[0].next_vertex	= &quad[1];
		quad[1].next_vertex	= &quad[2];
		quad[2].next_vertex	= &quad[3];
		quad[3].next_vertex	= NULL;

		draw_wbuffered_flat_shaded_textured_polygon (quad, colour, specular);

		////////////////////////////////////////

		set_d3d_transparency_off ();

		set_d3d_zbuffer_comparison (TRUE);

		set_d3d_culling (TRUE);

		end_3d_scene ();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_virtual_cockpit_3d_view (void)
{
	ASSERT (get_gunship_entity ());

	set_main_3d_full_screen_params (DISPLAY_3D_TINT_CLEAR, DISPLAY_3D_LIGHT_LEVEL_HIGH, DISPLAY_3D_NOISE_LEVEL_NONE);

	switch (get_global_gunship_type ())
	{
		////////////////////////////////////////
		case GUNSHIP_TYPE_COMANCHE:
		////////////////////////////////////////
		{
			pre_render_comanche_virtual_cockpit_displays ();

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_HOKUM:
		////////////////////////////////////////
		{
			pre_render_hokum_virtual_cockpit_displays ();

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_KIOWA:
		////////////////////////////////////////
		{
			pre_render_kiowa_virtual_cockpit_displays ();

			break;
		}
		////////////////////////////////////////
	}

	set_pilots_full_screen_params (night_vision_active());

	draw_main_3d_scene (&main_vp);

//	if (command_line_restricted_nvg_fov && night_vision_active() && !get_global_draw_cockpit_graphics ())
//		draw_night_vision_mask();

	switch (get_global_gunship_type ())
	{
		////////////////////////////////////////
		// JB 030313 Fly any aircraft
//		default:
		case GUNSHIP_TYPE_APACHE:
		////////////////////////////////////////
		{
			if (get_global_draw_cockpit_graphics ())
			{
				set_pilots_full_screen_params (FALSE);

#if 0  // the old experimental 3D cockpit by gotcha - not used anymore
				if (command_line_3d_cockpit)
				{

					draw_apache_external_virtual_cockpit_3d
					(
						VIRTUAL_COCKPIT_STOWED_WIPER |
						VIRTUAL_COCKPIT_MOVING_WIPER |
						VIRTUAL_COCKPIT_ADI |
						VIRTUAL_COCKPIT_COMPASS |
						VIRTUAL_COCKPIT_RAIN_EFFECT |
						VIRTUAL_COCKPIT_MAIN_ROTOR//,NULL
					);

					draw_apache_internal_virtual_cockpit_3d
					(
						VIRTUAL_COCKPIT_COCKPIT |
						VIRTUAL_COCKPIT_LHS_MFD_DISPLAY |
						VIRTUAL_COCKPIT_RHS_MFD_DISPLAY |
						VIRTUAL_COCKPIT_UPFRONT_DISPLAY |
						VIRTUAL_COCKPIT_INSTRUMENT_NEEDLES
					);
				}
				else
#endif
				{
					draw_apache_external_virtual_cockpit
					(
						VIRTUAL_COCKPIT_STOWED_WIPER |
						VIRTUAL_COCKPIT_MOVING_WIPER |
						VIRTUAL_COCKPIT_ADI |
						VIRTUAL_COCKPIT_COMPASS |
						VIRTUAL_COCKPIT_RAIN_EFFECT |
						VIRTUAL_COCKPIT_MAIN_ROTOR,
						NULL
					);

					if (get_local_entity_int_value (get_pilot_entity (), INT_TYPE_CREW_ROLE) == CREW_ROLE_PILOT)
						draw_apache_internal_virtual_cockpit
						(
							VIRTUAL_COCKPIT_COCKPIT |
							VIRTUAL_COCKPIT_UPFRONT_DISPLAY |
							VIRTUAL_COCKPIT_PILOT_LHS_MFD_DISPLAY |
							VIRTUAL_COCKPIT_PILOT_RHS_MFD_DISPLAY |
							VIRTUAL_COCKPIT_INSTRUMENT_NEEDLES
						);
					else
						draw_apache_internal_virtual_cockpit
						(
							VIRTUAL_COCKPIT_COCKPIT |
							VIRTUAL_COCKPIT_UPFRONT_DISPLAY |
							VIRTUAL_COCKPIT_CPG_LHS_MFD_DISPLAY |
							VIRTUAL_COCKPIT_CPG_RHS_MFD_DISPLAY |
							VIRTUAL_COCKPIT_ORT_DISPLAY
						);
				}
			}
			else
			{
				if(command_line_export_mfd)
				{
					draw_apache_mfd_on_texture(MFD_LOCATION_LHS);
					draw_apache_mfd_on_texture(MFD_LOCATION_RHS);
				}
				else
				{
					if (get_global_draw_overlaid_instruments ())
					{
						draw_overlaid_apache_mfd (100.0, 380.0, 192.0, MFD_LOCATION_LHS);
						draw_overlaid_apache_mfd (540.0, 380.0, 192.0, MFD_LOCATION_RHS);
					}
				}
			}

			draw_apache_hud ();

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_HAVOC:
		////////////////////////////////////////
		{
			if (get_global_draw_cockpit_graphics ())
			{
				set_pilots_full_screen_params (FALSE);
				draw_havoc_external_virtual_cockpit
				(
					VIRTUAL_COCKPIT_STOWED_WIPER |
					VIRTUAL_COCKPIT_MOVING_WIPER |
					VIRTUAL_COCKPIT_ADI |
					VIRTUAL_COCKPIT_HSI |
					VIRTUAL_COCKPIT_COMPASS |
					VIRTUAL_COCKPIT_RAIN_EFFECT |
					VIRTUAL_COCKPIT_MAIN_ROTOR,
					NULL
				);

				draw_havoc_internal_virtual_cockpit
				(
					VIRTUAL_COCKPIT_COCKPIT |
					VIRTUAL_COCKPIT_HUD_GLASS |
					VIRTUAL_COCKPIT_HUD_DISPLAY |
					VIRTUAL_COCKPIT_CRT_DISPLAY |
					VIRTUAL_COCKPIT_EKRAN_DISPLAY |
					VIRTUAL_COCKPIT_INSTRUMENT_NEEDLES
				);
			}
			else
			{
				draw_external_havoc_hud ();

				if(command_line_export_mfd)
				{
					draw_havoc_mfd_on_texture();
					if (get_global_draw_overlaid_instruments ())
					{
						draw_overlaid_threat_warning_display (int_full_screen_width - 64, int_full_screen_height - 84);
					}
				}
				else
				{
					if (get_global_draw_overlaid_instruments ())
					{
						draw_overlaid_havoc_mfd (100.0, 380.0, 192.0);
						draw_overlaid_threat_warning_display (int_full_screen_width - 64, int_full_screen_height - 84);
					}
				}
			}

			draw_havoc_hms ();

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_COMANCHE:
		////////////////////////////////////////
		{
			set_pilots_full_screen_params (FALSE);

			draw_comanche_virtual_cockpit ();

			if (!get_global_draw_cockpit_graphics ())
			{
				if(command_line_export_mfd)
				{
					draw_comanche_mfd();
				}
				else
				{
					if (get_global_draw_overlaid_instruments ())
					{
						draw_overlaid_comanche_mfd ();
					}
				}
			}

			draw_comanche_hud ();

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_HOKUM:
		////////////////////////////////////////
		{
			set_pilots_full_screen_params (FALSE);

			draw_hokum_virtual_cockpit ();

			if (!get_global_draw_cockpit_graphics ())
			{
				if(command_line_export_mfd)
				{
					draw_hokum_mfd();
				}
				else
				{
					if (get_global_draw_overlaid_instruments ())
					{
						draw_overlaid_hokum_mfd ();
					}
				}
			}

			draw_hokum_hms ();

			break;
		}
		////Moje 030518 Start
		case GUNSHIP_TYPE_BLACKHAWK:
		////////////////////////////////////////
		{
			if (get_global_draw_cockpit_graphics ())
			{
				set_pilots_full_screen_params (FALSE);
/* VJ 050114 doesn't work yet
				if (command_line_3d_cockpit)
				{
					draw_blackhawk_external_virtual_cockpit_3d
					(
						VIRTUAL_COCKPIT_STOWED_WIPER |
						VIRTUAL_COCKPIT_MOVING_WIPER |
						VIRTUAL_COCKPIT_ADI |
						VIRTUAL_COCKPIT_COMPASS |
						VIRTUAL_COCKPIT_RAIN_EFFECT |
						VIRTUAL_COCKPIT_MAIN_ROTOR
					);

					draw_blackhawk_internal_virtual_cockpit_3d
					(
						VIRTUAL_COCKPIT_COCKPIT |
						VIRTUAL_COCKPIT_LHS_MFD_DISPLAY |
						VIRTUAL_COCKPIT_RHS_MFD_DISPLAY |
						VIRTUAL_COCKPIT_UPFRONT_DISPLAY |
						VIRTUAL_COCKPIT_INSTRUMENT_NEEDLES
					);

				}
				else
				{
*/
					draw_blackhawk_external_virtual_cockpit
					(
						VIRTUAL_COCKPIT_STOWED_WIPER |
						VIRTUAL_COCKPIT_MOVING_WIPER |
						VIRTUAL_COCKPIT_ADI |
						VIRTUAL_COCKPIT_COMPASS |
						VIRTUAL_COCKPIT_RAIN_EFFECT |
						VIRTUAL_COCKPIT_MAIN_ROTOR,
						NULL
					);

					draw_blackhawk_internal_virtual_cockpit
					(
						VIRTUAL_COCKPIT_COCKPIT |
						VIRTUAL_COCKPIT_LHS_MFD_DISPLAY |
						VIRTUAL_COCKPIT_RHS_MFD_DISPLAY |
						VIRTUAL_COCKPIT_UPFRONT_DISPLAY |
						VIRTUAL_COCKPIT_INSTRUMENT_NEEDLES
					);
//				}

			}
			else
			{
				if(command_line_export_mfd)
				{
					draw_blackhawk_mfd_on_texture(MFD_LOCATION_LHS);
					draw_blackhawk_mfd_on_texture(MFD_LOCATION_RHS);
				}
				else
				{
					if (get_global_draw_overlaid_instruments ())
					{
						draw_overlaid_blackhawk_mfd (68.0, 412.0, 128.0, MFD_LOCATION_LHS);
						draw_overlaid_blackhawk_mfd (572.0, 412.0, 128.0, MFD_LOCATION_RHS);
					}
				}
			}

			draw_blackhawk_hud ();

			break;
		}

		////Moje 030518 End
		////Moje 030612 Start
		////////////////////////////////////////
		case GUNSHIP_TYPE_HIND:
		////////////////////////////////////////
		{
			if (get_global_draw_cockpit_graphics ())
			{
				set_pilots_full_screen_params (FALSE);

				if (custom_3d_models.arneh_mi24v_cockpit)
				{
					draw_hind_external_3d_cockpit(0, NULL);
					draw_hind_internal_3d_cockpit(0);
				}
				else
				{
					draw_hind_external_virtual_cockpit
					(
						VIRTUAL_COCKPIT_STOWED_WIPER |
						VIRTUAL_COCKPIT_MOVING_WIPER |
						VIRTUAL_COCKPIT_ADI |
						VIRTUAL_COCKPIT_HSI |
						VIRTUAL_COCKPIT_COMPASS |
						VIRTUAL_COCKPIT_RAIN_EFFECT |
						VIRTUAL_COCKPIT_MAIN_ROTOR,
						NULL
					);

					draw_hind_internal_virtual_cockpit
					(
						VIRTUAL_COCKPIT_COCKPIT |
						VIRTUAL_COCKPIT_HUD_GLASS |
						VIRTUAL_COCKPIT_HUD_DISPLAY |
						VIRTUAL_COCKPIT_CRT_DISPLAY |
						VIRTUAL_COCKPIT_EKRAN_DISPLAY |
						VIRTUAL_COCKPIT_INSTRUMENT_NEEDLES
					);
				}
			}
			else
			{
				draw_external_hind_hud ();

				if(command_line_export_mfd)
				{
					draw_hind_mfd_on_texture();
					if (get_global_draw_overlaid_instruments ())
					{
						draw_overlaid_hind_threat_warning_display (int_full_screen_width - 64, int_full_screen_height - 84);
					}
				}
				else
				{
					if (get_global_draw_overlaid_instruments ())
					{
						draw_overlaid_hind_mfd (68.0, 412.0, 128.0);
						draw_overlaid_hind_threat_warning_display (int_full_screen_width - 64, int_full_screen_height - 84);
					}
				}
			}

			draw_hind_hms ();

			break;
		}
		////Moje 030612 End
		////Moje 030816 Start
		case GUNSHIP_TYPE_AH64A:
		////////////////////////////////////////
		{
			if (get_global_draw_cockpit_graphics ())
			{
				set_pilots_full_screen_params (FALSE);

				draw_ah64a_external_virtual_cockpit
				(
					VIRTUAL_COCKPIT_STOWED_WIPER |
					VIRTUAL_COCKPIT_MOVING_WIPER |
					VIRTUAL_COCKPIT_ADI |
					VIRTUAL_COCKPIT_COMPASS |
					VIRTUAL_COCKPIT_RAIN_EFFECT |
					VIRTUAL_COCKPIT_MAIN_ROTOR,
					NULL
				);

				draw_ah64a_internal_virtual_cockpit
				(
					VIRTUAL_COCKPIT_COCKPIT |
					VIRTUAL_COCKPIT_LHS_MFD_DISPLAY |
					VIRTUAL_COCKPIT_RHS_MFD_DISPLAY |
					VIRTUAL_COCKPIT_UPFRONT_DISPLAY |
					VIRTUAL_COCKPIT_INSTRUMENT_NEEDLES
				);
			}
			else
			{
				if(command_line_export_mfd)
				{
					draw_ah64a_mfd_on_texture(MFD_LOCATION_LHS);
					draw_ah64a_mfd_on_texture(MFD_LOCATION_RHS);
				}
				else
				{
					if (get_global_draw_overlaid_instruments ())
					{
						draw_overlaid_ah64a_mfd (68.0, 412.0, 128.0, MFD_LOCATION_LHS);
						draw_overlaid_ah64a_mfd (572.0, 412.0, 128.0, MFD_LOCATION_RHS);
					}
				}
			}

			draw_ah64a_hud ();

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_KA50:
		////////////////////////////////////////
		{
			if (get_global_draw_cockpit_graphics ())
			{
				set_pilots_full_screen_params (FALSE);

				draw_ka50_external_virtual_cockpit
				(
					VIRTUAL_COCKPIT_STOWED_WIPER |
					VIRTUAL_COCKPIT_MOVING_WIPER |
					VIRTUAL_COCKPIT_ADI |
					VIRTUAL_COCKPIT_HSI |
					VIRTUAL_COCKPIT_COMPASS |
					VIRTUAL_COCKPIT_RAIN_EFFECT |
					VIRTUAL_COCKPIT_MAIN_ROTOR,
					NULL
				);

				draw_ka50_internal_virtual_cockpit
				(
					VIRTUAL_COCKPIT_COCKPIT |
					VIRTUAL_COCKPIT_HUD_GLASS |
					VIRTUAL_COCKPIT_HUD_DISPLAY |
					VIRTUAL_COCKPIT_CRT_DISPLAY |
					VIRTUAL_COCKPIT_EKRAN_DISPLAY |
					VIRTUAL_COCKPIT_INSTRUMENT_NEEDLES
				);
			}
			else
			{
				draw_external_ka50_hud ();

				if(command_line_export_mfd)
				{
					draw_ka50_mfd_on_texture();
					if (get_global_draw_overlaid_instruments ())
					{
						draw_overlaid_ka50_threat_warning_display (int_full_screen_width - 64, int_full_screen_height - 84);
					}
				}
				else
				{
					if (get_global_draw_overlaid_instruments ())
					{
						draw_overlaid_ka50_mfd (68.0, 412.0, 128.0);
						draw_overlaid_ka50_threat_warning_display (int_full_screen_width - 64, int_full_screen_height - 84);
					}
				}
			}

			draw_ka50_hms ();

			break;
		}
		////Moje 030816 End
		case GUNSHIP_TYPE_KIOWA:
		////////////////////////////////////////
		{
			set_pilots_full_screen_params (FALSE);

			draw_kiowa_virtual_cockpit ();

			if (!get_global_draw_cockpit_graphics ())
			{
				if(command_line_export_mfd)
				{
					draw_kiowa_mfd();
				}
				else
				{
					if (get_global_draw_overlaid_instruments ())
					{
						draw_overlaid_kiowa_mfd ();
					}
				}
			}

			draw_kiowa_hud ();

			break;
		}
		////////////////////////////////////////

		case GUNSHIP_TYPE_VIPER:
		////////////////////////////////////////
		// GCsDriver  08-12-2007
		default:
		////////////////////////////////////////
		{
			if (get_global_draw_cockpit_graphics ())
			{
				set_pilots_full_screen_params (FALSE);

				if (command_line_3d_cockpit)
				{

					draw_default_external_virtual_cockpit_3d
					(
						VIRTUAL_COCKPIT_STOWED_WIPER |
						VIRTUAL_COCKPIT_MOVING_WIPER |
						VIRTUAL_COCKPIT_ADI |
						VIRTUAL_COCKPIT_COMPASS |
						VIRTUAL_COCKPIT_RAIN_EFFECT |
						VIRTUAL_COCKPIT_MAIN_ROTOR//,NULL
					);

					draw_default_internal_virtual_cockpit_3d
					(
						VIRTUAL_COCKPIT_COCKPIT |
						VIRTUAL_COCKPIT_LHS_MFD_DISPLAY |
						VIRTUAL_COCKPIT_RHS_MFD_DISPLAY |
						VIRTUAL_COCKPIT_UPFRONT_DISPLAY |
						VIRTUAL_COCKPIT_INSTRUMENT_NEEDLES
					);
				}
				else
				{
					draw_default_external_virtual_cockpit
					(
						VIRTUAL_COCKPIT_STOWED_WIPER |
						VIRTUAL_COCKPIT_MOVING_WIPER |
						VIRTUAL_COCKPIT_ADI |
						VIRTUAL_COCKPIT_COMPASS |
						VIRTUAL_COCKPIT_RAIN_EFFECT |
						VIRTUAL_COCKPIT_MAIN_ROTOR,
						NULL
					);

					draw_default_internal_virtual_cockpit
					(
						VIRTUAL_COCKPIT_COCKPIT |
						VIRTUAL_COCKPIT_LHS_MFD_DISPLAY |
						VIRTUAL_COCKPIT_RHS_MFD_DISPLAY |
						VIRTUAL_COCKPIT_UPFRONT_DISPLAY |
						VIRTUAL_COCKPIT_INSTRUMENT_NEEDLES
					);
				}
			}
			else
			{
				if(command_line_export_mfd)
				{
					draw_default_mfd_on_texture(MFD_LOCATION_LHS);
					draw_default_mfd_on_texture(MFD_LOCATION_RHS);
				}
				else
				{
					if (get_global_draw_overlaid_instruments ())
					{
						draw_overlaid_default_mfd (100.0, 380.0, 192.0, MFD_LOCATION_LHS);
						draw_overlaid_default_mfd (540.0, 380.0, 192.0, MFD_LOCATION_RHS);
					}
				}
			}

			draw_default_hud ();

			break;
		}


	}

	if (command_line_restricted_nvg_fov && night_vision_system_active && get_global_draw_cockpit_graphics ())
		draw_night_vision_mask();

	// Jabberwock 031016 Inset view - cockpit
	if (external_view_inset_target)
	{
		entity
			*source,
			*target;

		viewpoint
			vp;

		source = get_external_view_entity ();

		target = get_inset ();

		ASSERT (source);

		if (target)
		{
			store_reverse_tactical_camera_values ();

			set_reverse_tactical_camera_values (source, target);

		   	get_local_entity_vec3d (get_camera_entity (), VEC3D_TYPE_POSITION, &vp.position);

   			get_local_entity_attitude_matrix (get_camera_entity (), vp.attitude);

			set_main_3d_inset_target_screen_params ();

			draw_main_3d_scene (&vp);

			restore_reverse_tactical_camera_values ();

			set_main_3d_full_screen_params (DISPLAY_3D_TINT_CLEAR, DISPLAY_3D_LIGHT_LEVEL_HIGH, DISPLAY_3D_NOISE_LEVEL_NONE);
		}
	}
	// Jabberwock 031016 ends


	//
	// restore virtual cockpit 3D instance
	//

	get_pilot_head_viewpoint ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_virtual_cockpit_3d_crew_view (void)
{
	vec3d
		position;

	ASSERT (get_gunship_entity ());

	ASSERT (get_comanche_hokum_gunship ());

	ASSERT (virtual_cockpit_inst3d);

	ASSERT (get_crew_camera_index (get_crew_role ()) != OBJECT_3D_INVALID_CAMERA_INDEX);

	ASSERT (get_num_virtual_cockpit_cameras (get_crew_role ()) > 0);

	ASSERT (get_current_virtual_cockpit_camera (get_crew_role ()) != INVALID_VIRTUAL_COCKPIT_CAMERA);

	////////////////////////////////////////
	//
	// check if the gunship has been destroyed before the pilot's ejected
	//

	if (get_local_entity_int_value (get_gunship_entity (), INT_TYPE_EJECTED))
	{
		if (!get_local_entity_int_value (get_gunship_entity (), INT_TYPE_ALIVE))
		{
			set_external_view_entity (get_gunship_entity ());

			notify_local_entity (ENTITY_MESSAGE_SET_CAMERA_ACTION, get_camera_entity (), NULL, CAMERA_ACTION_EJECT);
		}
	}

	//
	////////////////////////////////////////

	switch (get_global_gunship_type ())
	{
		////////////////////////////////////////
		case GUNSHIP_TYPE_COMANCHE:
		////////////////////////////////////////
		{
			pre_render_comanche_virtual_cockpit_displays ();

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_HOKUM:
		////////////////////////////////////////
		{
			pre_render_hokum_virtual_cockpit_displays ();

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_KIOWA:
		////////////////////////////////////////
		{
			pre_render_kiowa_virtual_cockpit_displays ();

			break;
		}
		////////////////////////////////////////
	}

	//
	// get camera viewpoint
	//

	virtual_cockpit_inst3d->vp.x = 0.0;
	virtual_cockpit_inst3d->vp.y = 0.0;
	virtual_cockpit_inst3d->vp.z = 0.0;

	get_local_entity_attitude_matrix (get_gunship_entity (), virtual_cockpit_inst3d->vp.attitude);

	get_object_3d_camera_position (virtual_cockpit_inst3d, get_crew_camera_index (get_crew_role ()), get_current_virtual_cockpit_camera (get_crew_role ()), 0.0, &main_vp);

	position.x = -main_vp.x;
	position.y = -main_vp.y;
	position.z = -main_vp.z;

	multiply_transpose_matrix3x3_vec3d (&virtual_cockpit_inst3d->vp.position, main_vp.attitude, &position);

	get_local_entity_vec3d (get_gunship_entity (), VEC3D_TYPE_POSITION, &position);

	main_vp.x += position.x;
	main_vp.y += position.y;
	main_vp.z += position.z;

	//
	// draw view
	//

	set_crew_view_full_screen_params ();

	draw_main_3d_scene (&main_vp);

	switch (get_global_gunship_type ())
	{
		////////////////////////////////////////
		case GUNSHIP_TYPE_COMANCHE:
		////////////////////////////////////////
		{
			draw_comanche_virtual_cockpit ();

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_HOKUM:
		////////////////////////////////////////
		{
			draw_hokum_virtual_cockpit ();

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_KIOWA:
		////////////////////////////////////////
		{
			draw_kiowa_virtual_cockpit ();

			break;
		}
		////////////////////////////////////////
	}

	//
	// restore virtual cockpit 3D instance
	//

	get_pilot_head_viewpoint ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_virtual_cockpit_3d_hud_view (void)
{
	ASSERT (get_gunship_entity ());

	switch (get_global_gunship_type ())
	{
		////////////////////////////////////////
		case GUNSHIP_TYPE_HAVOC:
		////////////////////////////////////////
		{
			set_pilots_full_screen_params (night_vision_system_active);

			draw_main_3d_scene (&main_vp);

			if (get_global_draw_cockpit_graphics ())
			{
				set_pilots_full_screen_params (FALSE);

				draw_havoc_external_virtual_cockpit
				(
					VIRTUAL_COCKPIT_STOWED_WIPER |
					VIRTUAL_COCKPIT_MOVING_WIPER |
					VIRTUAL_COCKPIT_RAIN_EFFECT |
					VIRTUAL_COCKPIT_MAIN_ROTOR,
					NULL
				);

				draw_havoc_internal_virtual_cockpit
				(
					VIRTUAL_COCKPIT_COCKPIT |
					VIRTUAL_COCKPIT_HUD_GLASS
				);
			}
			else
			{
				if (get_global_draw_overlaid_instruments ())
				{
					draw_overlaid_havoc_mfd (68.0, 412.0, 128.0);

					draw_overlaid_threat_warning_display (int_full_screen_width - 64, int_full_screen_height - 84);
				}
			}

			draw_external_havoc_hud ();

			draw_havoc_hms ();

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_HOKUM:
		////////////////////////////////////////
		{
			vec3d
				position;

			ASSERT (virtual_cockpit_inst3d);

			pre_render_hokum_virtual_cockpit_displays ();

			//
			// get camera viewpoint
			//

			virtual_cockpit_inst3d->vp.x = 0.0;
			virtual_cockpit_inst3d->vp.y = 0.0;
			virtual_cockpit_inst3d->vp.z = 0.0;

			get_local_entity_attitude_matrix (get_gunship_entity (), virtual_cockpit_inst3d->vp.attitude);

			get_object_3d_camera_position (virtual_cockpit_inst3d, OBJECT_3D_CAMERA_VIEW_STATIC_HUD, 0, 0.0, &main_vp);

			position.x = -main_vp.x;
			position.y = -main_vp.y;
			position.z = -main_vp.z;

			multiply_transpose_matrix3x3_vec3d (&virtual_cockpit_inst3d->vp.position, main_vp.attitude, &position);

			get_local_entity_vec3d (get_gunship_entity (), VEC3D_TYPE_POSITION, &position);

			main_vp.x += position.x;
			main_vp.y += position.y;
			main_vp.z += position.z;

			//
			// draw view
			//

			set_pilots_full_screen_params (night_vision_system_active);

			draw_main_3d_scene (&main_vp);

			set_pilots_full_screen_params (FALSE);

			draw_hokum_virtual_cockpit ();

			draw_hokum_hms ();

			break;
		}
		////moje 030615 think I missed out a section here. This code isn't in the 030615 exe
		////////////////////////////////////////
		case GUNSHIP_TYPE_HIND:
		////////////////////////////////////////
		{
			set_pilots_full_screen_params (night_vision_system_active);

			draw_main_3d_scene (&main_vp);

			if (get_global_draw_cockpit_graphics ())
			{
				set_pilots_full_screen_params (FALSE);

				if (custom_3d_models.arneh_mi24v_cockpit)
				{
					draw_hind_external_3d_cockpit(0, NULL);
					draw_hind_internal_3d_cockpit(0);
				}
				else
				{
					draw_hind_external_virtual_cockpit
					(
						VIRTUAL_COCKPIT_STOWED_WIPER |
						VIRTUAL_COCKPIT_MOVING_WIPER |
						VIRTUAL_COCKPIT_RAIN_EFFECT |
						VIRTUAL_COCKPIT_MAIN_ROTOR,
						NULL
					);

					draw_hind_internal_virtual_cockpit
					(
						VIRTUAL_COCKPIT_COCKPIT |
						VIRTUAL_COCKPIT_HUD_GLASS
					);
				}
			}
			else
			{
				if (get_global_draw_overlaid_instruments ())
				{
					draw_overlaid_hind_mfd (68.0, 412.0, 128.0);

					draw_overlaid_hind_threat_warning_display (int_full_screen_width - 64, int_full_screen_height - 84);
				}
			}

			draw_external_hind_hud ();

			draw_hind_hms ();

			break;
		}
		////Moje 030615 end
		////moje 030816
		////////////////////////////////////////
		case GUNSHIP_TYPE_KA50:
		////////////////////////////////////////
		{
			set_pilots_full_screen_params (night_vision_system_active);

			draw_main_3d_scene (&main_vp);

			if (get_global_draw_cockpit_graphics ())
			{
				set_pilots_full_screen_params (FALSE);

				draw_ka50_external_virtual_cockpit
				(
					VIRTUAL_COCKPIT_STOWED_WIPER |
					VIRTUAL_COCKPIT_MOVING_WIPER |
					VIRTUAL_COCKPIT_RAIN_EFFECT |
					VIRTUAL_COCKPIT_MAIN_ROTOR,
					NULL
				);

				draw_ka50_internal_virtual_cockpit
				(
					VIRTUAL_COCKPIT_COCKPIT |
					VIRTUAL_COCKPIT_HUD_GLASS
				);
			}
			else
			{
				if (get_global_draw_overlaid_instruments ())
				{
					draw_overlaid_ka50_mfd (68.0, 412.0, 128.0);

					draw_overlaid_ka50_threat_warning_display (int_full_screen_width - 64, int_full_screen_height - 84);
				}
			}

			draw_external_ka50_hud ();

			draw_ka50_hms ();

			break;
		}
		////Moje 030816 end
	}

	//
	// restore virtual cockpit 3D instance
	//

	get_pilot_head_viewpoint ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_virtual_cockpit_3d_periscope_view (void)
{
	int
		x_excess = ((full_screen_x_max - full_screen_x_min) - (full_screen_y_max - full_screen_y_min)) / 2,
		x_min = full_screen_x_min + x_excess,
		x_max = full_screen_x_max - x_excess;


	ASSERT (get_gunship_entity ());

	switch (get_global_gunship_type())
	{
	case  GUNSHIP_TYPE_APACHE:
		draw_apache_virtual_cockpit_ort_view(x_min, x_max - x_excess);
		draw_virtual_cockpit_periscope_mask (x_min, x_max, TRUE);
		draw_apache_virtual_cockpit_ort_symbology();
		break;
	case GUNSHIP_TYPE_HOKUM:
		draw_hokum_virtual_cockpit_periscope_view ();
		draw_virtual_cockpit_periscope_mask (full_screen_x_min, full_screen_x_max, FALSE);
		draw_hokum_virtual_cockpit_periscope_symbology ();
		break;
	case GUNSHIP_TYPE_HIND:
		draw_hind_virtual_cockpit_ort_view(x_min, x_max - x_excess);
		draw_virtual_cockpit_periscope_mask (x_min, x_max, TRUE);
		draw_hind_virtual_cockpit_ort_symbology();
		break;
	default:
		ASSERT(FALSE);
	}
	//
	// restore virtual cockpit 3D instance
	//

	get_pilot_head_viewpoint ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_virtual_cockpit_3d_display_view (void)
{
	//VJ# THIS CODE IS ONLY REACHED WHEN CLOSEUP F3 or F4!!!!!!!
	//

	switch (get_global_gunship_type ())
	{
		////////////////////////////////////////
		// JB 030313 Fly any aircraft
//		default:
		case GUNSHIP_TYPE_APACHE:
		////////////////////////////////////////
		{
			set_pilots_full_screen_params (FALSE);

			if (get_local_entity_int_value (get_pilot_entity (), INT_TYPE_CREW_ROLE) == CREW_ROLE_PILOT)
				draw_apache_internal_virtual_cockpit
				(
					VIRTUAL_COCKPIT_COCKPIT |
					VIRTUAL_COCKPIT_UPFRONT_DISPLAY |
					VIRTUAL_COCKPIT_PILOT_LHS_MFD_DISPLAY |
					VIRTUAL_COCKPIT_PILOT_RHS_MFD_DISPLAY |
					VIRTUAL_COCKPIT_INSTRUMENT_NEEDLES
				);
			else
				draw_apache_internal_virtual_cockpit
				(
					VIRTUAL_COCKPIT_COCKPIT |
					VIRTUAL_COCKPIT_UPFRONT_DISPLAY |
					VIRTUAL_COCKPIT_CPG_LHS_MFD_DISPLAY |
					VIRTUAL_COCKPIT_CPG_RHS_MFD_DISPLAY |
					VIRTUAL_COCKPIT_ORT_DISPLAY
				);

#if 0
			draw_apache_internal_virtual_cockpit
			(
				VIRTUAL_COCKPIT_DISPLAY_VIEW |
				VIRTUAL_COCKPIT_COCKPIT |
				VIRTUAL_COCKPIT_LHS_MFD_DISPLAY |
				VIRTUAL_COCKPIT_RHS_MFD_DISPLAY
			);
#endif
			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_HAVOC:
		////////////////////////////////////////
		{
			set_pilots_full_screen_params (FALSE);

			draw_havoc_internal_virtual_cockpit
			(
				VIRTUAL_COCKPIT_COCKPIT |
				VIRTUAL_COCKPIT_CRT_DISPLAY |
				VIRTUAL_COCKPIT_EKRAN_DISPLAY
			);

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_COMANCHE:
		////////////////////////////////////////
		{
			pre_render_comanche_virtual_cockpit_displays ();

			set_pilots_full_screen_params (FALSE);
//VJ#
			get_comanche_display_viewpoint (get_view_mode ());

			draw_comanche_virtual_cockpit ();

			draw_comanche_full_screen_display ();

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_HOKUM:
		////////////////////////////////////////
		{
			pre_render_hokum_virtual_cockpit_displays ();

			set_pilots_full_screen_params (FALSE);

			get_hokum_display_viewpoint (get_view_mode ());

			draw_hokum_virtual_cockpit ();

			draw_hokum_full_screen_display ();

			break;
		}
		////Moje 030518 Start
		case GUNSHIP_TYPE_BLACKHAWK:
		////////////////////////////////////////
		{
			set_pilots_full_screen_params (FALSE);

			draw_blackhawk_internal_virtual_cockpit
			(
				VIRTUAL_COCKPIT_DISPLAY_VIEW |
				VIRTUAL_COCKPIT_COCKPIT |
				VIRTUAL_COCKPIT_LHS_MFD_DISPLAY |
				VIRTUAL_COCKPIT_RHS_MFD_DISPLAY
			);

			break;
		}
		////Moje 030518 End
		////Moje 030612 Start
		////////////////////////////////////////
		case GUNSHIP_TYPE_HIND:
		////////////////////////////////////////
		{
			set_pilots_full_screen_params (FALSE);

			if (custom_3d_models.arneh_mi24v_cockpit)
				draw_hind_internal_3d_cockpit(0);
			else
				draw_hind_internal_virtual_cockpit
				(
					VIRTUAL_COCKPIT_COCKPIT |
					VIRTUAL_COCKPIT_CRT_DISPLAY |
					VIRTUAL_COCKPIT_EKRAN_DISPLAY
				);

			break;
		}
		////Moje 030612 End
		////Moje 030816 Start
		case GUNSHIP_TYPE_AH64A:
		////////////////////////////////////////
		{
			set_pilots_full_screen_params (FALSE);

			draw_ah64a_internal_virtual_cockpit
			(
				VIRTUAL_COCKPIT_DISPLAY_VIEW |
				VIRTUAL_COCKPIT_COCKPIT |
				VIRTUAL_COCKPIT_LHS_MFD_DISPLAY |
				VIRTUAL_COCKPIT_RHS_MFD_DISPLAY
			);

			break;
		}
		////////////////////////////////////////
		case GUNSHIP_TYPE_KA50:
		////////////////////////////////////////
		{
			set_pilots_full_screen_params (FALSE);

			draw_ka50_internal_virtual_cockpit
			(
				VIRTUAL_COCKPIT_COCKPIT |
				VIRTUAL_COCKPIT_CRT_DISPLAY |
				VIRTUAL_COCKPIT_EKRAN_DISPLAY
			);

			break;
		}
		////Moje 030816 End
		////////////////////////////////////////
		case GUNSHIP_TYPE_KIOWA:
		////////////////////////////////////////
		{
			pre_render_kiowa_virtual_cockpit_displays ();

			set_pilots_full_screen_params (FALSE);
//VJ#
			get_kiowa_display_viewpoint (get_view_mode ());

			draw_kiowa_virtual_cockpit ();

			draw_kiowa_full_screen_display ();

			break;
		}
		////////////////////////////////////////

		case GUNSHIP_TYPE_VIPER:
		////////////////////////////////////////
		// GCsDriver  08-12-2007
		default:
		////////////////////////////////////////
		{
			set_pilots_full_screen_params (FALSE);

			draw_default_internal_virtual_cockpit
			(
				VIRTUAL_COCKPIT_DISPLAY_VIEW |
				VIRTUAL_COCKPIT_COCKPIT |
				VIRTUAL_COCKPIT_LHS_MFD_DISPLAY |
				VIRTUAL_COCKPIT_RHS_MFD_DISPLAY
			);

			break;
		}

	}

	//
	// restore virtual cockpit 3D instance
	//

	get_pilot_head_viewpoint ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void store_pilot_seat_values (void)
{
	#if DEBUG_MODULE_SEAT_SWITCHING

	debug_filtered_log ("store_pilot_seat_values");

	#endif

	stored_pilot_head_heading = pilot_head_heading;
	stored_pilot_head_pitch = pilot_head_pitch;

	switch (get_view_mode ())
	{
		case VIEW_MODE_VIRTUAL_COCKPIT:
		case VIEW_MODE_VIRTUAL_COCKPIT_PADLOCK:
		case VIEW_MODE_VIRTUAL_COCKPIT_TRACK_TARGET:
		case VIEW_MODE_VIRTUAL_COCKPIT_CREW:
		case VIEW_MODE_VIRTUAL_COCKPIT_HUD:
		case VIEW_MODE_VIRTUAL_COCKPIT_PILOT_LHS_DISPLAY:
		case VIEW_MODE_VIRTUAL_COCKPIT_PILOT_RHS_DISPLAY:
		{
			stored_pilot_view_mode = get_view_mode ();

			break;
		}
		default:
		{
			stored_pilot_view_mode = VIEW_MODE_VIRTUAL_COCKPIT;

			break;
		}
	}

	stored_pilot_padlock_mode = padlock_mode;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void restore_pilot_seat_values (void)
{
	#if DEBUG_MODULE_SEAT_SWITCHING

	debug_filtered_log ("restore_pilot_seat_values");

	#endif

	pilot_head_heading = stored_pilot_head_heading;
	pilot_head_pitch = stored_pilot_head_pitch;

	if (stored_pilot_view_mode == VIEW_MODE_VIRTUAL_COCKPIT_PADLOCK)
	{
		//
		// clear co-pilot padlock mode (if any) and set default mode (in case padlock not available)
		//

		set_view_mode (VIEW_MODE_VIRTUAL_COCKPIT);

		select_padlock_view_event (stored_pilot_padlock_mode);
	}
	else if (!set_view_mode (stored_pilot_view_mode))
	{
		set_view_mode (VIEW_MODE_VIRTUAL_COCKPIT);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void store_co_pilot_seat_values (void)
{
	#if DEBUG_MODULE_SEAT_SWITCHING

	debug_filtered_log ("store_co_pilot_seat_values");

	#endif

	stored_co_pilot_head_heading = pilot_head_heading;
	stored_co_pilot_head_pitch = pilot_head_pitch;

	switch (get_view_mode ())
	{
		case VIEW_MODE_VIRTUAL_COCKPIT:
		case VIEW_MODE_VIRTUAL_COCKPIT_PADLOCK:
		case VIEW_MODE_VIRTUAL_COCKPIT_TRACK_TARGET:
		case VIEW_MODE_VIRTUAL_COCKPIT_CREW:
		case VIEW_MODE_VIRTUAL_COCKPIT_PERISCOPE:
		case VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_LHS_DISPLAY:
		case VIEW_MODE_VIRTUAL_COCKPIT_CO_PILOT_RHS_DISPLAY:
		{
			stored_co_pilot_view_mode = get_view_mode ();

			break;
		}
		default:
		{
			stored_co_pilot_view_mode = VIEW_MODE_VIRTUAL_COCKPIT;

			break;
		}
	}

	stored_co_pilot_padlock_mode = padlock_mode;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void restore_co_pilot_seat_values (void)
{
	#if DEBUG_MODULE_SEAT_SWITCHING

	debug_filtered_log ("restore_co_pilot_seat_values");

	#endif

	pilot_head_heading = stored_co_pilot_head_heading;
	pilot_head_pitch = stored_co_pilot_head_pitch;

	if (stored_co_pilot_view_mode == VIEW_MODE_VIRTUAL_COCKPIT_PADLOCK)
	{
		//
		// clear pilot padlock mode (if any) and set default mode (in case padlock not available)
		//

		set_view_mode (VIEW_MODE_VIRTUAL_COCKPIT);

		select_padlock_view_event (stored_co_pilot_padlock_mode);
	}
	else if (!set_view_mode (stored_co_pilot_view_mode))
	{
		set_view_mode (VIEW_MODE_VIRTUAL_COCKPIT);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void switch_seat_position (void)
{
	entity
		*en;

	ASSERT (get_gunship_entity ());

	ASSERT (get_comanche_hokum_gunship ());

	if (get_time_acceleration () == 0)
	{
		return;
	}

	en = get_pilot_entity ();

	ASSERT (en);

	if (get_local_entity_int_value (en, INT_TYPE_CREW_ROLE) == CREW_ROLE_PILOT)
	{
		////////////////////////////////////////
		//
		// PILOT ---> CO-PILOT
		//
		////////////////////////////////////////

		set_local_entity_int_value (en, INT_TYPE_CREW_ROLE, CREW_ROLE_CO_PILOT);

		store_pilot_seat_values ();

		restore_co_pilot_seat_values ();

		switch (wide_cockpit_nr)
		{
		case WIDEVIEW_COMANCHE_PILOT:
		case WIDEVIEW_HOKUM_PILOT:
		case WIDEVIEW_APACHE_PILOT:
		case WIDEVIEW_HIND_PILOT:
		case WIDEVIEW_KIOWA_PILOT:
			wide_cockpit_nr++;  // swtiches to co-pilot
			break;
		default:
			break;
		}

		// start periscope check by GCsDriver  08-12-2007
	  	// as copilot is no longer periscopes default position it can already be active
		if(command_line_pilot_as_periscope_default){
	  	if (target_acquisition_system == TARGET_ACQUISITION_SYSTEM_PERISCOPE)
	  	{
			set_view_mode (VIEW_MODE_VIRTUAL_COCKPIT_PERISCOPE);
		}
		}
		// end periscope check by GCsDriver  08-12-2007

	}
	else
	{
		////////////////////////////////////////
		//
		// CO-PILOT ---> PILOT
		//
		////////////////////////////////////////

		set_local_entity_int_value (en, INT_TYPE_CREW_ROLE, CREW_ROLE_PILOT);

		store_co_pilot_seat_values ();

		restore_pilot_seat_values ();

		switch (wide_cockpit_nr)
		{
		case WIDEVIEW_COMANCHE_COPILOT:
		case WIDEVIEW_HOKUM_COPILOT:
		case WIDEVIEW_APACHE_COPILOT:
		case WIDEVIEW_HIND_COPILOT:
		case WIDEVIEW_KIOWA_COPILOT:
			wide_cockpit_nr--;  // swtiches to pilot
			break;
		default:
			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_pilot_seat_position (void)
{
	ASSERT (get_gunship_entity ());

	ASSERT (get_comanche_hokum_gunship ());

	ASSERT (get_pilot_entity ());

	if (get_time_acceleration () == 0)
	{
		return;
	}

	if (get_crew_role () == CREW_ROLE_PILOT)
	{
		if (!in_cockpit)
		{
			restore_pilot_seat_values ();
		}
	}
	else
	{
		switch_seat_position ();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_co_pilot_seat_position (void)
{
	ASSERT (get_gunship_entity ());

	ASSERT (get_comanche_hokum_gunship ());

	ASSERT (get_pilot_entity ());

	if (get_time_acceleration () == 0)
	{
		return;
	}

	if (get_crew_role () == CREW_ROLE_CO_PILOT)
	{
		if (!in_cockpit)
		{
			restore_co_pilot_seat_values ();
		}
	}
	else
	{
		switch_seat_position ();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void leave_seat_position (view_modes new_view_mode, view_modes old_view_mode)
{
	if (!in_cockpit_flags[new_view_mode] && in_cockpit_flags[old_view_mode])
	{
		if (get_gunship_entity ())
		{
			if (get_comanche_hokum_gunship ())
			{
				if (get_pilot_entity ())
				{
					if (get_crew_role () == CREW_ROLE_PILOT)
					{
						store_pilot_seat_values ();
					}
					else
					{
						store_co_pilot_seat_values ();
					}
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// PADLOCK VIEWS
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

padlock_modes get_padlock_mode (void)
{
	return (padlock_mode);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// invoked via set_view_mode ()
//

void leave_padlock_view (void)
{
	if (get_gunship_entity ())
	{
		unlink_local_entity_children (get_gunship_entity (), LIST_TYPE_PADLOCK);
	}

	padlock_mode = PADLOCK_MODE_NONE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void display_padlock_message (padlock_modes mode)
{
	char
		s[200];

	switch (mode)
	{
		////////////////////////////////////////
		case PADLOCK_MODE_NONE:
		////////////////////////////////////////
		{
			debug_fatal ("Invalid padlock mode = PADLOCK_MODE_NONE");

			break;
		}
		////////////////////////////////////////
		case PADLOCK_MODE_WINGMAN:
		////////////////////////////////////////
		{
			char
				pilot_name[200];

			entity
				*wingman,
				*group,
				*pilot;

			wingman = get_local_entity_first_child (get_gunship_entity (), LIST_TYPE_PADLOCK);

			ASSERT (wingman);

			group = get_local_entity_parent (wingman, LIST_TYPE_MEMBER);

			if (group)
			{
				sprintf (s, "%s %s 1-%d", get_trans ("Padlock wingman"), get_local_entity_string (group, STRING_TYPE_GROUP_CALLSIGN), get_local_entity_int_value (wingman, INT_TYPE_GROUP_MEMBER_ID));

				if (get_local_entity_int_value (wingman, INT_TYPE_PLAYER) != ENTITY_PLAYER_AI)
				{
					pilot = get_local_entity_first_child (wingman, LIST_TYPE_AIRCREW);

					while (pilot)
					{
						sprintf (pilot_name, " (%s)", get_local_entity_string (pilot, STRING_TYPE_PILOTS_NAME));

						strcat (s, pilot_name);

						pilot = get_local_entity_child_succ (pilot, LIST_TYPE_AIRCREW);
					}
				}

				set_status_message (s, STATUS_MESSAGE_TYPE_NONE);
			}
			else
			{
				set_status_message (get_trans ("Padlock wingman"), STATUS_MESSAGE_TYPE_NONE);
			}

			break;
		}
		////////////////////////////////////////
		case PADLOCK_MODE_AIR_THREAT:
		////////////////////////////////////////
		{
			entity
				*air_threat;

			air_threat = get_local_entity_first_child (get_gunship_entity (), LIST_TYPE_PADLOCK);

			ASSERT (air_threat);

			sprintf (s, "%s %s", get_trans ("Padlock air threat"), get_local_entity_string (air_threat, STRING_TYPE_FULL_NAME));

			set_status_message (s, STATUS_MESSAGE_TYPE_NONE);

			break;
		}
		////////////////////////////////////////
		case PADLOCK_MODE_GROUND_THREAT:
		////////////////////////////////////////
		{
			entity
				*ground_threat;

			ground_threat = get_local_entity_first_child (get_gunship_entity (), LIST_TYPE_PADLOCK);

			ASSERT (ground_threat);

			sprintf (s, "%s %s", get_trans ("Padlock ground threat"), get_local_entity_string (ground_threat, STRING_TYPE_FULL_NAME));

			set_status_message (s, STATUS_MESSAGE_TYPE_NONE);

			break;
		}
		////////////////////////////////////////
		case PADLOCK_MODE_MISSILE_THREAT:
		////////////////////////////////////////
		{
			entity
				*incoming;

			incoming = get_local_entity_first_child (get_gunship_entity (), LIST_TYPE_PADLOCK);

			ASSERT (incoming);

			sprintf (s, "%s %s", get_trans ("Padlock incoming"), get_local_entity_string (incoming, STRING_TYPE_FULL_NAME));

			set_status_message (s, STATUS_MESSAGE_TYPE_NONE);

			break;
		}
		////////////////////////////////////////
		case PADLOCK_MODE_WAYPOINT:
		////////////////////////////////////////
		{
			entity
				*waypoint;

			waypoint = get_local_entity_current_waypoint (get_gunship_entity ());

			ASSERT (waypoint);

			sprintf (s, "%s '%c'", get_trans ("Padlock waypoint"), get_local_entity_char_value (waypoint, CHAR_TYPE_TAG));

			set_status_message (s, STATUS_MESSAGE_TYPE_NONE);

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			debug_fatal ("Invalid padlock mode = %d", mode);

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int get_valid_wingman (entity *wingman)
{
	ASSERT (wingman);

	if (get_local_entity_int_value (wingman, INT_TYPE_VIEWABLE))
	{
		if (wingman != get_gunship_entity ())
		{
			return (TRUE);
		}
	}

	return (FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static entity *get_first_wingman (void)
{
	entity
		*source,
		*group,
		*wingman;

	source = get_gunship_entity ();

	ASSERT (source);

	group = get_local_entity_parent (source, LIST_TYPE_MEMBER);

	if (group)
	{
		wingman = get_local_entity_first_child (group, LIST_TYPE_MEMBER);

		while (wingman)
		{
			if (get_valid_wingman (wingman))
			{
				break;
			}

			wingman = get_local_entity_child_succ (wingman, LIST_TYPE_MEMBER);
		}
	}
	else
	{
		wingman = NULL;
	}

	return (wingman);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static entity *get_next_wingman (void)
{
	entity
		*source,
		*group,
		*wingman;

	source = get_gunship_entity ();

	ASSERT (source);

	wingman = get_local_entity_first_child (source, LIST_TYPE_PADLOCK);

	//
	// check wingman is still a wingman
	//

	if (wingman)
	{
		if (get_local_entity_parent (wingman, LIST_TYPE_MEMBER) != get_local_entity_parent (source, LIST_TYPE_MEMBER))
		{
			wingman = NULL;
		}
	}

	//
	// find next wingman in list
	//

	if (wingman)
	{
		wingman = get_local_entity_child_succ (wingman, LIST_TYPE_MEMBER);

		while (wingman)
		{
			if (get_valid_wingman (wingman))
			{
				break;
			}

			wingman = get_local_entity_child_succ (wingman, LIST_TYPE_MEMBER);
		}
	}

	//
	// find first wingman in list
	//

	if (!wingman)
	{
		group = get_local_entity_parent (source, LIST_TYPE_MEMBER);

		if (group)
		{
			wingman = get_local_entity_first_child (group, LIST_TYPE_MEMBER);

			while (wingman)
			{
				if (get_valid_wingman (wingman))
				{
					break;
				}

				wingman = get_local_entity_child_succ (wingman, LIST_TYPE_MEMBER);
			}
		}
	}

	return (wingman);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int get_valid_air_threat (entity *threat, entity_sides source_side)
{
	ASSERT (threat);

	if (get_local_entity_int_value (threat, INT_TYPE_IDENTIFY_AIRCRAFT))
	{
		if (get_local_entity_int_value (threat, INT_TYPE_VIEWABLE))
		{
			if (source_side != get_local_entity_int_value (threat, INT_TYPE_SIDE))
			{
				return (TRUE);
			}
		}
	}

	return (FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static entity *get_first_air_threat (void)
{
	entity
		*source,
		*threat,
		*closest_threat;

	entity_sides
		source_side;

	float
		range,
		closest_threat_range;

	vec3d
		*source_position,
		*threat_position;

	source = get_gunship_entity ();

	ASSERT (source);

	source_side = (entity_sides) get_local_entity_int_value (source, INT_TYPE_SIDE);

	source_position = get_local_entity_vec3d_ptr (source, VEC3D_TYPE_POSITION);

	closest_threat = NULL;

	closest_threat_range = FLT_MAX;

	threat = get_local_entity_first_child (source, LIST_TYPE_TARGET);

	while (threat)
	{
		if (get_valid_air_threat (threat, source_side))
		{
			threat_position = get_local_entity_vec3d_ptr (threat, VEC3D_TYPE_POSITION);

			range = get_sqr_3d_range (source_position, threat_position);

			if (range < closest_threat_range)
			{
				closest_threat = threat;

				closest_threat_range = range;
			}
		}

		threat = get_local_entity_child_succ (threat, LIST_TYPE_TARGET);
	}

	return (closest_threat);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static entity *get_next_air_threat (void)
{
	entity
		*source,
		*threat;

	entity_sides
		source_side;

	source = get_gunship_entity ();

	ASSERT (source);

	source_side = (entity_sides) get_local_entity_int_value (source, INT_TYPE_SIDE);

	threat = get_local_entity_first_child (source, LIST_TYPE_PADLOCK);

	//
	// check threat is still a threat
	//

	if (threat)
	{
		if (get_local_entity_parent (threat, LIST_TYPE_TARGET) != source)
		{
			threat = NULL;
		}
	}

	//
	// find next threat in list
	//

	if (threat)
	{
		threat = get_local_entity_child_succ (threat, LIST_TYPE_TARGET);

		while (threat)
		{
			if (get_valid_air_threat (threat, source_side))
			{
				break;
			}

			threat = get_local_entity_child_succ (threat, LIST_TYPE_TARGET);
		}
	}

	//
	// find first threat in list
	//

	if (!threat)
	{
		threat = get_local_entity_first_child (source, LIST_TYPE_TARGET);

		while (threat)
		{
			if (get_valid_air_threat (threat, source_side))
			{
				break;
			}

			threat = get_local_entity_child_succ (threat, LIST_TYPE_TARGET);
		}
	}

	return (threat);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int get_valid_ground_threat (entity *threat, entity_sides source_side)
{
	ASSERT (threat);

	if (get_local_entity_int_value (threat, INT_TYPE_IDENTIFY_VEHICLE))
	{
		if (get_local_entity_int_value (threat, INT_TYPE_VIEWABLE))
		{
			if (source_side != get_local_entity_int_value (threat, INT_TYPE_SIDE))
			{
				return (TRUE);
			}
		}
	}

	return (FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static entity *get_first_ground_threat (void)
{
	entity
		*source,
		*threat,
		*closest_threat;

	entity_sides
		source_side;

	float
		range,
		closest_threat_range;

	vec3d
		*source_position,
		*threat_position;

	source = get_gunship_entity ();

	ASSERT (source);

	source_side = (entity_sides) get_local_entity_int_value (source, INT_TYPE_SIDE);

	source_position = get_local_entity_vec3d_ptr (source, VEC3D_TYPE_POSITION);

	closest_threat = NULL;

	closest_threat_range = FLT_MAX;

	threat = get_local_entity_first_child (source, LIST_TYPE_TARGET);

	while (threat)
	{
		if (get_valid_ground_threat (threat, source_side))
		{
			threat_position = get_local_entity_vec3d_ptr (threat, VEC3D_TYPE_POSITION);

			range = get_sqr_3d_range (source_position, threat_position);

			if (range < closest_threat_range)
			{
				closest_threat = threat;

				closest_threat_range = range;
			}
		}

		threat = get_local_entity_child_succ (threat, LIST_TYPE_TARGET);
	}

	return (closest_threat);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static entity *get_next_ground_threat (void)
{
	entity
		*source,
		*threat;

	entity_sides
		source_side;

	source = get_gunship_entity ();

	ASSERT (source);

	source_side = (entity_sides) get_local_entity_int_value (source, INT_TYPE_SIDE);

	threat = get_local_entity_first_child (source, LIST_TYPE_PADLOCK);

	//
	// check threat is still a threat
	//

	if (threat)
	{
		if (get_local_entity_parent (threat, LIST_TYPE_TARGET) != source)
		{
			threat = NULL;
		}
	}

	//
	// find next threat in list
	//

	if (threat)
	{
		threat = get_local_entity_child_succ (threat, LIST_TYPE_TARGET);

		while (threat)
		{
			if (get_valid_ground_threat (threat, source_side))
			{
				break;
			}

			threat = get_local_entity_child_succ (threat, LIST_TYPE_TARGET);
		}
	}

	//
	// find first threat in list
	//

	if (!threat)
	{
		threat = get_local_entity_first_child (source, LIST_TYPE_TARGET);

		while (threat)
		{
			if (get_valid_ground_threat (threat, source_side))
			{
				break;
			}

			threat = get_local_entity_child_succ (threat, LIST_TYPE_TARGET);
		}
	}

	return (threat);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int get_valid_missile_threat (entity *threat)
{
	ASSERT (threat);

	if (get_local_entity_int_value (threat, INT_TYPE_VIEWABLE_WEAPON))
	{
		return (TRUE);
	}

	return (FALSE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static entity *get_first_missile_threat (void)
{
	entity
		*source,
		*threat,
		*closest_missile;

	int
		overshot;

	float
		threat_range,
		threat_velocity,
		time_to_impact,
		closest_missile_time_to_impact,
		length,
		cos_error;

	vec3d
		*source_position,
		*threat_position,
		uvec_threat_to_target;

	matrix3x3
		*attitude;

	source = get_gunship_entity ();

	ASSERT (source);

	source_position = get_local_entity_vec3d_ptr (source, VEC3D_TYPE_POSITION);

	closest_missile = NULL;

	closest_missile_time_to_impact = 1000000.0;

	threat = get_local_entity_first_child (get_gunship_entity (), LIST_TYPE_TARGET);

	while (threat)
	{
		if (get_valid_missile_threat (threat))
		{
			threat_position = get_local_entity_vec3d_ptr (threat, VEC3D_TYPE_POSITION);

			threat_range = get_3d_range (source_position, threat_position);

			threat_velocity = get_local_entity_float_value (threat, FLOAT_TYPE_VELOCITY);

			time_to_impact = threat_range / max (threat_velocity, 1.0f);

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
				if (time_to_impact < closest_missile_time_to_impact)
				{
					closest_missile = threat;

					closest_missile_time_to_impact = time_to_impact;
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

static entity *get_next_missile_threat (void)
{
	entity
		*source,
		*threat;

	source = get_gunship_entity ();

	ASSERT (source);

	threat = get_local_entity_first_child (source, LIST_TYPE_PADLOCK);

	//
	// check threat is still a threat
	//

	if (threat)
	{
		if (get_local_entity_parent (threat, LIST_TYPE_TARGET) != source)
		{
			threat = NULL;
		}
	}

	//
	// find next threat in list
	//

	if (threat)
	{
		threat = get_local_entity_child_succ (threat, LIST_TYPE_TARGET);

		while (threat)
		{
			if (get_valid_missile_threat (threat))
			{
				break;
			}

			threat = get_local_entity_child_succ (threat, LIST_TYPE_TARGET);
		}
	}

	//
	// find first threat in list
	//

	if (!threat)
	{
		threat = get_local_entity_first_child (source, LIST_TYPE_TARGET);

		while (threat)
		{
			if (get_valid_missile_threat (threat))
			{
				break;
			}

			threat = get_local_entity_child_succ (threat, LIST_TYPE_TARGET);
		}
	}

	return (threat);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void select_padlock_view_event (padlock_modes mode)
{
	entity
		*source,
		*target;

	source = get_gunship_entity ();

	ASSERT (source);

	switch (mode)
	{
		////////////////////////////////////////
		case PADLOCK_MODE_NONE:
		////////////////////////////////////////
		{
			if (get_view_mode () == VIEW_MODE_VIRTUAL_COCKPIT_TRACK_TARGET)
			{
				//
				// padlock target is handled via VIEW_MODE_VIRTUAL_COCKPIT_TRACK_TARGET
				//

				if (get_apache_havoc_gunship_fixed_cockpit ())
				{
					target = get_local_entity_parent (source, LIST_TYPE_TARGET);

					if (target)
					{
						get_pilot_head_heading_and_pitch_to_target (target);
					}

					set_view_mode (get_nearest_fixed_cockpit_view (pilot_head_heading, pilot_head_pitch));
				}
				else
				{
					set_view_mode (VIEW_MODE_VIRTUAL_COCKPIT);
				}
			}
			else if (get_view_mode () == VIEW_MODE_VIRTUAL_COCKPIT_PADLOCK)
			{
				//
				// cancel padlock
				//

				if (get_apache_havoc_gunship_fixed_cockpit ())
				{
					//
					// leave_padlock_view () tidies up padlock list and mode
					//

					set_view_mode (get_nearest_fixed_cockpit_view (pilot_head_heading, pilot_head_pitch));
				}
				else
				{
					//
					// leave_padlock_view () tidies up padlock list and mode
					//

					set_view_mode (VIEW_MODE_VIRTUAL_COCKPIT);
				}
			}

			break;
		}
		////////////////////////////////////////
		case PADLOCK_MODE_WINGMAN:
		////////////////////////////////////////
		{
			if ((get_view_mode () == VIEW_MODE_VIRTUAL_COCKPIT_PADLOCK) && (padlock_mode == PADLOCK_MODE_WINGMAN))
			{
				//
				// padlock next wingman
				//

				target = get_next_wingman ();

				if (target)
				{
					unlink_local_entity_children (source, LIST_TYPE_PADLOCK);

					insert_local_entity_into_parents_child_list (target, LIST_TYPE_PADLOCK, source, NULL);

					display_padlock_message (mode);
				}
			}
			else
			{
				//
				// padlock first wingman
				//

				target = get_first_wingman ();

				if (target)
				{
					//
					// leave_padlock_view () tidies up padlock list and mode
					//

					set_view_mode (VIEW_MODE_VIRTUAL_COCKPIT_PADLOCK);

					insert_local_entity_into_parents_child_list (target, LIST_TYPE_PADLOCK, source, NULL);

					padlock_mode = mode;

					display_padlock_message (mode);
				}
			}

			break;
		}
		////////////////////////////////////////
		case PADLOCK_MODE_AIR_THREAT:
		////////////////////////////////////////
		{
			if ((get_view_mode () == VIEW_MODE_VIRTUAL_COCKPIT_PADLOCK) && (padlock_mode == PADLOCK_MODE_AIR_THREAT))
			{
				//
				// padlock next air threat
				//

				target = get_next_air_threat ();

				if (target)
				{
					unlink_local_entity_children (source, LIST_TYPE_PADLOCK);

					insert_local_entity_into_parents_child_list (target, LIST_TYPE_PADLOCK, source, NULL);

					display_padlock_message (mode);
				}
			}
			else
			{
				//
				// padlock first air threat
				//

				target = get_first_air_threat ();

				if (target)
				{
					//
					// leave_padlock_view () tidies up padlock list and mode
					//

					set_view_mode (VIEW_MODE_VIRTUAL_COCKPIT_PADLOCK);

					insert_local_entity_into_parents_child_list (target, LIST_TYPE_PADLOCK, source, NULL);

					padlock_mode = mode;

					display_padlock_message (mode);
				}
			}

			break;
		}
		////////////////////////////////////////
		case PADLOCK_MODE_GROUND_THREAT:
		////////////////////////////////////////
		{
			if ((get_view_mode () == VIEW_MODE_VIRTUAL_COCKPIT_PADLOCK) && (padlock_mode == PADLOCK_MODE_GROUND_THREAT))
			{
				//
				// padlock next ground threat
				//

				target = get_next_ground_threat ();

				if (target)
				{
					unlink_local_entity_children (source, LIST_TYPE_PADLOCK);

					insert_local_entity_into_parents_child_list (target, LIST_TYPE_PADLOCK, source, NULL);

					display_padlock_message (mode);
				}
			}
			else
			{
				//
				// padlock first ground threat
				//

				target = get_first_ground_threat ();

				if (target)
				{
					//
					// leave_padlock_view () tidies up padlock list and mode
					//

					set_view_mode (VIEW_MODE_VIRTUAL_COCKPIT_PADLOCK);

					insert_local_entity_into_parents_child_list (target, LIST_TYPE_PADLOCK, source, NULL);

					padlock_mode = mode;

					display_padlock_message (mode);
				}
			}

			break;
		}
		////////////////////////////////////////
		case PADLOCK_MODE_MISSILE_THREAT:
		////////////////////////////////////////
		{
			if ((get_view_mode () == VIEW_MODE_VIRTUAL_COCKPIT_PADLOCK) && (padlock_mode == PADLOCK_MODE_MISSILE_THREAT))
			{
				//
				// padlock next missile threat
				//

				target = get_next_missile_threat ();

				if (target)
				{
					unlink_local_entity_children (source, LIST_TYPE_PADLOCK);

					insert_local_entity_into_parents_child_list (target, LIST_TYPE_PADLOCK, source, NULL);

					display_padlock_message (mode);
				}
			}
			else
			{
				//
				// padlock first missile threat
				//

				target = get_first_missile_threat ();

				if (target)
				{
					//
					// leave_padlock_view () tidies up padlock list and mode
					//

					set_view_mode (VIEW_MODE_VIRTUAL_COCKPIT_PADLOCK);

					insert_local_entity_into_parents_child_list (target, LIST_TYPE_PADLOCK, source, NULL);

					padlock_mode = mode;

					display_padlock_message (mode);
				}
			}

			break;
		}
		////////////////////////////////////////
		case PADLOCK_MODE_WAYPOINT:
		////////////////////////////////////////
		{
			if ((get_view_mode () == VIEW_MODE_VIRTUAL_COCKPIT_PADLOCK) && (padlock_mode == PADLOCK_MODE_WAYPOINT))
			{
				target = get_local_entity_current_waypoint (source);

				if (target)
				{
					display_padlock_message (mode);
				}
			}
			else
			{
				target = get_local_entity_current_waypoint (source);

				if (target)
				{
					//
					// leave_padlock_view () tidies up padlock list and mode
					//

					set_view_mode (VIEW_MODE_VIRTUAL_COCKPIT_PADLOCK);

					padlock_mode = mode;

					display_padlock_message (mode);
				}
			}

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			debug_fatal ("Invalid padlock mode = %d", mode);

			break;
		}
	}
}

// Jabberwock 031016 Inset view

void select_inset_view_event (padlock_modes mode)
{
	inset_mode = mode;
}


entity *get_inset (void)
{
	entity
		*source,
		*target;

	source = get_external_view_entity ();

	target = NULL;

	if (source)
	{
		switch (inset_mode)
		{
			case PADLOCK_MODE_NONE:
			{
				target = get_local_entity_parent (source, LIST_TYPE_TARGET);
				// Jabberwock 031027 not working :( target = get_gunship_entity();
				break;
			}
			case PADLOCK_MODE_WINGMAN:
			{
				if (source == get_gunship_entity())
				{
					target = get_next_wingman ();
				}
				break;
			}
			case PADLOCK_MODE_AIR_THREAT:
			{
				if (source == get_gunship_entity())
				{
					target = get_next_air_threat ();
				}
				break;
			}
			case PADLOCK_MODE_GROUND_THREAT:
			{
				if (source == get_gunship_entity())
				{
					target = get_next_ground_threat ();
				}
				break;
			}
			case PADLOCK_MODE_MISSILE_THREAT:
			{
				if (source == get_gunship_entity())
				{
					target = get_next_missile_threat ();
				}
				break;
			}
			case PADLOCK_MODE_WAYPOINT:
			{
				if (!target)
				{
					if (source == get_gunship_entity())
					{
						target = get_local_entity_current_waypoint (source);
					}
				}
				break;
			}
		}
	}
	return (target);
}



// Jabberwock 031016 ends

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *get_players_padlock (void)
{
	entity
		*target;

	target = NULL;

	if (get_view_mode () == VIEW_MODE_VIRTUAL_COCKPIT_TRACK_TARGET)
	{
		target = get_local_entity_parent (get_gunship_entity (), LIST_TYPE_TARGET);
	}
	else if (get_view_mode () == VIEW_MODE_VIRTUAL_COCKPIT_PADLOCK)
	{
		switch (padlock_mode)
		{
			////////////////////////////////////////
			case PADLOCK_MODE_NONE:
			////////////////////////////////////////
			{
				debug_fatal ("Invalid padlock mode = PADLOCK_MODE_NONE");

				break;
			}
			////////////////////////////////////////
			case PADLOCK_MODE_WINGMAN:
			case PADLOCK_MODE_AIR_THREAT:
			case PADLOCK_MODE_GROUND_THREAT:
			case PADLOCK_MODE_MISSILE_THREAT:
			////////////////////////////////////////
			{
				target = get_local_entity_first_child (get_gunship_entity (), LIST_TYPE_PADLOCK);

				break;
			}
			////////////////////////////////////////
			case PADLOCK_MODE_WAYPOINT:
			////////////////////////////////////////
			{
				target = NULL;

				break;
			}
			////////////////////////////////////////
			default:
			////////////////////////////////////////
			{
				debug_fatal ("Invalid padlock mode = %d", padlock_mode);

				break;
			}
		}
	}

	return (target);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_virtual_cockpit_padlock_view (void)
{
	float
		old_heading,
		old_pitch,
		delta_heading,
		delta_pitch,
		frame_rotate_rate;

	entity
		*source,
		*target;

	source = get_gunship_entity ();

	ASSERT (source);

	switch (padlock_mode)
	{
		////////////////////////////////////////
		case PADLOCK_MODE_NONE:
		////////////////////////////////////////
		{
			debug_fatal ("Invalid padlock mode = PADLOCK_MODE_NONE");

			break;
		}
		////////////////////////////////////////
		case PADLOCK_MODE_WINGMAN:
		case PADLOCK_MODE_AIR_THREAT:
		case PADLOCK_MODE_GROUND_THREAT:
		case PADLOCK_MODE_MISSILE_THREAT:
		////////////////////////////////////////
		{
			target = get_local_entity_first_child (source, LIST_TYPE_PADLOCK);

			break;
		}
		////////////////////////////////////////
		case PADLOCK_MODE_WAYPOINT:
		////////////////////////////////////////
		{
			target = get_local_entity_current_waypoint (source);

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			debug_fatal ("Invalid padlock mode = %d", padlock_mode);

			break;
		}
	}

	if (target)
	{
		old_heading = pilot_head_heading;

		old_pitch = pilot_head_pitch;

		get_pilot_head_heading_and_pitch_to_target (target);

		frame_rotate_rate = rad (45.0) * get_delta_time ();

		delta_heading = pilot_head_heading - old_heading;

		delta_heading = bound (delta_heading, -frame_rotate_rate, frame_rotate_rate);

		pilot_head_heading = old_heading + delta_heading;

		delta_pitch = pilot_head_pitch - old_pitch;

		delta_pitch = bound (delta_pitch, -frame_rotate_rate, frame_rotate_rate);

		pilot_head_pitch = old_pitch + delta_pitch;
	}
	else
	{
		frame_rotate_rate = rad (45.0) * get_delta_time ();

		delta_heading = bound (-pilot_head_heading, -frame_rotate_rate, frame_rotate_rate);

		pilot_head_heading += delta_heading;

		delta_pitch = bound (-pilot_head_pitch, -frame_rotate_rate, frame_rotate_rate);

		pilot_head_pitch += delta_pitch;

		if
		(
			(pilot_head_heading >= rad (-1.0)) &&
			(pilot_head_heading <= rad (1.0)) &&
			(pilot_head_pitch >= rad (-1.0)) &&
			(pilot_head_pitch <= rad (1.0))
		)
		{
			//
			// leave_padlock_view () tidies up padlock list and mode
			//

			set_view_mode (VIEW_MODE_COCKPIT_PANEL_LEVEL_AHEAD);
		}
	}
/*
//VJ wideview mod, date: 27-mar-03
//VJ 050131 wideview mod, better
	if (get_global_wide_cockpit () &&
		 !command_line_3d_cockpit &&
		 get_global_gunship_type () != GUNSHIP_TYPE_COMANCHE &&
		 get_global_gunship_type () != GUNSHIP_TYPE_HOKUM
		)
	{
         float max_pitch = -0.271*pilot_head_heading*pilot_head_heading - 0.05;

   		pilot_head_pitch = max (max_pitch, pilot_head_pitch);
		//debug_log("heading: %f    pitch %f [%f]",pilot_head_heading,pilot_head_pitch,max_pitch);
	}
	*/
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_position_nose_relative_position ( vec3d *position, vec3d *r )
{
	vec3d
		relative_position;
	matrix3x3*
		attitude;

	ASSERT(current_flight_dynamics);

	relative_position.x = position->x - current_flight_dynamics->position.x;
	relative_position.y = position->y - current_flight_dynamics->position.y;
	relative_position.z = position->z - current_flight_dynamics->position.z;

	attitude = &current_flight_dynamics->attitude;
//	xv = &attitude[0][0];

	r->x = ( relative_position.x * (*attitude)[0][0] + relative_position.y * (*attitude)[0][1] + relative_position.z * (*attitude)[0][2] );
	r->y = ( relative_position.x * (*attitude)[1][0] + relative_position.y * (*attitude)[1][1] + relative_position.z * (*attitude)[1][2] );
	r->z = ( relative_position.x * (*attitude)[2][0] + relative_position.y * (*attitude)[2][1] + relative_position.z * (*attitude)[2][2] );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum OBJECT_3D_VISIBILITY get_position_nose_relative_coordinates ( vec3d *position, float *x, float *y )
{

	vec3d
		relative_position;

	float
		q,
		i,
		j;

	get_position_nose_relative_position ( position, &relative_position );

	if ( relative_position.z < clip_hither )
		return ( OBJECT_3D_NOT_VISIBLE );

	q = 1.0 / relative_position.z;

	i = ( active_3d_environment->screen_i_scale * relative_position.x * q );
	j = ( active_3d_environment->screen_j_scale * relative_position.y * q );

	*x = active_3d_environment->x_origin + i;
	*y = active_3d_environment->y_origin - j;

	return ( OBJECT_3D_COMPLETELY_VISIBLE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
