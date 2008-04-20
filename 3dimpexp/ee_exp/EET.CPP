// Slashes are correct!
#define TEXTURES_ROOT ":TEXTURES/"

class EET
{
 private:

 struct Texture
 {
  unsigned long index;
  char name[64];
 };
 Array<Texture> textures;
 unsigned long index;
 char textures_drive;
 const char* extention;

 public:

 EET(char drive = 'D', const char* ext = "tga");
 void Clear(void);
 unsigned long GetIndex(LWO_File& lwofile, unsigned textindex);
 unsigned Append(const char* name);
};

EET::EET(char drive, const char* ext)
 : index(0), textures_drive(drive), extention(ext)
{
 FILE* file;

 file = fopen("TEXTURES.TXT", "r");
 if (!file)
  return;
 Texture texture;
 texture.index = ~0u;
 while (fgets(texture.name, sizeof(texture.name), file) != NULL)
  {
   texture.name[strlen(texture.name) - 1] = '\0';
   if (!*texture.name)
    break;
   textures.Append(texture);
  }
 fclose(file);
}

void EET::Clear(void)
{
 for (unsigned i = 0; i < !textures; i++)
  textures[i].index = ~0u;
 index = 0;
}

unsigned long EET::GetIndex(LWO_File& lwofile, unsigned textindex)
{
 LWO_Chunk* chunk;
 LWO_SubChunk* subchunk;
 char buf[1024];

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
     subchunk = new LWO_SubChunk("FLAG", 2, "\0\x80");
     chunk->AddSubChunk(subchunk);
     textures[textindex].index = index++;
    }

   return textures[textindex].index;
  }
 return 0;
}

unsigned EET::Append(const char* name)
{
 Texture texture;
 texture.index = ~0u;
 strcpy(texture.name, name);
 textures.Append(texture);
 return !textures - 1;
}
