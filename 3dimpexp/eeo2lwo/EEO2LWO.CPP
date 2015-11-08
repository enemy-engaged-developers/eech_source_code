#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <assert.h>
#include <memory.h>
#include <ctype.h>
#include <sys/stat.h>

#define SAFE_FOPEN_RB

#include "../ee_exp/ee3dexp.cpp"
#include "../ee_exp/names.cpp"
#include "../ee_exp/textures.cpp"
#include "eeo2lwo.h"

int main(int argc, char* argv[])
{
 puts("Enemy Engaged EEO to LWO converter build " __DATE__);

 if (argc < 3)
  {
   printf("Usage: eeo2lwo file_name.eeo file_name.lwo [textures directories]");
   return -1;
  }

 char filename[1024];

 FileTexturesFinder textures_finder(*getcwd(filename, sizeof(filename)), argv + 3);
 EET eet(textures_finder);
 AllNames names(eet);
 TexturesExporter_ textures;
 textures.export_textures(eet, false);
 const Object object(argv[1], eet);
 ExportLWO(eet, argv[2], object);

 return 0;
}
