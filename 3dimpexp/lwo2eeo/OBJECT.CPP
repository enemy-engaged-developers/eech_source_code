class OBJECT_3D : private Convert
{
 private:

 void Create(void)
 {
  Array<RNormal> normals;

  number_of_points = !Rpoints;
  number_of_faces = 0;
  number_of_surfaces = 0;
  number_of_texture_points = 0;
  number_of_polygoned_faces = 0;
  number_of_face_normal_references = 0;
  number_of_point_normals = 0;
  number_of_lighting_normals = 0;
  number_of_point_references = 0;
  number_of_surface_point_references = 0;
  number_of_surface_point_normals = 0;
  for (unsigned i = 0; i < !es; i++)
   {
    if (!!es[i].polys)
     continue;
    number_of_surfaces++;
    number_of_faces += !es[i].polys;
    if (es[i].rs->polygons)
     {
      number_of_polygoned_faces += !es[i].polys;
      if (!es[i].rs->smoothed)
       number_of_face_normal_references += !es[i].polys;

      for (unsigned j = 0; j < !es[i].polys; j++)
       {
        number_of_point_references += !es[i].polys[j].points;
        if (!es[i].rs->smoothed)
         AddPoint(normals, es[i].polys[j].norm);
       }

       if (es[i].rs->smoothed)
        {
         for (unsigned j = 0; j < !es[i].points; j++)
          {
           RNormal norm;
           es[i].points[j].normal.SetTo(norm);
           AddPoint(normals, norm);
           es[i].points[j].normal.index = norm.index;
          }
        }
     }
    else
     number_of_point_references += 2 * !es[i].polys;
    number_of_surface_point_references += !es[i].points;
    if (es[i].rs->smoothed)
     number_of_surface_point_normals += !es[i].points;
    if (es[i].rs->texture[0] != '\0')
     number_of_texture_points += !es[i].points;
    if (es[i].rs->ltexture[0] != '\0')
     number_of_texture_points += !es[i].points;
   }
  number_of_point_normals = !normals;
  number_of_lighting_normals = number_of_point_normals;

  bounding_box.xmin = BBI.x;
  bounding_box.ymin = BBI.y;
  bounding_box.zmin = BBI.z;
  bounding_box.xmax = BBA.x;
  bounding_box.ymax = BBA.y;
  bounding_box.zmax = BBA.z;
  bounding_box2 = bounding_box;
  radius = Radius;

  points = new OBJECT_SHORT_3D_POINT[number_of_points];
  for (unsigned i = 0; i < number_of_points; i++)
   {
    points[i].x = Rpoints[i].x;
    points[i].y = Rpoints[i].y;
    points[i].z = Rpoints[i].z;
   }

  faces = new OBJECT_3D_FACE[number_of_polygoned_faces];
  {
   unsigned m = 0;
   for (unsigned i = 0; i < !es; i++)
    {
     if (!!es[i].polys)
      continue;
     if (!es[i].rs->polygons)
      continue;
     for (unsigned j = 0; j < !es[i].polys; j++)
      faces[m++].number_of_points = (unsigned char)!es[i].polys[j].points;
    }
   if (m != number_of_polygoned_faces)
    error("number_of_polygoned_faces");
  }

  point_normals = new OBJECT_3D_HEADING_PITCH_NORMAL[number_of_point_normals];
  for (unsigned i = 0; i < !normals; i++)
   {
    point_normals[i].heading = normals[i].heading;
    point_normals[i].pitch = normals[i].pitch;
   }

  object_faces_point_plain_list = new POINT_3D_SHORT_REFERENCE[number_of_point_references];
  {
   unsigned m = 0;
   for (unsigned i = 0; i < !es; i++)
    {
     if (!!es[i].polys)
      continue;
     for (unsigned j = 0; j < !es[i].polys; j++)
      for (unsigned k = 0; k < !es[i].polys[j].points; k++)
       object_faces_point_plain_list[m++].point = (unsigned char)es[i].polys[j].points[k].index;
    }
   if (m != number_of_point_references)
    error("number_of_point_references");
  }

  surfaces = new FACE_SURFACE_DESCRIPTION[number_of_surfaces];
  memset(surfaces, 0, number_of_surfaces * sizeof(*surfaces));
  textures = new SURFACE_TEXTURE[number_of_surfaces];
  memset(textures, 0, number_of_surfaces * sizeof(*textures));
  {
   unsigned m = 0;
   for (unsigned i = 0; i < !es; i++)
    {
     if (!!es[i].polys)
      continue;

     SURFACE_TEXTURE* t = &textures[m];
     FACE_SURFACE_DESCRIPTION* su = &surfaces[m++];
     const ESurface* s = &es[i];

     strcpy(t->texture, s->rs->texture);
     if (s->rs->camo)
      strcat(t->texture, "-D");
     strcpy(t->luminosity, s->rs->ltexture);
     su->polygons = s->rs->polygons;
     su->detail = s->rs->detail;
     su->smoothed = s->rs->smoothed;
     su->textured = t->texture[0] != '\0';
     su->has_luminosity_texture = t->luminosity[0] != '\0';
     su->translucent = s->rs->translucent;
     su->has_specularity = s->rs->has_specularity;
     su->texture_animation = s->rs->texture_animation != 0;
     su->texture_filtered = s->rs->texture_filtered;
     su->texture_mipmapped = s->rs->texture_mipmapped;
     su->texture_wrapped_u = s->rs->texture_wrapped_u;
     su->texture_wrapped_v = s->rs->texture_wrapped_v;
     su->luminosity_texture_animation = s->rs->luminosity_texture_animation != 0;
     su->luminosity_texture_filtered = s->rs->luminosity_texture_filtered;
     su->luminosity_texture_mipmapped = s->rs->luminosity_texture_mipmapped;
     su->luminosity_texture_wrapped_u = s->rs->luminosity_texture_wrapped_u;
     su->luminosity_texture_wrapped_v = s->rs->luminosity_texture_wrapped_v;
     su->number_of_points = (unsigned char)!s->points;
     su->texture_index = 0;
     su->luminosity_texture_index = 0;
     su->number_of_faces = (unsigned short)!s->polys;
     su->reflectivity = s->rs->reflectivity;
     su->specularity = s->rs->specularity;
     su->blue = s->rs->blue;
     su->green = s->rs->green;
     su->red = s->rs->red;
     su->alpha = s->rs->alpha;
    }
   if (m != number_of_surfaces)
    error("number_of_surfaces");
  }

  object_face_normal_references = new POINT_3D_PLAIN_REFERENCE[number_of_face_normal_references];
  {
   unsigned m = 0;
   for (unsigned i = 0; i < !es; i++)
    {
     if (!!es[i].polys)
      continue;
     if (!es[i].rs->polygons)
      continue;
     if (es[i].rs->smoothed)
      continue;
     for (unsigned j = 0; j < !es[i].polys; j++)
      object_face_normal_references[m++].point = (unsigned short)es[i].polys[j].norm.index;
    }
   if (m != number_of_face_normal_references)
    error("number_of_face_normal_references");
  }

  surface_texture_points = new OBJECT_3D_SHORT_TEXTURED_POINT[number_of_texture_points];
  {
   unsigned m = 0;
   for (unsigned i = 0; i < !es; i++)
    {
     if (!!es[i].polys)
      continue;
     if (es[i].rs->texture[0] == '\0' && es[i].rs->ltexture[0] == '\0')
      continue;
     for (unsigned j = 0; j < !es[i].points; j++)
      {
       if (es[i].rs->texture[0] != '\0')
        {
         surface_texture_points[m].u = es[i].points[j].tp.u;
         surface_texture_points[m].v = es[i].points[j].tp.v;
         m++;
        }
       if (es[i].rs->ltexture[0] != '\0')
        {
         surface_texture_points[m].u = es[i].points[j].lp.u;
         surface_texture_points[m].v = es[i].points[j].lp.v;
         m++;
        }
      }
    }
   if (m != number_of_texture_points)
    error("number_of_texture_points");
  }

  surface_points = new POINT_3D_PLAIN_REFERENCE[number_of_surface_point_references];
  {
   unsigned m = 0;
   for (unsigned i = 0; i < !es; i++)
    {
     if (!!es[i].polys)
      continue;
     for (unsigned j = 0; j < !es[i].points; j++)
      surface_points[m++].point = (unsigned short)es[i].points[j].p.index;
    }
   if (m != number_of_surface_point_references)
    error("number_of_surface_point_references");
  }

  surface_point_normals = new POINT_3D_PLAIN_REFERENCE[number_of_surface_point_normals];
  {
   unsigned m = 0;
   for (unsigned i = 0; i < !es; i++)
    {
     if (!!es[i].polys)
      continue;
     if (!es[i].rs->smoothed)
      continue;
     for (unsigned j = 0; j < !es[i].points; j++)
      surface_point_normals[m++].point = (unsigned short)es[i].points[j].normal.index;
    }
   if (m != number_of_surface_point_normals)
    error("number_of_surface_point_references");
  }
 }

 void Clear(void)
 {
  delete [] surface_point_normals;
  delete [] surface_points;
  delete [] surface_texture_points;
  delete [] object_face_normal_references;
  delete [] textures;
  delete [] surfaces;
  delete [] object_faces_point_plain_list;
  delete [] point_normals;
  delete [] faces;
  delete [] points;
 }

 void Write(const char* filename)
 {
  FILE* file = fopen(filename, "wb");
  if (!file)
   error("Failed to create %s", filename);

  int format = 2;
  fwrite(&format, 4, 1, file);
  fwrite(&number_of_points, 4, 1, file);
  fwrite(&number_of_faces, 4, 1, file);
  fwrite(&number_of_polygoned_faces, 4, 1, file);
  fwrite(&number_of_face_normal_references, 4, 1, file);
  fwrite(&number_of_surfaces, 4, 1, file);
  fwrite(&number_of_point_normals, 4, 1, file);
  fwrite(&number_of_lighting_normals, 4, 1, file);
  fwrite(&number_of_point_references, 4, 1, file);
  fwrite(&number_of_texture_points, 4, 1, file);
  fwrite(&number_of_surface_point_references, 4, 1, file);
  fwrite(&number_of_surface_point_normals, 4, 1, file);
  fwrite(&bounding_box, 24, 1, file);
  fwrite(&bounding_box2, 24, 1, file);
  fwrite(&radius, 4, 1, file);
  fwrite(points, 6, number_of_points, file);
  fwrite(faces, 1, number_of_polygoned_faces, file);
  fwrite(point_normals, 2, number_of_point_normals, file);
  fwrite(object_faces_point_plain_list, 1, number_of_point_references, file);
  fwrite(surfaces, 16, number_of_surfaces, file);
  fwrite(object_face_normal_references, 2, number_of_face_normal_references, file);
  fwrite(surface_texture_points, 8, number_of_texture_points, file);
  fwrite(surface_points, 2, number_of_surface_point_references, file);
  fwrite(surface_point_normals, 2, number_of_surface_point_normals, file);
  for (unsigned i = 0; i < number_of_surfaces; i++)
  {
   fwrite(textures[i].texture, 1, strlen(textures[i].texture) + 1, file);
   fwrite(textures[i].luminosity, 1, strlen(textures[i].luminosity) + 1, file);
  }

  fclose(file);
 }

 unsigned number_of_points, number_of_faces, number_of_point_normals, number_of_surfaces, number_of_lighting_normals;
 float radius;
 struct OBJECT_3D_BOUNDS { float xmin, xmax, ymin, ymax, zmin, zmax; } bounding_box, bounding_box2;
 struct OBJECT_SHORT_3D_POINT { short int x, y, z; } *points;
 struct OBJECT_3D_FACE { unsigned char number_of_points; } *faces;
 struct OBJECT_3D_HEADING_PITCH_NORMAL { unsigned char heading, pitch; } *point_normals;
 struct POINT_3D_SHORT_REFERENCE { unsigned char point; } *object_faces_point_plain_list;
 struct FACE_SURFACE_DESCRIPTION
 {
  union
  {
   struct
   {
    unsigned short int polygons:1, detail:1, smoothed:1, textured:1, has_luminosity_texture:1, additive:1, translucent:1, luminous:1, has_specularity:1, texture_animation:1, texture_filtered:1, texture_mipmapped:1, texture_wrapped_u:1, texture_wrapped_v:1;
    unsigned char luminosity_texture_animation:1, luminosity_texture_filtered:1, luminosity_texture_mipmapped:1, luminosity_texture_wrapped_u:1, luminosity_texture_wrapped_v:1;
    unsigned char number_of_points;
   };
   unsigned int surface_flags;
  };
  unsigned short int texture_index, luminosity_texture_index, number_of_faces;
  union
  {
   struct { unsigned char reflectivity, specularity; };
   unsigned short int additional_surface_information;
  };
  union
  {
   struct { unsigned char blue, green, red, alpha; };
   unsigned int colour;
  };
 } *surfaces;
 struct SURFACE_TEXTURE
 {
  char texture[256];
  char luminosity[256];
 } *textures;
 struct POINT_3D_PLAIN_REFERENCE { unsigned short int point; } *object_face_normal_references;
 struct OBJECT_3D_SHORT_TEXTURED_POINT { float u, v; } *surface_texture_points;
 struct POINT_3D_PLAIN_REFERENCE /*{ unsigned short int point; }*/ *surface_points;
 struct POINT_3D_PLAIN_REFERENCE /*{ unsigned short int point; }*/ *surface_point_normals;


 unsigned number_of_texture_points;
 unsigned number_of_polygoned_faces;
 unsigned number_of_face_normal_references;
 unsigned number_of_point_references;
 unsigned number_of_surface_point_references;
 unsigned number_of_surface_point_normals;

 public:

 OBJECT_3D(const char* lwo, const char* eeo, const char* log)
   : Convert(lwo, log)
 {
  Create();
  Write(eeo);
  Clear();
 }
};
