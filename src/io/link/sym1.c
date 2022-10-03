#include <_io_.h>


int
main(int argc, char **argv)
{
  struct stat  ss;

  if (argc < 3)
    {
      fprintf(stderr, "usage: <actualpath> <sympath>\n");
      exit(EXIT_FAILURE);
    }

  if (symlinkat(argv[1], AT_FDCWD, argv[2]) == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  if (lstat(argv[2], &ss) == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  assert(S_ISLNK(ss.st_mode));


  exit(EXIT_SUCCESS);
}
