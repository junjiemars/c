#include <_signal_.h>

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
  int rc;
  struct sigaction nact, oact;
  sigset_t nset, oset1, oset2, wset;

  if (argc > 1)
    {
      N = atoi (argv[1]);
    }

  setvbuf (stdout, NULL, _IONBF, 0);
  printf ("%d\n", getpid ());

  nact.sa_handler = on_sig_int;
  sigemptyset (&nact.sa_mask);
  nact.sa_flags = 0;
  if (sigaction (SIGINT, &nact, &oact) == -1)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }

  sigemptyset (&nset);
  sigaddset (&nset, SIGINT);

  if (sigprocmask (SIG_BLOCK, &nset, &oset1))
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }
  printf ("# %s(%d) blocked\n", _str_ (SIGINT), SIGINT);

  printf ("! enter critical ...\n");

  sleep (N);

  printf ("! leaved\n");

  if (sigpending (&wset) == 0)
    {
      if (sigismember (&wset, SIGINT))
        {
          printf ("# %s(%d) pending\n", _str_ (SIGINT), SIGINT);

          rc = sigsuspend (&oset1);

          /* examine `sigsuspend' effects */
          assert (rc == -1 && errno == EINTR && "should return -1");
          sigprocmask (0, NULL, &oset2);
          assert (oset1 == oset2 && "should restored");

          printf ("# %s(%d) go\n", _str_ (SIGINT), SIGINT);
        }
    }

  if (sigprocmask (SIG_SETMASK, &oset1, NULL))
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
  if (signo == SIGINT)
    {
      printf ("# %s(%d) at %s\n", _str_ (SIGINT), signo, __FUNCTION__);
    }
}
