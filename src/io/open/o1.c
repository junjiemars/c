#include <_io_.h>


int
main(int argc, char **argv)
{
  int fd;

  if (argc > 1)
    {
      fd = openat(AT_FDCWD, argv[1], O_RDONLY);
    }

  exit(EXIT_SUCCESS);
}
