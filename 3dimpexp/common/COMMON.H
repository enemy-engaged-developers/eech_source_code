#ifndef COMMON_H
#define COMMON_H

#include <math.h>

#ifdef unix
#define mkdir(x) mkdir((x), 0666)
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

#ifndef __WATCOMC__
#define truncate trunc
#else
#define fabsf fabs
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

#endif
