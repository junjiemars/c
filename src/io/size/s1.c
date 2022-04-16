#include "_io_.h"

int
main(int argc, char **argv)
{
  struct stat  buf;

  if (argc < 2)
    {
      fprintf(stderr, "usage: %s <pathname>\n", basename(argv[0]));
      exit(EXIT_FAILURE);
    }

  if (lstat(argv[1], &buf) == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  printf("size: %lld\nblock size: %d\nblocks: %lld\n",
         buf.st_size, buf.st_blksize, buf.st_blocks);


  exit(EXIT_SUCCESS);
}
