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

#include "ai_dbase.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define AI_DATABASE_DEBUG 0

#define AI_POPULATION_NAME_FILENAME "route\\popname.dat"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static const char
	*population_name_type_strings [] =
	{
		"KEYSITE",
		"TOWN",

		"NUM_POPULATION_NAME_TYPES"
	};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

population_name_database_type
	*population_name_database = NULL;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_ai_database (void)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_ai_database (void)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void load_ai_sector_data (const char *sector_filename)
{

	entity
		*sector = nullptr;

	int
		size,
		side,
		loop_x,
		loop_z;

	FILE
		*file_ptr = nullptr;

	// JB 030311 Enable running out of separate directories
	file_ptr = safe_fopen (sector_filename, "rb");

	if (!file_ptr)
	{

		return;
	}

	size = file_size (sector_filename);

	ASSERT (size == (NUM_MAP_X_SECTORS * NUM_MAP_Z_SECTORS) * sizeof (int));

	if (file_ptr)
	{
	
		for (loop_x = 0; loop_x < NUM_MAP_X_SECTORS; loop_x ++)
		{
	
			for (loop_z = 0; loop_z < NUM_MAP_Z_SECTORS; loop_z ++)
			{
	
				fread (&side, 1, sizeof (int), file_ptr);
	
				sector = get_local_raw_sector_entity (loop_x, loop_z);
	
				set_local_entity_int_value (sector, INT_TYPE_SIDE, side);
			}
		}
	}

	fclose (file_ptr);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_population_name_database (void)
{

	FILE
		*file_ptr = nullptr;

	population_name_database_type
		*new_city = nullptr;

	session_list_data_type
		*current_session = nullptr;

	char
		temp_filename [256];

	file_tags
		result,
		tag;

	current_session = get_current_game_session ();

	sprintf (temp_filename, "%s\\%s", current_session->data_path, AI_POPULATION_NAME_FILENAME);

	// JB 030311 Enable running out of separate directories
	file_ptr = safe_fopen (temp_filename, "r");

	if (!file_ptr)
	{

		return;
	}

	deinitialise_population_name_database ();

	while (TRUE)
	{

		tag = ( file_tags ) get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);

		switch (tag)
		{

			case FILE_TAG_START:
			{

				continue;
			}

			case FILE_TAG_END:
			{

				fclose (file_ptr);

				return;
			}

			case FILE_TAG_NAME:
			{

				char
					name [128];

				//
				// Name
				//

				get_next_file_string (file_ptr, name, sizeof (name));

				new_city = (population_name_database_type *) malloc_heap_mem (sizeof (population_name_database_type));

				new_city->name = ( char * ) malloc_heap_mem (strlen (name) + 4);

				new_city->next = population_name_database;

				population_name_database = new_city;

				sprintf (new_city->name, "%s", name);

				//
				// Type
				//

				result = ( file_tags ) get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);

				ASSERT (result == FILE_TAG_POPULATION_TYPE);

				new_city->type = ( population_name_types ) get_next_file_enum (file_ptr, population_name_type_strings, NUM_POPULATION_NAME_TYPES);

				//
				// Position
				//
		
				result = (file_tags) get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);

				ASSERT (result == FILE_TAG_POSITION);

				new_city->x = get_next_file_float (file_ptr);
				new_city->z = get_next_file_float (file_ptr);

				//
				// Zoom Level
				//

				result = (file_tags) get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);

				ASSERT (result == FILE_TAG_ZOOM);

				new_city->zoom = get_next_file_float (file_ptr) * (1.0 * KILOMETRE);

				#if DEBUG_MODULE

				debug_log ("AI_DBASE: new city name %s at %f, %f", new_city->name, new_city->x, new_city->z);

				#endif

				break;
			}

			default:
			{

				debug_log ("AI_DBASE: city name database: unknown campaign tag %d (string %s)", tag, application_tag_strings [tag]);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_population_name_database (void)
{

	if (population_name_database)
	{

		population_name_database_type
			*destroy_city = nullptr;

		while (population_name_database)
		{
		
			destroy_city = population_name_database;

			population_name_database = population_name_database->next;

			if (destroy_city->name)
			{

				free_mem (destroy_city->name);
			}

			free_mem (destroy_city);
		}
	}

	population_name_database = NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
