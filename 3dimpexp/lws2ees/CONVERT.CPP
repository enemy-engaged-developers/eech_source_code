#include <vector>
#include <map>
#include <set>
#include <list>
#include <algorithm>



class Convert
{
 public:

 Convert(const Lws& lws, const char* filename)
  : root(0), collision(0), shadow(0)
 {
  convert(lws);
  save(filename);
 }

 ~Convert(void)
 {
 }


 private:

 struct HierObj;
 typedef std::vector<HierObj*> HierObjs;
 struct HierObj
 {
  HierObj(void)
   : object(0)
  {
  }

  const Object* object;
  HierObjs hierobjs;
 };

 struct SubObject;
 typedef std::vector<SubObject> SubObjects;
 struct SubObject
 {
  std::string filename;
  int lod_min, lod_max;

  const Object* object;
  SubObjects subobjects;
  int indices;
 };

 struct MainLod
 {
  MainLod(void) {}
  MainLod(float dist) : distance(dist) {}

  std::string filename;
  float distance;
 };
 typedef std::vector<MainLod> Lods;

 struct LightDesc
 {
  LightDesc(void)
   : light(0)
  {
  }

  const Light* light;
 };
 typedef std::vector<LightDesc> LightDescs;

 struct CameraDesc
 {
  CameraDesc(void)
   : camera(0), target(0)
  {
  }

  const Camera* camera;
  const Object* target;
 };
 typedef std::vector<CameraDesc> CameraDescs;

 typedef std::vector<const Object*> Links;

 void convert(const Lws& lws)
 {
  build_hierarchy(lws);
  if (!root)
   error("No objects in scene");
  //print(root, 0);
  main_lods();
  set_lods(&main, root);
  clear(root);
  //print(main, 0);
 }

 void save(const char* filename)
 {
  fp = fopen(filename, "wb");
  if (!fp)
   error("Failed to create %s", filename);
  save_scene();
  fclose(fp);
 }

 void clear(HierObj* hierobj)
 {
  if (!hierobj)
   return;
  for (HierObjs::iterator itor(hierobj->hierobjs.begin()); itor != hierobj->hierobjs.end(); ++itor)
   clear(*itor);
  delete hierobj;
 }

