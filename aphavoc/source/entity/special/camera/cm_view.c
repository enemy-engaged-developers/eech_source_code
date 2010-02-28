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

void set_raw_external_view_entity (entity *en)
{
	int
		new_view_entity;

	camera
		*raw;

	ASSERT (en);

	ASSERT (get_camera_entity ());

	raw = (camera *) get_local_entity_data (get_camera_entity ());

	new_view_entity = raw->external_view_entity != en;

	raw->external_view_entity = en;

	if (new_view_entity)
	{
//		debug_log ("Setting view entity (type = %s, index = %d%)", get_local_entity_type_name (en), get_local_entity_index (en));

		switch (raw->camera_mode)
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
			////////////////////////////////////////
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
				set_camera_mode (raw, CAMERA_MODE_CHASE, FALSE);

				break;
			}
			////////////////////////////////////////
			case CAMERA_MODE_WEAPON_EXPLOSION:
			////////////////////////////////////////
			{
				set_camera_mode (raw, CAMERA_MODE_CHASE, FALSE);

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
					set_camera_mode (raw, CAMERA_MODE_CHASE, FALSE);
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
					set_camera_mode (raw, CAMERA_MODE_CHASE, FALSE);
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
					set_camera_mode (raw, CAMERA_MODE_CHASE, FALSE);
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
					set_camera_mode (raw, CAMERA_MODE_CHASE, FALSE);
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
					set_camera_mode (raw, CAMERA_MODE_CHASE, FALSE);
				}

				break;
			}
			////////////////////////////////////////
			case CAMERA_MODE_FREE:
			////////////////////////////////////////
			{
				set_camera_mode (raw, CAMERA_MODE_FREE, FALSE);

				break;
			}
			////////////////////////////////////////
			default:
			////////////////////////////////////////
			{
				debug_fatal ("Invalid camera mode = %d", raw->camera_mode);

				break;
			}
		}

		reset_cinematic_camera_for_new_view_entity (raw);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_external_view_entity (entity *en)
{
	ASSERT (en);

	set_raw_external_view_entity (en);

	set_view_menu_to_match_external_view_entity ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *get_external_view_entity (void)
{
	entity
		*en;

	if (get_camera_entity ())
	{
		en = (entity *) get_local_entity_ptr_value (get_camera_entity (), PTR_TYPE_EXTERNAL_VIEW_ENTITY);
	}
	else
	{
		en = NULL;
	}

	return (en);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
