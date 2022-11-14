#include "_io_.h"

/*
 * 1. Tom Duff is the author of /dev/fd feature and Duff Device.
 *
 * 2. open(/dev/fd/0) has the same manner as dup(0).
 *
 */


int
main(int argc, char *argv[])
{
  int           fd, fl;
  char         *dev  =  "/dev/fd/0";
  struct stat   ss;

  if (argc > 1)
    {
      dev = argv[1];
    }

  if (lstat(dev, &ss) == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  printf("link?(%s): %d\n", dev, S_ISLNK(ss.st_mode));

  printf("try to open with O_RDWR\n");
  if ((fd = open(dev, O_RDWR)) == -1)
    {
      perror(NULL);

      printf("try to open with O_RDONLY\n");
      if ((fd = open(dev, O_RDONLY)) == -1)
        {
          perror(NULL);
          exit(EXIT_FAILURE);
        }
    }

  if ((fl = fcntl(fd, F_GETFL)) == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  switch (fl & O_ACCMODE)
    {
    case O_RDONLY:
      printf("readonly?(%s): 1\n", dev);
      break;

    case O_WRONLY:
      printf("writeonly?(%s): 1\n", dev);
      break;

    case O_RDWR:
      printf("readwrite?(%s): 1\n", dev);
      break;
    }

  exit(EXIT_SUCCESS);
}
