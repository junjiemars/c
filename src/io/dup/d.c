#include "_io_.h"

/*
 * 1. the fd return by `dup' is guaranteed to be the lowest-numbered
 * available file descriptor.
 *
 */

static char  buf[BUFSIZ];
static __attribute__((unused)) int  next_fd  =  STDERR_FILENO;

int
main(void)
{
  int  n;
  int  fd_in, fd_out;

  fd_in = dup(STDIN_FILENO);
  if (fd_in == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  /* in Makefile redirection, there are one more fd opened */
  assert(fd_in > next_fd++);

  fd_out = dup(STDOUT_FILENO);
  if (fd_out == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  assert(fd_out > next_fd++);

  while ((n = read(fd_in, buf, BUFSIZ)) > 0)
    {
      if (write(fd_out, buf, n) != n)
        {
          perror(NULL);
          exit(EXIT_FAILURE);
        }
    }

  exit(EXIT_SUCCESS);
}
