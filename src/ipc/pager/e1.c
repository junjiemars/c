#include <_ipc_.h>

static pid_t *childpid = NULL;
static int maxfd = 16;

FILE *
popen (const char *command, const char *mode)
{
  int fd[2];
  pid_t pid;
  FILE *fp;

  if (!(*mode == 'r' || *mode == 'w'))
    {
      errno = EINVAL;
      return NULL;
    }

  if (childpid == NULL)
    {
      if ((childpid = calloc (maxfd, sizeof (pid_t))) == NULL)
        {
          return NULL;
        }
    }

  if (pipe (fd) == -1)
    {
      return NULL;
    }

  if (fd[0] >= maxfd || fd[1] >= maxfd)
    {
      close (fd[0]);
      close (fd[1]);

      errno = EMFILE;
      return NULL;
    }

  if ((pid = fork ()) == -1)
    {
      return NULL;
    }
  else if (pid == 0)
    {
      if (*mode == 'r')
        {
          close (fd[0]);
          if (fd[1] != STDOUT_FILENO)
            {
              dup2 (fd[1], STDOUT_FILENO);
              close (fd[1]);
            }
        }
      else
        {
          close (fd[1]);
          if (fd[0] != STDIN_FILENO)
            {
              dup2 (fd[0], STDIN_FILENO);
              close (fd[0]);
            }
        }

      for (int i = 0; i < maxfd; i++)
        {
          if (childpid[i] > 0)
            {
              close (i);
            }
        }

      execl ("/bin/sh", "sh", "-c", command, 0);

      _exit (127);
    }

  if (*mode == 'r')
    {
      close (fd[1]);
      if ((fp = fdopen (fd[0], mode)) == NULL)
        {
          return NULL;
        }
    }
  else
    {
      close (fd[0]);
      if ((fp = fdopen (fd[1], mode)) == NULL)
        {
          return NULL;
        }
    }

  childpid[fileno (fp)] = pid;

  return fp;
}

int
pclose (FILE *fp)
{
  int fd, stat;
  pid_t pid;

  if (childpid == NULL)
    {
      errno = EINVAL;
      return -1;
    }

  if ((fd = fileno (fp)) >= maxfd)
    {
      errno = EINVAL;
      return -1;
    }

  if ((pid = childpid[fd]) == 0)
    {
      errno = EINVAL;
      return -1;
    }

  childpid[fd] = 0;
  if (fclose (fp) == EOF)
    {
      return -1;
    }

  while (waitpid (pid, &stat, 0) == -1)
    {
      if (errno != EINTR)
        {
          return -1;
        }
    }

  return stat;
}
