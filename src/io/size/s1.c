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

  printf("size: %lld\nblock size: %lld\nblocks: %lld\n",
         (long long int) buf.st_size,
         (long long int) buf.st_blksize,
         (long long int) buf.st_blocks);


  exit(EXIT_SUCCESS);
}
