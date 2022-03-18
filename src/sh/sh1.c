#include "_sh_.h"
#include <sys/wait.h>


#define MAXLINE 64

int
main(void)
{
  size_t  n;
  pid_t   pid;
  int     status;
  char    buf[MAXLINE];

  /* shell prompt */
  printf("%% ");

  while (fgets(buf, MAXLINE, stdin) != NULL)
    {
      n = strnlen(buf, MAXLINE);
      if (buf[n-1] == '\n')
        {
          buf[n-1] = 0;
        }

      pid = fork();
      if (pid == -1)
        {
          perror(NULL);
          exit(EXIT_FAILURE);
        }
      else if (pid == 0)
        {
          execlp(buf, buf, (char *) 0);

          fprintf(stderr, "couldn't execute %s\n", buf);
          exit(EXIT_FAILURE);
        }

      if (waitpid(pid, &status, 0) == -1)
        {
          perror(NULL);
          exit(EXIT_FAILURE);
        }

      /* shell prompt */
      printf("%% ");
    }

  exit(EXIT_SUCCESS);
}
