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

#define DEBUG_3D_OBJECT_SOUND_RANGE		(5000.0)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static float
	max_3d_object_sound_range;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void scan_local_entity_sounds (viewpoint *vp)
{

	int
		x_sec_min,
		z_sec_min,
		x_sec_max,
		z_sec_max,
		x_sec,
		z_sec;

	entity
		*sctr,
		*en,
		*parent;

	vec3d
		scan_origin,
		*position;

	float
		range,
		max_range;

	struct SYSTEM_SOUND_EFFECT
		*snd_eff;

	ASSERT (vp);

	if (!get_application_sound_system_status ())
	{
		return;
	}

	if (get_sound_system_paused ())
	{
		return;
	}

	// Casm 07DEC09 OpenAL support
	set_system_sound_listener_orientation ( vp->zv, vp->yv, vp->zv );

	//
	// update playing samples
	//

	update_system_sound_effect_system ();

	//
	// play session sound effects
	//
			
	en = get_local_entity_first_child (get_session_entity (), LIST_TYPE_SPECIAL_EFFECT);

	while (en)
	{
		play_local_entity_sound (en, vp, 0.0);

		en = get_local_entity_child_succ (en, LIST_TYPE_SPECIAL_EFFECT);
	}

	//
	// play local sound effects
	//

	scan_origin = vp->position;

	bound_position_to_map_area (&scan_origin);

	get_x_sector (x_sec_min, scan_origin.x - max_3d_object_sound_range);
	get_z_sector (z_sec_min, scan_origin.z - max_3d_object_sound_range);

	get_x_sector (x_sec_max, scan_origin.x + max_3d_object_sound_range);
	get_z_sector (z_sec_max, scan_origin.z + max_3d_object_sound_range);

	x_sec_min = max (x_sec_min, MIN_MAP_X_SECTOR);
	z_sec_min = max (z_sec_min, MIN_MAP_Z_SECTOR);

	x_sec_max = min (x_sec_max, MAX_MAP_X_SECTOR);
	z_sec_max = min (z_sec_max, MAX_MAP_Z_SECTOR);

	//
	// Scan for valid sound effects
	//

	for (z_sec = z_sec_min; z_sec <= z_sec_max; z_sec++)
	{

		for (x_sec = x_sec_min; x_sec <= x_sec_max; x_sec++)
		{

			sctr = get_local_raw_sector_entity (x_sec, z_sec);

			//
			// play sound effects in the sector
			//
			
			en = get_local_entity_first_child (sctr, LIST_TYPE_SPECIAL_EFFECT);

			while (en)
			{
				position = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);

				range = get_approx_3d_range (&vp->position, position);

				max_range = DEBUG_3D_OBJECT_SOUND_RANGE;

				if (range < max_range)
				{
					play_local_entity_sound (en, vp, range);
				}

				en = get_local_entity_child_succ (en, LIST_TYPE_SPECIAL_EFFECT);
			}

			//
			// play sound effects attached to other entities in the sector
			//
			
			parent = get_local_entity_first_child (sctr, LIST_TYPE_SECTOR);

			while (parent)
			{
				if (get_local_entity_int_value (parent, INT_TYPE_SOUND_LIST_VALID))
				{
					position = get_local_entity_vec3d_ptr (parent, VEC3D_TYPE_POSITION);
	
					range = get_approx_3d_range (&vp->position, position);
	
					max_range = DEBUG_3D_OBJECT_SOUND_RANGE;
	
					if (range < max_range)
					{
						en = get_local_entity_first_child (parent, LIST_TYPE_SPECIAL_EFFECT);
	
						while (en)
						{
							if (get_local_entity_type (en) == ENTITY_TYPE_SOUND_EFFECT)
							{
								play_local_entity_sound (en, vp, range);
							}
	
							en = get_local_entity_child_succ (en, LIST_TYPE_SPECIAL_EFFECT);
						}
					}
				}

				parent = get_local_entity_child_succ (parent, LIST_TYPE_SECTOR);
			}
		}
	}

	//
	// Update playing sound effects
	//

	snd_eff = get_first_system_sound_effect ();

	while (snd_eff)
	{

		en = (entity *) get_system_sound_effect_user_data (snd_eff);

		if (!get_system_sound_effect_playing (snd_eff))
		{
			#if DEBUG_MODULE

			debug_log ("EN_SND : destroying sound coz it's not being played");

			#endif

			destroy_system_sound_effect (snd_eff);

			if (en)
			{

				set_local_entity_ptr_value (en, PTR_TYPE_SOUND_EFFECT_DATA, NULL);
			}
		}
		else if (en)
		{
			if (get_local_entity_parent (en, LIST_TYPE_SPECIAL_EFFECT) != get_session_entity ())
			{
				position = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);
	
				range = get_approx_3d_range (&vp->position, position);
	
				max_range = 5000;
	
				if (range > max_range)
				{
	
					#if DEBUG_MODULE
	
					debug_log ("EN_SND: destroying sound effect (too far away)");
	
					#endif
	
					destroy_system_sound_effect (snd_eff);
	
					set_local_entity_ptr_value (en, PTR_TYPE_SOUND_EFFECT_DATA, NULL);
				}
			}
		}

		snd_eff = get_next_system_sound_effect (snd_eff);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stop_local_entity_sounds ()
{
	struct SYSTEM_SOUND_EFFECT
		*snd_eff;

	entity
		*en;

	//
	// stop all sounds (not in the 3d visual)
	//

	snd_eff = get_first_system_sound_effect ();

	while (snd_eff)
	{

		en = (entity *) get_system_sound_effect_user_data (snd_eff);

		if (en)
		{
			destroy_system_sound_effect (snd_eff);

			set_local_entity_ptr_value (en, PTR_TYPE_SOUND_EFFECT_DATA, NULL);
		}

		snd_eff = get_next_system_sound_effect (snd_eff);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void (*fn_play_local_entity_sound[NUM_ENTITY_TYPES]) (entity *en, viewpoint *vp, float range);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void default_play_entity_sound (entity *en, viewpoint *vp, float range)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_entity_sound_default_functions (void)
{

	int
		i;

	max_3d_object_sound_range = DEBUG_3D_OBJECT_SOUND_RANGE;

	for (i = 0; i < NUM_ENTITY_TYPES; i++)
	{

		fn_play_local_entity_sound[i]	= default_play_entity_sound;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
