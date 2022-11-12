#include "_io_.h"
#include <time.h>

/*
 * readv/writev more faster than read/write.
 *
 */

#define BUF_FACTOR  4
#define BLK_SIZE    4096
#define BUF_SIZE    (BUF_FACTOR * BLK_SIZE)


static char  buf[BUF_SIZE];

static void  copy_block_iov(int src, int dst);


int
main(int argc, char **argv)
{
  int     fd_src, fd_dst;
  double  elapsed  =  0;

  if (argc < 3)
    {
      fprintf(stderr, "usage: <src> <dst>\n");
      exit(EXIT_FAILURE);
    }

  fd_src = open(argv[1], O_RDONLY);
  if (fd_src == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  fd_dst = open(argv[2], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
  if (fd_dst == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  _time_(copy_block_iov(fd_src, fd_dst), elapsed);

  printf("elapsed(non sync, iov): %16lfs\n", elapsed);



  exit(EXIT_SUCCESS);
}

void
copy_block_iov(int src, int dst)
{
  ssize_t       r, w;
  struct iovec  iov[BUF_FACTOR];

  for (int i = 0; i < BUF_FACTOR; i++)
    {
      iov[i].iov_base = &buf[i * BLK_SIZE];
      iov[i].iov_len = BLK_SIZE;
    }

  while ((r = readv(src, iov, BUF_FACTOR)) > 0)
    {
      int  m  =  (r % BLK_SIZE);
      int  c  =  (r + BLK_SIZE - 1) / BLK_SIZE;

      if (m > 0)
        {
          iov[c-1].iov_len = m;
        }

      w = writev(dst, iov, c);
      while (w != r)
        {
          perror(NULL);
          exit(EXIT_FAILURE);
        }
    }

  if (r == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

}
