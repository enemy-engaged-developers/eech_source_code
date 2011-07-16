#include "lws_exp.hpp"

#ifndef NO_LWSFILEEXPORTER
class LwsFileExporter : public LwsExporter
{
 public:

 LwsFileExporter(const AllNames& names, Translator& translator, const char* filename)
  : names(names), translator(translator),
    fp(safe_fopen(filename, "w"))
 {
 }

 ~LwsFileExporter(void)
 {
  fclose(fp);
 }

 void Begin(void)
 {
#ifdef SCENE_3
  fprintf(fp, "LWSC\n3\n\nFirstFrame 0\nLastFrame 600\nFramesPerSecond 30\n"); //FIXME
#else
  fprintf(fp, "LWSC\n4\n\nFirstFrame 0\nLastFrame 600\nFramesPerSecond 30\n"); //FIXME
#endif
 }

 void End(void)
 {
 }

 void Object(int index, int number, int sub_object_index, int special, const char* null_special = NULL)
 {
#ifdef SCENE_3
  (void)index;
#endif
  fprintf(fp, "\n");
  if (number)
#ifdef SCENE_3
   fprintf(fp, "LoadObjectLayer 1 %s.LWO\n", translator(number));
#else
   fprintf(fp, "LoadObjectLayer 1 %08X %s.LWO\n", 0x10000000 + index, translator(number));
#endif
  else
   {
    if (null_special)
#ifdef SCENE_3
     fprintf(fp, "AddNullObject NullObject (%s)\n", null_special);
#else
     fprintf(fp, "AddNullObject %08X NullObject (%s)\n", 0x10000000 + index, null_special);
#endif
    else
#ifdef SCENE_3
     fprintf(fp, "AddNullObject NullObject\n");
#else
     fprintf(fp, "AddNullObject %08X NullObject\n", 0x10000000 + index);
#endif
   }
  const char* special_txt = 0;
  switch (special)
   {
    case 0:
     if (sub_object_index)
      special_txt = names.SubObjects[sub_object_index];
     break;
    case -1:
     special_txt = "SHADOW_OBJECT";
     break;
    case -2:
     special_txt = "COLLISION_OBJECT";
     break;
    default:
     special_txt = names.Objects[special];
     break;
   }
  if (special_txt)
   fprintf(fp, "Plugin CustomObjHandler 1 LW_ItemShape\n4\n1\n1\n0\n0\n0\n0 0 0\n0 0 0\n0 0 0\n1\n0\n\"%s\"\nEndPlugin\n", special_txt);
 }

 void Parent(int index)
 {
  fprintf(fp, "ParentItem %08X\n", 0x10000000 + index);
 }
 void KeyFrames(const char* type, int visibility, int color, int number_of_keyframes, const OBJECT_3D_SUB_OBJECT_KEYFRAME* keyframes)
 {
  fprintf(fp, "Show%s %i %i\n%sMotion\nNumChannels 9\n", type, visibility, color, type);
  for (int c = 0; c < 9; c++)
   {
    fprintf(fp, "Channel %i\n{ Envelope\n  %i\n", c, number_of_keyframes);
    for (int i = 0; i < number_of_keyframes; i++)
     {
      const OBJECT_3D_SUB_OBJECT_KEYFRAME* f = &keyframes[i];
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
      fprintf(fp, "  Key %f %f %i %f %f %f 0 0 0\n", value, f->index / 30.0, f->linear ? 3 : 0, f->tension, f->continuity, f->bias);
     }
    fprintf(fp, "  Behaviors 1 2\n}\n");
   }
 }

 void Limits(const char* l, double min, double max)
 {
  fprintf(fp, "%sLimits %f %f\n", l, deg(min), deg(max));
 }

 void LODs(int number_of_approximation_info, const OBJECT_3D_APPROXIMATION_INFO* approximation_info)
 {
  int i;
  fprintf(fp, "Plugin ObjReplacementHandler 1 LW_Level_Of_Detail\n1\n%i\n", number_of_approximation_info);
  for (i = 0; i < number_of_approximation_info; i++)
   {
    const OBJECT_3D_APPROXIMATION_INFO* ap = approximation_info + i;
    fprintf(fp, "%f\n", ap->distance);
    if (ap->object_number)
     fprintf(fp, "\"%s.LWO\"\n", translator(ap->object_number));
    else
     fprintf(fp, "\"NullObject\"\n");
   }
  fprintf(fp, "EndPlugin\n");
 }

