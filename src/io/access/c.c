#include "_io_.h"


#define ON   1
#define OFF  0

int cntl_fl(int fd, int flags, int on);


int
main(int argc, char **argv)
{
  int  rc;
  int  fd;

  if (argc < 2)
    {
      fprintf(stderr, "usage: %s <pathname>\n", basename(argv[1]));
      exit(EXIT_FAILURE);
    }

  fd = open(argv[1], O_RDONLY | O_CREAT | O_NONBLOCK, S_IRUSR | S_IWUSR);
  if (fd == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  if (cntl_fl(fd, O_NONBLOCK, OFF) == -1)
  {
    fprintf(stderr, "!panic: turn O_NONBLOCK off failed\n");
    exit(EXIT_FAILURE);
  }

  if (cntl_fl(fd, O_APPEND, ON) == -1)
    {
      fprintf(stderr, "!panic: turn O_APPEND on failed\n");
      exit(EXIT_FAILURE);
    }

  rc = fcntl(fd, F_GETFL);
  if (rc == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  assert((rc & O_NONBLOCK) != O_NONBLOCK);
  assert((rc & O_APPEND) == O_APPEND);

  exit(EXIT_SUCCESS);

}


int
cntl_fl(int fd, int flags, int on)
{
  int  fl, rc;

  fl = fcntl(fd, F_GETFL);
  if (fl == -1)
    {
      return -1;
    }

  if (on)
    {
      fl |= flags;
    }
  else
    {
      fl &= ~flags;
    }

  rc = fcntl(fd, F_SETFL, fl);
  if (rc == -1)
    {
      return -1;
    }

  return 0;
}