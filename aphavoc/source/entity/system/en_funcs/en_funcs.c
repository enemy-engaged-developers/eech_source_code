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

void initialise_entity_functions (void)
{
	//
	// set default functions
	//

	initialise_entity_attitude_default_functions ();

	initialise_entity_char_value_default_functions ();

	initialise_entity_create_default_functions ();

	initialise_entity_draw_default_functions ();

	initialise_entity_destroy_default_functions ();

	initialise_entity_float_value_default_functions ();

	initialise_entity_int_value_default_functions ();

	initialise_entity_pack_default_functions ();

	initialise_entity_ptr_value_default_functions ();

	initialise_entity_list_default_functions ();

	initialise_entity_sound_default_functions ();

	initialise_entity_string_default_functions ();

	initialise_entity_update_default_functions ();

	initialise_entity_vec3d_default_functions ();

	//
	// overload default functions
	//

	overload_anti_aircraft_functions ();

	overload_bridge_functions ();

	overload_camera_functions ();

	overload_cargo_functions ();

	overload_city_functions ();

	overload_city_building_functions ();

	overload_crater_functions ();

	overload_division_functions ();

	overload_explosion_functions ();

	overload_fixed_wing_functions ();

	overload_force_functions ();

	overload_group_functions ();

	overload_guide_functions ();

	overload_helicopter_functions ();

	overload_keysite_functions ();

	overload_landing_functions ();

	overload_object_functions ();

	overload_particle_functions ();

	overload_person_functions ();

	overload_pilot_functions ();

	overload_pylon_functions ();

	overload_regen_functions ();

	overload_routed_vehicle_functions ();

	overload_sector_functions ();

	overload_segment_functions ();

	overload_session_functions ();

	overload_scenic_functions ();

	overload_ship_vehicle_functions ();

	overload_site_functions ();

	overload_site_updatable_functions ();

	overload_smoke_list_functions ();

	overload_sound_effect_functions ();

	overload_sprite_functions ();

	overload_task_functions ();

	overload_update_functions ();

	overload_waypoint_functions ();

	overload_weapon_functions ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
