#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <assert.h>
#include <memory.h>
#include <ctype.h>
#include <sys/stat.h>
#include <map>
#include <set>
#include <vector>
#include <string>

#define LOAD_CUSTOM
#define EET_NOEXPORT
#define SAFE_FOPEN_RB

class Object;

#include "../ee_exp/ee3dexp.cpp"
#include "../common/common.h"
#include "../ee_exp/names.cpp"
#include "../ee_exp/textures.cpp"
#include "../ee_exp/trans.cpp"
#include "../ee_exp/scenes.cpp"
#include "../ee_exp/lws_exp.cpp"
#include "../ees2lws/ees2lws.h"

#define PREC (1 << 12)

struct DDS_PIXELFORMAT
{
 DWORD dwSize;
 DWORD dwFlags;
 DWORD dwFourCC;
 DWORD dwRGBBitCount;
 DWORD dwRBitMask;
 DWORD dwGBitMask;
 DWORD dwBBitMask;
 DWORD dwABitMask;
};
struct DDS_HEADER
{
 DWORD dwSize;
 DWORD dwFlags;
 DWORD dwHeight;
 DWORD dwWidth;
 DWORD dwPitchOrLinearSize;
 DWORD dwDepth;
 DWORD dwMipMapCount;
 DWORD dwReserved1[11];
 struct DDS_PIXELFORMAT ddspf;
 DWORD dwCaps;
 DWORD dwCaps2;
 DWORD dwCaps3;
 DWORD dwCaps4;
 DWORD dwReserved2;
};

unsigned log_2(unsigned x)
{
 int l = 0;
 while ((1u << l) < x)
  l++;
 return l;
}

class Skin : public AggTranslator, public LwsExporter, public BaseTexturesExporter
{
 public:

 Skin(const char* dir, Objects& objects, EET& eet, const char* scene, const char* ignore, const char* const* text_dirs)
  : dir(dir), objects(objects), eet(eet), scene(scene), ignore(ignore), text_dirs(text_dirs)
 {
 }

 const char* operator ()(int number)
 {
  Objs::const_iterator itor = objs.find(number);
  if (itor == objs.end())
   {
    itor = spec.find(number);
    if (itor == spec.end())
     error ("object not found");
    return objects[*itor].file;
   }
  sprintf(file, "%s_%s", scene, objects[*itor].file);
  return file;
 }
 int operator ()(const char* name)
 {
  char file[1024];
  char* p = strrchr(name, '/');
  strcpy(file, p ? p + 1 : name);
  p = strrchr(file, '.');
  if (p)
   *p = '\0';
  strupr(file);
  if (isxdigit(file[0]) && isxdigit(file[1]) && isxdigit(file[2]) && isxdigit(file[3]) && !file[4])
   return strtol(file, 0, 16);
  strupr(file);
  Loaded::iterator l = loaded.find(file);
  if (l != loaded.end())
   return l->second;
  char buf[1024];
  sprintf(buf, "%s\\%s.EEO", dir, file);
  int index = objects.LoadCustomObject(buf, eet);
  loaded.insert(Loaded::value_type(file, index));
  return index;
 }

 virtual void Begin(int)
 {
 }
 virtual void End(void)
 {
 }
 virtual void Object(int, int number, int, int special = 0, const char* = NULL)
 {
  if (number)
   if (special)
    {
     if (special < 0)
      spec.insert(number);
    }
   else
    objs.insert(number);
 }
 virtual void Parent(int)
 {
 }
 virtual void KeyFrames(const char*, int, int, int, const OBJECT_3D_SUB_OBJECT_KEYFRAME*)
 {
 }
 virtual void Limits(const char*, double, double)
 {
 }
 void LODs(int number_of_approximation_info, const OBJECT_3D_APPROXIMATION_INFO* approximation_info)
 {
  for (int i = 0; i < number_of_approximation_info; i++)
   {
    int number = approximation_info[i].object_number;
    if (number)
     objs.insert(number);
   }
 }
 virtual void Collision(void)
 {
 }
 virtual void Dissolve(int, const OBJECT_3D_SUB_OBJECT_VALUE_KEYFRAME*)
 {
 }
 virtual void Ambient(void)
 {
 }
 virtual void Light(int)
 {
 }
 virtual void LightAttrs(const REAL_COLOUR*)
 {
 }
#ifndef NO_LWSCAMERAEXPORT
 virtual void Camera(int, int)
 {
 }
 virtual void CameraAttrs(int, int, int, int, int)
 {
 }
#endif

