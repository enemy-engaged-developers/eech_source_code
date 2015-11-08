OBJECT_3D_SUB_OBJECT_INDEX *current_scene_sub_object_index_array;
OBJECT_3D_DATABASE_ENTRY *current_scene_sub_object_array;

int get_object(FILE* fp)
{
 char filename[1024];

 if (!get_nul_string(filename, sizeof(filename), fp) || !*filename)
  return 0;

 char* ptr = strrchr(filename, '/');
 if (!ptr)
  {
   ptr = strrchr(filename, '\\');
   if (!ptr)
    ptr = strrchr(filename, ':');
  }
 if (!ptr)
  ptr = filename;
 else
  ptr++;
 char* ext = strrchr(ptr, '.');
 if (ext)
  *ext = '\0';

 return translator(ptr);
}

unsigned get_name(FILE* fp, Names& names)
{
 char name[1024];

 if (!get_nul_string(name, sizeof(name), fp) || !*name)
  return 0;

 return names += name;
}

int get_subobject(FILE* fp)
{
 return get_name(fp, names.SubObjects);
}

int get_scene(FILE* fp)
{
 return get_name(fp, names.Objects);
}

int get_camera(FILE* fp)
{
 return get_name(fp, names.Cameras);
}

int get_light(FILE* fp)
{
  return get_name(fp, names.Lights);
}

void read_keyframes(FILE *fp, int *number_of_keyframes, struct OBJECT_3D_SUB_OBJECT_KEYFRAME **keyframes)
{
 fread(number_of_keyframes, sizeof(int), 1, fp);
 *keyframes = new OBJECT_3D_SUB_OBJECT_KEYFRAME[*number_of_keyframes];
 for (int keyframe_count = 0; keyframe_count < *number_of_keyframes; keyframe_count++)
  {
   fread(&(*keyframes)[keyframe_count].index, sizeof(int), 1, fp);
   fread(&(*keyframes)[keyframe_count].linear, sizeof(int), 1, fp);

   fread(&(*keyframes)[keyframe_count].x, sizeof(float), 1, fp);
   fread(&(*keyframes)[keyframe_count].y, sizeof(float), 1, fp);
   fread(&(*keyframes)[keyframe_count].z, sizeof(float), 1, fp);

   fread(&(*keyframes)[keyframe_count].heading, sizeof(float), 1, fp);
   fread(&(*keyframes)[keyframe_count].pitch, sizeof(float), 1, fp);
   fread(&(*keyframes)[keyframe_count].roll, sizeof(float), 1, fp);

   fread(&(*keyframes)[keyframe_count].scale_x, sizeof(float), 1, fp);
   fread(&(*keyframes)[keyframe_count].scale_y, sizeof(float), 1, fp);
   fread(&(*keyframes)[keyframe_count].scale_z, sizeof(float), 1, fp);

   fread(&(*keyframes)[keyframe_count].tension, sizeof(float), 1, fp);
   fread(&(*keyframes)[keyframe_count].continuity, sizeof(float), 1, fp);
   fread(&(*keyframes)[keyframe_count].bias, sizeof(float), 1, fp);
  }
}

void read_value_keyframes(FILE *fp, int *number_of_keyframes, struct OBJECT_3D_SUB_OBJECT_VALUE_KEYFRAME **keyframes)
{
 fread(number_of_keyframes, sizeof(int), 1, fp);
 if (!*number_of_keyframes)
  {
   *keyframes = NULL;
   return;
  }

 *keyframes = new OBJECT_3D_SUB_OBJECT_VALUE_KEYFRAME[*number_of_keyframes];
 for (int keyframe_count = 0; keyframe_count < *number_of_keyframes; keyframe_count++)
  {
   fread(&(*keyframes)[keyframe_count].index, sizeof(int), 1, fp);
   fread(&(*keyframes)[keyframe_count].linear, sizeof(int), 1, fp);

   fread(&(*keyframes)[keyframe_count].value, sizeof(float), 1, fp);
   fread(&(*keyframes)[keyframe_count].tension, sizeof(float), 1, fp);
   fread(&(*keyframes)[keyframe_count].continuity, sizeof(float), 1, fp);
   fread(&(*keyframes)[keyframe_count].bias, sizeof(float), 1, fp);
  }
}

void read_indices(FILE *fp, int *number_of_sub_object_indices, struct OBJECT_3D_SUB_OBJECT_INDEX **sub_object_indices)
{
 fread(number_of_sub_object_indices, sizeof(int), 1, fp);
 if (!*number_of_sub_object_indices)
 {
  *sub_object_indices = NULL;
  return;
 }

 *sub_object_indices = current_scene_sub_object_index_array;
 current_scene_sub_object_index_array += *number_of_sub_object_indices;

 for (int index_count = 0; index_count < *number_of_sub_object_indices; index_count++)
  {
   int sub_object_index, object_index;
   sub_object_index = get_subobject(fp);
   fread(&object_index, sizeof(int), 1, fp);
   (*sub_object_indices)[index_count].sub_object_index = sub_object_index;
   (*sub_object_indices)[index_count].object_index = object_index;
  }
}

