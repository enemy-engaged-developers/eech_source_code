#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <vector>
#include <string>


template <typename T>
void PrintAll(T begin, T end)
{
 for (; begin != end; ++begin)
  begin->Print();
}

struct Key
{
 Key(void)
  : value(0), time(0), spantime(0)
 {
  for (size_t i = 0; i < sizeof(p) / sizeof(*p); i++)
   p[i] = 0;
 }

 void Print(void) const
 {
  printf("  Key %f %f %i %f %f %f %f %f %f\n", value, time, spantime, p[0], p[1], p[2], p[3], p[4], p[5]);
 }

 float value;
 float time;
 int spantime;
 float p[6];
};

struct Channel
{
 Channel(void)
  : pre(0), post(0)
 {
 }

 void Print(void) const
 {
  printf("{ Envelope\n");
  printf("  %u\n", keys.size());
  PrintAll(keys.begin(), keys.end());
  printf("  Behaviors %i %i\n", pre, post);
  printf("}\n");
 }

 typedef std::vector<Key> Keys;
 
 Keys keys;
 int pre, post;
};

struct Motion
{
 Motion(void)
  : nchannels(0), parent(0)
 {
 }

 void Print(void) const
 {
  printf("NumChannels %i\n", nchannels);
  for (int i = 0; i < nchannels; i++)
   {
    printf("Channel %i\n", i);
    channels[i].Print();
   }
  if (parent)
   printf("ParentItem %lX\n", parent);
 }

 int nchannels;
 Channel channels[9];
 long parent;
};

struct LOD
{
 float distance;
 std::string filename;

 void Print(void) const
 {
  printf("%f\n", distance);
  printf("%s\n", filename.c_str());
 }
};

struct PluginLod
{
 void Print(void) const
 {
  if (!lods.size())
   return;

  printf("Plugin ObjReplacementHandler 1 LW_Level_Of_Detail\n");
  printf("1\n");
  printf("%u\n", lods.size());
  PrintAll(lods.begin(), lods.end());
  printf("EndPlugin\n");
 }


 typedef std::vector<LOD> LODs;

 LODs lods;
};

struct GeneralObject
{
 GeneralObject(void)
  : visibility(0), color(0)
 {
 }

 void Print(const char* type) const
 {
  printf("Show%s %i %i\n", type, visibility, color);
  printf("%sMotion\n", type);
  motion.Print();
  lods.Print();
  printf("\n");
 }

 int visibility;
 int color;
 Motion motion;
 PluginLod lods;
 Channel dissolve;
};

struct Limits
{
 Limits(void)
  : set(false), min(0), max(0)
 {
 }

 void Print(const char* limit) const
 {
  if (set)
   printf("%sLimits %f %f\n", limit, min, max);
 }

 bool set;
 float min, max;
};

struct Collision
{
 Collision(void)
  : collision(false)
 {
 }

 void Print(void) const
 {
  if (!collision)
   return;

  printf("Plugin CustomObjHandler 1 FX_Collision\n");
  printf("format 2\n");
  printf(" collision 0 0 2 3 0 0 0\n");
  printf(" collision 0 1 0 0 0 0 0 0\n");
  printf(" collision 0\n");
  printf("EndPlugin\n");
 }

 bool collision;
};

struct Object : GeneralObject
{
 Object(void)
  : index(0), layer(-1)
 {
 }

 void Print(void) const
 {
  if (layer)
   printf("LoadObjectLayer %i %lX %s\n", layer, index, filename.c_str());
  else
   if (filename[0])
    printf("AddNullObject %lX NullObject (%s)\n", index, filename.c_str());
   else
    printf("AddNullObject %lX NullObject\n", index);
  GeneralObject::Print("Object");
  h.Print("H");
  p.Print("P");
  b.Print("B");
  collision.Print();
  if (dissolve.keys.size())
   {
    printf("ObjectDissolve (envelope)\n");
    dissolve.Print();
    printf("\n");
   }
 }

 long index;
 int layer;
 std::string filename;
 std::string search;
 Limits h, p, b;
 Collision collision;
};

struct Color
{
 Color(void)
  : red(0), green(0), blue(0)
 {
 }

 void Print(const char* type) const
 {
  printf("%sColor %f %f %f\n", type, red, green, blue);
 }

