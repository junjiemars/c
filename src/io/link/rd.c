#include <_io_.h>

int
main(int argc, char **argv)
{
  if (argc < 2)
    {
      fprintf(stderr, "usage: <dir>\n");
      exit(EXIT_FAILURE);
    }

  printf("rmdir %s... ", argv[1]);

  if (rmdir(argv[1]) == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  printf("done\n");


  exit(EXIT_SUCCESS);
}
