#ifndef COMMON_H
#define COMMON_H

#include <ctype.h>
#include <math.h>

#ifdef unix
#define mkdir(x) mkdir((x), 0777)
#else
#include <direct.h>
#endif

#include "array.h"

#ifndef M_PI
#define M_PI (3.14159265359)
#endif

double deg(double rad)
{
 return rad * 180.0 / M_PI;
}

double rad(double deg)
{
 return deg * M_PI / 180.0;
}

#ifdef __WATCOMC__
#define fabsf fabs
#endif
#ifdef __GNUC__
void strupr(char* ptr)
{
 for (; (*ptr = toupper(*ptr)); ptr++);
}
#endif

#ifdef unix
#define stricmp strcasecmp
#endif

template <class T>
T min(T a, T b)
{
 return a < b ? a : b;
}
template <class T>
T max(T a, T b)
{
 return a > b ? a : b;
}

bool get_nul_string(char* buf, int buf_len, FILE* file)
{
 if (buf_len <= 0)
  return false;
 buf_len--;
 while (int ch = fgetc(file))
  {
   if (ch == EOF)
    return false;

   *buf++ = toupper(ch);
   buf_len--;
   if (!buf_len)
    break;
  }
 *buf = '\0';
 return true;
}

#endif