 float red, green, blue;
};

struct Light : GeneralObject
{
 Light(void)
  : index(0), intensity(0.0), type(0)
 {
 }

 void Print(void) const
 {
  printf("AddLight %lX\n", index);
  printf("LightName %s\n", name.c_str());
  GeneralObject::Print("Light");
  light.Print("Light");
  printf("LightIntensity %f\n", intensity);
  printf("LightType %i\n", type);
  printf("\n");
 }

 long index;
 std::string name;
 Color light;
 float intensity;
 int type;
};

struct Camera : GeneralObject
{
 Camera(void)
  : index(0), locked(0), target(0)
 {
 }

 void Print(void) const
 {
  printf("AddCamera %lX\n", index);
  printf("CameraName %s\n", name.c_str());
  GeneralObject::Print("Camera");
  printf("LockedChannels %u\n", locked);
  if (target)
   printf("TargetItem %lX\n", target);
  printf("\n");
 }

 long index;
 std::string name;
 unsigned locked;
 long target;
};

struct Lws
{
 Lws(void)
  : fps(1)
 {
 }

 void Print(void) const
 {
  printf("LWSC\n");
  printf("4\n");
  printf("\n");
  printf("FirstFrame 1\n");
  printf("LastFrame 600\n");
  printf("FramesPerSecond %f\n", fps);
  printf("\n");

  PrintAll(objects.begin(), objects.end());

  printf("AmbientColor 1 1 1\n");
  printf("AmbientIntensity 0.5\n");
  printf("\n");

  PrintAll(lights.begin(), lights.end());
  PrintAll(cameras.begin(), cameras.end());
 }

 typedef std::vector<Object> Objects;
 typedef std::vector<Light> Lights;
 typedef std::vector<Camera> Cameras;

 float fps;
 Objects objects;
 Lights lights;
 Cameras cameras;
};

class LwsFile : public Lws
{
 public:

 LwsFile(const char* filename)
 {
  clearlast();

  load(filename);
 }


 private:

 typedef void (LwsFile::*Processor)(void);
 struct ProcessorAssignment
 {
  const char* keyword;
  Processor processor;
 };
 static ProcessorAssignment Processors[];


 bool gets(void)
 {
  if (fgets(str, sizeof(str), fp))
   {
    line++;
    for (int i = strlen(str) - 1; i >= 0 && isspace(str[i]); str[i--] = '\0');
    return true;
   }
  str[0] = '\0';
  return false;
 }

 void findkeyword(void)
 {
  keyword.clear();
  int i = 0;
  while (str[i] && isspace(str[i]))
   i++;
  if (!str[i])
   return;
  int j = i + 1;
  while (str[j] && !isspace(str[j]))
   j++;
  keyword.assign(str + i, j - i);
  while (str[j] && isspace(str[j]))
   j++;
  memmove(str, str + j, sizeof(str) - j);
 }

 void clearlast(void)
 {
  LastGeneralObject = 0;
  LastObject = 0;
  LastLight = 0;
  LastCamera = 0;
 }

 void load(const char* filename)
 {
  line = 0;
  fp = fopen(filename, "r");
  if (!fp)
   error("Failed to open file %s", filename);

  if (!gets() || strcmp(str, "LWSC"))
   error("Provided file is not Lightwave Scene version 4");
  if (!gets() || strcmp(str, "4"))
   error("Provided file is not Lightwave Scene version 4");

  while (gets())
   {
    if (str[0] == '\0')
     continue;

    findkeyword();
    for (ProcessorAssignment* p = Processors; p->keyword; p++)
     if (keyword == p->keyword)
      {
       (this->*(p->processor))();
       break;
      }
   }

  fclose(fp);
 }

 void show(GeneralObject* general)
 {
  if (!general)
   error("Line %i: Show directive without previous object/light/camera", line);
  sscanf(str, "%i %i", &general->visibility, &general->color);
 }

 void ProcessFPS(void)
 {
  sscanf(str, "%f", &fps);
 }

 void SkipBlock(void)
 {
  int braces = 1;
  while (gets())
   {
    findkeyword();
    switch (keyword[0])
     {
      case '{':
       braces++;
       break;
      case '}':
       braces--;
       if (!braces)
        return;
       break;
     }
   }
 }

