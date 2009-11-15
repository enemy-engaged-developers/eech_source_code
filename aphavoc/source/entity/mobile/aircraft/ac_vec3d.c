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

#define DEBUG_MODULE 									0

#define DEBUG_MODULE_AIRCRAFT_POSITION_MESSAGE	0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_local_raw_vec3d (entity *en, vec3d_types type, vec3d *v)
{
   aircraft
      *raw;

   ASSERT (v);

   #if DEBUG_MODULE

   debug_log_entity_args (ENTITY_DEBUG_LOCAL, ENTITY_DEBUG_VEC3D, en, type, v);

   #endif

   raw = (aircraft *) get_local_entity_data (en);

   switch (type)
   {
      ////////////////////////////////////////
      case VEC3D_TYPE_POSITION:
      ////////////////////////////////////////
      {
         raw->mob.position = *v;

         break;
      }
      ////////////////////////////////////////
      default:
      ////////////////////////////////////////
      {
         debug_fatal_invalid_vec3d_type (en, type);

         break;
      }
   }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_local_vec3d (entity *en, vec3d_types type, vec3d *v)
{
   aircraft
      *raw;

   ASSERT (v);

   #if DEBUG_MODULE

   debug_log_entity_args (ENTITY_DEBUG_LOCAL, ENTITY_DEBUG_VEC3D, en, type, v);

   #endif

   raw = (aircraft *) get_local_entity_data (en);

   switch (type)
   {
      ////////////////////////////////////////
      case VEC3D_TYPE_MOTION_VECTOR:
      ////////////////////////////////////////
      {
         raw->mob.motion_vector = *v;

         break;
      }
      ////////////////////////////////////////
      case VEC3D_TYPE_POSITION:
      ////////////////////////////////////////
      {

         float
            heading;

         entity
				*dependent,
				*special_effect,
				*old_sector,
				*new_sector;

			//
			// notify dependents of move, must be done before set_vec3d so children can work out delta positions
			//

         heading = 0.0;

			//if (get_local_entity_type (en) == ENTITY_TYPE_HELICOPTER)
			{

				heading = get_heading_from_attitude_matrix (raw->mob.attitude);
	
				dependent = get_local_entity_first_child (en, LIST_TYPE_MOVEMENT_DEPENDENT);
	
				while (dependent)
				{
					#if DEBUG_MODULE_AIRCRAFT_POSITION_MESSAGE
	
					debug_log ("AIRCRAFT VEC3D: sending set entity position %f, %f, %f", raw->mob.position.x, raw->mob.position.y, raw->mob.position.z);
	
					#endif
	
					notify_local_entity (ENTITY_MESSAGE_SET_ENTITY_POSITION, dependent, en, v, (double) heading, (double) raw->mob.velocity);
	
					dependent = get_local_entity_child_succ (dependent, LIST_TYPE_MOVEMENT_DEPENDENT);
				}
			}

			//
			// Actual set_vec3d
			//

         raw->mob.position = *v;

			//
			// check if entered new sector
			//

			old_sector = get_local_entity_parent (en, LIST_TYPE_SECTOR);

			new_sector = get_local_sector_entity (v);

         if (old_sector != new_sector)
         {
            delete_local_entity_from_parents_child_list (en, LIST_TYPE_SECTOR);

            insert_local_entity_into_parents_child_list (en, LIST_TYPE_SECTOR, new_sector, NULL);

				//
				// play speech for flown across "front-line"
				//

				if (get_comms_model () == COMMS_MODEL_SERVER)
				{
					if (get_local_entity_int_value (new_sector, INT_TYPE_SIDE) != get_local_entity_int_value (old_sector, INT_TYPE_SIDE))
					{
						play_aircraft_flown_into_new_sector_speech (en, old_sector, new_sector);
					}
				}
         }

			//
			// notify special effects of move
			//

			special_effect = get_local_entity_first_child (en, LIST_TYPE_SPECIAL_EFFECT);

			while (special_effect)
			{
				#if DEBUG_MODULE_AIRCRAFT_POSITION_MESSAGE

				debug_log ("AIRCRAFT VEC3D: sending set entity position %f, %f, %f", raw->mob.position.x, raw->mob.position.y, raw->mob.position.z);

				#endif

				notify_local_entity (ENTITY_MESSAGE_SET_ENTITY_POSITION, special_effect, en, &raw->mob.position, (double) heading, (double) raw->mob.velocity);

				special_effect = get_local_entity_child_succ (special_effect, LIST_TYPE_SPECIAL_EFFECT);
			}

         break;
      }
      ////////////////////////////////////////
      case VEC3D_TYPE_WEAPON_TO_TARGET_VECTOR:
      ////////////////////////////////////////
      {
         raw->weapon_to_target_vector = *v;

         break;
      }
      ////////////////////////////////////////
      case VEC3D_TYPE_WEAPON_VECTOR:
      ////////////////////////////////////////
      {
         raw->weapon_vector = *v;

         break;
      }
      ////////////////////////////////////////
      default:
      ////////////////////////////////////////
      {
         debug_fatal_invalid_vec3d_type (en, type);

         break;
      }
   }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_remote_vec3d (entity *en, vec3d_types type, vec3d *v)
{
   ASSERT (v);

   #if DEBUG_MODULE

   debug_log_entity_args (ENTITY_DEBUG_REMOTE, ENTITY_DEBUG_VEC3D, en, type, v);

   #endif

   transmit_entity_comms_message (ENTITY_COMMS_VEC3D, en, type, v);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_server_vec3d (entity *en, vec3d_types type, vec3d *v)
{
   ASSERT (v);

   validate_client_server_local_fn ();

   set_local_vec3d (en, type, v);

   validate_client_server_remote_fn ();

   set_remote_vec3d (en, type, v);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void set_client_vec3d (entity *en, vec3d_types type, vec3d *v)
{
   ASSERT (v);

   if (get_comms_data_flow () == COMMS_DATA_FLOW_TX)
   {
      validate_client_server_remote_fn ();

      set_remote_vec3d (en, type, v);
   }
   else
   {
      validate_client_server_local_fn ();

      set_local_vec3d (en, type, v);
   }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void get_local_vec3d (entity *en, vec3d_types type, vec3d *v)
{
   aircraft
      *raw;

   ASSERT (v);

   raw = (aircraft *) get_local_entity_data (en);

   switch (type)
   {
		////////////////////////////////////////
		case VEC3D_TYPE_MOTION_VECTOR:
		////////////////////////////////////////
		{
			*v = raw->mob.motion_vector;

			break;
		}
		////////////////////////////////////////
		case VEC3D_TYPE_POSITION:
		////////////////////////////////////////
		{
			*v = raw->mob.position;

			break;
		}
		////////////////////////////////////////
		case VEC3D_TYPE_WEAPON_TO_TARGET_VECTOR:
		////////////////////////////////////////
		{
			*v = raw->weapon_to_target_vector;

			break;
		}
		////////////////////////////////////////
		case VEC3D_TYPE_WEAPON_VECTOR:
		////////////////////////////////////////
		{
			*v = raw->weapon_vector;

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			debug_fatal_invalid_vec3d_type (en, type);

			break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static vec3d *get_local_vec3d_ptr (entity *en, vec3d_types type)
{
	aircraft
		*raw;

	vec3d
		*v;

	raw = (aircraft *) get_local_entity_data (en);

	switch (type)
	{
		////////////////////////////////////////
		case VEC3D_TYPE_MOTION_VECTOR:
		////////////////////////////////////////
		{
			v = &raw->mob.motion_vector;

			break;
		}
		////////////////////////////////////////
		case VEC3D_TYPE_POSITION:
		////////////////////////////////////////
		{
			v = &raw->mob.position;

			break;
		}
		////////////////////////////////////////
		case VEC3D_TYPE_WEAPON_TO_TARGET_VECTOR:
		////////////////////////////////////////
		{
			v = &raw->weapon_to_target_vector;

			break;
		}
		////////////////////////////////////////
		case VEC3D_TYPE_WEAPON_VECTOR:
		////////////////////////////////////////
		{
			v = &raw->weapon_vector;

			break;
		}
		////////////////////////////////////////
		default:
		////////////////////////////////////////
		{
			debug_fatal_invalid_vec3d_type (en, type);

			break;
		}
	}

	return (v);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_aircraft_vec3d_functions (entity_types type)
{
	fn_set_local_entity_raw_vec3d			[type][VEC3D_TYPE_MOTION_VECTOR]								= set_local_vec3d;
	fn_set_local_entity_vec3d				[type][VEC3D_TYPE_MOTION_VECTOR]								= set_local_vec3d;
	fn_set_client_server_entity_vec3d	[type][VEC3D_TYPE_MOTION_VECTOR][COMMS_MODEL_SERVER]	= set_server_vec3d;
	fn_set_client_server_entity_vec3d	[type][VEC3D_TYPE_MOTION_VECTOR][COMMS_MODEL_CLIENT]	= set_client_vec3d;
	fn_get_local_entity_vec3d				[type][VEC3D_TYPE_MOTION_VECTOR]								= get_local_vec3d;
	fn_get_local_entity_vec3d_ptr			[type][VEC3D_TYPE_MOTION_VECTOR]								= get_local_vec3d_ptr;

	fn_set_local_entity_raw_vec3d			[type][VEC3D_TYPE_POSITION]									= set_local_raw_vec3d;
	fn_set_local_entity_vec3d				[type][VEC3D_TYPE_POSITION]									= set_local_vec3d;
	fn_set_client_server_entity_vec3d	[type][VEC3D_TYPE_POSITION][COMMS_MODEL_SERVER]			= set_server_vec3d;
	fn_set_client_server_entity_vec3d	[type][VEC3D_TYPE_POSITION][COMMS_MODEL_CLIENT]			= set_client_vec3d;
	fn_get_local_entity_vec3d				[type][VEC3D_TYPE_POSITION]							 		= get_local_vec3d;
	fn_get_local_entity_vec3d_ptr			[type][VEC3D_TYPE_POSITION]									= get_local_vec3d_ptr;

	fn_set_local_entity_raw_vec3d			[type][VEC3D_TYPE_WEAPON_TO_TARGET_VECTOR]  				= set_local_vec3d;
	fn_set_local_entity_vec3d				[type][VEC3D_TYPE_WEAPON_TO_TARGET_VECTOR]  				= set_local_vec3d;
	fn_get_local_entity_vec3d				[type][VEC3D_TYPE_WEAPON_TO_TARGET_VECTOR]  				= get_local_vec3d;
	fn_get_local_entity_vec3d_ptr			[type][VEC3D_TYPE_WEAPON_TO_TARGET_VECTOR]  				= get_local_vec3d_ptr;

	fn_set_local_entity_raw_vec3d			[type][VEC3D_TYPE_WEAPON_VECTOR]								= set_local_vec3d;
	fn_set_local_entity_vec3d				[type][VEC3D_TYPE_WEAPON_VECTOR]								= set_local_vec3d;
	fn_get_local_entity_vec3d				[type][VEC3D_TYPE_WEAPON_VECTOR]								= get_local_vec3d;
	fn_get_local_entity_vec3d_ptr			[type][VEC3D_TYPE_WEAPON_VECTOR]								= get_local_vec3d_ptr;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
