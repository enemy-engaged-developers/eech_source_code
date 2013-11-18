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

static entity *create_local (entity_types type, int index, char *pargs)
{
	entity
		*en;

	particle
		*raw;

	int
		seed,
		loop;

	matrix3x3
		rotation_matrix;

	#if DEBUG_MODULE

	debug_log ("PARTICLE : create");

	#endif

	////////////////////////////////////////
  	//
  	// VALIDATE
  	//
	////////////////////////////////////////

	validate_local_create_entity_index (index);

	#if DEBUG_MODULE

	debug_log_entity_args (ENTITY_DEBUG_LOCAL, ENTITY_DEBUG_CREATE, NULL, type, index);

	#endif

	en = get_free_entity (index);

	if (en)
	{
		////////////////////////////////////////
   	//
   	// MALLOC ENTITY DATA
   	//
		////////////////////////////////////////

		set_local_entity_type (en, type);

		raw = (particle *) malloc_fast_mem (sizeof (particle));

		set_local_entity_data (en, raw);

		////////////////////////////////////////
   	//
   	// INITIALISE ALL ENTITY DATA TO 'WORKING' DEFAULT VALUES
		//
		// DO NOT USE ACCESS FUNCTIONS
		//
		// DO NOT USE RANDOM VALUES
		//
		////////////////////////////////////////

		memset (raw, 0, sizeof (particle));

		//
		// fixed
		//

		raw->eff.position.x = MID_MAP_X;
		raw->eff.position.y = MID_MAP_Y;
		raw->eff.position.z = MID_MAP_Z;

		////////////////////////////////////////
		//
		// OVERWRITE DEFAULT VALUES WITH GIVEN ATTRIBUTES
		//
		////////////////////////////////////////

		set_local_entity_attributes (en, pargs);

		////////////////////////////////////////
		//
		// CHECK MANDATORY ATTRIBUTES HAVE BEEN GIVEN
		//
		////////////////////////////////////////

		ASSERT (entity_sub_type_effect_valid (raw->eff.sub_type));

		ASSERT (raw->particle_count > 0);

		ASSERT (raw->initial_speed > 0.0);

		////////////////////////////////////////
		//
		// RESOLVE DEFAULT VALUES
		//
		////////////////////////////////////////

		////////////////////////////////////////
		//
		// BUILD COMPONENTS
		//
		////////////////////////////////////////

		//
		// Build array of particle positions, and set all to effect position
		//

		raw->valid = (unsigned char *) malloc_fast_mem (sizeof (unsigned char) * raw->particle_count);

		raw->position = (vec3d *) malloc_fast_mem (sizeof (vec3d) * raw->particle_count);

		raw->motion_vector = (vec3d *) malloc_fast_mem (sizeof (vec3d) * raw->particle_count);

		raw->inst3d = (object_3d_instance **) malloc_fast_mem (sizeof (object_3d_instance *) * raw->particle_count);

		seed = get_client_server_entity_random_number_seed( en );

		#if DEBUG_MODULE

		debug_log ("PARTICLE : initial speed = %f", raw->initial_speed);

		#endif

		for ( loop = raw->particle_count - 1 ; loop >= 0 ; loop -- )
		{
			raw->valid[ loop ] = TRUE;

			if (raw->object_3d_shape != OBJECT_3D_INVALID_OBJECT_INDEX)
			{
				raw->inst3d[ loop ] = construct_3d_object (raw->object_3d_shape);

				if (raw->heading || raw->pitch || raw->roll)
					get_3d_transformation_matrix_fast (rotation_matrix, raw->heading, raw->pitch, raw->roll);
				else	// okay to use random values as its for visual effect only
					get_3d_transformation_matrix_fast (rotation_matrix, PI * sfrand1(), PI * sfrand1(), PI * sfrand1());
				
					memcpy (raw->inst3d [loop]->vp.attitude, rotation_matrix, sizeof (matrix3x3));
			}
			else
			{
				raw->inst3d[ loop ] = NULL;
			}

			raw->position[ loop ].x = raw->eff.position.x;
			raw->position[ loop ].y = raw->eff.position.y;
			raw->position[ loop ].z = raw->eff.position.z;

			raw->motion_vector[ loop ].x = ( sfrand1x( &seed ) * raw->initial_speed );
			raw->motion_vector[ loop ].y = ( (0.25 + 0.75 * frand1x( &seed )) * raw->initial_speed );
			raw->motion_vector[ loop ].z = ( sfrand1x( &seed ) * raw->initial_speed );

		}

		////////////////////////////////////////
		//
		// LINK INTO SYSTEM
		//
		////////////////////////////////////////

		insert_local_entity_into_parents_child_list (en, LIST_TYPE_UPDATE, get_update_entity(), NULL);

		insert_local_entity_into_parents_child_list (en, LIST_TYPE_SECTOR, get_local_sector_entity (&raw->eff.position), NULL);
	}

	return (en);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static entity *create_remote (entity_types type, int index, char *pargs)
{
	validate_remote_create_entity_index (index);

	#if DEBUG_MODULE

	debug_log_entity_args (ENTITY_DEBUG_REMOTE, ENTITY_DEBUG_CREATE, NULL, type, index);

	#endif

	transmit_entity_comms_message (ENTITY_COMMS_CREATE, NULL, type, index, pargs);

	return (NULL);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static entity *create_server (entity_types type, int index, char *pargs)
{
	entity
		*en;

	validate_client_server_local_fn ();

	en = create_local (type, index, pargs);

	if (en)
	{
		validate_client_server_remote_fn ();

		create_remote (type, get_local_entity_index (en), pargs);
	}

	return (en);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static entity *create_client (entity_types type, int index, char *pargs)
{
	entity
		*en;

	if (get_comms_data_flow () == COMMS_DATA_FLOW_TX)
	{
		validate_client_server_remote_fn ();

		en = create_remote (type, index, pargs);
	}
	else
	{
		validate_client_server_local_fn ();

		en = create_local (type, index, pargs);
	}

	return (en);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity *create_client_server_particle_entity (int particle_count, viewpoint vp, float initial_speed, object_3d_index_numbers object_3d_shape)
{

	entity
		*en;

	int
		create_stack_attributes;

	create_stack_attributes = force_local_entity_create_stack_attributes;

	if (get_comms_data_flow () == COMMS_DATA_FLOW_RX)
	{
		set_force_local_entity_create_stack_attributes (TRUE);
	}

	en = create_client_server_entity
	(
		ENTITY_TYPE_PARTICLE,
		ENTITY_INDEX_DONT_CARE,
		ENTITY_ATTR_INT_VALUE (INT_TYPE_ENTITY_SUB_TYPE, ENTITY_SUB_TYPE_EFFECT_PARTICLE),
		ENTITY_ATTR_INT_VALUE (INT_TYPE_PARTICLE_COUNT, particle_count),
		ENTITY_ATTR_INT_VALUE (INT_TYPE_OBJECT_3D_SHAPE, object_3d_shape),
		ENTITY_ATTR_VEC3D (VEC3D_TYPE_POSITION, vp.x, vp.y, vp.z),
		ENTITY_ATTR_FLOAT_VALUE (FLOAT_TYPE_INITIAL_SPEED, initial_speed),
		ENTITY_ATTR_FLOAT_VALUE (FLOAT_TYPE_HEADING, get_heading_from_attitude_matrix(vp.attitude)),
		ENTITY_ATTR_FLOAT_VALUE (FLOAT_TYPE_PITCH, get_pitch_from_attitude_matrix(vp.attitude)),
		ENTITY_ATTR_FLOAT_VALUE (FLOAT_TYPE_ROLL, get_roll_from_attitude_matrix(vp.attitude)),
		ENTITY_ATTR_END
	);

	set_force_local_entity_create_stack_attributes (create_stack_attributes);

	return en;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_particle_create_functions (void)
{
	fn_create_local_entity[ENTITY_TYPE_PARTICLE]			  								= create_local;

	fn_create_client_server_entity[ENTITY_TYPE_PARTICLE][COMMS_MODEL_SERVER]	= create_server;

	fn_create_client_server_entity[ENTITY_TYPE_PARTICLE][COMMS_MODEL_CLIENT]	= create_client;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
