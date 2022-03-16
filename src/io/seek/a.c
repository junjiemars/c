#include "_io_.h"

/*
 * Q1: If you open a file for read-write with append flag, can you
 * still read from anywhere in the file using lseek?
 *
 * Q2: Can you use lseek to replace existing data in the file?
 *
 */

int
main(int argc, char **argv)
{
  int      fd;
  ssize_t  n;
  off_t    cur;
  char     buf1[]  =  "abcdefghij";
  char     buf2[]  =  "ABCDEFGHIJ";
  char     rbuf[64] = {0};

  if (argc < 2)
    {
      fprintf(stderr, "usage: %s <pathname>\n", basename(argv[0]));
      exit(EXIT_FAILURE);
    }

  fd = open(argv[1], O_RDWR | O_CREAT | O_APPEND | O_TRUNC, S_IRUSR | S_IWUSR);
  if (fd == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  n = write(fd, buf1, sizeof(buf1)-1);
  if (n == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  assert(n == sizeof(buf1)-1);

  cur = lseek(fd, 0, SEEK_CUR);
  if (cur == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  assert(cur == n);

  cur = lseek(fd, 0, SEEK_SET);
  if (cur == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  assert(cur == 0);

  n = read(fd, rbuf, sizeof(rbuf)-1);
  if (n == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  assert( n == sizeof(buf1)-1);

  n = write(fd, buf2, sizeof(buf2)-1);
  if (n == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  assert(n == sizeof(buf2)-1);

  exit(EXIT_SUCCESS);

}
