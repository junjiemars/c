#include "_signal_.h"

static void on_sig_chld (int signo);

int
main (void)
{
  int err;
  pid_t pid;

  if (SIG_ERR == signal (SIGCHLD, on_sig_chld))
    {
      err = errno;
      fprintf (stderr, "!main: %s\n", strerror (err));
      return err;
    }

  pid = fork ();
  if (-1 == pid)
    {
      err = errno;
      fprintf (stderr, "!main: %s\n", strerror (err));
      return err;
    }

  if (0 == pid)
    {
      fprintf (stdout, "!main: child %d\n", getpid ());
      sleep (2);
      exit (0x1122);
    }
  else
    {
      fprintf (stdout, "!main: pause %d\n", getpid ());
      pause ();
    }

  return 0;
}

void
on_sig_chld (int signo)
{
  pid_t pid;
  int status;

  if (SIGCHLD == signo)
    {
      fprintf (stdout, "!on_sig_chld: %d wait child ...\n", getpid ());

      pid = wait (&status);
      if (-1 == pid)
        {
          fprintf (stderr, "!on_sig_chld: %s\n", strerror (errno));
        }

      fprintf (stdout, "!on_sig_chld: child %d with 0x%04x exit ...\n", pid,
               WEXITSTATUS (status));
    }
}
