#include "ndef.h"
#include <stdio.h>

#define BIT8_SEP  ","
#define BIT16_SEP "|"
#define BIT32_SEP "\n                         "
#define BIT8_PRE  "0b: "
#define BIT8_SUF  "\n"

#include "nbits.h"

int
main(int argc, char **argv) 
{
  _unused_(argc);
  _unused_(argv);

  printf("%#18x = ", 0x12);
  printf(BPRI8(0x12));

  printf("%#18x = ", 0x1234);
  printf(BPRI16(0x1234));

  printf("%#18x = ", 0x12345678);
  printf(BPRI32(0x12345678));

#if (NM_CPU_CACHE_LINE == 64)
  printf("0x%16lx = ", 0x1234567890abcdef);
  printf(BPRI64(0x1234567890abcdef));
#endif
  
  return 0;
}
