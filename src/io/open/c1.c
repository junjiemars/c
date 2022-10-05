#include <_io_.h>

/*
 * 1. If the file exists, `creat' diffs with open(path, O_CREAT,...).
 *
 * 2. If the file exists you cann't change its mode via `creat'.
 *
 */

int
main(int argc, char **argv)
{
  int  fd;

  if (argc < 2)
    {
      fprintf(stderr, "usage: <filename>\n");
      exit(EXIT_FAILURE);
    }

  fd = creat(argv[1], 0644);
  if (fd == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  exit(EXIT_SUCCESS);
}
