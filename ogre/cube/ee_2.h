#define _TERRAIN_INCLUDED_

#define ASSERT assert

using std::min;
#define bound(VALUE,LOWER,UPPER) ( ( VALUE ) < ( LOWER ) ? ( LOWER ) : ( ( VALUE ) > ( UPPER ) ? ( UPPER ) : ( VALUE ) ) )
enum SESSION_SEASON_SETTINGS
{

	SESSION_SEASON_INVALID,
	SESSION_SEASON_DEFAULT,
	SESSION_SEASON_SUMMER,
	SESSION_SEASON_WINTER,
	SESSION_SEASON_DESERT,
};

typedef enum SESSION_SEASON_SETTINGS session_season_settings;

#define get_global_season() 0
int file_exist (const char *filename)
{
	FILE
		*file_ptr;

	if (file_ptr = fopen (filename, "r"))
	{

		fclose (file_ptr);

		return TRUE;
	}

	return FALSE;
}
#define safe_malloc malloc
#define safe_free free
#define get_list_item(PTR,TYPE) ((PTR) += sizeof (TYPE), *(TYPE *) ((PTR) - sizeof (TYPE)))
#define DEBUG_COLOUR_DARK_RED 0
#define DEBUG_COLOUR_RED 0
#define DEBUG_COLOUR_BLUE 0
#define DEBUG_MT_INT 0
#define MT_INT 0
static void debug_log(...)
{
}
static void debug_fatal(...)
{
	assert(0);
}
#define debug_colour_log debug_log
#define debug_colour_watch debug_log
#define command_line_texture_colour 0
#define command_line_cloud_puffs 0
#define cloud_puffs_colours ((real_colour*)NULL)
#define number_of_cloud_puffs_colours 1
#define command_line_render_shadows 2
#define command_line_render_tree_shadows 1
#define command_line_trees_fog 1
#define global_anisotropic 0
#define d3d_modulate_alpha 0
#define d3d_using_hardware_tnl 0
#define global_dynamic_water 0
#define set_3d_rain_special_snow_flag(x)
#define set_object_3d_texture_camoflage_by_name(x)
#define set_object_3d_reflection_texture_map(x)
#define add_new_texture(x, y) -1
static struct
{
	int gouraud_shading;
	int user_defined_contour_heights;
	float* contour_heights;
	int texture_override_scales[64][2];
	int dry_river;
	struct
	{
		int delay, scale_bottom, scale_top, placenr, number;
	} water_info[3];
} current_map_info;
env_3d act_env, *active_3d_environment = ((act_env.render_filter = RENDER_CLEAR), &act_env);
#ifndef USE_TERRAIN_CURRENT
#define infrared_mode render_filter + 1
#endif
#define INFRARED_ON 1
#define ARRAY_LENGTH(array) (sizeof(array) / sizeof(array[0]))
#define construct_3d_object_by_name(x) NULL
#define destruct_3d_object(x)
#define d3d_fog_start 0
#define d3d_fog_end 0
#define D3DTFG_LINEAR 0
#define D3DTFN_LINEAR 0
#define D3DTFP_LINEAR 0
#define D3DTFP_POINT 0
#define D3DTEXF_LINEAR 0
#define D3DTEXF_POINT 0
#define iff_int_write(x, y)
#define iff_float_write(x, y)
#define iff_short_int_write(x, y)
#define set_fpu_rounding_mode_zero()
#define convert_float_to_int(x, y) *(y) = (int)(x)
#define asm_convert_float_to_int convert_float_to_int
static struct SCREEN* system_textures[4096];
static void fill_system_textures(void)
{
	for (int i = 0; i < sizeof(system_textures) / sizeof(*system_textures); i++)
		system_textures[i] = (struct SCREEN*)i;
}
static int init_system_textures = (fill_system_textures(), 1);

float normalise_3d_vector ( vec3d *vector )
{

	float
		x,
		y,
		z,
		length,
		one_over_length;

	ASSERT ( vector );

	x = ( ( vector->x ) * ( vector->x ) );
	y = ( ( vector->y ) * ( vector->y ) );
	z = ( ( vector->z ) * ( vector->z ) );

	length = sqrt ( x + y + z );

	ASSERT ( length > 0.0 );

	one_over_length = 1.0f / length;

	vector->x = ( vector->x * one_over_length );
	vector->y = ( vector->y * one_over_length );
	vector->z = ( vector->z * one_over_length );

	return ( length );
}

float normalise_any_3d_vector ( vec3d *vector )
{

	float
		x,
		y,
		z,
		length;

	ASSERT ( vector );

	x = ( ( vector->x ) * ( vector->x ) );
	y = ( ( vector->y ) * ( vector->y ) );
	z = ( ( vector->z ) * ( vector->z ) );

	length = sqrt ( x + y + z );

	if ( length > 0 )
	{

		float
			one_over_length;

		one_over_length = 1.0f / length;

		vector->x = ( vector->x * one_over_length );
		vector->y = ( vector->y * one_over_length );
		vector->z = ( vector->z * one_over_length );
	}
	else
	{

		vector->x = 0;
		vector->y = 0;
		vector->z = 0;
	}

	return ( length );
}



