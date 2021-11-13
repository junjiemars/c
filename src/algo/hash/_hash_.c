#include "_hash_.h"
#include <bits.h>
#include <stdio.h>


void 
print_hash(const char *name, const char *ss, unsigned long hash)
{
  printf("%s\n------------\n%s -> %16lu\n", name, ss, hash);
  printf(BPRI64((uint64_t)hash));
}
