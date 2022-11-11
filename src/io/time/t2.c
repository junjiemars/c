#include <_io_.h>

/*
 * Keep the access/modification time unchanged between system calls;
 *
 */

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

  memcpy(&ts[0], &ss.st_atime, sizeof(ts[0]));
  memcpy(&ts[1], &ss.st_mtime, sizeof(ts[1]));

  if (futimens(fd, ts) == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }


  exit(EXIT_SUCCESS);
}
