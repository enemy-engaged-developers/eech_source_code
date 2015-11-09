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

enum CamoType
{
 CT_DEFAULT,
 CT_DESERT,
 CT_WINTER,
 CT_LAST
};
const char* suf[CT_LAST] = { "", "-D", "-W" };
const char* SUF[CT_LAST] = { "", "-DESERT", "-WINTER" };
unsigned log_2(unsigned x)
{
 int l = 0;
 while ((1u << l) < x)
  l++;
 return l;
}

typedef std::set<std::string> Ignore;
typedef std::vector<std::string> Textures;
struct Config
{
 Config(const char* file, const char* scene_file)
 {
  const char* p = strrchr(scene_file, '\\');
  if (p)
   {
    scene_objects.assign(scene_file, p - scene_file);
    p++;
   }
  else
   {
    scene_objects = ".";
    p = scene_file;
   }
  char* e = strrchr(scene_file, '.');
  if (e && e > p)
   scene.assign(p, e - p);
  else
   scene = p;
  strupr(const_cast<char*>(scene.c_str()));
  char buf[256];
  std::string category;
  FILE* f = safe_fopen(file, "r");
  while (fgets(buf, sizeof(buf), f))
   {
    size_t l = strlen(buf);
    while (l > 0 && isspace(buf[l - 1]))
     l--;
    if (!l)
     continue;
    buf[l] = '\0';
    strupr(buf);
    if (*buf == '[')
     {
      category = buf;
      continue;
     }
    if (category == "[TEXTURES]")
     textures.push_back(buf);
    else
     {
      if (category == "[IGNORE_TEXTURES]")
       ignore.insert(buf);
      else
       {
        char* p = strchr(buf, '=');
        if (p)
         {
          *p++ = '\0';
          if (!strcmp(buf, "EE_OBJECTS"))
           ee_objects = p;
          else
           {
            if (!strcmp(buf, "COMMON_OBJECTS"))
             common_objects = p;
            else
             {
              if (!strcmp(buf, "ANIMATIONS"))
               animations = p;
             }
           }
         }
       }
     }
   }
  fclose(f);
 }

 std::string ee_objects, common_objects, scene_objects, animations;
 std::string scene;
 Ignore ignore;
 Textures textures;
};

class Skin : public AggTranslator, public LwsExporter, public BaseTexturesExporter
{
 public:

 Skin(const char* dir, Objects& objects, EET& eet, const char* scene, const Ignore& ignore, const Textures& textures)
  : dir(dir), objects(objects), eet(eet), scene(scene), ignore(ignore), textures(textures)
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
  sort_textures();
  make_decisions();
  convert_objects();
 }

 void use_texture(int count, const char* name, int mip)
 {
  if (mip)
   return;
  CamoType ct = CT_DEFAULT;
  size_t l = strlen(name);
  char n[256];
  if (l > 2 && name[-2] == '-' && name[-1] == 'D')
   {
    ct = CT_DESERT;
    count--;
    memcpy(n, name, l - 2);
    n[l - 2] = '\0';
    name = n;
   }
  Texts::iterator itor = texts.find(count);
  if (itor == texts.end())
   return;
  Text& t = itor->second;
  if (!try_load(t, name, ct))
   {
    printf("Loading from textures.bin %s%s\n", name, suf[ct]);
    t.images[ct].width = width;
    t.images[ct].height = height;
    t.images[ct].alpha = bpp == 4;
    unsigned size = width * height * bpp;
    t.images[ct].data.resize(size);
    memcpy(&t.images[ct].data[0], texture_image_data, size);
   }
 }

