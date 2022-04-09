#include "_io_.h"

/*
 * file status flags
 *
 */


int
main(int argc, char **argv)
{
  int  fd, fl;

  if (argc < 2)
    {
      fprintf(stderr, "usage: %s <fd>\n", basename(argv[0]));
      exit(EXIT_FAILURE);
    }

  fd = atoi(argv[1]);

  fl = fcntl(fd, F_GETFL, 0);
  if (fl == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  /* access mode */
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

#if defined(O_EXEC)
    case O_EXEC:
      printf("execute only");
      break;

#endif  /* O_EXEC */

#if defined(O_SEARCH)
    case O_SEARCH:
      printf("searching only");
      break;

#endif  /* O_SEARCH */

    default:
      printf("(unknown access mode)");
      break;
    }

  /* optional */
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
