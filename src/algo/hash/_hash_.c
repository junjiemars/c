#include "_hash_.h"
#include <stdio.h>


void 
print_hash(const char *name, const char *ss, unsigned long hash)
{
  printf("%s\n------------\n", name);
  printf("%16lu: %s\n", hash, ss);
}
