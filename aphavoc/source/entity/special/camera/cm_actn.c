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

void set_camera_action (camera *raw, camera_actions action)
{
	ASSERT (raw);

	ASSERT (raw->external_view_entity);

	if ((action >= 0) && (action < NUM_CAMERA_ACTIONS))
	{
		debug_log (camera_action_names[action]);
	}

	switch (action)
	{
		////////////////////////////////////////
		case CAMERA_ACTION_CHASE:
		////////////////////////////////////////
		{
			if (get_view_mode () != VIEW_MODE_EXTERNAL)
			{
				if (!set_view_mode (VIEW_MODE_EXTERNAL))
				{
					break;
				}
			}

			set_camera_mode (raw, CAMERA_MODE_CHASE, FALSE);

			break;
		}
		////////////////////////////////////////
		case CAMERA_ACTION_RESET_CHASE_POSITION:
		////////////////////////////////////////
		{
			if (get_view_mode () != VIEW_MODE_EXTERNAL)
			{
				if (!set_view_mode (VIEW_MODE_EXTERNAL))
				{
					break;
				}
			}

			set_camera_mode (raw, CAMERA_MODE_CHASE, FALSE);

			reset_chase_camera_position (raw);

			break;
		}
		////////////////////////////////////////
		case CAMERA_ACTION_TOGGLE_CHASE_LOCK_ROTATE:
		////////////////////////////////////////
		{
			if (get_view_mode () != VIEW_MODE_EXTERNAL)
			{
				if (!set_view_mode (VIEW_MODE_EXTERNAL))
				{
					break;
				}
			}

			set_camera_mode (raw, CAMERA_MODE_CHASE, FALSE);

			//
			// adjust the camera heading so that the camera does not 'jump' when toggle lock
			//

			if (raw->chase_camera_lock_rotate)
			{
				raw->chase_camera_heading += get_local_entity_float_value (raw->external_view_entity, FLOAT_TYPE_HEADING);
			}
			else
			{
				raw->chase_camera_heading -= get_local_entity_float_value (raw->external_view_entity, FLOAT_TYPE_HEADING);
			}

			raw->chase_camera_heading = wrap_angle (raw->chase_camera_heading);

			raw->chase_camera_lock_rotate ^= 1;

			break;
		}
		////////////////////////////////////////
		case CAMERA_ACTION_END_OF_MISSION:
		////////////////////////////////////////
		{
			if (get_view_mode () != VIEW_MODE_EXTERNAL)
			{
				if (!set_view_mode (VIEW_MODE_EXTERNAL))
				{
					break;
				}
			}

			set_camera_mode (raw, CAMERA_MODE_END_OF_MISSION, FALSE);

			break;
		}
		////////////////////////////////////////
		case CAMERA_ACTION_DROP:
		////////////////////////////////////////
		{
			if (get_view_mode () != VIEW_MODE_EXTERNAL)
			{
				if (!set_view_mode (VIEW_MODE_EXTERNAL))
				{
					break;
				}
			}

			set_camera_mode (raw, CAMERA_MODE_DROP, FALSE);

			break;
		}
		////////////////////////////////////////
		case CAMERA_ACTION_STATIC:
		////////////////////////////////////////
		{
			if (get_view_mode () != VIEW_MODE_EXTERNAL)
			{
				if (!set_view_mode (VIEW_MODE_EXTERNAL))
				{
					break;
				}
			}

			set_camera_mode (raw, CAMERA_MODE_STATIC, FALSE);

			break;
		}
		
		// Jabberwock 031009 Satellite view
		////////////////////////////////////////
		case CAMERA_ACTION_SATELLITE:
		////////////////////////////////////////
		{
			if (get_view_mode () != VIEW_MODE_EXTERNAL)
			{
				if (!set_view_mode (VIEW_MODE_EXTERNAL))
				{
					break;
				}
			}

			set_camera_mode (raw, CAMERA_MODE_SATELLITE, FALSE);

			break;
		}
		// Jabberwock 031009 ends
		
		////////////////////////////////////////
		case CAMERA_ACTION_EJECT:
		////////////////////////////////////////
		{
			if (get_view_mode () != VIEW_MODE_EXTERNAL)
			{
				if (!set_view_mode (VIEW_MODE_EXTERNAL))
				{
					break;
				}
			}

			set_camera_mode (raw, CAMERA_MODE_EJECT, FALSE);

			break;
		}
		////////////////////////////////////////
		case CAMERA_ACTION_FLY_BY:
		////////////////////////////////////////
		{
			if (get_view_mode () != VIEW_MODE_EXTERNAL)
			{
				if (!set_view_mode (VIEW_MODE_EXTERNAL))
				{
					break;
				}
			}

			set_camera_mode (raw, CAMERA_MODE_FLY_BY, FALSE);

			break;
		}
		////////////////////////////////////////
		case CAMERA_ACTION_CINEMATIC:
		////////////////////////////////////////
		{
			if (get_view_mode () != VIEW_MODE_EXTERNAL)
			{
				if (!set_view_mode (VIEW_MODE_EXTERNAL))
				{
					break;
				}
			}

			set_camera_mode (raw, CAMERA_MODE_CINEMATIC, FALSE);

			break;
		}
		////////////////////////////////////////
		case CAMERA_ACTION_BUILDING:
		////////////////////////////////////////
		{
			if (get_view_mode () != VIEW_MODE_EXTERNAL)
			{
				if (!set_view_mode (VIEW_MODE_EXTERNAL))
				{
					break;
				}
			}

			set_camera_mode (raw, CAMERA_MODE_BUILDING, FALSE);

			break;
		}
		////////////////////////////////////////
		case CAMERA_ACTION_WEAPON:
		////////////////////////////////////////
		{
			entity
				*en;

			en = get_external_view_entity_viewable_weapon ();

			if (en)
			{
				if (get_view_mode () != VIEW_MODE_EXTERNAL)
				{
					if (!set_view_mode (VIEW_MODE_EXTERNAL))
					{
						break;
					}
				}

				if (raw->view_weapon_root.first_child)
				{
					delete_local_entity_from_parents_child_list (raw->view_weapon_root.first_child, LIST_TYPE_VIEW_WEAPON);

					ASSERT (!raw->view_weapon_root.first_child);
				}

				insert_local_entity_into_parents_child_list (en, LIST_TYPE_VIEW_WEAPON, get_camera_entity (), NULL);

				set_camera_mode (raw, CAMERA_MODE_WEAPON, FALSE);
			}
			else
			{
				raw->weapon_camera_primed ^= 1;

				if (raw->weapon_camera_primed)
				{
					set_status_message (get_trans ("Weapon camera primed"), STATUS_MESSAGE_TYPE_CAMERA);
				}
			}

			break;
		}
		////////////////////////////////////////
		case CAMERA_ACTION_WEAPON_EXPLOSION:
		////////////////////////////////////////
		{
			if (get_view_mode () != VIEW_MODE_EXTERNAL)
			{
				if (!set_view_mode (VIEW_MODE_EXTERNAL))
				{
					break;
				}
			}

			set_camera_mode (raw, CAMERA_MODE_WEAPON_EXPLOSION, FALSE);

			break;
		}
		////////////////////////////////////////
		case CAMERA_ACTION_AUTO_EDIT:
		////////////////////////////////////////
		{
			if (get_view_mode () != VIEW_MODE_EXTERNAL)
			{
				if (!set_view_mode (VIEW_MODE_EXTERNAL))
				{
					break;
				}
			}

			set_camera_mode (raw, get_auto_edit_random_camera_mode (raw), TRUE);

			break;
		}
		////////////////////////////////////////
		case CAMERA_ACTION_DEBRIEFING:
		////////////////////////////////////////
		{
			if (get_gunship_entity ())
			{
				if (get_view_mode () != VIEW_MODE_EXTERNAL)
				{
					if (!set_view_mode (VIEW_MODE_EXTERNAL))
					{
						break;
					}
				}

				set_external_view_entity (get_gunship_entity ());

				set_camera_mode (raw, CAMERA_MODE_DEBRIEFING, FALSE);

				set_view_menu_display_visible_status (FALSE);
			}

			break;
		}
		////////////////////////////////////////
		case CAMERA_ACTION_RECOGNITION_GUIDE_TOP_VIEW:
		////////////////////////////////////////
		{
			if (get_view_mode () != VIEW_MODE_EXTERNAL)
			{
				if (!set_view_mode (VIEW_MODE_EXTERNAL))
				{
					break;
				}
			}

			set_camera_mode (raw, CAMERA_MODE_RECOGNITION_GUIDE_TOP_VIEW, FALSE);

			break;
		}
		////////////////////////////////////////
		case CAMERA_ACTION_RECOGNITION_GUIDE_SIDE_VIEW:
		////////////////////////////////////////
		{
			if (get_view_mode () != VIEW_MODE_EXTERNAL)
			{
				if (!set_view_mode (VIEW_MODE_EXTERNAL))
				{
					break;
				}
			}

			set_camera_mode (raw, CAMERA_MODE_RECOGNITION_GUIDE_SIDE_VIEW, FALSE);

			break;
		}
		////////////////////////////////////////
		case CAMERA_ACTION_RECOGNITION_GUIDE_FRONT_VIEW:
		////////////////////////////////////////
		{
			if (get_view_mode () != VIEW_MODE_EXTERNAL)
			{
				if (!set_view_mode (VIEW_MODE_EXTERNAL))
				{
					break;
				}
			}

			set_camera_mode (raw, CAMERA_MODE_RECOGNITION_GUIDE_FRONT_VIEW, FALSE);

			break;
		}
		////////////////////////////////////////
		case CAMERA_ACTION_RECOGNITION_GUIDE_3D_VIEW:
		////////////////////////////////////////
		{
			if (get_view_mode () != VIEW_MODE_EXTERNAL)
			{
				if (!set_view_mode (VIEW_MODE_EXTERNAL))
				{
					break;
				}
			}

			set_camera_mode (raw, CAMERA_MODE_RECOGNITION_GUIDE_3D_VIEW, FALSE);

			break;
		}
		////////////////////////////////////////
		case CAMERA_ACTION_FREE:
		////////////////////////////////////////
		{
			if (get_view_mode () != VIEW_MODE_EXTERNAL)
			{
				if (!set_view_mode (VIEW_MODE_EXTERNAL))
				{
					break;
				}
			}

			set_camera_mode (raw, CAMERA_MODE_FREE, FALSE);

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			debug_fatal ("Invalid camera action = %d", action);

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
