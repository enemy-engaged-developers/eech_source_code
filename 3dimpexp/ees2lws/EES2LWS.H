class Scene : public OBJECT_3D_SCENE_DATABASE_ENTRY
{
 public:
 
 Scene(const char* filename, AllNames& names, Cameras& cameras, AggTranslator& translator)
  : names(names), cameras_(cameras), translator(translator)
 {
  FILE* fp = safe_fopen(filename, "rb");
  int version;
  fread(&version, 1, sizeof(int), fp);
  read_scene(fp, version);
  fclose(fp);
 }

 private:

 AllNames& names;
 Cameras& cameras_;
 AggTranslator& translator;

#include "scene.cpp"
};
