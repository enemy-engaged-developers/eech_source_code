#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class TexturesExporter
{
 private:

 struct TEXTURE_FLAGS
 {
  union
  {
   struct
   {
    unsigned short int reserved_texture:1, vertically_inverted:1, contains_alpha:1, referenced:1, wrapped:1, mipmap_enabled:1, main_texture:1, camoflage_texture:1;
    unsigned char number_of_camoflage_textures, camoflage_index;
   };
   unsigned int flags;
  };
 };

 enum TEXTURE_MAP_TYPES
 {
  TEXTURE_TYPE_INVALID,
  TEXTURE_TYPE_NOALPHA,
  TEXTURE_TYPE_SINGLEALPHA,
  TEXTURE_TYPE_MULTIPLEALPHA,
  TEXTURE_TYPE_SCREEN,
  TEXTURE_TYPE_NOALPHA_NOPALETTE,
 };

 int width, height, type;
 unsigned char* texture_image_data;
 char filename[260];

 void save_tga(void)
 {
  int bpp = type == TEXTURE_TYPE_SINGLEALPHA || type == TEXTURE_TYPE_MULTIPLEALPHA ? 4 : 3;
  {
   unsigned char* cur = texture_image_data;
   for (int i = 0; i < width * height; i++)
    {
     unsigned char tmp = cur[0];
     cur[0] = cur[2];
     cur[2] = tmp;
     if (bpp == 4)
      {
       if (type == TEXTURE_TYPE_SINGLEALPHA)
        cur[3] = cur[3] ? 255 : 0;
       else
        cur[3] = 255 - cur[3];
      }
     cur += bpp;
    }
  }
  FILE* file = safe_fopen(filename, "wb");
  fwrite("\0\0\002\0\0\0\0\0\0\0\0\0", 12, 1, file);
  fwrite(&width, 2, 1, file);
  fwrite(&height, 2, 1, file);
  fwrite(bpp == 3 ? "\030\040" : "\040\040", 2, 1, file);
  fwrite(texture_image_data, width * height, bpp, file);
  fclose(file);
 }

 void print_flags(const TEXTURE_FLAGS& flags)
 {
  if (!flags.flags)
   {
    printf("\n");
    return;
   }

  printf(" FLAGS%s%s%s%s %i %i\n",
         flags.reserved_texture ? " reserved_texture" : "",
         flags.contains_alpha ? " contains_alpha" : "",
         flags.main_texture ? " main_texture" : "",
         flags.camoflage_texture ? " camoflage_texture" : "",
         (int)flags.number_of_camoflage_textures,
         (int)flags.camoflage_index);
 }

 public:

 TexturesExporter(void)
 {
  texture_image_data = new unsigned char [1024 * 1024];
 }

 ~TexturesExporter(void)
 {
  delete [] texture_image_data;
 }
 void export_textures(EET& eet)
 {
  int number_of_textures;
  FILE *fp;

  fp = safe_fopen("textures.bin", "rb");

  printf("Exporting textures\n");
  {
   int tmp;
   fread(&tmp, sizeof(int), 1, fp);
   fseek(fp, 1024 * tmp, SEEK_CUR);
  }

  fread(&number_of_textures, sizeof(int), 1, fp);
  for (int count = 0; count < number_of_textures; count++)
   {
    int length, number_of_mipmaps;
    TEXTURE_FLAGS flags;
    char name[1024];

    fread(&flags, sizeof(unsigned int), 1, fp);
    fread(&length, sizeof(int), 1, fp);
    memset(name, 0, sizeof(name));
    fread(name, length, 1, fp);
    strupr(name);
    printf("%i %s", count, name);

    if (flags.camoflage_texture)
     strcat(name, "-D");
    eet.Append(name);

    if (flags.reserved_texture)
     {
      print_flags(flags);
      continue;
     }

    fread(&type, sizeof(int), 1, fp);
    fread(&number_of_mipmaps, sizeof(int), 1, fp);
    fread(&width, sizeof(int), 1, fp);
    fread(&height, sizeof(int), 1, fp);

    printf(" ML:%i%s %ix%i", number_of_mipmaps, type == TEXTURE_TYPE_NOALPHA || type == TEXTURE_TYPE_NOALPHA_NOPALETTE ? "" : " ALPHA", width, height);
    print_flags(flags);

    for (int temp = 0; temp <= number_of_mipmaps; temp++)
     {
      switch (type)
       {
        case TEXTURE_TYPE_NOALPHA:
        case TEXTURE_TYPE_NOALPHA_NOPALETTE:
         fread(texture_image_data, (width * height * 3), 1, fp);
         break;

        case TEXTURE_TYPE_SINGLEALPHA:
         fread(texture_image_data, (width * height * 4), 1, fp);
         break;

        case TEXTURE_TYPE_MULTIPLEALPHA:
         fread(texture_image_data, (width * height * 4), 1, fp);
         break;
       }

      if (temp)
       sprintf(filename, "\\TEXTURES\\%s@%i.TGA", name, temp);
      else
       sprintf(filename, "\\TEXTURES\\%s.TGA", name);
      save_tga();

      width >>= 1;
      height >>= 1;
     }
   }
  fclose(fp);
  printf("\n");
 }
};
