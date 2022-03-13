#include "_io_.h"

/*
 * 1. file descriptor always independent.
 * 2. file table entry can be sharing after dup.
 *
 */

int
main(int argc, char **argv)
{
  int  rc;
  int  ofds, nfds;
  int  ofls, nfls;
  int  fd1, fd2, fd3;

  if (argc < 2)
    {
      fprintf(stderr, "usage: %s <pathname>\n", basename(argv[0]));
      exit(EXIT_FAILURE);
    }

  fd1 = open(argv[1], O_RDONLY | O_CREAT | O_TRUNC, S_IRUSR);
  if (fd1 == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  fd2 = dup(fd1);
  if (fd2 == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  fd3 = open(argv[1], O_RDONLY | O_CREAT | O_APPEND, S_IRUSR);
  if (fd3 == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  ofds = fcntl(fd1, F_GETFD);
  nfds = (ofds & FD_CLOEXEC) ? (ofds & ~FD_CLOEXEC) : (ofds | FD_CLOEXEC);
  rc = fcntl(fd2, F_SETFD, nfds);
  if (rc == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  ofds = fcntl(fd1, F_GETFD);
  if (ofds == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  assert(ofds != nfds);

  ofls = fcntl(fd1, F_GETFL);
  nfls = (ofls & O_APPEND) ? (ofls & ~O_APPEND) : (ofls | O_APPEND);
  if (nfls == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  rc = fcntl(fd2, F_SETFL, nfls);
  if (rc == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  ofls = fcntl(fd1, F_GETFL);
  if (ofls == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  assert(ofls == nfls);


  exit(EXIT_SUCCESS);

}
