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

  printf("size: %lld\nblock size: %ld\nblocks: %lld\n",
         buf.st_size,
         (long long int) buf.st_blksize,
         (long int) buf.st_blocks);


  exit(EXIT_SUCCESS);
}
