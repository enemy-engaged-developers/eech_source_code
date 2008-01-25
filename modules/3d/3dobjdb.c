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

#include	"3d.h"
#include "global.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define REPORT_OBJECT_STATS 1

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float
	object_approximation_distance_bias = 0.0;

static int
	initialised_3d_objects = FALSE;

int
	current_number_of_3d_objects_constructed,
	current_amount_of_3d_objects_memory;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct OBJECT_3D_SCENE_DATABASE_ENTRY
	*objects_3d_scene_database;

struct OBJECT_3D_SCENE_CAMERA
	*objects_3d_camera_database;

struct OBJECT_3D_SCENE_LINK_OBJECT
	*objects_3d_scene_link_array,
	*objects_3d_scene_link_ptr;

struct OBJECT_3D_SPRITE_LIGHT
	*objects_3d_scene_sprite_light_array,
	*objects_3d_scene_sprite_light_ptr;

struct OBJECT_3D_SUB_OBJECT_KEYFRAME
	*objects_3d_camera_keyframes;

struct OBJECT_3D_SCENE_CAMERA_INFO
	*objects_3d_camera_info_array,
	*objects_3d_camera_info_array_ptr;

struct OBJECT_3D_DATABASE_ENTRY
	*objects_3d_scene_sub_objects_array,
	*objects_3d_scene_sub_objects_array_ptr;

struct OBJECT_3D_SUB_OBJECT_INDEX
	*objects_3d_scene_sub_object_indices_array,
	*objects_3d_scene_sub_object_indices_array_ptr;

struct OBJECT_3D_APPROXIMATION_INFO
	*objects_3d_scene_approximations_array,
	*objects_3d_scene_approximations_array_ptr;

int
	*objects_3d_scene_texture_animations_array,
	*objects_3d_scene_texture_animations_array_ptr;

struct OBJECT_3D_SUB_OBJECT_KEYFRAME
	*objects_3d_scene_sub_object_keyframes_array,
	*objects_3d_scene_sub_object_keyframes_array_ptr;

struct OBJECT_3D_SUB_OBJECT_VALUE_KEYFRAME
	*objects_3d_scene_sub_object_dissolve_keyframes_array,
	*objects_3d_scene_sub_object_dissolve_keyframes_array_ptr;

int
	object_3d_scenes_creation_count[OBJECT_3D_LAST];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int
	total_number_of_cameras,
	total_number_of_scene_link_objects,
	total_number_of_sprite_light_objects,
	total_number_of_camera_keyframes,
	total_number_of_scene_camera_indices,
	total_number_of_scene_sub_objects,
	total_number_of_scene_sub_object_indices,
	total_number_of_scene_texture_animations,
	total_number_of_scene_approximations,
	total_number_of_scene_sub_object_keyframes,
	total_number_of_scene_sub_object_dissolve_keyframes;

static unsigned
	next_free_custom_object,
	total_objects;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct OBJECT_3D
	*objects_3d_data;

int
	total_number_of_raw_3d_objects;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static object_3d_sub_object_index
	*current_scene_sub_object_index_array;

static object_3d_database_entry
	*current_scene_sub_object_array;

//
// Arrays for the objects
//

struct FACE_SURFACE_DESCRIPTION
	*object_database_surfaces;

static struct OBJECT_SHORT_3D_POINT
	*object_database_points;

static struct OBJECT_3D_FACE
	*object_database_faces;

static struct OBJECT_3D_HEADING_PITCH_NORMAL
	*object_database_point_normals;

static struct POINT_3D_SHORT_REFERENCE
	*object_database_faces_point_list;

static struct POINT_3D_PLAIN_REFERENCE
	*object_database_faces_gouraud_list,
	*object_database_faces_face_normal_list,
	*object_database_surface_point_list,
	*object_database_surface_point_normal_list;

static struct OBJECT_3D_SHORT_TEXTURED_POINT
	*object_database_faces_texture_list,
	*object_database_surface_point_texture_list;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void initialise_3d_sub_object ( FILE *fp, struct OBJECT_3D_DATABASE_ENTRY *parent, struct OBJECT_3D_DATABASE_ENTRY *sub_object );

static void construct_3d_sub_objects ( object_3d_sub_instance *parent, object_3d_sub_instance *sub_objects, struct OBJECT_3D_DATABASE_ENTRY *source_objects, int number_of_sub_objects );

static void count_sub_object_statistics ( object_3d_database_entry *sub_object, int approximation, int *triangles, int *points, int *objects );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** Gets the first nul terminated string from file and puts it in buf.
 *  Makes sure not to exceed the buf_len, and will NUL-terminate where if the string is truncated
 *  If uppercase is TRUE it will switch all characters in the string to uppercase (useful 
 *  for case insensitive filenames)
 */
static int get_nul_string(char* buf, unsigned buf_len, FILE* file, int uppercase)
{
	int chr;
	unsigned dest = 0;

	while (chr = fgetc(file))
	{
		if (chr == EOF)
			return FALSE;

		if (uppercase)
			chr = toupper(chr);

		buf[dest] = chr;
		dest++;

		if (dest >= buf_len)
		{
			buf[buf_len-1] = '\0';
			return TRUE;
		}
	}

	buf[dest] = '\0';
	return TRUE;
}

