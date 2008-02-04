#include <iostream.h>
#include <fstream.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../common/common.h"
#include "../common/error.cpp"
#include "lwo_exp.cpp"
#include "eet.cpp"
#include "objects.cpp"

void convert(const OBJECT_3D& obj, LWO_File& lwofile, EET& eet)
{
 LWO_Chunk* chunk;
 LWO_Chunk* vmadt;
 LWO_Chunk* vmadl;
 LWO_SubChunk* subchunk;
 LWO_SubChunk* ssc;
 LWO_SubChunk* sssc;
 int i, j, k;
 float value;
 char buf[1024];

 const OBJECT_3D::OBJECT_3D_FACE* current_object_3d_faces = obj.faces;
 const OBJECT_3D::POINT_3D_SHORT_REFERENCE* current_object_3d_point_list = obj.object_faces_point_plain_list;
 const OBJECT_3D::POINT_3D_PLAIN_REFERENCE* current_object_3d_surface_point_list = obj.surface_points;
 const OBJECT_3D::OBJECT_3D_SHORT_TEXTURED_POINT* current_object_3d_surface_point_texture_list = obj.surface_texture_points;

 eet.Clear();

 chunk = new LWO_Chunk("TAGS", 0, NULL);
 lwofile.AddSubChunk(chunk);
 for (i = 0; i < obj.number_of_surfaces; i++)
  {
   sprintf(buf, "Surface%03u", i);
   chunk->AddBasicData(strlen(buf) + 1, buf);
  }

 chunk = new LWO_Chunk("LAYR", 18, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0");
 lwofile.AddSubChunk(chunk);

 float xmax = max(fabs(obj.bounding_box.xmin), fabs(obj.bounding_box.xmax)),
       ymax = max(fabs(obj.bounding_box.ymin), fabs(obj.bounding_box.ymax)),
       zmax = max(fabs(obj.bounding_box.zmin), fabs(obj.bounding_box.zmax));
 chunk = new LWO_Chunk("PNTS", 0, NULL);
 lwofile.AddSubChunk(chunk);
 for (i = 0; i < obj.number_of_points; i++)
  {
   value = obj.points[i].x * xmax / 32767.0f;
   chunk->AddData(4, &value);
   value = obj.points[i].y * ymax / 32767.0f;
   chunk->AddData(4, &value);
   value = obj.points[i].z * zmax / 32767.0f;
   chunk->AddData(4, &value);
  }

 chunk = new LWO_Chunk("BBOX", 0, NULL);
 lwofile.AddSubChunk(chunk);
 value = obj.bounding_box2.xmin;
 chunk->AddData(4, &value);
 value = obj.bounding_box2.ymin;
 chunk->AddData(4, &value);
 value = obj.bounding_box2.zmin;
 chunk->AddData(4, &value);
 value = obj.bounding_box2.xmax;
 chunk->AddData(4, &value);
 value = obj.bounding_box2.ymax;
 chunk->AddData(4, &value);
 value = obj.bounding_box2.zmax;
 chunk->AddData(4, &value);

 value = 0.0;
 for (i = 0; i < obj.number_of_surfaces; i++)
  {
   const OBJECT_3D::FACE_SURFACE_DESCRIPTION * current_surface = &obj.surfaces[i];
   int number_of_surface_points = current_surface->number_of_points;

   if (number_of_surface_points == 0)
    number_of_surface_points = 256;

   if (current_surface->textured)
    {
     chunk = new LWO_Chunk("VMAP", 6, "TXUV\x00\x02");
     lwofile.AddSubChunk(chunk);
     sprintf(buf, "VertexMapTexture%03u", i);
     chunk->AddBasicData(strlen(buf) + 1, buf);
     for (j = 0; j < number_of_surface_points; j++)
      {
       chunk->AddIndex(current_object_3d_surface_point_list[j].point);
       chunk->AddData(4, &value);
       chunk->AddData(4, &value);
      }
    }
   if (current_surface->has_luminosity_texture)
    {
     chunk = new LWO_Chunk("VMAP", 6, "TXUV\x00\x02");
     lwofile.AddSubChunk(chunk);
     sprintf(buf, "VertexMapLuminosity%03u", i);
     chunk->AddBasicData(strlen(buf) + 1, buf);
     for (j = 0; j < number_of_surface_points; j++)
      {
       chunk->AddIndex(current_object_3d_surface_point_list[j].point);
       chunk->AddData(4, &value);
       chunk->AddData(4, &value);
      }
    }
  }

 chunk = new LWO_Chunk("POLS", 4, "FACE");
 lwofile.AddSubChunk(chunk);
 int cur_poly = 0;
 for (i = 0; i < obj.number_of_surfaces; i++)
  {
   const OBJECT_3D::FACE_SURFACE_DESCRIPTION * current_surface = &obj.surfaces[i];
   int number_of_surface_points = current_surface->number_of_points;

   if (number_of_surface_points == 0)
    number_of_surface_points = 256;

   if (current_surface->detail)
    printf("\tSurface %u: detail not supported\n", i);
   if (current_surface->additive)
    printf("\tSurface %u: additive not supported\n", i);
   if (current_surface->luminous)
    printf("\tSurface %u: luminous not supported\n", i);
   if (current_surface->texture_animation)
    printf("\tSurface %u: texture_animation not supported\n", i);
   if (current_surface->luminosity_texture_animation)
    printf("\tSurface %u: luminosity_texture_animation not supported\n", i);

   value = 0.0;
   if (current_surface->textured)
    {
     sprintf(buf, "VertexMapTexture%03u", i);
     vmadt = new LWO_Chunk("VMAD", 6, "TXUV\x00\x02");
     lwofile.AddSubChunk(vmadt);
     vmadt->AddBasicData(strlen(buf) + 1, buf);
    }
   if (current_surface->has_luminosity_texture)
    {
     sprintf(buf, "VertexMapLuminosity%03u", i);
     vmadl = new LWO_Chunk("VMAD", 6, "TXUV\x00\x02");
     lwofile.AddSubChunk(vmadl);
     vmadl->AddBasicData(strlen(buf) + 1, buf);
    }

   for (j = 0; j < current_surface->number_of_faces; j++, cur_poly++)
    {
     int number_of_face_points;

     if (current_surface->polygons)
      number_of_face_points = current_object_3d_faces->number_of_points;
     else
      number_of_face_points = 2;

     chunk->AddData(2, &number_of_face_points);

     for (k = 0; k < number_of_face_points; k++)
      {
       int surface_point_index = current_object_3d_point_list->point;
       int texture_point_index = surface_point_index;
       int point_index = current_object_3d_surface_point_list [ surface_point_index ].point;

       chunk->AddIndex(point_index);

       if (current_surface->textured)
        {
         if (current_surface->has_luminosity_texture)
          texture_point_index *= 2;
         vmadt->AddIndex(point_index);
         vmadt->AddIndex(cur_poly);
         value = current_object_3d_surface_point_texture_list [ texture_point_index ].u;
         vmadt->AddData(4, &value);
         value = 1.0f - current_object_3d_surface_point_texture_list [ texture_point_index ].v;
         vmadt->AddData(4, &value);
        }
       if (current_surface->has_luminosity_texture)
        {
         if (current_surface->textured)
          texture_point_index++;
         vmadl->AddIndex(point_index);
         vmadl->AddIndex(cur_poly);
         value = current_object_3d_surface_point_texture_list [ texture_point_index ].u;
         vmadl->AddData(4, &value);
         value = 1.0f - current_object_3d_surface_point_texture_list [ texture_point_index ].v;
         vmadl->AddData(4, &value);
        }

       current_object_3d_point_list++;
      }

     if (current_surface->polygons)
      current_object_3d_faces++;
    }

   current_object_3d_surface_point_list += number_of_surface_points;

   if (current_surface->textured)
    current_object_3d_surface_point_texture_list += number_of_surface_points;

   if (current_surface->has_luminosity_texture)
    current_object_3d_surface_point_texture_list += number_of_surface_points;
  }

 chunk = new LWO_Chunk("PTAG", 4, "SURF");
 lwofile.AddSubChunk(chunk);
 unsigned long index = 0;
 for (i = 0; i < obj.number_of_surfaces; i++)
  {
   const OBJECT_3D::FACE_SURFACE_DESCRIPTION * current_surface = &obj.surfaces[i];

   for (j = 0; j < current_surface->number_of_faces; j++)
    {
     chunk->AddIndex(index++);
     chunk->AddData(2, &i);
    }
  }

 for (i = 0; i < obj.number_of_surfaces; i++)
  {
   const OBJECT_3D::FACE_SURFACE_DESCRIPTION* current_surface = &obj.surfaces[i];

   if (current_surface->textured)
    eet.GetIndex(lwofile, current_surface->texture_index);
   if (current_surface->has_luminosity_texture)
    eet.GetIndex(lwofile, current_surface->luminosity_texture_index);

   chunk = new LWO_Chunk("SURF", 0, NULL);
   lwofile.AddSubChunk(chunk);
   sprintf(buf, "Surface%03u", i);
   chunk->AddBasicData(strlen(buf) + 1, buf);
   chunk->AddBasicData(2, "\0\0");

   subchunk = new LWO_SubChunk("COLR", 0, NULL);
   chunk->AddSubChunk(subchunk);
   value = current_surface->red / 255.0f;
   subchunk->AddData(4, &value);
   value = current_surface->green / 255.0f;
   subchunk->AddData(4, &value);
   value = current_surface->blue / 255.0f;
   subchunk->AddData(4, &value);
   subchunk->AddData(2, "\0\0");

   subchunk = new LWO_SubChunk("LUMI", 0, NULL);
   chunk->AddSubChunk(subchunk);
   value = 0.0;
   subchunk->AddData(4, &value);
   subchunk->AddIndex(0);

   subchunk = new LWO_SubChunk("SIDE", 2, "\x00\x03");
   chunk->AddSubChunk(subchunk);

   subchunk = new LWO_SubChunk("REFL", 0, NULL);
   chunk->AddSubChunk(subchunk);
   value = current_surface->reflectivity / 255.0f;
   subchunk->AddData(4, &value);
   subchunk->AddData(2, "\0\0");

   if (current_surface->has_specularity)
    {
     subchunk = new LWO_SubChunk("SPEC", 0, NULL);
     chunk->AddSubChunk(subchunk);
     value = current_surface->specularity / 255.0f;
     subchunk->AddData(4, &value);
     subchunk->AddData(2, "\0\0");
    }

   if (current_surface->translucent)
    {
     subchunk = new LWO_SubChunk("TRAN", 0, NULL);
     chunk->AddSubChunk(subchunk);
     value = 1.0f - current_surface->alpha / 255.0f;
     subchunk->AddData(4, &value);
     subchunk->AddData(2, "\0\0");
    }

   if (current_surface->smoothed)
    {
     subchunk = new LWO_SubChunk("SMAN", 0, NULL);
     chunk->AddSubChunk(subchunk);
     value = 1.5;
     subchunk->AddData(4, &value);
    }

   if (current_surface->textured)
    {
     subchunk = new LWO_SubChunk("BLOK", 0, NULL);
     chunk->AddSubChunk(subchunk);

     ssc = new LWO_SubChunk("IMAP", 2, "\x80");
     subchunk->AddSubChunk(ssc);

     sssc = new LWO_SubChunk("OPAC", 0, NULL);
     ssc->AddSubChunk(sssc);
     sssc->AddBasicData(2, "\0\0");
     value = 1.0;
     sssc->AddData(4, &value);
     sssc->AddBasicData(2, "\0\0");

     sssc = new LWO_SubChunk("CHAN", 4, "COLR");
     ssc->AddSubChunk(sssc);

     ssc = new LWO_SubChunk("TMAP", 0, NULL);
     subchunk->AddSubChunk(ssc);
     sssc = new LWO_SubChunk("SIZE", 0, NULL);
     ssc->AddSubChunk(sssc);
     value = 1.0;
     sssc->AddData(4, &value);
     sssc->AddData(4, &value);
     sssc->AddData(4, &value);
     sssc->AddData(2, "\0\0");

     ssc = new LWO_SubChunk("PROJ", 2, "\x00\x05");
     subchunk->AddSubChunk(ssc);

     ssc = new LWO_SubChunk("AXIS", 2, "\x00\x00");
     subchunk->AddSubChunk(ssc);

     ssc = new LWO_SubChunk("IMAG", 0, NULL);
     subchunk->AddSubChunk(ssc);
     ssc->AddIndex(eet.GetIndex(lwofile, current_surface->texture_index));

     ssc = new LWO_SubChunk("WRAP", 0, NULL);
     subchunk->AddSubChunk(ssc);
     j = current_surface->texture_wrapped_u;
     ssc->AddData(2, &j);
     j = current_surface->texture_wrapped_v;
     ssc->AddData(2, &j);

     ssc = new LWO_SubChunk("VMAP", 0, NULL);
     subchunk->AddSubChunk(ssc);
     sprintf(buf, "VertexMapTexture%03u", i);
     ssc->AddBasicData(strlen(buf) + 1, buf);

     ssc = new LWO_SubChunk("AAST", 0, NULL);
     subchunk->AddSubChunk(ssc);
     j = current_surface->texture_mipmapped;
     ssc->AddData(2, &j);
     value = 1.0;
     ssc->AddData(4, &value);

     ssc = new LWO_SubChunk("PIXB", 0, NULL);
     subchunk->AddSubChunk(ssc);
     j = current_surface->texture_filtered;
     ssc->AddData(2, &j);
    }

   if (current_surface->has_luminosity_texture)
    {
     subchunk = new LWO_SubChunk("BLOK", 0, NULL);
     chunk->AddSubChunk(subchunk);

     ssc = new LWO_SubChunk("IMAP", 2, "\x90");
     subchunk->AddSubChunk(ssc);

     sssc = new LWO_SubChunk("OPAC", 0, NULL);
     ssc->AddSubChunk(sssc);
     sssc->AddBasicData(2, "\0\0");
     value = 1.0;
     sssc->AddData(4, &value);
     sssc->AddBasicData(2, "\0\0");

     sssc = new LWO_SubChunk("CHAN", 4, "LUMI");
     ssc->AddSubChunk(sssc);

     ssc = new LWO_SubChunk("TMAP", 0, NULL);
     subchunk->AddSubChunk(ssc);
     sssc = new LWO_SubChunk("SIZE", 0, NULL);
     ssc->AddSubChunk(sssc);
     value = 1.0;
     sssc->AddData(4, &value);
     sssc->AddData(4, &value);
     sssc->AddData(4, &value);
     sssc->AddData(2, "\0\0");

     ssc = new LWO_SubChunk("PROJ", 2, "\x00\x05");
     subchunk->AddSubChunk(ssc);

     ssc = new LWO_SubChunk("AXIS", 2, "\x00\x00");
     subchunk->AddSubChunk(ssc);

     ssc = new LWO_SubChunk("IMAG", 0, NULL);
     subchunk->AddSubChunk(ssc);
     ssc->AddIndex(eet.GetIndex(lwofile, current_surface->luminosity_texture_index));

     ssc = new LWO_SubChunk("WRAP", 0, NULL);
     subchunk->AddSubChunk(ssc);
     j = current_surface->luminosity_texture_wrapped_u;
     ssc->AddData(2, &j);
     j = current_surface->luminosity_texture_wrapped_v;
     ssc->AddData(2, &j);

     ssc = new LWO_SubChunk("VMAP", 0, NULL);
     subchunk->AddSubChunk(ssc);
     sprintf(buf, "VertexMapLuminosity%03u", i);
     ssc->AddBasicData(strlen(buf) + 1, buf);

     ssc = new LWO_SubChunk("AAST", 0, NULL);
     subchunk->AddSubChunk(ssc);
     j = current_surface->luminosity_texture_mipmapped;
     ssc->AddData(2, &j);
     value = 1.0;
     ssc->AddData(4, &value);

     ssc = new LWO_SubChunk("PIXB", 0, NULL);
     subchunk->AddSubChunk(ssc);
     j = current_surface->luminosity_texture_filtered;
     ssc->AddData(2, &j);
    }
  }
}

void ExportLWO(EET& eet, const char* filename, const OBJECT_3D& obj)
{
 LWO_File lwofile;
 printf("Exporting object %s\n", filename);
 convert(obj, lwofile, eet);
 lwofile.WriteFile(filename);
}

#if 0
int main(void)
{
 char filename[1024];

 setbuf(stdout, NULL);

 EET eet;
 mkdir("_OBJECTS");
 printf("Loading objects\n");
 const Objects objects;
 for (int i = 1; i < objects.GetNumberOfObjects(); i++)
  {
   const OBJECT_3D& obj = objects.GetObject(i);
   if (obj.surfaces)
    {
     sprintf(filename, "_OBJECTS/%04X.LWO", i);
     ExportLWO(eet, filename, obj);
    }
  }
 return 0;
}
#endif
