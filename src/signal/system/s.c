#include "_signal_.h"

/*
 * emulate `system(3)'.
 *
 *
 */


int
system(const char *command)
{
  int               status;
  pid_t             pid;
  sigset_t          chldmask, savemask;
  struct sigaction  ignore, saveintr, savequit;

  if (NULL == command)
    {
      return 1;
    }

  ignore.sa_handler = SIG_IGN;
  sigemptyset(&ignore.sa_mask);
  ignore.sa_flags = 0;

  if (-1 == sigaction(SIGINT, &ignore, &saveintr))
    {
      return -1;
    }

  if (-1 == sigaction(SIGQUIT, &ignore, &savequit))
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
      sigaction(SIGINT, &saveintr, NULL);
      sigaction(SIGQUIT, &savequit, NULL);
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

  if (-1 == sigaction(SIGINT, &saveintr, NULL))
    {
      return -1;
    }

  if (-1 == sigaction(SIGQUIT, &savequit, NULL))
    {
      return -1;
    }

  return status;
}
