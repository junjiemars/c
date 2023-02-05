#include "_ipc_.h"

#if !defined(DEF_PAGER)
#  define DEF_PAGER  "/usr/bin/more"
#endif  /* DEF_PAGER */


int
main(int argc, char *argv[])
{
  FILE   *fp;
  int     fd[2];
  pid_t   pid;

  if (argc < 2)
    {
      fprintf(stderr, "usage: %s <pathname>\n", argv[0]);
      exit(EXIT_FAILURE);
    }

  if ((fp = fopen(argv[1], "r")) == NULL)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  if (pipe(fd) == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  if ((pid = fork()) == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  else if (pid > 0)
    {
      char     line[NM_LINE_MAX], *linep;
      size_t   linecap  =  NM_LINE_MAX;
      ssize_t  n;

      close(fd[0]);

      linep = &line[0];

      while ((n = getline(&linep, &linecap, fp)) > 0)
        {
          if (write(fd[1], line, n) != n)
            {
              if (errno)
                {
                  perror(NULL);
                }
              exit(EXIT_FAILURE);
            }
        }

      if (ferror(fp))
        {
          perror(NULL);
          exit(EXIT_FAILURE);
        }

      close(fd[1]);

      if (waitpid(pid, NULL, 0) == -1)
        {
          perror(NULL);
          exit(EXIT_FAILURE);
        }
    }
  else
    {
      char  *pager;
      char  *pager_name;

      close(fd[1]);

      if (fd[0] != STDIN_FILENO)
        {
          if (dup2(fd[0], STDIN_FILENO) != STDIN_FILENO)
            {
              perror(NULL);
              exit(EXIT_FAILURE);
            }
          close(fd[0]);
        }

      if ((pager = getenv("PAGER")) == NULL)
        {
          pager = DEF_PAGER;
        }

      if ((pager_name = strrchr(pager, '/')) != NULL)
        {
          pager_name++;
        }

      if (execl(pager, pager_name, 0) == -1)
        {
          perror(NULL);
          exit(EXIT_FAILURE);
        }
    }

  exit(EXIT_SUCCESS);
}
