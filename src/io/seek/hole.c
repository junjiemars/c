#include "_io_.h"


int
main(int argc, char **argv)
{
  int    fd, n;
  off_t  rc, offset;
  char dbuf[]  =  "abcdefghij";
  char ubuf[]  =  "ABCDEFGHIJ";

  if (argc < 2)
    {
      fprintf(stderr, "usage: %s <pathname> [holesize]\n",
              basename(argv[0]));
      exit(EXIT_FAILURE);
    }

  fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR);
  if (fd == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  n = write(fd, dbuf, sizeof(dbuf) - 1);
  if (n != sizeof(dbuf) - 1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  /* make hole */
  if (argc > 2)
    {
      offset = (off_t) atoi(argv[2]);
      rc = lseek(fd, offset, SEEK_SET);
      if (rc == -1)
        {
          perror(NULL);
          exit(EXIT_FAILURE);
        }
    }

  n = write(fd, ubuf, sizeof(ubuf) - 1);
  if (n != sizeof(ubuf) - 1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  exit(EXIT_SUCCESS);

}
