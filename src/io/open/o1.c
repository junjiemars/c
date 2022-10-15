#include <_io_.h>

/*
 * The only way to retrieve fd!?.
 *
 * 1. convert file name to inode.
 *
 * 2. allocate file table entry for inode, initialize offset.
 *
 * 3. allocate an entry in user fd table, set pointer to file table
 * entry.
 *
 * 4. return the index of the entry in user fd table.
 *
 */


int
main(int argc, char **argv)
{
  int fd;

  if (argc < 2)
    {
      printf("usage: <path>\n");
      exit(EXIT_FAILURE);
    }

  fd = openat(AT_FDCWD, argv[1], O_RDONLY);
  if (fd == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  exit(EXIT_SUCCESS);
}