 void process_textures(void)
 {
  load_ignore();
  gather_textures();
  printf("Total %u textures\n", texts.size());
  if (texts.empty())
   error("No textures found");
  export_textures(eet, false);
  load_textures();
  printf("Total %u textures\n", texts.size());
  if (texts.empty())
   error("No textures found");
  mkdir(scene);
  sort_textures();
  make_decisions();
  convert_objects();
 }

 void use_texture(int count, const char* name, int mip)
 {
  if (mip)
   return;
  Texts::iterator itor = texts.find(count);
  if (itor == texts.end())
   return;
  Text& t = itor->second;
  if (!try_load(t, name))
   {
    printf("Loading from textures.bin %s\n", name);
    t.width = width;
    t.height = height;
    t.alpha = bpp == 4;
    unsigned size = width * height * bpp;
    t.data.resize(size);
    memcpy(&t.data[0], texture_image_data, size);
   }
 }

private:
 const char* dir;
 Objects& objects;
 EET& eet;
 const char* scene;
 const char* ignore;
 const char* const* text_dirs;
 typedef std::map<std::string, int> Loaded;
 Loaded loaded;
 typedef std::set<int> Objs;
 Objs spec, objs;
 char file[256];
 std::set<unsigned> ign;
 struct Text
 {
  Text()
   : width(0), height(0), alpha(false), ui(FLT_MAX), ua(-FLT_MAX), vi(FLT_MAX), va(-FLT_MAX)
  {
  }
  unsigned width, height;
  bool alpha;
  std::vector<unsigned char> data;
  float ui, ua, vi, va;
  int iu, au, iv, av;
  int ru, rv;
 };
 typedef std::map<int, Text> Texts;
 Texts texts;
 typedef std::pair<int, int> Dim;
 struct RevCmp
 {
  bool operator ()(const Dim& d1, const Dim& d2) const
  {
   return d2 < d1;
  }
 };
 typedef std::multimap<Dim, Text*, RevCmp> STexts;
 STexts stexts;
 struct Position
 {
  unsigned u, v;
 };
 typedef std::map<const Text*, Position> Placement;
 struct Decision
 {
  Position size;
  Placement placement;
 };
 std::auto_ptr<Decision> bd;

 bool try_load(Text& t, const char* name)
 {
  bool loaded = false;
  for (const char* const* text_dir = text_dirs; *text_dir; text_dir++)
   {
    char file[1024];
    FILE* f;
    sprintf(file, "%s\\%s.BMP", *text_dir, name);
    f = fopen(file, "rb");
    if (f)
     {
      printf("Loading %s\n", file);
      load_bmp(f, t);
      loaded = true;
      fclose(f);
     }
    sprintf(file, "%s\\%s.TGA", *text_dir, name);
    f = fopen(file, "rb");
    if (f)
     {
      printf("Loading %s\n", file);
      load_tga(f, t);
      loaded = true;
      fclose(f);
     }
    sprintf(file, "%s\\%s.DDS", *text_dir, name);
    f = fopen(file, "rb");
    if (f)
     {
      printf("Loading %s\n", file);
      load_dds(f, t);
      loaded = true;
      fclose(f);
     }
   }
  if (loaded)
   {
    if (t.width & (t.width - 1))
     warning("Invalid width %u", t.width);
    if (t.height & (t.height - 1))
     warning("Invalid height %u", t.height);
   }
  return loaded;
 }

 void load_bmp(FILE* f, Text& t)
 {
  BITMAPFILEHEADER bmfh;
  BITMAPINFOHEADER bmih;
  fread(&bmfh, sizeof(bmfh), 1, f);
  fread(&bmih, sizeof(bmih), 1, f);
  if (bmih.biSize != sizeof(bmih) || bmih.biCompression != BI_RGB || (bmih.biBitCount != 24 && bmih.biBitCount != 32))
   error("Invalid BMP");
  t.width = bmih.biWidth;
  t.height = bmih.biHeight;
  t.alpha = false;
  unsigned s = t.width * 3 % 4;
  if (s)
   s = 4 - s;
  unsigned size = t.width * t.height * 3;
  t.data.resize(size);
  if (bmih.biBitCount == 24)
   if (!s)
    fread(&t.data[0], size, 1, f);
   else
   for (unsigned i = 0; i < size; i += t.width * 3)
    {
     fread(&t.data[i], t.width * 3, 1, f);
     fseek(f, s, SEEK_CUR);
    }
  else
   for (unsigned i = 0; i < size; i += 3)
    {
     fread(&t.data[i], 3, 1, f);
     fseek(f, 1, SEEK_CUR);
    }
  for (unsigned i = 0; i < t.height / 2; i++)
   for (unsigned j = 0; j < t.width * 3; j++)
    {
      unsigned char& a = t.data[i * t.width * 3 + j];
      unsigned char& b = t.data[(t.height - i - 1) * t.width * 3 + j];
      unsigned char c = a;
      a = b;
      b = c;
    }
 }

