#include "_ld_.h"

/*
 * 1. Using `exit' instead of  using `return'.
 *
 * 2. Can't get `argc' and `argv' when compile with `-nostartfiles'.
 *
 * 3. Can access `environ'.
 *
 * 4. Access `fprintf' on Linux failed.
 *
 */

extern char  **environ;

static char  BUF[NM_LINE_MAX];


int
_main1(void)
{
  size_t   n;
  ssize_t  rc;

  n = strlen(environ[0]);
  memcpy(BUF, environ[0], n);
  BUF[n++] = '\n';
  BUF[n++] = '\0';

  rc = write(STDOUT_FILENO, BUF, n-1);
  if (rc == -1)
    {
      exit(EXIT_FAILURE);
    }


  exit(EXIT_SUCCESS);
}
