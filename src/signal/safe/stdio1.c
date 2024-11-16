#include "../_signal_.h"

/*
 * 1. the outputs of `printf(3)' are interleaved.
 *
 * 2. stdio is not async-signal-safe.
 *
 * 3. `man signal-safety(7)' on Linux.
 *
 */

static void on_sig (int);

static volatile int count = 8;

static char alpha[] = "abcdefghijklmnopqrstuvwxyz";
static char digit[] = "0123456789";

int
main (void)
{
  sigset_t set;
  struct sigaction act;

  setvbuf (stdout, 0, _IONBF, 0);
  printf ("%d\n%s\n%s\n", getpid (), alpha, digit);

  act.sa_handler = on_sig;
  act.sa_flags = 0;
  sigfillset (&set);
  sigdelset (&set, SIGALRM);

  if (sigaction (SIGALRM, &act, NULL) == -1)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }

  alarm (1);

  for (;;)
    {
      printf ("%c", alpha[count % _nof_ (alpha)]);
      pause ();
    }
  putchar ('\n');

  exit (EXIT_SUCCESS);
}

void
on_sig (int signo)
{
  if (signo == SIGALRM)
    {
      printf ("%c\n", digit[count % _nof_ (digit)]);

      alarm (1);
    }

  if (--count < 1)
    {
      putchar ('\n');
      exit (EXIT_SUCCESS);
    }
}
