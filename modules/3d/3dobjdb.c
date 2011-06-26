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

int
	object_3d_scenes_creation_count[OBJECT_3D_LAST];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// XXX: These numbers must be large enough
static int
	custom_number_of_objects = 1000,
	custom_number_of_cameras = 200;

static int
	total_number_of_objects,
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

static int
	sceneid = 0;

static char
	prefix[260];

static int
	fail;


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

static int get_subobject ( FILE *fp );

static int read_object ( object_3d *obj, const char* filename );

static void read_custom_scene ( const char* filename );

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** Gets the first nul terminated string from file and puts it in buf.
 *  Makes sure not to exceed the buf_len, and will NUL-terminate where if the string is truncated
 *  If uppercase is TRUE it will switch all characters in the string to uppercase (useful
 *  for case insensitive filenames)
 */
static int get_nul_string ( char* buf, unsigned buf_len, FILE* file, int uppercase )
{
	int chr;
	unsigned dest = 0;

	while ( chr = fgetc ( file ) )
	{
		if ( chr == EOF )
			return FALSE;

		if ( uppercase )
			chr = toupper ( chr );

		buf[dest] = chr;
		dest++;

		if ( dest >= buf_len )
		{
			buf[buf_len - 1] = '\0';
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

static void read_keyframes ( FILE *fp, int *number_of_keyframes, struct OBJECT_3D_SUB_OBJECT_KEYFRAME **keyframes, int read_number )
{
	int
		keyframe_count;

	if ( read_number )
		fread ( number_of_keyframes, sizeof ( int ), 1, fp );

	ASSERT ( *number_of_keyframes );

	*keyframes = ( struct OBJECT_3D_SUB_OBJECT_KEYFRAME * ) safe_malloc ( sizeof ( struct OBJECT_3D_SUB_OBJECT_KEYFRAME ) * *number_of_keyframes );

	for ( keyframe_count = 0; keyframe_count < *number_of_keyframes; keyframe_count++ )
	{
		fread ( &(*keyframes)[keyframe_count].index, sizeof ( int ), 1, fp );
		fread ( &(*keyframes)[keyframe_count].linear, sizeof ( int ), 1, fp );

		fread ( &(*keyframes)[keyframe_count].x, sizeof ( float ), 1, fp );
		fread ( &(*keyframes)[keyframe_count].y, sizeof ( float ), 1, fp );
		fread ( &(*keyframes)[keyframe_count].z, sizeof ( float ), 1, fp );

		fread ( &(*keyframes)[keyframe_count].heading, sizeof ( float ), 1, fp );
		fread ( &(*keyframes)[keyframe_count].pitch, sizeof ( float ), 1, fp );
		fread ( &(*keyframes)[keyframe_count].roll, sizeof ( float ), 1, fp );

		fread ( &(*keyframes)[keyframe_count].scale_x, sizeof ( float ), 1, fp );
		fread ( &(*keyframes)[keyframe_count].scale_y, sizeof ( float ), 1, fp );
		fread ( &(*keyframes)[keyframe_count].scale_z, sizeof ( float ), 1, fp );

		fread ( &(*keyframes)[keyframe_count].tension, sizeof ( float ), 1, fp );
		fread ( &(*keyframes)[keyframe_count].continuity, sizeof ( float ), 1, fp );
		fread ( &(*keyframes)[keyframe_count].bias, sizeof ( float ), 1, fp );
	}
}

static void read_value_keyframes ( FILE *fp, int *number_of_keyframes, struct OBJECT_3D_SUB_OBJECT_VALUE_KEYFRAME **keyframes )
{
	int
		keyframe_count;

	fread ( number_of_keyframes, sizeof ( int ), 1, fp );

	if ( !*number_of_keyframes )
	{
		*keyframes = NULL;
		return;
	}

	*keyframes = ( struct OBJECT_3D_SUB_OBJECT_VALUE_KEYFRAME * ) safe_malloc ( sizeof ( struct OBJECT_3D_SUB_OBJECT_VALUE_KEYFRAME ) * *number_of_keyframes );

	for ( keyframe_count = 0; keyframe_count < *number_of_keyframes; keyframe_count++ )
	{
		fread ( &(*keyframes)[keyframe_count].index, sizeof ( int ), 1, fp );
		fread ( &(*keyframes)[keyframe_count].linear, sizeof ( int ), 1, fp );

		fread ( &(*keyframes)[keyframe_count].value, sizeof ( float ), 1, fp );
		fread ( &(*keyframes)[keyframe_count].tension, sizeof ( float ), 1, fp );
		fread ( &(*keyframes)[keyframe_count].continuity, sizeof ( float ), 1, fp );
		fread ( &(*keyframes)[keyframe_count].bias, sizeof ( float ), 1, fp );
	}
}

static void read_indices ( FILE *fp, int *number_of_sub_object_indices, object_3d_sub_object_index **sub_object_indices )
{
	int
		index_count;

	fread ( number_of_sub_object_indices, sizeof ( int ), 1, fp );

	if ( !*number_of_sub_object_indices )
	{
		*sub_object_indices = NULL;
		return;
	}

	*sub_object_indices = current_scene_sub_object_index_array;
	current_scene_sub_object_index_array += *number_of_sub_object_indices;

	for ( index_count = 0; index_count < *number_of_sub_object_indices; index_count++ )
	{
		int
			sub_object_index,
			object_index;

		if ( sceneid )
			sub_object_index = get_subobject ( fp );
		else
			fread ( &sub_object_index, sizeof ( int ), 1, fp );
		fread ( &object_index, sizeof ( int ), 1, fp );
		(*sub_object_indices)[index_count].sub_object_index = sub_object_index;
		(*sub_object_indices)[index_count].object_index = object_index;

		if ( index_count != 0 )
		{
			ASSERT ( (*sub_object_indices)[index_count-1].object_index <
					(*sub_object_indices)[index_count].object_index );
		}
	}
}

static void read_subobjects ( FILE *fp, int *number_of_sub_objects, struct OBJECT_3D_DATABASE_ENTRY **sub_objects, struct OBJECT_3D_DATABASE_ENTRY *parent )
{
	int
		sub_object_count;

	fread ( number_of_sub_objects, sizeof ( int ), 1, fp );
	if ( !*number_of_sub_objects )
	{
		*sub_objects = NULL;
		return;
	}

	*sub_objects = current_scene_sub_object_array;
	current_scene_sub_object_array += *number_of_sub_objects;

	for ( sub_object_count = 0; sub_object_count < *number_of_sub_objects; sub_object_count++ )
		initialise_3d_sub_object ( fp, parent, &(*sub_objects)[sub_object_count] );
}

static void read_camera ( FILE *fp, struct OBJECT_3D_SCENE_CAMERA *camera )
{
	if ( sceneid )
		camera->target_sub_object_id = get_subobject ( fp );
	else
	{
		fread ( &camera->number_of_keyframes, sizeof ( int ), 1, fp );
		fread ( &camera->target_sub_object_id, sizeof ( int ), 1, fp );
	}

	fread ( &camera->heading_locked, sizeof ( int ), 1, fp );
	fread ( &camera->pitch_locked, sizeof ( int ), 1, fp );
	fread ( &camera->roll_locked, sizeof ( int ), 1, fp );

	read_keyframes ( fp, &camera->number_of_keyframes, &camera->keyframes, sceneid );
}

#define OBJECT_3D_DECLARATION(x)
#define OBJECT_3D_INDEX(x) #x,
#define OBJECT_3D_INDEX_(x) NULL,
#define OBJECT_3D_SUBINDEX(x)
#define OBJECT_3D_SUBINDEX_(x)
#define OBJECT_3D_CAMERA(x)
#define OBJECT_3D_CAMERA_(x)
#define OBJECT_3D_LIGHT(x)
#define OBJECT_3D_LIGHT_(x)
const char* object_3d_scene_names[] = {
#include "3dmodels.h"
};
#undef OBJECT_3D_DECLARATION
#undef OBJECT_3D_INDEX
#undef OBJECT_3D_INDEX_
#undef OBJECT_3D_SUBINDEX
#undef OBJECT_3D_SUBINDEX_
#undef OBJECT_3D_CAMERA
#undef OBJECT_3D_CAMERA_
#undef OBJECT_3D_LIGHT
#undef OBJECT_3D_LIGHT_

static int get_scene ( const char *filename )
{
	char
		name[1024];
	int
		i;

	strcpy ( name, filename );
	name[strlen ( name ) - 4] = '\0';
	strupr ( name );

	for ( i = 1; object_3d_scene_names[i]; i++ )
		if ( !strcmp ( name, object_3d_scene_names[i] ) )
			return i;

	return 0;
}

static int get_next_object_id ( void )
{
	if ( !custom_number_of_objects )
	{
		debug_fatal ( "Too many custom objects" );
		return 0;
	}

	custom_number_of_objects--;
	return total_number_of_objects++;
}

static int get_object ( FILE *fp )
{
	struct object_history
	{
		char filename[260];
		int object_id;
	};

	static int
		last_scene_id,
		current;
	static struct object_history
		history[1000];

	char
		*ptr,
		*ext,
		filename[260],
		new_filename[260];
	int
		objid = 0;
	int
		i;

	if ( !get_nul_string ( filename, sizeof ( filename ), fp, TRUE ) || !*filename )
		return 0;

	ptr = strrchr ( filename, '/' );
	if ( !ptr )
		ptr = strrchr ( filename, '\\' );
	if ( !ptr )
		ptr = strrchr ( filename, ':' );
	if ( !ptr )
		ptr = filename;
	else
		ptr++;
	strupr ( ptr );

	if ( isxdigit ( ptr[0] ) && isxdigit ( ptr[1] ) &&
		isxdigit ( ptr[2] ) && isxdigit ( ptr[3] ) &&
		strcasecmp(ptr + 4, ".LWO") == 0 &&
		sscanf ( ptr, "%X.LWO", &objid ) == 1 &&
		objid > 0 && objid < total_number_of_raw_3d_objects )
		return objid;

	ext = strrchr ( ptr, '.' );
	if ( ext )
		*ext = '\0';

	if ( sceneid != last_scene_id )
	{
		current = 0;
		last_scene_id = sceneid;
	}

	for ( i = 0; i < current; i++ )
		if ( !strcmp ( history[i].filename, ptr ) )
			return history[i].object_id;

	objid = get_next_object_id();
	if ( !objid )
		return 0;

	if ( current < sizeof ( history ) / sizeof ( *history ) )
	{
		strcpy ( history[current].filename, ptr );
		history[current].object_id = objid;
		current++;
	}

	sprintf ( new_filename, "%s\\%s.EEO", prefix, ptr );
	if ( !read_object ( &objects_3d_data[objid], new_filename ) )
	{
		debug_log ( "failed to load object: %s", new_filename );
		fail = 1;
	}

	return objid;
}


#define OBJECT_3D_DECLARATION(x)
#define OBJECT_3D_INDEX(x)
#define OBJECT_3D_INDEX_(x)
#define OBJECT_3D_SUBINDEX(x) #x,
#define OBJECT_3D_SUBINDEX_(x) NULL,
#define OBJECT_3D_CAMERA(x)
#define OBJECT_3D_CAMERA_(x)
#define OBJECT_3D_LIGHT(x)
#define OBJECT_3D_LIGHT_(x)
const char* object_3d_subobject_names[] = {
	#include "3dmodels.h"
};
#undef OBJECT_3D_DECLARATION
#undef OBJECT_3D_INDEX
#undef OBJECT_3D_INDEX_
#undef OBJECT_3D_SUBINDEX
#undef OBJECT_3D_SUBINDEX_
#undef OBJECT_3D_CAMERA
#undef OBJECT_3D_CAMERA_
#undef OBJECT_3D_LIGHT
#undef OBJECT_3D_LIGHT_

int get_subobject ( FILE *fp )
{
	char
		name[1024];
	int
		i;


	if ( !get_nul_string ( name, sizeof ( name ), fp, TRUE ) || !*name )
		return -1;

	for ( i = 1; object_3d_subobject_names[i]; i++ )
		if ( !strcmp ( name, object_3d_subobject_names[i] ) )
			return i;

	debug_fatal ( "Failed to find subobject '%s'", name );

	return -1;
}

#define OBJECT_3D_DECLARATION(x)
#define OBJECT_3D_INDEX(x)
#define OBJECT_3D_INDEX_(x)
#define OBJECT_3D_SUBINDEX(x)
#define OBJECT_3D_SUBINDEX_(x)
#define OBJECT_3D_CAMERA(x) #x,
#define OBJECT_3D_CAMERA_(x) NULL,
#define OBJECT_3D_LIGHT(x)
#define OBJECT_3D_LIGHT_(x)
static const char
	*cameras[] =
	{
#include "3dmodels.h"
	};
#undef OBJECT_3D_DECLARATION
#undef OBJECT_3D_INDEX
#undef OBJECT_3D_INDEX_
#undef OBJECT_3D_SUBINDEX
#undef OBJECT_3D_SUBINDEX_
#undef OBJECT_3D_CAMERA
#undef OBJECT_3D_CAMERA_
#undef OBJECT_3D_LIGHT
#undef OBJECT_3D_LIGHT_

static int get_camera ( FILE *fp )
{
	char
		name[1024];
	int
		i;

	if ( !get_nul_string ( name, sizeof ( name ), fp, TRUE ) || !*name )
		return 0;

	for ( i = 1; cameras[i]; i++ )
		if ( !strcmp ( name, cameras[i]) )
			return i;

	return 0;
}

static int read_new_camera ( FILE *fp )
{
	ASSERT ( custom_number_of_cameras );

	if ( !custom_number_of_cameras )
		return 0;

	custom_number_of_cameras--;

	read_camera ( fp, &objects_3d_camera_database[total_number_of_cameras] );

	return total_number_of_cameras++;
}

#define OBJECT_3D_DECLARATION(x)
#define OBJECT_3D_INDEX(x)
#define OBJECT_3D_INDEX_(x)
#define OBJECT_3D_SUBINDEX(x)
#define OBJECT_3D_SUBINDEX_(x)
#define OBJECT_3D_CAMERA(x)
#define OBJECT_3D_CAMERA_(x)
#define OBJECT_3D_LIGHT(x) #x,
#define OBJECT_3D_LIGHT_(x) NULL,
static const char
	*lights[] =
	{
#include "3dmodels.h"
	};
#undef OBJECT_3D_DECLARATION
#undef OBJECT_3D_INDEX
#undef OBJECT_3D_INDEX_
#undef OBJECT_3D_SUBINDEX
#undef OBJECT_3D_SUBINDEX_
#undef OBJECT_3D_CAMERA
#undef OBJECT_3D_CAMERA_
#undef OBJECT_3D_LIGHT
#undef OBJECT_3D_LIGHT_

static int get_light ( FILE *fp )
{
	char
		name[1024];
	int
		i;

	if ( !get_nul_string ( name, sizeof ( name ), fp, TRUE ) || !*name )
		return 0;

	for ( i = 1; lights[i]; i++ )
		if ( !strcmp ( name, lights[i] ) )
			return i;

	return 0;
}

static void add_animation (struct OBJECT_3D_SCENE_DATABASE_ENTRY *scene, int *allocated, int animation )
{
	int
		anim,
		*new_anim;

	for ( anim = 0; anim < scene->number_of_texture_animations; anim++ )
	{
		if ( scene->texture_animations[anim] == animation )
		{
			return;
		}
	}

	if ( *allocated == scene->number_of_texture_animations )
	{
		*allocated = *allocated ? *allocated * 2 : 8;
		new_anim = safe_malloc ( *allocated * sizeof ( int ) );
		if ( scene->number_of_texture_animations )
		{
			memcpy ( new_anim, scene->texture_animations, scene->number_of_texture_animations * sizeof ( int ) );
			safe_free ( scene->texture_animations );
		}
		scene->texture_animations = new_anim;
	}
	scene->texture_animations[scene->number_of_texture_animations++] = animation;
}

static void add_animation_object (struct OBJECT_3D_SCENE_DATABASE_ENTRY *scene, int *allocated, int object_id )
{
	struct OBJECT_3D
		*object_3d;
	int
		surface;

	object_3d = &objects_3d_data[object_id];
	for ( surface = 0; surface < object_3d->number_of_surfaces; surface++)
	{
		if ( object_3d->surfaces[surface].texture_animation )
		{
			add_animation ( scene, allocated, object_3d->surfaces[surface].texture_index );
		}
		if ( object_3d->surfaces[surface].luminosity_texture_animation )
		{
			add_animation ( scene, allocated, object_3d->surfaces[surface].luminosity_texture_index );
		}
	}
}

static void read_scene ( FILE *fp, int version )
{
	int
		tmp,
		scene_index,
		number_of_texture_animations,
		approximation,
		number_of_approximations,
		number_of_scene_sub_objects,
		number_of_scene_lights,
		number_of_scene_cameras,
		number_of_scene_links,
		number_of_sprite_lights,
		number_of_ambient_lights,
		number_of_distant_lights,
		number_of_scene_named_sub_objects;

	fail = 0;

	number_of_scene_lights = 0;

	if ( !sceneid )
		for ( tmp = 0; tmp < 16; tmp++ )
		{
			int
				temp;
			fread ( &temp, sizeof ( int ), 1, fp );
			if ( temp != -1 )
				debug_fatal ( "3d objects scene definitions file is corrupted" );
		}

	if ( sceneid )
		scene_index = sceneid;
	else
		fread ( &scene_index, sizeof ( int ), 1, fp );

	if ( ( scene_index <= OBJECT_3D_INVALID_OBJECT_INDEX ) || ( scene_index >= OBJECT_3D_LAST ) )
	{
		debug_fatal ( "Scene index is out of range: %d ( %d to %d allowed )", scene_index, OBJECT_3D_INVALID_OBJECT_INDEX, OBJECT_3D_LAST );
	}

	if ( !sceneid )
		fread ( &objects_3d_scene_database[scene_index].self_shadows, sizeof ( int ), 1, fp );

	//
	// Set the approximation scale to 1.0
	//

	objects_3d_scene_database[scene_index].object_approximation_scale = 1.0;

	//
	// Read in the number of lights
	//

	if ( !sceneid )
		fread ( &number_of_scene_lights, sizeof ( int ), 1, fp );
	else
		number_of_scene_lights = 0;

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

		objects_3d_scene_database[scene_index].cameras = ( struct OBJECT_3D_SCENE_CAMERA_INFO * ) safe_malloc ( sizeof ( struct OBJECT_3D_SCENE_CAMERA_INFO ) * number_of_scene_cameras );

		ASSERT ( objects_3d_scene_database[scene_index].cameras );

		for ( camera_count = 0; camera_count < number_of_scene_cameras; camera_count++ )
		{

			if ( sceneid )
			{
				objects_3d_scene_database[scene_index].cameras[camera_count].camera_name_index = get_camera ( fp );
				objects_3d_scene_database[scene_index].cameras[camera_count].camera_index = read_new_camera ( fp );
			}
			else
			{
				fread ( &objects_3d_scene_database[scene_index].cameras[camera_count].camera_name_index, sizeof ( int ), 1, fp );

				fread ( &objects_3d_scene_database[scene_index].cameras[camera_count].camera_index, sizeof ( int ), 1, fp );
			}
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

	if ( number_of_scene_links )
	{
		struct OBJECT_3D_SCENE_LINK_OBJECT
			*objects_3d_scene_link_ptr;

		objects_3d_scene_link_ptr = ( struct OBJECT_3D_SCENE_LINK_OBJECT * ) safe_malloc ( sizeof ( struct OBJECT_3D_SCENE_LINK_OBJECT ) * number_of_scene_links );
		objects_3d_scene_database[scene_index].scene_link_objects = objects_3d_scene_link_ptr;
		for ( tmp = 0; tmp < number_of_scene_links; tmp++ )
		{
			if ( sceneid )
			{
				char
					name[1024];

				get_nul_string ( name, sizeof ( name ), fp, TRUE );
				objects_3d_scene_link_ptr->scene_index = get_scene ( name );
			}
			else
				fread ( &objects_3d_scene_link_ptr->scene_index, sizeof ( int ), 1, fp );
			fread ( &objects_3d_scene_link_ptr->x, sizeof ( float ), 1, fp );
			fread ( &objects_3d_scene_link_ptr->y, sizeof ( float ), 1, fp );
			fread ( &objects_3d_scene_link_ptr->z, sizeof ( float ), 1, fp );
			fread ( &objects_3d_scene_link_ptr->heading, sizeof ( float ), 1, fp );
			fread ( &objects_3d_scene_link_ptr->pitch, sizeof ( float ), 1, fp );
			fread ( &objects_3d_scene_link_ptr->roll, sizeof ( float ), 1, fp );

			objects_3d_scene_link_ptr++;
		}
	}
	else
		objects_3d_scene_database[scene_index].scene_link_objects = NULL;

	//
	// Read in the sprite lights
	//

	fread ( &number_of_sprite_lights, sizeof ( int ), 1, fp );

	objects_3d_scene_database[scene_index].number_of_sprite_lights = number_of_sprite_lights;

	objects_3d_scene_database[scene_index].sprite_lights = NULL;

	if ( number_of_sprite_lights )
	{
		struct OBJECT_3D_SPRITE_LIGHT
			*objects_3d_scene_sprite_light_ptr;

		objects_3d_scene_sprite_light_ptr = ( struct OBJECT_3D_SPRITE_LIGHT * ) safe_malloc ( sizeof ( struct OBJECT_3D_SPRITE_LIGHT ) * number_of_sprite_lights );
		objects_3d_scene_database[scene_index].sprite_lights = objects_3d_scene_sprite_light_ptr;

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
	}

	//
	// Read in the ambient lights
	//

	if ( version <= -2 )
		fread ( &number_of_ambient_lights, sizeof ( int ), 1, fp );
	else
		number_of_ambient_lights = 0;

	objects_3d_scene_database[scene_index].number_of_ambient_lights = number_of_ambient_lights;

	objects_3d_scene_database[scene_index].ambient_lights = NULL;

	if ( number_of_ambient_lights )
	{
		struct OBJECT_3D_AMBIENT_LIGHT
			*objects_3d_scene_ambient_light_ptr;

		objects_3d_scene_ambient_light_ptr = ( struct OBJECT_3D_AMBIENT_LIGHT * ) safe_malloc ( sizeof ( struct OBJECT_3D_AMBIENT_LIGHT ) * number_of_ambient_lights );
		objects_3d_scene_database[scene_index].ambient_lights = objects_3d_scene_ambient_light_ptr;

		for ( tmp = 0; tmp < number_of_ambient_lights; tmp++ )
		{
			fread ( &objects_3d_scene_ambient_light_ptr->colour.red, sizeof ( float ), 1, fp );
			fread ( &objects_3d_scene_ambient_light_ptr->colour.green, sizeof ( float ), 1, fp );
			fread ( &objects_3d_scene_ambient_light_ptr->colour.blue, sizeof ( float ), 1, fp );

			objects_3d_scene_ambient_light_ptr->light_index = get_light ( fp );

			objects_3d_scene_ambient_light_ptr++;
		}
	}

	//
	// Read in the distant lights
	//

	if ( version <= -2 )
		fread ( &number_of_distant_lights, sizeof ( int ), 1, fp );
	else
		number_of_distant_lights = 0;

	objects_3d_scene_database[scene_index].number_of_distant_lights = number_of_distant_lights;

	objects_3d_scene_database[scene_index].distant_lights = NULL;

	if ( number_of_distant_lights )
	{
		struct OBJECT_3D_DISTANT_LIGHT
			*objects_3d_scene_distant_light_ptr;

		objects_3d_scene_distant_light_ptr = ( struct OBJECT_3D_DISTANT_LIGHT * ) safe_malloc ( sizeof ( struct OBJECT_3D_DISTANT_LIGHT ) * number_of_distant_lights );
		objects_3d_scene_database[scene_index].distant_lights = objects_3d_scene_distant_light_ptr;

		for ( tmp = 0; tmp < number_of_distant_lights; tmp++ )
		{
			fread ( &objects_3d_scene_distant_light_ptr->heading, sizeof ( float ), 1, fp );
			fread ( &objects_3d_scene_distant_light_ptr->pitch, sizeof ( float ), 1, fp );
			fread ( &objects_3d_scene_distant_light_ptr->roll, sizeof ( float ), 1, fp );

			fread ( &objects_3d_scene_distant_light_ptr->colour.red, sizeof ( float ), 1, fp );
			fread ( &objects_3d_scene_distant_light_ptr->colour.green, sizeof ( float ), 1, fp );
			fread ( &objects_3d_scene_distant_light_ptr->colour.blue, sizeof ( float ), 1, fp );

			objects_3d_scene_distant_light_ptr->light_index = get_light ( fp );

			objects_3d_scene_distant_light_ptr++;
		}
	}

	//
	// Read in the number of sub objects, and the number of *named* sub objects
	//

	fread ( &number_of_scene_sub_objects, sizeof ( int ), 1, fp );

	fread ( &number_of_scene_named_sub_objects, sizeof ( int ), 1, fp );

	if ( number_of_scene_named_sub_objects )
		current_scene_sub_object_index_array = ( struct OBJECT_3D_SUB_OBJECT_INDEX * ) safe_malloc ( sizeof ( struct OBJECT_3D_SUB_OBJECT_INDEX ) * number_of_scene_named_sub_objects );
	else
		current_scene_sub_object_index_array = NULL;
	if ( number_of_scene_sub_objects )
		current_scene_sub_object_array = ( struct OBJECT_3D_DATABASE_ENTRY * ) safe_malloc ( sizeof ( struct OBJECT_3D_DATABASE_ENTRY ) * number_of_scene_sub_objects );
	else
		current_scene_sub_object_array = NULL;

	objects_3d_scene_database[scene_index].total_number_of_sub_objects = number_of_scene_sub_objects;
	objects_3d_scene_database[scene_index].total_number_of_sub_object_indices = number_of_scene_named_sub_objects;

	objects_3d_scene_database[scene_index].scene_sub_object_indices_array = current_scene_sub_object_index_array;
	objects_3d_scene_database[scene_index].scene_sub_object_array = current_scene_sub_object_array;

	fread ( &number_of_texture_animations, sizeof ( int ), 1, fp );

	ASSERT ( !sceneid || !number_of_texture_animations );

	objects_3d_scene_database[scene_index].number_of_texture_animations = number_of_texture_animations;

	if ( number_of_texture_animations )
	{
		objects_3d_scene_database[scene_index].texture_animations = ( int * ) safe_malloc ( sizeof ( int ) * number_of_texture_animations );

		for ( tmp = 0; tmp < number_of_texture_animations; tmp++ )
			fread ( &objects_3d_scene_database[scene_index].texture_animations[tmp], sizeof ( int ), 1, fp );
	}
	else
		objects_3d_scene_database[scene_index].texture_animations = NULL;

	fread ( &number_of_approximations, sizeof ( int ), 1, fp );

	if ( sceneid )
		objects_3d_scene_database[scene_index].index = get_object ( fp );
	else
		fread ( &objects_3d_scene_database[scene_index].index, sizeof ( int ), 1, fp );

	ASSERT ( objects_3d_scene_database[scene_index].index >= 0 );
	ASSERT ( objects_3d_scene_database[scene_index].index <= total_number_of_raw_3d_objects );

	objects_3d_scene_database[scene_index].number_of_approximations = number_of_approximations;

	if ( number_of_approximations )
	{
		objects_3d_scene_database[scene_index].approximations = ( struct OBJECT_3D_APPROXIMATION_INFO * ) safe_malloc ( sizeof ( struct OBJECT_3D_APPROXIMATION_INFO ) * objects_3d_scene_database[scene_index].number_of_approximations );
		//
		// Read any approximation information in
		//

		for ( approximation = 0; approximation < number_of_approximations; approximation++ )
		{

			if ( sceneid )
				objects_3d_scene_database[scene_index].approximations[approximation].object_number = get_object ( fp );
			else
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

	ASSERT ( !sceneid || !objects_3d_scene_database[scene_index].shadow_approximation_index );

	//
	// Read in the shadow polygon object index
	//

	if ( sceneid )
		objects_3d_scene_database[scene_index].shadow_polygon_object_index = get_object ( fp );
	else
		fread ( &objects_3d_scene_database[scene_index].shadow_polygon_object_index, sizeof ( int ), 1, fp );
	fread ( &objects_3d_scene_database[scene_index].shadow_polygon_object_scale.x, sizeof ( float ), 1, fp );
	fread ( &objects_3d_scene_database[scene_index].shadow_polygon_object_scale.y, sizeof ( float ), 1, fp );
	fread ( &objects_3d_scene_database[scene_index].shadow_polygon_object_scale.z, sizeof ( float ), 1, fp );

	//
	// Read in the collision object index
	//

	if ( sceneid )
	{
		objects_3d_scene_database[scene_index].collision_object_index = get_object ( fp );
		if ( !objects_3d_scene_database[scene_index].collision_object_index )
			objects_3d_scene_database[scene_index].collision_object_index = -1;
	}
	else
		fread ( &objects_3d_scene_database[scene_index].collision_object_index, sizeof ( int ), 1, fp );

	//
	// Next, read in the keyframes for the main object in the scene.
	//

	read_keyframes ( fp, &objects_3d_scene_database[scene_index].number_of_keyframes, &objects_3d_scene_database[scene_index].keyframes, TRUE );

	//
	// Next the object dissolve for the main object & any keyframes associate with it
	//

	fread ( &objects_3d_scene_database[scene_index].object_dissolve, sizeof ( float ), 1, fp );

	read_value_keyframes ( fp, &objects_3d_scene_database[scene_index].number_of_object_dissolve_keyframes, &objects_3d_scene_database[scene_index].object_dissolve_keyframes );

	//
	// Next read in the object displacement sequence number
	//

	if ( !sceneid )
		fread ( &objects_3d_scene_database[scene_index].displacement_sequence_index, sizeof ( int ), 1, fp );

	read_value_keyframes ( fp, &objects_3d_scene_database[scene_index].number_of_displacement_amplitude_keyframes, &objects_3d_scene_database[scene_index].displacement_amplitude_keyframes );


	//
	// Read in any sub object indices
	//

	read_indices ( fp, &objects_3d_scene_database[scene_index].number_of_sub_object_indices, &objects_3d_scene_database[scene_index].sub_object_indices );

	//
	// Read in any immediate sub objects
	//

	read_subobjects ( fp, &objects_3d_scene_database[scene_index].number_of_sub_objects, &objects_3d_scene_database[scene_index].sub_objects, NULL );

	// Check for animation textures references in the objects of the scene
	if ( sceneid )
	{
		int
			allocated,
			count;

		allocated = 0;

		add_animation_object ( &objects_3d_scene_database[scene_index], &allocated, objects_3d_scene_database[scene_index].index );
		for ( count = 0; count < objects_3d_scene_database[scene_index].number_of_approximations; count++ )
		{
			add_animation_object ( &objects_3d_scene_database[scene_index], &allocated, objects_3d_scene_database[scene_index].approximations[count].object_number );
		}
		for ( count = 0; count < objects_3d_scene_database[scene_index].total_number_of_sub_objects; count++ )
		{
			add_animation_object ( &objects_3d_scene_database[scene_index], &allocated, objects_3d_scene_database[scene_index].sub_objects[count].index );
		}
	}

	initialise_scene_quick_sub_object_search ( scene_index );

	initialise_scene_visible_sub_objects ( scene_index );

	initialise_scene_bounding_sub_objects ( scene_index );


	objects_3d_scene_database[scene_index].succeeded = !fail;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// returns TRUE if all scenes between the parameters (including start and end index) have loaded successfully
static int all_scenes_loaded_successfully(unsigned from_index, unsigned to_index)
{
	unsigned sceneno;

	for (sceneno = from_index; sceneno <= to_index; sceneno++)
		if (!objects_3d_scene_database[sceneno].succeeded)
		{
			debug_log("failed: %s", object_3d_scene_names[sceneno]);
//			ASSERT(FALSE);
			return FALSE;
		}

	return TRUE;
}

static void initialise_custom_scenes(const char* directory)
{
	/* 06FEB08 Casm Import of 3D scenes BEGIN */
	int
		rc = 0;
	long
		handle;
	struct _finddata_t
		di;

	char
		filename[512];

	snprintf ( filename, ARRAY_LENGTH(filename), "%s\\OBJECTS\\*.*", directory );
	for ( rc = handle = _findfirst ( filename, &di ); rc != -1; rc = _findnext ( handle, &di ) )
	{
		int
			rc;
		long
			handle;
		struct _finddata_t
			fi;

		if ( !( di.attrib & _A_SUBDIR ) )
			continue;

		if ( !strcmp ( di.name, "." ) || !strcmp ( di.name, ".." ) )
			continue;

		snprintf ( filename, ARRAY_LENGTH(filename), "%s\\OBJECTS\\%s\\*.EES", directory, di.name );
		for ( rc = handle = _findfirst ( filename, &fi ); rc != -1; rc = _findnext ( handle, &fi ) )
		{
			if ( fi.attrib & _A_SUBDIR )
				continue;

			sceneid = get_scene ( fi.name );
			if ( !sceneid )
				continue;

			snprintf ( prefix, ARRAY_LENGTH(prefix), "%s\\OBJECTS\\%s", directory, di.name );
			snprintf ( filename, ARRAY_LENGTH(filename), "%s\\%s", prefix, fi.name );

			read_custom_scene ( filename );
		}
		_findclose ( handle );
	}

	_findclose ( handle );
	/* 06FEB08 Casm Import of 3D scenes END */

	/** check which custom scenes have loaded correctly **/
	custom_3d_models.arneh_ah64d_cockpit = all_scenes_loaded_successfully(OBJECT_3D_ARNEH_AH64D_COCKPIT, OBJECT_3D_ARNEH_AH64D_INSTRUMENTS_NEEDLES);
	custom_3d_models.arneh_mi24v_cockpit = all_scenes_loaded_successfully(OBJECT_3D_MI24V_PILOT_COCKPIT, OBJECT_3D_MI24V_CANOPY_GLASS_DETAILS);
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

	for (i = 0; i < min(level * 2,127u); i++)
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

void read_custom_scene ( const char* filename )
{
	FILE
		*fp;
	int
		version;

	fp = safe_fopen ( filename, "rb" );
	fread ( &version, sizeof ( int ), 1, fp );
	if ( version <= -1 && version >= -2 )
	{
		read_scene ( fp, version );
	}
	safe_fclose ( fp );
}


int read_object ( object_3d *obj, const char* filename )
{
	FILE
		*file;

	int
		format_version,
		number_of_points,
		number_of_faces,
		number_of_surfaces,
		number_of_texture_points,
		number_of_polygoned_faces,
		number_of_face_normals,
		number_of_point_normals,
		number_of_lighting_normals,
		number_of_point_references,
		number_of_surface_point_references,
		number_of_surface_point_normals;

	file = fopen ( filename, "rb" );
	if ( !file )
		return FALSE;

	debug_log ( "Replacing 3d object %s", filename );

	fread ( &format_version, 4, 1, file );

	if ( format_version < 1 || format_version > 2 )
	{
		debug_log ( "Incompatible object: %s (object version %d)", filename, format_version );
		return FALSE;
	}

	fread ( &number_of_points, 4, 1, file );
	fread ( &number_of_faces, 4, 1, file );
	fread ( &number_of_polygoned_faces, 4, 1, file );
	if (format_version > 1)
		fread ( &number_of_face_normals, 4, 1, file );
	else
		number_of_face_normals = number_of_polygoned_faces;
	fread ( &number_of_surfaces, 4, 1, file );
	fread ( &number_of_point_normals, 4, 1, file );
	fread ( &number_of_lighting_normals, 4, 1, file );
	fread ( &number_of_point_references, 4, 1, file );
	fread ( &number_of_texture_points, 4, 1, file );
	fread ( &number_of_surface_point_references, 4, 1, file );
	fread ( &number_of_surface_point_normals, 4, 1, file );

	obj->number_of_points = number_of_points;
	obj->number_of_faces = number_of_faces;
	obj->number_of_surfaces = number_of_surfaces;
	obj->number_of_point_normals = number_of_point_normals;
	obj->number_of_lighting_normals = number_of_lighting_normals;

	fread ( &obj->bounding_box, 24, 1, file );
	fread ( &obj->bounding_box2, 24, 1, file );
	fread ( &obj->radius, 4, 1, file );

	if ( obj->number_of_points )  // read all points
	{
		obj->points = ( struct OBJECT_SHORT_3D_POINT * ) safe_malloc ( 6 * obj->number_of_points );
		fread ( obj->points, 6, obj->number_of_points, file );
	}
	else
		obj->points = NULL;
	if ( number_of_polygoned_faces )  // number of points in each poly
	{
		obj->faces = ( struct OBJECT_3D_FACE * ) safe_malloc ( 1 * number_of_polygoned_faces );
		fread ( obj->faces, 1, number_of_polygoned_faces, file );
	}
	else
		obj->faces = NULL;
	if ( obj->number_of_point_normals )
	{
		obj->point_normals = ( struct OBJECT_3D_HEADING_PITCH_NORMAL * ) safe_malloc ( 2 * obj->number_of_point_normals );
		fread ( obj->point_normals, 2, obj->number_of_point_normals, file );
	}
	else
		obj->point_normals = NULL;
	if ( number_of_point_references )  // the points of all faces in same order as faces
	{
		obj->object_faces_point_plain_list = ( struct POINT_3D_SHORT_REFERENCE * ) safe_malloc ( 1 * number_of_point_references );
		fread ( obj->object_faces_point_plain_list, 1, number_of_point_references, file );
	}
	else
		obj->object_faces_point_plain_list = NULL;
	if ( obj->number_of_surfaces )
	{
		obj->surfaces = ( struct FACE_SURFACE_DESCRIPTION * ) safe_malloc ( 16 * obj->number_of_surfaces );
		fread ( obj->surfaces, 16, obj->number_of_surfaces, file );
	}
	else
		obj->surfaces = NULL;
	if ( number_of_face_normals )   // read face normals
	{
		obj->object_face_normal_references = ( struct POINT_3D_PLAIN_REFERENCE * ) safe_malloc ( 2 * number_of_face_normals );
		fread ( obj->object_face_normal_references, 2, number_of_face_normals, file );
	}
	else
		obj->object_face_normal_references = NULL;
	if ( number_of_texture_points )
	{
		obj->surface_texture_points = ( struct OBJECT_3D_SHORT_TEXTURED_POINT * ) safe_malloc ( 8 * number_of_texture_points );
		fread ( obj->surface_texture_points, 8, number_of_texture_points, file );
	}
	else
		obj->surface_texture_points = NULL;
	if ( number_of_surface_point_references )
	{
		obj->surface_points = ( struct POINT_3D_PLAIN_REFERENCE * ) safe_malloc ( 2 * number_of_surface_point_references );
		fread ( obj->surface_points, 2, number_of_surface_point_references, file );
	}
	else
		obj->surface_points = NULL;
	if ( number_of_surface_point_normals )
	{
		obj->surface_point_normals = ( struct POINT_3D_PLAIN_REFERENCE * ) safe_malloc ( 2 * number_of_surface_point_normals );
		fread ( obj->surface_point_normals, 2, number_of_surface_point_normals, file );
	}
	else
		obj->surface_point_normals = NULL;

	obj->custom = 1;

	// texture overrides
	{
		int
			i;
		char
			texture_name[256];

		for ( i = 0; i < obj->number_of_surfaces; i++ )
		{
			if ( !get_nul_string ( texture_name, sizeof ( texture_name ), file, TRUE ) )
				break;
			if ( *texture_name )
				obj->surfaces[i].texture_index = obj->surfaces[i].texture_animation ? add_new_animation ( texture_name ) : add_new_texture ( texture_name );

			if ( !get_nul_string ( texture_name, sizeof ( texture_name ), file, TRUE ) )
				break;
			if ( *texture_name )
				obj->surfaces[i].luminosity_texture_index = obj->surfaces[i].luminosity_texture_animation ? add_new_animation ( texture_name ) : add_new_texture ( texture_name );
		}
	}

	fclose ( file );

	{
		int
			i;
		for ( i = 0; i < number_of_polygoned_faces; i++ )
		{
			if ( obj->faces[i].number_of_points < 3 )
			{
				ASSERT ( FALSE );
				return FALSE;
			}
		}
		for ( i = 0; i < obj->number_of_surfaces; i++ )
		{
			if ( !obj->surfaces[i].polygons && obj->surfaces[i].smoothed )
			{
				ASSERT ( FALSE );
				return FALSE;
			}
		}
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initialise_3d_objects ( const char *directory )
{

	int
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
	object_database_points = ( struct OBJECT_SHORT_3D_POINT * ) safe_mopen ( filename );

	sprintf ( filename, "%s\\3dobjs.sp", directory );
	object_database_surface_point_list = ( struct POINT_3D_PLAIN_REFERENCE * ) safe_mopen ( filename );

	sprintf ( filename, "%s\\3dobjs.spn", directory );
	object_database_surface_point_normal_list = ( struct POINT_3D_PLAIN_REFERENCE * ) safe_mopen ( filename );

	sprintf ( filename, "%s\\3dobjs.spt", directory );
	object_database_surface_point_texture_list = ( struct OBJECT_3D_SHORT_TEXTURED_POINT * ) safe_mopen ( filename );

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

#if REPORT_OBJECT_STATS
	debug_log ( "THERE ARE %d 3D OBJECT SHAPES", total_number_of_objects );
#endif

	total_number_of_raw_3d_objects = total_number_of_objects + custom_number_of_objects;

	objects_3d_data = ( struct OBJECT_3D * ) safe_malloc ( ( total_number_of_raw_3d_objects + 1 ) * sizeof ( struct OBJECT_3D ) );
	memset ( objects_3d_data, 0, ( total_number_of_raw_3d_objects + 1 ) * sizeof ( struct OBJECT_3D ) );

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

		object_database_faces = ( struct OBJECT_3D_FACE * ) safe_malloc ( sizeof ( object_3d_face ) * total_number_of_polygons );
	}

	if ( total_number_of_point_normals )
	{

		object_database_point_normals = ( struct OBJECT_3D_HEADING_PITCH_NORMAL * ) safe_malloc ( sizeof ( object_3d_heading_pitch_normal ) * total_number_of_point_normals );
	}

	if ( total_number_of_surfaces )
	{

		object_database_surfaces = ( struct FACE_SURFACE_DESCRIPTION * ) safe_malloc ( sizeof ( face_surface_description ) * total_number_of_surfaces );
	}

	if ( total_number_of_plain_points )
	{

		object_database_faces_point_list = ( struct POINT_3D_SHORT_REFERENCE * ) safe_malloc ( sizeof ( point_3d_short_reference ) * total_number_of_plain_points );
	}

	if ( total_number_of_face_normal_points )
	{

		object_database_faces_face_normal_list = ( struct POINT_3D_PLAIN_REFERENCE * ) safe_malloc ( sizeof ( point_3d_plain_reference ) * total_number_of_face_normal_points );
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

			if ( number_of_real_polygons )
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

		sprintf ( filename, "%s\\OBJECTS\\????.EEO", directory );
		for ( rc = handle = _findfirst ( filename, &fi ); rc != -1; rc = _findnext ( handle, &fi ) )
		{
			int
				objid;

			if ( fi.attrib & _A_SUBDIR )
				continue;

			if ( !isxdigit ( fi.name[0] ) || !isxdigit ( fi.name[1] ) ||
				 !isxdigit ( fi.name[2] ) || !isxdigit ( fi.name[3] ) )
				continue;

			objid = strtol ( fi.name, NULL, 16 );
			if ( objid <= 0 || objid > total_number_of_objects )
				continue;

			sprintf ( filename, "%s\\OBJECTS\\%s", directory, fi.name );
			read_object ( &objects_3d_data[objid], filename );
		}
		_findclose ( handle );
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

	objects_3d_scene_database = ( struct OBJECT_3D_SCENE_DATABASE_ENTRY * ) safe_malloc ( sizeof ( struct OBJECT_3D_SCENE_DATABASE_ENTRY ) * OBJECT_3D_LAST );

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


	// read in all the default scenes
	for ( count = 0; count < total_number_of_scenes; count++ )
		read_scene ( fp, 0 );

	//
	// Read in the camera information
	//

	fread ( &total_number_of_cameras, sizeof ( int ), 1, fp );

	fread ( &total_number_of_camera_keyframes, sizeof ( int ), 1, fp );

	if ( total_number_of_cameras )
	{
		objects_3d_camera_database = ( struct OBJECT_3D_SCENE_CAMERA * ) safe_malloc ( sizeof ( struct OBJECT_3D_SCENE_CAMERA ) * ( total_number_of_cameras + custom_number_of_cameras ) );

		for ( count = 0; count < total_number_of_cameras; count++ )
			read_camera ( fp, &objects_3d_camera_database[count] );
	}

	fclose ( fp );

	initialise_custom_scenes(directory);

	{
		// reallocates surfaces memory

		struct FACE_SURFACE_DESCRIPTION
			*surfaces,
			*cursurface;
		int
			number_of_surfaces = 0;

		for ( count = 1; count <= total_number_of_objects; count++ )
			number_of_surfaces += objects_3d_data[count].number_of_surfaces;
		surfaces = ( face_surface_description * ) safe_malloc ( sizeof ( face_surface_description ) * number_of_surfaces );
		cursurface = surfaces;
		for ( count = 1; count <= total_number_of_objects; count++ )
		{
			object_3d *obj = &objects_3d_data[count];

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
		sub_object_approximation_out_level;

	sub_object->parent = parent;

	if ( sceneid )
		index = get_object ( fp );
	else
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

	{
		int
			number_of_keyframes;

		read_keyframes ( fp, &number_of_keyframes, &sub_object->keyframes, TRUE );
		sub_object->number_of_keyframes = number_of_keyframes;
	}

	//
	// Next the object dissolve for the sub object & any keyframes associate with it
	//

	{
		int
			number_of_object_dissolve_keyframes;

		fread ( &sub_object->object_dissolve, sizeof ( float ), 1, fp );
		read_value_keyframes ( fp, &number_of_object_dissolve_keyframes, &sub_object->object_dissolve_keyframes );
		sub_object->number_of_object_dissolve_keyframes = number_of_object_dissolve_keyframes;
	}

	//
	// Now the sub objects
	//

	{
		int
			number_of_sub_object_indices;

		read_indices ( fp, &number_of_sub_object_indices, &sub_object->sub_object_indices );
		sub_object->number_of_sub_object_indices = number_of_sub_object_indices;
	}

	{
		int
			number_of_sub_objects;

		read_subobjects ( fp, &number_of_sub_objects, &sub_object->sub_objects, sub_object );
		sub_object->number_of_sub_objects = number_of_sub_objects;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deinitialise_3d_objects ( void )
{
	int
		i;

	//
	// Deinitialise the d3d versions first
	//

	deinitialise_3d_objects_in_d3d ();

	for ( i = 0; i < total_number_of_objects; i++ )
	{
		if ( objects_3d_scene_database[i].texture_animations )
			safe_free ( objects_3d_scene_database[i].texture_animations );
		if ( objects_3d_scene_database[i].approximations )
			safe_free ( objects_3d_scene_database[i].approximations );
		if ( objects_3d_scene_database[i].cameras )
			safe_free ( objects_3d_scene_database[i].cameras );
		if ( objects_3d_scene_database[i].scene_link_objects )
			safe_free ( objects_3d_scene_database[i].scene_link_objects );
		if ( objects_3d_scene_database[i].sprite_lights )
			safe_free ( objects_3d_scene_database[i].sprite_lights );
		if ( objects_3d_scene_database[i].keyframes )
			safe_free ( objects_3d_scene_database[i].keyframes );
		if ( objects_3d_scene_database[i].object_dissolve_keyframes )
			safe_free ( objects_3d_scene_database[i].object_dissolve_keyframes );
		if ( objects_3d_scene_database[i].displacement_amplitude_keyframes )
			safe_free ( objects_3d_scene_database[i].displacement_amplitude_keyframes );
		if ( objects_3d_scene_database[i].scene_sub_object_indices_array )
			safe_free ( objects_3d_scene_database[i].scene_sub_object_indices_array );
		if ( objects_3d_scene_database[i].sub_objects )
			safe_free ( objects_3d_scene_database[i].scene_sub_object_array );
	}

	//
	// Free up the scene array itself
	//

	safe_free ( objects_3d_scene_database );

	objects_3d_scene_database = NULL;

	for ( i = 0; i < total_number_of_cameras; i++ )
	{
		if ( objects_3d_camera_database[i].keyframes )
			safe_free ( objects_3d_camera_database[i].keyframes );
	}

	//
	// Free up the cameras
	//

	if ( objects_3d_camera_database )
	{

		safe_free ( objects_3d_camera_database );

		objects_3d_camera_database = NULL;
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

		object_3d_sub_instance_construction_array = ( object_3d_sub_instance * ) safe_malloc ( sizeof ( object_3d_sub_instance ) * objects_3d_scene_database[index].total_number_of_sub_objects );
	}

	object = ( object_3d_instance * ) safe_malloc ( sizeof ( object_3d_instance ) );

	object->object_number = index;

	found = FALSE;

	count = index;

	object->parent = NULL;

	if ( objects_3d_scene_database[count].number_of_texture_animations )
	{

		object->texture_animations = ( int * ) malloc_fast_mem ( sizeof ( int ) * objects_3d_scene_database[count].number_of_texture_animations );

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

		sub_objects[temp].relative_heading = source_objects[temp].keyframes[0].heading;
		sub_objects[temp].relative_pitch = source_objects[temp].keyframes[0].pitch;
		sub_objects[temp].relative_roll = source_objects[temp].keyframes[0].roll;

		sub_objects[temp].relative_position.x = source_objects[temp].keyframes[0].x;
		sub_objects[temp].relative_position.y = source_objects[temp].keyframes[0].y;
		sub_objects[temp].relative_position.z = source_objects[temp].keyframes[0].z;

		sub_objects[temp].relative_scale.x = source_objects[temp].keyframes[0].scale_x;
		sub_objects[temp].relative_scale.y = source_objects[temp].keyframes[0].scale_y;
		sub_objects[temp].relative_scale.z = source_objects[temp].keyframes[0].scale_z;

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

	if ( ( sub_object->sub_object_approximation_in_level <= approximation ) &&
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