 void build_hierarchy(const Lws& lws)
 {
  typedef std::map<long, HierObj*> Cache;
  typedef std::set<float> Distances;
  typedef std::list<HierObj*> Deferred;

  Cache cache;
  Distances distances;
  Deferred deferred;

  fps = lws.fps;

  for (Lws::Objects::const_iterator itor(lws.objects.begin()); itor != lws.objects.end(); ++itor)
   {
    if (itor->search == "SHADOW_OBJECT")
     {
      if (!itor->layer)
       continue;
      if (shadow)
       error("Duplicate shadow objects found: %08lX and %08lX", shadow->index, itor->index);
      shadow = &*itor;
      continue;
     }

    if (itor->search == "COLLISION_OBJECT")
     {
      if (!itor->layer)
       continue;
      if (collision)
       error("Duplicate collision objects found: %08lX and %08lX", collision->index, itor->index);
      collision = &*itor;
      continue;
     }

    if (!itor->layer && itor->filename == "LINK_OBJECT")
     {
      links.push_back(&*itor);
      continue;
     }

    {
     Cache::iterator found(cache.find(itor->index));
     if (found != cache.end())
      error("Objects with duplicate index %08lX are found", itor->index);
    }

    {
     if (itor->motion.nchannels != 9)
      error("Invalid motion for object %08lX", itor->index);
     for (int i = 1; i < 9; i++)
      {
       if (itor->motion.channels[0].keys.size() != itor-> motion.channels[i].keys.size())
        error("Invalid motion for object %08lX", itor->index);
       for (int j = 0; j < itor->motion.channels[0].keys.size(); j++)
        if (itor->motion.channels[0].keys[j].time != itor->motion.channels[i].keys[j].time ||
            itor->motion.channels[0].keys[j].spantime != itor->motion.channels[i].keys[j].spantime ||
            itor->motion.channels[0].keys[j].spantime != 0 &&
            itor->motion.channels[0].keys[j].spantime != 3 ||
            itor->motion.channels[0].keys[j].p[0] != itor->motion.channels[i].keys[j].p[0] ||
            itor->motion.channels[0].keys[j].p[1] != itor->motion.channels[i].keys[j].p[1] ||
            itor->motion.channels[0].keys[j].p[2] != itor->motion.channels[i].keys[j].p[2] ||
            itor->motion.channels[0].keys[j].p[3] != itor->motion.channels[i].keys[j].p[3] ||
            itor->motion.channels[0].keys[j].p[4] != itor->motion.channels[i].keys[j].p[4] ||
            itor->motion.channels[0].keys[j].p[5] != itor->motion.channels[i].keys[j].p[5])
         error("Invalid motion for object %08lX", itor->index);
      }
    }

    HierObj* hierobj = new HierObj;
    hierobj->object = &*itor;

    for (PluginLod::LODs::const_iterator itor(hierobj->object->lods.lods.begin()); itor != hierobj->object->lods.lods.end(); ++itor)
     distances.insert(itor->distance);

    if (itor->motion.parent)
     {
      Cache::iterator found(cache.find(itor->motion.parent));
      if (found == cache.end())
       {
        deferred.push_back(hierobj);
        continue;
       }
      found->second->hierobjs.push_back(hierobj);
     }
    else
     {
      if (root)
       {
        error("Only one root object allowed, but two found: %08lX and %08lX", root->object->index, hierobj->object->index);
#if 0
        if (root->object)
         {
          HierObj* newroot = new HierObj;
          newroot->hierobjs.push_back(root);
          root = newroot;
         }
        root->hierobjs.push_back(hierobj);
#endif
       }
      else
       root = hierobj;
     }
    cache[itor->index] = hierobj;
   }

  while (deferred.size())
   {
    bool modified = false;
    for (Deferred::iterator itor(deferred.begin()); itor != deferred.end(); )
     {
      HierObj* hierobj = *itor;
      {
       Cache::iterator found(cache.find(hierobj->object->index));
       if (found != cache.end())
        error("Objects with duplicate index %08lX are found", hierobj->object->index);
      }
      Cache::iterator found(cache.find(hierobj->object->motion.parent));
      if (found != cache.end())
       {
        found->second->hierobjs.push_back(hierobj);
        cache[hierobj->object->index] = hierobj;
        itor = deferred.erase(itor);
        modified = true;
       }
      else
       ++itor;
     }
    if (!modified)
     error("Either cyclic dependency within hierarchy or inexisting parent for object(s) "
           "(at least %08lX)", deferred.front()->object->index);
   }

  for (Lws::Lights::const_iterator itor(lws.lights.begin()); itor != lws.lights.end(); ++itor)
   if (itor->type == 1)
    {
     LightDesc lightdesc;
     lightdesc.light = &*itor;
     lights.push_back(lightdesc);
    }

  for (Lws::Cameras::const_iterator itor(lws.cameras.begin()); itor != lws.cameras.end(); ++itor)
   {
    CameraDesc cameradesc;
    cameradesc.camera = &*itor;
    if (itor->target)
     {
      Cache::iterator found(cache.find(itor->target));
      if (found == cache.end())
       error("Failed to find object with index %08lX as target for camera '%s'", itor->target, itor->name);
      cameradesc.target = found->second->object;
     }
    cameras.push_back(cameradesc);
   }

  if (distances.size() && *distances.begin() < 1E-2)
   distances.erase(distances.begin());
  lods.insert(lods.end(), distances.begin(), distances.end());
 }

 void main_lods(void)
 {
  std::string filename = root->object->filename;

  total_indices = total_subobjects = 0;

  main.filename = filename;
  main.lod_min = 0;
  main.lod_max = lods.size();

  for (Lods::iterator itor(lods.begin()); itor != lods.end(); ++itor)
   {
    for (PluginLod::LODs::const_iterator lod(root->object->lods.lods.begin()); lod != root->object->lods.lods.end() && lod->distance <= itor->distance; ++lod)
     filename = lod->filename;
    itor->filename = filename;
   }
 }

 void set_minmax(const Channel::Keys& keys, float* minval, float* maxval)
 {
  Channel::Keys::const_iterator itor(keys.begin());
  *minval = *maxval = itor->value;
  for (++itor; itor != keys.end(); ++itor)
   {
    *minval = std::min(*minval, itor->value);
    *maxval = std::max(*maxval, itor->value);
   }
 }

 void set_lods(SubObject* subobject, const HierObj* hierobj)
 {
  subobject->object = hierobj->object;
  subobject->indices = 0;

  for (HierObjs::const_iterator itor(hierobj->hierobjs.begin()); itor != hierobj->hierobjs.end(); ++itor)
   {
    const HierObj* hierobj = *itor;

    Lods slods = lods;
    slods.insert(slods.begin(), 0);
    std::string filename = hierobj->object->filename;
    for (Lods::iterator itor(slods.begin()); itor != slods.end(); ++itor)
     {
      for (PluginLod::LODs::const_iterator lod(hierobj->object->lods.lods.begin()); lod != hierobj->object->lods.lods.end() && lod->distance <= itor->distance; ++lod)
       filename = lod->filename;
      itor->filename = filename;
     }

    Lods::iterator cur(slods.begin());
    while (cur != slods.end())
     {
      Lods::iterator next(cur);
      for (++next; next != slods.end() && (subobject == &main || next->filename == cur->filename); ++next);

      SubObject subobj;
      subobj.filename = cur->filename;
      subobj.lod_min = cur - slods.begin();
      subobj.lod_max = next - slods.begin() - 1;
      if (subobj.lod_min <= subobject->lod_max && subobj.lod_max >= subobject->lod_min)
       {
        subobj.lod_min = std::max(subobj.lod_min, subobject->lod_min);
        subobj.lod_max = std::min(subobj.lod_max, subobject->lod_max);
        if (subobj.lod_min <= subobj.lod_max)
         {
          total_subobjects++;
          if (hierobj->object->search.size())
           {
            subobject->indices++;
            total_indices++;
           }
          subobject->subobjects.push_back(subobj);
          set_lods(&subobject->subobjects.back(), hierobj);
         }
       }

      cur = next;
     }
   }
 }

