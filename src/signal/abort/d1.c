#include <_signal_.h>
#include <signal.h>

/*
 * 1. `abort(3)' never return to its caller.
 * 2. The output streams are flushed and closed is implementation defined.
 * 3. If `on_sig_abrt' returns, `abort(3)' terminates the process.
 *
 */

extern void abort (void);

/* ignore > 0, default = 0, raise < 0 */
static int ignore_abort = 0;

/* exit > 0 */
static sig_atomic_t exit_on_sig = 1;

static void on_sig_abrt (int);
static void on_abrt_exit (void);

int
main (int argc, char **argv)
{
  struct sigaction oact;

  /* usage: [ignore-abort] [exit-on-signal] */
  if (argc > 1)
    {
      ignore_abort = atoi (argv[1]);
    }
  if (argc > 2)
    {
      exit_on_sig = atoi (argv[2]);
    }

  setvbuf (stdout, NULL, _IOFBF, 0);
  printf ("%d\n", getpid ());
  atexit (on_abrt_exit);

  /* examine current sigaction */
  if (sigaction (SIGABRT, NULL, &oact) == -1)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }

  if (ignore_abort > 0)
    {
      if (oact.sa_handler != SIG_IGN)
        {
          printf ("# ignore SIGABRT ... \n");
          signal (SIGABRT, SIG_IGN);
        }
    }
  else if (ignore_abort < 0)
    {
      printf ("# trap SIGABRT ...\n");
      signal (SIGABRT, on_sig_abrt);
    }
  else
    {
      /* SIG_DFL*/
      printf ("# default SIGABRT ...\n");
    }

  abort ();

  /* never reach here; */
}

void
on_sig_abrt (int signo)
{
  printf ("# caught %s(%d)\n", _str_ (SIGABRT), signo);

  signal (SIGABRT, on_sig_abrt);
  if (exit_on_sig > 0)
    {
      exit (EXIT_SUCCESS);
    }
}

void
on_abrt_exit (void)
{
  printf ("# exiting ...\n");
}
