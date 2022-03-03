#include "_io_.h"
#include <errno.h>

/*
 * 1. It's unseekable when fd point to a pipe, FIFO, or socket.
 *
 */


int
main(void)
{
  off_t  rc;

  rc = lseek(STDIN_FILENO, 0, SEEK_CUR);
  if (rc == -1)
    {
      perror("!panic");
    }

  return 0;
}
