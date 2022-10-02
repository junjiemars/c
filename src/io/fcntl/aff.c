#include <_io_.h>

/*
 * 1. fcntl(fd, F_SETFD) just affects the fd entry.
 *
 * 2. fcntl(fd, F_SETFL) affects the file table entry.
 *
 */

#define ON   0
#define OFF  1

static int turn_fd_flags(int, int, int);
static int has_fd_flags(int, int);

static int turn_file_flags(int, int, int);
static int has_file_flags(int, int);

int
main(int argc, char **argv)
{

  int  fd1, fd2, fd3;

  if (argc < 2)
    {
      fprintf(stderr, "usage: <path>\n");
      exit(EXIT_FAILURE);
    }

  fd1 = open(argv[1], O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR);
  fd2 = dup(fd1);
  fd3 = open(argv[1], O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR);

  assert(0 == turn_fd_flags(fd1, FD_CLOEXEC, ON));
  assert(FD_CLOEXEC == has_fd_flags(fd1, FD_CLOEXEC));
  assert(0 == has_fd_flags(fd2, FD_CLOEXEC));
  assert(0 == has_fd_flags(fd3, FD_CLOEXEC));

  assert(0 == turn_file_flags(fd1, O_NONBLOCK, ON));
  assert(O_NONBLOCK == has_file_flags(fd1, O_NONBLOCK));
  assert(O_NONBLOCK == has_file_flags(fd2, O_NONBLOCK));
  assert(0 == has_file_flags(fd3, O_NONBLOCK));

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

  if (fcntl(fd, F_SETFD, fd_flags) == -1)
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
      return flags;
    }

  return 0;
}

int
turn_file_flags(int fd, int flags, int off)
{
  int  file_flags;

  file_flags = fcntl(fd, F_GETFL);
  if (file_flags == -1)
    {
      return -1;
    }

  if (off == OFF)
    {
      file_flags &= ~flags;
    }
  else
    {
      file_flags |= flags;
    }

  if (fcntl(fd, F_SETFL, file_flags) == -1)
    {
      return -1;
    }

  return 0;
}

int
has_file_flags(int fd, int flags)
{
  int  file_flags;

  file_flags = fcntl(fd, F_GETFL);
  if (file_flags == -1)
    {
      return -1;
    }

  if ((file_flags & flags) == flags)
    {
      return flags;
    }

  return 0;
}
