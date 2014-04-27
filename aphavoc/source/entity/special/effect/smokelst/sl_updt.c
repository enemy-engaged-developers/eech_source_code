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

static int update_smoke( entity *en );

static void create_new_point( entity *en, vec3d *new_pos, vec3d *initial_velocity, smoke_list_types smoke_type, int number_of_slots );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_server (entity *en)
{
	if ( !update_smoke( en ) )
	{
		destroy_client_server_entity_family( en );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void update_client (entity *en)
{
	//VJ 030508 if downwash 
	if (command_line_downwash)
	{
		//Xhit: if this is a local created entity then it should also be destroyed localy. (030428)
		if ( !update_smoke( en ) && (get_local_entity_index( en ) >= start_of_local_entity_heap))
		{
			destroy_client_server_entity_family( en );
		}
	}
	else
	{
			update_smoke( en );
	}
	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int update_smoke( entity *en )
{
	smoke_list
		*raw;

	vec3d
		*tail_pos,
		*last_pos,
		new_pos,
		interpolated_pos,
		d,
		initial_velocity,
		motion_vector;

	int
		create_loop,
		create_count,
		last_index,
		last_tail,
		number_of_slots,
		number_of_frames,
		draw_last = FALSE;

	smoke_list_types
		smoke_type;

	float
		t,
		distance;

	#if DEBUG_MODULE

//	debug_log ("SL_UPDT: update smoke");

	#endif

	raw = (smoke_list *) get_local_entity_data (en);

	number_of_slots = raw->smoke_lifetime / raw->frequency;

	smoke_type = raw->smoke_type;

	motion_vector.x = motion_vector.y = motion_vector.z = 0;

	//
	// Check if the entity should stop producing more smoke
	//

	if ( raw->generator_lifetime <= 0.0 )
	{
		if ( raw->alive_count == 0 )
		{
			if ( raw->infinite_generator )
			{
				//
				// infinite generator is not generating, and has no active points - so temporarily remove it from the update list
				//

				if (raw->eff.special_effect_link.parent)
				{
					delete_local_entity_from_parents_child_list (en, LIST_TYPE_UPDATE);

					return TRUE;
				}
				else
				{
					return FALSE;
				}
			}
			else
			{
				//
				// The entity is no longer producing smoke, and all the smoke points are inactive - so kill the entity
				//

				#if DEBUG_MODULE

				debug_log ("SMOKE LIST: DESTROYING SMOKE ENTITY");

				#endif

				return FALSE;
			}
		}
	}
	else
	{
		if ( !(raw->infinite_generator) )
		{
			if (get_local_entity_int_value(en, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_GUN_SMOKE && raw->alive_count) // do not create additional smoke puffs for guns /thealx/
				raw->generator_lifetime = - get_delta_time ();
			else
				raw->generator_lifetime -= get_delta_time ();
			
			if (raw->generator_lifetime <= 0.0 && smoke_list_draw_mode( smoke_type ) == SMOKE_DRAW_TYPE_TRAILS) // make sure we got last trail point
				draw_last = TRUE;
		}
	}

	//
	// Create / Destroy individual smoke points
	//

	if ( raw->alive_count == 1 && get_local_entity_int_value(en, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_MISSILE_TRAIL )
		raw->smoke_sleep -= 5 * get_delta_time (); // make second point as soon as possible
	else if (raw->eff.special_effect_link.parent && (smoke_type == SMOKE_LIST_TYPE_FLAME || smoke_type == SMOKE_LIST_TYPE_FIRE || smoke_type == SMOKE_LIST_TYPE_SMALL_FIRE)) // do not create flame for moving object
	{
		float parent_velocity = get_local_entity_float_value(raw->eff.special_effect_link.parent, FLOAT_TYPE_VELOCITY);

		if (parent_velocity < 5)
			raw->smoke_sleep -= get_delta_time ();
	}
	else if (draw_last) // make sure we got last trail point
		raw->smoke_sleep = - get_delta_time();
	else
		raw->smoke_sleep -= get_delta_time ();
	
	create_count = 0;

	while ( raw->smoke_sleep < 0.0 )
	{
		//
		// update timer
		//

		raw->smoke_sleep += raw->frequency;

		create_count ++;

		//
		// move tail regardless of whether there are any points alive ( for the purpose of inf. generators )
		//
		
		last_tail = raw->tail;

		raw->tail ++;

		if ( raw->tail >= number_of_slots )
		{
			raw->tail = 0;
		}

		//
		// Destroy smoke at the tail end
		//

		if ( raw->alive_count > 0 )
		{
			if ( raw->valid[ last_tail ] )
			{
				last_pos = &(raw->position[ last_tail ]);
	
				if ( ( smoke_list_draw_mode( smoke_type ) == SMOKE_DRAW_TYPE_TRAILS ) && ( raw->valid[ raw->tail ] ) )
				{
					//
					// adjust texture distance
					//

					tail_pos = &(raw->position[ raw->tail ]);
					
					raw->texture_distance += get_3d_range( tail_pos, last_pos );
				}
	
				last_pos->x = -1.0;
				last_pos->y = -1.0;
				last_pos->z = -1.0;
		
				raw->valid[ last_tail ] = FALSE;

				raw->alive_count --;
			}
		}	
	}

	if ( ( create_count > 0 ) && ( raw->generator_lifetime > 0.0 || draw_last ) )
	{

		//
		// create more smoke ( if still generating )
		//

		get_new_smoke_position (en, &new_pos);
	
		get_local_entity_vec3d( en, VEC3D_TYPE_INITIAL_VELOCITY, &initial_velocity );

		#if DEBUG_MODULE

		debug_log("SMOKE LIST : creating %d new points", create_count);

		#endif

		
		if (raw->eff.special_effect_link.parent)
		{
			matrix3x3
				attitude;

			get_local_entity_attitude_matrix(raw->eff.special_effect_link.parent, &attitude);

			if (!raw->alive_count && get_local_entity_int_value(en, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_MISSILE_TRAIL && smoke_list_draw_mode( smoke_type ) == SMOKE_DRAW_TYPE_TRAILS) // move 1st trail point backward
				motion_vector.z = - 20;
			else if (get_local_entity_int_value(en, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_GUN_SMOKE) // move gun smoke forward
				motion_vector.z = 20;
			else if (smoke_type == SMOKE_LIST_TYPE_REAR_SHIP_WAKE || smoke_type == SMOKE_LIST_TYPE_FRONT_SHIP_WAKE) // move ship wake backward
				motion_vector.z = - 10;

			multiply_matrix3x3_vec3d(&motion_vector, &attitude, &motion_vector);

			motion_vector.y /= 2.5; // can't find what is wrong..
		}

		motion_vector.x += initial_velocity.x;
		motion_vector.y += initial_velocity.y;
		motion_vector.z += initial_velocity.z;

		if ( smoke_list_draw_mode( smoke_type ) == SMOKE_DRAW_TYPE_TRAILS )
		{
			//
			// smoke trails
			//

			//
			// required for interpolating points
			//

			last_index = raw->head - 1;
					
			if ( last_index < 0 )
			{
				last_index = number_of_slots - 1;
			}
	
			last_pos = &(raw->position[ last_index ]);

			d.x = new_pos.x - last_pos->x;
			d.y = new_pos.y - last_pos->y;
			d.z = new_pos.z - last_pos->z;

			distance = get_3d_vector_magnitude( &d );
					
			if ( distance > 0.0 )
			{

				if ( ( create_count > 1 ) && ( raw->valid[ last_index ] ) )
				{
	
					//
					// create "create_count" - 1 number of interpolated points ( requires previous point to be active )
					//
		
					for ( create_loop = 1 ; create_loop < create_count ; create_loop ++ )
					{
		
						t = (float)create_loop / (float)create_count;
		
						interpolated_pos.x = last_pos->x + ( d.x * t );
						interpolated_pos.y = last_pos->y + ( d.y * t );
						interpolated_pos.z = last_pos->z + ( d.z * t );
		
						create_new_point( en, &interpolated_pos, &motion_vector, smoke_type, number_of_slots );
					}
				}
	
				//
				// create new point at current position
				//
	
				create_new_point( en, &new_pos, &motion_vector, smoke_type, number_of_slots );
			}
		}
		else
		{
			//
			// smoke puffs
			//

			for ( create_loop = 0 ; create_loop < create_count ; create_loop ++ )
			{
				//
				// create new point at current position
				//

				create_new_point( en, &new_pos, &motion_vector, smoke_type, number_of_slots );
			}
		}
	}
	else if ( create_count > 0 )
	{
		//
		// smoke generator is not generating, but tail is moving - so move head as well
		// ( Currently a result of infinite generator being turned off )
		//

		raw->head += create_count;
	
		while ( raw->head >= number_of_slots )
		{
			raw->head -= number_of_slots;
		}
	}

	//
	// texture animation
	//

	//-- Werewolf: Sanity check to fix a crash 4 Apr 2003
	// Sometimes, smoke_list_texture (smoke_type) is undefined, because smoke_list_database[smoke_type] is invalid
	// I suspect that a smoke_type value of 21 is too high, or that the smoke_list_database becomes corrupted sometimes.
	// What we would need to do are lots of sanity checks instead of blindly accessing arrays.
    number_of_frames = 0;
    if (smoke_list_database[smoke_type].texture>=0)
	//-- Werewolf
	number_of_frames = get_texture_animation_number_of_frames (smoke_list_texture (smoke_type));

	if ((number_of_frames > 1) && (smoke_list_animation_rate (smoke_type) > 0.0))
	{
		raw->current_frame += (get_delta_time () / smoke_list_animation_rate (smoke_type));

		while (raw->current_frame >= number_of_frames)
		{
			raw->current_frame -= number_of_frames;
		}
	}
	else
	{
		raw->current_frame = 0;
	}

	//
	// update all individual smoke points
	//

	smoke_list_movement( en );

	return TRUE;
}
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_new_point( entity *en, vec3d *new_pos, vec3d *initial_velocity, smoke_list_types smoke_type, int number_of_slots )
{

	vec3d
		*head_pos;

	smoke_list
		*raw;

	float
		iv_noise = 0;
	
	smoke_list_data
		*smoke_info;
	
	raw = (smoke_list *) get_local_entity_data( en );

	smoke_info = &(smoke_list_database[ raw->smoke_type ]);

	//
	// set position
	//

	head_pos = &(raw->position[ raw->head ]);

	head_pos->x = new_pos->x;
	head_pos->y = new_pos->y;
	head_pos->z = new_pos->z;

	//
	// set intital motion vector
	//

	if(!(smoke_list_draw_mode( smoke_type ) == SMOKE_DRAW_TYPE_TRAILS && raw->alive_count < 4)) // do not displace first trail points
		iv_noise = smoke_list_initial_velocity_noise( smoke_type );

	raw->motion_vector[ raw->head ].x = initial_velocity->x + ( sfrand1() * iv_noise );
	raw->motion_vector[ raw->head ].z = initial_velocity->z + ( sfrand1() * iv_noise );

	if ( smoke_list_ground_based( smoke_type ) )
	{
		raw->motion_vector[ raw->head ].y = initial_velocity->y + ( frand1() * iv_noise );
	}
	else
	{
		raw->motion_vector[ raw->head ].y = initial_velocity->y + ( sfrand1() * iv_noise );
	}

	//
	// give random rotation value
	//

	if (!smoke_info->flat)
		raw->start_rotation[ raw->head ] = sfrand1() * PI;
	else
		raw->start_rotation[ raw->head ] = 0;

	#if DEBUG_MODULE

	debug_log( "SMOKE LIST : Creating Point %i at %f, %f, %f ", raw->head, head_pos->x, head_pos->y, head_pos->z );

	#endif

	//
	// update
	//

	raw->valid[ raw->head ] = TRUE;

	raw->alive_count ++;

	raw->head ++;
	
	if ( raw->head >= number_of_slots )
	{
		raw->head = 0;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_new_smoke_position (entity *en, vec3d *new_pos)
{

	//
	// set new smoke position to the position of a specified sub object of it's parent
	//

	entity
		*parent;

	if (get_local_entity_int_value (en, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_EFFECT_SMOKE_LIST_EXPLOSION_PARTICLE)
	{
		//
		// special case for particles - ignore parent
		//

		get_local_entity_vec3d (en, VEC3D_TYPE_POSITION, new_pos);

		return TRUE;
	}

	parent = get_local_entity_parent (en, LIST_TYPE_SPECIAL_EFFECT);

	if (parent)
	{
		vec3d
			*offset,
			*raw_position;

		matrix3x3
			m;

		raw_position = get_local_entity_vec3d_ptr (parent, VEC3D_TYPE_POSITION);

		offset = get_local_entity_vec3d_ptr (en, VEC3D_TYPE_RELATIVE_POSITION);

		if (check_zero_3d_vector (offset))
		{
			new_pos->x = raw_position->x;
			new_pos->y = raw_position->y;
			new_pos->z = raw_position->z;
		}
		else
		{	
			get_local_entity_attitude_matrix (parent, m);
	
			new_pos->x = raw_position->x + ( ( offset->x * m[0][0] ) + ( offset->y * m[1][0] ) + ( offset->z * m[2][0] ) );
			new_pos->y = raw_position->y + ( ( offset->x * m[0][1] ) + ( offset->y * m[1][1] ) + ( offset->z * m[2][1] ) );
			new_pos->z = raw_position->z + ( ( offset->x * m[0][2] ) + ( offset->y * m[1][2] ) + ( offset->z * m[2][2] ) );
		}
	}
	else
	{			
		get_local_entity_vec3d (en, VEC3D_TYPE_POSITION, new_pos);
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_smoke_list_update_functions (void)
{
	fn_update_client_server_entity[ENTITY_TYPE_SMOKE_LIST][COMMS_MODEL_SERVER]  	= update_server;

	fn_update_client_server_entity[ENTITY_TYPE_SMOKE_LIST][COMMS_MODEL_CLIENT]  	= update_client;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
