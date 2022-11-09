#include "_io_.h"


int
main(int argc, char **argv)
{
  if (argc < 3)
    {
      fprintf(stderr, "usage: <old> <new>\n");
      exit(EXIT_FAILURE);
    }

  if (renameat(AT_FDCWD, argv[1], AT_FDCWD, argv[2]) == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  exit(EXIT_SUCCESS);
}