 void ProcessChannel(Channel& channel)
 {
  gets();
  gets();
  int index;
  sscanf(str, "%i", &index);
  for (int i = 0; i < index; i++)
   {
    Key key;
    gets();
    sscanf(str, "  Key %f %f %i %f %f %f %f %f %f",
           &key.value, &key.time, &key.spantime,
           &key.p[0], &key.p[1], &key.p[2], &key.p[3], &key.p[4], &key.p[5]);
    channel.keys.push_back(key);
   }
  gets();
  sscanf(str, "  Behaviors %i %i", &channel.pre, &channel.post);
  gets();
 }

 void ProcessChannel(void)
 {
  if (!LastGeneralObject)
   error("Line %i: Motion without previous object/light/camera", line);
  int index;
  sscanf(str, "%i", &index);
  ProcessChannel(LastGeneralObject->motion.channels[index]);
 }

 void ProcessMotion(void)
 {
  if (!LastGeneralObject)
   error("Line %i: Motion without previous object/light/camera", line);
  sscanf(str, "%i", &LastGeneralObject->motion.nchannels);
 }

 void ProcessShowObject(void)
 {
  show(LastObject);
 }

 void ProcessShowLight(void)
 {
  show(LastLight);
 }

 void ProcessShowCamera(void)
 {
  show(LastCamera);
 }

 void ProcessObjectMotion(void)
 {
  LastGeneralObject = LastObject;
 }

 void ProcessLightMotion(void)
 {
  LastGeneralObject = LastLight;
 }

 void ProcessCameraMotion(void)
 {
  LastGeneralObject = LastCamera;
 }

 void ProcessParent(void)
 {
  if (!LastGeneralObject)
   error("Line %i: Parent without previous object/light/camera", line);
  sscanf(str, "%lX", &LastGeneralObject->motion.parent);
 }

 void ProcessPlugin(void)
 {
  if (!strcmp(str, "ObjReplacementHandler 1 LW_Level_Of_Detail"))
   {
    if (!LastObject)
     error("Line %i: Plugin LOD without previous object", line);

    gets();
    gets();
    int lod = 0;
    sscanf(str, "%i", &lod);
    for (int i = 0; i < lod; i++)
     {
      LOD lod;
      gets();
      sscanf(str, "%f", &lod.distance);
      gets();
      if (str[0] && str[1])
       lod.filename.assign(str + 1, strlen(str) - 2);
      LastObject->lods.lods.push_back(lod);
     }
    gets();
   }
  else
  if (!strcmp(str, "CustomObjHandler 1 LW_ItemShape"))
   {
    for (int i = 0; i < 12; i++)
     gets();
    if (LastObject)
     LastObject->search.assign(str + 1, strlen(str) - 2);
    gets();
   }
  else
  if (!strcmp(str, "CustomObjHandler 1 FX_Collision"))
   {
    if (LastObject)
     LastObject->collision.collision = true;
    for (int i = 0; i < 5; i++)
     gets();
   }
  else
   {
    while (gets())
     {
      if (!strcmp(str, "EndPlugin"))
       break;
     }
   }

  if (strcmp(str, "EndPlugin"))
   error("Line %i: Plugin without EndPlugin at expected place", line);
 }

 void ProcessDissolve(void)
 {
  if (!LastObject)
   error("Line %i: ObjectDissolve without previous object", line);
  if (strcmp(str, "(envelope)"))
   return;
  ProcessChannel(LastObject->dissolve);
 }

 void ProcessLoad(void)
 {
  clearlast();
  Object object;

  findkeyword();
  sscanf(keyword.c_str(), "%i", &object.layer);
  findkeyword();
  sscanf(keyword.c_str(), "%lx", &object.index);
  object.filename = str;

  objects.push_back(object);
  LastObject = &objects.back();
 }

 void ProcessNull(void)
 {
  clearlast();
  Object object;
  findkeyword();
  sscanf(keyword.c_str(), "%lx", &object.index);
  findkeyword();
  if (str[0] && str[1])
   object.filename.assign(str + 1, strlen(str) - 2);
  object.layer = 0;
  objects.push_back(object);
  LastObject = &objects.back();
 }

