#include <_ipc_.h>
#include <string.h>

#define _TXT_ "hello pipe"

int
main (void)
{
  ssize_t n;
  int fd[2];
  pid_t pid;
  char line[NM_LINE_MAX];

  if (pipe (fd) == -1)
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
      close (fd[0]); /* close read fd */
      write (fd[1], _TXT_, sizeof (_TXT_) - 1);
      waitpid (pid, NULL, 0);
    }
  else
    {
      close (fd[1]); /* close write fd */
      n = snprintf (line, NM_LINE_MAX,
                    "%zi received from %zi: ", (size_t)getpid (),
                    (size_t)getppid ());
      n += read (fd[0], line + n, NM_LINE_MAX);
      write (STDOUT_FILENO, line, n);
    }

  exit (0);
}
