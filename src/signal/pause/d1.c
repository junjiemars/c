#include <_signal_.h>

/*
 * Implementations derived from UNIX System V support the signal
 * function, but it provides the old unreliable signal semantics.
 *
 */

extern int pause (void);

static void on_sig_usr1 (int signo);
static void on_sig_term (int signo);

int
main (void)
{
  pid_t pid;
  sigset_t oset1, oset2;

  setvbuf (stdout, NULL, _IONBF, 0);
  printf ("%d\n", (pid = getpid ()));

  sigprocmask (0, NULL, &oset1);

  signal (SIGUSR1, on_sig_usr1);
  signal (SIGTERM, on_sig_term);

  for (;;)
    {
      printf ("# kill -USR1 %d\n# kill -TERM %d\n", pid, pid);

      pause ();

      sigprocmask (0, NULL, &oset2);
      assert (oset1 == oset2 && "signal mark should be restore");
    }

  exit (EXIT_SUCCESS);
}

void
on_sig_usr1 (int signo)
{
  printf ("! %s(%d)\n", _str_ (SIGUSR1), signo);
}

void
on_sig_term (int signo)
{
  printf ("! %s(%d)\n", _str_ (SIGTERM), signo);
  printf ("# exiting ...\n");
  exit (EXIT_SUCCESS);
}
