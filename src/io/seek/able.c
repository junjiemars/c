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

  if (buf.st_mode & S_IFIFO)
    {
      printf("named pipe (fifo) file\n");
    }
  else if (buf.st_mode & S_IFCHR)
    {
      printf("character special file\n");
    }
  else if (buf.st_mode & S_IFBLK)
    {
      printf("block special file\n");
    }
  else if (buf.st_mode & S_IFIFO)
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
