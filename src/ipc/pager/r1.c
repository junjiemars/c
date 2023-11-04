#include "_ipc_.h"


int
paging (const char *pathname, const char *pager)
{
  FILE   *fp;
  int     fd[2];
  pid_t   pid;

  if ((fp = fopen (pathname, "r")) == NULL)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }

  if (pipe (fd) == -1)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }

  if ((pid = fork ()) == -1)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }
  else if (pid > 0)
    {
      char     line[NM_LINE_MAX], *linep;
      size_t   linecap  =  NM_LINE_MAX;
      ssize_t  n;

      close (fd[0]);

      linep = &line[0];

      while ((n = getline (&linep, &linecap, fp)) > 0)
        {
          if (write (fd[1], line, n) != n)
            {
              if (errno)
                {
                  perror (NULL);
                }
              exit (EXIT_FAILURE);
            }
        }

      if (ferror (fp))
        {
          perror (NULL);
          exit (EXIT_FAILURE);
        }

      close (fd[1]);

      if (waitpid (pid, NULL, 0) == -1)
        {
          perror (NULL);
          exit (EXIT_FAILURE);
        }
    }
  else
    {
      char  *pager_name;

      close (fd[1]);

      if (fd[0] != STDIN_FILENO)
        {
          if (dup2 (fd[0], STDIN_FILENO) != STDIN_FILENO)
            {
              perror (NULL);
              exit (EXIT_FAILURE);
            }
          close (fd[0]);
        }

      if ((pager_name = strrchr (pager, '/')) != NULL)
        {
          pager_name++;
        }

      if (execl (pager, pager_name, 0) == -1)
        {
          perror (NULL);
          exit (EXIT_FAILURE);
        }
    }

  return 0;
}
