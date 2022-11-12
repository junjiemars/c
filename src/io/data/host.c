#include "_io_.h"

/*
 * gethostname(2), hostname(1).
 *
 *
 */

#if !defined(HOST_NAME_MAX)
#  define HOST_NAME_MAX  NAME_MAX
#endif

static char  host[HOST_NAME_MAX];


int
main(void)
{
  if (gethostname(host, HOST_NAME_MAX) == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  printf("hostname: %s\n", host);

  exit(EXIT_SUCCESS);
}
