#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#include "../common/common.h"
#include "../common/error.cpp"

#include "lwofile.h"

#include "types.cpp"
#include "convert.cpp"
#include "object.cpp"

int main(int argc, char* argv[])
{
 puts("Enemy Engaged LWO to EEO converter build " __DATE__);

 if (argc < 3)
  error("Usage: %s file_in.lwo file_out.eeo [file_log.txt]", argv[0]);

 OBJECT_3D obj(argv[1], argv[2], argv[3]);
 return 0;
}
