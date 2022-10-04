#include <_io_.h>

int
main(int argc, char **argv)
{
  struct timespec  ts[2];

  if (argc < 2)
    {
      fprintf(stderr, "usage: <pathname>\n");
      exit(EXIT_FAILURE);
    }

  ts[0].tv_sec = 1;
  ts[1].tv_sec = 2;

  if (utimensat(AT_FDCWD, argv[1], ts, AT_SYMLINK_NOFOLLOW) == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  exit(EXIT_SUCCESS);
}
