#include "_io_.h"

/*
 * Assume that a process executes the following three function calls:
 * fd1 = open(path, oflags)
 * fd2 = dup(fd1);
 * fd3 = open(path, oflags);
 *
 * Q1: Which fildes are affected by an fcntl on fd1 with a command of F_SETFD?
 * Q2: Which fildes are affected by an fcntl on fd1 with a command of F_SETFL?
 *
 */


#define OFLAGS  O_RDWR | O_CREAT | O_APPEND
#define MFLAGS  S_IRUSR | S_IWUSR

void check_flag(int, int, const char*, int);


int
main(int argc, char **argv)
{
  int  fd1, fd2, fd3;
  int  flag;

  if (argc < 2)
    {
      fprintf(stderr, "usage: %s <pathname>\n", basename(argv[0]));
      exit(EXIT_FAILURE);
    }


  /* open fd1, fd2, fd3 */
  fd1 = open(argv[1], OFLAGS, MFLAGS);
  if (fd1 == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  check_flag(fd1, F_GETFD, _str_(FD_CLOEXEC), FD_CLOEXEC);


  fd2 = dup(fd1);
  if (fd2 == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  check_flag(fd2, F_GETFD, _str_(FD_CLOEXEC), FD_CLOEXEC);


  fd3 = open(argv[1], OFLAGS, MFLAGS);
  if (fd3 == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  check_flag(fd3, F_GETFD, _str_(FD_CLOEXEC), FD_CLOEXEC);

  /* set fd flag on fd1 */
  flag = fcntl(fd1, F_GETFD);
  if (flag == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  flag |= FD_CLOEXEC;
  if (fcntl(fd1, F_SETFD, flag) == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  printf("turn %d's %s on\n", fd1, _str_(FD_CLOEXEC));

  /* A1 */
  check_flag(fd1, F_GETFD, _str_(FD_CLOEXEC), FD_CLOEXEC);
  check_flag(fd2, F_GETFD, _str_(FD_CLOEXEC), FD_CLOEXEC);
  check_flag(fd3, F_GETFD, _str_(FD_CLOEXEC), FD_CLOEXEC);


  /* set fl flag on fd1 */
  flag = fcntl(fd1, F_GETFL);
  if (flag == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  flag |= O_SYNC;
  if (fcntl(fd1, F_SETFL, flag))
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  printf("turn %d's %s on\n", fd1, _str_(O_SYNC));

  /* A2 */
  check_flag(fd1, F_GETFL, _str_(O_SYNC), O_SYNC);
  check_flag(fd2, F_GETFL, _str_(O_SYNC), O_SYNC);
  check_flag(fd3, F_GETFL, _str_(O_SYNC), O_SYNC);


  exit(EXIT_SUCCESS);
}


void
check_flag(int fd, const int op, const char *name, int flag)
{
  int fl;

  fl = fcntl(fd, op);
  if (fl == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  printf("%4d: %c %s\n", fd, (fl & flag) == flag ? '+' : '-', name);
}
