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



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "project.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG_MODULE 0

#define WAYPOINT_ALTITUDE route_waypoint_positions[current_route_waypoint_offset].position.y

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum TEMPLATE_TYPE
{

	TEMPLATE_TYPE_INVALID,
	TEMPLATE_TYPE_SPACE,
	TEMPLATE_TYPE_HOUSING,
	TEMPLATE_TYPE_OFFICE,
	TEMPLATE_TYPE_INDUSTRY,
	TEMPLATE_TYPE_CULTURAL,
	TEMPLATE_TYPE_CHURCH,
	TEMPLATE_TYPE_OUTSKIRTS,
	TEMPLATE_TYPE_AIRFIELD,
	TEMPLATE_TYPE_AAASAM,
	TEMPLATE_TYPE_PORTSE,
	TEMPLATE_TYPE_PORTNW,
	TEMPLATE_TYPE_MILITARY,
	TEMPLATE_TYPE_FARM,
	TEMPLATE_TYPE_OIL,

	TEMPLATE_TYPE_KEY_POWER,
	TEMPLATE_TYPE_KEY_RADIO,
	TEMPLATE_TYPE_KEY_INDUSTRY,
	TEMPLATE_TYPE_KEY_PORT,
	TEMPLATE_TYPE_KEY_MILITARY,
	TEMPLATE_TYPE_KEY_OIL,

	TEMPLATE_TYPE_CONSTRUCT,
	TEMPLATE_TYPE_RUIN,
	TEMPLATE_TYPE_WATER,

	TEMPLATE_TYPE_ROAD_X,
	TEMPLATE_TYPE_ROAD_JUNC_N,
	TEMPLATE_TYPE_ROAD_JUNC_S,
	TEMPLATE_TYPE_ROAD_JUNC_E,
	TEMPLATE_TYPE_ROAD_JUNC_W,
	TEMPLATE_TYPE_ROAD_CROSS,
	TEMPLATE_TYPE_ROAD_Z,

	TEMPLATE_TYPE_ROAD,
};

typedef enum TEMPLATE_TYPE template_type;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct TEMPORARY_TEMPLATE
{

	int
		number_of_objects;

	template_type
		type;

	object_3d_index_numbers
		approximation_object,
		base_object,
		routes_object;

	struct TEMPORARY_TEMPLATE_OBJECT
		*objects;
};

typedef struct TEMPORARY_TEMPLATE temporary_template;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct TEMPORARY_TEMPLATE_OBJECT
{

	object_3d_index_numbers
		object_index;

	float
		x,
		y,
		heading;
};

typedef struct TEMPORARY_TEMPLATE_OBJECT temporary_template_object;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct TROOP_LANDING_ROUTE_INFORMATION
{

	int
		number_of_landing_route_nodes,
		number_of_takeoff_route_nodes,
		landing_position_valid;

	vec3d
		*landing_route,
		*takeoff_route,
		landing_position;

	float
		heading;
};

typedef struct TROOP_LANDING_ROUTE_INFORMATION troop_landing_route_information;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*static*/ void validate_airport_links ( object_3d_index_numbers index );

static void reset_population_sector_values ( int width, int height );

static void process_population_forces ( psd_rgb *ptr, int width, int height );

static entity_sides get_initial_sector_side ( int x_sec, int z_sec );

static void read_population_templates ( FILE *fp );

static void read_population_city_placements ( FILE *fp );

static void read_population_airfield_placements ( FILE *fp );

static void read_population_sam_placements ( FILE *fp );

static unsigned int get_waypoint_inhangar_bits ( route_waypoint_position *waypoint, object_3d_instance *inst3d );

static int get_object_index_from_name ( char *name );

static object_3d_database_entry * get_airfield_waypoint_route_object ( object_3d_instance *instance, object_3d_sub_object_index_numbers index );

static void insert_airport_fixedwing_routes ( int entity_subtype, vec3d *position, object_3d_database_entry *landing, object_3d_database_entry *takeoff );

static void insert_airport_helicopter_routes ( vec3d *position, object_3d_database_entry *landing, object_3d_database_entry *takeoff, object_3d_database_entry *landing_holding, object_3d_database_entry *takeoff_holding );

static void insert_airport_routed_vehicles_routes ( vec3d *position, object_3d_database_entry *landing, object_3d_database_entry *takeoff );

static void insert_airport_ship_routes ( vec3d *position, object_3d_database_entry *landing, object_3d_database_entry *takeoff );

static void insert_airport_general_takeoff_landing_routes ( int entity_subtype, vec3d *position, object_3d_database_entry *landing_route, object_3d_database_entry *takeoff_route );

static void insert_airport_holding_routes ( vec3d *position, object_3d_database_entry *landing_holding_route, object_3d_database_entry *takeoff_holding_route );

static void create_airfield_waypoint ( entity_sub_types type, vec3d *waypoint_world_pos, int formation_index, float altitude );

static void insert_airfield_buildings ( int side, object_3d_instance *instance );

static void insert_keysite_or_city_object ( entity *city, entity *keysite, entity *keysite_group, entity_sides keysite_side, int object_number, float world_x, float world_y, float world_z, float heading );

static unsigned char *get_keysite_name (float x, float z, entity_sides *side);

static void initialise_object_3d_troop_landing_routes ( void );

static void process_population_importance ( psd_rgb *ptr, int side, int width, int height );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int
	current_map_max_z;

int
	number_of_temporary_templates;

temporary_template
	*temporary_templates;

vec3d
	temporary_relative_waypoints[256];

static int
	population_file_version2;

static psd_rgb
	*current_initial_sector_sides = NULL;

static int
	current_initial_sector_sides_x_length,
	current_initial_sector_sides_z_length;

char *blue_force_carrier_names[] =
	{

		"USS TARAWA",
		"USS SAIPAN",
		"USS PELELIU",
		"USS NASSAU",
		"USS BELLEAU WOOD",
		"USS ENTERPRISE",
		"USS CARRIER 2",
		"USS CARRIER 3",
		"USS CARRIER 4",
		"USS CARRIER 5",
		"USS CARRIER 6",
		"USS CARRIER 7",
		"USS CARRIER 8",
		"USS CARRIER 9",
	};

char *red_force_carrier_names[] =
	{

		"BODRY",
		"ZHARKY",
		"LADNY",
		"SVIREPY",
		"LEGKY",
		"SILNY",
		"ZADORNY",
		"DOBLESTNY",
		"CIS CARRIER 1",
		"CIS CARRIER 2",
		"CIS CARRIER 3",
		"CIS CARRIER 4",
		"CIS CARRIER 5",
		"CIS CARRIER 6",
		"CIS CARRIER 7",
		"CIS CARRIER 8",
		"CIS CARRIER 9",
	};

object_3d_instance
	*current_airport_inst3d = NULL;

troop_landing_route_information
	*object_3d_troop_routes = NULL;

