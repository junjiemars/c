#include "_io_.h"
#include <errno.h>

/*
 * 1. It's unseekable when fd point to a pipe, FIFO, or socket.
 *
 */


int
main(int argc, char **argv)
{

  int          fd;
  off_t        offset;
  struct stat  buf;


  if (argc < 2)
    {
      fprintf(stderr, "usage: %s <fileno>\n", basename(argv[0]));
      exit(EXIT_FAILURE);
    }

  fd = atoi(argv[1]);

  if (fstat(fd, &buf) == -1)
    {
      perror("!panic");
      exit(EXIT_FAILURE);
    }

  if (S_ISFIFO(buf.st_mode))
    {
      printf("named pipe (fifo) file\n");
    }
  else if (S_ISCHR(buf.st_mode))
    {
      printf("character special file\n");
    }
  else if (S_ISBLK(buf.st_mode))
    {
      printf("block special file\n");
    }
  else if (S_ISREG(buf.st_mode))
    {
      printf("regular file\n");
    }
  else
    {
      printf("st_mode = %d\n", buf.st_mode);
    }

  offset = lseek(fd, 0, SEEK_CUR);
  if (offset == -1)
    {
      printf("cannot seek\n");
    }
  else
    {
      printf("seekable\n");
    }

  exit(EXIT_SUCCESS);
}
