#include <_io_.h>

/*
 * 1. Make a hard link.
 *
 * 2. Because hard links can cause loops in the file system, so hard
 * links to directories is restricted to only the superuser.
 *
 */

int
main(int argc, char **argv)
{
  if (argc < 3)
    {
      fprintf(stderr, "usage: <existing> <link>\n");
      exit(EXIT_FAILURE);
    }

  if (linkat(AT_FDCWD, argv[1], AT_FDCWD, argv[2], AT_SYMLINK_FOLLOW) == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  exit(EXIT_SUCCESS);
}
