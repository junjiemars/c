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
  int      flag;
  ssize_t  n  =  sizeof(ALPHA_L10)-1;

  if (write(STDOUT_FILENO, ALPHA_L10, n) != n)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  /* try to set O_SYNC */
  flag = fcntl(STDOUT_FILENO, F_GETFL);
  if (flag == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  flag |= O_SYNC;
  flag = fcntl(STDOUT_FILENO, F_SETFL, flag);
  if (flag == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  flag = fcntl(STDOUT_FILENO, F_GETFL);
  if (flag == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  /* on Linux, O_SYNC via F_SETFL be ignored  */
  if ((flag & O_SYNC) == O_SYNC)
    {
      if (fsync(STDOUT_FILENO) == -1)
        {
          perror(NULL);
          exit(EXIT_FAILURE);
        }
    }

  exit(EXIT_SUCCESS);
}
