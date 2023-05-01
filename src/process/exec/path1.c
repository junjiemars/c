#include "_process_.h"
#include <stdlib.h>

int
main (int argc, char *argv[])
{
  pid_t pid;
  char *bin, *name;
  char *exec_fn = "execl";

  if (argc < 2)
    {
      fprintf (stderr, "usage: %s <path> [execl|execlp]\n", argv[0]);
      exit (EXIT_FAILURE);
    }
  bin = argv[1];
  name = strrchr (bin, '/') + 1;
  if (argc > 2)
    {
      exec_fn = argv[2];
    }

  if ((pid = fork ()) == -1)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }
  else if (pid == 0)
    {
      int rc = 0;

      if (strcmp (exec_fn, "execl") == 0)
        {
          rc = execl (bin, name, "a1", "a2", (char *)0);
        }
      else if (strcmp (exec_fn, "execlp") == 0)
        {
          rc = execlp (name, name, "b1", "b2", (char *)0);
        }

      if (rc < 0)
        {
          perror (NULL);
        }
      exit (rc);
    }

  if (waitpid (pid, NULL, 0) == -1)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }

  exit (EXIT_SUCCESS);
}
