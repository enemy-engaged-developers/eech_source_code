class Translator
{
 public:

 virtual const char* operator ()(int number) = 0;
};

class SimpleTranslator : public Translator
{
 public:

 const char* operator ()(int number)
 {
  snprintf(buf, sizeof(buf), "%04X", number);
  return buf;
 }

 private:

 char buf[64];
};

class AggTranslator : public Translator
{
 public:

 int Add(const char* name)
 {
  return names += name;
 }

 const char* operator ()(int number)
 {
  return names[number];
 }

 private:

 Names names;
};
