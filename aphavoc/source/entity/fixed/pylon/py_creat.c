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

static int load_local_pylon_entities (const char *name)
{
	entity
		*last_entity,
		*last_last_entity,
		*new_entity;

	entity_sub_types
		sub_type;

	int
		type,
		node_count,
		*node_link_count,
		path_count,
		node_loop,
		path_loop,
		start,
		end,
		link_count,
		link_loop;

	vec3d
		*node_positions,
		pos;

	FILE
		*pylon_node_file_ptr,
		*pylon_link_file_ptr;

	char
		filename [1024];

	session_list_data_type
		*current_session;

	//
	// Create "Node" Pylons
	//

	ASSERT (get_valid_current_game_session ());

	ASSERT (name);

	current_session = get_current_game_session ();

	sprintf (filename, "%s\\route\\%s.nde", current_session->data_path, name);

	if (file_exist (filename))
	{
		pylon_node_file_ptr = safe_fopen (filename, "rb");

		fread (&node_count, sizeof (int), 1, pylon_node_file_ptr);

		node_positions = (vec3d *) malloc_heap_mem (sizeof (vec3d) * node_count);

		node_link_count = (int *) malloc_heap_mem (sizeof (int) * node_count);

		for (node_loop = 0 ; node_loop < node_count ; node_loop ++)
		{
			fread (&pos, sizeof (vec3d), 1, pylon_node_file_ptr);

			node_positions [node_loop].x = pos.x;
			node_positions [node_loop].y = pos.y;
			node_positions [node_loop].z = pos.z;

			node_link_count [node_loop] = 0;
		}

		fclose (pylon_node_file_ptr);

		//
		// Create "Link" Pylons
		//

		sprintf (filename, "%s\\route\\%s.wp", current_session->data_path, name);

		pylon_link_file_ptr = safe_fopen (filename, "rb");

		fread (&path_count, sizeof (int), 1, pylon_link_file_ptr);

		new_entity = NULL;

		for (path_loop = 0 ; path_loop < path_count ; path_loop ++)
		{
			fread (&start, sizeof (int), 1, pylon_link_file_ptr);

			fread (&end, sizeof (int), 1, pylon_link_file_ptr);

			fread (&type, sizeof (int), 1, pylon_link_file_ptr);

			fread (&link_count, sizeof (int), 1, pylon_link_file_ptr);

			node_link_count [start] += 1;
			node_link_count [end] += 1;

			if (link_count > 0)
			{
				last_entity = NULL;

				last_last_entity = NULL;

				for (link_loop = 0 ; link_loop < link_count ; link_loop ++)
				{
					fread (&pos, sizeof (vec3d), 1, pylon_link_file_ptr);

					if (link_loop == 0)
					{
						sub_type = ENTITY_SUB_TYPE_FIXED_ELECTRICITY_PYLON_START_TERMINATOR;
					}
					else if (link_loop == link_count - 1)
					{
						sub_type = ENTITY_SUB_TYPE_FIXED_ELECTRICITY_PYLON_END_TERMINATOR;
					}
					else 
					{
						sub_type = ENTITY_SUB_TYPE_FIXED_ELECTRICITY_PYLON_STANDARD;
					}

					new_entity = create_local_entity
					(
						ENTITY_TYPE_PYLON,
						ENTITY_INDEX_DONT_CARE,
						ENTITY_ATTR_INT_VALUE (INT_TYPE_ENTITY_SUB_TYPE, sub_type),
						ENTITY_ATTR_VEC3D (VEC3D_TYPE_POSITION, pos.x, pos.y, pos.z),
						ENTITY_ATTR_FLOAT_VALUE (FLOAT_TYPE_HEADING, 0),
						ENTITY_ATTR_PTR_VALUE (PTR_TYPE_SUCC, last_entity),
						ENTITY_ATTR_END
					);

					calculate_pylon_heading (last_last_entity, last_entity, new_entity, &node_positions [start], &node_positions [end]);

					last_last_entity = last_entity;

					last_entity = new_entity;
				}

				// last pylon in the link
				calculate_pylon_heading (last_last_entity, last_entity, NULL, &node_positions [start], &node_positions [end]);
			}
		}

		for (node_loop = 0 ; node_loop < node_count ; node_loop ++)
		{
			//
			// create node entities here
			//
		}

		fclose (pylon_link_file_ptr);

		free_mem (node_positions);

		free_mem (node_link_count);

		return TRUE;
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_local_pylon_entities (pack_modes pack_mode)
{
	debug_assert (get_comms_model () == COMMS_MODEL_SERVER);

	if (pack_mode == PACK_MODE_BROWSE_SESSION)
	{
		return;
	}

	if (!load_local_pylon_entities ("utils"))
	{
		load_local_pylon_entities ("utildata");
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static entity *create_local (entity_types type, int index, char *pargs)
{
	entity
		*en;

	pylon
		*raw;

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

		raw = (pylon *) malloc_fast_mem (sizeof (pylon));

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

		memset (raw, 0, sizeof (pylon));

		//
		// fixed
		//

		raw->fix.position.x = MID_MAP_X;
		raw->fix.position.y = MID_MAP_Y;
		raw->fix.position.z = MID_MAP_Z;

		raw->fix.object_3d_shape = OBJECT_3D_INVALID_OBJECT_INDEX;

		raw->fix.alive = TRUE;

		raw->fix.side = ENTITY_SIDE_NEUTRAL;

		//
		// pylon
		//

		raw->damage_level = PYLON_DAMAGE_LEVEL;

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

		////////////////////////////////////////
		//
		// RESOLVE DEFAULT VALUES
		//
		////////////////////////////////////////

		if (raw->fix.object_3d_shape == OBJECT_3D_INVALID_OBJECT_INDEX)
		{
			raw->fix.object_3d_shape = pylon_default_object_3d_shape (get_pylon_sub_type (raw->fix.sub_type));
		}

		////////////////////////////////////////
		//
		// BUILD COMPONENTS
		//
		////////////////////////////////////////

		////////////////////////////////////////
		//
		// LINK INTO SYSTEM
		//
		////////////////////////////////////////

		insert_local_entity_into_parents_child_list (en, LIST_TYPE_SECTOR, get_local_sector_entity (&raw->fix.position), NULL);
	}

	return (en);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void overload_pylon_create_functions (void)
{
	fn_create_local_entity[ENTITY_TYPE_PYLON]		 				 					 = create_local;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
