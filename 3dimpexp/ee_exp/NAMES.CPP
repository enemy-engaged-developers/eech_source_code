class Names
{
 private:

 struct Name
 {
  char name[64];
 };
 Array<Name> names;

 public:
 unsigned operator !(void) const
 {
  return !names;
 }
 const char* operator [](unsigned index) const
 {
  if (index >= !names)
   return "NO NAME";
  return names[index].name;
 }
 unsigned operator += (const char* name)
 {
  for (unsigned i = 0; i < !names; i++)
   if (!strcmp(names[i].name, name))
    return i;

  return *this <<= name;
 }
 unsigned operator <<= (const char* name)
 {
  Name new_name;
  strcpy(new_name.name, name);
  names.Append(new_name);
  return !names - 1;
 }
};

struct AllNames
{
 Names Objects;
 Names SubObjects;
 Names Cameras;

 AllNames(void)
 {
  Objects <<= "OBJECT_INVALID_INDEX";
  SubObjects <<= "INVALID_SUB_OBJECT_INDEX";
  Cameras <<= "INVALID_CAMERA_INDEX";

  FILE* file = fopen("bininfo.bin", "rb");
  if (!file)
   return;

  int total, length;
  char name[1024];

  fread(&total, sizeof(int), 1, file);

  if (total)
   {
    fseek(file, sizeof(int), SEEK_CUR);
    for (int count = 1; count < total; count++)
     {
      fread (&length, sizeof(int), 1, file);
      fread (name, length, 1, file);
      Objects <<= name;
      fseek(file, sizeof(float), SEEK_CUR);
     }
   }

  fread (&total, sizeof(int), 1, file);
  if (total)
   {
    fseek(file, sizeof(int), SEEK_CUR);
    for (int count = 1; count < total; count++)
     {
      fread (&length, sizeof(int), 1, file);
      fread (name, length, 1, file);
      SubObjects <<= name;
     }
   }

  fread (&total, sizeof(int), 1, file);
  if (total)
   {
    fseek(file, sizeof(int), SEEK_CUR);
    for (int count = 1; count < total; count++)
     {
      fread (&length, sizeof(int), 1, file);
      fread (name, length, 1, file);
      Cameras <<= name;
     }
   }
 }
};
