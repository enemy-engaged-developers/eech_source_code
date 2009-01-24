#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <assert.h>
#include <memory.h>
#include <ctype.h>
#include <sys/stat.h>

#include "../common/common.h"
#include "../ee_exp/ee3dexp.cpp"
#include "../ee_exp/names.cpp"
#include "../ee_exp/scenes.cpp"
#include "../ee_exp/trans.cpp"
#include "../ee_exp/lws_exp.cpp"

class Scene : public OBJECT_3D_SCENE_DATABASE_ENTRY
{
 public:
 
 Scene(const char* filename, AllNames& names, Cameras& cameras, AggTranslator& translator)
  : names(names), cameras_(cameras), translator(translator)
 {
  FILE* fp = safe_fopen(filename, "rb");
  int version;
  fread(&version, 1, sizeof(int), fp);
  read_scene(fp);
  fclose(fp);
 }

 private:

 AllNames& names;
 Cameras& cameras_;
 AggTranslator& translator;

#include "scene.cpp"
};

int main(int argc, char* argv[])
{
 puts("Enemy Engaged EES to LWS converter build " __DATE__);

 if (argc < 3)
  {
   printf("Usage: ees2lws file_name.ees file_name.lws");
   return -1;
  }

 char filename[1024];

 EET eet(*getcwd(filename, sizeof(filename)));
 AllNames names(eet);
 Cameras cameras;
 AggTranslator translator;
 const Scene scene(argv[1], names, cameras, translator);
 LwsExport exporter(names, cameras, translator);
 exporter.ExportScene(argv[2], scene);

 return 0;
}
