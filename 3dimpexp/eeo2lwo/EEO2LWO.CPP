#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <assert.h>
#include <memory.h>
#include <ctype.h>
#include <sys/stat.h>

#include "../ee_exp/ee3dexp.cpp"
#include "../ee_exp/names.cpp"

class Object : public OBJECT_3D
{
 public:
 
 Object(const char* filename, EET& eet)
 {
  FILE *file;

  int format_version, number_of_texture_points, number_of_polygoned_faces, number_of_point_normals, number_of_lighting_normals, number_of_point_references, number_of_surface_point_references, number_of_surface_point_normals;

  file = fopen(filename, "rb");
  if (!file)
   return;

  fread(&format_version, 4, 1, file);
  if (format_version != 1)
   return;

  fread(&number_of_points, 4, 1, file);
  fread(&number_of_faces, 4, 1, file);
  fread(&number_of_polygoned_faces, 4, 1, file);
  fread(&number_of_surfaces, 4, 1, file);
  fread(&number_of_point_normals, 4, 1, file);
  fread(&number_of_lighting_normals, 4, 1, file);
  fread(&number_of_point_references, 4, 1, file);
  fread(&number_of_texture_points, 4, 1, file);
  fread(&number_of_surface_point_references, 4, 1, file);
  fread(&number_of_surface_point_normals, 4, 1, file);

  fread(&bounding_box, 24, 1, file);
  fread(&bounding_box2, 24, 1, file);
  fseek(file, 4, SEEK_CUR);

  if (number_of_points)
   {
    points = new OBJECT_SHORT_3D_POINT[number_of_points];
    fread(points, 6, number_of_points, file);
   }
  else
   points = NULL;
  if (number_of_polygoned_faces)
   {
    faces = new OBJECT_3D_FACE[number_of_polygoned_faces];
    fread(faces, 1, number_of_polygoned_faces, file);
   }
  else
   faces = NULL;
  fseek(file, 2 * number_of_point_normals, SEEK_CUR);
  if (number_of_point_references)
   {
    object_faces_point_plain_list = new POINT_3D_SHORT_REFERENCE[number_of_point_references];
    fread(object_faces_point_plain_list, 1, number_of_point_references, file);
   }
  else
   object_faces_point_plain_list = NULL;
  if (number_of_surfaces)
   {
    surfaces = new FACE_SURFACE_DESCRIPTION[number_of_surfaces];
    fread(surfaces, 16, number_of_surfaces, file);
   }
  else
   surfaces = NULL;
  fseek(file, 2 * number_of_polygoned_faces, SEEK_CUR);
  if (number_of_texture_points)
   {
    surface_texture_points = new OBJECT_3D_SHORT_TEXTURED_POINT[number_of_texture_points];
    fread(surface_texture_points, 8, number_of_texture_points, file);
   }
  else
   surface_texture_points = NULL;
  if (number_of_surface_point_references)
   {
    surface_points = new POINT_3D_PLAIN_REFERENCE[number_of_surface_point_references];
    fread(surface_points, 2, number_of_surface_point_references, file);
   }
  else
   surface_points = NULL;
  fseek(file, 2 * number_of_surface_point_normals, SEEK_CUR);

  char texture_name[256];
  for (int i = 0; i < number_of_surfaces; i++)
   {
    if (!get_nul_string(texture_name, sizeof(texture_name), file))
     break;
    if (*texture_name)
     surfaces[i].texture_index = (unsigned short int)eet.Append(texture_name);

    if (!get_nul_string(texture_name, sizeof(texture_name), file))
     break;
    if (*texture_name)
     surfaces[i].luminosity_texture_index = (unsigned short int)eet.Append(texture_name);
   }

  fclose (file);
 }
};

int main(int argc, char* argv[])
{
 puts("Enemy Engaged EEO to LWO converter build " __DATE__);

 if (argc < 3)
  {
   printf("Usage: eeo2lwo file_name.eeo file_name.lwo [textures extention]");
   return -1;
  }

 char filename[1024];

 EET eet(*getcwd(filename, sizeof(filename)), argc > 3 ? argv[3] : "tga");
 AllNames names(eet);
 const Object object(argv[1], eet);
 ExportLWO(eet, argv[2], object);

 return 0;
}
