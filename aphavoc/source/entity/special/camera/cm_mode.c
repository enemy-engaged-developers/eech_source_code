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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "project.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_camera_mode (camera *raw, camera_modes mode, int auto_edit)
{
	ASSERT (raw);

	if ((mode >= 0) && (mode < NUM_CAMERA_MODES))
	{
		debug_log ("Setting camera mode to %s", camera_mode_names[mode]);
	}

	// Jabberwock 031009 - Satellite view - only satellite view for sites
	if (get_local_entity_type (raw->external_view_entity) == ENTITY_TYPE_KEYSITE)
	{ 
		mode = CAMERA_MODE_SATELLITE;
		auto_edit = 0;
	}
	// Jabberwock 031009 ends
	
	
	if (auto_edit)
	{
		if (!raw->auto_edit)
		{
			set_status_message (get_trans ("Auto-action camera"), STATUS_MESSAGE_TYPE_CAMERA);
		}
	}
	else
	{
		const char
			*s;

		s = get_camera_mode_name (mode);

		if (s)
		{
			set_status_message (get_trans (s), STATUS_MESSAGE_TYPE_CAMERA);
		}
	}
	
	switch (mode)
	{
		////////////////////////////////////////
		case CAMERA_MODE_CHASE:
		////////////////////////////////////////
		{
			reset_chase_camera (raw);

			break;
		}
		////////////////////////////////////////
		case CAMERA_MODE_END_OF_MISSION:
		////////////////////////////////////////
		{
			reset_end_of_mission_camera (raw);

			break;
		}
		////////////////////////////////////////
		case CAMERA_MODE_DROP:
		////////////////////////////////////////
		{
			reset_drop_camera (raw);

			break;
		}
		////////////////////////////////////////
		case CAMERA_MODE_STATIC:
		////////////////////////////////////////
		{
			reset_static_camera (raw);

			break;
		}
		
		// Jabberwock 031009 Satellite view
		case CAMERA_MODE_SATELLITE:
		////////////////////////////////////////
		{
			reset_satellite_camera (raw);

			break;
		}
		
		// Jabberwock 031009 ends
		
		////////////////////////////////////////
		case CAMERA_MODE_EJECT:
		////////////////////////////////////////
		{
			reset_eject_camera (raw);

			break;
		}
		////////////////////////////////////////
		case CAMERA_MODE_FLY_BY:
		////////////////////////////////////////
		{
			reset_fly_by_camera (raw);

			break;
		}
		////////////////////////////////////////
		case CAMERA_MODE_CINEMATIC:
		////////////////////////////////////////
		{
			reset_cinematic_camera (raw);

			break;
		}
		////////////////////////////////////////
		case CAMERA_MODE_BUILDING:
		////////////////////////////////////////
		{
			reset_building_camera (raw);

			break;
		}
		////////////////////////////////////////
		case CAMERA_MODE_WEAPON:
		////////////////////////////////////////
		{
			if (weapon_camera_valid (raw))
			{
				reset_weapon_camera (raw);
			}
			else
			{
				mode = CAMERA_MODE_CHASE;

				reset_chase_camera (raw);
			}

			break;
		}
		////////////////////////////////////////
		case CAMERA_MODE_WEAPON_EXPLOSION:
		////////////////////////////////////////
		{
			reset_weapon_explosion_camera (raw);

			break;
		}
		////////////////////////////////////////
		case CAMERA_MODE_DEBRIEFING:
		////////////////////////////////////////
		{
			if (debriefing_camera_valid (raw))
			{
				reset_debriefing_camera (raw);
			}
			else
			{
				mode = CAMERA_MODE_CHASE;

				reset_chase_camera (raw);
			}

			break;
		}
		////////////////////////////////////////
		case CAMERA_MODE_RECOGNITION_GUIDE_TOP_VIEW:
		////////////////////////////////////////
		{
			if (recognition_guide_top_view_camera_valid (raw))
			{
				reset_recognition_guide_top_view_camera (raw);
			}
			else
			{
				mode = CAMERA_MODE_CHASE;

				reset_chase_camera (raw);
			}

			break;
		}
		////////////////////////////////////////
		case CAMERA_MODE_RECOGNITION_GUIDE_SIDE_VIEW:
		////////////////////////////////////////
		{
			if (recognition_guide_side_view_camera_valid (raw))
			{
				reset_recognition_guide_side_view_camera (raw);
			}
			else
			{
				mode = CAMERA_MODE_CHASE;

				reset_chase_camera (raw);
			}

			break;
		}
		////////////////////////////////////////
		case CAMERA_MODE_RECOGNITION_GUIDE_FRONT_VIEW:
		////////////////////////////////////////
		{
			if (recognition_guide_front_view_camera_valid (raw))
			{
				reset_recognition_guide_front_view_camera (raw);
			}
			else
			{
				mode = CAMERA_MODE_CHASE;

				reset_chase_camera (raw);
			}

			break;
		}
		////////////////////////////////////////
		case CAMERA_MODE_RECOGNITION_GUIDE_3D_VIEW:
		////////////////////////////////////////
		{
			if (recognition_guide_3d_view_camera_valid (raw))
			{
				reset_recognition_guide_3d_view_camera (raw);
			}
			else
			{
				mode = CAMERA_MODE_CHASE;

				reset_chase_camera (raw);
			}

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

	raw->camera_mode = mode;

	raw->auto_edit = auto_edit;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
