#include <unistd.h>
#include <signal.h>
#include <stdio.h>

#define STR(s)   #s
#define YES(s)   (s) ? "yes" : "no"

#define FMT_SIG  "%-16s %04i, %-4s\n"
#define FMT_SYM  "%-16s (no symbol)\n"


int main(void)
{
  int       rc;
  sigset_t  oset;

  sigprocmask(0, NULL, &oset);

#if defined(SIGQUIT)
  {
     rc = sigismember(&oset, SIGQUIT);
     printf(FMT_SIG, STR(SIGQUIT), SIGQUIT, YES(SIGQUIT));
  }
#else
  printf(FMT_SYM, STR(SIGQUIT));
#endif

#if defined(SIGTERM)
  {
     rc = sigismember(&oset, SIGTERM);
     printf(FMT_SIG, STR(SIGTERM), SIGTERM, YES(SIGTERM));
  }
#else
  printf(FMT_SYM, STR(SIGTERM));
#endif

#if defined(SIGUSR1)
  {
     rc = sigismember(&oset, SIGUSR1);
     printf(FMT_SIG, STR(SIGUSR1), SIGUSR1, YES(SIGUSR1));
  }
#else
  printf(FMT_SYM, STR(SIGUSR1));
#endif


  return 0;
}