#ifdef DEBUG_MODULE
static void debug_object(const char* filename, int objid)
{
	int count;
	struct OBJECT_3D *obj = &objects_3d_data[objid];
	FILE* debug = fopen(filename, "w");

	if (debug)
	{
		unsigned i;
		struct POINT_3D_SHORT_REFERENCE* points = obj->object_faces_point_plain_list;
		struct POINT_3D_PLAIN_REFERENCE* surface_points = obj->surface_points;
		struct OBJECT_3D_SHORT_TEXTURED_POINT* texture_points = obj->surface_texture_points;

		fprintf(debug, "points: %d: \n", obj->number_of_points);
		fprintf(debug, "normals: %d: \n", obj->number_of_point_normals);
		fprintf(debug, "lighting normals: %d: \n", obj->number_of_lighting_normals);
		fprintf(debug, "faces: %d: \n", obj->number_of_faces);
		fprintf(debug, "surfaces: %d: \n", obj->number_of_surfaces);
		fprintf(debug, "bounding box: x: %.2f %.2f;  y: %.2f, %.2f;  z: %.2f, %.2f\n", 
			obj->bounding_box.xmin,
			obj->bounding_box.xmax,
			obj->bounding_box.ymin,
			obj->bounding_box.ymax,
			obj->bounding_box.zmin,
			obj->bounding_box.zmax);
		fprintf(debug, "bounding box2: x: %.2f %.2f;  y: %.2f, %.2f;  z: %.2f, %.2f\n", 
			obj->bounding_box2.xmin,
			obj->bounding_box2.xmax,
			obj->bounding_box2.ymin,
			obj->bounding_box2.ymax,
			obj->bounding_box2.zmin,
			obj->bounding_box2.zmax);

		for (i=0; i < obj->number_of_points; i++)
		{
			fprintf(debug, "point: (%d, %d, %d)\n", obj->points[i].x, obj->points[i].y, obj->points[i].z);
//				fprintf(debug, "point idx: %d\n", obj->points[i].point);
		}

		for (i=0; i < obj->number_of_faces; i++)
		{
			unsigned j;
			int nfaces = obj->faces[i].number_of_points;
			int pref = obj->object_face_normal_references[i].point;

			ASSERT(pref < obj->number_of_point_normals + obj->number_of_points);

			fprintf(debug, "%d: ", nfaces);
			for (j=0; j < nfaces; j++)
			{
				fprintf(debug, "%d ", points->point);
/*					fprintf(debug, "%d (%d, %d, %d), ", points->point,
//					fprintf(debug, "(%d, %d, %d), ", 
						obj->points[points->point].x,
						obj->points[points->point].y,
						obj->points[points->point].z
						);
*/
				points++;
			}
//				fprintf(debug, ";  normal: %d - (%d, %d)\n", pref,
			fprintf(debug, "(%d, %d)", 
				obj->point_normals[pref].heading,
				obj->point_normals[pref].pitch
				);
/*				fprintf(debug, ";  normal: %d - (%d, %d, %d)\n", pref,
					obj->points[pref].x,
					obj->points[pref].y,
					obj->points[pref].z
					);*/
			fprintf(debug, "\n");
		}
		
		{
			int poly_index = 0;
			points = obj->object_faces_point_plain_list;
			for (i=0; i < obj->number_of_surfaces; i++)
			{
				face_surface_description* surf = &obj->surfaces[i];
				int npoints = surf->number_of_points;
				if (npoints == 0)
					npoints = 256;

				fprintf(debug, "number of faces: %d\n  ", surf->number_of_faces);
				fprintf(debug, "number of points: %d\n  ", npoints);
				
//					surf->surface_flags = 0;
//					surf->polygons = 1;
				
				fprintf(debug, "pols: %d,  detail: %d,  smoothed: %d,  textured: %d  lumi tex: %d  additive: %d  trans: %d  lumi: %d  spec: %d\n,",
					surf->polygons,
					surf->detail,
					surf->smoothed,
					surf->textured,
					surf->has_luminosity_texture,
					surf->additive,
					surf->translucent,
					surf->luminous,
					surf->has_specularity
					);
				fprintf(debug, "flags: %08x, %8x, %d, %d, %d\n", 
					surf->surface_flags,
					surf->colour,
					surf->texture_index,
					surf->reflectivity,
					surf->specularity);

				for (count = 0; count < surf->number_of_faces; count++)
				{
					int nvertices = obj->faces[poly_index].number_of_points;
					
					while (nvertices--)
					{
						int
							surface_point_index;
					
						surface_point_index = points->point;
						fprintf(debug, "  idx: %d -> %d; ", surface_point_index, surface_points[surface_point_index]);
						if (surf->textured)
							fprintf(debug, "  u: %.2f, v: %.2f;  ", texture_points[surface_point_index].u, texture_points[surface_point_index].v);
						fprintf(debug, "\n");
						
						points++;	
					}

					{
						int pref = obj->object_face_normal_references[poly_index].point;
//						int pref = obj->object_face_normal_references[surface_point_index].point;
						fprintf(debug, "%d, normal: [%d,%d]", pref, obj->point_normals[pref].heading, obj->point_normals[pref].pitch);
						fprintf(debug, "\n");
					}						

					poly_index++;
				}

				surface_points += npoints;
				if (surf->textured)
					texture_points += npoints;
				fprintf(debug, "\n");
			}
		}
		
		fclose(debug);
	}
}
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void read_scene(FILE* fp)
{
	int
		tmp,
		keyframe_count,
		scene_index,
		number_of_texture_animations,
		approximation,
		number_of_approximations,
		number_of_scene_sub_objects,
		number_of_scene_lights,
		number_of_scene_cameras,
		number_of_scene_links,
		number_of_sprite_lights,
		number_of_scene_named_sub_objects;

	number_of_scene_lights = 0;

	for ( tmp = 0; tmp < 16; tmp++ )
	{

		int
			temp;

		fread ( &temp, sizeof ( int ), 1, fp );

		if ( temp != -1 )
		{

			debug_fatal ( "3d objects scene definitions file is corrupted" );
		}
	}

	fread ( &scene_index, sizeof ( int ), 1, fp );

	if ( ( scene_index <= OBJECT_3D_INVALID_OBJECT_INDEX ) || ( scene_index >= OBJECT_3D_LAST ) )
	{
		debug_fatal ( "Scene index is out of range: %d ( %d to %d allowed )", scene_index, OBJECT_3D_INVALID_OBJECT_INDEX, OBJECT_3D_LAST );
	}

	fread ( &objects_3d_scene_database[scene_index].self_shadows, sizeof ( int ), 1, fp );

	//
	// Set the approximation scale to 1.0
	//

	objects_3d_scene_database[scene_index].object_approximation_scale = 1.0;

	//
	// Read in the number of lights
	//

	fread ( &number_of_scene_lights, sizeof ( int ), 1, fp );

	for ( tmp = 0; tmp < number_of_scene_lights; tmp++ )
	{

		rgb_colour
			light_colour;

		float
			light_intensity,
			heading,
			pitch,
			roll,
			x,
			y,
			z;

		int
			light_type;

		fread ( &light_colour, sizeof ( rgb_colour ), 1, fp );
		fread ( &light_intensity, sizeof ( float ), 1, fp );
		fread ( &light_type, sizeof ( int ), 1, fp );
		fread ( &x, sizeof ( float ), 1, fp );
		fread ( &y, sizeof ( float ), 1, fp );
		fread ( &z, sizeof ( float ), 1, fp );
		fread ( &heading, sizeof ( float ), 1, fp );
		fread ( &pitch, sizeof ( float ), 1, fp );
		fread ( &roll, sizeof ( float ), 1, fp );
	}

	//
	// Read in the number of camera
	//

	fread ( &number_of_scene_cameras, sizeof ( int ), 1, fp );

	objects_3d_scene_database[scene_index].number_of_cameras = number_of_scene_cameras;

	if ( number_of_scene_cameras )
	{

		int
			camera_count;

		objects_3d_scene_database[scene_index].cameras = objects_3d_camera_info_array_ptr;

		objects_3d_camera_info_array_ptr += number_of_scene_cameras;

		ASSERT ( objects_3d_scene_database[scene_index].cameras );

		for ( camera_count = 0; camera_count < number_of_scene_cameras; camera_count++ )
		{

			fread ( &objects_3d_scene_database[scene_index].cameras[camera_count].camera_name_index, sizeof ( int ), 1, fp );

			fread ( &objects_3d_scene_database[scene_index].cameras[camera_count].camera_index, sizeof ( int ), 1, fp );
		}
	}
	else
	{

		objects_3d_scene_database[scene_index].cameras = NULL;
	}

	//
	// Read in the number of scene links
	//

	fread ( &number_of_scene_links, sizeof ( int ), 1, fp );

	objects_3d_scene_database[scene_index].number_of_scene_link_objects = number_of_scene_links;

	objects_3d_scene_database[scene_index].scene_link_objects = NULL;

	if ( number_of_scene_links )
	{

		objects_3d_scene_database[scene_index].scene_link_objects = objects_3d_scene_link_ptr;
	}

	for ( tmp = 0; tmp < number_of_scene_links; tmp++ )
	{

		fread ( &objects_3d_scene_link_ptr->scene_index, sizeof ( int ), 1, fp );
		fread ( &objects_3d_scene_link_ptr->x, sizeof ( float ), 1, fp );
		fread ( &objects_3d_scene_link_ptr->y, sizeof ( float ), 1, fp );
		fread ( &objects_3d_scene_link_ptr->z, sizeof ( float ), 1, fp );
		fread ( &objects_3d_scene_link_ptr->heading, sizeof ( float ), 1, fp );
		fread ( &objects_3d_scene_link_ptr->pitch, sizeof ( float ), 1, fp );
		fread ( &objects_3d_scene_link_ptr->roll, sizeof ( float ), 1, fp );

		objects_3d_scene_link_ptr++;
	}

	//
	// Read in the sprite lights
	//

	fread ( &number_of_sprite_lights, sizeof ( int ), 1, fp );

	objects_3d_scene_database[scene_index].number_of_sprite_lights = number_of_sprite_lights;

	objects_3d_scene_database[scene_index].sprite_lights = NULL;

	if ( number_of_sprite_lights )
	{

		objects_3d_scene_database[scene_index].sprite_lights = objects_3d_scene_sprite_light_ptr;
	}

	for ( tmp = 0; tmp < number_of_sprite_lights; tmp++ )
	{

		int
			red,
			green,
			blue;

		fread ( &objects_3d_scene_sprite_light_ptr->position.x, sizeof ( float ), 1, fp );
		fread ( &objects_3d_scene_sprite_light_ptr->position.y, sizeof ( float ), 1, fp );
		fread ( &objects_3d_scene_sprite_light_ptr->position.z, sizeof ( float ), 1, fp );
		fread ( &objects_3d_scene_sprite_light_ptr->scale.x, sizeof ( float ), 1, fp );
		fread ( &objects_3d_scene_sprite_light_ptr->scale.y, sizeof ( float ), 1, fp );
		fread ( &objects_3d_scene_sprite_light_ptr->scale.z, sizeof ( float ), 1, fp );

		fread ( &red, sizeof ( int ), 1, fp );
		fread ( &green, sizeof ( int ), 1, fp );
		fread ( &blue, sizeof ( int ), 1, fp );

		objects_3d_scene_sprite_light_ptr->colour.red = red;
		objects_3d_scene_sprite_light_ptr->colour.green = green;
		objects_3d_scene_sprite_light_ptr->colour.blue = blue;

		objects_3d_scene_sprite_light_ptr++;
	}

	//
	// Read in the number of sub objects, and the number of *named* sub objects
	//

	fread ( &number_of_scene_sub_objects, sizeof ( int ), 1, fp );

	fread ( &number_of_scene_named_sub_objects, sizeof ( int ), 1, fp );

	if (scene_index == OBJECT_3D_APACHE_VIRTUAL_COCKPIT_LEVEL1)
	{
		number_of_scene_sub_objects++;	
	}

	//
	// Allocate the memory for all sub objects
	//

	current_scene_sub_object_array = NULL;

	current_scene_sub_object_index_array = NULL;

	if ( number_of_scene_named_sub_objects )
	{
		current_scene_sub_object_index_array = safe_malloc(sizeof ( struct OBJECT_3D_SUB_OBJECT_INDEX ) * number_of_scene_named_sub_objects);
//		current_scene_sub_object_index_array = objects_3d_scene_sub_object_indices_array_ptr;
//		objects_3d_scene_sub_object_indices_array_ptr += number_of_scene_named_sub_objects;
	}

	if ( number_of_scene_sub_objects )
	{
		current_scene_sub_object_array = safe_malloc(sizeof(object_3d_database_entry) * number_of_scene_sub_objects);
//		current_scene_sub_object_array = objects_3d_scene_sub_objects_array_ptr;
//		objects_3d_scene_sub_objects_array_ptr += number_of_scene_sub_objects;
	}


	objects_3d_scene_database[scene_index].total_number_of_sub_objects = number_of_scene_sub_objects;
	objects_3d_scene_database[scene_index].total_number_of_sub_object_indices = number_of_scene_named_sub_objects;

	objects_3d_scene_database[scene_index].scene_sub_object_indices_array = current_scene_sub_object_index_array;
	objects_3d_scene_database[scene_index].scene_sub_object_array = current_scene_sub_object_array;


	fread ( &number_of_texture_animations, sizeof ( int ), 1, fp );

	objects_3d_scene_database[scene_index].number_of_texture_animations = number_of_texture_animations;

	if ( number_of_texture_animations )
	{

		objects_3d_scene_database[scene_index].texture_animations = objects_3d_scene_texture_animations_array_ptr;

		objects_3d_scene_texture_animations_array_ptr += number_of_texture_animations;

		ASSERT ( objects_3d_scene_database[scene_index].texture_animations );

		for ( tmp =0; tmp < number_of_texture_animations; tmp++ )
		{

			fread ( &objects_3d_scene_database[scene_index].texture_animations[tmp], sizeof ( int ), 1, fp );
		}
	}

	fread ( &number_of_approximations, sizeof ( int ), 1, fp );

	fread ( &objects_3d_scene_database[scene_index].index, sizeof ( int ), 1, fp );

	ASSERT ( objects_3d_scene_database[scene_index].index >= 0 );
	ASSERT ( objects_3d_scene_database[scene_index].index <= total_number_of_raw_3d_objects );

	objects_3d_scene_database[scene_index].number_of_approximations = number_of_approximations;

	if ( number_of_approximations )
	{

		ASSERT ( ( objects_3d_scene_approximations_array_ptr - objects_3d_scene_approximations_array ) < total_number_of_scene_approximations );

		objects_3d_scene_database[scene_index].approximations = objects_3d_scene_approximations_array_ptr;

		objects_3d_scene_approximations_array_ptr += number_of_approximations;

		ASSERT ( ( objects_3d_scene_approximations_array_ptr - objects_3d_scene_approximations_array ) <= total_number_of_scene_approximations );

		ASSERT ( objects_3d_scene_database[scene_index].approximations );

		//
		// Read any approximation information in
		//

		for ( approximation = 0; approximation < number_of_approximations; approximation++ )
		{

			fread ( &objects_3d_scene_database[scene_index].approximations[approximation].object_number, sizeof ( int ), 1, fp );

			fread ( &objects_3d_scene_database[scene_index].approximations[approximation].distance, sizeof ( float ), 1, fp );

			//
			// Approximation distance adjustment
			//

			objects_3d_scene_database[scene_index].approximations[approximation].distance /= 1;
		}
	}

	//
	// Read in the shadow approximation index
	//

	fread ( &objects_3d_scene_database[scene_index].shadow_approximation_index, sizeof ( int ), 1, fp );

	//
	// Read in the shadow polygon object index
	//

	fread ( &objects_3d_scene_database[scene_index].shadow_polygon_object_index, sizeof ( int ), 1, fp );
	fread ( &objects_3d_scene_database[scene_index].shadow_polygon_object_scale.x, sizeof ( float ), 1, fp );
	fread ( &objects_3d_scene_database[scene_index].shadow_polygon_object_scale.y, sizeof ( float ), 1, fp );
	fread ( &objects_3d_scene_database[scene_index].shadow_polygon_object_scale.z, sizeof ( float ), 1, fp );

	//
	// Read in the collision object index
	//

	fread ( &objects_3d_scene_database[scene_index].collision_object_index, sizeof ( int ), 1, fp );

	//
	// Next, read in the keyframes for the main object in the scene.
	//

	fread ( &objects_3d_scene_database[scene_index].number_of_keyframes, sizeof ( int ), 1, fp );

	objects_3d_scene_database[scene_index].keyframes = objects_3d_scene_sub_object_keyframes_array_ptr;

	objects_3d_scene_sub_object_keyframes_array_ptr += objects_3d_scene_database[scene_index].number_of_keyframes;

	for ( keyframe_count = 0; keyframe_count < objects_3d_scene_database[scene_index].number_of_keyframes; keyframe_count++ )
	{

		fread ( &objects_3d_scene_database[scene_index].keyframes[keyframe_count].index, sizeof ( int ), 1, fp );
		fread ( &objects_3d_scene_database[scene_index].keyframes[keyframe_count].linear, sizeof ( int ), 1, fp );

		fread ( &objects_3d_scene_database[scene_index].keyframes[keyframe_count].x, sizeof ( float ), 1, fp );
		fread ( &objects_3d_scene_database[scene_index].keyframes[keyframe_count].y, sizeof ( float ), 1, fp );
		fread ( &objects_3d_scene_database[scene_index].keyframes[keyframe_count].z, sizeof ( float ), 1, fp );

		fread ( &objects_3d_scene_database[scene_index].keyframes[keyframe_count].heading, sizeof ( float ), 1, fp );
		fread ( &objects_3d_scene_database[scene_index].keyframes[keyframe_count].pitch, sizeof ( float ), 1, fp );
		fread ( &objects_3d_scene_database[scene_index].keyframes[keyframe_count].roll, sizeof ( float ), 1, fp );

		fread ( &objects_3d_scene_database[scene_index].keyframes[keyframe_count].scale_x, sizeof ( int ), 1, fp );
		fread ( &objects_3d_scene_database[scene_index].keyframes[keyframe_count].scale_y, sizeof ( int ), 1, fp );
		fread ( &objects_3d_scene_database[scene_index].keyframes[keyframe_count].scale_z, sizeof ( int ), 1, fp );

		fread ( &objects_3d_scene_database[scene_index].keyframes[keyframe_count].tension, sizeof ( int ), 1, fp );
		fread ( &objects_3d_scene_database[scene_index].keyframes[keyframe_count].continuity, sizeof ( int ), 1, fp );
		fread ( &objects_3d_scene_database[scene_index].keyframes[keyframe_count].bias, sizeof ( int ), 1, fp );
	}

	//
	// Next the object dissolve for the main object & any keyframes associate with it
	//

	fread ( &objects_3d_scene_database[scene_index].object_dissolve, sizeof ( float ), 1, fp );

	fread ( &objects_3d_scene_database[scene_index].number_of_object_dissolve_keyframes, sizeof ( int ), 1, fp );

	objects_3d_scene_database[scene_index].object_dissolve_keyframes = objects_3d_scene_sub_object_dissolve_keyframes_array_ptr;

	objects_3d_scene_sub_object_dissolve_keyframes_array_ptr += objects_3d_scene_database[scene_index].number_of_object_dissolve_keyframes;

	for ( keyframe_count = 0; keyframe_count < objects_3d_scene_database[scene_index].number_of_object_dissolve_keyframes; keyframe_count++ )
	{

		fread ( &objects_3d_scene_database[scene_index].object_dissolve_keyframes[keyframe_count].index, sizeof ( int ), 1, fp );
		fread ( &objects_3d_scene_database[scene_index].object_dissolve_keyframes[keyframe_count].linear, sizeof ( int ), 1, fp );

		fread ( &objects_3d_scene_database[scene_index].object_dissolve_keyframes[keyframe_count].value, sizeof ( float ), 1, fp );
		fread ( &objects_3d_scene_database[scene_index].object_dissolve_keyframes[keyframe_count].tension, sizeof ( int ), 1, fp );
		fread ( &objects_3d_scene_database[scene_index].object_dissolve_keyframes[keyframe_count].continuity, sizeof ( int ), 1, fp );
		fread ( &objects_3d_scene_database[scene_index].object_dissolve_keyframes[keyframe_count].bias, sizeof ( int ), 1, fp );
	}

	//
	// Next read in the object displacement sequence number
	//

	fread ( &objects_3d_scene_database[scene_index].displacement_sequence_index, sizeof ( int ), 1, fp );

	fread ( &objects_3d_scene_database[scene_index].number_of_displacement_amplitude_keyframes, sizeof ( int ), 1, fp );

	objects_3d_scene_database[scene_index].displacement_amplitude_keyframes = objects_3d_scene_sub_object_dissolve_keyframes_array_ptr;

	objects_3d_scene_sub_object_dissolve_keyframes_array_ptr += objects_3d_scene_database[scene_index].number_of_displacement_amplitude_keyframes;

	for ( keyframe_count = 0; keyframe_count < objects_3d_scene_database[scene_index].number_of_displacement_amplitude_keyframes; keyframe_count++ )
	{

		fread ( &objects_3d_scene_database[scene_index].displacement_amplitude_keyframes[keyframe_count].index, sizeof ( int ), 1, fp );
		fread ( &objects_3d_scene_database[scene_index].displacement_amplitude_keyframes[keyframe_count].linear, sizeof ( int ), 1, fp );

		fread ( &objects_3d_scene_database[scene_index].displacement_amplitude_keyframes[keyframe_count].value, sizeof ( float ), 1, fp );
		fread ( &objects_3d_scene_database[scene_index].displacement_amplitude_keyframes[keyframe_count].tension, sizeof ( int ), 1, fp );
		fread ( &objects_3d_scene_database[scene_index].displacement_amplitude_keyframes[keyframe_count].continuity, sizeof ( int ), 1, fp );
		fread ( &objects_3d_scene_database[scene_index].displacement_amplitude_keyframes[keyframe_count].bias, sizeof ( int ), 1, fp );
	}


	//
	// Read in any sub object indices
	//

	{

		int
			number_of_sub_object_indices;

		fread ( &number_of_sub_object_indices, sizeof ( int ), 1, fp );

		objects_3d_scene_database[scene_index].number_of_sub_object_indices = number_of_sub_object_indices;

		if ( number_of_sub_object_indices )
		{

			int
				index_count,
				sub_object_index,
				object_index;

			//
			// Allocate the array
			//

			objects_3d_scene_database[scene_index].sub_object_indices = current_scene_sub_object_index_array;

			current_scene_sub_object_index_array += number_of_sub_object_indices;

			ASSERT ( objects_3d_scene_database[scene_index].sub_object_indices );

			for ( index_count = 0; index_count < objects_3d_scene_database[scene_index].number_of_sub_object_indices; index_count++ )
			{

				fread ( &sub_object_index, sizeof ( int ), 1, fp );

				fread ( &object_index, sizeof ( int ), 1, fp );

				objects_3d_scene_database[scene_index].sub_object_indices[index_count].sub_object_index = sub_object_index;

				objects_3d_scene_database[scene_index].sub_object_indices[index_count].object_index = object_index;

				if ( index_count != 0 )
				{

					ASSERT ( objects_3d_scene_database[scene_index].sub_object_indices[index_count-1].object_index <
								objects_3d_scene_database[scene_index].sub_object_indices[index_count].object_index );
				}
			}
		}
	}

	//
	// Read in any immediate sub objects
	//

	fread ( &objects_3d_scene_database[scene_index].number_of_sub_objects, sizeof ( int ), 1, fp );

	if ( objects_3d_scene_database[scene_index].number_of_sub_objects )
	{

		int
			sub_object_total,
			sub_object_count;

		struct OBJECT_3D_DATABASE_ENTRY
			*sub_objects;

		sub_object_total = objects_3d_scene_database[scene_index].number_of_sub_objects;

		sub_objects = current_scene_sub_object_array;

		current_scene_sub_object_array += sub_object_total;

		ASSERT ( sub_objects );

		objects_3d_scene_database[scene_index].sub_objects = sub_objects;

		for ( sub_object_count = 0; sub_object_count < sub_object_total; sub_object_count++ )
			initialise_3d_sub_object ( fp, NULL, &sub_objects[sub_object_count] );

	}

	initialise_scene_quick_sub_object_search ( scene_index );

	initialise_scene_visible_sub_objects ( scene_index );

	initialise_scene_bounding_sub_objects ( scene_index );	
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void initialise_sub_object(object_3d_database_entry* entry, unsigned model_index)
{
	entry->index = model_index;
	entry->default_visibility = TRUE;

	entry->sub_object_approximation_in_level = 1;
	entry->sub_object_approximation_out_level = 1;

	entry->object_dissolve = 1.0;
}

static void initialise_custom_scenes(const char* directory)
{
	char filename[1024];
	object_3d_scene_database_entry* scene;

	custom_3d_models.arneh_ah64d_cockpit = FALSE;  // don't set it to true unless we find all subobjects
		
	// internal occkpit
	scene = &objects_3d_scene_database[OBJECT_3D_ARNEH_AH64D_COCKPIT];
	scene->number_of_sub_objects = 1;  // the entire cockpit
	scene->total_number_of_sub_objects = 9;  // main object, 2 invisible objects which just contain other objects, and 6 actual objects

	scene->object_dissolve = 1.0;
	scene->radius = 10.0;
	scene->object_approximation_scale = 1.0;

	scene->sub_objects = safe_malloc(sizeof(object_3d_database_entry) * scene->total_number_of_sub_objects);

	memset(scene->sub_objects, 0, sizeof(object_3d_database_entry) * scene->total_number_of_sub_objects);

	// the sub-objects:
	{
		object_3d_database_entry* entry = &scene->sub_objects[0];
		object_3d_database_entry* main_entry = entry;

		snprintf(filename, sizeof(filename) - 1, "%s\\objects\\ah-64d-cockpit\\ah-64d-cockpit.eeo", directory);
		if (read_object(&objects_3d_data[next_free_custom_object], filename))
		{
			initialise_sub_object(entry, next_free_custom_object++);

			entry->number_of_sub_objects = 7;  // one for view + one for co-pilot helmet + 4 for the throttles + one for radio switches
			entry->sub_objects = &scene->sub_objects[1];

			// make an empty sub-object for views
			entry = &main_entry->sub_objects[0];
			entry->parent = main_entry;

			initialise_sub_object(entry, 0);

			// make sub-objects for the throttles
			snprintf(filename, sizeof(filename) - 1, "%s\\objects\\ah-64d-cockpit\\ah-64d-throttle-left.eeo", directory);
			if (read_object(&objects_3d_data[next_free_custom_object], filename))
			{
				int
					left_throttle = next_free_custom_object++,
					right_throttle = next_free_custom_object++;

				snprintf(filename, sizeof(filename) - 1, "%s\\objects\\ah-64d-cockpit\\ah-64d-throttle-right.eeo", directory);
				if (read_object(&objects_3d_data[right_throttle], filename))
				{
					int i;
					
					for (i= 0; i < 4; i++)
					{
						entry = &main_entry->sub_objects[i+1];
						entry->parent = main_entry;

						// left throttle in position 0 and 2, right in 1 and 3
						initialise_sub_object(entry, (i % 2) ? right_throttle : left_throttle);
					}
	
					custom_3d_models.arneh_ah64d_cockpit = TRUE;
				}
			}

			if (!custom_3d_models.arneh_ah64d_cockpit)
				return;

			snprintf(filename, sizeof(filename) - 1, "%s\\objects\\ah-64d-cockpit\\ah-64d-helmet.eeo", directory);
			if (read_object(&objects_3d_data[next_free_custom_object++], filename))
			{
				entry = &main_entry->sub_objects[5];
				entry->parent = main_entry;

				// first an invisible object for the torso
				initialise_sub_object(entry, 0);
				entry->number_of_sub_objects = 1;
				entry->sub_objects = &main_entry->sub_objects[7];
//				entry->default_visibility = TRUE;

				// then the helmet
				entry = &main_entry->sub_objects[7];
				initialise_sub_object(entry, next_free_custom_object-1);
				entry->parent = &main_entry->sub_objects[5];
//				entry->default_visibility = FALSE;
			}
			else
				custom_3d_models.arneh_ah64d_cockpit = FALSE;

			snprintf(filename, sizeof(filename) - 1, "%s\\objects\\ah-64d-cockpit\\ah-64d-radio-switches.eeo", directory);
			if (read_object(&objects_3d_data[next_free_custom_object++], filename))
			{
				// the radio switches
				entry = &main_entry->sub_objects[6];
				entry->parent = main_entry;
				initialise_sub_object(entry, next_free_custom_object-1);
				entry->default_visibility = TRUE;
			}
			else
				custom_3d_models.arneh_ah64d_cockpit = FALSE;
		}
	}

	if (!custom_3d_models.arneh_ah64d_cockpit)
		return;

	// external part of cockpit
	scene = &objects_3d_scene_database[OBJECT_3D_ARNEH_AH64D_VCKPT_NOSE];

	scene->number_of_sub_objects = 1;
	scene->total_number_of_sub_objects = 2;

	scene->object_dissolve = 1.0;
	scene->radius = 10.0;
	scene->object_approximation_scale = 1.0;

	scene->sub_objects = safe_malloc(sizeof(object_3d_database_entry) * scene->total_number_of_sub_objects);

	memset(scene->sub_objects, 0, sizeof(object_3d_database_entry) * scene->total_number_of_sub_objects);

	// the sub-objects:
	{
		object_3d_database_entry* entry = &scene->sub_objects[0];

		custom_3d_models.arneh_ah64d_cockpit = FALSE;  // don't set it to true unless we find all subobjects
		
		snprintf(filename, sizeof(filename) - 1, "%s\\objects\\ah-64d-cockpit\\ah-64d-nose.eeo", directory);
		if (read_object(&objects_3d_data[next_free_custom_object], filename))
		{
			initialise_sub_object(entry, next_free_custom_object++);

			snprintf(filename, sizeof(filename) - 1, "%s\\objects\\ah-64d-cockpit\\ah-64d-pnvs.eeo", directory);
			if (read_object(&objects_3d_data[next_free_custom_object], filename))
			{
				entry->number_of_sub_objects = 1;
				entry->sub_objects = &scene->sub_objects[1];
				
				entry->sub_objects[0].parent = entry;
				entry = &entry->sub_objects[0];
				initialise_sub_object(entry, next_free_custom_object++);
				custom_3d_models.arneh_ah64d_cockpit = TRUE;
			}
		}
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#define DEBUG_DB_INT(var)  fprintf(out, "%s" #var ": %d\n", indent, db_entry->var)
#define DEBUG_DB_HEX(var)  fprintf(out, "%s" #var ": %08X\n", indent, db_entry->var)
#define DEBUG_DB_FLOAT(var)  fprintf(out, "%s" #var ": %.3f\n", indent, db_entry->var)

void debug_database_entry(object_3d_database_entry* db_entry, FILE* out, unsigned level)
{
	char indent[128];
	int i, nsubs;

	for (i = 0; i < min(level * 2,127); i++)
		indent[i] = ' ';
	indent[i] = '\0';

	DEBUG_DB_HEX(index);
	DEBUG_DB_INT(number_of_sub_objects);
	DEBUG_DB_INT(number_of_keyframes);

	DEBUG_DB_INT(default_visibility);
	DEBUG_DB_INT(collision_contribution);

	DEBUG_DB_INT(number_of_object_dissolve_keyframes);
	DEBUG_DB_INT(sub_object_approximation_in_level);
	DEBUG_DB_INT(sub_object_approximation_out_level);

	DEBUG_DB_INT(number_of_sub_object_indices);
	DEBUG_DB_FLOAT(object_dissolve);

	nsubs = db_entry->number_of_sub_objects;
	if (nsubs)
	{
		fprintf(out, "%ssub objects:\n", indent);

		for (i=0; i < nsubs; i++)
		{
			fprintf(out, "%ssub index: %d\n", indent, i);
			debug_database_entry(&db_entry->sub_objects[i], out, level + 1);
		}
	}
}

void debug_database_scene(object_3d_scene_database_entry* db_entry, FILE* out)
{
	char indent[1] = {'\0'};
	int i;

	DEBUG_DB_HEX(index);
	DEBUG_DB_INT(number_of_texture_animations);
	DEBUG_DB_INT(number_of_cameras);
	DEBUG_DB_INT(number_of_keyframes);
	DEBUG_DB_INT(number_of_scene_link_objects);

	DEBUG_DB_INT(number_of_sub_objects);
	DEBUG_DB_INT(number_of_sub_object_indices);
	DEBUG_DB_INT(number_of_sub_object_table_entries);
	DEBUG_DB_INT(total_number_of_sub_objects);
	DEBUG_DB_INT(total_number_of_sub_object_indices);

	DEBUG_DB_FLOAT(radius);
	DEBUG_DB_FLOAT(object_dissolve);
	DEBUG_DB_FLOAT(object_approximation_scale);

	for (i=0; i < db_entry->number_of_sub_objects; i++)
	{
		fprintf(out, "%ssub index: %d\n", indent, i);
		debug_database_entry(&db_entry->sub_objects[i], out, 1);
		fprintf(out, "\n");
	}
}
#undef DEBUG_DB_INT
#undef DEBUG_DB_HEX


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


static int read_object(object_3d *obj, const char* filename)
{
	FILE*
		file;

	int
		i,
		number_of_points,
		number_of_faces,
		number_of_surfaces,
		number_of_texture_points,
		format_version,
		number_of_point_normals,
		number_of_point_references,
		number_of_surface_point_references,
		number_of_surface_point_normals;

	file = fopen ( filename, "rb" );
	if ( !file )
		return FALSE;

	fread ( &format_version, 4, 1, file );
	fread ( &number_of_points, 4, 1, file );
	fread ( &number_of_faces, 4, 1, file );
	fread ( &number_of_surfaces, 4, 1, file );
	fread ( &number_of_point_normals, 4, 1, file );
	fread ( &number_of_point_references, 4, 1, file );
	fread ( &number_of_texture_points, 4, 1, file );
	fread ( &number_of_surface_point_references, 4, 1, file );
	fread ( &number_of_surface_point_normals, 4, 1, file );

	if (format_version != 1)
		debug_fatal("Incompatible object: %s (object version %d)", filename, format_version);

	obj->number_of_points = number_of_points;
	obj->number_of_faces = number_of_faces;
	obj->number_of_point_normals = number_of_point_normals;
	obj->number_of_lighting_normals = number_of_point_normals;
	obj->number_of_surfaces = number_of_surfaces;

	fread ( &obj->bounding_box, 24, 1, file );
	fread ( &obj->bounding_box2, 24, 1, file );

	if ( obj->number_of_points )  // read all points
	{
		obj->points = safe_malloc ( 6 * obj->number_of_points );
		fread ( obj->points, 6, obj->number_of_points, file );
	}
	else
		obj->points = NULL;
	if ( number_of_faces )  // number of points in each poly
	{
		obj->faces = safe_malloc ( 1 * number_of_faces );
		fread ( obj->faces, 1, number_of_faces, file );
	}
	else
		obj->faces = NULL;
	if ( number_of_point_normals )
	{
		obj->point_normals = safe_malloc ( 2 * number_of_point_normals );
		fread ( obj->point_normals, 2, number_of_point_normals, file );
	}
	else
		obj->point_normals = NULL;
	if ( number_of_point_references )  // the points of all faces in same order as faces
	{
		obj->object_faces_point_plain_list = safe_malloc ( 1 * number_of_point_references );
		fread ( obj->object_faces_point_plain_list, 1, number_of_point_references, file );
	}
	else
		obj->object_faces_point_plain_list = NULL;
	if ( obj->number_of_surfaces )
	{
		obj->surfaces = safe_malloc ( 16 * obj->number_of_surfaces );
		fread ( obj->surfaces, 16, obj->number_of_surfaces, file );
	}
	else
		obj->surfaces = NULL;
	if ( number_of_faces )   // read face normals
	{
		obj->object_face_normal_references = safe_malloc ( 2 * number_of_faces );
		fread ( obj->object_face_normal_references, 2, number_of_faces, file );
	}
	else
		obj->object_face_normal_references = NULL;
	if ( number_of_texture_points )
	{
		obj->surface_texture_points = safe_malloc ( 8 * number_of_texture_points );
		fread ( obj->surface_texture_points, 8, number_of_texture_points, file );
	}
	else
		obj->surface_texture_points = NULL;
	if ( number_of_surface_point_references )
	{
		obj->surface_points = safe_malloc ( 2 * number_of_surface_point_references );
		fread ( obj->surface_points, 2, number_of_surface_point_references, file );
	}
	else
		obj->surface_points = NULL;

	if ( number_of_surface_point_normals )
	{
		obj->surface_point_normals = safe_malloc ( 2 * number_of_surface_point_normals );
		fread ( obj->surface_points, 2, number_of_surface_point_normals, file );
	}
	else
		obj->surface_point_normals = NULL;

	obj->custom = 1;

	// texture overrides
	for (i = 0; i < obj->number_of_surfaces; i++)
	{
		char texture_name[256];

		if (!get_nul_string(texture_name, sizeof(texture_name), file, TRUE))
			break;

		if (*texture_name)
			obj->surfaces[i].texture_index = add_new_texture(texture_name);
	}

	fclose(file);

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_3d_objects ( const char *directory )
{

	int
		total_number_of_objects,
		number_of_custom_objects,
		total_number_of_scenes,
		total_number_of_surfaces,
		total_number_of_points,
		total_number_of_point_normals,
		total_number_of_plain_points,
		total_number_of_face_normal_points,
		total_number_of_polygons,
		count;

	object_short_3d_point
		*current_points;

	object_3d_face
		*current_faces;

	object_3d_heading_pitch_normal
		*current_point_normals;

	face_surface_description
		*current_surfaces;

	point_3d_short_reference
		*current_faces_point_list;

	point_3d_plain_reference
		*current_faces_face_normal_list,
		*current_object_surface_point_references,
		*current_object_surface_point_normal_references;

	object_3d_short_textured_point
		*current_object_surface_point_texture_references;

	FILE
		*fp;

	char
		filename[512];

	ASSERT ( get_memory_block_system_installed () );

	//
	// Initialise the objects lookup tablesj
	//

	initialise_object_3d_lookup_tables ();

	//
 	// Initialise the objects name data first
	//

	initialise_3d_objects_info ( directory );

	//
	// Open the files
	//

	sprintf ( filename, "%s\\3dobjs.bin", directory );
	fp = safe_fopen ( filename, "rb" );

	sprintf ( filename, "%s\\3dobjs.pts", directory );
	object_database_points = safe_mopen ( filename );

	sprintf ( filename, "%s\\3dobjs.sp", directory );
	object_database_surface_point_list = safe_mopen ( filename );

	sprintf ( filename, "%s\\3dobjs.spn", directory );
	object_database_surface_point_normal_list = safe_mopen ( filename );

	sprintf ( filename, "%s\\3dobjs.spt", directory );
	object_database_surface_point_texture_list = safe_mopen ( filename );

#if REPORT_OBJECT_STATS
	debug_log ( "Reading in 3d objects" );
#endif

	//
	// Now theres the number of 3d objects
	//

	total_number_of_points = 0;
	total_number_of_point_normals = 0;
	total_number_of_surfaces = 0;
	total_number_of_polygons = 0;
	total_number_of_plain_points = 0;
	total_number_of_face_normal_points = 0;

	fread ( &total_number_of_objects, sizeof ( int ), 1, fp );

	number_of_custom_objects = 2;  // apache cockpit and its nose
	next_free_custom_object = total_number_of_objects;
	total_objects = total_number_of_objects + number_of_custom_objects;

#if REPORT_OBJECT_STATS
	debug_log ( "THERE ARE %d 3D OBJECT SHAPES", total_number_of_objects );
#endif

	objects_3d_data = safe_malloc ( ( total_number_of_objects + 1 + number_of_custom_objects) * sizeof ( struct OBJECT_3D ) );
	memset ( objects_3d_data, 0, ( total_number_of_objects + 1 + number_of_custom_objects) * sizeof ( struct OBJECT_3D ) );

	//
	// Now the first object ( index 0 ) is a NULL object - and has no 3d points, or anything at all
	//

	objects_3d_data[0].number_of_points = 0;
	objects_3d_data[0].number_of_surfaces = 0;
	objects_3d_data[0].number_of_faces = 0;
	objects_3d_data[0].number_of_point_normals = 0;
	objects_3d_data[0].bounding_box.xmin = 0;
	objects_3d_data[0].bounding_box.xmax = 0;
	objects_3d_data[0].bounding_box.ymin = 0;
	objects_3d_data[0].bounding_box.ymax = 0;
	objects_3d_data[0].bounding_box.zmin = 0;
	objects_3d_data[0].bounding_box.zmax = 0;
	objects_3d_data[0].bounding_box2.xmin = 0;
	objects_3d_data[0].bounding_box2.xmax = 0;
	objects_3d_data[0].bounding_box2.ymin = 0;
	objects_3d_data[0].bounding_box2.ymax = 0;
	objects_3d_data[0].bounding_box2.zmin = 0;
	objects_3d_data[0].bounding_box2.zmax = 0;
	objects_3d_data[0].radius = 0;

	total_number_of_raw_3d_objects = total_number_of_objects;

	//
	// Now a count of how many of each array type
	//

	fread ( &total_number_of_surfaces, sizeof ( int ), 1, fp );
	fread ( &total_number_of_points, sizeof ( int ), 1, fp );
	fread ( &total_number_of_point_normals, sizeof ( int ), 1, fp );
	fread ( &total_number_of_plain_points, sizeof ( int ), 1, fp );
	fread ( &total_number_of_face_normal_points, sizeof ( int ), 1, fp );
	fread ( &total_number_of_polygons, sizeof ( int ), 1, fp );

	//
	// Malloc the arrays
	//

	object_database_faces = NULL;
	object_database_point_normals = NULL;
	object_database_surfaces = NULL;
	object_database_faces_point_list = NULL;
	object_database_faces_face_normal_list = NULL;

	if ( total_number_of_polygons )
	{

		object_database_faces = safe_malloc ( sizeof ( object_3d_face ) * total_number_of_polygons );
	}

	if ( total_number_of_point_normals )
	{

		object_database_point_normals = safe_malloc ( sizeof ( object_3d_heading_pitch_normal ) * total_number_of_point_normals );
	}

	if ( total_number_of_surfaces )
	{

		object_database_surfaces = safe_malloc ( sizeof ( face_surface_description ) * total_number_of_surfaces );
	}

	if ( total_number_of_plain_points )
	{

		object_database_faces_point_list = safe_malloc ( sizeof ( point_3d_short_reference ) * total_number_of_plain_points );
	}

	if ( total_number_of_face_normal_points )
	{

		object_database_faces_face_normal_list = safe_malloc ( sizeof ( point_3d_plain_reference ) * total_number_of_face_normal_points );
	}

	current_points = object_database_points;
	current_faces = object_database_faces;
	current_point_normals = object_database_point_normals;
	current_surfaces = object_database_surfaces;
	current_faces_point_list = object_database_faces_point_list;
	current_faces_face_normal_list = object_database_faces_face_normal_list;

	current_object_surface_point_references = object_database_surface_point_list;
	current_object_surface_point_normal_references = object_database_surface_point_normal_list;
	current_object_surface_point_texture_references = object_database_surface_point_texture_list;

	for ( count = 1; count <= total_number_of_objects; count++ )
	{
		int
			surface_count,
			point_reference_count,
			face_normal_reference_count;

		int
			pretend_null_object,
			number_of_points,
			number_of_surfaces,
			number_of_faces,
			number_of_point_normals,
			number_of_lighting_normals,
			culling_normals_offset;

		//
		// Zero the pointers to start with ( for safety in deinitialisation )
		//

		objects_3d_data[count].number_of_points = 0;
		objects_3d_data[count].number_of_surfaces = 0;
		objects_3d_data[count].number_of_faces = 0;
		objects_3d_data[count].number_of_point_normals = 0;
		objects_3d_data[count].number_of_lighting_normals = 0;
		objects_3d_data[count].culling_normals_offset = 0;
		objects_3d_data[count].object_faces_point_plain_list = NULL;
		objects_3d_data[count].faces = NULL;
		objects_3d_data[count].radius = 0;

		memset ( &objects_3d_data[count].bounding_box, 0, sizeof ( object_3d_bounds ) );
		memset ( &objects_3d_data[count].bounding_box2, 0, sizeof ( object_3d_bounds ) );

		fread ( &pretend_null_object, sizeof ( int ), 1, fp );

		if ( !pretend_null_object )
		{

			int
				number_of_real_polygons;
	
			fread ( &number_of_points, sizeof ( int ), 1, fp );
			fread ( &number_of_surfaces, sizeof ( int ), 1, fp );
			fread ( &number_of_faces, sizeof ( int ), 1, fp );
			fread ( &number_of_point_normals, sizeof ( int ), 1, fp );
			fread ( &number_of_lighting_normals, sizeof ( int ), 1, fp );
			fread ( &culling_normals_offset, sizeof ( int ), 1, fp );

			objects_3d_data[count].number_of_points = number_of_points;
			objects_3d_data[count].number_of_surfaces = number_of_surfaces;
			objects_3d_data[count].number_of_faces = number_of_faces;
			objects_3d_data[count].number_of_point_normals = number_of_point_normals;
			objects_3d_data[count].number_of_lighting_normals = number_of_lighting_normals;
			objects_3d_data[count].culling_normals_offset = culling_normals_offset;

			fread ( &objects_3d_data[count].radius, sizeof ( int ), 1, fp );

			{

				int
					number_of_point_references,
					number_of_point_normals,
					number_of_point_textures;

				fread ( &number_of_point_references, sizeof ( int ), 1, fp );
				fread ( &number_of_point_normals, sizeof ( int ), 1, fp );
				fread ( &number_of_point_textures, sizeof ( int ), 1, fp );

				objects_3d_data[count].surface_points = current_object_surface_point_references;
				objects_3d_data[count].surface_point_normals = current_object_surface_point_normal_references;
				objects_3d_data[count].surface_texture_points = current_object_surface_point_texture_references;

				current_object_surface_point_references += number_of_point_references;
				current_object_surface_point_normal_references += number_of_point_normals;
				current_object_surface_point_texture_references += number_of_point_textures;
			}

			fread ( &objects_3d_data[count].bounding_box, sizeof ( object_3d_bounds ), 1, fp );
			fread ( &objects_3d_data[count].bounding_box2, sizeof ( object_3d_bounds ), 1, fp );
	
			objects_3d_data[count].surfaces = current_surfaces;
	
			current_surfaces += objects_3d_data[count].number_of_surfaces;

			number_of_real_polygons = 0;

			for ( surface_count = 0; surface_count < objects_3d_data[count].number_of_surfaces; surface_count++ )
			{
	
				fread ( &objects_3d_data[count].surfaces[surface_count].surface_flags, sizeof ( unsigned int ), 1, fp );
				fread ( &objects_3d_data[count].surfaces[surface_count].texture_index, sizeof ( unsigned short int ), 1, fp );
				fread ( &objects_3d_data[count].surfaces[surface_count].luminosity_texture_index, sizeof ( unsigned short int ), 1, fp );
				fread ( &objects_3d_data[count].surfaces[surface_count].number_of_faces, sizeof ( int ), 1, fp );
				fread ( &objects_3d_data[count].surfaces[surface_count].colour, sizeof ( unsigned int ), 1, fp );
				fread ( &objects_3d_data[count].surfaces[surface_count].reflectivity, sizeof ( unsigned char ), 1, fp );
				fread ( &objects_3d_data[count].surfaces[surface_count].specularity, sizeof ( unsigned char ), 1, fp );

				if ( objects_3d_data[count].surfaces[surface_count].textured )
				{

					if ( objects_3d_data[count].surfaces[surface_count].texture_animation )
					{

						if ( objects_3d_data[count].surfaces[surface_count].texture_index >= number_of_texture_animations )
						{

							BREAKOUT ();
						}
					}
				}

				if ( objects_3d_data[count].surfaces[surface_count].polygons )
				{

					number_of_real_polygons += objects_3d_data[count].surfaces[surface_count].number_of_faces;
				}
			}
	
			if ( objects_3d_data[count].number_of_points )
			{

				//
				// XYZ points are in separate memory mapped file - just set up the pointer
				//
	
				objects_3d_data[count].points = current_points;
	
				current_points += objects_3d_data[count].number_of_points;
			}
	
			if ( objects_3d_data[count].number_of_point_normals )
			{
	
				//
				// Read in the point normals
				//
	
				objects_3d_data[count].point_normals = current_point_normals;
	
				current_point_normals += objects_3d_data[count].number_of_point_normals;
	
				fread ( objects_3d_data[count].point_normals, sizeof ( object_3d_heading_pitch_normal ), objects_3d_data[count].number_of_point_normals, fp );
			}
	
			fread ( &point_reference_count, sizeof ( int ), 1, fp );
			fread ( &face_normal_reference_count, sizeof ( int ), 1, fp );
	
			//
			// Read in the data for the object
			//
	
			if ( objects_3d_data[count].number_of_faces )
			{

				fread ( current_faces, sizeof ( struct OBJECT_3D_FACE ), number_of_real_polygons, fp );
	
				objects_3d_data[count].faces = current_faces;
		
				current_faces += number_of_real_polygons;
			}
	
			if ( point_reference_count )
			{
	
				fread ( current_faces_point_list, sizeof ( struct POINT_3D_SHORT_REFERENCE ), point_reference_count, fp );
	
				objects_3d_data[count].object_faces_point_plain_list = current_faces_point_list;

				current_faces_point_list += point_reference_count;
			}
	
			if ( face_normal_reference_count )
			{

				fread ( current_faces_face_normal_list, sizeof ( struct POINT_3D_PLAIN_REFERENCE ), face_normal_reference_count, fp );
	
				objects_3d_data[count].object_face_normal_references = current_faces_face_normal_list;

				current_faces_face_normal_list += face_normal_reference_count;
			}
		}
	}

	fclose ( fp );

	/* 26JUL06 Casm Import of 3D objects BEGIN */
	{
		int
			rc;
		long
			handle;
		struct _finddata_t
			fi;
		struct OBJECT_3D
			*obj;

		sprintf ( filename, "%s\\OBJECTS\\????.EEO", directory );
		for ( rc = handle = _findfirst ( filename, &fi ); rc != -1; rc = _findnext ( handle, &fi ) )
		{
			int
				objid;

			if ( !isxdigit ( fi.name[0] ) || !isxdigit ( fi.name[1] ) ||
			     !isxdigit ( fi.name[2] ) || !isxdigit ( fi.name[3] ) )
				continue;

			objid = strtol ( fi.name, NULL, 16 );
			if ( objid <= 0 || objid > total_number_of_objects )
				continue;

			obj = &objects_3d_data[objid];
			sprintf ( filename, "%s\\OBJECTS\\%s", directory, fi.name );
			
			read_object(obj, filename);
		}
		_findclose ( handle );

#if 0   // arneh - this code doesn't seem to be necessary
		if (handle != -1 )
		{
			// reallocates surfaces memory
			
			struct FACE_SURFACE_DESCRIPTION
				*surfaces,
				*cursurface;
			int
				number_of_surfaces = 0;

			for ( count = 1; count <= total_number_of_objects; count++ )
				number_of_surfaces += objects_3d_data[count].number_of_surfaces;
			surfaces = safe_malloc ( sizeof ( face_surface_description ) * number_of_surfaces );
			cursurface = surfaces;
			for ( count = 1; count <= total_number_of_objects; count++ )
			{
				obj = &objects_3d_data[count];

				if ( !obj->number_of_surfaces )
					continue;
				memcpy ( cursurface, obj->surfaces, sizeof ( face_surface_description ) * obj->number_of_surfaces );
				if ( obj->custom )
					safe_free ( obj->surfaces );
				obj->surfaces = cursurface;
				cursurface += obj->number_of_surfaces;
			}
			safe_free ( object_database_surfaces );
			object_database_surfaces = surfaces;
			total_number_of_surfaces = number_of_surfaces;
		}
#endif
	}
	/* 26JUL06 Casm Import of 3D objects END */

#if REPORT_OBJECT_STATS
	debug_log ( "Total number of surfaces: %d, memory used: %d", total_number_of_surfaces, ( total_number_of_surfaces * sizeof ( face_surface_description ) ) );
//	debug_log ( "Total number of points: %d, memory used: %d", total_number_of_points, ( total_number_of_points * sizeof ( object_short_3d_point ) ) );
	debug_log ( "Total number of points: %d, memory used: %d", total_number_of_points, ( total_number_of_points * sizeof ( object_short_3d_point ) ) );
	debug_log ( "Total number of point_normals: %d, memory used: %d", total_number_of_point_normals, ( total_number_of_point_normals * sizeof ( object_3d_point_normal ) ) );
	debug_log ( "Total number of polygons: %d, memory used: %d", total_number_of_polygons, ( total_number_of_polygons * sizeof ( object_3d_face ) ) );
	debug_log ( "Total number of plain points: %d, memory used: %d", total_number_of_plain_points, ( total_number_of_plain_points ) );

	debug_log ( "Total 3d objects memory used: %d", total_number_of_surfaces * sizeof ( face_surface_description ) +
//																	total_number_of_points * sizeof ( object_short_3d_point ) +
																	total_number_of_points * sizeof ( object_3d_point ) +
																	total_number_of_point_normals * sizeof ( object_3d_point_normal ) +
																	total_number_of_polygons * sizeof ( object_3d_face ) +
																	total_number_of_plain_points * 2 );

	debug_log ( "Reading in 3d scenes" );
#endif

	//
	// Now read in the scenes
	//

	sprintf ( filename, "%s\\3dobjdb.bin", directory );
	fp = safe_fopen ( filename, "rb" );

	fread ( &total_number_of_scenes, sizeof ( int ), 1, fp );

	ASSERT ( total_number_of_scenes );

	objects_3d_scene_database = safe_malloc ( sizeof ( struct OBJECT_3D_SCENE_DATABASE_ENTRY ) * OBJECT_3D_LAST );

	ASSERT ( objects_3d_scene_database );

	memset ( objects_3d_scene_database, 0, ( sizeof ( struct OBJECT_3D_SCENE_DATABASE_ENTRY ) * OBJECT_3D_LAST ) );

	//
	// Read in the memory stats for all the scenes
	//

	fread ( &total_number_of_scene_camera_indices, sizeof ( int ), 1, fp );
	fread ( &total_number_of_scene_link_objects, sizeof ( int ), 1, fp );
	fread ( &total_number_of_sprite_light_objects, sizeof ( int ), 1, fp );
	fread ( &total_number_of_scene_sub_objects, sizeof ( int ), 1, fp );
	fread ( &total_number_of_scene_sub_object_indices, sizeof ( int ), 1, fp );
	fread ( &total_number_of_scene_texture_animations, sizeof ( int ), 1, fp );
	fread ( &total_number_of_scene_approximations, sizeof ( int ), 1, fp );
	fread ( &total_number_of_scene_sub_object_keyframes, sizeof ( int ), 1, fp );
	fread ( &total_number_of_scene_sub_object_dissolve_keyframes, sizeof ( int ), 1, fp );

	

	//
	// Allocate the memory
	//

	objects_3d_camera_info_array = NULL;
	objects_3d_scene_link_array = NULL;
	objects_3d_scene_sprite_light_array = NULL;
	objects_3d_scene_sub_objects_array = NULL;
	objects_3d_scene_sub_object_indices_array = NULL;
	objects_3d_scene_approximations_array = NULL;
	objects_3d_scene_texture_animations_array = NULL;
	objects_3d_scene_sub_object_keyframes_array = NULL;
	objects_3d_scene_sub_object_dissolve_keyframes_array = NULL;

	objects_3d_camera_info_array_ptr = NULL;
	objects_3d_scene_link_ptr = NULL;
	objects_3d_scene_sprite_light_ptr = NULL;
	objects_3d_scene_sub_objects_array_ptr = NULL;
	objects_3d_scene_sub_object_indices_array_ptr = NULL;
	objects_3d_scene_approximations_array_ptr = NULL;
	objects_3d_scene_texture_animations_array_ptr = NULL;
	objects_3d_scene_sub_object_keyframes_array_ptr = NULL;
	objects_3d_scene_sub_object_dissolve_keyframes_array_ptr = NULL;

	if ( total_number_of_scene_camera_indices )
	{

		objects_3d_camera_info_array = safe_malloc ( sizeof ( struct OBJECT_3D_SCENE_CAMERA_INFO ) * total_number_of_scene_camera_indices );
	}

	if ( total_number_of_scene_link_objects )
	{

		objects_3d_scene_link_array = safe_malloc ( sizeof ( struct OBJECT_3D_SCENE_LINK_OBJECT ) * total_number_of_scene_link_objects );
	}

	if ( total_number_of_sprite_light_objects )
	{

		objects_3d_scene_sprite_light_array = safe_malloc ( sizeof ( struct OBJECT_3D_SPRITE_LIGHT ) * total_number_of_sprite_light_objects );
	}

#if 0  // arneh - these are alloced separetly for each scene to make it easier to add new scenes
	if ( total_number_of_scene_sub_objects )
	{
		objects_3d_scene_sub_objects_array = safe_malloc ( sizeof ( struct OBJECT_3D_DATABASE_ENTRY ) * total_number_of_scene_sub_objects );
	}

	if ( total_number_of_scene_sub_object_indices )
	{
		objects_3d_scene_sub_object_indices_array = safe_malloc ( sizeof ( struct OBJECT_3D_SUB_OBJECT_INDEX ) * total_number_of_scene_sub_object_indices );
	}
#endif

	if ( total_number_of_scene_texture_animations )
	{

		objects_3d_scene_texture_animations_array = safe_malloc ( sizeof ( int ) * total_number_of_scene_texture_animations );
	}

	if ( total_number_of_scene_approximations )
	{

		objects_3d_scene_approximations_array = safe_malloc ( sizeof ( struct OBJECT_3D_APPROXIMATION_INFO ) * total_number_of_scene_approximations );
	}

	if ( total_number_of_scene_sub_object_keyframes )
	{

		objects_3d_scene_sub_object_keyframes_array = safe_malloc ( sizeof ( struct OBJECT_3D_SUB_OBJECT_KEYFRAME ) * total_number_of_scene_sub_object_keyframes );
	}

	if ( total_number_of_scene_sub_object_dissolve_keyframes )
	{

		objects_3d_scene_sub_object_dissolve_keyframes_array = safe_malloc ( sizeof ( struct OBJECT_3D_SUB_OBJECT_VALUE_KEYFRAME ) * total_number_of_scene_sub_object_dissolve_keyframes );
	}

	objects_3d_camera_info_array_ptr = objects_3d_camera_info_array;
	objects_3d_scene_link_ptr = objects_3d_scene_link_array;
	objects_3d_scene_sprite_light_ptr = objects_3d_scene_sprite_light_array;
	objects_3d_scene_sub_objects_array_ptr = NULL; //objects_3d_scene_sub_objects_array;
	objects_3d_scene_sub_object_indices_array_ptr = objects_3d_scene_sub_object_indices_array;
	objects_3d_scene_texture_animations_array_ptr = objects_3d_scene_texture_animations_array;
	objects_3d_scene_approximations_array_ptr = objects_3d_scene_approximations_array;
	objects_3d_scene_sub_object_keyframes_array_ptr = objects_3d_scene_sub_object_keyframes_array;
	objects_3d_scene_sub_object_dissolve_keyframes_array_ptr = objects_3d_scene_sub_object_dissolve_keyframes_array;

	// read in all the default scenes
	for ( count = 0; count < total_number_of_scenes; count++ )
	{
		read_scene(fp);
	}

	// arneh - this will initialize new custom scenes
	initialise_custom_scenes(directory);

	//
	// Read in the camera information
	//

	fread ( &total_number_of_cameras, sizeof ( int ), 1, fp );

	fread ( &total_number_of_camera_keyframes, sizeof ( int ), 1, fp );

	if ( total_number_of_cameras )
	{

		object_3d_sub_object_keyframe
			*keyframes;

		objects_3d_camera_database = safe_malloc ( sizeof ( struct OBJECT_3D_SCENE_CAMERA ) * total_number_of_cameras );

		objects_3d_camera_keyframes = safe_malloc ( sizeof ( struct OBJECT_3D_SUB_OBJECT_KEYFRAME ) * total_number_of_camera_keyframes );

		keyframes = objects_3d_camera_keyframes;

		for ( count = 0; count < total_number_of_cameras; count++ )
		{

			int
				keyframe_count;

			fread ( &objects_3d_camera_database[count].number_of_keyframes, sizeof ( int ), 1, fp );
			fread ( &objects_3d_camera_database[count].target_sub_object_id, sizeof ( int ), 1, fp );
			fread ( &objects_3d_camera_database[count].heading_locked, sizeof ( int ), 1, fp );
			fread ( &objects_3d_camera_database[count].pitch_locked, sizeof ( int ), 1, fp );
			fread ( &objects_3d_camera_database[count].roll_locked, sizeof ( int ), 1, fp );

			objects_3d_camera_database[count].keyframes = keyframes;

			for ( keyframe_count = 0; keyframe_count < objects_3d_camera_database[count].number_of_keyframes; keyframe_count++ )
			{

				fread ( &keyframes[keyframe_count].index, sizeof ( int ), 1, fp );
				fread ( &keyframes[keyframe_count].linear, sizeof ( int ), 1, fp );
		
				fread ( &keyframes[keyframe_count].x, sizeof ( float ), 1, fp );
				fread ( &keyframes[keyframe_count].y, sizeof ( float ), 1, fp );
				fread ( &keyframes[keyframe_count].z, sizeof ( float ), 1, fp );
		
				fread ( &keyframes[keyframe_count].heading, sizeof ( float ), 1, fp );
				fread ( &keyframes[keyframe_count].pitch, sizeof ( float ), 1, fp );
				fread ( &keyframes[keyframe_count].roll, sizeof ( float ), 1, fp );

				fread ( &keyframes[keyframe_count].scale_x, sizeof ( float ), 1, fp );
				fread ( &keyframes[keyframe_count].scale_y, sizeof ( float ), 1, fp );
				fread ( &keyframes[keyframe_count].scale_z, sizeof ( float ), 1, fp );

				fread ( &keyframes[keyframe_count].tension, sizeof ( float ), 1, fp );
				fread ( &keyframes[keyframe_count].continuity, sizeof ( float ), 1, fp );
				fread ( &keyframes[keyframe_count].bias, sizeof ( float ), 1, fp );
			}

			keyframes += objects_3d_camera_database[count].number_of_keyframes;
		}
	}

	{

		int
			total_keyframes;

		total_keyframes = objects_3d_scene_sub_object_keyframes_array_ptr - objects_3d_scene_sub_object_keyframes_array;

		if ( total_keyframes != total_number_of_scene_sub_object_keyframes )
		{

			debug_fatal ( "Read in %d keyframes, but allocated %d keyframes", total_keyframes, total_number_of_scene_sub_object_keyframes );
		}

	}

	fclose ( fp );

	//
	// Initialise the d3d version of the objects now
	//

	if ( d3d_using_hardware_tnl )
	{
	
		initialise_3d_objects_in_d3d ();
	}

#if REPORT_OBJECT_STATS
	debug_log ( "Finished" );
#endif

	initialised_3d_objects = TRUE;

	//
	// Setup a sprite flare texture
	//

	{

		int
			index;

		object_3d_sprite_flare_texture = NULL;

		index = get_system_texture_index ( "FLARE001" );

		if ( index != -1 )
		{

			object_3d_sprite_flare_texture = get_system_texture_ptr ( index );
		}
	}

	current_number_of_3d_objects_constructed = 0;

	current_amount_of_3d_objects_memory = 0;

	debug_watch ( "NUMBER OF 3D INSTANCES: %d", MT_INT, &current_number_of_3d_objects_constructed );

	debug_watch ( "3D INSTANCES MEMORY: %d", MT_INT, &current_amount_of_3d_objects_memory );

	memset ( object_3d_scenes_creation_count, 0, sizeof ( int ) * OBJECT_3D_LAST );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_3d_sub_object ( FILE *fp, struct OBJECT_3D_DATABASE_ENTRY *parent, struct OBJECT_3D_DATABASE_ENTRY *sub_object )
{

	int
		flag,
		index,
		contributes_to_collisions,
		sub_object_approximation_in_level,
		sub_object_approximation_out_level,
		number_of_keyframes,
		keyframe_count,
		number_of_object_dissolve_keyframes,
		number_of_sub_object_indices,
		number_of_sub_objects;

	sub_object->parent = parent;

	fread ( &index, sizeof ( int ), 1, fp );

	if ( index < 0 )
	{

		index = 0;
	}
//	ASSERT ( index >= 0 );
//	ASSERT ( index < total_number_of_raw_3d_objects );

	fread ( &contributes_to_collisions, sizeof ( int ), 1, fp );
	fread ( &sub_object_approximation_in_level, sizeof ( int ), 1, fp );
	fread ( &sub_object_approximation_out_level, sizeof ( int ), 1, fp );

	sub_object->index = index;
	sub_object->collision_contribution = contributes_to_collisions;
	sub_object->sub_object_approximation_in_level = sub_object_approximation_in_level;
	sub_object->sub_object_approximation_out_level = sub_object_approximation_out_level;

	fread ( &flag, sizeof ( int ), 1, fp );

	if ( flag )
	{

		fread ( &sub_object->relative_heading_maximum, sizeof ( float ), 1, fp );
		fread ( &sub_object->relative_heading_minimum, sizeof ( float ), 1, fp );
	
		fread ( &sub_object->relative_pitch_maximum, sizeof ( float ), 1, fp );
		fread ( &sub_object->relative_pitch_minimum, sizeof ( float ), 1, fp );
	
		fread ( &sub_object->relative_roll_maximum, sizeof ( float ), 1, fp );
		fread ( &sub_object->relative_roll_minimum, sizeof ( float ), 1, fp );
	}

	fread ( &number_of_keyframes, sizeof ( int ), 1, fp );
	ASSERT ( number_of_keyframes );
	sub_object->number_of_keyframes = number_of_keyframes;

	sub_object->keyframes = objects_3d_scene_sub_object_keyframes_array_ptr;
	objects_3d_scene_sub_object_keyframes_array_ptr += number_of_keyframes;
	ASSERT ( sub_object->keyframes );

	for ( keyframe_count = 0; keyframe_count < number_of_keyframes; keyframe_count++ )
	{

		fread ( &sub_object->keyframes[keyframe_count].index, sizeof ( int ), 1, fp );
		fread ( &sub_object->keyframes[keyframe_count].linear, sizeof ( int ), 1, fp );
		fread ( &sub_object->keyframes[keyframe_count].x, sizeof ( float ), 1, fp );
		fread ( &sub_object->keyframes[keyframe_count].y, sizeof ( float ), 1, fp );
		fread ( &sub_object->keyframes[keyframe_count].z, sizeof ( float ), 1, fp );
		fread ( &sub_object->keyframes[keyframe_count].heading, sizeof ( float ), 1, fp );
		fread ( &sub_object->keyframes[keyframe_count].pitch, sizeof ( float ), 1, fp );
		fread ( &sub_object->keyframes[keyframe_count].roll, sizeof ( float ), 1, fp );
		fread ( &sub_object->keyframes[keyframe_count].scale_x, sizeof ( float ), 1, fp );
		fread ( &sub_object->keyframes[keyframe_count].scale_y, sizeof ( float ), 1, fp );
		fread ( &sub_object->keyframes[keyframe_count].scale_z, sizeof ( float ), 1, fp );
		fread ( &sub_object->keyframes[keyframe_count].tension, sizeof ( float ), 1, fp );
		fread ( &sub_object->keyframes[keyframe_count].continuity, sizeof ( float ), 1, fp );
		fread ( &sub_object->keyframes[keyframe_count].bias, sizeof ( float ), 1, fp );
	}

	//
	// Next the object dissolve for the sub object & any keyframes associate with it
	//

	fread ( &sub_object->object_dissolve, sizeof ( float ), 1, fp );
	fread ( &number_of_object_dissolve_keyframes, sizeof ( int ), 1, fp );

	sub_object->number_of_object_dissolve_keyframes = number_of_object_dissolve_keyframes;
	sub_object->object_dissolve_keyframes = objects_3d_scene_sub_object_dissolve_keyframes_array_ptr;
	objects_3d_scene_sub_object_dissolve_keyframes_array_ptr += sub_object->number_of_object_dissolve_keyframes;

	for ( keyframe_count = 0; keyframe_count < sub_object->number_of_object_dissolve_keyframes; keyframe_count++ )
	{

		fread ( &sub_object->object_dissolve_keyframes[keyframe_count].index, sizeof ( int ), 1, fp );
		fread ( &sub_object->object_dissolve_keyframes[keyframe_count].linear, sizeof ( int ), 1, fp );

		fread ( &sub_object->object_dissolve_keyframes[keyframe_count].value, sizeof ( float ), 1, fp );
		fread ( &sub_object->object_dissolve_keyframes[keyframe_count].tension, sizeof ( int ), 1, fp );
		fread ( &sub_object->object_dissolve_keyframes[keyframe_count].continuity, sizeof ( int ), 1, fp );
		fread ( &sub_object->object_dissolve_keyframes[keyframe_count].bias, sizeof ( int ), 1, fp );
	}

	//
	// Now the sub objects
	//

	fread ( &number_of_sub_object_indices, sizeof ( int ), 1, fp );
	sub_object->number_of_sub_object_indices = number_of_sub_object_indices;

	if ( number_of_sub_object_indices )
	{

		int
			index_count;

		//
		// Alloocate the array
		//

		sub_object->sub_object_indices = current_scene_sub_object_index_array;

		current_scene_sub_object_index_array += sub_object->number_of_sub_object_indices;

		ASSERT ( sub_object->sub_object_indices );

		for ( index_count = 0; index_count < sub_object->number_of_sub_object_indices; index_count++ )
		{

			int
				sub_object_index,
				object_index;

			fread ( &sub_object_index, sizeof ( int ), 1, fp );

			fread ( &object_index, sizeof ( int ), 1, fp );

			sub_object->sub_object_indices[index_count].sub_object_index = sub_object_index;

			sub_object->sub_object_indices[index_count].object_index = object_index;
		}
	}

	fread ( &number_of_sub_objects, sizeof ( int ), 1, fp );
	sub_object->number_of_sub_objects = number_of_sub_objects;

	if ( number_of_sub_objects )
	{

		struct OBJECT_3D_DATABASE_ENTRY
			*sub_objects;

		int
			sub_object_count,
			sub_object_total;


		sub_object_total = sub_object->number_of_sub_objects;

		sub_objects = current_scene_sub_object_array;

		current_scene_sub_object_array += sub_object_total;

		sub_object->sub_objects = sub_objects;

		for ( sub_object_count = 0; sub_object_count < sub_object_total; sub_object_count++ )
		{

			initialise_3d_sub_object ( fp, sub_object, &sub_objects[sub_object_count] );
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_3d_objects ( void )
{
	int i;

	//
	// Deinitialise the d3d versions first
	//

	deinitialise_3d_objects_in_d3d ();

	//
	// Go through all the scenes, deallocating the keyframes, and sub objects
	//

	if ( objects_3d_camera_info_array )
	{

		safe_free ( objects_3d_camera_info_array );

		objects_3d_camera_info_array = NULL;
	}

	if ( objects_3d_scene_link_array )
	{

		safe_free ( objects_3d_scene_link_array );

		objects_3d_scene_link_array = NULL;
	}

	if ( objects_3d_scene_sub_objects_array )
	{

		safe_free ( objects_3d_scene_sub_objects_array );

		objects_3d_scene_sub_objects_array = NULL;
	}

	if ( objects_3d_scene_sub_object_indices_array )
	{

		safe_free ( objects_3d_scene_sub_object_indices_array );

		objects_3d_scene_sub_object_indices_array = NULL;
	}

	if ( objects_3d_scene_texture_animations_array )
	{

		safe_free ( objects_3d_scene_texture_animations_array );

		objects_3d_scene_texture_animations_array = NULL;
	}

	if ( objects_3d_scene_approximations_array )
	{

		safe_free ( objects_3d_scene_approximations_array );

		objects_3d_scene_approximations_array = NULL;
	}

	if ( objects_3d_scene_sub_object_keyframes_array )
	{

		safe_free ( objects_3d_scene_sub_object_keyframes_array );

		objects_3d_scene_sub_object_keyframes_array = NULL;
	}

	// free the dynamically allocet sub_objects for each scene
	for (i=0; i < total_objects; i++)
	{
		if (objects_3d_scene_database[i].sub_objects)
			safe_free(objects_3d_scene_database[i].scene_sub_object_array);
		if (objects_3d_scene_database[i].scene_sub_object_indices_array)
			safe_free(objects_3d_scene_database[i].scene_sub_object_indices_array);
	}

	//
	// Free up the scene array itself
	//

	safe_free ( objects_3d_scene_database );

	objects_3d_scene_database = NULL;

	//
	// Free up the cameras
	//

	if ( objects_3d_camera_database )
	{

		safe_free ( objects_3d_camera_database );

		objects_3d_camera_database = NULL;
	}

	if ( objects_3d_camera_keyframes )
	{

		safe_free ( objects_3d_camera_keyframes );

		objects_3d_camera_keyframes = NULL;
	}

	//
	// Free up the object data arrays
	//

	if ( object_database_points )
	{

		safe_mclose ( object_database_points );

		object_database_points = NULL;
	}

	if ( object_database_faces )
	{

		safe_free ( object_database_faces );

		object_database_faces = NULL;
	}

	if ( object_database_point_normals )
	{

		safe_free ( object_database_point_normals );

		object_database_point_normals = NULL;
	}

	if ( object_database_surfaces )
	{

		safe_free ( object_database_surfaces );

		object_database_surfaces = NULL;
	}

	if ( object_database_faces_point_list )
	{

		safe_free ( object_database_faces_point_list );

		object_database_faces_point_list = NULL;
	}

	if ( object_database_faces_gouraud_list )
	{

		safe_free ( object_database_faces_gouraud_list );

		object_database_faces_gouraud_list = NULL;
	}

	if ( object_database_faces_face_normal_list )
	{

		safe_free ( object_database_faces_face_normal_list );

		object_database_faces_face_normal_list = NULL;
	}

	if ( object_database_faces_texture_list )
	{

		safe_mclose ( object_database_faces_texture_list );

		object_database_faces_texture_list = NULL;
	}


	if ( object_database_surface_point_list )
	{

		safe_mclose ( object_database_surface_point_list );

		object_database_surface_point_list = NULL;
	}

	if ( object_database_surface_point_normal_list )
	{

		safe_mclose ( object_database_surface_point_normal_list );

		object_database_surface_point_normal_list = NULL;
	}


	if ( object_database_surface_point_texture_list )
	{

		safe_mclose ( object_database_surface_point_texture_list );

		object_database_surface_point_texture_list = NULL;
	}

	//
	// Now free the database array
	//

	safe_free ( objects_3d_data );

	objects_3d_data = NULL;

	initialised_3d_objects = FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_3d_objects_initialised ( void )
{

	return ( initialised_3d_objects );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void destruct_sub_scene_keyframes ( object_3d_database_entry *sub_scene )
{

	int
		sub_scene_index;

	//
	// If there are any keyframes, deallocate the memory
	//

	if ( sub_scene->number_of_keyframes )
	{

		safe_free ( sub_scene->keyframes );

		sub_scene->number_of_keyframes = 0;

		sub_scene->keyframes = NULL;
	}

	for ( sub_scene_index = 0; sub_scene_index < sub_scene->number_of_sub_objects; sub_scene_index++ )
	{

		destruct_sub_scene_keyframes ( &sub_scene->sub_objects[sub_scene_index] );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_object_approximation_number ( int scene_index, float distance, int *approximation_level )
{

	int
		count,
		total,
		index,
		object_approximation_level;

	object_approximation_level = 1;

	distance += object_approximation_distance_bias;

	distance *= current_3d_viewangle_distance_conversion_factor;

	distance *= objects_3d_scene_database[scene_index].object_approximation_scale;

	index = objects_3d_scene_database[scene_index].index;

	total = objects_3d_scene_database[scene_index].number_of_approximations;

	for ( count = 0; count < total; count++ )
	{

		if ( distance >= objects_3d_scene_database[scene_index].approximations[count].distance )
		{

			index = objects_3d_scene_database[scene_index].approximations[count].object_number;

			object_approximation_level++;
		}
		else
		{

			break;
		}
	}

	*approximation_level = object_approximation_level;

	return ( index );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_object_shadow_polygon_object ( int scene_index )
{

	return ( objects_3d_scene_database[scene_index].shadow_polygon_object_index );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_object_shadow_approximation_number ( int scene_index, float distance, int *approximation_level )
{

	int
		count,
		total,
		index,
		object_approximation_level;

	object_approximation_level = 1;

	index = objects_3d_scene_database[scene_index].index;

	total = objects_3d_scene_database[scene_index].number_of_approximations;

	for ( count = 0; count < total; count++ )
	{

		if ( distance >= objects_3d_scene_database[scene_index].approximations[count].distance )
		{

			index = objects_3d_scene_database[scene_index].approximations[count].object_number;

			object_approximation_level++;
		}
		else
		{

			break;
		}
	}

	if ( object_approximation_level < objects_3d_scene_database[scene_index].shadow_approximation_index )
	{

		object_approximation_level = objects_3d_scene_database[scene_index].shadow_approximation_index;

		if ( object_approximation_level == 1 )
		{

			index = objects_3d_scene_database[scene_index].index;
		}
		else
		{

			index = objects_3d_scene_database[scene_index].approximations[object_approximation_level].object_number;
		}
	}

	*approximation_level = object_approximation_level;

	return ( index );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_object_light_sourcing ( int scene_index )
{

	return ( objects_3d_scene_database[scene_index].shaded );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

object_3d_sub_instance
	*object_3d_sub_instance_construction_array;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

object_3d_instance *construct_3d_object ( object_3d_index_numbers index )
{

	object_3d_instance
		*object;

	int
		count,
		found;

	ASSERT ( index > OBJECT_3D_INVALID_OBJECT_INDEX );
	ASSERT ( index < OBJECT_3D_LAST );
/*
	if ( index == 1 )
	{

		BREAKOUT ();
	}
*/
	current_number_of_3d_objects_constructed += objects_3d_scene_database[index].total_number_of_sub_objects + 1;

	current_amount_of_3d_objects_memory += ( sizeof ( object_3d_instance ) );

	current_amount_of_3d_objects_memory += ( sizeof ( object_3d_sub_instance ) * objects_3d_scene_database[index].total_number_of_sub_objects );

	object_3d_scenes_creation_count[index]++;

	if ( objects_3d_scene_database[index].total_number_of_sub_objects )
	{

		object_3d_sub_instance_construction_array = safe_malloc ( sizeof ( object_3d_sub_instance ) * objects_3d_scene_database[index].total_number_of_sub_objects );
	}

	object = safe_malloc ( sizeof ( object_3d_instance ) );

	object->object_number = index;

	found = FALSE;

	count = index;

	object->parent = NULL;

	if ( objects_3d_scene_database[count].number_of_texture_animations )
	{

		object->texture_animations = malloc_fast_mem ( sizeof ( int ) * objects_3d_scene_database[count].number_of_texture_animations );

		ASSERT ( object->texture_animations );

		memset ( object->texture_animations, 0, ( sizeof ( int ) * objects_3d_scene_database[count].number_of_texture_animations ) );
	}
	else
	{

		object->texture_animations = NULL;
	}

	if ( objects_3d_scene_database[count].number_of_sub_objects )
	{

		object->sub_objects = object_3d_sub_instance_construction_array;

		object_3d_sub_instance_construction_array += objects_3d_scene_database[count].number_of_sub_objects;

		construct_3d_sub_objects ( ( object_3d_sub_instance * ) object,
												object->sub_objects,
												objects_3d_scene_database[count].sub_objects,
												objects_3d_scene_database[count].number_of_sub_objects );
	}
	else
	{

		object->sub_objects = NULL;
	}

	object_3d_sub_instance_construction_array = NULL;

	//
	// Zero the data for the main object
	//

	//
	// Get identity matrix for the main attitude initially
	//

	get_3d_transformation_matrix ( object->vp.attitude, 0, 0, 0 );

	//
	// All object constructed at ( 0, 0, 0 )
	//

	object->vp.x = 0;
	object->vp.y = 0;
	object->vp.z = 0;

	//
	// All objects scaled to original size to start with
	//

	object->relative_scale.x = 1;
	object->relative_scale.y = 1;
	object->relative_scale.z = 1;

	//
	// Objects normally have shadows ( default )
	//

	object->object_has_shadow = TRUE;

	//
	// Objects DON'T normally have internal lighting turned on
	//

	object->object_internal_lighting = FALSE;

	//
	// Objects DON'T normally have sprite lighting turned on
	//

	object->object_sprite_lights = FALSE;

	//
	// Most objects don't need immediate rendering
	//

	object->requires_immediate_render = FALSE;

	//
	// Most objects are NOT dissolved at all
	//

	object->object_dissolve_value = 255;
	
	return ( object );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// functions to dump some information about scenes to file
void dump_sub_object(object_3d_sub_instance* obj, FILE* output);
void dump_object(object_3d_instance* obj, FILE* output)
{
	int i;
	int index = obj->object_number;
	object_3d_scene_database_entry* scene = &objects_3d_scene_database[index];
	
	fprintf(output, "index: %04X\n", index);
	fprintf(output, "view position: %.3f %.3f %.3f\n", obj->view_position.x, obj->view_position.y, obj->view_position.z);
	fprintf(output, "relative scale: %.3f %.3f %.3f\n", obj->relative_scale.x, obj->relative_scale.y, obj->relative_scale.z);
	fprintf(output, "visible %d, immediate render: %d, shadow: %d, lighting: %d, dissolve: %d, sprite light: %d\n",
		obj->visible_object, obj->requires_immediate_render, obj->object_has_shadow,
		obj->object_internal_lighting, obj->object_dissolve_value, obj->object_sprite_lights);

	fprintf(output, "scene index: %04X\n", scene->index);
	fprintf(output, "self shadows: %d, shadow index: %X\n", scene->self_shadows, scene->shadow_polygon_object_index);
	fprintf(output, "collision object: %X\n", scene->collision_object_index);
	fprintf(output, "displacement sequence index: %X\n", scene->displacement_sequence_index);
	fprintf(output, "link objects: %d\n", scene->number_of_scene_link_objects);
	fprintf(output, "radius: %.3f\n", scene->radius);
	fprintf(output, "sub objects: %d (total: %d)\n", scene->number_of_sub_objects, scene->total_number_of_sub_objects);
	fprintf(output, "sub object indices: %d\n", scene->number_of_sub_object_indices);
	fprintf(output, "sub object table entries: %d\n", scene->number_of_sub_object_table_entries);
	fprintf(output, "total sub objects: %d\n\n", scene->total_number_of_sub_objects);

	for (i=0; i < scene->number_of_sub_object_indices; i++)
	{
		fprintf(output, "sub object index array: %d\n", scene->scene_sub_object_indices_array[i]);
		fprintf(output, "sub object index: %d\n", scene->sub_object_indices[i]);
	}

	for (i=0; i < scene->total_number_of_sub_objects; i++)
	{
		object_3d_database_entry* ent = &scene->sub_objects[i];
		object_3d_sub_instance* sub = &obj->sub_objects[i];

		fprintf(output, "\nsub index: %04X\n", ent->index);
		fprintf(output, "number of subobjects: %d\n", ent->number_of_sub_objects);
		dump_sub_object(sub, output);
	}

	for (i=0; i < scene->number_of_sub_object_table_entries; i++)
	{
		object_3d_scene_sub_object_table_entry* ent = &scene->sub_object_indices_table[i];
		fprintf(output, "sub index: %04X\n", ent->sub_object_index);
		fprintf(output, "number of sub objects: %d\n", ent->number_of_sub_objects);
/*		object_3d_database_entry* ent = &scene->scene_sub_object_array[i];
		fprintf(output, "sub index: %X\n", ent->index);
		fprintf(output, "number of subobjects: %d\n", ent->number_of_sub_objects);*/
	}

	fprintf(output, "\n\n");
}
/*
void dump_sub_object(object_3d_sub_instance* obj, FILE* output)
{
//	fprintf(output, "sub object number: %X\n", obj->object_number);
	fprintf(output, "relative position: %.3f %.3f %.3f\n", obj->relative_position.x, obj->relative_position.y, obj->relative_position.z);
	fprintf(output, "heading: %.3f pitch: %.3f roll %.3f\n", deg(obj->relative_heading), obj->relative_pitch, obj->relative_roll);
}		
*/

void dump_sub_object(object_3d_sub_instance* obj, FILE* output)
{
//	int index = obj->object_number;
//	object_3d_scene_database_entry* scene = &objects_3d_scene_database[index];
	
//	fprintf(output, "index: %X\n", index);
//	fprintf(output, "sub object number: %X\n", obj->object_number);
	fprintf(output, "relative position: %.3f %.3f %.3f\n", obj->relative_position.x, obj->relative_position.y, obj->relative_position.z);
	fprintf(output, "heading: %.3f pitch: %.3f roll %.3f\n", deg(obj->relative_heading), obj->relative_pitch, obj->relative_roll);

//	fprintf(output, "view position: %.3f %.3f %.3f\n", obj->view_position.x, obj->view_position.y, obj->view_position.z);
	fprintf(output, "relative scale: %.3f %.3f %.3f\n", obj->relative_scale.x, obj->relative_scale.y, obj->relative_scale.z);
	fprintf(output, "visible %d, immediate render: %d, shadow: %d, lighting: %d, dissolve: %d\n",
		obj->visible_object, obj->requires_immediate_render, obj->object_has_shadow, obj->object_internal_lighting, obj->object_dissolve_value);

/*
	fprintf(output, "scene index: %X\n", scene->index);
	fprintf(output, "self shadows: %d, shadow index: %X\n", scene->self_shadows, scene->object_3d_scene_database_entry);
	fprintf(output, "collision object: %X\n", scene->collision_object_index);
	fprintf(output, "displacement sequence index: %X\n", scene->displacement_sequence_index);
	fprintf(output, "link objects: %d\n", scene->number_of_scene_link_objects);
	fprintf(output, "sub objects: %d\n", scene->number_of_sub_objects);
	fprintf(output, "total sub objects: %d\n", scene->total_number_of_sub_objects);
	fprintf(output, "radius: %.3f", scene->radius);
*/
}

void construct_3d_sub_objects ( object_3d_sub_instance *parent, object_3d_sub_instance *sub_objects, struct OBJECT_3D_DATABASE_ENTRY *source_objects, int number_of_sub_objects )
{
    // number_of_sub_objects is the number of sub objects at this level, there might be more at lower levels */
	int
		temp;

	for ( temp = 0; temp < number_of_sub_objects; temp ++ )
	{
//		sub_objects[temp].object_number = source_objects[temp].index;

		if (source_objects[temp].number_of_keyframes)
		{
			sub_objects[temp].relative_heading = source_objects[temp].keyframes[0].heading;
			sub_objects[temp].relative_pitch = source_objects[temp].keyframes[0].pitch;
			sub_objects[temp].relative_roll = source_objects[temp].keyframes[0].roll;
	
			sub_objects[temp].relative_position.x = source_objects[temp].keyframes[0].x;
			sub_objects[temp].relative_position.y = source_objects[temp].keyframes[0].y;
			sub_objects[temp].relative_position.z = source_objects[temp].keyframes[0].z;
	
			sub_objects[temp].relative_scale.x = source_objects[temp].keyframes[0].scale_x;
			sub_objects[temp].relative_scale.y = source_objects[temp].keyframes[0].scale_y;
			sub_objects[temp].relative_scale.z = source_objects[temp].keyframes[0].scale_z;
		}
		else
		{
			sub_objects[temp].relative_heading = 0.0;
			sub_objects[temp].relative_pitch = 0.0;
			sub_objects[temp].relative_roll = 0.0;
	
			sub_objects[temp].relative_position.x = 0.0;
			sub_objects[temp].relative_position.y = 0.0;
			sub_objects[temp].relative_position.z = 0.0;
	
			sub_objects[temp].relative_scale.x = 1.0;
			sub_objects[temp].relative_scale.y = 1.0;
			sub_objects[temp].relative_scale.z = 1.0;
		}
		
		sub_objects[temp].visible_object = source_objects[temp].default_visibility;

		sub_objects[temp].object_dissolve_value = 255;

		sub_objects[temp].parent = parent;

		// create all sub objects of this sub object
		if ( source_objects[temp].number_of_sub_objects )
		{
			sub_objects[temp].sub_objects = object_3d_sub_instance_construction_array;

			object_3d_sub_instance_construction_array += source_objects[temp].number_of_sub_objects;

			construct_3d_sub_objects ( &sub_objects[temp], sub_objects[temp].sub_objects, source_objects[temp].sub_objects, source_objects[temp].number_of_sub_objects );
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void destruct_3d_object ( object_3d_instance *object )
{

	//
	// Used to be recursive, not anymore.
	//

	current_number_of_3d_objects_constructed -= objects_3d_scene_database[object->object_number].total_number_of_sub_objects + 1;

	current_amount_of_3d_objects_memory -= sizeof ( object_3d_instance );

	current_amount_of_3d_objects_memory -= ( sizeof ( object_3d_sub_instance ) * objects_3d_scene_database[object->object_number].total_number_of_sub_objects );

	object_3d_scenes_creation_count[object->object_number]--;

	//
	// Free up the texture animations array
	//

	if ( object->texture_animations )
	{

		free_mem ( object->texture_animations );
	}

	if ( object->sub_objects )
	{

		safe_free ( object->sub_objects );

		object->sub_objects = NULL;
	}

	safe_free ( object );
/*
	//
	// Recursive routine.
	//

	if ( object->number_of_sub_objects )
	{

		int
			count;

		for ( count = 0; count < object->number_of_sub_objects; count++ )
		{

			destruct_3d_object ( object->sub_objects[count] );
		}

		free_mem ( object->sub_objects );
	}

	free_mem ( object );
	*/
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void scale_object_3d_approximation_distances ( object_3d_index_numbers scene_index, float factor )
{

	ASSERT ( scene_index > OBJECT_3D_INVALID_OBJECT_INDEX );
	ASSERT ( scene_index < OBJECT_3D_LAST );

	ASSERT ( ( factor <= 1.0 ) && ( factor > 0.0 ) );

	objects_3d_scene_database[scene_index].object_approximation_scale = 1.0 / factor;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_object_3d_collision_object_geometry_triangle ( object_3d_index_numbers index, vec3d *return_points, int depth )
{

	ASSERT ( ( index > OBJECT_3D_INVALID_OBJECT_INDEX ) && ( index < OBJECT_3D_LAST ) );

	ASSERT ( return_points );

	if ( objects_3d_scene_database[index].collision_object_index != -1 )
	{

		int
			number_of_surface_points,
			surface,
			number_of_surface_faces,
			count;

		object_3d
			*obj;

		struct POINT_3D_SHORT_REFERENCE
			*refs;

		struct POINT_3D_PLAIN_REFERENCE
			*surface_point_refs;

		obj = &objects_3d_data[ objects_3d_scene_database[index].collision_object_index ];

		refs = obj->object_faces_point_plain_list;

		surface_point_refs = obj->surface_points;

		//
		// Go through the faces, until we come to the one that we need
		//

		count = 0;

		surface = 0;

		number_of_surface_points = obj->surfaces[surface].number_of_points;

		if ( number_of_surface_points == 0 )
		{

			number_of_surface_points = 256;
		}

		number_of_surface_faces = obj->surfaces[surface].number_of_faces;

		while ( ( count < obj->number_of_faces ) && ( ( obj->faces[count].number_of_points - 3 ) < depth ) )
		{

			depth -= ( obj->faces[count].number_of_points - 2 );

			refs += obj->faces[count].number_of_points;

			count++;

			number_of_surface_faces--;

			if ( number_of_surface_faces == 0 )
			{

				surface_point_refs += number_of_surface_points;

				surface++;

				number_of_surface_points = obj->surfaces[surface].number_of_points;
		
				if ( number_of_surface_points == 0 )
				{
		
					number_of_surface_points = 256;
				}
		
				number_of_surface_faces = obj->surfaces[surface].number_of_faces;
			}
		}

		if ( count < obj->number_of_faces )
		{

			float
				xmax,
				ymax,
				zmax;

			xmax = max ( fabs ( obj->bounding_box.xmin ), fabs ( obj->bounding_box.xmax ) );
			ymax = max ( fabs ( obj->bounding_box.ymin ), fabs ( obj->bounding_box.ymax ) );
			zmax = max ( fabs ( obj->bounding_box.zmin ), fabs ( obj->bounding_box.zmax ) );

			xmax /= 32767.0;
			ymax /= 32767.0;
			zmax /= 32767.0;

			return_points[0].x = ( float ) obj->points[ surface_point_refs[ refs[0].point ].point ].x * xmax;
			return_points[0].y = ( float ) obj->points[ surface_point_refs[ refs[0].point ].point ].y * ymax;
			return_points[0].z = ( float ) obj->points[ surface_point_refs[ refs[0].point ].point ].z * zmax;

			return_points[1].x = ( float ) obj->points[ surface_point_refs[ refs[depth+1].point ].point ].x * xmax;
			return_points[1].y = ( float ) obj->points[ surface_point_refs[ refs[depth+1].point ].point ].y * ymax;
			return_points[1].z = ( float ) obj->points[ surface_point_refs[ refs[depth+1].point ].point ].z * zmax;

			return_points[2].x = ( float ) obj->points[ surface_point_refs[ refs[depth+2].point ].point ].x * xmax;
			return_points[2].y = ( float ) obj->points[ surface_point_refs[ refs[depth+2].point ].point ].y * ymax;
			return_points[2].z = ( float ) obj->points[ surface_point_refs[ refs[depth+2].point ].point ].z * zmax;

			return ( TRUE );
		}
		else
		{

			return ( FALSE );
		}
	}
	else
	{

		return ( FALSE );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_object_3d_number_of_poly_lines ( object_3d_index_numbers index )
{

	int
		surface,
		count;

	object_3d
		*obj;

	ASSERT ( ( index > OBJECT_3D_INVALID_OBJECT_INDEX ) && ( index < OBJECT_3D_LAST ) );

	ASSERT ( objects_3d_scene_database[index].index );

	obj = &objects_3d_data[ objects_3d_scene_database[index].index ];

	count = 0;

	for ( surface = 0; surface < obj->number_of_surfaces; surface++ )
	{

		if ( !obj->surfaces[surface].polygons )
		{

			count += ( obj->surfaces[surface].number_of_faces * 2 );
		}
	}

	return ( count );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_object_3d_poly_line_data ( object_3d_index_numbers index, vec3d *return_points )
{

	int
		count,
		surface;

	object_3d
		*obj;

	float
		xmax,
		ymax,
		zmax;

	struct POINT_3D_SHORT_REFERENCE
		*refs;

	struct POINT_3D_PLAIN_REFERENCE
		*surface_point_refs;

	ASSERT ( ( index > OBJECT_3D_INVALID_OBJECT_INDEX ) && ( index < OBJECT_3D_LAST ) );
	ASSERT ( objects_3d_scene_database[index].index );
	ASSERT ( return_points );

	obj = &objects_3d_data[ objects_3d_scene_database[index].index ];

	xmax = max ( fabs ( obj->bounding_box.xmin ), fabs ( obj->bounding_box.xmax ) );
	ymax = max ( fabs ( obj->bounding_box.ymin ), fabs ( obj->bounding_box.ymax ) );
	zmax = max ( fabs ( obj->bounding_box.zmin ), fabs ( obj->bounding_box.zmax ) );

	xmax /= 32767.0;
	ymax /= 32767.0;
	zmax /= 32767.0;

	refs = obj->object_faces_point_plain_list;

	surface_point_refs = obj->surface_points;

	count = 0;

	for ( surface = 0; surface < obj->number_of_surfaces; surface++ )
	{

		int
			face_count,
			number_of_surface_faces,
			number_of_surface_points;

		number_of_surface_points = obj->surfaces[surface].number_of_points;

		if ( number_of_surface_points == 0 )
		{

			number_of_surface_points = 256;
		}

		ASSERT ( !obj->surfaces[surface].polygons );

		number_of_surface_faces = obj->surfaces[surface].number_of_faces;

		for ( face_count = 0; face_count < number_of_surface_faces; face_count++ )
		{

			return_points[count].x = ( float ) obj->points[ surface_point_refs[ refs->point ].point ].x * xmax;
			return_points[count].y = ( float ) obj->points[ surface_point_refs[ refs->point ].point ].y * ymax;
			return_points[count].z = ( float ) obj->points[ surface_point_refs[ refs->point ].point ].z * zmax;

			refs++;
			count++;

			return_points[count].x = ( float ) obj->points[ surface_point_refs[ refs->point ].point ].x * xmax;
			return_points[count].y = ( float ) obj->points[ surface_point_refs[ refs->point ].point ].y * ymax;
			return_points[count].z = ( float ) obj->points[ surface_point_refs[ refs->point ].point ].z * zmax;

			refs++;
			count++;
		}

		surface_point_refs += number_of_surface_points;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void get_3d_sub_object_world_viewpoint ( struct OBJECT_3D_SUB_INSTANCE *object, viewpoint *vp )
{

	object_3d_sub_instance
		*this_object,
		*objects[256];

	object_3d_instance
		*main_object;

	int
		count;

	float
		x,
		y,
		z,
		x_scale,
		y_scale,
		z_scale;

	matrix3x3
		attitude;

	count = 0;

	objects[0] = object;

	this_object = object->parent;

	while ( this_object->parent )
	{

		objects[++count] = this_object;

		this_object = this_object->parent;
	}

	main_object = ( object_3d_instance * ) this_object;

	x = main_object->vp.x;
	y = main_object->vp.y;
	z = main_object->vp.z;

	memcpy ( attitude, main_object->vp.attitude, sizeof ( matrix3x3 ) );

	x_scale = main_object->relative_scale.x;
	y_scale = main_object->relative_scale.y;
	z_scale = main_object->relative_scale.z;

	for ( ; count >= 0; count-- )
	{

		float
			sub_x,
			sub_y,
			sub_z;

		matrix3x3
			result_attitude,
			sub_attitude;

		sub_x = objects[count]->relative_position.x * x_scale;
		sub_y = objects[count]->relative_position.y * y_scale;
		sub_z = objects[count]->relative_position.z * z_scale;

		x += ( ( sub_x * attitude[0][0] ) + ( sub_y * attitude[1][0] ) + ( sub_z * attitude[2][0] ) );
		y += ( ( sub_x * attitude[0][1] ) + ( sub_y * attitude[1][1] ) + ( sub_z * attitude[2][1] ) );
		z += ( ( sub_x * attitude[0][2] ) + ( sub_y * attitude[1][2] ) + ( sub_z * attitude[2][2] ) );

		x_scale *= objects[count]->relative_scale.x;
		y_scale *= objects[count]->relative_scale.y;
		z_scale *= objects[count]->relative_scale.z;

		get_3d_transformation_matrix ( sub_attitude, objects[count]->relative_heading, -objects[count]->relative_pitch, -objects[count]->relative_roll );

		multiply_matrix3x3_matrix3x3 ( result_attitude, sub_attitude, attitude );

		memcpy ( attitude, result_attitude, sizeof ( matrix3x3 ) );
	}

	memcpy ( vp->attitude, attitude, sizeof ( matrix3x3 ) );

	vp->x = x;
	vp->y = y;
	vp->z = z;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_number_of_3d_scene_cameras ( object_3d_index_numbers scene_index, object_3d_camera_index_numbers camera_index )
{

	int
		total,
		count;

	total = 0;

	for ( count = 0; count < objects_3d_scene_database[scene_index].number_of_cameras; count++ )
	{

		if ( objects_3d_scene_database[scene_index].cameras[count].camera_name_index == camera_index )
		{

			total++;
		}
	}

	return ( total );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_number_of_3d_object_cameras ( object_3d_instance *object, object_3d_camera_index_numbers camera_index )
{

	int
		total,
		count;

	object_3d_index_numbers
		scene_index;

	scene_index = object->object_number;

	total = 0;

	for ( count = 0; count < objects_3d_scene_database[scene_index].number_of_cameras; count++ )
	{

		if ( objects_3d_scene_database[scene_index].cameras[count].camera_name_index == camera_index )
		{

			total++;
		}
	}

	return ( total );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

object_3d_scene_camera *get_3d_scene_camera ( object_3d_index_numbers scene_index, object_3d_camera_index_numbers camera_index, int camera_depth )
{

	int
		depth,
		count;

	depth = camera_depth;

	for ( count = 0; count < objects_3d_scene_database[scene_index].number_of_cameras; count++ )
	{

		if ( objects_3d_scene_database[scene_index].cameras[count].camera_name_index == camera_index )
		{

			if ( depth == 0 )
			{

				return ( &objects_3d_camera_database[ objects_3d_scene_database[scene_index].cameras[count].camera_index ] );
			}
			else
			{

				depth--;
			}
		}
	}

	return ( NULL );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

object_3d_scene_camera *get_3d_object_camera ( object_3d_instance *object, object_3d_camera_index_numbers camera_index, int camera_depth )
{

	int
		scene_index,
		count,
		depth;

	depth = camera_depth;

	scene_index = object->object_number;

	for ( count = 0; count < objects_3d_scene_database[scene_index].number_of_cameras; count++ )
	{

		if ( objects_3d_scene_database[scene_index].cameras[count].camera_name_index == camera_index )
		{

			if ( depth == 0 )
			{
	
				return ( &objects_3d_camera_database[ objects_3d_scene_database[scene_index].cameras[count].camera_index ] );
			}
			else
			{

				depth--;
			}
		}
	}

	return ( NULL );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float get_object_3d_camera_lifetime ( object_3d_instance *obj, object_3d_camera_index_numbers camera_index, int camera_depth )
{

	object_3d_scene_camera
		*camera;

	//
	// Get the camera
	//

	camera = get_3d_object_camera ( obj, camera_index, camera_depth );

	if ( camera )
	{

		int
			last_keyframe,
			last_keyframe_index;

		last_keyframe = camera->number_of_keyframes - 1;

		last_keyframe_index = camera->keyframes[last_keyframe].index;

		return ( ( ( float ) last_keyframe_index ) / 30.0 );
	}
	else
	{

		return ( 0.0 );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int get_object_3d_camera_position ( object_3d_instance *obj, object_3d_camera_index_numbers camera_index, int camera_depth, float t, viewpoint *vp )
{

	object_3d_scene_camera
		*camera;

	//
	// Get the camera
	//

	camera = get_3d_object_camera ( obj, camera_index, camera_depth );

	if ( !camera )
	{

		return ( FALSE );
	}

	if ( camera )
	{

		object_3d_sub_object_keyframe
			keyframe;

		vec3d
			relative_position;

		matrix3x3
			attitude;

		float
			heading,
			pitch,
			roll;

		float
			object_heading,
			object_pitch,
			object_roll;

		matrix3x3
			new_object_attitude;

		//
		// Query the keyframe we want
		//

		calculate_keyframe ( camera->number_of_keyframes, camera->keyframes, &keyframe, t );

		relative_position.x = keyframe.x;
		relative_position.y = keyframe.y;
		relative_position.z = keyframe.z;

		//
		// Lock the angles if we have to
		//

		object_heading = get_heading_from_attitude_matrix ( obj->vp.attitude );
		object_pitch = get_pitch_from_attitude_matrix ( obj->vp.attitude );
		object_roll = get_roll_from_attitude_matrix ( obj->vp.attitude );

		if ( camera->heading_locked ) object_heading = 0;
		if ( camera->pitch_locked ) object_pitch = 0;
		if ( camera->roll_locked ) object_roll = 0;

		get_3d_transformation_matrix ( new_object_attitude, object_heading, object_pitch, object_roll );

		//
		// Now calculate the relative camera position
		//

//		multiply_matrix3x3_vec3d ( &vp->position, obj->vp.attitude, &relative_position );
		multiply_matrix3x3_vec3d ( &vp->position, new_object_attitude, &relative_position );

		vp->position.x += obj->vp.x;
		vp->position.y += obj->vp.y;
		vp->position.z += obj->vp.z;
	
		heading = keyframe.heading;
		pitch = keyframe.pitch;
		roll = keyframe.roll;

		if ( camera->target_sub_object_id != -1 )
		{

			object_3d_sub_object_search_data
				search;

			viewpoint
				sub_object_viewpoint;

			search.search_object = obj;
			search.search_depth = 0;
			search.sub_object_index = camera->target_sub_object_id;

			if ( find_object_3d_sub_object ( &search ) == SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND )
			{

				vec3d
					view_vector;

				get_3d_sub_object_world_viewpoint ( search.result_sub_object, &sub_object_viewpoint );

				//
				// Strike a vector between camera & sub object.
				//

				view_vector.x = sub_object_viewpoint.x - vp->position.x;
				view_vector.y = sub_object_viewpoint.y - vp->position.y;
				view_vector.z = sub_object_viewpoint.z - vp->position.z;

				normalise_any_3d_vector ( &view_vector );

				get_matrix3x3_from_unit_vec3d_and_roll ( vp->attitude, &view_vector, roll );

				return ( TRUE );
			}
			else
			{

				return ( FALSE );
			}
		}
		else
		{

			get_3d_transformation_matrix ( attitude, heading, -pitch, -roll );
	
			multiply_matrix3x3_matrix3x3 ( vp->attitude, attitude, new_object_attitude );	//obj->vp.attitude );
	
			return ( TRUE );
		}
	}
	else
	{

		return ( FALSE );
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void report_all_3d_objects_statistics ( void )
{

	int
		count;


	int
		scene_approximation_triangles[64],
		scene_approximation_points[64],
		scene_approximation_objects[64],
		scene_approximation_distances[64];

	for ( count = OBJECT_3D_INVALID_OBJECT_INDEX; count < OBJECT_3D_LAST; count++ )
	{

		int
			current_triangles,
			current_points,
			current_objects,
			current_approximation,
			object_index;

		float
			distance;

		debug_log ( "Object %s", object_3d_enumeration_names[count] );

		memset ( scene_approximation_triangles, 0, ( sizeof ( int ) * 64 ) );
		memset ( scene_approximation_points, 0, ( sizeof ( int ) * 64 ) );
		memset ( scene_approximation_objects, 0, ( sizeof ( int ) * 64 ) );
		memset ( scene_approximation_distances, 0, ( sizeof ( float ) * 64 ) );

		distance = 0;

		for ( current_approximation = 0; current_approximation <= objects_3d_scene_database[count].number_of_approximations; current_approximation++ )
		{
	
			current_triangles = 0;
			current_points = 0;
			current_objects = 0;

			if ( current_approximation == 0 )
			{

				object_index = objects_3d_scene_database[count].index;
			}
			else
			{

				object_index = objects_3d_scene_database[count].approximations[current_approximation - 1].object_number;
			}
	
			current_objects++;
	
			if ( object_index > 0 )
			{
	
				current_triangles += objects_3d_data[object_index].number_of_faces;
	
				current_points += objects_3d_data[object_index].number_of_points;
			}
			else if ( object_index < 0 )
			{

				debug_log ( "Negative approximation error in scene: %s", object_3d_enumeration_names[count] );
			}

			if ( objects_3d_scene_database[count].number_of_sub_objects )
			{

				int
					sub_object_index;

				for ( sub_object_index = 0; sub_object_index < objects_3d_scene_database[count].number_of_sub_objects; sub_object_index++ )
				{

					if ( objects_3d_scene_database[count].sub_objects[sub_object_index].default_visibility )
					{
	
						count_sub_object_statistics ( &objects_3d_scene_database[count].sub_objects[sub_object_index],
																	current_approximation + 1,
																	&current_triangles,
																	&current_points,
																	&current_objects );
					}
				}
			}

			scene_approximation_triangles[current_approximation] = current_triangles;
			scene_approximation_points[current_approximation] = current_points;
			scene_approximation_objects[current_approximation] = current_objects;

			if ( current_approximation == 0 )
			{
	
				debug_log ( "Distance: %f, %d triangles, %d points, %d objects",
										distance,
										scene_approximation_triangles[0],
										scene_approximation_points[0],
										scene_approximation_objects[0] );
			}
			else
			{
	
				debug_log ( "Distance: %f, %d triangles, %d points, %d objects",
										objects_3d_scene_database[count].approximations[current_approximation-1].distance,
										scene_approximation_triangles[current_approximation],
										scene_approximation_points[current_approximation],
										scene_approximation_objects[current_approximation] );
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void count_sub_object_statistics ( object_3d_database_entry *sub_object, int approximation, int *triangles, int *points, int *objects )
{

	if (	( sub_object->sub_object_approximation_in_level <= approximation ) &&
			( sub_object->sub_object_approximation_out_level >= approximation ) )
	{

		int
			object_index;

		( *objects )++;

		object_index = sub_object->index;

		if ( object_index != 0 )
		{

			( *triangles ) += objects_3d_data[object_index].number_of_faces;

			( *points ) += objects_3d_data[object_index].number_of_points;
		}

		if ( sub_object->number_of_sub_objects )
		{

			int
				sub_object_index;

			for ( sub_object_index = 0; sub_object_index < sub_object->number_of_sub_objects; sub_object_index++ )
			{

				if ( sub_object->sub_objects[sub_object_index].default_visibility )
				{
	
					count_sub_object_statistics ( &sub_object->sub_objects[sub_object_index],
																approximation,
																triangles,
																points,
																objects );
				}
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void report_objects_not_destructed ( void )
{

	int
		count;

	for ( count = OBJECT_3D_INVALID_OBJECT_INDEX + 1; count < OBJECT_3D_LAST; count++ )
	{

		if ( object_3d_scenes_creation_count[count] )
		{

			debug_log ( "WARNING: %d instances of %s remain",
								object_3d_scenes_creation_count[count],
								object_3d_enumeration_names[count] );
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

