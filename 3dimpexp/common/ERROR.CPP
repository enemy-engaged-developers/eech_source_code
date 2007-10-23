#include <stdarg.h>

void error(const char* msg, ...)
{
 va_list va;

 va_start(va, msg);
 vprintf(msg, va);
 va_end(va);
 putchar('\n');

 exit(1);
}

FILE* safe_fopen(const char* filename, const char* mode)
{
 FILE* file = fopen(filename, mode);
 if (!file)
  error("Failed to open '%s'", filename);
 return file;
}
