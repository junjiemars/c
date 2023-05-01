#include "_process_.h"

int
main (int argc, char *argv[])
{
  char *dirname;
  DIR *dir;
  pid_t pid;

  if (argc < 2)
    {
      fprintf (stderr, "usage: %s <dirname>\n", argv[0]);
      exit (EXIT_FAILURE);
    }
  dirname = argv[1];

  if ((dir = opendir (dirname)) == NULL)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }

  if ((pid = fork ()) == -1)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }
  else if (pid == 0)
    {

    }

  exit (EXIT_SUCCESS);
}
