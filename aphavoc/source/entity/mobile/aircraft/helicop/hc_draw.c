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

static float
	sprite_light_timer = 0.0;

#define SPRITE_LIGHT_TIMER_FREQUENCY 0.5

#define SPRITE_LIGHT_ON_THRESHOLD 0.1

static int object_internal_lighting_valid (entity *en);

static int sprite_light_valid (entity *en);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_local_3d_object (entity *en, float range)
{
	helicopter
		*raw;

	int
		internal_view;

	raw = get_local_entity_data (en);

	//
	// the player's gunship is visible from the menus - where the in_cockpit flag is invalid
	//

	if (en == get_gunship_entity ())
	{
		internal_view = ((in_cockpit) && (get_in_flight_game_mode () == IN_FLIGHT_GAME_MODE_SIMULATOR));
	}
	else
	{
		internal_view = FALSE;
	}

	////////////////////////////////////////
	//
	// SORT COMANCHE AND HOKUM INSTANCES
	//
	// It is necessary to switch parts on and off for all Comanche and Hokum instances
	// because the player can change gunship so the instances need to be fixed up.
	//
	////////////////////////////////////////

	{
		int
			draw_virtual_cockpit_parts,
			draw_canopy_doors,
			draw_loading_doors,
			ejected;

		object_3d_sub_object_search_data
			search;

		if (raw->ac.object_3d_shape == OBJECT_3D_RAH66)
		{
			////////////////////////////////////////
			//
			// Comanche
			//
			////////////////////////////////////////

			//
			// draw 'canopy' doors on player object and 'loading' doors on AI object
			//

			draw_virtual_cockpit_parts = FALSE;

			draw_canopy_doors = FALSE;

			draw_loading_doors = FALSE;

			if (en == get_gunship_entity ())
			{
				draw_canopy_doors = TRUE;

				if (!internal_view)
				{
					draw_virtual_cockpit_parts = TRUE;
				}
			}
			else
			{
				draw_loading_doors = TRUE;
			}

			//
			// fuselage
			//

			search.search_depth = 0;
			search.search_object = raw->ac.inst3d;
			search.sub_object_index = OBJECT_3D_SUB_OBJECT_RAH66_FUSELAGE;

			if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
			{
				// search.result_sub_object->visible_object = !draw_virtual_cockpit_parts; Jabberwock 031016 Inset view
			}

			//
			// canopy/loading doors
			//

			search.search_depth = 0;
			search.search_object = raw->ac.inst3d;
			search.sub_object_index = OBJECT_3D_SUB_OBJECT_CANOPY_DOORS;

			if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
			{
				search.result_sub_object->visible_object = draw_canopy_doors;
			}

			search.search_depth = 1;
			search.search_object = raw->ac.inst3d;
			search.sub_object_index = OBJECT_3D_SUB_OBJECT_CANOPY_DOORS;

			if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
			{
				search.result_sub_object->visible_object = draw_canopy_doors;
			}

			search.search_depth = 0;
			search.search_object = raw->ac.inst3d;
			search.sub_object_index = OBJECT_3D_SUB_OBJECT_LOADING_DOOR;

			if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
			{
				search.result_sub_object->visible_object = draw_loading_doors;
			}

			search.search_depth = 1;
			search.search_object = raw->ac.inst3d;
			search.sub_object_index = OBJECT_3D_SUB_OBJECT_LOADING_DOOR;

			if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
			{
				search.result_sub_object->visible_object = draw_loading_doors;
			}
		}
		else if (raw->ac.object_3d_shape == OBJECT_3D_KA_52)
		{
			////////////////////////////////////////
			//
			// Hokum
			//
			////////////////////////////////////////

			//
			// draw 'canopy' doors on player object and 'loading' doors on AI object
			//

			ejected = get_local_entity_int_value (en, INT_TYPE_EJECTED);

			draw_virtual_cockpit_parts = FALSE;

			draw_canopy_doors = FALSE;

			draw_loading_doors = FALSE;

			if (en == get_gunship_entity ())
			{
				if (!ejected)
				{
					draw_canopy_doors = TRUE;
				}

				if (internal_view)
				{
					draw_virtual_cockpit_parts = TRUE;
				}
			}
			else
			{
				if (!ejected)
				{
					draw_loading_doors = TRUE;
				}
			}

			//
			// stub wings
			//

			search.search_depth = 0;
			search.search_object = raw->ac.inst3d;
			search.sub_object_index = OBJECT_3D_SUB_OBJECT_KA52_WINGS;

			if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
			{
				// search.result_sub_object->visible_object = draw_virtual_cockpit_parts; Jabberwock 031016 Inset view
			}

			//
			// fuselage
			//

			search.search_depth = 0;
			search.search_object = raw->ac.inst3d;
			search.sub_object_index = OBJECT_3D_SUB_OBJECT_KA52_FUSELAGE;

			if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
			{
				// search.result_sub_object->visible_object = !draw_virtual_cockpit_parts; Jabberwock 031016 Inset view
			}

			//
			// canopy/loading doors
			//

			search.search_depth = 0;
			search.search_object = raw->ac.inst3d;
			search.sub_object_index = OBJECT_3D_SUB_OBJECT_CANOPY_DOORS;

			if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
			{
				search.result_sub_object->visible_object = draw_canopy_doors;
			}

			search.search_depth = 1;
			search.search_object = raw->ac.inst3d;
			search.sub_object_index = OBJECT_3D_SUB_OBJECT_CANOPY_DOORS;

			if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
			{
				search.result_sub_object->visible_object = draw_canopy_doors;
			}

			search.search_depth = 0;
			search.search_object = raw->ac.inst3d;
			search.sub_object_index = OBJECT_3D_SUB_OBJECT_LOADING_DOOR;

			if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
			{
				search.result_sub_object->visible_object = draw_loading_doors;
			}

			search.search_depth = 1;
			search.search_object = raw->ac.inst3d;
			search.sub_object_index = OBJECT_3D_SUB_OBJECT_LOADING_DOOR;

			if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
			{
				search.result_sub_object->visible_object = draw_loading_doors;
			}

			//
			// ejector seats & crew
			//

			search.search_depth = 0;
			search.search_object = raw->ac.inst3d;
			search.sub_object_index = OBJECT_3D_SUB_OBJECT_KA52_EJECTOR_SEAT;

			if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
			{
				search.result_sub_object->visible_object = !ejected;
			}

			search.search_depth = 1;
			search.search_object = raw->ac.inst3d;
			search.sub_object_index = OBJECT_3D_SUB_OBJECT_KA52_EJECTOR_SEAT;

			if (find_object_3d_sub_object (&search) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND)
			{
				search.result_sub_object->visible_object = !ejected;
			}
		}
	}

	////////////////////////////////////////

	if (en == get_gunship_entity ())
	{
		//
		// update viewpoint
		//

		raw->ac.inst3d->vp.position = raw->ac.mob.position;

		memcpy (&raw->ac.inst3d->vp.attitude, &raw->ac.mob.attitude, sizeof (matrix3x3));

		//
		// animate
		//

		if (!internal_view)
		{
			if (raw->main_rotor_damaged)
			{
				animate_damaged_helicopter_main_rotors (en, TRUE);
			}
			else
			{
				animate_helicopter_main_rotors (en, TRUE, FALSE);
			}
		}

		animate_helicopter_tail_rotor (en);

		animate_helicopter_wipers (en);

		animate_helicopter_eo (en);

		animate_aircraft_loading_doors (en);

		animate_aircraft_cargo_doors (en);

		animate_aircraft_undercarriage (en);

		animate_aircraft_weapon_system_ready (en);

		animate_aircraft_shadow (en);

		animate_aircraft_rudder (en);

		raw->ac.inst3d->object_internal_lighting = object_internal_lighting_valid (en);

		raw->ac.inst3d->object_sprite_lights = (raw->ac.inst3d->object_internal_lighting && sprite_light_valid (en));

		//
		// draw
		//

		
		if (!internal_view)
		{
			if (!in_flight_invisible_object)
			{
				animate_and_draw_entity_muzzle_flash_effect (en);
			
				insert_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_OBJECT, raw->ac.inst3d);
			}
		}
		else
		{
			if (get_comanche_hokum_gunship ())
			{
				if (get_global_draw_cockpit_graphics ())
				{
					if (!get_global_glass_cockpit ())
					{
						if
						(
							(get_view_mode () == VIEW_MODE_VIRTUAL_COCKPIT_CREW) ||
							(get_global_cockpit_detail_level () == COCKPIT_DETAIL_LEVEL_HIGH)
						)
						{
							animate_and_draw_entity_muzzle_flash_effect (en);

							raw->ac.inst3d->vp.position = virtual_cockpit_inst3d->vp.position;

							memcpy (&raw->ac.inst3d->vp.attitude, &virtual_cockpit_inst3d->vp.attitude, sizeof (matrix3x3));

							insert_relative_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_ZBUFFERED_OBJECT, &raw->ac.inst3d->vp.position, raw->ac.inst3d);
						}
					}
				}
			}
		}
	}
	// else Jabberwock 031016 Inset view
	{
		//
		// update viewpoint
		//

		raw->ac.inst3d->vp.position = raw->ac.mob.position;

		memcpy (&raw->ac.inst3d->vp.attitude, &raw->ac.mob.attitude, sizeof (matrix3x3));

		//
		// animate
		//

		if (get_local_entity_int_value (en, INT_TYPE_ALIVE))
		{
			animate_helicopter_main_rotors (en, FALSE, FALSE);
		}
		else
		{
			animate_damaged_helicopter_main_rotors (en, FALSE);
		}

		animate_helicopter_tail_rotor (en);

		animate_aircraft_loading_doors (en);

		animate_aircraft_cargo_doors (en);

		animate_aircraft_undercarriage (en);

		animate_aircraft_weapon_system_ready (en);

		animate_aircraft_shadow (en);

		animate_and_draw_entity_muzzle_flash_effect (en);

		raw->ac.inst3d->object_internal_lighting = object_internal_lighting_valid (en);

		raw->ac.inst3d->object_sprite_lights = (raw->ac.inst3d->object_internal_lighting && sprite_light_valid (en));

		//
		// draw
		//

		insert_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_OBJECT, raw->ac.inst3d);
	}

	////////////////////////////////////////
	//
	// draw comanche and hokum shadows
	//
	////////////////////////////////////////

	if (raw->ac.object_3d_shape == OBJECT_3D_RAH66)
	{
		object_3d_instance
			*shadow_object;

		shadow_object = construct_temporary_3d_object (OBJECT_3D_RAH66_FUSELAGE, FALSE);

		shadow_object->vp = raw->ac.inst3d->vp;

		insert_object_shadow_into_3d_scene (shadow_object);
	}
	else if (raw->ac.object_3d_shape == OBJECT_3D_KA_52)
	{
		object_3d_instance
			*shadow_object;

		shadow_object = construct_temporary_3d_object (OBJECT_3D_KA_52_FUSELAGE, FALSE);

		shadow_object->vp = raw->ac.inst3d->vp;

		insert_object_shadow_into_3d_scene (shadow_object);
	}

	////////////////////////////////////////

	////////////////////////////////////////
	// Xhit: added for downwash effect. (030328)
	// VJ 030512 changed from no_downbwash to downwash
	////////////////////////////////////////
	if(command_line_downwash)
	{
		draw_downwash_effect(en);
	}
	////////////////////////////////////////

	#if DEBUG_MODULE

	if (en == get_external_view_entity ())
	{
		draw_mobile_entity_debug_info (en);
	}

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_helicopter_draw_functions (void)
{
	fn_draw_local_entity_3d_object[ENTITY_TYPE_HELICOPTER]	= draw_local_3d_object;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int object_internal_lighting_valid (entity *en)
{
	day_segment_types
		day_segment_type;

	if (get_local_entity_int_value (en, INT_TYPE_PLAYER) != ENTITY_PLAYER_AI)
	{
		return (get_local_entity_int_value (en, INT_TYPE_LIGHTS_ON));
	}
	else
	{
		day_segment_type = get_local_entity_int_value (get_session_entity (), INT_TYPE_DAY_SEGMENT_TYPE);

		return ((day_segment_type == DAY_SEGMENT_TYPE_NIGHT) || (day_segment_type == DAY_SEGMENT_TYPE_DUSK));
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_helicopter_sprite_light_timers (void)
{
	sprite_light_timer += (get_delta_time () * SPRITE_LIGHT_TIMER_FREQUENCY);

	if (sprite_light_timer >= 1.0)
	{
		sprite_light_timer = frac (sprite_light_timer);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int sprite_light_valid (entity *en)
{
	int
		integer_offset;

	float
		val,
		float_offset;

	//
	// uses entity index to offset sprite lights so that they are not all flashing in sync on all objects
	//

	integer_offset = get_local_entity_index (en);

	integer_offset = integer_offset & 0x0f;

	float_offset = ((float)integer_offset) * 0.0625;

	val = frac (sprite_light_timer + float_offset);

	return (val < SPRITE_LIGHT_ON_THRESHOLD);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
