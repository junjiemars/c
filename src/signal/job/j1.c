#include "../_signal_.h"

static void on_sig_tstp (int);

int
main (void)
{
  ssize_t n;
  char buf[BUFSIZ];
  void (*oact) (int);

  setvbuf (stdout, 0, _IONBF, 0);
  printf ("%d\n", getpid ());

  if ((oact = signal (SIGTSTP, SIG_IGN)) == SIG_ERR)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }
  else if (oact == SIG_DFL)
    {
      printf ("# %s(%d) catching...\n", _str_ (SIGTSTP), SIGTSTP);
      signal (SIGTSTP, on_sig_tstp);
    }
  else
    {
      printf ("# %s(%d) ignored\n", _str_ (SIGTSTP), SIGTSTP);
      exit (EXIT_FAILURE);
    }

  while ((n = read (STDIN_FILENO, buf, BUFSIZ)) > 0)
    {
      if (write (STDOUT_FILENO, buf, n) != n)
        {
          printf ("! write error\n");
        }
    }

  if (n < 0)
    {
      perror (NULL);
    }

  exit (EXIT_SUCCESS);
}

void
on_sig_tstp (int signo)
{
  sigset_t set;

  if (signo != SIGTSTP)
    {
      printf ("# %d skip\n", signo);
      return;
    }
  printf ("# %s caught\n", _str_ (SIGTSTP));

  sigemptyset (&set);
  sigaddset (&set, SIGTSTP);
  if (sigprocmask (SIG_UNBLOCK, &set, NULL) == -1)
    {
      perror (NULL);
    }
  else
    {
      printf ("! %s unblocked\n", _str_ (SIGTSTP));
    }

  if (signal (SIGTSTP, SIG_DFL) == SIG_ERR)
    {
      perror (NULL);
    }
  else
    {
      printf ("! %s restore to default\n", _str_ (SIGTSTP));
    }

  printf ("! %s(%d) raising...\n", _str_ (SIGTSTP), SIGTSTP);

  kill (getpid (), SIGTSTP);

  /* reach here after received SIGCONT signal */

  printf ("! %s(%d) raised...\n", _str_ (SIGTSTP), SIGTSTP);

  if (signal (SIGTSTP, on_sig_tstp) == SIG_ERR)
    {
      perror (NULL);
    }
  else
    {
      printf ("! %s(%d) catching...\n", _str_ (SIGTSTP), SIGTSTP);
    }
}
