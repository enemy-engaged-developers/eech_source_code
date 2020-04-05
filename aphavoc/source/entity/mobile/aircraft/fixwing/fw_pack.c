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

static void pack_local_data (entity *en, pack_modes mode)
{
	ASSERT ((mode >= 0) && (mode < NUM_PACK_MODES));

	switch (mode)
	{
		////////////////////////////////////////
		case PACK_MODE_SERVER_SESSION:
		case PACK_MODE_CLIENT_SESSION:
		////////////////////////////////////////
		{
			fixed_wing
				*raw = nullptr;

			raw = (fixed_wing *) get_local_entity_data (en);

			pack_entity_type (get_local_entity_type (en));

			pack_entity_safe_ptr (en);

			//
			// pack aircraft data
			//

			pack_aircraft_data (en, &raw->ac, mode);

			////////////////////////////////////////

			if (raw->ac.mob.velocity == 0.0)
			{

				pack_int_value (en, INT_TYPE_VALID, TRUE);
			}
			else
			{

				pack_int_value (en, INT_TYPE_VALID, FALSE);

				pack_float_value (en, FLOAT_TYPE_HIGH_VELOCITY, raw->ac.mob.velocity);

				pack_float_value (en, FLOAT_TYPE_AFTERBURNER_STATE, raw->afterburner_state);
			}

			////////////////////////////////////////

			//
			// pack fixwing data
			//

			//
			// spin through special effects link and pack up local only smoke trails
			//

//			pack_aircraft_meta_smoke_lists (en, mode);

			pack_mobile_local_sound_effects (en, mode);

			break;
		}
		////////////////////////////////////////
		case PACK_MODE_BROWSE_SESSION:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case PACK_MODE_UPDATE_ENTITY:
		////////////////////////////////////////
		{
			/*
			fixed_wing
				*raw = nullptr;

			raw = get_local_entity_data (en);

			pack_vec3d (en, VEC3D_TYPE_POSITION, &raw->ac.mob.position);

			pack_attitude_matrix (en, raw->ac.mob.attitude);

			pack_vec3d (en, VEC3D_TYPE_MOTION_VECTOR, &raw->ac.mob.motion_vector);

			*/
			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void unpack_local_data (entity *en, entity_types type, pack_modes mode)
{
	ASSERT ((mode >= 0) && (mode < NUM_PACK_MODES));

	switch (mode)
	{
		////////////////////////////////////////
		case PACK_MODE_SERVER_SESSION:
		case PACK_MODE_CLIENT_SESSION:
		////////////////////////////////////////
		{
			int
				index;

			fixed_wing
				*raw = nullptr;

			//
			// create entity
			//

			index = unpack_entity_safe_index ();

			en = get_free_entity (index);

			set_local_entity_type (en, type);

			raw = (fixed_wing *) malloc_fast_mem (sizeof (fixed_wing));

			set_local_entity_data (en, raw);

			memset (raw, 0, sizeof (fixed_wing));

			//
			// unpack data (in exactly the same order as the data was packed)
			//

			unpack_aircraft_data (en, &raw->ac, mode);

			////////////////////////////////////////

			if (unpack_int_value (en, INT_TYPE_VALID))
			{

				raw->ac.mob.velocity = 0.0;

				raw->afterburner_state = 0.0;
			}
			else
			{

				raw->ac.mob.velocity = unpack_float_value (en, FLOAT_TYPE_HIGH_VELOCITY);

				raw->afterburner_state = unpack_float_value (en, FLOAT_TYPE_AFTERBURNER_STATE);
			}

			////////////////////////////////////////

			set_fixed_wing_id_number (en);

			initialise_fixed_wing_propellors (en);

			//
			// link into system
			//

			insert_local_entity_into_parents_child_list (en, LIST_TYPE_VIEW, get_camera_entity (), NULL);

			insert_local_entity_into_parents_child_list (en, LIST_TYPE_SECTOR, get_local_sector_entity (&raw->ac.mob.position), NULL);

			insert_local_entity_into_parents_child_list (en, LIST_TYPE_UPDATE, get_update_entity (), NULL);

			add_to_force_info (get_local_force_entity ((entity_sides) raw->ac.mob.side), en);

			//
			// attached smoke lists must be unpacked after the entity is linked into the world
			//

//			unpack_aircraft_meta_smoke_lists (en, mode);
//			switch_aircraft_damaged_smoke(en);

			unpack_mobile_local_sound_effects (en, mode);

			break;
		}
		////////////////////////////////////////
		case PACK_MODE_BROWSE_SESSION:
		////////////////////////////////////////
		{
			break;
		}
		////////////////////////////////////////
		case PACK_MODE_UPDATE_ENTITY:
		////////////////////////////////////////
		{
			/*
			//
			// always use access functions to set the data
			//

			vec3d
				position,
				motion_vector;

			matrix3x3
				attitude;

			float
				velocity;

			velocity = 0;

			//
			// unpack all data (even if the echoed data is to be ignored)
			//

			unpack_vec3d (en, VEC3D_TYPE_POSITION, &position);

			unpack_attitude_matrix (en, attitude);

			unpack_vec3d (en, VEC3D_TYPE_MOTION_VECTOR, &motion_vector);

			if (!check_zero_3d_vector (&motion_vector))
			{

				vec3d
					normalised_motion_vector;

				flat
					mag;

				normalised_motion_vector = motion_vector;

				mag = normalise_3d_vector (&normalised_motion_vector);

				velocity = mag *
								(normalised_motion_vector.x * attitude [2][0] +
								normalised_motion_vector.y * attitude [2][1] +
								normalised_motion_vector.z * attitude [2][2]);
			}

			set_local_entity_vec3d (en, VEC3D_TYPE_POSITION, &position);

			set_local_entity_attitude_matrix (en, attitude);

			set_local_entity_vec3d (en, VEC3D_TYPE_MOTION_VECTOR, &motion_vector);

			set_local_entity_float_value (en, FLOAT_TYPE_VELOCITY, velocity);

			*/
			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_fixed_wing_pack_functions (void)
{
	fn_pack_local_entity_data[ENTITY_TYPE_FIXED_WING]		= pack_local_data;

	fn_unpack_local_entity_data[ENTITY_TYPE_FIXED_WING]	= unpack_local_data;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
