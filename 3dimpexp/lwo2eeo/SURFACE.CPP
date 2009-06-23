struct RSurface
{
 Convert* Global;

 const Surface* s;
 Array<RPoly> polys;
 char texture[1024];
 char ltexture[1024];
 char tvmap[1024];
 char lvmap[1024];

 Array<RPolyPoint> points;

 unsigned polygons:1, detail:1, smoothed:1, translucent:1, has_specularity:1, texture_animation:1, texture_filtered:1, texture_mipmapped:1, texture_wrapped_u:1, texture_wrapped_v:1, luminosity_texture_animation, luminosity_texture_filtered:1, luminosity_texture_mipmapped:1, luminosity_texture_wrapped_u:1, luminosity_texture_wrapped_v:1;
 unsigned char reflectivity, specularity;
 unsigned char blue, green, red, alpha;

 RSurface(void)
  : Global(NULL), s(NULL),
    polygons(0), detail(0), smoothed(0), translucent(0), has_specularity(0), texture_animation(0), texture_filtered(0), texture_mipmapped(0), texture_wrapped_u(0), texture_wrapped_v(0), luminosity_texture_animation(0), luminosity_texture_filtered(0), luminosity_texture_mipmapped(0), luminosity_texture_wrapped_u(0), luminosity_texture_wrapped_v(0),
    reflectivity(0), specularity(0),
    blue(0), green(0), red(0), alpha(0)
 {
  texture[0] = '\0';
  ltexture[0] = '\0';
  tvmap[0] = '\0';
  lvmap[0] = '\0';
 }
 void ParseBlock(const LWOFile& lwofile, const Block* bl)
 {
  enum { NONE, TEXTURE, LUMINOSITY } type = NONE;

  if (!bl->header ||
      bl->header->blockheadertype != BlockHeader::IMAGEMAPTEXTURE)
   return;

  const Channel* bhc = NULL;
  for (unsigned k = 0; k < !bl->header->attributes; k++)
   if (bl->header->attributes[k]->blockheaderattributetype == BlockHeaderAttribute::CHANNEL)
    {
     bhc = static_cast<const Channel*>(bl->header->attributes[k]);
     break;
    }
  if (!bhc)
   return;
  if (bhc->texture_channel == "COLR")
   type = TEXTURE;
  if (bhc->texture_channel == "LUMI")
   type = LUMINOSITY;
  if (type == NONE)
   return;

  for (unsigned k = 0; k < !bl->attributes; k++)
   switch (bl->attributes[k]->blockattributetype)
    {
     case BlockAttribute::IMAGEWRAPOPTIONS:
      {
       const ImageWrapOptions* iwo = static_cast<const ImageWrapOptions*>(bl->attributes[k]);

       switch (type)
        {
         case TEXTURE:
          texture_wrapped_u = iwo->width_wrap;
          texture_wrapped_v = iwo->height_wrap;
          break;
         case LUMINOSITY:
          luminosity_texture_wrapped_u = iwo->width_wrap;
          luminosity_texture_wrapped_v = iwo->height_wrap;
          break;
        }
      }
      break;

     case BlockAttribute::ANTIALIASINGSTRENGTH:
      {
       const AntialiasingStrength* as = static_cast<const AntialiasingStrength*>(bl->attributes[k]);

       switch (type)
        {
         case TEXTURE:
          texture_mipmapped = as->flags;
          break;
         case LUMINOSITY:
          luminosity_texture_mipmapped = as->flags;
          break;
        }
      }
      break;

     case BlockAttribute::PIXELBLENDING:
      {
       const PixelBlending* pb = static_cast<const PixelBlending*>(bl->attributes[k]);

       switch (type)
        {
         case TEXTURE:
          texture_filtered = pb->flags;
          break;
         case LUMINOSITY:
          luminosity_texture_filtered = pb->flags;
          break;
        }
      }
      break;

     case BlockAttribute::UVVERTEXMAP:
      {
       const UVVertexMap* uv = static_cast<const UVVertexMap*>(bl->attributes[k]);

       switch (type)
        {
         case TEXTURE:
          if (tvmap[0] != '\0')
           error("Surface '%s': Duplicate vertex mapping name for surface '%s' '%s'", &s->name, tvmap, &uv->txuv_map_name);
          strcpy(tvmap, uv->txuv_map_name);
          break;
         case LUMINOSITY:
          if (lvmap[0] != '\0')
           error("Surface '%s': Duplicate luminosity vertex mapping name for surface '%s' '%s'", &s->name, lvmap, &uv->txuv_map_name);
          strcpy(lvmap, uv->txuv_map_name);
          break;
        }
      }
      break;

     case BlockAttribute::IMAGEMAP:
      {
       const ImageMap* im = static_cast<const ImageMap*>(bl->attributes[k]);
       const Image* image = NULL;

       for (unsigned m = 0; m < !lwofile.chunks; m++)
        if (lwofile.chunks[m]->chunktype == Chunk::IMAGE)
         {
          const Image* ima = static_cast<const Image*>(lwofile.chunks[m]);
          if (ima->index == im->texture_image)
           {
            image = ima;
            break;
           }
         }

       if (!image)
        {
         switch (type)
          {
           case TEXTURE:
            warning("Surface '%s': Texture is set but texture file is not", &s->name);
            break;
           case LUMINOSITY:
            warning("Surface '%s': Luminosity texture is set but texture file is not", &s->name);
            break;
          }
         break;
        }

       char filename[1024] = "";

       for (unsigned m = 0; m < !image->attributes; m++)
        {
         if (image->attributes[m]->imageattributetype == ImageAttribute::STILLIMAGE)
          {
           const StillImage* si = static_cast<const StillImage*>(image->attributes[m]);
           if (*filename)
            error("Surface '%s': Filename for image supplied more then once '%s' and '%s'", &s->name, filename, &si->name);
           strcpy(filename, si->name);
          }
        }

       if (!*filename)
        {
         switch (type)
          {
           case TEXTURE:
            warning("Surface '%s': Filename for texture image is not supplied", &s->name);
            break;
           case LUMINOSITY:
            warning("Surface '%s': Filename for texture image is not supplied", &s->name);
            break;
          }
         break;
        }

       switch (type)
        {
         case TEXTURE:
          if (texture[0] != '\0')
           error("Surface '%s': Duplicate texture for surface", &s->name);
          GetTextureName(texture, filename);
          break;
         case LUMINOSITY:
          if (ltexture[0] != '\0')
           error("Surface '%s': Duplicate luminosity texture for surface", &s->name);
          GetTextureName(ltexture, filename);
          break;
         }
       }
       break;

      default:
       break;
    }
 }
 void ParseAttribute(const LWOFile& lwofile, const SurfaceAttribute* attr)
 {
  switch (attr->surfaceattributetype)
   {
    case SurfaceAttribute::BASECOLOR:
     {
      const BaseColor* bc = static_cast<const BaseColor*>(attr);

      red = (unsigned char)(bc->base_color.red * 255.0f);
      green = (unsigned char)(bc->base_color.green * 255.0f);
      blue = (unsigned char)(bc->base_color.blue * 255.0f);
     }
     break;

    case SurfaceAttribute::REFLECTION:
     {
      const Reflection* r = static_cast<const Reflection*>(attr);

      reflectivity = (unsigned char)(r->intensity * 255.0f);
     }
     break;

    case SurfaceAttribute::SPECULARGLOSSINESS:
     {
      const SpecularGlossiness* sg = static_cast<const SpecularGlossiness*>(attr);

      has_specularity = 1;
      specularity = (unsigned char)(sg->glossiness * 255.0f);
     }
     break;

    case SurfaceAttribute::TRANSPARENCY:
     {
      const Transparency* t = static_cast<const Transparency*>(attr);

      translucent = 1;
      alpha = (unsigned char)((1.0f - t->intensity) * 255.0f);
     }
     break;

    case SurfaceAttribute::BLOCK:
     ParseBlock(lwofile, static_cast<const Block*>(attr));
     break;

    case SurfaceAttribute::COMMENT:
     {
      const Comment* c = static_cast<const Comment*>(attr);

      if (strstr(&c->comment, "detail="))
       detail = 1;

      texture_animation = ProcessAnimation(&c->comment, "texture_animation=", texture);
      luminosity_texture_animation = ProcessAnimation(&c->comment, "luminosity_animation=", ltexture);
     }
     break;

    case SurfaceAttribute::MAXSMOOTHINGANGLE:
     {
      const MaxSmoothingAngle* a = static_cast<const MaxSmoothingAngle*>(attr);

      if (a->max_smoothing_angle > 0.1)
       smoothed = 1;
     }
     break;

    default:
     break;
   }
 }
 void Parse(const LWOFile& lwofile, Convert& global)
 {
  Global = &global;

  for (unsigned i = 0; i < !Global->Point; i++)
   for (unsigned j = 0; j < !Global->Point[i].pl; j++)
    {
     const PolygonList* pl = Global->Point[i].pl[j].pl;

     for (unsigned k = 0; k < !Global->Point[i].pl[j].pt; k++)
      {
       unsigned index = ~0u;

       /* Find tag index which matches surface's name */
       const Tags* t = Global->Point[i].pl[j].pt[k].t;
       for (unsigned l = 0; l < !t->tags; l++)
        if (strcmp(s->name, t->tags[l]) == 0)
         if (index != ~0u)
          error("Duplicate surface tag '%s'", &s->name);
         else
          index = l;

       /* Find all of the polygons for found index */
       const PTags* pt = Global->Point[i].pl[j].pt[k].pt;
       for (unsigned l = 0; l < !pt->ptags; l++)
        if (pt->ptags[l].tag == index)
         {
          unsigned m = pt->ptags[l].poly;
          if (m >= !pl->list)
           error("Invalid polygon index %u %u", m, !pl->list);

          unsigned npoints = pl->list[m].numvertflags & 0x3FF;

          if (npoints < 2)
           error("Surface '%s': Invalid polygon %u (< 2 points)", &s->name, npoints);

          if (npoints >= 256)
           error("Surface '%s': Too large polygon %u point (> 256 points)", &s->name, npoints);

          if (!!polys)
           polygons = npoints > 2;
          else
           if (polygons != (npoints > 2))
            error("Surface '%s': Mix of polygons and nonpolygons", &s->name);

          RPoly* ro = &polys.Append();

          ro->pl = Global->Point[i].pl[j].pl;
          ro->index = m;
          for (unsigned n = 0; n < npoints; n++)
           {
            unsigned o = pl->list[m].vert[n];
            if (o >= !Global->Point[i].p->points)
             error("Surface '%s': Invalid point index %u %u", &s->name, o, !Global->Point[i].p->points);
            ro->points[n].p = Global->Rpoints[Global->Point[i].rp[o]];
            ro->points[n].p.index = o;
           }

          if (polygons)
           {
            bool clear = true;
            for (unsigned i = 0; clear && i < npoints - 2; i++)
             for (unsigned j = i + 1; clear && j < npoints - 1; j++)
              for (unsigned k = j + 1; clear && k < npoints; k++)
               if (!ro->norm.Set(ro->points[i].p, ro->points[j].p, ro->points[k].p))
                clear = false;
           }
         }
      }
    }

  /* Find names of textures and vertex maps for the surface */
  for (unsigned i = 0; i < !s->attributes; i++)
   ParseAttribute(lwofile, s->attributes[i]);

  if (texture[0] == '\0')
   {
    if (tvmap[0] != '\0')
     {
      warning("Surface '%s': UV mapping is supplied but texture is not", &s->name);
      tvmap[0] = '\0';
     }
   }
  else
   if (tvmap[0] == '\0')
    {
     warning("Surface '%s': Texture is supplied but UV mapping is not", &s->name);
     texture[0] = '\0';
    }
  if (texture[0] != '\0')
   UV(tvmap, &RPolyPoint::tp);
  if (ltexture[0] == '\0')
   {
    if (lvmap[0] != '\0')
     {
      warning("Surface '%s': UV mapping is supplied but luminosity texture is not", &s->name);
      lvmap[0] = '\0';
     }
   }
  else
   if (lvmap[0] == '\0')
    {
     warning("Surface '%s': Luminosity texture is supplied but UV mapping is not", &s->name);
     ltexture[0] = '\0';
    }
  if (ltexture[0] != '\0')
   UV(lvmap, &RPolyPoint::lp);

  /* Create points */
  for (unsigned i = 0; i < !polys; i++)
   for (unsigned j = 0; j < !polys[i].points; j++)
    AddPoint(points, polys[i].points[j]);
  if (!points > 256)
   error("Surface '%s': More than 256 different points", &s->name);

  if (smoothed)
   {
    for (unsigned i = 0; i < !polys; i++)
     {
      for (unsigned j = 0; j < !polys[i].points; j++)
       {
        points[polys[i].points[j].index].normal += polys[i].norm;
       }
     }
   }
 }
 void UV(const char* vmap, RTPoint RPolyPoint::* tp)
 {
  char buf[4096];

  for (unsigned i = 0; i < !polys; i++)
   {
    const VertexMapping* vm = NULL;
    const DiscontinuousVertexMapping* dvm = NULL;
    const PTags::Ptags* pttp = NULL;
    const Tags* t = NULL;

    for (unsigned j = 0; j < !Global->Point; j++)
     for (unsigned k = 0; k < !Global->Point[j].pl; k++)
      if (Global->Point[j].pl[k].pl == polys[i].pl)
       {
        for (unsigned l = 0; l < !Global->Point[j].vm; l++)
         if (strcmp(Global->Point[j].vm[l]->name, vmap) == 0)
          {
           if (vm)
            error("Surface '%s': Duplicate vertex mapping '%s'", &s->name, vmap);
           vm = Global->Point[j].vm[l];
          }

        for (unsigned l = 0; l < !Global->Point[j].pl[k].dvm; l++)
         if (strcmp(Global->Point[j].pl[k].dvm[l]->name, vmap) == 0)
          {
           if (dvm)
            error("Surface '%s': Duplicate discontinuous vertex mapping '%s'", &s->name, vmap);
           dvm = Global->Point[j].pl[k].dvm[l];
          }

        for (unsigned l = 0; l < !Global->Point[j].pl[k].ptt; l++)
         {
          const LPTags& lp = Global->Point[j].pl[k].ptt[l];
          for (unsigned j = 0; j < !lp.pt->ptags; j++)
           if (lp.pt->ptags[j].poly == polys[i].index)
            {
             if (pttp)
              error("Surface '%s': Duplicate PTAG TXUV entry", &s->name);
             pttp = &lp.pt->ptags[j];
             if (pttp->tag >= !lp.t->tags)
              error("Surface '%s': Invalid tag index", &s->name);
             t = lp.t;
            }
         }
       }

    if (pttp)
     {
      const char* ptr;

      strcpy(buf, t->tags[pttp->tag]);
      ptr = buf;
      for (unsigned j = 0; j < !polys[i].points; j++)
       {
        float value[2];

        for (unsigned k = 0; k < 2; k++)
         {
          while (*ptr == ' ')
           ptr++;
          if (*ptr == '\0')
           error("Surface '%s': Invalid locked vertex map", &s->name);
          value[k] = atof(ptr);
          while (*ptr != ' ' && *ptr != '\0')
           ptr++;
         }
        (polys[i].points[j].*tp).Set(value);
       }
     }
    else
     if (dvm)
      {
       for (unsigned j = 0; j < !dvm->mapping; j++)
        if (polys[i].index == dvm->mapping[j].poly)
         for (unsigned k = 0; k < !polys[i].points; k++)
          if (polys[i].points[k].p.index == dvm->mapping[j].vert)
           (polys[i].points[k].*tp).Set(&dvm->mapping[j].value[0]);
      }
     else
      if (vm)
       {
        for (unsigned j = 0; j < !vm->mapping; j++)
         for (unsigned k = 0; k < !polys[i].points; k++)
          if (polys[i].points[k].p.index == vm->mapping[j].vert)
           (polys[i].points[k].*tp).Set(&vm->mapping[j].value[0]);
       }
      else
       {
        warning("Surface '%s': No vertex mapping '%s' found", &s->name, vmap);
        float zero[2] = { 0, 0 };
        for (unsigned k = 0; k < !polys[i].points; k++)
         (polys[i].points[k].*tp).Set(zero);
       }

    for (unsigned j = 0; j < !polys[i].points; j++)
     if (!(polys[i].points[j].*tp).set)
      error("Surface '%s': Not all texture points set for polygon # %i", &s->name, polys[i].index + 1);
   }
 }
 void GetTextureName(char* texture, const char* filename)
 {
  char* ptr;

  ptr = strrchr(filename, '\\');
  if (!ptr)
   ptr = strchr(filename, ':');
  if (ptr)
   strcpy(texture, ptr + 1);
  else
   strcpy(texture, filename);
  ptr = strchr(texture, '.');
  if (ptr)
   *ptr = '\0';
 }
 unsigned ProcessAnimation(const char* comment, const char* tag, char* name)
 {
  const char* p = strstr(comment, tag);
  if (!p)
   return 0;
  p += strlen(tag);
  const char* g = p;
  for (; *g && !isspace(*g); g++);
  if (p == g)
   return 0;
  int length = g - p;
  memcpy(name, p, length);
  name[length] = '\0';
  return 1;
 }
};
