#include "sig2str.h"
#include <_signal_.h>

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
main (void)
{
  char *d;
  char s[SIG2STR_MAX];
  int nsig = N_SIG2STR; /* NSIG */
  struct sigaction act;
  char *sact;
  char desc[BUFSIZ];
  char *eof_desc;

  for (int i = 1; i < nsig; i++)
    {
      if (sig2str (i, &s[0]) == -1)
        {
          perror (NULL);
          exit (EXIT_FAILURE);
        }

      if (sigaction (i, 0, &act) == 0)
        {
          if (act.sa_handler == SIG_DFL)
            {
              sact = "DFL";
            }
          else if (act.sa_handler == SIG_IGN)
            {
              sact = "IGN";
            }
          else
            {
              sact = "---";
            }
        }

      d = strsignal (i);
      strncpy (desc, d, BUFSIZ);
      eof_desc = strchr (desc, ':');
      if (eof_desc)
        {
          *eof_desc = '\0';
        }

      printf ("SIG%-10s %2i %4s %s\n", s, i, sact, desc);
    }

  exit (EXIT_SUCCESS);
}
