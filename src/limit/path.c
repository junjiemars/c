#include "_limit_.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * NAME_MAX and PATH_MAX depend on the file system.
 *
 */


int
main(int argc, char **argv)
{
  long  rc;

  for (int i = 1; i < argc; i++)
    {
      printf("@%s\n------------\n", argv[i]);

#if defined(_PC_NAME_MAX)
      rc = pathconf(argv[i], _PC_NAME_MAX);
      if (rc == -1)
        {
          perror(argv[i]);
          continue;
        }
      printf("_PC_NAME_MAX: %li\n", rc);

#endif  /* _PC_NAME_MAX */


#if defined(_PC_PATH_MAX)

      rc = pathconf(argv[i], _PC_PATH_MAX);
      if (rc == -1)
        {
          perror(argv[i]);
          continue;
        }
      printf("_PC_PATH_MAX: %li\n", rc);

#endif  /* _PC_PATH_MAX */

    }

  _exit(EXIT_SUCCESS);
}
