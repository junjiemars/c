#include <_io_.h>

/*
 *
 */


int
main(int argc, char **argv)
{
  int fd;

  if (argc < 2)
    {
      printf("usage: <path>\n");
      exit(EXIT_FAILURE);
    }

  fd = openat(AT_FDCWD, argv[1], O_RDONLY);
  if (fd == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  exit(EXIT_SUCCESS);
}
