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

#define RW____ (S_IRUSR | S_IWUSR)
#define __RW__ (S_IRGRP | S_IWGRP)
#define ____RW (S_IROTH | S_IWOTH)

#define __RWRW (__RW__ | ____RW)
#define RWRWRW (RW____ | __RW__ | ____RW)



static void print_mask(int);
static int has_mask(int, int);



int
main(int argc, char **argv)
{
  int   rc;
  int   fd;
  char  path[PATH_MAX];

  if (argc < 2)
    {
      fprintf(stderr, "usage: %s <prefix>\n", basename(argv[0]));
      exit(EXIT_FAILURE);
    }

  sprintf(path, "%s/zoo", argv[1]);
  fd = creat(path, RWRWRW);
  if (fd == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  rc = umask(0);
  print_mask(rc);

  sprintf(path, "%s/foo", argv[1]);

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

void
print_mask(int m)
{
  printf("%c%c%c%c%c%c%c%c%c\n",
         (m & S_IRUSR) == S_IRUSR ? 'r' : '-',
         (m & S_IWUSR) == S_IWUSR ? 'w' : '-',
         (m & S_IXUSR) == S_IXUSR ? 'x' : '-',
         (m & S_IRGRP) == S_IRGRP ? 'r' : '-',
         (m & S_IWGRP) == S_IWGRP ? 'w' : '-',
         (m & S_IXGRP) == S_IXGRP ? 'x' : '-',
         (m & S_IROTH) == S_IROTH ? 'r' : '-',
         (m & S_IWOTH) == S_IWOTH ? 'w' : '-',
         (m & S_IXOTH) == S_IXOTH ? 'x' : '-');

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