static int
	*population_importances = NULL;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void read_sector_side_file ( char *sides_filename )
{

	#if DEBUG_MODULE

	debug_log ( "READING IN SIDE DATA" );

	#endif

	if ( sides_filename )
	{

		int
			layer,
			width,
			height,
			channels;

		unsigned char
			*sides_data;

		sides_data = load_psd_file ( sides_filename, &width, &height, &channels );

		if ( sides_data )
		{

			psd_rgb
				*ptr;

			ASSERT ( channels == 3 );
			ASSERT ( width == ( MAX_MAP_X_SECTOR + 1 ) );
			ASSERT ( height == ( MAX_MAP_Z_SECTOR + 1 ) );

			//
			// Reset the population values
			//

			reset_population_sector_values ( width, height );

			//
			// Now do the special layers
			//

			if ( number_of_psd_layers == 0 )
			{

				//
				// Process the forces...
				//

				process_population_forces ( ( psd_rgb * ) sides_data, width, height );
			}
			else
			{
				for ( layer = 0; layer < number_of_psd_layers; layer++ )
				{

					ptr = ( psd_rgb * ) psd_layers[layer].data;

					if ( ( strnicmp ( psd_layers[layer].name, "BACKGROUND", strlen ( "BACKGROUND" ) ) == 0 ) ||
							( strlen ( psd_layers[layer].name ) == 0 ) )
					{

						process_population_forces ( ptr, width, height );
					}
					else if ( strnicmp ( psd_layers[layer].name, "IMPORTANCE", strlen ( "IMPORTANCE" ) ) == 0 )
					{

						process_population_importance ( ptr, ENTITY_SIDE_RED_FORCE, width, height );
					}
				}
			}

			safe_free ( sides_data );
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reset_population_sector_values ( int width, int height )
{

	int
		x,
		y;

	sector
		*sector_raw;

	for ( y = 0; y < height; y++ )
	{

		for ( x = 0; x < width; x++ )
		{

			entity
				*sector;

			sector = get_local_raw_sector_entity ( x, ( MAX_MAP_Z_SECTOR - y ) );

			sector_raw = get_local_entity_data ( sector );

			set_local_entity_int_value ( sector, INT_TYPE_SIDE, ENTITY_SIDE_NEUTRAL );
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void process_population_forces ( psd_rgb *ptr, int width, int height )
{

	int
		x,
		y;

	if ( current_initial_sector_sides )
	{

		safe_free ( current_initial_sector_sides );

		current_initial_sector_sides = NULL;
	}

	current_initial_sector_sides = safe_malloc ( sizeof ( psd_rgb ) * width * height );

	memcpy ( current_initial_sector_sides, ptr, ( sizeof ( psd_rgb ) * width * height ) );

	current_initial_sector_sides_x_length = width;

	current_initial_sector_sides_z_length = height;

	for ( y = 0; y < height; y++ )
	{

		for ( x = 0; x < width; x++ )
		{

			entity
				*sector;

			if ( ptr->r > 240 )
			{

				sector = get_local_raw_sector_entity (x, ( MAX_MAP_Z_SECTOR - y ) );

				set_local_entity_int_value ( sector, INT_TYPE_SIDE, ENTITY_SIDE_RED_FORCE );
			}
			else if ( ptr->b > 240 )
			{

				sector = get_local_raw_sector_entity ( x, ( MAX_MAP_Z_SECTOR - y ) );

				set_local_entity_int_value ( sector, INT_TYPE_SIDE, ENTITY_SIDE_BLUE_FORCE );
			}
			else
			{

				sector = get_local_raw_sector_entity ( x, ( MAX_MAP_Z_SECTOR - y ) );

				set_local_entity_int_value ( sector, INT_TYPE_SIDE, ENTITY_SIDE_NEUTRAL );

				debug_fatal ("POPREAD: neutral sector %d, %d", x, y);
			}

			ptr++;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void process_population_importance ( psd_rgb *ptr, int side, int width, int height )
{

	int
		x,
		y;

	ASSERT ( width == ( MAX_MAP_X_SECTOR + 1 ) );
	ASSERT ( height == ( MAX_MAP_Z_SECTOR + 1 ) );

	if ( population_importances )
	{

		safe_free ( population_importances );

		population_importances = NULL;
	}

	population_importances = safe_malloc ( sizeof ( int ) * width * height );

	for ( y = 0; y < height; y++ )
	{

		for ( x = 0; x < width; x++ )
		{

			population_importances[ ( MAX_MAP_Z_SECTOR - y ) * width + x ] = ptr->r;

			ptr++;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

entity_sides get_initial_sector_side ( int x_sec, int z_sec )
{

	psd_rgb
		*ptr;

	ASSERT ( current_initial_sector_sides );

	z_sec = ( current_initial_sector_sides_z_length - 1 ) - z_sec;

	ptr = &current_initial_sector_sides[ ( current_initial_sector_sides_x_length * z_sec ) + x_sec ];

	if ( ptr->r > 240 )
	{

		return ( ENTITY_SIDE_RED_FORCE );
	}
	else if ( ptr->b > 240 )
	{

		return ( ENTITY_SIDE_BLUE_FORCE );
	}
	else
	{

		return ( ENTITY_SIDE_NEUTRAL );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void read_population_placement_file ( char *placement_filename )
{

	FILE
		*fp;

	int
		count;

	current_map_max_z = terrain_3d_max_map_z;
	current_map_max_z /= 100;
	current_map_max_z *= 100;

	validate_airport_links ( OBJECT_3D_AMERICAN_AIRPORT01 );
	validate_airport_links ( OBJECT_3D_AMERICAN_AIRPORT02 );
	validate_airport_links ( OBJECT_3D_AMERICAN_AIRPORT03 );
	validate_airport_links ( OBJECT_3D_AMERICAN_FARP01 );
	validate_airport_links ( OBJECT_3D_AMERICAN_FARP02 );
	validate_airport_links ( OBJECT_3D_AMERICAN_FARP03 );
	validate_airport_links ( OBJECT_3D_AMERICAN_FARP04 );
	validate_airport_links ( OBJECT_3D_AMERICAN_FARP05 );
	validate_airport_links ( OBJECT_3D_AMERICAN_FARP06 );
	validate_airport_links ( OBJECT_3D_AMERICAN_FARP07 );
	validate_airport_links ( OBJECT_3D_AMERICAN_FARP08 );
	validate_airport_links ( OBJECT_3D_AMERICAN_FARP09 );
//	validate_airport_links ( OBJECT_3D_AMERICAN_FARP10 );
	validate_airport_links ( OBJECT_3D_AMERICAN_FARP11 );
	validate_airport_links ( OBJECT_3D_AMERICAN_FARP12 );
	validate_airport_links ( OBJECT_3D_AMERICAN_FARP13 );
	validate_airport_links ( OBJECT_3D_RUSSIAN_AIRPORT01 );
	validate_airport_links ( OBJECT_3D_RUSSIAN_AIRPORT02 );
	validate_airport_links ( OBJECT_3D_RUSSIAN_AIRPORT03 );
	validate_airport_links ( OBJECT_3D_RUSSIAN_AIRPORT04 );
	validate_airport_links ( OBJECT_3D_RUSSIAN_AIRPORT05 );
	validate_airport_links ( OBJECT_3D_RUSSIAN_AIRPORT06 );
	validate_airport_links ( OBJECT_3D_RUSSIAN_AIRPORT07 );
	validate_airport_links ( OBJECT_3D_RUSSIAN_AIRPORT09 );
	validate_airport_links ( OBJECT_3D_RUSSIAN_AIRPORT10 );
	validate_airport_links ( OBJECT_3D_RUSSIAN_AIRPORT11 );
	validate_airport_links ( OBJECT_3D_RUSSIAN_AIRPORT12 );
	validate_airport_links ( OBJECT_3D_RUSSIAN_AIRPORT13 );
	validate_airport_links ( OBJECT_3D_RUSSIAN_FARP01 );
	validate_airport_links ( OBJECT_3D_RUSSIAN_FARP02 );
	validate_airport_links ( OBJECT_3D_RUSSIAN_FARP03 );
	validate_airport_links ( OBJECT_3D_RUSSIAN_FARP04 );
	validate_airport_links ( OBJECT_3D_RUSSIAN_FARP05 );
	validate_airport_links ( OBJECT_3D_RUSSIAN_FARP06 );
	validate_airport_links ( OBJECT_3D_RUSSIAN_FARP07 );
	validate_airport_links ( OBJECT_3D_RUSSIAN_FARP08 );
	validate_airport_links ( OBJECT_3D_RUSSIAN_FARP09 );
//	validate_airport_links ( OBJECT_3D_RUSSIAN_FARP10 );
	validate_airport_links ( OBJECT_3D_RUSSIAN_FARP11 );
	validate_airport_links ( OBJECT_3D_RUSSIAN_FARP12 );
	validate_airport_links ( OBJECT_3D_RUSSIAN_FARP13 );

	//
	// Read in the placement file
	//

	if (!placement_filename)
	{

		return;
	}

	fp = safe_fopen ( placement_filename, "rb" );

	//
	// First the city block templates
	//

	#if DEBUG_MODULE

	debug_log ( "Starting to build cities" );

	#endif

	read_population_templates ( fp );

	//
	// Next the actual placement of the templates
	//

	#if DEBUG_MODULE

	debug_log ( "Placing the templates" );

	#endif

	read_population_city_placements ( fp );

	//
	// Free up the template memory
	//

	if ( number_of_temporary_templates )
	{

		for ( count = 0; count < number_of_temporary_templates; count++ )
		{

			if ( temporary_templates[count].objects )
			{

				safe_free ( temporary_templates[count].objects );

				temporary_templates[count].objects = NULL;
			}
		}

		if ( temporary_templates )
		{

			safe_free ( temporary_templates );

			temporary_templates = NULL;
		}
	}

	#if DEBUG_MODULE

	debug_log ( "Finished building cities" );

	#endif

	//
	// Next the airfield placements
	//

	read_population_airfield_placements ( fp );

	initialise_keysite_farp_enable (get_local_force_entity (ENTITY_SIDE_BLUE_FORCE));

	initialise_keysite_farp_enable (get_local_force_entity (ENTITY_SIDE_RED_FORCE));

	//
	// Read in the AAA/SAM placements
	//

	read_population_sam_placements ( fp );

	#if DEBUG_MODULE

	debug_log ( "Finished airport placement" );

	#endif

	fclose ( fp );

	initialise_formation_database_table ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void read_population_templates ( FILE *fp )
{

	int
		count;

	population_file_version2 = FALSE;

	fread ( &number_of_temporary_templates, sizeof ( int ), 1, fp );

	if ( number_of_temporary_templates < 0 )
	{

		population_file_version2 = TRUE;

		number_of_temporary_templates = -number_of_temporary_templates;
	}

	temporary_templates = safe_malloc ( number_of_temporary_templates * sizeof ( temporary_template ) );

	for ( count = 0; count < number_of_temporary_templates; count++ )
	{

		temporary_template_object
			*objects;

		int
			valid,
			object_count,
			string_length;

		char
			object_name[256];

		#if DEBUG_MODULE

		debug_log ( "Template: %d", count );

		#endif

		temporary_templates[count].approximation_object = OBJECT_3D_INVALID_OBJECT_INDEX;

		temporary_templates[count].base_object = OBJECT_3D_INVALID_OBJECT_INDEX;

		temporary_templates[count].routes_object = OBJECT_3D_INVALID_OBJECT_INDEX;

		fread ( &temporary_templates[count].number_of_objects, sizeof ( int ), 1, fp );

		fread ( &temporary_templates[count].type, sizeof ( int ), 1, fp );

		fread ( &valid, sizeof ( int ), 1, fp );

		if ( valid )
		{

			fread ( &string_length, sizeof ( int ), 1, fp );

			memset ( object_name, 0, 256 );

			fread ( object_name, string_length, 1, fp );

			temporary_templates[count].approximation_object = get_object_index_from_name ( object_name );

			if ( temporary_templates[count].approximation_object == OBJECT_3D_INVALID_OBJECT_INDEX )
			{

				debug_log ( "Invalid approximation specified: %s", object_name );
			}
		}

		fread ( &valid, sizeof ( int ), 1, fp );

		if ( valid )
		{

			fread ( &string_length, sizeof ( int ), 1, fp );

			memset ( object_name, 0, 256 );

			fread ( object_name, string_length, 1, fp );

			temporary_templates[count].base_object = get_object_index_from_name ( object_name );

			if ( temporary_templates[count].base_object == OBJECT_3D_INVALID_OBJECT_INDEX )
			{

				debug_log ( "Invalid approximation specified: %s", object_name );
			}
		}

		if ( population_file_version2 )
		{
	
			fread ( &valid, sizeof ( int ), 1, fp );
	
			if ( valid )
			{
	
				fread ( &string_length, sizeof ( int ), 1, fp );
	
				memset ( object_name, 0, 256 );
	
				fread ( object_name, string_length, 1, fp );
	
				temporary_templates[count].routes_object = get_object_index_from_name ( object_name );
	
				if ( temporary_templates[count].routes_object == OBJECT_3D_INVALID_OBJECT_INDEX )
				{
	
					debug_log ( "Invalid approximation specified: %s", object_name );
				}
			}
		}

		if ( temporary_templates[count].number_of_objects )
		{

			objects = safe_malloc ( temporary_templates[count].number_of_objects * sizeof ( temporary_template_object ) );

			temporary_templates[count].objects = objects;

			for ( object_count = 0; object_count < temporary_templates[count].number_of_objects; object_count++ )
			{

				fread ( &objects[object_count].x, sizeof ( float ), 1, fp );
				fread ( &objects[object_count].y, sizeof ( float ), 1, fp );
				fread ( &objects[object_count].heading, sizeof ( float ), 1, fp );
				objects[object_count].heading = rad ( objects[object_count].heading);

				fread ( &string_length, sizeof ( int ), 1, fp );

				memset ( object_name, 0, 256 );

				fread ( object_name, string_length, 1, fp );

				objects[object_count].object_index = get_object_index_from_name ( object_name );

				if ( objects[object_count].object_index != OBJECT_3D_INVALID_OBJECT_INDEX )
				{

					#if DEBUG_MODULE

					debug_log ( "3D Object: %s", object_3d_enumeration_names[ objects[object_count].object_index ] );

					#endif
				}
				else
				{

					#if DEBUG_MODULE

					debug_log ( "3D Object: %s ( was %s ) ", object_3d_enumeration_names[ objects[object_count].object_index ], object_name );

					#endif
				}

				ASSERT ( objects[object_count].object_index < OBJECT_3D_LAST );
			}
		}
		else
		{

			temporary_templates[count].objects = NULL;
		}
	}

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void read_population_city_placements ( FILE *fp )
{

	int
		number_of_instances,
		keysite_factory_count,
		keysite_oil_rig_count,
		keysite_placement_count,
		sam_placement_count,
		count;

	entity
		*city,
		*closest_keysite,
		*sector,
		*keysite,
		*keysite_group = NULL;

   int
		keysite_totals[NUM_ENTITY_SUB_TYPE_KEYSITES];

	entity_sides
		keysite_side = ENTITY_SIDE_NEUTRAL;

	vec3d
		keysite_pos;
	
	keysite_factory_count = 0;
	keysite_oil_rig_count = 0;
	keysite_placement_count = 0;
	sam_placement_count = 0;

	memset ( keysite_totals, 0, sizeof ( keysite_totals ) );

	fread ( &number_of_instances, sizeof ( int ), 1, fp );

	for ( count = 0; count < number_of_instances; count++ )
	{

		float
			x,
			y,
			z;

		int
			x_sec,
			z_sec,
			loop,
			index,
			object_number,
			keysite_type;

		char
			keysite_name[256];

		fread ( &index, sizeof ( int ), 1, fp );
		fread ( &x, sizeof ( float ), 1, fp );
		fread ( &z, sizeof ( float ), 1, fp );

		//
		// If its a port, or industry, place a keysite.
		//

		keysite_type = -1;

//			ENTITY_SUB_TYPE_KEYSITE_OIL_RIG

		/////////////////////////////////////////////////////////////////
		update_gunships_screen_progress_indicator ();
		/////////////////////////////////////////////////////////////////

		keysite = NULL;

		city = NULL;

		if ( population_file_version2 )
		/*
		{
	
			switch ( temporary_templates[index].type )
			{
	
				case TEMPLATE_TYPE_INDUSTRY:	{ keysite_type = ENTITY_SUB_TYPE_KEYSITE_FACTORY; break; }
				case TEMPLATE_TYPE_PORTSE:		{ keysite_type = ENTITY_SUB_TYPE_KEYSITE_FACTORY; break; }
				case TEMPLATE_TYPE_PORTNW:		{ keysite_type = ENTITY_SUB_TYPE_KEYSITE_FACTORY; break; }
			}
	
			if ( keysite_type != -1 )
			{
	
				if ( keysite_placement_count == 0 )
				{
	
					keysite_placement_count = 20;
		
					switch ( temporary_templates[index].type )
					{
						case TEMPLATE_TYPE_INDUSTRY:
						{
							sprintf ( keysite_name, "FACTORY %03d", keysite_factory_count );
	
							keysite_factory_count++;
		
							break;
						}
						case TEMPLATE_TYPE_PORTSE:
						case TEMPLATE_TYPE_PORTNW:
						{
							sprintf ( keysite_name, "PORT %03d", keysite_factory_count );
	
							keysite_factory_count++;
		
							break;
						}
					}
		
					keysite_x = x;
					keysite_z = current_map_max_z - z;
					keysite_y = get_3d_terrain_point_data ( keysite_x, keysite_z, NULL );
		
					//
					// create city template
					//
		
					get_x_sector ( x_sec, keysite_x );
					get_x_sector ( z_sec, keysite_z );
	
					keysite_side = get_initial_sector_side ( x_sec, z_sec );
	
					sector = get_local_raw_sector_entity ( x_sec, z_sec );
	
					keysite = create_local_entity
					(
						ENTITY_TYPE_KEYSITE,
						ENTITY_INDEX_DONT_CARE,
						ENTITY_ATTR_PARENT ( LIST_TYPE_KEYSITE_FORCE, get_local_force_entity (keysite_side) ),
						ENTITY_ATTR_INT_VALUE ( INT_TYPE_ENTITY_SUB_TYPE, keysite_type ),
						ENTITY_ATTR_INT_VALUE ( INT_TYPE_SIDE, keysite_side ),
						ENTITY_ATTR_INT_VALUE ( INT_TYPE_IN_USE, TRUE ),
						ENTITY_ATTR_FLOAT_VALUE (FLOAT_TYPE_AMMO_SUPPLY_LEVEL, 100.0),
						ENTITY_ATTR_FLOAT_VALUE (FLOAT_TYPE_FUEL_SUPPLY_LEVEL, 100.0),
						ENTITY_ATTR_VEC3D ( VEC3D_TYPE_POSITION, keysite_x, keysite_y, keysite_z ),
						ENTITY_ATTR_STRING ( STRING_TYPE_KEYSITE_NAME, keysite_name ),
						ENTITY_ATTR_END
					);

					keysite = NULL;
				}
				else
				{
	
					keysite_placement_count--;
				}
			}
		}
		else*/
		{

			keysite_type = -1;

			switch ( temporary_templates[index].type )
			{
	
				case TEMPLATE_TYPE_KEY_POWER:		{ keysite_type = ENTITY_SUB_TYPE_KEYSITE_POWER_STATION; break; }
				case TEMPLATE_TYPE_KEY_RADIO:		{ keysite_type = ENTITY_SUB_TYPE_KEYSITE_RADIO_TRANSMITTER; break; }
				case TEMPLATE_TYPE_KEY_INDUSTRY:	{ keysite_type = ENTITY_SUB_TYPE_KEYSITE_FACTORY; break; }
				case TEMPLATE_TYPE_KEY_PORT:		{ keysite_type = ENTITY_SUB_TYPE_KEYSITE_PORT; break; }
				case TEMPLATE_TYPE_KEY_MILITARY:	{ keysite_type = ENTITY_SUB_TYPE_KEYSITE_MILITARY_BASE; break; }
				case TEMPLATE_TYPE_KEY_OIL:		{ keysite_type = ENTITY_SUB_TYPE_KEYSITE_OIL_REFINERY; break; }
			}

			if ( keysite_type != -1 )
			{

				int
					important;
		
				keysite_totals[keysite_type]++;
	
				sprintf (keysite_name, "%s %d", get_trans (keysite_database[keysite_type].short_name), keysite_totals[keysite_type]);
	
				keysite_pos.x = x;
				keysite_pos.z = current_map_max_z - z;
				keysite_pos.y = get_3d_terrain_point_data ( keysite_pos.x, keysite_pos.z, NULL );

				ASSERT (point_inside_adjusted_map_area (&keysite_pos));
	
				get_x_sector ( x_sec, keysite_pos.x );
				get_x_sector ( z_sec, keysite_pos.z );
	
				keysite_side = get_initial_sector_side ( x_sec, z_sec );
	
				sector = get_local_raw_sector_entity ( x_sec, z_sec );

				if ( population_importances )
				{
					important = population_importances[( z_sec * ( MAX_MAP_X_SECTOR + 1 ) ) + x_sec] ? FALSE : TRUE;
				}
				else
				{

					important = FALSE;
				}

				keysite = create_local_entity
								(
									ENTITY_TYPE_KEYSITE,
									ENTITY_INDEX_DONT_CARE,
									ENTITY_ATTR_PARENT ( LIST_TYPE_KEYSITE_FORCE, get_local_force_entity (keysite_side) ),
									ENTITY_ATTR_INT_VALUE ( INT_TYPE_ENTITY_SUB_TYPE, keysite_type ),
									ENTITY_ATTR_INT_VALUE ( INT_TYPE_SIDE, keysite_side ),
									ENTITY_ATTR_INT_VALUE ( INT_TYPE_IN_USE, TRUE ),
									ENTITY_ATTR_INT_VALUE ( INT_TYPE_KEYSITE_ID, keysite_totals [keysite_type] ),
									ENTITY_ATTR_FLOAT_VALUE (FLOAT_TYPE_AMMO_SUPPLY_LEVEL, 100.0),
									ENTITY_ATTR_FLOAT_VALUE (FLOAT_TYPE_FUEL_SUPPLY_LEVEL, 100.0),
									ENTITY_ATTR_VEC3D ( VEC3D_TYPE_POSITION, keysite_pos.x, keysite_pos.y, keysite_pos.z ),
									ENTITY_ATTR_STRING ( STRING_TYPE_KEYSITE_NAME, keysite_name ),
									ENTITY_ATTR_INT_VALUE ( INT_TYPE_OBJECT_INDEX, temporary_templates[index].routes_object ),
									ENTITY_ATTR_END
								);
	
				keysite_group = get_local_entity_first_child ( keysite, LIST_TYPE_BUILDING_GROUP );
			}
		}

		if ( temporary_templates[index].number_of_objects )
		{

			entity_sides
				sector_side;

			z = current_map_max_z - z;

			//
			// If its a port, it assumes sea-level height, otherwise get the height of the template from the terrain height.
			//

			switch ( temporary_templates[index].type )
			{

				case TEMPLATE_TYPE_PORTSE:
				case TEMPLATE_TYPE_PORTNW:
				{

					y = terrain_3d_map_minimum_height;

					break;
				}

				default:
				{

					y = get_3d_terrain_point_data ( x, z, NULL );

					break;
				}
			}

			//
			// create city template
			//

			get_x_sector ( x_sec, x );
			get_x_sector ( z_sec, z );

			sector = get_local_raw_sector_entity ( x_sec, z_sec );

			sector_side = get_initial_sector_side ( x_sec, z_sec );

			if ( !keysite )
			{
	
				city = create_local_entity
				(
					ENTITY_TYPE_CITY,
					ENTITY_INDEX_DONT_CARE,
					ENTITY_ATTR_PARENT ( LIST_TYPE_SECTOR, sector ),
					ENTITY_ATTR_INT_VALUE ( INT_TYPE_ENTITY_SUB_TYPE, ENTITY_SUB_TYPE_FIXED_CITY ),
					ENTITY_ATTR_VEC3D ( VEC3D_TYPE_POSITION, x, y, z ),
					ENTITY_ATTR_END
				);
			}

			if ( ( city ) || ( keysite ) )
			{

				//
				// Set base & approximation objects for the templates ( version1 of the population files only )
				//

				//
				// Ports have their bases inserted as a normal object
				//

				if ( city )
				{
	
					switch ( temporary_templates[index].type )
					{
		
						case TEMPLATE_TYPE_PORTSE:
						case TEMPLATE_TYPE_PORTNW:
						{
	
							ASSERT ( city );
	
							if ( temporary_templates[index].base_object != OBJECT_3D_INVALID_OBJECT_INDEX )
							{
		
								create_local_entity
								(
									ENTITY_TYPE_CITY_BUILDING,
									ENTITY_INDEX_DONT_CARE,
									ENTITY_ATTR_PARENT ( LIST_TYPE_CITY_BUILDING, city ),
									ENTITY_ATTR_INT_VALUE ( INT_TYPE_ENTITY_SUB_TYPE, ENTITY_SUB_TYPE_FIXED_CITY_BUILDING ),
									ENTITY_ATTR_VEC3D ( VEC3D_TYPE_POSITION, x, y, z ),
									ENTITY_ATTR_INT_VALUE ( INT_TYPE_OBJECT_3D_SHAPE, temporary_templates[index].base_object ),
									ENTITY_ATTR_FLOAT_VALUE ( FLOAT_TYPE_HEADING, 0 ),
									ENTITY_ATTR_END
								);
							}
	
							break;
						}
		
						default:
						{
	
							set_local_entity_int_value ( city, INT_TYPE_OBJECT_3D_SHAPE, temporary_templates[index].base_object );
	
							break;
						}
					}
		
					set_local_entity_int_value ( city, INT_TYPE_APPROXIMATION_OBJECT_3D_SHAPE, temporary_templates[index].approximation_object );
				}
				else if ( keysite )
				{

					if ( temporary_templates[index].base_object != OBJECT_3D_INVALID_OBJECT_INDEX )
					{

						create_local_entity
						(
							ENTITY_TYPE_SCENIC,
							ENTITY_INDEX_DONT_CARE,
							ENTITY_ATTR_INT_VALUE ( INT_TYPE_ENTITY_SUB_TYPE,ENTITY_SUB_TYPE_FIXED_MILITARY_BUILDING ),
							ENTITY_ATTR_INT_VALUE ( INT_TYPE_OBJECT_3D_SHAPE, temporary_templates[index].base_object ),
							ENTITY_ATTR_INT_VALUE ( INT_TYPE_SIDE, keysite_side ),
							ENTITY_ATTR_VEC3D ( VEC3D_TYPE_POSITION, x, y, z ),
							ENTITY_ATTR_END
						);
					}
				}
				else
				{

					debug_fatal ( "No city or keysite to attach city buildings to" );
				}


				//
				// create city buildings
				//

				for (loop = 0; loop < temporary_templates[index].number_of_objects; loop ++)
				{

					float
						world_x,
						world_y,
						world_z,
						heading;

					/////////////////////////////////////////////////////////////////
					update_gunships_screen_progress_indicator ();
					/////////////////////////////////////////////////////////////////

					world_x = x;
					world_z = z;

					world_x += temporary_templates[index].objects[loop].x;
					world_z -= temporary_templates[index].objects[loop].y;
					world_y = y;

					//
					// If its a farm, let buildings find their own height
					//

					if ( ( temporary_templates[index].type == TEMPLATE_TYPE_FARM ) || ( population_file_version2 ) )
					{

						world_y = get_3d_terrain_point_data ( world_x, world_z, NULL );
					}


					heading = ( temporary_templates[index].objects[loop].heading );

					object_number = temporary_templates[index].objects[loop].object_index;

					if ( object_number != OBJECT_3D_INVALID_OBJECT_INDEX )
					{

						insert_keysite_or_city_object ( city, keysite, keysite_group, keysite_side, object_number, world_x, world_y, world_z, heading );

						//
						// Check for scene links ( SAMS on buildings! )
						//
	
						if ( ( objects_3d_scene_database[object_number].number_of_scene_link_objects ) )
						{
	
							int
								scene_link_count;

							for ( scene_link_count = 0; scene_link_count < objects_3d_scene_database[object_number].number_of_scene_link_objects; scene_link_count++ )
							{

								if (	( objects_3d_scene_database[object_number].scene_link_objects[scene_link_count].scene_index == OBJECT_3D_PORTNW_FC_HUGE_CRANE01_BOOM ) ||
										( objects_3d_scene_database[object_number].scene_link_objects[scene_link_count].scene_index == OBJECT_3D_PORTNW_FC_HUGE_CRANE02_BOOM ) ||
										( objects_3d_scene_database[object_number].scene_link_objects[scene_link_count].scene_index == OBJECT_3D_LEBANON_CONSTRUCT_CRANE_BOOM_01 ) ||
										( objects_3d_scene_database[object_number].scene_link_objects[scene_link_count].scene_index == OBJECT_3D_LEBANON_CONSTRUCT_CRANE_BOOM_02 ) )
								{

									insert_keysite_or_city_object ( city, keysite, keysite_group, keysite_side,
																				objects_3d_scene_database[object_number].scene_link_objects[scene_link_count].scene_index,
																				objects_3d_scene_database[object_number].scene_link_objects[scene_link_count].x + world_x,
																				objects_3d_scene_database[object_number].scene_link_objects[scene_link_count].y + world_y,
																				objects_3d_scene_database[object_number].scene_link_objects[scene_link_count].z + world_z,
																				heading );
								}
								else
								{
		
									if ( ( count % 4 ) == 1 )
									{
		
		
										vec3d
											pos;
			
										vec3d
											relative_position;
			
										matrix3x3
											m;
			
										formation_component_types
											formation_type;
			
										entity
											*group,
											*member;
		
										if (sam_placement_count & 1)
										{
		
											formation_type = FORMATION_COMPONENT_INFANTRY_SAM_KNEELING;
										}
										else
										{
		
											formation_type = FORMATION_COMPONENT_INFANTRY_SAM_STANDING;
										}
			
										relative_position.x = objects_3d_scene_database[object_number].scene_link_objects[scene_link_count].x;
										relative_position.y = objects_3d_scene_database[object_number].scene_link_objects[scene_link_count].y;
										relative_position.z = objects_3d_scene_database[object_number].scene_link_objects[scene_link_count].z;
			
										get_3d_transformation_heading_matrix ( m, heading );
			
										multiply_matrix3x3_vec3d ( &pos, m, &relative_position );
			
										pos.x += world_x;
										pos.y += world_y;
										pos.z += world_z;
		
										if ( keysite )
										{
											closest_keysite = keysite;
										}
										else
										{
											closest_keysite = NULL;
										}

										group = create_faction_members ( closest_keysite, ENTITY_SUB_TYPE_GROUP_STATIC_INFANTRY, formation_type, 1, sector_side, &pos, FALSE, FALSE );
			
										if ( group )
										{
			
											float
												relative_heading;
			
											relative_heading = objects_3d_scene_database[object_number].scene_link_objects[scene_link_count].heading + heading;
			
											member = get_local_entity_first_child ( group, LIST_TYPE_MEMBER );
			
											while ( member )
											{
			
												set_local_entity_float_value ( member, FLOAT_TYPE_HEADING, relative_heading );
			
												member = get_local_entity_child_succ ( member, LIST_TYPE_MEMBER );
											}
										}
									}
								}
							}

							sam_placement_count++;
						}
					}
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void read_population_airfield_placements ( FILE *fp )
{

	int
		airfield_count,
		farp_count,
		blue_force_carrier_count,
		red_force_carrier_count,
		number_of_instances,
		count;

	entity
		*sector;

	airfield_count = 1;

	farp_count = 1;

	blue_force_carrier_count = 0;

	red_force_carrier_count = 0;

	fread ( &number_of_instances, sizeof ( int ), 1, fp );

	//
	// Initialise the terrain object system
	//

	initialise_terrain_objects ();

	if ( number_of_instances )
	{

		set_number_of_terrain_objects ( number_of_instances );
	}

	//
	// Read in the airfields themselves
	//

	#if DEBUG_MODULE
	
	debug_log ( "Starting airport placement" );

	#endif

	for ( count = 0; count < number_of_instances; count++ )
	{

		int
			string_length;

		float
			x,
			y,
			z;

		char
			object_name[256];

		entity_sub_types
			keysite_sub_type;

		object_3d_index_numbers
			object_index;

		memset ( object_name, 0, 256 );

		fread ( &x, sizeof ( float ), 1, fp );
		fread ( &z, sizeof ( float ), 1, fp );

		z = current_map_max_z - z;
		y = get_3d_terrain_point_data ( x, z, NULL );

		fread ( &string_length, sizeof ( int ), 1, fp );
		fread ( object_name, string_length, 1, fp );

		object_index = get_object_index_from_name ( object_name );


		if ( object_index == OBJECT_3D_AIRFIELD_FR_CUBA_TREEBLOCK )
		{

			//
			// This is the cuba problem - don't insert it into the AI at all
			//

			current_airport_inst3d = construct_3d_object ( object_index );
	
			current_airport_inst3d->vp.position.x = x;
			current_airport_inst3d->vp.position.y = y;
			current_airport_inst3d->vp.position.z = z;
	
			current_airport_inst3d->object_has_shadow = FALSE;
			current_airport_inst3d->object_internal_lighting = FALSE;
	
			get_3d_transformation_matrix ( current_airport_inst3d->vp.attitude, 0.0, 0.0, 0.0 );

			insert_3d_object_into_terrain ( current_airport_inst3d );
		}
		else
		{
	
			switch ( object_index )
			{
	
				case OBJECT_3D_AMERICAN_AIRPORT01:
				case OBJECT_3D_AMERICAN_AIRPORT02:
				case OBJECT_3D_AMERICAN_AIRPORT03:
				case OBJECT_3D_RUSSIAN_AIRPORT01:
				case OBJECT_3D_RUSSIAN_AIRPORT02:
				case OBJECT_3D_RUSSIAN_AIRPORT03:
				case OBJECT_3D_RUSSIAN_AIRPORT04:
				case OBJECT_3D_RUSSIAN_AIRPORT05:
				case OBJECT_3D_RUSSIAN_AIRPORT06:
				case OBJECT_3D_RUSSIAN_AIRPORT07:
				case OBJECT_3D_RUSSIAN_AIRPORT09:
				case OBJECT_3D_RUSSIAN_AIRPORT10:
				case OBJECT_3D_RUSSIAN_AIRPORT11:
				case OBJECT_3D_RUSSIAN_AIRPORT12:
				case OBJECT_3D_RUSSIAN_AIRPORT13:
				{
	
					#if DEBUG_MODULE
	
					debug_log ( "Placing main airport at %f, %f", x, z );
	
					#endif
	
					keysite_sub_type = ENTITY_SUB_TYPE_KEYSITE_AIRBASE;
	
					break;
				}
	
				case OBJECT_3D_RUSSIAN_FARP11:
				case OBJECT_3D_AMERICAN_FARP11:
				case OBJECT_3D_AMERICAN_FARP01:
				case OBJECT_3D_AMERICAN_FARP02:
				case OBJECT_3D_AMERICAN_FARP03:
				case OBJECT_3D_AMERICAN_FARP04:
				case OBJECT_3D_AMERICAN_FARP05:
				case OBJECT_3D_AMERICAN_FARP06:
				case OBJECT_3D_AMERICAN_FARP07:
				case OBJECT_3D_AMERICAN_FARP08:
				case OBJECT_3D_AMERICAN_FARP09:
				case OBJECT_3D_AMERICAN_FARP10:
				case OBJECT_3D_AMERICAN_FARP12:
				case OBJECT_3D_AMERICAN_FARP13:
				case OBJECT_3D_RUSSIAN_FARP01:
				case OBJECT_3D_RUSSIAN_FARP02:
				case OBJECT_3D_RUSSIAN_FARP03:
				case OBJECT_3D_RUSSIAN_FARP04:
				case OBJECT_3D_RUSSIAN_FARP05:
				case OBJECT_3D_RUSSIAN_FARP06:
				case OBJECT_3D_RUSSIAN_FARP07:
				case OBJECT_3D_RUSSIAN_FARP08:
				case OBJECT_3D_RUSSIAN_FARP09:
				case OBJECT_3D_RUSSIAN_FARP10:
				case OBJECT_3D_RUSSIAN_FARP12:
				case OBJECT_3D_RUSSIAN_FARP13:
				{
	
					#if DEBUG_MODULE
	
					debug_log ( "Placing FARP at %f, %f", x, z );
	
					#endif
	
					keysite_sub_type = ENTITY_SUB_TYPE_KEYSITE_FARP;
	
					break;
				}
	
				default:
				{
	
					keysite_sub_type = ENTITY_SUB_TYPE_KEYSITE_AIRBASE;
				}
			}
	
			//
			// Check the terrain type here
	
			{
	
				terrain_types
					type;
	
				get_3d_terrain_point_data ( x, z, NULL );
	
				type = get_3d_terrain_point_data_type ( NULL );
	
				if ( get_terrain_type_class ( type ) == TERRAIN_CLASS_WATER )
				{
	
					int
						x_sec,
						z_sec;

					entity_sides
						side;
	
					//
					// Change object to KIEV or TARAWA for routes
					//
	
					get_x_sector ( x_sec, x );
	
					get_z_sector ( z_sec, z );

					sector = get_local_raw_sector_entity ( x_sec, z_sec );

					side = get_initial_sector_side ( x_sec, z_sec );

					if ( side == ENTITY_SIDE_RED_FORCE )
					{
	
						#if DEBUG_MODULE
	
						debug_log ( "Placing a kiev keysite" );

						#endif
	
						object_index = OBJECT_3D_KIEV_CLASS;
					}
					else if ( side == ENTITY_SIDE_BLUE_FORCE )
					{
	
						#if DEBUG_MODULE
	
						debug_log ( "Placing a tarawa keysite" );

						#endif
	
						object_index = OBJECT_3D_TARAWA;
					}
					else
					{
	
						debug_fatal ( "Placing a sea keysite - but sector belongs to neither side" );
					}
	
					keysite_sub_type = ENTITY_SUB_TYPE_KEYSITE_ANCHORAGE;
				}
			}
	
			current_airport_inst3d = construct_3d_object ( object_index );
	
			current_airport_inst3d->vp.position.x = x;
			current_airport_inst3d->vp.position.y = y;
			current_airport_inst3d->vp.position.z = z;
	
			current_airport_inst3d->object_has_shadow = FALSE;
	
			get_3d_transformation_matrix ( current_airport_inst3d->vp.attitude, 0.0, 0.0, 0.0 );
	
	#if ( !DEBUG_MODULE )
	
			{
	
				//
				// Remove the waypoint route objects
				//
	
				object_3d_sub_object_search_data
					search;
	
				search.search_object = current_airport_inst3d;
				search.search_depth = 0;
				search.sub_object_index = OBJECT_3D_SUB_OBJECT_WAYPOINT_ROUTES;
	
				if ( find_object_3d_sub_object ( &search ) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND )
				{
	
					search.result_sub_object->visible_object = FALSE;
				}
			}
	
	#endif
	
			if ( keysite_sub_type != ENTITY_SUB_TYPE_KEYSITE_ANCHORAGE )
			{
	
				current_airport_inst3d->object_internal_lighting = TRUE;
	
				insert_3d_object_into_terrain ( current_airport_inst3d );
			}
	
			//
			// Create keysite,
			//
	
			{
	
				entity
					*force,
					*sector,
					*keysite;
	
				vec3d
					position;
	
				char
					buffer [256],
					*airfield_name;
	
				int
					fixed_wing_flag,
					helicopter_flag,
					routed_vehicle_flag,
					ship_flag,
					transport_flag,
					people_flag,
					keysite_id,
					important,
					x_sec,
					z_sec;
	
				entity_sides
					keysite_side;
	
				object_3d_database_entry
					*landing_route,
					*takeoff_route,
					*landing_holding_route,
					*takeoff_holding_route;

				position.x = x;
				position.y = y;
				position.z = z;
	
				airfield_name = NULL;

				keysite_id = -1;

				get_x_sector ( x_sec, position.x );

				get_z_sector ( z_sec, position.z );

				if ( keysite_sub_type == ENTITY_SUB_TYPE_KEYSITE_AIRBASE )
				{
	
					airfield_name = get_keysite_name ( x, z, &keysite_side );
				}
				else
				{

					keysite_side = get_initial_sector_side ( x_sec, z_sec );

					sector = get_local_sector_entity (&position);
				}
	
				if (keysite_sub_type == ENTITY_SUB_TYPE_KEYSITE_FARP)
				{

					keysite_id = farp_count;

					sprintf (buffer, "%s %d", get_trans (keysite_database [keysite_sub_type].short_name), farp_count ++);
				}
				else if (keysite_sub_type == ENTITY_SUB_TYPE_KEYSITE_ANCHORAGE)
				{

					keysite_id = blue_force_carrier_count + red_force_carrier_count + 1;

					switch ( object_index )
					{

						case OBJECT_3D_KIEV_CLASS:
						{

							ASSERT ( red_force_carrier_count < ( ( sizeof ( red_force_carrier_names ) / sizeof ( char * ) ) ) );

							strcpy ( buffer, red_force_carrier_names[red_force_carrier_count++] );

							break;
						}

						case OBJECT_3D_TARAWA:
						{

							ASSERT ( blue_force_carrier_count < ( ( sizeof ( blue_force_carrier_names ) / sizeof ( char * ) ) ) );

							strcpy ( buffer, blue_force_carrier_names[blue_force_carrier_count++] );

							break;
						}
					}
				}
				else
				{
					ASSERT (keysite_sub_type == ENTITY_SUB_TYPE_KEYSITE_AIRBASE);

					keysite_id = airfield_count;

					sprintf (buffer, "%s %d", get_trans (keysite_database [keysite_sub_type].short_name), airfield_count ++);
				}

				if (!airfield_name)
				{

					airfield_name = buffer;
				}

				ASSERT (keysite_id > 0);
/*
				if (	( keysite_sub_type == ENTITY_SUB_TYPE_KEYSITE_FARP ) ||
						( keysite_sub_type == ENTITY_SUB_TYPE_KEYSITE_AIRBASE ) )
				{

					if ( keysite_side == ENTITY_SIDE_RED_FORCE )
					{

						debug_log ( "RUSSIAN AIRPORT: %s", object_3d_enumeration_names[object_index] );
					}
					else
					{

						debug_log ( "AMERICAN AIRPORT: %s", object_3d_enumeration_names[object_index] );
					}
				}
*/

				force = get_local_force_entity (keysite_side);

				if ( population_importances )
				{

					important = population_importances[( z_sec * ( MAX_MAP_X_SECTOR + 1 ) ) + x_sec] ? FALSE : TRUE;
				}
				else
				{

					important = FALSE;
				}

				keysite =	create_local_entity
								(
									ENTITY_TYPE_KEYSITE,
									ENTITY_INDEX_DONT_CARE,
									ENTITY_ATTR_PARENT ( LIST_TYPE_KEYSITE_FORCE, force ),
									ENTITY_ATTR_INT_VALUE ( INT_TYPE_ENTITY_SUB_TYPE, keysite_sub_type ),
									ENTITY_ATTR_INT_VALUE ( INT_TYPE_OBJECT_INDEX, object_index ),
									ENTITY_ATTR_INT_VALUE ( INT_TYPE_SIDE, keysite_side ),
									ENTITY_ATTR_INT_VALUE ( INT_TYPE_KEYSITE_ID, keysite_id ),
									ENTITY_ATTR_FLOAT_VALUE ( FLOAT_TYPE_AMMO_SUPPLY_LEVEL, 100.0),
									ENTITY_ATTR_FLOAT_VALUE ( FLOAT_TYPE_FUEL_SUPPLY_LEVEL, 100.0),
									ENTITY_ATTR_VEC3D ( VEC3D_TYPE_POSITION, position.x, position.y, position.z ),
									ENTITY_ATTR_STRING ( STRING_TYPE_KEYSITE_NAME, airfield_name ),
									ENTITY_ATTR_END
								);

				#if LANDING_KEYSITE_DEBUG_OUTPUT

				if (keysite_sub_type != ENTITY_SUB_TYPE_KEYSITE_FARP)
				{
					debug_filtered_log ("                             ");
					debug_filtered_log ("%s (%s)", airfield_name, entity_side_names [keysite_side]);
				}

				#endif

				set_parser_keysite ( keysite );

				fixed_wing_flag = FALSE;
				helicopter_flag = FALSE;
				routed_vehicle_flag = FALSE;
				ship_flag = FALSE;
				transport_flag = FALSE;
				people_flag = FALSE;

				//
				// Insert FIXEDWING waypoint routes into keysite.
				//

				landing_route = get_airfield_waypoint_route_object ( current_airport_inst3d, OBJECT_3D_SUB_OBJECT_FIXED_WING_LANDING_ROUTE );
				takeoff_route = get_airfield_waypoint_route_object ( current_airport_inst3d, OBJECT_3D_SUB_OBJECT_FIXED_WING_TAKEOFF_ROUTE );
				landing_holding_route = get_airfield_waypoint_route_object ( current_airport_inst3d, OBJECT_3D_SUB_OBJECT_FIXED_WING_LANDING_HOLDING_ROUTE );
				takeoff_holding_route = get_airfield_waypoint_route_object ( current_airport_inst3d, OBJECT_3D_SUB_OBJECT_FIXED_WING_TAKEOFF_HOLDING_ROUTE );
	
				if ( ( landing_route ) && ( takeoff_route ) )
				{

					fixed_wing_flag = TRUE;

					insert_airport_fixedwing_routes ( ENTITY_SUB_TYPE_LANDING_FIXED_WING, &position, landing_route, takeoff_route );

					insert_airport_holding_routes ( &position, landing_holding_route, takeoff_holding_route );
				}

				//
				// Insert HELICOPTER waypoint routes into keysite.
				//

				landing_route = get_airfield_waypoint_route_object ( current_airport_inst3d, OBJECT_3D_SUB_OBJECT_HELI_LANDING_ROUTE );
				takeoff_route = get_airfield_waypoint_route_object ( current_airport_inst3d, OBJECT_3D_SUB_OBJECT_HELI_TAKEOFF_ROUTE );
				landing_holding_route = get_airfield_waypoint_route_object ( current_airport_inst3d, OBJECT_3D_SUB_OBJECT_HELI_LANDING_HOLDING_ROUTE );
				takeoff_holding_route = get_airfield_waypoint_route_object ( current_airport_inst3d, OBJECT_3D_SUB_OBJECT_HELI_TAKEOFF_HOLDING_ROUTE );
	
				if ( ( landing_route ) && ( takeoff_route ) )
				{

					helicopter_flag = TRUE;

					insert_airport_helicopter_routes ( &position, landing_route, takeoff_route, landing_holding_route, takeoff_holding_route );
				}
	
				//
				// Insert ROUTED VEHICLE waypoint routes into keysite.
				//

				landing_route = get_airfield_waypoint_route_object ( current_airport_inst3d, OBJECT_3D_SUB_OBJECT_ROUTED_VEHICLE_LANDING_ROUTE );
				takeoff_route = get_airfield_waypoint_route_object ( current_airport_inst3d, OBJECT_3D_SUB_OBJECT_ROUTED_VEHICLE_TAKEOFF_ROUTE );
				landing_holding_route = get_airfield_waypoint_route_object ( current_airport_inst3d, OBJECT_3D_SUB_OBJECT_ROUTED_VEHICLE_LANDING_HOLDING_ROUTE );
				takeoff_holding_route = get_airfield_waypoint_route_object ( current_airport_inst3d, OBJECT_3D_SUB_OBJECT_ROUTED_VEHICLE_TAKEOFF_HOLDING_ROUTE );
	
				if ( ( landing_route ) && ( takeoff_route ) )
				{

					routed_vehicle_flag = TRUE;

					insert_airport_general_takeoff_landing_routes ( ENTITY_SUB_TYPE_LANDING_GROUND , &position, landing_route, takeoff_route );

					insert_airport_holding_routes ( &position, landing_holding_route, takeoff_holding_route );
				}
	
	
				//
				// Insert SHIP waypoint routes into keysite.
				//
	
				landing_route = get_airfield_waypoint_route_object ( current_airport_inst3d, OBJECT_3D_SUB_OBJECT_SHIP_LANDING_ROUTE );
				takeoff_route = get_airfield_waypoint_route_object ( current_airport_inst3d, OBJECT_3D_SUB_OBJECT_SHIP_TAKEOFF_ROUTE );
				landing_holding_route = get_airfield_waypoint_route_object ( current_airport_inst3d, OBJECT_3D_SUB_OBJECT_SHIP_LANDING_HOLDING_ROUTE );
				takeoff_holding_route = get_airfield_waypoint_route_object ( current_airport_inst3d, OBJECT_3D_SUB_OBJECT_SHIP_TAKEOFF_HOLDING_ROUTE );

				if ( ( landing_route ) && ( takeoff_route ) )
				{

					ship_flag = TRUE;

					insert_airport_general_takeoff_landing_routes ( ENTITY_SUB_TYPE_LANDING_SEA, &position, landing_route, takeoff_route );

					insert_airport_holding_routes ( &position, landing_holding_route, takeoff_holding_route );
				}
	
				//
				// Insert TRANSPORT waypoint routes into keysite.
				//

				landing_route = get_airfield_waypoint_route_object ( current_airport_inst3d, OBJECT_3D_SUB_OBJECT_TRANSPORT_LANDING_ROUTE );
				takeoff_route = get_airfield_waypoint_route_object ( current_airport_inst3d, OBJECT_3D_SUB_OBJECT_TRANSPORT_TAKEOFF_ROUTE );
				landing_holding_route = get_airfield_waypoint_route_object ( current_airport_inst3d, OBJECT_3D_SUB_OBJECT_TRANSPORT_LANDING_HOLDING_ROUTE );
				takeoff_holding_route = get_airfield_waypoint_route_object ( current_airport_inst3d, OBJECT_3D_SUB_OBJECT_TRANSPORT_TAKEOFF_HOLDING_ROUTE );

				if ( ( landing_route ) && ( takeoff_route ) )
				{

					transport_flag = TRUE;

					insert_airport_fixedwing_routes ( ENTITY_SUB_TYPE_LANDING_FIXED_WING_TRANSPORT , &position, landing_route, takeoff_route );

					insert_airport_holding_routes ( &position, landing_holding_route, takeoff_holding_route );
				}
	
				//
				// Insert ASTHETIC PEOPLE waypoint routes into keysite.
				//
	
				landing_route = get_airfield_waypoint_route_object ( current_airport_inst3d, OBJECT_3D_SUB_OBJECT_PERSON_LANDING_ROUTE );
				takeoff_route = get_airfield_waypoint_route_object ( current_airport_inst3d, OBJECT_3D_SUB_OBJECT_PERSON_TAKEOFF_ROUTE );
				landing_holding_route = get_airfield_waypoint_route_object ( current_airport_inst3d, OBJECT_3D_SUB_OBJECT_PERSON_LANDING_HOLDING_ROUTE );
				takeoff_holding_route = get_airfield_waypoint_route_object ( current_airport_inst3d, OBJECT_3D_SUB_OBJECT_PERSON_TAKEOFF_HOLDING_ROUTE );

				if ( ( landing_route ) && ( takeoff_route ) )
				{

					people_flag = TRUE;

					insert_airport_general_takeoff_landing_routes ( ENTITY_SUB_TYPE_LANDING_PEOPLE , &position, landing_route, takeoff_route );

					insert_airport_holding_routes ( &position, landing_holding_route, takeoff_holding_route );
				}

				//
				// Insert any buildings into the keysite
				//

				if ( keysite_sub_type != ENTITY_SUB_TYPE_KEYSITE_ANCHORAGE )
				{
	
					insert_airfield_buildings ( keysite_side, current_airport_inst3d );
				}
				else
				{
	
					destruct_3d_object ( current_airport_inst3d );
				}

				// debug_log used to generate POPNAME.DAT. just replace the - with newlines....

				#if DEBUG_MODULE

				debug_log ("POPREAD: POPNAME.DAT (%s) :NAME %s-:POPULATION_TYPE KEYSITE-:POSITION %.0f %.0f-:ZOOM 0. (FW %d)(HC %d)(RV %d)(SH %d)(T-FW %d)(PPL %d)",
							entity_side_names [keysite_side], airfield_name, position.x, position.z, fixed_wing_flag, helicopter_flag, routed_vehicle_flag, ship_flag, transport_flag, people_flag);

				#endif

				//
				// Check all the landing site are on flat land
				//

				validate_keysite_landing_site_heights (keysite);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void read_population_sam_placements ( FILE *fp )
{

	int
		number_of_instances,
		count;

	fread ( &number_of_instances, sizeof ( int ), 1, fp );

	#if DEBUG_MODULE

	debug_log ( "reading in %d aaa/sam placements", number_of_instances );

	#endif

	for ( count = 0; count < number_of_instances; count++ )
	{

		vec3d
			pos;

		entity
			*sector;

		entity_sides
			side;

		formation_vehicle_components
			*formation_vehicle_component;

		formation_component_types
			formation_type;

		int
			count,
			x_sec,
			z_sec;

		fread ( &pos.x, sizeof ( float ), 1, fp );

		fread ( &pos.z, sizeof ( float ), 1, fp );

		pos.z = current_map_max_z - pos.z;

		pos.y = get_3d_terrain_point_data ( pos.x, pos.z, NULL );

		get_x_sector ( x_sec, pos.x );

		get_z_sector ( z_sec, pos.z );

		side = get_initial_sector_side ( x_sec, z_sec );

		sector = get_local_raw_sector_entity ( x_sec, z_sec );

		formation_type = FORMATION_COMPONENT_LIGHT_SAM_AAA_GROUP;

		formation_vehicle_component = get_formation_components (formation_type);

		count = max (0, formation_vehicle_component->count - 1);

		create_faction_members (NULL, ENTITY_SUB_TYPE_GROUP_ANTI_AIRCRAFT, formation_type, count, side, &pos, FALSE, TRUE );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void validate_airport_links ( object_3d_index_numbers object_index )
{

	object_3d_instance
		*current_airport_inst3d;

	object_3d_database_entry
		*fixedwing_landing_route,
		*fixedwing_takeoff_route,
		*helicopter_landing_route,
		*helicopter_takeoff_route,
		*vehicle_landing_route,
		*vehicle_takeoff_route,
		*ship_landing_route,
		*ship_takeoff_route,
		*fixedwing_landing_holding_route,
		*fixedwing_takeoff_holding_route,
		*helicopter_landing_holding_route,
		*helicopter_takeoff_holding_route,
		*vehicle_landing_holding_route,
		*vehicle_takeoff_holding_route,
		*ship_landing_holding_route,
		*ship_takeoff_holding_route;

	current_airport_inst3d = construct_3d_object ( object_index );

	//
	// Get pointers to the waypoint route objects
	//

	fixedwing_landing_route = get_airfield_waypoint_route_object ( current_airport_inst3d, OBJECT_3D_SUB_OBJECT_FIXED_WING_LANDING_ROUTE );
	fixedwing_takeoff_route = get_airfield_waypoint_route_object ( current_airport_inst3d, OBJECT_3D_SUB_OBJECT_FIXED_WING_TAKEOFF_ROUTE );

	helicopter_landing_route = get_airfield_waypoint_route_object ( current_airport_inst3d, OBJECT_3D_SUB_OBJECT_HELI_LANDING_ROUTE );
	helicopter_takeoff_route = get_airfield_waypoint_route_object ( current_airport_inst3d, OBJECT_3D_SUB_OBJECT_HELI_TAKEOFF_ROUTE );

	vehicle_landing_route = get_airfield_waypoint_route_object ( current_airport_inst3d, OBJECT_3D_SUB_OBJECT_ROUTED_VEHICLE_LANDING_ROUTE );
	vehicle_takeoff_route = get_airfield_waypoint_route_object ( current_airport_inst3d, OBJECT_3D_SUB_OBJECT_ROUTED_VEHICLE_TAKEOFF_ROUTE );

	ship_landing_route = get_airfield_waypoint_route_object ( current_airport_inst3d, OBJECT_3D_SUB_OBJECT_SHIP_LANDING_ROUTE );
	ship_takeoff_route = get_airfield_waypoint_route_object ( current_airport_inst3d, OBJECT_3D_SUB_OBJECT_SHIP_TAKEOFF_ROUTE );

	fixedwing_landing_holding_route = get_airfield_waypoint_route_object ( current_airport_inst3d, OBJECT_3D_SUB_OBJECT_FIXED_WING_LANDING_HOLDING_ROUTE );
	fixedwing_takeoff_holding_route = get_airfield_waypoint_route_object ( current_airport_inst3d, OBJECT_3D_SUB_OBJECT_FIXED_WING_TAKEOFF_HOLDING_ROUTE );

	helicopter_landing_holding_route = get_airfield_waypoint_route_object ( current_airport_inst3d, OBJECT_3D_SUB_OBJECT_HELI_LANDING_HOLDING_ROUTE );
	helicopter_takeoff_holding_route = get_airfield_waypoint_route_object ( current_airport_inst3d, OBJECT_3D_SUB_OBJECT_HELI_TAKEOFF_HOLDING_ROUTE );

	vehicle_landing_holding_route = get_airfield_waypoint_route_object ( current_airport_inst3d, OBJECT_3D_SUB_OBJECT_ROUTED_VEHICLE_LANDING_HOLDING_ROUTE );
	vehicle_takeoff_holding_route = get_airfield_waypoint_route_object ( current_airport_inst3d, OBJECT_3D_SUB_OBJECT_ROUTED_VEHICLE_TAKEOFF_HOLDING_ROUTE );

	ship_landing_holding_route = get_airfield_waypoint_route_object ( current_airport_inst3d, OBJECT_3D_SUB_OBJECT_SHIP_LANDING_HOLDING_ROUTE );
	ship_takeoff_holding_route = get_airfield_waypoint_route_object ( current_airport_inst3d, OBJECT_3D_SUB_OBJECT_SHIP_TAKEOFF_HOLDING_ROUTE );

	//
	// Create keysite,
	//

	{

		int
			total_landing_sites;

		int
			current_route_waypoint_offset,
			raw_object_index,
			number_of_matching_slots,
			slot_count;

		vec3d
			*matching_slots;


		//
		// Insert FIXEDWING waypoint routes into keysite.
		//

		if ( ( fixedwing_landing_route ) && ( fixedwing_takeoff_route ) )
		{

			//
			// Insert the landing routes
			//

			raw_object_index = fixedwing_landing_route->index;

			parse_waypoint_routes_from_object ( raw_object_index, 0, NULL );

			current_route_waypoint_offset = number_of_route_waypoint_positions - 1;

			total_landing_sites = route_waypoint_positions[current_route_waypoint_offset].number_of_positions;

			number_of_matching_slots = total_landing_sites;

			matching_slots = safe_malloc ( sizeof ( vec3d ) * number_of_matching_slots );

			memcpy ( matching_slots, route_waypoint_positions[current_route_waypoint_offset].offsets, ( sizeof ( vec3d ) * number_of_matching_slots ) );

			for ( slot_count = 0; slot_count < number_of_matching_slots; slot_count++ )
			{

				matching_slots[slot_count].x += route_waypoint_positions[current_route_waypoint_offset].position.x;
				matching_slots[slot_count].y += route_waypoint_positions[current_route_waypoint_offset].position.y;
				matching_slots[slot_count].z += route_waypoint_positions[current_route_waypoint_offset].position.z;
			}

			destroy_routegen_waypoint_routes ();

			//
			// Insert the takeoff routes
			//

			raw_object_index = fixedwing_takeoff_route->index;

			parse_waypoint_routes_from_object ( raw_object_index, number_of_matching_slots, matching_slots );

			destroy_routegen_waypoint_routes ();

			//
			// Insert the holding loops for fixed wing takeoff & landing.
			//

			if ( ( fixedwing_landing_holding_route ) && ( fixedwing_takeoff_holding_route ) )
			{

				//
				// Insert the landing holding routes
				//

				raw_object_index = fixedwing_landing_holding_route->index;

				parse_waypoint_routes_from_object ( raw_object_index, 0, NULL );

				destroy_routegen_waypoint_routes ();

				//
				// Insert the takeoff holding routes
				//

				raw_object_index = fixedwing_takeoff_holding_route->index;

				parse_waypoint_routes_from_object ( raw_object_index, 0, NULL );

				destroy_routegen_waypoint_routes ();
			}

			if ( matching_slots )
			{

				safe_free ( matching_slots );

				matching_slots = NULL;
			}
		}

		//
		// Insert HELICOPTER waypoint routes into keysite.
		//

		if ( ( helicopter_landing_route ) && ( helicopter_takeoff_route ) )
		{

			//
			// Insert the landing routes
			//

			raw_object_index = helicopter_landing_route->index;

			parse_waypoint_routes_from_object ( raw_object_index, 0, NULL );

			current_route_waypoint_offset = number_of_route_waypoint_positions - 1;

			total_landing_sites = route_waypoint_positions[current_route_waypoint_offset].number_of_positions;

			number_of_matching_slots = total_landing_sites;

			matching_slots = safe_malloc ( sizeof ( vec3d ) * number_of_matching_slots );

			memcpy ( matching_slots, route_waypoint_positions[current_route_waypoint_offset].offsets, ( sizeof ( vec3d ) * number_of_matching_slots ) );

			for ( slot_count = 0; slot_count < number_of_matching_slots; slot_count++ )
			{

				matching_slots[slot_count].x += route_waypoint_positions[current_route_waypoint_offset].position.x;
				matching_slots[slot_count].y += route_waypoint_positions[current_route_waypoint_offset].position.y;
				matching_slots[slot_count].z += route_waypoint_positions[current_route_waypoint_offset].position.z;
			}

			destroy_routegen_waypoint_routes ();

			//
			// Insert the takeoff routes
			//

			raw_object_index = helicopter_takeoff_route->index;

			parse_waypoint_routes_from_object ( raw_object_index, number_of_matching_slots, matching_slots );

			destroy_routegen_waypoint_routes ();

			//
			// Insert the holding loops for helicopter takeoff & landing.
			//

			if ( ( helicopter_landing_holding_route ) && ( helicopter_takeoff_holding_route ) )
			{

				//
				// Insert the landing holding routes
				//

				raw_object_index = helicopter_landing_holding_route->index;

				parse_waypoint_routes_from_object ( raw_object_index, 0, NULL );

				destroy_routegen_waypoint_routes ();

				//
				// Insert the takeoff holding routes
				//

				raw_object_index = helicopter_takeoff_holding_route->index;

				parse_waypoint_routes_from_object ( raw_object_index, 0, NULL );

				destroy_routegen_waypoint_routes ();
			}
		}

		//
		// Insert ROUTED VEHICLE waypoint routes into keysite.
		//

		if ( ( vehicle_landing_route ) && ( vehicle_takeoff_route ) )
		{

			//
			// Insert the landing routes
			//

			raw_object_index = vehicle_landing_route->index;

			parse_waypoint_routes_from_object ( raw_object_index, 0, NULL );

			current_route_waypoint_offset = number_of_route_waypoint_positions - 1;

			total_landing_sites = route_waypoint_positions[current_route_waypoint_offset].number_of_positions;

			number_of_matching_slots = total_landing_sites;

			matching_slots = safe_malloc ( sizeof ( vec3d ) * number_of_matching_slots );

			memcpy ( matching_slots, route_waypoint_positions[current_route_waypoint_offset].offsets, ( sizeof ( vec3d ) * number_of_matching_slots ) );

			for ( slot_count = 0; slot_count < number_of_matching_slots; slot_count++ )
			{

				matching_slots[slot_count].x += route_waypoint_positions[current_route_waypoint_offset].position.x;
				matching_slots[slot_count].y += route_waypoint_positions[current_route_waypoint_offset].position.y;
				matching_slots[slot_count].z += route_waypoint_positions[current_route_waypoint_offset].position.z;
			}

			destroy_routegen_waypoint_routes ();

			//
			// Insert the takeoff routes
			//

			raw_object_index = vehicle_takeoff_route->index;

			parse_waypoint_routes_from_object ( raw_object_index, number_of_matching_slots, matching_slots );

			destroy_routegen_waypoint_routes ();

			//
			// Insert the holding loops
			//

			if ( ( vehicle_landing_holding_route ) && ( vehicle_takeoff_holding_route ) )
			{

				//
				// Insert the landing holding routes
				//

				raw_object_index = vehicle_landing_holding_route->index;

				parse_waypoint_routes_from_object ( raw_object_index, 0, NULL );

				destroy_routegen_waypoint_routes ();

				//
				// Insert the takeoff holding routes
				//

				raw_object_index = vehicle_takeoff_holding_route->index;

				parse_waypoint_routes_from_object ( raw_object_index, 0, NULL );

				destroy_routegen_waypoint_routes ();
			}
		}

		//
		// Insert SHIP waypoint routes into keysite.
		//

		if ( ( ship_landing_route ) && ( ship_takeoff_route ) )
		{

			//
			// Insert the landing routes
			//

			raw_object_index = ship_landing_route->index;

			parse_waypoint_routes_from_object ( raw_object_index, 0, NULL );

			current_route_waypoint_offset = number_of_route_waypoint_positions - 1;

			total_landing_sites = route_waypoint_positions[current_route_waypoint_offset].number_of_positions;

			number_of_matching_slots = total_landing_sites;

			matching_slots = safe_malloc ( sizeof ( vec3d ) * number_of_matching_slots );

			memcpy ( matching_slots, route_waypoint_positions[current_route_waypoint_offset].offsets, ( sizeof ( vec3d ) * number_of_matching_slots ) );

			for ( slot_count = 0; slot_count < number_of_matching_slots; slot_count++ )
			{

				matching_slots[slot_count].x += route_waypoint_positions[current_route_waypoint_offset].position.x;
				matching_slots[slot_count].y += route_waypoint_positions[current_route_waypoint_offset].position.y;
				matching_slots[slot_count].z += route_waypoint_positions[current_route_waypoint_offset].position.z;
			}

			destroy_routegen_waypoint_routes ();

			//
			// Insert the takeoff routes
			//

			raw_object_index = ship_takeoff_route->index;

			parse_waypoint_routes_from_object ( raw_object_index, number_of_matching_slots, matching_slots );

			destroy_routegen_waypoint_routes ();

			//
			// Insert the holding loops
			//

			if ( ( ship_landing_holding_route ) && ( ship_takeoff_holding_route ) )
			{

				//
				// Insert the landing holding routes
				//

				raw_object_index = ship_landing_holding_route->index;

				parse_waypoint_routes_from_object ( raw_object_index, 0, NULL );

				destroy_routegen_waypoint_routes ();

				//
				// Insert the takeoff holding routes
				//

				raw_object_index = ship_takeoff_holding_route->index;

				parse_waypoint_routes_from_object ( raw_object_index, 0, NULL );

				destroy_routegen_waypoint_routes ();
			}
		}

		destruct_3d_object ( current_airport_inst3d );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned int get_waypoint_inhangar_bits ( route_waypoint_position *waypoint, object_3d_instance *inst3d )
{

	int
		count,
		object;

	unsigned int
		inhangar_bits;

	object_3d_scene_database_entry
		*scene_link,
		*scene;

	inhangar_bits = 0;

	scene = &objects_3d_scene_database[inst3d->object_number];

	ASSERT ( waypoint->number_of_positions < 32 );

	for ( count = 0; count < waypoint->number_of_positions; count++ )
	{

		vec3d
			waypoint_position;

		waypoint_position.x = waypoint->position.x + waypoint->offsets[count].x;
		waypoint_position.y = waypoint->position.y + waypoint->offsets[count].y;
		waypoint_position.z = waypoint->position.z + waypoint->offsets[count].z;

		for ( object = 0; object < scene->number_of_scene_link_objects; object++ )
		{

			object_3d_bounds
				object_bounds;

			scene_link = &objects_3d_scene_database[ scene->scene_link_objects[object].scene_index ];

			object_bounds.xmin = scene_link->bounding_box2.xmin + scene->scene_link_objects[object].x;
			object_bounds.xmax = scene_link->bounding_box2.xmax + scene->scene_link_objects[object].x;
			object_bounds.zmin = scene_link->bounding_box2.zmin + scene->scene_link_objects[object].z;
			object_bounds.zmax = scene_link->bounding_box2.zmax + scene->scene_link_objects[object].z;

			if (	( ( waypoint_position.x >= object_bounds.xmin ) && ( waypoint_position.x <= object_bounds.xmax ) ) &&
					( ( waypoint_position.z >= object_bounds.zmin ) && ( waypoint_position.z <= object_bounds.zmax ) ) )
			{

				//
				// Set the in hangar bit
				//

				inhangar_bits |= ( 1 << count );
			}
		}
	}

	return ( inhangar_bits );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_object_index_from_name ( char *name )
{

	int
		count;

	for ( count = OBJECT_3D_INVALID_OBJECT_INDEX + 1; count < OBJECT_3D_LAST; count++ )
	{

		if ( stricmp ( name, object_3d_enumeration_names[count] ) == 0 )
		{

			return ( count );
		}
	}

	return ( OBJECT_3D_INVALID_OBJECT_INDEX );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

object_3d_database_entry * get_airfield_waypoint_route_object ( object_3d_instance *instance, object_3d_sub_object_index_numbers index )
{

	object_3d_sub_object_search_data
		search;

	search.search_object = instance;
	search.search_depth = 0;
	search.sub_object_index = index;

	if ( find_object_3d_sub_object ( &search ) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND )
	{

		return ( search.object_scene );
	}
	else
	{

		return ( NULL );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void insert_airport_fixedwing_routes ( int entity_subtype, vec3d *position, object_3d_database_entry *landing_route, object_3d_database_entry *takeoff_route )
{

	int
		current_route_waypoint_offset,
		raw_object_index,
		number_of_matching_slots,
		total_landing_sites,
		slot_count,
		formation_index;

	vec3d
		waypoint_world_pos,
		*matching_slots,
		*keysite_pos;

	entity
		*landing;

	unsigned int
		inhangar_flags;

	//
	// Insert the landing routes
	//

	raw_object_index = landing_route->index;

	parse_waypoint_routes_from_object ( raw_object_index, 0, NULL );

	current_route_waypoint_offset = number_of_route_waypoint_positions - 1;

	total_landing_sites = route_waypoint_positions[current_route_waypoint_offset].number_of_positions;

	number_of_matching_slots = total_landing_sites;

	matching_slots = safe_malloc ( sizeof ( vec3d ) * number_of_matching_slots );

	memcpy ( matching_slots, route_waypoint_positions[current_route_waypoint_offset].offsets, ( sizeof ( vec3d ) * number_of_matching_slots ) );

	for ( slot_count = 0; slot_count < number_of_matching_slots; slot_count++ )
	{

		matching_slots[slot_count].x += route_waypoint_positions[current_route_waypoint_offset].position.x;
		matching_slots[slot_count].y += route_waypoint_positions[current_route_waypoint_offset].position.y;
		matching_slots[slot_count].z += route_waypoint_positions[current_route_waypoint_offset].position.z;
	}

	keysite_pos = get_local_entity_vec3d_ptr ( get_parser_keysite (), VEC3D_TYPE_POSITION );

	landing =	create_local_entity
					(
						ENTITY_TYPE_LANDING,
						ENTITY_INDEX_DONT_CARE,
						ENTITY_ATTR_PARENT ( LIST_TYPE_LANDING_SITE, get_parser_keysite () ),
						ENTITY_ATTR_VEC3D ( VEC3D_TYPE_POSITION, keysite_pos->x, keysite_pos->y, keysite_pos->z ),
						ENTITY_ATTR_INT_VALUE ( INT_TYPE_ENTITY_SUB_TYPE, entity_subtype ),
						ENTITY_ATTR_INT_VALUE ( INT_TYPE_TOTAL_LANDING_SITES, total_landing_sites ),
						ENTITY_ATTR_END
					);

	// update keysites landing types
	{

		unsigned int
			landing_types;

		landing_types = get_local_entity_int_value (get_parser_keysite (), INT_TYPE_LANDING_TYPES);

		ASSERT (!(landing_types & 1 << get_local_entity_int_value (landing, INT_TYPE_ENTITY_SUB_TYPE)));

		landing_types |= 1 << get_local_entity_int_value (landing, INT_TYPE_ENTITY_SUB_TYPE);

		set_local_entity_int_value (get_parser_keysite (), INT_TYPE_LANDING_TYPES, landing_types);
	}

	set_parser_landing ( landing );

	set_parser_route ( get_local_landing_entity_task ( get_parser_landing (), ENTITY_SUB_TYPE_TASK_LANDING ) );

	{

		//
		// Landed waypoint
		//

		waypoint_world_pos.x = position->x + route_waypoint_positions[current_route_waypoint_offset].position.x;
		waypoint_world_pos.y = position->y + route_waypoint_positions[current_route_waypoint_offset].position.y;
		waypoint_world_pos.z = position->z + route_waypoint_positions[current_route_waypoint_offset].position.z;

		inhangar_flags = get_waypoint_inhangar_bits ( &route_waypoint_positions[current_route_waypoint_offset], current_airport_inst3d );

		set_local_entity_int_value (landing, INT_TYPE_INSIDE_HANGAR, inhangar_flags);

		formation_index = add_formation_to_database ( route_waypoint_positions[current_route_waypoint_offset].number_of_positions,
																		route_waypoint_positions[current_route_waypoint_offset].offsets );

		create_airfield_waypoint ( ENTITY_SUB_TYPE_WAYPOINT_LANDED, &waypoint_world_pos, formation_index, WAYPOINT_ALTITUDE );

		current_route_waypoint_offset--;

		for ( ; current_route_waypoint_offset > 3; current_route_waypoint_offset-- )
		{

			//
			// Taxi-ing waypoints
			//

			waypoint_world_pos.x = position->x + route_waypoint_positions[current_route_waypoint_offset].position.x;
			waypoint_world_pos.y = position->y + route_waypoint_positions[current_route_waypoint_offset].position.y;
			waypoint_world_pos.z = position->z + route_waypoint_positions[current_route_waypoint_offset].position.z;

			formation_index = add_formation_to_database ( route_waypoint_positions[current_route_waypoint_offset].number_of_positions,
																			route_waypoint_positions[current_route_waypoint_offset].offsets );
			create_airfield_waypoint ( ENTITY_SUB_TYPE_WAYPOINT_TAXI, &waypoint_world_pos, formation_index, WAYPOINT_ALTITUDE );
		}

		//
		// Touchdown waypoint
		//

		waypoint_world_pos.x = position->x + route_waypoint_positions[current_route_waypoint_offset].position.x;
		waypoint_world_pos.y = position->y + route_waypoint_positions[current_route_waypoint_offset].position.y;
		waypoint_world_pos.z = position->z + route_waypoint_positions[current_route_waypoint_offset].position.z;

		formation_index = add_formation_to_database ( route_waypoint_positions[current_route_waypoint_offset].number_of_positions,
																		route_waypoint_positions[current_route_waypoint_offset].offsets );
		create_airfield_waypoint ( ENTITY_SUB_TYPE_WAYPOINT_TOUCH_DOWN, &waypoint_world_pos, formation_index, WAYPOINT_ALTITUDE );

		current_route_waypoint_offset--;

		//
		// Lower undercarriage waypoint
		//

		waypoint_world_pos.x = position->x + route_waypoint_positions[current_route_waypoint_offset].position.x;
		waypoint_world_pos.y = position->y + route_waypoint_positions[current_route_waypoint_offset].position.y;
		waypoint_world_pos.z = position->z + route_waypoint_positions[current_route_waypoint_offset].position.z;

		formation_index = add_formation_to_database ( route_waypoint_positions[current_route_waypoint_offset].number_of_positions,
																		route_waypoint_positions[current_route_waypoint_offset].offsets );
		create_airfield_waypoint ( ENTITY_SUB_TYPE_WAYPOINT_LOWER_UNDERCARRIAGE, &waypoint_world_pos, formation_index, WAYPOINT_ALTITUDE );

		current_route_waypoint_offset--;

		//
		// Approach waypoint
		//

		waypoint_world_pos.x = position->x + route_waypoint_positions[current_route_waypoint_offset].position.x;
		waypoint_world_pos.y = position->y + route_waypoint_positions[current_route_waypoint_offset].position.y;
		waypoint_world_pos.z = position->z + route_waypoint_positions[current_route_waypoint_offset].position.z;

		formation_index = add_formation_to_database ( route_waypoint_positions[current_route_waypoint_offset].number_of_positions,
																		route_waypoint_positions[current_route_waypoint_offset].offsets );
		create_airfield_waypoint ( ENTITY_SUB_TYPE_WAYPOINT_APPROACH, &waypoint_world_pos, formation_index, WAYPOINT_ALTITUDE );

		//
		// Approach waypoint
		//

		waypoint_world_pos.x = position->x + route_waypoint_positions[current_route_waypoint_offset].position.x;
		waypoint_world_pos.y = position->y + route_waypoint_positions[current_route_waypoint_offset].position.y;
		waypoint_world_pos.z = position->z + route_waypoint_positions[current_route_waypoint_offset].position.z;

		formation_index = add_formation_to_database ( route_waypoint_positions[current_route_waypoint_offset].number_of_positions,
																		route_waypoint_positions[current_route_waypoint_offset].offsets );
		create_airfield_waypoint ( ENTITY_SUB_TYPE_WAYPOINT_APPROACH, &waypoint_world_pos, formation_index, WAYPOINT_ALTITUDE );
	}

	destroy_routegen_waypoint_routes ();

	//
	// Insert the takeoff routes
	//

	raw_object_index = takeoff_route->index;

	parse_waypoint_routes_from_object ( raw_object_index, number_of_matching_slots, matching_slots );

	current_route_waypoint_offset = 0;

	set_parser_route ( get_local_landing_entity_task ( get_parser_landing (), ENTITY_SUB_TYPE_TASK_TAKEOFF ) );

	{

		//
		// Taken off waypoint
		//

		waypoint_world_pos.x = position->x + route_waypoint_positions[current_route_waypoint_offset].position.x;
		waypoint_world_pos.y = position->y + route_waypoint_positions[current_route_waypoint_offset].position.y;
		waypoint_world_pos.z = position->z + route_waypoint_positions[current_route_waypoint_offset].position.z;

		formation_index = add_formation_to_database ( route_waypoint_positions[current_route_waypoint_offset].number_of_positions,
																		route_waypoint_positions[current_route_waypoint_offset].offsets );
		create_airfield_waypoint ( ENTITY_SUB_TYPE_WAYPOINT_TAKEN_OFF, &waypoint_world_pos, formation_index, WAYPOINT_ALTITUDE );
		current_route_waypoint_offset++;

		//
		// Raise undercarriage waypoint
		//

		waypoint_world_pos.x = position->x + route_waypoint_positions[current_route_waypoint_offset].position.x;
		waypoint_world_pos.y = position->y + route_waypoint_positions[current_route_waypoint_offset].position.y;
		waypoint_world_pos.z = position->z + route_waypoint_positions[current_route_waypoint_offset].position.z;

		formation_index = add_formation_to_database ( route_waypoint_positions[current_route_waypoint_offset].number_of_positions,
																		route_waypoint_positions[current_route_waypoint_offset].offsets );
		create_airfield_waypoint ( ENTITY_SUB_TYPE_WAYPOINT_RAISE_UNDERCARRIAGE, &waypoint_world_pos, formation_index, WAYPOINT_ALTITUDE );
		current_route_waypoint_offset++;

		//
		// Lift off waypoint
		//

		waypoint_world_pos.x = position->x + route_waypoint_positions[current_route_waypoint_offset].position.x;
		waypoint_world_pos.y = position->y + route_waypoint_positions[current_route_waypoint_offset].position.y;
		waypoint_world_pos.z = position->z + route_waypoint_positions[current_route_waypoint_offset].position.z;

		formation_index = add_formation_to_database ( route_waypoint_positions[current_route_waypoint_offset].number_of_positions,
																		route_waypoint_positions[current_route_waypoint_offset].offsets );
		create_airfield_waypoint ( ENTITY_SUB_TYPE_WAYPOINT_LIFT_OFF, &waypoint_world_pos, formation_index, WAYPOINT_ALTITUDE );
		current_route_waypoint_offset++;

		//
		// Start up waypoint
		//

		waypoint_world_pos.x = position->x + route_waypoint_positions[current_route_waypoint_offset].position.x;
		waypoint_world_pos.y = position->y + route_waypoint_positions[current_route_waypoint_offset].position.y;
		waypoint_world_pos.z = position->z + route_waypoint_positions[current_route_waypoint_offset].position.z;

		formation_index = add_formation_to_database ( route_waypoint_positions[current_route_waypoint_offset].number_of_positions,
																		route_waypoint_positions[current_route_waypoint_offset].offsets );
		create_airfield_waypoint ( ENTITY_SUB_TYPE_WAYPOINT_START_UP, &waypoint_world_pos, formation_index, WAYPOINT_ALTITUDE );
		current_route_waypoint_offset++;

		for ( ; current_route_waypoint_offset < number_of_route_waypoint_positions; current_route_waypoint_offset++ )
		{

			//
			// Taxi-ing waypoints
			//

			waypoint_world_pos.x = position->x + route_waypoint_positions[current_route_waypoint_offset].position.x;
			waypoint_world_pos.y = position->y + route_waypoint_positions[current_route_waypoint_offset].position.y;
			waypoint_world_pos.z = position->z + route_waypoint_positions[current_route_waypoint_offset].position.z;

			formation_index = add_formation_to_database ( route_waypoint_positions[current_route_waypoint_offset].number_of_positions,
																			route_waypoint_positions[current_route_waypoint_offset].offsets );
			create_airfield_waypoint ( ENTITY_SUB_TYPE_WAYPOINT_TAXI, &waypoint_world_pos, formation_index, WAYPOINT_ALTITUDE );
		}
	}

	destroy_routegen_waypoint_routes ();

	if ( matching_slots )
	{

		safe_free ( matching_slots );

		matching_slots = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void insert_airport_helicopter_routes ( vec3d *position, object_3d_database_entry *landing_route, object_3d_database_entry *takeoff_route, object_3d_database_entry *landing_holding_route, object_3d_database_entry *takeoff_holding_route )
{

	int
		current_route_waypoint_offset,
		raw_object_index,
		number_of_matching_slots,
		total_landing_sites,
		slot_count,
		formation_index,
		offset_index;

	vec3d
		waypoint_world_pos,
		*matching_slots,
		*keysite_pos;

	entity
		*landing;

	unsigned int
		inhangar_flags;

	float
		terrain_height,
		height_offset;
	
	//
	// Insert the landing routes
	//

	raw_object_index = landing_route->index;

	parse_waypoint_routes_from_object ( raw_object_index, 0, NULL );

	current_route_waypoint_offset = number_of_route_waypoint_positions - 1;

	total_landing_sites = route_waypoint_positions[current_route_waypoint_offset].number_of_positions;

	number_of_matching_slots = total_landing_sites;

	matching_slots = safe_malloc ( sizeof ( vec3d ) * number_of_matching_slots );

	memcpy ( matching_slots, route_waypoint_positions[current_route_waypoint_offset].offsets, ( sizeof ( vec3d ) * number_of_matching_slots ) );

	for ( slot_count = 0; slot_count < number_of_matching_slots; slot_count++ )
	{

		matching_slots[slot_count].x += route_waypoint_positions[current_route_waypoint_offset].position.x;
		matching_slots[slot_count].y += route_waypoint_positions[current_route_waypoint_offset].position.y;
		matching_slots[slot_count].z += route_waypoint_positions[current_route_waypoint_offset].position.z;
	}

	keysite_pos = get_local_entity_vec3d_ptr ( get_parser_keysite (), VEC3D_TYPE_POSITION );

	landing =	create_local_entity
					(
						ENTITY_TYPE_LANDING,
						ENTITY_INDEX_DONT_CARE,
						ENTITY_ATTR_PARENT ( LIST_TYPE_LANDING_SITE, get_parser_keysite () ),
						ENTITY_ATTR_VEC3D ( VEC3D_TYPE_POSITION, keysite_pos->x, keysite_pos->y, keysite_pos->z ),
						ENTITY_ATTR_INT_VALUE ( INT_TYPE_ENTITY_SUB_TYPE, ENTITY_SUB_TYPE_LANDING_HELICOPTER ),
						ENTITY_ATTR_INT_VALUE ( INT_TYPE_TOTAL_LANDING_SITES, total_landing_sites ),
						ENTITY_ATTR_END
					);

	// update keysites landing types
	{

		unsigned int
			landing_types;

		landing_types = get_local_entity_int_value (get_parser_keysite (), INT_TYPE_LANDING_TYPES);

		ASSERT (!(landing_types & 1 << get_local_entity_int_value (landing, INT_TYPE_ENTITY_SUB_TYPE)));

		landing_types |= 1 << get_local_entity_int_value (landing, INT_TYPE_ENTITY_SUB_TYPE);

		set_local_entity_int_value (get_parser_keysite (), INT_TYPE_LANDING_TYPES, landing_types);
	}

	set_parser_landing ( landing );

	set_parser_route ( get_local_landing_entity_task ( get_parser_landing (), ENTITY_SUB_TYPE_TASK_LANDING ) );

	{

		//
		// Landed waypoint
		//

		waypoint_world_pos.x = position->x + route_waypoint_positions[current_route_waypoint_offset].position.x;
		waypoint_world_pos.y = position->y + route_waypoint_positions[current_route_waypoint_offset].position.y;
		waypoint_world_pos.z = position->z + route_waypoint_positions[current_route_waypoint_offset].position.z;

		height_offset = 0;

		for ( offset_index = 0; offset_index < route_waypoint_positions[current_route_waypoint_offset].number_of_positions; offset_index++ )
		{

			terrain_height = get_3d_terrain_point_data ( waypoint_world_pos.x + route_waypoint_positions[current_route_waypoint_offset].offsets[offset_index].x,
																		waypoint_world_pos.z + route_waypoint_positions[current_route_waypoint_offset].offsets[offset_index].z, NULL );

			if ( terrain_height > position->y )
			{

				height_offset = max ( height_offset, ( terrain_height - position->y ) );
			}
		}

		waypoint_world_pos.y += height_offset;

//VJ FARP bug, date: 18-mar-03

// ensure the waypoint elevation (y coord) is at the terrain elevation or higher (because ships are 20m above sealevel)
// and add 10 cm to the elevation to ensure the aircraft touch the ground when landing, 
// this seems to trigger a change of status
		waypoint_world_pos.y = max(waypoint_world_pos.y,get_3d_terrain_point_data (waypoint_world_pos.x,waypoint_world_pos.z, NULL ));		
		waypoint_world_pos.y += 0.1;
//VJ FARP bug, date: 18-mar-03, end

		inhangar_flags = get_waypoint_inhangar_bits ( &route_waypoint_positions[current_route_waypoint_offset], current_airport_inst3d );

		formation_index = add_formation_to_database ( route_waypoint_positions[current_route_waypoint_offset].number_of_positions,
																		route_waypoint_positions[current_route_waypoint_offset].offsets );

		create_airfield_waypoint ( ENTITY_SUB_TYPE_WAYPOINT_LANDED, &waypoint_world_pos, formation_index, WAYPOINT_ALTITUDE );

		current_route_waypoint_offset--;

		for ( ; current_route_waypoint_offset >= 0; current_route_waypoint_offset-- )
		{

			//
			// Taxi-ing waypoints
			//

			waypoint_world_pos.x = position->x + route_waypoint_positions[current_route_waypoint_offset].position.x;
			waypoint_world_pos.y = position->y + route_waypoint_positions[current_route_waypoint_offset].position.y;
			waypoint_world_pos.z = position->z + route_waypoint_positions[current_route_waypoint_offset].position.z;

			height_offset = 0;

			for ( offset_index = 0; offset_index < route_waypoint_positions[current_route_waypoint_offset].number_of_positions; offset_index++ )
			{

				terrain_height = get_3d_terrain_point_data ( waypoint_world_pos.x + route_waypoint_positions[current_route_waypoint_offset].offsets[offset_index].x,
																			waypoint_world_pos.z + route_waypoint_positions[current_route_waypoint_offset].offsets[offset_index].z, NULL );

				if ( terrain_height > position->y )
				{

					height_offset = max ( height_offset, ( terrain_height - position->y ) );
				}
			}

			waypoint_world_pos.y += height_offset;

			formation_index = add_formation_to_database ( route_waypoint_positions[current_route_waypoint_offset].number_of_positions,
																			route_waypoint_positions[current_route_waypoint_offset].offsets );

//			if ( current_route_waypoint_offset == 1 )
			if ( current_route_waypoint_offset == (number_of_route_waypoint_positions - 2))
			{

				create_airfield_waypoint ( ENTITY_SUB_TYPE_WAYPOINT_LOWER_UNDERCARRIAGE, &waypoint_world_pos, formation_index, WAYPOINT_ALTITUDE );
			}
			else
			{

				create_airfield_waypoint ( ENTITY_SUB_TYPE_WAYPOINT_TAXI, &waypoint_world_pos, formation_index, WAYPOINT_ALTITUDE );
			}
		}
	}

	destroy_routegen_waypoint_routes ();

	//
	// Insert the takeoff routes
	//

	raw_object_index = takeoff_route->index;

	parse_waypoint_routes_from_object ( raw_object_index, number_of_matching_slots, matching_slots );

	current_route_waypoint_offset = 0;

	set_parser_route ( get_local_landing_entity_task ( get_parser_landing (), ENTITY_SUB_TYPE_TASK_TAKEOFF ) );

	{

		waypoint_world_pos.x = position->x + route_waypoint_positions[current_route_waypoint_offset].position.x;
		waypoint_world_pos.y = position->y + route_waypoint_positions[current_route_waypoint_offset].position.y;
		waypoint_world_pos.z = position->z + route_waypoint_positions[current_route_waypoint_offset].position.z;

		height_offset = 0;

		for ( offset_index = 0; offset_index < route_waypoint_positions[current_route_waypoint_offset].number_of_positions; offset_index++ )
		{

			terrain_height = get_3d_terrain_point_data ( waypoint_world_pos.x + route_waypoint_positions[current_route_waypoint_offset].offsets[offset_index].x,
																		waypoint_world_pos.z + route_waypoint_positions[current_route_waypoint_offset].offsets[offset_index].z, NULL );

			if ( terrain_height > position->y )
			{

				height_offset = max ( height_offset, ( terrain_height - position->y ) );
			}
		}

		waypoint_world_pos.y += height_offset;

		//
		// Taken off waypoint
		//

		formation_index = add_formation_to_database ( route_waypoint_positions[current_route_waypoint_offset].number_of_positions,
																		route_waypoint_positions[current_route_waypoint_offset].offsets );

		create_airfield_waypoint ( ENTITY_SUB_TYPE_WAYPOINT_TAKEN_OFF, &waypoint_world_pos, formation_index, WAYPOINT_ALTITUDE );

		current_route_waypoint_offset++;

		for ( ; current_route_waypoint_offset < number_of_route_waypoint_positions; current_route_waypoint_offset++ )
		{

			//
			// Taxi-ing waypoints
			//

			waypoint_world_pos.x = position->x + route_waypoint_positions[current_route_waypoint_offset].position.x;
			waypoint_world_pos.y = position->y + route_waypoint_positions[current_route_waypoint_offset].position.y;
			waypoint_world_pos.z = position->z + route_waypoint_positions[current_route_waypoint_offset].position.z;

			height_offset = 0;

			for ( offset_index = 0; offset_index < route_waypoint_positions[current_route_waypoint_offset].number_of_positions; offset_index++ )
			{

				terrain_height = get_3d_terrain_point_data ( waypoint_world_pos.x + route_waypoint_positions[current_route_waypoint_offset].offsets[offset_index].x,
																			waypoint_world_pos.z + route_waypoint_positions[current_route_waypoint_offset].offsets[offset_index].z, NULL );

				if ( terrain_height > position->y )
				{

					height_offset = max ( height_offset, ( terrain_height - position->y ) );
				}
			}

			waypoint_world_pos.y += height_offset;

			formation_index = add_formation_to_database ( route_waypoint_positions[current_route_waypoint_offset].number_of_positions,
																			route_waypoint_positions[current_route_waypoint_offset].offsets );

			if ( current_route_waypoint_offset == ( number_of_route_waypoint_positions - 2 ) )
			{

				create_airfield_waypoint ( ENTITY_SUB_TYPE_WAYPOINT_RAISE_UNDERCARRIAGE, &waypoint_world_pos, formation_index, WAYPOINT_ALTITUDE );
			}
			else
			{

				create_airfield_waypoint ( ENTITY_SUB_TYPE_WAYPOINT_TAXI, &waypoint_world_pos, formation_index, WAYPOINT_ALTITUDE );
			}
		}
	}

	destroy_routegen_waypoint_routes ();

	//
	// Insert the holding loops for helicopter takeoff & landing.
	//

	if ( ( landing_holding_route ) && ( takeoff_holding_route ) )
	{

		double
			average_x,
			average_y,
			average_z;

		//
		// Insert the landing holding routes
		//

		raw_object_index = landing_holding_route->index;

		parse_waypoint_routes_from_object ( raw_object_index, 0, NULL );

		set_parser_route ( get_local_landing_entity_task ( get_parser_landing (), ENTITY_SUB_TYPE_TASK_LANDING_HOLDING ) );

		{

			//
			// Figure out the average position so we can expand the holding patterns
			//

			current_route_waypoint_offset = 0;

			average_x = position->x + route_waypoint_positions[current_route_waypoint_offset].position.x;
			average_y = position->y + route_waypoint_positions[current_route_waypoint_offset].position.y;
			average_z = position->z + route_waypoint_positions[current_route_waypoint_offset].position.z;

			current_route_waypoint_offset++;

			for ( ; current_route_waypoint_offset < number_of_route_waypoint_positions; current_route_waypoint_offset++ )
			{

				average_x += position->x + route_waypoint_positions[current_route_waypoint_offset].position.x;
				average_y += position->y + route_waypoint_positions[current_route_waypoint_offset].position.y;
				average_z += position->z + route_waypoint_positions[current_route_waypoint_offset].position.z;
			}

			average_x /= number_of_route_waypoint_positions;
			average_y /= number_of_route_waypoint_positions;
			average_z /= number_of_route_waypoint_positions;

			//
			// Loop waypoint
			//

			current_route_waypoint_offset = 0;

			waypoint_world_pos.x = position->x + route_waypoint_positions[current_route_waypoint_offset].position.x;
			waypoint_world_pos.y = position->y + route_waypoint_positions[current_route_waypoint_offset].position.y;
			waypoint_world_pos.z = position->z + route_waypoint_positions[current_route_waypoint_offset].position.z;

			waypoint_world_pos.x += ( waypoint_world_pos.x - average_x ) * 3;
			waypoint_world_pos.y += ( waypoint_world_pos.y - average_y ) * 3;
			waypoint_world_pos.z += ( waypoint_world_pos.z - average_z ) * 3;

			formation_index = add_formation_to_database ( route_waypoint_positions[current_route_waypoint_offset].number_of_positions,
																			route_waypoint_positions[current_route_waypoint_offset].offsets );
			create_airfield_waypoint ( ENTITY_SUB_TYPE_WAYPOINT_HOLDING_LOOP, &waypoint_world_pos, formation_index, WAYPOINT_ALTITUDE );
			current_route_waypoint_offset++;

			for ( ; current_route_waypoint_offset < number_of_route_waypoint_positions; current_route_waypoint_offset++ )
			{

				//
				// Navigation waypoints
				//

				waypoint_world_pos.x = position->x + route_waypoint_positions[current_route_waypoint_offset].position.x;
				waypoint_world_pos.y = position->y + route_waypoint_positions[current_route_waypoint_offset].position.y;
				waypoint_world_pos.z = position->z + route_waypoint_positions[current_route_waypoint_offset].position.z;

				waypoint_world_pos.x += ( waypoint_world_pos.x - average_x ) * 3;
				waypoint_world_pos.y += ( waypoint_world_pos.y - average_y ) * 3;
				waypoint_world_pos.z += ( waypoint_world_pos.z - average_z ) * 3;

				formation_index = add_formation_to_database ( route_waypoint_positions[current_route_waypoint_offset].number_of_positions,
																				route_waypoint_positions[current_route_waypoint_offset].offsets );
				create_airfield_waypoint ( ENTITY_SUB_TYPE_WAYPOINT_HOLDING, &waypoint_world_pos, formation_index, WAYPOINT_ALTITUDE );
			}
		}

		destroy_routegen_waypoint_routes ();

		//
		// Insert the takeoff holding routes
		//

		raw_object_index = takeoff_holding_route->index;

		parse_waypoint_routes_from_object ( raw_object_index, 0, NULL );

		set_parser_route ( get_local_landing_entity_task ( get_parser_landing (), ENTITY_SUB_TYPE_TASK_TAKEOFF_HOLDING ) );

		{

			//
			// Figure out the average position so we can expand the holding patterns
			//

			current_route_waypoint_offset = 0;

			average_x = position->x + route_waypoint_positions[current_route_waypoint_offset].position.x;
			average_y = position->y + route_waypoint_positions[current_route_waypoint_offset].position.y;
			average_z = position->z + route_waypoint_positions[current_route_waypoint_offset].position.z;

			current_route_waypoint_offset++;

			for ( ; current_route_waypoint_offset < number_of_route_waypoint_positions; current_route_waypoint_offset++ )
			{

				average_x += position->x + route_waypoint_positions[current_route_waypoint_offset].position.x;
				average_y += position->y + route_waypoint_positions[current_route_waypoint_offset].position.y;
				average_z += position->z + route_waypoint_positions[current_route_waypoint_offset].position.z;
			}

			average_x /= number_of_route_waypoint_positions;
			average_y /= number_of_route_waypoint_positions;
			average_z /= number_of_route_waypoint_positions;

			//
			// Loop waypoint
			//

			current_route_waypoint_offset = 0;

			waypoint_world_pos.x = position->x + route_waypoint_positions[current_route_waypoint_offset].position.x;
			waypoint_world_pos.y = position->y + route_waypoint_positions[current_route_waypoint_offset].position.y;
			waypoint_world_pos.z = position->z + route_waypoint_positions[current_route_waypoint_offset].position.z;

			waypoint_world_pos.x += ( waypoint_world_pos.x - average_x ) * 3;
			waypoint_world_pos.y += ( waypoint_world_pos.y - average_y ) * 3;
			waypoint_world_pos.z += ( waypoint_world_pos.z - average_z ) * 3;

			formation_index = add_formation_to_database ( route_waypoint_positions[current_route_waypoint_offset].number_of_positions,
																			route_waypoint_positions[current_route_waypoint_offset].offsets );
			create_airfield_waypoint ( ENTITY_SUB_TYPE_WAYPOINT_HOLDING_LOOP, &waypoint_world_pos, formation_index, WAYPOINT_ALTITUDE );
			current_route_waypoint_offset++;

			for ( ; current_route_waypoint_offset < number_of_route_waypoint_positions; current_route_waypoint_offset++ )
			{

				//
				// Navigation waypoints
				//

				waypoint_world_pos.x = position->x + route_waypoint_positions[current_route_waypoint_offset].position.x;
				waypoint_world_pos.y = position->y + route_waypoint_positions[current_route_waypoint_offset].position.y;
				waypoint_world_pos.z = position->z + route_waypoint_positions[current_route_waypoint_offset].position.z;

				waypoint_world_pos.x += ( waypoint_world_pos.x - average_x ) * 3;
				waypoint_world_pos.y += ( waypoint_world_pos.y - average_y ) * 3;
				waypoint_world_pos.z += ( waypoint_world_pos.z - average_z ) * 3;

				formation_index = add_formation_to_database ( route_waypoint_positions[current_route_waypoint_offset].number_of_positions,
																				route_waypoint_positions[current_route_waypoint_offset].offsets );
				create_airfield_waypoint ( ENTITY_SUB_TYPE_WAYPOINT_HOLDING, &waypoint_world_pos, formation_index, WAYPOINT_ALTITUDE );
			}
		}

		destroy_routegen_waypoint_routes ();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void insert_airport_general_takeoff_landing_routes ( int entity_subtype, vec3d *position, object_3d_database_entry *landing_route, object_3d_database_entry *takeoff_route )
{

	int
		current_route_waypoint_offset,
		raw_object_index,
		number_of_matching_slots,
		total_landing_sites,
		slot_count,
		formation_index;

	vec3d
		waypoint_world_pos,
		*matching_slots,
		*keysite_pos;

	entity
		*landing;

	//
	// Insert the landing routes
	//

	raw_object_index = landing_route->index;

	parse_waypoint_routes_from_object ( raw_object_index, 0, NULL );

	current_route_waypoint_offset = number_of_route_waypoint_positions - 1;

	total_landing_sites = route_waypoint_positions[current_route_waypoint_offset].number_of_positions;

	number_of_matching_slots = total_landing_sites;

	matching_slots = safe_malloc ( sizeof ( vec3d ) * number_of_matching_slots );

	memcpy ( matching_slots, route_waypoint_positions[current_route_waypoint_offset].offsets, ( sizeof ( vec3d ) * number_of_matching_slots ) );

	for ( slot_count = 0; slot_count < number_of_matching_slots; slot_count++ )
	{

		matching_slots[slot_count].x += route_waypoint_positions[current_route_waypoint_offset].position.x;
		matching_slots[slot_count].y += route_waypoint_positions[current_route_waypoint_offset].position.y;
		matching_slots[slot_count].z += route_waypoint_positions[current_route_waypoint_offset].position.z;
	}

	keysite_pos = get_local_entity_vec3d_ptr ( get_parser_keysite (), VEC3D_TYPE_POSITION );

	landing =	create_local_entity
					(
						ENTITY_TYPE_LANDING,
						ENTITY_INDEX_DONT_CARE,
						ENTITY_ATTR_PARENT ( LIST_TYPE_LANDING_SITE, get_parser_keysite () ),
						ENTITY_ATTR_VEC3D ( VEC3D_TYPE_POSITION, keysite_pos->x, keysite_pos->y, keysite_pos->z ),
						ENTITY_ATTR_INT_VALUE ( INT_TYPE_ENTITY_SUB_TYPE, entity_subtype ),
						ENTITY_ATTR_INT_VALUE ( INT_TYPE_TOTAL_LANDING_SITES, total_landing_sites ),
						ENTITY_ATTR_END
					);

	// update keysites landing types
	{

		unsigned int
			landing_types;

		landing_types = get_local_entity_int_value (get_parser_keysite (), INT_TYPE_LANDING_TYPES);

		ASSERT (!(landing_types & 1 << get_local_entity_int_value (landing, INT_TYPE_ENTITY_SUB_TYPE)));

		landing_types |= 1 << get_local_entity_int_value (landing, INT_TYPE_ENTITY_SUB_TYPE);

		set_local_entity_int_value (get_parser_keysite (), INT_TYPE_LANDING_TYPES, landing_types);
	}

	set_parser_landing ( landing );

	set_parser_route ( get_local_landing_entity_task ( get_parser_landing (), ENTITY_SUB_TYPE_TASK_LANDING ) );

	{

		//
		// Landed waypoint
		//

		waypoint_world_pos.x = position->x + route_waypoint_positions[current_route_waypoint_offset].position.x;
		waypoint_world_pos.y = position->y + route_waypoint_positions[current_route_waypoint_offset].position.y;
		waypoint_world_pos.z = position->z + route_waypoint_positions[current_route_waypoint_offset].position.z;

		formation_index = add_formation_to_database ( route_waypoint_positions[current_route_waypoint_offset].number_of_positions,
																		route_waypoint_positions[current_route_waypoint_offset].offsets );

		create_airfield_waypoint ( ENTITY_SUB_TYPE_WAYPOINT_LANDED, &waypoint_world_pos, formation_index, WAYPOINT_ALTITUDE );

		current_route_waypoint_offset--;

		for ( ; current_route_waypoint_offset > 0; current_route_waypoint_offset-- )
		{

			//
			// Taxi-ing waypoints
			//

			waypoint_world_pos.x = position->x + route_waypoint_positions[current_route_waypoint_offset].position.x;
			waypoint_world_pos.y = position->y + route_waypoint_positions[current_route_waypoint_offset].position.y;
			waypoint_world_pos.z = position->z + route_waypoint_positions[current_route_waypoint_offset].position.z;

			formation_index = add_formation_to_database ( route_waypoint_positions[current_route_waypoint_offset].number_of_positions,
																			route_waypoint_positions[current_route_waypoint_offset].offsets );
			create_airfield_waypoint ( ENTITY_SUB_TYPE_WAYPOINT_NAVIGATION, &waypoint_world_pos, formation_index, WAYPOINT_ALTITUDE );
		}
	}

	destroy_routegen_waypoint_routes ();

	//
	// Insert the takeoff routes
	//

	raw_object_index = takeoff_route->index;

	parse_waypoint_routes_from_object ( raw_object_index, number_of_matching_slots, matching_slots );

	current_route_waypoint_offset = 0;

	set_parser_route ( get_local_landing_entity_task ( get_parser_landing (), ENTITY_SUB_TYPE_TASK_TAKEOFF ) );

	{

		//
		// Taken off waypoint
		//

		waypoint_world_pos.x = position->x + route_waypoint_positions[current_route_waypoint_offset].position.x;
		waypoint_world_pos.y = position->y + route_waypoint_positions[current_route_waypoint_offset].position.y;
		waypoint_world_pos.z = position->z + route_waypoint_positions[current_route_waypoint_offset].position.z;

		formation_index = add_formation_to_database ( route_waypoint_positions[current_route_waypoint_offset].number_of_positions,
																		route_waypoint_positions[current_route_waypoint_offset].offsets );
		create_airfield_waypoint ( ENTITY_SUB_TYPE_WAYPOINT_TAKEN_OFF, &waypoint_world_pos, formation_index, WAYPOINT_ALTITUDE );
		current_route_waypoint_offset++;

		for ( ; current_route_waypoint_offset < number_of_route_waypoint_positions; current_route_waypoint_offset++ )
		{

			//
			// Taxi-ing waypoints
			//

			waypoint_world_pos.x = position->x + route_waypoint_positions[current_route_waypoint_offset].position.x;
			waypoint_world_pos.y = position->y + route_waypoint_positions[current_route_waypoint_offset].position.y;
			waypoint_world_pos.z = position->z + route_waypoint_positions[current_route_waypoint_offset].position.z;

			formation_index = add_formation_to_database ( route_waypoint_positions[current_route_waypoint_offset].number_of_positions,
																			route_waypoint_positions[current_route_waypoint_offset].offsets );
			create_airfield_waypoint ( ENTITY_SUB_TYPE_WAYPOINT_NAVIGATION, &waypoint_world_pos, formation_index, WAYPOINT_ALTITUDE );
		}
	}

	destroy_routegen_waypoint_routes ();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void insert_airport_holding_routes ( vec3d *position, object_3d_database_entry *landing_holding_route, object_3d_database_entry *takeoff_holding_route )
{

	int
		current_route_waypoint_offset,
		raw_object_index,
		formation_index;

	vec3d
		waypoint_world_pos;

	//
	// Insert the holding loops
	//

	if ( ( landing_holding_route ) && ( takeoff_holding_route ) )
	{

		//
		// Insert the landing holding routes
		//

		raw_object_index = landing_holding_route->index;

		parse_waypoint_routes_from_object ( raw_object_index, 0, NULL );

		current_route_waypoint_offset = 0;

		set_parser_route ( get_local_landing_entity_task ( get_parser_landing (), ENTITY_SUB_TYPE_TASK_LANDING_HOLDING ) );

		{

			//
			// Loop waypoint
			//

			waypoint_world_pos.x = position->x + route_waypoint_positions[current_route_waypoint_offset].position.x;
			waypoint_world_pos.y = position->y + route_waypoint_positions[current_route_waypoint_offset].position.y;
			waypoint_world_pos.z = position->z + route_waypoint_positions[current_route_waypoint_offset].position.z;

			formation_index = add_formation_to_database ( route_waypoint_positions[current_route_waypoint_offset].number_of_positions,
																			route_waypoint_positions[current_route_waypoint_offset].offsets );
			create_airfield_waypoint ( ENTITY_SUB_TYPE_WAYPOINT_HOLDING_LOOP, &waypoint_world_pos, formation_index, WAYPOINT_ALTITUDE );
			current_route_waypoint_offset++;

			for ( ; current_route_waypoint_offset < number_of_route_waypoint_positions; current_route_waypoint_offset++ )
			{

				//
				// Navigation waypoints
				//

				waypoint_world_pos.x = position->x + route_waypoint_positions[current_route_waypoint_offset].position.x;
				waypoint_world_pos.y = position->y + route_waypoint_positions[current_route_waypoint_offset].position.y;
				waypoint_world_pos.z = position->z + route_waypoint_positions[current_route_waypoint_offset].position.z;

				formation_index = add_formation_to_database ( route_waypoint_positions[current_route_waypoint_offset].number_of_positions,
																				route_waypoint_positions[current_route_waypoint_offset].offsets );
				create_airfield_waypoint ( ENTITY_SUB_TYPE_WAYPOINT_HOLDING, &waypoint_world_pos, formation_index, WAYPOINT_ALTITUDE );
			}
		}

		destroy_routegen_waypoint_routes ();

		//
		// Insert the takeoff holding routes
		//

		raw_object_index = takeoff_holding_route->index;

		parse_waypoint_routes_from_object ( raw_object_index, 0, NULL );

		current_route_waypoint_offset = 0;

		set_parser_route ( get_local_landing_entity_task ( get_parser_landing (), ENTITY_SUB_TYPE_TASK_TAKEOFF_HOLDING ) );

		{

			//
			// Loop waypoint
			//

			waypoint_world_pos.x = position->x + route_waypoint_positions[current_route_waypoint_offset].position.x;
			waypoint_world_pos.y = position->y + route_waypoint_positions[current_route_waypoint_offset].position.y;
			waypoint_world_pos.z = position->z + route_waypoint_positions[current_route_waypoint_offset].position.z;

			formation_index = add_formation_to_database ( route_waypoint_positions[current_route_waypoint_offset].number_of_positions,
																			route_waypoint_positions[current_route_waypoint_offset].offsets );
			create_airfield_waypoint ( ENTITY_SUB_TYPE_WAYPOINT_HOLDING_LOOP, &waypoint_world_pos, formation_index, WAYPOINT_ALTITUDE );
			current_route_waypoint_offset++;

			for ( ; current_route_waypoint_offset < number_of_route_waypoint_positions; current_route_waypoint_offset++ )
			{

				//
				// Navigation waypoints
				//

				waypoint_world_pos.x = position->x + route_waypoint_positions[current_route_waypoint_offset].position.x;
				waypoint_world_pos.y = position->y + route_waypoint_positions[current_route_waypoint_offset].position.y;
				waypoint_world_pos.z = position->z + route_waypoint_positions[current_route_waypoint_offset].position.z;

				formation_index = add_formation_to_database ( route_waypoint_positions[current_route_waypoint_offset].number_of_positions,
																				route_waypoint_positions[current_route_waypoint_offset].offsets );
				create_airfield_waypoint ( ENTITY_SUB_TYPE_WAYPOINT_HOLDING, &waypoint_world_pos, formation_index, WAYPOINT_ALTITUDE );
			}
		}

		destroy_routegen_waypoint_routes ();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_airfield_waypoint ( entity_sub_types type, vec3d *waypoint_world_pos, int formation_index, float altitude )
{

	entity
		*wp;

	wp = create_local_entity
	(
		ENTITY_TYPE_WAYPOINT,
		ENTITY_INDEX_DONT_CARE,
		ENTITY_ATTR_PARENT ( LIST_TYPE_WAYPOINT, get_parser_route () ),
		ENTITY_ATTR_INT_VALUE ( INT_TYPE_ENTITY_SUB_TYPE, type ),
		ENTITY_ATTR_INT_VALUE ( INT_TYPE_WAYPOINT_FORMATION, formation_index ),
		ENTITY_ATTR_INT_VALUE ( INT_TYPE_POSITION_TYPE, POSITION_TYPE_RELATIVE ),
		ENTITY_ATTR_FLOAT_VALUE ( FLOAT_TYPE_ALTITUDE, altitude ),
		ENTITY_ATTR_VEC3D ( VEC3D_TYPE_POSITION, waypoint_world_pos->x, waypoint_world_pos->y, waypoint_world_pos->z ),
		ENTITY_ATTR_PTR_VALUE ( PTR_TYPE_POSITION_ENTITY, NULL),
		ENTITY_ATTR_END
	);

	/////////////////////////////////////////////////////////////////
	update_gunships_screen_progress_indicator ();
	/////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void insert_airfield_buildings ( int side, object_3d_instance *instance )
{

	int
		regeneration_sub_type,
		landing_sub_type,
		count;

	entity
		*keysite_group,
		*building;

	keysite_group = get_local_entity_first_child ( get_parser_keysite (), LIST_TYPE_BUILDING_GROUP );

	for ( count = 0; count < objects_3d_scene_database[instance->object_number].number_of_scene_link_objects; count++ )
	{

		float
			heading;

		vec3d
			position;

		int
			object_index;

		position.x = objects_3d_scene_database[instance->object_number].scene_link_objects[count].x;
		position.y = objects_3d_scene_database[instance->object_number].scene_link_objects[count].y;
		position.z = objects_3d_scene_database[instance->object_number].scene_link_objects[count].z;

		position.x += instance->vp.x;
		position.y += instance->vp.y;
		position.z += instance->vp.z;

		if (get_local_entity_int_value (get_parser_keysite (), INT_TYPE_ALIGN_WITH_TERRAIN))
		{

			position.y = get_3d_terrain_elevation (position.x, position.z);
		}

		heading = objects_3d_scene_database[instance->object_number].scene_link_objects[count].heading;

		object_index = objects_3d_scene_database[instance->object_number].scene_link_objects[count].scene_index;

		regeneration_sub_type = get_object_3d_regeneration_type ( object_index, &landing_sub_type );

		if (regeneration_sub_type != ENTITY_SUB_TYPE_REGEN_NONE)
		{

			entity
				*wp,
				*regen,
				*landing,
				*closest_wp;

			float
				wp_range,
				closest_wp_range;

			//
			// find closest waypoint
			//

			landing = get_local_entity_landing_entity (get_parser_keysite (), landing_sub_type);

			if (landing)
			{

				wp = get_local_landing_entity_route (landing, ENTITY_SUB_TYPE_TASK_LANDING);

				closest_wp = NULL;

				closest_wp_range = 10000000;

				while (wp)
				{

					if ((get_local_entity_int_value (wp, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_WAYPOINT_TAXI) ||
						(get_local_entity_int_value (wp, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_WAYPOINT_NAVIGATION) ||
						(get_local_entity_int_value (wp, INT_TYPE_ENTITY_SUB_TYPE) == ENTITY_SUB_TYPE_WAYPOINT_LANDED))
					{
	
						wp_range = get_2d_range (get_local_entity_vec3d_ptr (wp, VEC3D_TYPE_POSITION), &position);
	
						if (wp_range < closest_wp_range)
						{
	
							closest_wp_range = wp_range;
	
							closest_wp = wp;
						}
					}

					wp = get_local_entity_child_succ (wp, LIST_TYPE_WAYPOINT);
				}

				ASSERT (closest_wp);

				//
				// Create regen
				//

				regen = create_local_entity
				(
					ENTITY_TYPE_REGEN,
					ENTITY_INDEX_DONT_CARE,
					ENTITY_ATTR_PARENT (LIST_TYPE_REGEN, get_parser_keysite ()),
					ENTITY_ATTR_PARENT (LIST_TYPE_CURRENT_WAYPOINT, closest_wp),
					ENTITY_ATTR_INT_VALUE (INT_TYPE_ENTITY_SUB_TYPE, regeneration_sub_type),
					ENTITY_ATTR_INT_VALUE (INT_TYPE_ALIVE, TRUE),
					ENTITY_ATTR_INT_VALUE (INT_TYPE_SIDE, side),
					ENTITY_ATTR_VEC3D (VEC3D_TYPE_POSITION, position.x, position.y, position.z),
					ENTITY_ATTR_END
				);

				//
				// Create building
				//

				building = create_local_entity
							(
								ENTITY_TYPE_SITE_UPDATABLE,
								ENTITY_INDEX_DONT_CARE,
								ENTITY_ATTR_PARENT ( LIST_TYPE_MEMBER, regen ),
								ENTITY_ATTR_INT_VALUE ( INT_TYPE_ENTITY_SUB_TYPE,ENTITY_SUB_TYPE_FIXED_MILITARY_BUILDING ),
								ENTITY_ATTR_INT_VALUE ( INT_TYPE_OBJECT_3D_SHAPE, object_index ),
								ENTITY_ATTR_INT_VALUE ( INT_TYPE_SIDE, side ),
								ENTITY_ATTR_VEC3D ( VEC3D_TYPE_POSITION, position.x, position.y, position.z ),
								ENTITY_ATTR_FLOAT_VALUE ( FLOAT_TYPE_HEADING, heading ),
								ENTITY_ATTR_END
							);
			}
			else
			{

				#if DEBUG_MODULE

				debug_log ("POPREAD: WARNING: trying to create REGEN %s but keysite doesn't support that landing type", entity_sub_type_regen_names [regeneration_sub_type]);

				#endif
			}
		}
		else
		{

			if ( get_3d_object_updateable_flag ( object_index ) )
			{

				building = create_local_entity
								(
									ENTITY_TYPE_SITE_UPDATABLE,
									ENTITY_INDEX_DONT_CARE,
									ENTITY_ATTR_PARENT ( LIST_TYPE_MEMBER, keysite_group ),
									ENTITY_ATTR_INT_VALUE ( INT_TYPE_ENTITY_SUB_TYPE,ENTITY_SUB_TYPE_FIXED_MILITARY_BUILDING ),
									ENTITY_ATTR_INT_VALUE ( INT_TYPE_OBJECT_3D_SHAPE, object_index ),
									ENTITY_ATTR_INT_VALUE ( INT_TYPE_SIDE, side ),
									ENTITY_ATTR_VEC3D ( VEC3D_TYPE_POSITION, position.x, position.y, position.z ),
									ENTITY_ATTR_FLOAT_VALUE ( FLOAT_TYPE_HEADING, heading ),
									ENTITY_ATTR_END
								);
			}
			else
			{

				if (fixed_3d_object_database [object_index].importance > 0.0)
				{

					building = create_local_entity
									(
										ENTITY_TYPE_SITE,
										ENTITY_INDEX_DONT_CARE,
										ENTITY_ATTR_PARENT ( LIST_TYPE_MEMBER, keysite_group ),
										ENTITY_ATTR_INT_VALUE ( INT_TYPE_ENTITY_SUB_TYPE,ENTITY_SUB_TYPE_FIXED_MILITARY_BUILDING ),
										ENTITY_ATTR_INT_VALUE ( INT_TYPE_OBJECT_3D_SHAPE, object_index ),
										ENTITY_ATTR_INT_VALUE ( INT_TYPE_SIDE, side ),
										ENTITY_ATTR_VEC3D ( VEC3D_TYPE_POSITION, position.x, position.y, position.z ),
										ENTITY_ATTR_FLOAT_VALUE ( FLOAT_TYPE_HEADING, heading ),
										ENTITY_ATTR_END
									);
				}
				else
				{
					building = create_local_entity
									(
										ENTITY_TYPE_SCENIC,
										ENTITY_INDEX_DONT_CARE,
										ENTITY_ATTR_INT_VALUE ( INT_TYPE_ENTITY_SUB_TYPE, ENTITY_SUB_TYPE_FIXED_MILITARY_BUILDING ),
										ENTITY_ATTR_INT_VALUE ( INT_TYPE_OBJECT_3D_SHAPE, object_index ),
										ENTITY_ATTR_INT_VALUE ( INT_TYPE_SIDE, side ),
										ENTITY_ATTR_VEC3D ( VEC3D_TYPE_POSITION, position.x, position.y, position.z ),
										ENTITY_ATTR_FLOAT_VALUE ( FLOAT_TYPE_HEADING, heading ),
										ENTITY_ATTR_END
									);
				}
			}
		}

		/////////////////////////////////////////////////////////////////
		update_gunships_screen_progress_indicator ();
		/////////////////////////////////////////////////////////////////
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void insert_keysite_or_city_object ( entity *city, entity *keysite, entity *keysite_group, entity_sides keysite_side, int object_number, float world_x, float world_y, float world_z, float heading )
{


	if ( city )
	{

		create_local_entity
		(
			ENTITY_TYPE_CITY_BUILDING,
			ENTITY_INDEX_DONT_CARE,
			ENTITY_ATTR_PARENT ( LIST_TYPE_CITY_BUILDING, city ),
			ENTITY_ATTR_INT_VALUE ( INT_TYPE_ENTITY_SUB_TYPE, ENTITY_SUB_TYPE_FIXED_CITY_BUILDING ),
			ENTITY_ATTR_VEC3D ( VEC3D_TYPE_POSITION, world_x, world_y, world_z ),
			ENTITY_ATTR_INT_VALUE ( INT_TYPE_OBJECT_3D_SHAPE, object_number ),
			ENTITY_ATTR_FLOAT_VALUE ( FLOAT_TYPE_HEADING, heading ),
			ENTITY_ATTR_END
		);
	}
	else if ( keysite )
	{
		if ( get_3d_object_updateable_flag ( object_number ) )
		{

			create_local_entity
			(
				ENTITY_TYPE_SITE_UPDATABLE,
				ENTITY_INDEX_DONT_CARE,
				ENTITY_ATTR_PARENT ( LIST_TYPE_MEMBER, keysite_group ),
				ENTITY_ATTR_INT_VALUE ( INT_TYPE_ENTITY_SUB_TYPE,ENTITY_SUB_TYPE_FIXED_MILITARY_BUILDING ),
				ENTITY_ATTR_INT_VALUE ( INT_TYPE_OBJECT_3D_SHAPE, object_number ),
				ENTITY_ATTR_INT_VALUE ( INT_TYPE_SIDE, keysite_side ),
				ENTITY_ATTR_VEC3D ( VEC3D_TYPE_POSITION, world_x, world_y, world_z ),
				ENTITY_ATTR_FLOAT_VALUE ( FLOAT_TYPE_HEADING, heading ),
				ENTITY_ATTR_END
			);
		}
		else
		{

			if (fixed_3d_object_database [object_number].importance > 0.0)
			{

				create_local_entity
				(
					ENTITY_TYPE_SITE,
					ENTITY_INDEX_DONT_CARE,
					ENTITY_ATTR_PARENT ( LIST_TYPE_MEMBER, keysite_group ),
					ENTITY_ATTR_INT_VALUE ( INT_TYPE_ENTITY_SUB_TYPE,ENTITY_SUB_TYPE_FIXED_MILITARY_BUILDING ),
					ENTITY_ATTR_INT_VALUE ( INT_TYPE_OBJECT_3D_SHAPE, object_number ),
					ENTITY_ATTR_INT_VALUE ( INT_TYPE_SIDE, keysite_side ),
					ENTITY_ATTR_VEC3D ( VEC3D_TYPE_POSITION, world_x, world_y, world_z ),
					ENTITY_ATTR_FLOAT_VALUE ( FLOAT_TYPE_HEADING, heading ),
					ENTITY_ATTR_END
				);
			}
			else
			{
				create_local_entity
				(
					ENTITY_TYPE_SCENIC,
					ENTITY_INDEX_DONT_CARE,
					ENTITY_ATTR_INT_VALUE ( INT_TYPE_ENTITY_SUB_TYPE,ENTITY_SUB_TYPE_FIXED_MILITARY_BUILDING ),
					ENTITY_ATTR_INT_VALUE ( INT_TYPE_OBJECT_3D_SHAPE, object_number ),
					ENTITY_ATTR_INT_VALUE ( INT_TYPE_SIDE, keysite_side ),
					ENTITY_ATTR_VEC3D ( VEC3D_TYPE_POSITION, world_x, world_y, world_z ),
					ENTITY_ATTR_FLOAT_VALUE ( FLOAT_TYPE_HEADING, heading ),
					ENTITY_ATTR_END
				);
			}
		}
	}
	else
	{

		debug_fatal ( "No city or keysite to attach city buildings to" );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
unsigned char *get_keysite_name (float x, float z, entity_sides *side)
{

	float
		range,
		best_range;

	population_name_database_type
		*best_item,
		*item;

	entity
		*sector;

	int
		x_sec,
		z_sec;

	vec3d
		pos;

	best_item = NULL;

	item = population_name_database;

	best_range = MAX_MAP_X * MAX_MAP_Z * SECTOR_SIDE_LENGTH;

	while (item)
	{
		if (item->type == POPULATION_TYPE_KEYSITE)
		{
			pos.x = x - item->x;
			pos.y = 0;
			pos.z = z - item->z;
	
			range = get_3d_vector_magnitude (&pos);
	
			if ((range < best_range) && (range < (5.0 * KILOMETRE)))
			{
				best_range = range;
	
				best_item = item;
			}
		}
		
		item = item->next;
	}

	get_x_sector (x_sec, x);

	get_z_sector (z_sec, z);

	*side = get_initial_sector_side ( x_sec, z_sec );

	sector = get_local_raw_sector_entity (x_sec, z_sec);

	if (best_item)
	{

		#if DEBUG_MODULE

		debug_log ("AI_DBASE: closest city to %f, %f is (%s) at %f, %f (range %f) side %s", x, z, best_item->name, best_item->x, best_item->z, best_range, entity_side_names [*side]);

		#endif

		return best_item->name;
	}
	else
	{

		#if DEBUG_MODULE

		debug_log ("AI_DBASE: no match to closest city at %f, %f side %s", x, z, entity_side_names [*side]);
	
		#endif
	}

	return NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_object_3d_troop_landing_routes ( void )
{

	int
		count;

	if ( !object_3d_troop_routes )
	{

		object_3d_troop_routes = safe_malloc ( sizeof ( troop_landing_route_information ) * OBJECT_3D_LAST );

		for ( count = 0; count < OBJECT_3D_LAST; count++ )
		{

			object_3d_troop_routes[count].number_of_landing_route_nodes = 0;
			object_3d_troop_routes[count].landing_route = NULL;

			object_3d_troop_routes[count].number_of_takeoff_route_nodes = 0;
			object_3d_troop_routes[count].takeoff_route = NULL;

			object_3d_troop_routes[count].landing_position_valid = FALSE;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_object_3d_troop_landing_route ( int object_index, vec3d **route )
{

	object_3d_sub_object_search_data
		search;

	object_3d_instance
		*object;

	initialise_object_3d_troop_landing_routes ();

	if ( object_index == OBJECT_3D_INVALID_OBJECT_INDEX )
	{

		return ( NULL );
	}

	if ( !object_3d_troop_routes[object_index].landing_route )
	{
	
		object = construct_3d_object ( object_index );

		//
		// Construct the landing route
		//

		search.search_object = object;
		search.search_depth = 0;
		search.sub_object_index = OBJECT_3D_SUB_OBJECT_WAYPOINT_ROUTES;
	
		if ( find_object_3d_sub_object ( &search ) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND )
		{
	
			object_3d_database_entry
				*route;
	
			route = get_airfield_waypoint_route_object ( object, OBJECT_3D_SUB_OBJECT_TROOP_LANDING_ROUTE );
		
			if ( route )
			{
	
				int
					count;
	
				parse_waypoint_routes_from_object ( route->index, 0, NULL );
	
				object_3d_troop_routes[object_index].landing_route = safe_malloc ( sizeof ( vec3d ) * number_of_route_waypoint_positions );

				object_3d_troop_routes[object_index].number_of_landing_route_nodes = number_of_route_waypoint_positions;
	
				for ( count = 0; count < number_of_route_waypoint_positions; count++ )
				{
	
					object_3d_troop_routes[object_index].landing_route[count].x = route_waypoint_positions[count].position.x;
					object_3d_troop_routes[object_index].landing_route[count].y = route_waypoint_positions[count].position.y;
					object_3d_troop_routes[object_index].landing_route[count].z = route_waypoint_positions[count].position.z;
				}
			}
		}

		destruct_3d_object ( object );
	}

	*route = object_3d_troop_routes[object_index].landing_route;

	return ( object_3d_troop_routes[object_index].number_of_landing_route_nodes );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_object_3d_troop_takeoff_route ( int object_index, vec3d **route )
{

	object_3d_sub_object_search_data
		search;

	object_3d_instance
		*object;

	initialise_object_3d_troop_landing_routes ();

	if ( object_index == OBJECT_3D_INVALID_OBJECT_INDEX )
	{

		return ( NULL );
	}

	if ( !object_3d_troop_routes[object_index].takeoff_route )
	{
	
		object = construct_3d_object ( object_index );

		//
		// Construct the takeoff route
		//

		search.search_object = object;
		search.search_depth = 0;
		search.sub_object_index = OBJECT_3D_SUB_OBJECT_WAYPOINT_ROUTES;
	
		if ( find_object_3d_sub_object ( &search ) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND )
		{
	
			object_3d_database_entry
				*route;
	
			route = get_airfield_waypoint_route_object ( object, OBJECT_3D_SUB_OBJECT_TROOP_TAKEOFF_ROUTE );
		
			if ( route )
			{
	
				int
					count;
	
				parse_waypoint_routes_from_object ( route->index, 0, NULL );
	
				object_3d_troop_routes[object_index].takeoff_route = safe_malloc ( sizeof ( vec3d ) * number_of_route_waypoint_positions );

				object_3d_troop_routes[object_index].number_of_takeoff_route_nodes = number_of_route_waypoint_positions;
	
				for ( count = 0; count < number_of_route_waypoint_positions; count++ )
				{
	
					object_3d_troop_routes[object_index].takeoff_route[count].x = route_waypoint_positions[count].position.x;
					object_3d_troop_routes[object_index].takeoff_route[count].y = route_waypoint_positions[count].position.y;
					object_3d_troop_routes[object_index].takeoff_route[count].z = route_waypoint_positions[count].position.z;
				}
			}
		}

		destruct_3d_object ( object );
	}

	*route = object_3d_troop_routes[object_index].takeoff_route;

	return ( object_3d_troop_routes[object_index].number_of_takeoff_route_nodes );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_object_3d_troop_landing_position_and_heading ( int object_index, vec3d *position, float *heading )
{

	object_3d_sub_object_search_data
		search;

	object_3d_instance
		*object;

	int
		count;

	if ( !object_3d_troop_routes )
	{

		object_3d_troop_routes = safe_malloc ( sizeof ( troop_landing_route_information ) * OBJECT_3D_LAST );

		for ( count = 0; count < OBJECT_3D_LAST; count++ )
		{

			object_3d_troop_routes[count].landing_position_valid = FALSE;

			object_3d_troop_routes[count].number_of_landing_route_nodes = 0;
			object_3d_troop_routes[count].landing_route = NULL;

			object_3d_troop_routes[count].number_of_takeoff_route_nodes = 0;
			object_3d_troop_routes[count].takeoff_route = NULL;
		}
	}

	if ( object_index == OBJECT_3D_INVALID_OBJECT_INDEX )
	{

		position->x = 0;
		position->y = 0;
		position->z = 0;

		*heading = 0.0;

		return ( FALSE );
	}

	if ( !object_3d_troop_routes[object_index].landing_position_valid )
	{
	
		object_3d_troop_routes[object_index].landing_position.x = 0;
		object_3d_troop_routes[object_index].landing_position.y = 0;
		object_3d_troop_routes[object_index].landing_position.z = 0;
		object_3d_troop_routes[object_index].heading = 0;
		object_3d_troop_routes[object_index].landing_position_valid = TRUE;

		object = construct_3d_object ( object_index );

		//
		// Construct the landing route
		//

		search.search_object = object;
		search.search_depth = 0;
		search.sub_object_index = OBJECT_3D_SUB_OBJECT_WAYPOINT_ROUTES;
	
		if ( find_object_3d_sub_object ( &search ) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND )
		{
	
			object_3d_database_entry
				*troop_lz;
	
			troop_lz = get_airfield_waypoint_route_object ( object, OBJECT_3D_SUB_OBJECT_TROOP_LZ );
		
			if ( troop_lz )
			{

				object_3d_troop_routes[object_index].landing_position.x = troop_lz->keyframes[0].x;
				object_3d_troop_routes[object_index].landing_position.y = troop_lz->keyframes[0].y;
				object_3d_troop_routes[object_index].landing_position.z = troop_lz->keyframes[0].z;
				object_3d_troop_routes[object_index].heading = troop_lz->keyframes[0].heading;
			}
		}

		destruct_3d_object ( object );
	}

	position->x = object_3d_troop_routes[object_index].landing_position.x;
	position->y = object_3d_troop_routes[object_index].landing_position.y;
	position->z = object_3d_troop_routes[object_index].landing_position.z;

	*heading =  ( object_3d_troop_routes[object_index].heading );

	return ( TRUE );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

