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

#define DEBUG_MODULE	0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_routed_vehicle_weapon_fire (entity *en)
{
   routed_vehicle
      *raw;

	int
		continue_burst_fire;

	float
		launch_angle_error;

	vec3d
		*weapon_vector,
		*weapon_to_target_vector;

	ASSERT (en);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

   raw = get_local_entity_data (en);

	//
	// check valid selected weapon
	//

	if (raw->vh.selected_weapon == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
	{
		raw->vh.weapon_burst_timer = 0.0;

		return;
	}

	//
	// check selected weapon is ready
	//

	if (!raw->vh.selected_weapon_system_ready)
	{
		if (raw->vh.weapon_burst_timer > 0.0)
		{
			pause_client_server_continuous_weapon_sound_effect (en, raw->vh.selected_weapon);
		}

		return;
	}

	//
	// check valid target
	//

	if (!raw->vh.mob.target_link.parent)
	{
		if (raw->vh.weapon_burst_timer > 0.0)
		{
			pause_client_server_continuous_weapon_sound_effect (en, raw->vh.selected_weapon);
		}

		return;
	}

	//
	// check within max launch angle error
	//

	if (!get_local_entity_int_value (en, INT_TYPE_WEAPON_AND_TARGET_VECTORS_VALID))
	{
		if (raw->vh.weapon_burst_timer > 0.0)
		{
			pause_client_server_continuous_weapon_sound_effect (en, raw->vh.selected_weapon);
		}

		return;
	}

	weapon_vector = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_WEAPON_VECTOR);

	ASSERT (weapon_vector);

	weapon_to_target_vector = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_WEAPON_TO_TARGET_VECTOR);

	ASSERT (weapon_to_target_vector);

	launch_angle_error = acos (get_3d_unit_vector_dot_product (weapon_vector, weapon_to_target_vector));

	if (fabs (launch_angle_error) > weapon_database[raw->vh.selected_weapon].max_launch_angle_error)
	{
		if (raw->vh.weapon_burst_timer > 0.0)
		{
			pause_client_server_continuous_weapon_sound_effect (en, raw->vh.selected_weapon);
		}

		return;
	}

	//
	// update burst
	//

	continue_burst_fire = FALSE;

	if (raw->vh.weapon_burst_timer > 0.0)
	{
		raw->vh.weapon_burst_timer -= get_delta_time ();

		if (raw->vh.weapon_burst_timer > 0.0)
		{
			continue_burst_fire = TRUE;
		}
		else
		{
			pause_client_server_continuous_weapon_sound_effect (en, raw->vh.selected_weapon);
		}
	}

	//
	// fire weapon
	//

	if (raw->vh.ready_to_fire || continue_burst_fire)
	{
		if (!get_local_entity_int_value (get_session_entity (), INT_TYPE_SUPPRESS_AI_FIRE))
		{
			launch_client_server_weapon (en, raw->vh.selected_weapon);
		}

		/////////////////////////////////////////////////////////////////
		//
		// SPECIAL_EFFECT_HOOK FOR LAUNCHING WEAPON
		//
		/////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////
		//
		//
		//
		/////////////////////////////////////////////////////////////////
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