 void load_tga(FILE* f, Text& t)
 {
  unsigned char header[18];
  fread(header, sizeof(header), 1, f);
  if (header[1] || (header[2] != 2 && header[2] != 10) || (header[16] != 24 && header[16] != 32) || (header[17] & 0xD0))
   error("Invalid TGA");
  t.width = ((unsigned) header[13] << 8) | header[12];
  t.height = ((unsigned) header[15] << 8) | header[14];
  t.alpha = header[16] == 32;
  unsigned bpp = (t.alpha ? 4 : 3), size = t.width * t.height * bpp;
  t.data.resize(size);
  if (header[2] == 2)
   fread(&t.data[0], size, 1, f);
  else
   {
    unsigned char count;
    unsigned char buf[512];
    unsigned offset = 0;
    do
     {
      fread(&count, 1, 1, f);
      if (count++ & 0x80)
       {
        count -= 0x80;
        fread(buf, bpp, 1, f);
        while (count--)
         {
          memcpy(&t.data[offset], buf, bpp);
          offset += bpp;
         }
       }
      else
       {
        unsigned size;
        size = count * bpp;
        fread(&t.data[offset], size, 1, f);
        offset += size;
       }
     }
    while (offset < size);
   }
   if (!(header[17] & 0x20))
    for (unsigned i = 0; i < t.height / 2; i++)
     for (unsigned j = 0; j < t.width * bpp; j++)
      {
        unsigned char& a = t.data[i * t.width * bpp + j];
        unsigned char& b = t.data[(t.height - i - 1) * t.width * bpp + j];
        unsigned char c = a;
        a = b;
        b = c;
      }
 }

 void load_dds(FILE* f, Text& t)
 {
  DWORD dwmagic;
  DDS_HEADER ddsh;

  fread(&dwmagic, sizeof(dwmagic), 1, f);
  fread(&ddsh, sizeof(ddsh), 1, f);
  t.alpha = ddsh.ddspf.dwFlags & 1 ? true : false;
  t.width = ddsh.dwWidth;
  t.height = ddsh.dwHeight;
  unsigned size = ddsh.ddspf.dwRGBBitCount >> 3;
  if (size != (t.alpha ? 4 : 3))
   error("Invalid DDS");
  size *= t.width * t.height;
  t.data.resize(size);
  fread(&t.data[0], size, 1, f);
#if 1
  unsigned bpp = (t.alpha ? 4 : 3);
  for (unsigned i = 0; i < t.height / 2; i++)
   for (unsigned j = 0; j < t.width * bpp; j++)
    {
      unsigned char& a = t.data[i * t.width * bpp + j];
      unsigned char& b = t.data[(t.height - i - 1) * t.width * bpp + j];
      unsigned char c = a;
      a = b;
      b = c;
    }
#endif
 }

