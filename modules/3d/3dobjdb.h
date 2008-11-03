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

enum
{

	INVALID_SHADING_VALUE,
	NO_SHADING,
	LIGHT_SOURCED,
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#define MAX_OBJECT_3D_APPROXIMATIONS 256

#define MAX_OBJECT_3D_SUB_OBJECT_INDICES 256

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct OBJECT_3D_APPROXIMATION_INFO
{

	int
		object_number;

	float
		distance;
};

typedef struct OBJECT_3D_APPROXIMATION_INFO object_3d_approximation_info;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct OBJECT_3D_SUB_OBJECT_INDEX
{

	unsigned short int
		sub_object_index;

	unsigned short int
		object_index;   /// index into parent object's sub_objects array where the database_entry resides
};

typedef struct OBJECT_3D_SUB_OBJECT_INDEX object_3d_sub_object_index;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct OBJECT_3D_SCENE_CAMERA_INFO
{

	int
		camera_name_index,
		camera_index;
};

typedef struct OBJECT_3D_SCENE_CAMERA_INFO object_3d_scene_camera_info;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct OBJECT_3D_SCENE_CAMERA
{

	int
		target_sub_object_id,
		heading_locked,
		pitch_locked,
		roll_locked,
		number_of_keyframes;

	struct OBJECT_3D_SUB_OBJECT_KEYFRAME
		*keyframes;
};

typedef struct OBJECT_3D_SCENE_CAMERA object_3d_scene_camera;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct OBJECT_3D_SCENE_LINK_OBJECT
{

	int
		scene_index;

	float
		x,
		y,
		z,
		heading,
		pitch,
		roll;
};

typedef struct OBJECT_3D_SCENE_LINK_OBJECT object_3d_scene_link_object;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct OBJECT_3D_SPRITE_LIGHT
{

	vec3d
		position,
		scale;

	real_colour
		colour;
};

typedef struct OBJECT_3D_SPRITE_LIGHT object_3d_sprite_light;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct OBJECT_3D_SCENE_SUB_OBJECT_TABLE_ENTRY
{

	object_3d_sub_object_index_numbers  // typedefed int.  Used for searching for specific sub objects, this is the index we search for
		sub_object_index;

	int
		number_of_sub_objects;

	struct OBJECT_3D_DATABASE_ENTRY   // The sub object itself.  One for each depth (used for detail levels?)
		**sub_objects;
};

typedef struct OBJECT_3D_SCENE_SUB_OBJECT_TABLE_ENTRY object_3d_scene_sub_object_table_entry;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct OBJECT_3D_SCENE_DATABASE_ENTRY
{
	/* used to create object_3d_instance and its object_3d_sub_instance objects,
	 * the instances are the actual objects drawn on screen */


	int
		index,
		self_shadows,
		shadow_polygon_object_index,
		collision_object_index,
		displacement_sequence_index,
		number_of_texture_animations,
		number_of_approximations,
		number_of_cameras,
		number_of_keyframes,
		number_of_object_dissolve_keyframes,
		number_of_displacement_amplitude_keyframes,
		number_of_scene_link_objects,
		number_of_sprite_lights;

	vec3d
		shadow_polygon_object_scale;

	int
		*texture_animations;

	struct OBJECT_3D_APPROXIMATION_INFO
		*approximations;

	struct OBJECT_3D_SCENE_CAMERA_INFO
		*cameras;

	struct OBJECT_3D_SCENE_LINK_OBJECT
		*scene_link_objects;

	struct OBJECT_3D_SPRITE_LIGHT
		*sprite_lights;

	/* Array with pointer to all named subobject types used in the scene
	 * Length of array given by number_of_sub_object_table_entries
	 *
	 * Allocated and initialised (from scene_sub_object_indices_array)
	 * in initialise_scene_quick_sub_object_search()
	 *
	 * Used for finding named subobjects in find_object_3d_sub_object() */
	struct OBJECT_3D_SCENE_SUB_OBJECT_TABLE_ENTRY
		*sub_object_indices_table;

	/** Used for animations.  Animates by interpolating between the various
	 *  key frames
	 *
	 *  Every sub object MUST have at least one keyframe */
	struct OBJECT_3D_SUB_OBJECT_KEYFRAME
		*keyframes;

	struct OBJECT_3D_SUB_OBJECT_VALUE_KEYFRAME
		*object_dissolve_keyframes,
		*displacement_amplitude_keyframes;

	float
		radius;

	struct OBJECT_3D_BOUNDS
		bounding_box,
		bounding_box2;

	int
		shaded,
		shadow_approximation_index,
		number_of_sub_objects,
		number_of_sub_object_indices,
		number_of_sub_object_table_entries,
		total_number_of_sub_objects,
		total_number_of_sub_object_indices;

	float
		object_dissolve;

	float
		object_approximation_scale;

	object_3d_sub_object_index
		*scene_sub_object_indices_array;

	// Unused?
	struct OBJECT_3D_DATABASE_ENTRY
		*scene_sub_object_array;

	object_3d_sub_object_index
		*sub_object_indices;

	/* how to create the objects subobjects.  Length of array is
	 * total_number_of_sub_objects and includes all sub objects in width first
	 * order (i.e. all immediate sub objects first, then all their sub objects etc)
	 *
	 * Is a pointer into a global array of all (sub) objects, although each one
	 * is unique (i.e. used only once for only one parent).  All an object's
	 * sub objects follow the object itself directly */
	struct OBJECT_3D_DATABASE_ENTRY
		*sub_objects;

	int
		succeeded;
};

typedef struct OBJECT_3D_SCENE_DATABASE_ENTRY object_3d_scene_database_entry;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct OBJECT_3D_DATABASE_ENTRY
{

	unsigned short int
		index;

	unsigned char
		number_of_sub_objects,
		number_of_keyframes;

	unsigned char
		number_of_object_dissolve_keyframes,
		sub_object_approximation_in_level,
		sub_object_approximation_out_level;

	unsigned char
		number_of_sub_object_indices:6,
		default_visibility:1,
		collision_contribution:1;

	object_3d_sub_object_index
		*sub_object_indices;

	struct OBJECT_3D_SUB_OBJECT_KEYFRAME
		*keyframes;

	struct OBJECT_3D_SUB_OBJECT_VALUE_KEYFRAME
		*object_dissolve_keyframes;

	float
		object_dissolve,

		// limits for how much this sub object may rotate relative to parent
		relative_heading_minimum,
		relative_heading_maximum,

		relative_pitch_minimum,
		relative_pitch_maximum,

		relative_roll_minimum,
		relative_roll_maximum;

	struct OBJECT_3D_DATABASE_ENTRY
		*parent,
		*sub_objects;
};

typedef struct OBJECT_3D_DATABASE_ENTRY object_3d_database_entry;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum SUB_OBJECT_SEARCH_RESULT_TYPES
{

	SUB_OBJECT_SEARCH_RESULT_INVALID,
	SUB_OBJECT_SEARCH_RESULT_OBJECT_FOUND,
	SUB_OBJECT_SEARCH_RESULT_OBJECT_NOT_FOUND,
	SUB_OBJECT_SEARCH_RESULT_OBJECT_NOT_PRESENT,
};

typedef enum SUB_OBJECT_SEARCH_RESULT_TYPES sub_object_search_result_types;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct OBJECT_3D_SUB_OBJECT_LIMITS
{

	float
		relative_heading_minimum,
		relative_heading_maximum,

		relative_pitch_minimum,
		relative_pitch_maximum,

		relative_roll_minimum,
		relative_roll_maximum;
};

typedef struct OBJECT_3D_SUB_OBJECT_LIMITS object_3d_sub_object_limits;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct OBJECT_3D_SUB_OBJECT_SINGLE_KEYFRAME
{

	float
		x,
		y,
		z,
		heading,
		pitch,
		roll,
		scale_x,
		scale_y,
		scale_z;
};

typedef struct OBJECT_3D_SUB_OBJECT_SINGLE_KEYFRAME object_3d_sub_object_single_keyframe;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct OBJECT_3D_SUB_OBJECT_KEYFRAME
{

	int
		index,
		linear;

	float
		x,
		y,
		z,
		heading,
		pitch,
		roll,
		scale_x,
		scale_y,
		scale_z;

	float
		tension,
		continuity,
		bias;
};

typedef struct OBJECT_3D_SUB_OBJECT_KEYFRAME object_3d_sub_object_keyframe;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct OBJECT_3D_SUB_OBJECT_VALUE_KEYFRAME
{

	int
		index,
		linear;

	float
		value,
		tension,
		continuity,
		bias;
};

typedef struct OBJECT_3D_SUB_OBJECT_VALUE_KEYFRAME object_3d_sub_object_value_keyframe;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct OBJECT_3D_SUB_OBJECT_SEARCH_DATA
{

	struct OBJECT_3D_INSTANCE
		*search_object;

	struct OBJECT_3D_SUB_INSTANCE
		*result_sub_object;

	int
		search_depth;

	object_3d_sub_object_index_numbers
		sub_object_index;

	struct OBJECT_3D_DATABASE_ENTRY
		*object_scene;

	float
		relative_heading_initial,
		relative_heading_minimum,
		relative_heading_maximum,

		relative_pitch_initial,
		relative_pitch_minimum,
		relative_pitch_maximum,

		relative_roll_initial,
		relative_roll_minimum,
		relative_roll_maximum;
};

typedef struct OBJECT_3D_SUB_OBJECT_SEARCH_DATA object_3d_sub_object_search_data;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern object_3d_scene_database_entry
	*objects_3d_scene_database;

extern struct OBJECT_3D
	*objects_3d_data;

extern struct FACE_SURFACE_DESCRIPTION
	*object_database_surfaces;

extern int
	total_number_of_raw_3d_objects;

extern int
	current_number_of_3d_objects_constructed,
	current_amount_of_3d_objects_memory;

extern const char* object_3d_scene_names[];
extern const char* object_3d_subobject_names[];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void initialise_3d_objects ( const char *directory );

extern void deinitialise_3d_objects ( void );

extern int get_3d_objects_initialised ( void );

extern int get_object_approximation_number ( int scene_index, float distance, int *draw_sub_objects );

extern int get_object_shadow_polygon_object ( int scene_index );

extern int get_object_shadow_approximation_number ( int scene_index, float distance, int *draw_sub_objects );

extern int get_object_light_sourcing ( int scene_index );

extern struct OBJECT_3D_INSTANCE * construct_3d_object ( object_3d_index_numbers index );

extern void destruct_3d_object ( struct OBJECT_3D_INSTANCE *object );

extern void scale_object_3d_approximation_distances ( object_3d_index_numbers scene_index, float factor );

extern int get_object_3d_collision_object_geometry_triangle ( object_3d_index_numbers index, vec3d *return_points, int depth );

extern int get_object_3d_number_of_poly_lines ( object_3d_index_numbers index );

extern void get_object_3d_poly_line_data ( object_3d_index_numbers index, vec3d *return_points );

extern void get_3d_sub_object_world_viewpoint ( struct OBJECT_3D_SUB_INSTANCE *object, viewpoint *vp );

extern int get_number_of_3d_scene_cameras ( object_3d_index_numbers scene_index, object_3d_camera_index_numbers camera_index );

extern int get_number_of_3d_object_cameras ( struct OBJECT_3D_INSTANCE *object, object_3d_camera_index_numbers camera_index );

extern object_3d_scene_camera *get_3d_scene_camera ( object_3d_index_numbers scene_index, object_3d_camera_index_numbers camera_index, int camera_depth );

extern object_3d_scene_camera *get_3d_object_camera ( struct OBJECT_3D_INSTANCE *object, object_3d_camera_index_numbers camera_index, int camera_depth );

extern float get_object_3d_camera_lifetime ( struct OBJECT_3D_INSTANCE *obj, object_3d_camera_index_numbers camera_index, int camera_depth );

extern int get_object_3d_camera_position ( struct OBJECT_3D_INSTANCE *obj, object_3d_camera_index_numbers camera_index, int camera_depth, float t, viewpoint *vp );

extern void report_all_3d_objects_statistics ( void );

extern void report_objects_not_destructed ( void );

extern void debug_database_entry(object_3d_database_entry* db_entry, FILE* out, unsigned level);
extern void debug_database_scene(object_3d_scene_database_entry* db_entry, FILE* out);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


