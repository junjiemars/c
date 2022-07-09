#include <_signal_.h>
#include <ctype.h>

int
main(void)
{
  extern const char * const sys_siglist[];
  extern const char * const sys_signame[];

  for (unsigned i = 1; i < NSIG; i++)
    {
      printf("sig%s: %s\n", sys_signame[i], sys_siglist[i]);
    }

  exit(EXIT_SUCCESS);
}
