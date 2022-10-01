#include <_io_.h>

/*
 * 1. F_DUPFD/F_DUPFD_CLOEXEC: returns the lowest-numbered descriptor
 * that is not already open, and that is greater or equal to the third
 * argument.
 *
 * 2. F_DUPFD_CLOEXEC: turns on.
 *
 */

static int   next_fd  =  10;
static char  buf[BUFSIZ];

int
main(void)
{
  int  n;
  int  fd_in, fd_out;
  int  fd_flags;

  fd_in = fcntl(STDIN_FILENO, F_DUPFD, next_fd);
  if (fd_in == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  assert(fd_in >= next_fd);

  fd_flags = fcntl(fd_in, F_GETFD);
  if (fd_flags == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  assert((fd_flags & FD_CLOEXEC) == 0);


  fd_out = fcntl(STDOUT_FILENO, F_DUPFD_CLOEXEC, next_fd);
  if (fd_out == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  assert(fd_out >= next_fd);

  fd_flags = fcntl(fd_out, F_GETFD);
  if (fd_flags == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  assert((fd_flags & FD_CLOEXEC) == FD_CLOEXEC);


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
