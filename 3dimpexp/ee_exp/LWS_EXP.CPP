class LwsExport
{

 private:

struct sub_object_key
{
 unsigned short int sub_object_index;
 unsigned char number_of_keyframes, number_of_object_dissolve_keyframes;
 unsigned char collision_contribution:1;
 struct OBJECT_3D_SUB_OBJECT_KEYFRAME *keyframes;
 struct OBJECT_3D_SUB_OBJECT_VALUE_KEYFRAME *object_dissolve_keyframes;
 int flag;
 float object_dissolve, relative_heading_minimum, relative_heading_maximum, relative_pitch_minimum, relative_pitch_maximum, relative_roll_minimum, relative_roll_maximum;
};

struct sub_object_lod
{
 unsigned short int index;
 unsigned char sub_object_approximation_in_level, sub_object_approximation_out_level;
};

struct sub_object
{
 static const int max_lods = 16;
 static const int max_sub_objects = 100;

 sub_object_key key;
 int number_of_lods;
 sub_object_lod lods[max_lods + 1];
 int number_of_sub_objects;
 sub_object* sub_objects[max_sub_objects];

 sub_object(void) : number_of_lods(0), number_of_sub_objects(0) {}
 ~sub_object(void) { for (int i = 0; i < number_of_sub_objects; i++) delete sub_objects[i]; }
};


int sub_object_suits(sub_object* subo, struct OBJECT_3D_DATABASE_ENTRY* sub, int sub_object_index)
{
 if (sub->sub_object_approximation_out_level < sub->sub_object_approximation_in_level)
  error("Error in aproximation levels");

#define CH_EQ(x) if (sub->x != subo->key.x) return 0;

 for (int i = 0; i < subo->number_of_lods; i++)
  if (sub->sub_object_approximation_out_level >= subo->lods[i].sub_object_approximation_in_level &&
      sub->sub_object_approximation_in_level <= subo->lods[i].sub_object_approximation_out_level &&
      sub->index != subo->lods[i].index)
   return 0;

 if (sub_object_index != subo->key.sub_object_index)
  return 0;
 CH_EQ(number_of_keyframes)
 CH_EQ(number_of_object_dissolve_keyframes)
 CH_EQ(collision_contribution)
 CH_EQ(object_dissolve)
 CH_EQ(flag)
 CH_EQ(relative_heading_minimum)
 CH_EQ(relative_heading_maximum)
 CH_EQ(relative_pitch_minimum)
 CH_EQ(relative_pitch_maximum)
 CH_EQ(relative_roll_minimum)
 CH_EQ(relative_roll_maximum)

 for (int i = 0; i < sub->number_of_keyframes; i++)
  {
   CH_EQ(keyframes[i].index)
   CH_EQ(keyframes[i].linear)
   CH_EQ(keyframes[i].x)
   CH_EQ(keyframes[i].y)
   CH_EQ(keyframes[i].z)
   CH_EQ(keyframes[i].heading)
   CH_EQ(keyframes[i].pitch)
   CH_EQ(keyframes[i].roll)
   CH_EQ(keyframes[i].scale_x)
   CH_EQ(keyframes[i].scale_y)
   CH_EQ(keyframes[i].scale_z)
   CH_EQ(keyframes[i].tension)
   CH_EQ(keyframes[i].continuity)
   CH_EQ(keyframes[i].bias)
  }

 for (int i = 0; i < sub->number_of_object_dissolve_keyframes; i++)
  {
   CH_EQ(object_dissolve_keyframes[i].index)
   CH_EQ(object_dissolve_keyframes[i].linear)
   CH_EQ(object_dissolve_keyframes[i].value)
   CH_EQ(object_dissolve_keyframes[i].tension)
   CH_EQ(object_dissolve_keyframes[i].continuity)
   CH_EQ(object_dissolve_keyframes[i].bias)
  }

 return 1;

#undef CH_EQ
}

const OBJECT_3D_SCENE_DATABASE_ENTRY* G_scene;

void sub_object_add(sub_object* subo, int number_of_sub_objects, struct OBJECT_3D_DATABASE_ENTRY* sub)
{
 for (int i = 0; i < number_of_sub_objects; i++)
  {
   int sub_object_index = 0;
   for (int j = 0; j < G_scene->number_of_sub_object_table_entries && !sub_object_index; j++)
    {
     struct OBJECT_3D_SCENE_SUB_OBJECT_TABLE_ENTRY* t = &G_scene->sub_object_indices_table[j];
     for (int k = 0; k < t->number_of_sub_objects; k++)
      if (t->sub_objects[k] == &sub[i])
       {
        sub_object_index = t->sub_object_index;
        break;
       }
    }

   sub_object* added = NULL;
   for (int j = 0; j < subo->number_of_sub_objects; j++)
    if (sub_object_suits(subo->sub_objects[j], &sub[i], sub_object_index))
     {
      added = subo->sub_objects[j];
      break;
     }
   if (!added)
   {
    if (subo->number_of_sub_objects >= sub_object::max_sub_objects)
     error("Too many subobjects");
    added = subo->sub_objects[subo->number_of_sub_objects++] = new sub_object;

#define AS(x) added->key.x = sub[i].x;

    added->key.sub_object_index = sub_object_index;
    AS(number_of_keyframes)
    AS(number_of_object_dissolve_keyframes)
    AS(collision_contribution)
    AS(keyframes)
    AS(object_dissolve_keyframes)
    AS(object_dissolve)
    AS(flag)
    AS(relative_heading_minimum)
    AS(relative_heading_maximum)
    AS(relative_pitch_minimum)
    AS(relative_pitch_maximum)
    AS(relative_roll_minimum)
    AS(relative_roll_maximum)

#undef AS
   }

   if (added->number_of_lods >= sub_object::max_lods)
    error("Too many lods");

#define AS(x) added->lods[added->number_of_lods].x = sub[i].x;

   AS(index)
   AS(sub_object_approximation_in_level)
   AS(sub_object_approximation_out_level)

#undef AS

   added->number_of_lods++;

   sub_object_add(added, sub[i].number_of_sub_objects, sub[i].sub_objects);
  }
}

int current;
void ExportObject(FILE* fp, int index, int sub_object_index, const char* special = NULL, const char* null_special = NULL)
{
 fprintf(fp, "\n");
 current++;
 if (index)
#ifdef SCENE_3
  fprintf(fp, "LoadObjectLayer 1 %s.LWO\n", translator(index));
#else
  fprintf(fp, "LoadObjectLayer 1 %08X %s.LWO\n", 0x10000000 + current, translator(index));
#endif
 else
  {
   if (null_special)
#ifdef SCENE_3
    fprintf(fp, "AddNullObject NullObject (%s)\n", null_special);
#else
    fprintf(fp, "AddNullObject %08X NullObject (%s)\n", 0x10000000 + current, null_special);
#endif
   else
#ifdef SCENE_3
    fprintf(fp, "AddNullObject NullObject\n");
#else
    fprintf(fp, "AddNullObject %08X NullObject\n", 0x10000000 + current);
#endif
  }
 if (!special && sub_object_index)
  special = names.SubObjects[sub_object_index];
 if (special)
  fprintf(fp, "Plugin CustomObjHandler 1 LW_ItemShape\n4\n1\n1\n0\n0\n0\n0 0 0\n0 0 0\n0 0 0\n1\n0\n\"%s\"\nEndPlugin\n", special);
}
void ExportKeyFrames(FILE* fp, const char* type, int visibility, int color, int number_of_keyframes, struct OBJECT_3D_SUB_OBJECT_KEYFRAME* keyframes)
{
 fprintf(fp, "Show%s %i %i\n%sMotion\nNumChannels 9\n", type, visibility, color, type);
 for (int c = 0; c < 9; c++)
  {
   fprintf(fp, "Channel %i\n{ Envelope\n  %i\n", c, number_of_keyframes);
   for (int i = 0; i < number_of_keyframes; i++)
    {
     struct OBJECT_3D_SUB_OBJECT_KEYFRAME* f = &keyframes[i];
     float value;
     switch (c)
      {
       case 0:
        value = f->x;
        break;
       case 1:
        value = f->y;
        break;
       case 2:
        value = f->z;
        break;
       case 3:
        value = f->heading;
        break;
       case 4:
        value = f->pitch;
        break;
       case 5:
        value = f->roll;
        break;
       case 6:
        value = f->scale_x;
        break;
       case 7:
        value = f->scale_y;
        break;
       case 8:
        value = f->scale_z;
        break;
      }
     fprintf(fp, "  Key %f %i %i %f %f %f 0 0 0\n", value, f->index, f->linear ? 3 : 0, f->tension, f->continuity, f->bias);
    }
   fprintf(fp, "  Behaviors 1 2\n}\n");
  }
}

void ExportLimits(FILE* fp, const char* l, double min, double max)
{
 fprintf(fp, "%sLimits %f %f\n", l, deg(min), deg(max));
}

int target_sub_object_index[OBJECT_3D_SUB_OBJECT_LAST];

void sub_object_export(FILE* fp, sub_object* subo, int parent)
{
 for (int i = 0; i < subo->number_of_lods - 1; i++)
  {
   int k = i;
   for (int j = i + 1; j < subo->number_of_lods; j++)
    if (subo->lods[j].sub_object_approximation_in_level < subo->lods[k].sub_object_approximation_in_level)
     k = j;
   if (k != i)
    {
     sub_object_lod lod = subo->lods[i];
     subo->lods[i] = subo->lods[k];
     subo->lods[k] = lod;
    }
  }

 //FIXME
 for (int i = 0; i < subo->number_of_lods; i++)
  if (subo->lods[i].sub_object_approximation_in_level > G_scene->number_of_approximations + 1)
   subo->lods[i].sub_object_approximation_in_level = G_scene->number_of_approximations + 1;

 {
  int i = 1;
  for (int j = 1; j < subo->number_of_lods; j++)
   {
    if (subo->lods[j].index == subo->lods[i - 1].index &&
        subo->lods[j].sub_object_approximation_in_level <= subo->lods[i - 1].sub_object_approximation_out_level)
     {
      if (subo->lods[j].sub_object_approximation_out_level > subo->lods[i - 1].sub_object_approximation_out_level)
       subo->lods[i - 1].sub_object_approximation_out_level = subo->lods[j].sub_object_approximation_out_level;
     }
    else
     {
      if (i != j)
       subo->lods[i] = subo->lods[j];
      i++;
     }
   }
  subo->number_of_lods = i;
 }

 while (subo->number_of_lods > 1 && subo->lods[subo->number_of_lods - 1].index == 0)
  subo->number_of_lods--;
  //if (subo->lods[subo->number_of_lods - 1].sub_object_approximation_in_level > G_scene->number_of_approximations + 1)
  // error("Too great lod distance");

 if (subo->lods[subo->number_of_lods - 1].index && subo->lods[subo->number_of_lods - 1].sub_object_approximation_out_level < G_scene->number_of_approximations + 1)
  {
   subo->lods[subo->number_of_lods].index = 0;
   subo->lods[subo->number_of_lods].sub_object_approximation_in_level = subo->lods[subo->number_of_lods - 1].sub_object_approximation_out_level + 1;
   subo->lods[subo->number_of_lods].sub_object_approximation_out_level = G_scene->number_of_approximations + 1;
   subo->number_of_lods++;
  }


 int i = 0;
 if (subo->lods[0].sub_object_approximation_in_level == 1)
  {
   ExportObject(fp, subo->lods[0].index, subo->key.sub_object_index);
   i = 1;
  }
 else
  ExportObject(fp, 0, subo->key.sub_object_index);

 if (subo->key.sub_object_index)
  {
   bool found = false;
   for (int i = 0; i < G_scene->number_of_cameras; i++)
    {
     struct OBJECT_3D_SCENE_CAMERA_INFO* s = &G_scene->cameras[i];
     if (s->camera_name_index < 0 || (unsigned)s->camera_name_index >= !names.Cameras || s->camera_index >= cameras.GetNumberOfCameras())
      error("Invalid camera index\n");
     const struct OBJECT_3D_SCENE_CAMERA* c = &cameras.GetCamera(s->camera_index);
     if (c->target_sub_object_id == subo->key.sub_object_index)
      {
       found = true;
       break;
      }
    }
   if (found)
    {
     if (!target_sub_object_index[subo->key.sub_object_index])
      target_sub_object_index[subo->key.sub_object_index] = current;
    }
  }

 if (subo->number_of_lods > 1)
  {
   fprintf(fp, "Plugin ObjReplacementHandler 1 LW_Level_Of_Detail\n1\n");
   fprintf(fp, "%i\n", subo->number_of_lods - i);

   for (; i < subo->number_of_lods; i++)
    {
     fprintf(fp, "%f\n", G_scene->approximations[subo->lods[i].sub_object_approximation_in_level - 2].distance);
     if (subo->lods[i].index)
      fprintf(fp, "\"%s.LWO\"\n", translator(subo->lods[i].index));
     else
      fprintf(fp, "NullObject\n");
    }

   fprintf(fp, "EndPlugin\n");
  }

 ExportKeyFrames(fp, "Object", 7, 3, subo->key.number_of_keyframes, subo->key.keyframes);
 fprintf(fp, "ParentItem %08X\n", 0x10000000 + parent);
 if (subo->key.flag)
  {
   ExportLimits(fp, "H", subo->key.relative_heading_minimum, subo->key.relative_heading_maximum);
   ExportLimits(fp, "P", subo->key.relative_pitch_minimum, subo->key.relative_pitch_maximum);
   ExportLimits(fp, "B", subo->key.relative_roll_minimum, subo->key.relative_roll_maximum);
  }
 if (subo->key.collision_contribution)
  fprintf(fp, "Plugin CustomObjHandler 1 FX_Collision\nformat 2\n collision 0 0 2 3 0 0 0\n collision 0 1 0 0 0 0 0 0\n collision 0\nEndPlugin\n");

 sub_objects_export(fp, subo, current);
}

void sub_objects_export(FILE* fp, sub_object* subo, int parent)
{
  for (int i = 0; i < subo->number_of_sub_objects; i++)
   sub_object_export(fp, subo->sub_objects[i], parent);
}

void ExportScene(FILE* fp, const OBJECT_3D_SCENE_DATABASE_ENTRY* scene)
{
 if (scene->number_of_texture_animations)
  printf("\tTexture animation not supported\n");
 if (scene->number_of_displacement_amplitude_keyframes)
  printf("\tDisplacement animation not supported\n");
 if (scene->shadow_approximation_index > 0)
  printf("\tShadow approximation %i not supported\n", scene->shadow_approximation_index);

 current = -1;

#ifdef SCENE_3
 fprintf(fp, "LWSC\n3\n\nFirstFrame 0\nLastFrame 600\nFramesPerSecond 1\n"); //FIXME
#else
 fprintf(fp, "LWSC\n4\n\nFirstFrame 0\nLastFrame 600\nFramesPerSecond 1\n"); //FIXME
#endif

 if (scene->shadow_polygon_object_index > 0)
  {
   ExportObject(fp, scene->shadow_polygon_object_index, 0, "SHADOW_OBJECT");
   struct OBJECT_3D_SUB_OBJECT_KEYFRAME keyframe = { 0, 0, 50, 0, 0, 0, 0, 0, scene->shadow_polygon_object_scale.x, scene->shadow_polygon_object_scale.y, scene->shadow_polygon_object_scale.z };
   ExportKeyFrames(fp, "Object", 7, 3, 1, &keyframe);
  }

 if (scene->collision_object_index > 0)
  {
   ExportObject(fp, scene->collision_object_index, 0, "COLLISION_OBJECT");
   struct OBJECT_3D_SUB_OBJECT_KEYFRAME keyframe = { 0, 0, -50, 0, 0, 0, 0, 0, 1.0, 1.0, 1.0 };
   ExportKeyFrames(fp, "Object", 7, 3, 1, &keyframe);
  }

 for (int i = 0; i < scene->number_of_scene_link_objects; i++)
  {
   const struct OBJECT_3D_SCENE_LINK_OBJECT* link = &scene->scene_link_objects[i];

   ExportObject(fp, 0, 0, names.Objects[link->scene_index], "LINK_OBJECT");
   struct OBJECT_3D_SUB_OBJECT_KEYFRAME keyframe = { 0, 0, link->x, link->y, link->z, link->heading, link->pitch, link->roll, 1.0, 1.0, 1.0 };
   ExportKeyFrames(fp, "Object", 7, 3, 1, &keyframe);
  }

 ExportObject(fp, scene->index, 0);
 ExportKeyFrames(fp, "Object", 7, 3, scene->number_of_keyframes, scene->keyframes);
 if (scene->number_of_approximations)
  {
   struct OBJECT_3D_APPROXIMATION_INFO* last = &scene->approximations[scene->number_of_approximations - 1];
   while (last > scene->approximations && last->object_number == last[-1].object_number)
    last--;
   if (last->object_number != scene->index)
    {
     last++;
     fprintf(fp, "Plugin ObjReplacementHandler 1 LW_Level_Of_Detail\n1\n");
     fprintf(fp, "%i\n", last - scene->approximations);
     for (OBJECT_3D_APPROXIMATION_INFO* ap = scene->approximations; ap < last; ap++)
      {
       fprintf(fp, "%f\n", ap->distance);
       if (ap->object_number)
        fprintf(fp, "\"%s.LWO\"\n", translator(ap->object_number));
       else
        fprintf(fp, "NullObject\n");
      }
     fprintf(fp, "EndPlugin\n");
    }
  }

 if (scene->number_of_object_dissolve_keyframes)
  {
   fprintf(fp, "ObjectDissolve (envelope)\n{ Envelope\n  %i\n", scene->number_of_object_dissolve_keyframes);
   for (int i = 0; i < scene->number_of_object_dissolve_keyframes; i++)
    {
     const struct OBJECT_3D_SUB_OBJECT_VALUE_KEYFRAME* f = &scene->object_dissolve_keyframes[i];
     fprintf(fp, "  Key %f %i %i %f %f %f 0 0 0\n", f->value, f->index, f->linear ? 3 : 0, f->tension, f->continuity, f->bias);
    }
   fprintf(fp, "  Behaviors 1 2\n}\n");
  }

 int root = current;
 memset(target_sub_object_index, 0, sizeof(target_sub_object_index));
 {
  G_scene = scene;
  sub_object sub;
  sub_object_add(&sub, scene->number_of_sub_objects, scene->sub_objects);
  sub_objects_export(fp, &sub, root);
  G_scene = NULL;
 }

 fprintf(fp, "\nAmbientColor 1 1 1\nAmbientIntensity 0.500000\n\n");
 for (int i = 0; i < scene->number_of_sprite_lights; i++)
  {
   struct OBJECT_3D_SPRITE_LIGHT* s = &scene->sprite_lights[i];
   struct OBJECT_3D_SUB_OBJECT_KEYFRAME keyframe = { 0, 0, s->position.x, s->position.y, s->position.z, 0, 0, 0, s->scale.x, s->scale.y, s->scale.z };
#ifdef SCENE_3
   fprintf(fp, "AddLight\nLightName Light\n");
#else
   fprintf(fp, "AddLight %08X\nLightName Light\n", 0x20000000 + i);
#endif
   ExportKeyFrames(fp, "Light", 0, 7, 1, &keyframe);
   fprintf(fp, "LightColor %f %f %f\nLightIntensity 1.0\nLightType 1\n\n", s->colour.r / 255.0, s->colour.g / 255.0, s->colour.b / 255.0);
  }

 for (int i = 0; i < scene->number_of_cameras; i++)
  {
   struct OBJECT_3D_SCENE_CAMERA_INFO* s = &scene->cameras[i];
   if (s->camera_name_index < 0 || (unsigned)s->camera_name_index >= !names.Cameras || s->camera_index >= cameras.GetNumberOfCameras())
    error("Invalid camera index\n");
   const struct OBJECT_3D_SCENE_CAMERA* c = &cameras.GetCamera(s->camera_index);
#ifdef SCENE_3
   fprintf(fp, "\nAddCamera\nCameraName %s\n", names.Cameras[s->camera_name_index]);
#else
   fprintf(fp, "\nAddCamera %08X\nCameraName %s\n", 0x30000000 + i, names.Cameras[s->camera_name_index]);
#endif
   ExportKeyFrames(fp, "Camera", 7, 3, c->number_of_keyframes, c->keyframes);
   int locked = (c->heading_locked ? 8 : 0) | (c->pitch_locked ? 16 : 0) | (c->roll_locked ? 32 : 0);
   if (locked)
    fprintf(fp, "LockedChannels %i\n", locked);
   fprintf(fp, "ParentItem %08X\n", 0x10000000 + root);
   if (c->target_sub_object_id)
    {
     int object = target_sub_object_index[c->target_sub_object_id];
     if (object)
      fprintf(fp, "TargetItem %08X\n", 0x10000000 + object);
    }
  }
}


 const AllNames& names;
 const Cameras& cameras;
 typedef Array<int> ObjectSubobject;
 Translator& translator;

 public:

 LwsExport(const AllNames& names, const Cameras& cameras, Translator& translator)
  : names(names), cameras(cameras), translator(translator)
 {
 }

 ~LwsExport(void)
 {
 }

 void ExportScene(const char* filename, const OBJECT_3D_SCENE_DATABASE_ENTRY& scene)
 {
  printf("Exporting scene '%s'\n", filename);
  FILE* fp = safe_fopen(filename, "w");
  ExportScene(fp, &scene);
  fclose(fp);
 }
};
