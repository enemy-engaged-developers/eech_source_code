#ifndef EET_NO_EXPORT
#include <io.h>

class TexturesFinder
{
 public:

 TexturesFinder(char drive, const char* extention = "TGA")
  : drive(drive), extention(extention)
 {
 }

 virtual ~TexturesFinder()
 {
 }

 virtual void find(const char* texture, char* file)
 {
  if (isalpha(drive))
   sprintf(file, "%c:TEXTURES/%s.%s", drive, texture, extention);
  else
   sprintf(file, "%s.%s", texture, extention);
 }

 private:

 char drive;
 const char* extention;
};

class FileTexturesFinder : public TexturesFinder
{
 public:

 FileTexturesFinder(char drive, char** dirs, bool recursive = true)
  : TexturesFinder(drive), dirs(dirs), recursive(recursive)
 {
 }

 virtual void find(const char* texture, char* file)
 {
  for (char** cur = dirs; *cur; cur++)
   if (search_dir(texture, *cur, file))
    {
     file += 3;
     do
      file[-1] = *file == '\\' ? '/' : *file;
     while (*file++);
     return;
    }

  TexturesFinder::find(texture, file);
 }

 private:

 bool search_dir(const char* texture, const char* dir, char* file)
 {
  char buf[260];
  int rc;
  long handle;
  struct _finddata_t fd;

  //warning("Looking for '%s' in '%s'", texture, dir);
  sprintf(buf, "%s\\%s.*", dir, texture);
  for (rc = handle = _findfirst(buf, &fd); rc != -1; rc = _findnext(handle, &fd))
   if (!(fd.attrib & _A_SUBDIR))
    {
     const char* ext = fd.name + strlen(fd.name) - 4;
     if (!stricmp(ext, ".TGA") || !stricmp(ext, ".BMP"))
      {
       _findclose(handle);
       sprintf(file, "%s\\%s", dir, fd.name);
       return true;
      }
    }
  _findclose(handle);

  if (!recursive)
   return false;

  sprintf(buf, "%s\\*.*", dir);
  for (rc = handle = _findfirst(buf, &fd); rc != -1; rc = _findnext(handle, &fd))
   if ((fd.attrib & _A_SUBDIR) && fd.name[0] != '.')
    {
     sprintf(buf, "%s\\%s", dir, fd.name);
     if (search_dir(texture, buf, file))
      {
       _findclose(handle);
       return true;
      }
    }
  _findclose(handle);

  return false;
 }

 char** dirs;
 bool recursive;
};

#endif

class EET
{
 private:

 struct Texture
 {
  char name[64];
#ifndef EET_NO_EXPORT
  bool camo;
  unsigned long index;
#endif
 };
 struct Animation
 {
  char name[64];
  Array<unsigned> animation;
#ifndef EET_NO_EXPORT
  unsigned long index;
#endif
 };

 Array<Texture> textures;
 Array<Animation> animations;
 Array<Animation> displacement_animations;
#ifndef EET_NO_EXPORT
 unsigned long index;
 TexturesFinder& textures_finder;
#endif

 public:

#ifndef EET_NO_EXPORT
 EET(TexturesFinder& textures_finder);
#endif
 void LoadAnimations(FILE* file);
#ifdef LOAD_CUSTOM
 void LoadCustomAnimations(const char* dir);
 const char* GetTexture(unsigned index) const;
 void ExportAnimationTextures(std::set<unsigned>& s) const;
 unsigned AppendAnimation(const char* name, unsigned number_of_textures, const char** textures);
#endif
 unsigned Append(const char* name);
#ifndef EET_NO_EXPORT
 void Clear(void);
 bool IsCamo(unsigned textindex, bool animation);
 unsigned long GetIndex(LWO_File& lwofile, unsigned textindex, bool animation);
 const char* GetAnimation(unsigned textindex) const;
 unsigned GetAnimation(const char* name) const;
 void ExportAnimations(void) const;
#else
 unsigned GetTextures() const;
 const char* GetTexture(unsigned index) const;
 unsigned GetAnimations() const;
 unsigned GetAnimationSize(unsigned index) const;
 unsigned GetAnimationTexture(unsigned index, unsigned frame) const;
#endif
private:
 void LoadAnimations(FILE* file, Array<Animation>& animations);
 void ExportAnimations(const Array<Animation>& animations, char* postfix) const;
};

