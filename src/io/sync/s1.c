#include "_io_.h"
#include <time.h>

/*
 * 1. Tranditional implementations of the UNIX system have a buffer
 * cache or page cache in the kernel through which most disk I/O
 * passes.
 *
 *
 */

extern void copy_block_sync(int, int);
extern void copy_block_nsync(int, int);


#if defined(_SYNC_)
#  define copy_block  copy_block_sync
#  define ELAPSED  "sync"
#else
#  define copy_block  copy_block_nsync
#  define ELAPSED  "non"
#endif




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

  _times_(copy_block(fd_src, fd_dst), rs, us, ss);
  printf("elapsed(%s) real: %7.2fs, user: %7.2fs, sys: %7.2fs\n",
         ELAPSED, rs, us, ss);

#else
  double elapsed;

  _time_(copy_block(fd_src, fd_dst), elapsed);
  printf("elapsed(%s): %16lfs\n", ELAPSED, elapsed);

#endif


  exit(EXIT_SUCCESS);
}
