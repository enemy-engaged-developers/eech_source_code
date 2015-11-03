// This was taken from EE sources

class LwsExport;

#define MAX_NUMBER_OF_SUB_OBJECT_INDICES 512

#include "cameras.cpp"

#ifndef NATIVE_TYPES
struct VEC3D
{
 float x, y, z;
};

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
#endif

void print_keyframes(int number_of_keyframes, const struct OBJECT_3D_SUB_OBJECT_KEYFRAME *keyframes)
{
 printf(" KeyFrames %i", number_of_keyframes);
 for (int i = 0; i < number_of_keyframes; i++)
  printf(" (%i  %i  %f %f %f  %f %f %f  %f %f %f  %f %f %f)", keyframes[i].index, keyframes[i].linear, keyframes[i].x, keyframes[i].y, keyframes[i].z, keyframes[i].heading, keyframes[i].pitch, keyframes[i].roll, keyframes[i].scale_x, keyframes[i].scale_y, keyframes[i].scale_z, keyframes[i].tension, keyframes[i].continuity, keyframes[i].bias);
}

#ifndef NATIVE_TYPES
struct OBJECT_3D_SUB_OBJECT_VALUE_KEYFRAME
{
 int index, linear;
 float value, tension, continuity, bias;
};
#endif

void print_value_keyframes(int number_of_value_keyframes, const struct OBJECT_3D_SUB_OBJECT_VALUE_KEYFRAME *value_keyframes)
{
 printf(" ValueKeyFrames %i", number_of_value_keyframes);
 for (int i = 0; i < number_of_value_keyframes; i++)
  printf(" (%i  %i  %f  %f %f %f)", value_keyframes[i].index, value_keyframes[i].linear, value_keyframes[i].value, value_keyframes[i].tension, value_keyframes[i].continuity, value_keyframes[i].bias);
}


#ifndef NATIVE_TYPES
struct OBJECT_3D_SUB_OBJECT_INDEX
{
 unsigned short int sub_object_index;
 unsigned short int object_index;
};

struct OBJECT_3D_DATABASE_ENTRY;

struct OBJECT_3D_SCENE_SUB_OBJECT_TABLE_ENTRY
{
 int sub_object_index;
 int number_of_sub_objects;
 struct OBJECT_3D_DATABASE_ENTRY **sub_objects;
};

struct OBJECT_3D_DATABASE_ENTRY
{
 unsigned short int index;
 unsigned char number_of_sub_objects, number_of_keyframes;
 unsigned char number_of_object_dissolve_keyframes, sub_object_approximation_in_level, sub_object_approximation_out_level;
 unsigned char number_of_sub_object_indices:6, unused:1, collision_contribution:1;
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

 class Labeler
 {
  public:

  Labeler(int number_of_sub_object_table_entries, const struct OBJECT_3D_SCENE_SUB_OBJECT_TABLE_ENTRY* sub_object_indices_table, const Names& subobjects)
   : number_of_sub_object_table_entries(number_of_sub_object_table_entries), sub_object_indices_table(sub_object_indices_table), subobjects(subobjects)
  {
  }

  const char* label(const struct OBJECT_3D_DATABASE_ENTRY *sub_object)
  {
   for (int i = 0; i < number_of_sub_object_table_entries; i++)
    {
     const struct OBJECT_3D_SCENE_SUB_OBJECT_TABLE_ENTRY& t = sub_object_indices_table[i];
     for (int j = 0; j < t.number_of_sub_objects; j++)
      if (t.sub_objects[j] == sub_object)
       return subobjects[t.sub_object_index];
    }
   return "";
  }

  private:

  int number_of_sub_object_table_entries;
  const struct OBJECT_3D_SCENE_SUB_OBJECT_TABLE_ENTRY* sub_object_indices_table;
  const Names& subobjects;
 };

 void print(int offset, Translator& translator, Labeler& labeler) const
 {
  printf("% *c", offset * 4, ' ');
  printf("%i %i [%s] '%s' CC %i OD %f", sub_object_approximation_in_level, sub_object_approximation_out_level, translator(index), labeler.label(this), collision_contribution, object_dissolve);
  if (flag)
   printf(" L %f %f %f %f %f %f", relative_heading_minimum, relative_heading_maximum, relative_pitch_minimum, relative_pitch_maximum, relative_roll_minimum, relative_roll_maximum);
  print_keyframes(number_of_keyframes, keyframes);
  printf(" ObjectDissolve");
  print_value_keyframes(number_of_object_dissolve_keyframes, object_dissolve_keyframes);
  //unsigned char number_of_sub_object_indices:6;
  //struct OBJECT_3D_SUB_OBJECT_INDEX *sub_object_indices;
  printf("\n");

  print_subobjects(offset, number_of_sub_objects, sub_objects, translator, labeler);
 }

