#include "_io_.h"


int
main(int argc, char **argv)
{
  int              rc;
  struct timespec  ts[2] = {0};

  if (argc < 2)
    {
      fprintf(stderr, "usage: <pathname>\n");
      exit(EXIT_FAILURE);
    }

  ts[0].tv_sec = 1;
  ts[1].tv_sec = 2;
  ts[1].tv_nsec = UTIME_OMIT;

  rc = utimensat(AT_FDCWD, argv[1], ts, AT_SYMLINK_NOFOLLOW);
  if (rc == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  exit(EXIT_SUCCESS);
}
