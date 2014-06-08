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

#define DEBUG_MODULE	0

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define FORMATION_FILENAME				"forms.dat"
#define FORMATION_DEFAULT_FULLPATH 				"..\\common\\data\\forms.dat"

#define FORMATION_COMPONENT_FILENAME    "formcomp.dat"
#define FORMATION_COMPONENT_DEFAULT_FULLPATH 	"..\\common\\data\\formcomp.dat"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

formation_vehicle_components
	*formation_component_database = NULL;

formation_type
	**formation_database_table = NULL,
	*formation_database = NULL;

static int
	last_formation_index = 0;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char *formation_names [] =
{

	"NONE",

	"1",
	"ROW_LEFT",
	"ROW_RIGHT",
	"ECHELON_LEFT",
	"ECHELON_RIGHT",
	"COLUMN",
	"WEDGE",
   "DIAMOND",
//VJ 060305 three new formations for maverick
    "STAGGERED_TRAIL_LEFT",
    "STAGGERED_TRAIL_RIGHT",
    "80M_ROAD_NODE_16_TANKS",

	"INFANTRY_COLUMN",
	"INVALID",
	"NUM_FORMATION_TYPES"
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char *formation_display_names [] =
{

	"NONE",

	"SINGLE",
	"ROW LEFT",
	"ROW RIGHT",
	"ECHELON LEFT",
	"ECHELON RIGHT",
	"COLUMN",
	"WEDGE",
    "DIAMOND",
    "STAGGERED_TRAIL_LEFT",
    "STAGGERED_TRAIL_RIGHT",
    "TANK",
	"INFANTRY",

	"INVALID",
	"NUM_FORMATION_TYPES"
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char *formation_component_names [] =
{

	"HELICOPTER_LIGHT_ASSAULT_GROUP",
	"HELICOPTER_HEAVY_ASSAULT_GROUP",
	"HELICOPTER_MARINE_ASSAULT_GROUP_A",
	"HELICOPTER_MARINE_ASSAULT_GROUP_B",

	"HELICOPTER_LIGHT_ATTACK_GROUP_A",
	"HELICOPTER_LIGHT_ATTACK_GROUP_B",
	"HELICOPTER_HEAVY_ATTACK_GROUP_A",
	"HELICOPTER_HEAVY_ATTACK_GROUP_B",
	"HELICOPTER_MARINE_ATTACK_GROUP_A",
	"HELICOPTER_MARINE_ATTACK_GROUP_B",
	"HELICOPTER_MARINE_ATTACK_GROUP_C",
	"HELICOPTER_MARINE_ATTACK_GROUP_D",

	"HELICOPTER_LIGHT_RECON_GROUP",

	"HELICOPTER_LIGHT_RECON_ATTACK_GROUP",
	"HELICOPTER_HEAVY_RECON_ATTACK_GROUP",
	"HELICOPTER_HUNTER_KILLER_GROUP",

	"HELICOPTER_MEDIUM_LIFT_GROUP",
	"HELICOPTER_HEAVY_LIFT_GROUP_A",
	"HELICOPTER_HEAVY_LIFT_GROUP_B",

	"FIXED_WING_CLOSE_AIR_SUPPORT_GROUP",
	"FIXED_WING_MULTI_ROLE_GROUP",
	"FIXED_WING_CARRIER_BORNE_STRIKE_GROUP",
	"FIXED_WING_CARRIER_BORNE_INTERCEPTOR_GROUP",
	"FIXED_WING_MEDIUM_LIFT_GROUP",
	"FIXED_WING_HEAVY_LIFT_GROUP",
	"PRIMARY_FRONTLINE_GROUP",
	"SECONDARY_FRONTLINE_GROUP",
	"HEAVY_SAM_AAA_GROUP",
	"LIGHT_SAM_AAA_GROUP",
	"ARTILLERY_GROUP",
	"MLRS_GROUP",
	"INFANTRY",
	"INFANTRY_SAM_STANDING",
	"INFANTRY_SAM_KNEELING",
	"AIRCRAFT_CARRIER_GROUP",
	"FRIGATE_GROUP",
	"LANDING_GROUP",

	"NUM_FORMATION_COMPONENT_TYPES"
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_formation_database (void)
{

	session_list_data_type
		*current_session;

	formation_type
		*new_formation;

	FILE
		*file_ptr;

	file_tags
		tag;

	int
		loop,
		type,
		count,
		result;

	char
		name [1024],
		temp_filename [1024];

	float
		x,
		y,
		z;

	ASSERT ( formation_component_database == NULL );

	ASSERT ( formation_database == NULL );

	last_formation_index = NUM_FORMATION_TYPES;

	new_formation = NULL;

	ASSERT (!formation_database);

	current_session = get_current_game_session ();

	sprintf (temp_filename, "%s", FORMATION_DEFAULT_FULLPATH);

	file_ptr = safe_fopen (temp_filename, "r");

	while (TRUE)
	{

		tag = (file_tags) get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);

		switch (tag)
		{

			case FILE_TAG_START:
			{

				continue;
			}

			case FILE_TAG_FORMATION:
			{

				new_formation = (formation_type *) malloc_heap_mem (sizeof (formation_type));
				memset (new_formation, 0, sizeof (formation_type));

				result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
				ASSERT (result == FILE_TAG_TYPE);
				type = get_next_file_enum (file_ptr, formation_names, NUM_FORMATION_TYPES);

				new_formation->formation = (formation_types) type;

				result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
				ASSERT (result == FILE_TAG_NAME);
				get_next_file_string (file_ptr, name, sizeof (name));

				new_formation->name = (char *) malloc_heap_mem (sizeof (char) * (strlen (name) + 1));
				strcpy (new_formation->name, name);

				result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
				ASSERT (result == FILE_TAG_RADIUS);
				//new_formation->max_formation_radius = get_next_file_int (file_ptr);

				result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
				ASSERT (result == FILE_TAG_COUNT);
				count = get_next_file_int (file_ptr);

				new_formation->number_in_formation = count;

				if (count > 0)
				{

					new_formation->sites = (vec3d *) malloc_heap_mem (sizeof (vec3d) * (count));

					loop = 0;

  					#if DEBUG_MODULE

					debug_log ("EN_FORMS: loading formation %s", formation_names [new_formation->formation]);

					#endif

					while (loop < count)
					{

						result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
						ASSERT (result == FILE_TAG_POSITION);

						x = get_next_file_float (file_ptr);
						y = get_next_file_float (file_ptr);
						z = get_next_file_float (file_ptr);

						new_formation->sites [loop].x = x;
						new_formation->sites [loop].y = y;
						new_formation->sites [loop].z = z;

						#if DEBUG_MODULE

						debug_log ("	adding site %f, %f, %f", x, y, z);

						#endif

						loop ++;
					}
				}

				result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);

				ASSERT (result == FILE_TAG_END);

				//
				// link into database
				//

				new_formation->next = formation_database;

				formation_database = new_formation;

				break;
			}

			case FILE_TAG_END:
			{

				fclose (file_ptr);

				return;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_formation_database_table (void)
{

	formation_type
		*this_formation;

	if (formation_database_table)
	{

		free_mem (formation_database_table);
	}

	formation_database_table = (formation_type **) malloc_heap_mem (sizeof (formation_type *) * (last_formation_index + 1));

	memset (formation_database_table, 0, sizeof (formation_type *) * (last_formation_index + 1));

	this_formation = formation_database;

	while (this_formation)
	{

		formation_database_table [this_formation->formation] = this_formation;

		this_formation = this_formation->next;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int add_formation_to_database (int number_in_formation, vec3d *site_positions)
{

	formation_type
		*new_formation;

	char
		name [128];

	new_formation = (formation_type *) malloc_heap_mem (sizeof (formation_type));
	memset (new_formation, 0, sizeof (formation_type));

	last_formation_index ++;
	new_formation->formation = (formation_types) last_formation_index;

	sprintf (name, "USER FORMATION %d", last_formation_index);
	new_formation->name = (char *) malloc_heap_mem (sizeof (char) * (strlen (name) + 1));
	strcpy (new_formation->name, name);

	new_formation->number_in_formation = number_in_formation;

	if (number_in_formation > 0)
	{

		new_formation->sites = (vec3d *) malloc_heap_mem (sizeof (vec3d) * (number_in_formation));

		memcpy (new_formation->sites, site_positions, sizeof (vec3d) * number_in_formation);
	}

	//
	// link into database
	//

	new_formation->next = formation_database;

	formation_database = new_formation;

	return last_formation_index;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_formation_database_count (void)
{
	return last_formation_index;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_formation_database (void)
{

	formation_type
		*destroy_formation;

	while (formation_database)
	{

		destroy_formation = formation_database;

		formation_database = formation_database->next;

		if (destroy_formation->name)
		{

			free_mem (destroy_formation->name);
		}

		if (destroy_formation->sites)
		{

			free_mem (destroy_formation->sites);
		}

		free_mem (destroy_formation);
	}

	// deinitialise lookup table too

	if (formation_database_table)
	{

		free_mem (formation_database_table);

		formation_database_table = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

formation_type *get_formation (formation_types formation)
{
	formation_type
		*this_formation;

	ASSERT (formation_database);

	if (formation_database_table)
	{

		return formation_database_table [formation];
	}

	this_formation = formation_database;

	while (this_formation)
	{

		if (this_formation->formation == formation)
		{

			return this_formation;
		}

		this_formation = this_formation->next;
	}

	return NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

short int get_number_in_formation (formation_types formation)
{

	formation_type
		*this_formation;

	ASSERT (formation_database);

	this_formation = get_formation (formation);

	if (this_formation)
	{

		return this_formation->number_in_formation;
	}

	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char *get_formation_name (formation_types formation)
{

	formation_type
		*this_formation;

	ASSERT (formation_database);

	this_formation = get_formation (formation);

	if (this_formation)
	{

		return this_formation->name;
	}

	return NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_formation_member_radius (formation_types form, int member_count)
{

	formation_type
		*formation_data;

	int
		loop,
		biggest_radius_index;

	float
		radius,
		sqr_radius,
		biggest_sqr_radius;

	formation_data = get_formation (form);

	biggest_sqr_radius = 0.0;

	biggest_radius_index = 0;

	for (loop = 0; loop < member_count; loop ++)
	{

		sqr_radius = (formation_data->sites [loop].x * formation_data->sites [loop].x) + (formation_data->sites [loop].z * formation_data->sites [loop].z);

		if (sqr_radius > biggest_sqr_radius)
		{

			biggest_sqr_radius = sqr_radius;

			biggest_radius_index = loop;
		}
	}

	radius = get_3d_vector_magnitude (&formation_data->sites [biggest_radius_index]);

	return radius;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_formation_position (formation_types form, int index, vec3d *vec)
{

	formation_type
		*formation_data;

	formation_data = get_formation (form);

	vec->x = formation_data->sites [index].x;
	vec->y = formation_data->sites [index].y;
	vec->z = formation_data->sites [index].z;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_formation_component_database (void)
{

	formation_type
		*formation_data;

	session_list_data_type
		*current_session;

	formation_vehicle_components
		*new_formation_component;

	FILE
		*file_ptr;

	file_tags
		tag;

	int
		loop,
		type,
		count,
		result;

	char
		temp_filename [1024];

	ASSERT (!formation_component_database);

	current_session = get_current_game_session ();

	file_ptr = NULL;

	// check if this campaign has its own formation component database
	if (current_game_session->data_path && current_game_session->campaign_directory)
	{
		sprintf (temp_filename, "%s\\%s\\%s", current_game_session->data_path, current_game_session->campaign_directory, FORMATION_COMPONENT_FILENAME);
		if (file_exist(temp_filename))
			file_ptr = safe_fopen (temp_filename, "r");

		if (file_ptr)
		{
			debug_log("formcomp file: %s", temp_filename);
		}
	}

	// check if this map has its own formation component database
	if (!file_ptr && current_game_session->data_path)
	{
		sprintf (temp_filename, "%s\\%s", current_game_session->data_path, FORMATION_COMPONENT_FILENAME);
		if (file_exist(temp_filename))
			file_ptr = safe_fopen (temp_filename, "r");

		if (file_ptr)
		{
			debug_log("formcomp file: %s", temp_filename);
		}
	}

	// use default if there is no specific one
	if (!file_ptr)
	{
		sprintf (temp_filename, "%s", FORMATION_COMPONENT_DEFAULT_FULLPATH);

		file_ptr = safe_fopen (temp_filename, "r");
	}

	while (TRUE)
	{

		tag = (file_tags) get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);

		switch (tag)
		{

			case FILE_TAG_START:
			{

				continue;
			}

			case FILE_TAG_FORMATION_COMPONENT:
			{

				new_formation_component = (formation_vehicle_components *) malloc_heap_mem (sizeof (formation_vehicle_components));
				memset (new_formation_component, 0, sizeof (formation_vehicle_components));

				result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
				ASSERT (result == FILE_TAG_TYPE);
				type = get_next_file_enum (file_ptr, formation_component_names, NUM_FORMATION_COMPONENT_TYPES);

				new_formation_component->formation_component = (formation_component_types) type;

				result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
				ASSERT (result == FILE_TAG_TYPE);
				type = get_next_file_enum (file_ptr, formation_names, NUM_FORMATION_TYPES);

				new_formation_component->formation = (formation_types) type;

				result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);
				ASSERT (result == FILE_TAG_COUNT);
				count = get_next_file_int (file_ptr);

				formation_data = get_formation (new_formation_component->formation);

				new_formation_component->group_type = get_next_file_enum (file_ptr, entity_sub_type_group_names, NUM_ENTITY_SUB_TYPE_GROUPS);

				ASSERT (count <= formation_data->number_in_formation);

				new_formation_component->count = count;

				if (count > 0)
				{

					new_formation_component->components = (entity_sub_types *) malloc_heap_mem (sizeof (entity_sub_types) * (count * 2));

					loop = 0;

					#if DEBUG_MODULE

					debug_log ("EN_FORMS: loading formation components %s, formation %s", formation_component_names [new_formation_component->formation_component], formation_names [new_formation_component->formation]);

					#endif

					while (loop < count * 2)
					{

						switch (group_database [new_formation_component->group_type].default_landing_type)
						{

							case ENTITY_SUB_TYPE_LANDING_GROUND:
							case ENTITY_SUB_TYPE_LANDING_PEOPLE:
							case ENTITY_SUB_TYPE_LANDING_SEA:
							{

								type = get_next_file_enum (file_ptr, entity_sub_type_vehicle_names, NUM_ENTITY_SUB_TYPE_VEHICLES);

								#if DEBUG_MODULE
								debug_log ("	adding component %d %s", loop, entity_sub_type_vehicle_names [type]);
								#endif

								break;
							}

							case ENTITY_SUB_TYPE_LANDING_HELICOPTER:
							case ENTITY_SUB_TYPE_LANDING_FIXED_WING:
							case ENTITY_SUB_TYPE_LANDING_FIXED_WING_TRANSPORT:
							{

								type = get_next_file_enum (file_ptr, entity_sub_type_aircraft_names, NUM_ENTITY_SUB_TYPE_AIRCRAFT);

								#if DEBUG_MODULE
								debug_log ("	adding component %d %s", loop, entity_sub_type_aircraft_names [type]);
								#endif

								break;
							}
						}

						new_formation_component->components [loop] = type;

						loop ++;
					}
				}

				result = get_next_file_tag (file_ptr, application_tag_strings, FILE_TAG_APPLICATION_LAST_TAG);

				ASSERT (result == FILE_TAG_END);

				//
				// link into database
				//

				new_formation_component->next = formation_component_database;

				formation_component_database = new_formation_component;

				break;
			}

			case FILE_TAG_END:
			{

				fclose (file_ptr);

				return;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_formation_component_database (void)
{

	formation_vehicle_components
		*destroy_formation_component;

	while (formation_component_database)
	{

		destroy_formation_component = formation_component_database;

		formation_component_database = formation_component_database->next;

		if (destroy_formation_component->components)
		{

			free_mem (destroy_formation_component->components);
		}

		free_mem (destroy_formation_component);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

formation_vehicle_components *get_formation_components (formation_component_types formation_component)
{

	formation_vehicle_components
		*this_formation_component;

	ASSERT (formation_component_database);

	this_formation_component = formation_component_database;

	while (this_formation_component)
	{

		if (this_formation_component->formation_component == formation_component)
		{

			return this_formation_component;
		}

		this_formation_component = this_formation_component->next;
	}

	return NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
