#include <stdio.h>
#include <stdlib.h>

#include "../common/error.cpp"

#include "lws.cpp"
#include "convert.cpp"


int main(int argc, char* argv[])
{
 puts("Enemy Engaged LWS to EES converter build " __DATE__);

 if (argc != 3)
  error("Usage: %s file_in.lws file_out.ees", argv[0]);

 LwsFile file(argv[1]);
 //file.Print();

 Convert convert(file, argv[2]);

 return 0;
}

extern "C" int _compiled_under_generic;
int _compiled_under_generic;
