#include "_io_.h"

/*
 * Copy stdin to stdout using standard buffering IO.
 *
 */


static char  buf[BUFSIZ];


int
main(void)
{
  size_t  n;

  while ((n = fread(buf, sizeof(*buf), BUFSIZ, stdin)) > 0)
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
