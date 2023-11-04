#include "_ipc_.h"

static void  on_sig_pipe (int);


int
main (int argc, char *argv[])
{
  pid_t   pid;
  int     fdp[2], fdc[2];
  char   *filter, *filter_name;

  if (argc < 2)
    {
      fprintf (stderr, "usage: <filter-pathname>\n");
      exit (EXIT_FAILURE);
    }
  filter = argv[1];
  if ((filter_name = strrchr (filter, '/')) != NULL)
    {
      filter_name++;
    }

  if (signal (SIGPIPE, on_sig_pipe) == SIG_ERR)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }

  if (pipe (fdp) == -1 || pipe(fdc) == -1)
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
      close (fdp[0]);
      close (fdc[1]);

      char    line[NM_LINE_MAX];

      while (fgets (line, NM_LINE_MAX, stdin) != NULL)
        {
          size_t   nw  =  strlen (line);
          ssize_t  nr;

          if (write (fdp[1], line, nw) != (ssize_t) nw)
            {
              perror (NULL);
              exit (EXIT_FAILURE);
            }

          if ((nr = read (fdc[0], line, NM_LINE_MAX)) == -1)
            {
              perror (NULL);
              exit (EXIT_FAILURE);
            }
          if (nr == 0)
            {
              fprintf (stderr, "# child(%d) closed pipe\n", pid);
              break;
            }
          line[nr] = 0;

          if (fputs (line, stdout) == EOF)
            {
              perror (NULL);
              exit (EXIT_FAILURE);
            }
        }
    }
  else
    {
      close (fdp[1]);
      close (fdc[0]);

      if (fdp[0] != STDIN_FILENO)
        {
          if (dup2 (fdp[0], STDIN_FILENO) != STDIN_FILENO)
            {
              perror (NULL);
              exit (EXIT_FAILURE);
            }
          close (fdp[0]);
        }

      if (fdc[1] != STDOUT_FILENO)
        {
          if (dup2 (fdc[1], STDOUT_FILENO) != STDOUT_FILENO)
            {
              perror (NULL);
              exit (EXIT_FAILURE);
            }
          close (fdc[1]);
        }

      if (execl (filter, filter_name, 0) == -1)
        {
          perror (NULL);
          exit (EXIT_FAILURE);
        }
    }

  exit (EXIT_SUCCESS);
}

void
on_sig_pipe (int signo)
{
  printf ("SIGPIPE(%d) caught\n", signo);
  exit (EXIT_FAILURE);
}
