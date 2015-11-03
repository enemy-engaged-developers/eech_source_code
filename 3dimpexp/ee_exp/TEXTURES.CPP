#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef NATIVE_TYPES
enum TEXTURE_MAP_TYPES
{
 TEXTURE_TYPE_INVALID,
 TEXTURE_TYPE_NOALPHA,
 TEXTURE_TYPE_SINGLEALPHA,
 TEXTURE_TYPE_MULTIPLEALPHA,
 TEXTURE_TYPE_SCREEN,
 TEXTURE_TYPE_NOALPHA_NOPALETTE,
};
#endif

class BaseTexturesExporter
{
 public:

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

 protected:

 TEXTURE_FLAGS flags;
 int width, height, type, bpp, number_of_mipmaps;
 unsigned char* texture_image_data;

 void convert(void)
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

 virtual void use_texture(int count, const char* name, int mip) = 0;

 void print_flags(void)
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

 BaseTexturesExporter(void)
 {
  texture_image_data = new unsigned char [1024 * 1024 * 4];
 }

 virtual ~BaseTexturesExporter(void)
 {
  delete [] texture_image_data;
 }
 void export_textures(EET& eet, bool log = true)
 {
  int number_of_textures;

  FILE *fp = safe_fopen_rb("textures.bin");

  if (log)
   printf("Exporting textures\n");
  {
   int tmp;
   fread(&tmp, sizeof(int), 1, fp);
   fseek(fp, 1024 * tmp, SEEK_CUR);
  }

  fread(&number_of_textures, sizeof(int), 1, fp);
  for (int count = 0; count < number_of_textures; count++)
   {
    int length;
    char name[1024];

    fread(&flags, sizeof(unsigned int), 1, fp);
    fread(&length, sizeof(int), 1, fp);
    memset(name, 0, sizeof(name));
    fread(name, length, 1, fp);
    strupr(name);
    if (log)
     printf("%i %s", count, name);

    if (flags.camoflage_texture)
     strcat(name, "-D");
    eet.Append(name);

    if (flags.reserved_texture)
     {
      width = height = number_of_mipmaps = 1;
      bpp = 3;
      memset(texture_image_data, 0xFF, 3);
      use_texture(count, name, -1);
      if (log)
       print_flags();
      continue;
     }

    fread(&type, sizeof(int), 1, fp);
    bpp = type == TEXTURE_TYPE_SINGLEALPHA || type == TEXTURE_TYPE_MULTIPLEALPHA ? 4 : 3;
    fread(&number_of_mipmaps, sizeof(int), 1, fp);
    fread(&width, sizeof(int), 1, fp);
    fread(&height, sizeof(int), 1, fp);

    if (log)
     {
      printf(" ML:%i%s %ix%i", number_of_mipmaps, type == TEXTURE_TYPE_NOALPHA || type == TEXTURE_TYPE_NOALPHA_NOPALETTE ? "" : " ALPHA", width, height);
      print_flags();
     }

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

      convert();
      use_texture(count, name, temp);

      width >>= 1;
      height >>= 1;
     }
   }
  fclose(fp);
  if (log)
   printf("\n");
 }
};

class TexturesExporter : public BaseTexturesExporter
{
 virtual void use_texture(int, const char* name, int mip)
 {
  char filename[260];
  if (mip > 0)
   sprintf(filename, "\\TEXTURES\\%s@%i.TGA", name, mip);
  else
   sprintf(filename, "\\TEXTURES\\%s.TGA", name);
  FILE* file = safe_fopen(filename, "wb");
  fwrite("\0\0\002\0\0\0\0\0\0\0\0\0", 12, 1, file);
  fwrite(&width, 2, 1, file);
  fwrite(&height, 2, 1, file);
  fwrite(bpp == 3 ? "\030\040" : "\040\040", 2, 1, file);
  fwrite(texture_image_data, width * height, bpp, file);
  fclose(file);
 }
};

class TexturesExporter_ : public BaseTexturesExporter
{
 virtual void use_texture(int, const char*, int)
 {
 }
};