 void Collision(void)
 {
   fprintf(fp, "Plugin CustomObjHandler 1 FX_Collision\nformat 2\n collision 0 0 2 3 0 0 0\n collision 0 1 0 0 0 0 0 0\n collision 0\nEndPlugin\n");
 }

 void Dissolve(int number_of_object_dissolve_keyframes, const OBJECT_3D_SUB_OBJECT_VALUE_KEYFRAME* object_dissolve_keyframes)
 {
  fprintf(fp, "ObjectDissolve (envelope)\n{ Envelope\n  %i\n", number_of_object_dissolve_keyframes);
  for (int i = 0; i < number_of_object_dissolve_keyframes; i++)
   {
    const OBJECT_3D_SUB_OBJECT_VALUE_KEYFRAME* f = &object_dissolve_keyframes[i];
    fprintf(fp, "  Key %f %i %i %f %f %f 0 0 0\n", f->value, f->index, f->linear ? 3 : 0, f->tension, f->continuity, f->bias);
   }
  fprintf(fp, "  Behaviors 1 2\n}\n");
 }

 void Ambient(void)
 {
  fprintf(fp, "\nAmbientColor 1 1 1\nAmbientIntensity 0.500000\n\n");
 }

 void Light(int index)
 {
#ifdef SCENE_3
  (void)index;
#endif
#ifdef SCENE_3
  fprintf(fp, "AddLight\nLightName Light\n");
#else
  fprintf(fp, "AddLight %08X\nLightName Light\n", 0x20000000 + index);
#endif
 }

 void LightAttrs(const REAL_COLOUR* colour)
 {
  fprintf(fp, "LightColor %f %f %f\nLightIntensity 1.0\nLightType 1\n\n", colour->r / 255.0, colour->g / 255.0, colour->b / 255.0);
 }

#ifndef NO_LWSCAMERAEXPORT
 void Camera(int index, int name_index)
 {
#ifdef SCENE_3
  (void)index;
#endif
  if (name_index < 0 || (unsigned)name_index >= !names.Cameras)
   error("Invalid camera index\n");
#ifdef SCENE_3
  fprintf(fp, "\nAddCamera\nCameraName %s\n", names.Cameras[name_index]);
#else
  fprintf(fp, "\nAddCamera %08X\nCameraName %s\n", 0x30000000 + index, names.Cameras[name_index]);
#endif
 }

 void CameraAttrs(int heading_locked, int pitch_locked, int roll_locked, int root, int target_sub_object_index)
 {
  int locked = (heading_locked ? 8 : 0) | (pitch_locked ? 16 : 0) | (roll_locked ? 32 : 0);
  if (locked)
   fprintf(fp, "LockedChannels %i\n", locked);
  fprintf(fp, "ParentItem %08X\n", 0x10000000 + root);
  if (target_sub_object_index >= 0)
   fprintf(fp, "TargetItem %08X\n", 0x10000000 + target_sub_object_index);
 }
#endif

 private:

 const AllNames& names;
 Translator& translator;
 FILE* fp;
};
#endif

struct sub_object_key
{
 unsigned short int sub_object_index;
 unsigned char number_of_keyframes, number_of_object_dissolve_keyframes;
 unsigned char collision_contribution:1;
 const OBJECT_3D_SUB_OBJECT_KEYFRAME* keyframes;
 const OBJECT_3D_SUB_OBJECT_VALUE_KEYFRAME* object_dissolve_keyframes;
#ifndef NATIVE_TYPES
 int flag;
#endif
 float object_dissolve, relative_heading_minimum, relative_heading_maximum, relative_pitch_minimum, relative_pitch_maximum, relative_roll_minimum, relative_roll_maximum;
};

struct sub_object_lod
{
 unsigned short int index;
 unsigned char sub_object_approximation_in_level, sub_object_approximation_out_level;
};

struct sub_object_info
{
 const OBJECT_3D_SCENE_DATABASE_ENTRY* scene;
 int* target_sub_object_index;
 LwsExporter* ex;
 int& current;

 sub_object_info(const OBJECT_3D_SCENE_DATABASE_ENTRY* scene, int* target_sub_object_index, LwsExporter* ex, int& current)
  : scene(scene), target_sub_object_index(target_sub_object_index), ex(ex), current(current)
 {
 }
};

