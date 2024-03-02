#include "_io_.h"

/*
 * directory manipulation
 */

int
main (int argc, char **argv)
{
  int fd, fd1, fdr;

  if (argc < 2)
    {
      printf ("usage: <path>\n");
      exit (EXIT_SUCCESS);
    }

  fd = open (argv[1], O_RDONLY);
  if (fd == -1)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }
  fd1 = openat (fd, "r1.c", O_RDONLY);
  if (fd1 == -1)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }

  if (fchdir (fd) == -1)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }

  fdr = openat (AT_FDCWD, "r1.c", O_RDONLY);
  if (fdr == -1)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }

  exit (EXIT_SUCCESS);
}
