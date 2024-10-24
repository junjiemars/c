#include "_term_.h"
#include "ptys.h"
#include <limits.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * emulate script(1) program
 */

static sig_t sig_intr (int, sig_t);
static void dup_pty_io (int);
static void on_sigterm (int);

static volatile sig_atomic_t has_sigterm;

int
main (int argc, char **argv)
{
  int fd;
  pid_t pid;
  char name[_POSIX_PATH_MAX];

  if (argc < 2)
    {
      fprintf (stderr, "usage: %s <command>\n", argv[0]);
      exit (1);
    }

  if ((pid = pty_fork (&fd, name, _POSIX_PATH_MAX)) == -1)
    {
      perror (NULL);
      exit (1);
    }

  if (pid == 0)
    {
      if (execvp (argv[1], &argv[1]) == -1)
        {
          perror (NULL);
          exit (1);
        }
    }
  else
    {
      dup_pty_io (fd);
    }

  exit (0);
}

sig_t
sig_intr (int signo, sig_t fn)
{
  struct sigaction act, oact;
  act.sa_handler = fn;
  sigemptyset (&act.sa_mask);
  act.sa_flags = 0;
#ifdef SA_INTERRUPT
  act.sa_flags |= SA_INTERRUPT;
#endif
  if (sigaction (signo, &act, &oact) < 0)
    {
      return SIG_ERR;
    }
  return oact.sa_handler;
}

void
dup_pty_io (int fd)
{
  pid_t pid;
  int nread;
  char buf[BUFSIZ];

  if ((pid = fork ()) < 0)
    {
      perror (NULL);
      exit (1);
    }
  else if (pid == 0) /* child */
    {
      for (;;)
        {
          if ((nread = read (STDIN_FILENO, buf, BUFSIZ)) < 0)
            {
              perror (NULL);
              exit (1);
            }
          else if (nread == 0)
            {
              break;
            }
          if (write (fd, buf, nread) != nread)
            {
              perror (NULL);
              exit (1);
            }
        }
    }
  else /* parent */
    {
      if (sig_intr (SIGTERM, on_sigterm) == SIG_ERR)
        {
          perror (NULL);
          exit (1);
        }
      for (;;)
        {
          if ((nread = read (fd, buf, BUFSIZ)) <= 0)
            {
              break;
            }
          if (write (STDOUT_FILENO, buf, nread) != nread)
            {
              perror (NULL);
              exit (1);
            }
        }
      if (has_sigterm == 0)
        {
          kill (pid, SIGTERM);
        }
    }
}

void
on_sigterm (int signo)
{
  has_sigterm = signo;
}
