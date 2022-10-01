#include <_io_.h>

/*
 * close(fd) just remove the fd's entry from the process table.
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

  close(STDOUT_FILENO);

  if (write(fd, ALPHA_L, _nof_(ALPHA_L)-1) != _nof_(ALPHA_L)-1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }


  exit(EXIT_SUCCESS);
}
