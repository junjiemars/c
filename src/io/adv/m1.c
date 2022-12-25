#include "_io_.h"
#include <sys/mman.h>

int
main(int argc, char **argv)
{
  char         *src, *dst;
  int           rfd, wfd;
  char         *rptr, *wptr;
  struct stat   ss;

  if (argc < 3)
    {
      fprintf(stderr, "usage: <src> <dst>\n");
      exit(EXIT_FAILURE);
    }
  src = argv[1];
  dst = argv[2];

  rfd = open(src, O_RDONLY);
  if (rfd == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  if (fstat(rfd, &ss) == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  wfd = open(dst, O_RDWR | O_CREAT | O_TRUNC, 0666);
  if (wfd == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  rptr = NULL;
  wptr = NULL;

  rptr = mmap(0, ss.st_size, PROT_READ, MAP_SHARED, rfd, 0);
  if (rptr == MAP_FAILED)
    {
      perror(NULL);
      goto clean_exit;
    }

  wptr = mmap(0, ss.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, wfd, 0);
  if (wptr == MAP_FAILED)
    {
      perror(NULL);
      goto clean_exit;
    }

  /* memcpy(wptr, rptr, ss.st_size); */

 clean_exit:
  if (wptr != NULL && wptr != MAP_FAILED)
    {
      if (munmap(wptr, ss.st_size) == -1)
        {
          perror(NULL);
        }
    }
  if (rptr != NULL && rptr != MAP_FAILED)
    {
      if (munmap(rptr, ss.st_size) == -1)
        {
          perror(NULL);
        }
    }

  exit(EXIT_SUCCESS);
}
