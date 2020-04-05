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

void smoke_list_movement( entity *en )
{
	smoke_list
		*raw = nullptr;
		
	float
		dt,
		vertical_acceleration,
		desired_vertical_velocity,
		delta_speed;

	vec3d
		*smoke_pos = nullptr,
		*smoke_mv = nullptr,
		wind_velocity;

	int
		current,
		loop,
		number_of_slots;

	smoke_list_data
		*smoke_info = nullptr;

	raw = (smoke_list *) get_local_entity_data (en);

	smoke_info = &(smoke_list_database[ raw->smoke_type ]);

	dt = get_delta_time();

	//
	// calculate wind velocity
	//

//	wind_velocity = get_local_entity_vec3d_ptr( get_session_entity(), VEC3D_TYPE_WIND_VELOCITY );
	get_session_wind_velocity_at_point (get_local_entity_vec3d_ptr (en, VEC3D_TYPE_POSITION), &wind_velocity);

	vertical_acceleration = smoke_list_vertical_acceleration( raw->smoke_type );
	desired_vertical_velocity = smoke_list_final_vertical_velocity( raw->smoke_type );

	number_of_slots = raw->smoke_lifetime / raw->frequency;

	current = raw->head;

	for ( loop = 0 ; loop < number_of_slots ; loop ++ )
	{
		current --;

		if ( current < 0 )
		{
			current = number_of_slots - 1;
		}

		if ( !raw->valid[ current ] )
		{
			continue;
		}

		smoke_pos = &(raw->position[ current ]);

		smoke_mv = &(raw->motion_vector[ current ]);

		//
		// update position
		//

		smoke_pos->x += smoke_mv->x * dt;
		smoke_pos->y += smoke_mv->y * dt;
		smoke_pos->z += smoke_mv->z * dt;
/*
		smoke_pos->x = bound (smoke_pos->x, MIN_MAP_X, MAX_MAP_X);
		smoke_pos->y = bound (smoke_pos->y, MIN_MAP_Y, MAX_MAP_Y);
		smoke_pos->z = bound (smoke_pos->z, MIN_MAP_Z, MAX_MAP_Z);
*/
		//
		// update motion vector
		//

		if ( smoke_info->wind_affected && !bound_position_to_map_volume(smoke_pos))
		{
			float alt_modifier;
			
			ASSERT(point_inside_map_area(smoke_pos));
	
			alt_modifier = bound((smoke_pos->y - get_3d_terrain_elevation(smoke_pos->x, smoke_pos->z)) / 100, 0.5, 4); // increase wind force at high altitude, decrease at low
			smoke_mv->x += ( smoke_info->wind_affected * alt_modifier * ( wind_velocity.x + ( wind_velocity.x * sfrand1() * 0.5 ) ) - smoke_mv->x ) * dt;
			smoke_mv->z += ( smoke_info->wind_affected * alt_modifier * ( wind_velocity.z + ( wind_velocity.z * sfrand1() * 0.5 ) ) - smoke_mv->z ) * dt;
		}

		delta_speed = ( desired_vertical_velocity - smoke_mv->y );

		delta_speed = bound( delta_speed, -vertical_acceleration, vertical_acceleration );
		
		smoke_mv->y += ( delta_speed * dt );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


