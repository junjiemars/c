#include <_signal_.h>


/* a POSIX implementation of abort function */
static void abort1(void);

static void on_sig_abrt(int);


int
main(void)
{
  printf("%d\n", getpid());

  signal(SIGABRT, on_sig_abrt);

  abort1();

  printf("! never go here\n");

  exit(EXIT_SUCCESS);
}

void
abort1(void)
{
  sigset_t          set;
  struct sigaction  act;

  sigaction(SIGABRT, NULL, &act);
  if (act.sa_handler == SIG_IGN)
    {
      act.sa_handler = SIG_DFL;
      sigaction(SIGABRT, &act, NULL);
    }

  if (act.sa_handler == SIG_DFL)
    {
      fflush(NULL);
    }

  sigfillset(&set);
  sigdelset(&set, SIGABRT);
  sigprocmask(SIG_SETMASK, &set, NULL);

  kill(getpid(), SIGABRT);

  fflush(NULL);
  act.sa_handler = SIG_DFL;
  sigaction(SIGABRT, &act, NULL);

  sigprocmask(SIG_SETMASK, &set, NULL);
  kill(getpid(), SIGABRT);

  exit(EXIT_FAILURE);
}

void
on_sig_abrt(int signo)
{
  if (signo == SIGABRT)
    {
      printf("# %s\n", _str_(SIGABRT));

      /* cleanup then exit */
    }
}
