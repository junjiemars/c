#include "_ld_.h"

extern void a(char*);

int
main(void)
{
  static char  ss[]  =  "Hello, world!\n";

  a(ss);

}
