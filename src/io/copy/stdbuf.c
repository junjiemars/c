#include "_io_.h"

/*
 * Copy stdin to stdout using standard buffering IO.
 *
 */


#define BUFSIZE  64


int
main(void)
{
  size_t  n;
  char    buf[BUFSIZE];

  while ((n = fread(buf, sizeof(*buf), BUFSIZE/sizeof(*buf), stdin)) > 0)
    {
      if (fwrite(buf, sizeof(*buf), n, stdout) != n)
        {
          perror(NULL);
          exit(EXIT_FAILURE);
        }
    }

  if (ferror(stdin))
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  exit(EXIT_SUCCESS);
}
