#include "_io_.h"

/*
 * This non-blocking is saided to be pulling.
 *
 */


static char  buf[4096*20];


int
main(void)
{
  ssize_t   nr, nw;
  char     *pbuf;
  int       flags;

  flags = fcntl(STDOUT_FILENO, F_GETFL);
  if (flags == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  if (fcntl(STDOUT_FILENO, F_SETFL, flags | O_NONBLOCK) == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  nr = read(STDIN_FILENO, buf, _nof_(buf));
  if (nr == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  fprintf(stderr, "read  = %zd\n", nr);

  pbuf = buf;

  while (nr > 0)
    {
      errno = 0;
      nw = write(STDOUT_FILENO, pbuf, nr);

      fprintf(stderr, "wrote = %zd, errno = %d\n", nw, errno);

      if (nw > 0)
        {
          pbuf += nw;
          nr -= nw;
        }
    }

  if (fcntl(STDOUT_FILENO, F_SETFL, flags) == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  exit(EXIT_SUCCESS);
}