 void load_ignore(void)
 {
  eet.ExportAnimationTextures(ign);
  FILE* f = safe_fopen(ignore, "r");
  char buf[256];
  while (fgets(buf, sizeof(buf), f))
   {
    size_t l = strlen(buf);
    while (l && isspace(buf[l - 1]))
     l--;
    buf[l] = '\0';
    if (*buf)
     ign.insert(eet.Append(buf));
   }
  fclose(f);
 }
 void gather_textures(void)
 {
  for (Objs::const_iterator itor(objs.begin()); itor != objs.end(); ++itor)
   {
    const OBJECT_3D& obj = objects[*itor];
    const OBJECT_3D::OBJECT_3D_SHORT_TEXTURED_POINT* cstp = obj.surface_texture_points;
    for (unsigned i = 0; i < obj.number_of_surfaces; i++)
     {
      const OBJECT_3D::FACE_SURFACE_DESCRIPTION& s = obj.surfaces[i];
      int number_of_points = s.number_of_points ? s.number_of_points : 256;
      if (s.textured)
       {
        if (!s.texture_animation && ign.find(s.texture_index) == ign.end())
         {
          //printf("%s %s\n", obj.file, eet.GetTexture(s.texture_index));
          Text& t = texts[eet.Append(eet.GetTexture(s.texture_index))];
          for (int j = 0; j < number_of_points; j++) 
           {
            OBJECT_3D::OBJECT_3D_SHORT_TEXTURED_POINT p = cstp[s.has_luminosity_texture ? j * 2 : j];
            if (!s.texture_wrapped_u && (p.u < 0.0f || p.u > 1.0f))
             warning("Object %s texture %s not u wrapped but u %f", obj.file, eet.GetTexture(s.texture_index), p.u);
            if (!s.texture_wrapped_v && (p.v < 0.0f || p.v > 1.0f))
             warning("Object %s texture %s not v wrapped but v %f", obj.file, eet.GetTexture(s.texture_index), p.v);
            t.ui = min(t.ui, p.u);
            t.ua = max(t.ua, p.u);
            t.vi = min(t.vi, p.v);
            t.va = max(t.va, p.v);
           }
         }
        cstp += number_of_points;
        if (s.has_luminosity_texture)
         cstp += number_of_points;
       }
     }
   }
 }
 void load_textures(void)
 {
  for (Texts::iterator itor(texts.begin()); itor != texts.end(); ++itor)
   {
    Text& t = itor->second;
    const char* name = eet.GetTexture(itor->first);
    if (!t.data.empty())
     continue;
    if (!try_load(t, name))
     error("Failed to find texture %s", name);
   }
  bpp = 3;
  for (Texts::iterator itor(texts.begin()); itor != texts.end();)
   {
    if (itor->second.alpha)
     {
#if 1
      printf("%s has alpha\n", eet.GetTexture(itor->first));
      Texts::iterator old(itor);
      ++itor;
      texts.erase(old);
      continue;
#else
      bpp = 4;
      ++itor;
#endif
     }
    else
     ++itor;
   }
 }
 void sort_textures(void)
 {
  printf("    Actual     Required   U min   max     V min   max\n");
  for (Texts::iterator itor(texts.begin()); itor != texts.end(); ++itor)
   {
    Text& t = itor->second;
    t.iu = (int)(t.ui * PREC);
    t.au = (int)(t.ua * PREC);
    t.iv = (int)(t.vi * PREC);
    t.av = (int)(t.va * PREC);
    t.iu = min(t.iu, 0);
    t.au = max(t.au, PREC);
    t.iv = min(t.iv, 0);
    t.av = max(t.av, PREC);
    t.ru = (t.width * (t.au - t.iu) + PREC - 1) / PREC;
    t.rv = (t.height * (t.av - t.iv) + PREC - 1) / PREC;
    printf("% 5i % 5i % 5i % 5i % 7.3f % 7.3f % 7.3f % 7.3f %s\n", t.width, t.height, t.ru, t.rv, t.ui, t.ua, t.vi, t.va, eet.GetTexture(itor->first));
    stexts.insert(STexts::value_type(t.ru < t.rv ? std::make_pair(t.rv, t.ru) : std::make_pair(t.ru, t.rv), &t));
   }
 }
 void make_decisions(void)
 {
  for (unsigned w = 1u << log_2(stexts.begin()->first.first), i = 0; i < 5; w <<= 1, i++)
   {
    Decision d;
    make_decision(w, d);
    if (!bd.get() || d.size.u * d.size.v < bd->size.u * bd->size.v)
     bd.reset(new Decision(d));
    if (w >= (1 << 13))
     break;
   }
   export_decision(*bd);
 }
 void make_decision(unsigned w, Decision& d)
 {
  std::vector<unsigned> h;
  h.resize(w);
  d.size.u = w;
  for (STexts::const_iterator st(stexts.begin()); st != stexts.end(); ++st)
   {
    unsigned b, bh = ~0u;
    for (unsigned i = 0; i <= w - st->first.first; i++)
     {
      unsigned ih = h[i];
      for (unsigned j = 1; j < st->first.first; j++)
       ih = max(ih, h[i + j]);
      if (ih < bh)
       {
        b = i;
        bh = ih;
       }
     }
    Position p = { b, bh };
    bh += st->first.second + 1;
    {
      unsigned i = 0;
      for (; i < st->first.first; i++)
       h[b + i] = bh;
      i += b;
      if (i < w)
       h[i] = bh;
    }
    d.placement.insert(Placement::value_type(st->second, p));
   }
  d.size.v = h[0];
  for (unsigned i = 1; i < h.size(); i++)
   d.size.v = max(d.size.v, h[i]);
  d.size.v = 1 << log_2(d.size.v);
 }
 void export_decision(const Decision& d)
 {
  std::vector<unsigned char> data;
  data.resize(d.size.u * d.size.v * bpp);
#if 0
  for (unsigned i = 0; i < data.size(); i += bpp)
   data[i] = 255;
#endif
  for (Placement::const_iterator p(d.placement.begin()); p != d.placement.end(); ++p)
   if (p->first->ru < p->first->rv)
    copyt(&data[0], d.size.u, *p->first, p->second);
   else
    copy(&data[0], d.size.u, *p->first, p->second);

  char filename[1024];
  sprintf(filename, "%s\\%s.TGA", scene, scene);
  FILE* file = safe_fopen(filename, "wb");
  fwrite("\0\0\002\0\0\0\0\0\0\0\0\0", 12, 1, file);
  fwrite(&d.size.u, 2, 1, file);
  fwrite(&d.size.v, 2, 1, file);
  fwrite(bpp == 3 ? "\030\040" : "\040\040", 2, 1, file);
  fwrite(&data[0], data.size(), 1, file);
  fclose(file);
 }
 void copy(unsigned char* data, unsigned um, const Text& t, const Position& p)
 {
  unsigned tbpp = t.alpha ? 4 : 3;
  unsigned char pixel[4];
  pixel[3] = 255;
  int itu = t.iu * t.width, itv = t.iv * t.height;
  for (; itu < 0; itu += t.width * PREC);
  for (; itv < 0; itv += t.height * PREC);
  itv /= PREC;
  unsigned tu = itu / PREC;
  for (unsigned u = 0; u < t.ru; u++)
   {
    unsigned tv = itv;
    for (unsigned v = 0; v < t.rv; v++)
     {
      memcpy(pixel, &t.data[((tv * t.width) + tu) * tbpp], tbpp);
      memcpy(data + ((p.v + v) * um + p.u + u) * bpp, pixel, bpp);
      if (++tv == t.height)
       tv = 0;
     }
    if (++tu == t.width)
     tu = 0;
   }
 }
 void copyt(unsigned char* data, unsigned um, const Text& t, const Position& p)
 {
  unsigned tbpp = t.alpha ? 4 : 3;
  unsigned char pixel[4];
  pixel[3] = 255;
  int itu = t.iu * t.width, itv = t.av * t.height;
  for (; itu < 0; itu += t.width * PREC);
  itu /= PREC;
  for (; itv >= 0; itv -= t.height * PREC);
  itv += t.height * PREC;
  unsigned tv = itv / PREC;
  for (unsigned u = 0; u < t.rv; u++)
   {
    unsigned tu = itu;
    for (unsigned v = 0; v < t.ru; v++)
     {
      memcpy(pixel, &t.data[((tv * t.width) + tu) * tbpp], tbpp);
      memcpy(data + ((p.v + v) * um + p.u + u) * bpp, pixel, bpp);
      if (++tu == t.width)
       tu = 0;
     }
    if (!tv)
     tv = t.height;
    --tv;
   }
 }
 void convert_objects()
 {
  int texture = eet.Append(scene);
  for (Objs::iterator itor(objs.begin()); itor != objs.end(); ++itor)
   {
    OBJECT_3D& obj = const_cast<OBJECT_3D&>(objects[*itor]);
    OBJECT_3D::OBJECT_3D_SHORT_TEXTURED_POINT* cstp = obj.surface_texture_points;
    for (unsigned i = 0; i < obj.number_of_surfaces; i++)
     {
      OBJECT_3D::FACE_SURFACE_DESCRIPTION& s = obj.surfaces[i];
      int number_of_points = s.number_of_points ? s.number_of_points : 256;
      if (s.textured)
       {
        Texts::const_iterator itor;
        if (!s.texture_animation && (itor = texts.find(eet.Append(eet.GetTexture(s.texture_index)))) != texts.end())
         {
          const Text& t = itor->second;
          Placement::const_iterator pos = bd->placement.find(&t);
          if (pos == bd->placement.end())
           error("Failed to find position for texture");
          for (int j = 0; j < number_of_points; j++) 
           {
            OBJECT_3D::OBJECT_3D_SHORT_TEXTURED_POINT& p = cstp[s.has_luminosity_texture ? j * 2 : j];
            if (t.ru < t.rv)
             {
              int utmp = (((int)(p.u * PREC)) - t.iu) * (t.width - 1);
              int vtmp = (((int)(p.v * PREC)) - t.iv) * (t.height - 1);
              if (utmp < 0 || utmp >= t.ru * PREC)
               error("utmp %s %f %i %i", eet.GetTexture(s.texture_index), p.u, utmp, t.ru * PREC);
              if (vtmp < 0 || vtmp >= t.rv * PREC)
               error("vtmp %s %f %i %i", eet.GetTexture(s.texture_index), p.v, vtmp, t.rv * PREC);
              p.v = (utmp + pos->second.v * PREC) / (float)(bd->size.v * PREC);
              p.u = ((t.rv * PREC - 1 - vtmp) + pos->second.u * PREC) / (float)(bd->size.u * PREC);
             }
            else
             {
              int utmp = (((int)(p.u * PREC)) - t.iu) * (t.width - 1);
              int vtmp = (((int)(p.v * PREC)) - t.iv) * (t.height - 1);
              if (utmp < 0 || utmp >= t.ru * PREC)
               error("utmp %s %f %i %i", eet.GetTexture(s.texture_index), p.u, utmp, t.ru * PREC);
              if (vtmp < 0 || vtmp >= t.rv * PREC)
               error("vtmp %s %f %i %i", eet.GetTexture(s.texture_index), p.v, vtmp, t.rv * PREC);
              p.u = (utmp + pos->second.u * PREC) / (float)(bd->size.u * PREC);
              p.v = (vtmp + pos->second.v * PREC) / (float)(bd->size.v * PREC);
             }
           }
          s.texture_wrapped_u = 0;
          s.texture_wrapped_v = 0;
          s.texture_index = texture;
         }
        cstp += number_of_points;
        if (s.has_luminosity_texture)
         cstp += number_of_points;
       }
     }
    char file[1024];
    sprintf(file, "%s\\%s.LWO", scene, operator()(*itor));
    ExportLWO(eet, file, obj);
   }
 }
};

