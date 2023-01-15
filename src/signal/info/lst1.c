#include "_signal_.h"
#include <sys_signame.h>


/*
 * 1. `sys_signame' is not portable.
 *
 * 2. `sys_siglist' is nonstandard.
 *
 * 3. prefer `strsignal(3)' than sys_siglist.
 *
 * 4. `NSIG` symbol defined in <signal.h>.
 *
 * 5. 0 signal be called null signal.
 *
 * 6. `signo_s sys_signame1' is portable implementation.
 *
 */

extern signo_s  sys_signame1[];

/* extern const char * const  sys_siglist[]; */
/* extern const char * const  sys_signame[]; */


int
main(void)
{
  char  *s, *d;
  int    nsig  =  (int) _nof_(sys_signame1);

  for (int i = 1; i < nsig; i++)
    {
      s = sys_signame1[i].name;
      d = strsignal(i);

      printf("%-16s: [%02i] %s\n", s, i, d);
    }

  exit(EXIT_SUCCESS);
}
