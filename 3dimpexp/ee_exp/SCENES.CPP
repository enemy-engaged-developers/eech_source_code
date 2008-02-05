// This was taken from EE sources

class LwsExport;

// FIXME!!!!!
#define OBJECT_3D_LAST 2762
#define OBJECT_3D_INVALID_SUB_OBJECT_INDEX 0
#define OBJECT_3D_SUB_OBJECT_LAST 285

struct VEC3D
{
 float x, y, z;
};

typedef float matrix3x3[3][3];

struct REAL_COLOUR
{
 union
 {
  struct
  {
   struct { union { unsigned char blue, b; }; };
   struct { union { unsigned char green, g; }; };
   struct { union { unsigned char red, r; }; };
   union { union { unsigned char f, a, fog, alpha; }; };
  };
  unsigned int colour;
 };
};

struct OBJECT_3D_SUB_OBJECT_KEYFRAME
{
 int index, linear;
 float x, y, z, heading, pitch, roll, scale_x, scale_y, scale_z;
 float tension, continuity, bias;
};

struct OBJECT_3D_SUB_OBJECT_VALUE_KEYFRAME
{
 int index, linear;
 float value, tension, continuity, bias;
};

struct OBJECT_3D_SUB_OBJECT_INDEX
{
 unsigned short int sub_object_index;
 unsigned short int object_index;
};

struct OBJECT_3D_DATABASE_ENTRY
{
 unsigned short int index;
 unsigned char number_of_sub_objects, number_of_keyframes;
 unsigned char number_of_object_dissolve_keyframes, sub_object_approximation_in_level, sub_object_approximation_out_level;
 unsigned char number_of_sub_object_indices:6, default_visibility:1, collision_contribution:1;
 struct OBJECT_3D_SUB_OBJECT_INDEX *sub_object_indices;
 struct OBJECT_3D_SUB_OBJECT_KEYFRAME *keyframes;
 struct OBJECT_3D_SUB_OBJECT_VALUE_KEYFRAME *object_dissolve_keyframes;
 int flag;
 float
  object_dissolve,
  relative_heading_minimum,
  relative_heading_maximum,
  relative_pitch_minimum,
  relative_pitch_maximum,
  relative_roll_minimum,
  relative_roll_maximum;

 struct OBJECT_3D_DATABASE_ENTRY *parent, *sub_objects;
};

struct OBJECT_3D_SCENE_SUB_OBJECT_TABLE_ENTRY
{
 int sub_object_index;
 int number_of_sub_objects;
 struct OBJECT_3D_DATABASE_ENTRY **sub_objects;
};

struct OBJECT_3D_SCENE_CAMERA_INFO
{
 int camera_name_index, camera_index;
};

struct OBJECT_3D_SCENE_LINK_OBJECT
{
 int scene_index;
 float x, y, z, heading, pitch, roll;
};

struct OBJECT_3D_SPRITE_LIGHT
{
 struct VEC3D position, scale;
 struct REAL_COLOUR colour;
};

struct OBJECT_3D_APPROXIMATION_INFO
{
 int object_number;
 float distance;
};

struct OBJECT_3D_SCENE_DATABASE_ENTRY
{
 int
  index, // The main object
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

 struct VEC3D shadow_polygon_object_scale;
 int *texture_animations;
 struct OBJECT_3D_APPROXIMATION_INFO *approximations; //Approximation objects for index for different distances
 struct OBJECT_3D_SCENE_CAMERA_INFO *cameras;
 struct OBJECT_3D_SCENE_LINK_OBJECT *scene_link_objects;
 struct OBJECT_3D_SPRITE_LIGHT *sprite_lights;
 struct OBJECT_3D_SCENE_SUB_OBJECT_TABLE_ENTRY *sub_object_indices_table; //Указатели на все sub_objects с данным sub_object_id. Используется для поиска
 struct OBJECT_3D_SUB_OBJECT_KEYFRAME *keyframes;
 struct OBJECT_3D_SUB_OBJECT_VALUE_KEYFRAME *object_dissolve_keyframes, *displacement_amplitude_keyframes;
 float radius;
 struct OBJECT_3D_BOUNDS bounding_box, bounding_box2;

 int
  shaded,
  shadow_approximation_index,
  number_of_sub_objects,
  number_of_sub_object_indices,
  number_of_sub_object_table_entries,
  total_number_of_sub_objects,
  total_number_of_sub_object_indices;

 float object_dissolve;
 float object_approximation_scale;
 struct OBJECT_3D_SUB_OBJECT_INDEX *scene_sub_object_indices_array; //Какая-то хрень, грузится. sub_object_index
 struct OBJECT_3D_DATABASE_ENTRY *scene_sub_object_array;
 struct OBJECT_3D_SUB_OBJECT_INDEX *sub_object_indices;
 struct OBJECT_3D_DATABASE_ENTRY *sub_objects;
};

struct OBJECT_3D_SCENE_CAMERA
{
 int
  target_sub_object_id,
  heading_locked,
  pitch_locked,
  roll_locked,
  number_of_keyframes;
 struct OBJECT_3D_SUB_OBJECT_KEYFRAME *keyframes;
};

class Scenes
{

