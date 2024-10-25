#include "_io_.h"
#include <signal.h>

static void on_sig (int);

int
main (void)
{
  pid_t pid;
  /* int fd1 = 3, fd2 = 4; */
  /* ssize_t nread; */
  struct sigaction act_chld, act_usr;

  act_chld.sa_handler = on_sig;
  act_chld.sa_flags = 0;
  sigemptyset (&act_chld.sa_mask);
  if (sigaction (SIGCHLD, &act_chld, NULL) == -1)
    {
      perror (NULL);
      exit (1);
    }

  act_usr.sa_handler = on_sig;
  act_usr.sa_flags = 0;
  sigemptyset (&act_usr.sa_mask);
  if (sigaction (SIGUSR1, &act_usr, NULL) == -1)
    {
      perror (NULL);
      exit (1);
    }

  if ((pid = fork ()) < 0)
    {
      perror (NULL);
      exit (1);
    }
  else if (pid == 0)
    {
      /* !TODO: read from fd1 */
      exit (0);
    }
  else
    {
      /* !TODO: read from fd2 */
      waitpid (pid, NULL, 0);
      /* kill (pid, SIGUSR1); */
      exit (0);
    }
}

void
on_sig (int signo)
{
  int n;
  char ss[BUFSIZ];

  if (signo == SIGCHLD)
    {
      n = snprintf (ss, BUFSIZ, "%d %s(%d)\n", getpid (), _str_ (SIGCHLD),
                    SIGCHLD);
      write (STDERR_FILENO, ss, n);
    }
  else if (signo == SIGUSR1)
    {
      n = snprintf (ss, BUFSIZ, "%d %s(%d)\n", getpid (), _str_ (SIGUSR1),
                    SIGUSR1);
      write (STDERR_FILENO, ss, n);
    }
}
