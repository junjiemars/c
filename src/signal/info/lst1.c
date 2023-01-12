#include "_signal_.h"
#include <ctype.h>

/*
 * 1. `sys_signame' is not portable.
 * 2. prefer `strsignal(3)' than sys_siglist.
 * 3. `strsigno' is portable implementation in n1.awk.linux/darwin.in.
 * 4. `NSIG` symbol defined in <signal.h>.
 * 5. 0 signal be called null signal.
 *
 */

typedef struct signo_s
{
  unsigned int  signo;
  char *        str;
} signo_s;


static char *  strsigno(unsigned int);

/* extern const char * const  sys_siglist[]; */
/* extern const char * const  sys_signame[]; */


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
      printf("%-16s: [%02i] %s\n", s, i, strsignal(i));
    }

  exit(EXIT_SUCCESS);
}

char *
strsigno(unsigned int signo)
{
  static signo_s ss[] =
    {
      {.signo = SIGHUP, .str = _str_(SIGHUP)},
      {.signo = SIGINT, .str = _str_(SIGINT)},
      {.signo = SIGQUIT, .str = _str_(SIGQUIT)},
      {.signo = SIGILL, .str = _str_(SIGILL)},
      {.signo = SIGTRAP, .str = _str_(SIGTRAP)},
      {.signo = SIGABRT, .str = _str_(SIGABRT)},
      {.signo = SIGBUS, .str = _str_(SIGBUS)},
      {.signo = SIGFPE, .str = _str_(SIGFPE)},
      {.signo = SIGKILL, .str = _str_(SIGKILL)},
      {.signo = SIGUSR1, .str = _str_(SIGUSR1)},
      {.signo = SIGSEGV, .str = _str_(SIGSEGV)},
      {.signo = SIGUSR2, .str = _str_(SIGUSR2)},
      {.signo = SIGPIPE, .str = _str_(SIGPIPE)},
      {.signo = SIGALRM, .str = _str_(SIGALRM)},
      {.signo = SIGTERM, .str = _str_(SIGTERM)},
      {.signo = SIGSTKFLT, .str = _str_(SIGSTKFLT)},
      {.signo = SIGCHLD, .str = _str_(SIGCHLD)},
      {.signo = SIGCONT, .str = _str_(SIGCONT)},
      {.signo = SIGSTOP, .str = _str_(SIGSTOP)},
      {.signo = SIGTSTP, .str = _str_(SIGTSTP)},
      {.signo = SIGTTIN, .str = _str_(SIGTTIN)},
      {.signo = SIGTTOU, .str = _str_(SIGTTOU)},
      {.signo = SIGURG, .str = _str_(SIGURG)},
      {.signo = SIGXCPU, .str = _str_(SIGXCPU)},
      {.signo = SIGXFSZ, .str = _str_(SIGXFSZ)},
      {.signo = SIGVTALRM, .str = _str_(SIGVTALRM)},
      {.signo = SIGPROF, .str = _str_(SIGPROF)},
      {.signo = SIGWINCH, .str = _str_(SIGWINCH)},
      {.signo = SIGIO, .str = _str_(SIGIO)},
      {.signo = SIGPWR, .str = _str_(SIGPWR)},
      {.signo = SIGSYS, .str = _str_(SIGSYS)},
    };

  for (unsigned int i = 0; i < _nof_(ss); i++)
    {
      if (ss[i].signo == signo)
        {
          return ss[i].str;
        }
    }

  return NULL;
}