struct sub_object
{
 static const int max_lods = 16;
 static const int max_sub_objects = 100;

 static sub_object_info* G_info;


 sub_object_key key;
 int number_of_lods;
 sub_object_lod lods[max_lods + 1];
 int number_of_sub_objects;
 sub_object* sub_objects[max_sub_objects];

 sub_object(void) : number_of_lods(0), number_of_sub_objects(0) {}
 ~sub_object(void) { for (int i = 0; i < number_of_sub_objects; i++) delete sub_objects[i]; }

 int suits(const OBJECT_3D_DATABASE_ENTRY* sub, int sub_object_index) const
 {
  if (sub->sub_object_approximation_out_level < sub->sub_object_approximation_in_level)
   error("Error in aproximation levels");
  if (sub->sub_object_approximation_in_level < 1)
   error("Error in aproximation in level");

#define CH_EQ(x) if (sub->x != key.x) return 0;

  for (int i = 0; i < number_of_lods; i++)
   if (sub->sub_object_approximation_out_level >= lods[i].sub_object_approximation_in_level && sub->sub_object_approximation_in_level <= lods[i].sub_object_approximation_out_level)
    return 0;

  if (sub_object_index != key.sub_object_index)
   return 0;
  CH_EQ(number_of_keyframes)
  CH_EQ(number_of_object_dissolve_keyframes)
  CH_EQ(collision_contribution)
  CH_EQ(object_dissolve)
#ifndef NATIVE_TYPES
  CH_EQ(flag)
#endif
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

#undef CH_EQ

  return 1;
 }

