#include "_signal_.h"
#include "sig2str.h"


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
 * 6. `sig2str' is nonstandard and is a Solaris implementation.
 *
 */


/* extern const char * const  sys_siglist[]; */
/* extern const char * const  sys_signame[]; */


int
main(void)
{
  char  *d;
  char   s[SIG2STR_MAX];
  int    nsig  =  N_SIG2STR;    /* NSIG */

  for (int i = 1; i < nsig; i++)
    {
      if (sig2str(i, &s[0]) == -1)
        {
          perror(NULL);
          exit(EXIT_FAILURE);
        }

      d = strsignal(i);
      printf("SIG%-16s: [%02i] %s\n", s, i, d);
    }

  exit(EXIT_SUCCESS);
}
