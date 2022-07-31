#include <_signal_.h>

static void on_sig_quit(int);

static int  N  =  5;


int
main(int argc, char **argv)
{
  sigset_t  nmask, omask, pmask;

  if (argc > 1)
    {
      N = atoi(argv[1]);
    }

  signal(SIGQUIT, on_sig_quit);

  sigemptyset(&nmask);
  sigaddset(&nmask, SIGQUIT);

  sigprocmask(SIG_BLOCK, &nmask, &omask);
  printf("! %s blocked\n", _str_(SIGQUIT));

  sleep(N);

  sigpending(&pmask);
  if (sigismember(&pmask, SIGQUIT))
    {
      printf("# %s pending\n", _str_(SIGQUIT));
    }

  sigprocmask(SIG_SETMASK, &omask, NULL);
  printf("! %s unblocked\n", _str_(SIGQUIT));

  sleep(N);



  exit(EXIT_SUCCESS);
}

void
on_sig_quit(int signo)
{
  if (SIGQUIT == signo)
    {
      printf("# %s\n", _str_(SIGQUIT));

      signal(SIGQUIT, on_sig_quit);
    }
}
