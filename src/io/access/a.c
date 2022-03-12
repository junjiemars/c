#include "_io_.h"
#include <errno.h>


/*
 * https://pubs.opengroup.org/onlinepubs/9699919799/functions/access.html
 *
 */


int
main(int argc, char **argv)
{
  int    rc;
  uid_t  uid, euid;

  uid = getuid();
  euid = geteuid();

  printf("uid: %i, euid: %i\n------------\n", uid, euid);

  for (int i = 1; i < argc; i++)
    {
      rc = access(argv[i], R_OK);
      if (rc == -1)
        {
          printf("access error@%s: %s\n", argv[1], strerror(errno));
        }
      else
        {
          printf("read access@%s: ok\n", argv[i]);
        }

      rc = open(argv[1], O_RDONLY);
      if (rc == -1)
        {
          printf("read error@%s: %s\n", argv[1], strerror(errno));
        }
      else
        {
          printf("open for read@%s: ok\n", argv[1]);
        }

    }

  exit(EXIT_SUCCESS);
}
