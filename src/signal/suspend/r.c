#include "_signal_.h"

/*
 * POSIX `sigsuspend(2)':
 * https://pubs.opengroup.org/onlinepubs/9699919799/functions/sigsuspend.html#tag_16_555
 *
 * expect:
 * 1. block specified signal before enter critical section.
 * 2. unblock the signal after leaving critical section.
 * 3. pause and wait the deferred signal.
 *
 */

static void on_sig_int (int);

static int N = 1;

int
main (int argc, char **argv)
{
  sigset_t nset, oset, wset;

  if (argc > 1)
    {
      N = atoi (argv[1]);
    }

  setvbuf (stdout, NULL, _IONBF, 0);
  printf ("%d\n", getpid ());

  if (signal (SIGINT, on_sig_int) == SIG_ERR)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }

  sigemptyset (&nset);
  sigaddset (&nset, SIGINT);

  if (sigprocmask (SIG_BLOCK, &nset, &oset))
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }
  printf ("# %s(%d) blocked\n", _str_ (SIGINT), SIGINT);

  printf ("! enter ...\n");

  sleep (N);

  printf ("! leaved\n");

  if (sigpending (&wset) == 0)
    {
      if (sigismember (&wset, SIGINT))
        {
          printf ("# %s(%d) pending\n", _str_ (SIGINT), SIGINT);
          sigsuspend (&oset);
        }
    }

  if (sigprocmask (SIG_SETMASK, &oset, NULL))
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }
  printf ("# %s(%d) unblocked\n", _str_ (SIGINT), SIGINT);

  printf ("# exit\n");

  exit (EXIT_SUCCESS);
}

void
on_sig_int (int signo)
{
  printf ("# %s(%d) at %s\n", _str_ (SIGINT), signo, __FUNCTION__);
}
