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

static int sprite_light_valid (entity *en);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void draw_local_3d_object (entity *en, float range)
{
	fixed_wing
		*raw;

	day_segment_types
		day_segment_type;

	raw = get_local_entity_data (en);

	//
	// update viewpoint
	//

	raw->ac.inst3d->vp.position = raw->ac.mob.position;

	memcpy (&raw->ac.inst3d->vp.attitude, &raw->ac.mob.attitude, sizeof (matrix3x3));

	//
	// animate
	//

	animate_fixed_wing_afterburners (en);

	animate_fixed_wing_airbrakes (en);
	
	animate_fixed_wing_flaps (en);

	animate_fixed_wing_propellors (en);
	
	animate_aircraft_loading_doors (en);

	animate_aircraft_cargo_doors (en);

	animate_aircraft_undercarriage (en);

	animate_aircraft_weapon_system_ready (en);

	animate_aircraft_shadow (en);

	animate_aircraft_rudder (en);

	//
	// draw
	//

	day_segment_type = get_local_entity_int_value (get_session_entity (), INT_TYPE_DAY_SEGMENT_TYPE);

	raw->ac.inst3d->object_internal_lighting = ((day_segment_type == DAY_SEGMENT_TYPE_NIGHT) || (day_segment_type == DAY_SEGMENT_TYPE_DUSK));

	raw->ac.inst3d->object_sprite_lights = (raw->ac.inst3d->object_internal_lighting && sprite_light_valid (en));

	animate_and_draw_entity_muzzle_flash_effect (en);

	insert_object_into_3d_scene (OBJECT_3D_DRAW_TYPE_OBJECT, raw->ac.inst3d);

	#if DEBUG_MODULE

	if (en == get_external_view_entity ())
	{
		vec3d
			*pos,
			wp_pos;

		draw_mobile_entity_debug_info (en);

		if (get_local_entity_primary_task (en))
		{
			fixed_wing_movement_get_waypoint_position (en, &wp_pos);
	
			pos = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION);
	
			create_debug_3d_line (pos, &wp_pos, sys_col_dark_green, 0.0);
		}
	}
	
	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_fixed_wing_draw_functions (void)
{
	fn_draw_local_entity_3d_object[ENTITY_TYPE_FIXED_WING]	= draw_local_3d_object;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void update_fixed_wing_sprite_light_timers (void)
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
