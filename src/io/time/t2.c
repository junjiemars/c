#include <_io_.h>

int
main(int argc, char **argv)
{
  int              fd;
  struct stat      ss;
  struct timespec  ts[2]  =  {0};

  if (argc < 2)
    {
      fprintf(stderr, "usage: <pathname>\n");
      exit(EXIT_FAILURE);
    }

  if (lstat(argv[1], &ss) == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  fd = open(argv[1], O_RDWR | O_TRUNC, 0);
  if (fd == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  ts[0].tv_sec = ss.st_atime;
  ts[1].tv_sec = ss.st_mtime;

  if (futimens(fd, ts) == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }


  exit(EXIT_SUCCESS);
}
