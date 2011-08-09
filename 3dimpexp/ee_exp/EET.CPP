#ifndef EET_NO_EXPORT
// Slashes are correct!
#define TEXTURES_ROOT ":TEXTURES/"
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
 char textures_drive;
 const char* extention;
#endif

 public:

#ifndef EET_NO_EXPORT
 EET(char drive = 'D', const char* ext = "tga");
#endif
 void LoadAnimations(FILE* file);
 unsigned Append(const char* name);
#ifndef EET_NO_EXPORT
 void Clear(void);
 bool IsCamo(unsigned textindex, bool animation);
 unsigned long GetIndex(LWO_File& lwofile, unsigned textindex, bool animation);
 const char* GetAnimation(unsigned textindex) const;
 unsigned GetAnimation(const char* name) const;
 void ExportAnimations(void) const;
#else
 const char* GetTexture(unsigned index, bool animation, float frame) const;
#endif
private:
 void LoadAnimations(FILE* file, Array<Animation>& animations);
 void ExportAnimations(const Array<Animation>& animations, char* postfix) const;
};

#ifndef EET_NO_EXPORT
EET::EET(char drive, const char* ext)
 : index(0), textures_drive(drive), extention(ext)
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
         sprintf(buf, "%c%s%s.%s", textures_drive, TEXTURES_ROOT, textures[animation.animation[i]].name, extention);
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
       sprintf(buf, "%c%s%s.%s", textures_drive, TEXTURES_ROOT, textures[textindex].name, extention);
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
#ifndef EET_NO_EXPORT
 texture.camo = false;
 unsigned len = strlen(texture.name);
 if (len > 2 && !strcmp(texture.name + len - 2, "-D"))
  {
   texture.name[len - 2] = '\0';
   texture.camo = true;
  }
 texture.index = ~0u;
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
const char* EET::GetTexture(unsigned index, bool animation, float frame) const
{
 return animation ? index < !animations ? textures[animations[index].animation[(unsigned)(frame * !animations[index].animation)]].name : NULL : index < !textures ? textures[index].name : NULL;
}
#endif