void initialise_3d_sub_object(FILE *fp, struct OBJECT_3D_DATABASE_ENTRY *parent, struct OBJECT_3D_DATABASE_ENTRY *sub_object)
{
 int index, contributes_to_collisions, sub_object_approximation_in_level, sub_object_approximation_out_level;

 sub_object->parent = parent;
 index = get_object(fp);
 if (index < 0)
  index = 0;

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
  sub_object->relative_heading_maximum = 0;
  sub_object->relative_heading_minimum = 0;

  sub_object->relative_pitch_maximum = 0;
  sub_object->relative_pitch_minimum = 0;

  sub_object->relative_roll_maximum = 0;
  sub_object->relative_roll_minimum = 0;
 }

 int number_of_keyframes;
 read_keyframes(fp, &number_of_keyframes, &sub_object->keyframes);
 sub_object->number_of_keyframes = number_of_keyframes;

 int number_of_object_dissolve_keyframes;
 fread(&sub_object->object_dissolve, sizeof(float), 1, fp);
 read_value_keyframes(fp, &number_of_object_dissolve_keyframes, &sub_object->object_dissolve_keyframes);
 sub_object->number_of_object_dissolve_keyframes = number_of_object_dissolve_keyframes;

 int number_of_sub_object_indices;
 read_indices(fp, &number_of_sub_object_indices, &sub_object->sub_object_indices);
 sub_object->number_of_sub_object_indices = number_of_sub_object_indices;

 int number_of_sub_objects;
 read_subobjects(fp, &number_of_sub_objects, &sub_object->sub_objects, sub_object);
 sub_object->number_of_sub_objects = number_of_sub_objects;
}

void read_subobjects(FILE *fp, int *number_of_sub_objects, struct OBJECT_3D_DATABASE_ENTRY **sub_objects, struct OBJECT_3D_DATABASE_ENTRY *parent)
{
 fread(number_of_sub_objects, sizeof(int), 1, fp);
 if (!*number_of_sub_objects)
  {
   *sub_objects = NULL;
   return;
  }

 *sub_objects = current_scene_sub_object_array;
 current_scene_sub_object_array += *number_of_sub_objects;

 for (int sub_object_count = 0; sub_object_count < *number_of_sub_objects; sub_object_count++)
  initialise_3d_sub_object(fp, parent, &(*sub_objects)[sub_object_count]);
}

int read_new_camera(FILE *fp)
{
 OBJECT_3D_SCENE_CAMERA camera;

 camera.target_sub_object_id = get_subobject(fp);

 fread(&camera.heading_locked, sizeof(int), 1, fp);
 fread(&camera.pitch_locked, sizeof(int), 1, fp);
 fread(&camera.roll_locked, sizeof(int), 1, fp);

 read_keyframes(fp, &camera.number_of_keyframes, &camera.keyframes);

 return cameras_.Append(camera);
}

