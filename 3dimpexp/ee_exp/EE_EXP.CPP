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

int main(void)
{
 char filename[1024];

 freopen("EEEXPLOG.TXT", "w", stdout);

 EET eet(*getcwd(filename, sizeof(filename)));
 const AllNames names;
 const Objects objects;
 const Scenes scenes(objects);
 LwsExport lwsexp(eet, names, objects, scenes);

 mkdir("_OBJECTS");

 for (int i = 1; i <= objects.GetNumberOfObjects(); i++)
  {
   const OBJECT_3D& obj = objects.GetObject(i);
   if (obj.surfaces)
    {
     sprintf(filename, "_OBJECTS/%04X.LWO", i);
     ExportLWO(eet, filename, obj);
    }
  }

 for (int i = 1; i <= scenes.GetNumberOfScenes(); i++)
 {
  sprintf(filename, "_OBJECTS/%04X_%s.LWS", i, names.Objects[i]);
  lwsexp.ExportScene(filename, scenes.GetScene(i));
 }

 return 0;
}
