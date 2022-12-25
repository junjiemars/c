#include "_io_.h"
#include <sys/mman.h>

int
main(int argc, char **argv)
{
  int           fdin, fdout;
  char         *src, *dst;
  off_t         fsz;
  size_t        bsz;
  struct stat   ss;

  if (argc < 3)
    {
      fprintf(stderr, "usage: <src> <dst>\n");
      exit(EXIT_FAILURE);
    }

  if ((fdin = open(argv[1], O_RDONLY)) == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  if (fstat(fdin, &ss) == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  if ((fdout = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0666)) == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  if (ftruncate(fdout, ss.st_size) == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  fsz = 0;
  src = NULL;
  dst = NULL;

  while (fsz < ss.st_size)
    {
      if ((ss.st_size - fsz) > NM_PAGESIZE)
        {
          bsz = NM_PAGESIZE;
        }
      else
        {
          bsz = ss.st_size - fsz;
        }

      src = mmap(0, bsz, PROT_READ, MAP_SHARED, fdin, fsz);
      if (src == MAP_FAILED)
        {
          perror(NULL);
          exit(EXIT_FAILURE);
        }

      dst = mmap(0, bsz, PROT_READ | PROT_WRITE, MAP_SHARED, fdout, fsz);
      if (dst == MAP_FAILED)
        {
          perror(NULL);
          exit(EXIT_FAILURE);
        }

      memcpy(dst, src, bsz);
      munmap(src, bsz);
      munmap(dst, bsz);

      fsz += bsz;
    }

  exit(EXIT_SUCCESS);
}
