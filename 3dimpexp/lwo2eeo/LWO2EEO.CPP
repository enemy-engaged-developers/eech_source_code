#include <stdio.h>
#include <stdlib.h>

#include "../common/common.h"
#include "../common/error.cpp"

#include "lwofile.h"

#include "types.cpp"
#include "convert.cpp"
#include "object.cpp"

int main(int argc, char* argv[])
{
 if (argc != 3)
  error("Usage: %s file_in.lwo file_out.eeo", argv[0]);

 OBJECT_3D obj(argv[1], argv[2]);
 return 0;
}