private:
 const char* dir;
 Objects& objects;
 EET& eet;
 const char* scene;
 const Ignore& ignore;
 const Textures& textures;
 typedef std::map<std::string, int> Loaded;
 Loaded loaded;
 typedef std::set<int> Objs;
 Objs spec, objs;
 char file[256];
 std::set<unsigned> ign;
 bool has_desert, has_winter;
 struct Image
 {
  unsigned width, height;
  bool alpha;
  std::vector<unsigned char> data;
 };
 struct Text
 {
  Text()
   : ui(FLT_MAX), ua(-FLT_MAX), vi(FLT_MAX), va(-FLT_MAX)
  {
  }
  Image images[CT_LAST];
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

 bool try_load(Text& t, const char* name, CamoType ct)
 {
  bool loaded = false;
  for (Textures::const_iterator itor(textures.begin()); itor != textures.end(); ++itor)
   {
    char file[1024];
    FILE* f;
    sprintf(file, "%s\\%s%s.BMP", itor->c_str(), name, suf[ct]);
    f = fopen(file, "rb");
    if (f)
     {
      printf("Loading %s\n", file);
      load_bmp(f, t, ct);
      loaded = true;
      fclose(f);
     }
    sprintf(file, "%s\\%s%s.TGA", itor->c_str(), name, suf[ct]);
    f = fopen(file, "rb");
    if (f)
     {
      printf("Loading %s\n", file);
      load_tga(f, t, ct);
      loaded = true;
      fclose(f);
     }
    sprintf(file, "%s\\%s%s.DDS", itor->c_str(), name, suf[ct]);
    f = fopen(file, "rb");
    if (f)
     {
      printf("Loading %s\n", file);
      load_dds(f, t, ct);
      loaded = true;
      fclose(f);
     }
   }
  if (loaded)
   {
    if (t.images[ct].width & (t.images[ct].width - 1))
     warning("Invalid width %u", t.images[ct].width);
    if (t.images[ct].height & (t.images[ct].height - 1))
     warning("Invalid height %u", t.images[ct].height);
   }
  return loaded;
 }

 void load_bmp(FILE* f, Text& t, CamoType ct)
 {
  BITMAPFILEHEADER bmfh;
  BITMAPINFOHEADER bmih;
  fread(&bmfh, sizeof(bmfh), 1, f);
  fread(&bmih, sizeof(bmih), 1, f);
  if (bmih.biSize != sizeof(bmih) || bmih.biCompression != BI_RGB || (bmih.biBitCount != 24 && bmih.biBitCount != 32))
   error("Invalid BMP");
  t.images[ct].width = bmih.biWidth;
  t.images[ct].height = bmih.biHeight;
  t.images[ct].alpha = false;
  unsigned s = t.images[ct].width * 3 % 4;
  if (s)
   s = 4 - s;
  unsigned size = t.images[ct].width * t.images[ct].height * 3;
  t.images[ct].data.resize(size);
  if (bmih.biBitCount == 24)
   if (!s)
    fread(&t.images[ct].data[0], size, 1, f);
   else
   for (unsigned i = 0; i < size; i += t.images[ct].width * 3)
    {
     fread(&t.images[ct].data[i], t.images[ct].width * 3, 1, f);
     fseek(f, s, SEEK_CUR);
    }
  else
   for (unsigned i = 0; i < size; i += 3)
    {
     fread(&t.images[ct].data[i], 3, 1, f);
     fseek(f, 1, SEEK_CUR);
    }
  for (unsigned i = 0; i < t.images[ct].height / 2; i++)
   for (unsigned j = 0; j < t.images[ct].width * 3; j++)
    {
      unsigned char& a = t.images[ct].data[i * t.images[ct].width * 3 + j];
      unsigned char& b = t.images[ct].data[(t.images[ct].height - i - 1) * t.images[ct].width * 3 + j];
      unsigned char c = a;
      a = b;
      b = c;
    }
 }

 void load_tga(FILE* f, Text& t, CamoType ct)
 {
  unsigned char header[18];
  fread(header, sizeof(header), 1, f);
  if (header[1] || (header[2] != 2 && header[2] != 10) || (header[16] != 24 && header[16] != 32) || (header[17] & 0xD0))
   error("Invalid TGA");
  t.images[ct].width = ((unsigned) header[13] << 8) | header[12];
  t.images[ct].height = ((unsigned) header[15] << 8) | header[14];
  t.images[ct].alpha = header[16] == 32;
  unsigned bpp = (t.images[ct].alpha ? 4 : 3), size = t.images[ct].width * t.images[ct].height * bpp;
  t.images[ct].data.resize(size);
  if (header[2] == 2)
   fread(&t.images[ct].data[0], size, 1, f);
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
          memcpy(&t.images[ct].data[offset], buf, bpp);
          offset += bpp;
         }
       }
      else
       {
        unsigned size;
        size = count * bpp;
        fread(&t.images[ct].data[offset], size, 1, f);
        offset += size;
       }
     }
    while (offset < size);
   }
   if (!(header[17] & 0x20))
    for (unsigned i = 0; i < t.images[ct].height / 2; i++)
     for (unsigned j = 0; j < t.images[ct].width * bpp; j++)
      {
        unsigned char& a = t.images[ct].data[i * t.images[ct].width * bpp + j];
        unsigned char& b = t.images[ct].data[(t.images[ct].height - i - 1) * t.images[ct].width * bpp + j];
        unsigned char c = a;
        a = b;
        b = c;
      }
 }

 void load_dds(FILE* f, Text& t, CamoType ct)
 {
  DWORD dwmagic;
  DDS_HEADER ddsh;

  fread(&dwmagic, sizeof(dwmagic), 1, f);
  fread(&ddsh, sizeof(ddsh), 1, f);
  t.images[ct].alpha = ddsh.ddspf.dwFlags & 1 ? true : false;
  t.images[ct].width = ddsh.dwWidth;
  t.images[ct].height = ddsh.dwHeight;
  unsigned size = ddsh.ddspf.dwRGBBitCount >> 3;
  if (size != (t.images[ct].alpha ? 4 : 3))
   error("Invalid DDS");
  size *= t.images[ct].width * t.images[ct].height;
  t.images[ct].data.resize(size);
  fread(&t.images[ct].data[0], size, 1, f);
#if 1
  unsigned bpp = (t.images[ct].alpha ? 4 : 3);
  for (unsigned i = 0; i < t.images[ct].height / 2; i++)
   for (unsigned j = 0; j < t.images[ct].width * bpp; j++)
    {
      unsigned char& a = t.images[ct].data[i * t.images[ct].width * bpp + j];
      unsigned char& b = t.images[ct].data[(t.images[ct].height - i - 1) * t.images[ct].width * bpp + j];
      unsigned char c = a;
      a = b;
      b = c;
    }
#endif
 }

 void load_ignore(void)
 {
  eet.ExportAnimationTextures(ign);
  for (Ignore::const_iterator itor(ignore.begin()); itor != ignore.end(); ++itor)
   ign.insert(eet.Append(itor->c_str()));
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
    if (!t.images[CT_DEFAULT].data.empty())
     continue;
    if (!try_load(t, name, CT_DEFAULT))
     error("Failed to find texture %s", name);
    try_load(t, name, CT_DESERT);
    try_load(t, name, CT_WINTER);
   }
  bpp = 3;
  has_desert = false;
  has_winter = false;
  for (Texts::iterator itor(texts.begin()); itor != texts.end();)
   {
#define CH1(X, Y) (itor->second.images[X].Y != itor->second.images[CT_DEFAULT].Y)
#define CH(X) (CH1(X, alpha) || CH1(X, width) || CH1(X, height))
    if (!itor->second.images[CT_DESERT].data.empty())
     {
      has_desert = true;
      if (CH(CT_DESERT))
       error("Different default and desert image parameters for %s", eet.GetTexture(itor->first));
     }
    else
     itor->second.images[CT_DESERT] = itor->second.images[CT_DEFAULT];
    if (!itor->second.images[CT_WINTER].data.empty())
     {
      has_winter = true;
      if (CH(CT_WINTER))
       error("Different default and winter image parameters for %s", eet.GetTexture(itor->first));
     }
    else
     itor->second.images[CT_WINTER] = itor->second.images[CT_DEFAULT];
#undef CH
#undef CH1
    if (itor->second.images[CT_DEFAULT].alpha)
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
#if 0
    t.iu = min(t.iu, 0);
    t.au = max(t.au, PREC);
    t.iv = min(t.iv, 0);
    t.av = max(t.av, PREC);
#endif
    t.ru = (t.images[CT_DEFAULT].width * (t.au - t.iu) + PREC - 1) / PREC;
    t.rv = (t.images[CT_DEFAULT].height * (t.av - t.iv) + PREC - 1) / PREC;
    printf("% 5i % 5i % 5i % 5i % 7.3f % 7.3f % 7.3f % 7.3f %s\n", t.images[CT_DEFAULT].width, t.images[CT_DEFAULT].height, t.ru, t.rv, t.ui, t.ua, t.vi, t.va, eet.GetTexture(itor->first));
    stexts.insert(STexts::value_type(t.ru < t.rv ? std::make_pair(t.rv, t.ru) : std::make_pair(t.ru, t.rv), &t));
   }
 }
 void make_decisions(void)
 {
  for (unsigned w = 1u << log_2(stexts.begin()->first.first), i = 0; i < 5; w <<= 1, i++)
   {
    Decision d;
    make_decision(w, d);
    if (!bd.get() || std::make_pair(d.size.u * d.size.v, d.size.u + d.size.v) < std::make_pair(bd->size.u * bd->size.v, bd->size.u + bd->size.v))
     bd.reset(new Decision(d));
    if (w >= (1 << 13))
     break;
   }
   export_decision(*bd, CT_DEFAULT);
   if (has_desert)
    export_decision(*bd, CT_DESERT);
   if (has_winter)
    export_decision(*bd, CT_WINTER);
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
  d.size.v = 1 << log_2(d.size.v - 1);
 }
 void export_decision(const Decision& d, CamoType ct)
 {
  std::vector<unsigned char> data;
  data.resize(d.size.u * d.size.v * bpp);
#if 0
  for (unsigned i = 0; i < data.size(); i += bpp)
   data[i] = 255;
#endif
  for (Placement::const_iterator p(d.placement.begin()); p != d.placement.end(); ++p)
   if (p->first->ru < p->first->rv)
    copyt(&data[0], d.size.u, *p->first, ct, p->second);
   else
    copy(&data[0], d.size.u, *p->first, ct, p->second);

  char filename[1024];
  sprintf(filename, "%s\\%s%s.TGA", scene, scene, SUF[ct]);
  FILE* file = safe_fopen(filename, "wb");
  fwrite("\0\0\002\0\0\0\0\0\0\0\0\0", 12, 1, file);
  fwrite(&d.size.u, 2, 1, file);
  fwrite(&d.size.v, 2, 1, file);
  fwrite(bpp == 3 ? "\030\040" : "\040\040", 2, 1, file);
  fwrite(&data[0], data.size(), 1, file);
  fclose(file);
 }
 void copy(unsigned char* data, unsigned um, const Text& t, CamoType ct, const Position& p)
 {
  unsigned tbpp = t.images[ct].alpha ? 4 : 3;
  unsigned char pixel[4];
  pixel[3] = 255;
  int itu = t.iu * t.images[ct].width, itv = t.iv * t.images[ct].height;
  for (; itu < 0; itu += t.images[ct].width * PREC);
  for (; itv < 0; itv += t.images[ct].height * PREC);
  itv /= PREC;
  unsigned tu = itu / PREC;
  for (unsigned u = 0; u < t.ru; u++)
   {
    unsigned tv = itv;
    for (unsigned v = 0; v < t.rv; v++)
     {
      memcpy(pixel, &t.images[ct].data[((tv * t.images[ct].width) + tu) * tbpp], tbpp);
      memcpy(data + ((p.v + v) * um + p.u + u) * bpp, pixel, bpp);
      if (++tv == t.images[ct].height)
       tv = 0;
     }
    if (++tu == t.images[ct].width)
     tu = 0;
   }
 }
 void copyt(unsigned char* data, unsigned um, const Text& t, CamoType ct, const Position& p)
 {
  unsigned tbpp = t.images[ct].alpha ? 4 : 3;
  unsigned char pixel[4];
  pixel[3] = 255;
  int itu = t.iu * t.images[ct].width, itv = t.av * t.images[ct].height;
  for (; itu < 0; itu += t.images[ct].width * PREC);
  itu /= PREC;
  for (; itv >= 0; itv -= t.images[ct].height * PREC);
  itv += t.images[ct].height * PREC;
  unsigned tv = itv / PREC;
  for (unsigned u = 0; u < t.rv; u++)
   {
    unsigned tu = itu;
    for (unsigned v = 0; v < t.ru; v++)
     {
      memcpy(pixel, &t.images[ct].data[((tv * t.images[ct].width) + tu) * tbpp], tbpp);
      memcpy(data + ((p.v + v) * um + p.u + u) * bpp, pixel, bpp);
      if (++tu == t.images[ct].width)
       tu = 0;
     }
    if (!tv)
     tv = t.images[ct].height;
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
              int utmp = (((int)(p.u * PREC)) - t.iu) * (t.images[CT_DEFAULT].width - 1);
              int vtmp = (((int)(p.v * PREC)) - t.iv) * (t.images[CT_DEFAULT].height - 1);
              if (utmp < 0 || utmp >= t.ru * PREC)
               error("utmp %s %f %i %i", eet.GetTexture(s.texture_index), p.u, utmp, t.ru * PREC);
              if (vtmp < 0 || vtmp >= t.rv * PREC)
               error("vtmp %s %f %i %i", eet.GetTexture(s.texture_index), p.v, vtmp, t.rv * PREC);
              p.v = (utmp + pos->second.v * PREC) / (float)(bd->size.v * PREC);
              p.u = ((t.rv * PREC - 1 - vtmp) + pos->second.u * PREC) / (float)(bd->size.u * PREC);
             }
            else
             {
              int utmp = (((int)(p.u * PREC)) - t.iu) * (t.images[CT_DEFAULT].width - 1);
              int vtmp = (((int)(p.v * PREC)) - t.iv) * (t.images[CT_DEFAULT].height - 1);
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

 if (argc != 3)
  {
   puts("Usage: ee_skin.exe config scene.ees\nFor example, ee_skin.exe CONFIG.TXT \"D:\\GAMES\\EE\\COHOKUM\\3DDATA\\OBJECTS\\AH-64D Apache Longbow\\AH64D_APACHE_LONGBOW.EES\"");
   return -1;
  }

 Config config(argv[1], argv[2]);

 const char* scene = config.scene.c_str();
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
 eet.LoadCustomAnimations(config.animations.c_str());
 Objects objects(config.ee_objects.c_str(), 500);
 objects.LoadCustomObjects(config.common_objects.c_str(), eet);
 Cameras cameras;
 Skin skin(config.scene_objects.c_str(), objects, eet, scene, config.ignore, config.textures);
 sprintf(path, "%s\\%s.EES", config.scene_objects.c_str(), config.scene.c_str());
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
