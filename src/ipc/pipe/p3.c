#include <_ipc_.h>
#include <string.h>

#define _TXT_ "hello pipe\n"

int
main (void)
{
  ssize_t n;
  int fildes1[2], fildes2[2];
  pid_t pid;
  char line[PIPE_BUF];

  if (pipe (fildes1) == -1)
    {
      perror (0);
      exit (1);
    }

  if ((pid = fork ()) == -1)
    {
      perror (0);
      exit (1);
    }
  else if (pid > 0)
    {
      close (fildes1[0]);
      write (fildes1[1], _TXT_, sizeof (_TXT_) - 1);
      waitpid (pid, NULL, 0);
    }
  else
    {
      close (fildes1[1]);

      if (pipe (fildes2) == -1)
        {
          perror (NULL);
          exit (1);
        }

      if ((pid = fork ()) == -1)
        {
          perror (NULL);
          exit (1);
        }
      else if (pid > 0)
        {
          close (fildes2[0]);
          n = snprintf (line, PIPE_BUF,
                        "%zi received from %zi: ", (size_t)getpid (),
                        (size_t)getppid ());
          n += read (fildes1[0], line + n, PIPE_BUF);
          write (fildes2[1], line, n);
        }
      else
        {
          close (fildes2[1]);
          n = snprintf (line, PIPE_BUF,
                        "%zi received from %zi: ", (size_t)getpid (),
                        (size_t)getppid ());
          n += read (fildes2[0], line + n, PIPE_BUF);
          write (STDOUT_FILENO, line, n);
        }
    }

  exit (0);
}
