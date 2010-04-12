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

/*
void update_helicopter_target_scan (entity *en)
{
	helicopter
		*raw;

	entity
		*force,
		*target;

	ASSERT (en);

	ASSERT (get_comms_model () == COMMS_MODEL_SERVER);

   raw = get_local_entity_data (en);

	target = NULL;

	raw->ac.ready_to_fire = FALSE;

	//
	// aircraft must be armed
	//

	if (aircraft_database[raw->ac.mob.sub_type].default_weapon_type == ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
	{
		return;
	}

	//
	//
	//

	if (raw->ac.selected_weapon != ENTITY_SUB_TYPE_WEAPON_NO_WEAPON)
	{
		raw->ac.target_scan_timer -= get_delta_time ();

		if (raw->ac.target_scan_timer < 0.0)
		{
			//
			// reset target_scan_timer (okay to use a random number as this is a server only variable)
			//

			raw->ac.target_scan_timer = aircraft_database[raw->ac.mob.sub_type].target_scan_delay * ((frand1 () + 1.0) * 0.5);

			//
			// scan for target
			//

			//DEBUG//
			if (weapon_database[raw->ac.selected_weapon].weapon_class & WEAPON_CLASS_AIR_TO_AIR)
			{
				target = get_aircraft_air_to_air_scan_target (en);
			}
			else if (weapon_database[raw->ac.selected_weapon].weapon_class & WEAPON_CLASS_AIR_TO_SURFACE)
			{
				target = get_aircraft_air_to_surface_scan_target (en);
			}
			//DEBUG//

			//
			// set target if different to current target
			//

			if (target != get_local_entity_parent (en, LIST_TYPE_TARGET))
			{
				set_client_server_entity_parent (en, LIST_TYPE_TARGET, target);

				force = get_local_force_entity (raw->ac.mob.side);

				notify_local_entity (ENTITY_MESSAGE_FORCE_ALLIED_TARGET, force, en, target);
			}

			if (target)
			{
				raw->ac.ready_to_fire = TRUE;
			}
		}
	}
	else
	{
		//
		// if no selected weapon then lose target (if any)
		//

		if (target != get_local_entity_parent (en, LIST_TYPE_TARGET))
		{
			set_client_server_entity_parent (en, LIST_TYPE_TARGET, target);

			force = get_local_force_entity (raw->ac.mob.side);

			notify_local_entity (ENTITY_MESSAGE_FORCE_ALLIED_TARGET, force, en, target);
		}
	}
}
*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
