#include <stdio.h>
#include <stdlib.h>

#include "../common/common.h"
#include "../common/error.cpp"

#include "lwofile.h"

#include "eet.cpp"
#include "types.cpp"
#include "convert.cpp"
#include "object.cpp"

int main(int argc, char* argv[])
{
 if (argc != 3)
  error("Usage: %s file_in.lwo file_out.eeo", argv[0]);

 EET eet;
 OBJECT_3D obj(eet, argv[1], argv[2]);
 return 0;
}
