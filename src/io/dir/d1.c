#include "_io_.h"

int
main (int argc, char **argv)
{
  DIR *dir;
  struct dirent *ent;

  if (argc < 2)
    {
      fprintf (stderr, "usage: %s <dir>\n", argv[0]);
      exit (EXIT_FAILURE);
    }

  dir = opendir (argv[1]);
  if (dir == NULL)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }

  while ((ent = readdir (dir)) != NULL)
    {
      long loc = telldir (dir);
      printf ("#%07ld: %s\n", loc, ent->d_name);
    }

  closedir (dir);

  exit (EXIT_SUCCESS);
}
