#include "_term_.h"
#include "ptys.h"
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>

int
pty_open_master (char *name, size_t namesz)
{
  int fd;
  int rc;

  if ((fd = posix_openpt (O_RDWR)) < 0)
    {
      return -1;
    }

  if (grantpt (fd) < 0)
    {
      goto clean_exit;
    }

  if (unlockpt (fd) < 0)
    {
      goto clean_exit;
    }

#if (NM_HAVE_PTSNAME_R)
  char ss[_POSIX_PATH_MAX];
  if (ptsname_r (fd, ss, _POSIX_PATH_MAX) == -1)
    {
      goto clean_exit;
    }
#else
  char *ss;
  if ((ss = ptsname (fd)) == NULL)
    {
      goto clean_exit;
    }
#endif
  strncpy (name, ss, namesz);
  name[namesz - 1] = '\0';

  return fd;

clean_exit:
  rc = errno;
  close (fd);
  errno = rc;
  return -1;
}

int
pty_open_slave (char *name)
{
  int fd;

  if ((fd = open (name, O_RDWR)) < 0)
    {
      return -1;
    }

  return fd;
}

pid_t
pty_fork (int *fdp, char *name, size_t namesz)
{
  int fdm, fds;
  char ss[_POSIX_PATH_MAX];
  pid_t pid;

  if ((fdm = pty_open_master (ss, _POSIX_PATH_MAX)) < 0)
    {
      return -1;
    }
  strncpy (name, ss, namesz);
  name[namesz - 1] = '\0';

  if ((pid = fork ()) < 0)
    {
      return -1;
    }
  else if (pid == 0) /* child */
    {
      if (setsid () < 0)
        {
          return -1;
        }
      if ((fds = pty_open_slave (name)) < 0)
        {
          return -1;
        }
      close (fdm);

      if (ioctl (fds, TIOCSCTTY, (char *)0) < 0)
        {
          return -1;
        }

      if (dup2 (fds, STDIN_FILENO) != STDIN_FILENO)
        {
          return -1;
        }
      if (dup2 (fds, STDOUT_FILENO) != STDOUT_FILENO)
        {
          return -1;
        }
      if (dup2 (fds, STDERR_FILENO) != STDERR_FILENO)
        {
          return -1;
        }

      if (fds != STDIN_FILENO && fds != STDOUT_FILENO && fds != STDERR_FILENO)
        {
          close (fds);
        }

      return 0;
    }
  else /* parent */
    {
      *fdp = fdm;
      return pid;
    }
}
