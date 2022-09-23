#include <_io_.h>

/*
 * NAME_MAX, PATH_MAX
 *
 */


int
main(int argc, char **argv)
{
  int fd;

  if (argc < 2)
    {
      printf("usage: <pathname>\n");
      exit(EXIT_FAILURE);
    }

  fd = openat(AT_FDCWD, argv[1], O_WRONLY);
  if (fd == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  exit(EXIT_SUCCESS);
}
