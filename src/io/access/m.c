#include "_io_.h"

int
main(int argc, char **argv)
{
  int  fd, fl;

  if (argc < 2)
    {
      fprintf(stderr, "usage: %s <fd>\n", basename(argv[1]));
      exit(EXIT_FAILURE);
    }

  fd = atoi(argv[1]);

  fl = fcntl(fd, F_GETFL);
  if (fl == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  switch (fl & O_ACCMODE)
    {
    case O_RDONLY:
      printf("read only");
      break;

    case O_WRONLY:
      printf("write only");
      break;

    case O_RDWR:
      printf("read write");
      break;

    default:
      printf("(unknown access mode)");
    }

  if (fl & O_APPEND)
    {
      printf(", append");
    }

  if (fl & O_NONBLOCK)
    {
      printf(", nonblocking");
    }

  if (fl & O_SYNC)
    {
      printf(", synchronous writes");
    }

  putchar('\n');

  exit(EXIT_SUCCESS);

}
