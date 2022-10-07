#include <_ld_.h>

int
main(void)
{
  static char *ss = "Hi, ASM\n";

  fprintf(stdout, "%s", ss);

  return 0;
}
