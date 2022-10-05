#include <_io_.h>

/*
 * 1. `mkdir'
 *
 */

int
main(int argc, char **argv)
{
  int  fd;

  if (argc < 2)
    {
      printf("usage <pathname> [dir...]\n");
      exit(EXIT_SUCCESS);
    }

  fd = open(argv[1], O_RDONLY);
  if (fd == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  for (int i = 2; i < argc; i++)
    {
      if (mkdirat(fd, argv[i], 0755) == -1)
        {
          perror(NULL);
          continue;
        }
    }


  exit(EXIT_SUCCESS);

}
