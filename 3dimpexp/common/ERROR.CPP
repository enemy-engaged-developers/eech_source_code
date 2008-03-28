#include <stdarg.h>

void warning(const char* msg, ...)
{
 va_list va;

 printf("Warning: ");
 va_start(va, msg);
 vprintf(msg, va);
 va_end(va);
 putchar('\n');
}

void error(const char* msg, ...)
{
 va_list va;

 printf("Error: ");
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
