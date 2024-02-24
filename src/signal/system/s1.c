#include "_signal_.h"

/*
 * emulates POSIX `system(3)'.
 *
 * https://pubs.opengroup.org/onlinepubs/9699919799/functions/system.html
 *
 */

#define CMD_PROC "/bin/sh"

int
system (const char *command)
{
  int stat;
  pid_t pid;
  sigset_t nset, oset;
  struct sigaction ignore, intr, quit;

  if (command == NULL)
    {
      return !access (CMD_PROC, X_OK);
    }

  ignore.sa_handler = SIG_IGN;
  sigemptyset (&ignore.sa_mask);
  ignore.sa_flags = 0;

  if (sigaction (SIGINT, &ignore, &intr) == -1)
    {
      return -1;
    }

  if (sigaction (SIGQUIT, &ignore, &quit) == -1)
    {
      return -1;
    }

  sigemptyset (&nset);
  sigaddset (&nset, SIGCHLD);

  if (sigprocmask (SIG_BLOCK, &nset, &oset) == -1)
    {
      return -1;
    }

  if ((pid = fork ()) == -1)
    {
      stat = -1;
    }
  else if (pid == 0)
    {
      if (sigaction (SIGINT, &intr, NULL) == -1)
        {
          return -1;
        }
      if (sigaction (SIGQUIT, &quit, NULL) == -1)
        {
          return 1;
        }
      if (sigprocmask (SIG_SETMASK, &oset, NULL) == -1)
        {
          return 1;
        }

      execl (CMD_PROC, "sh", "-c", command, NULL);
      _exit (127);
    }
  else
    {
      while (waitpid (pid, &stat, 0) == -1)
        {
          if (errno != EINTR)
            {
              stat = -1;
              break;
            }
        }

      if (sigaction (SIGINT, &intr, NULL) == -1)
        {
          return -1;
        }
      if (sigaction (SIGQUIT, &quit, NULL) == -1)
        {
          return -1;
        }
      if (sigprocmask (SIG_SETMASK, &oset, NULL) == -1)
        {
          return -1;
        }
    }

  return stat;
}
