#include "_io_.h"

/*
 * 1. Access devices with the same syntax as accessing regular files.
 * 2. Access permissions also same for devices and regular files.
 */

#define BUF_SMALL 8
static char buf_small[BUF_SMALL];

int
main (int argc, char **argv)
{
  int n;
  int fd;

  if (argc < 2)
    {
      fprintf (stderr, "usage: <device>\n");
      exit (EXIT_FAILURE);
    }

  if ((fd = open (argv[1], O_RDONLY)) == -1)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }

  if ((n = read (fd, buf_small, BUF_SMALL)) < 0)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }

  if (write (STDOUT_FILENO, buf_small, n) != n)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }
  write (STDOUT_FILENO, "\n", sizeof ("\n") - 1);

  exit (EXIT_SUCCESS);
}
