#include <vector>
#include <map>
#include <set>
#include <list>
#include <algorithm>



class Convert
{
 public:

 Convert(const Lws& lws, const char* filename, const char* log_filename)
  : root(0), collision(0), shadow(0), log(0)
 {
  if (log_filename)
    log = safe_fopen(log_filename, "w");
  convert(lws);
  if (log)
    fclose(log);
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
  size_t last_lod;
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
  MainLod(int dist) : distance(dist) {}

  std::string filename;
  int distance;
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
  if (log)
   {
    fprintf(log, "ORIGINAL SCENE:\n");
    print(root, 0);
   }
  sort_by_labels(root);
  if (log)
   {
    fprintf(log, "\n\nSORTED BY PRIORITY SCENE:\n");
    print(root, 0);
   }
  main_lods();
  if (log)
   {
    fprintf(log, "\n\nLOD DISTANCES:");
    print_lods();
   }
  set_last_lods(root);
  set_lods(&main, root);
  clear(root);
  if (log)
   {
    fprintf(log, "\n\nRESULTED SCENE:\n");
    print(main, 0);
   }
 }

 void save(const char* filename)
 {
  fp = safe_fopen(filename, "wb");
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
  typedef std::set<int> Distances;
  typedef std::list<HierObj*> Deferred;

  Cache cache;
  Distances distances;
  Deferred deferred;

  fps = lws.fps;

  for (Lws::Objects::const_iterator itor(lws.objects.begin()); itor != lws.objects.end(); ++itor)
   {
    if (itor->search == "SHADOW_OBJECT")
     {
      if (shadow)
       error("Duplicate shadow objects found: %s and %s", shadow->print_name.c_str(), itor->print_name.c_str());
      if (!itor->lods.lods.empty())
       warning("LODs are ignored for %s", itor->print_name.c_str());
      shadow = &*itor;
      continue;
     }

    if (itor->search == "COLLISION_OBJECT")
     {
      if (!itor->layer)
       continue;
      if (collision)
       error("Duplicate collision objects found: %s and %s", collision->print_name.c_str(), itor->print_name.c_str());
      if (!itor->lods.lods.empty())
       warning("LODs are ignored for %s", itor->print_name.c_str());
      collision = &*itor;
      continue;
     }

    if (!itor->layer && itor->filename == "LINK_OBJECT")
     {
      links.push_back(&*itor);
      continue;
     }

    if (!itor->lods.lods.empty())
     {
      if ((int)itor->lods.lods[0].distance <= 0)
        error("First LOD is too close for object %s", itor->print_name.c_str());
      for (size_t i = 1; i < itor->lods.lods.size(); i++)
       if ((int)itor->lods.lods[i - 1].distance >= (int)itor->lods.lods[i].distance)
        error("Invalid distances for LODs %i and %i for object %s", i - 1, i, itor->print_name.c_str());
      if (itor->filename.empty())
       warning("Null object %s with LODs", itor->print_name.c_str());
      if ((itor->lods.lods.size() > 1 || !itor->lods.lods.back().filename.empty()) && !itor->search.empty())
       warning("Object %s has both a label and LODs", itor->print_name.c_str());
     }

    {
     Cache::iterator found(cache.find(itor->index));
     if (found != cache.end())
      error("Objects with duplicate index are found: %s and %s", itor->print_name.c_str(), found->second->object->print_name.c_str());
    }

    {
     if (itor->motion.nchannels != 9)
      error("Invalid motion for object %s: number of channels is %u", itor->print_name.c_str(), itor->motion.nchannels);

     typedef std::set<float> Times;
     Times times;
     for (int i = 0; i < 9; i++)
      {
       const Channel::Keys& keys = itor->motion.channels[i].keys;
       for (int j = 0; j < keys.size(); j++)
        {
         times.insert(keys[j].time);
        }
      }
     if (times.size() > 1)
      {
       for (int i = 0; i < 9; i++)
        {
         Channel::Keys& keys = const_cast<Channel::Keys&>(itor->motion.channels[i].keys);
         if (keys.size() == 1)
          {
           warning("Adding keys for object %s channel %i", itor->print_name.c_str(), i);
           Key key(keys.front());
           keys.clear();
           for (Times::const_iterator itor(times.begin()); itor != times.end(); ++itor)
            {
             key.time = *itor;
             keys.push_back(key);
            }
          }
        }
      }
     for (int i = 1; i < 9; i++)
      {
       if (itor->motion.channels[0].keys.size() != itor->motion.channels[i].keys.size())
        error("Invalid motion for object %s: size for channel 0 is %u, for channel %i is %u", itor->print_name.c_str(), itor->motion.channels[0].keys.size(), i, itor->motion.channels[i].keys.size());
       for (int j = 0; j < itor->motion.channels[0].keys.size(); j++)
        {
#define CHECK(name, type) \
 if (itor->motion.channels[0].keys[j]. ## name != itor->motion.channels[i].keys[j]. ## name) \
  warning("Invalid motion for object %s: parameter " #name " channel %i key %i expected %" type " got %" type, itor->print_name.c_str(), i, j, itor->motion.channels[0].keys[j]. ## name, itor->motion.channels[i].keys[j]. ## name);
         CHECK(time, "f")
         CHECK(spantype, "i")
         if (itor->motion.channels[0].keys[j].spantype != 0 && itor->motion.channels[0].keys[j].spantype != 3)
          error("Invalid motion for object %s: 0 %i spantype %i", itor->print_name.c_str(), j, itor->motion.channels[0].keys[j].spantype);
         CHECK(p[0], "f")
         CHECK(p[1], "f")
         CHECK(p[2], "f")
#if 0
         CHECK(p[3], "f")
         CHECK(p[4], "f")
#endif
         CHECK(p[5], "f")
        }
      }
    }

    HierObj* hierobj = new HierObj;
    hierobj->object = &*itor;

    for (PluginLod::LODs::const_iterator itor(hierobj->object->lods.lods.begin()); itor != hierobj->object->lods.lods.end(); ++itor)
     distances.insert((int)itor->distance);

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
        error("Only one root object allowed, but at least two are found: %s and %s", root->object->print_name.c_str(), hierobj->object->print_name.c_str());
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

  while (!deferred.empty())
   {
    bool modified = false;
    for (Deferred::iterator itor(deferred.begin()); itor != deferred.end(); )
     {
      HierObj* hierobj = *itor;
      {
       Cache::iterator found(cache.find(hierobj->object->index));
       if (found != cache.end())
        error("Objects with duplicate index are found %s and %s", hierobj->object->print_name.c_str(), found->second->object->print_name.c_str());
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
     error("Either cyclic dependency within hierarchy or inexisting parent for object(s) (at least %s)", deferred.front()->object->print_name.c_str());
   }

  for (Lws::Lights::const_iterator itor(lws.lights.begin()); itor != lws.lights.end(); ++itor)
   {
    LightDescs* lights = 0;
    switch (itor->type)
     {
      case 0:
       lights = &distant_lights;
       break;
      case 1:
       lights = &sprite_lights;
       break;
      case 4:
       lights = &ambient_lights;
       break;
      default:
       break;
     }
    if (lights)
     {
      LightDesc lightdesc;
      lightdesc.light = &*itor;
      lights->push_back(lightdesc);
     }
   }

  for (Lws::Cameras::const_iterator itor(lws.cameras.begin()); itor != lws.cameras.end(); ++itor)
   {
    CameraDesc cameradesc;
    cameradesc.camera = &*itor;
    if (itor->target)
     {
      Cache::iterator found(cache.find(itor->target));
      if (found == cache.end())
       error("Failed to find object with index %08lX as target for camera '%s'", itor->target, itor->print_name.c_str());
      cameradesc.target = found->second->object;
     }
    cameras.push_back(cameradesc);
   }

  if (!distances.empty() && !*distances.begin())
   distances.erase(distances.begin());
  lods.insert(lods.end(), distances.begin(), distances.end());
 }

 void print_lods(void)
 {
  for (size_t i = 0; i < lods.size(); i++)
   fprintf(log, " %i: %i (%s)", i + 1, lods[i].distance, lods[i].filename.c_str());
  fprintf(log, "\n");
 }

 void sort_by_labels(HierObj* hierobj)
 {
  if (hierobj != root && !hierobj->object->lods.lods.empty())
   {
    if (!hierobj->object->lods.lods.back().filename.empty())
     warning("Last LOD for object %s is not NullObject", hierobj->object->print_name.c_str());
   }

  {
   std::set<std::string> labels;

   for (HierObjs::iterator itor(hierobj->hierobjs.begin()); itor != hierobj->hierobjs.end(); ++itor)
   {
    const std::string& label = (*itor)->object->search;
    if (label.empty())
     continue;

    if (labels.find(label) != labels.end())
     continue;

    for (HierObjs::iterator i(itor); i != hierobj->hierobjs.end(); ++i)
     {
      HierObjs::iterator k(i);
      for (HierObjs::iterator j(i); j != hierobj->hierobjs.end(); ++j)
       {
        if ((*j)->object->search == label && (*j)->object->priority < (*k)->object->priority)
         k = j;
       }
      if (k != i)
       std::swap(*k, *i);
     }

    labels.insert(label);
   }
  }

  for (HierObjs::iterator itor(hierobj->hierobjs.begin()); itor != hierobj->hierobjs.end(); ++itor)
   sort_by_labels(*itor);
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
    for (PluginLod::LODs::const_iterator lod(root->object->lods.lods.begin()); lod != root->object->lods.lods.end() && (int)lod->distance <= itor->distance; ++lod)
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

 void set_last_lods(HierObj* hierobj)
 {
  PluginLod::LODs::const_iterator lod(hierobj->object->lods.lods.end());
  while (lod != hierobj->object->lods.lods.begin())
   {
    --lod;
    if (!lod->filename.empty())
     {
      ++lod;
      break;
     }
   }

  if (lod == hierobj->object->lods.lods.end())
   hierobj->last_lod = hierobj->object->filename.empty() ? 0 : lods.size();
  else
   for (Lods::const_iterator itor(lods.begin()); itor != lods.end(); ++itor)
    if (itor->distance == (int)lod->distance)
     hierobj->last_lod = itor - lods.begin();

  for (HierObjs::const_iterator itor(hierobj->hierobjs.begin()); itor != hierobj->hierobjs.end(); ++itor)
   {
    set_last_lods(*itor);
    hierobj->last_lod = std::max(hierobj->last_lod, (*itor)->last_lod);
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
    slods.erase(slods.begin() + hierobj->last_lod + 1, slods.end());
    std::string filename = hierobj->object->filename;
    for (Lods::iterator itor(slods.begin()); itor != slods.end(); ++itor)
     {
      for (PluginLod::LODs::const_iterator lod(hierobj->object->lods.lods.begin()); lod != hierobj->object->lods.lods.end() && (int)lod->distance <= itor->distance; ++lod)
       filename = lod->filename;
      itor->filename = filename;
     }

    Lods::iterator cur(slods.begin());
    while (cur != slods.end())
     {
      Lods::iterator next(cur);
      for (++next; next != slods.end() && next->filename == cur->filename; ++next);

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
          if (!hierobj->object->search.empty())
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
  fprintf(log, "% *s%s (%s)", 2 * depth++, "", hierobj->object->print_name.c_str(), hierobj->object->search.c_str());
  for (PluginLod::LODs::const_iterator lod(hierobj->object->lods.lods.begin()); lod != hierobj->object->lods.lods.end(); ++lod)
   fprintf(log, " %f '%s'", lod->distance, lod->filename.c_str());
  fprintf(log, "\n");
  for (HierObjs::const_iterator itor(hierobj->hierobjs.begin()); itor != hierobj->hierobjs.end(); ++itor)
   print(*itor, depth);
 }

 void print(const SubObject& subobject, int depth)
 {
  fprintf(log, "% *s%i %i (%s) '%s'\n", 2 * depth++, "", subobject.lod_min, subobject.lod_max, subobject.object ? subobject.object->search.c_str() : "", subobject.filename.c_str());
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
    fw(static_cast<int>(floor(itor->time * fps + 0.5)));
    fw(itor->spantype ? 1 : 0);
    fw(itor->value);
    fw(itor->p[0]);
    fw(itor->p[1]);
    fw(itor->p[2]);
   }
 }

 void save_animation(const GeneralObject& general_object) const
 {
  const Motion& motion = general_object.motion;
  if (motion.channels[0].keys.empty())
   error("Empty motion for %s", general_object.print_name.c_str());
  for (int i = 1; i < motion.channels[0].keys.size(); i++)
   {
    int cur = static_cast<int>(motion.channels[0].keys[i].time * fps);
    int prev = static_cast<int>(motion.channels[0].keys[i - 1].time * fps);
    if (cur <= prev)
     error("Invalid motion for %s: time is not increasing in channel 0 between keys %i (%i) and %i (%i)", general_object.print_name.c_str(), i - 1, prev, i, cur);
   }

  fw(static_cast<int>(motion.channels[0].keys.size()));
  for (int i = 0; i < motion.channels[0].keys.size(); i++)
   {
    fw(static_cast<int>(motion.channels[0].keys[i].time * fps));
    fw(motion.channels[0].keys[i].spantype ? 1 : 0);
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
    if (!itor->object->search.empty())
     {
      fw(itor->object->search.c_str());
      fw(offset);
     }
   }
 }

 void save_subobject(const SubObject& subobject) const
 {
  fw(subobject.filename.c_str());

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

  save_animation(*subobject.object);

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
  int version = ambient_lights.empty() && distant_lights.empty() ? -1 : -2;
  fw(version);

  fw(static_cast<int>(cameras.size()));
  for (CameraDescs::const_iterator itor(cameras.begin()); itor != cameras.end(); ++itor)
   {
    fw(itor->camera->name.c_str());
    fw(itor->target ? itor->target->search.c_str() : "");
    fw(itor->camera->locked & 8 ? 1 : 0);
    fw(itor->camera->locked & 16 ? 1 : 0);
    fw(itor->camera->locked & 32 ? 1 : 0);
    save_animation(*itor->camera);
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

  fw(static_cast<int>(sprite_lights.size()));
  for (LightDescs::const_iterator itor(sprite_lights.begin()); itor != sprite_lights.end(); ++itor)
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

  if (version <= -2)
   {
    fw(static_cast<int>(ambient_lights.size()));
    for (LightDescs::const_iterator itor(ambient_lights.begin()); itor != ambient_lights.end(); ++itor)
     {
      const Light* light = itor->light;

      fw(light->light.red * light->intensity);
      fw(light->light.green * light->intensity);
      fw(light->light.blue * light->intensity);

      fw(light->name.c_str());
     }

    fw(static_cast<int>(distant_lights.size()));
    for (LightDescs::const_iterator itor(distant_lights.begin()); itor != distant_lights.end(); ++itor)
     {
      const Light* light = itor->light;
      fw(light->motion.channels[3].keys.begin()->value);
      fw(light->motion.channels[4].keys.begin()->value);
      fw(light->motion.channels[5].keys.begin()->value);

      fw(light->light.red * light->intensity);
      fw(light->light.green * light->intensity);
      fw(light->light.blue * light->intensity);

      fw(light->name.c_str());
     }
   }

  fw(total_subobjects);
  fw(total_indices);

  fw(0);

  fw(static_cast<int>(lods.size()));
  fw(main.object ? main.object->filename.c_str() : "");
  for (Lods::const_iterator itor(lods.begin()); itor != lods.end(); ++itor)
   {
    fw(itor->filename.c_str());
    fw((float)itor->distance);
   }

  if (shadow && shadow->layer)
   {
    fw(0);
    fw(shadow->filename.c_str());
    fw(shadow->motion.channels[6].keys.front().value);
    fw(shadow->motion.channels[7].keys.front().value);
    fw(shadow->motion.channels[8].keys.front().value);
   }
  else
   {
    int shadow_approximation_index;
    shadow_approximation_index = !shadow || shadow->filename.empty() ? 0 : atoi(shadow->filename.c_str() + 1);
    fwrite(&shadow_approximation_index, sizeof(int), 1, fp);
    fw("");
    fw(1.0f);
    fw(1.0f);
    fw(1.0f);
   }

  if (collision)
   fw(collision->filename.c_str());
  else
   fw("");

  save_animation(*main.object);

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
 LightDescs sprite_lights, ambient_lights, distant_lights;
 CameraDescs cameras;
 Lods lods;
 SubObject main;
 const Object* collision;
 const Object* shadow;
 Links links;
 int total_indices, total_subobjects;
 FILE* fp;
 FILE* log;
};
