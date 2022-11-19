#include "_stdio_.h"
#include <stdio.h>

void
hex_out(const char *ss)
{
  unsigned char  c;
  while (0 != (c = *ss++))
    {
      fprintf(stdout, "0x%02x ", c);
    }
  fprintf(stdout, "\n");
}
