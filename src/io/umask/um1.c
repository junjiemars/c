#include <_io_.h>


int
main(int argc, char **argv)
{
  if (argc < 2)
    {
      fprintf(stderr, "usage: <path>\n");
      exit(EXIT_FAILURE);
    }

  if (chmod(argv[1], S_ISUID) == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  exit(EXIT_SUCCESS);
}
