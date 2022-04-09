#include "_io_.h"

/*
 * Q1: If you open a file for read-write with append flag, can you
 * still read from anywhere in the file using lseek?
 *
 * Q2: Can you use lseek to replace existing data in the file?
 *
 */

#define ALPHA_L10  "abcdefghij"
#define ALPHA_U10  "ABCDEFGHIJ"

int
main(int argc, char **argv)
{
  int      fd;
  off_t    cur;
  ssize_t  n;
  char     buf1[]  =  ALPHA_L10;
  char     buf2[]  =  ALPHA_U10;
  char     rbuf[sizeof(ALPHA_L10) * 2];

  if (argc < 2)
    {
      fprintf(stderr, "usage: %s <pathname>\n", basename(argv[0]));
      exit(EXIT_FAILURE);
    }

  fd = open(argv[1], O_RDWR | O_APPEND | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
  if (fd == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  n = write(fd, buf1, sizeof(buf1)-1);
  if (n != sizeof(buf1)-1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  cur = lseek(fd, 0, SEEK_CUR);
  if (cur == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  assert(cur == n);

  /* A1 */
  cur = lseek(fd, 0, SEEK_SET);
  if (cur == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  assert(cur == 0);

  n = read(fd, rbuf, sizeof(rbuf));
  if (n == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  assert(n == sizeof(buf1)-1);

  /* A2 */
  cur = lseek(fd, -3, SEEK_CUR);
  if (cur == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  assert(cur == sizeof(buf1)-3-1);

  n = write(fd, buf2, sizeof(buf2)-1);
  if (n != sizeof(buf2)-1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }


  exit(EXIT_SUCCESS);

}
