#include <_io_.h>
#include <time.h>


extern void copy_block(int, int);

int
main(int argc, char **argv)
{
  int     fd_src, fd_dst;
  double  elapsed  =  0;

  if (argc < 3)
    {
      fprintf(stderr, "usage: <src> <dst>\n");
      exit(EXIT_FAILURE);
    }

  fd_src = open(argv[1], O_RDONLY);
  if (fd_src == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  fd_dst = open(argv[2], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
  if (fd_dst == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  _time_(copy_block(fd_src, fd_dst), elapsed);

  printf("elapsed: %16lfs\n", elapsed);


  exit(EXIT_SUCCESS);
}
