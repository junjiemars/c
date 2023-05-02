#include "_process_.h"

static void on_sig_chld (int);

int
main (void)
{
  pid_t pid;

  if (signal (SIGCHLD, on_sig_chld) == SIG_ERR)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }

  if ((pid = fork ()) == -1)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }
  else if (pid == 0)
    {
      exit (EXIT_SUCCESS);
    }

  pause ();

  exit (EXIT_SUCCESS);
}

void
on_sig_chld (int signo)
{
  if (signo == SIGCHLD)
    {
      fprintf (stderr, "%s caught(%d)\n", _str_ (SIGCHLD), signo);
    }
}
