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

#ifdef SAFE_FOPEN_RB
FILE* safe_fopen_rb(const char* filename)
{
 FILE* file = NULL;
 HKEY key;
 if (RegOpenKey(HKEY_LOCAL_MACHINE, "Software\\Razorworks\\Comanche Hokum", &key ) == ERROR_SUCCESS)
  {
   char path[1024];
   DWORD type;
   DWORD string_length;
   string_length = sizeof(path);
   type = REG_SZ;
   RegQueryValueEx(key, "Installation Path", NULL, &type, (LPBYTE)path, (LPDWORD)&string_length);
   strcat(path, "\\COHOKUM\\3DDATA\\");
   strcat(path, filename);
   file = fopen(path, "rb");
   RegCloseKey(key);
  }
 if (!file)
  file = safe_fopen(filename, "rb");
 return file;
}
#endif
