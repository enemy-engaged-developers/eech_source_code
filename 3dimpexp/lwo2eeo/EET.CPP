class EET
{
 private:

 Array<FString> textures;

 public:

 EET(void)
 {
  FILE* file;
  char buf[1024];

  file = fopen("TEXTURES.TXT", "r");
  if (!file)
   return;
  while (fgets(buf, sizeof(buf), file))
   {
    buf[strlen(buf) - 1] = '\0';
    if (!*buf)
     break;
    textures.Append(buf);
   }
  fclose(file);
 }
 unsigned GetIndex(const char* filename)
 {
  char* ptr;
  char buf[1024];
  unsigned i;

  ptr = strrchr(filename, '\\');
  if (!ptr)
   ptr = strchr(filename, ':');
  if (ptr)
   strcpy(buf, ptr + 1);
  else
   strcpy(buf, filename);
  ptr = strchr(buf, '.');
  if (ptr)
   *ptr = '\0';

  for (i = 0; i < !textures; i++)
   if (stricmp(textures[i], buf) == 0)
    return i;
  error("Unknown texture name '%s' '%s'", buf, filename);
  return ~0;
 }
};
