#include <_io_.h>


/*
 * 1. The default file mode creation mask: 666 for file, 777 for
 * directory.
 *
 * 2. Any bits that are in the file mode creation mask are turn off in
 * the file's mode.
 *
 * 3. The symbolic format of umask command specifies which permission
 * are to be turn on.
 *
 * 4. New file permissions: 666 & ~(umask)
 *
 * 5. New directory permissions: 777 & ~(umask)
 *
 */

#define RWRWRW (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)
#define __RWRW (S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)
#define RW____ (S_IRUSR | S_IWUSR)


static int has_mask(int, int);


int
main(int argc, char **argv)
{
  int   fd;
  char  path[PATH_MAX];

  if (argc < 2)
    {
      fprintf(stderr, "usage: %s <prefix>\n", basename(argv[0]));
      exit(EXIT_FAILURE);
    }

  sprintf(path, "%s/foo", argv[1]);
  umask(0);
  fd = creat(path, RWRWRW);
  if (fd == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  assert(RWRWRW == has_mask(fd, RWRWRW));


  sprintf(path, "%s/bar", argv[1]);
  umask(__RWRW);
  fd = creat(path, RWRWRW);
  if (fd == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  assert(RW____ == has_mask(fd, RW____));


  exit(EXIT_SUCCESS);
}


int
has_mask(int fd, int mask)
{
  struct stat  ss;

  if (fstat(fd, &ss) == -1)
    {
      perror(NULL);
      return -1;
    }

  return ss.st_mode & mask;
}
