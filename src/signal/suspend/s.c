#include "_signal_.h"

static void on_sig_quit (int);

static int N = 1;

int
main (int argc, char **argv)
{
  sigset_t nmask, omask, pmask;

  if (argc > 1)
    {
      N = atoi (argv[1]);
    }

  setvbuf (stdout, NULL, _IONBF, 0);
  printf ("%d\n", getpid ());

  if (signal (SIGQUIT, on_sig_quit) == SIG_ERR)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }

  sigemptyset (&nmask);
  sigaddset (&nmask, SIGQUIT);

  if (sigprocmask (SIG_BLOCK, &nmask, &omask) == -1)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }
  printf ("! %s(%d) blocked\n", _str_ (SIGQUIT), SIGQUIT);

  sleep (N);

  if (sigpending (&pmask) == -1)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }

  if (sigismember (&pmask, SIGQUIT))
    {
      printf ("# %s(%d) pending\n", _str_ (SIGQUIT), SIGQUIT);
    }

  if (sigprocmask (SIG_SETMASK, &omask, NULL) == -1)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }
  printf ("! %s(%d) unblocked\n", _str_ (SIGQUIT), SIGQUIT);

  sleep (N);

  exit (EXIT_SUCCESS);
}

void
on_sig_quit (int signo)
{
  printf ("# %s(%d) caught\n", _str_ (SIGQUIT), signo);
  signal (SIGQUIT, SIG_DFL);
}
