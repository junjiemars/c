#include <_io_.h>

/*
 * same as `create'.
 *
 */

int
main(int argc, char **argv)
{
  int  fd;

  if (argc < 2)
    {
      fprintf(stderr, "usage: <filename>\n");
      exit(EXIT_FAILURE);
    }

  fd = open(argv[1], O_CREAT, 0644);
  if (fd == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }


  exit(EXIT_SUCCESS);
}
