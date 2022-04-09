#include "_io_.h"

/*
 * Tranditional implementations of the UNIX system have a buffer
 * cache or page cache in the kernel through which most disk I/O passes.
 *
 */

#define ALPHA_L10  "abcdefghij"


int
main(void)
{
  ssize_t  n  =  sizeof(ALPHA_L10) - 1;

  if (write(STDOUT_FILENO, ALPHA_L10, n) != n)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  if (fsync(STDOUT_FILENO) == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  exit(EXIT_SUCCESS);
}
