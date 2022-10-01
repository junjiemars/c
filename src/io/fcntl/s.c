#include <_io_.h>

/*
 * 1. fcntl(fd, F_SETFD) just affect the fd;
 *
 * 2. fcntl(fd, F_SETFL) affect the file table.
 *
 */

#define ON   0
#define OFF  1

int
main(int argc, char **argv)
{

  int  fd, fd1, fd2, fd3, fl;

  if (argc < 2)
    {
      fprintf(stderr, "usage: <path>\n");
      exit(EXIT_FAILURE);
    }

  fd1 = open(argv[1], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
  fd2 = dup(fd1);
  fd3 = open(argv[1], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);

  assert(0 == turn_fd_flags(fd1, FD_CLOEXEC, OFF));


  exit(EXIT_SUCCESS);

}

int
turn_fd_flags(int fd, int flags, int off)
{
  int  fd_flags;

  fd_flags = fcntl(fd, F_GETFD);
  if (fd_flags == -1)
    {
      return -1;
    }

  if (off == OFF)
    {
      fd_flags &= ~flags;
    }
  else
    {
      fd_flags |= flags;
    }

  if (fcntl(fd, F_SETFD, rc) == -1)
    {
      return -1;
    }

  return 0;
}

int
has_fd_flags(int fd, int flags)
{
  int  fd_flags;

  fd_flags = fcntl(fd, F_GETFD);
  if (fd_flags == -1)
    {
      return -1;
    }

  if ((fd_flags & flags) == flags)
    {
      return 0;
    }

  return -1;
}