 void print(const HierObj* hierobj, int depth)
 {
  printf("% *s%08lX (%s) '%s'", depth++, "", hierobj->object->index, hierobj->object->search.c_str(), hierobj->object->filename.c_str());
  for (PluginLod::LODs::const_iterator lod(hierobj->object->lods.lods.begin()); lod != hierobj->object->lods.lods.end(); ++lod)
   printf(" %f '%s'", lod->distance, lod->filename.c_str());
  printf("\n");
  for (HierObjs::const_iterator itor(hierobj->hierobjs.begin()); itor != hierobj->hierobjs.end(); ++itor)
   print(*itor, depth);
 }

 void print(const SubObject& subobject, int depth)
 {
  printf("% *s%i %i (%s) '%s'\n", depth++, "", subobject.lod_min, subobject.lod_max, subobject.object ? subobject.object->search.c_str() : "", subobject.filename.c_str());
  for (SubObjects::const_iterator itor(subobject.subobjects.begin()); itor != subobject.subobjects.end(); ++itor)
   print(*itor, depth);
 }


 void fw(int num) const
 {
  fwrite(&num, sizeof(num), 1, fp);
 }

 void fw(float num) const
 {
  fwrite(&num, sizeof(num), 1, fp);
 }

 void fw(const char* str) const
 {
  fwrite(str, strlen(str) + 1, 1, fp);
 }

 void save_dissolve(const Channel& channel) const
 {
  fw(1.0f);
  fw(static_cast<int>(channel.keys.size()));
  for (Channel::Keys::const_iterator itor(channel.keys.begin()); itor != channel.keys.end(); ++itor)
   {
    fw(static_cast<int>(itor->time * fps));
    fw(itor->spantime ? 1 : 0);
    fw(itor->value);
    fw(itor->p[0]);
    fw(itor->p[1]);
    fw(itor->p[2]);
   }
 }

 void save_animation(const Motion& motion) const
 {
  fw(static_cast<int>(motion.channels[0].keys.size()));
  for (int i = 0; i < motion.channels[0].keys.size(); i++)
   {
    fw(static_cast<int>(motion.channels[0].keys[i].time * fps));
    fw(motion.channels[0].keys[i].spantime ? 1 : 0);
    fw(motion.channels[0].keys[i].value);
    fw(motion.channels[1].keys[i].value);
    fw(motion.channels[2].keys[i].value);
    fw(motion.channels[3].keys[i].value);
    fw(motion.channels[4].keys[i].value);
    fw(motion.channels[5].keys[i].value);
    fw(motion.channels[6].keys[i].value);
    fw(motion.channels[7].keys[i].value);
    fw(motion.channels[8].keys[i].value);
    fw(motion.channels[0].keys[i].p[0]);
    fw(motion.channels[0].keys[i].p[1]);
    fw(motion.channels[0].keys[i].p[2]);
   }
 }

 void save_indices(const SubObject& subobject) const
 {
  fw(subobject.indices);
  int offset = 0;
  for (SubObjects::const_iterator itor(subobject.subobjects.begin()); itor != subobject.subobjects.end(); ++itor, offset++)
   {
    if (itor->object->search.size())
     {
      fw(itor->object->search.c_str());
      fw(offset);
     }
   }
 }

 void save_subobject(const SubObject& subobject) const
 {
  fw(subobject.object->filename.c_str());

  fw(subobject.object->collision.collision);
  fw(subobject.lod_min + 1);
  fw(subobject.lod_max + 1);

  if (subobject.object->h.set && subobject.object->p.set && subobject.object->b.set)
   {
    fw(1);
    fw(subobject.object->h.max);
    fw(subobject.object->h.min);
    fw(subobject.object->p.max);
    fw(subobject.object->p.min);
    fw(subobject.object->b.max);
    fw(subobject.object->b.min);
   }
  else
   fw(0);

  save_animation(subobject.object->motion);

  save_dissolve(subobject.object->dissolve);

  save_subobjects(subobject);
 }

