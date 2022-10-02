#include <_io_.h>

/*
 * A) size:
 * 1. regular file: actual bytes.
 *
 * 2. symbol link: the bytes of the absolute pathname of the link
 * point to.
 *
 * 3. device: 0.
 *
 * 4. directory: a multiple bytes of sizeof(short) or sizeof(int).
 *
 * B) block size: preferred for I/O for the file.
 *
 * C) blocks: 512-byte blocks that are allocated.
 *
 */


int
main(int argc, char **argv)
{
  struct stat  buf;

  if (argc < 2)
    {
      fprintf(stderr, "usage: %s <pathname> [pathname...]\n",
              basename(argv[0]));
      exit(EXIT_FAILURE);
    }

  for (int i = 1; i < argc; i++)
    {
      if (lstat(argv[i], &buf) == -1)
        {
          perror(argv[i]);
          continue;
        }

      printf("%s: size(%lld), block size(%lld), blocks(%lld)\n",
             argv[i],
             (long long int) buf.st_size,
             (long long int) buf.st_blksize,
             (long long int) buf.st_blocks);
    }


  exit(EXIT_SUCCESS);
}
