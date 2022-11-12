#include "_io_.h"

#define BUF_SMALL   32
#define BUF_BIG     BUFSIZ
#define BUF_FACTOR  2

static char  buf_small[BUF_SMALL];
static char  buf_big[BUF_BIG];

int
main(void)
{
  ssize_t       n, offset;
  struct stat   ss;
  struct iovec  iov_small[BUF_FACTOR], iov_big[BUF_FACTOR];

  if (fstat(STDIN_FILENO, &ss) == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  offset = 0;

  for (int i = 0; i < BUF_FACTOR; i++)
    {
      iov_small[i].iov_base = &buf_small[i * (BUF_SMALL/BUF_FACTOR)];
      iov_small[i].iov_len = BUF_SMALL/BUF_FACTOR;
    }

  n = readv(STDIN_FILENO, iov_small, BUF_FACTOR);
  if (n == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  offset += n;

  assert((offset < ss.st_size && n == BUF_SMALL)
         || (offset == ss.st_size && n < BUF_SMALL));

  for (int i = 0; i < BUF_FACTOR; i++)
    {
      iov_big[i].iov_base = &buf_big[i * (BUF_BIG/BUF_FACTOR)];
      iov_big[i].iov_len = BUF_BIG/BUF_FACTOR;
    }

  n = readv(STDIN_FILENO, iov_big, BUF_FACTOR);
  if (n == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  offset += n;

  assert((offset < ss.st_size && n == BUF_BIG)
         || (offset == ss.st_size && n < BUF_BIG));

  n = readv(STDIN_FILENO, iov_small, BUF_FACTOR);
  if (n == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  offset += n;

  assert((offset < ss.st_size && n == BUF_SMALL)
         || (offset == ss.st_size && n < BUF_SMALL));

  exit(EXIT_SUCCESS);
}
