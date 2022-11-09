#include "_io_.h"

/*
 * Q1: If you open a file for read-write with append flag, can you
 * still read from anywhere in the file using `lseek'?
 *
 * A1: Yes.
 *
 * Q2: Can you use `lseek' to replace existing data in the file?
 *
 * A2: No.
 *
 */


#define ALPHA_L  "abcdefghij"
#define ALPHA_U  "ABCDEFGHIJKLMN"

int
main(int argc, char **argv)
{
  int      fd;
  off_t    cur;
  ssize_t  n;
  char     rbuf[sizeof(ALPHA_L) + sizeof(ALPHA_U) + 1];

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

  n = write(fd, ALPHA_L, sizeof(ALPHA_L)-1);
  if (n != sizeof(ALPHA_L)-1)
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
  assert(n == sizeof(ALPHA_L)-1);

  /* A2 */
  cur = lseek(fd, 0, SEEK_SET);
  if (cur == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  assert(cur == 0);

  n = write(fd, ALPHA_U, sizeof(ALPHA_U)-1);
  if (n != sizeof(ALPHA_U)-1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }


  exit(EXIT_SUCCESS);

}
