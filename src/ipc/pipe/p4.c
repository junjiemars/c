#include <_ipc_.h>
#include <string.h>

#define _PAGER_ "/usr/bin/less"

int
main (int argc, char **argv)
{
  int fildes[2];
  pid_t pid;
  char buf[PIPE_BUF];
  FILE *fp;
  char *pathname, *pager, *pager_argv0;
  size_t nread;

  if (argc < 2)
    {
      fprintf (stderr, "usage: %s <pathname>\n", argv[0]);
      exit (1);
    }
  pathname = argv[1];

  if (pipe (fildes) == -1)
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
      close (fildes[0]);
      if ((fp = fopen (pathname, "r")) == NULL)
        {
          perror (NULL);
          exit (1);
        }
      while ((nread = fread (buf, sizeof (char), PIPE_BUF, fp)) > 0)
        {
          write (fildes[1], buf, nread);
        }
      if (ferror (fp))
        {
          fprintf (stderr, "fread error\n");
        }
      close (fildes[1]);
      waitpid (pid, NULL, 0);
    }
  else
    {
      close (fildes[1]);
      if (dup2 (fildes[0], STDIN_FILENO) != STDIN_FILENO)
        {
          fprintf (stderr, "dup2 stdin error\n");
          exit (1);
        }
      close (fildes[0]);
      if ((pager = getenv ("PAGER")) == NULL)
        {
          pager = _PAGER_;
        }
      if ((pager_argv0 = strrchr (pager, '/')) != NULL)
        {
          pager_argv0++;
        }
      else
        {
          pager_argv0 = pager;
        }
      if (execl (pager, pager_argv0, (char *)0) == -1)
        {
          perror (NULL);
          exit (1);
        }
    }

  exit (0);
}
