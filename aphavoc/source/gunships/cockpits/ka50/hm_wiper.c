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

static object_3d_instance
	*virtual_cockpit_wiper_arm_inst3d,
	*virtual_cockpit_wiper_rod_inst3d,
	*virtual_cockpit_large_hud_wiper_arm_inst3d,
	*virtual_cockpit_large_hud_wiper_rod_inst3d,
	*virtual_cockpit_rain_effect_inst3d,
	*virtual_cockpit_large_hud_rain_effect_inst3d;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_ka50_virtual_cockpit_wiper_and_rain_effect (void)
{
	virtual_cockpit_wiper_arm_inst3d = construct_3d_object (OBJECT_3D_HAVOC_VIRTUAL_COCKPIT_WIPER_ARM);

	virtual_cockpit_wiper_rod_inst3d = construct_3d_object (OBJECT_3D_HAVOC_VIRTUAL_COCKPIT_WIPER_ROD);

	virtual_cockpit_large_hud_wiper_arm_inst3d = construct_3d_object (OBJECT_3D_HAVOC_VIRTUAL_COCKPIT_WIPER_ARM_HUD);

	virtual_cockpit_large_hud_wiper_rod_inst3d = construct_3d_object (OBJECT_3D_HAVOC_VIRTUAL_COCKPIT_WIPER_ROD_HUD);

	virtual_cockpit_rain_effect_inst3d = construct_3d_object (OBJECT_3D_HAVOC_VIRTUAL_COCKPIT_GLASS);

	virtual_cockpit_large_hud_rain_effect_inst3d = construct_3d_object (OBJECT_3D_HAVOC_VIRTUAL_COCKPIT_GLASS_HUD);

	pilot_wiper = TRUE;

	pilot_wiped_rain_texture_screen = create_screen_for_system_texture (TEXTURE_INDEX_HAVOC_PILOT_RAIN_WIPE);

	pilot_wipe_type = WIPE_TYPE_LEFT_THEN_RIGHT;

	co_pilot_wiper = FALSE;

	co_pilot_wiped_rain_texture_screen = NULL;

	co_pilot_wipe_type = WIPE_TYPE_INVALID;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_ka50_virtual_cockpit_wiper_and_rain_effect (void)
{
	destruct_3d_object (virtual_cockpit_wiper_arm_inst3d);

	destruct_3d_object (virtual_cockpit_wiper_rod_inst3d);

	destruct_3d_object (virtual_cockpit_large_hud_wiper_arm_inst3d);

	destruct_3d_object (virtual_cockpit_large_hud_wiper_rod_inst3d);

	destruct_3d_object (virtual_cockpit_rain_effect_inst3d);

	destruct_3d_object (virtual_cockpit_large_hud_rain_effect_inst3d);

	destroy_screen (pilot_wiped_rain_texture_screen);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_ka50_virtual_cockpit_wiper (viewpoint *vp, int large_hud)
{
	object_3d_instance
		*wiper_arm_inst3d,
		*wiper_rod_inst3d;

	object_3d_sub_object_search_data
		search;

	ASSERT (vp);

	if (large_hud)
	{
		wiper_arm_inst3d = virtual_cockpit_large_hud_wiper_arm_inst3d;
		wiper_rod_inst3d = virtual_cockpit_large_hud_wiper_rod_inst3d;
	}
	else
	{
		wiper_arm_inst3d = virtual_cockpit_wiper_arm_inst3d;
		wiper_rod_inst3d = virtual_cockpit_wiper_rod_inst3d;
	}

	//
	// rotate wiper arm
	//

	search.search_depth = 0;
	search.search_object = wiper_arm_inst3d;
	search.sub_object_index = OBJECT_3D_SUB_OBJECT_HAVOC_VIRTUAL_COCKPIT_WIPER_ARM;

	if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		search.result_sub_object->relative_roll = wiper_position * (rad (65.3756) / MAX_WIPER_POSITION);
	}

	//
	// rotate wiper blade
	//

	search.search_depth = 0;
	search.search_object = wiper_arm_inst3d;
	search.sub_object_index = OBJECT_3D_SUB_OBJECT_HAVOC_VIRTUAL_COCKPIT_WIPER_BLADE;

	if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		search.result_sub_object->relative_roll = (wiper_position * (rad (-74.7756) / MAX_WIPER_POSITION)) + rad (4.7);
	}

	//
	// rotate wiper rod
	//

	search.search_depth = 0;
	search.search_object = wiper_rod_inst3d;
	search.sub_object_index = OBJECT_3D_SUB_OBJECT_HAVOC_VIRTUAL_COCKPIT_WIPER_ROD;

	if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		search.result_sub_object->relative_roll = wiper_position * (rad (65.3756) / MAX_WIPER_POSITION);
	}

	//
	// draw wiper arm and blade
	//

	memcpy (&wiper_arm_inst3d->vp, vp, sizeof (viewpoint));

	insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &wiper_arm_inst3d->vp.position, wiper_arm_inst3d);

	//
	// draw wiper rod
	//

	memcpy (&wiper_rod_inst3d->vp, vp, sizeof (viewpoint));

	insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &wiper_rod_inst3d->vp.position, wiper_rod_inst3d);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void draw_ka50_virtual_cockpit_rain_effect (viewpoint *vp, int large_hud)
{
	ASSERT (vp);

	if (get_global_graphics_rain_textures_enabled ())
	{
		if (large_hud)
		{
			memcpy (&virtual_cockpit_large_hud_rain_effect_inst3d->vp, vp, sizeof (viewpoint));

			insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_large_hud_rain_effect_inst3d->vp.position, virtual_cockpit_large_hud_rain_effect_inst3d);
		}
		else
		{
			memcpy (&virtual_cockpit_rain_effect_inst3d->vp, vp, sizeof (viewpoint));

			insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &virtual_cockpit_rain_effect_inst3d->vp.position, virtual_cockpit_rain_effect_inst3d);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void animate_ka50_external_wipers (object_3d_instance *inst3d)
{
	object_3d_sub_object_search_data
		search;

	////////////////////////////////////////
	//
	// pilot's wipers
	//
	////////////////////////////////////////

	search.search_depth = 0;
	search.search_object = inst3d;
	search.sub_object_index = OBJECT_3D_SUB_OBJECT_WIPER_ARM_PILOT;

	if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		search.result_sub_object->relative_roll = wiper_position * (rad (65.3756) / MAX_WIPER_POSITION);
	}

	search.search_depth = 0;
	search.search_object = inst3d;
	search.sub_object_index = OBJECT_3D_SUB_OBJECT_WIPER_BLADE_PILOT;

	if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		search.result_sub_object->relative_roll = (wiper_position * (rad (-74.7756) / MAX_WIPER_POSITION)) + rad (4.7);
	}

	////////////////////////////////////////
	//
	// co-pilot's wipers
	//
	////////////////////////////////////////

	search.search_depth = 0;
	search.search_object = inst3d;
	search.sub_object_index = OBJECT_3D_SUB_OBJECT_WIPER_ARM_COPILOT;

	if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		search.result_sub_object->relative_roll = wiper_position * (rad (90.0) / MAX_WIPER_POSITION);
	}

	search.search_depth = 0;
	search.search_object = inst3d;
	search.sub_object_index = OBJECT_3D_SUB_OBJECT_WIPER_BLADE_COPILOT;

	if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
	{
		search.result_sub_object->relative_roll = (wiper_position * (rad (-100.0) / MAX_WIPER_POSITION)) + rad (5.0);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