#define MAX_NUMBER_FILES 1024

struct FILEMAP
{

	int
		used;

	char
		filename[256];

#ifdef WIN32
	HANDLE
		hFile,
		hMap;
#else
	int
		fd;

	long
		length;
#endif

	void
		*data;
};

typedef struct FILEMAP filemap;

static filemap
	*file_maps;

BOOL initialise_file_system ( void )
{

	int
		count;

	file_maps = (filemap *) safe_malloc ( sizeof ( filemap ) * MAX_NUMBER_FILES );

	for ( count = 0; count < MAX_NUMBER_FILES; count++ )
	{

		file_maps[count].used = FALSE;
#ifdef WIN32
		file_maps[count].hFile = 0;
		file_maps[count].hMap = 0;
#else
		file_maps[count].fd = 0;
		file_maps[count].length = 0;
#endif
		file_maps[count].data = NULL;
	}

	//register_exit_function ( deinitialise_file_system );

	return ( TRUE );
}

static int initialise_file_system_ = initialise_file_system();

typedef struct FILEMAP filemap;

void * mopen ( const char *filename )
{
#ifdef WIN32
	HANDLE
		hFile,
		hMap;
#else
	int
		fd;

	long
		length;

	struct stat filestat;
#endif
	
	void
		*data;

	int
		count;

	for ( count=0; ( ( count<MAX_NUMBER_FILES ) && ( file_maps[count].used ) ); count++ )
	{
	}

	if ( count == MAX_NUMBER_FILES )
	{

		debug_log ( "Unable to create a file mapping - maximum files already mapped" );

		return ( NULL );
	}
	else
	{

#ifdef WIN32
		hFile = CreateFile ( filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );

		if ( hFile == INVALID_HANDLE_VALUE )
		{

			debug_log ( "Unable to memory map file %s", filename );

			return ( NULL );
		}
#else
		fd = open ( filename, O_RDONLY );

		if ( !fd )
		{
			debug_log ( "Unable to open file %s prior to mmap: %s", filename, strerror(errno) );

			return ( NULL );
		}
#endif

#ifdef WIN32
		hMap = CreateFileMapping ( hFile, NULL, PAGE_READONLY, 0, 0, NULL );

		if ( ! hMap )
		{

			CloseHandle ( hFile );

			debug_log ( "Unable to create memory mapped file %s", filename );

			return ( NULL );
		}

		data = MapViewOfFile ( hMap, FILE_MAP_READ, 0, 0, 0 );
#else
		// set length to size of file
		fstat( fd, &filestat );
		length = filestat.st_size;

		data = mmap(0, length, PROT_READ, MAP_SHARED, fd, 0);
#endif
		if ( ! data )
		{

#ifdef WIN32
			CloseHandle ( hMap );

			CloseHandle ( hFile );

			debug_log ( "Unable to create file mapping for memory mapped file %s", filename );
#else
			close(fd);

			debug_log ( "Unable to create file mapping for memory mapped file %s: %s", filename, strerror(errno) );
#endif

			return ( NULL );
		}

#ifdef WIN32
		file_maps[count].hFile = hFile;
		file_maps[count].hMap = hMap;
#else
		file_maps[count].fd = fd;
		file_maps[count].length = length;
#endif
		file_maps[count].data = data;

		strcpy ( file_maps[count].filename, filename );

		file_maps[count].used = TRUE;

		return ( data );
	}
}

BOOL mclose ( void *data )
{

	int
		count;

	for ( count=0; ( ( count<MAX_NUMBER_FILES ) && ( file_maps[count].data != data ) ); count++ )
	{
	}

	if ( count == MAX_NUMBER_FILES )
	{

		debug_log ( "Unable to locate memory mapped file to unmap file." );

		return ( FALSE );
	}

#ifdef WIN32
	UnmapViewOfFile ( file_maps[count].data );

	CloseHandle ( file_maps[count].hMap );

	CloseHandle ( file_maps[count].hFile );
#else
	munmap( file_maps[count].data, file_maps[count].length );

	close( file_maps[count].fd );
#endif


	file_maps[count].used = FALSE;
#ifdef WIN32
	file_maps[count].hFile = 0;
	file_maps[count].hMap = 0;
#else
	file_maps[count].fd = 0;
	file_maps[count].length = 0;
#endif
	file_maps[count].data = NULL;

	return ( TRUE );
}

void *safe_mopen (const char *filename)
{
	void
		*ptr;

	ASSERT (filename);

	ptr = mopen (filename);

	ASSERT (ptr);

	return ptr;
}