void read_scene(FILE* fp, int version)
{
 if (version > -1 || version < -2)
  error("Scene file version %d is not supported", version);
 fread(&number_of_cameras, sizeof(int), 1, fp);
 if (number_of_cameras)
  {
   cameras = new OBJECT_3D_SCENE_CAMERA_INFO[number_of_cameras];
   for (int camera_count = 0; camera_count < number_of_cameras; camera_count++)
    {
     cameras[camera_count].camera_name_index = get_camera(fp);
     cameras[camera_count].camera_index = read_new_camera(fp);
    }
  }
 else
  cameras = NULL;

 fread(&number_of_scene_link_objects, sizeof(int), 1, fp);
 if (number_of_scene_link_objects)
  {
   scene_link_objects = new OBJECT_3D_SCENE_LINK_OBJECT [number_of_scene_link_objects];
   for (int tmp = 0; tmp < number_of_scene_link_objects; tmp++)
    {
     scene_link_objects[tmp].scene_index = get_scene(fp);
     fread(&scene_link_objects[tmp].x, sizeof(float), 1, fp);
     fread(&scene_link_objects[tmp].y, sizeof(float), 1, fp);
     fread(&scene_link_objects[tmp].z, sizeof(float), 1, fp);
     fread(&scene_link_objects[tmp].heading, sizeof(float), 1, fp);
     fread(&scene_link_objects[tmp].pitch, sizeof(float), 1, fp);
     fread(&scene_link_objects[tmp].roll, sizeof(float), 1, fp);
    }
  }
 else
  scene_link_objects = NULL;

 fread(&number_of_sprite_lights, sizeof(int), 1, fp);
 number_of_sprite_lights = number_of_sprite_lights;
 sprite_lights = NULL;
 if (number_of_sprite_lights)
  {
   sprite_lights = new OBJECT_3D_SPRITE_LIGHT[number_of_sprite_lights];
   for (int tmp = 0; tmp < number_of_sprite_lights; tmp++)
    {
     int red, green, blue;
     fread(&sprite_lights[tmp].position.x, sizeof(float), 1, fp);
     fread(&sprite_lights[tmp].position.y, sizeof(float), 1, fp);
     fread(&sprite_lights[tmp].position.z, sizeof(float), 1, fp);
     fread(&sprite_lights[tmp].scale.x, sizeof(float), 1, fp);
     fread(&sprite_lights[tmp].scale.y, sizeof(float), 1, fp);
     fread(&sprite_lights[tmp].scale.z, sizeof(float), 1, fp);
     fread(&red, sizeof(int), 1, fp);
     fread(&green, sizeof(int), 1, fp);
     fread(&blue, sizeof(int), 1, fp);
     sprite_lights[tmp].colour.red = red;
     sprite_lights[tmp].colour.green = green;
     sprite_lights[tmp].colour.blue = blue;
    }
  }

 if (version <= -2)
  fread(&number_of_ambient_lights, sizeof(int), 1, fp);
 else
  number_of_ambient_lights = 0;

 ambient_lights = NULL;

 if (number_of_ambient_lights)
  {
   ambient_lights = new OBJECT_3D_AMBIENT_LIGHT[number_of_ambient_lights];
   for (int tmp = 0; tmp < number_of_ambient_lights; tmp++)
    {
     fread(&ambient_lights[tmp].colour.red, sizeof(float), 1, fp);
     fread(&ambient_lights[tmp].colour.green, sizeof(float), 1, fp);
     fread(&ambient_lights[tmp].colour.blue, sizeof(float), 1, fp);

     ambient_lights[tmp].light_index = get_light(fp);
    }
  }

 if (version <= -2)
  fread(&number_of_distant_lights, sizeof(int), 1, fp);
 else
  number_of_distant_lights = 0;

 distant_lights = NULL;

 if (number_of_distant_lights)
  {
   distant_lights = new OBJECT_3D_DISTANT_LIGHT[number_of_distant_lights];
   for (int tmp = 0; tmp < number_of_distant_lights; tmp++)
    {
     fread(&distant_lights[tmp].heading, sizeof(float), 1, fp);
     fread(&distant_lights[tmp].pitch, sizeof(float), 1, fp);
     fread(&distant_lights[tmp].roll, sizeof(float), 1, fp);

     fread(&distant_lights[tmp].colour.red, sizeof(float), 1, fp);
     fread(&distant_lights[tmp].colour.green, sizeof(float), 1, fp);
     fread(&distant_lights[tmp].colour.blue, sizeof(float), 1, fp);

     distant_lights[tmp].light_index = get_light(fp);
    }
  }

 fread(&total_number_of_sub_objects, sizeof(int), 1, fp);
 fread(&total_number_of_sub_object_indices, sizeof(int), 1, fp);
 if (total_number_of_sub_object_indices)
  current_scene_sub_object_index_array = new OBJECT_3D_SUB_OBJECT_INDEX[total_number_of_sub_object_indices];
 else
  current_scene_sub_object_index_array = NULL;
 if (total_number_of_sub_objects)
  current_scene_sub_object_array = new OBJECT_3D_DATABASE_ENTRY[total_number_of_sub_objects];
 else
  current_scene_sub_object_array = NULL;

 scene_sub_object_indices_array = current_scene_sub_object_index_array;
 scene_sub_object_array = current_scene_sub_object_array;

 fread(&number_of_texture_animations, sizeof(int), 1, fp);
 if (number_of_texture_animations)
  {
   texture_animations = new int[number_of_texture_animations];
   for (int tmp = 0; tmp < number_of_texture_animations; tmp++)
    fread(&texture_animations[tmp], sizeof(int), 1, fp);
  }
 else
  texture_animations = NULL;

 fread(&number_of_approximations, sizeof(int), 1, fp);
 index = get_object(fp);
 if (number_of_approximations)
  {
   approximations = new OBJECT_3D_APPROXIMATION_INFO[number_of_approximations];
   for (int approximation = 0; approximation < number_of_approximations; approximation++)
    {
     approximations[approximation].object_number = get_object(fp);
     fread(&approximations[approximation].distance, sizeof(float), 1, fp);
    }
  }

 fread(&shadow_approximation_index, sizeof(int), 1, fp);

 shadow_polygon_object_index = get_object(fp);
 fread(&shadow_polygon_object_scale.x, sizeof(float), 1, fp);
 fread(&shadow_polygon_object_scale.y, sizeof(float), 1, fp);
 fread(&shadow_polygon_object_scale.z, sizeof(float), 1, fp);

 collision_object_index = get_object(fp);
 if (!collision_object_index)
  collision_object_index = -1;

 read_keyframes(fp, &number_of_keyframes, &keyframes);

 fseek(fp, sizeof(float), SEEK_CUR);

 read_value_keyframes(fp, &number_of_object_dissolve_keyframes, &object_dissolve_keyframes);

 read_value_keyframes(fp, &number_of_displacement_amplitude_keyframes, &displacement_amplitude_keyframes);

 read_indices(fp, &number_of_sub_object_indices, &sub_object_indices);

 read_subobjects(fp, &number_of_sub_objects, &sub_objects, NULL);

 QuickSearch quick(*this);
}
