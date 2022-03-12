#include "_io_.h"

int
main(int argc, char **argv)
{
  int    fd, n;
  off_t  off;
  char dbuf[]  =  "abcdefghij";
  char ubuf[]  =  "ABCDEFGHIJ";

  if (argc < 2)
    {
      fprintf(stderr, "usage: %s <pathname> [yes|no]\n", argv[0]);
      exit(EXIT_FAILURE);
    }

  fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR);
  if (fd == -1)
    {
      perror("!panic");
      exit(EXIT_FAILURE);
    }

  n = write(fd, dbuf, sizeof(dbuf) - 1);
  if (n != sizeof(dbuf) - 1)
    {
      perror("!panic");
      exit(EXIT_FAILURE);
    }

  /* make hole */
  if (argc < 3 || strcmp("yes", argv[2]) == 0)
    {
      off = lseek(fd, 4096 /* guess */, SEEK_END);
      if (off == -1)
        {
          perror("!panic");
          exit(EXIT_FAILURE);
        }
    }

  n = write(fd, ubuf, sizeof(ubuf) - 1);
  if (n != sizeof(ubuf) - 1)
    {
      perror("!panic");
      exit(EXIT_FAILURE);
    }

  exit(EXIT_SUCCESS);

}
