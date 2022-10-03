#include <_io_.h>

/*
 * 1. close(fd) just remove the fd's entry from the process table.
 *
 * 2. if the fd is the last entry that points to the file table, the
 * file table also been closed.
 *
 */

#define ALPHA_L  "abc"

int
main(void)
{
  int fd;

  fd = dup(STDOUT_FILENO);
  if (fd == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  if (close(STDOUT_FILENO) == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  if (write(fd, ALPHA_L, _nof_(ALPHA_L)-1) != _nof_(ALPHA_L)-1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }


  exit(EXIT_SUCCESS);
}
