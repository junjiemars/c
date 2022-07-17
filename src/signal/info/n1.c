#include <_signal_.h>
#include <ctype.h>

/*
 * 1. sys_signame is not portable.
 * 2. prefer strsignal sys_siglist.
 * 3. strsigno is portable implementation.
 *
 */


extern const char * const  sys_siglist[];
/* extern const char * const  sys_signame[]; */
extern char * strsigno(int);


int
main(void)
{
  char  *s;

  for (unsigned i = 1; i < NSIG; i++)
    {
      s = strsigno(i);
      if (!s)
        {
          continue;
        }
      printf("%-16s: [%02i] %s\n", s, i, sys_siglist[i]);
    }

  exit(EXIT_SUCCESS);
}
