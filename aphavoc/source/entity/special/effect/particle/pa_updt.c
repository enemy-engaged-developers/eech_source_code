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

static int update_particle( entity *en );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_server (entity *en)
{
	if ( !update_particle( en ) )
	{
		destroy_client_server_entity_family( en );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_client (entity *en)
{
	update_particle( en );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int update_particle( entity *en )
{

	particle
		*raw;

	int
		alive_count,
		loop;

	float
		dt,
		dh,
		dp,
		dr;

	vec3d
		*pos,
		*mv;
		
	entity
		*next,
		*special_effect;

	matrix3x3
		m,
		rotation_matrix;

	raw = (particle *) get_local_entity_data (en);

	//
	// get special effect root - list of all smoke trails attached to the particles
	//

	special_effect = get_local_entity_first_child (en, LIST_TYPE_SPECIAL_EFFECT);

	dt = get_delta_time();

	dh = (PI) * dt;
	dr = (PI * 0.5) * dt;
	dp = (PI * 0.25) * dt;

	alive_count = 0;
	
	for ( loop = 0 ; loop < raw->particle_count ; loop ++ )
	{
		if ( !( raw->valid[ loop ] ) )
		{
			continue;
		}

		alive_count ++;

		pos = &(raw->position[ loop ]);

		mv = &(raw->motion_vector[ loop ]);

		//
		// update position
		//

		pos->x += mv->x * dt;
		pos->y += mv->y * dt;
		pos->z += mv->z * dt;

		bound_position_to_map_volume( pos );

		//
		// update motion vector
		//

		mv->y -= G * dt;

		//
		// update attitude
		//

		if (raw->inst3d [loop])
		{
			memcpy (m, raw->inst3d [loop]->vp.attitude, sizeof (matrix3x3));

			get_3d_transformation_matrix_fast (rotation_matrix, dh, dp, dr);

			multiply_matrix3x3_matrix3x3 (raw->inst3d [loop]->vp.attitude, m, rotation_matrix);
		}

		//
		//
		//
				
		if ( special_effect )
		{
			//
			// next trail
			//
	
			next = get_local_entity_child_succ( special_effect, LIST_TYPE_SPECIAL_EFFECT );
		}

		//
		// check if position is below ground / out of bounds
		//

		if ( ( !point_inside_map_area( pos ) ) ||
				( !point_above_ground( pos ) ) ||
				( !point_below_ceiling( pos ) ) )
		{

			if ( special_effect )
			{
				//
				// remove smoke from list
				//

				delete_local_entity_from_parents_child_list (special_effect, LIST_TYPE_SPECIAL_EFFECT);
			}

			raw->valid[ loop ] = FALSE;

			if (raw->inst3d [loop])
			{
				destruct_3d_object (raw->inst3d [loop]);
				
				raw->inst3d [loop] = NULL;
			}

			pos->y = 0.0;		// bound height above ground, otherwise an error will occur when trying to pack the position

			#if DEBUG_MODULE
	
			debug_log("PARTICLE : Particle %d expired", loop );

			#endif

		}
		else
		{
			//
			// notify smoke trail of new position
			//
	
			if ( special_effect )
			{
				notify_local_entity( ENTITY_MESSAGE_SET_ENTITY_POSITION, special_effect, en, pos, 0.0, 0.0 );
			}
		}

		if ( special_effect )
		{
			special_effect = next;
		}
	}

	//
	// if all particles have expired ( i.e. alive_count == 0 ) then destroy the particle entity
	//

	if ( alive_count == 0 )
	{
		#if DEBUG_MODULE

		debug_log("PARTICLE : All particles expired - destroy entity");

		#endif

		return FALSE;
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_particle_update_functions (void)
{
	fn_update_client_server_entity[ENTITY_TYPE_PARTICLE][COMMS_MODEL_SERVER]  	= update_server;

	fn_update_client_server_entity[ENTITY_TYPE_PARTICLE][COMMS_MODEL_CLIENT]  	= update_client;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
