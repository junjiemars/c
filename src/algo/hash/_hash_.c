#include "_hash_.h"
#include <stdio.h>
#include <bits.h>


void 
print_hash(const char *name, const char *ss, unsigned long hash)
{
  printf("%s\n------------\n%s -> %16lu\n", name, ss, hash);
  printf(BPRI64(hash));
}
