#include "_io_.h"

/*
 * 1. F_GETFL
 *
 */


int
main(int argc, char **argv)
{
  int  fd, fstatus;

  if (argc < 2)
    {
      fprintf(stderr, "usage: %s <fd>\n", basename(argv[0]));
      exit(EXIT_FAILURE);
    }
  fd = atoi(argv[1]);

  fstatus = fcntl(fd, F_GETFL);
  if (fstatus == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  /* access mode */
  switch (fstatus & O_ACCMODE)
    {
    case O_RDONLY:
      printf("%s: 0x%04x", _str_(O_RDONLY), O_RDONLY);
      break;

    case O_WRONLY:
      printf("%s: 0x%04x", _str_(O_WRONLY), O_WRONLY);
      break;

    case O_RDWR:
      printf("%s: 0x%04x", _str_(O_RDWR), O_RDWR);
      break;

#if defined(O_EXEC)
    case O_EXEC:
      printf("execute only");
      break;

#endif  /* O_EXEC */

#if defined(O_SEARCH)
    case O_SEARCH:
      printf("%s: 0x%04x", _str_(O_SEARCH), O_SEARCH);
      break;

#endif  /* O_SEARCH */

    default:
      printf("(no symbol): 0x%04x", (fstatus & O_ACCMODE));
      break;
    }

  /* optional */
  if (fstatus & O_APPEND)
    {
      printf(", %s: 0x%04x", _str_(O_APPEND), O_APPEND);
    }

  if (fstatus & O_NONBLOCK)
    {
      printf(", %s: 0x%04x", _str_(O_NONBLOCK), O_NONBLOCK);
    }

  if (fstatus & O_SYNC)
    {
      printf(", %s: 0x%04x", _str_(O_SYNC), O_SYNC);
    }

#if defined(O_FSYNC) && (O_FSYNC != O_SYNC)
  if (fstatus & O_FSYNC)
    {
      printf(", %s: 0x%04x", _str_(O_FSYNC), O_FSYNC);
    }

#endif  /* O_FSYNC */

  putchar('\n');

  exit(EXIT_SUCCESS);

}
