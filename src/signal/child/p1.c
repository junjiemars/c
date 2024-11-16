#include "../_signal_.h"

/*
 * The child inherits the parent's signal dispositions when a process
 * calls fork.
 *
 */

static void on_sig_alrm (int);

int
main (void)
{
  int stat;
  pid_t pid;

  signal (SIGALRM, on_sig_alrm);

  if ((pid = fork ()) == -1)
    {
      perror (NULL);
      exit (errno);
    }
  else if (pid == 0) /* child process */
    {
      printf ("%-8d: pause...\n", getpid ());
      pause ();
    }
  else
    {
      printf ("%-8d: sleep(1)...\n", getpid ());

      sleep (1);
      kill (pid, SIGALRM);

      waitpid (pid, &stat, 0);
    }

  exit (EXIT_SUCCESS);
}

void
on_sig_alrm (int signo)
{
  if (SIGALRM == signo)
    {
      printf ("%-8d: %s\n", getpid (), _str_ (SIGALRM));
    }
}
