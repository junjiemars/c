#include "_io_.h"

/*
 * 1. file descriptor always independent each other in process table.
 * 2. file table entry can be shared after dup.
 * 3. the same file share the same file table entry.
 */

int
main(int argc, char **argv)
{
  int  rc;
  int  ofds, nfds;
  int  ofls, nfls, ofls3;
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

  /* get file status flags for fd1 */
  ofls = fcntl(fd1, F_GETFL);
  if (ofls == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  /* get file status flags for fd3 */
  ofls3 = fcntl(fd3, F_GETFL);
  if (ofls3 == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  /* set file status flags for fd2 */
  nfls = (ofls & O_APPEND) ? (ofls & ~O_APPEND) : (ofls | O_APPEND);
  rc = fcntl(fd2, F_SETFL, nfls);
  if (rc == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  /* get file status flags for fd1 */
  ofls = fcntl(fd1, F_GETFL);
  if (ofls == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  assert(ofls == nfls);

  /* get file status flags for fd3 */
  ofls = fcntl(fd3, F_GETFL);
  if (ofls == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  assert(ofls3 == ofls);


  exit(EXIT_SUCCESS);

}
