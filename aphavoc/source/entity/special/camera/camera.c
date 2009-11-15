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

#define DEBUG_MODULE 0

#define CAMERA_MOVEMENT_RATE 8.0f
#define OFFSET_MOVEMENT_RATE 20.0f
#define MAX_OFFSET 20.0f

#define CHASE_CAMERA_ZOOM_RATE			(0.5f)
#define CHASE_CAMERA_ZOOM_IN_LIMIT		(0.0f)
#define CHASE_CAMERA_ZOOM_OUT_LIMIT		(2.0f)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "project.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char
	*camera_mode_names[NUM_CAMERA_MODES] =
	{
		"CAMERA_MODE_CHASE",
		"CAMERA_MODE_END_OF_MISSION",
		"CAMERA_MODE_DROP",
		"CAMERA_MODE_STATIC",
		"CAMERA_MODE_SATELLITE",		// Jabberwock 031009 Satellite view
		"CAMERA_MODE_EJECT",
		"CAMERA_MODE_FLY_BY",
		"CAMERA_MODE_CINEMATIC",
		"CAMERA_MODE_BUILDING",
		"CAMERA_MODE_WEAPON",
		"CAMERA_MODE_WEAPON_EXPLOSION",
		"CAMERA_MODE_DEBRIEFING",
		"CAMERA_MODE_RECOGNITION_GUIDE_TOP_VIEW",
		"CAMERA_MODE_RECOGNITION_GUIDE_SIDE_VIEW",
		"CAMERA_MODE_RECOGNITION_GUIDE_FRONT_VIEW",
		"CAMERA_MODE_RECOGNITION_GUIDE_3D_VIEW",
		"CAMERA_MODE_FREE",
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char
	*camera_action_names[NUM_CAMERA_ACTIONS] =
	{
		"CAMERA_ACTION_CHASE",
		"CAMERA_ACTION_RESET_CHASE_POSITION",
		"CAMERA_ACTION_TOGGLE_CHASE_LOCK_ROTATE",
		"CAMERA_ACTION_END_OF_MISSION",
		"CAMERA_ACTION_DROP",
		"CAMERA_ACTION_STATIC",
		"CAMERA_ACTION_SATELLITE", // Jabberwock 031009 Satellite view
		"CAMERA_ACTION_EJECT",
		"CAMERA_ACTION_FLY_BY",
		"CAMERA_ACTION_CINEMATIC",
		"CAMERA_ACTION_BUILDING",
		"CAMERA_ACTION_WEAPON",
		"CAMERA_ACTION_WEAPON_EXPLOSION",
		"CAMERA_ACTION_AUTO_EDIT",
		"CAMERA_ACTION_DEBRIEFING",
		"CAMERA_ACTION_RECOGNITION_GUIDE_TOP_VIEW",
		"CAMERA_ACTION_RECOGNITION_GUIDE_SIDE_VIEW",
		"CAMERA_ACTION_RECOGNITION_GUIDE_FRONT_VIEW",
		"CAMERA_ACTION_RECOGNITION_GUIDE_3D_VIEW",
		"CAMERA_ACTION_FREE",
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity
	*camera_entity = NULL;

int camera_previous_mouse_update_flag = 1;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define same_sign(f1, f2) (((f1) >= 0.0 && (f2) >= 0.0 ) || ((f1) < 0.0 && (f2) < 0.0))

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_camera_entity (entity *en)
{
	camera_entity = en;

/*
	if (en)
	{
		debug_log ("Setting camera_entity (type = %s, index = %d)", get_local_entity_type_name (en), get_local_entity_index (en));
	}
	else
	{
		debug_log ("Setting camera_entity to NULL");
	}
*/
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *get_local_entity_view_list_pred (entity *en)
{
	entity
		*pred,
		*parent;

	ASSERT (en);

	ASSERT (get_camera_entity ());

	parent = get_local_entity_parent (en, LIST_TYPE_MEMBER);

	ASSERT (parent);

	pred = get_local_entity_first_child (get_camera_entity (), LIST_TYPE_VIEW);

	while (pred)
	{
		if (parent == get_local_entity_parent (pred, LIST_TYPE_MEMBER))
		{
			break;
		}

		pred = get_local_entity_child_succ (pred, LIST_TYPE_VIEW);
	}

	return (pred);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char *get_camera_mode_name (camera_modes mode)
{
	camera
		*raw;

	char
		*s;

	ASSERT (get_camera_entity ());

	raw = (camera *) get_local_entity_data (get_camera_entity ());

	switch (mode)
	{
		////////////////////////////////////////
		case CAMERA_MODE_CHASE:
		////////////////////////////////////////
		{
			s = "Chase camera";

			break;
		}
		////////////////////////////////////////
		case CAMERA_MODE_DROP:
		////////////////////////////////////////
		{
			s = "Drop camera";

			break;
		}
		////////////////////////////////////////
		case CAMERA_MODE_STATIC:
		////////////////////////////////////////
		{
			s = "Static camera";

			break;
		}

		// Jabberwock 031009 Satellite view
		////////////////////////////////////////
		case CAMERA_MODE_SATELLITE:
		////////////////////////////////////////
		{
			s = "Satellite camera";

			break;
		}
		// Jabberwock 031009 ends
		
		////////////////////////////////////////
		case CAMERA_MODE_FLY_BY:
		////////////////////////////////////////
		{
			s = "Fly-by camera";

			break;
		}
		////////////////////////////////////////
		case CAMERA_MODE_CINEMATIC:
		////////////////////////////////////////
		{
			s = "Cinematic camera";

			break;
		}
		////////////////////////////////////////
		case CAMERA_MODE_BUILDING:
		////////////////////////////////////////
		{
			s = "Structure camera";

			break;
		}
		////////////////////////////////////////
		case CAMERA_MODE_WEAPON:
		////////////////////////////////////////
		{
			s = "Weapon camera";

			break;
		}
		////////////////////////////////////////
		case CAMERA_MODE_FREE:
		////////////////////////////////////////
		{
			s = "Free camera";

			break;
		}
		////////////////////////////////////////
		case CAMERA_MODE_END_OF_MISSION:
		case CAMERA_MODE_EJECT:
		case CAMERA_MODE_WEAPON_EXPLOSION:
		case CAMERA_MODE_DEBRIEFING:
		case CAMERA_MODE_RECOGNITION_GUIDE_TOP_VIEW:
		case CAMERA_MODE_RECOGNITION_GUIDE_SIDE_VIEW:
		case CAMERA_MODE_RECOGNITION_GUIDE_FRONT_VIEW:
		case CAMERA_MODE_RECOGNITION_GUIDE_3D_VIEW:
		////////////////////////////////////////
		{
			s = NULL;

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			debug_fatal ("Invalid camera mode = %d", mode);

			break;
		}
	}

	return (s);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void adjust_offset(camera* raw)
{
	float acceleration = 0.0;

	if (command_line_wobbly_camera)
	{
		if (move_view_forward_key)
			acceleration = OFFSET_MOVEMENT_RATE * move_view_forward_key;
		else if (move_view_backward_key)
			acceleration = -OFFSET_MOVEMENT_RATE * move_view_backward_key;
		else
			acceleration = -4.0 * raw->offset_movement.y;
	
		raw->offset_movement.y += acceleration * get_delta_time();

		if (move_view_right_key)
			acceleration = OFFSET_MOVEMENT_RATE * move_view_right_key;
		else if (move_view_left_key)
			acceleration = -OFFSET_MOVEMENT_RATE * move_view_left_key;
		else
			acceleration = -4.0 * raw->offset_movement.x;
	
		raw->offset_movement.x += acceleration * get_delta_time();
	}
	else
	{
		if (move_view_forward_key)
			raw->offset_movement.y = OFFSET_MOVEMENT_RATE * move_view_forward_key;
		else if (move_view_backward_key)
			raw->offset_movement.y = -OFFSET_MOVEMENT_RATE * move_view_backward_key;
		else
			raw->offset_movement.y = 0.0;

		if (move_view_right_key)
			raw->offset_movement.x = OFFSET_MOVEMENT_RATE * move_view_right_key;
		else if (move_view_left_key)
			raw->offset_movement.x = -OFFSET_MOVEMENT_RATE * move_view_left_key;
		else
			raw->offset_movement.x = 0.0;
	}


	raw->offset.x = bound(raw->offset.x + raw->offset_movement.x * get_delta_time(), -MAX_OFFSET, MAX_OFFSET);
	raw->offset.y = bound(raw->offset.y + raw->offset_movement.y * get_delta_time(), -MAX_OFFSET, MAX_OFFSET);
}

void reset_offset(camera* raw)
{
	raw->offset.x = 0.0;
	raw->offset.y = 0.0;
	raw->offset.z = 0.0;

#if 0
	raw->post_adjust_position.x = MID_MAP_X;
	raw->post_adjust_position.y = MID_MAP_Y;
	raw->post_adjust_position.z = MID_MAP_Z;
#endif
	raw->turbulence_offset.x = 0.0;
	raw->turbulence_offset.y = 0.0;
	raw->turbulence_offset.z = 0.0;

	raw->turbulence_movement.x = 0.0;
	raw->turbulence_movement.y = 0.0;
	raw->turbulence_movement.z = 0.0;
}

void adjust_camera_smooth(camera* raw, vec3d* new_position)
{
#if 0
	if (command_line_wobbly_camera)
	{
		vec3d adjust;

		adjust.x = new_position->x - raw->post_adjust_position.x;
		adjust.y = new_position->y - raw->post_adjust_position.y;
		adjust.z = new_position->z - raw->post_adjust_position.z;
	
		adjust.x *= CAMERA_MOVEMENT_RATE * get_delta_time();
		adjust.y *= CAMERA_MOVEMENT_RATE * get_delta_time();
		adjust.z *= CAMERA_MOVEMENT_RATE * get_delta_time();

		raw->position.x += adjust.x;
		raw->position.y += adjust.y;
		raw->position.z += adjust.z;
		raw->post_adjust_position = raw->position;
	}
	else
#endif
		raw->position = *new_position;

	// keep point above ground (unless point off map)
	if (point_inside_map_area (&raw->position))
		raw->position.y = max (raw->position.y, get_3d_terrain_point_data (raw->position.x, raw->position.z, &raw->terrain_info) + CAMERA_MIN_HEIGHT_ABOVE_GROUND);
}

void add_turbulence(camera* cam, vec3d* position)
{
	float
		velocity_factor,
		zoom_factor = 0.1,
		acceleration;

	if (!command_line_wobbly_camera)
		return;

	velocity_factor = bound(fabs(cam->motion_vector.x) + fabs(cam->motion_vector.y) + fabs(cam->motion_vector.z) * 1/200.0, 0.0, 1.0);
	if (cam->chase_camera_zoom)
		zoom_factor = cam->chase_camera_zoom + 0.25;

	// add random turbulence
	if (velocity_factor > 0.1 && (rand() % (int)(get_one_over_delta_time())) == 0)
		cam->turbulence_movement.x += sfrand1() * velocity_factor * zoom_factor;
	if (velocity_factor > 0.1 && (rand() % (int)(get_one_over_delta_time())) == 0)
		cam->turbulence_movement.y += sfrand1() * velocity_factor * zoom_factor;
	if (velocity_factor > 0.1 && (rand() % (int)(get_one_over_delta_time())) == 0)
		cam->turbulence_movement.z += sfrand1() * velocity_factor * zoom_factor;

	// bungy effect of camera trying to get itself back in position
	acceleration = -cam->turbulence_offset.x * 0.5 ;
	if (same_sign(acceleration, cam->turbulence_movement.x))
		acceleration *= 0.5;
	cam->turbulence_movement.x += acceleration * get_delta_time();
	cam->turbulence_offset.x += cam->turbulence_movement.x * get_delta_time();

	acceleration = -cam->turbulence_offset.y * 0.5 ;
	if (same_sign(acceleration, cam->turbulence_movement.y))
		acceleration *= 0.5;
	cam->turbulence_movement.y += acceleration * get_delta_time();
	cam->turbulence_offset.y += cam->turbulence_movement.y * get_delta_time();

	acceleration = -cam->turbulence_offset.z * 0.5 ;
	if (same_sign(acceleration, cam->turbulence_movement.z))
		acceleration *= 0.5;
	cam->turbulence_movement.z += acceleration * get_delta_time();
	cam->turbulence_offset.z += cam->turbulence_movement.z * get_delta_time();

	// move due to turbulence
	cam->position.x += cam->turbulence_offset.x;
	cam->position.y += cam->turbulence_offset.y;
	cam->position.z += cam->turbulence_offset.z;
}

void adjust_camera_zoom(camera* raw)
{
	if (adjust_view_zoom_in_key)
	{
		raw->chase_camera_zoom -= CHASE_CAMERA_ZOOM_RATE * get_delta_time ();

		raw->chase_camera_zoom = max (CHASE_CAMERA_ZOOM_IN_LIMIT, raw->chase_camera_zoom);
	}
	else if (adjust_view_zoom_out_key)
	{
		raw->chase_camera_zoom += CHASE_CAMERA_ZOOM_RATE * get_delta_time ();

		raw->chase_camera_zoom = min (CHASE_CAMERA_ZOOM_OUT_LIMIT, raw->chase_camera_zoom);
	}

	// Jabberwock 050103 - Mouse wheel zoom for external view
	if (mouse_wheel_up)
	{
		raw->chase_camera_zoom -= 2 * get_delta_time ();

		raw->chase_camera_zoom = max (CHASE_CAMERA_ZOOM_IN_LIMIT, raw->chase_camera_zoom);

		mouse_wheel_up--;
	}
	else if (mouse_wheel_down)
	{
		raw->chase_camera_zoom += 2 * get_delta_time ();

		raw->chase_camera_zoom = min (CHASE_CAMERA_ZOOM_OUT_LIMIT, raw->chase_camera_zoom);

		mouse_wheel_down--;
	}
	// Jabberwock 050103 ends	
}