BOOL safe_mclose (void *data)
{
	BOOL
		result;

	ASSERT (data);

	result = mclose (data);

	ASSERT (result);

	return (result);
}

void deinitialise_file_system ( void )
{

	int
		count;

	for ( count = 0; count < MAX_NUMBER_FILES; count++ )
	{

		if ( file_maps[count].used )
		{

			error ( "Memory mapped file %s not closed", file_maps[count].filename );
			mclose ( file_maps[count].data );
		}
	}

	safe_free ( file_maps );
}




#define get_3d_transformation_matrix(m, heading, pitch, roll)

int get_system_texture_index(const char* name);

void set_2d_terrain_contour_heights ( int number_of_heights, float *heights )
{
}
float check_coastal_river_intersection ( float x1, float z1, float x2, float z2 )
{
	return 0;
}

light_3d_source
	ambient_3d_light,
	*current_3d_lights;

const float
	float_value_zero = 0.0,
	float_value_one = 1.0,
	float_value_255 = 255.0;

viewpoint
	*visual_3d_vp;

float
	clip_hither_reciprocal,
	clip_hither,
	clip_yonder_reciprocal,
	clip_yonder;

#define get_3d_point_outcodes(x, y, z) 0


typedef int object_3d_index_numbers;

#include "../3dobjbuf.h"

#include "../../graphics/viewport.h"

#include "../3dobjvis.h"

#define set_object_3d_instance_relative_position(obj)
#define get_object_3d_instance_visibility(obj) OBJECT_3D_VISIBITY_ILLEGAL
#define insert_low_nonzbuffered_scene_slot_into_3d_scene(x)
#define insert_low_zbuffered_scene_slot_into_3d_scene(x)

#define shadows_enabled 0

#define draw_3d_object_shadow(obj)
#define copy_and_recolour_current_3d_lights(colour)
#define restore_uncoloured_current_3d_lights()

#define get_3d_scene_slot() 0

#define set_fpu_precision_mode_single()
#define set_fpu_precision_mode_double()

#define get_int_fog_distance_value(z) 255
void get_3d_fog_distances ( ENV_3D *, float *, float *dist)
{
	*dist = 10000;
}

#define set_d3d_int_state(x, y)
#define set_d3d_texture_stage_state(x, y, z)
#define set_d3d_sampler_state(x, y, z)
#define set_deferred_d3d_texture(x, y)
#define commit_deferred_state_changes()
#define set_d3d_texture(x, y)

#define reset_terrain_3d_buffered_polygons()
#define reset_deferred_state_changes()
#define draw_terrain_3d_buffered_polygons()
#define draw_wbuffered_3d_object(obj, object_is_flat, infrared_override)

#define outcode_3d_terrain_byte_polygon(num_points, reference_points, polygon_outcode) 0
#define outcode_3d_terrain_word_polygon(num_points, reference_points, polygon_outcode) 0

double
	zbuffer_factor,
	zbuffer_constant,
	zbuffer_constant_elevated_bias,
	zbuffer_constant_normal_bias,
	zbuffer_constant_lowered_bias,
	zbuffer_constant_lowered_bias2,
	zbuffer_constant_shadow_bias,
	zbuffer_constant_shadow_bias_decrement;

viewport
	active_viewport;

typedef	struct SCENE_SLOT_DRAWING_LIST scene_slot_drawing_list;

struct VERTEX
{

	//
	// 3D world coordinates ( q = 1/z )
	//

	float
		x,
		y,
		z,
		q;

	//
	// 2D screen coordinates
	//

	float
		i,
		j;

	//
	// Texture coordinates
	//

	float
		u,
		v,
		u2,
		v2;

	//
	// Linked list management ( next pointer )
	//

	struct VERTEX
		*next_vertex;

	unsigned char
		outcode,
		specular,
		fog;

	union
	{

		unsigned char
			userdata,
			userdata1,
			userdata2,
			normal_index;
	};

	//
	// The following union makes copying between a D3DCOLOR structure a simple memory move.
	//

	union
	{
	
		struct
		{
		
			unsigned char
				blue,
				green,
				red,
				alpha;
		};

		unsigned int
			colour;
	};

	union
	{
	
		struct
		{
		
			unsigned char
				blue2,
				green2,
				red2,
				alpha2;
		};

		unsigned int
			colour2;
	};

	//
	// Finally, 2 DWORDS to pad the structure to 64 bytes.
	//

	int
		padding_dword_1,
		padding_dword_2;
};

typedef	struct VERTEX vertex;

#include "terrelev.h"
#include "terrobjs.h"
#include "terrsel.h"
#include "terrgeom.h"
#include "../3dtrans.h"
#include "terrmap.h"

object_transformed_3d_point
	transformed_3d_3d_points[1];

object_transformed_2d_point
	transformed_3d_2d_points[1];

unsigned char
	transformed_3d_point_outcodes[1],
	transformed_3d_points_needed[1];
