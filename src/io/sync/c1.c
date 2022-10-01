#include <_io_.h>

#define BLKSIZ  4096

void copy_block(int, int);
void copy_block_sync(int, int);

static char  blk[BLKSIZ];

void
copy_block(int src, int dst)
{
  int n;

  while ((n = read(src, blk, BLKSIZ)) > 0)
    {
      if (write(dst, blk, n) != n)
        {
          perror(NULL);
          exit(EXIT_FAILURE);
        }
    }
}

void
copy_block_sync(int src, int dst)
{
  int  fl;

  fl = fcntl(dst, F_GETFL);
  if (fl == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  fl |= O_SYNC;
  if (fcntl(dst, F_SETFL, fl) == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  copy_block(src, dst);

  if (fsync(dst) == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
}
