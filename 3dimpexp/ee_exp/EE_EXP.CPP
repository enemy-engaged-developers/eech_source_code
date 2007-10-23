#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <assert.h>
#include <memory.h>
#include <ctype.h>
#include <sys/stat.h>

#include "ee3dexp.cpp"

#include "../common/common.h"
#include "names.cpp"
#include "scenes.cpp"
#include "lws_exp.cpp"

int main(int argc, char* argv[])
{
 setbuf(stdout, NULL);

 EET eet(argc > 1 && isalpha(argv[1][0]) ? toupper(argv[1][0]) : 'D');
 const AllNames names;
 const Objects objects;
 const Scenes scenes(objects);
 LwsExport lwsexp(eet, names, objects, scenes);

 mkdir("_OBJECTS");

 char filename[1024];

 for (int i = 1; i < objects.GetNumberOfObjects(); i++)
  {
   const OBJECT_3D& obj = objects.GetObject(i);
   if (obj.surfaces)
    {
     sprintf(filename, "_OBJECTS/%04X.LWO", i);
     ExportLWO(eet, filename, obj);
    }
  }

 for (int i = 1; i < scenes.GetNumberOfScenes(); i++)
 {
  sprintf(filename, "_OBJECTS/%04X_%s.LWS", i, names.Objects[i]);
  lwsexp.ExportScene(filename, scenes.GetScene(i));
 }

 return 0;
}
