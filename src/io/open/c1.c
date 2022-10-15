#include <_io_.h>

/*
 * A. If the file exists:
 * 1) `creat' same as open(file, O_RDWR) and then fchmod(fd, mode);
 * 2) but `creat' doesn't change the final mode of the file.
 *
 * B. If the file doesn't exist:
 * 1) `creat' same as open(file, O_RDWR) and then fchmod(fd, mode);
 *
 */

#define BUF  "abc\n"


int
main(int argc, char **argv)
{
  int  fd, rc;

  if (argc < 2)
    {
      fprintf(stderr, "usage: <filename>\n");
      exit(EXIT_FAILURE);
    }

  fd = creat(argv[1], 0644);
  if (fd == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  rc = write(fd, BUF, sizeof(BUF) - 1);
  if (rc != sizeof(BUF) - 1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }


  exit(EXIT_SUCCESS);
}