 void save_subobjects(const SubObject& subobject) const
 {
  save_indices(subobject);
  fw(static_cast<int>(subobject.subobjects.size()));
  for (SubObjects::const_iterator itor(subobject.subobjects.begin()); itor != subobject.subobjects.end(); ++itor)
   save_subobject(*itor);
 }

 void save_scene(void) const
 {
  // Version
  fw(-1);

  fw(static_cast<int>(cameras.size()));
  for (CameraDescs::const_iterator itor(cameras.begin()); itor != cameras.end(); ++itor)
   {
    fw(itor->camera->name.c_str());
    fw(itor->target ? itor->target->search.c_str() : "");
    fw(itor->camera->locked & 8 ? 1 : 0);
    fw(itor->camera->locked & 16 ? 1 : 0);
    fw(itor->camera->locked & 32 ? 1 : 0);
    save_animation(itor->camera->motion);
   }

  fw(static_cast<int>(links.size()));
  for (Links::const_iterator itor(links.begin()); itor != links.end(); ++itor)
   {
    fw((*itor)->search.c_str());
    fw((*itor)->motion.channels[0].keys.front().value);
    fw((*itor)->motion.channels[1].keys.front().value);
    fw((*itor)->motion.channels[2].keys.front().value);
    fw((*itor)->motion.channels[3].keys.front().value);
    fw((*itor)->motion.channels[4].keys.front().value);
    fw((*itor)->motion.channels[5].keys.front().value);
   }

  fw(static_cast<int>(lights.size()));
  for (LightDescs::const_iterator itor(lights.begin()); itor != lights.end(); ++itor)
   {
    const Light* light = itor->light;
    fw(light->motion.channels[0].keys.begin()->value);
    fw(light->motion.channels[1].keys.begin()->value);
    fw(light->motion.channels[2].keys.begin()->value);
    fw(light->motion.channels[6].keys.begin()->value);
    fw(light->motion.channels[7].keys.begin()->value);
    fw(light->motion.channels[8].keys.begin()->value);

    fw(static_cast<int>(light->light.red * light->intensity * 255));
    fw(static_cast<int>(light->light.green * light->intensity * 255));
    fw(static_cast<int>(light->light.blue * light->intensity * 255));
   }

  fw(total_subobjects);
  fw(total_indices);

#if 1
  fw(0);
#else
  fwrite(&number_of_texture_animations, sizeof(int), 1, fp);
  for (int tmp = 0; tmp < number_of_texture_animations; tmp++)
   fwrite(&texture_animations[tmp], sizeof(int), 1, fp);
#endif

  fw(static_cast<int>(lods.size()));
  fw(main.object ? main.object->filename.c_str() : "");
  for (Lods::const_iterator itor(lods.begin()); itor != lods.end(); ++itor)
   {
    fw(itor->filename.c_str());
    fw(itor->distance);
   }

#if 1
  fw(0);
#else
  fwrite(&shadow_approximation_index, sizeof(int), 1, fp);
#endif

  if (shadow)
   {
    fw(shadow->filename.c_str());
    fw(shadow->motion.channels[7].keys.front().value);
    fw(shadow->motion.channels[8].keys.front().value);
    fw(shadow->motion.channels[9].keys.front().value);
   }
  else
   {
    fw("");
    fw(1.0f);
    fw(1.0f);
    fw(1.0f);
   }

  if (collision)
   fw(collision->filename.c_str());
  else
   fw("");

  save_animation(main.object->motion);

  save_dissolve(main.object->dissolve);

#if 1
  fw(0);
#else
  fwrite(&number_of_displacement_amplitude_keyframes, sizeof(int), 1, fp);
  for (int keyframe_count = 0; keyframe_count < number_of_displacement_amplitude_keyframes; keyframe_count++)
   {
    fwrite(&displacement_amplitude_keyframes[keyframe_count].index, sizeof(int), 1, fp);
    fwrite(&displacement_amplitude_keyframes[keyframe_count].linear, sizeof(int), 1, fp);
    fwrite(&displacement_amplitude_keyframes[keyframe_count].value, sizeof(float), 1, fp);
    fwrite(&displacement_amplitude_keyframes[keyframe_count].tension, sizeof(int), 1, fp);
    fwrite(&displacement_amplitude_keyframes[keyframe_count].continuity, sizeof(int), 1, fp);
    fwrite(&displacement_amplitude_keyframes[keyframe_count].bias, sizeof(int), 1, fp);
   }
#endif

  save_subobjects(main);
 }

 HierObj* root;
 float fps;
 LightDescs lights;
 CameraDescs cameras;
 Lods lods;
 SubObject main;
 const Object* collision;
 const Object* shadow;
 Links links;
 int total_indices, total_subobjects;
 FILE* fp;
};
