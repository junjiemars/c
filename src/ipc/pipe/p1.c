#include "_ipc_.h"

#define _TXT_ "hello pipe\n"

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
      exit (EXIT_FAILURE);
    }

  if ((pid = fork ()) == -1)
    {
      perror (0);
      exit (EXIT_FAILURE);
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
      n = read (fd[0], line, NM_LINE_MAX);
      write (STDOUT_FILENO, line, n);
    }

  exit (EXIT_SUCCESS);
}
