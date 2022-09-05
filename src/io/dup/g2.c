#include "_io_.h"

/*
 * Q1: Why the if test is need when fd great than 2?
 * A1: why?
 *
 */

int
main(int argc, char **argv)
{
  __attribute__((unused)) int fd;
  __attribute__((unused)) int fd0;
  __attribute__((unused)) int fd1;
  __attribute__((unused)) int fd2;

  if (argc < 2)
    {
      fprintf(stderr, "usage: %s <fd>\n", basename(argv[0]));
      exit(EXIT_FAILURE);
    }

  fd = atoi(argv[1]);

  fd0 = dup2(fd, 0);
  fd1 = dup2(fd, 1);
  fd2 = dup2(fd, 2);

  if (fd > 2)
    {
      close(fd);
    }

  exit(EXIT_SUCCESS);
}
