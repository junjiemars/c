#include "_signal_.h"

/*
 * 1. the first sleep be protected by block SIGQUIT.
 *
 * 2. signals are not queued if we generate SIGQUIT more than once but
 * it's be caught only once.
 *
 */

static void on_sig_quit (int);

static unsigned int N = 1;

int
main (int argc, char **argv)
{
  sigset_t nset, oset, pset;

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

  sigemptyset (&nset);
  sigaddset (&nset, SIGQUIT);
  if (sigprocmask (SIG_BLOCK, &nset, &oset))
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }
  printf ("! %s(%d) blocked\n", _str_ (SIGQUIT), SIGQUIT);

  sleep (N);

  if (sigpending (&pset))
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }
  if (sigismember (&pset, SIGQUIT))
    {
      printf ("# %s(%d) pending\n", _str_ (SIGQUIT), SIGQUIT);
    }

  if (sigprocmask (SIG_SETMASK, &oset, NULL))
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }
  printf ("! %s(%d) unblocked\n", _str_ (SIGQUIT), SIGQUIT);

  exit (EXIT_SUCCESS);
}

void
on_sig_quit (int signo)
{
  printf ("# %s(%d) caught\n", _str_ (SIGQUIT), signo);
}