 private:

struct OBJECT_3D_SCENE_DATABASE_ENTRY *objects_3d_scene_database;

struct OBJECT_3D_SCENE_CAMERA *objects_3d_camera_database;

struct OBJECT_3D_SCENE_LINK_OBJECT *objects_3d_scene_link_array, *objects_3d_scene_link_ptr;

struct OBJECT_3D_SPRITE_LIGHT *objects_3d_scene_sprite_light_array, *objects_3d_scene_sprite_light_ptr;

struct OBJECT_3D_SUB_OBJECT_KEYFRAME *objects_3d_camera_keyframes;

struct OBJECT_3D_SCENE_CAMERA_INFO *objects_3d_camera_info_array, *objects_3d_camera_info_array_ptr;

struct OBJECT_3D_DATABASE_ENTRY *objects_3d_scene_sub_objects_array, *objects_3d_scene_sub_objects_array_ptr;

struct OBJECT_3D_SUB_OBJECT_INDEX *objects_3d_scene_sub_object_indices_array, *objects_3d_scene_sub_object_indices_array_ptr;

struct OBJECT_3D_APPROXIMATION_INFO *objects_3d_scene_approximations_array, *objects_3d_scene_approximations_array_ptr;

int *objects_3d_scene_texture_animations_array, *objects_3d_scene_texture_animations_array_ptr;

struct OBJECT_3D_SUB_OBJECT_KEYFRAME *objects_3d_scene_sub_object_keyframes_array, *objects_3d_scene_sub_object_keyframes_array_ptr;

struct OBJECT_3D_SUB_OBJECT_VALUE_KEYFRAME *objects_3d_scene_sub_object_dissolve_keyframes_array, *objects_3d_scene_sub_object_dissolve_keyframes_array_ptr;

struct OBJECT_3D_SCENE_SUB_OBJECT_TABLE_ENTRY *current_sub_object_table;


int number_of_sub_object_table_entries;
int sub_object_index_count[OBJECT_3D_SUB_OBJECT_LAST];


int
 total_number_of_scenes,
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


struct OBJECT_3D_SUB_OBJECT_INDEX *current_scene_sub_object_index_array;
struct OBJECT_3D_DATABASE_ENTRY *current_scene_sub_object_array;

struct OBJECT_3D_BOUNDS scene_bounds, scene_bounds2, rotated_bounds, rotated_bounds2;
struct VEC3D scene_position;
matrix3x3 scene_rotation;

void get_3d_transformation_matrix(matrix3x3 m, float heading, float pitch, float roll)
{
 float sinh, cosh, sinp, cosp, sinr, cosr, sinrsinh, sinrcosh, cosrsinh, cosrcosh;
 sinh = sin ( heading );
 cosh = cos ( heading );
 sinp = sin ( pitch );
 cosp = cos ( pitch );
 sinr = sin ( roll );
 cosr = cos ( roll );
 sinrsinh = sinr * sinh;
 sinrcosh = sinr * cosh;
 cosrsinh = cosr * sinh;
 cosrcosh = cosr * cosh;
 m[0][0] = cosrcosh + ( sinrsinh * sinp );
 m[0][1] = -sinr * cosp;
 m[0][2] = ( sinrcosh * sinp ) - cosrsinh;
 m[1][0] = sinrcosh - ( cosrsinh * sinp );
 m[1][1] = cosr * cosp;
 m[1][2] = -sinrsinh - ( cosrcosh * sinp );
 m[2][0] = cosp * sinh;
 m[2][1] = sinp;
 m[2][2] = cosp * cosh;
}

int* object_sub_object;


void initialise_3d_sub_object(FILE *fp, struct OBJECT_3D_DATABASE_ENTRY *parent, struct OBJECT_3D_DATABASE_ENTRY *sub_object)
{
 int
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

 fread(&index, sizeof(int), 1, fp);

 if (index < 0)
  index = 0;
// assert(index >= 0);
// assert(index < total_number_of_raw_3d_objects);

 fread(&contributes_to_collisions, sizeof(int), 1, fp);
 fread(&sub_object_approximation_in_level, sizeof(int), 1, fp);
 fread(&sub_object_approximation_out_level, sizeof(int), 1, fp);

 sub_object->index = index;
 sub_object->collision_contribution = contributes_to_collisions;
 sub_object->sub_object_approximation_in_level = sub_object_approximation_in_level;
 sub_object->sub_object_approximation_out_level = sub_object_approximation_out_level;

 fread(&sub_object->flag, sizeof(int), 1, fp);

 if (sub_object->flag)
 {
  fread(&sub_object->relative_heading_maximum, sizeof(float), 1, fp);
  fread(&sub_object->relative_heading_minimum, sizeof(float), 1, fp);
  fread(&sub_object->relative_pitch_maximum, sizeof(float), 1, fp);
  fread(&sub_object->relative_pitch_minimum, sizeof(float), 1, fp);
  fread(&sub_object->relative_roll_maximum, sizeof(float), 1, fp);
  fread(&sub_object->relative_roll_minimum, sizeof(float), 1, fp);
 }
 else
 {
  sub_object->relative_heading_maximum = 0.0;
  sub_object->relative_heading_minimum = 0.0;
  sub_object->relative_pitch_maximum = 0.0;
  sub_object->relative_pitch_minimum = 0.0;
  sub_object->relative_roll_maximum = 0.0;
  sub_object->relative_roll_minimum = 0.0;
 }

 fread(&number_of_keyframes, sizeof(int), 1, fp);

 assert(number_of_keyframes);

 sub_object->number_of_keyframes = number_of_keyframes;

 sub_object->keyframes = objects_3d_scene_sub_object_keyframes_array_ptr;

 objects_3d_scene_sub_object_keyframes_array_ptr += number_of_keyframes;

 assert(sub_object->keyframes);

 for (keyframe_count = 0; keyframe_count < number_of_keyframes; keyframe_count++)
 {

  fread(&sub_object->keyframes[keyframe_count].index, sizeof(int), 1, fp);
  fread(&sub_object->keyframes[keyframe_count].linear, sizeof(int), 1, fp);
  fread(&sub_object->keyframes[keyframe_count].x, sizeof(float), 1, fp);
  fread(&sub_object->keyframes[keyframe_count].y, sizeof(float), 1, fp);
  fread(&sub_object->keyframes[keyframe_count].z, sizeof(float), 1, fp);
  fread(&sub_object->keyframes[keyframe_count].heading, sizeof(float), 1, fp);
  fread(&sub_object->keyframes[keyframe_count].pitch, sizeof(float), 1, fp);
  fread(&sub_object->keyframes[keyframe_count].roll, sizeof(float), 1, fp);
  fread(&sub_object->keyframes[keyframe_count].scale_x, sizeof(float), 1, fp);
  fread(&sub_object->keyframes[keyframe_count].scale_y, sizeof(float), 1, fp);
  fread(&sub_object->keyframes[keyframe_count].scale_z, sizeof(float), 1, fp);
  fread(&sub_object->keyframes[keyframe_count].tension, sizeof(float), 1, fp);
  fread(&sub_object->keyframes[keyframe_count].continuity, sizeof(float), 1, fp);
  fread(&sub_object->keyframes[keyframe_count].bias, sizeof(float), 1, fp);
 }

 //
 // Next the object dissolve for the sub object & any keyframes associate with it
 //

 fread(&sub_object->object_dissolve, sizeof(float), 1, fp);

 fread(&number_of_object_dissolve_keyframes, sizeof(int), 1, fp);

 sub_object->number_of_object_dissolve_keyframes = number_of_object_dissolve_keyframes;

 sub_object->object_dissolve_keyframes = objects_3d_scene_sub_object_dissolve_keyframes_array_ptr;

 objects_3d_scene_sub_object_dissolve_keyframes_array_ptr += sub_object->number_of_object_dissolve_keyframes;

 for (keyframe_count = 0; keyframe_count < sub_object->number_of_object_dissolve_keyframes; keyframe_count++)
 {

  fread(&sub_object->object_dissolve_keyframes[keyframe_count].index, sizeof(int), 1, fp);
  fread(&sub_object->object_dissolve_keyframes[keyframe_count].linear, sizeof(int), 1, fp);

  fread(&sub_object->object_dissolve_keyframes[keyframe_count].value, sizeof(float), 1, fp);
  fread(&sub_object->object_dissolve_keyframes[keyframe_count].tension, sizeof(int), 1, fp);
  fread(&sub_object->object_dissolve_keyframes[keyframe_count].continuity, sizeof(int), 1, fp);
  fread(&sub_object->object_dissolve_keyframes[keyframe_count].bias, sizeof(int), 1, fp);
 }

 //
 // Now the sub objects
 //

 fread(&number_of_sub_object_indices, sizeof(int), 1, fp);
 sub_object->number_of_sub_object_indices = number_of_sub_object_indices;

 if (number_of_sub_object_indices)
 {

  int
   index_count;

  //
  // Alloocate the array
  //

  sub_object->sub_object_indices = current_scene_sub_object_index_array;

  current_scene_sub_object_index_array += sub_object->number_of_sub_object_indices;

  assert(sub_object->sub_object_indices);

  for (index_count = 0; index_count < sub_object->number_of_sub_object_indices; index_count++)
  {
   int sub_object_index, object_index;

   fread(&sub_object_index, sizeof(int), 1, fp);
   fread(&object_index, sizeof(int), 1, fp);
   sub_object->sub_object_indices[index_count].sub_object_index = sub_object_index;
   sub_object->sub_object_indices[index_count].object_index = object_index;
  }
 }

 fread(&number_of_sub_objects, sizeof(int), 1, fp);
 sub_object->number_of_sub_objects = number_of_sub_objects;

 if (number_of_sub_objects)
 {
  struct OBJECT_3D_DATABASE_ENTRY *sub_objects;
  int sub_object_count, sub_object_total;


  sub_object_total = sub_object->number_of_sub_objects;

  sub_objects = current_scene_sub_object_array;

  current_scene_sub_object_array += sub_object_total;

  sub_object->sub_objects = sub_objects;

  for (sub_object_count = 0; sub_object_count < sub_object_total; sub_object_count++)
   initialise_3d_sub_object(fp, sub_object, &sub_objects[sub_object_count]);
 }
}

void count_named_sub_objects(struct OBJECT_3D_DATABASE_ENTRY *sub_scene)
{
 int count;
 for (count = 0; count < sub_scene->number_of_sub_object_indices; count++)
  sub_object_index_count[sub_scene->sub_object_indices[count].sub_object_index]++;
 for (count = 0; count < sub_scene->number_of_sub_objects; count++)
  count_named_sub_objects(&sub_scene->sub_objects[count]);
}

void add_sub_object_index_to_table(int index, struct OBJECT_3D_DATABASE_ENTRY *object)
{
 int count;
 for (count = 0; count < number_of_sub_object_table_entries; count++)
 {
  if (current_sub_object_table[count].sub_object_index == index)
  {
   int offset;
   offset = current_sub_object_table[count].number_of_sub_objects;
   current_sub_object_table[count].sub_objects[offset] = object;
   current_sub_object_table[count].number_of_sub_objects++;
   return;
  }
 }
 error("Unable to find sub object index in table");
}

void populate_table_with_named_sub_objects(struct OBJECT_3D_DATABASE_ENTRY *object)
{
 int count;
 for (count = 0; count < object->number_of_sub_object_indices; count++)
 {
  int index;
  int offset;
  struct OBJECT_3D_DATABASE_ENTRY *sub_object;
  index = object->sub_object_indices[count].sub_object_index;
  offset = object->sub_object_indices[count].object_index;
  sub_object = &object->sub_objects[offset];
  add_sub_object_index_to_table(index, sub_object);
 }

 for (count = 0; count < object->number_of_sub_objects; count++)
  populate_table_with_named_sub_objects(&object->sub_objects[count]);
}

void initialise_scene_quick_sub_object_search(int scene_index)
{
 int index;
 int count, total_sub_object_indices, number_of_unique_indices;

 //
 // Set the sub object index array to 0
 //

 for (index = OBJECT_3D_INVALID_SUB_OBJECT_INDEX; index < OBJECT_3D_SUB_OBJECT_LAST; index++)
  sub_object_index_count[index] = 0;

 //
 // Go through all the objects in the scene counting the sub object indices
 //

 for (count = 0; count < objects_3d_scene_database[scene_index].number_of_sub_object_indices; count++)
  sub_object_index_count[ objects_3d_scene_database[scene_index].scene_sub_object_indices_array[count].sub_object_index ]++;

 //
 // Recurse down through any sub objects
 //

 for (count = 0; count < objects_3d_scene_database[scene_index].number_of_sub_objects; count++)
  count_named_sub_objects(&objects_3d_scene_database[scene_index].sub_objects[count]);

 //
 // Count up the total number of named sub objects
 //

 total_sub_object_indices = 0;
 number_of_unique_indices = 0;
 for (index = OBJECT_3D_INVALID_SUB_OBJECT_INDEX; index < OBJECT_3D_SUB_OBJECT_LAST; index++)
 {
  total_sub_object_indices += sub_object_index_count[index];
  if (sub_object_index_count[index])
   number_of_unique_indices++;
 }

 //
 // We should already have the total number, so check here
 //

 assert(total_sub_object_indices == objects_3d_scene_database[scene_index].total_number_of_sub_object_indices);

 if (number_of_unique_indices)
 {
  struct OBJECT_3D_DATABASE_ENTRY **sub_object_table_entries, **sub_object_entry_ptr;
  int table_index;

  number_of_sub_object_table_entries = number_of_unique_indices;

  //
  // Allocate memory for the table
  //

  current_sub_object_table = new OBJECT_3D_SCENE_SUB_OBJECT_TABLE_ENTRY[number_of_unique_indices];
  assert(current_sub_object_table);

  //
  // Record the data in the scene
  //

  objects_3d_scene_database[scene_index].sub_object_indices_table = current_sub_object_table;
  objects_3d_scene_database[scene_index].number_of_sub_object_table_entries = number_of_unique_indices;

  //
  // Allocate memory for the entries in the table
  //

  sub_object_table_entries = new OBJECT_3D_DATABASE_ENTRY *[total_sub_object_indices];

  //
  // Go through initialising the table
  //

  sub_object_entry_ptr = sub_object_table_entries;

  table_index = 0;
  for (index = OBJECT_3D_INVALID_SUB_OBJECT_INDEX; index < OBJECT_3D_SUB_OBJECT_LAST; index++)
  {
   if (sub_object_index_count[index] != 0)
   {
    current_sub_object_table[table_index].sub_object_index = index;
    current_sub_object_table[table_index].number_of_sub_objects = 0;
    current_sub_object_table[table_index].sub_objects = sub_object_entry_ptr;
    sub_object_entry_ptr += sub_object_index_count[index];
    table_index++;
   }
  }

  //
  // Now go through populating the table with the first level named sub objects
  //

  for (count = 0; count < objects_3d_scene_database[scene_index].number_of_sub_object_indices; count++)
  {
   int offset;
   struct OBJECT_3D_DATABASE_ENTRY *sub_object;
   index = objects_3d_scene_database[scene_index].scene_sub_object_indices_array[count].sub_object_index;
   offset = objects_3d_scene_database[scene_index].scene_sub_object_indices_array[count].object_index;
   sub_object = &objects_3d_scene_database[scene_index].sub_objects[offset];
   add_sub_object_index_to_table(index, sub_object);
  }

  //
  // Now recurse the sub objects doing the same thing
  //

  for (count = 0; count < objects_3d_scene_database[scene_index].number_of_sub_objects; count++)
   populate_table_with_named_sub_objects(&objects_3d_scene_database[scene_index].sub_objects[count]);
 }
}

int recurse_set_scene_sub_object_visibility(struct OBJECT_3D_DATABASE_ENTRY *sub_object )
{
 int count, visibility;
 visibility = 0;
 for (count = 0; count < sub_object->number_of_sub_objects; count++)
  visibility += recurse_set_scene_sub_object_visibility(&sub_object->sub_objects[count]);
 sub_object->default_visibility = (visibility) || (sub_object->index != 0);
 return sub_object->default_visibility;
}

void initialise_scene_visible_sub_objects(int scene_index)
{
 int count;
 for (count = 0; count < objects_3d_scene_database[scene_index].number_of_sub_objects; count++)
  recurse_set_scene_sub_object_visibility(&objects_3d_scene_database[scene_index].sub_objects[count]);
}

void rotate_sub_scene_boundaries(struct OBJECT_3D_BOUNDS *results, const struct OBJECT_3D_BOUNDS *source)
{
 struct VEC3D cube_points[8];
 int count;
 if ( ( source->xmin == 0.0 ) && ( source->xmax == 0.0 ) &&
   ( source->ymin == 0.0 ) && ( source->ymax == 0.0 ) &&
   ( source->zmin == 0.0 ) && ( source->zmax == 0.0 ) )
 {
  results->xmin = 0.0;
  results->xmax = 0.0;
  results->ymin = 0.0;
  results->ymax = 0.0;
  results->zmin = 0.0;
  results->zmax = 0.0;
 }
 else
 {
  cube_points[0].x = source->xmin; cube_points[0].y = source->ymin; cube_points[0].z = source->zmin;
  cube_points[1].x = source->xmin; cube_points[1].y = source->ymin; cube_points[1].z = source->zmax;
  cube_points[2].x = source->xmin; cube_points[2].y = source->ymax; cube_points[2].z = source->zmin;
  cube_points[3].x = source->xmin; cube_points[3].y = source->ymax; cube_points[3].z = source->zmax;
  cube_points[4].x = source->xmax; cube_points[4].y = source->ymin; cube_points[4].z = source->zmin;
  cube_points[5].x = source->xmax; cube_points[5].y = source->ymin; cube_points[5].z = source->zmax;
  cube_points[6].x = source->xmax; cube_points[6].y = source->ymax; cube_points[6].z = source->zmin;
  cube_points[7].x = source->xmax; cube_points[7].y = source->ymax; cube_points[7].z = source->zmax;

  for ( count = 0; count < 8; count++ )
  {
   float x, y, z;
   x = cube_points[count].x * scene_rotation[0][0] + cube_points[count].y * scene_rotation[1][0] + cube_points[count].z * scene_rotation[2][0];
   y = cube_points[count].x * scene_rotation[0][1] + cube_points[count].y * scene_rotation[1][1] + cube_points[count].z * scene_rotation[2][1];
   z = cube_points[count].x * scene_rotation[0][2] + cube_points[count].y * scene_rotation[1][2] + cube_points[count].z * scene_rotation[2][2];
   cube_points[count].x = x;
   cube_points[count].y = y;
   cube_points[count].z = z;
  }

  results->xmin = cube_points[0].x;
  results->xmax = cube_points[0].x;
  results->ymin = cube_points[0].y;
  results->ymax = cube_points[0].y;
  results->zmin = cube_points[0].z;
  results->zmax = cube_points[0].z;

  for ( count = 1; count < 8; count++ )
  {
   results->xmin = min ( results->xmin, cube_points[count].x );
   results->ymin = min ( results->ymin, cube_points[count].y );
   results->zmin = min ( results->zmin, cube_points[count].z );

   results->xmax = max ( results->xmax, cube_points[count].x );
   results->ymax = max ( results->ymax, cube_points[count].y );
   results->zmax = max ( results->zmax, cube_points[count].z );
  }
 }
}

int contributes_to_collision;
void recurse_initialise_sub_scene_bounding_box(struct OBJECT_3D_DATABASE_ENTRY *sub_object)
{
 struct VEC3D old_scene_position, relative_position;
 matrix3x3 matrix, new_rotation, old_scene_rotation;
 int old_contributes_to_collision, count;

 //
 // Save state variables
 //
 old_scene_position = scene_position;
 old_contributes_to_collision = contributes_to_collision;
 memcpy(old_scene_rotation, scene_rotation, sizeof(matrix3x3));

 //
 // Set the collision flag
 //

 if (!sub_object->collision_contribution)
  contributes_to_collision = 0;

 //
 // Figure out new position
 //

 relative_position.x = ( ( sub_object->keyframes[0].x * scene_rotation[0][0] ) +
         ( sub_object->keyframes[0].y * scene_rotation[1][0] ) +
         ( sub_object->keyframes[0].z * scene_rotation[2][0] ) );
 relative_position.y = ( ( sub_object->keyframes[0].x * scene_rotation[0][1] ) +
         ( sub_object->keyframes[0].y * scene_rotation[1][1] ) +
         ( sub_object->keyframes[0].z * scene_rotation[2][1] ) );
 relative_position.z = ( ( sub_object->keyframes[0].x * scene_rotation[0][2] ) +
         ( sub_object->keyframes[0].y * scene_rotation[1][2] ) +
         ( sub_object->keyframes[0].z * scene_rotation[2][2] ) );

 scene_position.x += relative_position.x;
 scene_position.y += relative_position.y;
 scene_position.z += relative_position.z;

 get_3d_transformation_matrix(matrix, sub_object->keyframes[0].heading, -sub_object->keyframes[0].pitch, -sub_object->keyframes[0].roll);

 new_rotation[0][0] = ( ( matrix[0][0] * scene_rotation[0][0] ) + ( matrix[0][1] * scene_rotation[1][0] ) + ( matrix[0][2] * scene_rotation[2][0] ) );
 new_rotation[0][1] = ( ( matrix[0][0] * scene_rotation[0][1] ) + ( matrix[0][1] * scene_rotation[1][1] ) + ( matrix[0][2] * scene_rotation[2][1] ) );
 new_rotation[0][2] = ( ( matrix[0][0] * scene_rotation[0][2] ) + ( matrix[0][1] * scene_rotation[1][2] ) + ( matrix[0][2] * scene_rotation[2][2] ) );

 new_rotation[1][0] = ( ( matrix[1][0] * scene_rotation[0][0] ) + ( matrix[1][1] * scene_rotation[1][0] ) + ( matrix[1][2] * scene_rotation[2][0] ) );
 new_rotation[1][1] = ( ( matrix[1][0] * scene_rotation[0][1] ) + ( matrix[1][1] * scene_rotation[1][1] ) + ( matrix[1][2] * scene_rotation[2][1] ) );
 new_rotation[1][2] = ( ( matrix[1][0] * scene_rotation[0][2] ) + ( matrix[1][1] * scene_rotation[1][2] ) + ( matrix[1][2] * scene_rotation[2][2] ) );

 new_rotation[2][0] = ( ( matrix[2][0] * scene_rotation[0][0] ) + ( matrix[2][1] * scene_rotation[1][0] ) + ( matrix[2][2] * scene_rotation[2][0] ) );
 new_rotation[2][1] = ( ( matrix[2][0] * scene_rotation[0][1] ) + ( matrix[2][1] * scene_rotation[1][1] ) + ( matrix[2][2] * scene_rotation[2][1] ) );
 new_rotation[2][2] = ( ( matrix[2][0] * scene_rotation[0][2] ) + ( matrix[2][1] * scene_rotation[1][2] ) + ( matrix[2][2] * scene_rotation[2][2] ) );

 memcpy(scene_rotation, new_rotation, sizeof(matrix3x3));

 scene_rotation[0][0] *= sub_object->keyframes[0].scale_x;
 scene_rotation[1][0] *= sub_object->keyframes[0].scale_y;
 scene_rotation[2][0] *= sub_object->keyframes[0].scale_z;

 scene_rotation[0][1] *= sub_object->keyframes[0].scale_x;
 scene_rotation[1][1] *= sub_object->keyframes[0].scale_y;
 scene_rotation[2][1] *= sub_object->keyframes[0].scale_z;

 scene_rotation[0][2] *= sub_object->keyframes[0].scale_x;
 scene_rotation[1][2] *= sub_object->keyframes[0].scale_y;
 scene_rotation[2][2] *= sub_object->keyframes[0].scale_z;

 //
 // Compute the bounding boxes
 //

 rotate_sub_scene_boundaries ( &rotated_bounds, &objects_3d_data[ sub_object->index ].bounding_box );
 rotate_sub_scene_boundaries ( &rotated_bounds2, &objects_3d_data[ sub_object->index ].bounding_box2 );

 rotated_bounds.xmin += scene_position.x;
 rotated_bounds.ymin += scene_position.y;
 rotated_bounds.zmin += scene_position.z;

 rotated_bounds.xmax += scene_position.x;
 rotated_bounds.ymax += scene_position.y;
 rotated_bounds.zmax += scene_position.z;

 scene_bounds.xmin = min ( scene_bounds.xmin, rotated_bounds.xmin );
 scene_bounds.ymin = min ( scene_bounds.ymin, rotated_bounds.ymin );
 scene_bounds.zmin = min ( scene_bounds.zmin, rotated_bounds.zmin );

 scene_bounds.xmax = max ( scene_bounds.xmax, rotated_bounds.xmax );
 scene_bounds.ymax = max ( scene_bounds.ymax, rotated_bounds.ymax );
 scene_bounds.zmax = max ( scene_bounds.zmax, rotated_bounds.zmax );

 if ( ( ( rotated_bounds2.xmax - rotated_bounds2.xmin ) != 0 ) ||
   ( ( rotated_bounds2.ymax - rotated_bounds2.ymin ) != 0 ) ||
   ( ( rotated_bounds2.zmax - rotated_bounds2.zmin ) != 0 ) )
 {

  rotated_bounds2.xmin += scene_position.x;
  rotated_bounds2.ymin += scene_position.y;
  rotated_bounds2.zmin += scene_position.z;

  rotated_bounds2.xmax += scene_position.x;
  rotated_bounds2.ymax += scene_position.y;
  rotated_bounds2.zmax += scene_position.z;

  if (contributes_to_collision)
  {

   scene_bounds2.xmin = min ( scene_bounds2.xmin, rotated_bounds2.xmin );
   scene_bounds2.ymin = min ( scene_bounds2.ymin, rotated_bounds2.ymin );
   scene_bounds2.zmin = min ( scene_bounds2.zmin, rotated_bounds2.zmin );

   scene_bounds2.xmax = max ( scene_bounds2.xmax, rotated_bounds2.xmax );
   scene_bounds2.ymax = max ( scene_bounds2.ymax, rotated_bounds2.ymax );
   scene_bounds2.zmax = max ( scene_bounds2.zmax, rotated_bounds2.zmax );
  }
 }

 //
 // Calculate sub objects
 //

 for ( count = 0; count < sub_object->number_of_sub_objects; count++ )
  recurse_initialise_sub_scene_bounding_box ( &sub_object->sub_objects[count] );

 //
 // Restore the original position & rotation
 //

 scene_position = old_scene_position;

 memcpy(scene_rotation, old_scene_rotation, sizeof(matrix3x3));

 contributes_to_collision = old_contributes_to_collision;
}

void initialise_scene_bounding_sub_objects(int scene_index)
{
 int index, count;

 memset(&scene_bounds, 0, sizeof(struct OBJECT_3D_BOUNDS));
 memset(&scene_bounds2, 0, sizeof(struct OBJECT_3D_BOUNDS));
 index = objects_3d_scene_database[scene_index].index;
 scene_position.x = 0;
 scene_position.y = 0;
 scene_position.z = 0;
 get_3d_transformation_matrix(scene_rotation, 0, 0, 0);
 if (index != 0)
 {
  rotate_sub_scene_boundaries(&rotated_bounds, &objects_3d_data[index].bounding_box);
  rotate_sub_scene_boundaries(&rotated_bounds2, &objects_3d_data[index].bounding_box2);
  scene_bounds.xmin = min(scene_bounds.xmin, rotated_bounds.xmin);
  scene_bounds.ymin = min(scene_bounds.ymin, rotated_bounds.ymin);
  scene_bounds.zmin = min(scene_bounds.zmin, rotated_bounds.zmin);
  scene_bounds.xmax = max(scene_bounds.xmax, rotated_bounds.xmax);
  scene_bounds.ymax = max(scene_bounds.ymax, rotated_bounds.ymax);
  scene_bounds.zmax = max(scene_bounds.zmax, rotated_bounds.zmax);
  scene_bounds2.xmin = min(scene_bounds2.xmin, rotated_bounds2.xmin);
  scene_bounds2.ymin = min(scene_bounds2.ymin, rotated_bounds2.ymin);
  scene_bounds2.zmin = min(scene_bounds2.zmin, rotated_bounds2.zmin);
  scene_bounds2.xmax = max(scene_bounds2.xmax, rotated_bounds2.xmax);
  scene_bounds2.ymax = max(scene_bounds2.ymax, rotated_bounds2.ymax);
  scene_bounds2.zmax = max(scene_bounds2.zmax, rotated_bounds2.zmax);
 }

 contributes_to_collision = 1;
 for (count = 0; count < objects_3d_scene_database[scene_index].number_of_sub_objects; count++)
  recurse_initialise_sub_scene_bounding_box(&objects_3d_scene_database[scene_index].sub_objects[count]);

 objects_3d_scene_database[scene_index].bounding_box = scene_bounds;
 objects_3d_scene_database[scene_index].bounding_box2 = scene_bounds2;

 //
 // Calculate the radius based on the bounding_box values
 //

 {
  double dxmin, dxmax, dymin, dymax, dzmin, dzmax, radius;
  dxmax =((double) scene_bounds.xmax * (double) scene_bounds.xmax);
  dxmin =((double) scene_bounds.xmin * (double) scene_bounds.xmin);
  dymax =((double) scene_bounds.ymax * (double) scene_bounds.ymax);
  dymin =((double) scene_bounds.ymin * (double) scene_bounds.ymin);
  dzmax =((double) scene_bounds.zmax * (double) scene_bounds.zmax);
  dzmin =((double) scene_bounds.zmin * (double) scene_bounds.zmin);
  radius = 0;
  radius = max(radius,(dxmax + dymax + dzmax));
  radius = max(radius,(dxmax + dymax + dzmin));
  radius = max(radius,(dxmax + dymin + dzmax));
  radius = max(radius,(dxmax + dymin + dzmin));
  radius = max(radius,(dxmin + dymax + dzmax));
  radius = max(radius,(dxmin + dymax + dzmin));
  radius = max(radius,(dxmin + dymin + dzmax));
  radius = max(radius,(dxmin + dymin + dzmin));
  radius = sqrt(radius);
  objects_3d_scene_database[scene_index].radius = radius;
 }
}

void LoadInit(FILE* fp)
{
 fread(&total_number_of_scenes, sizeof(int), 1, fp);

 assert(total_number_of_scenes);

 objects_3d_scene_database = new OBJECT_3D_SCENE_DATABASE_ENTRY[OBJECT_3D_LAST];

 assert(objects_3d_scene_database);

 memset(objects_3d_scene_database, 0,(sizeof(struct OBJECT_3D_SCENE_DATABASE_ENTRY) * OBJECT_3D_LAST));

 //
 // Read in the memory stats for all the scenes
 //

 fread(&total_number_of_scene_camera_indices, sizeof(int), 1, fp);
 fread(&total_number_of_scene_link_objects, sizeof(int), 1, fp);
 fread(&total_number_of_sprite_light_objects, sizeof(int), 1, fp);
 fread(&total_number_of_scene_sub_objects, sizeof(int), 1, fp);
 fread(&total_number_of_scene_sub_object_indices, sizeof(int), 1, fp);
 fread(&total_number_of_scene_texture_animations, sizeof(int), 1, fp);
 fread(&total_number_of_scene_approximations, sizeof(int), 1, fp);
 fread(&total_number_of_scene_sub_object_keyframes, sizeof(int), 1, fp);
 fread(&total_number_of_scene_sub_object_dissolve_keyframes, sizeof(int), 1, fp);

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

 if (total_number_of_scene_camera_indices)
  objects_3d_camera_info_array = new OBJECT_3D_SCENE_CAMERA_INFO[total_number_of_scene_camera_indices];

 if (total_number_of_scene_link_objects)
  objects_3d_scene_link_array = new OBJECT_3D_SCENE_LINK_OBJECT[total_number_of_scene_link_objects];

 if (total_number_of_sprite_light_objects)
  objects_3d_scene_sprite_light_array = new OBJECT_3D_SPRITE_LIGHT[total_number_of_sprite_light_objects];

 if (total_number_of_scene_sub_objects)
  objects_3d_scene_sub_objects_array = new OBJECT_3D_DATABASE_ENTRY[total_number_of_scene_sub_objects];

 if (total_number_of_scene_sub_object_indices)
  objects_3d_scene_sub_object_indices_array = new OBJECT_3D_SUB_OBJECT_INDEX[total_number_of_scene_sub_object_indices];

 if (total_number_of_scene_texture_animations)
  objects_3d_scene_texture_animations_array = new int[total_number_of_scene_texture_animations];

 if (total_number_of_scene_approximations)
  objects_3d_scene_approximations_array = new OBJECT_3D_APPROXIMATION_INFO[total_number_of_scene_approximations];

 if (total_number_of_scene_sub_object_keyframes)
  objects_3d_scene_sub_object_keyframes_array = new OBJECT_3D_SUB_OBJECT_KEYFRAME[total_number_of_scene_sub_object_keyframes];

 if (total_number_of_scene_sub_object_dissolve_keyframes)
  objects_3d_scene_sub_object_dissolve_keyframes_array = new OBJECT_3D_SUB_OBJECT_VALUE_KEYFRAME[total_number_of_scene_sub_object_dissolve_keyframes];

 objects_3d_camera_info_array_ptr = objects_3d_camera_info_array;
 objects_3d_scene_link_ptr = objects_3d_scene_link_array;
 objects_3d_scene_sprite_light_ptr = objects_3d_scene_sprite_light_array;
 objects_3d_scene_sub_objects_array_ptr = objects_3d_scene_sub_objects_array;
 objects_3d_scene_sub_object_indices_array_ptr = objects_3d_scene_sub_object_indices_array;
 objects_3d_scene_texture_animations_array_ptr = objects_3d_scene_texture_animations_array;
 objects_3d_scene_approximations_array_ptr = objects_3d_scene_approximations_array;
 objects_3d_scene_sub_object_keyframes_array_ptr = objects_3d_scene_sub_object_keyframes_array;
 objects_3d_scene_sub_object_dissolve_keyframes_array_ptr = objects_3d_scene_sub_object_dissolve_keyframes_array;
}

void LoadScene(FILE* fp, OBJECT_3D_SCENE_DATABASE_ENTRY* scene)
{
  int
   tmp,
   keyframe_count,
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

  fread(&scene->self_shadows, sizeof(int), 1, fp);

  //
  // Set the approximation scale to 1.0
  //

  scene->object_approximation_scale = 1.0;

  //
  // Read in the number of lights
  //

  fread(&number_of_scene_lights, sizeof(int), 1, fp);

  for (tmp = 0; tmp < number_of_scene_lights; tmp++)
  {
   struct REAL_COLOUR light_colour;

   float light_intensity, heading, pitch, roll, x, y, z;

   int light_type;

   fread(&light_colour, sizeof(struct REAL_COLOUR), 1, fp);
   fread(&light_intensity, sizeof(float), 1, fp);
   fread(&light_type, sizeof(int), 1, fp);
   fread(&x, sizeof(float), 1, fp);
   fread(&y, sizeof(float), 1, fp);
   fread(&z, sizeof(float), 1, fp);
   fread(&heading, sizeof(float), 1, fp);
   fread(&pitch, sizeof(float), 1, fp);
   fread(&roll, sizeof(float), 1, fp);
  }

  //
  // Read in the number of camera
  //

  fread(&number_of_scene_cameras, sizeof(int), 1, fp);

  scene->number_of_cameras = number_of_scene_cameras;

  if (number_of_scene_cameras)
  {
   int
    camera_count;

   scene->cameras = objects_3d_camera_info_array_ptr;

   objects_3d_camera_info_array_ptr += number_of_scene_cameras;

   assert(scene->cameras);

   for (camera_count = 0; camera_count < number_of_scene_cameras; camera_count++)
   {
    fread(&scene->cameras[camera_count].camera_name_index, sizeof(int), 1, fp);

    fread(&scene->cameras[camera_count].camera_index, sizeof(int), 1, fp);
   }
  }
  else
   scene->cameras = NULL;

  //
  // Read in the number of scene links
  //

  fread(&number_of_scene_links, sizeof(int), 1, fp);

  scene->number_of_scene_link_objects = number_of_scene_links;

  scene->scene_link_objects = NULL;

  if (number_of_scene_links)
   scene->scene_link_objects = objects_3d_scene_link_ptr;

  for (tmp = 0; tmp < number_of_scene_links; tmp++)
  {
   fread(&objects_3d_scene_link_ptr->scene_index, sizeof(int), 1, fp);
   fread(&objects_3d_scene_link_ptr->x, sizeof(float), 1, fp);
   fread(&objects_3d_scene_link_ptr->y, sizeof(float), 1, fp);
   fread(&objects_3d_scene_link_ptr->z, sizeof(float), 1, fp);
   fread(&objects_3d_scene_link_ptr->heading, sizeof(float), 1, fp);
   fread(&objects_3d_scene_link_ptr->pitch, sizeof(float), 1, fp);
   fread(&objects_3d_scene_link_ptr->roll, sizeof(float), 1, fp);

   objects_3d_scene_link_ptr++;
  }

  //
  // Read in the sprite lights
  //

  fread(&number_of_sprite_lights, sizeof(int), 1, fp);

  scene->number_of_sprite_lights = number_of_sprite_lights;

  scene->sprite_lights = NULL;

  if (number_of_sprite_lights)
   scene->sprite_lights = objects_3d_scene_sprite_light_ptr;

  for (tmp = 0; tmp < number_of_sprite_lights; tmp++)
  {
   int
    red,
    green,
    blue;

   fread(&objects_3d_scene_sprite_light_ptr->position.x, sizeof(float), 1, fp);
   fread(&objects_3d_scene_sprite_light_ptr->position.y, sizeof(float), 1, fp);
   fread(&objects_3d_scene_sprite_light_ptr->position.z, sizeof(float), 1, fp);
   fread(&objects_3d_scene_sprite_light_ptr->scale.x, sizeof(float), 1, fp);
   fread(&objects_3d_scene_sprite_light_ptr->scale.y, sizeof(float), 1, fp);
   fread(&objects_3d_scene_sprite_light_ptr->scale.z, sizeof(float), 1, fp);

   fread(&red, sizeof(int), 1, fp);
   fread(&green, sizeof(int), 1, fp);
   fread(&blue, sizeof(int), 1, fp);

   objects_3d_scene_sprite_light_ptr->colour.red = red;
   objects_3d_scene_sprite_light_ptr->colour.green = green;
   objects_3d_scene_sprite_light_ptr->colour.blue = blue;

   objects_3d_scene_sprite_light_ptr++;
  }

  //
  // Read in the number of sub objects, and the number of *named* sub objects
  //

  fread(&number_of_scene_sub_objects, sizeof(int), 1, fp);

  fread(&number_of_scene_named_sub_objects, sizeof(int), 1, fp);

  //
  // Allocate the memory for these sub objects
  //

  current_scene_sub_object_array = NULL;

  current_scene_sub_object_index_array = NULL;

  if (number_of_scene_named_sub_objects)
  {
   current_scene_sub_object_index_array = objects_3d_scene_sub_object_indices_array_ptr;
   objects_3d_scene_sub_object_indices_array_ptr += number_of_scene_named_sub_objects;
  }

  if (number_of_scene_sub_objects)
  {
   current_scene_sub_object_array = objects_3d_scene_sub_objects_array_ptr;
   objects_3d_scene_sub_objects_array_ptr += number_of_scene_sub_objects;
  }

  scene->total_number_of_sub_objects = number_of_scene_sub_objects;
  scene->total_number_of_sub_object_indices = number_of_scene_named_sub_objects;
  scene->scene_sub_object_indices_array = current_scene_sub_object_index_array;
  scene->scene_sub_object_array = current_scene_sub_object_array;


  fread(&number_of_texture_animations, sizeof(int), 1, fp);

  scene->number_of_texture_animations = number_of_texture_animations;

  if (number_of_texture_animations)
  {
   scene->texture_animations = objects_3d_scene_texture_animations_array_ptr;

   objects_3d_scene_texture_animations_array_ptr += number_of_texture_animations;

   assert(scene->texture_animations);

   for (tmp = 0; tmp < number_of_texture_animations; tmp++)
    fread(&scene->texture_animations[tmp], sizeof(int), 1, fp);
  }

  fread(&number_of_approximations, sizeof(int), 1, fp);

  fread(&scene->index, sizeof(int), 1, fp);

  assert(scene->index >= 0);
  //assert(scene->index <= total_number_of_raw_3d_objects);

  scene->number_of_approximations = number_of_approximations;

  if (number_of_approximations)
  {
   assert((objects_3d_scene_approximations_array_ptr - objects_3d_scene_approximations_array) < total_number_of_scene_approximations);

   scene->approximations = objects_3d_scene_approximations_array_ptr;

   objects_3d_scene_approximations_array_ptr += number_of_approximations;

   assert((objects_3d_scene_approximations_array_ptr - objects_3d_scene_approximations_array) <= total_number_of_scene_approximations);

   assert(scene->approximations);

   //
   // Read any approximation information in
   //

   for (approximation = 0; approximation < number_of_approximations; approximation++)
   {
    fread(&scene->approximations[approximation].object_number, sizeof(int), 1, fp);
    fread(&scene->approximations[approximation].distance, sizeof(float), 1, fp);

    //
    // Approximation distance adjustment
    //
    scene->approximations[approximation].distance /= 1;
   }
  }

  //
  // Read in the shadow approximation index
  //

  fread(&scene->shadow_approximation_index, sizeof(int), 1, fp);

  //
  // Read in the shadow polygon object index
  //

  fread(&scene->shadow_polygon_object_index, sizeof(int), 1, fp);
  fread(&scene->shadow_polygon_object_scale.x, sizeof(float), 1, fp);
  fread(&scene->shadow_polygon_object_scale.y, sizeof(float), 1, fp);
  fread(&scene->shadow_polygon_object_scale.z, sizeof(float), 1, fp);

  //
  // Read in the collision object index
  //

  fread(&scene->collision_object_index, sizeof(int), 1, fp);

  //
  // Next, read in the keyframes for the main object in the scene.
  //

  fread(&scene->number_of_keyframes, sizeof(int), 1, fp);

  scene->keyframes = objects_3d_scene_sub_object_keyframes_array_ptr;

  objects_3d_scene_sub_object_keyframes_array_ptr += scene->number_of_keyframes;

  for (keyframe_count = 0; keyframe_count < scene->number_of_keyframes; keyframe_count++)
  {
   fread(&scene->keyframes[keyframe_count].index, sizeof(int), 1, fp);
   fread(&scene->keyframes[keyframe_count].linear, sizeof(int), 1, fp);

   fread(&scene->keyframes[keyframe_count].x, sizeof(float), 1, fp);
   fread(&scene->keyframes[keyframe_count].y, sizeof(float), 1, fp);
   fread(&scene->keyframes[keyframe_count].z, sizeof(float), 1, fp);

   fread(&scene->keyframes[keyframe_count].heading, sizeof(float), 1, fp);
   fread(&scene->keyframes[keyframe_count].pitch, sizeof(float), 1, fp);
   fread(&scene->keyframes[keyframe_count].roll, sizeof(float), 1, fp);

   fread(&scene->keyframes[keyframe_count].scale_x, sizeof(int), 1, fp);
   fread(&scene->keyframes[keyframe_count].scale_y, sizeof(int), 1, fp);
   fread(&scene->keyframes[keyframe_count].scale_z, sizeof(int), 1, fp);

   fread(&scene->keyframes[keyframe_count].tension, sizeof(int), 1, fp);
   fread(&scene->keyframes[keyframe_count].continuity, sizeof(int), 1, fp);
   fread(&scene->keyframes[keyframe_count].bias, sizeof(int), 1, fp);
  }

  //
  // Next the object dissolve for the main object & any keyframes associate with it
  //

  fread(&scene->object_dissolve, sizeof(float), 1, fp);

  fread(&scene->number_of_object_dissolve_keyframes, sizeof(int), 1, fp);

  scene->object_dissolve_keyframes = objects_3d_scene_sub_object_dissolve_keyframes_array_ptr;

  objects_3d_scene_sub_object_dissolve_keyframes_array_ptr += scene->number_of_object_dissolve_keyframes;

  for (keyframe_count = 0; keyframe_count < scene->number_of_object_dissolve_keyframes; keyframe_count++)
  {

   fread(&scene->object_dissolve_keyframes[keyframe_count].index, sizeof(int), 1, fp);
   fread(&scene->object_dissolve_keyframes[keyframe_count].linear, sizeof(int), 1, fp);

   fread(&scene->object_dissolve_keyframes[keyframe_count].value, sizeof(float), 1, fp);
   fread(&scene->object_dissolve_keyframes[keyframe_count].tension, sizeof(int), 1, fp);
   fread(&scene->object_dissolve_keyframes[keyframe_count].continuity, sizeof(int), 1, fp);
   fread(&scene->object_dissolve_keyframes[keyframe_count].bias, sizeof(int), 1, fp);
  }

  //
  // Next read in the object displacement sequence number
  //

  fread(&scene->displacement_sequence_index, sizeof(int), 1, fp);

  fread(&scene->number_of_displacement_amplitude_keyframes, sizeof(int), 1, fp);

  scene->displacement_amplitude_keyframes = objects_3d_scene_sub_object_dissolve_keyframes_array_ptr;

  objects_3d_scene_sub_object_dissolve_keyframes_array_ptr += scene->number_of_displacement_amplitude_keyframes;

  for (keyframe_count = 0; keyframe_count < scene->number_of_displacement_amplitude_keyframes; keyframe_count++)
  {
   fread(&scene->displacement_amplitude_keyframes[keyframe_count].index, sizeof(int), 1, fp);
   fread(&scene->displacement_amplitude_keyframes[keyframe_count].linear, sizeof(int), 1, fp);

   fread(&scene->displacement_amplitude_keyframes[keyframe_count].value, sizeof(float), 1, fp);
   fread(&scene->displacement_amplitude_keyframes[keyframe_count].tension, sizeof(int), 1, fp);
   fread(&scene->displacement_amplitude_keyframes[keyframe_count].continuity, sizeof(int), 1, fp);
   fread(&scene->displacement_amplitude_keyframes[keyframe_count].bias, sizeof(int), 1, fp);
  }


  //
  // Read in any sub object indices
  //

  {
   int
    number_of_sub_object_indices;

   fread(&number_of_sub_object_indices, sizeof(int), 1, fp);

   scene->number_of_sub_object_indices = number_of_sub_object_indices;

   if (number_of_sub_object_indices)
   {
    int
     index_count,
     sub_object_index,
     object_index;

    //
    // Allocate the array
    //

    scene->sub_object_indices = current_scene_sub_object_index_array;

    current_scene_sub_object_index_array += number_of_sub_object_indices;

    assert(scene->sub_object_indices);

    for (index_count = 0; index_count < scene->number_of_sub_object_indices; index_count++)
    {
     fread(&sub_object_index, sizeof(int), 1, fp);

     fread(&object_index, sizeof(int), 1, fp);

     scene->sub_object_indices[index_count].sub_object_index = sub_object_index;

     scene->sub_object_indices[index_count].object_index = object_index;

     if (index_count != 0)
     {
      assert(scene->sub_object_indices[index_count-1].object_index <
         scene->sub_object_indices[index_count].object_index);
     }
    }
   }
  }

  //
  // Read in any sub objects
  //

  fread(&scene->number_of_sub_objects, sizeof(int), 1, fp);

  if (scene->number_of_sub_objects)
  {
   int
    sub_object_total,
    sub_object_count;

   struct OBJECT_3D_DATABASE_ENTRY
    *sub_objects;

   sub_object_total = scene->number_of_sub_objects;

   sub_objects = current_scene_sub_object_array;

   current_scene_sub_object_array += sub_object_total;

   assert(sub_objects);

   scene->sub_objects = sub_objects;

   for (sub_object_count = 0; sub_object_count < sub_object_total; sub_object_count++)
    initialise_3d_sub_object(fp, NULL, &sub_objects[sub_object_count]);
  }
}

void LoadCameras(FILE* fp)
{
 int count;

 //
 // Read in the camera information
 //

 fread(&total_number_of_cameras, sizeof(int), 1, fp);

 fread(&total_number_of_camera_keyframes, sizeof(int), 1, fp);

 if (total_number_of_cameras)
 {
  struct OBJECT_3D_SUB_OBJECT_KEYFRAME *keyframes;

  objects_3d_camera_database = new OBJECT_3D_SCENE_CAMERA[total_number_of_cameras];

  objects_3d_camera_keyframes = new OBJECT_3D_SUB_OBJECT_KEYFRAME[total_number_of_camera_keyframes];

  keyframes = objects_3d_camera_keyframes;

  for (count = 0; count < total_number_of_cameras; count++)
  {
   int
    keyframe_count;

   fread(&objects_3d_camera_database[count].number_of_keyframes, sizeof(int), 1, fp);
   fread(&objects_3d_camera_database[count].target_sub_object_id, sizeof(int), 1, fp);
   fread(&objects_3d_camera_database[count].heading_locked, sizeof(int), 1, fp);
   fread(&objects_3d_camera_database[count].pitch_locked, sizeof(int), 1, fp);
   fread(&objects_3d_camera_database[count].roll_locked, sizeof(int), 1, fp);

   objects_3d_camera_database[count].keyframes = keyframes;

   for (keyframe_count = 0; keyframe_count < objects_3d_camera_database[count].number_of_keyframes; keyframe_count++)
   {
    fread(&keyframes[keyframe_count].index, sizeof(int), 1, fp);
    fread(&keyframes[keyframe_count].linear, sizeof(int), 1, fp);

    fread(&keyframes[keyframe_count].x, sizeof(float), 1, fp);
    fread(&keyframes[keyframe_count].y, sizeof(float), 1, fp);
    fread(&keyframes[keyframe_count].z, sizeof(float), 1, fp);

    fread(&keyframes[keyframe_count].heading, sizeof(float), 1, fp);
    fread(&keyframes[keyframe_count].pitch, sizeof(float), 1, fp);
    fread(&keyframes[keyframe_count].roll, sizeof(float), 1, fp);

    fread(&keyframes[keyframe_count].scale_x, sizeof(float), 1, fp);
    fread(&keyframes[keyframe_count].scale_y, sizeof(float), 1, fp);
    fread(&keyframes[keyframe_count].scale_z, sizeof(float), 1, fp);

    fread(&keyframes[keyframe_count].tension, sizeof(float), 1, fp);
    fread(&keyframes[keyframe_count].continuity, sizeof(float), 1, fp);
    fread(&keyframes[keyframe_count].bias, sizeof(float), 1, fp);
   }

   keyframes += objects_3d_camera_database[count].number_of_keyframes;
  }
 }

 {
  int
   total_keyframes;

  total_keyframes = objects_3d_scene_sub_object_keyframes_array_ptr - objects_3d_scene_sub_object_keyframes_array;

  if (total_keyframes != total_number_of_scene_sub_object_keyframes)
   error("Read in %d keyframes, but allocated %d keyframes", total_keyframes, total_number_of_scene_sub_object_keyframes);
 }
}

void LoadAll(void)
{
 int count;

 FILE* fp = safe_fopen("3dobjdb.bin", "rb");

 LoadInit(fp);

 for (count = 0; count < total_number_of_scenes; count++)
 {
  int tmp, scene_index;

  for (tmp = 0; tmp < 16; tmp++)
  {
   int temp;
   fread(&temp, sizeof(int), 1, fp);
   if (temp != -1)
    error("3d objects scene definitions file is corrupted");
  }

  fread(&scene_index, sizeof(int), 1, fp);

  LoadScene(fp, &objects_3d_scene_database[scene_index]);
  initialise_scene_quick_sub_object_search(scene_index);
  initialise_scene_visible_sub_objects(scene_index);
  initialise_scene_bounding_sub_objects(scene_index);
 }

 LoadCameras(fp);

 fclose(fp);
}


 const Objects& objects_3d_data;


 friend class LwsExport;

 public:

 Scenes(const Objects& objects)
  : objects_3d_data(objects)
 {
  LoadAll();
 }

 ~Scenes(void)
 {
 }

 int GetNumberOfScenes(void) const { return total_number_of_scenes; }
 const OBJECT_3D_SCENE_DATABASE_ENTRY& GetScene(int index) const { return objects_3d_scene_database[index]; }
};