#ifndef EET_NO_EXPORT
EET::EET(TexturesFinder& textures_finder)
 : index(0), textures_finder(textures_finder)
{
}
#endif

void EET::LoadAnimations(FILE* file, Array<Animation>& animations)
{
 int number_of_texture_animations;
 fread(&number_of_texture_animations, sizeof(int), 1, file);
 if (number_of_texture_animations)
  {
   animations[number_of_texture_animations - 1];
   int length;
   fread(&length, sizeof(int), 1, file);
   for (int count = 0; count < number_of_texture_animations; count++)
    {
     Animation animation;
#ifndef EET_NO_EXPORT
     animation.index = ~0u;
#endif
     fread(&length, sizeof(int), 1, file);
     fread(animation.name, length, 1, file);
     fread(&length, sizeof(int), 1, file);
#ifndef EET_NO_EXPORT
     animations[count].index = ~0u;
#endif
     for (int temp = 0; temp < length; temp++)
      {
       unsigned texture;
       fread(&texture, sizeof(int), 1, file);
       animation.animation.Append(texture);
      }
     animations[count] = animation;
    }
  }
}

void EET::LoadAnimations(FILE* file)
{
 LoadAnimations(file, animations);
 LoadAnimations(file, displacement_animations);
}

#ifdef LOAD_CUSTOM
void EET::LoadCustomAnimations(const char* dir)
{
  char buf[260], file[260];
  int rc;
  long handle;
  struct _finddata_t fd;

  sprintf(buf, "%s\\*.TXT", dir);
  for (rc = handle = _findfirst(buf, &fd); rc != -1; rc = _findnext(handle, &fd))
   if (!(fd.attrib & _A_SUBDIR))
    {
     sprintf(file, "%s\\%s", dir, fd.name);
     FILE* f = safe_fopen(file, "r");
     *strrchr(fd.name, '.') = '\0';
     strupr(fd.name);
     Animation* animation = 0;
     for (unsigned i = 0; i < !animations; i++)
      if (!strcmp(fd.name, animations[i].name))
       {
        animation = &animations[i];
        break;
       }
     if (!animation)
      animation = &animations.Append();
     {
      Animation anim;
      strcpy(anim.name, fd.name);
      *animation = anim;
     }
     while (fgets(buf, sizeof(buf), f))
      {
       buf[strlen(buf) - 1] = '\0';
       animation->animation.Append(Append(buf));
      }
    }
  _findclose(handle);
}
const char* EET::GetTexture(unsigned index) const
{
 return index < !textures ? textures[index].name : NULL;
}
void EET::ExportAnimationTextures(std::set<unsigned>& s) const
{
 for (unsigned i = 0; i < !animations; i++)
  for (unsigned j = 0; j < !animations[i].animation; j++)
   s.insert(animations[i].animation[j]);
}
unsigned EET::AppendAnimation(const char* name, unsigned number_of_textures, const char** textures)
{
 Animation* animation = &animations.Append();
 strcpy(animation->name, name);
 for (; number_of_textures--; textures++)
  animation->animation.Append(Append(*textures));
 return !animations - 1;
}
#endif

#ifndef EET_NO_EXPORT
void EET::Clear(void)
{
 for (unsigned i = 0; i < !textures; i++)
  textures[i].index = ~0u;
 for (unsigned i = 0; i < !animations; i++)
  animations[i].index = ~0u;
 index = 0;
}

bool EET::IsCamo(unsigned textindex, bool animation)
{
  return !animation && textures[textindex].camo;
}