int main(int argc, char* argv[])
{
 puts("Enemy Engaged Skin build " __DATE__);

 if (argc < 8)
  {
   puts("Usage: ee_skin.exe 3ddata_objects_directory common_objects_directory scene_objects_directory scene ignore_textures animations_directory textures_directories\nFor example, ee_skin.exe C:\\GAMES\\EE\\COHOKUM\\3DDATA C:\\GAMES\\EE\\COHOKUM\\3DDATA\\OBJECTS \"C:\\GAMES\\EE\\COHOKUM\\3DDATA\\OBJECTS\\AH-64D Apache Longbow\" AH64D_APACHE_LONGBOW IGNORE.TXT C:\\GAMES\\EE\\COHOKUM\\GRAPHICS\\TEXTURES\\ANIMATION C:\\GAMES\\EE\\COHOKUM\\GRAPHICS\\TEXTURES\\CAMO C:\\GAMES\\EE\\COHOKUM\\GRAPHICS\\TEXTURES\\GENERAL C:\\TEXTURES");
   return -1;
  }

 char scene[256];
 strcpy(scene, argv[4]);
 strupr(scene);
 mkdir(scene);
 char path[1024];
 sprintf(path, "%s\\%s.LOG", scene, scene);
 FILE* f = freopen(path, "w", stdout);
 if (!f)
  error("Failed to create log file %s", path);
 TexturesFinder textures_finder('0');
 EET eet(textures_finder);
 AllNames names(eet);
 TexturesExporter_ textures;
 textures.export_textures(eet, false);
 eet.LoadCustomAnimations(argv[6]);
 Objects objects(argv[1], 500);
 objects.LoadCustomObjects(argv[2], eet);
 Cameras cameras;
 Skin skin(argv[3], objects, eet, scene, argv[5], (const char* const *)(argv + 7));
 sprintf(path, "%s\\%s.EES", argv[3], argv[4]);
 Scene sc(path, names, cameras, skin);
 LwsExport exporter(cameras);
 exporter.ExportScene(&skin, &sc, true);
 skin.process_textures();
 sprintf(path, "%s\\%s.LWS", scene, scene);
 exporter.ExportScene(names, skin, path, sc);
 fclose(f);
 return 0;
}

extern "C" int _compiled_under_generic;
int _compiled_under_generic;
