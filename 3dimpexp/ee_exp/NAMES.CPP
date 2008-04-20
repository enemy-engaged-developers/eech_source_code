class Names
{
 private:

 struct Name
 {
  char name[64];
 };
 Array<Name> names;

 public:
 Names(const char* filename = "")
 {
  Name name;
  FILE* file = fopen(filename, "r");
  if (!file)
   {
    Name name = { "INVALID NAME" };
    names.Append(name);
    return;
   }
  while (fgets(name.name, sizeof(name.name), file) && *name.name)
   {
    name.name[strlen(name.name) - 1] = '\0';
    names.Append(name);
   }
 }
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
  : Objects("OBJECTS.TXT"), SubObjects("SOBJECTS.TXT"), Cameras("CAMERAS.TXT")
 {
 }
};
