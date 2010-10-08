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
 unsigned long GetIndex(LWO_File& lwofile, unsigned textindex, bool animation);
 const char* GetAnimation(unsigned textindex) const;
 void ExportAnimations(void) const;
#else
 const char* GetTexture(unsigned index, bool animation, float frame) const;
#endif
};

#ifndef EET_NO_EXPORT
EET::EET(char drive, const char* ext)
 : index(0), textures_drive(drive), extention(ext)
{
}
#endif

void EET::LoadAnimations(FILE* file)
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

#ifndef EET_NO_EXPORT
void EET::Clear(void)
{
 for (unsigned i = 0; i < !textures; i++)
  textures[i].index = ~0u;
 for (unsigned i = 0; i < !animations; i++)
  animations[i].index = ~0u;
 index = 0;
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
#endif

unsigned EET::Append(const char* name)
{
 Texture texture;
#ifndef EET_NO_EXPORT
 texture.index = ~0u;
#endif
 strcpy(texture.name, name);
 textures.Append(texture);
 return !textures - 1;
}

#ifndef EET_NO_EXPORT
void EET::ExportAnimations(void) const
{
 for (unsigned i = 0; i < !animations; i++)
  {
   const Animation& animation = animations[i];
   char filename[128];
   sprintf(filename, "_OBJECTS/%04X_%s.TXT", i, animation.name);
   FILE* file = safe_fopen(filename, "w");
   for (unsigned j = 0; j < !animation.animation; j++)
    fprintf(file, "%s\n", textures[animation.animation[j]].name);
   fclose(file);
  }
}
#else
const char* EET::GetTexture(unsigned index, bool animation, float frame) const
{
 return animation ? index < !animations ? textures[animations[index].animation[(unsigned)(frame * !animations[index].animation)]].name : NULL : index < !textures ? textures[index].name : NULL;
}
#endif