 static void print_subobjects(int offset, int number_of_subobjects, const struct OBJECT_3D_DATABASE_ENTRY* sub_objects, Translator& translator, Labeler& labeler)
 {
  offset++;
  for (int i = 0; i < number_of_subobjects; i++)
   sub_objects[i].print(offset, translator, labeler);
 }
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

struct OBJECT_3D_AMBIENT_LIGHT
{
 struct REAL_COLOUR colour;
 int light_index;
};

struct OBJECT_3D_DISTANT_LIGHT
{
 float heading, pitch, roll;
 struct REAL_COLOUR colour;
 int light_index;
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
  shadow_polygon_object_index,
  collision_object_index,
  number_of_texture_animations,
  number_of_approximations,
  number_of_cameras,
  number_of_keyframes,
  number_of_object_dissolve_keyframes,
  number_of_displacement_amplitude_keyframes,
  number_of_scene_link_objects,
  number_of_sprite_lights,
  number_of_ambient_lights,
  number_of_distant_lights;

 struct VEC3D shadow_polygon_object_scale;
 int *texture_animations;
 struct OBJECT_3D_APPROXIMATION_INFO *approximations; //Approximation objects for index for different distances
 struct OBJECT_3D_SCENE_CAMERA_INFO *cameras;
 struct OBJECT_3D_SCENE_LINK_OBJECT *scene_link_objects;
 struct OBJECT_3D_SPRITE_LIGHT *sprite_lights;
 struct OBJECT_3D_AMBIENT_LIGHT *ambient_lights;
 struct OBJECT_3D_DISTANT_LIGHT *distant_lights;

 struct OBJECT_3D_SCENE_SUB_OBJECT_TABLE_ENTRY *sub_object_indices_table; //Указатели на все sub_objects с данным sub_object_id. Используется для поиска
 struct OBJECT_3D_SUB_OBJECT_KEYFRAME *keyframes;
 struct OBJECT_3D_SUB_OBJECT_VALUE_KEYFRAME *object_dissolve_keyframes, *displacement_amplitude_keyframes;

 int
  shadow_approximation_index,
  number_of_sub_objects,
  number_of_sub_object_indices,
  number_of_sub_object_table_entries,
  total_number_of_sub_objects,
  total_number_of_sub_object_indices;

 struct OBJECT_3D_SUB_OBJECT_INDEX *scene_sub_object_indices_array; //Какая-то хрень, грузится. sub_object_index
 struct OBJECT_3D_DATABASE_ENTRY *scene_sub_object_array;
 struct OBJECT_3D_SUB_OBJECT_INDEX *sub_object_indices;
 struct OBJECT_3D_DATABASE_ENTRY *sub_objects;

 struct OBJECT_3D_DATABASE_ENTRY **sub_object_table_entries;

 void print(const Names& names_subobjects, Translator& translator) const
 {
  printf("Index %s Shadow %i Collision %i SAI %i\n", translator(index), shadow_polygon_object_index, collision_object_index, shadow_approximation_index);


  //struct VEC3D shadow_polygon_object_scale;

  printf("Texture Animations %i\n", number_of_texture_animations);
  for (int i = 0; i < number_of_texture_animations; i++)
   printf(" %i", texture_animations[i]);
  printf("\n");

  printf("Approximations %i\n", number_of_approximations);
  for (int i = 0; i < number_of_approximations; i++)
   printf(" (%f, %s)", approximations[i].distance, translator(approximations[i].object_number));
  printf("\n");

  print_keyframes(number_of_keyframes, keyframes);
  printf("\n");

  printf("ObjectDissolve");
  print_value_keyframes(number_of_object_dissolve_keyframes, object_dissolve_keyframes);
  printf("\n");

  printf("Displacement");
  print_value_keyframes(number_of_displacement_amplitude_keyframes, displacement_amplitude_keyframes);
  printf("\n");

  //number_of_cameras,
  //struct OBJECT_3D_SCENE_CAMERA_INFO *cameras;

  //number_of_scene_link_objects,
  //struct OBJECT_3D_SCENE_LINK_OBJECT *scene_link_objects;

  //number_of_sprite_lights;
  //struct OBJECT_3D_SPRITE_LIGHT *sprite_lights;

  //number_of_sub_object_indices,
  //total_number_of_sub_objects,
  //total_number_of_sub_object_indices;

  //struct OBJECT_3D_SUB_OBJECT_INDEX *scene_sub_object_indices_array; //Какая-то хрень, грузится. sub_object_index
  //struct OBJECT_3D_DATABASE_ENTRY *scene_sub_object_array;
  //struct OBJECT_3D_SUB_OBJECT_INDEX *sub_object_indices;
  OBJECT_3D_DATABASE_ENTRY::Labeler labeler(number_of_sub_object_table_entries, sub_object_indices_table, names_subobjects);
  OBJECT_3D_DATABASE_ENTRY::print_subobjects(0, number_of_sub_objects, sub_objects, translator, labeler);

  printf("\n\n");
 }
};
#endif

class QuickSearch
{
 public:
 QuickSearch(OBJECT_3D_SCENE_DATABASE_ENTRY& scene)
  : scene(scene)
 {
  initialise_scene_quick_sub_object_search();
 }

