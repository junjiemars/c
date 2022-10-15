#include <_io_.h>

/*
 * `openat'
 *
 */

static char  buf[BUFSIZ];


int
main(int argc, char **argv)
{
  int  fd;

  if (argc < 2)
    {
      fprintf(stderr, "usage: <pathname>\n");
      exit(EXIT_FAILURE);
    }

  fd = openat(AT_FDCWD, argv[1], O_RDONLY | O_DIRECTORY);
  if (fd == -1)
    {
      perror("openat");
      exit(EXIT_FAILURE);
    }

  if (read(fd, buf, BUFSIZ) == -1)
    {
      perror("read");
      exit(EXIT_FAILURE);
    }

  exit(EXIT_SUCCESS);
}