 void add(int number_of_sub_objects_, const OBJECT_3D_DATABASE_ENTRY* sub)
 {
  for (int i = 0; i < number_of_sub_objects_; i++)
   {
    if (sub[i].sub_object_approximation_in_level > G_info->scene->number_of_approximations + 1)
     continue;

    int sub_object_index = 0;
    for (int j = 0; j < G_info->scene->number_of_sub_object_table_entries && !sub_object_index; j++)
     {
      const OBJECT_3D_SCENE_SUB_OBJECT_TABLE_ENTRY* t = &G_info->scene->sub_object_indices_table[j];
      for (int k = 0; k < t->number_of_sub_objects; k++)
       if (t->sub_objects[k] == &sub[i])
        {
         sub_object_index = t->sub_object_index;
         break;
        }
     }

    sub_object* added = NULL;
    for (int j = 0; j < number_of_sub_objects; j++)
     if (sub_objects[j]->suits(&sub[i], sub_object_index))
      {
       added = sub_objects[j];
       break;
      }
    if (!added)
     {
      if (number_of_sub_objects >= sub_object::max_sub_objects)
       error("Too many subobjects");
      added = sub_objects[number_of_sub_objects++] = new sub_object;

#define AS(x) added->key.x = sub[i].x;

      added->key.sub_object_index = sub_object_index;
      AS(number_of_keyframes)
      AS(number_of_object_dissolve_keyframes)
      AS(collision_contribution)
      AS(keyframes)
      AS(object_dissolve_keyframes)
      AS(object_dissolve)
#ifndef NATIVE_TYPES
      AS(flag)
#endif
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

    added->add(sub[i].number_of_sub_objects, sub[i].sub_objects);
   }
 }

 void do_export(int parent)
 {
  for (int i = 0; i < number_of_lods - 1; i++)
   {
    int k = i;
    for (int j = i + 1; j < number_of_lods; j++)
     if (lods[j].sub_object_approximation_in_level < lods[k].sub_object_approximation_in_level)
      k = j;
    if (k != i)
     {
      sub_object_lod lod = lods[i];
      lods[i] = lods[k];
      lods[k] = lod;
     }
   }

  for (int i = 0; i < number_of_lods; i++)
   assert(lods[i].sub_object_approximation_in_level <= G_info->scene->number_of_approximations + 1);

  {
   int i = 1;
   for (int j = 1; j < number_of_lods; j++)
    {
     if (lods[j].index == lods[i - 1].index && lods[j].sub_object_approximation_in_level <= lods[i - 1].sub_object_approximation_out_level)
      {
       if (lods[j].sub_object_approximation_out_level > lods[i - 1].sub_object_approximation_out_level)
        lods[i - 1].sub_object_approximation_out_level = lods[j].sub_object_approximation_out_level;
      }
     else
      {
       if (i != j)
        lods[i] = lods[j];
       i++;
      }
    }
   number_of_lods = i;
  }

  while (number_of_lods > 1 && lods[number_of_lods - 1].index == 0)
   number_of_lods--;

  if (lods[number_of_lods - 1].index && lods[number_of_lods - 1].sub_object_approximation_out_level < G_info->scene->number_of_approximations + 1)
   {
    lods[number_of_lods].index = 0;
    lods[number_of_lods].sub_object_approximation_in_level = lods[number_of_lods - 1].sub_object_approximation_out_level + 1;
    lods[number_of_lods].sub_object_approximation_out_level = G_info->scene->number_of_approximations + 1;
    number_of_lods++;
   }

  int current_lod = 0;
  if (lods[0].sub_object_approximation_in_level == 1)
   {
    G_info->ex->Object(++G_info->current, lods[0].index, key.sub_object_index);
    current_lod = 1;
   }
  else
   G_info->ex->Object(++G_info->current, 0, key.sub_object_index);

  if (key.sub_object_index && G_info->target_sub_object_index[key.sub_object_index] < 0)
   G_info->target_sub_object_index[key.sub_object_index] = G_info->current;

  if (number_of_lods > current_lod)
   {
    int real_number_of_lods = number_of_lods - current_lod;
    OBJECT_3D_APPROXIMATION_INFO* approximation_info = new OBJECT_3D_APPROXIMATION_INFO[real_number_of_lods];
    OBJECT_3D_APPROXIMATION_INFO* ap = approximation_info;
    for (; current_lod < number_of_lods; current_lod++, ap++)
     {
      if (lods[current_lod].sub_object_approximation_in_level < 2)
       error("error in approximation in level");
      ap->distance = G_info->scene->approximations[lods[current_lod].sub_object_approximation_in_level - 2].distance;
      ap->object_number = lods[current_lod].index;
     }
    G_info->ex->LODs(real_number_of_lods, approximation_info);
    delete [] approximation_info;
   }

  G_info->ex->KeyFrames("Object", 7, 3, key.number_of_keyframes, key.keyframes);
  G_info->ex->Parent(parent);
#ifndef NATIVE_TYPES
  if (key.flag)
   {
    G_info->ex->Limits("H", key.relative_heading_minimum, key.relative_heading_maximum);
    G_info->ex->Limits("P", key.relative_pitch_minimum, key.relative_pitch_maximum);
    G_info->ex->Limits("B", key.relative_roll_minimum, key.relative_roll_maximum);
   }
#endif
  if (key.collision_contribution)
   G_info->ex->Collision();

  make_export(G_info->current);
 }

 void make_export(int parent)
 {
  for (int i = 0; i < number_of_sub_objects; i++)
   sub_objects[i]->do_export(parent);
 }

 private:

 sub_object(sub_object&)
 {
  abort();
 }
 void operator =(sub_object&)
 {
  abort();
 }
};

sub_object_info* sub_object::G_info;

void LwsExport::ExportScene(LwsExporter* ex_, const OBJECT_3D_SCENE_DATABASE_ENTRY* scene, bool show_warnings)
{
 ex = ex_;
 current = -1;

 ex->Begin();

 if (show_warnings)
  {
   if (scene->number_of_displacement_amplitude_keyframes)
    printf("\tDisplacement animation is not exported as a part of LWS file\n");
   if (scene->shadow_approximation_index > 0)
    printf("\tShadow approximation %i not supported yet\n", scene->shadow_approximation_index);
  }

 if (scene->shadow_polygon_object_index > 0)
  {
   ex->Object(++current, scene->shadow_polygon_object_index, 0, -1);
   const OBJECT_3D_SUB_OBJECT_KEYFRAME keyframe = { 0, 0, 50, 0, 0, 0, 0, 0, scene->shadow_polygon_object_scale.x, scene->shadow_polygon_object_scale.y, scene->shadow_polygon_object_scale.z, 0, 0, 0 };
   ex->KeyFrames("Object", 7, 3, 1, &keyframe);
  }

 if (scene->collision_object_index > 0)
  {
   ex->Object(++current, scene->collision_object_index, 0, -2);
   const OBJECT_3D_SUB_OBJECT_KEYFRAME keyframe = { 0, 0, -50, 0, 0, 0, 0, 0, 1.0, 1.0, 1.0, 0, 0, 0 };
   ex->KeyFrames("Object", 7, 3, 1, &keyframe);
  }

 for (int i = 0; i < scene->number_of_scene_link_objects; i++)
  {
   const OBJECT_3D_SCENE_LINK_OBJECT* link = &scene->scene_link_objects[i];

   ex->Object(++current, 0, 0, link->scene_index, "LINK_OBJECT");
   const OBJECT_3D_SUB_OBJECT_KEYFRAME keyframe = { 0, 0, link->x, link->y, link->z, link->heading, link->pitch, link->roll, 1.0, 1.0, 1.0, 0, 0, 0 };
   ex->KeyFrames("Object", 7, 3, 1, &keyframe);
  }

 ex->Object(++current, scene->index, 0);
 ex->KeyFrames("Object", 7, 3, scene->number_of_keyframes, scene->keyframes);
 if (scene->number_of_approximations)
  {
   OBJECT_3D_APPROXIMATION_INFO* all;
   OBJECT_3D_APPROXIMATION_INFO* current;
   all = new OBJECT_3D_APPROXIMATION_INFO [ scene->number_of_approximations + 1 ];
   current = all;
   current->object_number = scene->index;
   current->distance = 0.0;
   for (int i = 0; i < scene->number_of_approximations; i++)
    {
     if (scene->approximations[i].object_number != current->object_number)
      {
       current++;
       *current = scene->approximations[i];
      }
    }
   if (current != all)
    ex->LODs(current - all, all + 1);
   delete [] all;
  }

 if (scene->number_of_object_dissolve_keyframes)
  ex->Dissolve(scene->number_of_object_dissolve_keyframes, scene->object_dissolve_keyframes);

 target_sub_object_index = new int [MAX_NUMBER_OF_SUB_OBJECT_INDICES];
 for (unsigned i = 0; i < MAX_NUMBER_OF_SUB_OBJECT_INDICES; i++)
  target_sub_object_index[i] = -1;

 int root = current;
 {
  sub_object::G_info = new sub_object_info(scene, target_sub_object_index, ex, current);
  sub_object sub;
  sub.add(scene->number_of_sub_objects, scene->sub_objects);
  sub.make_export(root);
  delete sub_object::G_info;
  sub_object::G_info = NULL;
 }

 ex->Ambient();
 for (int i = 0; i < scene->number_of_sprite_lights; i++)
  {
   const OBJECT_3D_SPRITE_LIGHT* s = &scene->sprite_lights[i];
   const OBJECT_3D_SUB_OBJECT_KEYFRAME keyframe = { 0, 0, s->position.x, s->position.y, s->position.z, 0, 0, 0, s->scale.x, s->scale.y, s->scale.z, 0, 0, 0 };
   ex->Light(i);
   ex->KeyFrames("Light", 0, 7, 1, &keyframe);
   ex->LightAttrs(&s->colour);
  }

#ifndef NO_LWSCAMERAEXPORT
 for (int i = 0; i < scene->number_of_cameras; i++)
  {
   const OBJECT_3D_SCENE_CAMERA_INFO* s = &scene->cameras[i];
   if (s->camera_index >= cameras.GetNumberOfCameras())
    error("Invalid camera index\n");
   const OBJECT_3D_SCENE_CAMERA* c = &cameras.GetCamera(s->camera_index);
   ex->Camera(i, s->camera_name_index);
   ex->KeyFrames("Camera", 7, 3, c->number_of_keyframes, c->keyframes);
   ex->CameraAttrs(c->heading_locked, c->pitch_locked, c->roll_locked, root, c->target_sub_object_id >= 0 ? target_sub_object_index[c->target_sub_object_id] : -1);
  }
#endif

 delete [] target_sub_object_index;
 target_sub_object_index = NULL;

 ex->End();
}

#ifndef NO_LWSFILEEXPORTER
void LwsExport::ExportScene(const AllNames& names, Translator& translator, const char* filename, const OBJECT_3D_SCENE_DATABASE_ENTRY& scene)
{
 //scene.print();
 LwsFileExporter exporter(names, translator, filename);
 ExportScene(&exporter, &scene, true);
}
#endif