 void ProcessLight(void)
 {
  clearlast();
  Light light;
  sscanf(str, "%lx", &light.index);
  lights.push_back(light);
  LastLight = &lights.back();
 }

 void ProcessLightName(void)
 {
  if (!LastLight)
   error("Line %i: LightName without previous light", line);
  LastLight->name = str;
 }

 void ProcessLightColor(void)
 {
  if (!LastLight)
   error("Line %i: LightColor without previous light", line);
  Color& color = LastLight->light;
  sscanf(str, "%f %f %f", &color.red, &color.green, &color.blue);
 }

 void ProcessLightIntensity(void)
 {
  if (!LastLight)
   error("Line %i: LightIntensity without previous light", line);
  sscanf(str, "%f", &LastLight->intensity);
 }

 void ProcessLightType(void)
 {
  if (!LastLight)
   error("Line %i: LightType without previous light", line);
  sscanf(str, "%i", &LastLight->type);
 }

 void ProcessCamera(void)
 {
  clearlast();
  Camera camera;
  sscanf(str, "%lx", &camera.index);
  cameras.push_back(camera);
  LastCamera = &cameras.back();
 }

 void ProcessCameraName(void)
 {
  if (!LastCamera)
   error("Line %i: CameraName without previous camera", line);
  LastCamera->name = str;
 }

 void ProcessCameraLocked(void)
 {
  if (!LastCamera)
   error("Line %i: LockedChannels without previous camera", line);
  sscanf(str, "%u", &LastCamera->locked);
 }

 void ProcessCameraTarget(void)
 {
  if (!LastCamera)
   error("Line %i: TargetItem without previous camera", line);
  sscanf(str, "%lx", &LastCamera->target);
 }

 void ProcessLimits(Limits Object::* limit)
 {
  if (!LastObject)
   return;
  sscanf(str, "%f %f", &(LastObject->*limit).min, &(LastObject->*limit).max);
  (LastObject->*limit).set = true;
 }

 void ProcessHLimits(void)
 {
  ProcessLimits(&Object::h);
 }

 void ProcessPLimits(void)
 {
  ProcessLimits(&Object::p);
 }

 void ProcessBLimits(void)
 {
  ProcessLimits(&Object::b);
 }


 FILE* fp;
 int line;
 char str[1024];
 std::string keyword;


 GeneralObject* LastGeneralObject;
 Object* LastObject;
 Light* LastLight;
 Camera* LastCamera;
};

LwsFile::ProcessorAssignment LwsFile::Processors[] =
{
 { "{", LwsFile::SkipBlock },
 { "FramesPerSecond", LwsFile::ProcessFPS },
 { "ShowObject", LwsFile::ProcessShowObject },
 { "ShowLight", LwsFile::ProcessShowLight },
 { "ShowCamera", LwsFile::ProcessShowCamera },
 { "ObjectMotion", LwsFile::ProcessObjectMotion },
 { "LightMotion", LwsFile::ProcessLightMotion },
 { "CameraMotion", LwsFile::ProcessCameraMotion },
 { "NumChannels", LwsFile::ProcessMotion },
 { "Channel", LwsFile::ProcessChannel },
 { "ParentItem", LwsFile::ProcessParent },
 { "Plugin", LwsFile::ProcessPlugin },
 { "ObjectDissolve", LwsFile::ProcessDissolve },
 { "LoadObjectLayer", LwsFile::ProcessLoad },
 { "AddNullObject", LwsFile::ProcessNull },
 { "AddLight", LwsFile::ProcessLight },
 { "LightName", LwsFile::ProcessLightName },
 { "LightColor", LwsFile::ProcessLightColor },
 { "LightIntensity", LwsFile::ProcessLightIntensity },
 { "LightType", LwsFile::ProcessLightType },
 { "AddCamera", LwsFile::ProcessCamera },
 { "CameraName", LwsFile::ProcessCameraName },
 { "LockedChannels", LwsFile::ProcessCameraLocked },
 { "TargetItem", LwsFile::ProcessCameraTarget },
 { "HLimits", LwsFile::ProcessHLimits },
 { "PLimits", LwsFile::ProcessPLimits },
 { "BLimits", LwsFile::ProcessBLimits },
 { 0, 0 }
};
