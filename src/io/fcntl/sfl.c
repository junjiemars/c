#include "_io_.h"

/*
 * 1. F_SETFL
 *
 */

#define ON   1
#define OFF  0


static void print_fl(int);
static int set_fl(int, int, int);


int
main(int argc, char **argv)
{
  int  fd;

  if (argc < 2)
    {
      fprintf(stderr, "usage: %s <pathname>\n", basename(argv[0]));
      exit(EXIT_FAILURE);
    }

  fd = open(argv[1], O_RDONLY | O_CREAT | O_APPEND | O_NONBLOCK,
            S_IRUSR | S_IWUSR);
  if (fd == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  print_fl(fd);


  if (set_fl(fd, O_APPEND, OFF) == -1)
    {
      perror(NULL);
    }
  print_fl(fd);

  if (set_fl(fd, O_NONBLOCK, OFF) == -1)
    {
      perror(NULL);
    }
  print_fl(fd);

  if (set_fl(fd, O_SYNC, ON) == -1)
    {
      perror(NULL);
    }
  print_fl(fd);

  if (set_fl(fd, O_APPEND, ON) == -1)
    {
      perror(NULL);
    }
  print_fl(fd);



  exit(EXIT_SUCCESS);

}

void
print_fl(int fd)
{
  int fl;
  fl = fcntl(fd, F_GETFL);
  if (fl == -1)
    {
      perror(NULL);
      return;
    }

  printf("O_GETFL(0x%04x): ", fl);

  switch (fl & O_ACCMODE)
    {
    case O_RDONLY:
      printf("%s", _str_(O_RDONLY));
      break;
    case O_WRONLY:
      printf("%s", _str_(O_WRONLY));
      break;
    case O_RDWR:
      printf("%s", _str_(O_RDWR));
      break;

#if defined(O_EXEC)
    case O_EXEC:
      printf("%s", _str_(O_EXEC));
      break;
#endif

#if defined(O_SEARCH)
    case O_SEARCH:
      printf("%s", _str_(O_SEARCH));
      break;
#endif
    default:
      printf("(0x%04x)", fl & O_ACCMODE);
      break;
    }

  if (fl & O_APPEND)
    {
      printf(",%s", _str_(O_APPEND));
    }
  if (fl & O_NONBLOCK)
    {
      printf(",%s", _str_(O_NONBLOCK));
    }
  if (fl & O_SYNC)
    {
      printf(",%s", _str_(O_SYNC));
    }

#if defined(O_FSYNC) && (O_FSYNC != O_SYNC)
  if (fl & O_FSYNC)
    {
      printf(",%s", _str_(O_FSYNC));
    }
#endif

  printf("\n");
}


int
set_fl(int fd, int flags, int on)
{
  int  fl, rc;

  fl = fcntl(fd, F_GETFL);
  if (fl == -1)
    {
      return -1;
    }

  if (on)
    {
      fl |= flags;
    }
  else
    {
      fl &= ~flags;
    }

  rc = fcntl(fd, F_SETFL, fl);
  if (rc == -1)
    {
      return -1;
    }

  return 0;
}
