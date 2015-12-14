#include <stdio.h>
#include <stdlib.h>

#include "../common/error.cpp"

#include "lws.cpp"
#include "convert.cpp"


int main(int argc, char* argv[])
{
 puts("Enemy Engaged LWS to EES converter build " __DATE__);

 int version = 0;

 if (argc > 1 && *argv[1] == '-')
  {
   version = atoi(argv[1]);
   argc--;
   argv++;
  }

 if (argc < 3)
  error("Usage: %s [-{1,2,3}] file_in.lws file_out.ees [file_log.txt]", argv[0]);

 LwsFile file(argv[1]);
 //file.Print();

 Convert convert(file, argv[2], argv[3], version);

 return 0;
}

extern "C" int _compiled_under_generic;
int _compiled_under_generic;
