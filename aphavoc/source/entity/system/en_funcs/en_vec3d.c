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

#define DEBUG_MODULE				0

#define DEBUG_MODULE_PACK_ONE	0

#define DEBUG_MODULE_PACK_ALL	(PACK_ENTIRE_SESSION || 0)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vec3d_type_data
	vec3d_type_database[NUM_VEC3D_TYPES] =
	{
		{
			"VEC3D_TYPE_BOUNDING_BOX_MAX",				// name
			VEC3D_PACK_TYPE_UNPACKED,	  					// pack_type
			(DEBUG_MODULE_PACK_ALL || 0),					// debug_pack
		},
		{
			"VEC3D_TYPE_BOUNDING_BOX_MIN",				// name
			VEC3D_PACK_TYPE_UNPACKED,	  					// pack_type
			(DEBUG_MODULE_PACK_ALL || 0),					// debug_pack
		},
		{
			"VEC3D_TYPE_COVER_POSITION",					// name
			VEC3D_PACK_TYPE_POSITION,						// pack_type
			(DEBUG_MODULE_PACK_ALL || 0),					// debug_pack
		},
		{
			"VEC3D_TYPE_GUIDE_POSITION",					// name
			VEC3D_PACK_TYPE_UNPACKED,						// pack_type
			(DEBUG_MODULE_PACK_ALL || 0),					// debug_pack
		},
		{
			"VEC3D_TYPE_INITIAL_VELOCITY",				// name
			VEC3D_PACK_TYPE_INITIAL_VELOCITY,			// pack_type
			(DEBUG_MODULE_PACK_ALL || 0),					// debug_pack
		},
		{
			"VEC3D_TYPE_MOTION_VECTOR",					// name
			VEC3D_PACK_TYPE_MOTION_VECTOR,				// pack_type
			(DEBUG_MODULE_PACK_ALL || 0),					// debug_pack
		},
		{
			"VEC3D_TYPE_OBJECT_SCALING",					// name
			VEC3D_PACK_TYPE_UNPACKED,	  					// pack_type
			(DEBUG_MODULE_PACK_ALL || 0),					// debug_pack
		},
		{
			"VEC3D_TYPE_POSITION",							// name
			VEC3D_PACK_TYPE_POSITION,						// pack_type
			(DEBUG_MODULE_PACK_ALL || 0),					// debug_pack
		},
		{
			"VEC3D_TYPE_RELATIVE_POSITION",				// name
			VEC3D_PACK_TYPE_RELATIVE_POSITION,			// pack_type
			(DEBUG_MODULE_PACK_ALL || 0),					// debug_pack
		},
		{
			"VEC3D_TYPE_START_POSITION",					// name
			VEC3D_PACK_TYPE_POSITION,	  					// pack_type
			(DEBUG_MODULE_PACK_ALL || 0),					// debug_pack
		},
		{
			"VEC3D_TYPE_STOP_POSITION",  					// name
			VEC3D_PACK_TYPE_POSITION,	  					// pack_type
			(DEBUG_MODULE_PACK_ALL || 0),					// debug_pack
		},
		{
			"VEC3D_TYPE_WAIT_POSITION",  					// name
			VEC3D_PACK_TYPE_POSITION,	  					// pack_type
			(DEBUG_MODULE_PACK_ALL || 0),					// debug_pack
		},
		{
			"VEC3D_TYPE_WEAPON_TO_TARGET_VECTOR",		// name
			VEC3D_PACK_TYPE_UNIT_VECTOR,					// pack_type
			(DEBUG_MODULE_PACK_ALL || 0),					// debug_pack
		},
		{
			"VEC3D_TYPE_WEAPON_VECTOR",					// name
			VEC3D_PACK_TYPE_UNIT_VECTOR,					// pack_type
			(DEBUG_MODULE_PACK_ALL || 0),					// debug_pack
		},
		{
			"VEC3D_TYPE_WEATHER_POSITION",				// name
			VEC3D_PACK_TYPE_POSITION,						// pack_type
			(DEBUG_MODULE_PACK_ALL || 0),					// debug_pack
		},
		{
			"VEC3D_TYPE_WEATHER_VELOCITY",				// name
			VEC3D_PACK_TYPE_MOTION_VECTOR,				// pack_type
			(DEBUG_MODULE_PACK_ALL || 0),					// debug_pack
		},
		{
			"VEC3D_TYPE_WIND_DIRECTION_VECTOR",			// name
			VEC3D_PACK_TYPE_UNIT_VECTOR,					// pack_type
			(DEBUG_MODULE_PACK_ALL || 0),					// debug_pack
		},
		{
			"VEC3D_TYPE_WIND_EFFECT_POSITION",			// name
			VEC3D_PACK_TYPE_POSITION,						// pack_type
			(DEBUG_MODULE_PACK_ALL || 0),					// debug_pack
		},
		{
			"VEC3D_TYPE_WIND_EFFECT_VELOCITY",			// name
			VEC3D_PACK_TYPE_MOTION_VECTOR,				// pack_type
			(DEBUG_MODULE_PACK_ALL || 0),					// debug_pack
		},
		{
			"VEC3D_TYPE_XV",									// name
			VEC3D_PACK_TYPE_UNPACKED,						// pack_type
			(DEBUG_MODULE_PACK_ALL || 0),					// debug_pack
		},
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char
	*overload_invalid_vec3d_type_message = "Overloaded entity function invoked with invalid vec3d type",
	*debug_fatal_invalid_vec3d_type_message = "Invalid vec3d type (entity type = %s, index = %d, vec3d type = %s, file = %s, line = %d)";

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void (*fn_set_local_entity_raw_vec3d[NUM_ENTITY_TYPES][NUM_VEC3D_TYPES]) (entity *en, vec3d_types type, vec3d *v);

void (*fn_set_local_entity_vec3d[NUM_ENTITY_TYPES][NUM_VEC3D_TYPES]) (entity *en, vec3d_types type, vec3d *v);

void (*fn_set_client_server_entity_vec3d[NUM_ENTITY_TYPES][NUM_VEC3D_TYPES][NUM_COMMS_MODEL_TYPES]) (entity *en, vec3d_types type, vec3d *v);

void (*fn_get_local_entity_vec3d[NUM_ENTITY_TYPES][NUM_VEC3D_TYPES]) (entity *en, vec3d_types type, vec3d *v);

vec3d *(*fn_get_local_entity_vec3d_ptr[NUM_ENTITY_TYPES][NUM_VEC3D_TYPES]) (entity *en, vec3d_types type);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void default_set_entity_vec3d (entity *en, vec3d_types type, vec3d *v)
{
	ASSERT (v);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void default_get_entity_vec3d (entity *en, vec3d_types type, vec3d *v)
{
	ASSERT (v);

	switch (type)
	{
		////////////////////////////////////////
		case VEC3D_TYPE_MOTION_VECTOR:
		////////////////////////////////////////
		{
			v->x = 0.0;
			v->y = 0.0;
			v->z = 1.0;

			break;
		}
		////////////////////////////////////////
		case VEC3D_TYPE_START_POSITION:
		////////////////////////////////////////
		{
			v->x = MID_MAP_X;
			v->y = 0.0;
			v->z = MID_MAP_Z;

			break;
		}
		////////////////////////////////////////
		case VEC3D_TYPE_STOP_POSITION:
		////////////////////////////////////////
		{
			v->x = MID_MAP_X;
			v->y = 0.0;
			v->z = MID_MAP_Z;

			break;
		}
		////////////////////////////////////////
		case VEC3D_TYPE_WEAPON_TO_TARGET_VECTOR:
		////////////////////////////////////////
		{
			v->x = 0.0;
			v->y = 0.0;
			v->z = -1.0;

			break;
		}
		////////////////////////////////////////
		case VEC3D_TYPE_WEAPON_VECTOR:
		////////////////////////////////////////
		{
			v->x = 0.0;
			v->y = 0.0;
			v->z = 1.0;

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			v->x = 0.0;
			v->y = 0.0;
			v->z = 0.0;

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static vec3d *default_get_entity_vec3d_ptr (entity *en, vec3d_types type)
{
	return (NULL);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_entity_vec3d_default_functions (void)
{
	int
		i,
		j;

	for (i = 0; i < NUM_ENTITY_TYPES; i++)
	{
		for (j = 0; j < NUM_VEC3D_TYPES; j++)
		{
			fn_set_local_entity_raw_vec3d[i][j]									= default_set_entity_vec3d;

			fn_set_local_entity_vec3d[i][j]										= default_set_entity_vec3d;

			fn_set_client_server_entity_vec3d[i][j][COMMS_MODEL_SERVER]	= default_set_entity_vec3d;

			fn_set_client_server_entity_vec3d[i][j][COMMS_MODEL_CLIENT]	= default_set_entity_vec3d;

			fn_get_local_entity_vec3d[i][j]										= default_get_entity_vec3d;

			fn_get_local_entity_vec3d_ptr[i][j]									= default_get_entity_vec3d_ptr;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void pack_vec3d (entity *en, vec3d_types type, vec3d *v)
{
	ASSERT ((type >= 0) && (type < NUM_VEC3D_TYPES));

	ASSERT (v);

	switch (vec3d_type_database[type].pack_type)
	{
		////////////////////////////////////////
		case VEC3D_PACK_TYPE_UNPACKED:
		////////////////////////////////////////
		{
			pack_unsigned_data (*(int *)&v->x, 32);

			pack_unsigned_data (*(int *)&v->y, 32);

			pack_unsigned_data (*(int *)&v->z, 32);

			#if (DEBUG_MODULE_PACK_ONE || DEBUG_MODULE_PACK_ALL)

			if (vec3d_type_database[type].debug_pack)
			{
				debug_log_entity_args (ENTITY_DEBUG_PACK, ENTITY_DEBUG_VEC3D, en, type, v);
			}

			#endif

			break;
		}
		////////////////////////////////////////
		case VEC3D_PACK_TYPE_UNIT_VECTOR:
		////////////////////////////////////////
		{
			int
				ix,
				iy,
				iz;

			convert_float_to_int (v->x * (float) 0x7ff, &ix);

			pack_signed_data (ix, 12);

			convert_float_to_int (v->y * (float) 0x7ff, &iy);

			pack_signed_data (iy, 12);

			convert_float_to_int (v->z * (float) 0x7ff, &iz);

			pack_signed_data (iz, 12);

			#if (DEBUG_MODULE_PACK_ONE || DEBUG_MODULE_PACK_ALL)

			if (vec3d_type_database[type].debug_pack)
			{
				vec3d
					v;

				//
				// packed debug message to match unpacked debug message
				//

				v.x = (float) ix * (1.0 / (float) 0x7ff);
				v.y = (float) iy * (1.0 / (float) 0x7ff);
				v.z = (float) iz * (1.0 / (float) 0x7ff);

				normalise_3d_vector (&v);

				debug_log_entity_args (ENTITY_DEBUG_PACK, ENTITY_DEBUG_VEC3D, en, type, &v);
			}

			#endif

			break;
		}
		////////////////////////////////////////
		case VEC3D_PACK_TYPE_POSITION:
		////////////////////////////////////////
		{
			int
				ix,
				iy,
				iz;

			ASSERT (point_inside_map_volume (v));

			pack_float_4_fractional_bits (v->x, &ix);

			pack_unsigned_data (ix, 19 + 4);

			pack_float_4_fractional_bits (v->y, &iy);

			pack_signed_data (iy, 1 + 16 + 4);

			pack_float_4_fractional_bits (v->z, &iz);

			pack_unsigned_data (iz, 19 + 4);

			#if (DEBUG_MODULE_PACK_ONE || DEBUG_MODULE_PACK_ALL)

			if (vec3d_type_database[type].debug_pack)
			{
				vec3d
					v;

				//
				// packed debug message to match unpacked debug message
				//

		 		v.x = unpack_float_4_fractional_bits (ix);
				v.y = unpack_float_4_fractional_bits (iy);
				v.z = unpack_float_4_fractional_bits (iz);

				debug_log_entity_args (ENTITY_DEBUG_PACK, ENTITY_DEBUG_VEC3D, en, type, &v);
			}

			#endif

			//
			// check packed position remains in the same sector
			//

			#ifdef DEBUG
			{
				int
					x_sec1,
					z_sec1,
					x_sec2,
					z_sec2;

				get_x_sector (x_sec1, v->x);
				get_z_sector (z_sec1, v->z);

				get_x_sector (x_sec2, unpack_float_4_fractional_bits (ix));
				get_z_sector (z_sec2, unpack_float_4_fractional_bits (iz));

				ASSERT (x_sec1 == x_sec2);
				ASSERT (z_sec1 == z_sec2);
			}
			#endif

			break;
		}
		////////////////////////////////////////
		case VEC3D_PACK_TYPE_RELATIVE_POSITION:
		////////////////////////////////////////
		{
			int
				ix,
				iy,
				iz;

			pack_float_2_fractional_bits (v->x, &ix);

			pack_signed_data (ix, 1 + 15 + 2);

			pack_float_2_fractional_bits (v->y, &iy);

			pack_signed_data (iy, 1 + 13 + 2);

			pack_float_2_fractional_bits (v->z, &iz);

			pack_signed_data (iz, 1 + 15 + 2);

			#if (DEBUG_MODULE_PACK_ONE || DEBUG_MODULE_PACK_ALL)

			if (vec3d_type_database[type].debug_pack)
			{
				vec3d
					v;

				//
				// packed debug message to match unpacked debug message
				//

		 		v.x = unpack_float_2_fractional_bits (ix);
				v.y = unpack_float_2_fractional_bits (iy);
				v.z = unpack_float_2_fractional_bits (iz);

				debug_log_entity_args (ENTITY_DEBUG_PACK, ENTITY_DEBUG_VEC3D, en, type, &v);
			}

			#endif

			break;
		}
		////////////////////////////////////////
		case VEC3D_PACK_TYPE_INITIAL_VELOCITY:
		////////////////////////////////////////
		{
			int
				ix,
				iy,
				iz;

			pack_float_3_fractional_bits (v->x, &ix);

			pack_signed_data (ix, 1 + 6 + 3);

			pack_float_3_fractional_bits (v->y, &iy);

			pack_signed_data (iy, 1 + 6 + 3);

			pack_float_3_fractional_bits (v->z, &iz);

			pack_signed_data (iz, 1 + 6 + 3);

			#if (DEBUG_MODULE_PACK_ONE || DEBUG_MODULE_PACK_ALL)

			if (vec3d_type_database[type].debug_pack)
			{
				vec3d
					v;

				//
				// packed debug message to match unpacked debug message
				//

		 		v.x = unpack_float_3_fractional_bits (ix);
				v.y = unpack_float_3_fractional_bits (iy);
				v.z = unpack_float_3_fractional_bits (iz);

				debug_log_entity_args (ENTITY_DEBUG_PACK, ENTITY_DEBUG_VEC3D, en, type, &v);
			}

			#endif

			break;
		}
		////////////////////////////////////////
		case VEC3D_PACK_TYPE_MOTION_VECTOR:
		////////////////////////////////////////
		{
			int
				ix,
				iy,
				iz;

			pack_float_6_fractional_bits (v->x, &ix);

			pack_signed_data (ix, 1 + 11 + 6);

			pack_float_6_fractional_bits (v->y, &iy);

			pack_signed_data (iy, 1 + 11 + 6);

			pack_float_6_fractional_bits (v->z, &iz);

			pack_signed_data (iz, 1 + 11 + 6);

			#if (DEBUG_MODULE_PACK_ONE || DEBUG_MODULE_PACK_ALL)

			if (vec3d_type_database[type].debug_pack)
			{
				vec3d
					v;

				//
				// packed debug message to match unpacked debug message
				//

		 		v.x = unpack_float_6_fractional_bits (ix);
				v.y = unpack_float_6_fractional_bits (iy);
				v.z = unpack_float_6_fractional_bits (iz);

				debug_log_entity_args (ENTITY_DEBUG_PACK, ENTITY_DEBUG_VEC3D, en, type, &v);
			}

			#endif

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			debug_fatal ("Invalid vec3d pack type = %d", vec3d_type_database[type].pack_type);

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void unpack_vec3d (entity *en, vec3d_types type, vec3d *v)
{
	ASSERT ((type >= 0) && (type < NUM_VEC3D_TYPES));

	ASSERT (v);

	switch (vec3d_type_database[type].pack_type)
	{
		////////////////////////////////////////
		case VEC3D_PACK_TYPE_UNPACKED:
		////////////////////////////////////////
		{
			int
				ix,
				iy,
				iz;

			ix = unpack_unsigned_data (32);

			v->x = *(float *)&ix;

			iy = unpack_unsigned_data (32);

			v->y = *(float *)&iy;

			iz = unpack_unsigned_data (32);

			v->z = *(float *)&iz;

			break;
		}
		////////////////////////////////////////
		case VEC3D_PACK_TYPE_UNIT_VECTOR:
		////////////////////////////////////////
		{
			int
				ix,
				iy,
				iz;

			ix = unpack_signed_data (12);

			v->x = (float) ix * (1.0 / (float) 0x7ff);

			iy = unpack_signed_data (12);

			v->y = (float) iy * (1.0 / (float) 0x7ff);

			iz = unpack_signed_data (12);

			v->z = (float) iz * (1.0 / (float) 0x7ff);

			normalise_3d_vector (v);

			break;
		}
		////////////////////////////////////////
		case VEC3D_PACK_TYPE_POSITION:
		////////////////////////////////////////
		{
			int
				ix,
				iy,
				iz;

			ix = unpack_unsigned_data (19 + 4);

			v->x = unpack_float_4_fractional_bits (ix);

			iy = unpack_signed_data (1 + 16 + 4);

			v->y = unpack_float_4_fractional_bits (iy);

			iz = unpack_unsigned_data (19 + 4);

			v->z = unpack_float_4_fractional_bits (iz);

			break;
		}
		////////////////////////////////////////
		case VEC3D_PACK_TYPE_RELATIVE_POSITION:
		////////////////////////////////////////
		{
			int
				ix,
				iy,
				iz;

			ix = unpack_signed_data (1 + 15 + 2);

			v->x = unpack_float_2_fractional_bits (ix);

			iy = unpack_signed_data (1 + 13 + 2);

			v->y = unpack_float_2_fractional_bits (iy);

			iz = unpack_signed_data (1 + 15 + 2);

			v->z = unpack_float_2_fractional_bits (iz);

			break;
		}
		////////////////////////////////////////
		case VEC3D_PACK_TYPE_INITIAL_VELOCITY:
		////////////////////////////////////////
		{
			int
				ix,
				iy,
				iz;

			ix = unpack_signed_data (1 + 6 + 3);

			v->x = unpack_float_3_fractional_bits (ix);

			iy = unpack_signed_data (1 + 6 + 3);

			v->y = unpack_float_3_fractional_bits (iy);

			iz = unpack_signed_data (1 + 6 + 3);

			v->z = unpack_float_3_fractional_bits (iz);

			break;
		}
		////////////////////////////////////////
		case VEC3D_PACK_TYPE_MOTION_VECTOR:
		////////////////////////////////////////
		{
			int
				ix,
				iy,
				iz;

			ix = unpack_signed_data (1 + 11 + 6);

			v->x = unpack_float_6_fractional_bits (ix);

			iy = unpack_signed_data (1 + 11 + 6);

			v->y = unpack_float_6_fractional_bits (iy);

			iz = unpack_signed_data (1 + 11 + 6);

			v->z = unpack_float_6_fractional_bits (iz);

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			debug_fatal ("Invalid vec3d pack type = %d", vec3d_type_database[type].pack_type);

			break;
		}
	}

	#if (DEBUG_MODULE_PACK_ONE || DEBUG_MODULE_PACK_ALL)

	if (vec3d_type_database[type].debug_pack)
	{
		debug_log_entity_args (ENTITY_DEBUG_UNPACK, ENTITY_DEBUG_VEC3D, en, type, v);
	}

	#endif
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void pack_vec3d_type (vec3d_types type)
{
	ASSERT ((type >= 0) && (type < NUM_VEC3D_TYPES));

	#if (DEBUG_MODULE_PACK_ONE || DEBUG_MODULE_PACK_ALL)

	if (vec3d_type_database[type].debug_pack)
	{
		debug_log_entity_args (ENTITY_DEBUG_PACK, ENTITY_DEBUG_VEC3D_TYPE, NULL, type);
	}

	#endif

	ASSERT(!(type >> NUM_VEC3D_TYPE_PACK_BITS));
	
	pack_unsigned_data (type, NUM_VEC3D_TYPE_PACK_BITS);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vec3d_types unpack_vec3d_type (void)
{
	vec3d_types
		type;

	type = unpack_unsigned_data (NUM_VEC3D_TYPE_PACK_BITS);

	ASSERT ((type >= 0) && (type < NUM_VEC3D_TYPES));

	#if (DEBUG_MODULE_PACK_ONE || DEBUG_MODULE_PACK_ALL)

	if (vec3d_type_database[type].debug_pack)
	{
		debug_log_entity_args (ENTITY_DEBUG_UNPACK, ENTITY_DEBUG_VEC3D_TYPE, NULL, type);
	}

	#endif

	return (type);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_local_entity_vec3d_magnitude (entity *en, vec3d_types type)
{
	vec3d
		*v;

	float
		m;

	ASSERT (en);

	ASSERT ((type >= 0) && (type < NUM_VEC3D_TYPES));

	v = get_local_entity_vec3d_ptr (en, type);

	if (v)
	{
		m = get_3d_vector_magnitude (v);
	}
	else
	{
		m = 0.0;
	}

	return (m);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