 private:
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

void initialise_scene_quick_sub_object_search(void)
{
 int index;
 int count, total_sub_object_indices, number_of_unique_indices;

 //
 // Set the sub object index array to 0
 //

 for (index = 0; index < MAX_NUMBER_OF_SUB_OBJECT_INDICES; index++)
  sub_object_index_count[index] = 0;

 //
 // Go through all the objects in the scene counting the sub object indices
 //

 for (count = 0; count < scene.number_of_sub_object_indices; count++)
  sub_object_index_count[ scene.scene_sub_object_indices_array[count].sub_object_index ]++;

 //
 // Recurse down through any sub objects
 //

 for (count = 0; count < scene.number_of_sub_objects; count++)
  count_named_sub_objects(&scene.sub_objects[count]);

 //
 // Count up the total number of named sub objects
 //

 total_sub_object_indices = 0;
 number_of_unique_indices = 0;
 for (index = 0; index < MAX_NUMBER_OF_SUB_OBJECT_INDICES; index++)
  {
   total_sub_object_indices += sub_object_index_count[index];
   if (sub_object_index_count[index])
    number_of_unique_indices++;
  }

 //
 // We should already have the total number, so check here
 //

 assert(total_sub_object_indices == scene.total_number_of_sub_object_indices);

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

   scene.sub_object_indices_table = current_sub_object_table;
   scene.number_of_sub_object_table_entries = number_of_unique_indices;

   //
   // Allocate memory for the entries in the table
   //

   sub_object_table_entries = new OBJECT_3D_DATABASE_ENTRY *[total_sub_object_indices];
#ifndef NATIVE_TYPES
   scene.sub_object_table_entries = sub_object_table_entries;
#endif

   //
   // Go through initialising the table
   //

   sub_object_entry_ptr = sub_object_table_entries;

   table_index = 0;
   for (index = 0; index < MAX_NUMBER_OF_SUB_OBJECT_INDICES; index++)
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

   for (count = 0; count < scene.number_of_sub_object_indices; count++)
    {
     int offset;
     struct OBJECT_3D_DATABASE_ENTRY *sub_object;
     index = scene.scene_sub_object_indices_array[count].sub_object_index;
     offset = scene.scene_sub_object_indices_array[count].object_index;
     sub_object = &scene.sub_objects[offset];
     add_sub_object_index_to_table(index, sub_object);
    }

   //
   // Now recurse the sub objects doing the same thing
   //

   for (count = 0; count < scene.number_of_sub_objects; count++)
    populate_table_with_named_sub_objects(&scene.sub_objects[count]);
  }
}

 OBJECT_3D_SCENE_DATABASE_ENTRY& scene;
 int number_of_sub_object_table_entries;
 int sub_object_index_count[MAX_NUMBER_OF_SUB_OBJECT_INDICES];
 struct OBJECT_3D_SCENE_SUB_OBJECT_TABLE_ENTRY *current_sub_object_table;
};

class Scenes
{

