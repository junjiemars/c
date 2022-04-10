#include "_io_.h"
#include <errno.h>


/*
 * 1. access just check real-user/group-id.
 * 2. open check effective-user/group-id.
 *
 */


int
main(int argc, char **argv)
{
  int    rc;
  uid_t  uid, euid;

  if (argc < 2)
    {
      fprintf(stderr, "usage: %s <pathname> [pathname...]\n",
              basename(argv[0]));
      exit(EXIT_FAILURE);
    }

  uid = getuid();
  euid = geteuid();

  printf("uid: %i, euid: %i\n------------\n", uid, euid);

  for (int i = 1; i < argc; i++)
    {
      rc = access(argv[i], R_OK);
      if (rc == -1)
        {
          perror("!access error");
        }
      else
        {
          printf("read access OK\n");
        }

      rc = open(argv[1], O_RDONLY);
      if (rc == -1)
        {
          perror("!read error");
        }
      else
        {
          printf("open for reading OK\n");
        }

    }

  exit(EXIT_SUCCESS);
}
