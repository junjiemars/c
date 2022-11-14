#include "_io_.h"
#include <time.h>

/*
 * readv/writev more faster than read/write.
 *
 */

#define BUF_FACTOR  4
/* #define BLK_SIZE    4096 */
#define BUF_SIZE    (BUF_FACTOR * BLK_SIZE)


static char  buf[BUF_SIZE];

static void  copy_block_iov(int src, int dst);


int
main(int argc, char **argv)
{
  int     fd_src, fd_dst;

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

#if defined(_times_)
  double rs, us, ss;

  _times_(copy_block_iov(fd_src, fd_dst), rs, us, ss);
  printf("elapsed(iov) real: %7.2fs, user: %7.2fs, sys: %7.2fs\n",
         rs, us, ss);

#else
  double elapsed;

  _time_(copy_block_iov(fd_src, fd_dst), elapsed);
  printf("elapsed(iov): %16lfs\n", elapsed);

#endif

  exit(EXIT_SUCCESS);
}

void
copy_block_iov(int src, int dst)
{
  ssize_t       n;
  struct iovec  iov[BUF_FACTOR];

  for (int i = 0; i < BUF_FACTOR; i++)
    {
      iov[i].iov_base = &buf[i * BLK_SIZE];
      iov[i].iov_len = BLK_SIZE;
    }

  while ((n = readv(src, iov, BUF_FACTOR)) > 0)
    {
      int  m  =  (n % BLK_SIZE);
      int  c  =  (n + BLK_SIZE - 1) / BLK_SIZE;

      if (m > 0)
        {
          iov[c-1].iov_len = m;
        }

      if (writev(dst, iov, c) != n)
        {
          perror(NULL);
          exit(EXIT_FAILURE);
        }
    }

  if (n == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

}
