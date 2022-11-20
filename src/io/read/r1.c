#include "_io_.h"

#define BUF_SMALL  32
#define BUF_BIG    BUFSIZ

static char  buf_small[BUF_SMALL];
static char  buf_big[BUF_BIG];

int
main(void)
{
  ssize_t                          n;
  __attribute__((unused)) ssize_t  offset;
  struct stat                      ss;

  if (fstat(STDIN_FILENO, &ss) == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  offset = 0;

  n = read(STDIN_FILENO, buf_small, BUF_SMALL);
  if (n == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  offset += n;
  assert(n < ss.st_size && n == BUF_SMALL);

  n = read(STDIN_FILENO, buf_big, BUF_BIG);
  if (n == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  offset += n;
  assert((offset < ss.st_size && n == BUF_BIG)
         || (offset == ss.st_size && n < BUF_BIG));

  n = read(STDIN_FILENO, buf_small, BUF_SMALL);
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
