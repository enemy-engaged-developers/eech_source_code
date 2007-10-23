#ifndef LWO_H_INCLUDED
#define LWO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>


#define USE_EXCEPTIONS_


class FString
{
 private:

 unsigned size;
 char* str;

 public:

 FString(const char* st = 0)
  : size(0), str(0)
 {
  if (st)
   {
    size = strlen(st) + 1;
    str = new char[size];
    memcpy(str, st, size);
   }
 }
 FString(const FString& fs)
  : size(fs.size), str(0)
 {
  if (size)
   {
    str = new char[size];
    memcpy(str, fs.str, size);
   }
 }
 ~FString(void) { if (str) delete [] str; }

 const char * operator & (void) const { return str; }
 operator const char * (void) const { return str; }
 void operator = (const FString& fs)
 {
  if (str == &fs)
   return;
  if (str)
   delete [] str;
  size = fs.size;
  if (size > 0)
   {
    str = new char[size];
    memcpy(str, fs.str, size);
   }
  else
   str = NULL;
 }
 void operator += (const FString& fs)
 {
  if (fs.size == 0)
   return;
  if (str)
   {
    int newsize = size + fs.size - 1;
    char* newstr = new char[newsize];
    if (size > 1)
     memcpy(newstr, str, size - 1);
    memcpy(newstr + size - 1, fs.str, fs.size);
    size = newsize;
    delete [] str;
    str = newstr;
   }
  else
   {
    size = fs.size;
    str = new char[size];
    memcpy(str, fs.str, size);
   }
 }
};


#define TAG(tag0, tag1, tag2, tag3) ((((unsigned long)(tag0)) << 0) | (((unsigned long)(tag1)) << 8) | (((unsigned long)(tag2)) << 16) | (((unsigned long)(tag3)) << 24))
#define TAG_(tag) TAG((tag)[0], (tag)[1], (tag)[2], (tag)[3])



class LWO
{
 public:

 class Tag
 {
  private:

  char tag[5];

  public:

  void operator = (const char* str) { memset(tag, 0, sizeof(tag)); if (str) strncpy(tag, str, sizeof(tag) - 1); }
  char* operator & (void) { return tag; }
  const char* operator & (void) const { return tag; }
  operator int (void) const { return tag[0] != '\0'; }
  int operator == (const char* str) const { return strcmp(tag, str) == 0; }
  int operator != (const char* str) const { return strcmp(tag, str) != 0; }
 };

 struct Color
 {
  float red, green, blue;
 };

 struct Vector
 {
  float x, y, z;
 };

 struct ChunkInfo
 {
  unsigned long size;
  unsigned padding;
 };

 private:

 FILE* lwo;
 unsigned level;
 ChunkInfo levels[5];

 static void error(const char* format, ...);

 void Check(unsigned long size);
 void Count(unsigned long size);

 void Read_Basic(void* buf, unsigned size);
 void Read(void* buf, unsigned size);

 public:

 LWO(void);
 ~LWO(void);

 int Open(const char* filename, ChunkInfo* info = 0);
 void Close(void);

 unsigned long Chunk_Left(void);
 unsigned long SubChunk_Left(void);

 void Skip(unsigned long size);
 void Skip_Chunk(void);
 void Skip_SubChunk(void);

 Tag Read_Tag_Header(void);
 Tag Read_Chunk_Header(ChunkInfo* info = 0);
 Tag Read_SubChunk_Header(ChunkInfo* info = 0);
 void SubChunk_Lower(void);
 void SubChunk_Higher(void);

 Tag Read_Tag(void);
 float Read_Float(void);
 unsigned char Read_U1(void);
 unsigned short Read_U2(void);
 unsigned long Read_U4(void);
 signed char Read_S1(void);
 signed short Read_S2(void);
 signed long Read_S4(void);
 FString Read_String(void);
 FString Read_FileName(void);
 unsigned long Read_Index(void);
 Color Read_Color(void);
 Vector Read_Vector(void);
 void Read_Data(void* data, unsigned size);
};


void LWO::error(const char* format, ...)
{
 static char buf[1024];
 va_list va;

 va_start(va, format);
 vsprintf(buf, format, va);
 va_end(va);
 strcat(buf, "\n");
#ifdef USE_EXCEPTIONS
 throw buf;
#else
 fputs(buf, stderr);
 exit(1);
#endif
}

LWO::LWO(void)
 : lwo(0)
{
}

LWO::~LWO(void)
{
 Close();
}

int LWO::Open(const char* filename, ChunkInfo* info)
{
 Tag tag;

 lwo = fopen(filename, "rb");
 if (!lwo)
  {
   error("Failed to open file");
   return -1;
  }

 levels[0].size = 12;
 levels[0].padding = 0;
 level = 1;
 tag = Read_Chunk_Header(0);
 if (tag != "FORM" || levels[0].size < 4)
  error("Invalid LWO file");
 tag = Read_Tag();
 if (tag != "LWO2")
  error("Incorrect LWO file");
 if (info)
  *info = levels[0];
 level = 2;
 return 0;
}

void LWO::Close(void)
{
 if (lwo)
  {
   fclose(lwo);
   lwo = NULL;
  }
}

void LWO::Check(unsigned long size)
{
 unsigned lev;

 for (lev = 0; lev < level; lev++)
  if (levels[lev].size < size)
   error("Unexpected end of chunk/subchunk");
}

void LWO::Count(unsigned long size)
{
 unsigned lev;

 for (lev = 0; lev < level; lev++)
  levels[lev].size -= size;
}