unsigned long EET::GetIndex(LWO_File& lwofile, unsigned textindex, bool animation)
{
 LWO_Chunk* chunk;
 LWO_SubChunk* subchunk;
 char buf[1024];

 if (animation)
  {
   if (textindex < !animations)
    {
     Animation& animation = animations[textindex];
     if (animation.index == ~0u)
      {
       chunk = new LWO_Chunk("CLIP", 0, NULL);
       lwofile.AddSubChunk(chunk);
       chunk->AddData(4, &index);
       for (int i = 0; i < 1 /*!animation.animation*/; i++)
        {
         subchunk = new LWO_SubChunk("STIL", 0, NULL);
         chunk->AddSubChunk(subchunk);
         textures_finder.find(textures[animation.animation[i]].name, buf);
         subchunk->AddBasicData(strlen(buf) + 1, buf);
        }
       animation.index = index++;
      }

     return animation.index;
    }
  }
 else
  {
   if (textindex < !textures)
    {
     if (textures[textindex].index == ~0u)
      {
       chunk = new LWO_Chunk("CLIP", 0, NULL);
       lwofile.AddSubChunk(chunk);
       chunk->AddData(4, &index);
       subchunk = new LWO_SubChunk("STIL", 0, NULL);
       chunk->AddSubChunk(subchunk);
       textures_finder.find(textures[textindex].name, buf);
       subchunk->AddBasicData(strlen(buf) + 1, buf);
       textures[textindex].index = index++;
      }

     return textures[textindex].index;
    }
  }
 return 0;
}
#endif

#ifndef EET_NO_EXPORT
const char* EET::GetAnimation(unsigned textindex) const
{
 return textindex < !animations ? animations[textindex].name : 0;
}

unsigned EET::GetAnimation(const char* name) const
{
 for (unsigned i = 0; i < !animations; i++)
  if (!strcasecmp(animations[i].name, name))
   return i;
 return -1;
}
#endif

unsigned EET::Append(const char* name)
{
 Texture texture;
 strcpy(texture.name, name);
 strupr(texture.name);
#ifndef EET_NO_EXPORT
 texture.camo = false;
 unsigned len = strlen(texture.name);
 if (len > 2 && !strcmp(texture.name + len - 2, "-D"))
  {
   texture.name[len - 2] = '\0';
   texture.camo = true;
  }
 texture.index = ~0u;
 for (unsigned i = 0; i < !textures; i++)
  if (!strcmp(textures[i].name, texture.name) && textures[i].camo == texture.camo)
   return i;
#endif
 textures.Append(texture);
 return !textures - 1;
}

#ifndef EET_NO_EXPORT
void EET::ExportAnimations(const Array<Animation>& animations, char* postfix) const
{
 for (unsigned i = 0; i < !animations; i++)
  {
   const Animation& animation = animations[i];
   char filename[128];
   sprintf(filename, "_OBJECTS/%04X_%s%s.TXT", i, animation.name, postfix);
   FILE* file = safe_fopen(filename, "w");
   for (unsigned j = 0; j < !animation.animation; j++)
    fprintf(file, "%s\n", textures[animation.animation[j]].name);
   fclose(file);
  }
}
void EET::ExportAnimations(void) const
{
 ExportAnimations(animations, "");
 ExportAnimations(displacement_animations, "_DISPLACEMENT");
}
#else
unsigned EET::GetTextures() const
{
 return !textures;
}
const char* EET::GetTexture(unsigned index) const
{
 return index < !textures ? textures[index].name : NULL;
}
unsigned EET::GetAnimations() const
{
 return !animations;
}
unsigned EET::GetAnimationSize(unsigned index) const
{
 return index < !animations ? !animations[index].animation : 0;
}
unsigned EET::GetAnimationTexture(unsigned index, unsigned frame) const
{
 return index < !animations ? animations[index].animation[frame] : -1;
}
#endif
