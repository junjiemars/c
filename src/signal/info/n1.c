#include <_signal_.h>
#include <ctype.h>

/*
 * 1. sys_signame is not portable.
 * 2. prefer strsignal sys_siglist.
 * 3. strsig is portable implementation.
 *
 */


extern const char * const  sys_siglist[];
/* extern const char * const  sys_signame[]; */
extern char * strsig(int);


int
main(void)
{
  for (unsigned i = 1; i < NSIG; i++)
    {
      printf("%-16s: [%02i] %s\n", strsig(i), i, sys_siglist[i]);
    }

  exit(EXIT_SUCCESS);
}