void LWO::Read_Basic(void* buf, unsigned size)
{
 Check(size);
 if (fread(buf, 1, size, lwo) != size)
  error("Unexpected EOF while trying to read %lu bytes", size);
 Count(size);
}

void LWO::Read(void* buf, unsigned size)
{
 register char* b;
 register char* e;
 register char tmp;

 Read_Basic(buf, size);
 for (b = (char *)buf, e = b + size - 1; b < e; b++, e--)
  {
   tmp = *b;
   *b = *e;
   *e = tmp;
  }
}

unsigned long LWO::Chunk_Left(void)
{
 return levels[1].size - levels[1].padding;
}

unsigned long LWO::SubChunk_Left(void)
{
 if (level < 3)
  error("Unable to determine subchunk left");
 return levels[level - 1].size - levels[level - 1].padding;
}

void LWO::Skip(unsigned long size)
{
 Check(size);
 if (fseek(lwo, size, SEEK_CUR))
  error("Unexpected EOF while trying to skip %lu bytes", size);
 Count(size);
}

void LWO::Skip_Chunk(void)
{
 level = 2;
 Skip(Chunk_Left());
}

void LWO::Skip_SubChunk(void)
{
 if (level < 3)
  error("Unable to skip subchunk");
 Skip(SubChunk_Left());
}

LWO::Tag LWO::Read_Tag_Header(void)
{
 Tag tag;

 tag = NULL;
 if (level > 0 && levels[level - 1].size < 6)
  {
   if (levels[level - 1].size == levels[level - 1].padding)
    {
     Skip(levels[level - 1].size);
     return tag;
    }
   error("Unexpected EOF/EOC on half-tag");
  }
 if (fread(&tag, 1, 4, lwo) != 4)
  error("Unexpected EOF/EOC on tag");
 Count(4);
 return tag;
}

LWO::Tag LWO::Read_Chunk_Header(ChunkInfo* info)
{
 Tag tag;

 if (level > 2)
  level = 2;
 level--;
 tag = Read_Tag_Header();
 if (!tag)
  return tag;
 levels[level].size = Read_U4();
 levels[level].padding = (unsigned)(levels[level].size & 1);
 if (info)
  *info = levels[level];
 level++;
 return tag;
}

LWO::Tag LWO::Read_SubChunk_Header(ChunkInfo* info)
{
 Tag tag;

 if (level < 2)
  error("Level too high for subchunk");
 if (level == 2)
  level = 3;
 level--;
 tag = Read_Tag_Header();
 if (!tag)
  return tag;
 levels[level].size = Read_U2();
 levels[level].padding = (unsigned)(levels[level].size & 1);
 if (info)
  *info = levels[level];
 level++;
 return tag;
}

void LWO::SubChunk_Lower(void)
{
 if (level <= 2 || level == 5)
  error("Cannot go lower");
 level++;
}

void LWO::SubChunk_Higher(void)
{
 if (level == 2)
  error("Cannot go higher");
 level--;
}

LWO::Tag LWO::Read_Tag(void)
{
 Tag tag;

 tag = NULL;
 Read_Basic(&tag, 4);
 return tag;
}

float LWO::Read_Float(void)
{
 float flt;

 Read(&flt, 4);
 return flt;
}

unsigned char LWO::Read_U1(void)
{
 unsigned char u1 = 0;

 Read(&u1, 1);
 return u1;
}

unsigned short LWO::Read_U2(void)
{
 unsigned short u2 = 0;

 Read(&u2, 2);
 return u2;
}

unsigned long LWO::Read_U4(void)
{
 unsigned long u4 = 0;

 Read(&u4, 4);
 return u4;
}

signed char LWO::Read_S1(void)
{
 signed char s1 = 0;

 Read(&s1, 1);
 return s1;
}

signed short LWO::Read_S2(void)
{
 signed short s2 = 0;

 Read(&s2, 2);
 return s2;
}

signed long LWO::Read_S4(void)
{
 signed long s4 = 0;

 Read(&s4, 4);
 return s4;
}

FString LWO::Read_String(void)
{
 FString str;
 char st[2] = " ";

 str = NULL;
 do
  {
   Read_Basic(st, 1);
   str += st;
  }
 while (*st);
 if (!(strlen(str) & 1))
  Skip(1);
 return str;
}

FString LWO::Read_FileName(void)
{
 FString fname;
 FString str;
 const char* ptr;
 char tmp[2] = " ";

 str = Read_String();
 fname = NULL;
 ptr = &str;
 if (!*ptr)
  return fname;
 if (ptr[1] == ':')
  {
   *tmp = *ptr;
   ptr += 2;
   fname += tmp;
   fname += ":\\";
  }
 for (; *ptr; ptr++)
  if (*ptr == '/')
   fname += "\\";
  else
   {
    *tmp = *ptr;
    fname += tmp;
   }
 return fname;
}

unsigned long LWO::Read_Index(void)
{
 unsigned long index;
 unsigned short tmp;

 tmp = Read_U2();
 if (tmp >= 0xFF00)
  index = (((unsigned long)(tmp & 0xFF00)) << 16) | Read_U2();
 else
  index = tmp;
 return index;
}

LWO::Color LWO::Read_Color(void)
{
 Color color;

 color.red = Read_Float();
 color.green = Read_Float();
 color.blue = Read_Float();
 return color;
}

LWO::Vector LWO::Read_Vector(void)
{
 Vector vector;

 vector.x = Read_Float();
 vector.y = Read_Float();
 vector.z = Read_Float();
 return vector;
}

void LWO::Read_Data(void* data, unsigned size)
{
 Read_Basic(data, size);
}

#endif
