#include "_io_.h"

#define BUFSIZE  64

/*
 * Copy stdin to stdout.
 *
 * 1. convert file offset to disk block.
 *
 * 2. copy data from system buffer to user address.
 *
 */

int
main(void)
{
  int   n;
  char  buf[BUFSIZE];

  while ((n = read(STDIN_FILENO, buf, BUFSIZE)) > 0)
    {
      if (write(STDOUT_FILENO, buf, n) != n)
        {
          perror("!write error");
          exit(EXIT_FAILURE);
        }
    }

  if (n == -1)
    {
      perror("!read error");
      exit(EXIT_FAILURE);
    }

  exit(EXIT_SUCCESS);

}