 private:

struct OBJECT_3D_SCENE_DATABASE_ENTRY *objects_3d_scene_database;

struct OBJECT_3D_SCENE_LINK_OBJECT *objects_3d_scene_link_array, *objects_3d_scene_link_ptr;

struct OBJECT_3D_SPRITE_LIGHT *objects_3d_scene_sprite_light_array, *objects_3d_scene_sprite_light_ptr;

struct OBJECT_3D_SCENE_CAMERA_INFO *objects_3d_camera_info_array, *objects_3d_camera_info_array_ptr;

struct OBJECT_3D_DATABASE_ENTRY *objects_3d_scene_sub_objects_array, *objects_3d_scene_sub_objects_array_ptr;

struct OBJECT_3D_SUB_OBJECT_INDEX *objects_3d_scene_sub_object_indices_array, *objects_3d_scene_sub_object_indices_array_ptr;

struct OBJECT_3D_APPROXIMATION_INFO *objects_3d_scene_approximations_array, *objects_3d_scene_approximations_array_ptr;

int *objects_3d_scene_texture_animations_array, *objects_3d_scene_texture_animations_array_ptr;

struct OBJECT_3D_SUB_OBJECT_KEYFRAME *objects_3d_scene_sub_object_keyframes_array, *objects_3d_scene_sub_object_keyframes_array_ptr;

struct OBJECT_3D_SUB_OBJECT_VALUE_KEYFRAME *objects_3d_scene_sub_object_dissolve_keyframes_array, *objects_3d_scene_sub_object_dissolve_keyframes_array_ptr;

int
 total_number_of_scenes,
 total_number_of_scene_link_objects,
 total_number_of_sprite_light_objects,
 total_number_of_scene_camera_indices,
 total_number_of_scene_sub_objects,
 total_number_of_scene_sub_object_indices,
 total_number_of_scene_texture_animations,
 total_number_of_scene_approximations,
 total_number_of_scene_sub_object_keyframes,
 total_number_of_scene_sub_object_dissolve_keyframes;


struct OBJECT_3D_SUB_OBJECT_INDEX *current_scene_sub_object_index_array;
struct OBJECT_3D_DATABASE_ENTRY *current_scene_sub_object_array;

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

 int flag;

 fread(&flag, sizeof(int), 1, fp);

 if (flag)
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

#ifndef NATIVE_TYPES
 sub_object->flag = flag;
#endif

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

void LoadInit(FILE* fp)
{
 fread(&total_number_of_scenes, sizeof(int), 1, fp);

 assert(total_number_of_scenes);

 objects_3d_scene_database = new OBJECT_3D_SCENE_DATABASE_ENTRY[total_number_of_scenes + 1];

 assert(objects_3d_scene_database);

 memset(objects_3d_scene_database, 0, sizeof(struct OBJECT_3D_SCENE_DATABASE_ENTRY) * (total_number_of_scenes + 1));

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
   number_of_scene_cameras,
   number_of_scene_links,
   number_of_sprite_lights,
   number_of_scene_named_sub_objects;

  fseek(fp, sizeof(int), SEEK_CUR);

  fread(&tmp, sizeof(int), 1, fp);
  fseek(fp, 36 * tmp, SEEK_CUR);

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

  fseek(fp, sizeof(float), SEEK_CUR);

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

  fseek(fp, sizeof(int), SEEK_CUR);

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
  if (scene_index >= total_number_of_scenes + 1)
   error("invalid scene index %i", scene_index);

  LoadScene(fp, &objects_3d_scene_database[scene_index]);
  QuickSearch quick(objects_3d_scene_database[scene_index]);
#ifdef NATIVE_TYPES
  objects_3d_scene_database[scene_index].succeeded = 1;
#endif
 }

 {
  int
   total_keyframes;

  total_keyframes = objects_3d_scene_sub_object_keyframes_array_ptr - objects_3d_scene_sub_object_keyframes_array;

  if (total_keyframes != total_number_of_scene_sub_object_keyframes)
   error("Read in %d keyframes, but allocated %d keyframes", total_keyframes, total_number_of_scene_sub_object_keyframes);
 }

 cameras.LoadAll(fp);

 fclose(fp);
}


 const Objects& objects_3d_data;
 Cameras cameras;


 friend class LwsExport;

 public:

 Scenes(const Objects& objects)
  : objects_3d_data(objects)
 {
  LoadAll();
 }

 ~Scenes(void)
 {
  delete [] objects_3d_scene_sub_object_dissolve_keyframes_array;
  delete [] objects_3d_scene_sub_object_keyframes_array;
  delete [] objects_3d_scene_approximations_array;
  delete [] objects_3d_scene_texture_animations_array;
  delete [] objects_3d_scene_sub_object_indices_array;
  delete [] objects_3d_scene_sub_objects_array;
  delete [] objects_3d_scene_sprite_light_array;
  delete [] objects_3d_scene_link_array;
  delete [] objects_3d_camera_info_array;
  for (int i = 0; i < total_number_of_scenes + 1; i++)
   {
    struct OBJECT_3D_SCENE_DATABASE_ENTRY* scene = &objects_3d_scene_database[i];
#ifndef NATIVE_TYPES
    delete [] scene->sub_object_table_entries;
#endif
    delete [] scene->sub_object_indices_table;
   }
  delete [] objects_3d_scene_database;
 }

 int GetNumberOfScenes(void) const { return total_number_of_scenes; }
 const OBJECT_3D_SCENE_DATABASE_ENTRY& GetScene(int index) const { return objects_3d_scene_database[index]; }
 const Cameras& GetCameras(void) const { return cameras; }
};
