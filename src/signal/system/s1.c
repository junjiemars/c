#include "_signal_.h"

/*
 * emulates POSIX `system(3)'.
 *
 * https://pubs.opengroup.org/onlinepubs/9699919799/functions/system.html
 *
 */


int
system(const char *command)
{
  int               status;
  pid_t             pid;
  sigset_t          chldmask, savemask;
  struct sigaction  ignore, intr, quit;

  if (command == NULL)
    {
      return 1;
    }

  ignore.sa_handler = SIG_IGN;
  sigemptyset(&ignore.sa_mask);
  ignore.sa_flags = 0;

  if (-1 == sigaction(SIGINT, &ignore, &intr))
    {
      return -1;
    }

  if (-1 == sigaction(SIGQUIT, &ignore, &quit))
    {
      return -1;
    }

  sigemptyset(&chldmask);
  sigaddset(&chldmask, SIGCHLD);

  if (-1 == sigprocmask(SIG_BLOCK, &chldmask, &savemask))
    {
      return -1;
    }

  pid = fork();
  if (-1 == pid)
    {
      status = -1;
    }
  else if (0 == pid)
    {
      sigaction(SIGINT, &intr, NULL);
      sigaction(SIGQUIT, &quit, NULL);
      sigprocmask(SIG_SETMASK, &savemask, NULL);

      execl("/bin/sh", "sh", "-c", command, (char *) 0);
      _exit(127);
    }
  else
    {
      while (-1 == waitpid(pid, &status, 0))
        {
          if (errno != EINTR)
            {
              status = -1;
              break;
            }
        }
    }

  if (-1 == sigaction(SIGINT, &intr, NULL))
    {
      return -1;
    }

  if (-1 == sigaction(SIGQUIT, &quit, NULL))
    {
      return -1;
    }

  return status;
}
