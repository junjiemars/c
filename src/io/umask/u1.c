#include "_io_.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <libgen.h>


/*
 * 1. The default file mode creation mask: 666 for file, 777 for directory
 * 2. Any bits that are in the file mode creation mask are turn off
 *    in the file's mode.
 * 3. The symbolic format of umask command specifies which permission
 *    are to be turn on.
 * 4. New file permissions: 666 & ~(umask)
 * 5. New directory permissions: 777 & ~(umask)
 */

#define RWRWRW (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)

int
main(int argc, char **argv)
{
  int   rc;
  char  name_buf[PATH_MAX];

  if (argc < 2)
    {
      fprintf(stderr, "usage: %s <prefix>\n", basename(argv[0]));
      exit(EXIT_FAILURE);
    }

  sprintf(name_buf, "%s/foo", argv[1]);
  umask(0);
  rc = creat(name_buf, RWRWRW);
  if (rc == -1)
    {
      perror("!panic");
      exit(EXIT_FAILURE);
    }

  sprintf(name_buf, "%s/bar", argv[1]);
  umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
  rc = creat(name_buf, RWRWRW);
  if (rc == -1)
    {
      perror("!panic");
      exit(EXIT_FAILURE);
    }

  exit(EXIT_SUCCESS);
}
