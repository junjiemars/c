#include <_io_.h>

/*
 * 1. O_SYNC: each `write' wait for physical I/O to complete,
 * including I/O neccessary to update file attributes modified as a
 * result of the `write'.
 *
 * 2. O_DSYNC: each `write' wait for physical I/O to complete, but
 * don't wait for file attributes to be updated if they don't affect
 * the ability to read the data just written.
 *
 * 3. O_RSYNC: each `read' on the file descriptor wait until any
 * pending writes for the same portion of the file are complete.
 *
 */

int
main(int argc, char **argv)
{
  int          fd;
  int          oflags;
  const char  *ss  =  "abc";
  size_t       n   =  sizeof(ss);

#if (O_SYNC)
  printf("%s=0x%x\n", _str_(O_SYNC), O_SYNC);
#endif

#if (O_DSYNC)
  printf("%s=0x%x\n", _str_(O_DSYNC), O_DSYNC);
#endif

#if (O_RSYNC)
  printf("%s=0x%x\n", _str_(O_RSYNC), O_RSYNC);
#endif

  if (argc < 2)
    {
      printf("usage: <pathname>\n");
      exit(EXIT_FAILURE);
    }


  oflags = O_WRONLY | O_CREAT | O_SYNC;

  fd = open(argv[1], oflags, S_IRUSR);
  if (fd == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  if (write(fd, ss, n-1) == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  exit(EXIT_SUCCESS);
}
