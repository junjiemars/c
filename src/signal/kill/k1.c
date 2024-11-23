#include "../_signal_.h"

/*
 * 1. `raise(3)' function was defined by ISO C, sends a signal to the
 * calling process.
 *
 * 2. `raise(3)' equals `kill(getpid(), signo)`.
 *
 * 3. `kill(2)' is a system call, sends a signal to process or process
 * group.
 *
 */

static void on_sig_usr (int);

int
main ()
{
  signal (SIGUSR1, on_sig_usr);
  signal (SIGUSR2, on_sig_usr);

  raise (SIGUSR1);
  kill (getpid (), SIGUSR2);

  exit (EXIT_SUCCESS);
}

void
on_sig_usr (int signo)
{
  if (SIGUSR1 == signo)
    {
      printf ("# caught %s(%d)\n", _str_ (SIGUSR1), SIGUSR1);
    }
  else if (SIGUSR2 == signo)
    {
      printf ("# caught %s(%d)\n", _str_ (SIGUSR2), SIGUSR2);
    }
}
