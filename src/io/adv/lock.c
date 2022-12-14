#include "_io_.h"

static int  try_lock(int, int, int, off_t, off_t, int);

int
main(void)
{
  int           fd;
  struct flock  lock;

  fd = STDIN_FILENO;
  lock.l_type = F_RDLCK;
  lock.l_start = 16;
  lock.l_len = 64;
  lock.l_whence = SEEK_SET;

  if (fcntl(fd, F_GETLK, &lock) == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  if (F_UNLCK == lock.l_type)
    {
      /* F_GETLK and F_SETLK is not automic */
      if (try_lock(fd, F_SETLK, F_RDLCK, 16, 64, SEEK_SET) == -1)
        {
          perror(NULL);
          exit(EXIT_FAILURE);
        }
    }

  exit(EXIT_SUCCESS);
}

int
try_lock(int fd, int cmd, int type, off_t start, off_t len, int whence)
{
  struct flock  lock;

  lock.l_type = type;
  lock.l_start = start;
  lock.l_len = len;
  lock.l_whence = whence;

  return fcntl(fd, cmd, &lock);
}
