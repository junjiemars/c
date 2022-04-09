#include "_io_.h"


#define ON   1
#define OFF  0


#define pr_fl(fl, n, v)                               \
  do                                                  \
    {                                                 \
      printf("%s already turn %s\n",  n,              \
             ((fl) & (v))  ==  (v)  ? "on" : "off");  \
    } while (0)


int set_fl(int, int, int);


int
main(int argc, char **argv)
{
  int  fd, fl;

  if (argc < 2)
    {
      fprintf(stderr, "usage: %s <pathname>\n", basename(argv[0]));
      exit(EXIT_FAILURE);
    }

  fd = open(argv[1], O_RDONLY | O_CREAT | O_NONBLOCK, S_IRUSR | S_IWUSR);
  if (fd == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  /* change fl */
  if (set_fl(fd, O_NONBLOCK, OFF) == -1)
    {
      fprintf(stderr, "!panic: turn %s off failed\n", _str_(O_NONBLOCK));
    }

  if (set_fl(fd, O_APPEND, ON) == -1)
    {
      fprintf(stderr, "!panic: turn %s on failed\n", _str_(O_APPEND));
    }

  if (set_fl(fd, O_SYNC, ON) == -1)
    {
      fprintf(stderr, "!panic: turn %s on failed\n", _str_(O_SYNC));
    }

  /* changed? */
  fl = fcntl(fd, F_GETFL);
  if (fl == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  pr_fl(fl, _str_(O_NONBLOCK), O_NONBLOCK);
  pr_fl(fl, _str_(O_APPEND), O_APPEND);
  pr_fl(fl, _str_(O_SYNC), O_SYNC);


  exit(EXIT_SUCCESS);

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
