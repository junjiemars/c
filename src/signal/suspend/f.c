#include <_signal_.h>

static void on_sig (int);

static int N = 1;
static volatile sig_atomic_t qflag;

int
main (int argc, char **argv)
{
  sigset_t nset, oset, zset;

  if (argc > 1)
    {
      N = atoi (argv[1]);
    }
  printf ("%d\n", getpid ());
  setvbuf (stdout, 0, _IONBF, 0);

  signal (SIGINT, on_sig);
  signal (SIGQUIT, on_sig);

  sigemptyset (&zset);
  sigemptyset (&nset);
  sigaddset (&nset, SIGQUIT);

  if (sigprocmask (SIG_BLOCK, &nset, &oset))
    {
      perror (NULL);
    };
  printf ("! %s(%d) blocked\n", _str_ (SIGQUIT), SIGQUIT);

  sleep (N);

  while (qflag == 0)
    {
      printf ("! suspend enter ...\n");
      sigsuspend (&zset);
    }
  qflag = 0;

  printf ("! suspend return\n");

  if (sigprocmask (SIG_SETMASK, &oset, NULL))
    {
      perror (NULL);
    }
  printf ("! %s(%d) unblocked\n", _str_ (SIGQUIT), SIGQUIT);

  exit (EXIT_SUCCESS);
}

void
on_sig (int signo)
{
  if (SIGINT == signo)
    {
      printf ("# %s(%d), qflag=%d\n", _str_ (SIGINT), SIGINT, qflag);
    }
  else if (SIGQUIT == signo)
    {
      qflag = 1;
      printf ("# %s(%d), qflag=%d\n", _str_ (SIGQUIT), SIGQUIT, qflag);
    }
}
