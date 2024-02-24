#include "_signal_.h"

/*
 * `alarm` recursively
 *
 */

extern unsigned int alarm (unsigned int);

static void on_sig_segv (int sig);
static void on_sig_alrm (int sig);

volatile int alrm_count = _ALRM_N_;

int
main (void)
{
  unsigned int n;
  struct sigaction act;
  volatile int i;

  setvbuf (stdout, NULL, _IONBF, 0);
  signal (SIGSEGV, on_sig_segv);

  if (sigaction (SIGALRM, NULL, &act) == -1)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }

  n = alarm (0);
  assert (n == 0);

  act.sa_handler = on_sig_alrm;
  sigemptyset(&act.sa_mask);
  act.sa_flags = 0;
  if (sigaction (SIGALRM, &act, NULL) == -1)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }

  alarm (1);

  for (i = 0;; i++)
    {
      /* void */
      sleep (1);
    }

  exit (EXIT_SUCCESS);
}

void
on_sig_segv (int signo)
{
  printf ("# %s(%d)\n", _str_ (SIGSEGV), signo);
  exit (EXIT_SUCCESS);
}

void
on_sig_alrm (int signo)
{
  printf ("# %s(%d)\n", _str_ (SIGALRM), signo);

  if (--alrm_count < 1)
    {
      exit (EXIT_SUCCESS);
    }

  alarm (1);
}
