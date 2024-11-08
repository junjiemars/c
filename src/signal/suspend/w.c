#include <_signal_.h>

/*
 * expect:
 *
 * 1. block specified signal before enter critical section.
 *
 * 2. unblock the signal after leaving critical section.
 *
 * 3. pause and wait the deferred signal.
 *
 */

static void on_sig_int (int);

static int N = 1;

int
main (int argc, char **argv)
{
  sigset_t nset, oset;

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

  printf ("! %s blocked(%d)\n", _str_ (SIGINT), SIGINT);

  if (sigprocmask (SIG_SETMASK, &nset, &oset) == -1)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }

  printf ("! enter...\n");

  sleep (N);

  printf ("! leaved\n");

  if (sigprocmask (SIG_SETMASK, &oset, NULL) == -1)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }
  printf ("! %s(%d) unblocked\n", _str_ (SIGINT), SIGINT);

  printf ("# exit\n");

  exit (EXIT_SUCCESS);
}

void
on_sig_int (int signo)
{
  printf ("# %s(%d) caught\n", _str_ (SIGINT), signo);
}
