#include "_signal_.h"


/*
 * `sigqueue(2)'
 *
 *
 *
 */

static void  on_sig_alrm(int, siginfo_t*, void*);


int
main(void)
{
  pid_t             pid;
  struct sigaction  act;
  union sigval      val  =  { .sival_int = 0x11223344 };

  pid = getpid();
  fprintf(stderr, "%d\n", pid);

  sigemptyset(&act.sa_mask);
  act.sa_flags = SA_SIGINFO;
  act.sa_sigaction = on_sig_alrm;

  if (sigaction(SIGALRM, &act, NULL) == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  if (sigqueue(pid, SIGALRM, val) == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  exit(EXIT_SUCCESS);
}


void
on_sig_alrm(int signo, siginfo_t *info, void *uctx)
{
  (void) uctx;

  fprintf(stderr, "# %s(%d) caught, 0x%x\n", _str_(SIGALRM), signo,
          info->si_value.sival_int);
}
