#include "../_signal_.h"

/* extern const char * const  sys_siglist[]; */
/* extern const char * const  sys_signame[]; */

int
main (void)
{
#if (NM_SYS_SIGNAME)
  for (int i = 1; i < NSIG; i++)
    {
      char *s = (char *)sys_signame[i];
      psignal (i, s);
    }
#endif

#if (NM_SYS_SIGLIST)
  for (int i = 1; i < NSIG; i++)
    {
      fprintf (stderr, "%2i %s\n", i, sys_siglist[i]);
    }
#endif

  exit (EXIT_SUCCESS);
}
