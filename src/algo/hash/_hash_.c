#include "_hash_.h"
#include <nbits.h>

void
print_hash (const char *name, const char *ss, unsigned long hash)
{
  printf ("%s\n------------\n%s -> %16lu\n" BPRI64 "\n", name, ss, hash,
          BIT64 ((uint64_t)hash));
}
